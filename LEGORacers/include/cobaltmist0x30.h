#ifndef COBALTMIST0X30_H
#define COBALTMIST0X30_H

#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x4afc6c
// SIZE 0x30
class CobaltMist0x30 {
public:
	virtual ~CobaltMist0x30();                 // vtable+0x00
	virtual undefined4 VTable0x04(undefined4); // vtable+0x04
	virtual void VTable0x08();                 // vtable+0x08
	virtual void VTable0x0c();                 // vtable+0x0c
	virtual void VTable0x10();                 // vtable+0x10
	virtual void VTable0x14();                 // vtable+0x14
	virtual void VTable0x18(undefined4*);      // vtable+0x18
	virtual void VTable0x1c();                 // vtable+0x1c
	virtual void VTable0x20(undefined4*);      // vtable+0x20
	virtual void VTable0x24();                 // vtable+0x24
	virtual void VTable0x28(undefined4);       // vtable+0x28

	// SYNTHETIC: LEGORACERS 0x41bce0
	// CobaltMist0x30::`scalar deleting destructor'

private:
	undefined4 m_unk0x04;      // 0x04
	undefined4 m_unk0x08;      // 0x08
	undefined4 m_unk0x0c;      // 0x0c
	undefined m_unk0x10[0x08]; // 0x10
	undefined4* m_unk0x18;     // 0x18
	undefined m_unk0x1c[0x08]; // 0x1c
	undefined4* m_unk0x24;     // 0x24
	undefined m_unk0x28[0x08]; // 0x28
};

#endif // COBALTMIST0X30_H
