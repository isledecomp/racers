#include "chromespike0x4.h"

#include "golerror.h"
#include "imaginaryaxe0x36c4.h"
#include "imaginarybandsaw0x2228.h"
#include "imaginarybelt0x2548.h"
#include "imaginarybolt0x4774.h"
#include "imaginarybrush0x6410.h"
#include "imaginaryclaw0x15ec.h"
#include "imaginarycrowbar0x6750.h"
#include "imaginarycube0x3c34.h"
#include "imaginarydrill0x2450.h"
#include "imaginaryfeather0x658.h"
#include "imaginarygear0x4c8c.h"
#include "imaginaryhammer0x658.h"
#include "imaginarylever0x1d7c.h"
#include "imaginaryorb0x7b0.h"
#include "imaginaryplate0x770.h"
#include "imaginaryring0x3360.h"
#include "imaginaryruler0x2e60.h"
#include "imaginaryspool0x2cc4.h"
#include "imaginaryspring0x658.h"
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
ImaginaryTool0x368* ChromeSpike0x4::FUN_0047f4e0(undefined2 p_param)
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

	case 0x03:
		tool = new ImaginaryBrush0x6410();
		break;

	case 0x10:
		tool = new ImaginaryWrench0x23bc();
		break;

	case 0x11:
		tool = new ImaginaryAxe0x36c4();
		break;

	case 0x0f:
		tool = new ImaginaryBolt0x4774();
		break;

	case 0x08:
		tool = new ImaginaryCrowbar0x6750();
		break;

	case 0x0a:
	case 0x0b:
		tool = new ImaginaryRing0x3360();
		break;

	case 0x0c:
		tool = new ImaginaryBelt0x2548();
		break;

	case 0x13:
	case 0x14:
	case 0x15:
		tool = new ImaginaryGear0x4c8c();
		break;

	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1a:
	case 0x1b:
	case 0x1c:
	case 0x25:
		tool = new ImaginaryOrb0x7b0();
		break;

	case 0x1f:
	case 0x20:
	case 0x21:
	case 0x22:
	case 0x23:
	case 0x24:
		tool = new ImaginarySpring0x658();
		break;

	case 0x0e:
		tool = new ImaginaryCube0x3c34();
		break;

	case 0x1e:
		tool = new ImaginarySpool0x2cc4();
		break;

	case 0x2c:
		tool = new ImaginaryClaw0x15ec();
		break;

	case 0x2d:
	case 0x2e:
	case 0x2f:
	case 0x30:
	case 0x31:
		tool = new ImaginaryLever0x1d7c();
		break;

	case 0x90:
		tool = new ImaginaryPlate0x770();
		break;

	default:
		tool = NULL;
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
