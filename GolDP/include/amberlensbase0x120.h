#ifndef AMBERLENSBASE0X120_H
#define AMBERLENSBASE0X120_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: GOLDP 0x10056cc0
// SIZE 0x120
class AmberLensBase0x120 {
public:
	AmberLensBase0x120();
	virtual void VTable0x00() = 0; // vtable+0x00
	virtual void VTable0x04() = 0; // vtable+0x04

#if defined(AMBERLENSBASE0X120_DECLARE_DTOR_ONLY) || defined(COMPAT_MODE)
	virtual ~AmberLensBase0x120(); // vtable+0x08
#else
	virtual ~AmberLensBase0x120() {} // vtable+0x08
#endif

	virtual void VTable0x0c() = 0;                                                             // vtable+0x0c
	virtual void VTable0x10() = 0;                                                             // vtable+0x10
	virtual void VTable0x14() = 0;                                                             // vtable+0x14
	virtual void VTable0x18() = 0;                                                             // vtable+0x18
	virtual void VTable0x1c() = 0;                                                             // vtable+0x1c
	virtual void VTable0x20(undefined4 p_unk0x04, undefined4 p_unk0x08);                       // vtable+0x20
	virtual void VTable0x24(undefined4 p_unk0x04, undefined4 p_unk0x08, undefined4 p_unk0x0c); // vtable+0x24
	virtual void VTable0x28() = 0;                                                             // vtable+0x28

	// SYNTHETIC: GOLDP 0x1001bf90
	// AmberLensBase0x120::`scalar deleting destructor'

	void* m_unk0x04;                   // 0x04
	LegoFloat m_unk0x08;               // 0x08
	LegoFloat m_unk0x0c;               // 0x0c
	LegoFloat m_unk0x10;               // 0x10
	LegoFloat m_unk0x14;               // 0x14
	undefined4 m_unk0x18;              // 0x18
	undefined4 m_unk0x1c;              // 0x1c
	LegoFloat m_unk0x20;               // 0x20
	LegoFloat m_unk0x24;               // 0x24
	undefined4 m_unk0x28;              // 0x28
	undefined4 m_unk0x2c;              // 0x2c
	LegoU32 m_flags;                   // 0x30
	undefined m_unk0x34[0x110 - 0x34]; // 0x34
	undefined4 m_unk0x110;             // 0x110
	undefined4 m_unk0x114;             // 0x114
	undefined4 m_unk0x118;             // 0x118
	undefined4 m_unk0x11c;             // 0x11c
};

#endif // AMBERLENSBASE0X120_H
