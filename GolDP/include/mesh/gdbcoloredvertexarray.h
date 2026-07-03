#ifndef GDBCOLOREDVERTEXARRAY_H
#define GDBCOLOREDVERTEXARRAY_H

#include "compat.h"
#include "gdbvertexarray.h"

// VTABLE: GOLDP 0x100568d0
// SIZE 0x1c
class GdbColoredVertexArray : public GdbVertexArray {
public:
	GdbColoredVertexArray();
	~GdbColoredVertexArray() override; // vtable+0x00
	void VTable0x0c() override;
	void VTable0x34(const ColorTransform& p_details) override;
	void VTable0x38() override;

	// SYNTHETIC: GOLDP 0x10016f40
	// GdbColoredVertexArray::`scalar deleting destructor'

	GolVec2* GetTextureCoordinates() const { return m_unk0x0c; }
	LegoU32* GetColors() const { return m_unk0x10; }
	LegoBool32 HasTransformedColors() const { return m_unk0x14; }
	LegoU32* GetTransformedColors() const { return m_unk0x18; }

protected:
	GolVec2* m_unk0x0c;   // 0x0c
	LegoU32* m_unk0x10;   // 0x10
	undefined4 m_unk0x14; // 0x14
	LegoU32* m_unk0x18;   // 0x18
};

#endif // GDBCOLOREDVERTEXARRAY_H
