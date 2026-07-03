#ifndef GOLORIENTEDENTITY_H
#define GOLORIENTEDENTITY_H

#include "compat.h"
#include "golmath.h"
#include "golworldentity.h"

// VTABLE: GOLDP 0x100571d8
// VTABLE: LEGORACERS 0x004af700
// SIZE 0x58
class GolOrientedEntity : public GolWorldEntity {
public:
	GolOrientedEntity();

	void GetPosition(GolVec3* p_v) const override;                            // vtable+0x04
	void SetPosition(const GolVec3& p_v) override;                            // vtable+0x08
	void LocalToWorld(const GolVec3& p_add, GolVec3* p_dest) const override;  // vtable+0x2c
	void WorldToLocal(const GolVec3& p_src, GolVec3* p_dest) const override;  // vtable+0x30
	void RotateToWorld(const GolVec3& p_src, GolVec3* p_dest) override;       // vtable+0x34
	void RotateToLocal(const GolVec3& p_src, GolVec3* p_dest) const override; // vtable+0x38
	void SetOrientationMatrix(const GolMatrix3&) override;                    // vtable+0x3c
	void SetDirectionUp(const GolVec3& p_v1, const GolVec3& p_v2) override;   // vtable+0x40
	void CopyOrientation(GolMatrix3*) const override;                         // vtable+0x44
	void GetAxes(GolVec3* p_dest1, GolVec3* p_dest2) const override;          // vtable+0x48

	void Reset();
	void SetDirectionSide(const GolVec3& p_direction, const GolVec3& p_side);
	void SetUpDirection(const GolVec3& p_up, const GolVec3& p_direction);
	void CopyOrientationToMatrix4(GolMatrix4* p_dest);
	void SetBoundsCenterAndSpan(const GolVec3& p_center);
	void CopyScaledOrientationTo(GolMatrix4* p_dest, LegoFloat p_scale) const;
	void TransformMatrixToLocal(const GolMatrix3& p_matrix, GolMatrix3* p_dest) const;
	void MirrorY();
	GolMatrix3& GetOrientation() { return m_orientation; }
	const GolMatrix3& GetOrientation() const { return m_orientation; }
	const GolVec3& GetPosition() const { return m_position; }
	const GolMatrix34& GetTransform() const { return m_transform; }
	void SetOrientation(const GolMatrix3& p_orientation)
	{
		m_orientation.m_m[0][0] = p_orientation.m_m[0][0];
		m_orientation.m_m[0][1] = p_orientation.m_m[0][1];
		m_orientation.m_m[0][2] = p_orientation.m_m[0][2];
		m_orientation.m_m[1][0] = p_orientation.m_m[1][0];
		m_orientation.m_m[1][1] = p_orientation.m_m[1][1];
		m_orientation.m_m[1][2] = p_orientation.m_m[1][2];
		m_orientation.m_m[2][0] = p_orientation.m_m[2][0];
		m_orientation.m_m[2][1] = p_orientation.m_m[2][1];
		m_orientation.m_m[2][2] = p_orientation.m_m[2][2];
	}
	void SetOrientationFromQuaternion(const GolQuat& p_rotation)
	{
		GolMath::QuatToMatrix3(&p_rotation, &m_orientation.m_m[0][0]);
	}
	void CopyPositionFrom(const GolOrientedEntity& p_other)
	{
		m_position = p_other.m_position;
		m_radius = -1.0f;
	}
	void CopyOrientationFrom(const GolOrientedEntity& p_other)
	{
		m_orientation.m_m[0][0] = p_other.m_orientation.m_m[0][0];
		m_orientation.m_m[0][1] = p_other.m_orientation.m_m[0][1];
		m_orientation.m_m[0][2] = p_other.m_orientation.m_m[0][2];
		m_orientation.m_m[1][0] = p_other.m_orientation.m_m[1][0];
		m_orientation.m_m[1][1] = p_other.m_orientation.m_m[1][1];
		m_orientation.m_m[1][2] = p_other.m_orientation.m_m[1][2];
		m_orientation.m_m[2][0] = p_other.m_orientation.m_m[2][0];
		m_orientation.m_m[2][1] = p_other.m_orientation.m_m[2][1];
		m_orientation.m_m[2][2] = p_other.m_orientation.m_m[2][2];
	}
	void CopyTransformFrom(const GolOrientedEntity& p_other)
	{
		m_orientation.m_m[0][0] = p_other.m_orientation.m_m[0][0];
		const GolVec3& position = p_other.m_position;
		m_orientation.m_m[0][1] = p_other.m_orientation.m_m[0][1];
		m_orientation.m_m[0][2] = p_other.m_orientation.m_m[0][2];
		m_orientation.m_m[1][0] = p_other.m_orientation.m_m[1][0];
		m_orientation.m_m[1][1] = p_other.m_orientation.m_m[1][1];
		m_orientation.m_m[1][2] = p_other.m_orientation.m_m[1][2];
		m_orientation.m_m[2][0] = p_other.m_orientation.m_m[2][0];
		m_orientation.m_m[2][1] = p_other.m_orientation.m_m[2][1];
		m_orientation.m_m[2][2] = p_other.m_orientation.m_m[2][2];
		m_position.m_x = position.m_x;
		m_position.m_y = position.m_y;
		m_position.m_z = position.m_z;
		m_radius = -1.0f;
	}
	void CopyOrientationFrom2(const GolOrientedEntity& p_other);
	void CopyOrientationTo(GolMatrix3* p_orientation) const
	{
		p_orientation->m_m[0][0] = m_orientation.m_m[0][0];
		p_orientation->m_m[0][1] = m_orientation.m_m[0][1];
		p_orientation->m_m[0][2] = m_orientation.m_m[0][2];
		p_orientation->m_m[1][0] = m_orientation.m_m[1][0];
		p_orientation->m_m[1][1] = m_orientation.m_m[1][1];
		p_orientation->m_m[1][2] = m_orientation.m_m[1][2];
		p_orientation->m_m[2][0] = m_orientation.m_m[2][0];
		p_orientation->m_m[2][1] = m_orientation.m_m[2][1];
		p_orientation->m_m[2][2] = m_orientation.m_m[2][2];
	}
	void GetOrientationRow0(GolVec3* p_dest) const
	{
		p_dest->m_x = m_orientation.m_m[0][0];
		p_dest->m_y = m_orientation.m_m[0][1];
		p_dest->m_z = m_orientation.m_m[0][2];
	}
	void GetOrientationRow1(GolVec3* p_dest) const
	{
		p_dest->m_x = m_orientation.m_m[1][0];
		p_dest->m_y = m_orientation.m_m[1][1];
		p_dest->m_z = m_orientation.m_m[1][2];
	}

public:
	union {
		struct {
			GolMatrix3 m_orientation; // 0x28
			GolVec3 m_position;       // 0x4c
		};
		GolMatrix34 m_transform; // 0x28
	};
};

#endif // GOLORIENTEDENTITY_H
