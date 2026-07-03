#ifndef GOLSURFACE_H
#define GOLSURFACE_H

#include "decomp.h"
#include "golsurfaceformat.h"
#include "render/rectangle.h"
#include "types.h"

class GolDirectDrawPalette;
class GolPaletteBase;
class GolD3DRenderDevice;

// VTABLE: GOLDP 0x10056d3c
// VTABLE: LEGORACERS 0x004af4f0
// SIZE 0x30
class GolSurface {
public:
	enum {
		c_lockRequestRead = 0x01,
		c_lockRequestWrite = 0x02,
		c_lockFlagLocked = 0x02,
		c_lockFlagFlipPending = 0x04,
		c_lockFlagRead = 0x08,
		c_lockFlagWrite = 0x10,
		c_lockStateMask = c_lockFlagLocked | c_lockFlagRead | c_lockFlagWrite
	};

	GolSurface();

	virtual ~GolSurface();                                                                  // vtable+0x00
	virtual void LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags);          // vtable+0x04
	virtual void UnlockPixels();                                                            // vtable+0x08
	virtual void LockAuxPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags);       // vtable+0x0c
	virtual void UnlockAuxPixels();                                                         // vtable+0x10
	virtual void Present(undefined4);                                                       // vtable+0x14
	virtual void FinishPendingFlip();                                                       // vtable+0x18
	virtual GolPaletteBase* GetPalette();                                                   // vtable+0x1c
	virtual void Fill(LegoU32 p_color);                                                     // vtable+0x20
	virtual void Blit(LegoU32 p_x, LegoU32 p_y, GolSurface* p_source, Rect* p_sourceRect);  // vtable+0x24
	virtual void BlitStretched(Rect* p_destRect, GolSurface* p_source, Rect* p_sourceRect); // vtable+0x28
	virtual void CopyFromDisplay();                                                         // vtable+0x2c

	// SYNTHETIC: GOLDP 0x1001cf40
	// SYNTHETIC: LEGORACERS 0x004084d0
	// GolSurface::`scalar deleting destructor'

	LegoU16 GetPixelFlags() const { return m_pixelFlags; }
	LegoU16 GetWidth() const { return m_width; }
	LegoU16 GetHeight() const { return m_height; }
	LegoU32 GetWidthU32() const { return m_width; }
	LegoU32 GetHeightU32() const { return m_height; }
	GolSurfaceFormat& GetTextureFormat() { return m_textureFormat; }
	const GolSurfaceFormat& GetTextureFormat() const { return m_textureFormat; }

protected:
	friend class GolD3DRenderDevice;

	GolSurfaceFormat m_textureFormat; // 0x04
	LegoU8* m_pixels;                 // 0x1c
	LegoU8* m_auxPixels;              // 0x20
	LegoU16 m_pitch;                  // 0x24
	LegoU16 m_pixelFlags;             // 0x26
	LegoU16 m_auxFlags;               // 0x28
	LegoU16 m_width;                  // 0x2a
	LegoU16 m_height;                 // 0x2c
};

#endif // GOLSURFACE_H
