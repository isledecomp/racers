#ifndef FLOATYPONTOON0x4C_H
#define FLOATYPONTOON0x4C_H

#include "compat.h"
#include "floatyboat0x28.h"

// VTABLE: GOLDP 0x10057500
// SIZE 0x4c
class FloatyPontoon0x4c : public FloatyBoat0x28 {
public:
	FloatyPontoon0x4c();

	// FUNCTION: GOLDP 0x100156c0
	void VTable0x08(const GolVec3& p_v) override { FloatyBoat0x28::VTable0x08(p_v); } // vtable+0x08
	void VTable0x14(GolVec3* p_arg1, undefined4*) override;                           // vtable+0x14
	void VTable0x1c(undefined4*) override;                                            // vtable+0x1c
	undefined4 VTable0x20() override;                                                 // vtable+0x20
	virtual undefined4 VTable0x4c(
		LegoFloat p_arg1,
		LegoFloat p_arg2,
		LegoFloat p_arg3,
		LegoFloat p_arg4
	);                         // vtable+0x4c
	virtual void VTable0x50(); // vtable+0x50

	undefined4 FUN_10026fa0(LegoFloat p_arg1);
	void FUN_10029e90(undefined4* p_arg1, LegoS32 p_arg2, undefined4 p_arg3, undefined4 p_arg4, undefined4 p_arg5);
	undefined4 FUN_1002a020();

private:
	LegoFloat m_unk0x28;  // 0x28
	LegoFloat m_unk0x2c;  // 0x2c
	LegoFloat m_unk0x30;  // 0x30
	LegoFloat m_unk0x34;  // 0x34
	LegoFloat m_unk0x38;  // 0x38
	LegoFloat m_unk0x3c;  // 0x3c
	LegoFloat m_unk0x40;  // 0x40
	LegoFloat m_unk0x44;  // 0x44
	undefined2 m_unk0x48; // 0x48
	undefined2 m_unk0x4a; // 0x4a
};

#endif // FLOATYPONTOON0x4C_H
