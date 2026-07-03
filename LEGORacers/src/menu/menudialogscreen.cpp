#include "menu/menudialog.h"
#include "menu/style/sharedmenustyletable.h"

DECOMP_SIZE_ASSERT(MenuDialog::DialogScreen, 0x74c)
DECOMP_SIZE_ASSERT(MenuDialog::DialogScreen::CreateParams, 0x18)

// GLOBAL: LEGORACERS 0x004b2160
extern const LegoFloat g_dialogAnimRate = 0.0033333334f;

// FUNCTION: LEGORACERS 0x00468140
MenuDialog::DialogScreen::DialogScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004681b0
MenuDialog::DialogScreen::~DialogScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00468220
void MenuDialog::DialogScreen::Reset()
{
	m_owner = NULL;
	m_menuStyles = NULL;
	m_eventHandler = NULL;
	m_yesIcon = NULL;
	m_noIcon = NULL;
	m_popupIcon = NULL;
	m_state = 0;
	m_result = 0;
	m_centerX = 0;
	m_centerY = 0;
	m_notifyId = 0;
	m_ageMs = 0;
	m_animMs = 0;
	m_halfWidth = 0.0f;
	m_halfHeight = 0.0f;
	m_closed = 0;
	m_defaultYes = 0;
	m_type = 1;
	m_frame.Destroy();
	m_messageLabel.Destroy();
	MenuScreen::Reset();
}

// FUNCTION: LEGORACERS 0x004682c0
void MenuDialog::DialogScreen::CreateWidgets()
{
	CreateFrame(&m_frame, 0x11f, 0x47);
	CreateTextLabel(&m_messageLabel, 0x120, 0x37, m_notifyId);
}

// FUNCTION: LEGORACERS 0x00468300
LegoBool32 MenuDialog::DialogScreen::Initialize(CreateParams* p_createParams)
{
	Destroy();

	m_owner = p_createParams->m_owner;
	m_menuStyles = p_createParams->m_createParams->m_menuStyles;
	m_eventHandler = p_createParams->m_eventHandler;
	p_createParams->m_createParams->m_dialog = NULL;
	m_type = p_createParams->m_type;
	m_notifyId = p_createParams->m_notifyId;
	m_defaultYes = p_createParams->m_defaultYes;
	m_closed = 0;

	if (!MenuScreen::Initialize(p_createParams->m_createParams)) {
		return FALSE;
	}

	m_result = 0;
	m_state = 1;

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00468390
void MenuDialog::DialogScreen::AttachPopupIcon()
{
	Rect rect;

	m_popupIcon->SetIconEventHandler(this);

	LegoS32 bottom = m_popupIcon->GetRect()->m_bottom + 0x14;
	m_halfHeight += bottom * 0.5f;

	rect.m_top = m_messageLabel.GetRect()->m_bottom + 0x14;
	LegoS32 rectBottom = m_popupIcon->GetRect()->m_bottom;
	rectBottom += rect.m_top;
	rect.m_left = 0x19;
	rect.m_bottom = rectBottom;
	rect.m_right = m_popupIcon->GetRect()->m_right + 0x19;

	m_popupIcon->SetRect(&rect);
	m_popupIcon->SetParent(&m_frame);
	m_popupIcon->AttachToParent(GetRootIcon());
	m_popupIcon->Select(5);
}

// FUNCTION: LEGORACERS 0x00468430
void MenuDialog::DialogScreen::AttachYesIcon()
{
	Rect rect;

	m_yesIcon->SetIconEventHandler(this);

	LegoS32 bottom = m_yesIcon->GetRect()->m_bottom + 0x14;
	m_halfHeight += bottom * 0.5f;

	rect.m_top = m_messageLabel.GetRect()->m_bottom + 0x14;
	LegoS32 rectBottom = m_yesIcon->GetRect()->m_bottom;
	rectBottom += rect.m_top;
	rect.m_left = 0x19;
	rect.m_bottom = rectBottom;
	rect.m_right = m_yesIcon->GetRect()->m_right + 0x19;

	m_yesIcon->SetRect(&rect);
	m_yesIcon->SetParent(&m_frame);
	m_yesIcon->AttachToParent(GetRootIcon());

	if (m_defaultYes) {
		m_yesIcon->Select(5);
	}
}

// FUNCTION: LEGORACERS 0x004684e0
void MenuDialog::DialogScreen::AttachNoIcon()
{
	Rect rect;

	m_noIcon->SetIconEventHandler(this);

	LegoS32 bottom = m_noIcon->GetRect()->m_bottom + 0x14;
	m_halfHeight += bottom * 0.5f;

	LegoS32 rectTop = m_yesIcon->GetRect()->m_bottom + 0x14;
	rect.m_top = rectTop;
	LegoS32 rectBottom = m_noIcon->GetRect()->m_bottom;
	rectBottom += rectTop;
	LegoS32 rectRight = m_noIcon->GetRect()->m_right;
	rectRight += 0x19;
	rect.m_left = 0x19;
	rect.m_bottom = rectBottom;
	rect.m_right = rectRight;

	m_noIcon->SetRect(&rect);
	m_noIcon->SetParent(&m_frame);
	m_noIcon->AttachToParent(GetRootIcon());

	if (!m_defaultYes) {
		m_noIcon->Select(5);
	}
}

// FUNCTION: LEGORACERS 0x00468590
void MenuDialog::DialogScreen::Open()
{
	Rect rect;

	m_halfWidth = (m_messageLabel.GetRect()->m_right + 0x28) * 0.5f;
	m_halfHeight = (m_messageLabel.GetRect()->m_bottom + 0x28) * 0.5f;

	rect.m_top = m_messageLabel.GetRect()->m_top + 0x14;
	rect.m_bottom = m_messageLabel.GetRect()->m_bottom + 0x14;
	rect.m_left = m_messageLabel.GetRect()->m_left + 0x14;
	rect.m_right = m_messageLabel.GetRect()->m_right + 0x14;
	m_messageLabel.SetRect(&rect);

	m_centerX = m_rootIcon.GetRect()->m_right >> 1;
	m_centerY = m_rootIcon.GetRect()->m_bottom >> 1;

	switch (m_type) {
	case 2:
		AttachYesIcon();
		AttachNoIcon();
		break;
	case 1:
		AttachPopupIcon();
		break;
	}

	DisableWidgets();
}

// FUNCTION: LEGORACERS 0x00468670
void MenuDialog::DialogScreen::OnIconUnfocused(MenuWidget* p_source)
{
	if (p_source == m_popupIcon) {
		m_result = 2;
	}
	else if (p_source == m_yesIcon) {
		m_result = 3;
	}
	else if (p_source == m_noIcon) {
		m_result = 4;
	}

	if (m_eventHandler) {
		m_eventHandler->OnIconUnfocused(p_source);
	}
	else {
		BeginClose();
	}
}

// FUNCTION: LEGORACERS 0x004686d0
MenuStyleTable* MenuDialog::DialogScreen::GetMenuStyles()
{
	return m_menuStyles;
}

// FUNCTION: LEGORACERS 0x004686e0
MenuInputBindingTable* MenuDialog::DialogScreen::GetMenuInputBindings()
{
	return (MenuInputBindingTable*) m_owner;
}

// STUB: LEGORACERS 0x004686f0
void MenuDialog::DialogScreen::EnableWidgets()
{
	m_messageLabel.SetFlags(2);

	MenuIcon* icon = m_popupIcon;
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}

	icon = m_yesIcon;
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}

	icon = m_noIcon;
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}
}

// STUB: LEGORACERS 0x00468740
void MenuDialog::DialogScreen::DisableWidgets()
{
	m_messageLabel.ClearFlags(2);

	MenuIcon* icon = m_popupIcon;
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}

	icon = m_yesIcon;
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}

	icon = m_noIcon;
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00468790
undefined4 MenuDialog::DialogScreen::GetResult() const
{
	return m_result;
}

// FUNCTION: LEGORACERS 0x004687a0
void MenuDialog::DialogScreen::BeginClose()
{
	DisableWidgets();

	if (m_popupIcon && (m_popupIcon->GetFlags() & 1)) {
		m_popupIcon->DetachFromParent();
		m_popupIcon->RemoveFromParent();
	}

	if (m_yesIcon && (m_yesIcon->GetFlags() & 1)) {
		m_yesIcon->DetachFromParent();
		m_yesIcon->RemoveFromParent();
	}

	if (m_noIcon && (m_noIcon->GetFlags() & 1)) {
		m_noIcon->DetachFromParent();
		m_noIcon->RemoveFromParent();
	}

	m_state = 3;
}

// FUNCTION: LEGORACERS 0x00468820 FOLDED
LegoBool32 MenuDialog::DialogScreen::HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_state != 2;
}

// FUNCTION: LEGORACERS 0x00468820 FOLDED
LegoBool32 MenuDialog::DialogScreen::HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_state != 2;
}

// FUNCTION: LEGORACERS 0x00468840
LegoBool32 MenuDialog::DialogScreen::Draw(Rect* p_arg1, Rect* p_arg2)
{
	return MenuScreen::Draw(p_arg1, p_arg2);
}

// FUNCTION: LEGORACERS 0x00468860
LegoBool32 MenuDialog::DialogScreen::Update(undefined4 p_elapsedMs)
{
	LegoFloat scale = 1.0f;

	m_ageMs += p_elapsedMs;

	if (!m_type && m_ageMs > 5000) {
		m_result = 1;
		BeginClose();
	}

	if (m_state == 1 || m_state == 3) {
		m_animMs += p_elapsedMs;
		LegoS32 elapsedMs = m_animMs;
		LegoFloat elapsedScale = (LegoFloat) elapsedMs;
		scale = elapsedScale * g_dialogAnimRate;

		if ((LegoU32) elapsedMs > 300) {
			if (m_state == 1) {
				EnableWidgets();
				m_animMs = 0;
				m_state = 2;
			}
			else {
				m_animMs = 0;
				m_state = 0;
				m_closed = 1;
			}
		}

		if (m_state == 3) {
			scale = 1.0f - scale;
		}

		if (scale > 1.0f) {
			scale = 1.0f;
		}
		else if (scale < 0.0f) {
			scale = 0.0f;
		}
	}

	LegoFloat scaledX = m_halfWidth;
	scaledX *= scale;
	LegoS32 x = (LegoS32) scaledX;

	LegoFloat scaledY = m_halfHeight;
	scaledY *= scale;
	LegoS32 y = (LegoS32) scaledY;

	Rect rect;
	LegoS32 right = m_centerX;
	LegoS32 left = right;
	right += x;
	rect.m_right = right;
	left -= x;
	rect.m_left = left;

	LegoS32 bottom = m_centerY;
	LegoS32 top = bottom;
	bottom += y;
	rect.m_bottom = bottom;
	top -= y;
	rect.m_top = top;

	m_frame.SetRect(&rect);

	return m_closed == 0;
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
undefined4 MenuDialog::DialogScreen::ShouldLoadResources()
{
	return 0;
}
