#include "cinderbasin0x28.h"

#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfontbase0x40.h"
#include "golhashtable.h"
#include "golstream.h"
#include "golstring.h"
#include "goltxtparser.h"
#include "whitebaffoon0x50.h"

#include <string.h>

DECOMP_SIZE_ASSERT(FdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CinderBasin0x28::FontParseStyle, 0x0c)
DECOMP_SIZE_ASSERT(CinderBasin0x28, 0x28)

// FUNCTION: GOLDP 0x1001d830
CinderBasin0x28::CinderBasin0x28()
{
	m_renderer = NULL;
	m_numItems = 0;
	m_unk0x24 = 0;
}

// FUNCTION: GOLDP 0x1001d870
CinderBasin0x28::~CinderBasin0x28()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveFontList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x1001d8f0
void CinderBasin0x28::VTable0x20(BronzeFalcon0xc8770* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_numItems > 0) {
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
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

	m_numItems = parser->ReadBracketedCountAndLeftCurly();

	if (!m_numItems) {
		parser->Dispose();
		delete parser;
		return;
	}

	GolNameTable::Allocate(m_numItems);
	m_unk0x24 = g_hashTable ? (undefined4) g_hashTable->GetCurrentEntry() : 0;
	AllocateItems();

	for (LegoU32 i = 0; i < m_numItems; i++) {
		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		GolFontBase0x40* font = GetItem(i);

		FourBytes name[2];
		::strncpy(&name[0].m_bytes[0], parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		AddName(&name[0].m_bytes[0], font);

		parser->ReadLeftCurly();

		FontParseStyle style;
		style.m_foregroundColor.m_bytes[3] = -1;
		style.m_textColor.m_bytes[3] = -1;

		style.m_flags = 0;
		style.m_foregroundColor.m_bytes[0] = 0;
		style.m_foregroundColor.m_bytes[1] = 0;
		style.m_foregroundColor.m_bytes[2] = 0;
		style.m_textColor.m_bytes[0] = -1;
		style.m_textColor.m_bytes[1] = -1;
		style.m_textColor.m_bytes[2] = -1;

		GolFileParser::ParserTokenType token = parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				style.m_flags &= GolFontBase0x40::c_flagsWithoutBit4;
				style.m_flags |= GolFontBase0x40::c_flagBit3;
				break;
			case GolFileParser::e_unknown0x29:
				style.m_flags &= GolFontBase0x40::c_flagsWithoutBit3;
				style.m_flags |= GolFontBase0x40::c_flagBit4;
				break;
			case GolFileParser::e_unknown0x2a:
				style.m_flags |= GolFontBase0x40::c_flagBit5;
				style.m_foregroundColor.m_bytes[0] = parser->ReadInteger();
				style.m_foregroundColor.m_bytes[1] = parser->ReadInteger();
				style.m_foregroundColor.m_bytes[2] = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2c:
				font->m_unk0x20 = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2b: {
				LegoU16 count;
				undefined2 chars[100];
				CinderBasin0x28::ReadFontCharList(parser, chars, &count);
				m_unk0x20[i] = count;
				VTable0x10(i);
				::memcpy(m_unk0x1c[i], chars, 2 * count);
				m_unk0x1c[i][count] = 0;

				if (!m_unk0x18[i].CopyFromBufSelection(m_unk0x1c[i], m_unk0x20[i] + 1)) {
					GOL_FATALERROR(c_golErrorGeneral);
				}
				break;
			}
			case GolFileParser::e_unknown0x2d:
				style.m_textColor.m_bytes[0] = parser->ReadInteger();
				style.m_textColor.m_bytes[1] = parser->ReadInteger();
				style.m_textColor.m_bytes[2] = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = parser->GetNextToken();
		}

		font->m_nameParts[0] = name[0];
		LegoU32 flags = style.m_flags;
		font->m_nameParts[1] = name[1];
		font->m_colorPacked = *(LegoU32*) &style.m_textColor;
		font->m_unk0x2c = flags;

		if (flags & GolFontBase0x40::c_flagBit5) {
			font->m_unk0x38 = *(LegoU32*) &style.m_foregroundColor;
			font->m_unk0x2c = flags | GolFontBase0x40::c_flagBit11;
		}
	}

	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;

	if (g_hashTable) {
		g_hashTable->SetCurrentEntry((GolHashTable::Entry*) m_unk0x24);
	}

	for (LegoU32 j = 0; j < m_numItems; j++) {
		GolFontBase0x40* font = GetItem(j);
		font->FUN_1001df80(m_renderer, &m_unk0x18[j], m_unk0x20[j]);
	}
}

// FUNCTION: GOLDP 0x1001dd20
void __stdcall CinderBasin0x28::ReadFontCharList(GolFileParser* p_parser, undefined2* p_chars, LegoU16* p_count)
{
	*p_count = 0;

	if (p_parser->GetNextToken() != GolFileParser::e_leftBracket) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_leftBracket);
	}

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightBracket) {
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
		token = p_parser->GetNextToken();
	}
}

// FUNCTION: GOLDP 0x1001ddf0
void CinderBasin0x28::Clear()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveFontList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void CinderBasin0x28::ReleaseFontSurfaces()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void CinderBasin0x28::RefreshFontSurfaces()
{
	// empty
}
