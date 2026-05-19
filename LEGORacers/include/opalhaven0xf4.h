#ifndef OPALHAVEN0XF4_H
#define OPALHAVEN0XF4_H

#include "compat.h"
#include "decomp.h"
#include "silverhollow0xb8.h"
#include "types.h"

class CmbModelPart0x34;
class IGdbModel0x40;
class WhiteFalconNode0x18;

// VTABLE: LEGORACERS 0x004af5ec
// SIZE 0xf4
class OpalHaven0xf4 : public SilverHollow0xb8 {
public:
	OpalHaven0xf4();

	void VTable0x10(undefined4 p_unk0x04) override;   // vtable+0x10
	void VTable0x14(undefined4, undefined4) override; // vtable+0x14
	void VTable0x4c(undefined4 p_unk0x04) override;   // vtable+0x4c
	void VTable0x54() override;                       // vtable+0x54
	void FUN_0040d550(
		IGdbModel0x40* p_model,
		WhiteFalconNode0x18* p_node,
		CmbModelPart0x34* p_modelParts,
		LegoFloat p_unk0x10
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
	LegoU32 GetUnk0x5c() const { return m_unk0x5c; }
	void SetUnk0x5c(LegoU32 p_unk0x5c) { m_unk0x5c = p_unk0x5c; }
	LegoU16 GetActiveState() const { return (m_unk0x5c & 0x20000) ? m_unk0xd8 : m_unk0xbc; }
	LegoFloat GetActiveValue() const { return (m_unk0x5c & 0x20000) ? m_unk0xd0 : m_unk0xb4; }

private:
	void Reset();

	undefined4 m_unk0xb8;             // 0xb8
	undefined2 m_unk0xbc;             // 0xbc
	undefined m_unk0xbe[0xd0 - 0xbe]; // 0xbe
	LegoFloat m_unk0xd0;              // 0xd0
	undefined4 m_unk0xd4;             // 0xd4
	undefined2 m_unk0xd8;             // 0xd8
	undefined m_unk0xda[0xec - 0xda]; // 0xda
	undefined4 m_unk0xec;             // 0xec
	undefined4 m_unk0xf0;             // 0xf0
};

#endif // OPALHAVEN0XF4_H
