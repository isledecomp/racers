#ifndef GOLD3DRENDERSURFACE_H
#define GOLD3DRENDERSURFACE_H

#include "decomp.h"
#include "surface/golrendertarget.h"

class GolD3DRenderDevice;

// VTABLE: GOLDP 0x100566d0
// SIZE 0x5c
class GolD3DRenderSurface : public GolRenderTarget {
public:
	GolD3DRenderSurface();
	~GolD3DRenderSurface() override;   // vtable+0x00
	void Present(undefined4) override; // vtable+0x14
	void Destroy() override;           // vtable+0x34

	void FUN_10013600(GolD3DRenderDevice*, undefined2, undefined2);

	friend class GolD3DRenderDevice;

	// SYNTHETIC: GOLDP 0x10013560
	// GolD3DRenderSurface::`scalar deleting destructor'

private:
	void FUN_100136a0(GolD3DRenderDevice*);
	void ReleaseResources();

	GolD3DRenderSurface* m_next; // 0x58
};

#endif // GOLD3DRENDERSURFACE_H
