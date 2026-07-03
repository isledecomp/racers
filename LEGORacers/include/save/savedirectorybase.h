#ifndef SAVEDIRECTORYBASE_H
#define SAVEDIRECTORYBASE_H

#include "save/savedirectoryslot.h"

// VTABLE: LEGORACERS 0x004b12d8
// SIZE 0x08
class SaveDirectoryBase {
public:
	virtual void Clear() = 0;                // vtable+0x00
	virtual LegoU32 GetEntryCount() = 0;     // vtable+0x04
	virtual SaveSlot* GetEntry(LegoU32) = 0; // vtable+0x08

	const LegoChar* GetDirectoryPath() const { return m_directoryPath; }

protected:
	LegoChar* m_directoryPath; // 0x04
};

#endif // SAVEDIRECTORYBASE_H
