#include "menu/screens/controlconfigscreen.h"

#include "audio/soundgroupbinding.h"
#include "input/inputdevice.h"
#include "input/inputmanager.h"
#include "input/joystickdevice.h"
#include "input/keyboarddevice.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ControlConfigScreen, 0x3360)
DECOMP_SIZE_ASSERT(ControlConfigScreen::FieldAt0x32f4, 0xc)

// FUNCTION: LEGORACERS 0x00449e10 FOLDED
ControlConfigScreen::FieldAt0x32f4::FieldAt0x32f4()
{
	m_unk0x00 = 0;
	m_unk0x08 = 0;
	m_unk0x06 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00449e30 FOLDED
ControlConfigScreen::FieldAt0x32f4::~FieldAt0x32f4()
{
	m_unk0x00 = 0;
	m_unk0x08 = 0;
	m_unk0x06 = 0;
	m_unk0x04 = 0;
}

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

	undefined4* text = m_unk0x76c;
	::memset(text, 0, sizeof(m_unk0x76c) + sizeof(m_unk0x77c));
	text[0] = 0x002e002e;
	text[1] = 0x002e002e;
	text[2] = 0x002e002e;
	text[3] = 0x002e002e;
	ImaginaryTool0x368::Reset();
}

// FUNCTION: LEGORACERS 0x0047a860
void ControlConfigScreen::VTable0x4c()
{
	LegoU16 idBase = m_unk0x3a4 + 0x17;

	FUN_0046bef0(&m_unk0x3a8, 0x49, 0x49);
	FUN_0046bf80(&m_unk0x404, 0x3a, 0x3a, idBase);
	m_unk0x404.FUN_0046f6b0(0x14);
	FUN_0046c240(&m_unk0x780, 0x3e, 0x3b);
	FUN_0046c2b0(&m_unk0x814, &m_unk0x780, 0x111, 0x4d);

	for (LegoU32 i = 0; i < 9; i++) {
		FUN_0047fdc0(&m_unk0x144c[i], i + 0x108, 0x42, 0x69);
		FUN_0046bf80(&m_unk0x2ebc[i], i + 0x116, 0x37, i + 0x69);
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

			FUN_0046bef0(&m_unk0x1208[i], id, id);
			m_unk0x780.FUN_0046d9c0(&m_unk0x1208[i]);
			m_unk0x368[i] = device;
			m_unk0x37c[i] = i;
		}
	}

	if (m_inputManager->IsKeyboardAvailable()) {
		InputDevice* keyboard = m_inputManager->GetKeyboard();
		for (LegoU32 i = 2; i < 5; i++) {
			FUN_0046bef0(&m_unk0x1208[m_unk0x39c], 0x115, 0x115);
			m_unk0x780.FUN_0046d9c0(&m_unk0x1208[m_unk0x39c]);
			m_unk0x368[m_unk0x39c] = keyboard;
			m_unk0x37c[m_unk0x39c] = i;
			m_unk0x39c++;
		}
	}
}

// FUNCTION: LEGORACERS 0x0047aaa0
LegoBool32 ControlConfigScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (p_createParams->m_menuId == 0x0b) {
		m_unk0x3a4 = 1;
	}

	p_createParams->m_menuId = 9;
	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	FUN_0047a930();
	LegoS32 selectedEntryIndex = m_context->m_unk0x258.GetUnk0x18c4().GetSelectedInputBindingEntryIndex(m_unk0x3a4);

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
	m_context->m_unk0x258.GetUnk0x18c4().FUN_0042eb20(m_unk0x3a4, m_unk0x37c[m_unk0x3a0]);
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(0x30);
}

// FUNCTION: LEGORACERS 0x0047abb0
void ControlConfigScreen::VTable0x44(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x814) {
		m_unk0x3a0 = m_unk0x780.GetUnk0x6c();
	}
}

// STUB: LEGORACERS 0x0047abd0
void ControlConfigScreen::VTable0x34(ObscureIcon0x1a8*)
{
	STUB(0x0047abd0);
}

// FUNCTION: LEGORACERS 0x0047ac60
void ControlConfigScreen::VTable0x38(ObscureVantage0x58* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x47c) {
		m_unk0x360 = 8;
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = p_unk0x04;
}

// STUB: LEGORACERS 0x0047ac90
undefined4 ControlConfigScreen::VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x0047ac90);
	return 0;
}

// FUNCTION: LEGORACERS 0x0047ad90
undefined4 ControlConfigScreen::VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	if (m_unk0x364) {
		return TRUE;
	}

	return m_unk0x390;
}

// STUB: LEGORACERS 0x0047adb0
void ControlConfigScreen::FUN_0047adb0()
{
	STUB(0x0047adb0);
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

	return ImaginaryTool0x368::VTable0x78(p_unk0x04);
}
