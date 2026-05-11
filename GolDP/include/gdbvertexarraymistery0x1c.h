#ifndef GDBVERTEXARRAYMISTERY0x1C_H
#define GDBVERTEXARRAYMISTERY0x1C_H

#include "compat.h"
#include "gdbcommonvertexarray0x1c.h"

// VTABLE: GOLDP 0x100567b4
// SIZE 0x1c
class GdbVertexArrayMistery0x1c : public GdbCommonVertexArray0x1c {
public:
	GdbVertexArrayMistery0x1c();

	void VTable0x04(LegoU16 p_count) override;                    // vtable+0x04
	void VTable0x08(GolFileParser& p_parser) override;            // vtable+0x08
	void VTable0x18(LegoU32 p_index, GolVec2* p_dest) override;   // vtable+0x18
	void VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) override; // vtable+0x20
	void VTable0x28(LegoU32 p_index, const GolVec2&) override;    // vtable+0x28

	// SYNTHETIC: GOLDP 0x10016af0 FOLDED
	// GdbVertexArrayMistery0x1c::`scalar deleting destructor'
};

#endif // GDBVERTEXARRAYMISTERY0x1C_H
