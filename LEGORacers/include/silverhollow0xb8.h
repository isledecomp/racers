#ifndef SILVERHOLLOW0XB8_H
#define SILVERHOLLOW0XB8_H

#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af754
// SIZE 0xb8
class SilverHollow0xb8 {
public:
	SilverHollow0xb8();
	virtual void VTable0x00(); // vtable+0x00

protected:
	undefined m_unk0x04[0x10 - 0x04]; // 0x04
	LegoFloat m_unk0x10;              // 0x10
	undefined m_unk0x14[0x5c - 0x14]; // 0x14
	LegoU32 m_unk0x5c;                // 0x5c
	undefined m_unk0x60[0x90 - 0x60]; // 0x60
	undefined4 m_unk0x90[3];          // 0x90
	undefined4 m_unk0x9c[3];          // 0x9c
	undefined4 m_unk0xa8[3];          // 0xa8
	LegoFloat m_unk0xb4;              // 0xb4
};

#endif // SILVERHOLLOW0XB8_H
