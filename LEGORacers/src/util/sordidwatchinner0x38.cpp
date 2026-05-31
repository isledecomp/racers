#include "util/sordidwatchinner0x38.h"

DECOMP_SIZE_ASSERT(SordidWatchInner0x38, 0x38)

// FUNCTION: LEGORACERS 0x004145e0
SordidWatchInner0x38::SordidWatchInner0x38()
{
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = NULL;
	m_next = NULL;
}

// FUNCTION: LEGORACERS 0x00414600
void SordidWatchInner0x38::FUN_00414600(LegoFloat p_deltaT, GolVec3* p_acceleration)
{
	GolVec3 deltaVelocity;

	LegoFloat halfDeltaT = p_deltaT * 0.5f;
	deltaVelocity.m_x = p_deltaT * p_acceleration->m_x;
	deltaVelocity.m_y = p_deltaT * p_acceleration->m_y;
	deltaVelocity.m_z = p_deltaT * p_acceleration->m_z;
	m_center.m_x += deltaVelocity.m_x * halfDeltaT + m_velocity.m_x * p_deltaT;
	m_center.m_y += deltaVelocity.m_y * halfDeltaT + m_velocity.m_y * p_deltaT;
	m_center.m_z += deltaVelocity.m_z * halfDeltaT + m_velocity.m_z * p_deltaT;
	m_velocity.m_x += deltaVelocity.m_x;
	m_velocity.m_y += deltaVelocity.m_y;
	m_velocity.m_z += deltaVelocity.m_z;
}
