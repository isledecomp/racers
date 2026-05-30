#ifndef TEALCRUCIBLE0X50_H
#define TEALCRUCIBLE0X50_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

// SIZE 0x50
class TealCrucible0x50 {
public:
	TealCrucible0x50();
	~TealCrucible0x50();

	LegoBool32 FUN_004991c0();

private:
	undefined m_unk0x00[0x10];        // 0x00
	undefined4 m_unk0x10;             // 0x10
	undefined m_unk0x14[0x50 - 0x14]; // 0x14
};

#endif // TEALCRUCIBLE0X50_H
