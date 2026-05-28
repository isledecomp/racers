#ifndef IGDBMODELINDEXARRAY0X8_H
#define IGDBMODELINDEXARRAY0X8_H

#include "decomp.h"
#include "types.h"

class GolFileParser;

// VTABLE: GOLDP 0x10056dfc
// SIZE 0x8
class IGdbModelIndexArray0x8 {
public:
	IGdbModelIndexArray0x8();

	virtual ~IGdbModelIndexArray0x8();                    // vtable+0x00
	virtual void VTable0x04(GolFileParser& p_parser) = 0; // vtable+0x04
	virtual void VTable0x08();                            // vtable+0x08

	// SYNTHETIC: GOLDP 0x1001d7e0
	// IGdbModelIndexArray0x8::`scalar deleting destructor'

	LegoU32 GetCount() const { return m_unk0x04; }

protected:
	undefined4 m_unk0x04; // 0x04
};

#endif // IGDBMODELINDEXARRAY0X8_H
