#ifndef GOLMODEL_H
#define GOLMODEL_H

#include "compat.h"
#include "decomp.h"
#include "golboundingshape.h"
#include "golmodelbase.h"

class GdbVertexArray;
class GolD3DRenderDevice;
struct MaterialTable;

// VTABLE: GOLDP 0x100563fc
// SIZE 0x48
class GolModel : public GolModelBase {
public:
	enum {
		e_vertexType1 = 1,
		e_vertexType2 = 2,
		e_vertexType3 = 3,
	};

	enum GdbModelGroupType {
		c_groupTypeMask = 0xe0000000,
		c_groupTypeTriangles = 0x00000000,
		c_groupTypeTriangleBatch = 0x20000000,
		c_groupTypeMaterial = 0x80000000,
		c_groupTypeMatrix = 0xa0000000,
		c_groupTypeEnd = 0xc0000000,
	};

	enum GdbGroupDataFields {
		c_triangleCountMask = 0x7f,
		c_vertexCountMask = 0x3f,
		c_vertexIndexHighFlag = 0x40,
		c_materialMatrixIndexMask = 0xffff,
		c_matrixSelectShift = 22,
		c_groupDataUpperWordShift = 16,
		c_lastVertexShift = 23,
	};

	GolModel();
	~GolModel() override; // vtable+0x20

	void ParseUncoloredVertices(GolFileParser& p_parser) override; // vtable+0x0c
	void ParseColoredVertices(GolFileParser& p_parser) override;   // vtable+0x10
	void ParseNormalVertices(GolFileParser& p_parser) override;    // vtable+0x14
	void Allocate(
		GolRenderDevice* p_renderer,
		undefined2,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) override;                                                                                   // vtable+0x18
	void Load(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoBool32 p_binary) override; // vtable+0x1c
	void Destroy() override;                                                                      // vtable+0x24
	void Draw(GolD3DRenderDevice* p_renderer, MaterialTable* p_materialTable);
	void DrawNode(
		GolD3DRenderDevice* p_renderer,
		MaterialTable* p_materialTable,
		GolBoundingShape::TreeNode::Node* p_node
	);
	LegoU32 FindMaxVertexIndex(LegoU32 p_firstTriangle, LegoU32 p_triangleCount) const;
	GdbVertexArray* GetModelVertexArray() const { return m_modelVertexArray; }

	// SYNTHETIC: GOLDP 0x100178e0
	// GolModel::`vector deleting destructor'

private:
	GdbVertexArray* m_modelVertexArray; // 0x40
	undefined m_unk0x44[0x48 - 0x44];   // 0x44
};

#endif // GOLMODEL_H
