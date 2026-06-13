#include "menu/menudialog.h"

#include "font/golfont.h"
#include "golerror.h"
#include "menu/menuinputdispatcher.h"

DECOMP_SIZE_ASSERT(MenuDialog, 0xa4)
DECOMP_SIZE_ASSERT(MenuDialog::TextLine, 0x78)

// GLOBAL: LEGORACERS 0x004c1ccc
const LegoChar* g_dialogMidFileName = "Dialog.mid";

// FUNCTION: LEGORACERS 0x004689e0
MenuDialog::MenuDialog()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00468a30
MenuDialog::~MenuDialog()
{
	FUN_00468ab0();
}

// FUNCTION: LEGORACERS 0x00468a80
LegoS32 MenuDialog::Reset()
{
	m_entries = NULL;
	m_inputDispatcher = NULL;
	m_previousScreen = NULL;
	m_count = 0;
	m_unk0x9c = 0;
	m_unk0xa0 = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x00468ab0
LegoS32 MenuDialog::FUN_00468ab0()
{
	MenuInputBindingTable* inputBindings = &m_unk0x00;
	inputBindings->Clear();

	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	Reset();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00468af0
LegoBool32 MenuDialog::FUN_00468af0(
	MenuScreenCreateParams* p_createParams,
	LegoS32 p_count,
	MenuInputDispatcher* p_inputDispatcher
)
{
	FUN_00468ab0();

	m_createParams = *p_createParams;
	m_inputDispatcher = p_inputDispatcher;
	m_count = p_count;
	m_entries = new DialogScreen[p_count];

	if (!m_entries) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	MenuInputBindingTable::ResourceLoadParams params;
	params.m_renderer = p_createParams->m_renderer;
	params.m_fileName = g_dialogMidFileName;
	params.m_binary = p_createParams->m_unk0x2c;

	return m_unk0x00.Load(&params);
}

// FUNCTION: LEGORACERS 0x00468c50
MenuDialog::DialogScreen* MenuDialog::FUN_00468c50(
	undefined4 p_unk0x04,
	undefined2 p_unk0x08,
	MenuScreen* p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (!m_unk0x9c) {
		m_previousScreen = m_inputDispatcher->GetActiveScreen();
	}

	DialogScreen::CreateParams createParams;
	createParams.m_createParams = &m_createParams;
	createParams.m_owner = this;
	createParams.m_eventHandler = p_unk0x0c;
	createParams.m_unk0x0c = p_unk0x04;
	createParams.m_unk0x10 = p_unk0x08;
	createParams.m_unk0x14 = p_unk0x10;

	DialogScreen* entry = &m_entries[m_unk0x9c];
	entry->FUN_00468300(&createParams);
	m_inputDispatcher->SetActiveScreen(entry);
	m_unk0x9c++;

	return entry;
}

// FUNCTION: LEGORACERS 0x00468cf0
void MenuDialog::FUN_00468cf0()
{
	m_entries[m_unk0x9c - 1].FUN_004687a0();
}

// FUNCTION: LEGORACERS 0x00468d20
void MenuDialog::FUN_00468d20()
{
	m_unk0x9c--;
	m_entries[m_unk0x9c].Destroy();

	if (m_unk0x9c > 0) {
		m_inputDispatcher->SetActiveScreen(&m_entries[m_unk0x9c]);
	}
	else {
		m_inputDispatcher->SetActiveScreen(m_previousScreen);
	}
}

// FUNCTION: LEGORACERS 0x00468da0
void MenuDialog::FUN_00468da0(LegoU32 p_elapsedMs)
{
	if (m_unk0x9c) {
		if (!m_entries[m_unk0x9c - 1].VTable0x78(p_elapsedMs)) {
			m_unk0xa0 = m_entries[m_unk0x9c - 1].GetUnk0x2c0();
			FUN_00468d20();
		}
	}
}

// FUNCTION: LEGORACERS 0x00468e20
void MenuDialog::FUN_00468e20()
{
	if (m_unk0x9c) {
		m_inputDispatcher->SetActiveScreen(m_previousScreen);
		m_inputDispatcher->DrawCursor();

		for (LegoU32 i = 0; i < m_unk0x9c; i++) {
			m_inputDispatcher->SetActiveScreen(&m_entries[i]);
			m_inputDispatcher->DrawCursor();
		}

		m_inputDispatcher->SetActiveScreen(&m_entries[m_unk0x9c - 1]);
	}
}

// FUNCTION: LEGORACERS 0x0046f810
MenuDialog::TextLine::TextLine()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046f880
MenuDialog::TextLine::~TextLine()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046f8d0
void MenuDialog::TextLine::VTable0x40(GolString* p_string, LegoS32 p_unk0x08)
{
	GolString* originalString = p_string;
	LegoS32 width;
	LegoS32 height;
	LegoFloat heightFloat;

	m_unk0x64.CopyFromGolString(originalString);
	if (m_unk0x34.m_right) {
		m_unk0x60->MeasureString(&m_unk0x64, &width, &height);

		if (width < m_unk0x34.m_right - m_unk0x34.m_left) {
			m_unk0x74 = FALSE;
			MenuTextLabel::VTable0x40(originalString, p_unk0x08);
			return;
		}
	}

	m_unk0x74 = TRUE;
	m_unk0x60->FUN_00408d50(&m_unk0x64, m_unk0x70, 0, m_unk0x44, m_unk0x48, &width, &height);

	if (m_unk0x34.m_right && m_unk0x34.m_bottom && !p_unk0x08) {
		LegoS32 bottom = m_unk0x34.m_bottom - m_unk0x34.m_top;
		if (static_cast<LegoU32>(height) > static_cast<LegoU32>(bottom)) {
			heightFloat = static_cast<LegoFloat>(height);
			m_unk0x48 = static_cast<LegoFloat>(bottom) / heightFloat;
		}
	}
	else {
		m_unk0x34.m_right = width + m_unk0x34.m_left;
		m_unk0x34.m_bottom = height + m_unk0x34.m_top;
	}
}

// FUNCTION: LEGORACERS 0x0046f9b0
MenuWidget* MenuDialog::TextLine::VTable0x38(Rect* p_rect, Rect* p_arg)
{
	if (!m_unk0x74) {
		return MenuTextLabel::VTable0x38(p_rect, p_arg);
	}

	LegoS32 xOffset = p_arg->m_left - p_rect->m_left;
	LegoS32 yOffset = p_arg->m_top - p_rect->m_top;

	m_unk0x64.FirstLine();

	Rect source;
	source.m_bottom = yOffset + m_unk0x34.m_bottom - m_unk0x34.m_top;
	source.m_top = yOffset;
	source.m_right = xOffset + m_unk0x34.m_right - m_unk0x34.m_left;
	source.m_left = xOffset;

	DrawString(&source, p_arg, m_unk0x60, &m_unk0x64, m_unk0x70, m_unk0x58->m_unk0x10);
	return NULL;
}
