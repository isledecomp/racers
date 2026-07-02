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
	m_playerDevices[0] = NULL;
	m_playerDevices[1] = NULL;
	m_bindingEntries = NULL;
	::memset(m_nameBuffers, 0, sizeof(m_nameBuffers));
	RacerModelScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x00481830
void MultiplayerPickScreen::CreateWidgets()
{
	CreateImage(&m_photoImage, 0x49, 0x49);
	RacerModelScreenBase::CreateWidgets();
	CreateTextLabel(&m_player1Label, 0xf0, 0x37, 0x56);
	CreateTextLabel(&m_player2Label, 0xf1, 0x37, 0x57);
	CreateTextLabel(&m_nameLabels[0], 0x8e, 0x37, 0x56);
	CreateTextLabel(&m_nameLabels[1], 0x8f, 0x37, 0x56);
	CreateImage(&m_promptImages[0], 0x86, 0x4b);
	CreateImage(&m_promptImages[1], 0x87, 0x4b);
	CreateImage(&m_promptImages[2], 0x88, 0x4a);
	CreateImage(&m_promptImages[3], 0x89, 0x4a);
	CreateImage(&m_promptImages[4], 0x8c, 0x50);
	CreateImage(&m_promptImages[5], 0x8d, 0x51);
	CreateTextLabel(&m_selectHintLabel, 0x8a, 0x37, 0x72);
	CreateTextLabel(&m_backHintLabel, 0x8b, 0x37, 0x1f);
}

// FUNCTION: LEGORACERS 0x00481960
InputDevice* MultiplayerPickScreen::ResolveInputDevice(LegoU32 p_deviceType, LegoU32 p_deviceId)
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
void MultiplayerPickScreen::RefreshPlayerDevices()
{
	GameState* gameState = &m_context->m_saveSystem.GetGameState();
	LegoU32 entryIndex = gameState->GetState().m_inputBindings.m_players[0].m_selectedEntryIndex;
	LegoU32 deviceType = gameState->GetState().m_inputBindings.m_entries[entryIndex].m_deviceType;
	LegoU32 deviceId = gameState->GetState().m_inputBindings.m_entries[entryIndex].m_deviceId;
	m_playerDevices[0] = ResolveInputDevice(deviceType, deviceId);

	entryIndex = gameState->GetState().m_inputBindings.m_players[1].m_selectedEntryIndex;
	deviceType = gameState->GetState().m_inputBindings.m_entries[entryIndex].m_deviceType;
	deviceId = gameState->GetState().m_inputBindings.m_entries[entryIndex].m_deviceId;
	m_playerDevices[1] = ResolveInputDevice(deviceType, deviceId);
}

// FUNCTION: LEGORACERS 0x00481a30
LegoBool32 MultiplayerPickScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	undefined4 params[3];
	params[0] = 2;
	params[1] = 2;
	p_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(1, NULL);
	p_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(0, NULL);
	params[2] = 0xffff3;

	if (!RacerModelScreenBase::Initialize(p_context, p_createParams, params)) {
		return FALSE;
	}

	m_bindingEntries = &p_context->m_context->m_inputBindings[0];
	m_nameStrings[0].CopyFromBufSelection(m_nameBuffers[0], 0x10);
	m_nameStrings[1].CopyFromBufSelection(m_nameBuffers[1], 0x10);
	ReinitializeInputBindings();
	SwapSlotModel(0);
	SwapSlotModel(1);
	UpdateNameLabel(0);
	UpdateNameLabel(1);
	RefreshPlayerDevices();
	SetupLighting();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00481b10
void MultiplayerPickScreen::UpdateNameLabel(LegoS32 p_index)
{
	SaveRecordList::Record* record = m_recordCursors[p_index].GetSelectedRecord();
	GolString* string = &m_nameStrings[p_index];

	record->GetName(string);
	m_nameLabels[p_index].SetString(string, 0);
}

// FUNCTION: LEGORACERS 0x00481b60
void MultiplayerPickScreen::DimSlotLighting(LegoS32 p_index)
{
	GolWorldDatabase** database = m_sceneViews[p_index].GetWorldAddress();
	GolRenderDevice::MaterialColor* materialColor = (*database)->GetAmbientMaterial();

	ColorRGBA color = materialColor->GetColor();
	color.m_red >>= 1;
	color.m_grn >>= 1;
	color.m_blu >>= 1;
	materialColor->SetColor(color);

	GolRenderDevice::Light* light = (*database)->GetLight();
	color = light->GetColor();
	color.m_red >>= 1;
	color.m_grn >>= 1;
	color.m_blu >>= 1;
	light->SetColor(color);
}

// FUNCTION: LEGORACERS 0x00481bf0
void MultiplayerPickScreen::RestoreSlotLighting(LegoS32 p_index)
{
	GolWorldDatabase** database = m_sceneViews[p_index].GetWorldAddress();
	GolRenderDevice::MaterialColor* materialColor = (*database)->GetAmbientMaterial();

	ColorRGBA color = materialColor->GetColor();
	color.m_red *= 2;
	color.m_grn *= 2;
	color.m_blu *= 2;
	materialColor->SetColor(color);

	GolRenderDevice::Light* light = (*database)->GetLight();
	color = light->GetColor();
	color.m_red *= 2;
	color.m_grn *= 2;
	color.m_blu *= 2;
	light->SetColor(color);
}

// STUB: LEGORACERS 0x00481c80
LegoBool32 MultiplayerPickScreen::HandleKeyDown(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4,
	undefined4
)
{
	LegoBool32 result = TRUE;

	if (m_navPending) {
		return result;
	}

	if (p_source != GetRootIcon()) {
		return FALSE;
	}

	for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
		if (p_event->m_device == m_playerDevices[i]) {
			SaveRecordList::Record* record = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord(i);

			switch (p_event->m_keyCode) {
			case 0x10000001:
			case 0x30000005:
				if (record != NULL) {
					m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(i, NULL);
					RestoreSlotLighting(i);
				}
				else {
					LegoS32 modelIndex = m_slotModelToggle[i] + (m_modelsPerSlot * i);
					m_driverEntities[modelIndex].SetFlags(m_driverEntities[modelIndex].GetFlags() & ~0x10000);
					m_nextMenuId = 0x3f;
				}
				break;
			case 0x10000039:
			case 0x1000009c:
			case 0x30000004:
				if (record == NULL) {
					m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(
						i,
						m_recordCursors[i].GetSelectedRecord()
					);
					DimSlotLighting(i);
					m_nextMenuId = 0x41;
					PlayRandomNamedAnimation(i);
				}
				break;
			case 0x100000cb:
			case 0x30000009:
			case 0x3000000b:
			case 0x40000001:
				if (record == NULL) {
					m_context->m_modelBuilder.RefreshMenuResources();
					SelectPreviousRecord(i);
					UpdateNameLabel(i);

					for (LegoS32 j = 0; j < m_modelSlotCount; j++) {
						if (j != i) {
							SwapSlotModel(j);
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
					SelectNextRecord(i);
					UpdateNameLabel(i);

					for (LegoS32 j = 0; j < m_modelSlotCount; j++) {
						if (j != i) {
							SwapSlotModel(j);
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

	if (m_nextMenuId == 0x41) {
		for (LegoS32 i = 0; i < m_modelSlotCount; i++) {
			if (m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord(i) == NULL) {
				m_nextMenuId = 0xffff;
				break;
			}
		}
	}

	if (m_nextMenuId != 0xffff) {
		m_navPending = TRUE;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00481f50
void MultiplayerPickScreen::Navigate()
{
	switch (m_nextMenuId) {
	case 0x3f:
		m_context->m_menuStack.Pop();
		break;
	case 0x41:
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(2);
		m_context->m_context->m_racerCount = 2;
		m_navPending = TRUE;
		m_context->m_menuStack.ResetSize();
		break;
	}

	CommitRecordSelections();
}

// FUNCTION: LEGORACERS 0x00481fc0
LegoBool32 MultiplayerPickScreen::Update(undefined4 p_elapsed)
{
	LegoBool32 result = RacerModelScreenBase::Update(p_elapsed);
	RefreshPlayerDevices();
	return result;
}
