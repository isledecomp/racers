#include "golcpu.h"

#include "types.h"

#if defined(_MSC_VER) && _MSC_VER < 1300
#define DETECTCPU_ASSEMBLY 1
#else
#define DETECTCPU_ASSEMBLY 0
#if defined(__i386__) || defined(_M_X86) || defined(_M_X64) || defined(__x86_64__)
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <cpuid.h>
#endif
#include <string.h>
#else
#include <string.h>
#endif
#endif

// GLOBAL: GOLDP 0x10065ed8
LegoBool32 g_cpuidDetected;

// GLOBAL: GOLDP 0x10065edc
LegoS32 g_maxCPUID;

// GLOBAL: GOLDP 0x10065ee0
LegoBool32 g_cpuSupportsMMX;

// GLOBAL: GOLDP 0x10065ee4
LegoChar g_cpuManufacturer[16];

// FUNCTION: GOLDP 0x10032c30
void DetectCPU()
{
#if DETECTCPU_ASSEMBLY
	__asm {
		// Verify cpuid instruction is supported (bit 21 of FLAGS register): Pentium+
		pushfd
		pop        eax
		mov        edx, eax
		xor        eax, 0x200000
		push       eax
		popfd
		pushfd
		pop        eax
		cmp        eax, edx
		jz         nocpuid
			// CPUID(0): EAX=Highest CPUID function, [EBX,EDX,ECX]=Manufacturer
		xor        eax, eax
		cpuid
		mov        [g_maxCPUID], eax
		mov        dword ptr [g_cpuManufacturer], ebx
		xor        eax,eax
		mov        dword ptr [g_cpuManufacturer+4], edx
		mov        dword ptr [g_cpuManufacturer+12], eax
		inc        eax
		mov        dword ptr [g_cpuManufacturer+8], ecx
		mov        [g_cpuidDetected], eax
		// CPUID(1): EDX: bit 23 = MMX support
		cpuid
		and        edx, 0x800000
		shr        edx, 0x17
		mov        dword ptr [g_cpuSupportsMMX], edx
	nocpuid:
	}
#else
#if defined(__i386__) || defined(_M_X86) || defined(_M_X64) || defined(__x86_64__)
#ifdef _MSC_VER
	int regs[4];
	g_cpuidDetected = TRUE;
	__cpuid(regs, 0);
	g_maxCPUID = regs[0];
	::memcpy(&g_cpuManufacturer[0], &regs[1], 4);
	::memcpy(&g_cpuManufacturer[4], &regs[3], 4);
	::memcpy(&g_cpuManufacturer[8], &regs[2], 4);
	::memset(&g_cpuManufacturer[12], 0, 4);
	__cpuid(regs, 1);
	g_cpuSupportsMMX = !!(regs[3] & 0x800000);
#else
	LegoU32 regEax, regEbx, regEcx, regEdx;
	g_cpuidDetected = TRUE;
	__cpuid(0, regEax, regEbx, regEcx, regEdx);
	g_maxCPUID = regEax;
	::memcpy(&g_cpuManufacturer[0], &regEbx, 4);
	::memcpy(&g_cpuManufacturer[4], &regEdx, 4);
	::memcpy(&g_cpuManufacturer[8], &regEcx, 4);
	::memset(&g_cpuManufacturer[12], 0, 4);
	__cpuid(1, regEax, regEbx, regEcx, regEdx);
	g_cpuSupportsMMX = !!(regEdx & 0x800000);
#endif
#else
	::strcpy(g_cpuManufacturer, "unknown");
#endif
#endif
}
