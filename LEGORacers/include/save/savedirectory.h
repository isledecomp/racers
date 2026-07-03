#ifndef SAVEDIRECTORY_H
#define SAVEDIRECTORY_H

#include "compat.h"
#include "decomp.h"
#include "save/savedirectorybase.h"
#include "types.h"

class SaveDirectory;
class MemoryCardFileBase;

// VTABLE: LEGORACERS 0x004b12c8
// SIZE 0x108
class SaveDirectory : public SaveDirectoryBase {
public:
	SaveDirectory();
	void Clear() override;                // vtable+0x00
	LegoU32 GetEntryCount() override;     // vtable+0x04
	SaveSlot* GetEntry(LegoU32) override; // vtable+0x08
	virtual ~SaveDirectory();             // vtable+0x0c
	void Initialize(const LegoChar* p_path);

	// SYNTHETIC: LEGORACERS 0x00450ef0
	// SaveDirectory::`scalar deleting destructor'

private:
	SaveDirectorySlot m_entries[16]; // 0x08
};

#endif // SAVEDIRECTORY_H
