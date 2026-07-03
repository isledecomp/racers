#include "race/hazards/lavageyserhazard.h"

#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "menu/runtime/cutsceneanimation.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "race/racer/racer.h"
#include "race/racer/racersoundsource.h"
#include "types.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(LavaGeyserHazard, 0x5c)

extern const LegoFloat g_unk0x004afde0;

// GLOBAL: LEGORACERS 0x004b44b8
extern const LegoFloat g_lavaGeyserSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b44bc
extern const LegoFloat g_lavaGeyserSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b44c8
extern const LegoFloat g_lavaGeyserLavaStartFrames[3] = {0.0f, 61.0f, 119.0f};

// GLOBAL: LEGORACERS 0x004b44d4
extern const LegoFloat g_lavaGeyserLavaEndFrames[3] = {26.0f, 86.0f, 146.0f};

// GLOBAL: LEGORACERS 0x004c22d8
extern const GolVec3 g_lavaGeyserLavaPositions[3] = {
	{577.0f, -444.0f, 7.3340001f},
	{605.0f, -500.0f, 19.0f},
	{525.0f, -505.0f, 4.6f},
};

// FUNCTION: LEGORACERS 0x0048d7f0
LavaGeyserHazard::LavaGeyserHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048d870
LavaGeyserHazard::~LavaGeyserHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048d8c0
LegoS32 LavaGeyserHazard::ClearFields()
{
	m_eventQueue = NULL;
	m_collisionEvent = NULL;
	m_particleAnimation = NULL;
	m_entity = NULL;
	m_loopSound = NULL;
	m_soundSource = NULL;
	m_smokeMs = 0;
	m_eventMs = 0;
	m_unk0x58 = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x0048d8e0
void LavaGeyserHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0;
	m_eventTable = p_context->GetEventTable();
	m_eventQueue = p_context->GetEventQueue();
	m_particleAnimation = p_context->GetParticleAnimation();
	m_soundSource = p_context->GetSoundSource();
	m_unk0x58 = p_context->GetMirror();
	m_entity = p_context->GetTrackDatabase()->FindAnimatedEntity("mmlavbl");
	m_trigger.SetBoundsRadius(m_entity->GetModel(0)->GetRadius());
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048d960
LegoS32 LavaGeyserHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048d980
void LavaGeyserHazard::OnActivate(void*)
{
	LegoEventQueue::Descriptor descriptor;
	m_smokeMs = 0;
	m_eventMs = 0;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_type = 4;
	descriptor.m_flags = 1;
	descriptor.m_worldEntity = &m_trigger;

	m_collisionEvent = m_eventQueue->AllocateEvent(this, &descriptor);
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048d9d0
void LavaGeyserHazard::OnDeactivate(void*)
{
	if (m_collisionEvent) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	if (m_loopSound) {
		m_soundSource->ReleaseSound(m_loopSound);
		m_loopSound = NULL;
	}

	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048da10
void LavaGeyserHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	LegoFloat frame = m_entity->GetPartTimeMs();
	LegoFloat scale = m_entity->GetModel(0)->GetScale() * m_entity->GetScale();
	GolSceneNode* node = m_entity->GetSceneNode(0);
	GolTransformBase* transform = node->GetTransform(0);
	LegoU32 elapsedMs = p_elapsedMs;
	Hazard::Update(p_elapsedMs);

	{
		GolVec3 localPosition;
		transform->GetPosition(&localPosition);
		localPosition.m_x *= scale;
		localPosition.m_y *= scale;
		localPosition.m_z *= scale;

		GolVec3 position;
		m_entity->LocalToWorld(localPosition, &position);
		m_trigger.SetBoundsCenter(position);

		if (m_loopSound) {
			m_loopSound->SetPosition(&position);
		}
	}

	GolVec3 effectPosition;
	if (m_smokeMs == 0) {
		for (LegoS32 i = 0; i < c_lavaPositionCount; i++) {
			if (frame > g_lavaGeyserLavaStartFrames[i] && frame < g_lavaGeyserLavaEndFrames[i]) {
				effectPosition = g_lavaGeyserLavaPositions[i];
				if (m_unk0x58) {
					effectPosition.m_y = -effectPosition.m_y;
				}

				m_particleAnimation->SpawnParticle("lavasmk", &effectPosition, NULL, NULL);
				m_smokeMs = c_smokeCooldownMs;
			}
		}
	}
	else if (elapsedMs > m_smokeMs) {
		m_smokeMs = 0;
	}
	else {
		m_smokeMs -= elapsedMs;
	}

	if (m_eventMs == 0) {
		for (LegoS32 i = 0; i < c_lavaPositionCount; i++) {
			LegoFloat startFrame = g_lavaGeyserLavaStartFrames[i];
			startFrame += g_unk0x004afde0;
			if (frame > g_lavaGeyserLavaStartFrames[i] && startFrame > frame) {
				effectPosition = g_lavaGeyserLavaPositions[i];
				if (m_unk0x58) {
					effectPosition.m_y = -effectPosition.m_y;
				}

				m_eventTable->FireEventsAt(c_eventId, c_eventId, &effectPosition);
				m_eventMs = c_eventCooldownMs;
				if (m_loopSound) {
					m_soundSource->ReleaseSound(m_loopSound);
					m_loopSound = NULL;
				}
			}

			LegoFloat endFrame = g_lavaGeyserLavaEndFrames[i];
			endFrame += g_unk0x004afde0;
			if (frame > g_lavaGeyserLavaEndFrames[i] && endFrame > frame) {
				effectPosition = g_lavaGeyserLavaPositions[i];
				if (m_unk0x58) {
					effectPosition.m_y = -effectPosition.m_y;
				}

				m_eventTable->FireEventsAt(c_eventId, c_eventId, &effectPosition);
				m_eventMs = c_eventCooldownMs;
				m_loopSound = m_soundSource->AcquireSoundById(c_soundId);
				if (m_loopSound) {
					m_loopSound->Play(TRUE);
					LegoFloat maxDistance = g_lavaGeyserSoundMaxDistance;
					LegoFloat minDistance = g_lavaGeyserSoundMinDistance;
					m_loopSound->SetDistanceRangeWithMinSquared(minDistance * minDistance, maxDistance);
				}
			}
		}
	}
	else if (elapsedMs > m_eventMs) {
		m_eventMs = 0;
		return;
	}
	else {
		m_eventMs -= elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x0048dcd0
void LavaGeyserHazard::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	Racer* racer = static_cast<Racer*>(p_data->m_data);
	RacerPhysics* physics = &racer->m_physics;
	if (!(physics->m_flags & RacerPhysics::c_flagSpinning) && physics->m_forwardSpeed != 0.0f) {
		physics->StartSpin(1.0f, 0.01f, 0.0f);
		racer->PlayReaction(FALSE);
	}
}
