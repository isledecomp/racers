#ifndef RACEEVENTRECORD_H
#define RACEEVENTRECORD_H

#include "decomp.h"
#include "golmaterial.h"
#include "golmath.h"
#include "golname.h"
#include "race/checkpointgraph.h"
#include "types.h"

#include <string.h>

// Collision queries return the GolMaterial assigned to the hit triangle: the race
// session stores its Target/checkpoint pointers in the material's user data, and
// checkpoint materials are tagged by a leading digit in the material name.
// SIZE 0x24
class RaceEventRecord : public GolMaterial {
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

	Target* GetTarget() const { return static_cast<Target*>(m_userData); }
	CheckpointGraph::Entry* GetPathField() const { return static_cast<CheckpointGraph::Entry*>(m_userData); }

	LegoS32 GetKind() const
	{
		LegoS32 kind;
		::memcpy(&kind, m_nameRecord.m_name, sizeof(kind));
		return kind;
	}
};

#endif // RACEEVENTRECORD_H
