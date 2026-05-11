#ifndef GDBMODEL0x48_H
#define GDBMODEL0x48_H

#include "compat.h"
#include "decomp.h"
#include "igdbmodel0x40.h"

class GdbVertexArray0xc;

// VTABLE: GOLDP 0x100563fc
// SIZE 0x48
class GdbModel0x48 : public IGdbModel0x40 {
public:
	enum {
		e_vertexType1 = 1,
		e_vertexType2 = 2,
		e_vertexType3 = 3,
	};

	GdbModel0x48();
	~GdbModel0x48() override; // vtable+0x20

	void VTable0x0c(GolFileParser& p_parser) override;                                                // vtable+0x0c
	void VTable0x10(GolFileParser& p_parser) override;                                                // vtable+0x10
	void VTable0x14(GolFileParser& p_parser) override;                                                // vtable+0x14
	void VTable0x18(undefined4, undefined2, undefined4, undefined4, undefined4, undefined4) override; // vtable+0x18
	void VTable0x1c(undefined4 p_arg1, const LegoChar* p_name, LegoBool32 p_binary) override;         // vtable+0x1c
	void VTable0x24() override;                                                                       // vtable+0x24

	// SYNTHETIC: GOLDP 0x100178e0
	// GdbModel0x48::`vector deleting destructor'

private:
	GdbVertexArray0xc* m_unk0x40;     // 0x44
	undefined m_unk0x44[0x48 - 0x44]; // 0x44
};

#endif // GDBMODEL0x48_H
