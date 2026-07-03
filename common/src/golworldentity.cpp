#include "golworldentity.h"

#include <float.h>

DECOMP_SIZE_ASSERT(GolWorldEntity, 0x28)
DECOMP_SIZE_ASSERT(GolWorldEntity::ViewResult, 0x08)

// TODO: Might need to be on GolOrientedEntity?
// FUNCTION: GOLDP 0x10026fa0 FOLDED
// FUNCTION: LEGORACERS 0x00410f10
void GolWorldEntity::SetBoundsRadius(LegoFloat p_scalar)
{
	m_radius = p_scalar;
	m_minX = m_center.m_x - p_scalar;
	m_maxX = p_scalar + m_center.m_x;
}

// FUNCTION: GOLDP 0x100284c0
// FUNCTION: LEGORACERS 0x00411a40
GolWorldEntity::GolWorldEntity()
{
	m_center.m_x = 0.0f;
	m_center.m_y = 0.0f;
	m_center.m_z = 0.0f;
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_radius = 0.0f;
	m_minX = 0.0f;
	m_maxX = 0.0f;
}

// FUNCTION: GOLDP 0x100284f0
// FUNCTION: LEGORACERS 0x00411a70
void GolWorldEntity::Update(LegoS32 p_elapsed)
{
	if (m_radius < 0.0f) {
		UpdateBounds();
	}

	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsed);
	GolVec3 delta;
	delta.m_x = elapsed * m_velocity.m_x;
	delta.m_y = m_velocity.m_y;
	delta.m_y *= elapsed;
	delta.m_z = elapsed * m_velocity.m_z;
	m_center += delta;

	m_minX = m_center.m_x - m_radius;
	LegoFloat maxX = m_radius;
	maxX += m_center.m_x;
	m_maxX = maxX;
}

// FUNCTION: GOLDP 0x10028560
// FUNCTION: LEGORACERS 0x00411ae0
void GolWorldEntity::Integrate(LegoFloat p_elapsed)
{
	if (m_radius < 0.0f) {
		UpdateBounds();
	}

	GolVec3 delta;
	delta.m_x = p_elapsed * m_velocity.m_x;
	delta.m_y = m_velocity.m_y;
	delta.m_y *= p_elapsed;
	delta.m_z = m_velocity.m_z;
	delta.m_z *= p_elapsed;
	m_center += delta;

	m_minX = m_center.m_x - m_radius;
	LegoFloat maxX = m_radius;
	maxX += m_center.m_x;
	m_maxX = maxX;
}

// FUNCTION: GOLDP 0x100285d0
// FUNCTION: LEGORACERS 0x00411b50
void GolWorldEntity::ComputeVisibility(const GolViewFrustum& p_view, ViewResult* p_result)
{
	if (m_radius < 0.0f) {
		UpdateBounds();
	}

	p_result->m_lodIndex = 0;
	p_result->m_visibility = p_view.ClassifySphere(m_center, m_radius);
}

// FUNCTION: GOLDP 0x10028610
// FUNCTION: LEGORACERS 0x00411b90
LegoBool32 GolWorldEntity::Intersects(GolWorldEntity* p_model)
{
	if (m_radius < 0.0f) {
		UpdateBounds();
	}

	if (p_model->m_radius < 0.0f) {
		p_model->UpdateBounds();
	}

	LegoFloat distanceSquared = m_center.DistanceSquaredTo(p_model->m_center);

	if (distanceSquared == FLT_MAX) {
		return FALSE;
	}

	LegoFloat radius = p_model->m_radius + m_radius;
	if (distanceSquared < radius * radius) {
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: GOLDP 0x100286b0
// FUNCTION: LEGORACERS 0x00411c30
void GolWorldEntity::GetPosition(GolVec3* p_center) const
{
	p_center->m_x = m_center.m_x;
	p_center->m_y = m_center.m_y;
	p_center->m_z = m_center.m_z;
}

// FUNCTION: GOLDP 0x10028730 FOLDED
// FUNCTION: LEGORACERS 0x00411c50
void GolWorldEntity::SetPosition(const GolVec3& p_center)
{
	SetBoundsCenter(p_center);
}

// FUNCTION: GOLDP 0x100286d0
// FUNCTION: LEGORACERS 0x00411c60
void GolWorldEntity::GetBoundsCenter(GolVec3* p_center)
{
	if (m_radius < 0.0f) {
		UpdateBounds();
	}

	p_center->m_x = m_center.m_x;
	p_center->m_y = m_center.m_y;
	p_center->m_z = m_center.m_z;
}

// FUNCTION: GOLDP 0x10028700
// FUNCTION: LEGORACERS 0x00411c90
void GolWorldEntity::UpdateBounds()
{
	m_radius = 0.0f;
	m_center.m_z = 0.0f;
	m_center.m_y = 0.0f;
	m_center.m_x = 0.0f;
}

// FUNCTION: GOLDP 0x10028710
// FUNCTION: LEGORACERS 0x00411ca0
LegoFloat GolWorldEntity::GetBoundsRadius()
{
	if (m_radius < 0.0f) {
		UpdateBounds();
	}

	return m_radius;
}

// FUNCTION: GOLDP 0x10028730 FOLDED
// FUNCTION: LEGORACERS 0x00411cc0
void GolWorldEntity::SetBoundsCenter(const GolVec3& p_center)
{
	m_center.m_x = p_center.m_x;
	m_center.m_y = p_center.m_y;
	m_center.m_z = p_center.m_z;
	m_minX = m_center.m_x - m_radius;
	m_maxX = m_radius + m_center.m_x;
}

// FUNCTION: GOLDP 0x10028760
// FUNCTION: LEGORACERS 0x00411cf0
void GolWorldEntity::LocalToWorld(const GolVec3& p_add, GolVec3* p_dest) const
{
	p_dest->m_x = m_center.m_x + p_add.m_x;
	p_dest->m_y = m_center.m_y + p_add.m_y;
	p_dest->m_z = m_center.m_z + p_add.m_z;
}

// FUNCTION: GOLDP 0x10028790
// FUNCTION: LEGORACERS 0x00411d20
void GolWorldEntity::WorldToLocal(const GolVec3& p_src, GolVec3* p_dest) const
{
	p_dest->m_x = p_src.m_x - m_center.m_x;
	p_dest->m_y = p_src.m_y - m_center.m_y;
	p_dest->m_z = p_src.m_z - m_center.m_z;
}

// FUNCTION: GOLDP 0x100287c0 FOLDED
// FUNCTION: LEGORACERS 0x00411d50 FOLDED
void GolWorldEntity::RotateToWorld(const GolVec3& p_src, GolVec3* p_dest)
{
	*p_dest = p_src;
}

// FUNCTION: GOLDP 0x100287c0 FOLDED
// FUNCTION: LEGORACERS 0x00411d50 FOLDED
void GolWorldEntity::RotateToLocal(const GolVec3& p_src, GolVec3* p_dest) const
{
	*p_dest = p_src;
}

// FUNCTION: GOLDP 0x100287e0
// FUNCTION: LEGORACERS 0x00411d70
void GolWorldEntity::GetAxes(GolVec3* p_right, GolVec3* p_forward) const
{
	p_right->m_x = 1.0f;
	p_right->m_y = 0.0f;
	p_right->m_z = 0.0f;
	p_forward->m_x = 0.0f;
	p_forward->m_y = 0.0f;
	p_forward->m_z = 1.0f;
}

// FUNCTION: GOLDP 0x10028810
// FUNCTION: LEGORACERS 0x00411da0
void GolWorldEntity::CopyOrientation(GolMatrix3* p_dest) const
{
	p_dest->m_m[0][0] = 1.0f;
	p_dest->m_m[0][1] = 0.0f;
	p_dest->m_m[0][2] = 0.0f;
	p_dest->m_m[1][0] = 0.0f;
	p_dest->m_m[1][1] = 1.0f;
	p_dest->m_m[1][2] = 0.0f;
	p_dest->m_m[2][0] = 0.0f;
	p_dest->m_m[2][1] = 0.0f;
	p_dest->m_m[2][2] = 1.0f;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolWorldEntity::ClearColorTransform()
{
	// empty
}

// FUNCTION: GOLDP 0x100016f0 FOLDED
// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
undefined4 GolWorldEntity::GetKind()
{
	return 0;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void GolWorldEntity::SetDirectionUp(const GolVec3& p_direction, const GolVec3& p_up)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolWorldEntity::Draw(GolRenderDevice&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolWorldEntity::ApplyColorTransform(ColorTransform*)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolWorldEntity::SetOrientationMatrix(const GolMatrix3&)
{
	// empty
}
