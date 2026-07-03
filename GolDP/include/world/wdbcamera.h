#ifndef WDBCAMERA_H
#define WDBCAMERA_H

#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "types.h"

// SIZE 0x4c
struct WdbCamera {
	LegoFloat GetNearClip() const { return m_nearClip; }
	LegoFloat GetFarClip() const { return m_farClip; }
	LegoFloat GetFov() const { return m_fov; }

	GolName m_name;                // 0x00
	LegoS32 m_animatedEntityIndex; // 0x08
	undefined4 m_trackedNodeIndex; // 0x0c
	LegoS32 m_partIndex;           // 0x10
	GolName m_partName;            // 0x14
	GolVec3 m_position;            // 0x1c
	GolVec3 m_direction;           // 0x28
	GolVec3 m_up;                  // 0x34
	LegoFloat m_nearClip;          // 0x40
	LegoFloat m_farClip;           // 0x44
	LegoFloat m_fov;               // 0x48
};

#endif // WDBCAMERA_H
