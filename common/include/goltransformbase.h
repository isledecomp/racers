#ifndef GOLTRANSFORMBASE_H
#define GOLTRANSFORMBASE_H

#include "types.h"

struct GolQuat;
struct GolVec3;

// VTABLE: GOLDP 0x10056cf0
// SIZE 0x10
class GolTransformBase {
public:
	GolTransformBase();
	virtual void VTable0x00() = 0;                                                  // vtable+0x00
	virtual void TransformPoint(const GolVec3* p_src, GolVec3* p_dest) = 0;         // vtable+0x04
	virtual void InverseTransformPoint(const GolVec3* p_src, GolVec3* p_dest) = 0;  // vtable+0x08
	virtual void TransformVector(const GolVec3* p_src, GolVec3* p_dest) = 0;        // vtable+0x0c
	virtual void InverseTransformVector(const GolVec3* p_src, GolVec3* p_dest) = 0; // vtable+0x10
	virtual void GetRotation(GolQuat* p_rotation) = 0;                              // vtable+0x14
	virtual void GetBasis(GolVec3* p_right, GolVec3* p_forward,
						  GolVec3* p_up) = 0;                                   // vtable+0x18
	virtual void GetDirectionUp(GolVec3* p_direction, GolVec3* p_up) = 0;       // vtable+0x1c
	virtual void GetRightDirection(GolVec3* p_right, GolVec3* p_direction) = 0; // vtable+0x20
	virtual void SetDirectionUp(GolVec3* p_direction, GolVec3* p_up) = 0;       // vtable+0x24
	virtual void SetRightDirection(GolVec3* p_right, GolVec3* p_direction) = 0; // vtable+0x28
	virtual void SetRotation(LegoFloat* p_quat) = 0;                            // vtable+0x2c
	virtual void GetUp(GolVec3* p_up) = 0;                                      // vtable+0x30
	virtual void GetForward(GolVec3* p_forward) = 0;                            // vtable+0x34
	virtual void GetRight(GolVec3* p_right) = 0;                                // vtable+0x38
	virtual LegoFloat DistanceSquaredTo(GolVec3* p_position) = 0;               // vtable+0x3c
	virtual void GetPosition(GolVec3* p_position) = 0;                          // vtable+0x40
	virtual void SetPosition(GolVec3* p_position) = 0;                          // vtable+0x44
	virtual void CopyFrom(GolTransformBase* p_source) = 0;                      // vtable+0x48

	void AttachChild(GolTransformBase* p_child);

	GolTransformBase* m_parent;      // 0x04
	GolTransformBase* m_nextSibling; // 0x08
	GolTransformBase* m_firstChild;  // 0x0c
};

#endif // GOLTRANSFORMBASE_H
