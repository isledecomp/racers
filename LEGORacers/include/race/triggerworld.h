#ifndef TRIGGERWORLD_H
#define TRIGGERWORLD_H

#include "decomp.h"
#include "golboundingvolume.h"
#include "golmath.h"
#include "race/raceeventrecord.h"
#include "types.h"

class RaceEventTable;
class GolBoundedEntity;
class GolNameTable;
class GolWorldDatabase;

class TriggerWorld {
public:
	TriggerWorld();
	GolWorldDatabase* Initialize(
		GolWorldDatabase* p_triggerDatabase,
		LegoChar* p_worldName,
		RaceEventTable* p_eventTable,
		GolNameTable* p_recordNames
	);
	LegoBool32 IntersectSegment(
		GolVec3* p_start,
		GolVec3* p_end,
		GolBoundingVolume::HitTriangle* p_hitTriangle,
		GolVec3* p_hitPosition,
		RaceEventRecord::Target** p_hitTarget
	);
	LegoBool32 IntersectSegmentAndFireEvents(
		GolVec3* p_start,
		GolVec3* p_end,
		GolBoundingVolume::HitTriangle* p_hitTriangle,
		GolVec3* p_hitPosition
	);

private:
	GolWorldDatabase* m_triggerDatabase; // 0x00
	RaceEventTable* m_eventTable;        // 0x04
	GolNameTable* m_recordNames;         // 0x08
	GolBoundedEntity* m_boundsEntity;    // 0x0c
};

#endif // TRIGGERWORLD_H
