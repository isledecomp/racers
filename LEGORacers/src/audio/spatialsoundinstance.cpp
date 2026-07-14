#include "audio/spatialsoundinstance.h"

#include "audio/directsoundgroup.h"
#include "audio/soundmanager.h"
#include "audio/soundnode.h"

#include <math.h>

DECOMP_SIZE_ASSERT(SpatialSoundInstance, 0x38)

// GLOBAL: LEGORACERS 0x004afab8
const LegoFloat g_defaultSpatialVolume = 1.0f;

// GLOBAL: LEGORACERS 0x004afabc
const LegoFloat g_defaultSpatialPan = 0.0f;

// GLOBAL: LEGORACERS 0x004afac0
const LegoFloat g_defaultSpatialFrequencyScale = 1.0f;

// GLOBAL: LEGORACERS 0x004afac4
const LegoFloat g_defaultSoundSpeed = 343.0f;

// GLOBAL: LEGORACERS 0x004afac8
const LegoFloat g_negativePanScale = -0.7f;

// GLOBAL: LEGORACERS 0x004afacc
const LegoFloat g_positivePanScale = 0.7f;

inline LegoFloat DotVectors(const GolVec3& p_left, const GolVec3& p_right)
{
	LegoFloat result = p_left.m_z;
	LegoFloat z = p_right.m_z;
	result *= z;
	LegoFloat y = p_left.m_y;
	y *= p_right.m_y;
	result += y;
	result += p_left.m_x * p_right.m_x;

	return result;
}

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
	LegoFloat yDistanceSquared = GOL_SQUARED(m_position.m_y);
	LegoFloat distanceSquared = m_position.m_z;
	distanceSquared *= m_position.m_z;
	LegoFloat squaredComponent = m_position.m_y;
	squaredComponent *= m_position.m_y;
	distanceSquared += squaredComponent;
	LegoFloat xDistanceSquared = m_position.m_x;
	xDistanceSquared *= m_position.m_x;
	distanceSquared += xDistanceSquared;

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
			LegoFloat pan;
			if (m_position.m_y > 0.0f) {
				pan = yDistanceSquared / distanceSquared * g_negativePanScale;
			}
			else {
				pan = yDistanceSquared / distanceSquared * g_positivePanScale;
			}

			m_spatialPan = g_defaultSpatialPan + pan;

			LegoFloat distance = sqrt(distanceSquared);
			LegoFloat inverseDistance = distance;
			if (inverseDistance != 0.0f) {
				inverseDistance = -1.0f / distance;
				SoundVector direction;
				direction.m_x = inverseDistance * m_position.m_x;
				direction.m_y = m_position.m_y;
				direction.m_y *= inverseDistance;
				direction.m_z = inverseDistance * m_position.m_z;
				LegoFloat velocity = DotVectors(m_velocity, direction);
				LegoFloat maxVelocity = g_defaultSoundSpeed * 0.5f;

				if (velocity > maxVelocity) {
					velocity = maxVelocity;
				}

				LegoFloat frequency = m_frequencyScale;
				frequency *= g_defaultSoundSpeed;
				m_spatialFrequencyScale = frequency / (g_defaultSoundSpeed - velocity);
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
	SoundVector nodePosition = p_node->m_position;
	SoundVector relativePosition;
	relativePosition.m_x = m_position.m_x - nodePosition.m_x;
	relativePosition.m_y = m_position.m_y - nodePosition.m_y;
	relativePosition.m_z = m_position.m_z - nodePosition.m_z;
	LegoFloat distanceSquared = DotVectors(relativePosition, relativePosition);

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
			LegoFloat dot = (orientation.m_z * relativePosition.m_z) + (orientation.m_y * relativePosition.m_y) +
							(orientation.m_x * relativePosition.m_x);
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
			LegoFloat inverseDistance = distance;
			if (inverseDistance != 0.0f) {
				LegoFloat nodeVelocityX = p_node->m_velocity.m_x;
				inverseDistance = -1.0f / distance;
				LegoFloat nodeVelocityY = p_node->m_velocity.m_y;
				LegoFloat nodeVelocityZ = p_node->m_velocity.m_z;
				LegoFloat xVelocity = m_velocity.m_x - nodeVelocityX;
				LegoFloat yVelocity = m_velocity.m_y - nodeVelocityY;
				LegoFloat zVelocity = m_velocity.m_z - nodeVelocityZ;
				LegoFloat xDirection = relativePosition.m_x * inverseDistance;
				LegoFloat yDirection = relativePosition.m_y * inverseDistance;
				LegoFloat zDirection = relativePosition.m_z * inverseDistance;
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

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SpatialSoundInstance::Play(LegoBool32)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SpatialSoundInstance::SetPriority(undefined4)
{
}
