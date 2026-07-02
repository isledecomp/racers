#include "race/raceeventtable.h"

DECOMP_SIZE_ASSERT(RaceEventTable, 0x90)

// STUB: LEGORACERS 0x0045c660
LegoU32 RacePowerupManager::TargetPointList::DisableTargetPoints(undefined4 p_unk0x04)
{
	LegoU32 i = 0;
	if (static_cast<LegoU32>(m_count) > 0) {
		Entry* entry = m_entries;
		while (i < static_cast<LegoU32>(m_count)) {
			if (entry->m_index == p_unk0x04) {
				if (entry->m_flags0x10 & TargetPointList::Entry::c_flagEnabled) {
					entry->m_flags0x10 &= ~TargetPointList::Entry::c_flagEnabled;
				}
			}

			i++;
			entry++;
		}
	}

	return m_count;
}

// FUNCTION: LEGORACERS 0x0045ee50
void RaceEventTable::Resource::OnEventStart(GolVec3* p_unk0x04)
{
	if (!(m_flags0x1c & 4) && (m_state0x18 == 1 || m_state0x18 == 4)) {
		OnStartAt(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0045ee70
void RaceEventTable::Resource::OnEventEnd(GolVec3* p_unk0x04)
{
	if (m_flags0x1c & 4) {
		if (m_state0x18 == 1 || m_state0x18 == 4) {
			OnStartAt(p_unk0x04);

			if (!(m_flags0x1c & 2)) {
				OnEnd();
			}

			return;
		}
	}

	if (m_state0x18 != 1 && !(m_flags0x1c & 2)) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x0045eec0
void RaceEventTable::Resource::ForceEventStart(RaceState::Racer* p_racer)
{
	if (!(m_flags0x1c & 4) && (m_state0x18 == 1 || m_state0x18 == 4)) {
		OnStartForRacer(p_racer);
	}
}

// FUNCTION: LEGORACERS 0x00461ef0
LegoU32 RaceEventTable::StartEventsAt(undefined4 p_unk0x04, GolVec3* p_unk0x08)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_unk0x04) {
				m_sounds[i].OnEventStart(p_unk0x08);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_unk0x04) {
				m_partAnimations[i].OnEventStart(p_unk0x08);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_unk0x04) {
				m_materialAnimations[i].OnEventStart(p_unk0x08);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_unk0x04) {
				m_particles[i].OnEventStart(p_unk0x08);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_unk0x04) {
				m_skyStates[i].OnEventStart(p_unk0x08);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_unk0x04) {
				m_timers[i].OnEventStart(p_unk0x08);
			}

			if (m_timers[i].m_unk0x20 == p_unk0x04) {
				m_timers[i].m_flags0x2c |= 1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_unk0x04) {
				m_nodeTransforms[i].OnEventStart(p_unk0x08);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_unk0x04) {
				m_modelDistances[i].OnEventStart(p_unk0x08);
			}
		}
	}

	if (m_eventLinks) {
		for (LegoU32 i = 0; i < m_eventLinkCount; i++) {
			if (m_eventLinks[i].m_eventId == p_unk0x04) {
				ForceEvents(m_eventLinks[i].m_forcedEventId);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_unk0x30 == p_unk0x04) {
				m_externalForces[i].m_flags0x34 |= 1;
			}
		}
	}

	m_hazardManager->NotifyEventStart(p_unk0x04, p_unk0x08);
	return m_targetPoints->DisableTargetPoints(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00462140
void RaceEventTable::EndEventsAt(undefined4 p_unk0x04, GolVec3* p_unk0x08)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_unk0x04) {
				m_sounds[i].OnEventEnd(p_unk0x08);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_unk0x04) {
				m_partAnimations[i].OnEventEnd(p_unk0x08);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_unk0x04) {
				m_materialAnimations[i].OnEventEnd(p_unk0x08);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_unk0x04) {
				m_particles[i].OnEventEnd(p_unk0x08);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_unk0x04) {
				m_skyStates[i].OnEventEnd(p_unk0x08);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_unk0x04) {
				m_timers[i].OnEventEnd(p_unk0x08);
			}

			if (m_timers[i].m_unk0x20 == p_unk0x04) {
				m_timers[i].m_flags0x2c &= ~1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_unk0x04) {
				m_nodeTransforms[i].OnEventEnd(p_unk0x08);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_unk0x04) {
				m_modelDistances[i].OnEventEnd(p_unk0x08);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_unk0x30 == p_unk0x04) {
				m_externalForces[i].m_flags0x34 &= ~1;
			}
		}
	}

	m_hazardManager->NotifyEventEnd(p_unk0x04, p_unk0x08);
}

// FUNCTION: LEGORACERS 0x00462350
void RaceEventTable::ForceEvents(undefined4 p_unk0x04)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_unk0x04) {
				m_sounds[i].m_state0x18 = 5;
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_unk0x04) {
				m_partAnimations[i].m_state0x18 = 5;
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_unk0x04) {
				m_materialAnimations[i].m_state0x18 = 5;
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_unk0x04) {
				m_particles[i].m_state0x18 = 5;
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_unk0x04) {
				m_skyStates[i].m_state0x18 = 5;
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_unk0x04) {
				m_timers[i].m_state0x18 = 5;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_unk0x04) {
				m_nodeTransforms[i].m_state0x18 = 5;
			}
		}
	}

	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_unk0x04) {
				m_colorTransforms[i].m_state0x18 = 5;
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_unk0x04) {
				m_lapZones[i].m_state0x18 = 5;
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_unk0x04) {
				m_modelDistances[i].m_state0x18 = 5;
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_unk0x04) {
				m_lookTargets[i].m_state0x18 = 5;
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_unk0x04) {
				m_externalForces[i].m_state0x18 = 5;
			}
		}
	}

	m_hazardManager->ForceActivate(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00462580
void RaceEventTable::FireEventsAt(undefined4 p_unk0x04, undefined4 p_unk0x08, GolVec3* p_unk0x0c)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_unk0x04) {
				m_sounds[i].OnEventStart(p_unk0x0c);
			}

			if (m_sounds[i].m_eventId == p_unk0x08) {
				m_sounds[i].OnEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_unk0x04) {
				m_partAnimations[i].OnEventStart(p_unk0x0c);
			}

			if (m_partAnimations[i].m_eventId == p_unk0x08) {
				m_partAnimations[i].OnEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_unk0x04) {
				m_materialAnimations[i].OnEventStart(p_unk0x0c);
			}

			if (m_materialAnimations[i].m_eventId == p_unk0x08) {
				m_materialAnimations[i].OnEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_unk0x04) {
				m_particles[i].OnEventStart(p_unk0x0c);
			}

			if (m_particles[i].m_eventId == p_unk0x08) {
				m_particles[i].OnEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_unk0x04) {
				m_skyStates[i].OnEventStart(p_unk0x0c);
			}

			if (m_skyStates[i].m_eventId == p_unk0x08) {
				m_skyStates[i].OnEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_unk0x04) {
				m_timers[i].OnEventStart(p_unk0x0c);
			}

			if (m_timers[i].m_unk0x20 == p_unk0x04) {
				m_timers[i].m_flags0x2c |= 1;
			}

			if (m_timers[i].m_eventId == p_unk0x08) {
				m_timers[i].OnEventEnd(p_unk0x0c);
			}

			if (m_timers[i].m_unk0x20 == p_unk0x08) {
				m_timers[i].m_flags0x2c &= ~1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_unk0x04) {
				m_nodeTransforms[i].OnEventStart(p_unk0x0c);
			}

			if (m_nodeTransforms[i].m_eventId == p_unk0x08) {
				m_nodeTransforms[i].OnEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_unk0x04) {
				m_modelDistances[i].OnEventStart(p_unk0x0c);
			}

			if (m_modelDistances[i].m_eventId == p_unk0x08) {
				m_modelDistances[i].OnEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_eventLinks) {
		for (LegoU32 i = 0; i < m_eventLinkCount; i++) {
			if (m_eventLinks[i].m_eventId == p_unk0x04) {
				ForceEvents(m_eventLinks[i].m_forcedEventId);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_unk0x30 == p_unk0x04) {
				m_externalForces[i].m_flags0x34 |= 1;
			}

			if (m_externalForces[i].m_unk0x30 == p_unk0x08) {
				m_externalForces[i].m_flags0x34 &= ~1;
			}
		}
	}

	m_hazardManager->NotifyEventPair(p_unk0x04, p_unk0x08, p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x004628c0
void RaceEventTable::StartEventsForRacer(undefined4 p_unk0x04, RaceState::Racer* p_unk0x08)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_unk0x04) {
				m_colorTransforms[i].ForceEventStart(p_unk0x08);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_unk0x04) {
				m_lapZones[i].ForceEventStart(p_unk0x08);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_unk0x04) {
				m_lookTargets[i].ForceEventStart(p_unk0x08);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_unk0x04) {
				m_externalForces[i].ForceEventStart(p_unk0x08);
			}
		}
	}

	if (p_unk0x08) {
		m_hazardManager->DispatchEventStart(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x004629d0
void RaceEventTable::EndEventsForRacer(undefined4 p_unk0x04, RaceState::Racer* p_unk0x08)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_unk0x04) {
				m_colorTransforms[i].ForceEventEnd(p_unk0x08);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_unk0x04) {
				m_lapZones[i].ForceEventEnd(p_unk0x08);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_unk0x04) {
				m_lookTargets[i].ForceEventEnd(p_unk0x08);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_unk0x04) {
				m_externalForces[i].ForceEventEnd(p_unk0x08);
			}
		}
	}

	if (p_unk0x08) {
		m_hazardManager->DispatchEventEnd(p_unk0x04, p_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x00462ae0
void RaceEventTable::FireEventsForRacer(undefined4 p_unk0x04, undefined4 p_unk0x08, RaceState::Racer* p_unk0x0c)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_unk0x04) {
				m_colorTransforms[i].ForceEventStart(p_unk0x0c);
			}

			if (m_colorTransforms[i].m_eventId == p_unk0x08) {
				m_colorTransforms[i].ForceEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_unk0x04) {
				m_lapZones[i].ForceEventStart(p_unk0x0c);
			}

			if (m_lapZones[i].m_eventId == p_unk0x08) {
				m_lapZones[i].ForceEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_unk0x04) {
				m_lookTargets[i].ForceEventStart(p_unk0x0c);
			}

			if (m_lookTargets[i].m_eventId == p_unk0x08) {
				m_lookTargets[i].ForceEventEnd(p_unk0x0c);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_unk0x04) {
				m_externalForces[i].ForceEventStart(p_unk0x0c);
			}

			if (m_externalForces[i].m_eventId == p_unk0x08) {
				m_externalForces[i].ForceEventEnd(p_unk0x0c);
			}
		}
	}

	if (p_unk0x0c) {
		m_hazardManager->DispatchEventPair(p_unk0x04, p_unk0x08, p_unk0x0c);
	}
}
