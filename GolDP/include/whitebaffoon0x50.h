#ifndef WHITEBAFFOON0X58_H
#define WHITEBAFFOON0X58_H

#include "decomp.h"
#include "types.h"

// VTABLE: GOLDP 0x10056ee4
// SIZE 0x50
class WhiteBaffoon0x50 {
public:
	WhiteBaffoon0x50();

	virtual void VTable0x00() = 0; // vtable+0x00
	virtual void VTable0x04() = 0; // vtable+0x04
	virtual void VTable0x08() = 0; // vtable+0x08
	virtual void VTable0x0c(undefined4, undefined4, undefined4*) = 0; // vtable+0x0c
	virtual void VTable0x10(); // vtable+0x10
	// FUNCTION: GOLDP 0x1001f2a0
	virtual ~WhiteBaffoon0x50() // vtable+0x14
	{
		Reset();
	}
	// FUNCTION: GOLDP 0x1001f2f0
	virtual void Reset()  // vtable+0x18
	{

		m_unk0x24 = NULL;
		m_unk0x2c = 0;
		m_unk0x30 = 0;
		m_unk0x34 = 0;
		m_unk0x38 = 0;
		m_unk0x3c = 0x22;
		m_unk0x40 = 0;
		m_unk0x28 = 0;
		m_unk0x29 = 0;
		m_unk0x2a = 0;
		m_unk0x2b = 0xff;
		m_unk0x4a = 0xff;
		m_unk0x4b = 0xff;
		m_unk0x4c = 0xff;
		m_unk0x4d = 0xff;
		m_unk0x04 = 0;
		m_unk0x08 = 0;
	}
	virtual undefined4 VTable0x1c(undefined4, undefined4) = 0; // vtable+0x1c

	void FUN_1001f430();
	void FUN_1001f790();
	void FUN_1001fde0();

	LegoU32 GetUnk0x3c() const { return m_unk0x3c; }

	// SYNTHETIC: GOLDP 0x1001f240
	// WhiteBaffoon0x50::`scalar deleting destructor'
protected:
	undefined4 m_unk0x04;
	undefined4 m_unk0x08;
	undefined4 m_unk0x0c;
	undefined4 m_unk0x10;
	undefined4 m_unk0x14;
	undefined4 m_unk0x18;
	undefined4 m_unk0x1c;
	undefined2 m_unk0x20;
	undefined2 m_unk0x22;
	undefined4* m_unk0x24;
	undefined m_unk0x28;
	undefined m_unk0x29;
	undefined m_unk0x2a;
	undefined m_unk0x2b;
	LegoU32 m_unk0x2c;
	undefined4 m_unk0x30;
	undefined4 m_unk0x34;
	undefined4 m_unk0x38;
	LegoU32 m_unk0x3c;
	undefined2 m_unk0x40;
	undefined m_unk0x42[0x4a - 0x42];
	undefined m_unk0x4a;
	undefined m_unk0x4b;
	undefined m_unk0x4c;
	undefined m_unk0x4d;
	undefined m_unk0x4f[0x50-0x4f];
};

#endif // WHITEBAFFOON0X58_H

