#include "menu/widgets/menuselector.h"

#include "input/inputdevice.h"

DECOMP_SIZE_ASSERT(MenuSelectorBase, 0x5ec)
DECOMP_SIZE_ASSERT(MenuSelector, 0x9f4)

// FUNCTION: LEGORACERS 0x00466f60
MenuSelectorBase::MenuSelectorBase()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00466ff0
MenuSelectorBase::~MenuSelectorBase()
{
}

// FUNCTION: LEGORACERS 0x00467060
void MenuSelectorBase::Reset()
{
	m_unk0x1ac.VTable0x08();
	m_unk0x3c8.VTable0x08();
	m_unk0x1a8 = 0;
	m_unk0x5e4 = 0;
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x004670a0
LegoBool32 MenuSelectorBase::FUN_004670a0(
	CreateParams* p_createParams,
	const MenuStyleTable::SelectorStyleBase* p_styleEntry
)
{
	static_cast<MenuWidget::CreateParams*>(p_createParams->m_unk0x84)->m_parent = this;
	static_cast<MenuWidget::CreateParams*>(p_createParams->m_unk0x88)->m_parent = this;

	if (!m_unk0x1ac.FUN_004663d0(p_createParams->m_unk0x84, p_styleEntry->m_unk0x90)) {
		return FALSE;
	}

	if (!m_unk0x3c8.FUN_004663d0(p_createParams->m_unk0x88, p_styleEntry->m_unk0x94)) {
		return FALSE;
	}

	if (m_stateFlags & c_flagBit0) {
		m_unk0x1ac.VTable0x44(5);
		m_unk0x3c8.VTable0x44(5);
	}
	else {
		m_unk0x1ac.VTable0x48(5);
		m_unk0x3c8.VTable0x48(5);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467150
LegoBool32 MenuSelectorBase::FUN_00467150(
	CreateParams* p_createParams,
	const MenuStyleTable::SelectorStyleBase* p_styleEntry
)
{
	if (FUN_00471e30(p_createParams, p_styleEntry)) {
		return FUN_004670a0(p_createParams, p_styleEntry);
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00467180
void MenuSelectorBase::FUN_00467180(undefined4 p_param)
{
	if (m_unk0x54 & 1) {
		return;
	}

	m_unk0x5e4 = -1;

	if (m_unk0x1ac.GetStateFlags() & c_flagBit2) {
		VTable0x78();

		if (p_param) {
			m_unk0x1ac.VTable0x58(2);
			VTable0x58(0);
		}
	}
	else {
		m_unk0x3c8.VTable0x58(2);
	}
}

// FUNCTION: LEGORACERS 0x004671e0
void MenuSelectorBase::FUN_004671e0(undefined4 p_param)
{
	if (m_unk0x54 & 1) {
		return;
	}

	m_unk0x5e4 = 1;

	if (m_unk0x3c8.GetStateFlags() & c_flagBit2) {
		VTable0x7c();

		if (p_param) {
			m_unk0x3c8.VTable0x58(2);
			VTable0x58(0);
		}
	}
	else {
		m_unk0x1ac.VTable0x58(2);
	}
}

// FUNCTION: LEGORACERS 0x00467240
void MenuSelectorBase::VTable0x44(undefined4 p_flags)
{
	if (m_stateFlags & c_flagBit0) {
		return;
	}

	if (m_unk0x1ac.GetFlags() & 1) {
		m_unk0x1ac.VTable0x44(2);
		m_unk0x3c8.VTable0x44(2);
	}

	MenuIcon::VTable0x44(p_flags);
}

// FUNCTION: LEGORACERS 0x00467290
void MenuSelectorBase::VTable0x48(undefined4 p_flags)
{
	if (!(m_stateFlags & c_flagBit0)) {
		return;
	}

	if (m_unk0x1ac.GetFlags() & 1) {
		m_unk0x1ac.VTable0x48(5);
		m_unk0x3c8.VTable0x48(5);
	}

	MenuIcon::VTable0x48(p_flags);
}

// FUNCTION: LEGORACERS 0x004672e0
void MenuSelectorBase::VTable0x4c(undefined4 p_flags)
{
	MenuIcon::VTable0x4c(p_flags);

	if (m_unk0x1ac.GetFlags() & 1) {
		m_unk0x1ac.VTable0x4c(2);
		m_unk0x3c8.VTable0x4c(2);
	}
}

// FUNCTION: LEGORACERS 0x00467320
void MenuSelectorBase::VTable0x50(undefined4 p_flags)
{
	MenuIcon::VTable0x50(p_flags);

	if (m_unk0x1ac.GetFlags() & 1) {
		m_unk0x1ac.VTable0x50(2);
		m_unk0x3c8.VTable0x50(2);
	}
}

// FUNCTION: LEGORACERS 0x00467360
void MenuSelectorBase::VTable0x58(undefined4 p_flags)
{
	MenuIcon::VTable0x58(p_flags);

	if (m_unk0x1ac.GetFlags() & 1) {
		m_unk0x1ac.VTable0x58(2);
		m_unk0x3c8.VTable0x58(2);
	}
}

// FUNCTION: LEGORACERS 0x004673a0
undefined4 MenuSelectorBase::VTable0x70(undefined4 p_event, undefined4 p_x, undefined4 p_y)
{
	if ((p_event & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		undefined4 x = p_x;
		undefined4 y = p_y;
		m_unk0x1ac.ScreenToLocal(x, y);
		if (m_unk0x1ac.HitTest(x, y)) {
			return InputDevice::c_sourceJoystickButton | 0xb;
		}

		x = p_x;
		y = p_y;
		m_unk0x3c8.ScreenToLocal(x, y);
		if (m_unk0x3c8.HitTest(x, y)) {
			return InputDevice::c_sourceJoystickButton | 0xa;
		}
	}

	return p_event;
}

// FUNCTION: LEGORACERS 0x00467450
LegoBool32 MenuSelectorBase::VTable0x20(MenuInputDispatcher::Cursor* p_cursor, undefined4 p_x, undefined4 p_y)
{
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	if (HitTest(x, y) && VTable0x2c(p_cursor, x, y)) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004674c0
LegoBool32 MenuSelectorBase::VTable0x24(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	return MenuEventResult(VTable0x30(p_param1, x, y));
}

// FUNCTION: LEGORACERS 0x00467510
LegoBool32 MenuSelectorBase::VTable0x28(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	return MenuEventResult(VTable0x34(p_param1, x, y));
}

// FUNCTION: LEGORACERS 0x00467560
LegoBool32 MenuSelectorBase::FUN_00467560(InputEventQueue::Event* p_event, undefined4 p_result)
{
	switch (p_result) {
	case InputDevice::c_sourceJoystickButton | 0xa:
		if (m_unk0x3c8.GetUnk0x54() & 1) {
			return TRUE;
		}

		if (p_event->m_isRepeat && (m_unk0x3c8.GetStateFlags() & c_flagBit2)) {
			FUN_004671e0(0);
			return TRUE;
		}

		if (m_stateFlags & c_flagBit2) {
			return TRUE;
		}

		m_unk0x3c8.VTable0x54(2);
		FUN_004671e0(0);
		VTable0x54(0);
		return TRUE;

	case InputDevice::c_sourceJoystickButton | 0xb:
		if (m_unk0x1ac.GetUnk0x54() & 1) {
			return TRUE;
		}

		if (p_event->m_isRepeat && (m_unk0x1ac.GetStateFlags() & c_flagBit2)) {
			FUN_00467180(0);
			return TRUE;
		}

		if (m_stateFlags & c_flagBit2) {
			return TRUE;
		}

		m_unk0x1ac.VTable0x54(2);
		FUN_00467180(0);
		VTable0x54(0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00467670
LegoBool32 MenuSelectorBase::FUN_00467670(InputEventQueue::Event*, undefined4 p_result)
{
	if (p_result == (InputDevice::c_sourceJoystickButton | 0x1)) {
		return FALSE;
	}

	MenuButton* glyph;
	if (m_unk0x1ac.GetStateFlags() & c_flagBit2) {
		glyph = &m_unk0x1ac;
	}
	else if (m_unk0x3c8.GetStateFlags() & c_flagBit2) {
		glyph = &m_unk0x3c8;
	}
	else {
		return FALSE;
	}

	glyph->VTable0x58(1);
	VTable0x58(1);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004676d0
MenuSelector::MenuSelector()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00467750
MenuSelector::~MenuSelector()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x004677b0
void MenuSelector::Reset()
{
	m_unk0x5ec.VTable0x08();
	m_unk0x9e8 = NULL;
	m_unk0x9f0 = 0;
	m_unk0x9ec = 0;
	MenuSelectorBase::Reset();
}

// FUNCTION: LEGORACERS 0x004677e0
LegoBool32 MenuSelectorBase::FUN_004677e0(CreateParamsWithCarousel* p_createParams)
{
	p_createParams->m_unk0x8c->m_parent = this;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467800
LegoBool32 MenuSelector::FUN_00467800(CreateParams* p_createParams, MenuStyleTable::SelectorStyle* p_styleEntry)
{
	VTable0x08();

	if (FUN_00467150(p_createParams, p_styleEntry) && FUN_004677e0(p_createParams)) {
		m_styleEntry = p_styleEntry;
		m_unk0x9e8 = p_createParams->m_unk0x90;
		m_unk0x9e8->VTable0x14(&m_unk0x174[m_visualStateIndex]);
		m_unk0x9ec = p_createParams->m_unk0x94;
		m_unk0x9e8->SetParent(this);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00467880
LegoBool32 MenuSelector::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		if (m_unk0x9e8) {
			m_unk0x9e8->VTable0x08();
		}

		result = MenuIcon::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004678b0
void MenuSelector::VTable0x14(VisualStateColor* p_visualState)
{
	if (m_unk0x9e8) {
		m_unk0x9e8->VTable0x14(p_visualState);
	}

	MenuWidget::VTable0x14(p_visualState);
}

// FUNCTION: LEGORACERS 0x004678e0
LegoBool32 MenuSelector::VTable0x24(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	if (VTable0x30(p_param1, x, y)) {
		return TRUE;
	}

	return m_unk0x9e8->VTable0x24(p_param1, x, y);
}

// FUNCTION: LEGORACERS 0x00467960
void MenuSelector::VTable0x78()
{
	if (m_unk0x9f0) {
		return;
	}

	LegoU32 previousIndex = m_unk0x9e8->GetUnk0x6c();
	m_unk0x9e8->VTable0x58();

	if (m_unk0x9e8->GetUnk0x6c() != previousIndex && m_eventHandler) {
		m_eventHandler->VTable0x44(this);
	}

	m_unk0x9f0 = m_unk0x9e8->GetUnk0x54() & 1;
}

// FUNCTION: LEGORACERS 0x004679b0
void MenuSelector::VTable0x7c()
{
	if (m_unk0x9f0) {
		return;
	}

	LegoU32 previousIndex = m_unk0x9e8->GetUnk0x6c();
	m_unk0x9e8->VTable0x54();

	if (m_unk0x9e8->GetUnk0x6c() != previousIndex && m_eventHandler) {
		m_eventHandler->VTable0x44(this);
	}

	m_unk0x9f0 = m_unk0x9e8->GetUnk0x54() & 1;
}

// FUNCTION: LEGORACERS 0x00467a00
undefined4 MenuSelector::VTable0x3c(undefined4)
{
	LegoU32 index = m_stateFlags & c_flagBit1;

	if (m_unk0x9f0 && !(m_unk0x9e8->GetUnk0x54() & 1) && m_eventHandler) {
		m_eventHandler->VTable0x48(this);
		m_unk0x9f0 = 0;
	}

	m_unk0x9e8->VTable0x48(&GetStyleEntry()->m_unk0x9c[index], &GetStyleEntry()->m_unk0x9c[index + 1]);
	m_unk0x9e8->VTable0x4c(&GetStyleEntry()->m_unk0x9c[index], &GetStyleEntry()->m_unk0x9c[index + 1]);

	if (m_unk0x1ac.GetStateFlags() & c_flagBit2) {
		VTable0x78();
	}
	else if (m_unk0x3c8.GetStateFlags() & c_flagBit2) {
		VTable0x7c();
	}
	else {
		MenuCarousel* carousel = m_unk0x9e8;
		MenuStyleTable::SelectorStyle* styleEntry = GetStyleEntry();
		carousel->VTable0x4c(&styleEntry->m_unk0xac[index], &styleEntry->m_unk0xac[index + 1]);
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00467ae0
undefined4 MenuSelector::VTable0x74(undefined4 p_event)
{
	switch (p_event) {
	case InputDevice::c_sourceJoystickButton | 0x7:
	case InputDevice::c_sourceJoystickAxisButton | 0x0:
	case InputDevice::c_sourceJoystickButton | 0xa:
	case InputDevice::c_sourceKeyboard | 0xcd:
		return InputDevice::c_sourceJoystickButton | 0xa;
	case InputDevice::c_sourceJoystickButton | 0x9:
	case InputDevice::c_sourceJoystickButton | 0xb:
	case InputDevice::c_sourceJoystickAxisButton | 0x1:
	case InputDevice::c_sourceKeyboard | 0xcb:
		return InputDevice::c_sourceJoystickButton | 0xb;
	default:
		return InputDevice::c_sourceJoystickButton | 0x1;
	}
}

// FUNCTION: LEGORACERS 0x00467b50
MenuWidget* MenuSelector::VTable0x30(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	LegoU8 stateFlags = m_stateFlags;
	LegoU32 keyCode = p_param1->m_keyCode;

	if ((stateFlags & c_flagBit0) && (!m_activeKeyCode || m_activeKeyCode == keyCode) &&
		((stateFlags & c_flagBit2) || !p_param1->m_isRepeat)) {

		undefined4 mappedEvent = VTable0x70(keyCode, p_x, p_y);
		undefined4 result = VTable0x74(mappedEvent);

		stateFlags = m_stateFlags;
		if ((stateFlags & c_flagBit0) && ((stateFlags & c_flagBit1) || m_unk0x9ec) && FUN_00467560(p_param1, result)) {
			m_activeKeyCode = p_param1->m_keyCode;
			return this;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00467be0
MenuWidget* MenuSelector::VTable0x34(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	LegoU32 keyCode = p_param1->m_keyCode;

	if (m_activeKeyCode != keyCode) {
		return NULL;
	}

	undefined4 mappedEvent = VTable0x70(keyCode, p_x, p_y);
	undefined4 result = VTable0x74(mappedEvent);

	LegoU8 stateFlags = m_stateFlags;
	m_activeKeyCode = 0;

	if ((stateFlags & c_flagBit0) && (stateFlags & c_flagBit2) && ((stateFlags & c_flagBit1) || m_unk0x9ec)) {
		FUN_00467670(p_param1, result);
	}

	VTable0x58(0);
	return this;
}
