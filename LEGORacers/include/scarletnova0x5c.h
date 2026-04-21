#ifndef SCARLETNOVA0X5C_H
#define SCARLETNOVA0X5C_H

#include "decomp.h"
#include "types.h"

// SIZE 0x5c
class ScarletNova0x5c {
public:
	undefined m_unk0x00[4];           // 0x00
	LegoBool m_flag;                  // 0x04
	undefined m_unk0x05[0x20 - 0x05]; // 0x05
	undefined4* m_unk0x20[12];        // 0x20
	undefined m_unk0x50[0x5c - 0x50]; // 0x50
};

#endif // SCARLETNOVA0X5C_H
