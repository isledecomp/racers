#ifndef GOLCAMERABASE_H
#define GOLCAMERABASE_H

#include "camera/golviewfrustum.h"
#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "render/rectangle.h"
#include "types.h"

class GolTransform;

#ifdef BUILDING_LEGORACERS
class OpalHaven0xf4;
typedef OpalHaven0xf4 AmberLensTrackedObject0xf4;
#else
class GolSkinnedEntity;
typedef GolSkinnedEntity AmberLensTrackedObject0xf4;
#endif

// VTABLE: GOLDP 0x10056cc0
// SIZE 0x120
class GolCameraBase {
public:
	GolCameraBase();
	virtual void VTable0x00() = 0;                                                             // vtable+0x00
	virtual void VTable0x04() = 0;                                                             // vtable+0x04
	virtual ~GolCameraBase();                                                                  // vtable+0x08
	virtual void VTable0x0c(Rect* p_rect) = 0;                                                 // vtable+0x0c
	virtual void VTable0x10(const GolVec4* p_bounds) = 0;                                      // vtable+0x10
	virtual void VTable0x14(GolMatrix4* p_dest) = 0;                                           // vtable+0x14
	virtual void VTable0x18(GolMatrix4* p_dest) = 0;                                           // vtable+0x18
	virtual void VTable0x1c(const GolVec3* p_src, GolVec3* p_dest) = 0;                        // vtable+0x1c
	virtual void VTable0x20(const GolVec3* p_src, GolVec3* p_dest);                            // vtable+0x20
	virtual void VTable0x24(undefined4 p_unk0x04, undefined4 p_unk0x08, undefined4 p_unk0x0c); // vtable+0x24
	virtual void VTable0x28() = 0;                                                             // vtable+0x28

	// SYNTHETIC: GOLDP 0x1001bf90
	// GolCameraBase::`scalar deleting destructor'

	void FUN_1001bfc0(GolViewFrustum* p_view);
	void FUN_1001c450(GolViewFrustum* p_view);
	void FUN_1001cb30(AmberLensTrackedObject0xf4* p_arg1, LegoU32 p_arg2);
	void FUN_004046a0(GolVec3* p_position, GolVec3* p_target, GolVec3* p_up);
	void FUN_00404740(LegoFloat p_aspect);
	void FUN_004047b0();
	const Rect* GetViewport() const { return &m_viewport; }

	GolTransform* m_unk0x04;               // 0x04
	LegoFloat m_unk0x08;                   // 0x08
	LegoFloat m_unk0x0c;                   // 0x0c
	LegoFloat m_unk0x10;                   // 0x10
	LegoFloat m_unk0x14;                   // 0x14
	LegoFloat m_unk0x18;                   // 0x18
	LegoFloat m_unk0x1c;                   // 0x1c
	LegoFloat m_unk0x20;                   // 0x20
	LegoFloat m_unk0x24;                   // 0x24
	AmberLensTrackedObject0xf4* m_unk0x28; // 0x28
	LegoU32 m_unk0x2c;                     // 0x2c
	LegoU32 m_flags;                       // 0x30
	GolViewFrustum m_unk0x34;              // 0x34
	GolVec4 m_unk0x100;                    // 0x100
	Rect m_viewport;                       // 0x110
};

#endif // GOLCAMERABASE_H
