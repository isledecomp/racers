#include "inputdevice.h"

#include "golerror.h"

#include <dinput.h>
#include <string.h>

DECOMP_SIZE_ASSERT(InputDevice, 0x9c)

// GLOBAL: LEGORACERS 0x004c7080
undefined2 g_defaultMapping[256];

// FUNCTION: LEGORACERS 0x0044b8f0
InputDevice::InputDevice()
{
	LegoU16 i;
	undefined2* writePtr;

	for (i = 0, writePtr = g_defaultMapping; i < sizeOfArray(g_defaultMapping); i++, writePtr++) {
		*writePtr = i;
	}

	Init();
}

// FUNCTION: LEGORACERS 0x0044b940
InputDevice::~InputDevice()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0044b950
void InputDevice::Init()
{
	m_unk0x28 = 0;
	m_unk0x24 = 0;
	m_unk0x20 = 0;
	m_unk0x1c = 0;
	m_unk0x18 = FALSE;
	m_unk0x30 = g_defaultMapping;
	m_unk0x2c = g_defaultMapping;
	::memset(&m_unk0x04, 0, sizeof(m_unk0x04));
	m_unk0x5c = 0;
	m_opalVault = NULL;
	m_buttonCount = 0;
	m_axisCount = 0;
	m_unk0x50 = 0;
	m_devType = 0;
	m_devSubType = 0;
	m_unk0x38 = 0;
	m_unk0x90 = 0;
	m_unk0x34 = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x60[0] = '\0';
	m_stringBuffer = NULL;
	m_callback = NULL;
}

// FUNCTION: LEGORACERS 0x0044b9c0
LegoBool32 InputDevice::Destroy()
{
	if (!m_unk0x18) {
		return true;
	}

	Init();
	return !m_unk0x18;
}

// FUNCTION: LEGORACERS 0x0044b9f0
void InputDevice::FUN_0044b9f0()
{
	LegoU32 flag = 0;

	switch (m_devType) {
	case DIDEVTYPE_MOUSE:
		flag = c_sourceMouse;
		break;
	case DIDEVTYPE_KEYBOARD:
		flag = c_sourceKeyboard;
		break;
	case DIDEVTYPE_JOYSTICK:
		flag = c_sourceJoystick1;
		break;
	}

	LegoS32 i;
	for (i = 0; i < VTable0x1c(); i++) {
		if (VTable0x34(i | flag)) {
			VTable0x04(i | flag, FALSE, TRUE);
		}
	}
}

// STUB: LEGORACERS 0x0044ba60
undefined4 InputDevice::VTable0x14(undefined4 p_arg)
{
	LegoS32 i;

	m_unk0x34 += p_arg;

	for (i = 0; i < m_unk0x50; i++) {
		// TODO
		STUB(0x0044ba60);
	}

	FUN_0044bc60(p_arg);
	return 0;
}

// FUNCTION: LEGORACERS 0x0044bab0
void InputDevice::FUN_0044bab0(undefined4 p_arg1, undefined4 p_arg2)
{
	m_unk0x3c = p_arg2;
	m_unk0x40 = p_arg1;
	m_unk0x20 = 1;
	m_unk0x44 = p_arg2;
}

// FUNCTION: LEGORACERS 0x0044bad0
void InputDevice::FUN_0044bad0(const LegoChar* p_str)
{
	strncpy(m_unk0x60, p_str, sizeOfArray(m_unk0x60) - 1);
	m_unk0x60[sizeOfArray(m_unk0x60) - 1] = '\0';
}

// FUNCTION: LEGORACERS 0x0044baf0
void InputDevice::FUN_0044baf0(undefined2* p_arg1, undefined2* p_arg2)
{
	if (p_arg1 == NULL) {
		p_arg1 = g_defaultMapping;
	}

	m_unk0x2c = p_arg1;

	if (p_arg2 == NULL) {
		p_arg2 = g_defaultMapping;
	}

	m_unk0x30 = p_arg2;
}

// FUNCTION: LEGORACERS 0x0044bb20
undefined2* InputDevice::FUN_0044bb20()
{
	if (m_unk0x2c == g_defaultMapping) {
		return NULL;
	}
	return m_unk0x2c;
}

// FUNCTION: LEGORACERS 0x0044bb40
undefined2* InputDevice::FUN_0044bb40()
{
	if (m_unk0x30 == g_defaultMapping) {
		return NULL;
	}
	return m_unk0x30;
}

// STUB: LEGORACERS 0x0044bb60
void InputDevice::FUN_0044bb60(float p_arg1, float p_arg2, undefined4 p_arg3)
{
	// TODO
	STUB(0x0044bb60);
}

// STUB: LEGORACERS 0x0044bc60
void InputDevice::FUN_0044bc60(undefined4)
{
	// TODO
	STUB(0x0044bb60);
}

// FUNCTION: LEGORACERS 0x0044bda0
void InputDevice::FUN_0044bda0()
{
	LegoU32 flag = 0x1;
	LegoU32 bits = m_unk0x38;
	LegoS32 i;

	for (i = 16; i != 0; flag <<= 1, i--) {
		if (bits & flag) {
			VTable0x08(flag, 0.0f);
		}
	}
}

// FUNCTION: LEGORACERS 0x0044bdd0
void InputDevice::VTable0x04(undefined4, LegoU8 p_state, LegoBool32)
{
	if (p_state) {
		m_unk0x44 = m_unk0x3c;
	}
}

// FUNCTION: LEGORACERS 0x0044bdf0
void InputDevice::FUN_0044bdf0(undefined4 p_arg)
{
	m_unk0x04[m_unk0x50] = p_arg;
	m_unk0x50 += 1;
}

// FUNCTION: LEGORACERS 0x0044be10
LegoBool32 InputDevice::FUN_0044be10(undefined4 p_arg)
{
	LegoS32 i;

	for (i = 0; i < m_unk0x50; i++) {
		if (m_unk0x04[i] == p_arg) {
			while (i < (LegoS32) sizeOfArray(m_unk0x04)) {
				m_unk0x04[i] = m_unk0x04[i + 1];
				i++;
			}

			m_unk0x50 -= 1;
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044be70
LegoS16 InputDevice::StoreString(const LegoChar* p_str)
{
	wchar_t* ptr = m_stringBuffer;

	if (m_stringBuffer == NULL) {
		return -1;
	}

	while (ptr[0] != L'\0' || ptr[1] != L'\0') {
		ptr += 1;
	}

	if (m_stringBuffer != ptr) {
		ptr += 1;
	}

	LegoS16 result = ((LegoU16) ((LegoChar*) ptr - (LegoChar*) m_stringBuffer)) / (sizeof(*ptr));

	while (*p_str != '\0') {
		*ptr++ = (LegoU8) *p_str++;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0044bed0
LegoS32 InputDevice::VTable0x1c()
{
	return sizeOfArray(g_defaultMapping);
}

// FUNCTION: LEGORACERS 0x0044bee0
const wchar_t* InputDevice::VTable0x24(undefined4)
{
	return L"";
}

// FUNCTION: LEGORACERS 0x0044bef0
undefined4 InputDevice::VTable0x18()
{
	return m_unk0x1c;
}

// FUNCTION: LEGORACERS 0x0044bf00
undefined4 InputDevice::VTable0x50()
{
	m_unk0x1c = 1;
	return m_unk0x1c;
}

// FUNCTION: LEGORACERS 0x0044bf10
undefined4 InputDevice::VTable0x54()
{
	m_unk0x1c = 0;
	return m_unk0x1c;
}

// FUNCTION: LEGORACERS 0x00451080 FOLDED
undefined4 InputDevice::VTable0x20()
{
	return 16;
}
