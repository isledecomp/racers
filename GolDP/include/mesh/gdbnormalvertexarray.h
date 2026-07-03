#ifndef GDBNORMALVERTEXARRAY_H
#define GDBNORMALVERTEXARRAY_H

#include "compat.h"
#include "mesh/gdbcoloredvertexarraybase.h"

// VTABLE: GOLDP 0x10056894
// SIZE 0x20
class GdbNormalVertexArray : public GdbColoredVertexArrayBase {
public:
	GdbNormalVertexArray();

	void Allocate(LegoU16 p_count) override;                                    // vtable+0x04
	void Parse(GolFileParser& p_parser) override;                               // vtable+0x08
	void Destroy() override;                                                    // vtable+0x0c
	void GetTextureCoordinate(LegoU32 p_index, GolVec2* p_dest) const override; // vtable+0x18
	void GetNormal(LegoU32 p_index, GolVec3* p_dest) const override;            // vtable+0x1c
	void GetColor(LegoU32 p_index, ColorRGBA* p_dest) const override;           // vtable+0x20
	void SetTextureCoordinate(LegoU32 p_index, const GolVec2&) override;        // vtable+0x28
	void SetNormal(LegoU32 p_index, const GolVec3&) override;                   // vtable+0x2c
	void SetColor(LegoU32 p_index, const ColorRGBA&) override;                  // vtable+0x30

	GolVec3* GetNormals() const { return m_normals; }

protected:
	GolVec3* m_normals; // 0x1c
};

#endif // GDBNORMALVERTEXARRAY_H
