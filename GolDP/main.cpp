#include "types.h"
#include "unk0x10056440.h"

#include <windows.h>

// GLOBAL: GOLDP 0x10063148
Unk0x10056440* g_unk0x10063148;

// STUB: GOLDP 0x10006ff0
LegoS32* GolEntry(LegoS32* p_a1)
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
