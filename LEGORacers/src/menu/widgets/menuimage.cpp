#include "menu/widgets/menuimage.h"

#include "image/golimage.h"

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
	MenuWidget::Destroy();
}

// FUNCTION: LEGORACERS 0x0046f140
void MenuImage::Reset()
{
	m_image = NULL;
	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x0046f150
LegoBool32 MenuImage::Create(CreateParams* p_createParams)
{
	Destroy();

	m_image = p_createParams->m_image;

	if (!p_createParams->m_rect.m_right) {
		p_createParams->m_rect.m_right = m_image->GetWidth() + p_createParams->m_rect.m_left;
	}

	if (!p_createParams->m_rect.m_bottom) {
		p_createParams->m_rect.m_bottom = m_image->GetHeight() + p_createParams->m_rect.m_top;
	}

	return CreateWidget(p_createParams);
}

// FUNCTION: LEGORACERS 0x0046f1a0
MenuWidget* MenuImage::DrawSelf(Rect* p_rect, Rect* p_arg)
{
	Rect sourceRect;
	sourceRect.m_top = 0;
	sourceRect.m_left = 0;
	sourceRect.m_right = m_image->GetWidth();
	sourceRect.m_bottom = m_image->GetHeight();

	ComputeScale(&sourceRect, &m_rect);
	ScaleRect(p_rect, &sourceRect);
	DrawImage(p_arg, &sourceRect, m_image);

	return NULL;
}
