#include "legoracers.h"

#include "aquacoral0x37b8.h"
#include "menumanager.h"
#include "videoplayer.h"

#include <golerror.h>
#include <string.h>

DECOMP_SIZE_ASSERT(LegoRacers, 0x1d6c)
DECOMP_SIZE_ASSERT(LegoRacers::Context, 0x12b0)
DECOMP_SIZE_ASSERT(LegoRacers::RaceSlot, 0x18)
DECOMP_SIZE_ASSERT(LegoRacers::Context::SaveRecord, 0x22d)
DECOMP_SIZE_ASSERT(LegoRacers::Context::SaveState, 0x42c)

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
LegoRacers::LegoRacers() : m_soundManager(&m_nullSoundManager)
{
	m_golBackendType = Win32GolApp::c_golBackendDP;
	m_cutscenes = TRUE;
	m_unk0xa1c = 0;
	m_videoFlags = c_videoFullScreen | c_videoBit4;
	m_bpp = 16;

	memset(&m_context, 0, sizeof(m_context));

	m_context.m_unk0x00 = TRUE;
	m_context.m_golApp = &m_golApp;
	m_context.m_soundManager = m_soundManager;
	m_context.m_unk0x0c = g_unk0x4b055c;
	m_context.m_unk0x10 = g_unk0x4b0560;
	m_context.m_unk0x14 = g_unk0x4b0564;
	m_context.m_unk0x24 = 1;
	m_context.m_unk0x32c = 1;
	m_context.m_unk0x1c = 40;
	m_context.m_unk0x398 = 0;
	m_context.m_raceSlots[0].m_unk0x00 = 1;
	strncpy(m_context.m_raceSlots[0].m_unk0x08, "racec0r0", sizeof(m_context.m_raceSlots[0].m_unk0x08));
	strncpy(m_context.m_raceSlots[0].m_raceName, "racec0r0", sizeof(m_context.m_raceSlots[0].m_raceName));
	strncpy(m_context.m_unk0x2d, "c0", sizeof(m_context.m_unk0x2d));
	m_context.m_unk0x18 = 1;
}

// FUNCTION: LEGORACERS 0x0042bb40
LegoRacers::~LegoRacers()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0042bbb0
LegoS32 LegoRacers::Init(LegoS32 p_argc, LegoChar** p_argv)
{
	if (m_golApp.GetFlags() & GolApp::c_flagInitialized) {
		Destroy();
	}

	LegoS32 result = ParseArguments(p_argc, p_argv);
	if (!result) {
		return result;
	}

	m_golApp.GetHashTable().Init(100, 4096);
	m_golApp.SetGolBackendType(m_golBackendType);
	m_golApp.Init("LEGO Racers", g_jamFile);
	return 1;
}

// FUNCTION: LEGORACERS 0x0042bc20
void LegoRacers::Destroy()
{
	FUN_0042bd00();
	Shutdown();
	m_golApp.Destroy();
}

// FUNCTION: LEGORACERS 0x0042bc40
void LegoRacers::Run()
{
	if (!(m_golApp.GetFlags() & GolApp::c_flagInitialized)) {
		return;
	}

	CactusInterface0x4::VTable0x00();

	if (m_cutscenes) {
		VideoPlayer::Begin(&m_golApp, 640, 480);
		VideoPlayer::Play(&m_golApp, "lmicmp.avi", FALSE, FALSE);
		VideoPlayer::Play(&m_golApp, "hvscmp.avi", TRUE, FALSE);
		VideoPlayer::Play(&m_golApp, "introcmp.avi", TRUE, FALSE);
		VideoPlayer::End(&m_golApp);
	}

	FUN_0042be00();

	while (m_context.m_unk0x00) {
		FUN_0042bdc0();
		if (!m_context.m_unk0x00) {
			break;
		}
		FUN_0042bde0();
	}

	FUN_0042bd00();
	Shutdown();
	ResetDisplay();
}

// FUNCTION: LEGORACERS 0x0042bd00
void LegoRacers::FUN_0042bd00()
{
	GolExport* golExport = m_context.m_golApp->GetGolExport();

	for (LegoU32 i = 0; i < m_context.m_unk0x32c; i++) {
		ScarletNova0x5c& slot = m_context.m_unk0x108[i];

		if (slot.m_flag) {
			if (slot.m_unk0x20[0]) {
				golExport->VTable0x48(slot.m_unk0x20[0]);
				slot.m_unk0x20[0] = NULL;
			}
			if (slot.m_unk0x20[1]) {
				golExport->VTable0x44(slot.m_unk0x20[1]);
				slot.m_unk0x20[1] = NULL;
			}
			if (slot.m_unk0x20[2]) {
				golExport->VTable0x40(slot.m_unk0x20[2]);
				slot.m_unk0x20[2] = NULL;
			}
			if (slot.m_unk0x20[9]) {
				golExport->VTable0x48(slot.m_unk0x20[9]);
				slot.m_unk0x20[9] = NULL;
			}
			if (slot.m_unk0x20[10]) {
				golExport->VTable0x44(slot.m_unk0x20[10]);
				slot.m_unk0x20[10] = NULL;
			}
			if (slot.m_unk0x20[11]) {
				golExport->VTable0x40(slot.m_unk0x20[11]);
				slot.m_unk0x20[11] = NULL;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0042bdc0
void LegoRacers::FUN_0042bdc0()
{
	MenuManager::Run(&m_context);
	m_golApp.ClearFileSourceDirectoryCaches();
}

// FUNCTION: LEGORACERS 0x0042bde0
void LegoRacers::FUN_0042bde0()
{
	AquaCoral0x37b8::FUN_0042b130(&m_context);
	m_golApp.ClearFileSourceDirectoryCaches();
}

// FUNCTION: LEGORACERS 0x0042be00
void LegoRacers::FUN_0042be00()
{
	LegoS32 initDisplayResult =
		m_golApp.InitializeDisplay(g_horizontalResolution, g_verticalResolution, m_bpp, m_videoFlags);

	m_directSoundManager.SetCooperativeWindow(m_golApp.GetHwnd());

	if (m_directSoundManager.Initialize(DirectSoundManager::c_defaultActiveSoundCount)) {
		m_soundManager = &m_directSoundManager;
	}
	else {
		m_soundManager = &m_nullSoundManager;
	}

	m_context.m_soundManager = m_soundManager;

	if (initDisplayResult) {
		GolFatalErrorMessage("Unable to initialize display - out of video memory", NULL, 0);
	}
}

// FUNCTION: LEGORACERS 0x0042be90
void LegoRacers::Shutdown()
{
	m_directSoundManager.Shutdown();
	m_nullSoundManager.Shutdown();
	m_golApp.ShutdownDisplay();
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
			m_cutscenes = FALSE;
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
	return ChangeDisplaySettings(NULL, 0);
}
