#ifndef OPALHAVEN0XF4_H
#define OPALHAVEN0XF4_H

#include "compat.h"
#include "decomp.h"
#include "silverhollow0xb8.h"
#include "types.h"

class CmbModelPart0x34;
class IGdbModel0x40;
class WhiteFalconNode0x18;

// Completes the same 0x90..0xf4 tail that GOLDP keeps entirely in
// FloatyFerry0xf4; the base SilverHollow0xb8 owns 0x90..0xb8 here.
// VTABLE: LEGORACERS 0x004af5ec
// SIZE 0xf4
class OpalHaven0xf4 : public SilverHollow0xb8 {
public:
	OpalHaven0xf4();

	void VTable0x10(LegoS32 p_elapsed) override;                                       // vtable+0x10
	void VTable0x14(const WhiteFalconView0xcc& p_view, ViewResult* p_result) override; // vtable+0x14
	void VTable0x4c(LegoU32 p_index) override;                                         // vtable+0x4c
	void VTable0x54() override;                                                        // vtable+0x54
	WhiteFalconNode0x18* VTable0x58(LegoU32 p_arg1) override;                          // vtable+0x58
	void VTable0x5c(LegoU32 p_arg1) override;                                          // vtable+0x5c

	void FUN_0040d550(
		IGdbModel0x40* p_model,
		WhiteFalconNode0x18* p_node,
		CmbModelPart0x34* p_modelParts,
		LegoFloat p_modelDistance
	);
	void FUN_0040dad0(undefined2 p_unk0x04);
	void FUN_0040db80(
		undefined4 p_unk0x04,
		undefined4 p_unk0x08,
		LegoFloat p_unk0x0c,
		undefined4 p_unk0x10,
		undefined4 p_unk0x14,
		undefined4 p_unk0x18
	);
	LegoBool32 FUN_0040e360();
	LegoU32 GetFlags() const { return m_flags; }
	void SetFlags(LegoU32 p_flags) { m_flags = p_flags; }
	LegoU16 GetActiveState() const { return (m_flags & 0x20000) ? m_unk0xd8 : m_unk0xbc; }
	LegoFloat GetActiveValue() const { return (m_flags & 0x20000) ? m_unk0xd0 : m_unk0xb4; }

private:
	void Reset();
	void FUN_0040d650();

	LegoFloat m_unk0xb8;              // 0xb8
	LegoU16 m_unk0xbc;                // 0xbc
	undefined m_unk0xbe[0xd0 - 0xbe]; // 0xbe
	LegoFloat m_unk0xd0;              // 0xd0
	undefined4 m_unk0xd4;             // 0xd4
	LegoU16 m_unk0xd8;                // 0xd8
	undefined m_unk0xda[0xec - 0xda]; // 0xda
	undefined4 m_unk0xec;             // 0xec
	undefined4 m_unk0xf0;             // 0xf0
};

#endif // OPALHAVEN0XF4_H
