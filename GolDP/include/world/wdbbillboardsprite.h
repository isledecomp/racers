#ifndef WDBBILLBOARDSPRITE_H
#define WDBBILLBOARDSPRITE_H

#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "types.h"

// SIZE 0x38
struct WdbBillboardSprite {
	enum {
		c_flagAxisLocked = 0x1 << 1,
		c_flagMaterialAssignment = 0x1 << 2,
	};

	GolName m_materialName;              // 0x00
	GolVec3 m_position;                  // 0x08
	GolVec3 m_axis;                      // 0x14
	LegoFloat m_width;                   // 0x20
	LegoFloat m_height;                  // 0x24
	LegoFloat m_maxDistance;             // 0x28
	LegoU8 m_flags;                      // 0x2c
	undefined m_unk0x2d[0x2e - 0x2d];    // 0x2d
	undefined2 m_materialAnimationIndex; // 0x2e
	undefined2 m_materialTrackIndex;     // 0x30
	undefined2 m_hasMaterialAnimation;   // 0x32
	undefined2 m_materialTableIndex;     // 0x34
	undefined2 m_materialIndex;          // 0x36
};

#endif // WDBBILLBOARDSPRITE_H
