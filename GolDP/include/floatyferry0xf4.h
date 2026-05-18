#ifndef FLOATYFERRY0XF4_H
#define FLOATYFERRY0XF4_H

#include "compat.h"
#include "decomp.h"
#include "floatycanoe0x90.h"

// VTABLE: GOLDP 0x10056fc8
// SIZE 0xf4
class FloatyFerry0xf4 : public FloatyCanoe0x90 {
public:
	FloatyFerry0xf4();

	void VTable0x10(LegoS32 p_v) override;
	void VTable0x14(const GolVec3& p_vector, ResultStruct* p_result) override;
	void VTable0x4c(LegoU32 p_index) override;
	void VTable0x54() override;
	undefined4 VTable0x58(LegoU32 p_arg1) override;
	void VTable0x5c(undefined4) override;

	void FUN_10023490(undefined4* p_arg1, undefined4 p_arg2, undefined4* p_arg3, LegoFloat p_arg4);
	void FUN_100234c0(undefined4 p_arg1, undefined4* p_arg2, LegoFloat p_arg3);
	void FUN_10023940(undefined4*, undefined4, undefined4, LegoFloat);
	void FUN_100239e0(undefined4, undefined4*, LegoFloat);
	void FUN_10023a70(undefined2);

protected:
	undefined4 m_unk0x90[3];
	undefined4 m_unk0x9c[3];
	undefined4* m_unk0xa8[3];
	undefined4 m_unk0xb4;
	undefined4 m_unk0xb8;
	undefined2 m_unk0xbc;
	undefined m_unk0xbe[0xd0 - 0xbe];
	undefined4 m_unk0xd0;
	undefined4 m_unk0xd4;
	undefined2 m_unk0xd8;
	undefined m_unk0xda[0xec - 0xda];
	undefined4 m_unk0xec;
	undefined4 m_unk0xf0;
};

#endif //  FLOATYFERRY0XF4_H
