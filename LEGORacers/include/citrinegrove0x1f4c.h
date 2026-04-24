#ifndef CITRINEGROVE0X1F4C_H
#define CITRINEGROVE0X1F4C_H

#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b0b94
// SIZE 0x1f4c
class CitrineGrove0x1f4c {
public:
	CitrineGrove0x1f4c();
	virtual void VTable0x00(); // vtable+0x00
	~CitrineGrove0x1f4c();

	LegoU8 GetUnk0x18e6() const { return m_unk0x18e6; }

private:
	undefined m_unk0x04[0x18e6 - 0x04];     // 0x04
	LegoU8 m_unk0x18e6;                     // 0x18e6
	undefined m_unk0x18e7[0x1f4c - 0x18e7]; // 0x18e7
};

#endif // CITRINEGROVE0X1F4C_H
