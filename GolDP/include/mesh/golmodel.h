#ifndef GOLMODEL_H
#define GOLMODEL_H

#include "bounds/golboundingshape.h"
#include "compat.h"
#include "decomp.h"
#include "mesh/golmodelbase.h"

class GdbVertexArray0xc;
class GolD3DRenderDevice;
struct MaterialTable0x0c;

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

	void VTable0x0c(GolFileParser& p_parser) override; // vtable+0x0c
	void VTable0x10(GolFileParser& p_parser) override; // vtable+0x10
	void VTable0x14(GolFileParser& p_parser) override; // vtable+0x14
	void VTable0x18(
		GolRenderDevice* p_renderer,
		undefined2,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) override;                                                                                         // vtable+0x18
	void VTable0x1c(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoBool32 p_binary) override; // vtable+0x1c
	void VTable0x24() override;                                                                         // vtable+0x24
	void FUN_10006c50(GolD3DRenderDevice* p_renderer, MaterialTable0x0c* p_materialTable);
	void FUN_10006e00(
		GolD3DRenderDevice* p_renderer,
		MaterialTable0x0c* p_materialTable,
		GolBoundingShape::StructField0x08::Node* p_node
	);
	LegoU32 FUN_10006fa0(LegoU32 p_firstTriangle, LegoU32 p_triangleCount) const;
	GdbVertexArray0xc* GetModelVertexArray() const { return m_unk0x40; }

	// SYNTHETIC: GOLDP 0x100178e0
	// GolModel::`vector deleting destructor'

private:
	GdbVertexArray0xc* m_unk0x40;     // 0x40
	undefined m_unk0x44[0x48 - 0x44]; // 0x44
};

#endif // GOLMODEL_H
