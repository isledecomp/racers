#ifndef RACEEVENTRECORD_H
#define RACEEVENTRECORD_H

#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "race/racesessionfield0x27f4.h"
#include "types.h"

// SIZE 0x20
class RaceEventRecord {
public:
	// SIZE 0x5c
	class Target {
	public:
		enum {
			c_flags0x08Loaded = 1 << 0,
			c_flags0x08Unk0x0c = 1 << 1,
			c_flags0x08Unk0x10 = 1 << 2,
			c_flags0x08Bit3 = 1 << 3,
			c_flags0x08Unk0x1c = 1 << 5,
			c_flags0x08Unk0x28 = 1 << 6,
			c_flags0x08Unk0x34 = 1 << 7,
			c_flags0x08Unk0x40 = 1 << 10,
			c_flags0x08Unk0x48 = 1 << 11,
			c_flags0x08Unk0x4c = 1 << 12,
			c_flags0x08Unk0x50 = 1 << 13,
			c_flags0x08Unk0x54 = 1 << 14,
			c_flags0x08Unk0x58 = 1 << 15,
			c_flags0x08Bit16 = 1 << 16,
			c_flags0x08Bit18 = 1 << 18,
		};

		GolName m_name;      // 0x00
		LegoU32 m_flags0x08; // 0x08
		LegoS32 m_unk0x0c;   // 0x0c
		LegoS32 m_unk0x10;   // 0x10
		LegoS32 m_unk0x14;   // 0x14
		LegoS32 m_unk0x18;   // 0x18
		GolVec3 m_unk0x1c;   // 0x1c
		GolVec3 m_unk0x28;   // 0x28
		LegoS32 m_unk0x34;   // 0x34
		LegoS32 m_unk0x38;   // 0x38
		LegoS32 m_unk0x3c;   // 0x3c
		GolName m_unk0x40;   // 0x40
		LegoFloat m_unk0x48; // 0x48
		LegoFloat m_unk0x4c; // 0x4c
		LegoFloat m_unk0x50; // 0x50
		LegoFloat m_unk0x54; // 0x54
		LegoFloat m_unk0x58; // 0x58
	};

	undefined m_unk0x00[0x14 - 0x00]; // 0x00
	union {
		RaceSessionField0x27f4::Entry* m_pathField; // 0x14
		Target* m_target;                           // 0x14
	};
	LegoS32 m_unk0x18;    // 0x18
	undefined4 m_unk0x1c; // 0x1c
};

#endif // RACEEVENTRECORD_H
