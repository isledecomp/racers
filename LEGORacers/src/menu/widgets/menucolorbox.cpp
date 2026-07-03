#include "menu/widgets/menucolorbox.h"

DECOMP_SIZE_ASSERT(MenuColorBox, 0xc0)
DECOMP_SIZE_ASSERT(MenuColorBox::CreateParams, 0x44)

// FUNCTION: LEGORACERS 0x00467e70
MenuColorBox::MenuColorBox()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00467ee0
MenuColorBox::~MenuColorBox()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00467f30
void MenuColorBox::Reset()
{
	m_blinkMs = 0;
	m_onDurationMs = 0;
	m_offDurationMs = 0;
	m_width = 0;
	m_height = 0;
	m_blinkEnabled = 1;
	m_visible = 1;
	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x00467f70
LegoBool32 MenuColorBox::Create(CreateParams* p_createParams)
{
	Destroy();

	m_onDurationMs = p_createParams->m_onDurationMs;
	m_offDurationMs = p_createParams->m_offDurationMs;
	m_blinkEnabled = p_createParams->m_blinkEnabled;
	m_width = p_createParams->m_rect.m_right - p_createParams->m_rect.m_left;
	m_height = p_createParams->m_rect.m_bottom - p_createParams->m_rect.m_top;

	return MenuTriangle::Create(p_createParams);
}

// FUNCTION: LEGORACERS 0x00467fc0
void MenuColorBox::SetPosition(LegoS32 p_x, LegoS32 p_y)
{
	Rect rect;
	rect.m_left = p_x;
	rect.m_right = p_x + m_width;
	rect.m_top = p_y;
	rect.m_bottom = p_y + m_height;

	MenuWidget::SetRect(&rect);
}

// FUNCTION: LEGORACERS 0x00468000
void MenuColorBox::SetWidth(LegoS32 p_width)
{
	LegoS32 width = p_width;
	m_width = width;

	Rect rect;
	rect.m_left = m_rect.m_left;
	rect.m_right = rect.m_left + width;
	rect.m_top = m_rect.m_top;
	rect.m_bottom = rect.m_top + m_height;

	MenuWidget::SetRect(&rect);
}

// FUNCTION: LEGORACERS 0x00468040
void MenuColorBox::SetHeight(LegoS32 p_height)
{
	LegoS32 height = p_height;
	m_height = height;

	Rect rect;
	rect.m_left = m_rect.m_left;
	rect.m_right = rect.m_left + m_width;
	rect.m_top = m_rect.m_top;
	rect.m_bottom = rect.m_top + height;

	MenuWidget::SetRect(&rect);
}

// FUNCTION: LEGORACERS 0x00468080
void MenuColorBox::SetRect(Rect* p_rect)
{
	m_width = p_rect->m_right - p_rect->m_left;
	m_height = p_rect->m_bottom - p_rect->m_top;
	MenuWidget::SetRect(p_rect);
}

// FUNCTION: LEGORACERS 0x004680b0
MenuWidget* MenuColorBox::DrawSelf(Rect* p_param1, Rect* p_param2)
{
	if (!m_visible) {
		return NULL;
	}

	return MenuTriangle::DrawSelf(p_param1, p_param2);
}

// FUNCTION: LEGORACERS 0x004680e0
undefined4 MenuColorBox::OnEvent(undefined4 p_param)
{
	if (m_blinkEnabled) {
		if (p_param < m_blinkMs) {
			m_blinkMs -= p_param;
		}
		else {
			m_visible = (m_visible == 0);

			if (m_visible) {
				m_blinkMs = m_onDurationMs;
			}
			else {
				m_blinkMs = m_offDurationMs;
			}
		}
	}

	return 0;
}
