#include "race/hazards/ghosthazard.h"

#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "cmbmodelpart.h"
#include "cmbmodelpartdata.h"
#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "menu/runtime/cutsceneanimation.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/hazards/hazardcontext.h"
#include "race/racer/racer.h"
#include "race/racer/racersoundsource.h"
#include "race/racestate.h"
#include "render/gold3drenderdevice.h"
#include "types.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(GhostHazard, 0x220)

extern LegoFloat g_cosineTable[1024];
extern const LegoFloat g_negativeRadiansToTableIndex;
extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern LegoFloat g_carBuildPreviewMouseScale;
extern const LegoFloat g_hazardPi;

// GLOBAL: LEGORACERS 0x004b43c0
extern const LegoFloat g_ghostLoopSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b43c4
extern const LegoFloat g_ghostSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b43c8
extern const LegoFloat g_ghostOneShotSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b43cc
extern const LegoFloat g_ghostTriggerRadiusPadding = 8.0f;

// GLOBAL: LEGORACERS 0x004b43d0
extern const LegoFloat g_ghostImpulseVectorZ = 150.0f;

// GLOBAL: LEGORACERS 0x004b43d4
extern const LegoFloat g_ghostFrequencyScaleJitter = 0.4f;

// GLOBAL: LEGORACERS 0x004b43d8
extern const LegoFloat g_ghostRacerSearchDistanceSquared = 3600.0f;

// FUNCTION: LEGORACERS 0x0048c850
GhostHazard::GhostHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048c8e0
GhostHazard::~GhostHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048c930
void GhostHazard::ClearFields()
{
	m_loopSound = NULL;
	m_soundSource = NULL;
	m_ghostEntity = NULL;
	m_trailModel = NULL;
	m_eventQueue = NULL;
	m_collisionEvent = NULL;
	m_particleAnimation = NULL;
	m_trailParticle = NULL;
	m_raceState = NULL;
	m_unk0x5c = 0;
	m_animationFrameCount = 0;
	m_soundJitterMs = 0;
	m_frequencyJitter = 0.0f;
	m_racerSearchMs = 0;
}

// FUNCTION: LEGORACERS 0x0048c960
void GhostHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	HazardContext* context = p_context;
	m_triggerId = 10;
	m_eventTable = context->GetEventTable();
	m_eventQueue = context->GetEventQueue();
	m_particleAnimation = context->GetParticleAnimation();
	m_soundSource = context->GetSoundSource();
	m_raceState = context->GetRaceState();

	m_ghostEntity = context->GetTrackDatabase()->FindAnimatedEntity("ghostly");
	m_trailModel = context->GetTrackDatabase()->FindModelEntity("gtrail");

	{
		GolModelEntity* modelEntity = m_trailModels;
		LegoS32 i = sizeOfArray(m_trailModels);
		do {
			modelEntity->SetPrimaryModel(m_trailModel->GetModel(0), m_trailModel->GetModelDistance(0));
			modelEntity++;
		} while (--i);
	}

	LegoS32 i;
	for (i = 0; i < sizeOfArray(m_trailModels); i++) {
		m_trailModel->SetModelDistance(i, 0.0f);
	}

	m_trigger.SetBoundsRadius(m_ghostEntity->GetModel(0)->GetRadius() + g_ghostTriggerRadiusPadding);

	LegoU32 frameCount = 0;
	CmbModelPartData* partData = m_ghostEntity->GetModelPart()->GetPartData();
	LegoFloat inverseDuration = 1.0f / partData->GetMsPerFrame();
	frameCount = partData->GetFrameCount();
	LegoFloat frameCountFloat = static_cast<LegoFloat>(frameCount);
	m_animationFrameCount = static_cast<LegoS32>(inverseDuration * frameCountFloat);
	m_racerSearchMs = 0;
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048ca80
LegoS32 GhostHazard::Reset()
{
	OnDeactivate(NULL);

	GolModelEntity* modelEntity = m_trailModels;
	LegoS32 i = sizeOfArray(m_trailModels);
	do {
		modelEntity->ResetModelState();
		modelEntity++;
	} while (--i);

	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048cac0
void GhostHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_type = 4;
	descriptor.m_flags = 1;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_worldEntity = &m_trigger;

	m_collisionEvent = m_eventQueue->AllocateEvent(this, &descriptor);
	m_unk0x5c = 0;
	m_soundJitterMs = 0x1f4;
	m_loopSound = m_soundSource->AcquireSoundById(c_soundLoop);

	if (m_loopSound != NULL) {
		m_loopSound->Play(TRUE);
		m_loopSound->SetDistanceRangeWithMinSquared(
			g_ghostLoopSoundMinDistance * g_ghostLoopSoundMinDistance,
			g_ghostSoundMaxDistance
		);
	}

	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048cb60
void GhostHazard::OnDeactivate(void*)
{
	if (m_trailParticle != NULL) {
		m_particleAnimation->FinishRef(m_trailParticle);
		m_trailParticle = NULL;
	}

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	if (m_loopSound != NULL) {
		m_soundSource->ReleaseSound(m_loopSound);
		m_loopSound = NULL;
	}

	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048cbb0
void GhostHazard::Update(undefined4 p_elapsedMs)
{
	LegoU32 elapsedMs = static_cast<LegoU32>(p_elapsedMs);
	m_racerSearchMs += elapsedMs;

	if (m_state != c_stateLoaded) {
		LegoU32 frameOffset;
		LegoU32 frame = static_cast<LegoS32>(m_ghostEntity->GetPartTimeMs() / m_ghostEntity->GetMsPerFrame());
		LegoFloat scale = m_ghostEntity->GetModel(0)->GetScale() * m_ghostEntity->GetScale();
		GolSceneNode* node = m_ghostEntity->GetSceneNode(0);
		GolTransformBase* transform = node->GetTransform(1);

		Hazard::Update(elapsedMs);

		SoundVector position;
		transform->GetPosition(&position);
		position.m_x *= scale;
		position.m_y *= scale;
		position.m_z *= scale;

		GolVec3 worldPosition;
		m_ghostEntity->LocalToWorld(position, &worldPosition);
		m_trigger.SetBoundsCenter(worldPosition);

		if (m_trailParticle == NULL) {
			m_trailParticle = m_particleAnimation->SpawnParticle("ghsttrl", NULL, NULL, NULL);
		}

		if (m_trailParticle != NULL) {
			worldPosition.m_z -= 5.0f;
			if (m_trailParticle->m_particle != NULL) {
				m_trailParticle->m_particle->SetPosition(&worldPosition);
			}
			worldPosition.m_z += 5.0f;
		}

		if (m_racerSearchMs > c_racerSearchIntervalMs) {
			m_racerSearchMs = 0;
			if (m_raceState->FindNearestRacerInRange(&position, 0.0f, g_ghostRacerSearchDistanceSquared) != NULL) {
				m_soundSource->PlaySpatialSoundById(
					c_soundNear,
					&position,
					g_ghostOneShotSoundMinDistance,
					g_ghostSoundMaxDistance,
					1.0f,
					1.0f
				);
			}
		}

		GolModelEntity* modelEntity;
		for (frameOffset = c_trailFrameOffsetStep, modelEntity = m_trailModels; frameOffset < c_trailFrameOffsetEnd;
			 frameOffset += c_trailFrameOffsetStep, modelEntity++) {
			LegoU32 trailFrame;
			if (frameOffset < frame) {
				trailFrame = frame - frameOffset;
			}
			else {
				trailFrame = m_animationFrameCount - frameOffset + frame;
			}

			GolQuat rotation;
			m_ghostEntity->SamplePartRotation(0, 1, 0, trailFrame, &rotation);
			m_ghostEntity->SamplePartPosition(0, 1, 0, trailFrame, &position);

			GolMatrix3 orientation;
			GolMath::QuatToMatrix3(&rotation, &orientation.m_m[0][0]);
			modelEntity->SetOrientationMatrix(orientation);

			position.m_x *= scale;
			position.m_y *= scale;
			position.m_z *= scale;
			modelEntity->SetPosition(position);
		}

		if (m_loopSound != NULL) {
			m_ghostEntity->LocalToWorld(position, &worldPosition);
			m_loopSound->SetPosition(&worldPosition);

			LegoU32 soundElapsedMs = m_soundJitterMs;
			soundElapsedMs += static_cast<LegoU32>(p_elapsedMs);
			m_soundJitterMs = soundElapsedMs;
			if (soundElapsedMs >= c_soundFrequencyUpdateMs) {
				m_soundJitterMs = 0;

				LegoU32 randomIndex = g_randomTableIndex + 1;
				randomIndex &= c_randomTableMask;
				g_randomTableIndex = randomIndex;

				LegoU16 randomValue = g_randomTable[randomIndex];
				LegoS32 randomFrequency = randomValue;
				randomFrequency %= c_randomFrequencyVariantCount;
				LegoFloat frequencyScale = static_cast<LegoFloat>(randomFrequency);
				frequencyScale *= g_carBuildPreviewMouseScale;
				frequencyScale *= g_ghostFrequencyScaleJitter;
				m_frequencyJitter = frequencyScale;
			}

			LegoFloat phase = static_cast<LegoFloat>(static_cast<LegoS32>(m_soundJitterMs));
			phase *= 0.002f;
			phase *= g_hazardPi;
			phase *= g_negativeRadiansToTableIndex;
			LegoS32 index = 0xffffff00 - static_cast<LegoS32>(phase);
			index &= c_randomTableMask;
			m_loopSound->SetFrequencyScale(1.0f - g_cosineTable[index] * m_frequencyJitter);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048ce90
void GhostHazard::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	Racer* racer = static_cast<Racer*>(p_data->m_data);
	RacerPhysics* physics = &racer->m_physics;

	if ((physics->m_flags & RacerPhysics::c_flagSpinning) || physics->m_forwardSpeed == 0.0f ||
		(racer->m_flags & Racer::c_flagShielded)) {
		return;
	}

	physics->StartSpin(1.0f, 0.01f, 0.0f);
	racer->StartSpinOut();

	GolVec3 impulse;
	impulse.m_y = 0.0f;
	impulse.m_z = 0.0f;

	physics->m_velocity.m_x = 0.0f;
	physics->m_velocity.m_y = impulse.m_y;
	physics->m_velocity.m_z = impulse.m_z;

	impulse.m_y = impulse.m_x = 0.0f;
	LegoFloat impulseZ = g_ghostImpulseVectorZ;
	impulse.m_z = impulseZ;
	physics->ApplyImpulse(&impulse, &impulse);

	racer->PlayReaction(FALSE);

	SoundVector position;
	racer->m_visuals.m_carEntity->GetPosition(&position);
	m_soundSource->PlaySpatialSoundById(
		c_soundHit,
		&position,
		g_ghostOneShotSoundMinDistance,
		g_ghostSoundMaxDistance,
		1.0f,
		1.0f
	);
}

// FUNCTION: LEGORACERS 0x0048cf90
void GhostHazard::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateLoaded) {
		LegoS32 alpha = 0x2a;
		GolModelEntity* modelEntity = &m_trailModels[2];
		LegoS32 i = sizeOfArray(m_trailModels);

		do {
			p_renderer->SetAlphaOverride(alpha, TRUE);
			p_renderer->DrawModelEntity(modelEntity);
			alpha += 0x2a;
			modelEntity--;
		} while (--i);

		p_renderer->ClearAlphaOverride();
	}
}
