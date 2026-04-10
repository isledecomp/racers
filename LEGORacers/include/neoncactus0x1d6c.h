#ifndef NEONCACTUS0X1D6C_H
#define NEONCACTUS0X1D6C_H

#include "amberwolf0x98.h"
#include "cobaltmist0x30.h"
#include "decomp.h"
#include "ironflame0x944.h"
#include "types.h"

// VTABLE: LEGORACERS 0x4b0568
// SIZE 0x1d6c
class NeonCactus0x1d6c {
public:
	virtual void VTable0x00();                       // vtable+0x00
	virtual void VTable0x04();                       // vtable+0x04
	virtual void VTable0x08();                       // vtable+0x08
	virtual void VTable0x0c();                       // vtable+0x0c
	virtual void VTable0x10();                       // vtable+0x10
	virtual void VTable0x14();                       // vtable+0x14
	virtual void VTable0x18();                       // vtable+0x18
	virtual void VTable0x1c(undefined4);             // vtable+0x1c
	virtual void VTable0x20(undefined4);             // vtable+0x20
	virtual void VTable0x24(undefined4, undefined4); // vtable+0x24
	virtual void VTable0x28();                       // vtable+0x28
	virtual void VTable0x2c();                       // vtable+0x2c
	virtual ~NeonCactus0x1d6c();                     // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x42bb20
	// NeonCactus0x1d6c::`scalar deleting destructor'

	LegoS32 FUN_0042bbb0(LegoS32 p_argc, LegoChar** p_argv);
	void FUN_0042bc20();
	void FUN_0042bc40();
	void FUN_0042bd00();
	void FUN_0042be90();

private:
	IronFlame0x944 m_unk0x04;             // 0x04
	AmberWolf0x98 m_unk0x948;             // 0x948
	CobaltMist0x30 m_unk0x9e0;            // 0x9e0
	undefined m_unk0xa10[0x1d6c - 0xa10]; // 0xa10
};

#endif // NEONCACTUS0X1D6C_H
