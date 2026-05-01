#include "chromespike0x4.h"

#include "golerror.h"
#include "imaginarybandsaw0x2228.h"
#include "imaginarydrill0x2450.h"
#include "imaginaryfeather0x658.h"
#include "imaginaryhammer0x658.h"
#include "imaginaryruler0x2e60.h"
#include "imaginarywrench0x23bc.h"

DECOMP_SIZE_ASSERT(ChromeSpike0x4, 0x4)

// STUB: LEGORACERS 0x0047f4c0
ChromeSpike0x4::~ChromeSpike0x4()
{
	// TODO
	STUB(0x47f4c0);
}

// STUB: LEGORACERS 0x0047f4d0
LegoBool32 ChromeSpike0x4::FUN_0047f4d0()
{
	// TODO
	STUB(0x47f4d0);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047f4e0
ImaginaryTool0x368* ChromeSpike0x4::FUN_0047f4e0(undefined4 p_param)
{
	ImaginaryTool0x368* tool;
	switch (p_param) {
	case 0x01:
	case 0x27:
	case 0x28:
	case 0x29:
		tool = new ImaginaryHammer0x658();
		break;

	case 0x26:
		tool = new ImaginaryFeather0x658();
		break;

	case 0x02:
		tool = new ImaginaryDrill0x2450();
		break;

	case 0x05:
		tool = new ImaginaryBandsaw0x2228();
		break;

	case 0x1d:
	case 0x06:
		tool = new ImaginaryRuler0x2e60();
		break;

	case 0x10:
		tool = new ImaginaryWrench0x23bc();
		break;
	}

	if (!tool) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return tool;
}

// STUB: LEGORACERS 0x0049eb10
ChromeSpike0x4::ChromeSpike0x4()
{
	MATCHING(0x49eb10);
}
