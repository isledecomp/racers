#include "audio/soundinstancebase0x38.h"

DECOMP_SIZE_ASSERT(SoundInstanceBase0x38, 0x38)

// GLOBAL: LEGORACERS 0x004afab8
LegoFloat g_unk0x4afab8 = 1.0f;

// GLOBAL: LEGORACERS 0x004afabc
LegoFloat g_unk0x4afabc = 0.0f;

// GLOBAL: LEGORACERS 0x004afac0
LegoFloat g_unk0x4afac0 = 1.0f;

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void SoundInstanceBase0x38::Stop()
{
}

// FUNCTION: LEGORACERS 0x00417bf0
SoundInstanceBase0x38::SoundInstanceBase0x38()
{
	m_volume = g_unk0x4afab8;
	m_frequencyScale = g_unk0x4afac0;
	m_spatialVolume = g_unk0x4afab8;
	m_spatialPan = g_unk0x4afabc;
	m_spatialFrequencyScale = g_unk0x4afac0;
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	m_velocityX = 0.0f;
	m_velocityY = 0.0f;
	m_velocityZ = 0.0f;
	m_minDistanceSquared = 8.0f;
	m_maxDistanceSquared = 1024.0f;
}

// FUNCTION: LEGORACERS 0x00417c70
SoundInstanceBase0x38::~SoundInstanceBase0x38()
{
}

// STUB: LEGORACERS 0x00417ff0
void SoundInstanceBase0x38::UpdateSpatial(SoundNode*)
{
	STUB(0x417ff0);
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 SoundInstanceBase0x38::IsPlaying()
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
FrostPetal0x34* SoundInstanceBase0x38::VTable0x10()
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SoundInstanceBase0x38::Play(LegoBool32)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SoundInstanceBase0x38::VTable0x14(undefined4)
{
}
