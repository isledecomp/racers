#include "race/events/soundresource.h"

#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "race/racer/racersoundsource.h"

DECOMP_SIZE_ASSERT(SoundResource::InitParams, 0x4c)
DECOMP_SIZE_ASSERT(SoundResource, 0x5c)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x00464130
SoundResource::SoundResource()
{
	m_sound = NULL;
	m_soundSource = NULL;
	m_flags = 0;
	m_trackedEntity = NULL;
	m_nodeIndex = 0;
	m_probability = 0xff;
}

// FUNCTION: LEGORACERS 0x00464160
SoundResource::~SoundResource()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004641b0
void SoundResource::Initialize(InitParams* p_params)
{
	if (m_state) {
		Destroy();
	}

	m_eventId = p_params->m_eventId;
	m_soundSource = p_params->m_soundSource;
	m_soundId = p_params->m_soundId;
	m_unk0x40 = p_params->m_unk0x1c;
	m_volume = p_params->m_volume;
	m_frequencyScale = p_params->m_frequencyScale;
	m_minDistance = p_params->m_minDistance;
	m_maxDistance = p_params->m_maxDistance;
	m_position.m_x = p_params->m_position.m_x;
	m_position.m_y = p_params->m_position.m_y;
	m_position.m_z = p_params->m_position.m_z;
	m_trackedEntity = p_params->m_entity;
	m_nodeIndex = p_params->m_nodeIndex;
	m_probability = static_cast<LegoU8>(p_params->m_probability * 255.0f);

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	m_retriggerDelayMs =
		static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % c_randomDelayRangeMs + c_randomDelayBaseMs;

	if (p_params->m_looping) {
		m_flags |= c_flagLooping;
	}
	if (p_params->m_noEnd) {
		m_flags |= c_flagNoEnd;
	}
	if (p_params->m_triggerOnEnd) {
		m_flags |= c_flagTriggerOnEnd;
	}
	if (p_params->m_positional) {
		m_flags |= c_flagAtEventPosition;
	}

	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x00464290
void SoundResource::Destroy()
{
	if (m_sound) {
		m_soundSource->ReleaseSound(m_sound);
		m_sound = NULL;
	}

	m_soundSource = NULL;
	m_trackedEntity = NULL;
	m_nodeIndex = 0;
	m_flags = 0;
	Reset();
}

// FUNCTION: LEGORACERS 0x004642c0
void SoundResource::OnStartAt(GolVec3* p_position)
{
	if (p_position && (m_flags & c_flagAtEventPosition)) {
		m_position.m_x = p_position->m_x;
		m_position.m_y = p_position->m_y;
		m_position.m_z = p_position->m_z;
	}

	if (m_probability < c_probabilityMax) {
		m_state = c_stateActive;
		return;
	}

	if (m_trackedEntity) {
		StopSound();
	}

	if (!(m_flags & c_flagLooping)) {
		m_soundSource
			->PlaySpatialSoundById(m_soundId, &m_position, m_minDistance, m_maxDistance, m_volume, m_frequencyScale);
		return;
	}

	m_sound = m_soundSource->AcquireSoundById(m_soundId);
	if (m_sound) {
		m_sound->Play(TRUE);
		m_sound->SetDistanceRangeWithMinSquared(m_minDistance * m_minDistance, m_maxDistance);
		m_sound->SetVolume(m_volume);
		m_sound->SetFrequencyScale(m_frequencyScale);
		m_sound->SetPosition(&m_position);

		GolVec3 velocity;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;
		m_sound->SetVelocity(velocity);
		m_state = c_stateActive;
	}
}

// FUNCTION: LEGORACERS 0x004643b0
void SoundResource::OnEnd()
{
	if (m_sound) {
		m_soundSource->ReleaseSound(m_sound);
		m_sound = NULL;
	}

	m_state = c_stateIdle;
}

// FUNCTION: LEGORACERS 0x004643e0
void SoundResource::Update(LegoU32 p_elapsedMs)
{
	RaceEventResource::Update(p_elapsedMs);
	if (m_state == c_stateIdle) {
		return;
	}

	if (m_retriggerDelayMs > p_elapsedMs) {
		m_retriggerDelayMs -= p_elapsedMs;
	}
	else {
		m_retriggerDelayMs = 0;
	}

	if (m_trackedEntity) {
		StopSound();
	}

	if (m_probability >= c_probabilityMax || m_retriggerDelayMs) {
		return;
	}

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	m_retriggerDelayMs =
		static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % c_randomDelayRangeMs + c_randomDelayBaseMs;

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	if (static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_probabilityMax >= m_probability) {
		return;
	}

	m_soundSource
		->PlaySpatialSoundById(m_soundId, &m_position, m_minDistance, m_maxDistance, m_volume, m_frequencyScale);
}

// FUNCTION: LEGORACERS 0x004644b0
void SoundResource::StopSound()
{
	GolSceneNode* node = m_trackedEntity->GetSceneNode(0);
	GolTransformBase* transform = node->GetTransform(m_nodeIndex);

	GolVec3 position;
	position.m_x = 0.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	GolVec3 transformedPosition;

	do {
		transformedPosition = position;
		transform->TransformPoint(&transformedPosition, &position);
		transform = transform->m_parent;
	} while (transform);

	LegoFloat scale = m_trackedEntity->GetModel(0)->GetScale() * m_trackedEntity->GetScale();
	position.m_x = position.m_x * scale;
	position.m_y = position.m_y * scale;
	position.m_z = position.m_z * scale;

	m_trackedEntity->LocalToWorld(position, &m_position);
	if (m_sound) {
		m_sound->SetPosition(&m_position);
	}
}

#pragma code_seg(".text$kbd_vt20")
// FUNCTION: LEGORACERS 0x0044f2e0 FOLDED
LegoU32 SoundResource::GetKind()
{
	return 0;
}
#pragma code_seg()
