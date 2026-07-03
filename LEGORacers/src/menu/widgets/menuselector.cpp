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
	m_prevButton.Destroy();
	m_nextButton.Destroy();
	m_unk0x1a8 = 0;
	m_stepDirection = 0;
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x004670a0
LegoBool32 MenuSelectorBase::Create(CreateParams* p_createParams, const MenuStyleTable::SelectorStyleBase* p_styleEntry)
{
	static_cast<MenuWidget::CreateParams*>(p_createParams->m_prevButtonParams)->m_parent = this;
	static_cast<MenuWidget::CreateParams*>(p_createParams->m_nextButtonParams)->m_parent = this;

	if (!m_prevButton.Create(p_createParams->m_prevButtonParams, p_styleEntry->m_prevButtonStyle)) {
		return FALSE;
	}

	if (!m_nextButton.Create(p_createParams->m_nextButtonParams, p_styleEntry->m_nextButtonStyle)) {
		return FALSE;
	}

	if (m_stateFlags & c_flagEnabled) {
		m_prevButton.Enable(5);
		m_nextButton.Enable(5);
	}
	else {
		m_prevButton.Disable(5);
		m_nextButton.Disable(5);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467150
LegoBool32 MenuSelectorBase::CreateDefault(
	CreateParams* p_createParams,
	const MenuStyleTable::SelectorStyleBase* p_styleEntry
)
{
	if (MenuIcon::Create(p_createParams, p_styleEntry)) {
		return Create(p_createParams, p_styleEntry);
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00467180
void MenuSelectorBase::OnPreviousPressed(undefined4 p_param)
{
	if (m_animFlags & 1) {
		return;
	}

	m_stepDirection = -1;

	if (m_prevButton.GetStateFlags() & c_flagFocused) {
		StepPrevious();

		if (p_param) {
			m_prevButton.Unfocus(2);
			Unfocus(0);
		}
	}
	else {
		m_nextButton.Unfocus(2);
	}
}

// FUNCTION: LEGORACERS 0x004671e0
void MenuSelectorBase::OnNextPressed(undefined4 p_param)
{
	if (m_animFlags & 1) {
		return;
	}

	m_stepDirection = 1;

	if (m_nextButton.GetStateFlags() & c_flagFocused) {
		StepNext();

		if (p_param) {
			m_nextButton.Unfocus(2);
			Unfocus(0);
		}
	}
	else {
		m_prevButton.Unfocus(2);
	}
}

// FUNCTION: LEGORACERS 0x00467240
void MenuSelectorBase::Enable(undefined4 p_flags)
{
	if (m_stateFlags & c_flagEnabled) {
		return;
	}

	if (m_prevButton.GetFlags() & 1) {
		m_prevButton.Enable(2);
		m_nextButton.Enable(2);
	}

	MenuIcon::Enable(p_flags);
}

// FUNCTION: LEGORACERS 0x00467290
void MenuSelectorBase::Disable(undefined4 p_flags)
{
	if (!(m_stateFlags & c_flagEnabled)) {
		return;
	}

	if (m_prevButton.GetFlags() & 1) {
		m_prevButton.Disable(5);
		m_nextButton.Disable(5);
	}

	MenuIcon::Disable(p_flags);
}

// FUNCTION: LEGORACERS 0x004672e0
void MenuSelectorBase::Select(undefined4 p_flags)
{
	MenuIcon::Select(p_flags);

	if (m_prevButton.GetFlags() & 1) {
		m_prevButton.Select(2);
		m_nextButton.Select(2);
	}
}

// FUNCTION: LEGORACERS 0x00467320
void MenuSelectorBase::Deselect(undefined4 p_flags)
{
	MenuIcon::Deselect(p_flags);

	if (m_prevButton.GetFlags() & 1) {
		m_prevButton.Deselect(2);
		m_nextButton.Deselect(2);
	}
}

// FUNCTION: LEGORACERS 0x00467360
void MenuSelectorBase::Unfocus(undefined4 p_flags)
{
	MenuIcon::Unfocus(p_flags);

	if (m_prevButton.GetFlags() & 1) {
		m_prevButton.Unfocus(2);
		m_nextButton.Unfocus(2);
	}
}

// FUNCTION: LEGORACERS 0x004673a0
undefined4 MenuSelectorBase::MapCursorToNavigation(undefined4 p_event, undefined4 p_x, undefined4 p_y)
{
	if ((p_event & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		undefined4 x = p_x;
		undefined4 y = p_y;
		m_prevButton.ScreenToLocal(x, y);
		if (m_prevButton.HitTest(x, y)) {
			return InputDevice::c_sourceJoystickButton | 0xb;
		}

		x = p_x;
		y = p_y;
		m_nextButton.ScreenToLocal(x, y);
		if (m_nextButton.HitTest(x, y)) {
			return InputDevice::c_sourceJoystickButton | 0xa;
		}
	}

	return p_event;
}

// FUNCTION: LEGORACERS 0x00467450
LegoBool32 MenuSelectorBase::DispatchCursorEvent(MenuInputDispatcher::Cursor* p_cursor, undefined4 p_x, undefined4 p_y)
{
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	if (HitTest(x, y) && OnCursorEvent(p_cursor, x, y)) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004674c0
LegoBool32 MenuSelectorBase::DispatchKeyDown(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	return MenuEventResult(OnKeyDown(p_param1, x, y));
}

// FUNCTION: LEGORACERS 0x00467510
LegoBool32 MenuSelectorBase::DispatchKeyUp(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	return MenuEventResult(OnKeyUp(p_param1, x, y));
}

// FUNCTION: LEGORACERS 0x00467560
LegoBool32 MenuSelectorBase::HandleNavigationKeyDown(InputEventQueue::Event* p_event, undefined4 p_result)
{
	switch (p_result) {
	case InputDevice::c_sourceJoystickButton | 0xa:
		if (m_nextButton.GetAnimFlags() & 1) {
			return TRUE;
		}

		if (p_event->m_isRepeat && (m_nextButton.GetStateFlags() & c_flagFocused)) {
			OnNextPressed(0);
			return TRUE;
		}

		if (m_stateFlags & c_flagFocused) {
			return TRUE;
		}

		m_nextButton.Focus(2);
		OnNextPressed(0);
		Focus(0);
		return TRUE;

	case InputDevice::c_sourceJoystickButton | 0xb:
		if (m_prevButton.GetAnimFlags() & 1) {
			return TRUE;
		}

		if (p_event->m_isRepeat && (m_prevButton.GetStateFlags() & c_flagFocused)) {
			OnPreviousPressed(0);
			return TRUE;
		}

		if (m_stateFlags & c_flagFocused) {
			return TRUE;
		}

		m_prevButton.Focus(2);
		OnPreviousPressed(0);
		Focus(0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00467670
LegoBool32 MenuSelectorBase::HandleNavigationKeyUp(InputEventQueue::Event*, undefined4 p_result)
{
	if (p_result == (InputDevice::c_sourceJoystickButton | 0x1)) {
		return FALSE;
	}

	MenuButton* glyph;
	if (m_prevButton.GetStateFlags() & c_flagFocused) {
		glyph = &m_prevButton;
	}
	else if (m_nextButton.GetStateFlags() & c_flagFocused) {
		glyph = &m_nextButton;
	}
	else {
		return FALSE;
	}

	glyph->Unfocus(1);
	Unfocus(1);
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
	Destroy();
}

// FUNCTION: LEGORACERS 0x004677b0
void MenuSelector::Reset()
{
	m_unk0x5ec.Destroy();
	m_carousel = NULL;
	m_scrollPending = 0;
	m_acceptUnfocusedInput = 0;
	MenuSelectorBase::Reset();
}

// FUNCTION: LEGORACERS 0x004677e0
LegoBool32 MenuSelectorBase::CreateWithFrame(CreateParamsWithCarousel* p_createParams)
{
	p_createParams->m_frameParams->m_parent = this;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00467800
LegoBool32 MenuSelector::Create(CreateParams* p_createParams, MenuStyleTable::SelectorStyle* p_styleEntry)
{
	Destroy();

	if (CreateDefault(p_createParams, p_styleEntry) && CreateWithFrame(p_createParams)) {
		m_styleEntry = p_styleEntry;
		m_carousel = p_createParams->m_carouselWidget;
		m_carousel->SetColor(&m_stateColors[m_visualStateIndex]);
		m_acceptUnfocusedInput = p_createParams->m_acceptUnfocusedInput;
		m_carousel->SetParent(this);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00467880
LegoBool32 MenuSelector::Destroy()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		if (m_carousel) {
			m_carousel->Destroy();
		}

		result = MenuIcon::Destroy();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004678b0
void MenuSelector::SetColor(VisualStateColor* p_visualState)
{
	if (m_carousel) {
		m_carousel->SetColor(p_visualState);
	}

	MenuWidget::SetColor(p_visualState);
}

// FUNCTION: LEGORACERS 0x004678e0
LegoBool32 MenuSelector::DispatchKeyDown(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	if (OnKeyDown(p_param1, x, y)) {
		return TRUE;
	}

	return m_carousel->DispatchKeyDown(p_param1, x, y);
}

// FUNCTION: LEGORACERS 0x00467960
void MenuSelector::StepPrevious()
{
	if (m_scrollPending) {
		return;
	}

	LegoU32 previousIndex = m_carousel->GetSelectedIndex();
	m_carousel->ScrollPrevious();

	if (m_carousel->GetSelectedIndex() != previousIndex && m_eventHandler) {
		m_eventHandler->OnWidgetValueChanged(this);
	}

	m_scrollPending = m_carousel->GetAnimFlags() & 1;
}

// FUNCTION: LEGORACERS 0x004679b0
void MenuSelector::StepNext()
{
	if (m_scrollPending) {
		return;
	}

	LegoU32 previousIndex = m_carousel->GetSelectedIndex();
	m_carousel->ScrollNext();

	if (m_carousel->GetSelectedIndex() != previousIndex && m_eventHandler) {
		m_eventHandler->OnWidgetValueChanged(this);
	}

	m_scrollPending = m_carousel->GetAnimFlags() & 1;
}

// FUNCTION: LEGORACERS 0x00467a00
undefined4 MenuSelector::OnEvent(undefined4)
{
	LegoU32 index = m_stateFlags & c_flagSelected;

	if (m_scrollPending && !(m_carousel->GetAnimFlags() & 1) && m_eventHandler) {
		m_eventHandler->OnSelectorSettled(this);
		m_scrollPending = 0;
	}

	m_carousel->SetItemColors(&GetStyleEntry()->m_itemColors[index], &GetStyleEntry()->m_itemColors[index + 1]);
	m_carousel->SetFocusedItemColors(&GetStyleEntry()->m_itemColors[index], &GetStyleEntry()->m_itemColors[index + 1]);

	if (m_prevButton.GetStateFlags() & c_flagFocused) {
		StepPrevious();
	}
	else if (m_nextButton.GetStateFlags() & c_flagFocused) {
		StepNext();
	}
	else {
		MenuCarousel* carousel = m_carousel;
		MenuStyleTable::SelectorStyle* styleEntry = GetStyleEntry();
		carousel->SetFocusedItemColors(
			&styleEntry->m_focusedItemColors[index],
			&styleEntry->m_focusedItemColors[index + 1]
		);
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00467ae0
undefined4 MenuSelector::TranslateNavigationEvent(undefined4 p_event)
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
MenuWidget* MenuSelector::OnKeyDown(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	LegoU8 stateFlags = m_stateFlags;
	LegoU32 keyCode = p_param1->m_keyCode;

	if ((stateFlags & c_flagEnabled) && (!m_activeKeyCode || m_activeKeyCode == keyCode) &&
		((stateFlags & c_flagFocused) || !p_param1->m_isRepeat)) {

		undefined4 mappedEvent = MapCursorToNavigation(keyCode, p_x, p_y);
		undefined4 result = TranslateNavigationEvent(mappedEvent);

		stateFlags = m_stateFlags;
		if ((stateFlags & c_flagEnabled) && ((stateFlags & c_flagSelected) || m_acceptUnfocusedInput) &&
			HandleNavigationKeyDown(p_param1, result)) {
			m_activeKeyCode = p_param1->m_keyCode;
			return this;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00467be0
MenuWidget* MenuSelector::OnKeyUp(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	LegoU32 keyCode = p_param1->m_keyCode;

	if (m_activeKeyCode != keyCode) {
		return NULL;
	}

	undefined4 mappedEvent = MapCursorToNavigation(keyCode, p_x, p_y);
	undefined4 result = TranslateNavigationEvent(mappedEvent);

	LegoU8 stateFlags = m_stateFlags;
	m_activeKeyCode = 0;

	if ((stateFlags & c_flagEnabled) && (stateFlags & c_flagFocused) &&
		((stateFlags & c_flagSelected) || m_acceptUnfocusedInput)) {
		HandleNavigationKeyUp(p_param1, result);
	}

	Unfocus(0);
	return this;
}
