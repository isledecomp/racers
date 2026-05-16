#ifndef FLOATYPONTOON0x4C_H
#define FLOATYPONTOON0x4C_H

#include "compat.h"
#include "floatyboat0x28.h"

#include <d3d.h>

class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x10057500
// SIZE 0x4c
class FloatyPontoon0x4c : public FloatyBoat0x28 {
public:
	enum {
		c_flagBit1 = 1 << 1,
		c_flagBit2 = 1 << 2,
	};

	// SIZE 0x0c
	struct Field0x2c {
		undefined m_unk0x00[0x08]; // 0x00
		undefined4** m_unk0x08;    // 0x08
	};

	FloatyPontoon0x4c();

	// FUNCTION: GOLDP 0x100156c0
	void VTable0x08(const GolVec3& p_v) override { FloatyBoat0x28::VTable0x08(p_v); } // vtable+0x08
	void VTable0x14(GolVec3* p_arg1, undefined4*) override;                           // vtable+0x14
	void VTable0x1c(WhiteFalcon0x140*) override;                                      // vtable+0x1c
	undefined4 VTable0x20() override;                                                 // vtable+0x20
	virtual void VTable0x4c(
		undefined4* p_position,
		LegoFloat p_width,
		LegoFloat p_height,
		LegoFloat p_maxDistanceSquared
	);                         // vtable+0x4c
	virtual void VTable0x50(); // vtable+0x50

	LegoBool32 FUN_10014e50(const GolVec3* p_arg1, const GolVec3* p_arg2, GolMatrix4* p_matrix);
	void FUN_10014ff0(BronzeFalcon0xc8770* p_renderer);
	void FUN_10026fa0(LegoFloat p_arg1);
	void FUN_10029e90(
		Field0x2c* p_container,
		LegoS32 p_index,
		LegoFloat p_width,
		LegoFloat p_height,
		LegoFloat p_maxDistanceSquared
	);
	void FUN_10029fa0(const GolVec3& p_arg1, LegoBool32* p_result);
	undefined4* FUN_1002a020();

private:
	undefined4* m_position;         // 0x28
	Field0x2c* m_positionContainer; // 0x2c
	GolVec3 m_unk0x30;              // 0x30
	LegoFloat m_width;              // 0x3c
	LegoFloat m_height;             // 0x40
	LegoFloat m_maxDistanceSquared; // 0x44
	LegoU16 m_flags;                // 0x48
	LegoU16 m_positionIndex;        // 0x4a
};

#endif // FLOATYPONTOON0x4C_H
