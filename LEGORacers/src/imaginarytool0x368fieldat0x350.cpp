#include "imaginarytool0x368.h"

DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x350, 0x4)

// FUNCTION: LEGORACERS 0x0040eac0
ImaginaryTool0x368::FieldAt0x350::FieldAt0x350()
{
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
}

// FUNCTION: LEGORACERS 0x00442e60
void ImaginaryTool0x368::FieldAt0x350::SetColor(ColorRGBA p_color)
{
	m_color = p_color;
}
