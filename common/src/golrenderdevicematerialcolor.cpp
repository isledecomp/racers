#include "decomp.h"
#include "render/golrenderdevice.h"
#include "surface/color.h"

DECOMP_SIZE_ASSERT(GolRenderDevice::MaterialColor, 0x4)

// FUNCTION: GOLDP 0x10024760
// FUNCTION: LEGORACERS 0x0040eac0
GolRenderDevice::MaterialColor::MaterialColor()
{
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
}

// FUNCTION: GOLDP 0x10024770
// FUNCTION: LEGORACERS 0x00442e60 FOLDED
void GolRenderDevice::MaterialColor::SetColor(ColorRGBA p_color)
{
	m_color = p_color;
}
