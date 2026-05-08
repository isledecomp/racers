#include "fluffygloomkins0x118.h"

#include "amberhaze0x20.h"
#include "amberlens0x344.h"
#include "boundingshape0x2c.h"
#include "golerror.h"
#include "purpleribbon0x24.h"

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

// STUB: GOLDP 0x10017250
undefined4* FluffyGloomkins0x118::VTable0x2c(undefined4)
{
	// TODO
	STUB(0x10017250);
	return NULL;
}

// STUB: GOLDP 0x10017270
undefined4* FluffyGloomkins0x118::VTable0x30(undefined4)
{
	// TODO
	STUB(0x10017270);
	return NULL;
}

// STUB: GOLDP 0x10017290
undefined4* FluffyGloomkins0x118::VTable0x34(undefined4)
{
	// TODO
	STUB(0x10017290);
	return NULL;
}

// STUB: GOLDP 0x100172b0
undefined4* FluffyGloomkins0x118::VTable0x38(undefined4)
{
	// TODO
	STUB(0x100172b0);
	return NULL;
}

// STUB: GOLDP 0x100172d0
undefined4* FluffyGloomkins0x118::VTable0x3c(undefined4)
{
	// TODO
	STUB(0x100172d0);
	return NULL;
}

// STUB: GOLDP 0x100172f0
undefined4* FluffyGloomkins0x118::VTable0x40(undefined4)
{
	// TODO
	STUB(0x100172f0);
	return NULL;
}

// STUB: GOLDP 0x10017310
undefined4* FluffyGloomkins0x118::VTable0x44(undefined4)
{
	// TODO
	STUB(0x10017310);
	return NULL;
}

// STUB: GOLDP 0x10017330
undefined4* FluffyGloomkins0x118::VTable0x48(undefined4)
{
	// TODO
	STUB(0x10017330);
	return NULL;
}

// STUB: GOLDP 0x10017350
undefined4* FluffyGloomkins0x118::VTable0x4c(undefined4)
{
	// TODO
	STUB(0x10017350);
	return NULL;
}

// STUB: GOLDP 0x10017370
undefined4* FluffyGloomkins0x118::VTable0x50(undefined4)
{
	// TODO
	STUB(0x10017370);
	return NULL;
}

// STUB: GOLDP 0x10017390
undefined4* FluffyGloomkins0x118::VTable0x08()
{
	// ...

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

	// ...

	if (GetUnk0x3c() != 0) {
		m_unk0x110 = new BoundingShape0x2c[GetUnk0x3c()];
		if (m_unk0x110 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	// ...

	if (GetUnk0x7c()) {
		m_unk0x114 = new AmberLens0x344[GetUnk0x7c()];
		if (m_unk0x114 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
	// TODO
	STUB(0x10017390);
	return NULL;
}

// STUB: GOLDP 0x10017ac0
undefined4* FluffyGloomkins0x118::VTable0x0c()
{
	// TODO
	STUB(0x10017ac0);
	return NULL;
}

// STUB: GOLDP 0x100180a0
void FluffyGloomkins0x118::VTable0x18()
{
	if (m_unk0x114) {
		delete[] m_unk0x114;
		m_unk0x114 = NULL;
	}
	STUB(0x100180a0);
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
