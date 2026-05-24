#include "lilacorbit0x28.h"

#include "whitefalconview0xcc.h"

#include <float.h>

DECOMP_SIZE_ASSERT(LilacOrbit0x28, 0x28)
DECOMP_SIZE_ASSERT(LilacOrbit0x28::ViewResult, 0x08)
DECOMP_SIZE_ASSERT(LilacOrbit0x28::TransformPayload0x20, 0x20)

// FUNCTION: LEGORACERS 0x00411a40
LilacOrbit0x28::LilacOrbit0x28()
{
	m_position.m_x = 0;
	m_position.m_y = 0;
	m_position.m_z = 0;
	m_velocity.m_x = 0;
	m_velocity.m_y = 0;
	m_velocity.m_z = 0;
	m_radius = 0;
	m_minX = 0;
	m_maxX = 0;
}

// FUNCTION: LEGORACERS 0x00411a70
void LilacOrbit0x28::VTable0x10(LegoS32 p_unk0x04)
{
	if (m_radius < 0.0f) {
		VTable0x00();
	}

	LegoFloat elapsed = static_cast<LegoFloat>(p_unk0x04);
	GolVec3 delta;
	delta.m_x = elapsed * m_velocity.m_x;
	delta.m_y = m_velocity.m_y;
	delta.m_y *= elapsed;
	delta.m_z = elapsed * m_velocity.m_z;
	m_position += delta;

	m_minX = m_position.m_x - m_radius;
	LegoFloat maxX = m_radius;
	maxX += m_position.m_x;
	m_maxX = maxX;
}

// FUNCTION: LEGORACERS 0x00411ae0
void LilacOrbit0x28::VTable0x0c(LegoFloat p_unk0x04)
{
	if (m_radius < 0.0f) {
		VTable0x00();
	}

	GolVec3 delta;
	delta.m_x = p_unk0x04 * m_velocity.m_x;
	delta.m_y = m_velocity.m_y;
	delta.m_y *= p_unk0x04;
	delta.m_z = m_velocity.m_z;
	delta.m_z *= p_unk0x04;
	m_position += delta;

	m_minX = m_position.m_x - m_radius;
	LegoFloat maxX = m_radius;
	maxX += m_position.m_x;
	m_maxX = maxX;
}

// FUNCTION: LEGORACERS 0x00411b50
void LilacOrbit0x28::VTable0x14(undefined4 p_unk0x04, undefined4 p_unk0x08)
{
	if (m_radius < 0.0f) {
		VTable0x00();
	}

	ViewResult* result = (ViewResult*) p_unk0x08;
	result->m_lodIndex = 0;
	result->m_visibility = ((WhiteFalconView0xcc*) p_unk0x04)->FUN_1002bc20(m_position, m_radius);
}

// FUNCTION: LEGORACERS 0x00411b90
LegoBool32 LilacOrbit0x28::VTable0x18(LilacOrbit0x28* p_unk0x04)
{
	if (m_radius < 0.0f) {
		VTable0x00();
	}

	if (p_unk0x04->m_radius < 0.0f) {
		p_unk0x04->VTable0x00();
	}

	LegoFloat distanceSquared = m_position.DistanceSquaredTo(p_unk0x04->m_position);

	if (distanceSquared == FLT_MAX) {
		return FALSE;
	}

	LegoFloat radius = p_unk0x04->m_radius + m_radius;
	if (distanceSquared < radius * radius) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00411c30
void LilacOrbit0x28::VTable0x04(LegoFloat* p_unk0x04)
{
	p_unk0x04[0] = m_position.m_x;
	p_unk0x04[1] = m_position.m_y;
	p_unk0x04[2] = m_position.m_z;
}

// FUNCTION: LEGORACERS 0x00411c50
void LilacOrbit0x28::VTable0x08(LegoFloat* p_unk0x04)
{
	FUN_00411cc0(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00411c60
void LilacOrbit0x28::FUN_00411c60(LegoFloat* p_unk0x04)
{
	if (m_radius < 0.0f) {
		VTable0x00();
	}

	p_unk0x04[0] = m_position.m_x;
	p_unk0x04[1] = m_position.m_y;
	p_unk0x04[2] = m_position.m_z;
}

// FUNCTION: LEGORACERS 0x00411c90
void LilacOrbit0x28::VTable0x00()
{
	m_radius = 0;
	m_position.m_z = 0;
	m_position.m_y = 0;
	m_position.m_x = 0;
}

// FUNCTION: LEGORACERS 0x00411ca0
LegoFloat LilacOrbit0x28::FUN_00411ca0()
{
	if (m_radius < 0.0f) {
		VTable0x00();
	}

	return m_radius;
}

// FUNCTION: LEGORACERS 0x00411cc0
void LilacOrbit0x28::FUN_00411cc0(LegoFloat* p_unk0x04)
{
	m_position.m_x = p_unk0x04[0];
	m_position.m_y = p_unk0x04[1];
	m_position.m_z = p_unk0x04[2];
	m_minX = m_position.m_x - m_radius;
	m_maxX = m_radius + m_position.m_x;
}

// FUNCTION: LEGORACERS 0x00411cf0
void LilacOrbit0x28::VTable0x2c(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x08[0] = m_position.m_x + p_unk0x04[0];
	p_unk0x08[1] = m_position.m_y + p_unk0x04[1];
	p_unk0x08[2] = m_position.m_z + p_unk0x04[2];
}

// FUNCTION: LEGORACERS 0x00411d20
void LilacOrbit0x28::VTable0x30(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x08[0] = p_unk0x04[0] - m_position.m_x;
	p_unk0x08[1] = p_unk0x04[1] - m_position.m_y;
	p_unk0x08[2] = p_unk0x04[2] - m_position.m_z;
}

// FUNCTION: LEGORACERS 0x00411d50 FOLDED
void LilacOrbit0x28::VTable0x34(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x08[0] = p_unk0x04[0];
	p_unk0x08[1] = p_unk0x04[1];
	p_unk0x08[2] = p_unk0x04[2];
}

// FUNCTION: LEGORACERS 0x00411d50 FOLDED
void LilacOrbit0x28::VTable0x38(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x08[0] = p_unk0x04[0];
	p_unk0x08[1] = p_unk0x04[1];
	p_unk0x08[2] = p_unk0x04[2];
}

// FUNCTION: LEGORACERS 0x00411d70
void LilacOrbit0x28::VTable0x48(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08)
{
	p_unk0x04[0] = 1.0f;
	p_unk0x04[1] = 0;
	p_unk0x04[2] = 0;
	p_unk0x08[0] = 0;
	p_unk0x08[1] = 0;
	p_unk0x08[2] = 1.0f;
}

// FUNCTION: LEGORACERS 0x00411da0
void LilacOrbit0x28::VTable0x44(LegoFloat* p_unk0x04)
{
	p_unk0x04[0] = 1.0f;
	p_unk0x04[1] = 0;
	p_unk0x04[2] = 0;
	p_unk0x04[3] = 0;
	p_unk0x04[4] = 1.0f;
	p_unk0x04[5] = 0;
	p_unk0x04[6] = 0;
	p_unk0x04[7] = 0;
	p_unk0x04[8] = 1.0f;
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void LilacOrbit0x28::VTable0x28()
{
}

// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoBool32 LilacOrbit0x28::VTable0x20()
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void LilacOrbit0x28::VTable0x1c(WhiteFalcon0x140*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void LilacOrbit0x28::VTable0x24(TransformPayload0x20*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void LilacOrbit0x28::VTable0x3c(LegoFloat*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void LilacOrbit0x28::VTable0x40(LegoFloat*, LegoFloat*)
{
}
