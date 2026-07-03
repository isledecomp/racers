#include "menu/widgets/menuframe.h"

#include "image/golimage.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuFrame, 0x3fc)
DECOMP_SIZE_ASSERT(MenuFrame::CreateParams, 0x60)
DECOMP_SIZE_ASSERT(MenuFrame::CreateParamsPrefix, 0x38)

// FUNCTION: LEGORACERS 0x0046ebb0
MenuFrame::MenuFrame()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046ec50
MenuFrame::~MenuFrame()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046ecd0
LegoBool32 MenuFrame::Create(CreateParams* p_createParams)
{
	Destroy();

	if (CreateWidget(p_createParams) && CreateBorder(p_createParams) && CreateFill(p_createParams)) {
		if (!p_createParams->m_hasFillColor) {
			m_fill.ClearFlags(0x10);
		}

		SetRect(&p_createParams->m_rect);
		return TRUE;
	}

	Destroy();
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046ed30
LegoBool32 MenuFrame::CreateFill(CreateParams* p_createParams)
{
	MenuImage::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));

	for (LegoS32 i = 0; i < 8; i++) {
		::memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));
		createParams.m_parent = this;
		createParams.m_flags |= 1;
		createParams.m_id = 0x400;

		GolImage* image = p_createParams->m_images[i];
		createParams.m_image = image;
		m_images[i] = image;
		createParams.m_color = p_createParams->m_color;

		if (!m_borderImages[i].Create(&createParams)) {
			return FALSE;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046edf0
LegoBool32 MenuFrame::CreateBorder(CreateParams* p_createParams)
{
	CreateParamsPrefix createParams;
	::memcpy(&createParams, p_createParams, sizeof(createParams));
	createParams.m_id = 0x29a;
	createParams.m_parent = this;
	createParams.m_flags |= 1;
	createParams.m_color = p_createParams->m_fillColor;

	return m_fill.Create(&createParams);
}

// STUB: LEGORACERS 0x0046ee40
void MenuFrame::SetRect(Rect* p_rect)
{
	MenuWidget::SetRect(p_rect);

	if (m_flags & 1) {
		LegoS32 width = m_rect.m_right - m_rect.m_left;
		LegoS32 height = m_rect.m_bottom - m_rect.m_top;

		Rect rect;
		Rect rect2;
		Rect rect3;

		rect.m_left = 0;
		rect.m_top = 0;
		rect.m_right = m_images[0]->GetWidth();
		rect.m_bottom = m_images[0]->GetHeight();

		rect2.m_left = m_images[0]->GetWidth();
		rect2.m_top = 0;
		rect2.m_right = width - m_images[2]->GetWidth();
		rect2.m_bottom = m_images[1]->GetHeight();

		rect3.m_left = width - m_images[2]->GetWidth();
		rect3.m_top = 0;
		rect3.m_right = width;
		rect3.m_bottom = m_images[0]->GetHeight();

		m_borderImages[0].SetRect(&rect);
		m_borderImages[1].SetRect(&rect2);
		m_borderImages[2].SetRect(&rect3);

		rect2.m_left = width - m_images[3]->GetWidth();
		rect2.m_top = m_images[0]->GetHeight();
		rect2.m_right = width;
		rect2.m_bottom = height - m_images[4]->GetHeight();

		rect.m_left = width - m_images[4]->GetWidth();
		rect.m_top = height - m_images[4]->GetHeight();
		rect.m_right = width;
		rect.m_bottom = height;

		m_borderImages[3].SetRect(&rect2);
		m_borderImages[4].SetRect(&rect);

		rect2.m_left = m_images[6]->GetWidth();
		rect2.m_top = height - m_images[5]->GetHeight();
		rect2.m_right = width - m_images[4]->GetWidth();
		rect2.m_bottom = height;

		rect3.m_left = 0;
		rect3.m_top = height - m_images[6]->GetHeight();
		rect3.m_right = m_images[6]->GetWidth();
		rect3.m_bottom = height;

		m_borderImages[5].SetRect(&rect2);
		m_borderImages[6].SetRect(&rect3);

		rect2.m_left = 0;
		rect2.m_top = m_borderImages[0].GetRect()->m_bottom;
		rect2.m_right = m_images[7]->GetWidth();
		rect2.m_bottom = height - m_images[6]->GetHeight();

		rect.m_left = m_borderImages[0].GetRect()->m_right;
		rect.m_top = m_borderImages[0].GetRect()->m_bottom;
		rect.m_right = m_borderImages[2].GetRect()->m_left;
		rect.m_bottom = m_borderImages[6].GetRect()->m_top;

		m_borderImages[7].SetRect(&rect2);
		m_fill.SetRect(&rect);
	}
}

// FUNCTION: LEGORACERS 0x0046f050
void MenuFrame::SetBorderColors(VisualStateColor* p_visualState)
{
	for (LegoS32 i = 0; i < 8; i++) {
		m_borderImages[i].SetColor(p_visualState);
	}
}
