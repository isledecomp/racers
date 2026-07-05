#ifndef SURFACETABLE_H
#define SURFACETABLE_H

#include "golmath.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;
class RaceSession;

// SIZE 0x14
// VTABLE: LEGORACERS 0x004b0c04
class SurfaceTable : public GolNameTable {
public:
	// SIZE 0x5c
	class Entry {
	public:
		Entry();
		void Unload();
		void Load(GolFileParser* p_parser, LegoBool32 p_mirror);
		void Reset();

		const LegoChar* GetName() const { return m_name; }

	private:
		friend class SurfaceTable;

		enum {
			c_flagLoaded = 1 << 0,
			c_flagEnterEventId = 1 << 1,
			c_flagLeaveEventId = 1 << 2,
			c_flagTouchEventId = 1 << 3,
			c_flagProjectileEventId = 1 << 4,
			c_flagUnk0x1c = 1 << 5,
			c_flagSurfaceForce = 1 << 6,
			c_flagSurfaceSoundId = 1 << 7,
			c_flagUnk0x38 = 1 << 8,
			c_flagUnk0x3c = 1 << 9,
			c_flagWheelParticleName = 1 << 10,
			c_flagSupportThreshold = 1 << 11,
			c_flagFriction = 1 << 12,
			c_flagLateralGrip = 1 << 13,
			c_flagUnk0x54 = 1 << 14,
			c_flagRollingResistance = 1 << 15,
			c_flagNonSolid = 1 << 16,
			c_flagProjectilePassThrough = 1 << 17,
			c_flagFinish = 1 << 18
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

	// VTABLE: LEGORACERS 0x004b0c10
	// SIZE 0x1fc
	class TmbTxtParser : public GolTxtParser {
	public:
		// .tmb tokens
		enum {
			e_surface = 0x27,
			e_enterEvent = 0x28,
			e_leaveEvent = 0x29,
			e_touchEvent = 0x2a,
			e_surfaceForce = 0x2d,
			e_surfaceSound = 0x2e,
			e_wheelParticle = 0x31,
			e_supportThreshold = 0x32,
			e_friction = 0x33,
			e_lateralGrip = 0x34,
			e_rollingResistance = 0x36,
			e_projectileEvent = 0x2b,
			e_unknown0x2c = 0x2c,
			e_unknown0x2f = 0x2f,
			e_unknown0x30 = 0x30,
			e_unknown0x35 = 0x35,
			e_nonSolid = 0x37,
			e_projectilePassThrough = 0x38,
			e_finish = 0x39,
		};
	};

	SurfaceTable();
	~SurfaceTable() override;
	void Clear() override;
	void Load(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);

	// SYNTHETIC: LEGORACERS 0x00443fc0
	// SurfaceTable::`scalar deleting destructor'

private:
	LegoU32 m_count;  // 0x0c
	Entry* m_entries; // 0x10
};

#endif // SURFACETABLE_H
