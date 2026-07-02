#include "menu/screens/mainmenuscreen.h"

#include "audio/soundgroupbinding.h"
#include "input/inputmanager.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MainMenuScreen, 0x2450)

// GLOBAL: LEGORACERS 0x004c214c
static LegoU8 g_menuDriverCosmeticIds[] = {0x13, 0x12, 0x16, 0x15, 0x14, 0x17, 0, 0};

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
	m_idleTimeoutMs = 60000;
	m_idleAnimTimerMs = 30000;
	m_cheatKeyMask = 0;
	m_driverEntity = NULL;
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00480e40
void MainMenuScreen::CreateDriverScene()
{
	MainMenuModelSlot::CreateParams params;
	GolVec3 vector0;
	GolVec3 vector1;
	GolD3DRenderDevice* renderer;

	CreateSceneView(&m_sceneView, 0, 0xd0);

	renderer = m_renderer;
	::memset(&params, 0, sizeof(params));
	params.m_golExport = m_golExport;
	params.m_modelBuilder = &m_context->m_modelBuilder;
	params.m_sceneView = &m_sceneView;
	params.m_renderer = renderer;
	params.m_position.m_x = 18.18122864f;
	params.m_position.m_y = -10.62275887f;
	params.m_position.m_z = 0.025708f;
	m_modelSlot.Create(&params);
	m_sceneView.AddElement(&m_modelSlot);

	vector1.m_x = 0.97237003f;
	vector1.m_y = -0.233445f;
	vector1.m_z = 0.0f;
	vector0.m_x = 0.0f;
	vector0.m_y = 0.0f;
	vector0.m_z = 1.0f;

	m_driverEntity = m_modelSlot.GetDriverEntity();
	m_driverEntity->VTable0x40(vector1, vector0);
}

// FUNCTION: LEGORACERS 0x00480f20
void MainMenuScreen::VTable0x4c()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
	CreateImage(&m_logoImage, 0x52, 0x52);
	CreateDriverScene();
	FUN_0047fdc0(&m_garageButton, 3, 0x42, 0x25);
	FUN_0047fdc0(&m_circuitRaceButton, 0x55, 0x42, 0x21);
	FUN_0047fdc0(&m_singleRaceButton, 0x56, 0x42, 0x22);
	FUN_0047fdc0(&m_versusRaceButton, 0x57, 0x42, 0x23);
	FUN_0047fdc0(&m_timeRaceButton, 0x58, 0x42, 0x24);
	FUN_0047fdc0(&m_optionsButton, 8, 0x42, 0x26);
	FUN_0047fdc0(&m_exitButton, 0x59, 0x42, 0x27);

	if (!m_inputManager->GetJoystickCount()) {
		m_versusRaceButton.Disable(5);
	}
}

// FUNCTION: LEGORACERS 0x00481000
LegoBool32 MainMenuScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!p_context->m_modelBuilder.HasMenuResources()) {
		FUN_00480210(p_context, 0);
	}

	if (!p_context->m_carBuildModel.IsInitialized()) {
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
	p_context->m_cosmeticTable.CopyCosmetics(g_menuDriverCosmeticIds[index], &cosmetics);
	m_modelSlot.SetCosmetics(&cosmetics);
	m_modelSlot.GetBodyModelPart()->VTable0x14("legoman", p_context->m_context->m_useBinaryFiles);
	m_driverEntity->FUN_0040dad0(0);
	m_driverEntity->SetFlags(m_driverEntity->GetFlags() | 0x10000);
	m_driverEntity->SetFlags(m_driverEntity->GetFlags() & ~0x40000);
	p_context->m_saveSystem.GetActiveRecord().Reset();
	m_garageButton.Select(5);
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
void MainMenuScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_circuitRaceButton) {
		m_unk0x360 = 5;
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowVersus
		);
	}
	else if (p_source == &m_singleRaceButton) {
		m_unk0x360 = 6;
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowVersus
		);
	}
	else if (p_source == &m_versusRaceButton) {
		m_unk0x360 = 6;
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() | DriverModelBuilder::c_menuFlowVersus
		);
	}
	else if (p_source == &m_timeRaceButton) {
		m_unk0x360 = 0x1d;
	}
	else if (p_source == &m_garageButton) {
		m_unk0x360 = 3;
		MenuGameScreen::FUN_004804c0(m_context);
	}
	else if (p_source == &m_optionsButton) {
		m_unk0x360 = 8;
	}
	else if (p_source == &m_exitButton) {
		FUN_0047fdc0(&m_confirmYesButton, 0x99, 0x46, 0x73);
		FUN_0047fdc0(&m_confirmNoButton, 0x99, 0x45, 0x74);
		FUN_0046c6f0(&m_confirmYesButton, &m_confirmNoButton, 0x75);
	}
	else if (p_source == &m_confirmYesButton) {
		m_unk0x284->FUN_00468cf0();
		m_unk0x360 = 0;
	}
	else if (p_source == &m_confirmNoButton || p_source == &m_noticePopup) {
		m_unk0x284->FUN_00468cf0();
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x35c = p_source;
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
LegoBool32 MainMenuScreen::HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	LegoBool32 result = m_unk0x364;
	if (result) {
		result = TRUE;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00481310
LegoBool32 MainMenuScreen::HandleKeyUp(MenuWidget* p_icon, InputEventQueue::Event* p_item, undefined4, undefined4)
{
	if (m_unk0x364) {
		return TRUE;
	}

	if (p_icon == &m_unk0xd8) {
		switch (p_item->m_keyCode) {
		case 0x1000001d:
		case 0x1000009d:
			m_cheatKeyMask &= ~1;
			return FALSE;
		case 0x1000002a:
		case 0x10000036:
			m_cheatKeyMask &= ~2;
			return FALSE;
		case 0x10000014:
			m_cheatKeyMask &= ~4;
			return FALSE;
		case 0x1000002e:
			m_cheatKeyMask &= ~8;
			return FALSE;
		case 0x1000002f:
			m_cheatKeyMask &= ~0x10;
			return FALSE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00481450
LegoBool32 MainMenuScreen::VTable0x78(undefined4 p_elapsed)
{
	if (p_elapsed > m_idleAnimTimerMs) {
		m_idleAnimTimerMs = 0;
	}
	else {
		m_idleAnimTimerMs -= p_elapsed;
	}

	if (p_elapsed > m_idleTimeoutMs) {
		m_idleTimeoutMs = 0;
	}
	else {
		m_idleTimeoutMs -= p_elapsed;
	}

	LegoU16 state = m_driverEntity->GetActiveState();
	if (state == 2) {
		if (m_driverEntity->GetActiveValue() < 208.0f) {
			m_animSoundPlayed = FALSE;
		}
		else {
			if (!m_animSoundPlayed) {
				m_soundGroupBinding->PlaySoundByIndex(0x1d);
				m_animSoundPlayed = TRUE;
			}
		}
	}

	if (m_context->m_modelBuilder.GetMenuFlowFlags() & DriverModelBuilder::c_menuFlowUnlockNotice) {
		FUN_0047fdc0(&m_noticePopup, 0x99, 0x46, 0x72);
		FUN_0046c730(&m_noticePopup, 0x7c);
		m_context->m_modelBuilder.SetMenuFlowFlags(
			m_context->m_modelBuilder.GetMenuFlowFlags() & ~DriverModelBuilder::c_menuFlowUnlockNotice
		);
	}

	if (!m_idleAnimTimerMs) {
		m_driverEntity->FUN_0040db80(2, 200, 0.0f, 0, 0, 0);
		m_driverEntity->SetFlags(m_driverEntity->GetFlags() | 0x10000);
		m_idleAnimTimerMs = 30000;
	}
	else if (m_driverEntity->FUN_0040e360()) {
		m_driverEntity->FUN_0040db80(1, 200, 0.0f, 0, 0, 1);
		m_driverEntity->SetFlags(m_driverEntity->GetFlags() | 0x10000);
	}

	if (!m_idleTimeoutMs) {
		m_unk0x364 = TRUE;
	}

	LegoBool32 result = MenuGameScreen::VTable0x78(p_elapsed);
	if (!m_unk0x360) {
		return TRUE;
	}

	return result;
}
