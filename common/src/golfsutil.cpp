#include "golfsutil.h"

#include "decomp.h"
#include "gol.h"
#include "golstream.h"
#include "types.h"

#if (defined(_MSC_VER) && defined(_M_X64)) || (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64)))
#include <cpuid.h>
#endif

#include <windows.h>

// GLOBAL: GOLDP 0x10065ed4
// GLOBAL: LEGORACERS 0x004c73f0
HANDLE g_hMutex;

// GLOBAL: GOLDP 0x10065ed8
BOOL g_CPUID_detected;

// GLOBAL: GOLDP 0x10065edc
LegoS32 g_maxCPUID;

// GLOBAL: GOLDP 0x10065ee0
BOOL g_CPU_supports_MMX;

// GLOBAL: GOLDP 0x10065ee4
LegoChar g_cpuManufacturer[16];

#ifdef BUILDING_LEGORACERS
// FUNCTION: LEGORACERS 0x00450d80
void CreateGolImport(GolImport* p_import)
{
	p_import->m_fileSources = g_fileSources;
	p_import->m_fileSourceCount = g_fileSourceCount;
	p_import->m_unk0x18 = g_unk0x4c739c;
	for (LegoU32 i = 0; i < p_import->m_unk0x18; i++) {
		p_import->m_unk0x8[i] = g_unk0x4c7384[i];
	}
	p_import->m_unk0x1c = g_unk0x4c73a0;
	p_import->m_mutex = g_hMutex;
}
#endif

#ifdef BUILDING_GOL

// FUNCTION: GOLDP 0x10032b80
void SetGolImport(GolImport* p_import)
{
	g_fileSourceCount = p_import->m_fileSourceCount;
	g_fileSources = p_import->m_fileSources;
	GolStream::FUN_100320d0();
	for (LegoU32 i = 0; i < p_import->m_unk0x18; i++) {
		GolStream::FUN_10032110(p_import->m_unk0x8[i]);
	}
	g_unk0x4c73a0 = p_import->m_unk0x1c;
	g_hMutex = p_import->m_mutex;
}
#endif

// FUNCTION: GOLDP 0x10032bf0
// FUNCTION: LEGORACERS 0x00450df0
void GolFsLock()
{
	if (g_hMutex) {
		WaitForSingleObject(g_hMutex, INFINITE);
	}
}

// FUNCTION: GOLDP 0x10032c10
// FUNCTION: LEGORACERS 0x00450e10
void GolFsUnlock()
{
	if (g_hMutex) {
		ReleaseMutex(g_hMutex);
	}
}
