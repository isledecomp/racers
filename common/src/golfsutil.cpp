#include "golfsutil.h"

#include "decomp.h"
#include "gol.h"
#include "types.h"

#if (defined(_MSC_VER) && defined(_M_X64)) || (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64)))
#include <cpuid.h>
#endif

#include <windows.h>

// GLOBAL: GOLDP 0x10065ed4
// GLOBAL: LEGORACERS 0x4c73f0
HANDLE g_hMutex;

// GLOBAL: GOLDP 0x10065ed8
BOOL g_CPUID_detected;

// GLOBAL: GOLDP 0x10065edc
int g_maxCPUID;

// GLOBAL: GOLDP 0x10065ee0
BOOL g_CPU_supports_MMX;

// GLOBAL: GOLDP 0x10065ee4
char g_cpuManufacturer[16];

#ifdef BUILDING_LEGORACERS
// STUB: LEGORACERS 0x00450d80
void CreateGolImport(GolImport* p_import)
{
	// TODO
	// result.m_unk0x1c = ;
	p_import->m_mutex = g_hMutex;
}
#endif

#ifdef BUILDING_GOL
// STUB: GOLDP 0x10032b80
void SetGolImport(GolImport* p_import)
{
	// TODO
	STUB(0x10032b80);
}
#endif

// FUNCTION: GOLDP 0x10032bf0
// FUNCTION: LEGORACERS 0x450df0
void GolFsLock()
{
	if (g_hMutex) {
		WaitForSingleObject(g_hMutex, INFINITE);
	}
}

// FUNCTION: GOLDP 0x10032c10
// FUNCTION: LEGORACERS 0x450e10
void GolFsUnlock()
{
	if (g_hMutex) {
		ReleaseMutex(g_hMutex);
	}
}
