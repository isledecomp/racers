#ifndef FLOATYBOAT0x28_H
#define FLOATYBOAT0x28_H

#include "decomp.h"
#include "golmath.h"
#include "whitefalconview0xcc.h"

class WhiteFalcon0x140;
class ZoweeBlubberworth0xf0;

// VTABLE: GOLDP 0x100572e4
// SIZE 0x28
class FloatyBoat0x28 {
public:
	FloatyBoat0x28();

	// SIZE 0x08
	struct ResultStruct {
		LegoS32 m_visibility; // 0x00
		LegoU32 m_lodIndex;   // 0x04
	};

	// SIZE 0x20
	struct TransformPayload0x20 {
		LegoS32 m_baseX;   // 0x00
		LegoS32 m_baseY;   // 0x04
		LegoS32 m_baseZ;   // 0x08
		LegoS32 m_baseW;   // 0x0c
		LegoS32 m_offsetX; // 0x10
		LegoS32 m_offsetY; // 0x14
		LegoS32 m_offsetZ; // 0x18
		LegoS32 m_offsetW; // 0x1c
	};

	virtual void VTable0x00();                                                          // vtable+0x00
	virtual void VTable0x04(GolVec3* p_v) const;                                        // vtable+0x04
	virtual void VTable0x08(const GolVec3& p_v);                                        // vtable+0x08
	virtual void VTable0x0c(LegoFloat p_v);                                             // vtable+0x0c
	virtual void VTable0x10(LegoS32);                                                   // vtable+0x10
	virtual void VTable0x14(const WhiteFalconView0xcc& p_view, ResultStruct* p_result); // vtable+0x14
	virtual LegoS32 VTable0x18();                                                       // vtable+0x18
	virtual void VTable0x1c(WhiteFalcon0x140&);                                         // vtable+0x1c
	virtual undefined4 VTable0x20();                                                    // vtable+0x20
	virtual void VTable0x24(TransformPayload0x20* p_transform);                         // vtable+0x24
	virtual void VTable0x28();                                                          // vtable+0x28
	virtual void VTable0x2c(const GolVec3& p_add, GolVec3* p_dest) const;               // vtable+0x2c
	virtual void VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const;               // vtable+0x30
	virtual void VTable0x34(const GolVec3& p_src, GolVec3* p_dest);                     // vtable+0x34
	virtual void VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const;               // vtable+0x38
	virtual void VTable0x3c(const GolMatrix34&);                                        // vtable+0x3c
	virtual void VTable0x40(const GolVec3& p_v1, const GolVec3& p_v2);                  // vtable+0x40
	virtual void VTable0x44(GolMatrix3*) const;                                         // vtable+0x44
	virtual void VTable0x48(GolVec3* p_v1, GolVec3* p_v2) const;                        // vtable+0x48

	void FUN_100286d0(GolVec3* p_v);
	LegoFloat FUN_10028710();

protected:
	friend class ZoweeBlubberworth0xf0;

	GolVec3 m_v0; // 0x04
	GolVec3 m_v1; // 0x10
	GolVec3 m_v2; // 0x1c
};

#endif // FLOATYBOAT0x28_H
