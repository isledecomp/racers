#include "race/powerups/warpaction.h"

#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racecameracontroller.h"
#include "race/racer/racer.h"
#include "race/racesoundsource.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

extern const LegoFloat g_warpPortalHeightOffset;

extern const LegoFloat g_warpFovBoost;

extern LegoFloat g_cosineTable[1024];

extern const LegoFloat g_hazardPi;

extern const LegoFloat g_negativeRadiansToTableIndex;

extern const LegoFloat g_homingProjectileCollisionProbeDepth;

extern const LegoFloat g_unk0x004b02fc;

// GLOBAL: LEGORACERS 0x004b1a60
const LegoFloat g_warpSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b1a64
const LegoFloat g_warpSoundMaxDistance = 600.0f;

// GLOBAL: LEGORACERS 0x004b1a68
const LegoFloat g_warpFovRange = 45.0f;

// GLOBAL: LEGORACERS 0x004b1a70
const LegoFloat g_warpPathSpeed = 0.6f;

// GLOBAL: LEGORACERS 0x004b1a74
const LegoFloat g_warpLaunchSpeed = 700.0f;

// GLOBAL: LEGORACERS 0x004b1aa8
const LegoFloat g_warpLerpScale = 0.00066666666f;

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoS32 WarpAction::GetBrickColor()
{
	return PowerupAction::c_brickColorGreen;
}

// FUNCTION: LEGORACERS 0x0045d400
WarpAction::WarpAction()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045d460
WarpAction::~WarpAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045d4b0
void WarpAction::Reset()
{
	m_state = c_stateUnloaded;
	m_isDemoRacer = 0;
	m_racer = 0;
	m_manager = 0;
	m_cameraFov = 0;
	m_startPosition.Clear();
	m_targetPosition.Clear();
	m_targetDirection.Clear();
	m_hasTarget = 0;
	m_followingPath = 0;
}

// FUNCTION: LEGORACERS 0x0045d510
void WarpAction::Initialize(const SetupParams* p_params)
{
	if (m_state != c_stateUnloaded) {
		Destroy();
	}

	m_manager = p_params->m_manager;
	m_cameraFov = p_params->m_cameraFov;
	m_state = c_stateInitialized;
}

// FUNCTION: LEGORACERS 0x0045d540
void WarpAction::Destroy()
{
	Deactivate();
	Reset();
}

// FUNCTION: LEGORACERS 0x0045d560
LegoU32 WarpAction::Activate(Racer* p_racer, GolModelEntity* p_model, ActionTarget* p_target)
{
	LegoU32 flags = p_racer->m_flags;
	if (!(flags & c_flagGhost)) {
		if (flags & Racer::c_flagWarping) {
			m_state = c_stateDone;
			return flags;
		}

		m_manager->CancelMagnetHold(p_racer);
		m_racer = p_racer;
		m_isDemoRacer = p_racer->m_controlMode == Racer::c_controlAi;
		p_racer->m_flags |= Racer::c_flagWarping;

		m_modelEntity.SetPrimaryModel(p_model->GetModel(0), p_model->GetModelDistance(0));
		for (LegoU32 i = 1; i < 3; i++) {
			GolModelBase* model = p_model->GetModel(i);
			if (model != NULL) {
				m_modelEntity.AddModel(model, p_model->GetModelDistance(i));
			}
		}

		m_modelEntity.SetTextureScrollU(p_model->GetTextureScrollU());
		m_modelEntity.SetTextureScrollV(p_model->GetTextureScrollV());
		m_modelEntity.SetTextureScrollSpeedU(p_model->GetTextureScrollSpeedU());
		m_modelEntity.SetTextureScrollSpeedV(p_model->GetTextureScrollSpeedV());

		GolAnimatedEntity* racerEntity = p_racer->m_visuals.m_carEntity;
		GolVec3 position;
		racerEntity->GetPosition(&position);
		LegoFloat positionZ = position.m_z;
		position.m_z = positionZ + g_warpPortalHeightOffset;
		m_modelEntity.SetPosition(position);
		position.m_z -= g_warpPortalHeightOffset;
		m_modelEntity.CopyOrientationFrom(*racerEntity);

		if (m_racer->m_cameraController != NULL) {
			m_racer->m_cameraController->m_targetFov = m_cameraFov + g_warpFovBoost;
		}

		if (p_target != NULL) {
			m_stateTimerMs = 0;
			m_targetPosition = p_target->m_position;
			m_targetDirection = p_target->m_direction;
			m_hasTarget = TRUE;
		}
		else {
			m_stateTimerMs = 500;
			m_hasTarget = FALSE;
		}

		m_state = c_stateStarting;
		return 0;
	}

	m_state = c_stateDone;
	return flags;
}

// FUNCTION: LEGORACERS 0x0045d780
void WarpAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	MenuAnimationList* animationList = m_manager->m_animationList;
	if (m_stateTimerMs < c_menuAnimationDurationMs && m_state == c_stateStarting && !m_isDemoRacer &&
		!animationList->HasActive()) {
		MenuAnimationList::Entry* entry =
			animationList->Activate(c_menuAnimationDurationMs, FALSE, NULL, m_racer->m_cameraController->m_camera);
		if (entry != NULL) {
			ColorRGBA color;
			color.m_red = 0;
			color.m_grn = 0;
			color.m_blu = c_menuAnimationColorBlue;
			entry->SetColor(color);
		}
	}

	if (m_state == c_stateActive) {
		GolVec3 position;
		do {
			if (m_hasTarget) {
				LegoFloat amount = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs)) * g_warpLerpScale;
				position.m_x = m_targetPosition.m_x - ((m_targetPosition.m_x - m_startPosition.m_x) * amount);
				position.m_y = m_targetPosition.m_y - ((m_targetPosition.m_y - m_startPosition.m_y) * amount);
				position.m_z = m_targetPosition.m_x - ((m_targetPosition.m_z - m_startPosition.m_z) * amount);
			}
			else {
				if (!m_followingPath || m_racer->m_checkpointGraph == NULL) {
					break;
				}

				LegoFloat distance = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * g_warpPathSpeed;
				CheckpointGraph::Entry* pathEntry = m_racer->m_checkpoint;
				if (pathEntry != NULL) {
					LegoU8 pathIndex = pathEntry->m_next.m_items[0];
					pathEntry = m_racer->m_checkpointGraph->GetCheckpoint(pathIndex);
				}

				CarVisuals* racerCarVisuals = &m_racer->m_visuals;
				racerCarVisuals->m_carEntity->GetPosition(&position);
				m_racer->m_checkpointGraph->AdvanceAlongGraph(&position, distance, pathEntry);
			}

			m_racer->m_visuals.m_carEntity->SetPosition(position);
			m_racer->m_physics.m_physicsEntity.SetPosition(position);
		} while (0);
	}

	m_modelEntity.Update(p_elapsedMs);
	PowerupAction::Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x0045d940
void WarpAction::Draw(GolD3DRenderDevice* p_renderer)
{
	MenuAnimationList* animationList = m_manager->m_animationList;
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state != c_stateActive) {
		return;
	}

	RaceCameraController* cameraController = m_racer->m_cameraController;
	if (cameraController == NULL) {
		return;
	}

	GolCamera* camera = p_renderer->GetCurrentCamera();
	if (cameraController->m_camera != camera) {
		return;
	}

	CarVisuals* racerField = &m_racer->m_visuals;
	GolAnimatedEntity* entity = racerField->m_carEntity;

	GolVec3 savedPosition;
	GolMatrix3 savedOrientation;
	entity->GetPosition(&savedPosition);
	entity->CopyOrientation(&savedOrientation);

	GolVec3 direction;
	direction.m_x = 0.0f;
	direction.m_y = -1.0f;
	direction.m_z = 0.0f;

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	GolVec3 position;
	position.Clear();
	entity->SetPosition(position);
	entity->SetDirectionUp(direction, up);

	m_racer->m_cameraController->m_dirty = TRUE;
	m_racer->m_cameraController->Update(0.0f);

	LegoFloat phase = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs));
	phase *= g_hazardPi;
	phase *= g_warpLerpScale;
	phase *= g_negativeRadiansToTableIndex;
	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(phase)) & 0x3ff;
	LegoFloat tableValue = g_cosineTable[tableIndex];
	LegoFloat fov = tableValue * g_warpFovRange + m_cameraFov;
	camera->m_flags |= GolCamera::c_flagProjectionDirty;
	camera->m_fov = fov;

	p_renderer->ApplyCamera();
	racerField->ShowModels();

	GolAnimatedEntity* dbricks = m_manager->m_turbo3Database->FindAnimatedEntity("dbricks");
	dbricks->ResetPartIndices();
	dbricks->SetActiveValue(0.0f);
	dbricks->SetTextureScrollU(0.0f);
	dbricks->SetTextureScrollV(0.0f);

	GolAnimatedEntity* dtube = m_manager->m_turbo3Database->FindAnimatedEntity("dtube");
	dtube->ResetPartIndices();
	dtube->SetActiveValue(0.0f);
	dtube->SetTextureScrollU(0.0f);
	dtube->SetTextureScrollV(0.0f);

	m_manager->m_turbo3Database->Update(c_transitionDurationMs - m_stateTimerMs);
	m_manager->m_turbo3Database->DrawWorld();

	racerField->SnapVisuals();
	if (m_racer->m_cameraViewIndex != c_stateActive) {
		racerField->Draw(p_renderer);
	}

	entity->SetPosition(savedPosition);
	entity->SetOrientationMatrix(savedOrientation);
	m_racer->InvalidateCamera();
	animationList->Draw(p_renderer);
	racerField->HideModels();

	LegoFloat restoredFov = m_cameraFov;
	camera->m_fov = restoredFov;
	camera->m_flags |= GolCamera::c_flagProjectionDirty;
}

// FUNCTION: LEGORACERS 0x0045dbe0
void WarpAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateStarting) {
		return;
	}

	GolVec3 position;
	LegoFloat phase = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs));
	phase *= g_unk0x004b02fc;
	phase *= g_hazardPi;
	phase *= g_negativeRadiansToTableIndex;
	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(phase)) & 0x3ff;
	LegoFloat scale = g_cosineTable[tableIndex];
	m_modelEntity.SetScaleAndInvalidateRadius(scale);

	if (m_stateTimerMs < 250) {
		m_racer->m_visuals.SetScale(scale);
	}

	CarVisuals* racerField = &m_racer->m_visuals;
	GolAnimatedEntity* entity = racerField->m_carEntity;
	entity->GetPosition(&position);
	m_modelEntity.SetPosition(position);
	m_modelEntity.Draw(*p_renderer);
}

// FUNCTION: LEGORACERS 0x0045dc90
void WarpAction::AdvanceState()
{
	switch (m_state) {
	case c_stateStarting: {
		m_racer->m_flags &= ~Racer::c_flagWarping;
		m_racer->EnterGhostMode();
		m_racer->m_visuals.SetScale(1.0f);
		m_racer->m_physics.EndExternalForce0();
		m_racer->m_physics.EndExternalForce1();

		RaceCameraController* cameraController = m_racer->m_cameraController;
		if (cameraController != NULL) {
			GolCamera* camera = cameraController->m_camera;
			LegoFloat fov = m_cameraFov;
			camera->m_fov = fov;
			camera->m_flags |= GolCamera::c_flagProjectionDirty;
			fov = m_cameraFov;
			m_racer->m_cameraController->m_targetFov = fov;
		}

		CarVisuals* racerField = &m_racer->m_visuals;
		racerField->m_carEntity->GetPosition(&m_startPosition);

		if (!m_isDemoRacer) {
			m_soundSource->PlaySoundById(c_soundStart);
		}

		m_soundSource->PlaySpatialSoundById(
			c_soundSpatial,
			&m_startPosition,
			g_warpSoundMinDistance,
			g_warpSoundMaxDistance,
			1.0f,
			1.0f
		);

		if (!m_isDemoRacer) {
			m_followingPath = TRUE;
		}

		m_stateTimerMs = c_transitionDurationMs;
		m_state = c_stateActive;
		break;
	}
	case c_stateActive: {
		RaceCameraController* cameraController = m_racer->m_cameraController;
		if (cameraController != NULL) {
			GolCamera* camera = cameraController->m_camera;
			LegoFloat fov = m_cameraFov;
			camera->m_fov = fov;
			camera->m_flags |= GolCamera::c_flagProjectionDirty;
			fov = m_cameraFov;
			m_racer->m_cameraController->m_targetFov = fov;
		}

		GolAnimatedEntity* entity = m_racer->m_visuals.m_carEntity;
		TeleportEntity(entity);
		m_racer->m_physics.m_physicsEntity.CopyPositionFrom(*entity);

		GolVec3 direction;
		if (m_hasTarget) {
			direction = m_targetDirection;
		}
		else {
			CheckpointGraph::Entry* racerPathEntry = m_racer->m_checkpoint;
			if (racerPathEntry != NULL) {
				LegoU8 pathIndex = racerPathEntry->m_next.m_items[0];
				CheckpointGraph* path = m_racer->m_checkpointGraph;
				CheckpointGraph::Entry* pathEntry = path->GetCheckpoint(pathIndex);
				direction.m_x = pathEntry->m_planeNormal.m_x;
				direction.m_y = pathEntry->m_planeNormal.m_y;
				LegoFloat z = pathEntry->m_planeNormal.m_z;
				direction.m_x = -direction.m_x;
				direction.m_y = -direction.m_y;
				direction.m_z = -z;
			}
			else {
				direction.m_x = 1.0f;
				direction.m_y = 0.0f;
				direction.m_z = 0.0f;
			}
		}

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;

		if (!m_isDemoRacer) {
			entity->SetDirectionUp(direction, up);
			m_racer->m_physics.m_physicsEntity.CopyOrientationFrom(*entity);

			RacerPhysics* racerPhysics = &m_racer->m_physics;
			up.Clear();
			racerPhysics->m_velocity.m_x = 0.0f;
			racerPhysics->m_velocity.m_y = up.m_y;
			racerPhysics->m_velocity.m_z = up.m_z;
			m_racer->m_physics.ApplyDirectionalImpulse(&direction, g_warpLaunchSpeed);
			m_racer->m_physics.SnapFacingDirection();
			m_racer->InvalidateCamera();

			if (!m_isDemoRacer) {
				m_soundSource->PlaySoundById(c_soundFinish);
			}
		}

		m_racer->LeaveGhostMode();
		m_state = c_stateDone;
		break;
	}
	}
}

// FUNCTION: LEGORACERS 0x0045e000
void WarpAction::Deactivate()
{
	m_state = c_stateInitialized;
	m_modelEntity.ResetModelState();
	if (m_racer != NULL) {
		RaceCameraController* cameraController = m_racer->m_cameraController;
		if (cameraController != NULL) {
			GolCamera* camera = cameraController->m_camera;
			LegoFloat fov = m_cameraFov;
			camera->m_fov = fov;
			camera->m_flags |= GolCamera::c_flagProjectionDirty;
			fov = m_cameraFov;
			m_racer->m_cameraController->m_targetFov = fov;
		}

		m_racer->m_visuals.SetScale(1.0f);
		m_racer = NULL;
	}

	m_followingPath = FALSE;
}

// FUNCTION: LEGORACERS 0x0045e080
void WarpAction::TeleportEntity(GolWorldEntity* p_entity)
{
	GolVec3 position;
	if (m_hasTarget) {
		position = m_targetPosition;
	}
	else {
		p_entity->GetPosition(&position);
	}

	GolVec3 start = position;
	GolVec3 end = position;
	end.m_z += 5.0f;
	start.m_z += 5.0f;
	start.m_z -= g_homingProjectileCollisionProbeDepth;

	GolBoundingVolume::HitTriangle record;
	m_manager->m_collisionWorld->IntersectSegment(&start, &end, &record, &position, NULL);

	position.m_z += 5.0f;
	p_entity->SetPosition(position);
}
