#ifndef GOLBOUNDINGVOLUME_H
#define GOLBOUNDINGVOLUME_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelmaterialtable.h"
#include "goltxtparser.h"
#include "types.h"

class GdbVertexArray;
class GolRenderDevice;
class RaceEventRecord;

// VTABLE: GOLDP 0x10056c3c
// SIZE 0x64
class GolBoundingVolume {
public:
	// SIZE 0x34
	class HitTriangle {
	public:
		const LegoFloat* GetFloatData() const { return &m_vertex0.m_x; }

		GolVec3 m_vertex0;         // 0x00
		GolVec3 m_vertex1;         // 0x0c
		GolVec3 m_vertex2;         // 0x18
		GolVec3 m_normal;          // 0x24
		LegoFloat m_planeDistance; // 0x30
	};

	// .bvb binary block tags
	enum BvbBlockType {
		c_bvbMaterials = 0x27,
		c_bvbTriangles = 0x2d,
		c_bvbVertices = 0x34,
		c_bvbNodes = 0x8b,
		c_bvbNodesFixedPoint = 0x8e,
		c_bvbChildNone = 0x8c,
		c_bvbChildLeaf = 0x8d,
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
	virtual void Load(GolRenderDevice* p_renderer, const LegoChar* p_name,
					  LegoBool32 p_binary); // vtable+0x04
	virtual void Destroy();                 // vtable+0x08

	// SYNTHETIC: GOLDP 0x1002e5e0
	// GolBoundingVolume::`vector deleting destructor'

	void MirrorY();
	LegoBool32 IntersectSegment(
		GolVec3* p_start,
		GolVec3* p_end,
		HitTriangle* p_record,
		GolVec3* p_hit,
		RaceEventRecord** p_hitRecord,
		LegoFloat* p_amountOut
	);
	GolModelMaterialTable* GetMaterialTable() { return &m_materialTable; }
	void SetMaterialTable(GolModelMaterialTable* p_materialTable) { m_activeMaterialTable = p_materialTable; }

	enum {
		c_invalidChildIndex = 0xfffe,
	};

	// SIZE 0x08
	struct Triangle {
		LegoU16 m_vertex0;       // 0x00
		LegoU16 m_vertex1;       // 0x02
		LegoU16 m_vertex2;       // 0x04
		LegoU16 m_materialIndex; // 0x06
	};

	// SIZE 0x14
	struct BspNode {
		GolVec3* GetPlaneNormal(GolVec3* p_dest) const;
		LegoU16& GetChildIndexSlot(LegoU32 p_index) { return m_childIndices[p_index]; }

		GolVec3 m_planeNormal;      // 0x00
		undefined2 m_firstTriangle; // 0x0c
		undefined2 m_triangleCount; // 0x0e
		LegoU16 m_childIndices[2];  // 0x10
	};

	// SIZE 0x0c
	struct TraversalEntry {
		GolVec3* m_planePoint;     // 0x00
		LegoFloat m_startDistance; // 0x04
		LegoU16 m_nodeIndex;       // 0x08
		LegoU16 m_stage;           // 0x0a
	};

private:
	void ParseTriangles(GolFileParser& p_parser);
	void ParseNodes(GolFileParser& p_parser);
	void ParseNodesFixedPoint(GolFileParser& p_parser);
	undefined4 ComputeTraversalDepth();

	LegoU32 m_nodeCount;                          // 0x04
	BspNode* m_nodes;                             // 0x08
	GdbVertexArray* m_vertices;                   // 0x0c
	LegoU32 m_triangleCount;                      // 0x10
	Triangle* m_triangles;                        // 0x14
	GolModelMaterialTable m_materialTable;        // 0x18
	GolModelMaterialTable* m_activeMaterialTable; // 0x24
	undefined4 m_traversalDepth;                  // 0x28
	TraversalEntry* m_traversalStack;             // 0x2c
	GolVec3 m_segmentStart;                       // 0x30
	GolVec3 m_segmentEnd;                         // 0x3c
	LegoFloat m_startDistance;                    // 0x48
	LegoFloat m_endDistance;                      // 0x4c
	BspNode* m_hitNode;                           // 0x50
	HitTriangle* m_hitTriangle;                   // 0x54
	GolVec3* m_hitPoint;                          // 0x58
	RaceEventRecord** m_hitRecord;                // 0x5c
	LegoFloat* m_hitAmount;                       // 0x60
};
#endif // GOLBOUNDINGVOLUME_H
