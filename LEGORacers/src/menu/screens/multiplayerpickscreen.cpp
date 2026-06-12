#include "menu/screens/multiplayerpickscreen.h"

#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "input/mousedevice.h"
#include "menu/menugamecontext.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MultiplayerPickScreen, 0x2cc4)

// FUNCTION: LEGORACERS 0x004815f0
MultiplayerPickScreen::MultiplayerPickScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00481710
MultiplayerPickScreen::~MultiplayerPickScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00481800
void MultiplayerPickScreen::Reset()
{
	m_unk0x2b70[0] = NULL;
	m_unk0x2b70[1] = NULL;
	m_unk0x2b78 = NULL;
	::memset(m_unk0x2b94, 0, sizeof(m_unk0x2b94));
	RacerModelScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x00481830
void MultiplayerPickScreen::VTable0x4c()
{
	CreateImage(&m_unk0x270c, 0x49, 0x49);
	RacerModelScreenBase::VTable0x4c();
	CreateTextLabel(&m_unk0x2990, 0xf0, 0x37, 0x56);
	CreateTextLabel(&m_unk0x2a08, 0xf1, 0x37, 0x57);
	CreateTextLabel(&m_unk0x2bd4[0], 0x8e, 0x37, 0x56);
	CreateTextLabel(&m_unk0x2bd4[1], 0x8f, 0x37, 0x56);
	CreateImage(&m_unk0x2768[0], 0x86, 0x4b);
	CreateImage(&m_unk0x2768[1], 0x87, 0x4b);
	CreateImage(&m_unk0x2768[2], 0x88, 0x4a);
	CreateImage(&m_unk0x2768[3], 0x89, 0x4a);
	CreateImage(&m_unk0x2768[4], 0x8c, 0x50);
	CreateImage(&m_unk0x2768[5], 0x8d, 0x51);
	CreateTextLabel(&m_unk0x2a80, 0x8a, 0x37, 0x72);
	CreateTextLabel(&m_unk0x2af8, 0x8b, 0x37, 0x1f);
}

// FUNCTION: LEGORACERS 0x00481960
InputDevice* MultiplayerPickScreen::FUN_00481960(LegoU32 p_deviceType, LegoU32 p_deviceId)
{
	InputManager* inputManager = m_context->m_context->m_golApp->GetInputManager();

	switch (p_deviceType) {
	case 2:
		return inputManager->GetMouse();
	case 3:
		return inputManager->GetKeyboard();
	case 4:
		return inputManager->FindJoystickByDeviceId(p_deviceId);
	default:
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x004819b0
void MultiplayerPickScreen::FUN_004819b0()
{
	GameState* gameState = &m_context->m_saveSystem.GetGameState();
	LegoU32 entryIndex = gameState->GetState().m_inputBindings.m_players[0].m_selectedEntryIndex;
	LegoU32 deviceType = gameState->GetState().m_inputBindings.m_entries[entryIndex].m_deviceType;
	LegoU32 deviceId = gameState->GetState().m_inputBindings.m_entries[entryIndex].m_deviceId;
	m_unk0x2b70[0] = FUN_00481960(deviceType, deviceId);

	entryIndex = gameState->GetState().m_inputBindings.m_players[1].m_selectedEntryIndex;
	deviceType = gameState->GetState().m_inputBindings.m_entries[entryIndex].m_deviceType;
	deviceId = gameState->GetState().m_inputBindings.m_entries[entryIndex].m_deviceId;
	m_unk0x2b70[1] = FUN_00481960(deviceType, deviceId);
}

// FUNCTION: LEGORACERS 0x00481a30
LegoBool32 MultiplayerPickScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	undefined4 params[3];
	params[0] = 2;
	params[1] = 2;
	p_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(1, NULL);
	p_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(0, NULL);
	params[2] = 0xffff3;

	if (!RacerModelScreenBase::VTable0xa0(p_context, p_createParams, params)) {
		return FALSE;
	}

	m_unk0x2b78 = &p_context->m_context->m_inputBindings[0];
	m_unk0x2b7c[0].CopyFromBufSelection(m_unk0x2b94[0], 0x10);
	m_unk0x2b7c[1].CopyFromBufSelection(m_unk0x2b94[1], 0x10);
	FUN_004803d0();
	FUN_00486400(0);
	FUN_00486400(1);
	FUN_00481b10(0);
	FUN_00481b10(1);
	FUN_004819b0();
	VTable0x80();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00481b10
void MultiplayerPickScreen::FUN_00481b10(LegoS32 p_index)
{
	SaveRecordList::Record* record = m_unk0x22dc[p_index].FUN_004430b0();
	GolString* string = &m_unk0x2b7c[p_index];

	record->GetName(string);
	m_unk0x2bd4[p_index].VTable0x40(string, 0);
}

// FUNCTION: LEGORACERS 0x00481b60
void MultiplayerPickScreen::FUN_00481b60(LegoS32 p_index)
{
	GolWorldDatabase** database = m_unk0x98c[p_index].GetUnk0x5cAddress();
	GolRenderDevice::MaterialColor* materialColor = (*database)->GetUnk0xac();

	ColorRGBA color = materialColor->GetColor();
	color.m_red >>= 1;
	color.m_grn >>= 1;
	color.m_blu >>= 1;
	materialColor->SetColor(color);

	GolRenderDevice::Light* light = (*database)->GetUnk0xb0();
	color = light->GetColor();
	color.m_red >>= 1;
	color.m_grn >>= 1;
	color.m_blu >>= 1;
	light->SetColor(color);
}

// FUNCTION: LEGORACERS 0x00481bf0
void MultiplayerPickScreen::FUN_00481bf0(LegoS32 p_index)
{
	GolWorldDatabase** database = m_unk0x98c[p_index].GetUnk0x5cAddress();
	GolRenderDevice::MaterialColor* materialColor = (*database)->GetUnk0xac();

	ColorRGBA color = materialColor->GetColor();
	color.m_red *= 2;
	color.m_grn *= 2;
	color.m_blu *= 2;
	materialColor->SetColor(color);

	GolRenderDevice::Light* light = (*database)->GetUnk0xb0();
	color = light->GetColor();
	color.m_red *= 2;
	color.m_grn *= 2;
	color.m_blu *= 2;
	light->SetColor(color);
}

// STUB: LEGORACERS 0x00481c80
LegoBool32 MultiplayerPickScreen::VTable0x18(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4,
	undefined4
)
{
	LegoBool32 result = TRUE;

	if (m_unk0x364) {
		return result;
	}

	if (p_source != GetUnk0xd8()) {
		return FALSE;
	}

	ActiveRecordBuffer& buffer = m_context->m_saveSystem.GetActiveRecord();

	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		if (p_event->m_device == m_unk0x2b70[i]) {
			SaveRecordList::Record* record = buffer.GetSelectedRecord(i);

			switch (p_event->m_keyCode) {
			case 0x10000001:
			case 0x30000005:
				if (record != NULL) {
					buffer.SetSelectedRecord(i, NULL);
					FUN_00481bf0(i);
				}
				else {
					LegoS32 modelIndex = m_unk0x780[i] + (m_unk0x2700 * i);
					m_unk0x232c[modelIndex].SetFlags(m_unk0x232c[modelIndex].GetFlags() & ~0x10000);
					m_unk0x360 = 0x3f;
				}
				break;
			case 0x10000039:
			case 0x30000004:
				if (record == NULL) {
					buffer.SetSelectedRecord(i, m_unk0x22dc[i].FUN_004430b0());
					FUN_00481b60(i);
					m_unk0x360 = 0x41;
					FUN_00486890(i);
				}
				break;
			case 0x100000cb:
			case 0x30000009:
			case 0x3000000b:
			case 0x40000001:
				if (record == NULL) {
					m_context->m_modelBuilder.RefreshMenuResources();
					FUN_004864f0(i);
					FUN_00481b10(i);

					for (LegoS32 j = 0; j < m_unk0x26fc; j++) {
						if (j != i) {
							FUN_00486400(j);
						}
					}
				}
				break;
			case 0x100000cd:
			case 0x30000007:
			case 0x3000000a:
			case 0x40000000:
				if (record == NULL) {
					m_context->m_modelBuilder.RefreshMenuResources();
					FUN_004864a0(i);
					FUN_00481b10(i);

					for (LegoS32 j = 0; j < m_unk0x26fc; j++) {
						if (j != i) {
							FUN_00486400(j);
						}
					}
				}
				break;
			default:
				result = FALSE;
				break;
			}
		}
		else {
			result = FALSE;
		}
	}

	if (m_unk0x360 == 0x41) {
		for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
			if (buffer.GetSelectedRecord(i) == NULL) {
				m_unk0x360 = 0xffff;
				break;
			}
		}
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00481f50
void MultiplayerPickScreen::VTable0x84()
{
	switch (m_unk0x360) {
	case 0x3f:
		m_context->m_menuStack.Pop();
		break;
	case 0x41:
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(2);
		m_context->m_context->m_unk0x100 = 2;
		m_unk0x364 = TRUE;
		m_context->m_menuStack.ResetSize();
		break;
	}

	FUN_004861b0();
}

// FUNCTION: LEGORACERS 0x00481fc0
LegoBool32 MultiplayerPickScreen::VTable0x78(undefined4 p_elapsed)
{
	LegoBool32 result = RacerModelScreenBase::VTable0x78(p_elapsed);
	FUN_004819b0();
	return result;
}
