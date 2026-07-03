#ifndef GDBNORMALVERTEXARRAY_H
#define GDBNORMALVERTEXARRAY_H

#include "compat.h"
#include "mesh/gdbcoloredvertexarraybase.h"

// VTABLE: GOLDP 0x10056894
// SIZE 0x20
class GdbNormalVertexArray : public GdbColoredVertexArrayBase {
public:
	GdbNormalVertexArray();

	void VTable0x04(LegoU16 p_count) override;                          // vtable+0x04
	void VTable0x08(GolFileParser& p_parser) override;                  // vtable+0x08
	void VTable0x0c() override;                                         // vtable+0x0c
	void VTable0x18(LegoU32 p_index, GolVec2* p_dest) const override;   // vtable+0x18
	void VTable0x1c(LegoU32 p_index, GolVec3* p_dest) const override;   // vtable+0x1c
	void VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) const override; // vtable+0x20
	void VTable0x28(LegoU32 p_index, const GolVec2&) override;          // vtable+0x28
	void VTable0x2c(LegoU32 p_index, const GolVec3&) override;          // vtable+0x2c
	void VTable0x30(LegoU32 p_index, const ColorRGBA&) override;        // vtable+0x30

	GolVec3* GetNormals() const { return m_unk0x1c; }

protected:
	GolVec3* m_unk0x1c; // 0x1c
};

#endif // GDBNORMALVERTEXARRAY_H
