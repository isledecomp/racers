#ifndef GOLSTRINGTABLE_H
#define GOLSTRINGTABLE_H

#include "decomp.h"
#include "types.h"

class GolString;

// VTABLE: LEGORACERS 0x004b0fec
// SIZE 0x14
class GolStringTable {
public:
	GolStringTable();
	virtual ~GolStringTable();                        // vtable+0x00
	virtual LegoS32 ReleaseOwnedBuffers();            // vtable+0x04
	virtual LegoS32 Load(const LegoChar* p_fileName); // vtable+0x08
	virtual void ReleaseBuffers();                    // vtable+0x0c

	LegoS32 CopyStringByIndex(GolString* p_string, LegoU16 p_index);
	LegoS32 UseOwnedBuffers();

	// SYNTHETIC: LEGORACERS 0x004a1480
	// GolStringTable::`vector deleting destructor'

private:
	LegoBool m_ownsBuffers;      // 0x04
	undefined m_unk0x05[3];      // 0x05
	undefined2* m_stringData;    // 0x08
	undefined2* m_stringOffsets; // 0x0c
	LegoU16 m_stringCount;       // 0x10
	undefined2 m_unk0x12;        // 0x12
};

#endif // GOLSTRINGTABLE_H
