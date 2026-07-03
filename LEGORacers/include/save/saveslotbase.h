#ifndef SAVESLOTBASE_H
#define SAVESLOTBASE_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b0f88
// SIZE 0x08
class SaveSlotBase {
public:
	SaveSlotBase();
	virtual ~SaveSlotBase();                              // vtable+0x00
	virtual LegoS32 EnsureDirectoryExists() = 0;          // vtable+0x04
	virtual LegoS32 CreateDirectories() = 0;              // vtable+0x08
	virtual LegoS32 CheckFileExists(const LegoChar*) = 0; // vtable+0x0c
	virtual LegoS32 VTable0x10(undefined4);               // vtable+0x10
	virtual LegoS32 RemoveFile(const LegoChar*) = 0;      // vtable+0x14
	virtual LegoS32 VTable0x18(undefined4, undefined4);   // vtable+0x18
	virtual LegoS32 VTable0x1c(undefined4);               // vtable+0x1c
	virtual LegoS32 VTable0x20(undefined4, undefined4);   // vtable+0x20

	// SYNTHETIC: LEGORACERS 0x0044e050
	// SaveSlotBase::`scalar deleting destructor'

	LegoBool32 HasUnk0x04() const { return m_unk0x04 != 0; }

protected:
	undefined4 m_unk0x04; // 0x04
};

#endif // SAVESLOTBASE_H
