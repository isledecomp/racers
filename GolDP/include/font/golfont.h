#ifndef GOLFONT_H
#define GOLFONT_H

#include "golfontbase.h"
#include "golpalettedtexture.h"

class GolD3DRenderDevice;
class GolSoftwareMaterial;
class GolD3DTexture;

// VTABLE: GOLDP 0x100562dc
// SIZE 0xa0
class GolFont : public GolFontBase {
public:
	GolFont();

	void Load(const LegoChar* p_name, GolD3DRenderDevice* p_renderer) override;                      // vtable+0x00
	void CreateSurfaces(GolD3DRenderDevice* p_renderer, GolSurfaceFormat* p_textureFormat) override; // vtable+0x04
	GolD3DTexture* GetTexture(LegoU32 p_index) override;                                             // vtable+0x08
	void BeginDrawing(GolRenderDevice* p_renderer, LegoU32 p_count) override;                        // vtable+0x0c
	void SelectSurface(LegoU32 p_index) override;                                                    // vtable+0x10
	void DrawGlyph(Rect* p_sourceRect, Rect* p_destRect) override;                                   // vtable+0x14
	void EndDrawing() override;                                                                      // vtable+0x18
	~GolFont() override;                                                                             // vtable+0x1c
	void Clear() override;                                                                           // vtable+0x20

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

	GolPalettedTexture m_sourceImage; // 0x40
	GolD3DRenderDevice* m_renderer;   // 0x8c
	GolD3DTexture* m_textures;        // 0x90
	LegoFloat m_inverseTextureWidth;  // 0x94
	LegoFloat m_inverseTextureHeight; // 0x98
	GolSoftwareMaterial* m_materials; // 0x9c
};

#endif // GOLFONT_H
