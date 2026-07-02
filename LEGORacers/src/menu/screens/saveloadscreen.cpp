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
	m_unk0x368 = 0;
	m_unk0x36c = 0;
	m_unk0x370 = 0;
	m_unk0x374 = FALSE;
	m_unk0x1d78 = 0;
	m_unk0x378 = TRUE;
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

	m_unk0x36c = p_createParams->m_menuId;
	p_createParams->m_menuId = 0x32;
	m_unk0x370 = p_context->m_modelBuilder.GetUnk0x84();
	FUN_00486e40(&p_context->m_saveSystem);

	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	m_cursor->SetCursorEnabled(FALSE);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00486e40
void SaveLoadScreen::FUN_00486e40(SaveSystem* p_source)
{
	LegoS32 emptyCount;
	LegoS32 statusEightCount;

	switch (m_unk0x36c) {
	case c_menuLoadAll: {
		emptyCount = 0;
		statusEightCount = 0;
		m_unk0x370 = p_source->GetMemoryCardSaveCount() - 1;
		while (m_unk0x370 >= 0) {
			LegoS32 status = p_source->FUN_00443420(m_unk0x370, TRUE);
			m_unk0x368 = status;
			if (!status) {
				emptyCount++;
			}
			else if (status == 8) {
				statusEightCount++;
			}

			m_unk0x370--;
		}

		LegoS32 status = 0;
		m_unk0x370 = status;
		if (emptyCount != status) {
			m_unk0x368 = status;
		}
		else if (statusEightCount > status) {
			m_unk0x368 = 8;
		}
		break;
	}
	case c_menuLoadCard:
		m_unk0x368 = p_source->FUN_00443420(m_unk0x370, FALSE);
		break;
	case c_menuLcCreate: {
		LegoU32 status = p_source->GetMemoryCardSaves()[m_unk0x370].GetRecordCount();
		if (status > 0) {
			m_unk0x368 = p_source->FUN_004434a0(m_unk0x370);
		}
		else {
			m_unk0x368 = p_source->FUN_00443420(m_unk0x370, TRUE);
		}
		m_unk0x378 = FALSE;
		break;
	}
	case c_menuSaveAll: {
		m_unk0x370 = p_source->GetMemoryCardSaveCount() - 1;
		m_unk0x368 = 0;
		while (m_unk0x370 >= 0) {
			LegoS32 status = p_source->FUN_004434a0(m_unk0x370);
			if (status && status != 0x12 && status != 8) {
				m_unk0x368 = status;
			}

			m_unk0x370--;
		}

		m_unk0x370 = 0;
		break;
	}
	case c_menuSaveCard:
		m_unk0x368 = p_source->FUN_004434a0(m_unk0x370);
		break;
	}

	m_unk0x368 = 0;
}

// FUNCTION: LEGORACERS 0x00486ff0
LegoBool32 SaveLoadScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_cursor->SetCursorEnabled(TRUE);
	m_unk0x368 = 0;
	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x00487020
LegoBool32 SaveLoadScreen::Update(undefined4)
{
	if (m_unk0x374) {
		FUN_0046c760();
		CreateWidgets();
		m_unk0x374 = FALSE;
	}

	if (!m_unk0x368) {
		Navigate();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00487060
void SaveLoadScreen::CreateWidgets()
{
	if (!(m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowSaveReminder)) {
		CreateImage(&m_unk0x37c, 0x49, 0x49);
	}
	else {
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowSaveReminder
		);
	}

	if (!m_unk0x368) {
		return;
	}

	if (m_unk0x378 == TRUE) {
		m_unk0x368 = 8;
		m_unk0x378 = FALSE;
	}

	CreateImage(&m_unk0x3d8, 0x53, 0x53);
	CreateImage(&m_unk0x434, 0x54, 0x54);

	switch (m_unk0x368) {
	case 8:
	case 0x12:
		return;
	case 0x18:
		CreateTextLabel(&m_unk0x490, 0x142, 0x37, 0x89);
		CreateTextLabel(&m_unk0x508, 0x143, 0x37, 0x87);
		CreateTextLabel(&m_unk0x580, 0x144, 0x37, 0x37);
		FUN_0047fdc0(&m_unk0x1a88, 0x40, 0x46, 0x72);
		m_unk0x1a88.Select(0);
		return;
	default:
		if (m_unk0x36c != c_menuSaveAll && m_unk0x36c != c_menuSaveCard) {
			CreateTextLabel(&m_unk0x490, 0x145, 0x37, 0xa9);
		}

	case 0x13:
		CreateTextLabel(&m_unk0x508, 0x143, 0x37, 0x37);

	case 0x14:
	case 0x16:
	case 0x17:
		CreateTextLabel(&m_unk0x580, 0x144, 0x37, 0x37);
		FUN_0047fdc0(&m_unk0x1a88, 0x40, 0x46, 0x72);
		m_unk0x1a88.Select(0);
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
	if (p_source == &m_unk0x1a88) {
		switch (m_unk0x368) {
		case 0x16:
		case 0x17:
			m_unk0x368 = 8;
			break;
		case 1:
		case 0x13:
		case 0x14:
		case 0x18:
			FUN_00486e40(&m_context->m_saveSystem);
			break;
		}

		m_unk0x374 = TRUE;
		return;
	}

	if (p_source == &m_unk0x14a8 && m_unk0x368 == 0x19) {
		SaveSlot* entry = m_context->m_saveSystem.GetDirectory().GetEntry(m_unk0x370);
		LegoS32 status = entry->CreateDirectories();
		m_unk0x368 = status;
		if (!status) {
			m_unk0x368 = m_context->m_saveSystem.FUN_00443420(m_unk0x370, TRUE);
		}

		m_unk0x374 = TRUE;
		return;
	}

	if (p_source == &m_unk0x1798 && m_unk0x368 == 0x19) {
		m_unk0x368 = 8;
		m_unk0x374 = TRUE;
		return;
	}

	if (p_source == &m_unk0x14a8 || p_source == &m_unk0x11b8) {
		if (m_unk0x368 == 0x15) {
			FUN_00486e40(&m_context->m_saveSystem);
			m_unk0x374 = TRUE;
			return;
		}

		Navigate();
		return;
	}

	if (p_source == &m_unk0x1798) {
		if (m_unk0x368 == 0x15) {
			SaveSlot* entry = m_context->m_saveSystem.GetDirectory().GetEntry(m_unk0x370);
			entry->CreateDirectories();
			m_unk0x374 = TRUE;
			return;
		}

		FUN_00486e40(&m_context->m_saveSystem);
		m_unk0x374 = TRUE;
		return;
	}

	if (p_source == &m_unk0x5f8) {
		m_unk0x370 = 0;
		m_context->m_saveSystem.GetDirectory().GetEntry(0)->EnsureDirectoryExists();
		m_unk0x368 = m_context->m_saveSystem.FUN_00443420(0, TRUE);
		m_unk0x374 = TRUE;
		return;
	}

	if (p_source == &m_unk0x8e8) {
		m_unk0x370 = 1;
		m_context->m_saveSystem.GetDirectory().GetEntry(1)->EnsureDirectoryExists();
		m_unk0x368 = m_context->m_saveSystem.FUN_00443420(1, TRUE);
		m_unk0x374 = TRUE;
		return;
	}

	if (p_source == &m_unk0xbd8) {
		m_unk0x370 = 2;
		m_context->m_saveSystem.GetDirectory().GetEntry(2)->EnsureDirectoryExists();
		m_unk0x368 = m_context->m_saveSystem.FUN_00443420(2, TRUE);
		m_unk0x374 = TRUE;
		return;
	}

	if (p_source == &m_unk0xec8) {
		m_unk0x370 = 3;
		m_context->m_saveSystem.GetDirectory().GetEntry(3)->EnsureDirectoryExists();
		m_unk0x368 = m_context->m_saveSystem.FUN_00443420(3, TRUE);
		m_unk0x374 = TRUE;
		return;
	}

	m_unk0x374 = TRUE;
}
