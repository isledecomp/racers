#include "floatypontoon0x4c.h"

#include "whitefalcon0x140.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(FloatyPontoon0x4c, 0x4c)

// GLOBAL: GOLDP 0x100574fc
float g_pontoonMaxFloat = FLT_MAX;

// FUNCTION: GOLDP 0x10029df0
FloatyPontoon0x4c::FloatyPontoon0x4c()
{
	m_unk0x28 = 0.0f;
	m_unk0x2c = 0.0f;
	m_unk0x30 = 0.0f;
	m_unk0x34 = 0.0f;
	m_unk0x38 = 1.0f;
	m_unk0x48 = 0;
	m_unk0x4a = 0;
	m_unk0x3c = 0.0f;
	m_unk0x40 = 0.0f;
	m_unk0x44 = g_pontoonMaxFloat; // std::numeric_limits<float>::max();
}

// FUNCTION: GOLDP 0x10029e30
undefined4 FloatyPontoon0x4c::VTable0x4c(LegoFloat p_arg1, LegoFloat p_arg2, LegoFloat p_arg3, LegoFloat p_arg4)

{
#define SQR(V) ((V) * (V))
	LegoFloat len = sqrtf(SQR(p_arg2 / 2.0f) + SQR(p_arg3 / 2.0f));
#undef SQR
	m_unk0x28 = p_arg1;
	m_unk0x3c = p_arg2;
	m_unk0x40 = p_arg3;
	m_unk0x48 = 1;
	m_unk0x44 = p_arg4;
	return FUN_10026fa0(len);
}

// STUB: GOLDP 0x10029e90
void FloatyPontoon0x4c::FUN_10029e90(
	undefined4* p_arg1,
	LegoS32 p_arg2,
	undefined4 p_arg3,
	undefined4 p_arg4,
	undefined4 p_arg5
)
{
	// TODO
	STUB(0x10029e90);
}

// FUNCTION: GOLDP 0x10029ed0
void FloatyPontoon0x4c::VTable0x50()
{
	m_unk0x28 = 0.0f;
	m_unk0x48 = 0;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
}

// STUB: GOLDP 0x10029ee0
void FloatyPontoon0x4c::VTable0x14(GolVec3* p_arg1, undefined4* p_arg2)
{
	// TODO
	STUB(0x10029ee0);
}

// STUB: GOLDP 0x10026fa0 FOLDED
undefined4 FloatyPontoon0x4c::FUN_10026fa0(LegoFloat p_arg1)
{
	// TODO
	STUB(0x10026fa0);
	return 0;
}

// STUB: GOLDP 0x10029fa0
void FloatyPontoon0x4c::FUN_10029fa0(const GolVec3&, undefined4*)
{
	STUB(0x10029fa0);
}

// STUB: GOLDP 0x1002a020
undefined4 FloatyPontoon0x4c::FUN_1002a020()
{
	// TODO
	STUB(0x1002a020);
	return 0;
}

// FUNCTION: GOLDP 0x1002a040
void FloatyPontoon0x4c::VTable0x1c(WhiteFalcon0x140* p_renderer)
{
	p_renderer->VTable0xb4(*this);
}

// STUB: GOLDP 0x1002a060
undefined4 FloatyPontoon0x4c::VTable0x20()
{
	// TODO
	STUB(0x1002a060);
	return 0;
}
