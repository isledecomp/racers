#include "camera/golcamerabase.h"

#include "camera/goltransform.h"

#include <math.h>

DECOMP_SIZE_ASSERT(GolCameraBase, 0x120)

// FUNCTION: GOLDP 0x1001bf30
GolCameraBase::GolCameraBase()
{
	m_transform = 0;
	m_fov = 40.0f;
	m_aspectRatio = 1.3333334f;
	m_nearClip = 2.0f;
	m_farClip = 200.0f;
	m_nearHalfWidth = 0.0f;
	m_nearHalfHeight = 0.0f;
	m_farHalfHeight = 0.0f;
	m_farHalfWidth = 0.0f;
	m_flags = 3;
	m_viewport.m_left = 0;
	m_viewport.m_right = 0;
	m_viewport.m_top = 0;
	m_viewport.m_bottom = 0;
	m_trackedEntity = 0;
	m_trackedNodeIndex = 0;
}

// FUNCTION: GOLDP 0x1001bfb0
GolCameraBase::~GolCameraBase()
{
}

// STUB: GOLDP 0x1001bfc0
void GolCameraBase::FUN_1001bfc0(GolViewFrustum* p_view)
{
	STUB(0x1001bfc0);

	m_transform->GetPosition(&p_view->m_position);

	LegoFloat tangent = static_cast<LegoFloat>(tan(m_fov * 0.0087266462f));
	m_farHalfHeight = m_farClip * tangent;
	m_farHalfWidth = m_aspectRatio * m_farHalfHeight;

	GolVec3 source;
	source.m_x = -m_farHalfWidth;
	source.m_y = -m_farHalfHeight;
	source.m_z = m_farClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[0]);

	source.m_x = -m_farHalfWidth;
	source.m_y = m_farHalfHeight;
	source.m_z = m_farClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[2]);

	source.m_x = m_farHalfWidth;
	source.m_y = -m_farHalfHeight;
	source.m_z = m_farClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[1]);

	source.m_x = m_farHalfWidth;
	source.m_y = m_farHalfHeight;
	source.m_z = m_farClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[3]);

	m_nearHalfHeight = m_nearClip * tangent;
	m_nearHalfWidth = m_aspectRatio * m_nearHalfHeight;

	source.m_x = -m_nearHalfWidth;
	source.m_y = -m_nearHalfHeight;
	source.m_z = m_nearClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[4]);

	source.m_x = -m_nearHalfWidth;
	source.m_y = m_nearHalfHeight;
	source.m_z = m_nearClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[6]);

	source.m_x = m_nearHalfWidth;
	source.m_y = -m_nearHalfHeight;
	source.m_z = m_nearClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[5]);

	source.m_x = m_nearHalfWidth;
	source.m_y = m_nearHalfHeight;
	source.m_z = m_nearClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[7]);

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
	normal.m_x = edge0.m_y * edge1.m_z - edge0.m_z * edge1.m_y;
	normal.m_y = edge0.m_z * edge1.m_x - edge0.m_x * edge1.m_z;
	normal.m_z = edge0.m_x * edge1.m_y - edge0.m_y * edge1.m_x;
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
	normal.m_x = edge0.m_y * edge1.m_z - edge0.m_z * edge1.m_y;
	normal.m_y = edge0.m_z * edge1.m_x - edge0.m_x * edge1.m_z;
	normal.m_z = edge0.m_x * edge1.m_y - edge0.m_y * edge1.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[3].m_normal = normal;
	p_view->m_planes[3].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	m_transform->GetRight(&normal);
	p_view->m_planes[5].m_normal = normal;
	p_view->m_planes[5].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	normal.m_x = -normal.m_x;
	normal.m_y = -normal.m_y;
	normal.m_z = -normal.m_z;
	p_view->m_planes[4].m_normal = normal;
	p_view->m_planes[4].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[2]);
}

// STUB: GOLDP 0x1001c450
void GolCameraBase::FUN_1001c450(GolViewFrustum* p_view)
{
	STUB(0x1001c450);

	m_transform->GetPosition(&p_view->m_position);

	LegoFloat farScale = m_farClip / m_nearClip;
	LegoFloat farLeft = m_viewBounds.m_x * farScale;
	LegoFloat farBottom = m_viewBounds.m_y * farScale;
	LegoFloat farRight = m_viewBounds.m_z * farScale;
	LegoFloat farTop = m_viewBounds.m_u * farScale;

	m_farHalfHeight = farTop - farBottom;
	m_farHalfWidth = farRight - farLeft;

	GolVec3 source;
	source.m_x = farLeft;
	source.m_y = farBottom;
	source.m_z = m_farClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[0]);

	source.m_x = farLeft;
	source.m_y = farTop;
	source.m_z = m_farClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[2]);

	source.m_x = farRight;
	source.m_y = farBottom;
	source.m_z = m_farClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[1]);

	source.m_x = farRight;
	source.m_y = farTop;
	source.m_z = m_farClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[3]);

	source.m_x = m_viewBounds.m_x;
	source.m_y = m_viewBounds.m_y;
	source.m_z = m_nearClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[4]);

	source.m_x = m_viewBounds.m_x;
	source.m_y = m_viewBounds.m_u;
	source.m_z = m_nearClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[6]);

	source.m_x = m_viewBounds.m_z;
	source.m_y = m_viewBounds.m_y;
	source.m_z = m_nearClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[5]);

	source.m_x = m_viewBounds.m_z;
	source.m_y = m_viewBounds.m_u;
	source.m_z = m_nearClip;
	m_transform->VTable0x04(&source, &p_view->m_corners[7]);

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
	normal.m_x = edge0.m_y * edge1.m_z - edge0.m_z * edge1.m_y;
	normal.m_y = edge0.m_z * edge1.m_x - edge0.m_x * edge1.m_z;
	normal.m_z = edge0.m_x * edge1.m_y - edge0.m_y * edge1.m_x;
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
	normal.m_x = edge0.m_y * edge1.m_z - edge0.m_z * edge1.m_y;
	normal.m_y = edge0.m_z * edge1.m_x - edge0.m_x * edge1.m_z;
	normal.m_z = edge0.m_x * edge1.m_y - edge0.m_y * edge1.m_x;
	GolMath::NormalizeVector3(normal, &normal);
	p_view->m_planes[3].m_normal = normal;
	p_view->m_planes[3].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	m_transform->GetRight(&normal);
	p_view->m_planes[5].m_normal = normal;
	p_view->m_planes[5].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[4]);

	normal.m_x = -normal.m_x;
	normal.m_y = -normal.m_y;
	normal.m_z = -normal.m_z;
	p_view->m_planes[4].m_normal = normal;
	p_view->m_planes[4].m_distance = -GOLVECTOR3_DOT(normal, p_view->m_corners[2]);
}

// STUB: GOLDP 0x1001c900
LegoBool32 GolCameraBase::VTable0x24(GolVec3*, LegoFloat, GolVec4*)
{
	STUB(0x1001c900);
	return FALSE;
}

// FUNCTION: GOLDP 0x1001cb30
void GolCameraBase::SetTrackedEntity(GolAnimatedEntity* p_trackedEntity, LegoU32 p_trackedNodeIndex)
{
	m_trackedEntity = p_trackedEntity;
	m_trackedNodeIndex = p_trackedNodeIndex;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolCameraBase::VTable0x20(const GolVec3*, GolVec3*)
{
	// empty
}
