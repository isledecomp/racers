#ifndef RACETRAILMANAGER_H
#define RACETRAILMANAGER_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "surface/color.h"
#include "types.h"

class DuskwindBananaRelic0x24;
class GolD3DRenderDevice;
class GolExport;
class GolModelBase;

// VTABLE: LEGORACERS 0x004b47a0
// SIZE 0x0c
class RaceTrailManager {
public:
	RaceTrailManager();
	virtual ~RaceTrailManager(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x004937d0
	// RaceTrailManager::`scalar deleting destructor'

	void Destroy();

	// VTABLE: LEGORACERS 0x004b4794
	// SIZE 0x2a4
	class Trail {
	public:
		// SIZE 0x1c
		class Params {
		public:
			LegoU32 m_unk0x00;   // 0x00
			LegoU32 m_unk0x04;   // 0x04
			LegoU32 m_unk0x08;   // 0x08
			LegoU32 m_unk0x0c;   // 0x0c
			LegoU32 m_unk0x10;   // 0x10
			LegoFloat m_unk0x14; // 0x14
			LegoFloat m_unk0x18; // 0x18
		};

		// SIZE 0x4c
		class Field0x0dc {
		public:
			LegoU32 m_unk0x00;    // 0x00
			GolVec3 m_unk0x04[5]; // 0x04
			GolVec3 m_unk0x40;    // 0x40
		};

		enum {
			c_flags0x09cBit0 = 1 << 0,
			c_flags0x09cBit1 = 1 << 1,
			c_flags0x09cBit2 = 1 << 2,
			c_flags0x09cBit3 = 1 << 3,
			c_flags0x09cBit4 = 1 << 4,
			c_flags0x09cBit5 = 1 << 5,
		};

		Trail();
		~Trail();
		virtual Trail* VTable0x00(undefined4 p_flags); // vtable+0x00

		void FUN_00492a50(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
		void FUN_00492a90(GolD3DRenderDevice* p_renderer, DuskwindBananaRelic0x24* p_material);
		void FUN_00492ab0(const ColorRGBA* p_color);
		void FUN_00492ae0(Params* p_params);
		void FUN_00492bd0();
		void FUN_00492be0(LegoU32 p_elapsedMs);
		void FUN_00492c30(LegoU32 p_elapsedMs);
		void FUN_00492ee0(LegoU32 p_elapsedMs, GolVec3* p_positions, GolVec3 p_center);
		void FUN_00492f10(LegoU32 p_elapsedMs, GolVec3* p_positions);
		void FUN_004931a0();
		void FUN_004513d0(GolD3DRenderDevice* p_renderer);
		void Destroy();
		void FUN_00493790(GolD3DRenderDevice* p_renderer);
		LegoU8 GetFlags0x09c() const { return m_flags0x09c; }
		LegoBool32 IsActive() const { return m_flags0x09c & c_flags0x09cBit0; }

	private:
		friend class RaceTrailManager;

		void Reset();

		GolExport* m_unk0x004;               // 0x004
		GolModelBase* m_unk0x008;            // 0x008
		GolModelEntity m_unk0x00c;           // 0x00c
		LegoU8 m_flags0x09c;                 // 0x09c
		undefined m_unk0x09d[0x0a0 - 0x09d]; // 0x09d
		LegoU32 m_unk0x0a0;                  // 0x0a0
		LegoU32 m_unk0x0a4;                  // 0x0a4
		LegoU32 m_unk0x0a8;                  // 0x0a8
		LegoU32 m_unk0x0ac;                  // 0x0ac
		LegoU32 m_unk0x0b0;                  // 0x0b0
		LegoU32 m_unk0x0b4;                  // 0x0b4
		LegoU32 m_unk0x0b8;                  // 0x0b8
		LegoU32 m_unk0x0bc;                  // 0x0bc
		LegoU32 m_unk0x0c0;                  // 0x0c0
		LegoFloat m_unk0x0c4;                // 0x0c4
		LegoFloat m_unk0x0c8;                // 0x0c8
		LegoFloat m_unk0x0cc;                // 0x0cc
		LegoFloat m_unk0x0d0;                // 0x0d0
		LegoFloat m_unk0x0d4;                // 0x0d4
		ColorRGBA m_unk0x0d8;                // 0x0d8
		Field0x0dc m_unk0x0dc[6];            // 0x0dc
	};

	LegoU32 FUN_00493a60(GolD3DRenderDevice* p_renderer);
	LegoU32 FUN_00493aa0(GolD3DRenderDevice* p_renderer);
	Trail* FUN_004939b0(Trail::Params* p_params);
	void FUN_00493a10(Trail* p_trail);
	LegoU32 FUN_00493a20(LegoU32 p_elapsedMs);
	void FUN_00493850(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, LegoU32 p_trailCount);

private:
	Trail* m_trails;      // 0x04
	LegoU32 m_trailCount; // 0x08
};

#endif // RACETRAILMANAGER_H
