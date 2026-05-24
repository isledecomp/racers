#ifndef WHITEFALCONVIEWSTATE0XCC_H
#define WHITEFALCONVIEWSTATE0XCC_H

#include "golmath.h"
#include "types.h"

// SIZE 0xcc
struct WhiteFalconViewState0xcc {
	LegoS32 FUN_1002bc20(const GolVec3& p_center, LegoFloat p_radius) const;

	GolVec3 m_position;   // 0x00
	GolVec3 m_corners[8]; // 0x0c
	GolVec4 m_planes[6];  // 0x6c
};

#endif // WHITEFALCONVIEWSTATE0XCC_H
