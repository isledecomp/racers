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
	Destroy();
}

// FUNCTION: LEGORACERS 0x00468a80
LegoS32 MenuDialog::Reset()
{
	m_entries = NULL;
	m_inputDispatcher = NULL;
	m_previousScreen = NULL;
	m_count = 0;
	m_openCount = 0;
	m_lastResult = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x00468ab0
LegoS32 MenuDialog::Destroy()
{
	MenuInputBindingTable* inputBindings = &m_bindingTable;
	inputBindings->Clear();

	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	Reset();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00468af0
LegoBool32 MenuDialog::Initialize(
	MenuScreenCreateParams* p_createParams,
	LegoS32 p_count,
	MenuInputDispatcher* p_inputDispatcher
)
{
	Destroy();

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
	params.m_binary = p_createParams->m_useBinaryFiles;

	return m_bindingTable.Load(&params);
}

// FUNCTION: LEGORACERS 0x00468c50
MenuDialog::DialogScreen* MenuDialog::OpenDialog(
	undefined4 p_type,
	undefined2 p_notifyId,
	MenuScreen* p_eventHandler,
	undefined4 p_defaultYes
)
{
	if (!m_openCount) {
		m_previousScreen = m_inputDispatcher->GetActiveScreen();
	}

	DialogScreen::CreateParams createParams;
	createParams.m_createParams = &m_createParams;
	createParams.m_owner = this;
	createParams.m_eventHandler = p_eventHandler;
	createParams.m_type = p_type;
	createParams.m_notifyId = p_notifyId;
	createParams.m_defaultYes = p_defaultYes;

	DialogScreen* entry = &m_entries[m_openCount];
	entry->Initialize(&createParams);
	m_inputDispatcher->SetActiveScreen(entry);
	m_openCount++;

	return entry;
}

// FUNCTION: LEGORACERS 0x00468cf0
void MenuDialog::DismissTop()
{
	m_entries[m_openCount - 1].BeginClose();
}

// FUNCTION: LEGORACERS 0x00468d20
void MenuDialog::CloseTop()
{
	m_openCount--;
	m_entries[m_openCount].Destroy();

	if (m_openCount > 0) {
		m_inputDispatcher->SetActiveScreen(&m_entries[m_openCount]);
	}
	else {
		m_inputDispatcher->SetActiveScreen(m_previousScreen);
	}
}

// FUNCTION: LEGORACERS 0x00468da0
void MenuDialog::Update(LegoU32 p_elapsedMs)
{
	if (m_openCount) {
		if (!m_entries[m_openCount - 1].Update(p_elapsedMs)) {
			m_lastResult = m_entries[m_openCount - 1].GetResult();
			CloseTop();
		}
	}
}

// FUNCTION: LEGORACERS 0x00468e20
void MenuDialog::DrawCursors()
{
	if (m_openCount) {
		m_inputDispatcher->SetActiveScreen(m_previousScreen);
		m_inputDispatcher->DrawCursor();

		for (LegoU32 i = 0; i < m_openCount; i++) {
			m_inputDispatcher->SetActiveScreen(&m_entries[i]);
			m_inputDispatcher->DrawCursor();
		}

		m_inputDispatcher->SetActiveScreen(&m_entries[m_openCount - 1]);
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
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046f8d0
void MenuDialog::TextLine::SetString(GolString* p_string, LegoS32 p_remeasure)
{
	GolString* originalString = p_string;
	LegoS32 width;
	LegoS32 height;
	LegoFloat heightFloat;

	m_string.CopyFromGolString(originalString);
	if (m_rect.m_right) {
		m_font->MeasureString(&m_string, &width, &height);

		if (width < m_rect.m_right - m_rect.m_left) {
			m_wrapped = FALSE;
			MenuTextLabel::SetString(originalString, p_remeasure);
			return;
		}
	}

	m_wrapped = TRUE;
	m_font->MeasureString(&m_string, m_wrapWidth, 0, m_scaleX, m_scaleY, &width, &height);

	if (m_rect.m_right && m_rect.m_bottom && !p_remeasure) {
		LegoS32 bottom = m_rect.m_bottom - m_rect.m_top;
		if (static_cast<LegoU32>(height) > static_cast<LegoU32>(bottom)) {
			heightFloat = static_cast<LegoFloat>(height);
			m_scaleY = static_cast<LegoFloat>(bottom) / heightFloat;
		}
	}
	else {
		m_rect.m_right = width + m_rect.m_left;
		m_rect.m_bottom = height + m_rect.m_top;
	}
}

// FUNCTION: LEGORACERS 0x0046f9b0
MenuWidget* MenuDialog::TextLine::DrawSelf(Rect* p_rect, Rect* p_arg)
{
	if (!m_wrapped) {
		return MenuTextLabel::DrawSelf(p_rect, p_arg);
	}

	LegoS32 xOffset = p_arg->m_left - p_rect->m_left;
	LegoS32 yOffset = p_arg->m_top - p_rect->m_top;

	m_string.FirstLine();

	Rect source;
	source.m_bottom = yOffset + m_rect.m_bottom - m_rect.m_top;
	source.m_top = yOffset;
	source.m_right = xOffset + m_rect.m_right - m_rect.m_left;
	source.m_left = xOffset;

	DrawString(&source, p_arg, m_font, &m_string, m_wrapWidth, m_style->m_centered);
	return NULL;
}
