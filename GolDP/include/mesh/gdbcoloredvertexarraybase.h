#ifndef GDBCOLOREDVERTEXARRAYBASE_H
#define GDBCOLOREDVERTEXARRAYBASE_H

#include "compat.h"
#include "gdbvertexarray.h"

// VTABLE: GOLDP 0x100568d0
// SIZE 0x1c
class GdbColoredVertexArrayBase : public GdbVertexArray {
public:
	GdbColoredVertexArrayBase();
	~GdbColoredVertexArrayBase() override; // vtable+0x00
	void VTable0x0c() override;
	void VTable0x34(const ColorTransform& p_details) override;
	void VTable0x38() override;

	// SYNTHETIC: GOLDP 0x10016f40
	// GdbColoredVertexArrayBase::`scalar deleting destructor'

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

#endif // GDBCOLOREDVERTEXARRAYBASE_H
