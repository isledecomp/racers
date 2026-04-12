#include "adapter.h"
#include "gol.h"
#include "goldpexport.h"
#include "types.h"

#include <windows.h>

// GLOBAL: GOLDP 0x10063148
GolDPExport* g_golDPExport;

// GLOBAL: GOLDP 0x1006314c
FatalErrorCBFN* g_fatalError;

// FUNCTION: GOLDP 0x10006ff0
GolExport* GolEntry(GolImport* p_import)
{
	SetGolImport(p_import);
	g_fatalError = p_import->m_fatalError;
	g_golDPExport = new GolDPExport;
	return g_golDPExport;
}

// FUNCTION: GOLDP 0x100070b0
void GolExit()
{
	if (g_golDPExport) {
		delete g_golDPExport;
	}

	g_golDPExport = NULL;
}

// This function only seems to match with /O1 (minimize size)
// FUNCTION: GOLDP 0x100502e3
#pragma optimize("s", on)
BOOL WINAPI DllMain(HINSTANCE p_hinstDLL, DWORD p_fdwReason, LPVOID p_lpvReserved)
{
	return TRUE;
}
#pragma optimize("", on)
