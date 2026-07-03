#ifndef GOLRENDERTARGET_H
#define GOLRENDERTARGET_H

#include "compat.h"
#include "device/goldirectdrawpalette.h"
#include "surface/goldepthbuffer.h"
#include "surface/goldisplaysurface.h"

class GolD3DRenderDevice;

// VTABLE: GOLDP 0x1005627c
// SIZE 0x58
class GolRenderTarget : public GolDisplaySurface {
public:
	GolRenderTarget();
	~GolRenderTarget() override;                                                       // vtable+0x00
	void LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags) override;    // vtable+0x04
	void UnlockPixels() override;                                                      // vtable+0x08
	void LockAuxPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags) override; // vtable+0x0c
	void UnlockAuxPixels() override;                                                   // vtable+0x10
	void Present(undefined4) override;                                                 // vtable+0x14
	void FinishPendingFlip() override;                                                 // vtable+0x18
	GolPaletteBase* GetPalette() override;                                             // vtable+0x1c
	void Fill(LegoU32 p_color) override;                                               // vtable+0x20
	void BlitStretched(Rect* p_destRect, GolSurface* p_source,
					   Rect* p_sourceRect) override; // vtable+0x28
	void CopyFromDisplay() override;                 // vtable+0x2c
	void Create(
		GolDrawState* p_drawState,
		undefined4 p_width,
		undefined4 p_height,
		undefined4 p_bpp
	) override;              // vtable+0x30
	void Destroy() override; // vtable+0x34

	// SYNTHETIC: GOLDP 0x10003170
	// GolRenderTarget::`scalar deleting destructor'

	LPDIRECTDRAWSURFACE4 GetDisplaySurface() const { return m_displaySurface; }
	LPDIRECTDRAWSURFACE4 GetRenderSurface() const { return m_renderSurface; }

protected:
	friend class GolDepthBuffer;
	friend class GolD3DRenderDevice;

	LegoS32 AttachDepthBuffer(GolDepthBuffer* p_depthBuffer);
	void DetachDepthBuffer(GolDepthBuffer* p_depthBuffer);
	void SetDisplayPalette(GolD3DRenderDevice* p_renderer);

	GolDirectDrawPalette m_palette;        // 0x38
	GolDrawState* m_drawState;             // 0x44
	LPDIRECTDRAWSURFACE4 m_displaySurface; // 0x48
	LPDIRECTDRAWSURFACE4 m_renderSurface;  // 0x4c
	LPDIRECTDRAWCLIPPER m_clipper;         // 0x50
	GolDepthBuffer* m_depthBuffer;         // 0x54
};

#endif // GOLRENDERTARGET_H
