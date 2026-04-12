#include "neoncactus0x1d6c.h"

#include <string.h>

DECOMP_SIZE_ASSERT(NeonCactus0x1d6c, 0x1d6c)

// GLOBAL: LEGORACERS 0x4be8d8
const LegoChar* g_jamFile = "lego.jam";

// clang-format off
// GLOBAL: LEGORACERS 0x4be8dc
const LegoChar* g_usage = "Usage: LEGORacers [options]\n\t[options] include:\n\t\t-novideo\t:disables video playback at the beginning of game\n\t\t-window\t:runs application in a window\n\t\t-primary\t:force use of primary display device\n\t\t-select3d\t:allows user to select 3D device\n\t\t-alphatrans\t:force use of alpha transparency\n\t\t-horzres res\t:where res is the desired horizontal resolution\n\t\t-vertres res\t:where res is the desired vertical resolution\n";
// clang-format on

// FUNCTION: LEGORACERS 0x42bb40
NeonCactus0x1d6c::~NeonCactus0x1d6c()
{
	FUN_0042bc20();
}

// FUNCTION: LEGORACERS 0x42bbb0
LegoS32 NeonCactus0x1d6c::Init(LegoS32 p_argc, LegoChar** p_argv)
{
	if (m_unk0x04.GetUnk0x04() & 1) {
		FUN_0042bc20();
	}

	LegoS32 result = FUN_0042bee0(p_argc, p_argv);
	if (!result) {
		return result;
	}

	m_unk0x04.GetUnk0x7dc().VTable0x08(100, 4096);
	m_unk0x04.SetUnk0x928(m_unk0xa14);
	m_unk0x04.VTable0x0c("LEGO Racers", g_jamFile);
	return 1;
}

// FUNCTION: LEGORACERS 0x42bc20
void NeonCactus0x1d6c::FUN_0042bc20()
{
	FUN_0042bd00();
	FUN_0042be90();
	m_unk0x04.VTable0x10();
}

// STUB: LEGORACERS 0x42bc40
void NeonCactus0x1d6c::FUN_0042bc40()
{
	// TODO
	STUB(0x42bc40);
}

// STUB: LEGORACERS 0x42bd00
void NeonCactus0x1d6c::FUN_0042bd00()
{
	// TODO
	STUB(0x42bd00);
}

// FUNCTION: LEGORACERS 0x42be90
void NeonCactus0x1d6c::FUN_0042be90()
{
	m_unk0x948.VTable0x08();
	m_unk0x9e0.VTable0x08();
	m_unk0x04.VTable0x2c();
}

// STUB: LEGORACERS 0x42bee0
LegoS32 NeonCactus0x1d6c::FUN_0042bee0(LegoS32 p_argc, LegoChar** p_argv)
{
	// TODO
	STUB(0x42bee0);
	return 0;
}
