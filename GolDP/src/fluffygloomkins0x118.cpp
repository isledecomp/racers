#include "fluffygloomkins0x118.h"

#include "amberhaze0x20.h"
#include "amberlens0x344.h"
#include "boundingshape0x2c.h"
#include "cmbmodelpart0x34.h"
#include "floatybarge0x4c.h"
#include "gdbmodel0x48.h"
#include "golerror.h"
#include "greyfalconnode0x1c.h"
#include "mabmaterialanimation0x14.h"
#include "purpleribbon0x24.h"
#include "shadowwolf0xc.h"

DECOMP_SIZE_ASSERT(FluffyGloomkins0x118, 0x118)

// FUNCTION: GOLDP 0x10017190
FluffyGloomkins0x118::FluffyGloomkins0x118()
{
	m_unk0xf0 = NULL;
	m_unk0xf4 = NULL;
	m_unk0x10c = NULL;
	m_unk0xf8 = NULL;
	m_unk0x104 = NULL;
	m_unk0xfc = NULL;
	m_unk0x110 = NULL;
	m_unk0x100 = NULL;
	m_unk0x108 = NULL;
	m_unk0x114 = NULL;
}

// FUNCTION: GOLDP 0x10017200
FluffyGloomkins0x118::~FluffyGloomkins0x118()
{
	VTable0x18();
}

// FUNCTION: GOLDP 0x10017250
MagentaRibbon0x20* FluffyGloomkins0x118::VTable0x2c(LegoU32 p_index) const
{
	return &m_unk0xf0[p_index];
}

// FUNCTION: GOLDP 0x10017270
AmberHaze0x1c* FluffyGloomkins0x118::VTable0x30(LegoU32 p_index) const
{
	return &m_unk0xf4[p_index];
}

// FUNCTION: GOLDP 0x10017290
CmbModelPart0x34* FluffyGloomkins0x118::VTable0x34(LegoU32 p_index) const
{
	return &m_unk0x10c[p_index];
}

// FUNCTION: GOLDP 0x100172b0
IGdbModel0x40* FluffyGloomkins0x118::VTable0x38(LegoU32 p_index) const
{
	return &m_unk0xf8[p_index];
}

// FUNCTION: GOLDP 0x100172d0
ShadowWolf0xc* FluffyGloomkins0x118::VTable0x3c(LegoU32 p_index) const
{
	return &m_unk0x104[p_index];
}

// FUNCTION: GOLDP 0x100172f0
WhiteFalconNode0x18* FluffyGloomkins0x118::VTable0x40(LegoU32 p_index) const
{
	return &m_unk0xfc[p_index];
}

// FUNCTION: GOLDP 0x10017310
BoundingShape0x2c* FluffyGloomkins0x118::VTable0x44(LegoU32 p_index) const
{
	return &m_unk0x110[p_index];
}

// FUNCTION: GOLDP 0x10017330
FloatyBoat0x28* FluffyGloomkins0x118::VTable0x48(LegoU32 p_index) const
{
	return &m_unk0x100[p_index];
}

// FUNCTION: GOLDP 0x10017350
MabMaterialAnimation0x14* FluffyGloomkins0x118::VTable0x4c(LegoU32 p_index) const
{
	return &m_unk0x108[p_index];
}

// FUNCTION: GOLDP 0x10017370
AmberLensBase0x120* FluffyGloomkins0x118::VTable0x50(LegoU32 p_index) const
{
	return &m_unk0x114[p_index];
}

// FUNCTION: GOLDP 0x10017390
void FluffyGloomkins0x118::VTable0x08()
{
	if (GetUnk0x0c() != 0) {
		m_unk0xf0 = new PurpleRibbon0x24[GetUnk0x0c()];
		if (m_unk0xf0 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x14() != 0) {
		m_unk0xf4 = new AmberHaze0x20[GetUnk0x14()];
		if (m_unk0xf4 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x1c() != 0) {
		m_unk0x10c = new CmbModelPart0x34[GetUnk0x1c()];
		if (m_unk0x10c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x24() != 0) {
		m_unk0xf8 = new GdbModel0x48[GetUnk0x24()];
		if (m_unk0xf8 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x2c() != 0) {
		m_unk0x104 = new ShadowWolf0xc[GetUnk0x2c()];
		if (m_unk0x104 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x34() != 0) {
		m_unk0xfc = new GreyFalconNode0x1c[GetUnk0x34()];
		if (m_unk0xfc == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x3c() != 0) {
		m_unk0x110 = new BoundingShape0x2c[GetUnk0x3c()];
		if (m_unk0x110 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x6c() != 0) {
		m_unk0x100 = new FloatyBarge0x4c[GetUnk0x6c()];
		if (m_unk0x100 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x74() != 0) {
		m_unk0x108 = new MabMaterialAnimation0x14[GetUnk0x74()];
		if (m_unk0x108 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetUnk0x7c()) {
		m_unk0x114 = new AmberLens0x344[GetUnk0x7c()];
		if (m_unk0x114 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// STUB: GOLDP 0x10017ac0
undefined4* FluffyGloomkins0x118::VTable0x0c()
{
	// TODO
	STUB(0x10017ac0);
	return NULL;
}

// FUNCTION: GOLDP 0x100180a0
void FluffyGloomkins0x118::VTable0x18()
{
	if (m_unk0x114) {
		delete[] m_unk0x114;
		m_unk0x114 = NULL;
	}
	if (m_unk0x100) {
		delete[] m_unk0x100;
		m_unk0x100 = NULL;
	}
	if (m_unk0x110) {
		delete[] m_unk0x110;
		m_unk0x110 = NULL;
	}
	if (m_unk0xfc) {
		delete[] m_unk0xfc;
		m_unk0xfc = NULL;
	}
	if (m_unk0x104) {
		delete[] m_unk0x104;
		m_unk0x104 = NULL;
	}
	if (m_unk0xf8) {
		delete[] m_unk0xf8;
		m_unk0xf8 = NULL;
	}
	if (m_unk0x10c) {
		delete[] m_unk0x10c;
		m_unk0x10c = NULL;
	}
	if (m_unk0xf4) {
		delete[] m_unk0xf4;
		m_unk0xf4 = NULL;
	}
	if (m_unk0xf0) {
		delete[] m_unk0xf0;
		m_unk0xf0 = NULL;
	}
	if (m_unk0x108) {
		delete[] m_unk0x108;
		m_unk0x108 = NULL;
	}

	ZoweeBlubberworth0xf0::VTable0x18();
}

// STUB: GOLDP 0x100181b0
void FluffyGloomkins0x118::VTable0x1c(undefined4*)
{
	// TODO
	STUB(0x100181b0);
}

// STUB: GOLDP 0x100181f0
void FluffyGloomkins0x118::VTable0x20(undefined4)
{
	// TODO
	STUB(0x100181f0);
}

// STUB: GOLDP 0x10018230
void FluffyGloomkins0x118::VTable0x24(undefined4)
{
	// TODO
	STUB(0x10018230);
}

// STUB: GOLDP 0x10018270
void FluffyGloomkins0x118::VTable0x28(undefined4*)
{
	// TODO
	STUB(0x10018270);
}
