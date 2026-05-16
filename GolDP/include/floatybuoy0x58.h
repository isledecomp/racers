#ifndef FLOATYBUOY0X58_H
#define FLOATYBUOY0X58_H

#include "compat.h"
#include "floatyboat0x28.h"
#include "golmath.h"

// VTABLE: GOLDP 0x100571d8
// SIZE 0x58
class FloatyBuoy0x58 : public FloatyBoat0x28 {
public:
	FloatyBuoy0x58();

	void VTable0x04(GolVec3* p_v) const override;                          // vtable+0x04
	void VTable0x08(const GolVec3& p_v) override;                          // vtable+0x08
	void VTable0x2c(const GolVec3& p_add, GolVec3* p_dest) const override; // vtable+0x2c
	void VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const override; // vtable+0x30
	void VTable0x34(const GolVec3& p_src, GolVec3* p_dest) override;       // vtable+0x34
	void VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const override; // vtable+0x38
	void VTable0x3c(const GolMatrix34&) override;                          // vtable+0x3c
	void VTable0x40(const GolVec3& p_v1, const GolVec3& p_v2) override;    // vtable+0x40
	void VTable0x44(GolMatrix3*) const override;                           // vtable+0x44
	void VTable0x48(GolVec3* p_dest1, GolVec3* p_dest2) const override;    // vtable+0x48

	void Reset();
	void FUN_10026c50(GolMatrix4* p_dest);
	void FUN_10026f70(const GolVec3& p_v);
	void FUN_10026fa0(LegoFloat p_scalar);
	void FUN_10026fc0(GolMatrix4* p_dest, float p_scale) const;

protected:
	void Initialize()
	{
		m_v2.m_x = 0.0f;
		m_v2.m_y = 0.0f;
		m_v2.m_z = 0.0f;
		m_unk0x28.m_m[0][0] = 1.0f;
		m_unk0x28.m_m[0][1] = 0.0f;
		m_unk0x28.m_m[0][2] = 0.0f;
		m_unk0x28.m_m[1][0] = 0.0f;
		m_unk0x28.m_m[1][1] = 1.0f;
		m_unk0x28.m_m[1][2] = 0.0f;
		m_unk0x28.m_m[2][0] = 0.0f;
		m_unk0x28.m_m[2][1] = 0.0f;
		m_unk0x28.m_m[2][2] = 1.0f;
		m_unk0x28.m_m[3][0] = 0.0f;
		m_unk0x28.m_m[3][1] = 0.0f;
		m_unk0x28.m_m[3][2] = 0.0f;
	}

	GolMatrix34 m_unk0x28; // 0x28
};

#endif // FLOATYBUOY0X58_H
