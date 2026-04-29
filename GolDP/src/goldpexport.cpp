#include "goldpexport.h"

#include "amberlens0x344.h"
#include "awakekite0x20.h"
#include "floatybarge0x4c.h"
#include "fluffygloomkins0x118.h"
#include "golerror.h"
#include "types.h"

DECOMP_SIZE_ASSERT(GolExport, 0x4)
DECOMP_SIZE_ASSERT(GolDPExport, 0xc8ac8)

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 GolDPExport::VTable0x24()
{
	MATCHING(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x10007060
GolDPExport::~GolDPExport()
{
}

// FUNCTION: GOLDP 0x10015090
GolDrawState* GolDPExport::VTable0x04()
{
	return &this->m_state;
}

// FUNCTION: GOLDP 0x100150a0
ZoweeBlubberworth0xf0* GolDPExport::VTable0x08()
{
	ZoweeBlubberworth0xf0* obj = new FluffyGloomkins0x118;

	if (obj == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return obj;
}

// STUB: GOLDP 0x10015110
undefined4* GolDPExport::VTable0x0c()
{
	// TODO
	STUB(0x10015110);
	return NULL;
}

// STUB: GOLDP 0x10015180
undefined4* GolDPExport::VTable0x10()
{
	// TODO
	STUB(0x10015180);
	return NULL;
}

// STUB: GOLDP 0x100151f0
undefined4* GolDPExport::VTable0x14()
{
	// TODO
	STUB(0x100151f0);
	return NULL;
}

// STUB: GOLDP 0x10015260
undefined4* GolDPExport::VTable0x18()
{
	// TODO
	STUB(0x10015260);
	return NULL;
}

// STUB: GOLDP 0x100152d0
undefined4* GolDPExport::VTable0x1c()
{
	// TODO
	STUB(0x100152d0);
	return NULL;
}

// FUNCTION: GOLDP 0x10015340
AmberLens0x344* GolDPExport::VTable0x20()
{
	AmberLens0x344* result = new AmberLens0x344;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return result;
}

// FUNCTION: GOLDP 0x100153b0
WhiteBaffoon0x50* GolDPExport::VTable0x28()
{
	UtopianPan0xa4* result = new UtopianPan0xa4;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return result;
}

// STUB: GOLDP 0x10015420
undefined4* GolDPExport::VTable0x2c()
{
	// TODO
	STUB(0x10015420);
	return NULL;
}

// FUNCTION: GOLDP 0x10015490
FloatyBoat0x28* GolDPExport::VTable0x30()
{
	FloatyBoat0x28* result = new FloatyBarge0x4c;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return result;
}

// FUNCTION: GOLDP 0x10015500
AwakeKite0x20* GolDPExport::VTable0x34()
{
	AwakeKite0x20* result = new AwakeKite0x20;
	if (result == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	return result;
}

// STUB: GOLDP 0x10015570
SmallCocoon0xc* GolDPExport::VTable0x38()
{
	// TODO
	STUB(0x10015570);
	return NULL;
}

// STUB: GOLDP 0x100155e0
void GolDPExport::VTable0x3c(undefined4*)
{
	// TODO
	STUB(0x100155e0);
}

// STUB: GOLDP 0x10015600 FOLDED
void GolDPExport::VTable0x40(undefined4*)
{
	// TODO
	STUB(0x10015600);
}

// STUB: GOLDP 0x10015600 FOLDED
void GolDPExport::VTable0x44(undefined4*)
{
	// TODO
	STUB(0x10015600);
}

// STUB: GOLDP 0x10015620
void GolDPExport::VTable0x48(undefined4*)
{
	// TODO
	STUB(0x10015620);
}

// STUB: GOLDP 0x10015600 FOLDED
void GolDPExport::VTable0x4c(undefined4*)
{
	// TODO
	STUB(0x10015600);
}

// STUB: GOLDP 0x10015600 FOLDED
void GolDPExport::VTable0x50(undefined4*)
{
	// TODO
	STUB(0x10015600);
}

// STUB: GOLDP 0x10015640
void GolDPExport::VTable0x54(undefined4*)
{
	// TODO
	STUB(0x10015640);
}

// STUB: GOLDP 0x10015660
void GolDPExport::VTable0x5c(undefined4*)
{
	// TODO
	STUB(0x10015660);
}

// STUB: GOLDP 0x10015680
void GolDPExport::VTable0x60(undefined4*)
{
	// TODO
	STUB(0x10015680);
}

// STUB: GOLDP 0x100156a0
void GolDPExport::VTable0x64(undefined4*)
{
	// TODO
	STUB(0x100156a0);
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GolDPExport::VTable0x58(undefined4*)
{
}

// STUB: GOLDP 0x10015600 FOLDED
void GolDPExport::VTable0x68(AwakeKite0x20*)
{
	// TODO
	STUB(0x10015600);
}

// STUB: GOLDP 0x10015600 FOLDED
void GolDPExport::VTable0x6c(SmallCocoon0xc*)
{
	// TODO
	STUB(0x10015600);
}
