#include "menu/style/sharedmenustyletable.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"
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
	case GolFileParser::e_unknown0x3e:
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

	::memset(p_entry->m_unk0xc0, 0xff, sizeof(p_entry->m_unk0xc0));

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x3a:
			ParseIconStyle(p_entry);
			break;
		case GolFileParser::e_unknown0x29:
			for (i = 0; i < 6; i++) {
				p_entry->m_unk0x90[i] = m_renderer->FindFontByName(m_parser->ReadString());
			}
			break;
		case GolFileParser::e_unknown0x28:
			for (i = 0; i < 6; i++) {
				p_entry->m_unk0xa8[i] = m_renderer->FindImageByName(m_parser->ReadString());
			}
			break;
		case GolFileParser::e_unknown0x2a:
			ReadVisualState(p_entry->m_unk0xd8.m_bytes);

			for (i = 0; i < 6; i++) {
				ReadVisualState(p_entry->m_unk0xc0[i].m_bytes);
			}

			for (i = 0; i < 6; i++) {
				ReadVisualState(p_entry->m_unk0x00[i].m_bytes);
			}

			p_entry->m_unk0x88 = TRUE;
			break;
		case GolFileParser::e_unknown0x2c:
			ReadRect(&p_entry->m_unk0xdc.m_left);
			ReadRect(&p_entry->m_unk0xec.m_left);
			break;
		case GolFileParser::e_unknown0x2e:
			p_entry->m_unk0xfc = m_parser->ReadInteger();
			p_entry->m_unk0x100 = TRUE;
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
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3e) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_textButtonStyles[i]);
		ParseTextButtonStyle(&m_textButtonStyles[i]);
	}
}
