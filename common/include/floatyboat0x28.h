#ifndef FLOATYBOAT0X28_H
#define FLOATYBOAT0X28_H

#include "decomp.h"
#include "gdbvertexarray0xc.h"
#include "golmath.h"
#include "whitefalconview0xcc.h"

class WhiteFalcon0x140;
class ZoweeBlubberworth0xf0;

// VTABLE: GOLDP 0x100572e4
// VTABLE: LEGORACERS 0x004af7cc
// SIZE 0x28
class FloatyBoat0x28 {
public:
	FloatyBoat0x28();

	// SIZE 0x08
	struct ViewResult {
		LegoS32 m_visibility; // 0x00
		LegoU32 m_lodIndex;   // 0x04
	};

	typedef ViewResult ResultStruct;

	virtual void VTable0x00();                                                        // vtable+0x00
	virtual void VTable0x04(GolVec3* p_center) const;                                 // vtable+0x04
	virtual void VTable0x08(const GolVec3& p_center);                                 // vtable+0x08
	virtual void VTable0x0c(LegoFloat p_elapsed);                                     // vtable+0x0c
	virtual void VTable0x10(LegoS32 p_elapsed);                                       // vtable+0x10
	virtual void VTable0x14(const WhiteFalconView0xcc& p_view, ViewResult* p_result); // vtable+0x14
	virtual LegoBool32 VTable0x18(FloatyBoat0x28* p_model);                           // vtable+0x18
	virtual void VTable0x1c(WhiteFalcon0x140& p_renderer);                            // vtable+0x1c
	virtual undefined4 VTable0x20();                                                  // vtable+0x20
	virtual void VTable0x24(ColorTransform0x20* p_transform);                         // vtable+0x24
	virtual void VTable0x28();                                                        // vtable+0x28
	virtual void VTable0x2c(const GolVec3& p_add, GolVec3* p_dest) const;             // vtable+0x2c
	virtual void VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const;             // vtable+0x30
	virtual void VTable0x34(const GolVec3& p_src, GolVec3* p_dest);                   // vtable+0x34
	virtual void VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const;             // vtable+0x38
	virtual void VTable0x3c(const GolMatrix34& p_matrix);                             // vtable+0x3c
	virtual void VTable0x40(const GolVec3& p_direction, const GolVec3& p_up);         // vtable+0x40
	virtual void VTable0x44(GolMatrix3* p_dest) const;                                // vtable+0x44
	virtual void VTable0x48(GolVec3* p_right, GolVec3* p_forward) const;              // vtable+0x48

	void FUN_100286d0(GolVec3* p_center);
	LegoFloat FUN_10028710();

protected:
	friend class ZoweeBlubberworth0xf0;

	void SetCenter(const GolVec3& p_center);

	GolVec3 m_center;   // 0x04
	LegoFloat m_radius; // 0x10
	LegoFloat m_minX;   // 0x14
	LegoFloat m_maxX;   // 0x18
	GolVec3 m_velocity; // 0x1c
};

#endif // FLOATYBOAT0X28_H
