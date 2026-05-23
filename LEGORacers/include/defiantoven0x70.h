#ifndef DEFIANTOVEN0x70_H
#define DEFIANTOVEN0x70_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;
class CrimsonPebble0x228;

// SIZE 0x70
class DefiantOven0x70 {
public:
	enum Flags {
		c_flagBit6 = 1 << 6,
		c_flagBit7 = 1 << 7,
	};

	void FUN_004a3550(LegoFloat p_param1);
	void FUN_004a4790(CrimsonPebble0x228*, BronzeFalcon0xc8770*);

private:
	undefined m_unk0x00[0x1c - 0x00];
	LegoFloat m_unk0x1c[2];
	undefined m_unk0x24[0x2c - 0x24];
	LegoFloat m_unk0x2c[2];
	LegoFloat m_unk0x34[2];
	LegoFloat m_unk0x3c[2];
	LegoU32 m_unk0x44;
	undefined m_unk0x48[0x70 - 0x48];
};

#endif // DEFIANTOVEN0x70_H
