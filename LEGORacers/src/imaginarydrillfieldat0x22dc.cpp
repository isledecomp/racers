#include "imaginarydrillfieldat0x22dc.h"

#include "bronzefalcon0xc8770.h"
#include "gol.h"
#include "golerror.h"
#include "igdbmodel0x40.h"
#include "tanzanitewisp0x88.h"
#include "whitefalconnode0x18.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryDrillFieldAt0x22dc, 0x15c)
DECOMP_SIZE_ASSERT(ImaginaryDrillFieldAt0x22dc::CreateParams, 0x1c)

// GLOBAL: LEGORACERS 0x004b33c4
LegoFloat g_fltMax0x004b33c4 = FLT_MAX;

// FUNCTION: LEGORACERS 0x0047de70
ImaginaryDrillFieldAt0x22dc::ImaginaryDrillFieldAt0x22dc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047df00
ImaginaryDrillFieldAt0x22dc::~ImaginaryDrillFieldAt0x22dc()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0047df60
void ImaginaryDrillFieldAt0x22dc::Reset()
{
	::memset(&m_unk0x154, 0, sizeof(m_unk0x154));
	m_unk0x150 = NULL;
	m_unk0x114 = NULL;
	m_unk0x110 = NULL;
	m_unk0x14c = 0;
}

// FUNCTION: LEGORACERS 0x0047df90
void ImaginaryDrillFieldAt0x22dc::FUN_0047df90()
{
	m_unk0x150->SetUnk0x10(TRUE);
	m_unk0x110 = m_unk0x0c->VTable0x14();

	undefined4 dimensions[5];
	m_unk0x150->FUN_0049dc90(dimensions);
	m_unk0x110->VTable0x18(m_unk0x10, 2, dimensions[0], dimensions[1], dimensions[2], dimensions[3]);

	undefined4 zero = 0;
	IGdbModel0x40* nullModel = NULL;
	WhiteFalconNode0x18* nullNode = NULL;
	m_unk0x154.m_unk0x03 = zero;
	m_unk0x154.m_unk0x02 = zero;
	m_unk0x154.m_unk0x01 = zero;
	m_unk0x154.m_unk0x00 = zero;
	m_unk0x110 = m_unk0x150->FUN_0049db90(&m_unk0x154, m_unk0x110, zero);
	if (m_unk0x110 == nullModel) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x114 = m_unk0x0c->VTable0x18();
	if (m_unk0x114 == nullNode) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x114->VTable0x10(m_unk0x150->FUN_0049dc10(&m_unk0x154));
	m_unk0x1c.FUN_0040d550(m_unk0x110, m_unk0x114, &m_unk0x118, g_fltMax0x004b33c4);
}

// FUNCTION: LEGORACERS 0x0047e0a0
LegoBool32 ImaginaryDrillFieldAt0x22dc::FUN_0047e0a0(CreateParams* p_createParams)
{
	VTable0x08();
	m_unk0x150 = p_createParams->m_unk0x0c;

	if (ObscureLink0x1c::FUN_0046b300(p_createParams)) {
		FUN_0047df90();
		m_unk0x1c.VTable0x08(p_createParams->m_position);
	}

	return m_unk0x18;
}

// FUNCTION: LEGORACERS 0x0047e0e0
LegoBool32 ImaginaryDrillFieldAt0x22dc::VTable0x08()
{
	if (!m_unk0x18) {
		return TRUE;
	}

	m_unk0x1c.VTable0x54();

	if (m_unk0x110) {
		m_unk0x0c->VTable0x48(m_unk0x110);
	}

	if (m_unk0x114) {
		m_unk0x0c->VTable0x4c(m_unk0x114);
	}

	return ObscureLink0x1c::VTable0x08();
}

// FUNCTION: LEGORACERS 0x0047e130
void ImaginaryDrillFieldAt0x22dc::FUN_0047e130(LegoU8 p_unk0x04)
{
	m_unk0x154.m_unk0x00 = p_unk0x04;
	m_unk0x150->FUN_0049db90(&m_unk0x154, m_unk0x110, 0);
}

// FUNCTION: LEGORACERS 0x0047e160
void ImaginaryDrillFieldAt0x22dc::FUN_0047e160(LegoU8 p_unk0x04, LegoU8 p_unk0x08)
{
	m_unk0x154.m_unk0x01 = p_unk0x04;
	m_unk0x154.m_unk0x04 = p_unk0x08;
	IGdbModel0x40* model = m_unk0x150->FUN_0049db90(&m_unk0x154, m_unk0x110, 0);
	m_unk0x150->FUN_0049dce0(model, &m_unk0x154);
}

// FUNCTION: LEGORACERS 0x0047e1b0
void ImaginaryDrillFieldAt0x22dc::FUN_0047e1b0(LegoU8 p_unk0x04)
{
	m_unk0x154.m_unk0x02 = p_unk0x04;
	m_unk0x150->FUN_0049db90(&m_unk0x154, m_unk0x110, 0);
}

// FUNCTION: LEGORACERS 0x0047e1e0
void ImaginaryDrillFieldAt0x22dc::FUN_0047e1e0(LegoU8 p_unk0x04)
{
	m_unk0x154.m_unk0x03 = p_unk0x04;
	m_unk0x150->FUN_0049db90(&m_unk0x154, m_unk0x110, 0);
}

// FUNCTION: LEGORACERS 0x0047e210
void ImaginaryDrillFieldAt0x22dc::FUN_0047e210(TurquoiseGlowColor* p_color)
{
	m_unk0x154 = *p_color;
	m_unk0x150->FUN_0049db90(&m_unk0x154, m_unk0x110, 0);
}

// FUNCTION: LEGORACERS 0x0047e250
LegoBool32 ImaginaryDrillFieldAt0x22dc::VTable0x0c()
{
	GolVec3 position;
	m_unk0x1c.VTable0x04(&position);
	m_unk0x1c.VTable0x08(position);
	m_unk0x10->VTable0x94(&m_unk0x1c);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047e290
LegoBool32 ImaginaryDrillFieldAt0x22dc::VTable0x10(undefined4 p_unk0x04)
{
	m_unk0x1c.VTable0x10(p_unk0x04);
	return TRUE;
}
