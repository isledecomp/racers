#ifndef GOLIMAGE_H
#define GOLIMAGE_H

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
	GolImage();

	void AllocateTileWidths() override;                                                           // vtable+0x00
	void AllocateTileHeights() override;                                                          // vtable+0x04
	void AllocateTileArrays() override;                                                           // vtable+0x08
	void CreateTile(LegoU32 p_row, LegoU32 p_column, GolSurfaceFormat* p_textureFormat) override; // vtable+0x0c
	void Load() override;                                                                         // vtable+0x10
	~GolImage() override;                                                                         // vtable+0x14
	void Reset() override;                                                                        // vtable+0x18
	GolD3DTexture* GetTile(LegoU32 p_row, LegoU32 p_column) override;                             // vtable+0x1c

	void DestroyTiles();
	void RebuildTiles();
	void CreateTileMaterial(GolRenderDevice* p_renderer, GolSoftwareMaterial* p_material, GolTexture* p_texture);
	void Draw(GolD3DRenderDevice*, undefined4, Rect*, Rect* p_clipRect);
	void DrawStretched(GolD3DRenderDevice*, undefined4, Rect*, Rect*, Rect* p_clipRect);
	void UploadTiles();

	// SYNTHETIC: GOLDP 0x10005e60
	// GolImage::`vector deleting destructor'

protected:
	GolD3DTexture* m_texture;         // 0x50
	GolSoftwareMaterial* m_materials; // 0x54
	GolPalettedTexture m_surface;     // 0x58
};

#endif // GOLIMAGE_H
