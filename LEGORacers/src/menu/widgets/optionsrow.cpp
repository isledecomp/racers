#include "menu/widgets/optionsrow.h"

#include "audio/soundgroupbinding.h"
#include "input/inputdevice.h"

DECOMP_SIZE_ASSERT(OptionsRowBase, 0x6e4)
DECOMP_SIZE_ASSERT(OptionsRow, 0x6ec)

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 OptionsRowBase::OnEvent(undefined4)
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
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046df60
void OptionsRowBase::Reset()
{
	m_value = 0;
	m_trackMaxX = 0;
	m_trackMinX = 0;
	m_stepWidth = 0.0f;
	m_styleEntry = NULL;
	m_track.Destroy();
	m_thumb.Destroy();
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x0046dfb0
LegoBool32 OptionsRowBase::Create(
	MenuInputBindingTable::CompositeBinding* p_createParams,
	MenuStyleTable::CompositeStyle* p_styleEntry
)
{
	Destroy();

	m_styleEntry = p_styleEntry;
	m_value = p_createParams->m_initialValue;
	m_stepCount = p_createParams->m_stepCount;

	MenuIcon::SoundIdPair* soundIds = &p_createParams->m_stepSoundIds;
	if (!p_createParams->m_hasSoundIds) {
		soundIds = &p_styleEntry->m_stepSoundIds;
	}

	m_soundIds = *soundIds;

	if (CreateDefault(p_createParams, p_styleEntry)) {
		p_createParams->m_trackParams->m_parent = this;
		p_createParams->m_thumbParams->m_parent = this;

		if (m_track.Create(p_createParams->m_trackParams) && m_thumb.Create(p_createParams->m_thumbParams)) {
			LayoutButtons();
			LayoutTrack();
			LayoutThumb();
			SetColor(&m_visualState);
			return TRUE;
		}
	}

	Destroy();
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046e090
void OptionsRowBase::SetColor(VisualStateColor* p_visualState)
{
	m_track.SetColor(p_visualState);
	m_thumb.SetColor(p_visualState);
	MenuWidget::SetColor(p_visualState);
}

// FUNCTION: LEGORACERS 0x0046e0d0
void OptionsRowBase::StepPrevious()
{
	if (m_value) {
		SetValue(m_value - 1);
		if (m_eventHandler) {
			m_eventHandler->OnWidgetValueChanged(this);
		}

		m_soundGroupBinding->PlaySoundByIndex(m_soundIds.m_first);
		return;
	}

	m_soundGroupBinding->PlaySoundByIndex(m_soundIds.m_second);
}

// FUNCTION: LEGORACERS 0x0046e130
void OptionsRowBase::StepNext()
{
	if (m_value != m_stepCount - 1) {
		SetValue(m_value + 1);
		if (m_eventHandler) {
			m_eventHandler->OnWidgetValueChanged(this);
		}

		m_soundGroupBinding->PlaySoundByIndex(m_soundIds.m_first);
		return;
	}

	m_soundGroupBinding->PlaySoundByIndex(m_soundIds.m_second);
}

// FUNCTION: LEGORACERS 0x0046e190
undefined4 OptionsRowBase::TranslateNavigationEvent(undefined4 p_event)
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
MenuWidget* OptionsRowBase::OnKeyDown(InputEventQueue::Event* p_event, undefined4 p_x, undefined4 p_y)
{
	LegoU8 stateFlags = m_stateFlags;
	LegoU32 keyCode = p_event->m_keyCode;

	if ((stateFlags & c_flagEnabled) && (!m_activeKeyCode || m_activeKeyCode == keyCode) &&
		((stateFlags & c_flagFocused) || !p_event->m_isRepeat)) {
		undefined4 mappedEvent = MapCursorToNavigation(keyCode, p_x, p_y);
		undefined4 result = TranslateNavigationEvent(mappedEvent);

		stateFlags = m_stateFlags;
		if ((stateFlags & c_flagEnabled) && (stateFlags & c_flagSelected)) {
			if ((result & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
				undefined4 x = p_x;
				undefined4 y = p_y;
				m_thumb.ScreenToLocal(x, y);

				if (m_thumb.HitTest(x, y)) {
					m_activeKeyCode = p_event->m_keyCode;
					m_soundGroupBinding->PlaySoundByIndex(m_soundIds.m_first);
					SetFocus();
					Focus(0);
					return this;
				}
			}

			if (HandleNavigationKeyDown(p_event, result)) {
				m_activeKeyCode = p_event->m_keyCode;
				return this;
			}
		}

		m_activeKeyCode = 0;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0046e340
MenuWidget* OptionsRowBase::OnKeyUp(InputEventQueue::Event* p_event, undefined4 p_x, undefined4 p_y)
{
	LegoU32 keyCode = p_event->m_keyCode;

	if (m_activeKeyCode != keyCode) {
		return NULL;
	}

	undefined4 mappedEvent = MapCursorToNavigation(keyCode, p_x, p_y);
	undefined4 result = TranslateNavigationEvent(mappedEvent);

	LegoU8 stateFlags = m_stateFlags;
	m_activeKeyCode = 0;

	if ((stateFlags & c_flagEnabled) && (stateFlags & c_flagFocused) && (stateFlags & c_flagSelected) &&
		HandleNavigationKeyUp(p_event, result)) {
		return this;
	}

	if ((result & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		m_soundGroupBinding->PlaySoundByIndex(m_soundIds.m_first);
		SnapThumbToValue();
		ClearFocus();
	}

	Unfocus(0);
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
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046e4b0
void OptionsRow::ComputeThumbRange()
{
	m_trackMinX = m_prevButton.GetRect()->m_right + ((m_thumb.GetRect()->m_right - m_thumb.GetRect()->m_left) >> 1);
	m_trackMaxX = m_nextButton.GetRect()->m_left - ((m_thumb.GetRect()->m_right - m_thumb.GetRect()->m_left) >> 1);
	m_stepWidth = static_cast<LegoFloat>(m_trackMaxX - m_trackMinX);

	if (m_stepCount > 2) {
		m_stepWidth = m_stepWidth / static_cast<LegoFloat>(m_stepCount - 1);
	}
}

// FUNCTION: LEGORACERS 0x0046e530
void OptionsRow::LayoutButtons()
{
	Rect rect;
	rect.m_top = 0;
	rect.m_left = 0;
	rect.m_bottom = m_rect.m_bottom - m_rect.m_top;
	rect.m_right = m_prevButton.GetRect()->m_right - m_prevButton.GetRect()->m_left;
	m_prevButton.SetRect(&rect);

	rect.m_right = m_rect.m_right - m_rect.m_left;
	rect.m_left = rect.m_right + (m_nextButton.GetRect()->m_left - m_nextButton.GetRect()->m_right);
	m_nextButton.SetRect(&rect);
}

// FUNCTION: LEGORACERS 0x0046e5b0
void OptionsRow::LayoutTrack()
{
	Rect rect;
	rect.m_left = m_prevButton.GetRect()->m_right + 1;
	rect.m_right = m_nextButton.GetRect()->m_left - 1;

	LegoS32 height = m_track.GetRect()->m_bottom - m_track.GetRect()->m_top;
	rect.m_top = ((m_rect.m_bottom - m_rect.m_top) >> 1) - (height >> 1);
	rect.m_bottom = rect.m_top + height;

	m_track.SetRect(&rect);
	m_trackRect = *m_track.GetGlobalRect();
}

// FUNCTION: LEGORACERS 0x0046e630
void OptionsRow::LayoutThumb()
{
	Rect rect;
	rect.m_left = m_prevButton.GetRect()->m_right;
	rect.m_right = m_thumb.GetRect()->m_right + rect.m_left;

	LegoS32 height = m_thumb.GetRect()->m_bottom - m_thumb.GetRect()->m_top;
	rect.m_top = ((m_rect.m_bottom - m_rect.m_top) >> 1) - (height >> 1);
	rect.m_bottom = rect.m_top + height;

	m_thumb.SetRect(&rect);
	ComputeThumbRange();
	SetValue(m_value);
}

// FUNCTION: LEGORACERS 0x0046e6b0
void OptionsRow::SnapThumbToValue()
{
	LegoS32 index = static_cast<LegoS32>(
		(static_cast<LegoFloat>(m_thumb.GetRect()->m_left - m_prevButton.GetRect()->m_right) / m_stepWidth) + 0.5f
	);

	SetValue(index);
}

// FUNCTION: LEGORACERS 0x0046e6f0
void OptionsRow::SetValue(LegoS32 p_value)
{
	if (p_value != m_value) {
		double step = m_stepWidth;
		double index = p_value;
		Rect rect = *m_thumb.GetRect();
		LegoS32 width = rect.m_right - rect.m_left;
		rect.m_left = m_trackMinX + static_cast<LegoS32>(step * index) - (width >> 1);
		rect.m_right = width + rect.m_left;
		m_thumb.SetRect(&rect);

		m_value = p_value;
		if (m_eventHandler) {
			m_eventHandler->OnWidgetValueChanged(this);
		}
	}
}

// FUNCTION: LEGORACERS 0x0046e780
undefined4 OptionsRow::MapCursorToNavigation(undefined4 p_event, undefined4 p_x, undefined4 p_y)
{
	if ((p_event & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse) {
		undefined4 x = p_x;
		undefined4 y = p_y;
		m_thumb.ScreenToLocal(x, y);

		if (!(m_stateFlags & c_flagFocused) && m_thumb.HitTest(x, y)) {
			return p_event;
		}

		return MenuSelectorBase::MapCursorToNavigation(p_event, p_x, p_y);
	}

	return p_event;
}

// STUB: LEGORACERS 0x0046e810
MenuWidget* OptionsRow::OnCursorEvent(void* p_item, undefined4 p_x, undefined4 p_y)
{
	MenuIcon::OnCursorEvent(p_item, p_x, p_y);

	if (!(m_flags & 8)) {
		return NULL;
	}

	if (!(m_prevButton.GetStateFlags() & c_flagFocused) && !(m_nextButton.GetStateFlags() & c_flagFocused)) {
		MenuInputDispatcher::Cursor* cursor = static_cast<MenuInputDispatcher::Cursor*>(p_item);
		cursor->m_bounds = m_trackRect;

		Rect rect = *m_thumb.GetRect();
		LegoS32 width = rect.m_right;
		width -= rect.m_left;
		rect.m_left += p_x;
		rect.m_right += p_x;

		if (rect.m_left < m_prevButton.GetRect()->m_right) {
			rect.m_left = m_prevButton.GetRect()->m_right;
			rect.m_right = rect.m_left + width;
		}
		else if (rect.m_right > m_nextButton.GetRect()->m_left) {
			rect.m_right = m_nextButton.GetRect()->m_left;
			rect.m_left = rect.m_right - width;
		}

		m_thumb.SetRect(&rect);
	}

	return this;
}
