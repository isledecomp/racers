#include "menu/widgets/menutriangle.h"

#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(MenuTriangle, 0xa4)

// FUNCTION: LEGORACERS 0x004734a0
MenuTriangle::MenuTriangle()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00473510
MenuTriangle::~MenuTriangle()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00473560
void MenuTriangle::Reset()
{
	m_vertices[2].m_z = 0;
	m_vertices[1].m_z = 0;
	m_vertices[0].m_z = 0;
	m_vertices[2].m_u = 0;
	m_vertices[1].m_u = 0;
	m_vertices[0].m_u = 0;
	m_vertices[2].m_v = 0;
	m_vertices[1].m_v = 0;
	m_vertices[0].m_v = 0;
	m_alphaOverride = 0;

	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x004735a0
LegoBool32 MenuTriangle::Create(CreateParams* p_createParams)
{
	Destroy();
	return CreateWidget(p_createParams);
}

// FUNCTION: LEGORACERS 0x004735c0
void MenuTriangle::SetColor(VisualStateColor* p_param)
{
	m_vertices[0].m_color = p_param->m_color;
	m_vertices[1].m_color = p_param->m_color;
	m_vertices[2].m_color = p_param->m_color;

	MenuWidget::SetColor(p_param);
}

// FUNCTION: LEGORACERS 0x004735f0
MenuWidget* MenuTriangle::DrawSelf(Rect*, Rect* p_rect)
{
	LegoU32 alphaFlags = 0;
	LegoU32 alphaOverride = m_alphaOverride;
	if (alphaOverride) {
		alphaFlags = 1;
	}

	m_vertices[0].m_x = static_cast<LegoFloat>(p_rect->m_left);
	m_vertices[0].m_y = static_cast<LegoFloat>(p_rect->m_top);
	m_vertices[1].m_x = static_cast<LegoFloat>(p_rect->m_right);
	m_vertices[1].m_y = m_vertices[0].m_y;
	m_vertices[2].m_x = m_vertices[0].m_x;
	m_vertices[2].m_y = static_cast<LegoFloat>(p_rect->m_bottom);

	if (alphaOverride) {
		m_renderer->SetAlphaOverride(alphaOverride, alphaFlags);
	}

	m_renderer->DrawTriangle(&m_vertices[0], &m_vertices[1], &m_vertices[2], NULL, 0);
	m_vertices[0].m_x = m_vertices[1].m_x;
	m_vertices[0].m_y = m_vertices[2].m_y;
	m_renderer->DrawTriangle(&m_vertices[2], &m_vertices[1], &m_vertices[0], NULL, 0);

	if (m_alphaOverride) {
		m_renderer->ClearAlphaOverride();
	}

	return NULL;
}
