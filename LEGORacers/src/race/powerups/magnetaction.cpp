#include "race/powerups/magnetaction.h"

#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racesoundsource.h"
#include "render/gold3drenderdevice.h"

#include <float.h>
#include <math.h>

extern const LegoFloat g_brickSettleRate;

// GLOBAL: LEGORACERS 0x004b15dc
const LegoFloat g_magnetSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b15e0
const LegoFloat g_magnetSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b15e4
const LegoFloat g_magnetTriggerRadius = 10.0f;

// GLOBAL: LEGORACERS 0x004b15e8
const LegoFloat g_magnetPullDistanceSquared = 100.0f;

// GLOBAL: LEGORACERS 0x004b15ec
const LegoFloat g_magnetGrabDistanceSquared = 81.0f;

// GLOBAL: LEGORACERS 0x004b15f0
const LegoFloat g_magnetHoldHeightOffset = 30.0f;

// GLOBAL: LEGORACERS 0x004b15f4
const LegoFloat g_magnetHoldImpulseScale = 1.0f;

// GLOBAL: LEGORACERS 0x004b15f8
const LegoFloat g_magnetPullImpulseScale = 1.0f;

// GLOBAL: LEGORACERS 0x004b1620
const LegoFloat g_magnetFadeAlpha = 127.0f;

// FUNCTION: LEGORACERS 0x00455710
MagnetAction::MagnetAction()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00455770
MagnetAction::~MagnetAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004557c0
void MagnetAction::Destroy()
{
	Deactivate();
	Reset();
}

// FUNCTION: LEGORACERS 0x004557e0
void MagnetAction::Reset()
{
	m_magnetEntity = 0;
	m_ringEntity = 0;
	m_insideEntity = 0;
	m_manager = 0;
	m_sound = 0;
	m_heldRacer = 0;
	m_pulledRacer = 0;
	m_flags = 0;
	m_direction.m_x = 0.0f;
	m_direction.m_y = 0.0f;
	m_direction.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00455810
void MagnetAction::Initialize(
	RacePowerupManager* p_manager,
	RaceState* p_raceState,
	TriggerWorld* p_collisionWorld,
	CutsceneAnimation*,
	GolExport*,
	GolD3DRenderDevice*,
	undefined4
)
{
	m_manager = p_manager;
	m_raceState = p_raceState;
	m_collisionWorld = p_collisionWorld;
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x00455830
void MagnetAction::Activate(
	Racer* p_racer,
	GolAnimatedEntity* p_magnetTemplate,
	GolAnimatedEntity* p_ringTemplate,
	GolAnimatedEntity* p_insideTemplate
)
{
	m_magnetEntity = m_manager->AllocateEffectEntity();
	if (m_magnetEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_ringEntity = m_manager->AllocateEffectEntity();
	if (m_ringEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_insideEntity = m_manager->AllocateEffectEntity();
	if (m_insideEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_ownerRacer = p_racer;
	m_state = c_stateArmed;
	m_stateTimerMs = c_armedDurationMs;

	m_magnetEntity->SetModel(
		p_magnetTemplate->GetModel(0),
		p_magnetTemplate->GetSceneNode(0),
		p_magnetTemplate->GetModelPart(0),
		p_magnetTemplate->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_magnetTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_magnetTemplate->GetModelDistance(i);
			CmbModelPart* modelPart = p_magnetTemplate->GetModelPart(i);
			m_magnetEntity->AddModel(model, p_magnetTemplate->GetSceneNode(i), modelPart, modelDistance);
		}
	}

	m_ringEntity->SetModel(
		p_ringTemplate->GetModel(0),
		p_ringTemplate->GetSceneNode(0),
		p_ringTemplate->GetModelPart(0),
		p_ringTemplate->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_ringTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_ringTemplate->GetModelDistance(i);
			CmbModelPart* modelPart = p_ringTemplate->GetModelPart(i);
			m_ringEntity->AddModel(model, p_ringTemplate->GetSceneNode(i), modelPart, modelDistance);
		}
	}
	m_ringEntity->SetTextureScrollU(p_ringTemplate->GetTextureScrollU());
	m_ringEntity->SetTextureScrollV(p_ringTemplate->GetTextureScrollV());
	m_ringEntity->SetTextureScrollSpeedU(p_ringTemplate->GetTextureScrollSpeedU());
	m_ringEntity->SetTextureScrollSpeedV(p_ringTemplate->GetTextureScrollSpeedV());

	m_insideEntity->SetModel(
		p_insideTemplate->GetModel(0),
		p_insideTemplate->GetSceneNode(0),
		p_insideTemplate->GetModelPart(0),
		p_insideTemplate->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_insideTemplate->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_insideTemplate->GetModelDistance(i);
			CmbModelPart* modelPart = p_insideTemplate->GetModelPart(i);
			m_insideEntity->AddModel(model, p_insideTemplate->GetSceneNode(i), modelPart, modelDistance);
		}
	}
	m_insideEntity->SetTextureScrollU(p_insideTemplate->GetTextureScrollU());
	m_insideEntity->SetTextureScrollV(p_insideTemplate->GetTextureScrollV());
	m_insideEntity->SetTextureScrollSpeedU(p_insideTemplate->GetTextureScrollSpeedU());
	m_insideEntity->SetTextureScrollSpeedV(p_insideTemplate->GetTextureScrollSpeedV());
}

// FUNCTION: LEGORACERS 0x00455a90
void MagnetAction::Deactivate()
{
	if (m_sound != NULL) {
		m_soundSource->ReleaseSound(m_sound);
		m_sound = NULL;
	}

	if (m_insideEntity != NULL) {
		m_insideEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_insideEntity);
		m_insideEntity = NULL;
	}

	if (m_ringEntity != NULL) {
		m_ringEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_ringEntity);
		m_ringEntity = NULL;
	}

	if (m_magnetEntity != NULL) {
		m_magnetEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_magnetEntity);
		m_magnetEntity = NULL;
	}

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_ownerRacer = NULL;

	if (m_heldRacer != NULL) {
		m_heldRacer->EndMagnetHold();
		m_heldRacer = NULL;
	}

	m_pulledRacer = NULL;
	m_flags = 0;
	m_direction.m_x = 0.0f;
	m_direction.m_y = 0.0f;
	m_direction.m_z = 0.0f;
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x00455b40
void MagnetAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state == c_stateArmed && m_stateTimerMs == c_armedDurationMs) {
		Deploy();
	}

	PowerupAction::Update(p_elapsedMs);

	if (m_heldRacer == NULL && m_pulledRacer == NULL) {
		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;
		m_magnetEntity->SetDirectionUp(m_direction, up);
	}
	else {
		GolAnimatedEntity* racerEntity;
		if (m_heldRacer != NULL) {
			racerEntity = m_heldRacer->m_visuals.m_carEntity;
		}
		else {
			racerEntity = m_pulledRacer->m_visuals.m_carEntity;
		}

		GolVec3 racerPosition;
		racerEntity->GetPosition(&racerPosition);

		GolVec3 modelPosition;
		m_magnetEntity->GetPosition(&modelPosition);

		GolVec3 direction;
		direction.m_x = modelPosition.m_x - racerPosition.m_x;
		direction.m_y = modelPosition.m_y - racerPosition.m_y;
		direction.m_z = modelPosition.m_z - racerPosition.m_z;
		GolMath::NormalizeVector3(direction, &direction);

		LegoFloat zero = 0.0f;
		GolVec3 side;
		side.m_x = zero - direction.m_y;
		side.m_y = direction.m_x - zero;
		side.m_z = zero;

		GolVec3 up;
		up.m_x = side.m_y * direction.m_z - side.m_z * direction.m_y;
		up.m_y = side.m_z * direction.m_x - side.m_x * direction.m_z;
		up.m_z = side.m_x * direction.m_y - side.m_y * direction.m_x;
		m_magnetEntity->SetUpDirection(direction, up);

		if (m_heldRacer != NULL) {
			if (m_heldRacer->m_physics.m_speed <= g_brickSettleRate) {
				m_flags |= c_flagVictimStopped;

				if (!(m_heldRacer->m_flags & c_flagHalted)) {
					if (m_stateTimerMs > c_fadeDurationMs) {
						m_stateTimerMs = c_fadeDurationMs;
					}
				}

				m_heldRacer->Halt();
			}

			if (m_heldRacer->m_physics.m_routeMode == 0 && (m_flags & c_flagVictimStopped) &&
				!(m_flags & c_flagVictimLifted)) {
				modelPosition.m_z -= g_magnetHoldHeightOffset;
				direction.m_x = modelPosition.m_x - racerPosition.m_x;
				direction.m_y = modelPosition.m_y - racerPosition.m_y;
				direction.m_z = modelPosition.m_z - racerPosition.m_z;
				GolMath::NormalizeVector3(direction, &direction);

				m_heldRacer->m_physics.ApplyDirectionalImpulse(
					&direction,
					static_cast<LegoS32>(p_elapsedMs) * g_magnetHoldImpulseScale
				);

				if (m_heldRacer->m_physics.m_speed <= g_brickSettleRate) {
					direction.m_x = racerPosition.m_x - modelPosition.m_x;
					direction.m_y = racerPosition.m_y - modelPosition.m_y;
					direction.m_z = racerPosition.m_z - modelPosition.m_z;
					LegoFloat distanceSquared =
						direction.m_x * direction.m_x + direction.m_y * direction.m_y + direction.m_z * direction.m_z;

					if (distanceSquared <= g_magnetPullDistanceSquared) {
						m_flags |= c_flagVictimLifted;
					}
				}
			}

			if (m_heldRacer->m_driveController.m_flags & DriveController::c_flagTurbo) {
				m_manager->CancelTurbo(m_heldRacer);
				m_heldRacer->ClearActiveAction();
			}
		}
		else {
			modelPosition.m_z -= g_magnetHoldHeightOffset;
			direction.m_x = modelPosition.m_x - racerPosition.m_x;
			direction.m_y = modelPosition.m_y - racerPosition.m_y;
			direction.m_z = modelPosition.m_z - racerPosition.m_z;
			GolMath::NormalizeVector3(direction, &direction);

			m_pulledRacer->m_physics.ApplyDirectionalImpulse(
				&direction,
				static_cast<LegoS32>(p_elapsedMs) * g_magnetPullImpulseScale
			);
			m_pulledRacer = NULL;
		}
	}

	if (m_state == c_stateFade) {
		m_magnetEntity->SetScaleAndInvalidateRadius(static_cast<LegoS32>(m_stateTimerMs) * 0.001f);
	}

	m_ringEntity->CopyOrientationFrom(*m_magnetEntity);
	m_insideEntity->CopyOrientationFrom(*m_magnetEntity);
	m_magnetEntity->Update(p_elapsedMs);
	m_ringEntity->Update(p_elapsedMs);
	m_insideEntity->Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00455ed0
void MagnetAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateDone) {
		p_renderer->DrawModelEntity(m_magnetEntity);
	}
}

// FUNCTION: LEGORACERS 0x00455ef0
void MagnetAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state == c_stateFade) {
		LegoFloat alphaScale = static_cast<LegoS32>(m_stateTimerMs) * 0.001f;
		LegoS32 alpha = static_cast<LegoS32>(alphaScale * g_magnetFadeAlpha);
		p_renderer->SetAlphaOverride(alpha, TRUE);
	}

	m_insideEntity->Draw(*p_renderer);
	m_ringEntity->Draw(*p_renderer);

	if (m_state == c_stateFade) {
		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x00455f50
void MagnetAction::AdvanceState()
{
	if (m_state == c_stateFade) {
		m_state = c_stateDone;
		return;
	}

	m_state = c_stateFade;
	m_stateTimerMs = c_fadeDurationMs;

	SoundVector position;
	m_magnetEntity->GetPosition(&position);
	m_soundSource->PlaySpatialSoundById(
		c_soundRelease,
		&position,
		g_magnetSoundMinDistance,
		g_magnetSoundMaxDistance,
		1.0f,
		1.0f
	);
}

// FUNCTION: LEGORACERS 0x00455fb0
void MagnetAction::OnHitRacer(Racer* p_racer)
{
	if (m_state == c_stateFade) {
		return;
	}

	if (m_state == c_stateArmed) {
		m_state = c_stateHolding;
		m_stateTimerMs = c_holdDurationMs;
	}

	if (m_state == c_stateHolding) {
		SoundVector modelPosition;
		GolVec3 racerPosition;
		m_magnetEntity->GetPosition(&modelPosition);
		modelPosition.m_z -= g_magnetHoldHeightOffset;
		p_racer->m_visuals.m_carEntity->GetPosition(&racerPosition);

		GolVec3 delta;
		delta.m_x = modelPosition.m_x - racerPosition.m_x;
		delta.m_y = modelPosition.m_y - racerPosition.m_y;
		delta.m_z = modelPosition.m_z - racerPosition.m_z;
		LegoFloat distanceSquared = delta.m_x * delta.m_x + delta.m_y * delta.m_y + delta.m_z * delta.m_z;

		if (distanceSquared <= g_magnetGrabDistanceSquared) {
			if (m_heldRacer == NULL) {
				m_heldRacer = p_racer;
				p_racer->StartMagnetHold();
				m_pulledRacer = NULL;
				m_soundSource->PlaySpatialSoundById(
					c_soundGrab,
					&modelPosition,
					g_magnetSoundMinDistance,
					g_magnetSoundMaxDistance,
					1.0f,
					1.0f
				);
				p_racer->PlayReaction(FALSE);
			}
		}
		else if (m_pulledRacer == NULL) {
			m_pulledRacer = p_racer;
		}
	}
}

// FUNCTION: LEGORACERS 0x004560b0
void MagnetAction::Deploy()
{
	SoundVector position;
	ComputeDropPosition(m_ownerRacer, &position, NULL);

	position.m_z += g_magnetHoldHeightOffset;
	m_magnetEntity->SetPosition(position);
	position.m_z -= g_magnetHoldHeightOffset;
	m_ringEntity->CopyPositionFrom(*m_magnetEntity);
	m_insideEntity->CopyPositionFrom(*m_magnetEntity);

	m_magnetEntity->SetFlags(m_magnetEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_magnetEntity->PlayPart(0);
	m_ringEntity->SetFlags(m_ringEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_ringEntity->PlayPart(0);
	m_insideEntity->SetFlags(m_insideEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_insideEntity->PlayPart(0);

	if (m_ownerRacer->m_checkpoint != NULL) {
		m_direction = m_ownerRacer->m_checkpoint->m_planeNormal;
	}
	else {
		m_direction.m_x = 1.0f;
		m_direction.m_y = 0.0f;
		m_direction.m_z = 0.0f;
	}

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	m_magnetEntity->SetDirectionUp(m_direction, up);

	m_worldEntity.SetPosition(position);
	m_worldEntity.SetBoundsRadius(g_magnetTriggerRadius);
	m_ownerRacer->m_physics.ApplyPitchImpulse(0.0015f, 150);
	m_soundSource->PlaySpatialSoundById(
		c_soundDeploy,
		&position,
		g_magnetSoundMinDistance,
		g_magnetSoundMaxDistance,
		1.0f,
		1.0f
	);

	m_sound = m_soundSource->AcquireSoundById(c_soundLoop);
	m_sound->Play(TRUE);
	m_sound->SetDistanceRange(g_magnetSoundMinDistance, g_magnetSoundMaxDistance);
	m_sound->SetPosition(position);
	m_sound->ClearVelocity();

	m_state = c_stateArmed;
	m_stateTimerMs = c_armedDurationMs;

	LegoEventQueue::Descriptor descriptor;
	descriptor.m_type = 4;
	descriptor.m_flags = 1;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_data = &m_worldEntity;
	m_collisionEvent = m_raceState->GetEventQueue()->AllocateEvent(this, &descriptor);
}
