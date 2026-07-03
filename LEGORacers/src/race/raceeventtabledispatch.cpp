#include "race/events/colortransformresource.h"
#include "race/events/externalforceresource.h"
#include "race/events/lapzoneresource.h"
#include "race/events/looktargetresource.h"
#include "race/events/materialanimationresource.h"
#include "race/events/modeldistanceresource.h"
#include "race/events/nodetransformresource.h"
#include "race/events/partanimationresource.h"
#include "race/events/particleresource.h"
#include "race/events/raceeventresource.h"
#include "race/events/skystateresource.h"
#include "race/events/soundresource.h"
#include "race/events/timerresource.h"
#include "race/hazardmanager.h"
#include "race/raceeventtable.h"
#include "race/targetpointlist.h"

DECOMP_SIZE_ASSERT(RaceEventTable, 0x90)

// STUB: LEGORACERS 0x0045c660
LegoU32 TargetPointList::DisableTargetPoints(undefined4 p_index)
{
	LegoU32 i = 0;
	if (static_cast<LegoU32>(m_count) > 0) {
		Entry* entry = m_entries;
		while (i < static_cast<LegoU32>(m_count)) {
			if (entry->m_index == p_index) {
				if (entry->m_flags & TargetPointList::Entry::c_flagEnabled) {
					entry->m_flags &= ~TargetPointList::Entry::c_flagEnabled;
				}
			}

			i++;
			entry++;
		}
	}

	return m_count;
}

// FUNCTION: LEGORACERS 0x0045ee50
void RaceEventResource::OnEventStart(GolVec3* p_position)
{
	if (!(m_flags & 4) && (m_state == 1 || m_state == 4)) {
		OnStartAt(p_position);
	}
}

// FUNCTION: LEGORACERS 0x0045ee70
void RaceEventResource::OnEventEnd(GolVec3* p_position)
{
	if (m_flags & 4) {
		if (m_state == 1 || m_state == 4) {
			OnStartAt(p_position);

			if (!(m_flags & 2)) {
				OnEnd();
			}

			return;
		}
	}

	if (m_state != 1 && !(m_flags & 2)) {
		OnEnd();
	}
}

// FUNCTION: LEGORACERS 0x0045eec0
void RaceEventResource::ForceEventStart(Racer* p_racer)
{
	if (!(m_flags & 4) && (m_state == 1 || m_state == 4)) {
		OnStartForRacer(p_racer);
	}
}

// FUNCTION: LEGORACERS 0x00461ef0
LegoU32 RaceEventTable::StartEventsAt(undefined4 p_eventId, GolVec3* p_position)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_eventId) {
				m_sounds[i].OnEventStart(p_position);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_eventId) {
				m_partAnimations[i].OnEventStart(p_position);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_eventId) {
				m_materialAnimations[i].OnEventStart(p_position);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_eventId) {
				m_particles[i].OnEventStart(p_position);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_eventId) {
				m_skyStates[i].OnEventStart(p_position);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_eventId) {
				m_timers[i].OnEventStart(p_position);
			}

			if (m_timers[i].m_holdEventId == p_eventId) {
				m_timers[i].m_timerFlags |= 1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_eventId) {
				m_nodeTransforms[i].OnEventStart(p_position);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_eventId) {
				m_modelDistances[i].OnEventStart(p_position);
			}
		}
	}

	if (m_eventLinks) {
		for (LegoU32 i = 0; i < m_eventLinkCount; i++) {
			if (m_eventLinks[i].m_eventId == p_eventId) {
				ForceEvents(m_eventLinks[i].m_forcedEventId);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_armEventId == p_eventId) {
				m_externalForces[i].m_forceFlags |= 1;
			}
		}
	}

	m_hazardManager->NotifyEventStart(p_eventId, p_position);
	return m_targetPoints->DisableTargetPoints(p_eventId);
}

// FUNCTION: LEGORACERS 0x00462140
void RaceEventTable::EndEventsAt(undefined4 p_eventId, GolVec3* p_position)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_eventId) {
				m_sounds[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_eventId) {
				m_partAnimations[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_eventId) {
				m_materialAnimations[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_eventId) {
				m_particles[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_eventId) {
				m_skyStates[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_eventId) {
				m_timers[i].OnEventEnd(p_position);
			}

			if (m_timers[i].m_holdEventId == p_eventId) {
				m_timers[i].m_timerFlags &= ~1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_eventId) {
				m_nodeTransforms[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_eventId) {
				m_modelDistances[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_armEventId == p_eventId) {
				m_externalForces[i].m_forceFlags &= ~1;
			}
		}
	}

	m_hazardManager->NotifyEventEnd(p_eventId, p_position);
}

// FUNCTION: LEGORACERS 0x00462350
void RaceEventTable::ForceEvents(undefined4 p_eventId)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_eventId) {
				m_sounds[i].m_state = 5;
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_eventId) {
				m_partAnimations[i].m_state = 5;
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_eventId) {
				m_materialAnimations[i].m_state = 5;
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_eventId) {
				m_particles[i].m_state = 5;
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_eventId) {
				m_skyStates[i].m_state = 5;
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_eventId) {
				m_timers[i].m_state = 5;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_eventId) {
				m_nodeTransforms[i].m_state = 5;
			}
		}
	}

	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_eventId) {
				m_colorTransforms[i].m_state = 5;
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_eventId) {
				m_lapZones[i].m_state = 5;
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_eventId) {
				m_modelDistances[i].m_state = 5;
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_eventId) {
				m_lookTargets[i].m_state = 5;
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_eventId) {
				m_externalForces[i].m_state = 5;
			}
		}
	}

	m_hazardManager->ForceDeactivate(p_eventId);
}

// FUNCTION: LEGORACERS 0x00462580
void RaceEventTable::FireEventsAt(undefined4 p_startId, undefined4 p_endId, GolVec3* p_position)
{
	if (m_sounds) {
		for (LegoU32 i = 0; i < m_soundCount; i++) {
			if (m_sounds[i].m_eventId == p_startId) {
				m_sounds[i].OnEventStart(p_position);
			}

			if (m_sounds[i].m_eventId == p_endId) {
				m_sounds[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_partAnimations) {
		for (LegoU32 i = 0; i < m_partAnimationCount; i++) {
			if (m_partAnimations[i].m_eventId == p_startId) {
				m_partAnimations[i].OnEventStart(p_position);
			}

			if (m_partAnimations[i].m_eventId == p_endId) {
				m_partAnimations[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_materialAnimations) {
		for (LegoU32 i = 0; i < m_materialAnimationCount; i++) {
			if (m_materialAnimations[i].m_eventId == p_startId) {
				m_materialAnimations[i].OnEventStart(p_position);
			}

			if (m_materialAnimations[i].m_eventId == p_endId) {
				m_materialAnimations[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_particles) {
		for (LegoU32 i = 0; i < m_particleCount; i++) {
			if (m_particles[i].m_eventId == p_startId) {
				m_particles[i].OnEventStart(p_position);
			}

			if (m_particles[i].m_eventId == p_endId) {
				m_particles[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_skyStates) {
		for (LegoU32 i = 0; i < m_skyStateCount; i++) {
			if (m_skyStates[i].m_eventId == p_startId) {
				m_skyStates[i].OnEventStart(p_position);
			}

			if (m_skyStates[i].m_eventId == p_endId) {
				m_skyStates[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_timers) {
		for (LegoU32 i = 0; i < m_timerCount; i++) {
			if (m_timers[i].m_eventId == p_startId) {
				m_timers[i].OnEventStart(p_position);
			}

			if (m_timers[i].m_holdEventId == p_startId) {
				m_timers[i].m_timerFlags |= 1;
			}

			if (m_timers[i].m_eventId == p_endId) {
				m_timers[i].OnEventEnd(p_position);
			}

			if (m_timers[i].m_holdEventId == p_endId) {
				m_timers[i].m_timerFlags &= ~1;
			}
		}
	}

	if (m_nodeTransforms) {
		for (LegoU32 i = 0; i < m_nodeTransformCount; i++) {
			if (m_nodeTransforms[i].m_eventId == p_startId) {
				m_nodeTransforms[i].OnEventStart(p_position);
			}

			if (m_nodeTransforms[i].m_eventId == p_endId) {
				m_nodeTransforms[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_modelDistances) {
		for (LegoU32 i = 0; i < m_modelDistanceCount; i++) {
			if (m_modelDistances[i].m_eventId == p_startId) {
				m_modelDistances[i].OnEventStart(p_position);
			}

			if (m_modelDistances[i].m_eventId == p_endId) {
				m_modelDistances[i].OnEventEnd(p_position);
			}
		}
	}

	if (m_eventLinks) {
		for (LegoU32 i = 0; i < m_eventLinkCount; i++) {
			if (m_eventLinks[i].m_eventId == p_startId) {
				ForceEvents(m_eventLinks[i].m_forcedEventId);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_armEventId == p_startId) {
				m_externalForces[i].m_forceFlags |= 1;
			}

			if (m_externalForces[i].m_armEventId == p_endId) {
				m_externalForces[i].m_forceFlags &= ~1;
			}
		}
	}

	m_hazardManager->NotifyEventPair(p_startId, p_endId, p_position);
}

// FUNCTION: LEGORACERS 0x004628c0
void RaceEventTable::StartEventsForRacer(undefined4 p_eventId, Racer* p_racer)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_eventId) {
				m_colorTransforms[i].ForceEventStart(p_racer);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_eventId) {
				m_lapZones[i].ForceEventStart(p_racer);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_eventId) {
				m_lookTargets[i].ForceEventStart(p_racer);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_eventId) {
				m_externalForces[i].ForceEventStart(p_racer);
			}
		}
	}

	if (p_racer) {
		m_hazardManager->DispatchEventStart(p_eventId, p_racer);
	}
}

// FUNCTION: LEGORACERS 0x004629d0
void RaceEventTable::EndEventsForRacer(undefined4 p_eventId, Racer* p_racer)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_eventId) {
				m_colorTransforms[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_eventId) {
				m_lapZones[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_eventId) {
				m_lookTargets[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_eventId) {
				m_externalForces[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (p_racer) {
		m_hazardManager->DispatchEventEnd(p_eventId, p_racer);
	}
}

// FUNCTION: LEGORACERS 0x00462ae0
void RaceEventTable::FireEventsForRacer(undefined4 p_startId, undefined4 p_endId, Racer* p_racer)
{
	if (m_colorTransforms) {
		for (LegoU32 i = 0; i < m_colorTransformCount; i++) {
			if (m_colorTransforms[i].m_eventId == p_startId) {
				m_colorTransforms[i].ForceEventStart(p_racer);
			}

			if (m_colorTransforms[i].m_eventId == p_endId) {
				m_colorTransforms[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_lapZones) {
		for (LegoU32 i = 0; i < m_lapZoneCount; i++) {
			if (m_lapZones[i].m_eventId == p_startId) {
				m_lapZones[i].ForceEventStart(p_racer);
			}

			if (m_lapZones[i].m_eventId == p_endId) {
				m_lapZones[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_lookTargets) {
		for (LegoU32 i = 0; i < m_lookTargetCount; i++) {
			if (m_lookTargets[i].m_eventId == p_startId) {
				m_lookTargets[i].ForceEventStart(p_racer);
			}

			if (m_lookTargets[i].m_eventId == p_endId) {
				m_lookTargets[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (m_externalForces) {
		for (LegoU32 i = 0; i < m_externalForceCount; i++) {
			if (m_externalForces[i].m_eventId == p_startId) {
				m_externalForces[i].ForceEventStart(p_racer);
			}

			if (m_externalForces[i].m_eventId == p_endId) {
				m_externalForces[i].ForceEventEnd(p_racer);
			}
		}
	}

	if (p_racer) {
		m_hazardManager->DispatchEventPair(p_startId, p_endId, p_racer);
	}
}
