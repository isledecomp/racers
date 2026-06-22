#ifndef RACESESSIONFIELD0X32B4_H
#define RACESESSIONFIELD0X32B4_H

#include "decomp.h"
#include "golmath.h"
#include "golnametable.h"
#include "golorientedentity.h"
#include "types.h"

class RaceEventTable0x90;

class RaceSessionField0x32b4 {
public:
	// SIZE 0x34
	class Field0x0c {
	public:
		const LegoFloat* GetFloatData() const { return &m_unk0x00.m_x; }

		GolVec3 m_unk0x00;   // 0x00
		GolVec3 m_unk0x0c;   // 0x0c
		GolVec3 m_unk0x18;   // 0x18
		GolVec3 m_unk0x24;   // 0x24
		LegoFloat m_unk0x30; // 0x30
	};

	class Field0x14 {
	public:
		undefined m_unk0x00[0x08 - 0x00]; // 0x00
		LegoU32 m_unk0x08;                // 0x08
		undefined m_unk0x0c[0x18 - 0x0c]; // 0x0c
		undefined4 m_unk0x18;             // 0x18
	};

	// SIZE 0x18
	class Field0x10 {
	public:
		undefined m_unk0x00[0x14 - 0x00]; // 0x00
		Field0x14* m_unk0x14;             // 0x14
	};

	class Field0x058 {
	public:
		enum {
			c_invalidChildIndex = 0xfffe,
		};

		// SIZE 0x0c
		class VertexTable {
		public:
			undefined4 m_unk0x00; // 0x00
			LegoU16 m_unk0x04;    // 0x04
			undefined2 m_unk0x06; // 0x06
			GolVec3* m_unk0x08;   // 0x08
		};

		// SIZE 0x14
		class Node {
		public:
			GolVec3* FUN_00404660(GolVec3* p_dest) const;

			GolVec3 m_unk0x00; // 0x00
			LegoU16 m_unk0x0c; // 0x0c
			LegoU16 m_unk0x0e; // 0x0e
			LegoU16 m_unk0x10; // 0x10
			LegoU16 m_unk0x12; // 0x12
		};

		// SIZE 0x08
		class Triangle {
		public:
			LegoU16 m_unk0x00; // 0x00
			LegoU16 m_unk0x02; // 0x02
			LegoU16 m_unk0x04; // 0x04
			LegoU16 m_unk0x06; // 0x06
		};

		// SIZE 0x0c
		class Field0x18 {
		public:
			undefined4 m_unk0x00;  // 0x00
			undefined4 m_unk0x04;  // 0x04
			Field0x10** m_unk0x08; // 0x08
		};

		// SIZE 0x0c
		class TraversalEntry {
		public:
			GolVec3* m_unk0x00;  // 0x00
			LegoFloat m_unk0x04; // 0x04
			LegoU16 m_unk0x08;   // 0x08
			LegoU16 m_unk0x0a;   // 0x0a
		};

		LegoBool32 FUN_00403fa0(
			GolVec3* p_start,
			GolVec3* p_end,
			Field0x0c* p_record,
			GolVec3* p_hit,
			Field0x10** p_hitRecord,
			LegoFloat* p_amountOut
		);

		undefined4 m_unk0x00;      // 0x00
		LegoU32 m_unk0x04;         // 0x04
		Node* m_unk0x08;           // 0x08
		VertexTable* m_unk0x0c;    // 0x0c
		LegoU32 m_unk0x10;         // 0x10
		Triangle* m_unk0x14;       // 0x14
		Field0x18 m_unk0x18;       // 0x18
		Field0x18* m_unk0x24;      // 0x24
		undefined4 m_unk0x28;      // 0x28
		TraversalEntry* m_unk0x2c; // 0x2c
		GolVec3 m_unk0x30;         // 0x30
		GolVec3 m_unk0x3c;         // 0x3c
		LegoFloat m_unk0x48;       // 0x48
		LegoFloat m_unk0x4c;       // 0x4c
		Node* m_unk0x50;           // 0x50
		Field0x0c* m_unk0x54;      // 0x54
		GolVec3* m_unk0x58;        // 0x58
		Field0x10** m_unk0x5c;     // 0x5c
		LegoFloat* m_unk0x60;      // 0x60
	};

	class Field0x000 {
	public:
		// SIZE 0x64
		class Field0x0a8 : public GolOrientedEntity {
		public:
			Field0x058* m_unk0x58;            // 0x58
			Field0x058::Field0x18* m_unk0x5c; // 0x5c
			LegoU32 m_unk0x60;                // 0x60
		};

		undefined m_unk0x000[0x064 - 0x000]; // 0x000
		LegoU32 m_unk0x064;                  // 0x064
		undefined m_unk0x068[0x0a8 - 0x068]; // 0x068
		Field0x0a8* m_unk0x0a8;              // 0x0a8
		undefined m_unk0x0ac[0x0d8 - 0x0ac]; // 0x0ac
		GolNameTable m_unk0x0d8;             // 0x0d8
	};

	RaceSessionField0x32b4();
	Field0x000* FUN_0041f440(
		Field0x000* p_unk0x04,
		LegoChar* p_unk0x08,
		RaceEventTable0x90* p_unk0x0c,
		undefined4 p_unk0x10
	);
	LegoBool32 FUN_0041f4d0(
		GolVec3* p_unk0x04,
		GolVec3* p_unk0x08,
		Field0x0c* p_unk0x0c,
		GolVec3* p_unk0x10,
		Field0x14** p_unk0x14
	);
	LegoBool32 FUN_0041f730(GolVec3* p_unk0x04, GolVec3* p_unk0x08, Field0x0c* p_unk0x0c, GolVec3* p_unk0x10);

private:
	Field0x000* m_unk0x00;             // 0x00
	RaceEventTable0x90* m_unk0x04;     // 0x04
	undefined4 m_unk0x08;              // 0x08
	Field0x000::Field0x0a8* m_unk0x0c; // 0x0c
};

#endif // RACESESSIONFIELD0X32B4_H
