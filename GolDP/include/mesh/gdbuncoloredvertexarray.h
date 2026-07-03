#ifndef GDBUNCOLOREDVERTEXARRAY_H
#define GDBUNCOLOREDVERTEXARRAY_H

#include "compat.h"
#include "mesh/gdbcoloredvertexarray.h"

// VTABLE: GOLDP 0x100567b4
// SIZE 0x1c
class GdbUncoloredVertexArray : public GdbColoredVertexArray {
public:
	GdbUncoloredVertexArray();

	void VTable0x04(LegoU16 p_count) override;                          // vtable+0x04
	void VTable0x08(GolFileParser& p_parser) override;                  // vtable+0x08
	void VTable0x18(LegoU32 p_index, GolVec2* p_dest) const override;   // vtable+0x18
	void VTable0x20(LegoU32 p_index, ColorRGBA* p_dest) const override; // vtable+0x20
	void VTable0x28(LegoU32 p_index, const GolVec2&) override;          // vtable+0x28

	// SYNTHETIC: GOLDP 0x10005fb0 FOLDED
	// GdbUncoloredVertexArray::~GdbUncoloredVertexArray

	// SYNTHETIC: GOLDP 0x10016af0 FOLDED
	// GdbUncoloredVertexArray::`scalar deleting destructor'
};

#endif // GDBUNCOLOREDVERTEXARRAY_H
