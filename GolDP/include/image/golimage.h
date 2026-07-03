#ifndef GOLDP_UTOPIANPAN_H
#define GOLDP_UTOPIANPAN_H

#include "decomp.h"
#include "golpalettedtexture.h"
#include "image/goltiledtexture.h"
#include "types.h"

class GolD3DRenderDevice;
class GolSoftwareMaterial;
class GolSurfaceFormat;
class GolTexture;
class GolD3DTexture;
class GolRenderDevice;
struct Rect;

// SIZE 0xa4
// VTABLE: GOLDP 0x10056340
class GolImage : public GolTiledTexture {
public:
	// SIZE 0x09
	struct UtopianPanImageName {
		union {
			FourBytes m_name[2]; // 0x00
			LegoChar m_chars[9]; // 0x00
		};
	};

	GolImage();

	void VTable0x00() override;                                                                   // vtable+0x00
	void VTable0x04() override;                                                                   // vtable+0x04
	void VTable0x08() override;                                                                   // vtable+0x08
	void VTable0x0c(LegoU32 p_row, LegoU32 p_column, GolSurfaceFormat* p_textureFormat) override; // vtable+0x0c
	void VTable0x10() override;                                                                   // vtable+0x10
	~GolImage() override;                                                                         // vtable+0x14
	void Reset() override;                                                                        // vtable+0x18
	GolD3DTexture* VTable0x1c(LegoU32 p_row, LegoU32 p_column) override;                          // vtable+0x1c

	void FUN_100051c0();
	void FUN_10005210();
	void FUN_10005440(GolRenderDevice* p_renderer, GolSoftwareMaterial* p_material, GolTexture* p_texture);
	void FUN_100054d0(GolD3DRenderDevice*, undefined4, Rect*, Rect* p_clipRect);
	void FUN_10005510(GolD3DRenderDevice*, undefined4, Rect*, Rect*, Rect* p_clipRect);
	void FUN_10005b00();

	// SYNTHETIC: GOLDP 0x10005e60
	// GolImage::`vector deleting destructor'

protected:
	GolD3DTexture* m_unk0x50;       // 0x50
	GolSoftwareMaterial* m_unk0x54; // 0x54
	GolPalettedTexture m_unk0x58;   // 0x58
};

#endif // GOLDP_UTOPIANPAN_H
