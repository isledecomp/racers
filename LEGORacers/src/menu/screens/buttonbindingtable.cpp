#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"
#include "menu/screens/menugamescreen.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuGameScreen::ButtonBindingTable, 0x60)
DECOMP_SIZE_ASSERT(MenuGameScreen::ButtonBindingTable::ButtonBinding, 0xe0)
DECOMP_SIZE_ASSERT(MenuGameScreen::ButtonBindingTable::MidTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x0047f0a0
MenuGameScreen::ButtonBindingTable::ButtonBindingTable()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047f110
MenuGameScreen::ButtonBindingTable::~ButtonBindingTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0047f160
void MenuGameScreen::ButtonBindingTable::Reset()
{
	m_entries = NULL;
	MenuInputBindingTable::Clear();
}

// FUNCTION: LEGORACERS 0x0047f170
void MenuGameScreen::ButtonBindingTable::Clear()
{
	if (m_nameEntries) {
		if (m_entries) {
			delete[] m_entries;
		}

		MenuInputBindingTable::Clear();
	}
}

// FUNCTION: LEGORACERS 0x0047f1a0
void MenuGameScreen::ButtonBindingTable::CreateParser(undefined4 p_param)
{
	if (p_param) {
		m_parser = new GolBinParser();
		if (m_parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_parser->SetSuffix(".mib");
	}
	else {
		m_parser = new MidTxtParser();
		if (m_parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// FUNCTION: LEGORACERS 0x0047f290
void MenuGameScreen::ButtonBindingTable::ParseSection(undefined4 p_arg1)
{
	if (p_arg1 != 0x46) {
		MenuInputBindingTable::ParseSection(p_arg1);
		return;
	}

	ParseButtonSection();
}

// FUNCTION: LEGORACERS 0x0047f2b0
void MenuGameScreen::ButtonBindingTable::ParseButtonBinding(ButtonBinding* p_entry)
{
	InitIconDefaults(p_entry);
	::memset(p_entry->m_stateColors, 0xff, sizeof(p_entry->m_stateColors));

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_font: {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_stateFonts[i] = m_renderer->FindFontByName(m_parser->ReadString());
			}
			break;
		}
		case MidTxtParser::e_image: {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_stateImages[i] = m_renderer->FindImageByName(m_parser->ReadString());
			}
			break;
		}
		case MidTxtParser::e_colors: {
			ReadVisualState(p_entry->m_unk0xd0.m_bytes);

			LegoS32 i;
			for (i = 0; i < 6; i++) {
				ReadVisualState(p_entry->m_stateColors[i].m_bytes);
			}

			for (i = 0; i < 6; i++) {
				ReadVisualState(p_entry->m_iconStateColors[i].m_bytes);
			}

			p_entry->m_hasStateColors = TRUE;
			break;
		}
		case MidTxtParser::e_value:
			p_entry->m_maxTextWidth = m_parser->ReadInteger();
			p_entry->m_hasMaxTextWidth = TRUE;
			break;
		default:
			ParseIconField(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0047f410
void MenuGameScreen::ButtonBindingTable::ParseButtonSection()
{
	LegoS32 entryCount = ReadSectionCount();
	m_entries = new ButtonBinding[entryCount];
	::memset(m_entries, 0, sizeof(ButtonBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != MidTxtParser::e_button) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_entries[i]);
		ParseButtonBinding(&m_entries[i]);
	}
}
