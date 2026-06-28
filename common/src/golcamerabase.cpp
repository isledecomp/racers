#include "golcamerabase.h"

#include "camera/goltransform.h"
#include "golanimatedentity.h"
#include "golscenenode.h"
#include "goltransformbase.h"

#include <math.h>

DECOMP_SIZE_ASSERT(GolCameraBase, 0x120)

// FUNCTION: LEGORACERS 0x004044f0
LegoFloat GolCameraBase::FUN_004044f0(GolVec3* p_left, GolVec3* p_right)
{
	return p_left->m_z * p_right->m_z + p_left->m_y * p_right->m_y + p_left->m_x * p_right->m_x;
}

// FUNCTION: LEGORACERS 0x00404510
GolVec3* GolCameraBase::FUN_00404510(GolVec3* p_left, GolVec3* p_right, GolVec3* p_dest)
{
	LegoFloat x = p_left->m_y;
	x *= p_right->m_z;
	x -= p_left->m_z * p_right->m_y;
	p_dest->m_x = x;

	LegoFloat y = p_left->m_z;
	y *= p_right->m_x;
	LegoFloat ySub = p_right->m_z;
	ySub *= p_left->m_x;
	y -= ySub;
	p_dest->m_y = y;

	LegoFloat z = p_right->m_y;
	z *= p_left->m_x;
	LegoFloat zSub = p_left->m_y;
	zSub *= p_right->m_x;
	z -= zSub;
	p_dest->m_z = z;

	return p_left;
}

// FUNCTION: LEGORACERS 0x00404550
GolVec3* GolCameraBase::FUN_00404550(GolVec3* p_left, GolVec3* p_right, GolVec3* p_dest)
{
	p_dest->m_x = p_left->m_x + p_right->m_x;
	p_dest->m_y = p_left->m_y + p_right->m_y;
	p_dest->m_z = p_left->m_z + p_right->m_z;

	return p_left;
}

// FUNCTION: LEGORACERS 0x00404580
GolVec3* GolCameraBase::FUN_00404580(GolVec3* p_left, GolVec3* p_right, GolVec3* p_dest)
{
	p_dest->m_x = p_left->m_x - p_right->m_x;
	p_dest->m_y = p_left->m_y - p_right->m_y;
	p_dest->m_z = p_left->m_z - p_right->m_z;

	return p_left;
}

// FUNCTION: LEGORACERS 0x004045b0
GolVec3* GolCameraBase::FUN_004045b0(GolVec3* p_src, LegoFloat p_scale, GolVec3* p_dest)
{
	p_dest->m_x = p_scale * p_src->m_x;

	LegoFloat y = p_src->m_y;
	y *= p_scale;
	p_dest->m_y = y;

	LegoFloat z = p_src->m_z;
	z *= p_scale;
	p_dest->m_z = z;

	return p_src;
}

// TODO: Unique section prevents ICF; the original keeps both dot helpers as distinct functions.
#pragma code_seg(".text$golcamerabase_00404680")
// FUNCTION: LEGORACERS 0x00404680
LegoFloat GolCameraBase::FUN_00404680(GolVec3* p_left, GolVec3* p_right)
{
	return p_left->m_z * p_right->m_z + p_left->m_y * p_right->m_y + p_left->m_x * p_right->m_x;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x004046a0
void GolCameraBase::LookAt(GolVec3* p_position, GolVec3* p_target, GolVec3* p_up)
{
	GolVec3 up;
	GolVec3 forward;
	forward.m_x = p_target->m_x - p_position->m_x;
	forward.m_y = p_target->m_y - p_position->m_y;
	forward.m_z = p_target->m_z - p_position->m_z;

	up.m_x = -p_up->m_x;
	up.m_y = -p_up->m_y;
	up.m_z = -p_up->m_z;

	m_transform->VTable0x24(&forward, &up);
	m_transform->SetPosition(p_position);
}

// FUNCTION: LEGORACERS 0x00404710
void GolCameraBase::FUN_00404710(LegoFloat p_fov, LegoFloat p_nearClip, LegoFloat p_farClip, LegoFloat p_aspectRatio)
{
	m_fov = p_fov;
	m_nearClip = p_nearClip;
	m_farClip = p_farClip;
	SetAspectRatio(p_aspectRatio);
}

// FUNCTION: LEGORACERS 0x00404740
void GolCameraBase::SetAspectRatio(LegoFloat p_aspect)
{
	if (p_aspect > 0.0f) {
		m_aspectRatio = p_aspect;
		m_flags |= 8;
	}
	else {
		m_flags &= ~8;
	}

	m_flags |= 3;
}

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
LegoBool32 GolCameraBase::VTable0x24(GolVec3* p_center, LegoFloat p_radius, GolVec4* p_bounds)
{
	LegoBool32 visibility = m_viewFrustum.ClassifySphere(*p_center, p_radius);

	if (visibility == FALSE) {
		return visibility;
	}

	GolVec3 tangentPoint;
	GolVec3 up;
	GolVec3 forward;
	GolVec3 scaledAxis;
	GolVec3 projectedPlane1;
	GolVec3 projectedPlane3;
	GolVec3 projectedPlane0;
	GolVec3 projectedPlane2;

	m_transform->GetUp(&up);

	const GolViewFrustum::Plane* plane = &m_viewFrustum.m_planes[1];
	LegoFloat dot = plane->m_normal.m_z;
	dot *= up.m_z;
	dot += plane->m_normal.m_y * up.m_y;
	dot += up.m_x * plane->m_normal.m_x;
	dot = -dot;
	LegoFloat scale = p_radius / dot;
	scaledAxis.m_x = scale * up.m_x;
	scaledAxis.m_y = scale * up.m_y;
	tangentPoint.m_x = scaledAxis.m_x + p_center->m_x;
	tangentPoint.m_y = scaledAxis.m_y + p_center->m_y;
	tangentPoint.m_z = scale * up.m_z + p_center->m_z;
	VTable0x20(&tangentPoint, &projectedPlane1);

	plane = &m_viewFrustum.m_planes[0];
	dot = plane->m_normal.m_z;
	dot *= up.m_z;
	dot += plane->m_normal.m_y * up.m_y;
	dot += up.m_x * plane->m_normal.m_x;
	scale = -(p_radius / dot);
	scaledAxis.m_x = scale * up.m_x;
	scaledAxis.m_y = scale * up.m_y;
	tangentPoint.m_x = scaledAxis.m_x + p_center->m_x;
	tangentPoint.m_y = scaledAxis.m_y + p_center->m_y;
	tangentPoint.m_z = scale * up.m_z + p_center->m_z;
	VTable0x20(&tangentPoint, &projectedPlane0);

	m_transform->GetForward(&forward);

	plane = &m_viewFrustum.m_planes[3];
	dot = plane->m_normal.m_z;
	dot *= forward.m_z;
	dot += plane->m_normal.m_y * forward.m_y;
	dot += forward.m_x * plane->m_normal.m_x;
	scale = -(p_radius / dot);
	scaledAxis.m_x = scale * forward.m_x;
	scaledAxis.m_y = scale * forward.m_y;
	tangentPoint.m_x = scaledAxis.m_x + p_center->m_x;
	tangentPoint.m_y = scaledAxis.m_y + p_center->m_y;
	tangentPoint.m_z = scale * forward.m_z + p_center->m_z;
	VTable0x20(&tangentPoint, &projectedPlane3);

	plane = &m_viewFrustum.m_planes[2];
	dot = plane->m_normal.m_z;
	dot *= forward.m_z;
	dot += plane->m_normal.m_y * forward.m_y;
	dot += forward.m_x * plane->m_normal.m_x;
	dot = -dot;
	scale = p_radius / dot;
	scaledAxis.m_x = scale * forward.m_x;
	scaledAxis.m_y = scale * forward.m_y;
	tangentPoint.m_x = scaledAxis.m_x + p_center->m_x;
	tangentPoint.m_y = scaledAxis.m_y + p_center->m_y;
	tangentPoint.m_z = scale * forward.m_z + p_center->m_z;
	VTable0x20(&tangentPoint, &projectedPlane2);

	p_bounds->m_z = projectedPlane1.m_x;
	p_bounds->m_y = projectedPlane3.m_y;
	p_bounds->m_x = projectedPlane0.m_x;
	p_bounds->m_u = projectedPlane2.m_y;

	return visibility;
}

// FUNCTION: GOLDP 0x1001cb30
// FUNCTION: LEGORACERS 0x00404780
void GolCameraBase::SetTrackedEntity(GolAnimatedEntity* p_trackedEntity, LegoU32 p_trackedNodeIndex)
{
	m_trackedEntity = p_trackedEntity;
	m_trackedNodeIndex = p_trackedNodeIndex;
}

// FUNCTION: LEGORACERS 0x004047a0
void GolCameraBase::ClearTrackedEntity()
{
	m_trackedEntity = NULL;
	m_trackedNodeIndex = 0;
}

// FUNCTION: LEGORACERS 0x004047b0
void GolCameraBase::UpdateFromTrackedEntity()
{
	if (m_trackedEntity == NULL) {
		return;
	}

	m_trackedEntity->VTable0x5c(0);
	GolSceneNode* frameSet = m_trackedEntity->VTable0x58(0);
	GolTransformBase* orbit = frameSet->VTable0x18(m_trackedNodeIndex);

	GolVec3 position;
	GolVec3 right;
	GolVec3 forward;
	GolVec3 transformedPosition;
	GolVec3 transformedRight;
	GolVec3 transformedForward;
	orbit->GetPosition(&position);
	orbit->VTable0x20(&right, &forward);

	for (GolTransformBase* parent = orbit->m_unk0x04; parent != NULL; parent = parent->m_unk0x04) {
		parent->VTable0x04(&position, &transformedPosition);
		parent->VTable0x0c(&right, &transformedRight);
		parent->VTable0x0c(&forward, &transformedForward);

		position = transformedPosition;
		right = transformedRight;
		forward = transformedForward;
	}

	m_trackedEntity->VTable0x2c(position, &transformedPosition);
	m_trackedEntity->VTable0x34(right, &transformedRight);
	m_trackedEntity->VTable0x34(forward, &transformedForward);

	m_transform->SetPosition(&transformedPosition);
	transformedForward.m_x = -transformedForward.m_x;
	m_flags |= 1;
	transformedForward.m_y = -transformedForward.m_y;
	transformedForward.m_z = -transformedForward.m_z;
	m_transform->VTable0x24(&transformedRight, &transformedForward);
	m_flags |= 1;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolCameraBase::VTable0x20(const GolVec3*, GolVec3*)
{
	// empty
}
