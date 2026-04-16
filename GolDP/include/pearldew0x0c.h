#ifndef GOLDP_PEARLDEW0X0C_H
#define GOLDP_PEARLDEW0X0C_H

#include "decomp.h"
#include "types.h"

// VTABLE: GOLDP 0x10056520
// SIZE 0x0c
class PearlDew0x0c {
public:
	PearlDew0x0c();
	~PearlDew0x0c();

	virtual void VTable0x00(undefined4, undefined4, undefined4); // vtable+0x00
	virtual void VTable0x04();                                   // vtable+0x04
	virtual void VTable0x08();                                   // vtable+0x08
	virtual void VTable0x0c();                                   // vtable+0x0c
	virtual void VTable0x10();                                   // vtable+0x10
	virtual void VTable0x14();                                   // vtable+0x14
	virtual void VTable0x18();                                   // vtable+0x18
	virtual void VTable0x1c();                                   // vtable+0x1c

private:
	undefined4 m_unk0x04; // 0x04
	undefined2 m_unk0x08; // 0x08
	undefined2 m_unk0x0a; // 0x0a
};

#endif // GOLDP_PEARLDEW0X0C_H
