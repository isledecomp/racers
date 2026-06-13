#ifndef GOLCAMERA_H
#define GOLCAMERA_H

#include "camera/golcamerabase.h"
#include "camera/jadeorbit0x220.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

#include <d3d.h>

class GolCamera;
class GolD3DRenderDevice;

// VTABLE: GOLDP 0x100561f8
// SIZE 0x344
class GolCamera : public GolCameraBase {
public:
	enum {
		c_flagBit0 = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagBit2 = 1 << 2,
		c_flagBit3 = 1 << 3,
	};

	GolCamera();
	void VTable0x00() override;                                      // vtable+0x00
	void VTable0x04() override;                                      // vtable+0x04
	~GolCamera() override;                                           // vtable+0x08
	void VTable0x0c(Rect* p_rect) override;                          // vtable+0x0c
	void VTable0x10(const GolVec4* p_bounds) override;               // vtable+0x10
	void VTable0x14(GolMatrix4* p_dest) override;                    // vtable+0x14
	void VTable0x18(GolMatrix4* p_dest) override;                    // vtable+0x18
	void VTable0x1c(const GolVec3* p_src, GolVec3* p_dest) override; // vtable+0x1c
	void VTable0x20(const GolVec3* p_src, GolVec3* p_dest) override; // vtable+0x20
	using GolCameraBase::VTable0x24;                                 // vtable+0x24
	void VTable0x28() override;                                      // vtable+0x28

	// SYNTHETIC: GOLDP 0x10017a60
	// GolCamera::`vector deleting destructor'

	GolTransform* GetTransform() { return m_transform; }

protected:
	friend class GolD3DRenderDevice;

	void FUN_10001f60(GolD3DRenderDevice*);
	void FUN_100022b0(
		GolMatrix4* p_matrix,
		LegoFloat p_unk0x08,
		LegoFloat p_unk0x0c,
		LegoFloat p_unk0x10,
		LegoFloat p_unk0x14
	);
	void FUN_10002860(D3DVIEWPORT2* p_viewport);

	JadeOrbit0x220 m_unk0x120;      // 0x120
	GolD3DRenderDevice* m_renderer; // 0x340
};

#endif // GOLCAMERA_H
