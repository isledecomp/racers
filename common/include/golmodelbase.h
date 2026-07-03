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

	void FUN_100272e0(LegoU32 p_countVertices, LegoU32 p_countGroups);
	void FUN_00411090();
	GolModelMaterialTable* GetMaterialTable() { return &m_unk0x04; }
	GdbVertexArray* GetVertexArray() const { return m_unk0x10; }
	GdbModelIndexArrayBase* GetIndexArray() const { return m_unk0x18; }
	const GolVec3& GetCenter() const { return m_unk0x28; }
	const GolVec3& GetBoundingCenter() const { return m_unk0x28; }
	LegoFloat GetRadius() const { return m_unk0x34; }
	LegoFloat GetBoundingRadius() const { return m_unk0x34; }
	LegoFloat GetScale() const { return m_unk0x38; }
	void SetScale(LegoFloat p_scale) { m_unk0x38 = p_scale; }
	void SetDirty(LegoBool32 p_dirty) { m_unk0x3c = p_dirty; }
	LegoU32 GetGroupCount() const { return m_countGroups; }
	const LegoU32* GetGroups() const { return m_unk0x24; }
	LegoU32* GetMutableGroups() { return m_unk0x24; }

	// SYNTHETIC: GOLDP 0x10027070
	// GolModelBase::`scalar deleting destructor'

protected:
	GolModelMaterialTable m_unk0x04;
	GdbVertexArray* m_unk0x10;
	GdbVertexArray* m_unk0x14;
	GdbModelIndexArrayBase* m_unk0x18;
	undefined4* m_unk0x1c;
	LegoU32 m_countGroups;
	LegoU32* m_unk0x24;
	GolVec3 m_unk0x28;
	LegoFloat m_unk0x34;
	LegoFloat m_unk0x38;
	LegoBool32 m_unk0x3c;
};

#endif // GOLMODELBASE_H
