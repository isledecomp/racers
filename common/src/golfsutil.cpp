#include "golfsutil.h"

#include "decomp.h"
#include "types.h"

#include <windows.h>

// GLOBAL: LEGORACERS 0x4c73f0
HANDLE g_hMutex;

// STUB: LEGORACERS 0x450d80
void FUN_00450d80(undefined4*)
{
	// TODO: save file system globals to struct
	STUB(0x450d80);
}

// FUNCTION: LEGORACERS 0x450df0
void GolFsLock()
{
	if (g_hMutex) {
		WaitForSingleObject(g_hMutex, INFINITE);
	}
}

// FUNCTION: LEGORACERS 0x450e10
void GolFsUnlock()
{
	if (g_hMutex) {
		ReleaseMutex(g_hMutex);
	}
}
