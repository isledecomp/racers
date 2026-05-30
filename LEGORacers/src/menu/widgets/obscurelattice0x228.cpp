#include "menu/widgets/obscurelattice0x228.h"

#include "input/inputdevice.h"

DECOMP_SIZE_ASSERT(ObscureLattice0x228, 0x228)
DECOMP_SIZE_ASSERT(ObscureLattice0x228::CreateParams0xa0, 0xa0)

// FUNCTION: LEGORACERS 0x00466510
ObscureLattice0x228::ObscureLattice0x228()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00466580
ObscureLattice0x228::~ObscureLattice0x228()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x004665d0
void ObscureLattice0x228::Reset()
{
	m_unk0x220 = NULL;
	m_unk0x224 = 0;
	ObscureGlyph0x21c::Reset();
}

// FUNCTION: LEGORACERS 0x004665f0
LegoBool32 ObscureLattice0x228::FUN_004665f0(
	CreateParams0xa0* p_createParams,
	CeruleanEmperor0x4c::Entry0x150* p_styleEntry
)
{
	VTable0x08();

	m_unk0x220 = p_createParams->m_unk0x9c;
	m_unk0x21c = p_styleEntry;

	return ObscureGlyph0x21c::FUN_004663d0(p_createParams, p_styleEntry);
}

// FUNCTION: LEGORACERS 0x00466620
LegoBool32 ObscureLattice0x228::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (m_flags & 1) {
		return ObscureGlyph0x21c::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00466640
Rect* ObscureLattice0x228::FUN_00466640(Rect* p_rect1, Rect* p_rect2, Rect* p_out)
{
	p_out->m_top = p_rect1->m_top < p_rect2->m_top ? p_rect2->m_top : p_rect1->m_top;
	p_out->m_left = p_rect1->m_left < p_rect2->m_left ? p_rect2->m_left : p_rect1->m_left;
	p_out->m_right = p_rect1->m_right <= p_rect2->m_right ? p_rect1->m_right : p_rect2->m_right;
	p_out->m_bottom = p_rect1->m_bottom > p_rect2->m_bottom ? p_rect2->m_bottom : p_rect1->m_bottom;

	return p_out;
}

// FUNCTION: LEGORACERS 0x00466690
void ObscureLattice0x228::FUN_00466690(LegoU32 p_code)
{
	LegoU32 source = p_code & InputDevice::c_sourceMask;
	LegoU32 id = p_code & InputDevice::c_keyCodeMask;

	if (source == c_sourceRegion) {
		for (LegoS32 i = 0; i < m_unk0x21c->m_unk0xac; i++) {
			if (!id || id == m_unk0x21c->m_unk0xb0[i]) {
				m_unk0x224 = id;

				if (m_eventHandler) {
					m_eventHandler->VTable0x44(this);
				}
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00466700
ObscureVantage0x58* ObscureLattice0x228::VTable0x38(Rect* p_arg1, Rect* p_arg2)
{
	ObscureGlyph0x21c::VTable0x38(p_arg1, p_arg2);
	m_unk0x1c0.VTable0x38(p_arg1, p_arg2);

	if (m_unk0x224) {
		LegoS32 index = 0;
		while (m_unk0x21c->m_unk0xb0[index] != m_unk0x224) {
			index++;
		}

		Rect rect = m_unk0x21c->m_unk0xd0[index];

		Rect sourceRect;
		FUN_00466640(&rect, p_arg1, &sourceRect);

		LegoS32 yOffset = p_arg2->m_top;
		rect.m_top += yOffset;
		rect.m_left += p_arg2->m_left;
		rect.m_right += p_arg2->m_left;
		rect.m_bottom += yOffset;

		Rect destRect;
		FUN_00466640(&rect, p_arg2, &destRect);

		FUN_00472d70(&destRect, &sourceRect, m_unk0x220);
	}

	return this;
}

// FUNCTION: LEGORACERS 0x00466800
ObscureVantage0x58* ObscureLattice0x228::FUN_00466800(InputEventQueue::Event*, undefined4 p_x, undefined4 p_y)
{
	for (LegoS32 i = 0; i < m_unk0x21c->m_unk0xac; i++) {
		if (FUN_00473a20(&m_unk0x21c->m_unk0xd0[i], p_x, p_y)) {
			FUN_00466690(m_unk0x21c->m_unk0xb0[i] | c_sourceRegion);
			return this;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466880
ObscureVantage0x58* ObscureLattice0x228::VTable0x30(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	LegoU32 keyCode = p_item->m_keyCode;
	LegoU32 source = keyCode & InputDevice::c_sourceMask;
	LegoU8 stateFlags = m_stateFlags;

	if (!(stateFlags & c_flagBit0)) {
		return NULL;
	}

	if (!(stateFlags & c_flagBit2)) {
		if (!(stateFlags & c_flagBit1)) {
			return NULL;
		}

		if (source == InputDevice::c_sourceMouse && FUN_00472c40(p_x, p_y)) {
			return FUN_00466800(p_item, p_x, p_y);
		}

		if (p_item->m_isRepeat) {
			return NULL;
		}

		switch (keyCode) {
		case InputDevice::c_sourceKeyboard | 0x39:
		case InputDevice::c_sourceKeyboard | 0x9c:
		case InputDevice::c_sourceJoystickButton | 0x4:
			VTable0x54(0);
			return this;
		}

		return NULL;
	}

	if (source == InputDevice::c_sourceKeyboard || source == InputDevice::c_sourceJoystickButton) {
		switch (keyCode) {
		case InputDevice::c_sourceKeyboard | 0x39:
		case InputDevice::c_sourceKeyboard | 0x9c:
		case InputDevice::c_sourceJoystickButton | 0x4:
			VTable0x58(0);
			break;
		}
	}
	else if (source == c_sourceRegion) {
		FUN_00466690(keyCode);
	}

	return this;
}

// FUNCTION: LEGORACERS 0x00466980
ObscureVantage0x58* ObscureLattice0x228::VTable0x34(InputEventQueue::Event* p_item, undefined4, undefined4)
{
	LegoU32 source = p_item->m_keyCode & InputDevice::c_sourceMask;
	LegoU8 stateFlags = m_stateFlags;

	if (stateFlags & c_flagBit0) {
		if (!(stateFlags & c_flagBit2)) {
			if (source != InputDevice::c_sourceMouse) {
				return this;
			}
		}
		else if (source != c_sourceRegion) {
			return this;
		}

		if (m_unk0x224) {
			FUN_00466690(c_sourceRegion);
			return this;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004669e0
void ObscureLattice0x228::VTable0x58(undefined4 p_flags)
{
	if (m_unk0x224) {
		FUN_00466690(c_sourceRegion);
	}

	ObscureIcon0x1a8::VTable0x58(p_flags);
}
