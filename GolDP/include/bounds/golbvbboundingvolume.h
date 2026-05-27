#ifndef GOLBVBBOUNDINGVOLUME_H
#define GOLBVBBOUNDINGVOLUME_H

#include "decomp.h"
#include "golmath.h"
#include "goltxtparser.h"
#include "mesh/golgdbmateriallist.h"
#include "types.h"

class GdbVertexArray0xc;
class GolRenderDevice;

// VTABLE: GOLDP 0x10056c3c
// SIZE 0x64
class GolBvbBoundingVolume {
public:
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
		// GolBvbBoundingVolume::BvbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolBvbBoundingVolume::BvbTxtParser::~BvbTxtParser
	};

	GolBvbBoundingVolume();

	virtual ~GolBvbBoundingVolume(); // vtable+0x00
	virtual void VTable0x04(GolRenderDevice* p_renderer, const LegoChar* p_name,
							LegoBool32 p_binary); // vtable+0x04
	virtual void VTable0x08();                    // vtable+0x08

	// SYNTHETIC: GOLDP 0x1002e5e0
	// GolBvbBoundingVolume::`vector deleting destructor'

private:
	struct PolygonId0x08 {
		LegoU16 m_unk0x00;
		LegoU16 m_unk0x02;
		LegoU16 m_unk0x04;
		LegoU16 m_unk0x06;
	};
	struct PolygonRange0x14 {
		GolVec3 m_unk0x00;
		undefined2 m_unk0x0c;
		undefined2 m_unk0x0e;
		undefined2 m_unk0x10[2];
	};

	void FUN_1001bb10(GolFileParser& p_parser);
	void FUN_1001bbb0(GolFileParser& p_parser);
	void FUN_1001bd00(GolFileParser& p_parser);
	undefined4 FUN_1001be50();

	undefined4 m_unk0x04;             // 0x04
	PolygonRange0x14* m_unk0x08;      // 0x08
	GdbVertexArray0xc* m_unk0x0c;     // 0x0c
	undefined4 m_unk0x10;             // 0x10
	PolygonId0x08* m_unk0x14;         // 0x14
	GolGdbMaterialList m_unk0x18;     // 0x18
	GolGdbMaterialList* m_unk0x24;    // 0x24
	undefined4 m_unk0x28;             // 0x28
	GolVec3* m_unk0x2c;               // 0x2c
	undefined m_unk0x30[0x64 - 0x30]; // 0x30
};
#endif // GOLBVBBOUNDINGVOLUME_H
