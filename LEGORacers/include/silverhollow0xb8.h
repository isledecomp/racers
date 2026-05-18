#ifndef SILVERHOLLOW0XB8_H
#define SILVERHOLLOW0XB8_H

#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af754
// SIZE 0xb8
class SilverHollow0xb8 {
public:
	SilverHollow0xb8();
	virtual void VTable0x00();                       // vtable+0x00
	virtual void VTable0x04(LegoFloat* p_unk0x04);   // vtable+0x04
	virtual void VTable0x08(LegoFloat* p_unk0x04);   // vtable+0x08
	virtual void VTable0x0c(undefined4 p_unk0x04);   // vtable+0x0c
	virtual void VTable0x10(undefined4 p_unk0x04);   // vtable+0x10
	virtual void VTable0x14(undefined4, undefined4); // vtable+0x14
	virtual void VTable0x18(undefined4 p_unk0x04);   // vtable+0x18
	virtual void VTable0x1c(undefined4 p_unk0x04);   // vtable+0x1c
	virtual void VTable0x20();                       // vtable+0x20
	virtual void VTable0x24(undefined4 p_unk0x04);   // vtable+0x24
	virtual void VTable0x28();                       // vtable+0x28
	virtual void VTable0x2c(LegoFloat*, LegoFloat*); // vtable+0x2c
	virtual void VTable0x30(LegoFloat*, LegoFloat*); // vtable+0x30
	virtual void VTable0x34(LegoFloat*, LegoFloat*); // vtable+0x34
	virtual void VTable0x38(LegoFloat*, LegoFloat*); // vtable+0x38
	virtual void VTable0x3c(LegoFloat* p_unk0x04);   // vtable+0x3c
	virtual void VTable0x40(LegoFloat*, LegoFloat*); // vtable+0x40
	virtual void VTable0x44(LegoFloat* p_unk0x04);   // vtable+0x44
	virtual void VTable0x48(LegoFloat*, LegoFloat*); // vtable+0x48
	virtual void VTable0x4c(undefined4 p_unk0x04);   // vtable+0x4c

protected:
	undefined m_unk0x04[0x10 - 0x04]; // 0x04
	LegoFloat m_unk0x10;              // 0x10
	undefined m_unk0x14[0x5c - 0x14]; // 0x14
	LegoU32 m_unk0x5c;                // 0x5c
	undefined m_unk0x60[0x90 - 0x60]; // 0x60
	undefined4 m_unk0x90[3];          // 0x90
	undefined4 m_unk0x9c[3];          // 0x9c
	undefined4 m_unk0xa8[3];          // 0xa8
	LegoFloat m_unk0xb4;              // 0xb4
};

#endif // SILVERHOLLOW0XB8_H
