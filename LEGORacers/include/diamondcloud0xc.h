#ifndef DIAMONDCLOUD0XC_H
#define DIAMONDCLOUD0XC_H

#include "decomp.h"
#include "types.h"

// SIZE 0xc
class DiamondCloud0xc {
public:
	DiamondCloud0xc();
	~DiamondCloud0xc();

private:
	void Reset();
	LegoBool32 FUN_0046e950();

	undefined4 m_unk0x00; // 0x00
	undefined4 m_unk0x04; // 0x04
	undefined4 m_unk0x08; // 0x08
};

#endif // DIAMONDCLOUD0XC_H
