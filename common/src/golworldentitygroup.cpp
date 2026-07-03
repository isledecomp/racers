#include "golworldentitygroup.h"

#include "golerror.h"

#include <math.h>

DECOMP_SIZE_ASSERT(GolWorldEntityGroup, 0x38)

// FUNCTION: LEGORACERS 0x00411dd0
GolWorldEntityGroup::GolWorldEntityGroup()
{
	m_entities = NULL;
	m_capacity = 0;
	m_inverseCount = 0.0f;
	m_count = 0;
	m_radius = -1.0f;
}

// FUNCTION: LEGORACERS 0x00411e20
GolWorldEntityGroup::~GolWorldEntityGroup()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00411e30
void GolWorldEntityGroup::Allocate(LegoU32 p_capacity)
{
	if (m_entities) {
		Destroy();
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
void GolWorldEntityGroup::Destroy()
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
void GolWorldEntityGroup::AddEntity(GolWorldEntity* p_entity)
{
	m_entities[m_count] = p_entity;
	m_count++;
	m_inverseCount = 1.0f / m_count;
}

// STUB: LEGORACERS 0x00411ef0
void GolWorldEntityGroup::UpdateBounds()
{
	LegoFloat radius;
	GolVec3 delta;
	GolVec3 offset;
	GolVec3 center;
	GolVec3 firstCenter;

	offset.m_z = 0.0f;
	offset.m_y = 0.0f;
	offset.m_x = 0.0f;

	m_entities[0]->GetBoundsCenter(&firstCenter);

	LegoU32 i;
	for (i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->GetBoundsCenter(&center);
		center -= firstCenter;
		offset += center;
	}

	offset *= m_inverseCount;

	radius = 0.0f;
	for (i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->GetBoundsCenter(&center);
		center -= firstCenter;
		delta = center - offset;

		LegoFloat childRadius = m_entities[i]->GetBoundsRadius();
		LegoFloat distance =
			childRadius +
			static_cast<LegoFloat>(::sqrt(delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x));
		if (distance > radius) {
			radius = distance;
		}
	}

	offset += firstCenter;
	SetBoundsCenter(offset);
	SetBoundsRadius(radius);
}

// FUNCTION: LEGORACERS 0x004120b0
void GolWorldEntityGroup::Draw(GolRenderDevice& p_renderer)
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->Draw(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004120e0
void GolWorldEntityGroup::Update(LegoS32 p_elapsed)
{
	LegoU32 i = 0;
	if (static_cast<LegoU32>(m_count) > 0) {
		LegoFloat elapsed = static_cast<LegoFloat>(p_elapsed);
		for (;;) {
			m_entities[i]->Update(p_elapsed);

			GolVec3 center;
			m_entities[i]->GetPosition(&center);

			GolVec3 delta;
			delta.m_x = elapsed * m_velocity.m_x;
			delta.m_y = m_velocity.m_y * elapsed;
			delta.m_z = m_velocity.m_z * elapsed;
			center += delta;
			m_entities[i]->SetPosition(center);

			if (++i >= static_cast<LegoU32>(m_count)) {
				break;
			}
		}
	}

	m_radius = -1.0f;
}

// FUNCTION: LEGORACERS 0x004121a0
void GolWorldEntityGroup::LocalToWorld(const GolVec3& p_add, GolVec3* p_dest) const
{
	m_entities[0]->LocalToWorld(p_add, p_dest);
}

// FUNCTION: LEGORACERS 0x004121c0
void GolWorldEntityGroup::WorldToLocal(const GolVec3& p_src, GolVec3* p_dest) const
{
	m_entities[0]->WorldToLocal(p_src, p_dest);
}

// FUNCTION: LEGORACERS 0x004121e0
void GolWorldEntityGroup::RotateToWorld(const GolVec3& p_src, GolVec3* p_dest)
{
	m_entities[0]->RotateToWorld(p_src, p_dest);
}

// FUNCTION: LEGORACERS 0x00412200
void GolWorldEntityGroup::RotateToLocal(const GolVec3& p_src, GolVec3* p_dest) const
{
	m_entities[0]->RotateToLocal(p_src, p_dest);
}

// FUNCTION: LEGORACERS 0x00412220
void GolWorldEntityGroup::SetPosition(const GolVec3& p_center)
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->SetPosition(p_center);
	}

	m_radius = -1.0f;
}

// FUNCTION: LEGORACERS 0x00412260
void GolWorldEntityGroup::GetPosition(GolVec3* p_center) const
{
	m_entities[0]->GetPosition(p_center);
}

// FUNCTION: LEGORACERS 0x00412280
void GolWorldEntityGroup::SetDirectionUp(const GolVec3& p_direction, const GolVec3& p_up)
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->SetDirectionUp(p_direction, p_up);
	}
}

// FUNCTION: LEGORACERS 0x004122c0
void GolWorldEntityGroup::GetAxes(GolVec3* p_right, GolVec3* p_forward) const
{
	m_entities[0]->GetAxes(p_right, p_forward);
}

// FUNCTION: LEGORACERS 0x004122e0
void GolWorldEntityGroup::CopyOrientation(GolMatrix3* p_dest) const
{
	m_entities[0]->CopyOrientation(p_dest);
}

// FUNCTION: LEGORACERS 0x00412300
void GolWorldEntityGroup::ApplyColorTransform(ColorTransform* p_transform)
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->ApplyColorTransform(p_transform);
	}
}

// FUNCTION: LEGORACERS 0x00412330
void GolWorldEntityGroup::ClearColorTransform()
{
	for (LegoU32 i = 0; i < static_cast<LegoU32>(m_count); i++) {
		m_entities[i]->ClearColorTransform();
	}
}
