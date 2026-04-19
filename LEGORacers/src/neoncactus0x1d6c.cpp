#include "neoncactus0x1d6c.h"

#include <string.h>

DECOMP_SIZE_ASSERT(NeonCactus0x1d6c, 0x1d6c)

// GLOBAL: LEGORACERS 0x004be8d8
const LegoChar* g_jamFile = "lego.jam";

// clang-format off
// GLOBAL: LEGORACERS 0x004be8dc
const LegoChar* g_usage = "Usage: LEGORacers [options]\n\t[options] include:\n\t\t-novideo\t:disables video playback at the beginning of game\n\t\t-window\t:runs application in a window\n\t\t-primary\t:force use of primary display device\n\t\t-select3d\t:allows user to select 3D device\n\t\t-alphatrans\t:force use of alpha transparency\n\t\t-horzres res\t:where res is the desired horizontal resolution\n\t\t-vertres res\t:where res is the desired vertical resolution\n";
// clang-format on

// GLOBAL: LEGORACERS 0x004be8e0
LegoS32 g_horizontalResolution = 640;

// GLOBAL: LEGORACERS 0x004be8e4
LegoS32 g_verticalResolution = 480;

// FUNCTION: LEGORACERS 0x0042bb40
NeonCactus0x1d6c::~NeonCactus0x1d6c()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0042bbb0
LegoS32 NeonCactus0x1d6c::Init(LegoS32 p_argc, LegoChar** p_argv)
{
	if (m_unk0x04.GetFlags() & CrimsonForge0x800::c_flagInitialized) {
		Shutdown();
	}

	LegoS32 result = ParseArguments(p_argc, p_argv);
	if (!result) {
		return result;
	}

	m_unk0x04.GetHashTable().Init(100, 4096);
	m_unk0x04.SetGolBackendType(m_golBackendType);
	m_unk0x04.Init("LEGO Racers", g_jamFile);
	return 1;
}

// FUNCTION: LEGORACERS 0x0042bc20
void NeonCactus0x1d6c::Shutdown()
{
	FUN_0042bd00();
	FUN_0042be90();
	m_unk0x04.Destroy();
}

// STUB: LEGORACERS 0x0042bc40
void NeonCactus0x1d6c::FUN_0042bc40()
{
	// TODO
	STUB(0x42bc40);
}

// STUB: LEGORACERS 0x0042bd00
void NeonCactus0x1d6c::FUN_0042bd00()
{
	// TODO
	STUB(0x42bd00);
}

// FUNCTION: LEGORACERS 0x0042be90
void NeonCactus0x1d6c::FUN_0042be90()
{
	m_soundManager.Shutdown();
	m_unk0x9e0.Shutdown();
	m_unk0x04.VTable0x2c();
}

// FUNCTION: LEGORACERS 0x0042bec0
void NeonCactus0x1d6c::ShowUsage()
{
	MessageBox(NULL, g_usage, "LEGO Racers Usage:", MB_ICONWARNING | MB_SETFOREGROUND | MB_TOPMOST);
}

// FUNCTION: LEGORACERS 0x0042bee0
LegoS32 NeonCactus0x1d6c::ParseArguments(LegoS32 p_argc, LegoChar** p_argv)
{
	if (p_argc < 1) {
		return 1;
	}

	for (LegoS32 i = 0; i < p_argc; i++) {
		if (strcmp(p_argv[i], "-novideo") == 0) {
			m_cutscenes = 0;
		}
		else if (strcmp(p_argv[i], "-primary") == 0) {
			m_videoFlags |= c_videoPrimaryDriver;
		}
		else if (strcmp(p_argv[i], "-select3d") == 0) {
			m_videoFlags |= c_videoSelect3D;
		}
		else if (strcmp(p_argv[i], "-window") == 0) {
			m_videoFlags &= ~c_videoFullScreen;
		}
		else if (strcmp(p_argv[i], "-alphatrans") == 0) {
			m_videoFlags |= c_videoAlphaTrans;
		}
		else if (strcmp(p_argv[i], "-horzres") == 0) {
			if (i + 1 >= p_argc) {
				ShowUsage();
				return 0;
			}
			++i;
			g_horizontalResolution = atoi(p_argv[i]);
		}
		else if (strcmp(p_argv[i], "-vertres") == 0) {
			if (i + 1 >= p_argc) {
				ShowUsage();
				return 0;
			}
			++i;
			g_verticalResolution = atoi(p_argv[i]);
		}
		else {
			ShowUsage();
			return 0;
		}
	}

	return 1;
}
