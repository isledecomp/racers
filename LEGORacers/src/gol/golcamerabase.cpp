#include "camera/golcamerabase.h"

#include "camera/goltransform.h"
#include "golanimatedentity.h"
#include "golscenenode.h"
#include "goltransformbase.h"

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
