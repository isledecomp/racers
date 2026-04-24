#ifndef AZURESPARK0X0C_H
#define AZURESPARK0X0C_H

#include "decomp.h"
#include "types.h"

// SIZE 0x0c
class AzureSpark0x0c {
public:
	AzureSpark0x0c();

	LegoS32 Reset();
	LegoS32 FUN_0047fa00(LegoS32 p_capacity);
	LegoBool32 FUN_0047fa40();
	LegoS32 FUN_0047fa70(LegoU16 p_value);
	LegoU16 FUN_0047faa0();
	LegoU16 FUN_0047fac0();

private:
	LegoU16* m_unk0x00; // 0x00
	LegoS32 m_unk0x04;  // 0x04
	LegoS32 m_unk0x08;  // 0x08
};

#endif // AZURESPARK0X0C_H
