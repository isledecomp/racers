#ifndef WDBMODEL_H
#define WDBMODEL_H

#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "render/rectangle.h"
#include "types.h"

// SIZE 0x8c
struct WdbModel {
	enum {
		e_flagBit1 = 0x1 << 1,
		e_flagBit2 = 0x1 << 2,
		e_flagTextureScroll = 0x1 << 3,
	};

	GolName m_name;                    // 0x00
	LegoS32 m_modelIndices[3];         // 0x08
	LegoS32 m_sceneNodeIndices[3];     // 0x14 (bounding-volume index in [0] for bounded entities)
	LegoS32 m_modelPartIndices[3];     // 0x20
	LegoS32 m_materialTableIndices[3]; // 0x2c
	LegoFloat m_modelDistances[3];     // 0x38
	LegoS32 m_nodeIndex;               // 0x44
	GolName m_nodeName;                // 0x48
	GolVec3 m_position;                // 0x50
	GolVec3 m_direction;               // 0x5c
	GolVec3 m_up;                      // 0x68
	LegoFloat m_scale;                 // 0x74
	Rect* m_animationBindings;         // 0x78 (left=animation, top=track, right=material, bottom=table)
	LegoU32 m_animationBindingCount;   // 0x7c
	LegoFloat m_textureScrollSpeedU;   // 0x80
	LegoFloat m_textureScrollSpeedV;   // 0x84
	LegoU32 m_flags;                   // 0x88
};

#endif // WDBMODEL_H
