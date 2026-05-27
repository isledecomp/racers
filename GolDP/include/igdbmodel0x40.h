#ifndef IGDBMODEL0x40_H
#define IGDBMODEL0x40_H

#include "decomp.h"
#include "golmath.h"
#include "goltxtparser.h"
#include "shadowwolf0xc.h"
#include "types.h"

class GdbVertexArray0xc;
class GolFileParser;
struct GolVec3;
class IGdbModelIndexArray0x8;
struct ColorTransform0x20;
class WhiteFalcon0x140;

// VTABLE: GOLDP 0x10057224
// SIZE 0x40
class IGdbModel0x40 {
public:
	// VTABLE: GOLDP 0x100570bc
	// SIZE 0x1fc
	class GdbTxtParser : public GolTxtParser {};

	IGdbModel0x40();

	virtual void VTable0x00(GolFileParser& p_parser);     // vtable+0x00
	virtual void VTable0x04(GolFileParser& p_parser);     // vtable+0x04
	virtual void VTable0x08(GolFileParser& p_parser);     // vtable+0x08
	virtual void VTable0x0c(GolFileParser& p_parser) = 0; // vtable+0x0c
	virtual void VTable0x10(GolFileParser& p_parser) = 0; // vtable+0x10
	virtual void VTable0x14(GolFileParser& p_parser);     // vtable+0x14
	virtual void VTable0x18(
		WhiteFalcon0x140* p_renderer,
		undefined2,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) = 0;                                                                                              // vtable+0x18
	virtual void VTable0x1c(WhiteFalcon0x140* p_renderer, const LegoChar* p_name, LegoBool32 p_binary); // vtable+0x1c
	virtual ~IGdbModel0x40();                                                                           // vtable+0x20
	virtual void VTable0x24();                                                                          // vtable+0x24
	virtual void VTable0x28(GdbVertexArray0xc** p_dest) const;                                          // vtable+0x28
	virtual void VTable0x2c(LegoU32, LegoBool32);                                                       // vtable+0x2c
	virtual void VTable0x30(IGdbModelIndexArray0x8**) const;                                            // vtable+0x30
	virtual void VTable0x34(LegoU32);                                                                   // vtable+0x34
	virtual void VTable0x38(GolVec3*, LegoFloat*, LegoFloat) const;                                     // vtable+0x38
	virtual void VTable0x3c(const ColorTransform0x20&);                                                 // vtable+0x3c
	virtual void VTable0x40();                                                                          // vtable+0x40

	void FUN_100272e0(LegoU32 p_countVertices, LegoU32 p_countGroups);
	ShadowWolf0xc* GetMaterialTable() { return &m_unk0x04; }
	GdbVertexArray0xc* GetVertexArray() const { return m_unk0x10; }
	IGdbModelIndexArray0x8* GetIndexArray() const { return m_unk0x18; }
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
	// IGdbModel0x40::`scalar deleting destructor'

protected:
	ShadowWolf0xc m_unk0x04;
	GdbVertexArray0xc* m_unk0x10;
	GdbVertexArray0xc* m_unk0x14;
	IGdbModelIndexArray0x8* m_unk0x18;
	undefined4* m_unk0x1c;
	LegoU32 m_countGroups;
	LegoU32* m_unk0x24;
	GolVec3 m_unk0x28;
	LegoFloat m_unk0x34;
	LegoFloat m_unk0x38;
	LegoBool32 m_unk0x3c;
};

#endif // IGDBMODEL0x40_H
