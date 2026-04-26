#ifndef CORUNDUMPEAK0X14_H
#define CORUNDUMPEAK0X14_H

#include "decomp.h"
#include "types.h"

class GolString;

// VTABLE: LEGORACERS 0x004b0fec
// SIZE 0x14
class CorundumPeak0x14 {
public:
	CorundumPeak0x14();
	virtual ~CorundumPeak0x14(); // vtable+0x00
	LegoS32 FUN_0044e500(GolString* p_string, LegoU16 p_index);

	// SYNTHETIC: LEGORACERS 0x004a1480
	// CorundumPeak0x14::`vector deleting destructor'

private:
	LegoBool m_unk0x04;     // 0x04
	undefined m_unk0x05[3]; // 0x05
	undefined2* m_unk0x08;  // 0x08
	undefined2* m_unk0x0c;  // 0x0c
	LegoU16 m_unk0x10;      // 0x10
	undefined2 m_unk0x12;   // 0x12
};

#endif // CORUNDUMPEAK0X14_H
