#ifndef FLOATYBUOY0X58_H
#define FLOATYBUOY0X58_H

#include "compat.h"
#include "floatyboat0x28.h"
#include "golmath.h"

// VTABLE: GOLDP 0x100571d8
// VTABLE: LEGORACERS 0x004af700
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
	GolMatrix3 m_orientation; // 0x28
	GolVec3 m_position;       // 0x4c
};

#endif // FLOATYBUOY0X58_H
