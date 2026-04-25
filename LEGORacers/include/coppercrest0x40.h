#ifndef COPPERCREST0X40_H
#define COPPERCREST0X40_H

#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b2164
// SIZE 0x40
class CopperCrest0x40 {
public:
	CopperCrest0x40();
	virtual LegoS32 VTable0x00();           // vtable+0x00
	virtual LegoS32 VTable0x04(undefined4); // vtable+0x04
	virtual ~CopperCrest0x40();             // vtable+0x08
	virtual LegoS32 VTable0x0c();           // vtable+0x0c
	virtual LegoS32 VTable0x10(undefined4); // vtable+0x10
	virtual void VTable0x14();              // vtable+0x14
	virtual void VTable0x18();              // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x00468f10
	// CopperCrest0x40::`scalar deleting destructor'

private:
	undefined m_unk0x04[0x40 - 0x04]; // 0x04
};

#endif // COPPERCREST0X40_H
