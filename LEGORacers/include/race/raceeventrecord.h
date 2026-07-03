#ifndef RACEEVENTRECORD_H
#define RACEEVENTRECORD_H

#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "race/checkpointgraph.h"
#include "types.h"

// SIZE 0x20
class RaceEventRecord {
public:
	// SIZE 0x5c
	class Target {
	public:
		enum {
			c_flagLoaded = 1 << 0,
			c_flagEnterEvent = 1 << 1,
			c_flagLeaveEvent = 1 << 2,
			c_flagTouchEvent = 1 << 3,
			c_flagProjectileEvent = 1 << 4,
			c_flagUnk0x1c = 1 << 5,
			c_flagSurfaceForce = 1 << 6,
			c_flagSurfaceSound = 1 << 7,
			c_flagWheelParticle = 1 << 10,
			c_flagSupportThreshold = 1 << 11,
			c_flagFriction = 1 << 12,
			c_flagLateralGrip = 1 << 13,
			c_flagUnk0x54 = 1 << 14,
			c_flagRollingResistance = 1 << 15,
			c_flagNonSolid = 1 << 16,
			c_flagProjectilePassThrough = 1 << 17,
			c_flagFinish = 1 << 18,
		};

		GolName m_name;                // 0x00
		LegoU32 m_flags;               // 0x08
		LegoS32 m_enterEventId;        // 0x0c
		LegoS32 m_leaveEventId;        // 0x10
		LegoS32 m_touchEventId;        // 0x14
		LegoS32 m_projectileEventId;   // 0x18
		GolVec3 m_unk0x1c;             // 0x1c
		GolVec3 m_surfaceForce;        // 0x28
		LegoS32 m_surfaceSoundId;      // 0x34
		LegoS32 m_unk0x38;             // 0x38
		LegoS32 m_unk0x3c;             // 0x3c
		GolName m_wheelParticleName;   // 0x40
		LegoFloat m_supportThreshold;  // 0x48
		LegoFloat m_friction;          // 0x4c
		LegoFloat m_lateralGrip;       // 0x50
		LegoFloat m_unk0x54;           // 0x54
		LegoFloat m_rollingResistance; // 0x58
	};

	undefined m_unk0x00[0x14 - 0x00]; // 0x00
	union {
		CheckpointGraph::Entry* m_pathField; // 0x14
		Target* m_target;                    // 0x14
	};
	LegoS32 m_kind;       // 0x18
	undefined4 m_unk0x1c; // 0x1c
};

#endif // RACEEVENTRECORD_H
