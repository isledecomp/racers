#ifndef GOLWORLDENTITYGROUP0X38_H
#define GOLWORLDENTITYGROUP0X38_H

#include "compat.h"
#include "golworldentity.h"

// VTABLE: LEGORACERS 0x004af81c
// SIZE 0x38
class GolWorldEntityGroup0x38 : public GolWorldEntity {
public:
	GolWorldEntityGroup0x38();
	virtual ~GolWorldEntityGroup0x38(); // vtable+0x4c

	void VTable0x00() override;                                                // vtable+0x00
	void VTable0x04(GolVec3* p_center) const override;                         // vtable+0x04
	void VTable0x08(const GolVec3& p_center) override;                         // vtable+0x08
	void VTable0x10(LegoS32 p_elapsed) override;                               // vtable+0x10
	void VTable0x1c(GolRenderDevice& p_renderer) override;                     // vtable+0x1c
	void VTable0x24(ColorTransform0x20* p_transform) override;                 // vtable+0x24
	void VTable0x28() override;                                                // vtable+0x28
	void VTable0x2c(const GolVec3& p_add, GolVec3* p_dest) const override;     // vtable+0x2c
	void VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const override;     // vtable+0x30
	void VTable0x34(const GolVec3& p_src, GolVec3* p_dest) override;           // vtable+0x34
	void VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const override;     // vtable+0x38
	void VTable0x40(const GolVec3& p_direction, const GolVec3& p_up) override; // vtable+0x40
	void VTable0x44(GolMatrix3* p_dest) const override;                        // vtable+0x44
	void VTable0x48(GolVec3* p_right, GolVec3* p_forward) const override;      // vtable+0x48

	void FUN_00411e30(LegoU32 p_capacity);
	void FUN_00411e90();
	void FUN_00411ec0(GolWorldEntity* p_entity);

	// SYNTHETIC: LEGORACERS 0x00411e00
	// GolWorldEntityGroup0x38::`scalar deleting destructor'

protected:
	LegoU32 m_capacity;          // 0x28
	LegoFloat m_inverseCount;    // 0x2c
	LegoS32 m_count;             // 0x30
	GolWorldEntity** m_entities; // 0x34
};

#endif // GOLWORLDENTITYGROUP0X38_H
