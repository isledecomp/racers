#include "audio/spatialsoundinstance.h"

#include "audio/directsoundgroup.h"
#include "audio/soundmanager.h"
#include "audio/soundnode.h"

#include <math.h>

DECOMP_SIZE_ASSERT(SpatialSoundInstance, 0x38)

// GLOBAL: LEGORACERS 0x004afab8
LegoFloat g_defaultSpatialVolume = 1.0f;

// GLOBAL: LEGORACERS 0x004afabc
LegoFloat g_defaultSpatialPan = 0.0f;

// GLOBAL: LEGORACERS 0x004afac0
LegoFloat g_defaultSpatialFrequencyScale = 1.0f;

// GLOBAL: LEGORACERS 0x004afac4
LegoFloat g_defaultSoundSpeed = 343.0f;

// GLOBAL: LEGORACERS 0x004afac8
LegoFloat g_negativePanScale = -0.7f;

// GLOBAL: LEGORACERS 0x004afacc
LegoFloat g_positivePanScale = 0.7f;

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void SpatialSoundInstance::Stop()
{
}

// FUNCTION: LEGORACERS 0x00417bf0
SpatialSoundInstance::SpatialSoundInstance()
{
	m_volume = g_defaultSpatialVolume;
	m_frequencyScale = g_defaultSpatialFrequencyScale;
	m_spatialVolume = g_defaultSpatialVolume;
	m_spatialPan = g_defaultSpatialPan;
	m_spatialFrequencyScale = g_defaultSpatialFrequencyScale;
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_minDistanceSquared = 8.0f;
	m_maxDistanceSquared = 1024.0f;
}

// FUNCTION: LEGORACERS 0x00417c70
SpatialSoundInstance::~SpatialSoundInstance()
{
}

// FUNCTION: LEGORACERS 0x00417c80
void SpatialSoundInstance::UpdateSpatialFromOrigin()
{
	LegoFloat yDistanceSquared = m_position.m_y;
	yDistanceSquared *= yDistanceSquared;

	LegoFloat distanceSquared = m_position.m_z * m_position.m_z;
	distanceSquared += m_position.m_y * m_position.m_y;
	distanceSquared += m_position.m_x * m_position.m_x;

	if (distanceSquared <= m_minDistanceSquared) {
		m_spatialVolume = m_volume;
	}
	else {
		if (distanceSquared >= m_maxDistanceSquared) {
			m_spatialVolume = 0.0f;
			return;
		}

		m_spatialVolume = m_volume * m_minDistanceSquared / distanceSquared;
	}

	if (m_spatialVolume != 0.0f) {
		if (distanceSquared == 0.0f) {
			m_spatialPan = g_defaultSpatialPan;
			m_spatialFrequencyScale = m_frequencyScale;
		}
		else {
			LegoFloat pan = yDistanceSquared / distanceSquared;
			if (m_position.m_y > 0.0f) {
				pan *= g_negativePanScale;
			}
			else {
				pan *= g_positivePanScale;
			}

			m_spatialPan = g_defaultSpatialPan + pan;

			LegoFloat distance = sqrt(distanceSquared);
			if (0.0f != distance) {
				LegoFloat inverseDistance = -1.0f / distance;
				LegoFloat xDirection = inverseDistance * m_position.m_x;
				LegoFloat yDirection = inverseDistance * m_position.m_y;
				LegoFloat velocity = (inverseDistance * m_position.m_z) * m_velocity.m_z;
				velocity += m_velocity.m_y * yDirection;
				velocity += m_velocity.m_x * xDirection;
				LegoFloat maxVelocity = g_defaultSoundSpeed * 0.5f;

				if (velocity > maxVelocity) {
					velocity = maxVelocity;
				}

				m_spatialFrequencyScale = m_frequencyScale * g_defaultSoundSpeed / (g_defaultSoundSpeed - velocity);
			}
			else {
				m_spatialFrequencyScale = m_frequencyScale;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00417de0
void SpatialSoundInstance::UpdateSpatialFromNode(SoundNode* p_node)
{
	LegoFloat z;
	LegoFloat y;
	LegoFloat x;
	SoundVector nodePosition = p_node->m_position;
	x = m_position.m_x - nodePosition.m_x;
	y = m_position.m_y - nodePosition.m_y;
	z = m_position.m_z - nodePosition.m_z;
	LegoFloat distanceSquared = (y * y) + (z * z) + (x * x);

	if (distanceSquared <= m_minDistanceSquared) {
		m_spatialVolume = m_volume;
	}
	else {
		if (distanceSquared >= m_maxDistanceSquared) {
			m_spatialVolume = 0.0f;
			return;
		}

		m_spatialVolume =
			(1.0f - ((distanceSquared - m_minDistanceSquared) / (m_maxDistanceSquared - m_minDistanceSquared))) *
			m_volume;
	}

	if (m_spatialVolume != 0.0f) {
		if (distanceSquared == 0.0f) {
			m_spatialPan = g_defaultSpatialPan;
			m_spatialFrequencyScale = m_frequencyScale;
		}
		else {
			SoundVector orientation = p_node->m_orientation;
			LegoFloat dot = (orientation.m_z * z) + (orientation.m_y * y) + (orientation.m_x * x);
			LegoFloat panScale;
			if (dot > 0.0f) {
				panScale = g_negativePanScale;
			}
			else {
				panScale = g_positivePanScale;
			}

			LegoFloat pan = dot * panScale;
			pan *= dot / distanceSquared;
			m_spatialPan = g_defaultSpatialPan + pan;

			LegoFloat distance = sqrt(distanceSquared);
			if (0.0f != distance) {
				LegoFloat inverseDistance = -1.0f / distance;
				SoundVector nodeVelocity = p_node->m_velocity;
				LegoFloat xVelocity = m_velocity.m_x - nodeVelocity.m_x;
				LegoFloat yVelocity = m_velocity.m_y - nodeVelocity.m_y;
				LegoFloat zVelocity = m_velocity.m_z - nodeVelocity.m_z;
				LegoFloat xDirection = x * inverseDistance;
				LegoFloat yDirection = y * inverseDistance;
				LegoFloat zDirection = z * inverseDistance;
				LegoFloat velocity = zDirection * zVelocity;
				velocity += yDirection * yVelocity;
				velocity += xDirection * xVelocity;

				if (velocity > p_node->m_maxVelocity) {
					velocity = p_node->m_maxVelocity;
				}

				m_spatialFrequencyScale = m_frequencyScale * p_node->m_soundSpeed / (p_node->m_soundSpeed - velocity);
			}
			else {
				m_spatialFrequencyScale = m_frequencyScale;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00417ff0
void SpatialSoundInstance::UpdateSpatial(SoundNode* p_node)
{
	if (!p_node) {
		UpdateSpatialFromOrigin();
		return;
	}

	if (!p_node->m_nextActiveSoundNode) {
		UpdateSpatialFromNode(p_node);
		return;
	}

	LegoS32 activeNodeCount = 0;
	LegoFloat weightedFrequency = 0.0f;
	LegoFloat weightedVolume = 0.0f;
	LegoFloat weightedPan = 0.0f;
	LegoFloat volume = 0.0f;

	do {
		UpdateSpatialFromNode(p_node);
		if (m_spatialVolume != 0.0f) {
			activeNodeCount++;

			if (volume < m_spatialVolume) {
				volume = m_spatialVolume;
			}

			weightedVolume += m_spatialVolume;
			weightedPan = (m_spatialPan * m_spatialVolume) + weightedPan;
			weightedFrequency = (m_spatialFrequencyScale * m_spatialVolume) + weightedFrequency;
		}

		p_node = p_node->m_nextActiveSoundNode;
	} while (p_node);

	if (activeNodeCount) {
		m_spatialVolume = volume;
		m_spatialPan = weightedPan / weightedVolume;
		m_spatialFrequencyScale = weightedFrequency / weightedVolume;
	}
	else {
		m_spatialVolume = 0.0f;
		m_spatialPan = 0.0f;
		m_spatialFrequencyScale = 1.0f;
	}
}

// FUNCTION: LEGORACERS 0x004180e0
void SpatialSoundInstance::SetVolume(LegoFloat p_volume)
{
	DirectSoundGroup* soundGroup = GetSoundGroup();
	SoundManager* soundManager = soundGroup->GetSoundManager();
	m_volume = soundManager->GetVolumeScale() * p_volume;
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 SpatialSoundInstance::IsPlaying()
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
DirectSoundGroup* SpatialSoundInstance::GetSoundGroup()
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SpatialSoundInstance::Play(LegoBool32)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SpatialSoundInstance::VTable0x14(undefined4)
{
}
