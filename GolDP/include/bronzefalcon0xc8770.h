#ifndef BRONZEFALCON0XC8770_H
#define BRONZEFALCON0XC8770_H

#include "decomp.h"
#include "types.h"

class SmallCocoon0xc;

// VTABLE: GOLDP 0x100565b8
// SIZE 0xc8770
class BronzeFalcon0xc8770 {
public:
	BronzeFalcon0xc8770();

	virtual void VTable0x00();                                              // vtable+0x00
	virtual void VTable0x04();                                              // vtable+0x04
	virtual ~BronzeFalcon0xc8770();                                         // vtable+0x08
	virtual void VTable0x0c(undefined4, undefined4, undefined4);            // vtable+0x0c
	virtual void VTable0x10();                                              // vtable+0x10
	virtual void VTable0x14();                                              // vtable+0x14
	virtual void VTable0x18();                                              // vtable+0x18
	virtual void VTable0x1c(undefined4);                                    // vtable+0x1c
	virtual void VTable0x20(undefined4);                                    // vtable+0x20
	virtual void VTable0x24();                                              // vtable+0x24
	virtual void VTable0x28();                                              // vtable+0x28
	virtual void VTable0x2c(undefined4);                                    // vtable+0x2c
	virtual void VTable0x30(undefined4);                                    // vtable+0x30
	virtual void VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08); // vtable+0x34
	virtual void VTable0x38();                                              // vtable+0x38
	virtual void VTable0x3c() = 0;                                          // vtable+0x3c
	virtual void VTable0x40() = 0;                                          // vtable+0x40
	virtual void VTable0x44() = 0;                                          // vtable+0x44
	virtual void VTable0x48() = 0;                                          // vtable+0x48
	virtual void VTable0x4c() = 0;                                          // vtable+0x4c
	virtual void VTable0x50() = 0;                                          // vtable+0x50
	virtual void VTable0x54() = 0;                                          // vtable+0x54
	virtual void VTable0x58() = 0;                                          // vtable+0x58
	virtual void VTable0x5c() = 0;                                          // vtable+0x5c
	virtual void VTable0x60() = 0;                                          // vtable+0x60
	virtual void VTable0x64() = 0;                                          // vtable+0x64
	virtual void VTable0x68() = 0;                                          // vtable+0x68
	virtual void VTable0x6c() = 0;                                          // vtable+0x6c
	virtual void VTable0x70() = 0;                                          // vtable+0x70
	virtual void VTable0x74() = 0;                                          // vtable+0x74
	virtual void VTable0x78() = 0;                                          // vtable+0x78
	virtual void VTable0x7c() = 0;                                          // vtable+0x7c
	virtual void VTable0x80() = 0;                                          // vtable+0x80
	virtual void VTable0x84() = 0;                                          // vtable+0x84
	virtual void VTable0x88() = 0;                                          // vtable+0x88
	virtual void VTable0x8c() = 0;                                          // vtable+0x8c
	virtual void VTable0x90() = 0;                                          // vtable+0x90
	virtual void VTable0x94() = 0;                                          // vtable+0x94
	virtual void VTable0x98() = 0;                                          // vtable+0x98
	virtual void VTable0x9c() = 0;                                          // vtable+0x9c
	virtual void VTable0xa0() = 0;                                          // vtable+0xa0
	virtual void VTable0xa4() = 0;                                          // vtable+0xa4
	virtual void VTable0xa8() = 0;                                          // vtable+0xa8
	virtual void VTable0xac() = 0;                                          // vtable+0xac
	virtual void VTable0xb0() = 0;                                          // vtable+0xb0
	virtual void VTable0xb4() = 0;                                          // vtable+0xb4
	virtual void VTable0xb8() = 0;                                          // vtable+0xb8
	virtual void VTable0xbc() = 0;                                          // vtable+0xbc
	virtual void VTable0xc0() = 0;                                          // vtable+0xc0
	virtual void VTable0xc4() = 0;                                          // vtable+0xc4
	virtual void VTable0xc8() = 0;                                          // vtable+0xc8
	virtual void VTable0xcc() = 0;                                          // vtable+0xcc
	virtual void VTable0xd0() = 0;                                          // vtable+0xd0
	virtual void VTable0xd4() = 0;                                          // vtable+0xd4
	virtual void VTable0xd8() = 0;                                          // vtable+0xd8
	virtual void VTable0xdc() = 0;                                          // vtable+0xdc
	virtual void VTable0xe0() = 0;                                          // vtable+0xe0
	virtual void VTable0xe4() = 0;                                          // vtable+0xe4
	virtual void VTable0xe8() = 0;                                          // vtable+0xe8
	virtual void VTable0xec() = 0;                                          // vtable+0xec
	virtual void VTable0xf0() = 0;                                          // vtable+0xf0
	virtual void VTable0xf4() = 0;                                          // vtable+0xf4
	virtual void VTable0xf8() = 0;                                          // vtable+0xf8
	virtual void VTable0xfc() = 0;                                          // vtable+0xfc
	virtual void VTable0x100() = 0;                                         // vtable+0x100
	virtual void VTable0x104() = 0;                                         // vtable+0x104
	virtual void VTable0x108() = 0;                                         // vtable+0x108
	virtual void VTable0x10c() = 0;                                         // vtable+0x10c
	virtual undefined4 VTable0x110() = 0;                                   // vtable+0x110

	void FUN_10028ad0(SmallCocoon0xc* p_param);
	void FUN_10028ae0(SmallCocoon0xc* p_param);

	// SYNTHETIC: GOLDP 0x10007960
	// BronzeFalcon0xc8770::`scalar deleting destructor'

	undefined4 GetUnk0x04() { return m_unk0x04; }
	undefined4* GetUnk0x0c() { return m_unk0x0c; }

private:
	undefined4 m_unk0x04;
	undefined m_unk0x08[0x0c - 0x08];   // 0x04
	undefined4* m_unk0x0c;               // 0x0c
	undefined m_unk0x10[0xc8770 - 0x10]; // 0x10
};

#endif // BRONZEFALCON0XC8770_H
