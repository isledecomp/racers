#ifndef GOLMODELBASE_H
#define GOLMODELBASE_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelmaterialtable.h"
#include "goltxtparser.h"
#include "types.h"

class GdbVertexArray;
class GolFileParser;
struct GolVec3;
class GdbModelIndexArrayBase;
struct ColorTransform;
class GolRenderDevice;

// VTABLE: GOLDP 0x10057224
// SIZE 0x40
class GolModelBase {
public:
	// VTABLE: GOLDP 0x100570bc
	// SIZE 0x1fc
	class GdbTxtParser : public GolTxtParser {
	public:
		// .gdb tokens; group-stream keywords map to GolModel::GdbModelGroupType
		enum {
			e_material = 0x27,
			e_uncoloredVertices = 0x28,
			e_normalVertices = 0x29,
			e_coloredVertices = 0x2a,
			e_indices = 0x2d,
			e_triangleBatch = 0x2d,
			e_groups = 0x2e,
			e_pushMatrix = 0x2f,
			e_popMatrix = 0x30,
			e_triangles = 0x31,
			e_setMatrix = 0x32,
			e_scale = 0x33,
			e_vertices = 0x34,
		};
	};

	GolModelBase();

	virtual void ParseGroups(GolFileParser& p_parser);                // vtable+0x00
	virtual void ParseIndices(GolFileParser& p_parser);               // vtable+0x04
	virtual void ParseVertices(GolFileParser& p_parser);              // vtable+0x08
	virtual void ParseUncoloredVertices(GolFileParser& p_parser) = 0; // vtable+0x0c
	virtual void ParseColoredVertices(GolFileParser& p_parser) = 0;   // vtable+0x10
	virtual void ParseNormalVertices(GolFileParser& p_parser);        // vtable+0x14
	virtual void Allocate(
		GolRenderDevice* p_renderer,
		undefined2,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) = 0;                                                                                       // vtable+0x18
	virtual void Load(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoBool32 p_binary); // vtable+0x1c
	virtual ~GolModelBase();                                                                     // vtable+0x20
	virtual void Destroy();                                                                      // vtable+0x24
	virtual void GetVertexArray(GdbVertexArray** p_dest) const;                                  // vtable+0x28
	virtual void AddFlagsWithBounds(LegoU32, LegoBool32);                                        // vtable+0x2c
	virtual void GetIndexArrayInto(GdbModelIndexArrayBase**) const;                              // vtable+0x30
	virtual void AddFlags(LegoU32);                                                              // vtable+0x34
	virtual void ComputeBounds(GolVec3*, LegoFloat*, LegoFloat) const;                           // vtable+0x38
	virtual void ApplyColorTransform(const ColorTransform&);                                     // vtable+0x3c
	virtual void ClearColorTransform();                                                          // vtable+0x40

	void AllocateIndices(LegoU32 p_countVertices, LegoU32 p_countGroups);
	void MirrorY();
	GolModelMaterialTable* GetMaterialTable() { return &m_materialTable; }
	GdbVertexArray* GetVertexArray() const { return m_vertexArray; }
	GdbModelIndexArrayBase* GetIndexArray() const { return m_indexArray; }
	const GolVec3& GetCenter() const { return m_center; }
	const GolVec3& GetBoundingCenter() const { return m_center; }
	LegoFloat GetRadius() const { return m_radius; }
	LegoFloat GetBoundingRadius() const { return m_radius; }
	LegoFloat GetScale() const { return m_scale; }
	void SetScale(LegoFloat p_scale) { m_scale = p_scale; }
	void SetDirty(LegoBool32 p_dirty) { m_dirty = p_dirty; }
	LegoU32 GetGroupCount() const { return m_groupCount; }
	const LegoU32* GetGroups() const { return m_groups; }
	LegoU32* GetMutableGroups() { return m_groups; }

	// SYNTHETIC: GOLDP 0x10027070
	// GolModelBase::`scalar deleting destructor'

protected:
	GolModelMaterialTable m_materialTable; // 0x04
	GdbVertexArray* m_vertexArray;         // 0x10
	GdbVertexArray* m_ownedVertexArray;    // 0x14
	GdbModelIndexArrayBase* m_indexArray;  // 0x18
	undefined4* m_unk0x1c;                 // 0x1c
	LegoU32 m_groupCount;                  // 0x20
	LegoU32* m_groups;                     // 0x24
	GolVec3 m_center;                      // 0x28
	LegoFloat m_radius;                    // 0x34
	LegoFloat m_scale;                     // 0x38
	LegoBool32 m_dirty;                    // 0x3c
};

#endif // GOLMODELBASE_H
