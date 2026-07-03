#ifndef RACESESSIONFIELD0X32B4_H
#define RACESESSIONFIELD0X32B4_H

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
	LegoBool32 FUN_0041f730(
		GolVec3* p_unk0x04,
		GolVec3* p_unk0x08,
		GolBoundingVolume::HitTriangle* p_unk0x0c,
		GolVec3* p_unk0x10
	);

private:
	GolWorldDatabase* m_unk0x00; // 0x00
	RaceEventTable* m_unk0x04;   // 0x04
	GolNameTable* m_unk0x08;     // 0x08
	GolBoundedEntity* m_unk0x0c; // 0x0c
};

#endif // RACESESSIONFIELD0X32B4_H
