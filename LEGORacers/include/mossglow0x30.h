#ifndef MOSSGLOW0X30_H
#define MOSSGLOW0X30_H

#include "decomp.h"

// VTABLE: LEGORACERS 0x4b0f38
// SIZE 0x30
class MossGlow0x30 {
public:
	MossGlow0x30();
	~MossGlow0x30();

	virtual void VTable0x00() = 0; // vtable+0x00
	virtual void VTable0x04() = 0; // vtable+0x04
	virtual void VTable0x08() = 0; // vtable+0x08
	virtual void VTable0x0c() = 0; // vtable+0x0c
	virtual void VTable0x10();     // vtable+0x10
	virtual void VTable0x14();     // vtable+0x14

	void FUN_0044c990();

protected:
	undefined m_unk0x04[0x24 - 0x04]; // 0x04
	undefined4* m_unk0x24;            // 0x24
	undefined m_unk0x28[0x2c - 0x28]; // 0x28
	undefined4 m_unk0x2c;             // 0x2c
};

#endif // MOSSGLOW0X30_H
