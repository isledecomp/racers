#ifndef GDBPRELITVERTEXARRAY_H
#define GDBPRELITVERTEXARRAY_H

#include "compat.h"
#include "mesh/gdbnormalvertexarray.h"

// VTABLE: GOLDP 0x10056858
// SIZE 0x20
class GdbPrelitVertexArray : public GdbNormalVertexArray {
public:
	GdbPrelitVertexArray();

	void VTable0x04(LegoU16 p_count) override;         // vtable+0x04
	void VTable0x08(GolFileParser& p_parser) override; // vtable+0x08
	void VTable0x10() override;                        // vtable+0x10
};

#endif // GDBPRELITVERTEXARRAY_H
