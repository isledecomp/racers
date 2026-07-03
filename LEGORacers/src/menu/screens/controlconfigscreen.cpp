#include "menu/screens/controlconfigscreen.h"

#include "audio/soundgroupbinding.h"
#include "input/inputdevice.h"
#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ControlConfigScreen, 0x3360)

// GLOBAL: LEGORACERS 0x004c1fc0
static LegoU32 g_controlConfigBlockedEvents[] = {
	InputDevice::c_sourceKeyboard | 0x01,
	InputDevice::c_sourceKeyboard | 0xb7,
	InputDevice::c_sourceKeyboard | 0x46,
	InputDevice::c_sourceKeyboard | 0xc5,
	InputDevice::c_sourceKeyboard | 0x45,
	InputDevice::c_sourceKeyboard | 0xdb,
	InputDevice::c_sourceKeyboard | 0xdc,
	InputDevice::c_sourceKeyboard | 0xdd,
	InputDevice::c_sourceKeyboard | 0xde,
	InputDevice::c_sourceKeyboard | 0xdf,
	InputDevice::c_sourceKeyboard | 0xe3,
};

// FUNCTION: LEGORACERS 0x0047a550
ControlConfigScreen::ControlConfigScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047a6b0
ControlConfigScreen::~ControlConfigScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047a7d0
void ControlConfigScreen::Reset()
{
	InputDevice** devices = m_devices;
	LegoS32* bindings = m_bindingIndices;

	m_deviceCount = 0;
	m_selectedDevice = 0;
	m_playerIndex = 0;
	m_awaitingButton = 0;
	m_savedButtonMapping = NULL;
	m_savedAxisMapping = NULL;

	::memset(devices, 0, sizeof(m_devices));
	::memset(bindings, 0, sizeof(m_bindingIndices));

	::memset(m_ellipsisText, 0, sizeof(m_ellipsisText));

	for (LegoU32 i = 0; i < sizeOfArray(m_ellipsisText) - 1; i++) {
		m_ellipsisText[i] = '.';
	}

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047a860
void ControlConfigScreen::CreateWidgets()
{
	LegoU16 idBase = m_playerIndex + 0x17;

	CreateImage(&m_photoImage, 0x49, 0x49);
	CreateTextLabel(&m_infoLabel, 0x3a, 0x3a, idBase);
	m_infoLabel.WrapText(0x14);
	CreateCarousel(&m_deviceCarousel, 0x3e, 0x3b);
	CreateSelector(&m_deviceSelector, &m_deviceCarousel, 0x111, 0x4d);

	for (LegoU32 i = 0; i < 9; i++) {
		CreateTextButton(&m_eventButtons[i], i + 0x108, 0x42, 0x69);
		CreateTextLabel(&m_eventLabels[i], i + 0x116, 0x37, i + 0x69);
	}

	CreateTextButton(&m_backButton, 0x3f, 0x46, 0x1e);
}

// FUNCTION: LEGORACERS 0x0047a930
void ControlConfigScreen::PopulateDeviceCarousel()
{
	ReinitializeInputBindings();
	m_deviceCount = m_inputManager->GetJoystickCount();
	if (m_deviceCount > 2) {
		m_deviceCount = 2;
	}

	for (LegoS32 i = 0; i < 2; i++) {
		InputDevice* device = m_inputManager->GetJoystick(i);
		if (device) {
			switch (device->GetDeviceSubType()) {
			case 4:
				CreateImage(&m_deviceIcons[i], 0x113, 0x113);
				break;
			case 6:
				CreateImage(&m_deviceIcons[i], 0x114, 0x114);
				break;
			default:
				CreateImage(&m_deviceIcons[i], 0x112, 0x112);
				break;
			}

			m_deviceCarousel.AddItem(&m_deviceIcons[i]);
			m_devices[i] = device;
			m_bindingIndices[i] = i;
		}
	}

	if (m_inputManager->IsKeyboardAvailable()) {
		InputDevice* keyboard = m_inputManager->GetKeyboard();
		for (LegoU32 i = 2; i < 5; i++) {
			CreateImage(&m_deviceIcons[m_deviceCount], 0x115, 0x115);
			m_deviceCarousel.AddItem(&m_deviceIcons[m_deviceCount]);
			m_devices[m_deviceCount] = keyboard;
			m_bindingIndices[m_deviceCount] = i;
			m_deviceCount++;
		}
	}
}

// FUNCTION: LEGORACERS 0x0047aaa0
LegoBool32 ControlConfigScreen::Initialize(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (p_createParams->m_menuId == 0x0b) {
		m_playerIndex = 1;
	}

	p_createParams->m_menuId = 9;
	if (!MenuGameScreen::Initialize(p_context, p_createParams)) {
		return FALSE;
	}

	PopulateDeviceCarousel();
	LegoS32 selectedEntryIndex =
		m_context->m_saveSystem.GetGameState().GetSelectedInputBindingEntryIndex(m_playerIndex);

	for (LegoU32 i = 0; i < m_deviceCount; i++) {
		if (m_bindingIndices[i] == selectedEntryIndex) {
			m_selectedDevice = i;
			break;
		}
	}

	m_deviceCarousel.SetSelection(m_selectedDevice);
	m_eventButtons[0].Select(4);
	Update(0);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047ab60
void ControlConfigScreen::Navigate()
{
	m_context->m_saveSystem.GetGameState().SelectInputBinding(m_playerIndex, m_bindingIndices[m_selectedDevice]);
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(0x30);
}

// FUNCTION: LEGORACERS 0x0047abb0
void ControlConfigScreen::OnWidgetValueChanged(MenuWidget* p_source)
{
	if (p_source == &m_deviceSelector) {
		m_selectedDevice = m_deviceCarousel.GetSelectedIndex();
	}
}

// FUNCTION: LEGORACERS 0x0047abd0
void ControlConfigScreen::OnIconFocused(MenuIcon* p_source)
{
	LegoS32 eventIndex = p_source->GetId() - m_eventButtons[0].GetId();

	if (eventIndex >= 0 && static_cast<LegoU32>(eventIndex) <= 8) {
		InputDevice* device = m_devices[m_selectedDevice];
		m_savedButtonMapping = device->GetCustomButtonMapping();
		m_savedAxisMapping = device->GetCustomAxisMapping();
		device->SetEventMappings(NULL, NULL);
		m_context->m_saveSystem.GetGameState().SetInputEvent(m_bindingIndices[m_selectedDevice], eventIndex, 0);
		m_awaitingButton = p_source;
	}
}

// FUNCTION: LEGORACERS 0x0047ac60
void ControlConfigScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == &m_backButton) {
		m_nextMenuId = 8;
		m_navPending = TRUE;
	}

	m_clickedWidget = p_source;
}

// FUNCTION: LEGORACERS 0x0047ac90
LegoBool32 ControlConfigScreen::HandleKeyDown(MenuWidget*, InputEventQueue::Event* p_item, undefined4, undefined4)
{
	LegoU32 keyCode = p_item->m_keyCode;
	LegoU32 source = keyCode & InputDevice::c_sourceMask;
	GameState& state = m_context->m_saveSystem.GetGameState();
	LegoS32 selectedDeviceIndex = m_selectedDevice;
	InputDevice* device = m_devices[selectedDeviceIndex];
	LegoS32 entryIndex = m_bindingIndices[selectedDeviceIndex];

	if (!m_navPending) {
		if (!m_awaitingButton) {
			return FALSE;
		}

		if (source == InputDevice::c_sourceJoystickButton || source == InputDevice::c_sourceKeyboard) {
			for (LegoU32 i = 0; i < sizeOfArray(g_controlConfigBlockedEvents); i++) {
				if (keyCode == g_controlConfigBlockedEvents[i]) {
					m_soundGroupBinding->PlaySoundByIndex(8);
					return TRUE;
				}
			}

			if (source == InputDevice::c_sourceJoystickButton && p_item->m_device != device) {
				m_soundGroupBinding->PlaySoundByIndex(8);
				return TRUE;
			}

			state.SetInputEvent(entryIndex, m_awaitingButton->GetId() - m_eventButtons[0].GetId(), keyCode);
			device->SetEventMappings(m_savedButtonMapping, m_savedAxisMapping);
			m_awaitingButton->Unfocus(0);
			m_awaitingButton = NULL;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047ad90
LegoBool32 ControlConfigScreen::HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	if (m_navPending) {
		return TRUE;
	}

	return MenuEventResult(m_awaitingButton);
}

// FUNCTION: LEGORACERS 0x0047adb0
void ControlConfigScreen::RefreshEventTexts()
{
	GameState& state = m_context->m_saveSystem.GetGameState();

	for (LegoS32 i = 0; i < sizeOfArray(m_eventButtons); i++) {
		m_eventTexts[i].CopyFromBufSelection(m_ellipsisText, 0);

		if (!(m_eventButtons[i].GetStateFlags() & MenuIcon::c_flagFocused)) {
			LegoU32 event = state.GetInputEvent(m_playerIndex, m_bindingIndices[m_selectedDevice], i);

			if (event) {
				InputDevice* device;
				if ((event & InputDevice::c_sourceMask) == InputDevice::c_sourceKeyboard) {
					device = m_inputManager->GetKeyboard();
				}
				else {
					device = m_devices[m_selectedDevice];
				}

				m_eventTexts[i].CopyFromBufSelection((undefined2*) device->GetControlName(event), 0);
				m_eventTexts[i].ToUpperCase();
			}
			else if (i < 2) {
				InputDevice* device = m_devices[m_selectedDevice];
				if (device->GetDeviceType() == 4 && (device->GetAxisMask() & 1)) {
					m_eventTexts[i].CopyFromBufSelection(
						(undefined2*) device->GetControlName(InputDevice::c_sourceJoystickAxisButton),
						0
					);
					m_eventTexts[i].ToUpperCase();
				}
			}
		}

		m_eventButtons[i].SetText(&m_eventTexts[i]);
	}
}

// FUNCTION: LEGORACERS 0x0047aeb0
LegoBool32 ControlConfigScreen::Update(undefined4 p_source)
{
	RefreshEventTexts();

	if (m_devices[m_selectedDevice]->GetDeviceType() == 3) {
		m_eventButtons[0].Enable(0);
		m_eventButtons[1].Enable(0);
	}
	else {
		m_eventButtons[0].Disable(0);
		m_eventButtons[1].Disable(0);
	}

	return MenuGameScreen::Update(p_source);
}
