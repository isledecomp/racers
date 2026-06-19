#ifndef MABMATERIALANIMATIONITEM0X18_H
#define MABMATERIALANIMATIONITEM0X18_H

#include "decomp.h"
#include "material/materialtable0x0c.h"
#include "types.h"

class MabMaterialAnimationItem0x8;
class DuskwindBananaRelic0x24;

// SIZE 0x18
class MabMaterialAnimationItem0x18 {
public:
	enum {
		c_flagBit0 = 0x1 << 0,
		c_flagBit1 = 0x1 << 1,
		c_flagBit2 = 0x1 << 2,
	};

	MabMaterialAnimationItem0x18();

	void FUN_10025d40(undefined2, undefined2, undefined2, LegoS32);
	void FUN_10025da0(MaterialTable0x0c* p_arg1, LegoU32 p_arg2, LegoBool32 p_arg3);
	void FUN_004103c0(const MabMaterialAnimationItem0x18& p_other);
	void Reset();
	void FUN_00410470();
	void FUN_00410480();
	void FUN_00410490();
	void FUN_004104c0(LegoS32 p_elapsedMs, MabMaterialAnimationItem0x8* p_items, LegoU32 p_itemCount);
	DuskwindBananaRelic0x24* FUN_00410560(
		LegoS32 p_elapsedMs,
		MabMaterialAnimationItem0x8* p_items,
		LegoU32 p_itemCount
	);
	MaterialTable0x0c* GetUnk0x00() const { return m_unk0x00; }
	LegoU16 GetUnk0x04() const { return m_unk0x04; }
	void SetUnk0x0c(LegoFloat p_unk0x0c) { m_unk0x0c = p_unk0x0c; }
	LegoBool32 IsConfigured() const { return m_flags & c_flagBit0; }
	LegoBool32 IsAssigned() const { return m_flags & c_flagBit1; }

private:
	MaterialTable0x0c* m_unk0x00; // 0x00
	LegoU16 m_unk0x04;            // 0x04
	LegoU16 m_unk0x06;            // 0x06
	LegoU16 m_unk0x08;            // 0x08
	LegoU16 m_unk0x0a;            // 0x0a
	LegoFloat m_unk0x0c;          // 0x0c
	LegoFloat m_unk0x10;          // 0x10
	LegoU32 m_flags;              // 0x14
};

#endif // MABMATERIALANIMATIONITEM0X18_H
