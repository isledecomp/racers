#include "menu/menudialog.h"
#include "menu/style/sharedmenustyletable.h"

DECOMP_SIZE_ASSERT(MenuDialog::DialogScreen, 0x74c)
DECOMP_SIZE_ASSERT(MenuDialog::DialogScreen::CreateParams, 0x18)

// GLOBAL: LEGORACERS 0x004b2160
extern const LegoFloat g_unk0x4b2160 = 0.0033333334f;

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
	m_unk0x290 = NULL;
	m_unk0x294 = NULL;
	m_unk0x298 = NULL;
	m_unk0x744 = NULL;
	m_unk0x748 = NULL;
	m_unk0x740 = NULL;
	m_unk0x2bc = 0;
	m_unk0x2c0 = 0;
	m_unk0x29c = 0;
	m_unk0x2a0 = 0;
	m_unk0x2ac = 0;
	m_unk0x2b0 = 0;
	m_unk0x2b4 = 0;
	m_unk0x2a4 = 0.0f;
	m_unk0x2a8 = 0.0f;
	m_unk0x2c4 = 0;
	m_unk0x2c8 = 0;
	m_unk0x2b8 = 1;
	m_unk0x2cc.VTable0x08();
	m_unk0x6c8.VTable0x08();
	MenuScreen::Reset();
}

// FUNCTION: LEGORACERS 0x004682c0
void MenuDialog::DialogScreen::VTable0x4c()
{
	CreateFrame(&m_unk0x2cc, 0x11f, 0x47);
	CreateTextLabel(&m_unk0x6c8, 0x120, 0x37, m_unk0x2ac);
}

// FUNCTION: LEGORACERS 0x00468300
LegoBool32 MenuDialog::DialogScreen::FUN_00468300(CreateParams* p_createParams)
{
	Destroy();

	m_unk0x290 = p_createParams->m_owner;
	m_unk0x294 = p_createParams->m_createParams->m_menuStyles;
	m_unk0x298 = p_createParams->m_eventHandler;
	p_createParams->m_createParams->m_unk0x20 = NULL;
	m_unk0x2b8 = p_createParams->m_unk0x0c;
	m_unk0x2ac = p_createParams->m_unk0x10;
	m_unk0x2c8 = p_createParams->m_unk0x14;
	m_unk0x2c4 = 0;

	if (!MenuScreen::Initialize(p_createParams->m_createParams)) {
		return FALSE;
	}

	m_unk0x2c0 = 0;
	m_unk0x2bc = 1;

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00468390
void MenuDialog::DialogScreen::FUN_00468390()
{
	Rect rect;

	m_unk0x740->VTable0x40(this);

	LegoS32 bottom = m_unk0x740->GetRect()->m_bottom + 0x14;
	m_unk0x2a8 += bottom * 0.5f;

	rect.m_top = m_unk0x6c8.GetRect()->m_bottom + 0x14;
	LegoS32 rectBottom = m_unk0x740->GetRect()->m_bottom;
	rectBottom += rect.m_top;
	rect.m_left = 0x19;
	rect.m_bottom = rectBottom;
	rect.m_right = m_unk0x740->GetRect()->m_right + 0x19;

	m_unk0x740->VTable0x10(&rect);
	m_unk0x740->SetParent(&m_unk0x2cc);
	m_unk0x740->AttachToParent(GetUnk0xd8());
	m_unk0x740->VTable0x4c(5);
}

// FUNCTION: LEGORACERS 0x00468430
void MenuDialog::DialogScreen::FUN_00468430()
{
	Rect rect;

	m_unk0x744->VTable0x40(this);

	LegoS32 bottom = m_unk0x744->GetRect()->m_bottom + 0x14;
	m_unk0x2a8 += bottom * 0.5f;

	rect.m_top = m_unk0x6c8.GetRect()->m_bottom + 0x14;
	LegoS32 rectBottom = m_unk0x744->GetRect()->m_bottom;
	rectBottom += rect.m_top;
	rect.m_left = 0x19;
	rect.m_bottom = rectBottom;
	rect.m_right = m_unk0x744->GetRect()->m_right + 0x19;

	m_unk0x744->VTable0x10(&rect);
	m_unk0x744->SetParent(&m_unk0x2cc);
	m_unk0x744->AttachToParent(GetUnk0xd8());

	if (m_unk0x2c8) {
		m_unk0x744->VTable0x4c(5);
	}
}

// FUNCTION: LEGORACERS 0x004684e0
void MenuDialog::DialogScreen::FUN_004684e0()
{
	Rect rect;

	m_unk0x748->VTable0x40(this);

	LegoS32 bottom = m_unk0x748->GetRect()->m_bottom + 0x14;
	m_unk0x2a8 += bottom * 0.5f;

	LegoS32 rectTop = m_unk0x744->GetRect()->m_bottom + 0x14;
	rect.m_top = rectTop;
	LegoS32 rectBottom = m_unk0x748->GetRect()->m_bottom;
	rectBottom += rectTop;
	LegoS32 rectRight = m_unk0x748->GetRect()->m_right;
	rectRight += 0x19;
	rect.m_left = 0x19;
	rect.m_bottom = rectBottom;
	rect.m_right = rectRight;

	m_unk0x748->VTable0x10(&rect);
	m_unk0x748->SetParent(&m_unk0x2cc);
	m_unk0x748->AttachToParent(GetUnk0xd8());

	if (!m_unk0x2c8) {
		m_unk0x748->VTable0x4c(5);
	}
}

// FUNCTION: LEGORACERS 0x00468590
void MenuDialog::DialogScreen::FUN_00468590()
{
	Rect rect;

	m_unk0x2a4 = (m_unk0x6c8.GetRect()->m_right + 0x28) * 0.5f;
	m_unk0x2a8 = (m_unk0x6c8.GetRect()->m_bottom + 0x28) * 0.5f;

	rect.m_top = m_unk0x6c8.GetRect()->m_top + 0x14;
	rect.m_bottom = m_unk0x6c8.GetRect()->m_bottom + 0x14;
	rect.m_left = m_unk0x6c8.GetRect()->m_left + 0x14;
	rect.m_right = m_unk0x6c8.GetRect()->m_right + 0x14;
	m_unk0x6c8.VTable0x10(&rect);

	m_unk0x29c = m_unk0xd8.GetRect()->m_right >> 1;
	m_unk0x2a0 = m_unk0xd8.GetRect()->m_bottom >> 1;

	switch (m_unk0x2b8) {
	case 2:
		FUN_00468430();
		FUN_004684e0();
		break;
	case 1:
		FUN_00468390();
		break;
	}

	FUN_00468740();
}

// FUNCTION: LEGORACERS 0x00468670
void MenuDialog::DialogScreen::VTable0x38(MenuWidget* p_unk0x04)
{
	if (p_unk0x04 == m_unk0x740) {
		m_unk0x2c0 = 2;
	}
	else if (p_unk0x04 == m_unk0x744) {
		m_unk0x2c0 = 3;
	}
	else if (p_unk0x04 == m_unk0x748) {
		m_unk0x2c0 = 4;
	}

	if (m_unk0x298) {
		m_unk0x298->VTable0x38(p_unk0x04);
	}
	else {
		FUN_004687a0();
	}
}

// FUNCTION: LEGORACERS 0x004686d0
MenuStyleTable* MenuDialog::DialogScreen::GetMenuStyles()
{
	return m_unk0x294;
}

// FUNCTION: LEGORACERS 0x004686e0
MenuInputBindingTable* MenuDialog::DialogScreen::GetMenuInputBindings()
{
	return (MenuInputBindingTable*) m_unk0x290;
}

// STUB: LEGORACERS 0x004686f0
void MenuDialog::DialogScreen::FUN_004686f0()
{
	m_unk0x6c8.SetFlags(2);

	MenuIcon* icon = m_unk0x740;
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}

	icon = m_unk0x744;
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}

	icon = m_unk0x748;
	if (icon && (icon->GetFlags() & 1)) {
		icon->SetFlags(2);
	}
}

// STUB: LEGORACERS 0x00468740
void MenuDialog::DialogScreen::FUN_00468740()
{
	m_unk0x6c8.ClearFlags(2);

	MenuIcon* icon = m_unk0x740;
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}

	icon = m_unk0x744;
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}

	icon = m_unk0x748;
	if (icon && (icon->GetFlags() & 1)) {
		icon->ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00468790
undefined4 MenuDialog::DialogScreen::GetUnk0x2c0() const
{
	return m_unk0x2c0;
}

// FUNCTION: LEGORACERS 0x004687a0
void MenuDialog::DialogScreen::FUN_004687a0()
{
	FUN_00468740();

	if (m_unk0x740 && (m_unk0x740->GetFlags() & 1)) {
		m_unk0x740->DetachFromParent();
		m_unk0x740->RemoveFromParent();
	}

	if (m_unk0x744 && (m_unk0x744->GetFlags() & 1)) {
		m_unk0x744->DetachFromParent();
		m_unk0x744->RemoveFromParent();
	}

	if (m_unk0x748 && (m_unk0x748->GetFlags() & 1)) {
		m_unk0x748->DetachFromParent();
		m_unk0x748->RemoveFromParent();
	}

	m_unk0x2bc = 3;
}

// FUNCTION: LEGORACERS 0x00468820 FOLDED
LegoBool32 MenuDialog::DialogScreen::VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_unk0x2bc != 2;
}

// FUNCTION: LEGORACERS 0x00468820 FOLDED
LegoBool32 MenuDialog::DialogScreen::VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return m_unk0x2bc != 2;
}

// FUNCTION: LEGORACERS 0x00468840
LegoBool32 MenuDialog::DialogScreen::VTable0x7c(Rect* p_arg1, Rect* p_arg2)
{
	return MenuScreen::VTable0x7c(p_arg1, p_arg2);
}

// FUNCTION: LEGORACERS 0x00468860
LegoBool32 MenuDialog::DialogScreen::VTable0x78(undefined4 p_elapsedMs)
{
	LegoFloat scale = 1.0f;

	m_unk0x2b0 += p_elapsedMs;

	if (!m_unk0x2b8 && m_unk0x2b0 > 5000) {
		m_unk0x2c0 = 1;
		FUN_004687a0();
	}

	if (m_unk0x2bc == 1 || m_unk0x2bc == 3) {
		m_unk0x2b4 += p_elapsedMs;
		LegoS32 elapsedMs = m_unk0x2b4;
		LegoFloat elapsedScale = (LegoFloat) elapsedMs;
		scale = elapsedScale * g_unk0x4b2160;

		if ((LegoU32) elapsedMs > 300) {
			if (m_unk0x2bc == 1) {
				FUN_004686f0();
				m_unk0x2b4 = 0;
				m_unk0x2bc = 2;
			}
			else {
				m_unk0x2b4 = 0;
				m_unk0x2bc = 0;
				m_unk0x2c4 = 1;
			}
		}

		if (m_unk0x2bc == 3) {
			scale = 1.0f - scale;
		}

		if (scale > 1.0f) {
			scale = 1.0f;
		}
		else if (scale < 0.0f) {
			scale = 0.0f;
		}
	}

	LegoFloat scaledX = m_unk0x2a4;
	scaledX *= scale;
	LegoS32 x = (LegoS32) scaledX;

	LegoFloat scaledY = m_unk0x2a8;
	scaledY *= scale;
	LegoS32 y = (LegoS32) scaledY;

	Rect rect;
	LegoS32 right = m_unk0x29c;
	LegoS32 left = right;
	right += x;
	rect.m_right = right;
	left -= x;
	rect.m_left = left;

	LegoS32 bottom = m_unk0x2a0;
	LegoS32 top = bottom;
	bottom += y;
	rect.m_bottom = bottom;
	top -= y;
	rect.m_top = top;

	m_unk0x2cc.VTable0x10(&rect);

	return m_unk0x2c4 == 0;
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
undefined4 MenuDialog::DialogScreen::VTable0x50()
{
	return 0;
}
