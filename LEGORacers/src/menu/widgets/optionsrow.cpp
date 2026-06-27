#include "menu/widgets/optionsrow.h"

#include "audio/soundgroupbinding.h"
#include "input/inputdevice.h"

DECOMP_SIZE_ASSERT(OptionsRowBase, 0x6e4)
DECOMP_SIZE_ASSERT(OptionsRow, 0x6ec)

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 OptionsRowBase::VTable0x3c(undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046de60
OptionsRowBase::OptionsRowBase()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046def0
OptionsRowBase::~OptionsRowBase()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046df60
void OptionsRowBase::Reset()
{
	m_unk0x6c0 = 0;
	m_unk0x6c8 = 0;
	m_unk0x6c4 = 0;
	m_unk0x6cc = 0.0f;
	m_styleEntry = NULL;
	m_unk0x648.VTable0x08();
	m_unk0x5ec.VTable0x08();
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x0046dfb0
LegoBool32 OptionsRowBase::FUN_0046dfb0(
	MenuInputBindingTable::CompositeBinding* p_createParams,
	MenuStyleTable::CompositeStyle* p_styleEntry
)
{
	VTable0x08();

	m_styleEntry = p_styleEntry;
	m_unk0x6c0 = p_createParams->m_unk0xb0;
	m_unk0x6bc = p_createParams->m_unk0xb4;

	MenuIcon::SoundIdPair* soundIds = &p_createParams->m_unk0xac;
	if (!p_createParams->m_unk0x7c) {
		soundIds = &p_styleEntry->m_unk0xb8;
	}

	m_unk0x6e0 = *soundIds;

	if (FUN_00467150(p_createParams, p_styleEntry)) {
		p_createParams->m_unk0x90->m_parent = this;
		p_createParams->m_unk0x8c->m_parent = this;

		if (m_unk0x648.FUN_0046f150(p_createParams->m_unk0x90) && m_unk0x5ec.FUN_0046f150(p_createParams->m_unk0x8c)) {
			VTable0x80();
			VTable0x84();
			VTable0x88();
			VTable0x14(&m_visualState);
			return TRUE;
		}
	}

	VTable0x08();
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046e090
void OptionsRowBase::VTable0x14(VisualStateColor* p_visualState)
{
	m_unk0x648.VTable0x14(p_visualState);
	m_unk0x5ec.VTable0x14(p_visualState);
	MenuWidget::VTable0x14(p_visualState);
}

// FUNCTION: LEGORACERS 0x0046e0d0
void OptionsRowBase::VTable0x78()
{
	if (m_unk0x6c0) {
		VTable0x90(m_unk0x6c0 - 1);
		if (m_eventHandler) {
			m_eventHandler->VTable0x44(this);
		}

		m_soundGroupBinding->FUN_0046e970(m_unk0x6e0.m_unk0x00);
		return;
	}

	m_soundGroupBinding->FUN_0046e970(m_unk0x6e0.m_unk0x02);
}

// FUNCTION: LEGORACERS 0x0046e130
void OptionsRowBase::VTable0x7c()
{
	if (m_unk0x6c0 != m_unk0x6bc - 1) {
		VTable0x90(m_unk0x6c0 + 1);
		if (m_eventHandler) {
			m_eventHandler->VTable0x44(this);
		}

		m_soundGroupBinding->FUN_0046e970(m_unk0x6e0.m_unk0x00);
		return;
	}

	m_soundGroupBinding->FUN_0046e970(m_unk0x6e0.m_unk0x02);
}

// FUNCTION: LEGORACERS 0x0046e190
undefined4 OptionsRowBase::VTable0x74(undefined4 p_event)
{
	if ((p_event & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		return p_event;
	}

	switch (p_event) {
	case InputDevice::c_sourceJoystickButton | 0x7:
	case InputDevice::c_sourceJoystickButton | 0xa:
	case InputDevice::c_sourceKeyboard | 0xcd:
	case InputDevice::c_sourceJoystickAxisButton | 0x0:
		return InputDevice::c_sourceJoystickButton | 0xa;
	case InputDevice::c_sourceJoystickButton | 0x9:
	case InputDevice::c_sourceJoystickButton | 0xb:
	case InputDevice::c_sourceKeyboard | 0xcb:
	case InputDevice::c_sourceJoystickAxisButton | 0x1:
		return InputDevice::c_sourceJoystickButton | 0xb;
	default:
		return InputDevice::c_sourceJoystickButton | 0x1;
	}
}

// FUNCTION: LEGORACERS 0x0046e210
MenuWidget* OptionsRowBase::VTable0x30(InputEventQueue::Event* p_event, undefined4 p_x, undefined4 p_y)
{
	LegoU8 stateFlags = m_stateFlags;
	LegoU32 keyCode = p_event->m_keyCode;

	if ((stateFlags & c_flagBit0) && (!m_activeKeyCode || m_activeKeyCode == keyCode) &&
		((stateFlags & c_flagBit2) || !p_event->m_isRepeat)) {
		undefined4 mappedEvent = VTable0x70(keyCode, p_x, p_y);
		undefined4 result = VTable0x74(mappedEvent);

		stateFlags = m_stateFlags;
		if ((stateFlags & c_flagBit0) && (stateFlags & c_flagBit1)) {
			if ((result & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
				undefined4 x = p_x;
				undefined4 y = p_y;
				m_unk0x5ec.ScreenToLocal(x, y);

				if (m_unk0x5ec.HitTest(x, y)) {
					m_activeKeyCode = p_event->m_keyCode;
					m_soundGroupBinding->FUN_0046e970(m_unk0x6e0.m_unk0x00);
					SetFocus();
					VTable0x54(0);
					return this;
				}
			}

			if (FUN_00467560(p_event, result)) {
				m_activeKeyCode = p_event->m_keyCode;
				return this;
			}
		}

		m_activeKeyCode = 0;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0046e340
MenuWidget* OptionsRowBase::VTable0x34(InputEventQueue::Event* p_event, undefined4 p_x, undefined4 p_y)
{
	LegoU32 keyCode = p_event->m_keyCode;

	if (m_activeKeyCode != keyCode) {
		return NULL;
	}

	undefined4 mappedEvent = VTable0x70(keyCode, p_x, p_y);
	undefined4 result = VTable0x74(mappedEvent);

	LegoU8 stateFlags = m_stateFlags;
	m_activeKeyCode = 0;

	if ((stateFlags & c_flagBit0) && (stateFlags & c_flagBit2) && (stateFlags & c_flagBit1) &&
		FUN_00467670(p_event, result)) {
		return this;
	}

	if ((result & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		m_soundGroupBinding->FUN_0046e970(m_unk0x6e0.m_unk0x00);
		VTable0x8c();
		ClearFocus();
	}

	VTable0x58(0);
	return this;
}

// FUNCTION: LEGORACERS 0x0046e3f0
OptionsRow::OptionsRow()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046e460
OptionsRow::~OptionsRow()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046e4b0
void OptionsRow::FUN_0046e4b0()
{
	m_unk0x6c4 = m_unk0x1ac.GetRect()->m_right + ((m_unk0x5ec.GetRect()->m_right - m_unk0x5ec.GetRect()->m_left) >> 1);
	m_unk0x6c8 = m_unk0x3c8.GetRect()->m_left - ((m_unk0x5ec.GetRect()->m_right - m_unk0x5ec.GetRect()->m_left) >> 1);
	m_unk0x6cc = static_cast<LegoFloat>(m_unk0x6c8 - m_unk0x6c4);

	if (m_unk0x6bc > 2) {
		m_unk0x6cc = m_unk0x6cc / static_cast<LegoFloat>(m_unk0x6bc - 1);
	}
}

// FUNCTION: LEGORACERS 0x0046e530
void OptionsRow::VTable0x80()
{
	Rect rect;
	rect.m_top = 0;
	rect.m_left = 0;
	rect.m_bottom = m_unk0x34.m_bottom - m_unk0x34.m_top;
	rect.m_right = m_unk0x1ac.GetRect()->m_right - m_unk0x1ac.GetRect()->m_left;
	m_unk0x1ac.VTable0x10(&rect);

	rect.m_right = m_unk0x34.m_right - m_unk0x34.m_left;
	rect.m_left = rect.m_right + (m_unk0x3c8.GetRect()->m_left - m_unk0x3c8.GetRect()->m_right);
	m_unk0x3c8.VTable0x10(&rect);
}

// FUNCTION: LEGORACERS 0x0046e5b0
void OptionsRow::VTable0x84()
{
	Rect rect;
	rect.m_left = m_unk0x1ac.GetRect()->m_right + 1;
	rect.m_right = m_unk0x3c8.GetRect()->m_left - 1;

	LegoS32 height = m_unk0x648.GetRect()->m_bottom - m_unk0x648.GetRect()->m_top;
	rect.m_top = ((m_unk0x34.m_bottom - m_unk0x34.m_top) >> 1) - (height >> 1);
	rect.m_bottom = rect.m_top + height;

	m_unk0x648.VTable0x10(&rect);
	m_unk0x6d0 = *m_unk0x648.GetGlobalRect();
}

// FUNCTION: LEGORACERS 0x0046e630
void OptionsRow::VTable0x88()
{
	Rect rect;
	rect.m_left = m_unk0x1ac.GetRect()->m_right;
	rect.m_right = m_unk0x5ec.GetRect()->m_right + rect.m_left;

	LegoS32 height = m_unk0x5ec.GetRect()->m_bottom - m_unk0x5ec.GetRect()->m_top;
	rect.m_top = ((m_unk0x34.m_bottom - m_unk0x34.m_top) >> 1) - (height >> 1);
	rect.m_bottom = rect.m_top + height;

	m_unk0x5ec.VTable0x10(&rect);
	FUN_0046e4b0();
	VTable0x90(m_unk0x6c0);
}

// FUNCTION: LEGORACERS 0x0046e6b0
void OptionsRow::VTable0x8c()
{
	LegoS32 index = static_cast<LegoS32>(
		(static_cast<LegoFloat>(m_unk0x5ec.GetRect()->m_left - m_unk0x1ac.GetRect()->m_right) / m_unk0x6cc) + 0.5f
	);

	VTable0x90(index);
}

// FUNCTION: LEGORACERS 0x0046e6f0
void OptionsRow::VTable0x90(LegoS32 p_unk0x04)
{
	if (p_unk0x04 != m_unk0x6c0) {
		double step = m_unk0x6cc;
		double index = p_unk0x04;
		Rect rect = *m_unk0x5ec.GetRect();
		LegoS32 width = rect.m_right - rect.m_left;
		rect.m_left = m_unk0x6c4 + static_cast<LegoS32>(step * index) - (width >> 1);
		rect.m_right = width + rect.m_left;
		m_unk0x5ec.VTable0x10(&rect);

		m_unk0x6c0 = p_unk0x04;
		if (m_eventHandler) {
			m_eventHandler->VTable0x44(this);
		}
	}
}

// FUNCTION: LEGORACERS 0x0046e780
undefined4 OptionsRow::VTable0x70(undefined4 p_event, undefined4 p_x, undefined4 p_y)
{
	if ((p_event & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		undefined4 x = p_x;
		undefined4 y = p_y;
		m_unk0x5ec.ScreenToLocal(x, y);

		if (!(m_stateFlags & c_flagBit2) && m_unk0x5ec.HitTest(x, y)) {
			return p_event;
		}

		return MenuSelectorBase::VTable0x70(p_event, p_x, p_y);
	}

	return p_event;
}

// STUB: LEGORACERS 0x0046e810
MenuWidget* OptionsRow::VTable0x2c(void* p_item, undefined4 p_x, undefined4 p_y)
{
	MenuIcon::VTable0x2c(p_item, p_x, p_y);

	if (!(m_flags & 8)) {
		return NULL;
	}

	if (!(m_unk0x1ac.GetStateFlags() & c_flagBit2) && !(m_unk0x3c8.GetStateFlags() & c_flagBit2)) {
		MenuInputDispatcher::Cursor* cursor = static_cast<MenuInputDispatcher::Cursor*>(p_item);
		cursor->m_bounds = m_unk0x6d0;

		Rect rect = *m_unk0x5ec.GetRect();
		LegoS32 width = rect.m_right;
		width -= rect.m_left;
		rect.m_left += p_x;
		rect.m_right += p_x;

		if (rect.m_left < m_unk0x1ac.GetRect()->m_right) {
			rect.m_left = m_unk0x1ac.GetRect()->m_right;
			rect.m_right = rect.m_left + width;
		}
		else if (rect.m_right > m_unk0x3c8.GetRect()->m_left) {
			rect.m_right = m_unk0x3c8.GetRect()->m_left;
			rect.m_left = rect.m_right - width;
		}

		m_unk0x5ec.VTable0x10(&rect);
	}

	return this;
}
