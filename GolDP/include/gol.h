#ifndef GOLDP_GOL_H
#define GOLDP_GOL_H

#include "decomp.h"
#include "types.h"

#include <windows.h>

typedef void FatalErrorCBFN(const char* p_message);
typedef void GolExitCBFN();

struct GolImport {
	undefined4* m_unk0x0;             // 0x00
	undefined4* m_unk0x4;             // 0x04
	undefined4* m_unk0x8[4];          // 0x08
	LegoU32 m_unk0x18;                // 0x18
	undefined4* m_unk0x1c;            // 0x1c
	HANDLE m_mutex;                   // 0x20
	undefined m_unk0x24[0x28 - 0x24]; // 0x24
	FatalErrorCBFN* m_fatalError;     // 0x28
};

// VTABLE: GOLDP 0x100564b0
// SIZE 0x4
class GolExport {
public:
	// SYNTHETIC: GOLDP 0x10007170
	// GolExport::`scalar deleting destructor'

	virtual ~GolExport() {}
	virtual undefined4* VTable0x04() = 0;
	virtual undefined4* VTable0x08() = 0;
	virtual undefined4* VTable0x0c() = 0;
	virtual undefined4* VTable0x10() = 0;
	virtual undefined4* VTable0x14() = 0;
	virtual undefined4* VTable0x18() = 0;
	virtual undefined4* VTable0x1c() = 0;
	virtual undefined4* VTable0x20() = 0;
	virtual undefined4 VTable0x24() = 0;
	virtual undefined4* VTable0x28() = 0;
	virtual undefined4* VTable0x2c() = 0;
	virtual undefined4* VTable0x30() = 0;
	virtual undefined4* VTable0x34() = 0;
	virtual undefined4* VTable0x38() = 0;
	virtual void VTable0x3c(undefined4*) = 0;
	virtual void VTable0x40(undefined4*) = 0;
	virtual void VTable0x44(undefined4*) = 0;
	virtual void VTable0x48(undefined4*) = 0;
	virtual void VTable0x4c(undefined4*) = 0;
	virtual void VTable0x50(undefined4*) = 0;
	virtual void VTable0x54(undefined4*) = 0;
	virtual void VTable0x58(undefined4*) = 0;
	virtual void VTable0x5c(undefined4*) = 0;
	virtual void VTable0x60(undefined4*) = 0;
	virtual void VTable0x64(undefined4*) = 0;
	virtual void VTable0x68(undefined4*) = 0;
	virtual void VTable0x6c(undefined4*) = 0;
};

typedef GolExport* GolEntryCBFN(GolImport*);
typedef void GolExitCBFN();

extern GolExport* GolEntry(GolImport* p_import);

extern void GolExit();

#endif // GOLDP_GOL_H
