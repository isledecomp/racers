#include "golworldentitygroup0x38.h"

#include "golerror.h"

#include <math.h>

DECOMP_SIZE_ASSERT(GolWorldEntityGroup0x38, 0x38)

// FUNCTION: LEGORACERS 0x00411dd0
GolWorldEntityGroup0x38::GolWorldEntityGroup0x38()
{
	m_entities = NULL;
	m_capacity = 0;
	m_inverseCount = 0.0f;
	m_count = 0;
	m_radius = -1.0f;
}

// FUNCTION: LEGORACERS 0x00411e20
GolWorldEntityGroup0x38::~GolWorldEntityGroup0x38()
{
	FUN_00411e90();
}

// FUNCTION: LEGORACERS 0x00411e30
void GolWorldEntityGroup0x38::FUN_00411e30(LegoU32 p_capacity)
{
	if (m_entities) {
		FUN_00411e90();
	}

	m_entities = new GolWorldEntity*[p_capacity];
	if (!m_entities) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_capacity = p_capacity;
	m_count = 0;
	m_inverseCount = 0.0f;
	m_radius = -1.0f;
}

// FUNCTION: LEGORACERS 0x00411e90
void GolWorldEntityGroup0x38::FUN_00411e90()
{
	if (m_entities) {
		delete[] m_entities;
		m_entities = NULL;
	}

	m_capacity = 0;
	m_count = 0;
	m_inverseCount = 0.0f;
}

// FUNCTION: LEGORACERS 0x00411ec0
void GolWorldEntityGroup0x38::FUN_00411ec0(GolWorldEntity* p_entity)
{
	m_entities[m_count] = p_entity;
	m_count++;
	m_inverseCount = 1.0f / m_count;
}

// STUB: LEGORACERS 0x00411ef0
void GolWorldEntityGroup0x38::VTable0x00()
{
	LegoFloat radius;
	GolVec3 delta;
	GolVec3 offset;
	GolVec3 center;
	GolVec3 firstCenter;

	offset.m_z = 0.0f;
	offset.m_y = 0.0f;
	offset.m_x = 0.0f;

	m_entities[0]->FUN_100286d0(&firstCenter);

	LegoU32 i;
	for (i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->FUN_100286d0(&center);
		center -= firstCenter;
		offset += center;
	}

	offset *= m_inverseCount;

	radius = 0.0f;
	for (i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->FUN_100286d0(&center);
		center -= firstCenter;
		delta = center - offset;

		LegoFloat childRadius = m_entities[i]->FUN_10028710();
		LegoFloat distance =
			childRadius +
			static_cast<LegoFloat>(::sqrt(delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x));
		if (distance > radius) {
			radius = distance;
		}
	}

	offset += firstCenter;
	SetCenter(offset);
	FUN_10026fa0(radius);
}

// FUNCTION: LEGORACERS 0x004120b0
void GolWorldEntityGroup0x38::VTable0x1c(GolRenderDevice& p_renderer)
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->VTable0x1c(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004120e0
void GolWorldEntityGroup0x38::VTable0x10(LegoS32 p_elapsed)
{
	LegoU32 i = 0;
	if (static_cast<LegoU32>(m_count) > 0) {
		LegoFloat elapsed = static_cast<LegoFloat>(p_elapsed);
		for (;;) {
			m_entities[i]->VTable0x10(p_elapsed);

			GolVec3 center;
			m_entities[i]->VTable0x04(&center);

			GolVec3 delta;
			delta.m_x = elapsed * m_velocity.m_x;
			delta.m_y = m_velocity.m_y * elapsed;
			delta.m_z = m_velocity.m_z * elapsed;
			center += delta;
			m_entities[i]->VTable0x08(center);

			if (++i >= static_cast<LegoU32>(m_count)) {
				break;
			}
		}
	}

	m_radius = -1.0f;
}

// FUNCTION: LEGORACERS 0x004121a0
void GolWorldEntityGroup0x38::VTable0x2c(const GolVec3& p_add, GolVec3* p_dest) const
{
	m_entities[0]->VTable0x2c(p_add, p_dest);
}

// FUNCTION: LEGORACERS 0x004121c0
void GolWorldEntityGroup0x38::VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const
{
	m_entities[0]->VTable0x30(p_src, p_dest);
}

// FUNCTION: LEGORACERS 0x004121e0
void GolWorldEntityGroup0x38::VTable0x34(const GolVec3& p_src, GolVec3* p_dest)
{
	m_entities[0]->VTable0x34(p_src, p_dest);
}

// FUNCTION: LEGORACERS 0x00412200
void GolWorldEntityGroup0x38::VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const
{
	m_entities[0]->VTable0x38(p_src, p_dest);
}

// FUNCTION: LEGORACERS 0x00412220
void GolWorldEntityGroup0x38::VTable0x08(const GolVec3& p_center)
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->VTable0x08(p_center);
	}

	m_radius = -1.0f;
}

// FUNCTION: LEGORACERS 0x00412260
void GolWorldEntityGroup0x38::VTable0x04(GolVec3* p_center) const
{
	m_entities[0]->VTable0x04(p_center);
}

// FUNCTION: LEGORACERS 0x00412280
void GolWorldEntityGroup0x38::VTable0x40(const GolVec3& p_direction, const GolVec3& p_up)
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->VTable0x40(p_direction, p_up);
	}
}

// FUNCTION: LEGORACERS 0x004122c0
void GolWorldEntityGroup0x38::VTable0x48(GolVec3* p_right, GolVec3* p_forward) const
{
	m_entities[0]->VTable0x48(p_right, p_forward);
}

// FUNCTION: LEGORACERS 0x004122e0
void GolWorldEntityGroup0x38::VTable0x44(GolMatrix3* p_dest) const
{
	m_entities[0]->VTable0x44(p_dest);
}

// FUNCTION: LEGORACERS 0x00412300
void GolWorldEntityGroup0x38::VTable0x24(ColorTransform0x20* p_transform)
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->VTable0x24(p_transform);
	}
}

// FUNCTION: LEGORACERS 0x00412330
void GolWorldEntityGroup0x38::VTable0x28()
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->VTable0x28();
	}
}
