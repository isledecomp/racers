#include "menu/widgets/menubutton.h"

#include "image/golimage.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuButton, 0x21c)
DECOMP_SIZE_ASSERT(MenuButton::CreateParams, 0x9c)

// FUNCTION: LEGORACERS 0x00466260
MenuButton::MenuButton()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004662e0
MenuButton::~MenuButton()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00466340
void MenuButton::Reset()
{
	::memset(m_stateImages, 0, sizeof(m_stateImages));

	m_imageWidget.Destroy();
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x00466370
LegoBool32 MenuButton::CreateImage(MenuImage* p_image, CreateParams* p_createParams)
{
	MenuImage::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));

	GolImage* image = p_createParams->m_stateImages[0];
	::memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));
	createParams.m_id = m_id;
	createParams.m_color = m_stateColors[0];
	createParams.m_parent = this;
	createParams.m_image = image;

	return p_image->Create(&createParams);
}

// FUNCTION: LEGORACERS 0x004663d0
LegoBool32 MenuButton::Create(CreateParams* p_createParams, const MenuIcon::CreateState* p_createState)
{
	Destroy();

	::memcpy(m_stateImages, p_createParams->m_stateImages, sizeof(m_stateImages));

	if (!p_createParams->m_rect.m_right) {
		p_createParams->m_rect.m_right = p_createParams->m_rect.m_left + m_stateImages[0]->GetWidth();
	}

	if (!p_createParams->m_rect.m_bottom) {
		p_createParams->m_rect.m_bottom = p_createParams->m_rect.m_top + m_stateImages[0]->GetHeight();
	}

	if (MenuIcon::Create(p_createParams, p_createState)) {
		return CreateImage(&m_imageWidget, p_createParams);
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00466450
LegoBool32 MenuButton::Destroy()
{
	LegoBool32 result = TRUE;

	if (m_flags & 1) {
		return MenuIcon::Destroy();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00466470
MenuWidget* MenuButton::DrawSelf(Rect*, Rect*)
{
	Rect rect;
	rect.m_top = 0;
	rect.m_left = 0;
	rect.m_right = m_rect.m_right - m_rect.m_left;
	rect.m_bottom = m_rect.m_bottom - m_rect.m_top;

	m_imageWidget.SetRect(&rect);
	m_imageWidget.SetImage(m_stateImages[m_visualStateIndex]);
	m_imageWidget.SetColor(&m_stateColors[m_visualStateIndex]);

	return NULL;
}
