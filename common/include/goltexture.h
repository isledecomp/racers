#ifndef GOLTEXTURE_H
#define GOLTEXTURE_H

#include "golsurface.h"
#include "surface/color.h"

class GolRenderDevice;
class GolImgFile;
class GolTextureList;
class GolTiledTexture;

// VTABLE: GOLDP 0x1005766c
// VTABLE: LEGORACERS 0x004af928
// SIZE 0x38
class GolTexture : public GolSurface {
public:
	enum {
		c_textureFlagMipmapped = 0x01,
		c_textureFlagBit1 = 0x02,
		c_textureFlagFlipVertically = 0x04,
		c_textureFlagBmpSource = 0x08,
		c_textureFlagTgaSource = 0x10,
		c_textureFlagColorKeyed = 0x20,
		c_textureFlagBit6 = 0x40,
		c_textureFlagBlackColorKey = 0x80,
		c_textureFlagBit8 = 0x100,
		c_textureFlagBit9 = 0x200,
		c_textureFlagColorKeyInAlpha = 0x400,
		c_textureFlagColorKeyDirty = 0x800,
	};
	GolTexture();

	virtual void LoadFromImgFile(GolRenderDevice& p_renderer, GolImgFile* p_source); // vtable+0x30
	virtual void Allocate(
		GolRenderDevice& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) = 0;                      // vtable+0x34
	virtual void Destroy() = 0; // vtable+0x38

	LegoU16 GetMipmapCount() const { return m_mipmapCount; }
	LegoU16 GetTextureFlags() const { return m_textureFlags; }
	const ColorRGBA& GetColorKey() const { return m_colorKey; }
	void SetTextureFlags(LegoU16 p_flags) { m_textureFlags = p_flags; }
	void SetTextureDefinition(LegoU16 p_mipmapCount, LegoU16 p_textureFlags, const ColorRGBA& p_colorKey)
	{
		m_mipmapCount = p_mipmapCount;
		p_textureFlags |= c_textureFlagColorKeyDirty;
		m_colorKey = p_colorKey;
		m_colorKey.m_alp = 0;
		m_textureFlags = p_textureFlags;
	}
	void SetSourceTextureDefinition(LegoU16 p_mipmapCount, LegoU16 p_textureFlags, const ColorRGBA& p_colorKey)
	{
		m_textureFlags = p_textureFlags;
		m_mipmapCount = p_mipmapCount;
		p_textureFlags |= c_textureFlagColorKeyDirty;
		m_textureFlags = p_textureFlags;
		m_colorKey = p_colorKey;
		m_colorKey.m_alp = 0;
	}
	void SetColorKey(const ColorRGBA& p_colorKey)
	{
		m_textureFlags |= c_textureFlagColorKeyDirty;
		m_colorKey = p_colorKey;
		m_colorKey.m_alp = 0;
	}

	// SYNTHETIC: GOLDP 0x10004470 FOLDED
	// SYNTHETIC: LEGORACERS 0x00408bd0 FOLDED
	// GolTexture::~GolTexture

	// SYNTHETIC: GOLDP 0x1002f380 FOLDED
	// SYNTHETIC: LEGORACERS 0x00415c40
	// GolTexture::`scalar deleting destructor'

protected:
	friend class GolTextureList;
	friend class GolTiledTexture;

	ColorRGBA m_colorKey;     // 0x30
	undefined2 m_mipmapCount; // 0x34
	LegoU16 m_textureFlags;   // 0x36
};

#endif // GOLTEXTURE_H
