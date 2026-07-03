#include "golviewfrustum.h"

// FUNCTION: GOLDP 0x1002bc90
LegoS32 __fastcall GolViewFrustum::ClassifyBox(const GolViewFrustum* p_frustum, undefined4, const LegoFloat* p_bounds)
{
	LegoS32 outsideMask = 0;
	const GolViewFrustum::Plane* plane = p_frustum->m_planes;
	const GolViewFrustum::Plane* end = p_frustum->m_planes + sizeOfArray(p_frustum->m_planes);

	for (; plane < end; plane++) {
		LegoS32 outsideCount = 0;
		LegoFloat x0 = plane->m_normal.m_x * p_bounds[0];
		LegoFloat y0 = plane->m_normal.m_y * p_bounds[1];
		LegoFloat z0 = plane->m_normal.m_z * p_bounds[2] + plane->m_distance;
		LegoFloat x1 = plane->m_normal.m_x * p_bounds[3];
		LegoFloat y1 = plane->m_normal.m_y * p_bounds[4];
		LegoFloat z1 = plane->m_normal.m_z * p_bounds[5] + plane->m_distance;
		LegoFloat yz0 = y0 + z0;

		if (yz0 + x0 < 0.0f) {
			outsideMask |= 1;
			outsideCount++;
		}
		if (yz0 + x1 < 0.0f) {
			outsideMask |= 2;
			outsideCount++;
		}

		LegoFloat y1x0 = y1 + x0;
		if (y1x0 + z0 < 0.0f) {
			outsideMask |= 4;
			outsideCount++;
		}
		if (y1x0 + z1 < 0.0f) {
			outsideMask |= 0x20;
			outsideCount++;
		}

		LegoFloat y0z1 = y0 + z1;
		if (y0z1 + x0 < 0.0f) {
			outsideMask |= 8;
			outsideCount++;
		}
		if (y0z1 + x1 < 0.0f) {
			outsideMask |= 0x40;
			outsideCount++;
		}

		LegoFloat y1x1 = y1 + x1;
		if (y1x1 + z1 < 0.0f) {
			outsideMask |= 0x10;
			outsideCount++;
		}
		if (y1x1 + z0 < 0.0f) {
			outsideMask |= 0x80;
			outsideCount++;
		}

		if (outsideCount == 8) {
			return 0;
		}
	}

	if (outsideMask == 0) {
		return 2;
	}
	return 1;
}
