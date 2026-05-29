#include "menu/widgets/obscurezebra0xa4.h"

#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(ObscureZebra0xa4, 0xa4)

// FUNCTION: LEGORACERS 0x004734a0
ObscureZebra0xa4::ObscureZebra0xa4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00473510
ObscureZebra0xa4::~ObscureZebra0xa4()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00473560
void ObscureZebra0xa4::Reset()
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

	ObscureVantage0x58::Reset();
}

// FUNCTION: LEGORACERS 0x004735a0
LegoBool32 ObscureZebra0xa4::FUN_004735a0(CreateParams0x38* p_createParams)
{
	VTable0x08();
	return FUN_00472a60(p_createParams);
}

// FUNCTION: LEGORACERS 0x004735c0
void ObscureZebra0xa4::VTable0x14(VisualState0x4* p_param)
{
	m_vertices[0].m_color = p_param->m_color;
	m_vertices[1].m_color = p_param->m_color;
	m_vertices[2].m_color = p_param->m_color;

	ObscureVantage0x58::VTable0x14(p_param);
}

// FUNCTION: LEGORACERS 0x004735f0
ObscureVantage0x58* ObscureZebra0xa4::VTable0x38(Rect*, Rect* p_rect)
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
