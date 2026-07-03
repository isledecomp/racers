#ifndef GOLCAMERA_H
#define GOLCAMERA_H

#include "camera/golcameramatrices.h"
#include "compat.h"
#include "decomp.h"
#include "golcamerabase.h"
#include "types.h"

#include <d3d.h>

class GolCamera;
class GolD3DRenderDevice;

// VTABLE: GOLDP 0x100561f8
// SIZE 0x344
class GolCamera : public GolCameraBase {
public:
	GolCamera();
	void UpdateViewMatrix() override;                                     // vtable+0x00
	void UpdateProjectionMatrices() override;                             // vtable+0x04
	~GolCamera() override;                                                // vtable+0x08
	void SetViewport(Rect* p_rect) override;                              // vtable+0x0c
	void SetViewBounds(const GolVec4* p_bounds) override;                 // vtable+0x10
	void GetViewMatrix(GolMatrix4* p_dest) override;                      // vtable+0x14
	void GetViewScreenProjection(GolMatrix4* p_dest) override;            // vtable+0x18
	void TransformToView(const GolVec3* p_src, GolVec3* p_dest) override; // vtable+0x1c
	void ProjectToScreen(const GolVec3* p_src, GolVec3* p_dest) override; // vtable+0x20
	using GolCameraBase::ProjectSphere;                                   // vtable+0x24
	void UpdateMatrices() override;                                       // vtable+0x28

	// SYNTHETIC: GOLDP 0x10017a60
	// GolCamera::`vector deleting destructor'

	GolTransform* GetTransform() { return m_transform; }

protected:
	friend class GolD3DRenderDevice;

	void AttachToRenderer(GolD3DRenderDevice*);
	void BuildProjection(
		GolMatrix4* p_matrix,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY,
		LegoFloat p_offsetX,
		LegoFloat p_offsetY
	);
	void BuildD3DViewport(D3DVIEWPORT2* p_viewport);

	GolCameraMatrices m_cameraMatrices; // 0x120
	GolD3DRenderDevice* m_renderer;     // 0x340
};

#endif // GOLCAMERA_H
