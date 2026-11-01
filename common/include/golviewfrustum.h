#ifndef GOLVIEWFRUSTUM_H
#define GOLVIEWFRUSTUM_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

// SIZE 0xcc
class GolViewFrustum {
public:
	// SIZE 0x10
	struct Plane {
		GolVec3 m_normal;     // 0x00
		LegoFloat m_distance; // 0x0c

		void Set(const GolVec3& p_normal, const GolVec3& p_point)
		{
			m_normal.m_x = p_normal.m_x;
			m_normal.m_y = p_normal.m_y;
			m_normal.m_z = p_normal.m_z;
			m_distance = -(m_normal.m_z * p_point.m_z + m_normal.m_y * p_point.m_y + m_normal.m_x * p_point.m_x);
		}
	};

	LegoS32 ClassifySphere(const GolVec3& p_center, LegoFloat p_radius) const;
	LegoS32 ClassifyBox(const LegoFloat* p_bounds) const;

	GolVec3 m_position;   // 0x00
	GolVec3 m_corners[8]; // 0x0c
	Plane m_planes[6];    // 0x6c
};

#endif // GOLVIEWFRUSTUM_H
