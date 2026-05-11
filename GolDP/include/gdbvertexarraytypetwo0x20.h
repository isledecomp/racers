#ifndef GDBVERTEXARRAYTYPETWO0x20_H
#define GDBVERTEXARRAYTYPETWO0x20_H

#include "compat.h"
#include "gdbcommonvertexarray0x1c.h"

// VTABLE: GOLDP 0x10056894
// SIZE 0x20
class GdbVertexArrayTypeTwo0x20 : public GdbCommonVertexArray0x1c {
public:
	GdbVertexArrayTypeTwo0x20();

	void VTable0x04(LegoU16 p_count) override;                    // vtable+0x04
	void VTable0x08(GolFileParser& p_parser) override;            // vtable+0x08
	void VTable0x0c() override;                                   // vtable+0x0c
	void VTable0x18(LegoU32 p_index, GolVec2* p_dest) override;   // vtable+0x18
	void VTable0x1c(LegoU32 p_index, GolVec3* p_dest) override;   // vtable+0x1c
	void VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) override; // vtable+0x20
	void VTable0x28(LegoU32 p_index, const GolVec2&) override;    // vtable+0x28
	void VTable0x2c(LegoU32 p_index, const GolVec3&) override;    // vtable+0x2c
	void VTable0x30(LegoU32 p_index, const ColorRGBA&) override;  // vtable+0x30

	// SYNTHETIC: GOLDP 0x10016af0 FOLDED
	// GdbVertexArrayTypeTwo0x20::`scalar deleting destructor'

protected:
	GolVec3* m_unk0x1c; // 0x1c
};

#endif // GDBVERTEXARRAYTYPETWO0x20_H
