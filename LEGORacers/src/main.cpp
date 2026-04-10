// clang-format off
#include <windows.h>
#include <mmsystem.h>
// clang-format on

#include "main.h"

#include "decomp.h"
#include "neoncactus0x1d6c.h"
#include "types.h"

#include <objbase.h>
#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(CommandLineArgs, 0x84)

// GLOBAL: LEGORACERS 0x4c47e4
HINSTANCE g_hInstance;

// GLOBAL: LEGORACERS 0x4c47e8
HINSTANCE g_hPrevInstance;

// GLOBAL: LEGORACERS 0x4c4a38
NeonCactus0x1d6c g_unk0x4c4a38;

// GLOBAL: LEGORACERS 0x4c6ee8
LegoChar g_commandLine[256];

// GLOBAL: LEGORACERS 0x4c6fe8
CommandLineArgs g_commandLineArgs;

// FUNCTION: LEGORACERS 0x42f870
LegoS32 GameMain(LegoS32 p_argc, LegoChar** p_argv)
{
	if (!g_unk0x4c4a38.FUN_0042bbb0(p_argc, p_argv)) {
		return 1;
	}

	g_unk0x4c4a38.FUN_0042bc40();
	g_unk0x4c4a38.FUN_0042bc20();
	return 0;
}

// FUNCTION: LEGORACERS 0x449ce0
void SplitCommand()
{
	LegoS32 offset = 0;
	g_commandLineArgs.m_argc = 0;

	if (!g_commandLine[0]) {
		return;
	}

	LegoS32 i;
	for (; g_commandLineArgs.m_argc < (LegoS32) sizeOfArray(g_commandLineArgs.m_argv);
		 offset += i, g_commandLineArgs.m_argc++) {
		LegoChar* arg = &g_commandLine[offset];

		for (i = 0; arg[i] && arg[i] != ' '; i++) {
		}

		g_commandLineArgs.m_argv[g_commandLineArgs.m_argc] = arg;

		if (!g_commandLine[offset + i]) {
			g_commandLineArgs.m_argc++;
			break;
		}

		arg[i++] = '\0';
	}
}

// FUNCTION: LEGORACERS 0x449d50
int WINAPI WinMain(HINSTANCE p_hInstance, HINSTANCE p_hPrevInstance, LPSTR p_lpCmdLine, int p_nShowCmd)
{
	int result;

	CoInitialize(0);
	g_hInstance = p_hInstance;
	g_hPrevInstance = p_hPrevInstance;
	srand((unsigned int) timeGetTime);
	strncpy(g_commandLine, p_lpCmdLine, sizeof(g_commandLine));
	g_commandLine[sizeof(g_commandLine) - 1] = '\0';
	SplitCommand();
	result = GameMain(g_commandLineArgs.m_argc, g_commandLineArgs.m_argv);
	CoUninitialize();

	return result;
}
