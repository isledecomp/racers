#include "menu/screens/saveloadscreen.h"

#include "menu/menuscreenid.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"
#include "save/peridottraceroot0x108.h"
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
LegoBool32 SaveLoadScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_unk0x36c = p_createParams->m_menuId;
	p_createParams->m_menuId = 0x32;
	m_unk0x370 = p_context->m_unk0x4b40.GetUnk0x84();
	FUN_00486e40(&p_context->m_unk0x258);

	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	m_cursorHelper->SetCursorEnabled(FALSE);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00486e40
void SaveLoadScreen::FUN_00486e40(SaveSystem* p_unk0x04)
{
	LegoS32 emptyCount;
	LegoS32 statusEightCount;

	switch (m_unk0x36c) {
	case c_menuLoadAll: {
		emptyCount = 0;
		statusEightCount = 0;
		m_unk0x370 = p_unk0x04->GetUnk0x18c0() - 1;
		while (m_unk0x370 >= 0) {
			LegoS32 status = p_unk0x04->FUN_00443420(m_unk0x370, TRUE);
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
		m_unk0x368 = p_unk0x04->FUN_00443420(m_unk0x370, FALSE);
		break;
	case c_menuLcCreate: {
		LegoU32 status = p_unk0x04->GetUnk0xa58()[m_unk0x370].GetUnk0x00();
		if (status > 0) {
			m_unk0x368 = p_unk0x04->FUN_004434a0(m_unk0x370);
		}
		else {
			m_unk0x368 = p_unk0x04->FUN_00443420(m_unk0x370, TRUE);
		}
		m_unk0x378 = FALSE;
		break;
	}
	case c_menuSaveAll: {
		m_unk0x370 = p_unk0x04->GetUnk0x18c0() - 1;
		m_unk0x368 = 0;
		while (m_unk0x370 >= 0) {
			LegoS32 status = p_unk0x04->FUN_004434a0(m_unk0x370);
			if (status && status != 0x12 && status != 8) {
				m_unk0x368 = status;
			}

			m_unk0x370--;
		}

		m_unk0x370 = 0;
		break;
	}
	case c_menuSaveCard:
		m_unk0x368 = p_unk0x04->FUN_004434a0(m_unk0x370);
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

	m_cursorHelper->SetCursorEnabled(TRUE);
	m_unk0x368 = 0;
	return ImaginaryTool0x368::Destroy();
}

// FUNCTION: LEGORACERS 0x00487020
LegoBool32 SaveLoadScreen::VTable0x78(undefined4)
{
	if (m_unk0x374) {
		FUN_0046c760();
		VTable0x4c();
		m_unk0x374 = FALSE;
	}

	if (!m_unk0x368) {
		VTable0x84();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00487060
void SaveLoadScreen::VTable0x4c()
{
	if (!(m_context->m_unk0x4b40.GetUnk0x78() & 0x10)) {
		FUN_0046bef0(&m_unk0x37c, 0x49, 0x49);
	}
	else {
		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~0x10);
	}

	if (!m_unk0x368) {
		return;
	}

	if (m_unk0x378 == TRUE) {
		m_unk0x368 = 8;
		m_unk0x378 = FALSE;
	}

	FUN_0046bef0(&m_unk0x3d8, 0x53, 0x53);
	FUN_0046bef0(&m_unk0x434, 0x54, 0x54);

	switch (m_unk0x368) {
	case 8:
	case 0x12:
		return;
	case 0x18:
		FUN_0046bf80(&m_unk0x490, 0x142, 0x37, 0x89);
		FUN_0046bf80(&m_unk0x508, 0x143, 0x37, 0x87);
		FUN_0046bf80(&m_unk0x580, 0x144, 0x37, 0x37);
		FUN_0047fdc0(&m_unk0x1a88, 0x40, 0x46, 0x72);
		m_unk0x1a88.VTable0x4c(0);
		return;
	default:
		if (m_unk0x36c != c_menuSaveAll && m_unk0x36c != c_menuSaveCard) {
			FUN_0046bf80(&m_unk0x490, 0x145, 0x37, 0xa9);
		}

	case 0x13:
		FUN_0046bf80(&m_unk0x508, 0x143, 0x37, 0x37);

	case 0x14:
	case 0x16:
	case 0x17:
		FUN_0046bf80(&m_unk0x580, 0x144, 0x37, 0x37);
		FUN_0047fdc0(&m_unk0x1a88, 0x40, 0x46, 0x72);
		m_unk0x1a88.VTable0x4c(0);
		return;
	}
}

// FUNCTION: LEGORACERS 0x00487210
void SaveLoadScreen::VTable0x84()
{
	m_context->m_menuStack.Pop();
}

// FUNCTION: LEGORACERS 0x00487220
void SaveLoadScreen::VTable0x38(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x1a88) {
		switch (m_unk0x368) {
		case 0x16:
		case 0x17:
			m_unk0x368 = 8;
			break;
		case 1:
		case 0x13:
		case 0x14:
		case 0x18:
			FUN_00486e40(&m_context->m_unk0x258);
			break;
		}

		m_unk0x374 = TRUE;
		return;
	}

	if (p_unk0x04 == &m_unk0x14a8 && m_unk0x368 == 0x19) {
		PeridotTraceRootEntry0x10* entry = m_context->m_unk0x258.GetUnk0x00().GetEntry(m_unk0x370);
		LegoS32 status = entry->VTable0x08();
		m_unk0x368 = status;
		if (!status) {
			m_unk0x368 = m_context->m_unk0x258.FUN_00443420(m_unk0x370, TRUE);
		}

		m_unk0x374 = TRUE;
		return;
	}

	if (p_unk0x04 == &m_unk0x1798 && m_unk0x368 == 0x19) {
		m_unk0x368 = 8;
		m_unk0x374 = TRUE;
		return;
	}

	if (p_unk0x04 == &m_unk0x14a8 || p_unk0x04 == &m_unk0x11b8) {
		if (m_unk0x368 == 0x15) {
			FUN_00486e40(&m_context->m_unk0x258);
			m_unk0x374 = TRUE;
			return;
		}

		VTable0x84();
		return;
	}

	if (p_unk0x04 == &m_unk0x1798) {
		if (m_unk0x368 == 0x15) {
			PeridotTraceRootEntry0x10* entry = m_context->m_unk0x258.GetUnk0x00().GetEntry(m_unk0x370);
			entry->VTable0x08();
			m_unk0x374 = TRUE;
			return;
		}

		FUN_00486e40(&m_context->m_unk0x258);
		m_unk0x374 = TRUE;
		return;
	}

	if (p_unk0x04 == &m_unk0x5f8) {
		m_unk0x370 = 0;
		m_context->m_unk0x258.GetUnk0x00().GetEntry(0)->VTable0x04();
		m_unk0x368 = m_context->m_unk0x258.FUN_00443420(0, TRUE);
		m_unk0x374 = TRUE;
		return;
	}

	if (p_unk0x04 == &m_unk0x8e8) {
		m_unk0x370 = 1;
		m_context->m_unk0x258.GetUnk0x00().GetEntry(1)->VTable0x04();
		m_unk0x368 = m_context->m_unk0x258.FUN_00443420(1, TRUE);
		m_unk0x374 = TRUE;
		return;
	}

	if (p_unk0x04 == &m_unk0xbd8) {
		m_unk0x370 = 2;
		m_context->m_unk0x258.GetUnk0x00().GetEntry(2)->VTable0x04();
		m_unk0x368 = m_context->m_unk0x258.FUN_00443420(2, TRUE);
		m_unk0x374 = TRUE;
		return;
	}

	if (p_unk0x04 == &m_unk0xec8) {
		m_unk0x370 = 3;
		m_context->m_unk0x258.GetUnk0x00().GetEntry(3)->VTable0x04();
		m_unk0x368 = m_context->m_unk0x258.FUN_00443420(3, TRUE);
		m_unk0x374 = TRUE;
		return;
	}

	m_unk0x374 = TRUE;
}
