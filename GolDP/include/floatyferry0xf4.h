#ifndef FLOATYFERRY0XF4_H
#define FLOATYFERRY0XF4_H

#include "compat.h"
#include "decomp.h"
#include "floatycanoe0x90.h"

class CmbModelPart0x34;
class IGdbModel0x40;
class WhiteFalconNode0x18;

// GOLDP keeps the node/model-part tail at 0x90..0xf4 in this derived class.
// The first tail block, 0x90..0xb8, corresponds to fields owned directly by
// LEGORACERS SilverHollow0xb8.
// VTABLE: GOLDP 0x10056fc8
// SIZE 0xf4
class FloatyFerry0xf4 : public FloatyCanoe0x90 {
public:
	FloatyFerry0xf4();

	void VTable0x10(LegoS32 p_elapsed) override;
	void VTable0x14(const WhiteFalconView0xcc& p_view, ResultStruct* p_result) override;
	void VTable0x4c(LegoU32 p_index) override;
	void VTable0x54() override;
	WhiteFalconNode0x18* VTable0x58(LegoU32 p_arg1) override;
	void VTable0x5c(LegoU32 p_arg1) override;

	void FUN_10023490(
		IGdbModel0x40* p_model,
		WhiteFalconNode0x18* p_node,
		CmbModelPart0x34* p_modelParts,
		LegoFloat p_modelDistance
	);
	void FUN_100234c0(WhiteFalconNode0x18* p_node, CmbModelPart0x34* p_modelParts, LegoFloat p_modelDistance);
	void FUN_10023940(IGdbModel0x40*, WhiteFalconNode0x18*, CmbModelPart0x34*, LegoFloat);
	void FUN_100239e0(WhiteFalconNode0x18* p_node, CmbModelPart0x34* p_modelParts, LegoFloat p_modelDistance);
	void FUN_10023a70(LegoU32 p_partIndex);

	CmbModelPart0x34* GetModelPart(LegoU32 p_index = 0) const { return m_modelParts[p_index]; }
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
		c_flagBit16 = 1 << 16,
		c_flagBit17 = 1 << 17,
		c_flagBit18 = 1 << 18,
		c_flagsPartAnimationMask = 0x005a0000,
	};

	WhiteFalconNode0x18* m_nodes[3];   // 0x90
	LegoS32 m_partIndices[3];          // 0x9c
	CmbModelPart0x34* m_modelParts[3]; // 0xa8
	LegoFloat m_unk0xb4;               // 0xb4
	LegoFloat m_unk0xb8;               // 0xb8
	LegoU16 m_unk0xbc;                 // 0xbc
	undefined m_unk0xbe[0xc0 - 0xbe];  // 0xbe
	GolVec3 m_unk0xc0;                 // 0xc0
	undefined m_unk0xcc[0xd0 - 0xcc];  // 0xcc
	LegoFloat m_unk0xd0;               // 0xd0
	undefined4 m_unk0xd4;              // 0xd4
	LegoU16 m_unk0xd8;                 // 0xd8
	undefined m_unk0xda[0xec - 0xda];  // 0xda
	undefined4 m_unk0xec;              // 0xec
	undefined4 m_unk0xf0;              // 0xf0
};

#endif // FLOATYFERRY0XF4_H
