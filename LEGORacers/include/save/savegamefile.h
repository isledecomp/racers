#ifndef SAVEGAMEFILE_H
#define SAVEGAMEFILE_H

#include "golfile.h"
#include "types.h"

class SaveSlot;

// VTABLE: LEGORACERS 0x004b0fac
// SIZE 0x30
class SaveGameFile : public GolFile {
public:
	~SaveGameFile() override; // vtable+0x18

	LegoS32 BufferedOpen(const LegoChar* p_fileName, LegoS32 p_mode, LegoU32 p_bufferSize) override; // vtable+0x1c
	LegoS32 Dispose() override;                                                                      // vtable+0x20
	virtual LegoS32 OpenSlotFile(SaveSlot* p_slot, const LegoChar* p_fileName, undefined4) = 0;      // vtable+0x38
	virtual LegoS32 BufferedOpenSlotFile(
		SaveSlot* p_slot,
		const LegoChar* p_fileName,
		LegoS32 p_mode,
		LegoU32 p_bufferSize,
		undefined4 p_createSize
	); // vtable+0x3c

	// SYNTHETIC: LEGORACERS 0x0044e110
	// SaveGameFile::`scalar deleting destructor'
};

#endif // SAVEGAMEFILE_H
