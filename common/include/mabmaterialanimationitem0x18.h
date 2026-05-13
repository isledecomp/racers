#ifndef MABMATERIALANIMATIONITEM0X18_H
#define MABMATERIALANIMATIONITEM0X18_H

#include "decomp.h"
#include "types.h"

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
	void FUN_10025da0(undefined4 p_arg1, undefined2 p_arg2, undefined4 p_arg3);
	void FUN_004103c0(const MabMaterialAnimationItem0x18& p_other);
	void Reset();
	void FUN_00410470();
	void FUN_00410480();
	void FUN_00410490();
	void FUN_004104c0(undefined4, undefined4*);
	void FUN_00410560(undefined4, undefined4*);

private:
	undefined4 m_unk0x00; // 0x00
	undefined2 m_unk0x04; // 0x04
	undefined2 m_unk0x06; // 0x06
	undefined2 m_unk0x08; // 0x08
	undefined2 m_unk0x0a; // 0x0a
	LegoFloat m_unk0x0c;  // 0x0c
	LegoFloat m_unk0x10;  // 0x10
	LegoU32 m_flags;      // 0x14
};

#endif // MABMATERIALANIMATIONITEM0X18_H
