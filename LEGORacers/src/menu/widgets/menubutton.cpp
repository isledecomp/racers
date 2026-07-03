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
	::memset(m_unk0x1a8, 0, sizeof(m_unk0x1a8));

	m_unk0x1c0.Destroy();
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x00466370
LegoBool32 MenuButton::FUN_00466370(MenuImage* p_unk0x04, CreateParams* p_createParams)
{
	MenuImage::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));

	GolImage* image = p_createParams->m_images[0];
	::memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));
	createParams.m_id = m_id;
	createParams.m_color = m_stateColors[0];
	createParams.m_parent = this;
	createParams.m_unk0x38 = image;

	return p_unk0x04->Create(&createParams);
}

// FUNCTION: LEGORACERS 0x004663d0
LegoBool32 MenuButton::Create(CreateParams* p_createParams, const MenuIcon::CreateState* p_createState)
{
	Destroy();

	::memcpy(m_unk0x1a8, p_createParams->m_images, sizeof(m_unk0x1a8));

	if (!p_createParams->m_rect.m_right) {
		p_createParams->m_rect.m_right = p_createParams->m_rect.m_left + m_unk0x1a8[0]->GetWidth();
	}

	if (!p_createParams->m_rect.m_bottom) {
		p_createParams->m_rect.m_bottom = p_createParams->m_rect.m_top + m_unk0x1a8[0]->GetHeight();
	}

	if (MenuIcon::Create(p_createParams, p_createState)) {
		return FUN_00466370(&m_unk0x1c0, p_createParams);
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

	m_unk0x1c0.SetRect(&rect);
	m_unk0x1c0.SetUnk0x58(m_unk0x1a8[m_visualStateIndex]);
	m_unk0x1c0.SetColor(&m_stateColors[m_visualStateIndex]);

	return NULL;
}
