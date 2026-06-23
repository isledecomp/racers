#ifndef RACESESSIONFIELD0X32B4_H
#define RACESESSIONFIELD0X32B4_H

#include "decomp.h"
#include "golboundingvolume.h"
#include "golmath.h"
#include "race/raceeventrecord.h"
#include "types.h"

class RaceEventTable0x90;
class GolBoundedEntity;
class GolNameTable;
class GolWorldDatabase;

class RaceSessionField0x32b4 {
public:
	RaceSessionField0x32b4();
	GolWorldDatabase* FUN_0041f440(
		GolWorldDatabase* p_unk0x04,
		LegoChar* p_unk0x08,
		RaceEventTable0x90* p_unk0x0c,
		GolNameTable* p_unk0x10
	);
	LegoBool32 FUN_0041f4d0(
		GolVec3* p_unk0x04,
		GolVec3* p_unk0x08,
		GolBoundingVolume::Field0x0c* p_unk0x0c,
		GolVec3* p_unk0x10,
		RaceEventRecord::Target** p_unk0x14
	);
	LegoBool32 FUN_0041f730(
		GolVec3* p_unk0x04,
		GolVec3* p_unk0x08,
		GolBoundingVolume::Field0x0c* p_unk0x0c,
		GolVec3* p_unk0x10
	);

private:
	GolWorldDatabase* m_unk0x00;   // 0x00
	RaceEventTable0x90* m_unk0x04; // 0x04
	GolNameTable* m_unk0x08;       // 0x08
	GolBoundedEntity* m_unk0x0c;   // 0x0c
};

#endif // RACESESSIONFIELD0X32B4_H
