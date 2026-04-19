#ifndef FLOATYBOAT0x28_H
#define FLOATYBOAT0x28_H

#include "decomp.h"
#include "types.h"

// FIXME: move to dedicated header once found to be useful
struct FloatyVec0xc {
	LegoFloat m_x;
	LegoFloat m_y;
	LegoFloat m_z;

	FloatyVec0xc operator+(const FloatyVec0xc& p_rhs) const
	{
		FloatyVec0xc result;
		result.m_x = this->m_x + p_rhs.m_x;
		result.m_y = this->m_y + p_rhs.m_y;
		result.m_z = this->m_z + p_rhs.m_z;
		return result;
	}
	FloatyVec0xc operator-(const FloatyVec0xc& p_rhs) const
	{
		FloatyVec0xc result;
		result.m_x = this->m_x - p_rhs.m_x;
		result.m_y = this->m_y - p_rhs.m_y;
		result.m_z = this->m_z - p_rhs.m_z;
		return result;
	}
	FloatyVec0xc operator*(LegoFloat p_f) const
	{
		FloatyVec0xc result;
		result.m_x = m_x * p_f;
		result.m_y = m_y * p_f;
		result.m_z = m_z * p_f;
		return result;
	}
	FloatyVec0xc& operator+=(const FloatyVec0xc& p_rhs)
	{
		m_x += p_rhs.m_x;
		m_y += p_rhs.m_y;
		m_z += p_rhs.m_z;
		return *this;
	}
	FloatyVec0xc& operator*=(LegoFloat p_f)
	{
		m_x *= p_f;
		m_y *= p_f;
		m_z *= p_f;
		return *this;
	}
};

inline FloatyVec0xc operator*(LegoFloat p_f, const FloatyVec0xc& p_rhs)
{
	FloatyVec0xc result;
	result.m_x = p_f * p_rhs.m_x;
	result.m_y = p_f * p_rhs.m_y;
	result.m_z = p_f * p_rhs.m_z;
	return result;
}

// VTABLE: GOLDP 0x100572e4
// SIZE: 0x28
class FloatyBoat0x28 {
public:
	FloatyBoat0x28();

	virtual void VTable0x00();
	virtual void VTable0x04(FloatyVec0xc* p_v) const;
	virtual void VTable0x08(const FloatyVec0xc& p_v);
	virtual void VTable0x0c(LegoFloat p_v);
	virtual void VTable0x10(LegoS32);
	virtual void VTable0x14(FloatyVec0xc* p_arg1, undefined4*);
	virtual LegoS32 VTable0x18();
	virtual void VTable0x1c(undefined4*);
	virtual undefined4 VTable0x20();
	virtual void VTable0x24(undefined4*);
	virtual void VTable0x28();
	virtual void VTable0x2c(const FloatyVec0xc& p_add, FloatyVec0xc* p_dest) const;
	virtual void VTable0x30(const FloatyVec0xc& p_src, FloatyVec0xc* p_dest) const;
	virtual void VTable0x34(const FloatyVec0xc& p_src, FloatyVec0xc* p_dest);
	virtual void VTable0x38(const FloatyVec0xc& p_src, FloatyVec0xc* p_dest) const;
	virtual void VTable0x3c(undefined4*);
	virtual void VTable0x40(undefined4, undefined4);
	virtual void VTable0x44(undefined4*) const;
	virtual void VTable0x48(FloatyVec0xc* p_v1, FloatyVec0xc* p_v2) const;

	void FUN_100286d0(FloatyVec0xc* p_v);
	LegoFloat FUN_10028710();

private:
	FloatyVec0xc m_v0; // 0x04
	FloatyVec0xc m_v1; // 0x10
	FloatyVec0xc m_v2; // 0x1c
};

#endif // FLOATYBOAT0x28_H
