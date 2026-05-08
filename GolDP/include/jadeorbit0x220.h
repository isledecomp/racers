#ifndef JADEORBIT0X220_H
#define JADEORBIT0X220_H

#include "compat.h"
#include "jadeorbitbase0x10.h"
#include "types.h"

// VTABLE: GOLDP 0x1005622c
// SIZE 0x220
class JadeOrbit0x220 : public JadeOrbitBase0x10 {
public:
	JadeOrbit0x220();
	void VTable0x00() override;                                                 // vtable+0x00
	void VTable0x04() override;                                                 // vtable+0x04
	void VTable0x08(undefined4, undefined4) override;                           // vtable+0x08
	void VTable0x0c() override;                                                 // vtable+0x0c
	void VTable0x10() override;                                                 // vtable+0x10
	void VTable0x14() override;                                                 // vtable+0x14
	void VTable0x18() override;                                                 // vtable+0x18
	void VTable0x1c() override;                                                 // vtable+0x1c
	void VTable0x20() override;                                                 // vtable+0x20
	void VTable0x24(FloatyVec0xc* p_unk0x04, FloatyVec0xc* p_unk0x08) override; // vtable+0x24
	void VTable0x28() override;                                                 // vtable+0x28
	void VTable0x2c() override;                                                 // vtable+0x2c
	void VTable0x30() override;                                                 // vtable+0x30
	void VTable0x34() override;                                                 // vtable+0x34
	void VTable0x38() override;                                                 // vtable+0x38
	void VTable0x3c() override;                                                 // vtable+0x3c
	void VTable0x40() override;                                                 // vtable+0x40
	void VTable0x44(FloatyVec0xc* p_unk0x04) override;                          // vtable+0x44
	void VTable0x48() override;                                                 // vtable+0x48

	LegoFloat m_unk0x10;               // 0x10
	LegoFloat m_unk0x14;               // 0x14
	LegoFloat m_unk0x18;               // 0x18
	LegoFloat m_unk0x1c;               // 0x1c
	LegoFloat m_unk0x20;               // 0x20
	LegoFloat m_unk0x24;               // 0x24
	LegoFloat m_unk0x28;               // 0x28
	LegoFloat m_unk0x2c;               // 0x2c
	LegoFloat m_unk0x30;               // 0x30
	LegoFloat m_unk0x34;               // 0x34
	LegoFloat m_unk0x38;               // 0x38
	LegoFloat m_unk0x3c;               // 0x3c
	LegoFloat m_unk0x40;               // 0x40
	LegoFloat m_unk0x44;               // 0x44
	LegoFloat m_unk0x48;               // 0x48
	LegoFloat m_unk0x4c;               // 0x4c
	LegoFloat m_unk0x50;               // 0x50
	LegoFloat m_unk0x54;               // 0x54
	LegoFloat m_unk0x58;               // 0x58
	LegoFloat m_unk0x5c;               // 0x5c
	LegoFloat m_unk0x60;               // 0x60
	LegoFloat m_unk0x64;               // 0x64
	LegoFloat m_unk0x68;               // 0x68
	LegoFloat m_unk0x6c;               // 0x6c
	LegoFloat m_unk0x70;               // 0x70
	LegoFloat m_unk0x74;               // 0x74
	LegoFloat m_unk0x78;               // 0x78
	LegoFloat m_unk0x7c;               // 0x7c
	LegoFloat m_unk0x80;               // 0x80
	LegoFloat m_unk0x84;               // 0x84
	LegoFloat m_unk0x88;               // 0x88
	LegoFloat m_unk0x8c;               // 0x8c
	LegoFloat m_unk0x90;               // 0x90
	LegoFloat m_unk0x94;               // 0x94
	LegoFloat m_unk0x98;               // 0x98
	LegoFloat m_unk0x9c;               // 0x9c
	LegoFloat m_unk0xa0;               // 0xa0
	LegoFloat m_unk0xa4;               // 0xa4
	LegoFloat m_unk0xa8;               // 0xa8
	LegoFloat m_unk0xac;               // 0xac
	LegoFloat m_unk0xb0;               // 0xb0
	LegoFloat m_unk0xb4;               // 0xb4
	LegoFloat m_unk0xb8;               // 0xb8
	LegoFloat m_unk0xbc;               // 0xbc
	LegoFloat m_unk0xc0;               // 0xc0
	LegoFloat m_unk0xc4;               // 0xc4
	LegoFloat m_unk0xc8;               // 0xc8
	LegoFloat m_unk0xcc;               // 0xcc
	undefined m_unk0xd0[0x190 - 0xd0]; // 0xd0
	undefined4 m_unk0x190[0x10];       // 0x190
	undefined4 m_unk0x1d0[0x10];       // 0x1d0
	LegoFloat m_unk0x210;              // 0x210
	LegoFloat m_unk0x214;              // 0x214
	LegoFloat m_unk0x218;              // 0x218
	LegoFloat m_unk0x21c;              // 0x21c
};

#endif // JADEORBIT0X220_H
