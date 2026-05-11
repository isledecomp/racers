#ifndef GDBVERTEXARRAYTYPETHREE0x20_H
#define GDBVERTEXARRAYTYPETHREE0x20_H

#include "compat.h"
#include "gdbvertexarraytypetwo0x20.h"

// VTABLE: GOLDP 0x10056858
// SIZE 0x20
class GdbVertexArrayTypeThree0x20 : public GdbVertexArrayTypeTwo0x20 {
public:
	GdbVertexArrayTypeThree0x20();

	void VTable0x04(LegoU16 p_count) override;         // vtable+0x04
	void VTable0x08(GolFileParser& p_parser) override; // vtable+0x08
	void VTable0x10() override;                        // vtable+0x10

	// SYNTHETIC: GOLDP 0x10016af0 FOLDED
	// GdbVertexArrayTypeThree0x20::`scalar deleting destructor'
};

#endif // GDBVERTEXARRAYTYPETHREE0x20_H
