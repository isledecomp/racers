#ifndef GOLD3DTEXTURE_H
#define GOLD3DTEXTURE_H

#include "golname.h"
#include "golsurfaceformat.h"
#include "goltexture.h"
#include "goltexturepalette.h"
#include "surface/mipmaplevel.h"

#include <d3d.h>
#include <ddraw.h>
#include <string.h>

class GolPaletteBase;
class GolCommonDrawState;
class GolImgFile;
class GolTextureList;

// VTABLE: GOLDP 0x1005681c
// SIZE 0x7c
class GolD3DTexture : public GolTexture {
public:
	GolD3DTexture();
	~GolD3DTexture() override; // vtable+0x00

	void LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags) override;   // vtable+0x04
	void UnlockPixels() override;                                                     // vtable+0x08
	GolPaletteBase* GetPalette() override;                                            // vtable+0x1c
	void LoadFromImgFile(GolRenderDevice& p_renderer, GolImgFile* p_source) override; // vtable+0x30
	void Allocate(
		GolRenderDevice& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) override;              // vtable+0x34
	void Destroy() override; // vtable+0x38

	void ApplyColorKey();
	void AllocateDeviceOnly(
		GolD3DRenderDevice& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	);
	void UploadPixels();
	void GenerateMipmaps();
	void ReleaseDeviceObjects();
	void RestoreDeviceObjects(GolD3DRenderDevice& p_renderer);
	void CreateDeviceObjects(GolD3DRenderDevice& p_renderer);
	void CreateDirectDrawSurface(GolCommonDrawState* p_drawState, GolD3DRenderDevice& p_renderer);
	void CreateMipmapBuffers(GolD3DRenderDevice& p_renderer);

	LPDIRECT3DTEXTURE2 GetDirect3DTexture() const { return m_d3dTexture; }
	MipmapLevel* GetMipmapLevel(LegoU32 p_index) { return m_mipmaps == NULL ? NULL : &m_mipmaps[p_index]; }
	const MipmapLevel* GetMipmapLevel(LegoU32 p_index) const { return m_mipmaps == NULL ? NULL : &m_mipmaps[p_index]; }
	const GolName& GetName() const { return m_name; }
	void SetName(const GolName& p_name) { ::memcpy(m_name, p_name, sizeof(m_name)); }
	void SetNameFromBuffer(const LegoChar* p_name) { ::memcpy(m_name, p_name, sizeof(m_name)); }
	void CopySourceTextureDefinitionFrom(const GolD3DTexture* p_texture)
	{
		::memcpy(m_name, p_texture->m_name, sizeof(m_name));
		m_textureFlags = p_texture->m_textureFlags;
		m_mipmapCount = p_texture->m_mipmapCount;
		ColorRGBA colorKey = p_texture->m_colorKey;
		m_textureFlags |= GolTexture::c_textureFlagColorKeyDirty;
		m_colorKey = colorKey;
		m_colorKey.m_alp = 0;
	}
	void CopyNameToBuffer(LegoChar* p_buffer) const
	{
		::memcpy(p_buffer, m_name, sizeof(m_name));
		p_buffer[sizeof(m_name)] = '\0';
	}

	MipmapLevel* GetMipmaps() { return m_mipmaps; }

	// SYNTHETIC: GOLDP 0x10004aa0
	// GolD3DTexture::`vector deleting destructor'

private:
	friend class GolTextureList;

	GolName m_name;                         // 0x38
	GolPaletteBase* m_palette;              // 0x40
	MipmapLevel* m_mipmaps;                 // 0x44
	LPDIRECTDRAWSURFACE4 m_surface;         // 0x48
	LPDIRECT3DTEXTURE2 m_d3dTexture;        // 0x4c
	GolTexturePalette m_sourcePalette;      // 0x50
	GolSurfaceFormat m_deviceTextureFormat; // 0x5c
	undefined4 m_deviceWidth;               // 0x74
	undefined4 m_deviceHeight;              // 0x78
};

#endif // GOLD3DTEXTURE_H
