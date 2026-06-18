#include "util/marblepath0x114.h"

#include "core/gol.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "render/golrenderdevice.h"

#include <float.h>

DECOMP_SIZE_ASSERT(MarblePath0x114, 0x114)

// GLOBAL: LEGORACERS 0x004af90c
const LegoFloat g_marblePathMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004af910
const LegoFloat g_marblePathDefaultUnk0x10c = 20.0f;

// GLOBAL: LEGORACERS 0x004af914
const LegoFloat g_marblePathDefaultUnk0x0fc = 0.4f;

extern LegoFloat g_unk0x004c3df4;
extern LegoFloat g_unk0x004c3e04;
extern LegoFloat g_unk0x004c3e14;
extern LegoFloat g_unk0x004c3e24;

// FUNCTION: LEGORACERS 0x00414850
MarblePath0x114::MarblePath0x114()
{
	m_unk0x000 = NULL;
	m_unk0x004 = NULL;
	m_unk0x008 = NULL;
	m_unk0x00c = NULL;
	m_unk0x0a0 = 0;
	m_unk0x0a4 = 0;
	m_unk0x0b0 = 0;
	m_unk0x0b4 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0b8 = 0;
	m_unk0x0a8 = 0;
	m_unk0x0ac = 0;
	m_unk0x10c = g_marblePathDefaultUnk0x10c;
	m_unk0x0c4.m_x = 1.0f;
	m_unk0x0c4.m_y = 0.0f;
	m_unk0x0c4.m_z = 0.0f;
	m_unk0x0d0.m_x = 0.0f;
	m_unk0x0d0.m_y = 1.0f;
	m_unk0x0d0.m_z = 0.0f;
	m_unk0x0dc.m_x = 0.0f;
	m_unk0x0dc.m_y = 0.0f;
	m_unk0x0dc.m_z = 1.0f;
	m_unk0x0e8.m_x = 0.0f;
	m_unk0x0e8.m_y = 0.0f;
	m_unk0x0e8.m_z = 0.0f;
	m_unk0x104 = 1.0f;
	m_unk0x108 = 1.0f;
	m_unk0x110.m_red = 0xff;
	m_unk0x110.m_grn = 0xff;
	m_unk0x110.m_blu = 0xff;
	m_unk0x110.m_alp = 0xff;
	g_unk0x004c3df4 = 0.0f;
	g_unk0x004c3e04 = 0.0f;
	g_unk0x004c3e14 = 0.0f;
	g_unk0x004c3e24 = 1.0f;
	m_flags0x100 = 0;
}

// FUNCTION: LEGORACERS 0x00414940
MarblePath0x114::~MarblePath0x114()
{
	FUN_004149f0();
}

// FUNCTION: LEGORACERS 0x00414950
void MarblePath0x114::FUN_00414950(GolExport* p_golExport, GolRenderDevice* p_renderer, LegoU32 p_count)
{
	if (m_flags0x100 & c_flags0x100Bit0) {
		FUN_004149f0();
	}

	m_unk0x000 = p_golExport;
	m_unk0x004 = p_golExport->VTable0x14();
	m_unk0x0a4 = p_count;
	m_unk0x0a0 = p_count * 3;
	m_unk0x004->VTable0x18(p_renderer, 1, m_unk0x0a0, p_count, p_count * 2 + 2, 1);
	m_unk0x010.VTable0x50(m_unk0x004, g_marblePathMaxFloat);
	m_unk0x0f4.m_x = 0.0f;
	m_unk0x0f4.m_y = 0.0f;
	m_unk0x0f4.m_z = g_marblePathDefaultUnk0x0fc;
	m_unk0x010.VTable0x08(m_unk0x0f4);
	m_flags0x100 = c_flags0x100Bit0;
}

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
