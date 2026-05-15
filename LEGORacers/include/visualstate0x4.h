#ifndef VISUALSTATE0X4_H
#define VISUALSTATE0X4_H

#include "decomp.h"
#include "types.h"

#pragma pack(push, 1)

// SIZE 0x04
class VisualState0x4 {
public:
	union {
		undefined4 m_unk0x00; // 0x00
		LegoS8 m_bytes[4];    // 0x00
	};
};

#pragma pack(pop)

#endif // VISUALSTATE0X4_H
