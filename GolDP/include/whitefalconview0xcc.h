#ifndef WHITEFALCONVIEW0XCC_H
#define WHITEFALCONVIEW0XCC_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

// SIZE 0xcc
class WhiteFalconView0xcc {
public:
	// SIZE 0x10
	struct Plane0x10 {
		GolVec3 m_normal;     // 0x00
		LegoFloat m_distance; // 0x0c
	};

	LegoS32 FUN_1002bc20(const GolVec3& p_center, LegoFloat p_radius) const;

	GolVec3 m_position;    // 0x00
	GolVec3 m_corners[8];  // 0x0c
	Plane0x10 m_planes[6]; // 0x6c
};

#endif // WHITEFALCONVIEW0XCC_H
