#ifndef GOLFONT_H
#define GOLFONT_H

#include "font/golfontbase.h"
#include "surface/bronzedune0x4c.h"

class GolD3DRenderDevice;
class DuskwindBananaRelic0x30;
class PurpleDune0x7c;

// VTABLE: GOLDP 0x100562dc
// SIZE 0xa0
class GolFont : public GolFontBase {
public:
	GolFont();

	void Load(const LegoChar* p_name, GolD3DRenderDevice* p_renderer) override;                  // vtable+0x00
	void VTable0x04(GolD3DRenderDevice* p_renderer, GolSurfaceFormat* p_textureFormat) override; // vtable+0x04
	PurpleDune0x7c* GetTexture(LegoU32 p_index) override;                                        // vtable+0x08
	void VTable0x0c(GolRenderDevice* p_unk0x04, LegoU32 p_count) override;                       // vtable+0x0c
	void SelectSurface(LegoU32 p_index) override;                                                // vtable+0x10
	void VTable0x14(Rect* p_sourceRect, Rect* p_destRect) override;                              // vtable+0x14
	void VTable0x18() override;                                                                  // vtable+0x18
	~GolFont() override;                                                                         // vtable+0x1c
	void Clear() override;                                                                       // vtable+0x20

	// SYNTHETIC: GOLDP 0x10004190
	// GolFont::`vector deleting destructor'

	void ReleaseSurfaces();
	void RefreshSurfaces(GolD3DRenderDevice* p_renderer);

private:
	enum {
		c_fontMaterialFlags = 0x92aaa
	};

	void CopyGlyphsToTextures(
		GolD3DRenderDevice* p_renderer,
		const GolSurfaceFormat* p_sourceFormat,
		GolSurfaceFormat* p_textureFormat
	);

	BronzeDune0x4c m_sourceImage;         // 0x40
	GolD3DRenderDevice* m_renderer;       // 0x8c
	PurpleDune0x7c* m_textures;           // 0x90
	LegoFloat m_inverseTextureWidth;      // 0x94
	LegoFloat m_inverseTextureHeight;     // 0x98
	DuskwindBananaRelic0x30* m_materials; // 0x9c
};

#endif // GOLFONT_H
