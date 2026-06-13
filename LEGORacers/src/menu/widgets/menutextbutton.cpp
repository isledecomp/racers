#include "menu/widgets/menutextbutton.h"

#include "font/golfont.h"
#include "golstringtable.h"
#include "image/utopianpan0xa4.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuTextButton, 0x2f0)
DECOMP_SIZE_ASSERT(MenuTextButton::CreateParams, 0xe0)

// FUNCTION: LEGORACERS 0x00482390
MenuTextButton::MenuTextButton()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00482420
MenuTextButton::~MenuTextButton()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00482490
void MenuTextButton::Reset()
{
	m_unk0x1a8 = NULL;
	m_unk0x2dc = 0;
	::memset(m_unk0x1c0, 0, sizeof(m_unk0x1c0) + sizeof(m_unk0x1d8) + sizeof(m_unk0x1f0));
	::memset(m_unk0x2e0, 0, sizeof(m_unk0x2e0));
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x004824d0
LegoBool32 MenuTextButton::FUN_004824d0(CreateParams* p_createParams)
{
	MenuImage::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	::memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));

	LegoU8 flags = createParams.m_flags;
	createParams.m_rect.m_left = 0;
	flags |= 1;
	createParams.m_rect.m_top = 0;
	createParams.m_flags = flags;
	createParams.m_rect.m_right = 0;
	createParams.m_unk0x38 = m_unk0x1d8[0];
	createParams.m_rect.m_bottom = 0;
	createParams.m_parent = this;
	createParams.m_unk0x22 = m_unk0x1f0[0];

	return m_unk0x208.FUN_0046f150(&createParams);
}

// FUNCTION: LEGORACERS 0x00482540
LegoBool32 MenuTextButton::FUN_00482540(CreateParams* p_createParams, MenuStyleTable::TextButtonStyle*)
{
	GolString string;
	MenuTextLabel::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	::memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));

	p_createParams->m_unk0xcc->CopyStringByIndex(&string, p_createParams->m_unk0xd4);

	Rect source;
	p_createParams->m_unk0x84[0]->MeasureString(&string, &source.m_right, &source.m_bottom);

	if (m_unk0x2dc && source.m_right > m_unk0x2dc) {
		source.m_right = m_unk0x2dc;
	}

	source.m_top = 0;
	source.m_left = 0;
	source.m_bottom = m_unk0x208.GetRect()->m_bottom - m_unk0x208.GetRect()->m_top;

	MeasureText(m_unk0x1c0[m_visualStateIndex], &string, &source, &createParams.m_rect, 0);

	LegoS32 right = m_unk0x208.GetRect()->m_right;
	createParams.m_rect.m_right += right;
	createParams.m_flags |= 3;
	createParams.m_unk0x38 = p_createParams->m_unk0xcc;
	createParams.m_unk0x3c = m_unk0x1c0[0];
	createParams.m_unk0x40 = p_createParams->m_unk0xd4;
	createParams.m_unk0x22 = m_unk0x174[0];
	createParams.m_rect.m_left += right;
	createParams.m_parent = this;
	m_unk0x1ac.m_unk0x10 = 0;

	return m_unk0x264.FUN_0046f520(&createParams, &m_unk0x1ac);
}

// FUNCTION: LEGORACERS 0x004826c0
LegoBool32 MenuTextButton::FUN_004826c0(CreateParams* p_createParams, MenuStyleTable::TextButtonStyle* p_styleEntry)
{
	VTable0x08();

	m_unk0x1a8 = p_styleEntry;
	LegoS32 maxWidth;
	if (p_createParams->m_unk0xdc) {
		maxWidth = p_createParams->m_unk0xd8;
	}
	else {
		maxWidth = p_styleEntry->m_unk0xfc;
	}

	m_unk0x2dc = maxWidth;
	::memcpy(m_unk0x1c0, p_createParams->m_unk0x84, sizeof(m_unk0x1c0) + sizeof(m_unk0x1d8) + sizeof(m_unk0x1f0));

	if (FUN_00471e30(p_createParams, p_styleEntry) && FUN_004824d0(p_createParams) &&
		FUN_00482540(p_createParams, p_styleEntry)) {
		VTable0x10(&p_createParams->m_rect);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00482760
LegoBool32 MenuTextButton::VTable0x08()
{
	MenuWidget* fieldAt0x264 = &m_unk0x264;
	fieldAt0x264->VTable0x08();

	MenuWidget* fieldAt0x208 = &m_unk0x208;
	fieldAt0x208->VTable0x08();

	return MenuIcon::VTable0x08();
}

// FUNCTION: LEGORACERS 0x00482790
void MenuTextButton::FUN_00482790(undefined4 p_unk0x04)
{
	m_unk0x264.VTable0x44(static_cast<undefined2>(p_unk0x04), TRUE);

	if (m_unk0x2dc && m_unk0x264.GetRect()->m_right - m_unk0x264.GetRect()->m_left > m_unk0x2dc) {
		Rect rect = *m_unk0x264.GetRect();
		rect.m_right = rect.m_left + m_unk0x2dc;
		m_unk0x264.VTable0x10(&rect);
	}

	VTable0x10(&m_unk0x34);
}

// FUNCTION: LEGORACERS 0x00482810
void MenuTextButton::FUN_00482810(GolString* p_string)
{
	m_unk0x264.VTable0x40(p_string, TRUE);

	if (m_unk0x2dc && m_unk0x264.GetRect()->m_right - m_unk0x264.GetRect()->m_left > m_unk0x2dc) {
		Rect rect = *m_unk0x264.GetRect();
		rect.m_right = rect.m_left + m_unk0x2dc;
		m_unk0x264.VTable0x10(&rect);
	}

	VTable0x10(&m_unk0x34);
}

// FUNCTION: LEGORACERS 0x00482890
void MenuTextButton::VTable0x10(Rect* p_rect)
{
	LegoU8 flags = m_flags;
	Rect rect = *p_rect;

	if (flags & 1) {
		rect.m_right = m_unk0x264.GetRect()->m_right + rect.m_left;
		rect.m_bottom = m_unk0x1d8[0]->GetHeight() + rect.m_top;
		MenuIcon::VTable0x10(&rect);
	}
}

// FUNCTION: LEGORACERS 0x004828f0
void MenuTextButton::VTable0x40(MenuScreenInterface* p_eventHandler)
{
	MenuIcon::VTable0x40(p_eventHandler);
	m_unk0x208.SetEventHandler(p_eventHandler);
	m_unk0x264.SetEventHandler(p_eventHandler);
}

// FUNCTION: LEGORACERS 0x00482910
MenuWidget* MenuTextButton::VTable0x38(Rect*, Rect*)
{
	m_unk0x208.SetUnk0x58(m_unk0x1d8[m_visualStateIndex]);
	m_unk0x208.VTable0x14(&m_unk0x1f0[m_visualStateIndex]);
	m_unk0x264.SetUnk0x60(m_unk0x1c0[m_visualStateIndex]);
	m_unk0x264.VTable0x14(&m_unk0x174[m_visualStateIndex]);

	return NULL;
}

// FUNCTION: LEGORACERS 0x00482980
MenuWidget* MenuTextButton::VTable0x34(InputEventQueue::Event* p_item, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	return MenuIcon::VTable0x34(p_item, p_unk0x08, p_unk0x0c);
}
