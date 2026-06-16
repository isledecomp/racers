#include "util/marblepath0x114.h"

#include "decomp.h"
#include "render/golrenderdevice.h"

DECOMP_SIZE_ASSERT(MarblePath0x114, 0x114)

// FUNCTION: LEGORACERS 0x004149f0
void MarblePath0x114::FUN_004149f0()
{
	m_unk0x010.VTable0x54();

	if (m_unk0x000 != NULL) {
		if (m_unk0x004 != 0) {
			m_unk0x000->VTable0x48(m_unk0x004);
		}
		m_unk0x000 = NULL;
	}

	m_unk0x004 = 0;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_flags0x100 = 0;
}

// FUNCTION: LEGORACERS 0x00415a40
void MarblePath0x114::FUN_00415a40(GolRenderDevice* p_renderer)
{
	if (m_flags0x100 & c_flags0x100Bit2) {
		p_renderer->VTable0x94(&m_unk0x010);
	}
}

// FUNCTION: LEGORACERS 0x00415bf0
LegoU8 MarblePath0x114::FUN_00415bf0(const ColorRGBA* p_color)
{
	m_unk0x110.m_red = p_color->m_red;
	m_unk0x110.m_grn = p_color->m_grn;
	m_unk0x110.m_blu = p_color->m_blu;
	LegoU8 result = p_color->m_alp;
	m_unk0x110.m_alp = result;

	return result;
}
