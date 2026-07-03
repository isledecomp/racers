#include "menu/style/sharedmenustyletable.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"
#include "menu/style/menubindingtoken.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SharedMenuStyleTable, 0x50)
DECOMP_SIZE_ASSERT(SharedMenuStyleTable::MidTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00480550
SharedMenuStyleTable::SharedMenuStyleTable()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004805c0
SharedMenuStyleTable::~SharedMenuStyleTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00480610
void SharedMenuStyleTable::Reset()
{
	m_textButtonStyles = NULL;
	MenuStyleTable::Reset();
}

// FUNCTION: LEGORACERS 0x00480620
void SharedMenuStyleTable::Clear()
{
	if (m_nameEntries) {
		if (m_textButtonStyles) {
			delete[] m_textButtonStyles;
		}

		MenuStyleTable::Clear();
	}
}

// FUNCTION: LEGORACERS 0x00480650
void SharedMenuStyleTable::CreateParser(undefined4 p_param)
{
	if (p_param) {
		m_parser = new GolBinParser();
		if (!m_parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_parser->SetSuffix(".msb");
	}
	else {
		m_parser = new MidTxtParser();
		if (!m_parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// FUNCTION: LEGORACERS 0x00480740
void SharedMenuStyleTable::ParseSection(undefined4 p_arg1)
{
	switch (p_arg1) {
	default:
		MenuStyleTable::ParseSection(p_arg1);
		return;
	case c_styleBlockTextButton:
		LoadTextButtonStyles();
		return;
	}
}

// FUNCTION: LEGORACERS 0x00480760
void SharedMenuStyleTable::ParseTextButtonStyle(TextButtonStyle* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	::memset(p_entry->m_stateColors, 0xff, sizeof(p_entry->m_stateColors));

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case c_styleIcon:
			ParseIconStyle(p_entry);
			break;
		case c_styleFont:
			for (i = 0; i < 6; i++) {
				p_entry->m_stateFonts[i] = m_renderer->FindFontByName(m_parser->ReadString());
			}
			break;
		case c_styleImage:
			for (i = 0; i < 6; i++) {
				p_entry->m_stateImages[i] = m_renderer->FindImageByName(m_parser->ReadString());
			}
			break;
		case c_styleColors:
			ReadVisualState(p_entry->m_unk0xd8.m_bytes);

			for (i = 0; i < 6; i++) {
				ReadVisualState(p_entry->m_stateColors[i].m_bytes);
			}

			for (i = 0; i < 6; i++) {
				ReadVisualState(p_entry->m_iconStateColors[i].m_bytes);
			}

			p_entry->m_hasStateColors = TRUE;
			break;
		case TextButtonStyle::e_rects:
			ReadRect(&p_entry->m_unk0xdc.m_left);
			ReadRect(&p_entry->m_unk0xec.m_left);
			break;
		case TextButtonStyle::e_maxTextWidth:
			p_entry->m_maxTextWidth = m_parser->ReadInteger();
			p_entry->m_hasMaxTextWidth = TRUE;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x004808f0
void SharedMenuStyleTable::LoadTextButtonStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_textButtonStyles = new TextButtonStyle[entryCount];
	if (!m_textButtonStyles) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_textButtonStyles, 0, sizeof(TextButtonStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockTextButton) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_textButtonStyles[i]);
		ParseTextButtonStyle(&m_textButtonStyles[i]);
	}
}
