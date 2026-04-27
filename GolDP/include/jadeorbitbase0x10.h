#ifndef JADEORBITBASE0X10_H
#define JADEORBITBASE0X10_H

#include "decomp.h"
#include "floatyboat0x28.h"
#include "types.h"

// VTABLE: GOLDP 0x10056cf0
// SIZE 0x10
class JadeOrbitBase0x10 {
public:
	JadeOrbitBase0x10();
	virtual void VTable0x00() = 0;                                                 // vtable+0x00
	virtual void VTable0x04() = 0;                                                 // vtable+0x04
	virtual void VTable0x08(undefined4, undefined4) = 0;                           // vtable+0x08
	virtual void VTable0x0c() = 0;                                                 // vtable+0x0c
	virtual void VTable0x10() = 0;                                                 // vtable+0x10
	virtual void VTable0x14() = 0;                                                 // vtable+0x14
	virtual void VTable0x18() = 0;                                                 // vtable+0x18
	virtual void VTable0x1c() = 0;                                                 // vtable+0x1c
	virtual void VTable0x20() = 0;                                                 // vtable+0x20
	virtual void VTable0x24(FloatyVec0xc* p_unk0x04, FloatyVec0xc* p_unk0x08) = 0; // vtable+0x24
	virtual void VTable0x28() = 0;                                                 // vtable+0x28
	virtual void VTable0x2c() = 0;                                                 // vtable+0x2c
	virtual void VTable0x30() = 0;                                                 // vtable+0x30
	virtual void VTable0x34() = 0;                                                 // vtable+0x34
	virtual void VTable0x38() = 0;                                                 // vtable+0x38
	virtual void VTable0x3c() = 0;                                                 // vtable+0x3c
	virtual void VTable0x40() = 0;                                                 // vtable+0x40
	virtual void VTable0x44(FloatyVec0xc* p_unk0x04) = 0;                          // vtable+0x44
	virtual void VTable0x48() = 0;                                                 // vtable+0x48

	undefined4 m_unk0x04; // 0x04
	undefined4 m_unk0x08; // 0x08
	undefined4 m_unk0x0c; // 0x0c
};

#endif // JADEORBITBASE0X10_H
