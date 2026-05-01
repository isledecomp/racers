#ifndef LAPISSIGIL0X14_H
#define LAPISSIGIL0X14_H

#include "decomp.h"
#include "types.h"

class GolStringTable;

// VTABLE: LEGORACERS 0x004affd4
// SIZE 0x14
class LapisSigil0x14 {
public:
	LapisSigil0x14();
	virtual ~LapisSigil0x14(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x0041f160
	// LapisSigil0x14::`scalar deleting destructor'

	void Load(GolStringTable* p_stringTable, const LegoChar* p_fileName, undefined4 p_binary);

private:
	undefined m_unk0x04[0x14 - 0x04]; // 0x04
};

#endif // LAPISSIGIL0X14_H
