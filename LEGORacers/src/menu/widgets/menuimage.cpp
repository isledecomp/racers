#include "menu/widgets/menuimage.h"

#include "image/utopianpan0xa4.h"

DECOMP_SIZE_ASSERT(MenuImage, 0x5c)
DECOMP_SIZE_ASSERT(MenuImage::CreateParams, 0x3c)

// FUNCTION: LEGORACERS 0x0046f080
MenuImage::MenuImage()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046f0f0
MenuImage::~MenuImage()
{
	MenuWidget::VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046f140
void MenuImage::Reset()
{
	m_unk0x58 = NULL;
	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x0046f150
LegoBool32 MenuImage::FUN_0046f150(CreateParams* p_createParams)
{
	VTable0x08();

	m_unk0x58 = p_createParams->m_unk0x38;

	if (!p_createParams->m_rect.m_right) {
		p_createParams->m_rect.m_right = m_unk0x58->GetWidth() + p_createParams->m_rect.m_left;
	}

	if (!p_createParams->m_rect.m_bottom) {
		p_createParams->m_rect.m_bottom = m_unk0x58->GetHeight() + p_createParams->m_rect.m_top;
	}

	return FUN_00472a60(p_createParams);
}

// FUNCTION: LEGORACERS 0x0046f1a0
MenuWidget* MenuImage::VTable0x38(Rect* p_rect, Rect* p_arg)
{
	Rect sourceRect;
	sourceRect.m_top = 0;
	sourceRect.m_left = 0;
	sourceRect.m_right = m_unk0x58->GetWidth();
	sourceRect.m_bottom = m_unk0x58->GetHeight();

	ComputeScale(&sourceRect, &m_unk0x34);
	ScaleRect(p_rect, &sourceRect);
	DrawImage(p_arg, &sourceRect, m_unk0x58);

	return NULL;
}
