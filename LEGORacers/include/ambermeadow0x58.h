#ifndef AMBERMEADOW0X58_H
#define AMBERMEADOW0X58_H

#include "compat.h"
#include "decomp.h"
#include "floatyboat0x28.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af700
// SIZE 0x58
class AmberMeadow0x58 : public FloatyBoat0x28 {
public:
	AmberMeadow0x58();

	void VTable0x04(GolVec3* p_center) const override;                         // vtable+0x04
	void VTable0x08(const GolVec3& p_center) override;                         // vtable+0x08
	void VTable0x2c(const GolVec3& p_add, GolVec3* p_dest) const override;     // vtable+0x2c
	void VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const override;     // vtable+0x30
	void VTable0x34(const GolVec3& p_src, GolVec3* p_dest) override;           // vtable+0x34
	void VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const override;     // vtable+0x38
	void VTable0x3c(const GolMatrix34& p_matrix) override;                     // vtable+0x3c
	void VTable0x40(const GolVec3& p_direction, const GolVec3& p_up) override; // vtable+0x40
	void VTable0x44(GolMatrix3* p_dest) const override;                        // vtable+0x44
	void VTable0x48(GolVec3* p_right, GolVec3* p_forward) const override;      // vtable+0x48

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
