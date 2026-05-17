#include "obscureanthem0x58.h"

#include "input/inputdevice.h"

DECOMP_SIZE_ASSERT(ObscureAnthem0x58, 0x58)

// FUNCTION: LEGORACERS 0x0046e9e0
ObscureAnthem0x58::ObscureAnthem0x58()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046ea50
ObscureAnthem0x58::~ObscureAnthem0x58()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046eaa0
ObscureVantage0x58* ObscureAnthem0x58::VTable0x2c(void* p_item, undefined4 p_x, undefined4 p_y)
{
	if (m_flags & 8) {
		if (m_unk0x28) {
			m_unk0x28->VTable0x28(this, p_item, p_x, p_y);
		}

		return this;
	}

	if (m_unk0x28) {
		m_unk0x28->VTable0x14(this, p_item, p_x, p_y);
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0046eaf0
ObscureVantage0x58* ObscureAnthem0x58::VTable0x30(OnyxCircularBuffer0x1c::Item* p_item, undefined4 p_x, undefined4 p_y)
{
	if ((p_item->m_keyCode & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse && !FUN_00472c40(p_x, p_y)) {
		return NULL;
	}

	if (m_unk0x28 && m_unk0x28->VTable0x18(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0046eb50
ObscureVantage0x58* ObscureAnthem0x58::VTable0x34(OnyxCircularBuffer0x1c::Item* p_item, undefined4 p_x, undefined4 p_y)
{
	if ((p_item->m_keyCode & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse && !FUN_00472c40(p_x, p_y)) {
		return NULL;
	}

	if (m_unk0x28 && m_unk0x28->VTable0x1c(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}
