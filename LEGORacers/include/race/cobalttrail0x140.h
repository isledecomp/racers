#ifndef COBALTTRAIL0X140_H
#define COBALTTRAIL0X140_H

#include "decomp.h"
#include "golstring.h"
#include "race/racestate.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFontBase;
class GolNameTable;
class GolStringTable;
class RaceSession;
class UtopianPan0xa4;

// SIZE 0x140
class CobaltTrail0x140 {
public:
	class ResourceTable {
	public:
		virtual void VTable0x00() = 0;                           // vtable+0x00
		virtual void VTable0x04() = 0;                           // vtable+0x04
		virtual void VTable0x08() = 0;                           // vtable+0x08
		virtual void VTable0x0c() = 0;                           // vtable+0x0c
		virtual void VTable0x10() = 0;                           // vtable+0x10
		virtual void VTable0x14() = 0;                           // vtable+0x14
		virtual void VTable0x18() = 0;                           // vtable+0x18
		virtual void VTable0x1c() = 0;                           // vtable+0x1c
		virtual UtopianPan0xa4* VTable0x20(LegoS32 p_index) = 0; // vtable+0x20
	};

	// SIZE 0x09
	struct TimeText {
		LegoChar m_text[9]; // 0x00
	};

	CobaltTrail0x140();

	// FUNCTION: LEGORACERS 0x00431980
	~CobaltTrail0x140() {}

	LegoS32 FUN_004261f0(LegoS32 p_unk0x04, LegoS32 p_unk0x08);
	void FUN_00426280(
		undefined4 p_unk0x04,
		LegoS32 p_unk0x08,
		LegoS32 p_unk0x0c,
		LegoS32 p_unk0x10,
		LegoS32 p_unk0x14,
		LegoBool p_unk0x18
	);
	RaceState::Racer* FUN_004262c0(RaceState::Racer* p_unk0x04);
	void FUN_004262d0(LegoU32 p_time);
	void FUN_00426360();
	void FUN_00426370();
	void FUN_00426390(LegoU32 p_elapsedMs);

private:
	friend class RaceSession;
	friend class RaceState::Racer;

	void FUN_004249b0();
	void FUN_00424fb0();
	LegoU32 FUN_004246d0(LegoChar* p_buffer, LegoU32 p_time);
	void FUN_004258e0();
	void FUN_004263a0();
	LegoS32 FUN_00425bf0(const LegoChar* p_text, LegoS32 p_x, LegoS32 p_y);
	LegoS32 FUN_00425d80(
		GolD3DRenderDevice* p_renderer,
		GolNameTable* p_nameTable,
		GolString* p_string,
		ResourceTable* p_resourceTable,
		RaceState* p_unk0x14,
		undefined4 p_unk0x18,
		GolStringTable* p_stringTable,
		RaceState::Racer::Field0x004* p_unk0x20,
		LegoBool p_unk0x24,
		LegoBool p_unk0x28
	);
	LegoS32 FUN_00425e90(LegoS32 p_unk0x04);
	void Reset();

	static undefined4 FUN_00425c70(const LegoChar* p_text, GolString* p_string);

	GolD3DRenderDevice* m_unk0x000;           // 0x000
	RaceState::Racer::Field0x004* m_unk0x004; // 0x004
	ResourceTable* m_unk0x008;                // 0x008
	GolStringTable* m_unk0x00c;               // 0x00c
	GolString* m_unk0x010;                    // 0x010
	GolString m_unk0x014;                     // 0x014
	GolFontBase* m_unk0x020;                  // 0x020
	GolFontBase* m_unk0x024;                  // 0x024
	RaceState* m_unk0x028;                    // 0x028
	RaceState::Racer* m_unk0x02c;             // 0x02c
	undefined4 m_unk0x030;                    // 0x030
	LegoU32 m_unk0x034;                       // 0x034
	LegoU8 m_unk0x038;                        // 0x038
	undefined m_unk0x039;                     // 0x039
	undefined m_unk0x03a;                     // 0x03a
	undefined m_unk0x03b;                     // 0x03b
	LegoU8 m_unk0x03c;                        // 0x03c
	TimeText m_unk0x03d;                      // 0x03d
	TimeText m_unk0x046;                      // 0x046
	TimeText m_unk0x04f;                      // 0x04f
	TimeText m_unk0x058;                      // 0x058
	LegoChar m_unk0x061[0x070 - 0x061];       // 0x061
	LegoS32 m_unk0x070;                       // 0x070
	LegoU32 m_unk0x074;                       // 0x074
	LegoFloat m_unk0x078;                     // 0x078
	LegoS32 m_unk0x07c;                       // 0x07c
	LegoU32 m_unk0x080;                       // 0x080
	LegoU32 m_unk0x084;                       // 0x084
	LegoU32 m_unk0x088;                       // 0x088
	LegoS32 m_unk0x08c;                       // 0x08c
	LegoS32 m_unk0x090;                       // 0x090
	LegoS32 m_unk0x094;                       // 0x094
	LegoS32 m_unk0x098;                       // 0x098
	LegoS32 m_unk0x09c;                       // 0x09c
	LegoS32 m_unk0x0a0;                       // 0x0a0
	LegoS32 m_unk0x0a4;                       // 0x0a4
	LegoS32 m_unk0x0a8;                       // 0x0a8
	LegoS32 m_unk0x0ac;                       // 0x0ac
	LegoS32 m_unk0x0b0;                       // 0x0b0
	LegoS32 m_unk0x0b4;                       // 0x0b4
	LegoS32 m_unk0x0b8;                       // 0x0b8
	LegoS32 m_unk0x0bc;                       // 0x0bc
	LegoS32 m_unk0x0c0;                       // 0x0c0
	LegoS32 m_unk0x0c4;                       // 0x0c4
	LegoS32 m_unk0x0c8;                       // 0x0c8
	LegoS32 m_unk0x0cc;                       // 0x0cc
	LegoS32 m_unk0x0d0;                       // 0x0d0
	LegoS32 m_unk0x0d4;                       // 0x0d4
	LegoS32 m_unk0x0d8;                       // 0x0d8
	LegoS32 m_unk0x0dc;                       // 0x0dc
	LegoS32 m_unk0x0e0;                       // 0x0e0
	LegoS32 m_unk0x0e4;                       // 0x0e4
	LegoS32 m_unk0x0e8;                       // 0x0e8
	LegoFloat m_unk0x0ec;                     // 0x0ec
	LegoFloat m_unk0x0f0;                     // 0x0f0
	LegoFloat m_unk0x0f4;                     // 0x0f4
	LegoFloat m_unk0x0f8;                     // 0x0f8
	LegoS32 m_unk0x0fc;                       // 0x0fc
	LegoS32 m_unk0x100;                       // 0x100
	LegoFloat m_unk0x104;                     // 0x104
	LegoFloat m_unk0x108;                     // 0x108
	LegoFloat m_unk0x10c;                     // 0x10c
	LegoFloat m_unk0x110;                     // 0x110
	LegoFloat m_unk0x114;                     // 0x114
	undefined4 m_unk0x118;                    // 0x118
	LegoS32 m_unk0x11c;                       // 0x11c
	LegoS32 m_unk0x120;                       // 0x120
	LegoS32 m_unk0x124;                       // 0x124
	LegoS32 m_unk0x128;                       // 0x128
	undefined4 m_unk0x12c;                    // 0x12c
	undefined4 m_unk0x130;                    // 0x130
	undefined4 m_unk0x134;                    // 0x134
	undefined4 m_unk0x138;                    // 0x138
	undefined4 m_unk0x13c;                    // 0x13c
};

#endif // COBALTTRAIL0X140_H
