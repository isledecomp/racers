#include "types.h"
#include "velvetthunder0xc8ac8.h"

#include <windows.h>

// GLOBAL: GOLDP 0x10063148
VelvetThunder0xc8ac8* g_unk0x10063148;

// STUB: GOLDP 0x10006ff0
LegoS32* GolEntry(LegoS32*)
{
	// TODO
	return 0;
}

// FUNCTION: GOLDP 0x100070b0
void GolExit()
{
	if (g_unk0x10063148) {
		delete g_unk0x10063148;
	}

	g_unk0x10063148 = NULL;
}

// This function only seems to match with /O1 (minimize size)
// FUNCTION: GOLDP 0x100502e3
#pragma optimize("s", on)
BOOL WINAPI DllMain(HINSTANCE p_hinstDLL, DWORD p_fdwReason, LPVOID p_lpvReserved)
{
	return TRUE;
}
#pragma optimize("", on)
