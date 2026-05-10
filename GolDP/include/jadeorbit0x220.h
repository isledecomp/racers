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
	void VTable0x00() override;                       // vtable+0x00
	void VTable0x04() override;                       // vtable+0x04
	void VTable0x08(undefined4, undefined4) override; // vtable+0x08
	void VTable0x0c() override;                       // vtable+0x0c
	void VTable0x10() override;                       // vtable+0x10
	void VTable0x14() override;                       // vtable+0x14
	void GetBasis(GolVec3* p_right, GolVec3* p_forward,
				  GolVec3* p_up) override;                            // vtable+0x18
	void VTable0x1c(GolVec3* p_unk0x04, GolVec3* p_unk0x08) override; // vtable+0x1c
	void VTable0x20(GolVec3* p_unk0x04, GolVec3* p_unk0x08) override; // vtable+0x20
	void VTable0x24(GolVec3* p_unk0x04, GolVec3* p_unk0x08) override; // vtable+0x24
	void VTable0x28() override;                                       // vtable+0x28
	void VTable0x2c() override;                                       // vtable+0x2c
	void GetUp(GolVec3* p_up) override;                               // vtable+0x30
	void GetForward(GolVec3* p_forward) override;                     // vtable+0x34
	void GetRight(GolVec3* p_right) override;                         // vtable+0x38
	void VTable0x3c() override;                                       // vtable+0x3c
	void GetPosition(GolVec3* p_position) override;                   // vtable+0x40
	void SetPosition(GolVec3* p_position) override;                   // vtable+0x44
	void VTable0x48() override;                                       // vtable+0x48

	GolVec3 m_up;          // 0x10
	LegoFloat m_unk0x1c;   // 0x1c
	GolVec3 m_forward;     // 0x20
	LegoFloat m_unk0x2c;   // 0x2c
	GolVec3 m_right;       // 0x30
	LegoFloat m_unk0x3c;   // 0x3c
	GolVec3 m_position;    // 0x40
	LegoFloat m_unk0x4c;   // 0x4c
	LegoFloat m_unk0x50;   // 0x50
	LegoFloat m_unk0x54;   // 0x54
	LegoFloat m_unk0x58;   // 0x58
	LegoFloat m_unk0x5c;   // 0x5c
	LegoFloat m_unk0x60;   // 0x60
	LegoFloat m_unk0x64;   // 0x64
	LegoFloat m_unk0x68;   // 0x68
	LegoFloat m_unk0x6c;   // 0x6c
	LegoFloat m_unk0x70;   // 0x70
	LegoFloat m_unk0x74;   // 0x74
	LegoFloat m_unk0x78;   // 0x78
	LegoFloat m_unk0x7c;   // 0x7c
	LegoFloat m_unk0x80;   // 0x80
	LegoFloat m_unk0x84;   // 0x84
	LegoFloat m_unk0x88;   // 0x88
	LegoFloat m_unk0x8c;   // 0x8c
	LegoFloat m_unk0x90;   // 0x90
	LegoFloat m_unk0x94;   // 0x94
	LegoFloat m_unk0x98;   // 0x98
	LegoFloat m_unk0x9c;   // 0x9c
	LegoFloat m_unk0xa0;   // 0xa0
	LegoFloat m_unk0xa4;   // 0xa4
	LegoFloat m_unk0xa8;   // 0xa8
	LegoFloat m_unk0xac;   // 0xac
	LegoFloat m_unk0xb0;   // 0xb0
	LegoFloat m_unk0xb4;   // 0xb4
	LegoFloat m_unk0xb8;   // 0xb8
	LegoFloat m_unk0xbc;   // 0xbc
	LegoFloat m_unk0xc0;   // 0xc0
	LegoFloat m_unk0xc4;   // 0xc4
	LegoFloat m_unk0xc8;   // 0xc8
	LegoFloat m_unk0xcc;   // 0xcc
	GolMatrix4 m_unk0xd0;  // 0xd0
	GolMatrix4 m_unk0x110; // 0x110
	GolMatrix4 m_unk0x150; // 0x150
	GolMatrix4 m_unk0x190; // 0x190
	GolMatrix4 m_unk0x1d0; // 0x1d0
	LegoFloat m_unk0x210;  // 0x210
	LegoFloat m_unk0x214;  // 0x214
	LegoFloat m_unk0x218;  // 0x218
	LegoFloat m_unk0x21c;  // 0x21c
};

#endif // JADEORBIT0X220_H
