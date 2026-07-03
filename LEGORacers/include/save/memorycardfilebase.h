#ifndef MEMORYCARDFILEBASE_H
#define MEMORYCARDFILEBASE_H

#include "save/savegamefile.h"

// VTABLE: LEGORACERS 0x004b1288
// SIZE 0x34
class MemoryCardFileBase : public SaveGameFile {
public:
	MemoryCardFileBase();
	LegoS32 OpenSlotFile(SaveSlot* p_slot, const LegoChar* p_fileName, undefined4) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x00450e70 FOLDED
	// MemoryCardFileBase::~MemoryCardFileBase

	// SYNTHETIC: LEGORACERS 0x00450e50 FOLDED
	// MemoryCardFileBase::`scalar deleting destructor'

private:
	undefined4 m_unk0x30; // 0x30
};

#endif // MEMORYCARDFILEBASE_H
