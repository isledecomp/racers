#include "particle0x18c.h"

#include "gol.h"

DECOMP_SIZE_ASSERT(Particle0x18c, 0x18c)

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void Particle0x18c::FUN_004513d0(BronzeFalcon0xc8770*)
{
}

// STUB: LEGORACERS 0x004893f0
Particle0x18c::Particle0x18c()
{
	STUB(0x004893f0);
}

// STUB: LEGORACERS 0x00489440
Particle0x18c::~Particle0x18c()
{
	STUB(0x00489440);
}

// STUB: LEGORACERS 0x00489520
void Particle0x18c::FUN_00489520(GolExport* p_golExport, BronzeFalcon0xc8770* p_renderer)
{
	STUB(0x00489540);
}

// STUB: LEGORACERS 0x00489540
void Particle0x18c::FUN_00489540(GolVec3* p_param1, GolVec3* p_param2)
{
	// should be semantically correct, but does not match yet

	float fVar1;
	GolVec3 v0, v1, v2, v3;

	GolMath::NormalizeVector3(*p_param1, &v0);
	GolMath::NormalizeVector3(*p_param1, &v1);
	fVar1 = v1.m_x * p_param2->m_x + p_param2->m_y * v1.m_y + v1.m_z * p_param2->m_z;

	v3.m_x = v1.m_x * fVar1;
	v3.m_y = v1.m_y * fVar1;
	v3.m_z = v1.m_z * fVar1;

	v2.m_x = p_param2->m_x - v3.m_x;
	v2.m_y = p_param2->m_y - v3.m_y;
	v2.m_z = p_param2->m_z - v3.m_z;

	GolMath::NormalizeVector3(v2, &v2);

	m_unk0x160.m_m[0][0] = v0.m_x;
	m_unk0x160.m_m[0][1] = v0.m_y;
	m_unk0x160.m_m[0][2] = v0.m_z;
	m_unk0x160.m_m[1][0] = v2.m_y * v0.m_z - v2.m_z * v0.m_y;
	m_unk0x160.m_m[1][1] = v2.m_z * v0.m_x - v0.m_z * v2.m_x;
	m_unk0x160.m_m[1][2] = v0.m_y * v2.m_x - v2.m_y * v0.m_x;
	m_unk0x160.m_m[2][0] = v2.m_x;
	m_unk0x160.m_m[2][1] = v2.m_y;
	m_unk0x160.m_m[2][2] = v2.m_z;
}

// FUNCTION: LEGORACERS 0x00489660
void Particle0x18c::FUN_00489660(GolVec3* p_vec)
{
	m_unk0x154.m_x = p_vec->m_x;
	m_unk0x154.m_y = p_vec->m_y;
	m_unk0x154.m_z = p_vec->m_z;
}

// STUB: LEGORACERS 0x004897e0
void Particle0x18c::FUN_004897e0(LegoU32)
{
	STUB(0x004897e0);
}

// STUB: LEGORACERS 0x00489960
void Particle0x18c::FUN_00489960(BronzeFalcon0xc8770*)
{
	STUB(0x00489960);
}
