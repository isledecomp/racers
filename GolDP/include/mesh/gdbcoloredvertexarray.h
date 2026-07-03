#ifndef GDBCOLOREDVERTEXARRAY_H
#define GDBCOLOREDVERTEXARRAY_H

#include "compat.h"
#include "mesh/gdbcoloredvertexarraybase.h"

struct GolVec2;
struct ColorRGBA;

// VTABLE: GOLDP 0x10056388
// SIZE 0x1c
class GdbColoredVertexArray : public GdbColoredVertexArrayBase {
public:
	GdbColoredVertexArray();

	void Allocate(LegoU16 p_count) override;                                    // vtable+0x04
	void Parse(GolFileParser& p_parser) override;                               // vtable+0x08
	void GetTextureCoordinate(LegoU32 p_index, GolVec2* p_dest) const override; // vtable+0x18
	void GetColor(LegoU32 p_index, ColorRGBA* p_dest) const override;           // vtable+0x20
	void SetTextureCoordinate(LegoU32 p_index, const GolVec2& p_arg2) override; // vtable+0x28
	void SetColor(LegoU32 p_index, const ColorRGBA&) override;                  // vtable+0x30

	// SYNTHETIC: GOLDP 0x10005fb0 FOLDED
	// GdbColoredVertexArray::~GdbColoredVertexArray

	// SYNTHETIC: GOLDP 0x10016af0 FOLDED
	// GdbColoredVertexArray::`scalar deleting destructor'
};

#endif // GDBCOLOREDVERTEXARRAY_H
