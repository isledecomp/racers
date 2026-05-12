#ifndef GDBCOMMONVERTEXARRAY0x1C_H
#define GDBCOMMONVERTEXARRAY0x1C_H

#include "compat.h"
#include "gdbvertexarray0xc.h"

// VTABLE: GOLDP 0x100568d0
// SIZE 0x1c
class GdbCommonVertexArray0x1c : public GdbVertexArray0xc {
public:
	GdbCommonVertexArray0x1c();
	~GdbCommonVertexArray0x1c() override; // vtable+0x00
	void VTable0x0c() override;
	void VTable0x34(const PixelFormatMod& p_details) override;
	void VTable0x38() override;

	// SYNTHETIC: GOLDP 0x10016f40
	// GdbCommonVertexArray0x1c::`scalar deleting destructor'

protected:
	GolVec2* m_unk0x0c;   // 0x0c
	LegoU32* m_unk0x10;   // 0x10
	undefined4 m_unk0x14; // 0x14
	LegoU32* m_unk0x18;   // 0x18
};

#endif // GDBCOMMONVERTEXARRAY0x1C_H
