#include "menu/screens/mainmenuscreen.h"

#include "audio/soundgroupbinding.h"
#include "input/inputmanager.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MainMenuScreen, 0x2450)

// GLOBAL: LEGORACERS 0x004c214c
static LegoU8 g_unk0x004c214c[] = {0x13, 0x12, 0x16, 0x15, 0x14, 0x17, 0, 0};

// FUNCTION: LEGORACERS 0x00480b70
MainMenuScreen::MainMenuScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00480cd0
MainMenuScreen::~MainMenuScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00480e10
void MainMenuScreen::Reset()
{
	m_unk0x2444 = 60000;
	m_unk0x2448 = 30000;
	m_unk0x244c = 0;
	m_unk0x2438 = NULL;
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00480e40
void MainMenuScreen::FUN_00480e40()
{
	MainMenuModelSlot::CreateParams params;
	GolVec3 vector0;
	GolVec3 vector1;
	GolD3DRenderDevice* renderer;

	CreateSceneView(&m_unk0x21f8, 0, 0xd0);

	renderer = m_renderer;
	::memset(&params, 0, sizeof(params));
	params.m_golExport = m_golExport;
	params.m_unk0x0c = &m_context->m_modelBuilder;
	params.m_unk0x08 = &m_unk0x21f8;
	params.m_renderer = renderer;
	params.m_position.m_x = 18.18122864f;
	params.m_position.m_y = -10.62275887f;
	params.m_position.m_z = 0.025708f;
	m_unk0x22dc.FUN_0047e0a0(&params);
	m_unk0x21f8.FUN_00465b40(&m_unk0x22dc);

	vector1.m_x = 0.97237003f;
	vector1.m_y = -0.233445f;
	vector1.m_z = 0.0f;
	vector0.m_x = 0.0f;
	vector0.m_y = 0.0f;
	vector0.m_z = 1.0f;

	m_unk0x2438 = m_unk0x22dc.GetUnk0x1c();
	m_unk0x2438->VTable0x40(vector1, vector0);
}

// FUNCTION: LEGORACERS 0x00480f20
void MainMenuScreen::VTable0x4c()
{
	CreateImage(&m_unk0x368, 0x49, 0x49);
	CreateImage(&m_unk0x3c4, 0x52, 0x52);
	FUN_00480e40();
	FUN_0047fdc0(&m_unk0x1058, 3, 0x42, 0x25);
	FUN_0047fdc0(&m_unk0x788, 0x55, 0x42, 0x21);
	FUN_0047fdc0(&m_unk0x498, 0x56, 0x42, 0x22);
	FUN_0047fdc0(&m_unk0xa78, 0x57, 0x42, 0x23);
	FUN_0047fdc0(&m_unk0xd68, 0x58, 0x42, 0x24);
	FUN_0047fdc0(&m_unk0x1348, 8, 0x42, 0x26);
	FUN_0047fdc0(&m_unk0x1638, 0x59, 0x42, 0x27);

	if (!m_inputManager->GetJoystickCount()) {
		m_unk0xa78.VTable0x48(5);
	}
}

// FUNCTION: LEGORACERS 0x00481000
LegoBool32 MainMenuScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!p_context->m_modelBuilder.HasMenuResources()) {
		FUN_00480210(p_context, 0);
	}

	if (!p_context->m_unk0x21f4.IsInitialized()) {
		FUN_0047ff50(p_context, TRUE);
	}

	if (!MenuGameScreen::FUN_00480440(p_context)) {
		FUN_00480470(p_context, 0, TRUE);
	}

	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	FUN_00480310();
	LegoU32 index = p_context->m_saveSystem.GetMaxUnlockedCircuitIndex();
	DriverCosmetics cosmetics;
	p_context->m_cosmeticTable.CopyCosmetics(g_unk0x004c214c[index], &cosmetics);
	m_unk0x22dc.FUN_0047e210(&cosmetics);
	m_unk0x22dc.GetUnk0x118()->VTable0x14("legoman", p_context->m_context->m_unk0x18);
	m_unk0x2438->FUN_0040dad0(0);
	m_unk0x2438->SetFlags(m_unk0x2438->GetFlags() | 0x10000);
	m_unk0x2438->SetFlags(m_unk0x2438->GetFlags() & ~0x40000);
	p_context->m_saveSystem.GetActiveRecord().Reset();
	m_unk0x1058.VTable0x4c(5);
	m_cursor->SetCursorEnabled(TRUE);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00481120
LegoBool32 MainMenuScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	FUN_004803a0();
	return MenuGameScreen::Destroy();
}

// FUNCTION: LEGORACERS 0x00481150
void MainMenuScreen::VTable0x38(MenuWidget* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x788) {
		m_unk0x360 = 5;
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() & ~2);
	}
	else if (p_unk0x04 == &m_unk0x498) {
		m_unk0x360 = 6;
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() & ~2);
	}
	else if (p_unk0x04 == &m_unk0xa78) {
		m_unk0x360 = 6;
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() | 2);
	}
	else if (p_unk0x04 == &m_unk0xd68) {
		m_unk0x360 = 0x1d;
	}
	else if (p_unk0x04 == &m_unk0x1058) {
		m_unk0x360 = 3;
		MenuGameScreen::FUN_004804c0(m_context);
	}
	else if (p_unk0x04 == &m_unk0x1348) {
		m_unk0x360 = 8;
	}
	else if (p_unk0x04 == &m_unk0x1638) {
		FUN_0047fdc0(&m_unk0x1928, 0x99, 0x46, 0x73);
		FUN_0047fdc0(&m_unk0x1c18, 0x99, 0x45, 0x74);
		FUN_0046c6f0(&m_unk0x1928, &m_unk0x1c18, 0x75);
	}
	else if (p_unk0x04 == &m_unk0x1928) {
		m_unk0x284->FUN_00468cf0();
		m_unk0x360 = 0;
	}
	else if (p_unk0x04 == &m_unk0x1c18 || p_unk0x04 == &m_unk0x1f08) {
		m_unk0x284->FUN_00468cf0();
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x35c = p_unk0x04;
		m_unk0x364 = TRUE;
	}
}

// FUNCTION: LEGORACERS 0x004812c0
void MainMenuScreen::VTable0x84()
{
	if (m_unk0x360 && m_unk0x360 != 0xffff) {
		m_context->m_menuStack.Push(m_unk0x360);
		return;
	}

	m_context->m_menuStack.ResetSize();
}

// STUB: LEGORACERS 0x004812f0
LegoBool32 MainMenuScreen::VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	LegoBool32 result = m_unk0x364;
	if (result) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00481310
LegoBool32 MainMenuScreen::VTable0x1c(MenuWidget* p_icon, InputEventQueue::Event* p_item, undefined4, undefined4)
{
	if (m_unk0x364) {
		return TRUE;
	}

	if (p_icon == &m_unk0xd8) {
		switch (p_item->m_keyCode) {
		case 0x1000001d:
		case 0x1000009d:
			m_unk0x244c &= ~1;
			return FALSE;
		case 0x1000002a:
		case 0x10000036:
			m_unk0x244c &= ~2;
			return FALSE;
		case 0x10000014:
			m_unk0x244c &= ~4;
			return FALSE;
		case 0x1000002e:
			m_unk0x244c &= ~8;
			return FALSE;
		case 0x1000002f:
			m_unk0x244c &= ~0x10;
			return FALSE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00481450
LegoBool32 MainMenuScreen::VTable0x78(undefined4 p_elapsed)
{
	if (p_elapsed > m_unk0x2448) {
		m_unk0x2448 = 0;
	}
	else {
		m_unk0x2448 -= p_elapsed;
	}

	if (p_elapsed > m_unk0x2444) {
		m_unk0x2444 = 0;
	}
	else {
		m_unk0x2444 -= p_elapsed;
	}

	LegoU16 state = m_unk0x2438->GetActiveState();
	if (state == 2) {
		if (m_unk0x2438->GetActiveValue() < 208.0f) {
			m_unk0x243c = FALSE;
		}
		else {
			if (!m_unk0x243c) {
				m_soundGroupBinding->FUN_0046e970(0x1d);
				m_unk0x243c = TRUE;
			}
		}
	}

	if (m_context->m_modelBuilder.GetUnk0x78() & 4) {
		FUN_0047fdc0(&m_unk0x1f08, 0x99, 0x46, 0x72);
		FUN_0046c730(&m_unk0x1f08, 0x7c);
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() & ~4);
	}

	if (!m_unk0x2448) {
		m_unk0x2438->FUN_0040db80(2, 200, 0.0f, 0, 0, 0);
		m_unk0x2438->SetFlags(m_unk0x2438->GetFlags() | 0x10000);
		m_unk0x2448 = 30000;
	}
	else if (m_unk0x2438->FUN_0040e360()) {
		m_unk0x2438->FUN_0040db80(1, 200, 0.0f, 0, 0, 1);
		m_unk0x2438->SetFlags(m_unk0x2438->GetFlags() | 0x10000);
	}

	if (!m_unk0x2444) {
		m_unk0x364 = TRUE;
	}

	LegoBool32 result = MenuGameScreen::VTable0x78(p_elapsed);
	if (!m_unk0x360) {
		return TRUE;
	}

	return result;
}
