#ifndef GOLCAMERABASE_H
#define GOLCAMERABASE_H

#include "camera/golviewfrustum.h"
#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "render/rectangle.h"
#include "types.h"

class GolTransform;

class GolAnimatedEntity;

// VTABLE: GOLDP 0x10056cc0
// SIZE 0x120
class GolCameraBase {
public:
	GolCameraBase();
	virtual void VTable0x00() = 0;                                                           // vtable+0x00
	virtual void VTable0x04() = 0;                                                           // vtable+0x04
	virtual ~GolCameraBase();                                                                // vtable+0x08
	virtual void VTable0x0c(Rect* p_rect) = 0;                                               // vtable+0x0c
	virtual void VTable0x10(const GolVec4* p_bounds) = 0;                                    // vtable+0x10
	virtual void VTable0x14(GolMatrix4* p_dest) = 0;                                         // vtable+0x14
	virtual void VTable0x18(GolMatrix4* p_dest) = 0;                                         // vtable+0x18
	virtual void VTable0x1c(const GolVec3* p_src, GolVec3* p_dest) = 0;                      // vtable+0x1c
	virtual void VTable0x20(const GolVec3* p_src, GolVec3* p_dest);                          // vtable+0x20
	virtual LegoBool32 VTable0x24(GolVec3* p_center, LegoFloat p_radius, GolVec4* p_bounds); // vtable+0x24
	virtual void VTable0x28() = 0;                                                           // vtable+0x28

	// SYNTHETIC: GOLDP 0x1001bf90
	// GolCameraBase::`scalar deleting destructor'

	void FUN_1001bfc0(GolViewFrustum* p_view);
	void FUN_1001c450(GolViewFrustum* p_view);
	static GolVec3* FUN_00404580(GolVec3* p_left, GolVec3* p_right, GolVec3* p_dest);
	void SetTrackedEntity(GolAnimatedEntity* p_trackedEntity, LegoU32 p_trackedNodeIndex);
	void ClearTrackedEntity();
	void LookAt(GolVec3* p_position, GolVec3* p_target, GolVec3* p_up);
	void FUN_00404710(LegoFloat p_fov, LegoFloat p_nearClip, LegoFloat p_farClip, LegoFloat p_aspectRatio);
	void SetAspectRatio(LegoFloat p_aspect);
	void UpdateFromTrackedEntity();
	LegoFloat GetFov() const { return m_fov; }
	const Rect* GetViewport() const { return &m_viewport; }

	GolTransform* m_transform;          // 0x04
	LegoFloat m_fov;                    // 0x08
	LegoFloat m_aspectRatio;            // 0x0c
	LegoFloat m_nearClip;               // 0x10
	LegoFloat m_farClip;                // 0x14
	LegoFloat m_nearHalfWidth;          // 0x18
	LegoFloat m_nearHalfHeight;         // 0x1c
	LegoFloat m_farHalfWidth;           // 0x20
	LegoFloat m_farHalfHeight;          // 0x24
	GolAnimatedEntity* m_trackedEntity; // 0x28
	LegoU32 m_trackedNodeIndex;         // 0x2c
	LegoU32 m_flags;                    // 0x30
	GolViewFrustum m_viewFrustum;       // 0x34
	GolVec4 m_viewBounds;               // 0x100
	Rect m_viewport;                    // 0x110
};

#endif // GOLCAMERABASE_H
