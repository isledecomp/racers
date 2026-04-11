#ifndef RUBYHAZE0X08_H
#define RUBYHAZE0X08_H

#include "decomp.h"
#include "util/list.h"

class AmberLeaf0x10;

// VTABLE: LEGORACERS 0x4afa9c
// SIZE 0x08
class RubyHaze0x08 {
public:
	RubyHaze0x08();
	virtual ~RubyHaze0x08();                           // vtable+0x00
	virtual ListLink* VTable0x04(undefined4) = 0;      // vtable+0x04
	virtual ListLink* VTable0x08() = 0;                // vtable+0x08
	virtual undefined4 VTable0x0c() = 0;               // vtable+0x0c
	virtual AmberLeaf0x10* VTable0x10(undefined4) = 0; // vtable+0x10
	virtual void VTable0x14(AmberLeaf0x10*) = 0;       // vtable+0x14
	virtual void* VTable0x18() = 0;                    // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x417bc0
	// RubyHaze0x08::`scalar deleting destructor'

protected:
	undefined4 m_unk0x04; // 0x04
};

#endif // RUBYHAZE0X08_H
