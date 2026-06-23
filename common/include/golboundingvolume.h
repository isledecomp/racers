#ifndef GOLBOUNDINGVOLUME_H
#define GOLBOUNDINGVOLUME_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelmaterialtable.h"
#include "goltxtparser.h"
#include "types.h"

class GdbVertexArray0xc;
class GolRenderDevice;
class RaceEventRecord;

// VTABLE: GOLDP 0x10056c3c
// SIZE 0x64
class GolBoundingVolume {
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

	// .bvb binary block tags (cf. data/liblr1/LibLR1/BVB.cs).
	enum BvbBlockType {
		c_bvbMaterials = 0x27,
		c_bvbPolygons = 0x2d,
		c_bvbVertices = 0x34,
		c_bvbPolygonRanges = 0x8e,
	};

	// VTABLE: GOLDP 0x10056c48
	// SIZE 0x1fc
	class BvbTxtParser : public GolTxtParser {
		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolBoundingVolume::BvbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolBoundingVolume::BvbTxtParser::~BvbTxtParser
	};

	GolBoundingVolume();

	virtual ~GolBoundingVolume(); // vtable+0x00
	virtual void VTable0x04(GolRenderDevice* p_renderer, const LegoChar* p_name,
							LegoBool32 p_binary); // vtable+0x04
	virtual void VTable0x08();                    // vtable+0x08

	// SYNTHETIC: GOLDP 0x1002e5e0
	// GolBoundingVolume::`vector deleting destructor'

	void FUN_004045e0();
	LegoBool32 FUN_00403fa0(
		GolVec3* p_start,
		GolVec3* p_end,
		Field0x0c* p_record,
		GolVec3* p_hit,
		RaceEventRecord** p_hitRecord,
		LegoFloat* p_amountOut
	);
	GolModelMaterialTable* GetUnk0x18() { return &m_unk0x18; }
	void SetUnk0x24(GolModelMaterialTable* p_unk0x24) { m_unk0x24 = p_unk0x24; }

	enum {
		c_invalidChildIndex = 0xfffe,
	};

	// SIZE 0x08
	struct PolygonId0x08 {
		LegoU16 m_unk0x00; // 0x00
		LegoU16 m_unk0x02; // 0x02
		LegoU16 m_unk0x04; // 0x04
		LegoU16 m_unk0x06; // 0x06
	};

	// SIZE 0x14
	struct PolygonRange0x14 {
		GolVec3* FUN_00404660(GolVec3* p_dest) const;
		LegoU16& GetChildIndexSlot(LegoU32 p_index) { return m_unk0x10[p_index]; }

		GolVec3 m_unk0x00;    // 0x00
		undefined2 m_unk0x0c; // 0x0c
		undefined2 m_unk0x0e; // 0x0e
		LegoU16 m_unk0x10[2]; // 0x10
	};

	// SIZE 0x0c
	struct TraversalEntry0x0c {
		GolVec3* m_unk0x00;  // 0x00
		LegoFloat m_unk0x04; // 0x04
		LegoU16 m_unk0x08;   // 0x08
		LegoU16 m_unk0x0a;   // 0x0a
	};

private:
	void FUN_1001bb10(GolFileParser& p_parser);
	void FUN_1001bbb0(GolFileParser& p_parser);
	void FUN_1001bd00(GolFileParser& p_parser);
	undefined4 FUN_1001be50();

	undefined4 m_unk0x04;             // 0x04
	PolygonRange0x14* m_unk0x08;      // 0x08
	GdbVertexArray0xc* m_unk0x0c;     // 0x0c
	undefined4 m_unk0x10;             // 0x10
	PolygonId0x08* m_unk0x14;         // 0x14
	GolModelMaterialTable m_unk0x18;  // 0x18
	GolModelMaterialTable* m_unk0x24; // 0x24
	undefined4 m_unk0x28;             // 0x28
	TraversalEntry0x0c* m_unk0x2c;    // 0x2c
	GolVec3 m_unk0x30;                // 0x30
	GolVec3 m_unk0x3c;                // 0x3c
	LegoFloat m_unk0x48;              // 0x48
	LegoFloat m_unk0x4c;              // 0x4c
	PolygonRange0x14* m_unk0x50;      // 0x50
	Field0x0c* m_unk0x54;             // 0x54
	GolVec3* m_unk0x58;               // 0x58
	RaceEventRecord** m_unk0x5c;      // 0x5c
	LegoFloat* m_unk0x60;             // 0x60
};
#endif // GOLBOUNDINGVOLUME_H
