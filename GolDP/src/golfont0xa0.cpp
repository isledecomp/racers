#include "golfont0xa0.h"

#include "bronzefalcon0xc8770.h"
#include "decomp.h"

DECOMP_SIZE_ASSERT(GolFont0xa0, 0xa0)

// STUB: GOLDP 0x100043d0
GolFont0xa0::GolFont0xa0()
{
	// TODO
	STUB(0x100043d0);
	m_unk0x90 = NULL;
	m_unk0x9c = NULL;
	m_unk0x8c = NULL;
}

// STUB: GOLDP 0x10004480
GolFont0xa0::~GolFont0xa0()
{
	// TODO
	STUB(0x10004480);
}

// STUB: GOLDP 0x10004520
void GolFont0xa0::Clear()
{
	// TODO
	STUB(0x10004520);
}

// STUB: GOLDP 0x10004570
void GolFont0xa0::VTable0x00(undefined4, undefined4)
{
	// TODO
	STUB(0x10004570);
}

// STUB: GOLDP 0x100046e0
void GolFont0xa0::ReleaseSurfaces()
{
	// TODO
	STUB(0x100046e0);
}

// STUB: GOLDP 0x10004720
void GolFont0xa0::RefreshSurfaces(BronzeFalcon0xc8770*)
{
	// TODO
	STUB(0x10004720);
}

// STUB: GOLDP 0x100047b0
void GolFont0xa0::VTable0x04(undefined4)
{
	// TODO
	STUB(0x100047b0);
}

// STUB: GOLDP 0x10004b60
undefined4* GolFont0xa0::VTable0x08(LegoU32)
{
	// TODO
	STUB(0x10004b60);
	return NULL;
}

// FUNCTION: GOLDP 0x10004b80
void GolFont0xa0::VTable0x0c(WhiteFalcon0x140* p_renderer, undefined4)
{
	m_unk0x8c = static_cast<BronzeFalcon0xc8770*>(p_renderer);
}

// STUB: GOLDP 0x10004b90
void GolFont0xa0::VTable0x10(LegoU32)
{
	// TODO
	STUB(0x10004b90);
}

// STUB: GOLDP 0x10004c20
void GolFont0xa0::VTable0x14(undefined4, undefined4)
{
	// TODO
	STUB(0x10004c20);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolFont0xa0::VTable0x18()
{
	// empty
}
