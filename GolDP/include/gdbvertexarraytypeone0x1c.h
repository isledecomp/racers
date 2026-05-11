#ifndef GDBVERTEXARRAYTYPEONE0x1C_H
#define GDBVERTEXARRAYTYPEONE0x1C_H

#include "compat.h"
#include "gdbcommonvertexarray0x1c.h"

struct GolVec2;
struct ColorRGBA;

// VTABLE: GOLDP 0x10056388
// SIZE 0x1c
class GdbVertexArrayTypeOne0x1c : public GdbCommonVertexArray0x1c {
public:
	GdbVertexArrayTypeOne0x1c();

	void VTable0x04(LegoU16 p_count) override;                        // vtable+0x04
	void VTable0x08(GolFileParser& p_parser) override;                // vtable+0x08
	void VTable0x18(LegoU32 p_index, GolVec2* p_dest) override;       // vtable+0x18
	void VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) override;     // vtable+0x20
	void VTable0x28(LegoU32 p_index, const GolVec2& p_arg2) override; // vtable+0x28
	void VTable0x30(LegoU32 p_index, const ColorRGBA&) override;      // vtable+0x30

	// SYNTHETIC: GOLDP 0x10005fb0
	// GdbVertexArrayTypeOne0x1c::~GdbVertexArrayTypeOne0x1c

	// SYNTHETIC: GOLDP 0x10016af0 FOLDED
	// GdbVertexArrayTypeOne0x1c::`scalar deleting destructor'
};

#endif // GDBVERTEXARRAYTYPEONE0x1C_H
