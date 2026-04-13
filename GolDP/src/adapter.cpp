#include "gol.h"

#include <windows.h>

#if (defined(_MSC_VER) && defined(_M_X64)) || (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64)))
#include <cpuid.h>
#endif

// #ifdef _MSC_VER
// #if _MSC_VER < 1300
// #define cpuid __emit 0x0f __emit 0xa2
// #endif
// #endif

// GLOBAL: GOLDP 0x10065ed4
HANDLE g_globalMutex;

// GLOBAL: GOLDP 0x10065ed8
BOOL g_CPUID_detected;

// GLOBAL: GOLDP 0x10065edc
int g_maxCPUID;

// GLOBAL: GOLDP 0x10065ee0
BOOL g_CPU_supports_MMX;

// GLOBAL: GOLDP 0x10065ee4
char g_cpuManufacturer[16];

// STUB: GOLDP 0x10032b80
void SetGolImport(GolImport* p_import)
{
	// TODO
	STUB(0x10032b80);
}

// FUNCTION: GOLDP 0x10032bf0
void LockGlobalMutex()
{
	if (g_globalMutex != NULL) {
		WaitForSingleObject(g_globalMutex, INFINITE);
	}
}

// FUNCTION: GOLDP 0x10032c10
void ReleaseGlobalMutex()
{
	if (g_globalMutex != NULL) {
		ReleaseMutex(g_globalMutex);
	}
}

#if defined(_MSC_VER) && defined(_M_IX86)
#define NAKED __declspec(naked)
#else
#define NAKED
#endif

// FUNCTION: GOLDP 0x10032c30
NAKED void DetectCPU()
{
#ifdef _MSC_VER
#ifdef _M_IX86
	__asm {
		push			ebx									; Save ebx register (eax, ecx, edx are caller saved)
		pushfd												; Push EFLAGS register on the stack
		pop				eax									; EAX = EFLAGS value
		mov 			edx, eax							; EDX = EAX = EFLAGS value
		xor 			eax, 0x200000						; EDX = EFLAGS value, EAX = EFLAGS ^ 0x200000
		push			eax									; Push modified EFLAGS value to the stack
		popfd												; Set the EFLAGS register to the modified value
		pushfd												; Push EFLAGS regsiter on the stack (again)
		pop eax												; EAX = current EFLAGS value; EDX = previous EFLAGS value
		cmp eax,		edx									; Compre current and modified EFLAGS value
		jz no_cpuid											; If they are identical, then the CPU does not support CPUID

		xor				eax, eax							; EAX=0: Highest Function Parameter and Manufacturer ID
#if _MSC_VER > 1300
		cpuid												; Run CPUID(0) [Highest Function Parameter and Manufacturer ID]
#else
		__emit 		0x0f
		__emit 		0xa2
#endif
		mov			[g_maxCPUID],eax						; CPUID(0) -> EAX = Highest Function Parameter (=maximum EAX for CPUID)
		mov			dword ptr 0[g_cpuManufacturer],ebx		; CPUID(0) -> EBX = characters [0,3] of manufacturer ID
		xor			eax,eax									; EAX = 0
		mov			dword ptr 4[g_cpuManufacturer],edx		; CPUID(0) -> EDX = characters [4,7] of manufacturer ID
		mov			dword ptr 12[g_cpuManufacturer], eax	;Set terminating zero
		inc			eax										; EAX = 1
		mov			dword ptr 8[g_cpuManufacturer],ecx		; CPUID(0) -> ECX = characters [8,12] of manufacturer ID
		mov			[g_CPUID_detected],eax					; Store we succesfully detected cpuid

#if _MSC_VER > 1300
		cpuid												; Run CPUID(1) [Processor Info and Feature Bits]
#else
		__emit 		0x0f
		__emit 		0xa2
#endif
		and			edx,0x800000							; Mask bit 23 of EDX: mmx feature (=64-bit SIMD)
		shr			edx,0x17								; Convert mmx feature bit to boolean
		mov			dword ptr [g_CPU_supports_MMX],edx		; Store MMX feature

	no_cpuid:
		pop			ebx									; Restore EBX
		ret												; Return to caller
	}
#elif defined(_M_IX64)
	int cpuinfo[4];
	_cpuid(cpuinfo, 0);
	g_maxCPUID = cpuinfo[0];
	memcpy(&g_cpuManufacturer[0], &cpuinfo[1], 4);
	memcpy(&g_cpuManufacturer[4], &cpuinfo[3], 4);
	memcpy(&g_cpuManufacturer[8], &cpuinfo[2], 4);
	g_cpuManufacturer[12] = '\0';
	_cpuid(cpuinfo, 1);
	g_CPU_supports_MMX = !!(cpuinfo[3] & 0x800000);
#endif
#elif defined(__i386__) || defined(x86_64)
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	__get_cpuid(0, &eax, &ebx, &ecx, &edx);
	g_maxCPUID = eax;
	memcpy(&g_cpuManufacturer[0], &ebx, 4);
	memcpy(&g_cpuManufacturer[4], &edx, 4);
	memcpy(&g_cpuManufacturer[8], &ecx, 4);
	g_cpuManufacturer[12] = '\0';
	__get_cpuid(1, &eax, &ebx, &ecx, &edx);
	g_CPU_supports_MMX = !!(edx & 0x800000);
#endif
}
