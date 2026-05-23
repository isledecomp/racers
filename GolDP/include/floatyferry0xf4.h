#ifndef FLOATYFERRY0XF4_H
#define FLOATYFERRY0XF4_H

#include "compat.h"
#include "decomp.h"
#include "floatycanoe0x90.h"

class CmbModelPart0x34;
class IGdbModel0x40;
class WhiteFalconNode0x18;

// VTABLE: GOLDP 0x10056fc8
// SIZE 0xf4
class FloatyFerry0xf4 : public FloatyCanoe0x90 {
public:
	FloatyFerry0xf4();

	void VTable0x10(LegoS32 p_v) override;
	void VTable0x14(const GolVec3& p_vector, ResultStruct* p_result) override;
	void VTable0x4c(LegoU32 p_index) override;
	void VTable0x54() override;
	WhiteFalconNode0x18* VTable0x58(LegoU32 p_arg1) override;
	void VTable0x5c(undefined4) override;

	void FUN_10023490(IGdbModel0x40* p_arg1, WhiteFalconNode0x18* p_arg2, CmbModelPart0x34* p_arg3, LegoFloat p_arg4);
	void FUN_100234c0(WhiteFalconNode0x18* p_arg1, CmbModelPart0x34* p_arg2, LegoFloat p_arg3);
	void FUN_10023940(IGdbModel0x40*, WhiteFalconNode0x18*, CmbModelPart0x34*, LegoFloat);
	void FUN_100239e0(WhiteFalconNode0x18*, CmbModelPart0x34*, LegoFloat);
	void FUN_10023a70(LegoU32 p_partIndex);

	CmbModelPart0x34* GetModelPart(LegoU32 p_index = 0) const { return m_unk0xa8[p_index]; }
	void SetPartAnimationEnabled(LegoBool32 p_enabled)
	{
		if (p_enabled) {
			m_flags |= c_flagBit16;
		}
		else {
			m_flags &= ~c_flagBit16;
		}
	}

protected:
	enum {
		c_flagBit16 = 0x1 << 16,
		c_flagBit18 = 0x1 << 18,
		c_flagsPartAnimationMask = 0x005a0000,
	};

	WhiteFalconNode0x18* m_unk0x90[3];
	LegoS32 m_unk0x9c[3];
	CmbModelPart0x34* m_unk0xa8[3];
	undefined4 m_unk0xb4;
	LegoFloat m_unk0xb8;
	LegoU16 m_unk0xbc;
	undefined m_unk0xbe[0xc0 - 0xbe];
	GolVec3 m_unk0xc0;
	undefined m_unk0xcc[0xd0 - 0xcc];
	undefined4 m_unk0xd0;
	undefined4 m_unk0xd4;
	undefined2 m_unk0xd8;
	undefined m_unk0xda[0xec - 0xda];
	undefined4 m_unk0xec;
	undefined4 m_unk0xf0;
};

#endif //  FLOATYFERRY0XF4_H
