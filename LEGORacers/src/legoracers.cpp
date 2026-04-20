#include "legoracers.h"

#include "amethystwake0x4dd4.h"
#include "aquacoral0x37b8.h"
#include "videoplayer.h"

#include <golerror.h>
#include <stddef.h>
#include <string.h>

DECOMP_SIZE_ASSERT(LegoRacers, 0x1d6c)

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

// GLOBAL: LEGORACERS 0x004b055c
LegoFloat g_unk0x4b055c = 65.0f;

// GLOBAL: LEGORACERS 0x004b0560
LegoFloat g_unk0x4b0560 = 5.0f;

// GLOBAL: LEGORACERS 0x004b0564
LegoFloat g_unk0x4b0564 = 800.0f;

// FUNCTION: LEGORACERS 0x0042b9d0
LegoRacers::LegoRacers() : m_unk0xa10(&m_unk0x9e0)
{
	m_golBackendType = IronFlame0x944::c_golBackendDP;
	m_cutscenes = TRUE;
	m_unk0xa1c = 0;
	m_videoFlags = 24;
	m_bpp = 16;

	memset(&m_unk0xabc, 0, sizeof(LegoRacers) - offsetof(LegoRacers, m_unk0xabc));

	m_unk0xabc = TRUE;
	m_unk0xac0 = &m_unk0x04;
	m_unk0xac4 = m_unk0xa10;
	m_unk0xac8 = g_unk0x4b055c;
	m_unk0xacc = g_unk0x4b0560;
	m_unk0xad0 = g_unk0x4b0564;
	m_unk0xae0 = 1;
	m_unk0xde8 = 1;
	m_unk0xad8 = 40;
	m_unk0xe54 = 0;
	m_unk0xaf4 = 1;
	strncpy(m_unk0xafc, "racec0r0", sizeof(m_unk0xafc));
	strncpy(m_unk0xb04, "racec0r0", sizeof(m_unk0xb04));
	strncpy(m_unk0xae9, "c0", sizeof(m_unk0xae9));
	m_unk0xad4 = 1;
}

// FUNCTION: LEGORACERS 0x0042bb40
LegoRacers::~LegoRacers()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0042bbb0
LegoS32 LegoRacers::Init(LegoS32 p_argc, LegoChar** p_argv)
{
	if (m_unk0x04.GetFlags() & CrimsonForge0x800::c_flagInitialized) {
		Destroy();
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
void LegoRacers::Destroy()
{
	FUN_0042bd00();
	Shutdown();
	m_unk0x04.Destroy();
}

// FUNCTION: LEGORACERS 0x0042bc40
void LegoRacers::Run()
{
	if (!(m_unk0x04.GetFlags() & CrimsonForge0x800::c_flagInitialized)) {
		return;
	}

	CactusInterface0x4::VTable0x00();

	if (m_cutscenes) {
		VideoPlayer::Begin(&m_unk0x04, 640, 480);
		VideoPlayer::Play(&m_unk0x04, "lmicmp.avi", FALSE, FALSE);
		VideoPlayer::Play(&m_unk0x04, "hvscmp.avi", TRUE, FALSE);
		VideoPlayer::Play(&m_unk0x04, "introcmp.avi", TRUE, FALSE);
		VideoPlayer::End(&m_unk0x04);
	}

	FUN_0042be00();

	while (m_unk0xabc) {
		FUN_0042bdc0();
		if (!m_unk0xabc) {
			break;
		}
		FUN_0042bde0();
	}

	FUN_0042bd00();
	Shutdown();
	ResetDisplay();
}

// STUB: LEGORACERS 0x0042bd00
void LegoRacers::FUN_0042bd00()
{
	// TODO
	STUB(0x42bd00);
}

// FUNCTION: LEGORACERS 0x0042bdc0
void LegoRacers::FUN_0042bdc0()
{
	AmethystWake0x4dd4::FUN_0042b1e0(&m_unk0xabc);
	m_unk0x04.FUN_00416490();
}

// FUNCTION: LEGORACERS 0x0042bde0
void LegoRacers::FUN_0042bde0()
{
	AquaCoral0x37b8::FUN_0042b130(&m_unk0xabc);
	m_unk0x04.FUN_00416490();
}

// FUNCTION: LEGORACERS 0x0042be00
void LegoRacers::FUN_0042be00()
{
	LegoS32 initDisplayResult =
		m_unk0x04.InitializeDisplay(g_horizontalResolution, g_verticalResolution, m_bpp, m_videoFlags);

	m_soundManager.FUN_00418f50(m_unk0x04.GetHwnd());

	if (m_soundManager.VTable0x04(0x20)) {
		m_unk0xa10 = &m_soundManager;
	}
	else {
		m_unk0xa10 = &m_unk0x9e0;
	}

	m_unk0xac4 = m_unk0xa10;

	if (initDisplayResult) {
		GolFatalErrorMessage("Unable to initialize display - out of video memory", NULL, 0);
	}
}

// FUNCTION: LEGORACERS 0x0042be90
void LegoRacers::Shutdown()
{
	m_soundManager.Shutdown();
	m_unk0x9e0.Shutdown();
	m_unk0x04.VTable0x2c();
}

// FUNCTION: LEGORACERS 0x0042bec0
void LegoRacers::ShowUsage()
{
	MessageBox(NULL, g_usage, "LEGO Racers Usage:", MB_ICONWARNING | MB_SETFOREGROUND | MB_TOPMOST);
}

// FUNCTION: LEGORACERS 0x0042bee0
LegoS32 LegoRacers::ParseArguments(LegoS32 p_argc, LegoChar** p_argv)
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

// FUNCTION: LEGORACERS 0x0042c1a0
LONG LegoRacers::ResetDisplay()
{
	return ChangeDisplaySettings(NULL, NULL);
}
