#include "menu/widgets/menuicon.h"

#include "audio/soundgroupbinding.h"
#include "input/inputdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuIcon, 0x1a8)
DECOMP_SIZE_ASSERT(MenuIcon::SoundIdPair, 0x04)
DECOMP_SIZE_ASSERT(MenuIcon::CreateParams, 0x84)
DECOMP_SIZE_ASSERT(MenuIcon::CreateState, 0x90)

// FUNCTION: LEGORACERS 0x004664f0
LegoBool32 MenuIcon::IsEnabled()
{
	if (m_flags & 2) {
		LegoBool32 result = TRUE;
		if (result & m_stateFlags) {
			return result;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x004676c0
#pragma code_seg(".text$obscureicon_vt38")
MenuWidget* MenuIcon::DrawSelf(Rect*, Rect*)
{
	return NULL;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x00471c30
MenuIcon::MenuIcon()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00471ca0
MenuIcon::~MenuIcon()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00471cf0
void MenuIcon::Reset()
{
	m_soundGroupBinding = NULL;
	m_eventHandler = NULL;
	m_selectedChild = NULL;
	m_stateFlags = 0;
	m_visualStateIndex = c_stateDisabled;
	m_attached = FALSE;
	m_lastChild = NULL;
	m_firstChild = NULL;
	m_nextSibling = NULL;
	m_prevSibling = NULL;
	m_parent = NULL;
	m_transitionRemainingMs = 0;
	m_unk0x1a4 = 0;
	m_activeKeyCode = 0;
	m_helpStringId = 0;

	::memset(m_unk0x158, 0, sizeof(m_unk0x158));
	::memset(m_stateColors, 0xff, sizeof(m_stateColors));
	::memset(m_soundIds, 0, sizeof(m_soundIds));
	::memset(m_stateRects, 0, sizeof(m_stateRects));

	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x00471d90
void MenuIcon::InitializeFromParams(CreateParams* p_createParams, const CreateState* p_createState)
{
	const VisualStateColor* defaultRects = p_createParams->m_iconStateColors;
	if (!p_createParams->m_hasStateColors) {
		defaultRects = p_createState->m_iconStateColors;
	}

	::memcpy(m_stateColors, defaultRects, sizeof(m_stateColors));
	::memcpy(
		m_soundIds,
		p_createParams->m_hasSoundIds ? p_createParams->m_soundIds : p_createState->m_iconSoundIds,
		sizeof(m_soundIds)
	);
	::memcpy(m_stateRects, p_createState->m_stateRects, sizeof(m_stateRects));

	m_eventHandler = p_createParams->m_iconEventHandler;
	m_soundGroupBinding = p_createParams->m_soundGroupBinding;
	m_helpStringId = p_createParams->m_helpStringId;
	m_transitionDurationMs = p_createState->m_transitionDurationMs;
	SetIconEventHandler(p_createParams->m_iconEventHandler);
}

// FUNCTION: LEGORACERS 0x00471e30
LegoBool32 MenuIcon::Create(CreateParams* p_createParams, const CreateState* p_createState)
{
	Destroy();
	InitializeFromParams(p_createParams, p_createState);

	if (CreateWidget(p_createParams)) {
		if (p_createParams->m_attachToParent && p_createParams->m_parent && (m_flags & 4)) {
			AttachToParent(p_createParams->m_parent);
		}

		if (p_createParams->m_startEnabled) {
			Enable(0);
		}

		RefreshVisualState();
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00471ea0
LegoBool32 MenuIcon::Destroy()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		DetachFromParent();
		result = MenuWidget::Destroy();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00471ec0
void MenuIcon::AttachToParent(MenuIcon* p_parent)
{
	DetachFromParent();
	m_parent = p_parent;

	if (m_parent) {
		if (!m_parent->m_lastChild) {
			m_parent->m_firstChild = this;
			m_parent->m_lastChild = this;
			return;
		}

		m_prevSibling = m_parent->m_lastChild;
		m_prevSibling->m_nextSibling = this;
		m_parent->m_lastChild = this;
	}

	m_attached = TRUE;
}

// FUNCTION: LEGORACERS 0x00471f00
void MenuIcon::DetachFromParent()
{
	if (!(m_flags & 4)) {
		return;
	}

	if (m_prevSibling) {
		m_prevSibling->m_nextSibling = m_nextSibling;
	}
	else if (m_parent) {
		m_parent->m_firstChild = m_nextSibling;
	}

	if (m_nextSibling) {
		m_nextSibling->m_prevSibling = m_prevSibling;
		m_nextSibling = NULL;
		m_prevSibling = NULL;
		m_parent = NULL;
		m_attached = FALSE;
		return;
	}

	if (m_parent) {
		m_parent->m_lastChild = m_prevSibling;
	}

	m_nextSibling = NULL;
	m_prevSibling = NULL;
	m_parent = NULL;
	m_attached = FALSE;
}

// FUNCTION: LEGORACERS 0x00471f70
MenuIcon* MenuIcon::FindRoot()
{
	MenuIcon* result = this;

	while (result->m_parent) {
		result = result->m_parent;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00471f90
MenuIcon* MenuIcon::FindSelectedLeaf()
{
	MenuIcon* result = FindRoot();
	MenuIcon* child = result->m_selectedChild;

	if (!child) {
		return NULL;
	}

	do {
		result = child;
	} while ((child = result->m_selectedChild));

	return result;
}

// FUNCTION: LEGORACERS 0x00471fb0
void MenuIcon::SetSelected(undefined4 p_flags)
{
	MenuIcon* icon = this;
	LegoU8 skipParentLink;

	if (icon) {
		skipParentLink = (LegoU8) p_flags & 2;

		for (; icon; icon = icon->m_parent) {
			icon->m_stateFlags |= c_flagSelected;
			RefreshVisualState();

			MenuScreenInterface* eventHandler = icon->m_eventHandler;
			if (eventHandler) {
				if (!(p_flags & 1)) {
					eventHandler->OnIconSelected(this);
				}
			}

			if (skipParentLink) {
				break;
			}

			if (icon->m_parent) {
				icon->m_parent->m_selectedChild = icon;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00472010
void MenuIcon::ClearSelected(undefined4 p_flags)
{
	MenuIcon* icon = this;

	if (icon) {
		LegoU8 skipParentLink = (LegoU8) p_flags & 2;

		for (; icon; icon = icon->m_parent) {
			icon->m_stateFlags &= ~c_flagSelected;
			RefreshVisualState();

			MenuScreenInterface* eventHandler = icon->m_eventHandler;
			if (eventHandler) {
				if (!(p_flags & 1)) {
					eventHandler->OnIconDeselected(this);
				}
			}

			if (skipParentLink) {
				break;
			}

			if (icon->m_parent) {
				icon->m_parent->m_selectedChild = NULL;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00472080
void MenuIcon::RefreshVisualState()
{
	LegoU8 flags = m_stateFlags;
	LegoU32 oldState = m_visualStateIndex;

	if (flags & c_flagEnabled) {
		if (flags & c_flagSelected) {
			m_visualStateIndex = c_stateFocused;
		}
		else {
			m_visualStateIndex = c_stateNormal;
		}
	}
	else {
		m_visualStateIndex = c_stateDisabled;
	}

	if (flags & c_flagFocused) {
		m_visualStateIndex++;
	}

	if (oldState != m_visualStateIndex) {
		BeginRectTransition();
	}

	SetColor(&m_stateColors[m_visualStateIndex]);
}

// FUNCTION: LEGORACERS 0x004720f0
void MenuIcon::Enable(undefined4 p_flags)
{
	if (!(m_stateFlags & c_flagEnabled)) {
		m_stateFlags |= c_flagEnabled;
		RefreshVisualState();

		if (m_eventHandler && !(p_flags & 1)) {
			m_eventHandler->OnIconEnabled(this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472130
void MenuIcon::Disable(undefined4 p_flags)
{
	if (m_stateFlags & c_flagEnabled) {
		LegoU8 flags = (LegoU8) p_flags;

		if (m_stateFlags & c_flagSelected) {
			MenuIcon* root = FindRoot();
			if (!root->SelectNext() && !root->SelectFirst()) {
				Deselect(0);
			}
		}

		m_stateFlags &= ~c_flagEnabled;
		RefreshVisualState();

		if (m_eventHandler && !flags) {
			m_eventHandler->OnIconDisabled(this);
		}
	}
}

// FUNCTION: LEGORACERS 0x004721a0
void MenuIcon::Select(undefined4 p_flags)
{
	if (m_stateFlags & c_flagEnabled) {
		if ((m_stateFlags & c_flagSelected) && !m_selectedChild) {
			return;
		}

		if (!(p_flags & 2)) {
			MenuIcon* icon = FindSelectedLeaf();
			if (icon) {
				icon->Deselect(0);
			}
		}

		SetSelected(p_flags);

		if (!(p_flags & 4)) {
			m_soundGroupBinding->PlaySoundByIndex(m_soundIds[0]);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472200
void MenuIcon::Deselect(undefined4 p_flags)
{
	if ((m_stateFlags & c_flagEnabled) && (m_stateFlags & c_flagSelected)) {
		if (m_stateFlags & c_flagFocused) {
			Unfocus(1);
		}

		if (m_parent && !(p_flags & 2)) {
			MenuIcon* icon = FindSelectedLeaf();
			if (!icon) {
				return;
			}

			icon->ClearSelected(p_flags);

			if (!(p_flags & 4)) {
				icon->m_soundGroupBinding->PlaySoundByIndex(icon->m_soundIds[1]);
			}

			return;
		}

		ClearSelected(p_flags);

		if (!(p_flags & 4)) {
			m_soundGroupBinding->PlaySoundByIndex(m_soundIds[1]);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472290
void MenuIcon::Focus(undefined4 p_flags)
{
	if (m_stateFlags & c_flagFocused) {
		return;
	}

	LegoU8 flags = (LegoU8) p_flags;

	if (m_parent && !(flags & 2)) {
		m_parent->Focus(0);
	}

	SetFocus();
	m_stateFlags |= c_flagFocused;
	RefreshVisualState();

	if (m_eventHandler && !flags) {
		m_eventHandler->OnIconFocused(this);
	}

	if (!(flags & 4)) {
		m_soundGroupBinding->PlaySoundByIndex(m_soundIds[2]);
	}
}

// FUNCTION: LEGORACERS 0x00472310
void MenuIcon::Unfocus(undefined4 p_flags)
{
	LegoU8 stateFlags = m_stateFlags;
	m_activeKeyCode = 0;

	if (stateFlags & c_flagFocused) {
		if (m_flags & 8) {
			ClearFocus();
		}

		LegoU8 flags = (LegoU8) p_flags;

		if (m_parent && !(flags & 2)) {
			m_parent->Unfocus(0);
		}

		m_stateFlags &= ~c_flagFocused;
		RefreshVisualState();

		if (m_eventHandler && !flags) {
			m_eventHandler->OnIconUnfocused(this);
		}

		if (!(flags & 4)) {
			m_soundGroupBinding->PlaySoundByIndex(m_soundIds[3]);
		}
	}
}

// FUNCTION: LEGORACERS 0x004723a0
MenuIcon* MenuIcon::SelectFirst()
{
	if (IsEnabled()) {
		MenuIcon* child = m_firstChild;

		while (child) {
			MenuIcon* result = child->SelectFirst();
			if (result) {
				result->Select(0);
				return result;
			}

			child = child->m_nextSibling;
		}

		Select(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004723f0
MenuIcon* MenuIcon::SelectLast()
{
	if (IsEnabled()) {
		MenuIcon* child = m_lastChild;

		while (child) {
			MenuIcon* result = child->SelectFirst();
			if (result) {
				result->Select(0);
				return result;
			}

			child = child->m_prevSibling;
		}

		Select(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00472440
MenuIcon* MenuIcon::SelectNext()
{
	if (m_stateFlags & c_flagSelected) {
		MenuIcon* child = m_selectedChild;

		while (child) {
			MenuIcon* result = child->SelectNext();
			if (result) {
				result->Select(0);
				return result;
			}

			child = child->m_nextSibling;
		}

		Deselect(0);
		return NULL;
	}

	if (IsEnabled()) {
		MenuIcon* child = m_firstChild;

		while (child) {
			MenuIcon* result = child->SelectNext();
			if (result) {
				result->Select(0);
				return result;
			}

			child = child->m_nextSibling;
		}

		Select(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004724c0
MenuIcon* MenuIcon::SelectPrevious()
{
	if (m_stateFlags & c_flagSelected) {
		MenuIcon* child = m_selectedChild;

		while (child) {
			MenuIcon* result = child->SelectPrevious();
			if (result) {
				result->Select(0);
				return result;
			}

			child = child->m_prevSibling;
		}

		Deselect(0);
		return NULL;
	}

	if (IsEnabled()) {
		MenuIcon* child = m_lastChild;

		while (child) {
			MenuIcon* result = child->SelectPrevious();
			if (result) {
				result->Select(0);
				return result;
			}

			child = child->m_prevSibling;
		}

		Select(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00472540
void MenuIcon::BeginRectTransition()
{
	LegoS32 count = m_transitionDurationMs;
	m_transitionRemainingMs = count;
	LegoFloat countFloat = (LegoFloat) count;

	if (count) {
		m_rectDeltaTop = (LegoFloat) (m_stateTargetRects[m_visualStateIndex].m_top - m_rect.m_top) / countFloat;
		m_rectTopF = (LegoFloat) m_rect.m_top;
		m_rectDeltaBottom =
			(LegoFloat) (m_stateTargetRects[m_visualStateIndex].m_bottom - m_rect.m_bottom) / countFloat;
		m_rectBottomF = (LegoFloat) m_rect.m_bottom;
		m_rectDeltaLeft = (LegoFloat) (m_stateTargetRects[m_visualStateIndex].m_left - m_rect.m_left) / countFloat;
		m_rectLeftF = (LegoFloat) m_rect.m_left;
		m_rectDeltaRight = (LegoFloat) (m_stateTargetRects[m_visualStateIndex].m_right - m_rect.m_right) / countFloat;
		m_rectRightF = (LegoFloat) m_rect.m_right;

		if (m_rectDeltaTop != 0.0f || m_rectDeltaBottom != 0.0f || m_rectDeltaLeft != 0.0f ||
			m_rectDeltaRight != 0.0f) {
			m_animFlags |= 1;
		}
	}
}

// FUNCTION: LEGORACERS 0x00472680
undefined4 MenuIcon::OnEvent(undefined4 p_elapsedMs)
{
	if (!(m_animFlags & 1)) {
		return 0;
	}

	if (!m_transitionRemainingMs) {
		m_animFlags &= ~1;

		m_rect = m_stateTargetRects[m_visualStateIndex];
		m_rectDeltaTop = 0.0f;
		return 0;
	}

	if ((undefined4) m_transitionRemainingMs < p_elapsedMs) {
		p_elapsedMs = m_transitionRemainingMs;
	}

	LegoFloat elapsedFloat = (LegoFloat) (LegoS32) p_elapsedMs;
	m_transitionRemainingMs -= p_elapsedMs;
	LegoFloat delta = m_rectDeltaTop;
	m_rectTopF += delta * elapsedFloat;
	delta = m_rectDeltaBottom;
	m_rectBottomF += delta * elapsedFloat;
	delta = m_rectDeltaLeft;
	m_rectLeftF += delta * elapsedFloat;
	delta = m_rectDeltaRight;
	m_rectRightF += delta * elapsedFloat;
	m_rect.m_top = (LegoS32) m_rectTopF;
	m_rect.m_bottom = (LegoS32) m_rectBottomF;
	m_rect.m_left = (LegoS32) m_rectLeftF;
	m_rect.m_right = (LegoS32) m_rectRightF;

	return 0;
}

// FUNCTION: LEGORACERS 0x00472790
MenuWidget* MenuIcon::OnCursorEvent(void* p_item, undefined4 p_x, undefined4 p_y)
{
	LegoU8 flag = 8;

	if (!m_parent) {
		if (!(flag & m_flags)) {
			return NULL;
		}
	}

	if (flag & m_flags) {
		if (m_notifyHandler) {
			m_notifyHandler->OnWidgetKeyDown(this, p_item, p_x, p_y);
		}

		return this;
	}

	if (!IsEnabled()) {
		return NULL;
	}

	Select(0);

	if (m_selectedChild || m_firstChild) {
		return NULL;
	}

	if (m_notifyHandler) {
		m_notifyHandler->OnWidgetKeyUp(this, p_item, p_x, p_y);
	}

	return this;
}

// FUNCTION: LEGORACERS 0x00472820
MenuWidget* MenuIcon::OnKeyDown(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	LegoU32 keyCode = p_item->m_keyCode;
	LegoU32 eventType = keyCode & InputDevice::c_sourceMask;
	LegoU8 stateFlags = m_stateFlags;
	LegoBool32 activate = FALSE;

	if (stateFlags & c_flagEnabled) {
		if (!m_activeKeyCode || m_activeKeyCode == keyCode) {
			if ((stateFlags & c_flagFocused) || !p_item->m_isRepeat) {
				if (keyCode == m_unk0x1a4) {
					activate = TRUE;
				}
				else if (stateFlags & c_flagSelected) {
					switch (eventType) {
					case InputDevice::c_sourceKeyboard:
						if (keyCode == (InputDevice::c_sourceKeyboard | 0x1c) ||
							keyCode == (InputDevice::c_sourceKeyboard | 0x39)) {
							activate = TRUE;
						}
						break;
					case InputDevice::c_sourceMouse:
						if (HitTest(p_x, p_y)) {
							activate = TRUE;
						}
						break;
					case InputDevice::c_sourceJoystickButton:
						if (keyCode == (InputDevice::c_sourceJoystickButton | 0x4)) {
							activate = TRUE;
						}
						break;
					}
				}
			}
		}
	}

	if (activate && !(m_stateFlags & c_flagFocused)) {
		Focus(0);
		m_activeKeyCode = keyCode;
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004728e0
MenuWidget* MenuIcon::OnKeyUp(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	LegoU32 keyCode = p_item->m_keyCode;
	LegoU32 eventType = keyCode;
	eventType &= InputDevice::c_sourceMask;
	LegoU32 activeKey = m_activeKeyCode;

	if (keyCode != activeKey) {
		return NULL;
	}

	if (eventType == InputDevice::c_sourceMouse) {
		m_activeKeyCode = 0;

		if (!HitTest(p_x, p_y) && (m_stateFlags & c_flagFocused)) {
			Unfocus(1);
			return this;
		}
	}
	else {
		m_activeKeyCode = 0;
	}

	Unfocus(0);
	return this;
}

// FUNCTION: LEGORACERS 0x00472950
void MenuIcon::SetRect(Rect* p_rect)
{
	MenuWidget::SetRect(p_rect);

	for (LegoS32 i = 0; i < sizeOfArray(m_stateRects); i++) {
		m_stateTargetRects[i].m_top = m_stateRects[i].m_top + p_rect->m_top;
		m_stateTargetRects[i].m_bottom = m_stateRects[i].m_bottom + p_rect->m_bottom;
		m_stateTargetRects[i].m_left = m_stateRects[i].m_left + p_rect->m_left;
		m_stateTargetRects[i].m_right = m_stateRects[i].m_right + p_rect->m_right;
	}
}

// FUNCTION: LEGORACERS 0x004729a0
void MenuIcon::SetIconEventHandler(MenuScreenInterface* p_eventHandler)
{
	m_eventHandler = p_eventHandler;
}
