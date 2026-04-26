#ifndef MITHRILCHAIN0X8_H
#define MITHRILCHAIN0X8_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;

// SIZE 0x8
class MithrilChain0x8 {
public:
	MithrilChain0x8();
	~MithrilChain0x8();
	void FUN_00494f60(LegoU32 p_unk0x04);
	void FUN_00494fa0(BronzeFalcon0xc8770* p_unk0x04);

private:
	undefined m_unk0x00[0x8 - 0x00]; // 0x00
};

#endif // MITHRILCHAIN0X8_H
