#include "menu/screens/saveloadscreen.h"

#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "save/savedirectory.h"
#include "save/savesystem.h"

DECOMP_SIZE_ASSERT(SaveLoadScreen, 0x1d7c)

// FUNCTION: LEGORACERS 0x00486b30
SaveLoadScreen::SaveLoadScreen()
{
	m_status = 0;
	m_requestMenuId = 0;
	m_saveIndex = 0;
	m_widgetsDirty = FALSE;
	m_unk0x1d78 = 0;
	m_skipFirstStatus = TRUE;
}

// FUNCTION: LEGORACERS 0x00486ca0
SaveLoadScreen::~SaveLoadScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00486dd0
LegoBool32 SaveLoadScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_requestMenuId = p_createParams->m_menuId;
	p_createParams->m_menuId = 0x32;
	m_saveIndex = p_context->m_modelBuilder.GetSaveSlot();
	ExecuteOperation(&p_context->m_saveSystem);

	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	m_cursor->SetCursorEnabled(FALSE);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00486e40
void SaveLoadScreen::ExecuteOperation(SaveSystem* p_source)
{
	LegoS32 emptyCount;
	LegoS32 statusEightCount;

	switch (m_requestMenuId) {
	case c_menuLoadAll: {
		emptyCount = 0;
		statusEightCount = 0;
		m_saveIndex = p_source->GetMemoryCardSaveCount() - 1;
		while (m_saveIndex >= 0) {
			LegoS32 status = p_source->LoadSlot(m_saveIndex, TRUE);
			m_status = status;
			if (!status) {
				emptyCount++;
			}
			else if (status == 8) {
				statusEightCount++;
			}

			m_saveIndex--;
		}

		LegoS32 status = 0;
		m_saveIndex = status;
		if (emptyCount != status) {
			m_status = status;
		}
		else if (statusEightCount > status) {
			m_status = 8;
		}
		break;
	}
	case c_menuLoadCard:
		m_status = p_source->LoadSlot(m_saveIndex, FALSE);
		break;
	case c_menuLcCreate: {
		LegoU32 status = p_source->GetMemoryCardSaves()[m_saveIndex].GetRecordCount();
		if (status > 0) {
			m_status = p_source->SaveSlot(m_saveIndex);
		}
		else {
			m_status = p_source->LoadSlot(m_saveIndex, TRUE);
		}
		m_skipFirstStatus = FALSE;
		break;
	}
	case c_menuSaveAll: {
		m_saveIndex = p_source->GetMemoryCardSaveCount() - 1;
		m_status = 0;
		while (m_saveIndex >= 0) {
			LegoS32 status = p_source->SaveSlot(m_saveIndex);
			if (status && status != 0x12 && status != 8) {
				m_status = status;
			}

			m_saveIndex--;
		}

		m_saveIndex = 0;
		break;
	}
	case c_menuSaveCard:
		m_status = p_source->SaveSlot(m_saveIndex);
		break;
	}

	m_status = 0;
}

// FUNCTION: LEGORACERS 0x00486ff0
LegoBool32 SaveLoadScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_cursor->SetCursorEnabled(TRUE);
	m_status = 0;
	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x00487020
LegoBool32 SaveLoadScreen::Update(undefined4)
{
	if (m_widgetsDirty) {
		DetachAllWidgets();
		CreateWidgets();
		m_widgetsDirty = FALSE;
	}

	if (!m_status) {
		Navigate();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00487060
void SaveLoadScreen::CreateWidgets()
{
	if (!(m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowSaveReminder)) {
		CreateImage(&m_photoImage, 0x49, 0x49);
	}
	else {
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowSaveReminder
		);
	}

	if (!m_status) {
		return;
	}

	if (m_skipFirstStatus == TRUE) {
		m_status = 8;
		m_skipFirstStatus = FALSE;
	}

	CreateImage(&m_statusPanelImage, 0x53, 0x53);
	CreateImage(&m_statusIconImage, 0x54, 0x54);

	switch (m_status) {
	case 8:
	case 0x12:
		return;
	case 0x18:
		CreateTextLabel(&m_statusLine1, 0x142, 0x37, 0x89);
		CreateTextLabel(&m_statusLine2, 0x143, 0x37, 0x87);
		CreateTextLabel(&m_statusLine3, 0x144, 0x37, 0x37);
		CreateTextButton(&m_okButton, 0x40, 0x46, 0x72);
		m_okButton.Select(0);
		return;
	default:
		if (m_requestMenuId != c_menuSaveAll && m_requestMenuId != c_menuSaveCard) {
			CreateTextLabel(&m_statusLine1, 0x145, 0x37, 0xa9);
		}

	case 0x13:
		CreateTextLabel(&m_statusLine2, 0x143, 0x37, 0x37);

	case 0x14:
	case 0x16:
	case 0x17:
		CreateTextLabel(&m_statusLine3, 0x144, 0x37, 0x37);
		CreateTextButton(&m_okButton, 0x40, 0x46, 0x72);
		m_okButton.Select(0);
		return;
	}
}

// FUNCTION: LEGORACERS 0x00487210
void SaveLoadScreen::Navigate()
{
	m_context->m_menuStack.Pop();
}

// FUNCTION: LEGORACERS 0x00487220
void SaveLoadScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_okButton) {
		switch (m_status) {
		case 0x16:
		case 0x17:
			m_status = 8;
			break;
		case 1:
		case 0x13:
		case 0x14:
		case 0x18:
			ExecuteOperation(&m_context->m_saveSystem);
			break;
		}

		m_widgetsDirty = TRUE;
		return;
	}

	if (p_source == &m_yesButton && m_status == 0x19) {
		SaveSlot* entry = m_context->m_saveSystem.GetDirectory().GetEntry(m_saveIndex);
		LegoS32 status = entry->CreateDirectories();
		m_status = status;
		if (!status) {
			m_status = m_context->m_saveSystem.LoadSlot(m_saveIndex, TRUE);
		}

		m_widgetsDirty = TRUE;
		return;
	}

	if (p_source == &m_noButton && m_status == 0x19) {
		m_status = 8;
		m_widgetsDirty = TRUE;
		return;
	}

	if (p_source == &m_yesButton || p_source == &m_cancelButton) {
		if (m_status == 0x15) {
			ExecuteOperation(&m_context->m_saveSystem);
			m_widgetsDirty = TRUE;
			return;
		}

		Navigate();
		return;
	}

	if (p_source == &m_noButton) {
		if (m_status == 0x15) {
			SaveSlot* entry = m_context->m_saveSystem.GetDirectory().GetEntry(m_saveIndex);
			entry->CreateDirectories();
			m_widgetsDirty = TRUE;
			return;
		}

		ExecuteOperation(&m_context->m_saveSystem);
		m_widgetsDirty = TRUE;
		return;
	}

	if (p_source == &m_slot0Button) {
		m_saveIndex = 0;
		m_context->m_saveSystem.GetDirectory().GetEntry(0)->EnsureDirectoryExists();
		m_status = m_context->m_saveSystem.LoadSlot(0, TRUE);
		m_widgetsDirty = TRUE;
		return;
	}

	if (p_source == &m_slot1Button) {
		m_saveIndex = 1;
		m_context->m_saveSystem.GetDirectory().GetEntry(1)->EnsureDirectoryExists();
		m_status = m_context->m_saveSystem.LoadSlot(1, TRUE);
		m_widgetsDirty = TRUE;
		return;
	}

	if (p_source == &m_slot2Button) {
		m_saveIndex = 2;
		m_context->m_saveSystem.GetDirectory().GetEntry(2)->EnsureDirectoryExists();
		m_status = m_context->m_saveSystem.LoadSlot(2, TRUE);
		m_widgetsDirty = TRUE;
		return;
	}

	if (p_source == &m_slot3Button) {
		m_saveIndex = 3;
		m_context->m_saveSystem.GetDirectory().GetEntry(3)->EnsureDirectoryExists();
		m_status = m_context->m_saveSystem.LoadSlot(3, TRUE);
		m_widgetsDirty = TRUE;
		return;
	}

	m_widgetsDirty = TRUE;
}
