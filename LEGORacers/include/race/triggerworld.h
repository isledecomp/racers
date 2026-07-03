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
		GolWorldDatabase* p_unk0x04,
		LegoChar* p_unk0x08,
		RaceEventTable* p_unk0x0c,
		GolNameTable* p_unk0x10
	);
	LegoBool32 IntersectSegment(
		GolVec3* p_unk0x04,
		GolVec3* p_unk0x08,
		GolBoundingVolume::HitTriangle* p_unk0x0c,
		GolVec3* p_unk0x10,
		RaceEventRecord::Target** p_unk0x14
	);
	LegoBool32 IntersectSegmentAndFireEvents(
		GolVec3* p_unk0x04,
		GolVec3* p_unk0x08,
		GolBoundingVolume::HitTriangle* p_unk0x0c,
		GolVec3* p_unk0x10
	);

private:
	GolWorldDatabase* m_triggerDatabase; // 0x00
	RaceEventTable* m_eventTable;        // 0x04
	GolNameTable* m_recordNames;         // 0x08
	GolBoundedEntity* m_boundsEntity;    // 0x0c
};

#endif // TRIGGERWORLD_H
