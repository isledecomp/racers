#ifndef AMBERMEADOW0X58_H
#define AMBERMEADOW0X58_H

#include "compat.h"
#include "decomp.h"
#include "lilacorbit0x28.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af700
// SIZE 0x58
class AmberMeadow0x58 : public LilacOrbit0x28 {
public:
	AmberMeadow0x58();

	void VTable0x04(LegoFloat* p_unk0x04) override;   // vtable+0x04
	void VTable0x08(LegoFloat* p_unk0x04) override;   // vtable+0x08
	void VTable0x2c(LegoFloat*, LegoFloat*) override; // vtable+0x2c
	void VTable0x30(LegoFloat*, LegoFloat*) override; // vtable+0x30
	void VTable0x34(LegoFloat*, LegoFloat*) override; // vtable+0x34
	void VTable0x38(LegoFloat*, LegoFloat*) override; // vtable+0x38
	void VTable0x3c(LegoFloat* p_unk0x04) override;   // vtable+0x3c
	void VTable0x40(LegoFloat*, LegoFloat*) override; // vtable+0x40
	void VTable0x44(LegoFloat* p_unk0x04) override;   // vtable+0x44
	void VTable0x48(LegoFloat*, LegoFloat*) override; // vtable+0x48

protected:
	void FUN_004108c0();

	LegoFloat m_unk0x28;  // 0x28
	undefined4 m_unk0x2c; // 0x2c
	undefined4 m_unk0x30; // 0x30
	undefined4 m_unk0x34; // 0x34
	LegoFloat m_unk0x38;  // 0x38
	undefined4 m_unk0x3c; // 0x3c
	undefined4 m_unk0x40; // 0x40
	undefined4 m_unk0x44; // 0x44
	LegoFloat m_unk0x48;  // 0x48
	undefined4 m_unk0x4c; // 0x4c
	undefined4 m_unk0x50; // 0x50
	undefined4 m_unk0x54; // 0x54
};

#endif // AMBERMEADOW0X58_H
