#include "menu/screens/controlconfigscreen.h"

#include "audio/soundgroupbinding.h"
#include "input/inputdevice.h"
#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "save/savegame.h"

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
	InputDevice** devices = m_unk0x368;
	LegoS32* bindings = m_unk0x37c;

	m_unk0x39c = 0;
	m_unk0x3a0 = 0;
	m_unk0x3a4 = 0;
	m_unk0x390 = 0;
	m_unk0x394 = NULL;
	m_unk0x398 = NULL;

	::memset(devices, 0, sizeof(m_unk0x368));
	::memset(bindings, 0, sizeof(m_unk0x37c));

	::memset(m_ellipsisText, 0, sizeof(m_ellipsisText));

	for (LegoU32 i = 0; i < sizeOfArray(m_ellipsisText) - 1; i++) {
		m_ellipsisText[i] = '.';
	}

	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x0047a860
void ControlConfigScreen::VTable0x4c()
{
	LegoU16 idBase = m_unk0x3a4 + 0x17;

	CreateImage(&m_unk0x3a8, 0x49, 0x49);
	CreateTextLabel(&m_unk0x404, 0x3a, 0x3a, idBase);
	m_unk0x404.FUN_0046f6b0(0x14);
	CreateCarousel(&m_unk0x780, 0x3e, 0x3b);
	CreateSelector(&m_unk0x814, &m_unk0x780, 0x111, 0x4d);

	for (LegoU32 i = 0; i < 9; i++) {
		FUN_0047fdc0(&m_unk0x144c[i], i + 0x108, 0x42, 0x69);
		CreateTextLabel(&m_unk0x2ebc[i], i + 0x116, 0x37, i + 0x69);
	}

	FUN_0047fdc0(&m_unk0x47c, 0x3f, 0x46, 0x1e);
}

// STUB: LEGORACERS 0x0047a930
void ControlConfigScreen::FUN_0047a930()
{
	FUN_004803d0();
	m_unk0x39c = m_inputManager->GetJoystickCount();
	if (m_unk0x39c > 2) {
		m_unk0x39c = 2;
	}

	LegoS32 i;
	for (i = 0; i < 2; i++) {
		InputDevice* device = m_inputManager->GetJoystick(i);
		if (device) {
			LegoU16 id;
			switch (device->GetDeviceSubType()) {
			case 4:
				id = 0x113;
				break;
			case 6:
				id = 0x114;
				break;
			default:
				id = 0x112;
				break;
			}

			CreateImage(&m_unk0x1208[i], id, id);
			m_unk0x780.FUN_0046d9c0(&m_unk0x1208[i]);
			m_unk0x368[i] = device;
			m_unk0x37c[i] = i;
		}
	}

	if (m_inputManager->IsKeyboardAvailable()) {
		InputDevice* keyboard = m_inputManager->GetKeyboard();
		for (LegoU32 i = 2; i < 5; i++) {
			CreateImage(&m_unk0x1208[m_unk0x39c], 0x115, 0x115);
			m_unk0x780.FUN_0046d9c0(&m_unk0x1208[m_unk0x39c]);
			m_unk0x368[m_unk0x39c] = keyboard;
			m_unk0x37c[m_unk0x39c] = i;
			m_unk0x39c++;
		}
	}
}

// FUNCTION: LEGORACERS 0x0047aaa0
LegoBool32 ControlConfigScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (p_createParams->m_menuId == 0x0b) {
		m_unk0x3a4 = 1;
	}

	p_createParams->m_menuId = 9;
	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	FUN_0047a930();
	LegoS32 selectedEntryIndex = m_context->m_saveSystem.GetGameState().GetSelectedInputBindingEntryIndex(m_unk0x3a4);

	for (LegoU32 i = 0; i < m_unk0x39c; i++) {
		if (m_unk0x37c[i] == selectedEntryIndex) {
			m_unk0x3a0 = i;
			break;
		}
	}

	m_unk0x780.VTable0x50(m_unk0x3a0);
	m_unk0x144c[0].VTable0x4c(4);
	VTable0x78(0);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047ab60
void ControlConfigScreen::VTable0x84()
{
	m_context->m_saveSystem.GetGameState().SelectInputBinding(m_unk0x3a4, m_unk0x37c[m_unk0x3a0]);
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(0x30);
}

// FUNCTION: LEGORACERS 0x0047abb0
void ControlConfigScreen::VTable0x44(MenuWidget* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x814) {
		m_unk0x3a0 = m_unk0x780.GetUnk0x6c();
	}
}

// FUNCTION: LEGORACERS 0x0047abd0
void ControlConfigScreen::VTable0x34(MenuIcon* p_source)
{
	LegoS32 eventIndex = p_source->GetUnk0x30() - m_unk0x144c[0].GetUnk0x30();

	if (eventIndex >= 0 && static_cast<LegoU32>(eventIndex) <= 8) {
		InputDevice* device = m_unk0x368[m_unk0x3a0];
		m_unk0x394 = device->GetCustomButtonMapping();
		m_unk0x398 = device->GetCustomAxisMapping();
		device->SetEventMappings(NULL, NULL);
		m_context->m_saveSystem.GetGameState().FUN_0042ee70(m_unk0x37c[m_unk0x3a0], eventIndex, 0);
		m_unk0x390 = p_source;
	}
}

// FUNCTION: LEGORACERS 0x0047ac60
void ControlConfigScreen::VTable0x38(MenuWidget* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x47c) {
		m_unk0x360 = 8;
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0047ac90
LegoBool32 ControlConfigScreen::VTable0x18(MenuWidget*, InputEventQueue::Event* p_item, undefined4, undefined4)
{
	LegoU32 keyCode = p_item->m_keyCode;
	LegoU32 source = keyCode & InputDevice::c_sourceMask;
	GameState& state = m_context->m_saveSystem.GetGameState();
	LegoS32 selectedDeviceIndex = m_unk0x3a0;
	InputDevice* device = m_unk0x368[selectedDeviceIndex];
	LegoS32 entryIndex = m_unk0x37c[selectedDeviceIndex];

	if (!m_unk0x364) {
		if (!m_unk0x390) {
			return FALSE;
		}

		if (source == InputDevice::c_sourceJoystickButton || source == InputDevice::c_sourceKeyboard) {
			for (LegoU32 i = 0; i < sizeOfArray(g_controlConfigBlockedEvents); i++) {
				if (keyCode == g_controlConfigBlockedEvents[i]) {
					m_soundGroupBinding->FUN_0046e970(8);
					return TRUE;
				}
			}

			if (source == InputDevice::c_sourceJoystickButton && p_item->m_device != device) {
				m_soundGroupBinding->FUN_0046e970(8);
				return TRUE;
			}

			state.FUN_0042ee70(entryIndex, m_unk0x390->GetUnk0x30() - m_unk0x144c[0].GetUnk0x30(), keyCode);
			device->SetEventMappings(m_unk0x394, m_unk0x398);
			m_unk0x390->VTable0x58(0);
			m_unk0x390 = NULL;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047ad90
LegoBool32 ControlConfigScreen::VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	if (m_unk0x364) {
		return TRUE;
	}

	return MenuEventResult(m_unk0x390);
}

// FUNCTION: LEGORACERS 0x0047adb0
void ControlConfigScreen::FUN_0047adb0()
{
	GameState& state = m_context->m_saveSystem.GetGameState();

	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x144c); i++) {
		m_unk0x32f4[i].CopyFromBufSelection(m_ellipsisText, 0);

		if (!(m_unk0x144c[i].GetStateFlags() & MenuIcon::c_flagBit2)) {
			LegoU32 event = state.GetInputEvent(m_unk0x3a4, m_unk0x37c[m_unk0x3a0], i);

			if (event) {
				InputDevice* device;
				if ((event & InputDevice::c_sourceMask) == InputDevice::c_sourceKeyboard) {
					device = m_inputManager->GetKeyboard();
				}
				else {
					device = m_unk0x368[m_unk0x3a0];
				}

				m_unk0x32f4[i].CopyFromBufSelection((undefined2*) device->GetControlName(event), 0);
				m_unk0x32f4[i].ToUpperCase();
			}
			else if (i < 2) {
				InputDevice* device = m_unk0x368[m_unk0x3a0];
				if (device->GetDeviceType() == 4 && (device->GetAxisMask() & 1)) {
					m_unk0x32f4[i].CopyFromBufSelection(
						(undefined2*) device->GetControlName(InputDevice::c_sourceJoystickAxisButton),
						0
					);
					m_unk0x32f4[i].ToUpperCase();
				}
			}
		}

		m_unk0x144c[i].FUN_00482810(&m_unk0x32f4[i]);
	}
}

// FUNCTION: LEGORACERS 0x0047aeb0
LegoBool32 ControlConfigScreen::VTable0x78(undefined4 p_unk0x04)
{
	FUN_0047adb0();

	if (m_unk0x368[m_unk0x3a0]->GetDeviceType() == 3) {
		m_unk0x144c[0].VTable0x44(0);
		m_unk0x144c[1].VTable0x44(0);
	}
	else {
		m_unk0x144c[0].VTable0x48(0);
		m_unk0x144c[1].VTable0x48(0);
	}

	return MenuGameScreen::VTable0x78(p_unk0x04);
}
