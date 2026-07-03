#include "world/golworlddatabase.h"

#include "cmbmodelpart.h"
#include "golanimatedentity.h"
#include "golboundedentity.h"
#include "golcamerabase.h"
#include "golcollidableentity.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golscenenode.h"
#include "golworldentity.h"
#include "mabmaterialanimation.h"

// FUNCTION: LEGORACERS 0x00416040
void GolWorldDatabase::DrawWorld()
{
	if (m_collidableEntityCount) {
		DrawCollidableEntities(m_renderer);
	}

	if (m_animatedEntityCount) {
		DrawAnimatedEntities(m_renderer);
	}

	if (m_modelEntityCount) {
		DrawModelEntities(m_renderer);
	}

	if (m_spriteCount) {
		DrawSprites(m_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00416090
void GolWorldDatabase::Update(LegoS32 p_elapsedMs)
{
	LegoU32 i;

	for (i = 0; i < m_materialAnimationCount; i++) {
		GetMaterialAnimation(i)->Update(p_elapsedMs);
	}

	for (i = 0; i < m_modelEntityCount; i++) {
		m_modelEntities[i].Update(p_elapsedMs);
	}

	for (i = 0; i < m_animatedEntityCount; i++) {
		m_animatedEntities[i].Update(p_elapsedMs);
	}

	for (i = 0; i < m_cameraCount; i++) {
		GetCamera(i)->UpdateFromTrackedEntity();
	}
}

// FUNCTION: LEGORACERS 0x00416140
void GolWorldDatabase::ResetEntities()
{
	LegoU32 i;

	for (i = 0; i < m_modelEntityCount; i++) {
		m_modelEntities[i].MirrorY();
	}

	for (i = 0; i < m_animatedEntityCount; i++) {
		m_animatedEntities[i].MirrorY();
	}

	for (i = 0; i < m_collidableEntityCount; i++) {
		m_collidableEntities[i].MirrorY();
	}

	for (i = 0; i < m_boundedEntityCount; i++) {
		m_boundedEntities[i].MirrorY();
	}

	for (i = 0; i < m_modelCount; i++) {
		GetModel(i)->MirrorY();
	}

	for (i = 0; i < m_spriteCount; i++) {
		GolWorldEntity* entity = GetWorldEntity(i);
		GolVec3 center;
		entity->GetBoundsCenter(&center);
		center.m_y = -center.m_y;
		entity->SetPosition(center);
	}

	for (i = 0; i < m_modelPartCount; i++) {
		GetModelPart(i)->MirrorY();
	}

	for (i = 0; i < m_sceneNodeCount; i++) {
		GetSceneNode(i)->MirrorY();
	}
}

// FUNCTION: LEGORACERS 0x00416290
LegoU32 GolWorldDatabase::SetCameraAspectRatios(LegoFloat p_scale)
{
	LegoU32 i = 0;
	LegoU32 result = m_cameraCount;
	if (result > 0) {
		do {
			GetCamera(i)->SetAspectRatio(p_scale);
			result = m_cameraCount;
			i++;
		} while (i < result);
	}

	return result;
}
