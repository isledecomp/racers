#ifndef GOLMATH_H
#define GOLMATH_H

#include "decomp.h"
#include "types.h"

#define GOL_SQUARED(V) ((V) * (V))
#define GOL_MUL(A, B) ((A) * (B))
#define GOLVECTOR3_DOT(V1, V2) ((V1).m_x * (V2).m_x + (V1).m_y * (V2).m_y + (V1).m_z * (V2).m_z)
#define GOLVECTOR3_DISTANCE_SQUARED(V1, V2)                                                                            \
	(GOL_SQUARED((V1).m_x - (V2).m_x) + GOL_SQUARED((V1).m_y - (V2).m_y) + GOL_SQUARED((V1).m_z - (V2).m_z))

// SIZE 0x8
struct GolVec2 {
	LegoFloat m_x; // 0x00
	LegoFloat m_y; // 0x04
};

// SIZE 0xc
struct GolVec3 {
	LegoFloat m_x; // 0x00
	LegoFloat m_y; // 0x04
	LegoFloat m_z; // 0x08

	void Clear()
	{
		m_x = 0.0f;
		m_y = 0.0f;
		m_z = 0.0f;
	}

	void Set(const GolVec3& p_other)
	{
		m_x = p_other.m_x;
		m_y = p_other.m_y;
		m_z = p_other.m_z;
	}

	GolVec3 operator+(const GolVec3& p_rhs) const
	{
		GolVec3 result;
		result.m_x = m_x + p_rhs.m_x;
		result.m_y = m_y + p_rhs.m_y;
		result.m_z = m_z + p_rhs.m_z;
		return result;
	}

	GolVec3 operator-(const GolVec3& p_rhs) const
	{
		GolVec3 result;
		result.m_x = m_x - p_rhs.m_x;
		result.m_y = m_y - p_rhs.m_y;
		result.m_z = m_z - p_rhs.m_z;
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

	GolVec3& operator-=(const GolVec3& p_rhs)
	{
		m_x -= p_rhs.m_x;
		m_y -= p_rhs.m_y;
		m_z -= p_rhs.m_z;
		return *this;
	}

	GolVec3& operator*=(LegoFloat p_f)
	{
		m_x *= p_f;
		m_y *= p_f;
		m_z *= p_f;
		return *this;
	}

	LegoFloat DistanceSquaredTo(const GolVec3& p_other) const
	{
		GolVec3 d = p_other - *this;
		return d.m_x * d.m_x + d.m_y * d.m_y + d.m_z * d.m_z;
	}
};

// SIZE 0x10
struct GolVec4 {
	LegoFloat m_x; // 0x00
	LegoFloat m_y; // 0x04
	LegoFloat m_z; // 0x08
	LegoFloat m_u; // 0x0c
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
	LegoFloat m_x; // 0x00
	LegoFloat m_y; // 0x04
	LegoFloat m_z; // 0x08
	LegoFloat m_w; // 0x0c
};

// SIZE 0x24
struct GolMatrix3 {
	union {
		LegoFloat m_m[3][3]; // 0x00
		GolVec3 m_rows[3];   // 0x00
	};
};

// SIZE 0x30
struct GolMatrix34 {
	union {
		LegoFloat m_m[4][3]; // 0x00
		struct {
			GolMatrix3 m_orientation; // 0x00
			GolVec3 m_position;       // 0x24
		};
	};
};

// SIZE 0x40
struct GolMatrix4 {
	LegoFloat m_m[4][4]; // 0x00
};

class GolMath {
public:
	static LegoFloat QuatDot(const GolQuat& p_left, const GolQuat& p_right)
	{
		LegoFloat result = p_left.m_y;
		result *= p_right.m_y;
		LegoFloat z = p_left.m_z;
		z *= p_right.m_z;
		result += z;
		LegoFloat w = p_left.m_w;
		w *= p_right.m_w;
		result += w;
		result += p_left.m_x * p_right.m_x;
		return result;
	}

	static void ScaleVector3(const GolVec3* p_src, LegoFloat p_scale, GolVec3* p_dest)
	{
		p_dest->m_x = p_scale * p_src->m_x;

		LegoFloat y = p_src->m_y;
		y *= p_scale;
		p_dest->m_y = y;

		LegoFloat z = p_src->m_z;
		z *= p_scale;
		p_dest->m_z = z;
	}

	static void CrossVector3(const GolVec3* p_left, const GolVec3* p_right, GolVec3* p_dest)
	{
		LegoFloat x = p_left->m_y;
		LegoFloat xRight = p_right->m_z;
		x *= xRight;
		LegoFloat xSub = p_left->m_z;
		LegoFloat xSubRight = p_right->m_y;
		xSub *= xSubRight;
		x -= xSub;
		p_dest->m_x = x;

		LegoFloat y = p_left->m_z;
		y *= p_right->m_x;
		LegoFloat ySub = p_right->m_z;
		ySub *= p_left->m_x;
		y -= ySub;
		p_dest->m_y = y;

		LegoFloat z = p_right->m_y;
		z *= p_left->m_x;
		LegoFloat zSub = p_left->m_y;
		zSub *= p_right->m_x;
		z -= zSub;
		p_dest->m_z = z;
	}

	static void MultiplyMatrix4(const GolMatrix4& p_left, const GolMatrix4& p_right, GolMatrix4* p_dest);
	static void MultiplyMatrix4Affine(const GolMatrix4& p_left, const GolMatrix4& p_right, GolMatrix4* p_dest);
	static void SinCos(LegoFloat p_angle, LegoFloat* p_sin, LegoFloat* p_cos);
	static void MultiplyMatrix3(const LegoFloat* p_left, const LegoFloat* p_right, LegoFloat* p_dest);
	static void __fastcall NormalizeVector2(const GolVec2& p_src, GolVec2* p_dest);
	static void __fastcall NormalizeVector3(const GolVec3& p_src, GolVec3* p_dest);
	static void QuatToMatrix3(const GolQuat* p_quat, LegoFloat* p_dest);
	static void Matrix3ToQuat(const GolMatrix3& p_matrix, GolQuat* p_dest);
	static void Matrix4ToQuat(const GolMatrix4& p_matrix, GolQuat* p_dest);
	static void LerpQuat(const GolQuat& p_from, const GolQuat& p_to, LegoFloat p_amount, GolQuat* p_dest);
	static void RotateAboutAxis(const GolVec3* p_src, GolVec3* p_dest, const GolVec3* p_axis, LegoFloat p_angle);
	static LegoBool32 PointInTriangle(const GolVec3* p_point, const LegoFloat* p_triangle);
	static LegoBool32 MoveToward(
		GolVec3* p_target,
		GolVec3* p_current,
		LegoFloat p_minDistSq,
		LegoFloat p_speed,
		LegoFloat p_dt
	);
	static void TransformVector(GolVec3 p_src, const LegoFloat* p_matrix, GolVec3* p_dest);
	static void MultiplyMatrixByTranspose(const LegoFloat* p_left, const LegoFloat* p_right, LegoFloat* p_dest);
};

#endif // GOLMATH_H
