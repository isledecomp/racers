// clang-format off
#include <windows.h>
#include <mmsystem.h>
// clang-format on

#include "types.h"

#include <objbase.h>
#include <stdlib.h>
#include <string.h>

// GLOBAL: LEGORACERS 0x4c47e4
HINSTANCE g_hInstance;

// GLOBAL: LEGORACERS 0x4c47e8
HINSTANCE g_hPrevInstance;

// GLOBAL: LEGORACERS 0x4c6ee8
LegoChar g_commandLine[256];

// GLOBAL: LEGORACERS 0x4c6fe8
LegoS32 g_unk0x4c6fe8;

// GLOBAL: LEGORACERS 0x4c6fec
LegoChar* g_unk0x4c6fec[32];

// STUB: LEGORACERS 0x42f870
LegoS32 FUN_0042f870(LegoS32 p_a1, LegoS32 p_a2)
{
	// TODO
	return 0;
}

// STUB: LEGORACERS 0x449ce0
LegoS8 FUN_00449ce0()
{
	// TODO
	return 0;
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
	FUN_00449ce0();
	result = FUN_0042f870(g_unk0x4c6fe8, (int) g_unk0x4c6fec);
	CoUninitialize();

	return result;
}
