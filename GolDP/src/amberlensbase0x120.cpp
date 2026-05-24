#include "amberlensbase0x120.h"

#include "jadeorbit0xd0.h"

#include <math.h>

DECOMP_SIZE_ASSERT(AmberLensBase0x120, 0x120)

// FUNCTION: GOLDP 0x1001bf30
AmberLensBase0x120::AmberLensBase0x120()
{
	m_unk0x04 = 0;
	m_unk0x08 = 40.0f;
	m_unk0x0c = 1.3333334f;
	m_unk0x10 = 2.0f;
	m_unk0x14 = 200.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0.0f;
	m_unk0x24 = 0.0f;
	m_unk0x20 = 0.0f;
	m_flags = 3;
	m_viewport.m_left = 0;
	m_viewport.m_right = 0;
	m_viewport.m_top = 0;
	m_viewport.m_bottom = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
}

// FUNCTION: GOLDP 0x1001bfb0
AmberLensBase0x120::~AmberLensBase0x120()
{
}

// STUB: GOLDP 0x1001bfc0
void AmberLensBase0x120::FUN_1001bfc0(WhiteFalconView0xcc* p_view)
{
	STUB(0x1001bfc0);

	m_unk0x04->GetPosition(&p_view->m_position);

	LegoFloat tangent = static_cast<LegoFloat>(tan(m_unk0x08 * 0.0087266462f));
	m_unk0x24 = m_unk0x14 * tangent;
	m_unk0x20 = m_unk0x0c * m_unk0x24;

	GolVec3 source;
	source.m_x = -m_unk0x20;
	source.m_y = -m_unk0x24;
	source.m_z = m_unk0x14;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[0]);

	source.m_x = -m_unk0x20;
	source.m_y = m_unk0x24;
	source.m_z = m_unk0x14;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[2]);

	source.m_x = m_unk0x20;
	source.m_y = -m_unk0x24;
	source.m_z = m_unk0x14;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[1]);

	source.m_x = m_unk0x20;
	source.m_y = m_unk0x24;
	source.m_z = m_unk0x14;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[3]);

	m_unk0x1c = m_unk0x10 * tangent;
	m_unk0x18 = m_unk0x0c * m_unk0x1c;

	source.m_x = -m_unk0x18;
	source.m_y = -m_unk0x1c;
	source.m_z = m_unk0x10;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[4]);

	source.m_x = -m_unk0x18;
	source.m_y = m_unk0x1c;
	source.m_z = m_unk0x10;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[6]);

	source.m_x = m_unk0x18;
	source.m_y = -m_unk0x1c;
	source.m_z = m_unk0x10;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[5]);

	source.m_x = m_unk0x18;
	source.m_y = m_unk0x1c;
	source.m_z = m_unk0x10;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[7]);

	GolVec3 edge0;
	GolVec3 edge1;
	GolVec3 normal;

	edge0 = p_view->m_corners[0] - p_view->m_corners[4];
	edge1 = p_view->m_corners[6] - p_view->m_corners[4];
	normal.m_x = edge1.m_y * edge0.m_z - edge1.m_z * edge0.m_y;
	normal.m_y = edge1.m_z * edge0.m_x - edge1.m_x * edge0.m_z;
	normal.m_z = edge1.m_x * edge0.m_y - edge1.m_y * edge0.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[0].m_normal = normal;
	p_view->m_planes[0].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	edge0 = p_view->m_corners[1] - p_view->m_corners[5];
	edge1 = p_view->m_corners[7] - p_view->m_corners[5];
	normal.m_x = edge1.m_y * edge0.m_z - edge1.m_z * edge0.m_y;
	normal.m_y = edge1.m_z * edge0.m_x - edge1.m_x * edge0.m_z;
	normal.m_z = edge1.m_x * edge0.m_y - edge1.m_y * edge0.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[1].m_normal = normal;
	p_view->m_planes[1].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[5]);

	edge0 = p_view->m_corners[2] - p_view->m_corners[6];
	edge1 = p_view->m_corners[7] - p_view->m_corners[6];
	normal.m_x = edge1.m_y * edge0.m_z - edge1.m_z * edge0.m_y;
	normal.m_y = edge1.m_z * edge0.m_x - edge1.m_x * edge0.m_z;
	normal.m_z = edge1.m_x * edge0.m_y - edge1.m_y * edge0.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[2].m_normal = normal;
	p_view->m_planes[2].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[6]);

	edge0 = p_view->m_corners[0] - p_view->m_corners[4];
	edge1 = p_view->m_corners[5] - p_view->m_corners[4];
	normal.m_x = edge1.m_y * edge0.m_z - edge1.m_z * edge0.m_y;
	normal.m_y = edge1.m_z * edge0.m_x - edge1.m_x * edge0.m_z;
	normal.m_z = edge1.m_x * edge0.m_y - edge1.m_y * edge0.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[3].m_normal = normal;
	p_view->m_planes[3].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	m_unk0x04->GetRight(&normal);
	p_view->m_planes[5].m_normal = normal;
	p_view->m_planes[5].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	normal.m_x = -normal.m_x;
	normal.m_y = -normal.m_y;
	normal.m_z = -normal.m_z;
	p_view->m_planes[4].m_normal = normal;
	p_view->m_planes[4].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[2]);
}

// STUB: GOLDP 0x1001c450
void AmberLensBase0x120::FUN_1001c450(WhiteFalconView0xcc* p_view)
{
	STUB(0x1001c450);

	m_unk0x04->GetPosition(&p_view->m_position);

	LegoFloat farScale = m_unk0x14 / m_unk0x10;
	LegoFloat farLeft = m_unk0x100.m_x * farScale;
	LegoFloat farBottom = m_unk0x100.m_y * farScale;
	LegoFloat farRight = m_unk0x100.m_z * farScale;
	LegoFloat farTop = m_unk0x100.m_u * farScale;

	m_unk0x24 = farTop - farBottom;
	m_unk0x20 = farRight - farLeft;

	GolVec3 source;
	source.m_x = farLeft;
	source.m_y = farBottom;
	source.m_z = m_unk0x14;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[0]);

	source.m_x = farLeft;
	source.m_y = farTop;
	source.m_z = m_unk0x14;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[2]);

	source.m_x = farRight;
	source.m_y = farBottom;
	source.m_z = m_unk0x14;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[1]);

	source.m_x = farRight;
	source.m_y = farTop;
	source.m_z = m_unk0x14;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[3]);

	source.m_x = m_unk0x100.m_x;
	source.m_y = m_unk0x100.m_y;
	source.m_z = m_unk0x10;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[4]);

	source.m_x = m_unk0x100.m_x;
	source.m_y = m_unk0x100.m_u;
	source.m_z = m_unk0x10;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[6]);

	source.m_x = m_unk0x100.m_z;
	source.m_y = m_unk0x100.m_y;
	source.m_z = m_unk0x10;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[5]);

	source.m_x = m_unk0x100.m_z;
	source.m_y = m_unk0x100.m_u;
	source.m_z = m_unk0x10;
	m_unk0x04->VTable0x04(&source, &p_view->m_corners[7]);

	GolVec3 edge0;
	GolVec3 edge1;
	GolVec3 normal;

	edge0 = p_view->m_corners[0] - p_view->m_corners[4];
	edge1 = p_view->m_corners[6] - p_view->m_corners[4];
	normal.m_x = edge1.m_y * edge0.m_z - edge1.m_z * edge0.m_y;
	normal.m_y = edge1.m_z * edge0.m_x - edge1.m_x * edge0.m_z;
	normal.m_z = edge1.m_x * edge0.m_y - edge1.m_y * edge0.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[0].m_normal = normal;
	p_view->m_planes[0].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	edge0 = p_view->m_corners[1] - p_view->m_corners[5];
	edge1 = p_view->m_corners[7] - p_view->m_corners[5];
	normal.m_x = edge1.m_y * edge0.m_z - edge1.m_z * edge0.m_y;
	normal.m_y = edge1.m_z * edge0.m_x - edge1.m_x * edge0.m_z;
	normal.m_z = edge1.m_x * edge0.m_y - edge1.m_y * edge0.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[1].m_normal = normal;
	p_view->m_planes[1].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[5]);

	edge0 = p_view->m_corners[2] - p_view->m_corners[6];
	edge1 = p_view->m_corners[7] - p_view->m_corners[6];
	normal.m_x = edge1.m_y * edge0.m_z - edge1.m_z * edge0.m_y;
	normal.m_y = edge1.m_z * edge0.m_x - edge1.m_x * edge0.m_z;
	normal.m_z = edge1.m_x * edge0.m_y - edge1.m_y * edge0.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[2].m_normal = normal;
	p_view->m_planes[2].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[6]);

	edge0 = p_view->m_corners[0] - p_view->m_corners[4];
	edge1 = p_view->m_corners[5] - p_view->m_corners[4];
	normal.m_x = edge1.m_y * edge0.m_z - edge1.m_z * edge0.m_y;
	normal.m_y = edge1.m_z * edge0.m_x - edge1.m_x * edge0.m_z;
	normal.m_z = edge1.m_x * edge0.m_y - edge1.m_y * edge0.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[3].m_normal = normal;
	p_view->m_planes[3].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	m_unk0x04->GetRight(&normal);
	p_view->m_planes[5].m_normal = normal;
	p_view->m_planes[5].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	normal.m_x = -normal.m_x;
	normal.m_y = -normal.m_y;
	normal.m_z = -normal.m_z;
	p_view->m_planes[4].m_normal = normal;
	p_view->m_planes[4].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[2]);
}

// STUB: GOLDP 0x1001c900
void AmberLensBase0x120::VTable0x24(undefined4, undefined4, undefined4)
{
	STUB(0x1001c900);
}

// FUNCTION: GOLDP 0x1001cb30
void AmberLensBase0x120::FUN_1001cb30(AmberLensTrackedObject0xf4* p_arg1, LegoU32 p_arg2)
{
	m_unk0x28 = p_arg1;
	m_unk0x2c = p_arg2;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void AmberLensBase0x120::VTable0x20(const GolVec3*, GolVec3*)
{
	// empty
}
