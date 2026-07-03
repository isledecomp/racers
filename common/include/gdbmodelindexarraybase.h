#ifndef GDBMODELINDEXARRAYBASE_H
#define GDBMODELINDEXARRAYBASE_H

#include "decomp.h"
#include "types.h"

class GolFileParser;

// VTABLE: GOLDP 0x10056dfc
// SIZE 0x8
class GdbModelIndexArrayBase {
public:
	GdbModelIndexArrayBase();

	virtual ~GdbModelIndexArrayBase();               // vtable+0x00
	virtual void Parse(GolFileParser& p_parser) = 0; // vtable+0x04
	virtual void Destroy();                          // vtable+0x08

	// SYNTHETIC: GOLDP 0x1001d7e0
	// GdbModelIndexArrayBase::`scalar deleting destructor'

	LegoU32 GetCount() const { return m_count; }

protected:
	undefined4 m_count; // 0x04
};

#endif // GDBMODELINDEXARRAYBASE_H
