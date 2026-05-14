#include "mabmaterialanimationitem0x18.h"

DECOMP_SIZE_ASSERT(MabMaterialAnimationItem0x18, 0x18)

// FUNCTION: GOLDP 0x10025d20
// FUNCTION: LEGORACERS 0x00410350
MabMaterialAnimationItem0x18::MabMaterialAnimationItem0x18()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x06 = 0;
	m_unk0x08 = 0;
	m_unk0x0a = 0;
	m_unk0x0c = 0.0f;
	m_unk0x10 = 0.0f;
	m_flags = 0;
}

// FUNCTION: GOLDP 0x10025d40
// FUNCTION: LEGORACERS 0x00410370
void MabMaterialAnimationItem0x18::FUN_10025d40(undefined2 p_arg1, undefined2 p_arg2, undefined2 p_arg3, LegoS32 p_arg4)
{
	if (m_flags & c_flagBit0) {
		Reset();
	}

	LegoFloat f = static_cast<LegoFloat>(p_arg4);
	m_unk0x06 = p_arg1;
	m_unk0x08 = p_arg2;
	m_unk0x0a = p_arg3;
	m_unk0x10 = 0.0f;
	m_unk0x0c = f / 1000.0f;
	m_flags = c_flagBit0;
}

// FUNCTION: LEGORACERS 0x004103c0
void MabMaterialAnimationItem0x18::FUN_004103c0(const MabMaterialAnimationItem0x18& p_other)
{
	if (m_flags & c_flagBit0) {
		Reset();
	}

	m_unk0x06 = p_other.m_unk0x06;
	m_unk0x08 = p_other.m_unk0x08;
	m_unk0x0a = p_other.m_unk0x0a;
	m_unk0x0c = p_other.m_unk0x0c;
	m_unk0x10 = 0.0f;
	m_flags = c_flagBit0;
}

// FUNCTION: LEGORACERS 0x00410410
void MabMaterialAnimationItem0x18::Reset()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x06 = 0;
	m_unk0x08 = 0;
	m_unk0x0a = 0;
	m_unk0x0c = 0.0f;
	m_unk0x10 = 0.0f;
	m_flags = 0;
}

// FUNCTION: GOLDP 0x10025da0
// FUNCTION: LEGORACERS 0x00410430
void MabMaterialAnimationItem0x18::FUN_10025da0(undefined4 p_arg1, undefined2 p_arg2, undefined4 p_arg3)
{
	m_unk0x00 = p_arg1;
	m_unk0x04 = p_arg2;
	if (p_arg3) {
		m_flags |= c_flagBit2;
	}
	else {
		m_flags &= ~c_flagBit2;
	}
	m_flags |= c_flagBit1;
}

// FUNCTION: LEGORACERS 0x00410470
void MabMaterialAnimationItem0x18::FUN_00410470()
{
	m_flags &= ~(c_flagBit1 | c_flagBit2);
}

// FUNCTION: LEGORACERS 0x00410480
void MabMaterialAnimationItem0x18::FUN_00410480()
{
	m_unk0x10 = 0.0f;
}

// FUNCTION: LEGORACERS 0x00410490
void MabMaterialAnimationItem0x18::FUN_00410490()
{
	if (m_unk0x0a > 0) {
		m_unk0x10 = static_cast<LegoFloat>(m_unk0x0a - 1);
	}
	else {
		m_unk0x10 = 0.0f;
	}
}

// STUB: LEGORACERS 0x004104c0
void MabMaterialAnimationItem0x18::FUN_004104c0(undefined4, undefined4*)
{
	// TODO
	STUB(0x004104c0);
}

// STUB: LEGORACERS 0x00410560
void MabMaterialAnimationItem0x18::FUN_00410560(undefined4, undefined4*)
{
	// TODO
	STUB(0x00410560);
}
