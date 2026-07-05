#include "font/golfontlibrary.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golfontbase.h"
#include "golhashtable.h"
#include "golstream.h"
#include "golstring.h"
#include "goltxtparser.h"
#include "image/goltiledtexture.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolFontLibrary::FdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(GolFontLibrary::FontParseStyle, 0x0c)
DECOMP_SIZE_ASSERT(GolFontLibrary, 0x28)

// FUNCTION: GOLDP 0x1001d830
GolFontLibrary::GolFontLibrary()
{
	m_renderer = NULL;
	m_itemCount = 0;
	m_hashTableCheckpoint = NULL;
}

// FUNCTION: GOLDP 0x1001d870
GolFontLibrary::~GolFontLibrary()
{
	m_itemCount = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveFontList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x1001d8f0
void GolFontLibrary::LoadFontDefinitions(
	GolD3DRenderDevice* p_renderer,
	const LegoChar* p_fileName,
	LegoBool32 p_binary
)
{
	if (m_itemCount > 0) {
		Clear();
	}

	m_renderer = p_renderer;
	m_renderer->AddFontList(this);

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser();

		if (!parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".fdb");
	}
	else {
		parser = new FdbTxtParser();

		if (!parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(FdbTxtParser::e_font));

	m_itemCount = parser->ReadBracketedCountAndLeftCurly();

	if (!m_itemCount) {
		parser->Dispose();
		delete parser;
		return;
	}

	GolNameTable::Allocate(m_itemCount);
	m_hashTableCheckpoint = g_hashTable ? g_hashTable->GetCurrentEntry() : NULL;
	AllocateItems();

	for (LegoU32 i = 0; i < m_itemCount; i++) {
		parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(FdbTxtParser::e_font));

		GolFontBase* font = GetItem(i);

		FourBytes name[2];
		::strncpy(&name[0].m_bytes[0], parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		AddName(&name[0].m_bytes[0], font);

		parser->ReadLeftCurly();

		FontParseStyle style;
		style.m_colorKey.m_alp = 0xff;
		style.m_textColor.m_alp = 0xff;

		style.m_flags = 0;
		style.m_colorKey.m_red = 0;
		style.m_colorKey.m_grn = 0;
		style.m_colorKey.m_blu = 0;
		style.m_textColor.m_red = 0xff;
		style.m_textColor.m_grn = 0xff;
		style.m_textColor.m_blu = 0xff;

		GolFileParser::ParserTokenType token = parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case FdbTxtParser::e_bmp:
				style.m_flags = (style.m_flags & GolFontBase::c_flagsWithoutTga) | GolFontBase::c_flagBmpSource;
				break;
			case FdbTxtParser::e_tga:
				style.m_flags = (style.m_flags & GolFontBase::c_flagsWithoutBmp) | GolFontBase::c_flagTgaSource;
				break;
			case FdbTxtParser::e_colorKey:
				style.m_flags |= GolFontBase::c_flagColorKeyed;
				style.m_colorKey.m_red = parser->ReadInteger();
				style.m_colorKey.m_grn = parser->ReadInteger();
				style.m_colorKey.m_blu = parser->ReadInteger();
				break;
			case FdbTxtParser::e_charSpacing:
				font->m_charSpacing = parser->ReadInteger();
				break;
			case FdbTxtParser::e_characters: {
				LegoU16 count;
				undefined2 chars[100];
				ReadFontCharList(parser, chars, &count);
				m_charCounts[i] = count;
				AllocateDefinitionBuffer(i);
				::memcpy(m_charCodes[i], chars, 2 * count);
				m_charCodes[i][count] = 0;

				if (!m_charStrings[i].CopyFromBufSelection(m_charCodes[i], m_charCounts[i] + 1)) {
					GOL_FATALERROR(c_golErrorGeneral);
				}
				break;
			}
			case FdbTxtParser::e_textColor:
				style.m_textColor.m_red = parser->ReadInteger();
				style.m_textColor.m_grn = parser->ReadInteger();
				style.m_textColor.m_blu = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = parser->GetNextToken();
		}

		font->m_nameParts[0] = name[0];
		LegoU16 flags = (LegoU16) style.m_flags;
		font->m_nameParts[1] = name[1];
		font->m_colorPacked = style.m_textColorPacked;
		font->m_flags = flags;

		if (flags & GolFontBase::c_flagColorKeyed) {
			font->m_colorKeyPacked = style.m_colorKeyPacked;
			font->m_flags = flags | GolFontBase::c_flagBit11;
		}
	}

	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;

	if (g_hashTable) {
		g_hashTable->SetCurrentEntry(m_hashTableCheckpoint);
	}

	for (LegoU32 j = 0; j < m_itemCount; j++) {
		GolFontBase* font = GetItem(j);
		font->CreateGlyphs(m_renderer, &m_charStrings[j], m_charCounts[j]);
	}
}

// FUNCTION: GOLDP 0x1001dd20
void GolFontLibrary::ReadFontCharList(GolFileParser* p_parser, undefined2* p_chars, LegoU16* p_count)
{
	*p_count = 0;

	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightBracket) {
		switch (token) {
		case GolFileParser::e_string:
			LegoChar character;
			if (::strlen(p_parser->GetLastString()) > 1) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			}
			::strncpy(&character, p_parser->GetLastString(), 1);
			p_chars[*p_count] = static_cast<LegoU8>(character);
			break;
		case GolFileParser::e_int: {
			LegoS32 value = p_parser->GetLastInt();
			if (value < 0 || value > 0xffff) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			}
			p_chars[*p_count] = static_cast<undefined2>(value);
			break;
		}
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		(*p_count)++;
	}
}

// FUNCTION: GOLDP 0x1001ddf0
void GolFontLibrary::Clear()
{
	m_itemCount = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveFontList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolFontLibrary::ReleaseFontSurfaces()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolFontLibrary::RefreshFontSurfaces()
{
	// empty
}
