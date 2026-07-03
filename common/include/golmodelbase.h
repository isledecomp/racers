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
	class GdbTxtParser : public GolTxtParser {};

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
	virtual void CommitColorTransform();                                                         // vtable+0x40

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
	LegoU32 GetGroupCount() const { return m_countGroups; }
	const LegoU32* GetGroups() const { return m_groups; }
	LegoU32* GetMutableGroups() { return m_groups; }

	// SYNTHETIC: GOLDP 0x10027070
	// GolModelBase::`scalar deleting destructor'

protected:
	GolModelMaterialTable m_materialTable;
	GdbVertexArray* m_vertexArray;
	GdbVertexArray* m_unk0x14;
	GdbModelIndexArrayBase* m_indexArray;
	undefined4* m_unk0x1c;
	LegoU32 m_countGroups;
	LegoU32* m_groups;
	GolVec3 m_center;
	LegoFloat m_radius;
	LegoFloat m_scale;
	LegoBool32 m_dirty;
};

#endif // GOLMODELBASE_H
