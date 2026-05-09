#ifndef GOLMATH_H
#define GOLMATH_H

#include "decomp.h"
#include "types.h"

#include <d3d.h>

// SIZE 0x8
struct GolVec2 {
	LegoFloat m_x;
	LegoFloat m_y;
};

// SIZE 0xc
struct GolVec3 {
	LegoFloat m_x;
	LegoFloat m_y;
	LegoFloat m_z;

	GolVec3 operator+(const GolVec3& p_rhs) const
	{
		GolVec3 result;
		result.m_x = this->m_x + p_rhs.m_x;
		result.m_y = this->m_y + p_rhs.m_y;
		result.m_z = this->m_z + p_rhs.m_z;
		return result;
	}

	GolVec3 operator-(const GolVec3& p_rhs) const
	{
		GolVec3 result;
		result.m_x = this->m_x - p_rhs.m_x;
		result.m_y = this->m_y - p_rhs.m_y;
		result.m_z = this->m_z - p_rhs.m_z;
		return result;
	}

	GolVec3 operator*(LegoFloat p_f) const
	{
		GolVec3 result;
		result.m_x = m_x * p_f;
		result.m_y = m_y * p_f;
		result.m_z = m_z * p_f;
		return result;
	}

	GolVec3& operator+=(const GolVec3& p_rhs)
	{
		m_x += p_rhs.m_x;
		m_y += p_rhs.m_y;
		m_z += p_rhs.m_z;
		return *this;
	}

	GolVec3& operator*=(LegoFloat p_f)
	{
		m_x *= p_f;
		m_y *= p_f;
		m_z *= p_f;
		return *this;
	}
};

inline GolVec3 operator*(LegoFloat p_f, const GolVec3& p_rhs)
{
	GolVec3 result;
	result.m_x = p_f * p_rhs.m_x;
	result.m_y = p_f * p_rhs.m_y;
	result.m_z = p_f * p_rhs.m_z;
	return result;
}

// SIZE 0x10
struct GolQuat {
	LegoFloat m_x;
	LegoFloat m_y;
	LegoFloat m_z;
	LegoFloat m_w;
};

class GolMath {
public:
	static void FUN_1002f3a0(const D3DMATRIX* p_left, const LegoFloat* p_right, LegoFloat* p_dest);
	static void FUN_1002f450(const LegoFloat* p_left, const LegoFloat* p_right, LegoFloat* p_dest);
	static void FUN_00449170(LegoFloat p_angle, LegoFloat* p_sin, LegoFloat* p_cos);
	static void FUN_00449190(const LegoFloat* p_left, const LegoFloat* p_right, LegoFloat* p_dest);
	static void __fastcall NormalizeVector2(const GolVec2& p_src, GolVec2& p_dest);
	static void __fastcall NormalizeVector3(const GolVec3& p_src, GolVec3& p_dest);
	static void FUN_00449340(const GolQuat* p_quat, LegoFloat* p_dest);
	static void FUN_1002f5a0(const LegoFloat* p_matrix, GolQuat* p_dest);
	static void FUN_1002f720(const LegoFloat* p_matrix, GolQuat* p_dest);
	static void FUN_1002f890(const GolQuat* p_from, const GolQuat* p_to, LegoFloat p_amount, GolQuat* p_dest);
	static void FUN_004496a0(const GolVec3* p_src, GolVec3* p_dest, const GolVec3* p_axis, LegoFloat p_angle);
	static LegoBool32 FUN_004497f0(const GolVec3* p_point, const LegoFloat* p_triangle);
	static LegoBool32 FUN_00449a90(
		GolVec3* p_target,
		GolVec3* p_current,
		LegoFloat p_minDistSq,
		LegoFloat p_speed,
		LegoFloat p_dt
	);
	static void FUN_00449b90(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z, const LegoFloat* p_matrix, GolVec3* p_dest);
	static void FUN_00449bf0(const LegoFloat* p_left, const LegoFloat* p_right, LegoFloat* p_dest);
};

#endif // GOLMATH_H
