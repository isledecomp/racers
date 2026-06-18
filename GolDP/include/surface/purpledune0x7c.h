#ifndef PURPLEDUNE0x7C_H
#define PURPLEDUNE0x7C_H

#include "golname.h"
#include "golsurfaceformat.h"
#include "surface/bronzedunebag0xc.h"
#include "surface/golddune0x38.h"

#include <d3d.h>
#include <ddraw.h>
#include <string.h>

class GolPaletteBase;
class GolCommonDrawState;
class GolImgFile;

// VTABLE: GOLDP 0x1005681c
// SIZE 0x7c
class PurpleDune0x7c : public GoldDune0x38 {
public:
	// SIZE 0x18
	struct MipmapLevel {
		LegoU8* m_pixels;       // 0x00
		LegoU32 m_pitch;        // 0x04
		LegoU32 m_width;        // 0x08
		LegoU32 m_height;       // 0x0c
		LegoU8 m_bitsPerPixel;  // 0x10
		LegoU8 m_unk0x11;       // 0x11
		LegoU8 m_bytesPerPixel; // 0x12
		LegoU8 m_unk0x13;       // 0x13
		LegoU16* m_paletteData; // 0x14
	};

	PurpleDune0x7c();
	~PurpleDune0x7c() override; // vtable+0x00

	void LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags) override; // vtable+0x04
	void UnlockPixels() override;                                                   // vtable+0x08
	GolPaletteBase* GetPalette() override;                                          // vtable+0x1c
	void VTable0x30(GolRenderDevice& p_renderer, GolImgFile* p_source) override;    // vtable+0x30
	void VTable0x34(
		GolRenderDevice& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) override;                 // vtable+0x34
	void VTable0x38() override; // vtable+0x38

	void FUN_10015fb0();
	void FUN_10015d00(
		GolD3DRenderDevice& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	);
	void FUN_10016100();
	void FUN_10016260();
	void FUN_10016380();
	void FUN_10016440(GolD3DRenderDevice& p_renderer);
	void FUN_10016460(GolD3DRenderDevice& p_renderer);
	void FUN_100165c0(GolCommonDrawState* p_drawState, GolD3DRenderDevice& p_renderer);
	void FUN_100168c0(GolD3DRenderDevice& p_renderer);

	LPDIRECT3DTEXTURE2 GetDirect3DTexture() const { return m_d3dTexture; }
	MipmapLevel* GetMipmapLevel(LegoU32 p_index) { return m_mipmaps == NULL ? NULL : &m_mipmaps[p_index]; }
	const MipmapLevel* GetMipmapLevel(LegoU32 p_index) const { return m_mipmaps == NULL ? NULL : &m_mipmaps[p_index]; }
	const GolName& GetName() const { return m_name; }
	void SetName(const GolName& p_name) { ::memcpy(m_name, p_name, sizeof(m_name)); }
	void SetNameFromBuffer(const LegoChar* p_name) { ::memcpy(m_name, p_name, sizeof(m_name)); }
	void CopySourceTextureDefinitionFrom(const PurpleDune0x7c* p_texture)
	{
		::memcpy(m_name, p_texture->m_name, sizeof(m_name));
		m_unk0x36 = p_texture->m_unk0x36;
		m_unk0x34 = p_texture->m_unk0x34;
		ColorRGBA colorKey = p_texture->m_colorKey;
		m_unk0x36 |= GoldDune0x38::c_unk0x36Bit11;
		m_colorKey = colorKey;
		m_colorKey.m_alp = 0;
	}
	void CopyNameToBuffer(LegoChar* p_buffer) const
	{
		::memcpy(p_buffer, m_name, sizeof(m_name));
		p_buffer[sizeof(m_name)] = '\0';
	}

	// SYNTHETIC: GOLDP 0x10004aa0
	// PurpleDune0x7c::`vector deleting destructor'

private:
	GolName m_name;                    // 0x38
	GolPaletteBase* m_palette;         // 0x40
	MipmapLevel* m_mipmaps;            // 0x44
	LPDIRECTDRAWSURFACE4 m_surface;    // 0x48
	LPDIRECT3DTEXTURE2 m_d3dTexture;   // 0x4c
	BronzeDuneBag0xc m_unk0x50;        // 0x50
	GolSurfaceFormat m_textureFormat2; // 0x5c
	undefined4 m_unk0x74;              // 0x74
	undefined4 m_unk0x78;              // 0x78
};

#endif // PURPLEDUNE0x7C_H
