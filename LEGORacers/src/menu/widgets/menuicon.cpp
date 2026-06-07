#include "menu/widgets/menuicon.h"

#include "audio/soundgroupbinding.h"
#include "input/inputdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuIcon, 0x1a8)
DECOMP_SIZE_ASSERT(MenuIcon::SoundIdPair, 0x04)
DECOMP_SIZE_ASSERT(MenuIcon::CreateParams, 0x84)
DECOMP_SIZE_ASSERT(MenuIcon::CreateState, 0x90)

// FUNCTION: LEGORACERS 0x004664f0
LegoBool32 MenuIcon::VTable0x5c()
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
MenuWidget* MenuIcon::VTable0x38(Rect*, Rect*)
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
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00471cf0
void MenuIcon::Reset()
{
	m_soundGroupBinding = NULL;
	m_eventHandler = NULL;
	m_activeChild = NULL;
	m_stateFlags = 0;
	m_visualStateIndex = c_stateDisabled;
	m_unk0x12d = FALSE;
	m_lastChild = NULL;
	m_firstChild = NULL;
	m_nextSibling = NULL;
	m_prevSibling = NULL;
	m_parent = NULL;
	m_transitionRemainingMs = 0;
	m_unk0x1a4 = 0;
	m_activeKeyCode = 0;
	m_unk0x168 = 0;

	::memset(m_unk0x158, 0, sizeof(m_unk0x158));
	::memset(m_unk0x174, 0xff, sizeof(m_unk0x174));
	::memset(m_soundIds, 0, sizeof(m_soundIds));
	::memset(m_unk0x6c, 0, sizeof(m_unk0x6c));

	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x00471d90
void MenuIcon::FUN_00471d90(CreateParams* p_createParams, const CreateState* p_createState)
{
	const VisualStateColor* defaultRects = p_createParams->m_unk0x52;
	if (!p_createParams->m_unk0x78) {
		defaultRects = p_createState->m_unk0x00;
	}

	::memcpy(m_unk0x174, defaultRects, sizeof(m_unk0x174));
	::memcpy(
		m_soundIds,
		p_createParams->m_unk0x7c ? p_createParams->m_soundIds : p_createState->m_unk0x18,
		sizeof(m_soundIds)
	);
	::memcpy(m_unk0x6c, p_createState->m_unk0x24, sizeof(m_unk0x6c));

	m_eventHandler = p_createParams->m_unk0x80;
	m_soundGroupBinding = p_createParams->m_soundGroupBinding;
	m_unk0x168 = p_createParams->m_unk0x40;
	m_transitionDurationMs = p_createState->m_unk0x84;
	VTable0x40(p_createParams->m_unk0x80);
}

// FUNCTION: LEGORACERS 0x00471e30
LegoBool32 MenuIcon::FUN_00471e30(CreateParams* p_createParams, const CreateState* p_createState)
{
	VTable0x08();
	FUN_00471d90(p_createParams, p_createState);

	if (FUN_00472a60(p_createParams)) {
		if (p_createParams->m_unk0x74 && p_createParams->m_parent && (m_flags & 4)) {
			AttachToParent(p_createParams->m_parent);
		}

		if (p_createParams->m_unk0x38) {
			VTable0x44(0);
		}

		RefreshVisualState();
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00471ea0
LegoBool32 MenuIcon::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		DetachFromParent();
		result = MenuWidget::VTable0x08();
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

	m_unk0x12d = TRUE;
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
		m_unk0x12d = FALSE;
		return;
	}

	if (m_parent) {
		m_parent->m_lastChild = m_prevSibling;
	}

	m_nextSibling = NULL;
	m_prevSibling = NULL;
	m_parent = NULL;
	m_unk0x12d = FALSE;
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
MenuIcon* MenuIcon::FUN_00471f90()
{
	MenuIcon* result = FindRoot();
	MenuIcon* child = result->m_activeChild;

	if (!child) {
		return NULL;
	}

	do {
		result = child;
	} while ((child = result->m_activeChild));

	return result;
}

// FUNCTION: LEGORACERS 0x00471fb0
void MenuIcon::FUN_00471fb0(undefined4 p_flags)
{
	MenuIcon* icon = this;
	LegoU8 skipParentLink;

	if (icon) {
		skipParentLink = (LegoU8) p_flags & 2;

		for (; icon; icon = icon->m_parent) {
			icon->m_stateFlags |= c_flagBit1;
			RefreshVisualState();

			MenuScreenInterface* eventHandler = icon->m_eventHandler;
			if (eventHandler) {
				if (!(p_flags & 1)) {
					eventHandler->VTable0x3c(this);
				}
			}

			if (skipParentLink) {
				break;
			}

			if (icon->m_parent) {
				icon->m_parent->m_activeChild = icon;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00472010
void MenuIcon::FUN_00472010(undefined4 p_flags)
{
	MenuIcon* icon = this;

	if (icon) {
		LegoU8 skipParentLink = (LegoU8) p_flags & 2;

		for (; icon; icon = icon->m_parent) {
			icon->m_stateFlags &= ~c_flagBit1;
			RefreshVisualState();

			MenuScreenInterface* eventHandler = icon->m_eventHandler;
			if (eventHandler) {
				if (!(p_flags & 1)) {
					eventHandler->VTable0x40(this);
				}
			}

			if (skipParentLink) {
				break;
			}

			if (icon->m_parent) {
				icon->m_parent->m_activeChild = NULL;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00472080
void MenuIcon::RefreshVisualState()
{
	LegoU8 flags = m_stateFlags;
	LegoU32 oldState = m_visualStateIndex;

	if (flags & c_flagBit0) {
		if (flags & c_flagBit1) {
			m_visualStateIndex = c_stateFocused;
		}
		else {
			m_visualStateIndex = c_stateNormal;
		}
	}
	else {
		m_visualStateIndex = c_stateDisabled;
	}

	if (flags & c_flagBit2) {
		m_visualStateIndex++;
	}

	if (oldState != m_visualStateIndex) {
		BeginRectTransition();
	}

	VTable0x14(&m_unk0x174[m_visualStateIndex]);
}

// FUNCTION: LEGORACERS 0x004720f0
void MenuIcon::VTable0x44(undefined4 p_flags)
{
	if (!(m_stateFlags & c_flagBit0)) {
		m_stateFlags |= c_flagBit0;
		RefreshVisualState();

		if (m_eventHandler && !(p_flags & 1)) {
			m_eventHandler->VTable0x2c(this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472130
void MenuIcon::VTable0x48(undefined4 p_flags)
{
	if (m_stateFlags & c_flagBit0) {
		LegoU8 flags = (LegoU8) p_flags;

		if (m_stateFlags & c_flagBit1) {
			MenuIcon* root = FindRoot();
			if (!root->VTable0x60() && !root->VTable0x68()) {
				VTable0x50(0);
			}
		}

		m_stateFlags &= ~c_flagBit0;
		RefreshVisualState();

		if (m_eventHandler && !flags) {
			m_eventHandler->VTable0x30(this);
		}
	}
}

// FUNCTION: LEGORACERS 0x004721a0
void MenuIcon::VTable0x4c(undefined4 p_flags)
{
	if (m_stateFlags & c_flagBit0) {
		if ((m_stateFlags & c_flagBit1) && !m_activeChild) {
			return;
		}

		if (!(p_flags & 2)) {
			MenuIcon* icon = FUN_00471f90();
			if (icon) {
				icon->VTable0x50(0);
			}
		}

		FUN_00471fb0(p_flags);

		if (!(p_flags & 4)) {
			m_soundGroupBinding->FUN_0046e970(m_soundIds[0]);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472200
void MenuIcon::VTable0x50(undefined4 p_flags)
{
	if ((m_stateFlags & c_flagBit0) && (m_stateFlags & c_flagBit1)) {
		if (m_stateFlags & c_flagBit2) {
			VTable0x58(1);
		}

		if (m_parent && !(p_flags & 2)) {
			MenuIcon* icon = FUN_00471f90();
			if (!icon) {
				return;
			}

			icon->FUN_00472010(p_flags);

			if (!(p_flags & 4)) {
				icon->m_soundGroupBinding->FUN_0046e970(icon->m_soundIds[1]);
			}

			return;
		}

		FUN_00472010(p_flags);

		if (!(p_flags & 4)) {
			m_soundGroupBinding->FUN_0046e970(m_soundIds[1]);
		}
	}
}

// FUNCTION: LEGORACERS 0x00472290
void MenuIcon::VTable0x54(undefined4 p_flags)
{
	if (m_stateFlags & c_flagBit2) {
		return;
	}

	LegoU8 flags = (LegoU8) p_flags;

	if (m_parent && !(flags & 2)) {
		m_parent->VTable0x54(0);
	}

	SetFocus();
	m_stateFlags |= c_flagBit2;
	RefreshVisualState();

	if (m_eventHandler && !flags) {
		m_eventHandler->VTable0x34(this);
	}

	if (!(flags & 4)) {
		m_soundGroupBinding->FUN_0046e970(m_soundIds[2]);
	}
}

// FUNCTION: LEGORACERS 0x00472310
void MenuIcon::VTable0x58(undefined4 p_flags)
{
	LegoU8 stateFlags = m_stateFlags;
	m_activeKeyCode = 0;

	if (stateFlags & c_flagBit2) {
		if (m_flags & 8) {
			ClearFocus();
		}

		LegoU8 flags = (LegoU8) p_flags;

		if (m_parent && !(flags & 2)) {
			m_parent->VTable0x58(0);
		}

		m_stateFlags &= ~c_flagBit2;
		RefreshVisualState();

		if (m_eventHandler && !flags) {
			m_eventHandler->VTable0x38(this);
		}

		if (!(flags & 4)) {
			m_soundGroupBinding->FUN_0046e970(m_soundIds[3]);
		}
	}
}

// FUNCTION: LEGORACERS 0x004723a0
MenuIcon* MenuIcon::VTable0x68()
{
	if (VTable0x5c()) {
		MenuIcon* child = m_firstChild;

		while (child) {
			MenuIcon* result = child->VTable0x68();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_nextSibling;
		}

		VTable0x4c(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004723f0
MenuIcon* MenuIcon::VTable0x6c()
{
	if (VTable0x5c()) {
		MenuIcon* child = m_lastChild;

		while (child) {
			MenuIcon* result = child->VTable0x68();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_prevSibling;
		}

		VTable0x4c(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00472440
MenuIcon* MenuIcon::VTable0x60()
{
	if (m_stateFlags & c_flagBit1) {
		MenuIcon* child = m_activeChild;

		while (child) {
			MenuIcon* result = child->VTable0x60();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_nextSibling;
		}

		VTable0x50(0);
		return NULL;
	}

	if (VTable0x5c()) {
		MenuIcon* child = m_firstChild;

		while (child) {
			MenuIcon* result = child->VTable0x60();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_nextSibling;
		}

		VTable0x4c(0);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004724c0
MenuIcon* MenuIcon::VTable0x64()
{
	if (m_stateFlags & c_flagBit1) {
		MenuIcon* child = m_activeChild;

		while (child) {
			MenuIcon* result = child->VTable0x64();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_prevSibling;
		}

		VTable0x50(0);
		return NULL;
	}

	if (VTable0x5c()) {
		MenuIcon* child = m_lastChild;

		while (child) {
			MenuIcon* result = child->VTable0x64();
			if (result) {
				result->VTable0x4c(0);
				return result;
			}

			child = child->m_prevSibling;
		}

		VTable0x4c(0);
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
		m_rectDeltaTop = (LegoFloat) (m_unk0xcc[m_visualStateIndex].m_top - m_unk0x34.m_top) / countFloat;
		m_rectTopF = (LegoFloat) m_unk0x34.m_top;
		m_rectDeltaBottom = (LegoFloat) (m_unk0xcc[m_visualStateIndex].m_bottom - m_unk0x34.m_bottom) / countFloat;
		m_rectBottomF = (LegoFloat) m_unk0x34.m_bottom;
		m_rectDeltaLeft = (LegoFloat) (m_unk0xcc[m_visualStateIndex].m_left - m_unk0x34.m_left) / countFloat;
		m_rectLeftF = (LegoFloat) m_unk0x34.m_left;
		m_rectDeltaRight = (LegoFloat) (m_unk0xcc[m_visualStateIndex].m_right - m_unk0x34.m_right) / countFloat;
		m_rectRightF = (LegoFloat) m_unk0x34.m_right;

		if (m_rectDeltaTop != 0.0f || m_rectDeltaBottom != 0.0f || m_rectDeltaLeft != 0.0f ||
			m_rectDeltaRight != 0.0f) {
			m_unk0x54 |= 1;
		}
	}
}

// FUNCTION: LEGORACERS 0x00472680
undefined4 MenuIcon::VTable0x3c(undefined4 p_elapsedMs)
{
	if (!(m_unk0x54 & 1)) {
		return 0;
	}

	if (!m_transitionRemainingMs) {
		m_unk0x54 &= ~1;

		m_unk0x34 = m_unk0xcc[m_visualStateIndex];
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
	m_unk0x34.m_top = (LegoS32) m_rectTopF;
	m_unk0x34.m_bottom = (LegoS32) m_rectBottomF;
	m_unk0x34.m_left = (LegoS32) m_rectLeftF;
	m_unk0x34.m_right = (LegoS32) m_rectRightF;

	return 0;
}

// FUNCTION: LEGORACERS 0x00472790
MenuWidget* MenuIcon::VTable0x2c(void* p_item, undefined4 p_x, undefined4 p_y)
{
	LegoU8 flag = 8;

	if (!m_parent) {
		if (!(flag & m_flags)) {
			return NULL;
		}
	}

	if (flag & m_flags) {
		if (m_unk0x28) {
			m_unk0x28->VTable0x28(this, p_item, p_x, p_y);
		}

		return this;
	}

	if (!VTable0x5c()) {
		return NULL;
	}

	VTable0x4c(0);

	if (m_activeChild || m_firstChild) {
		return NULL;
	}

	if (m_unk0x28) {
		m_unk0x28->VTable0x14(this, p_item, p_x, p_y);
	}

	return this;
}

// FUNCTION: LEGORACERS 0x00472820
MenuWidget* MenuIcon::VTable0x30(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	LegoU32 keyCode = p_item->m_keyCode;
	LegoU32 eventType = keyCode & InputDevice::c_sourceMask;
	LegoU8 stateFlags = m_stateFlags;
	LegoBool32 activate = FALSE;

	if (stateFlags & c_flagBit0) {
		if (!m_activeKeyCode || m_activeKeyCode == keyCode) {
			if ((stateFlags & c_flagBit2) || !p_item->m_isRepeat) {
				if (keyCode == m_unk0x1a4) {
					activate = TRUE;
				}
				else if (stateFlags & c_flagBit1) {
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

	if (activate && !(m_stateFlags & c_flagBit2)) {
		VTable0x54(0);
		m_activeKeyCode = keyCode;
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004728e0
MenuWidget* MenuIcon::VTable0x34(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
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

		if (!HitTest(p_x, p_y) && (m_stateFlags & c_flagBit2)) {
			VTable0x58(1);
			return this;
		}
	}
	else {
		m_activeKeyCode = 0;
	}

	VTable0x58(0);
	return this;
}

// FUNCTION: LEGORACERS 0x00472950
void MenuIcon::VTable0x10(Rect* p_rect)
{
	MenuWidget::VTable0x10(p_rect);

	for (LegoS32 i = 0; i < sizeOfArray(m_unk0x6c); i++) {
		m_unk0xcc[i].m_top = m_unk0x6c[i].m_top + p_rect->m_top;
		m_unk0xcc[i].m_bottom = m_unk0x6c[i].m_bottom + p_rect->m_bottom;
		m_unk0xcc[i].m_left = m_unk0x6c[i].m_left + p_rect->m_left;
		m_unk0xcc[i].m_right = m_unk0x6c[i].m_right + p_rect->m_right;
	}
}

// FUNCTION: LEGORACERS 0x004729a0
void MenuIcon::VTable0x40(MenuScreenInterface* p_eventHandler)
{
	m_eventHandler = p_eventHandler;
}
