#include "font/golfont.h"

#include "decomp.h"
#include "device/golpalettebase.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golimgfile.h"
#include "goltgafile.h"
#include "material/duskwindbananarelic0x30.h"
#include "render/gold3drenderdevice.h"
#include "render/rectangle.h"
#include "surface/purpledune0x7c.h"
#include "surface/silverdune0x30.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolFont, 0xa0)

// GLOBAL: GOLDP 0x10062568
static GolImgFile g_unk0x10062568;

extern SilverDune0x30* g_fontSourceImage;

extern GolTgaFile g_unk0x10063ca0;

extern GolBmpFile g_unk0x10064280;

extern const ColorRGBA g_unk0x10057668;

// FUNCTION: GOLDP 0x100043d0
GolFont::GolFont()
{
	m_textures = NULL;
	m_materials = NULL;
	m_renderer = NULL;
}

// FUNCTION: GOLDP 0x10004480
GolFont::~GolFont()
{
	Clear();
}

// FUNCTION: GOLDP 0x10004520
void GolFont::Clear()
{
	m_sourceImage.VTable0x38();
	ReleaseSurfaces();
	GolFontBase::Clear();
}

// FUNCTION: GOLDP 0x10004570
void GolFont::Load(const LegoChar* p_name, GolD3DRenderDevice* p_renderer)
{
	GolSurfaceFormat sourceFormat;

	GolImgFile* imageFile = &g_unk0x10063ca0;
	if (!(m_flags & c_flagBit4)) {
		imageFile = &g_unk0x10064280;
	}

	imageFile->VTable0x08(p_name);
	LegoU32 sourceHeight = imageFile->GetHeight();
	sourceFormat = imageFile->GetTextureFormat();
	m_fontHeight = sourceHeight;

	if (sourceFormat.m_paletteMask && sourceFormat.m_bitsPerPixel == 4) {
		::memset(&sourceFormat, 0, sizeof(sourceFormat));
		sourceFormat.m_bitsPerPixel = 8;
		sourceFormat.m_paletteMask = 0x00ff;
	}

	LegoU32 sourceWidth = imageFile->GetWidth();
	g_fontSourceImage = &m_sourceImage;
	m_sourceImage.VTable0x34(*p_renderer, sourceFormat, sourceWidth, m_fontHeight);
	imageFile->VTable0x20(&m_sourceImage, m_flags & c_flagBit2, NULL);
	imageFile->Destroy();

	ScanGlyphs(p_name);

	GolSurfaceFormat textureFormat;
	g_fontSourceImage = &m_sourceImage;
	GolSurfaceFormat surfaceFormat = m_sourceImage.GetTextureFormat();
	LegoU32 selectFlags = m_flags & c_flagBit5;
	p_renderer->SelectTextureFormat(surfaceFormat, &textureFormat, selectFlags);
	PackGlyphTextures(p_renderer, &textureFormat);
	VTable0x04(p_renderer, &textureFormat);
	CopyGlyphsToTextures(p_renderer, &surfaceFormat, &textureFormat);

	::qsort(m_glyphs, m_glyphCount, sizeof(Glyph), GolFontBase::CompareGlyphChars);
}

// FUNCTION: GOLDP 0x100046e0
void GolFont::ReleaseSurfaces()
{
	if (m_materials != NULL) {
		delete[] m_materials;
		m_materials = NULL;
	}

	if (m_textures != NULL) {
		delete[] m_textures;
		m_textures = NULL;
	}
}

// FUNCTION: GOLDP 0x10004720
void GolFont::RefreshSurfaces(GolD3DRenderDevice* p_renderer)
{
	GolSurfaceFormat textureFormat;

	g_fontSourceImage = &m_sourceImage;
	GolSurfaceFormat sourceFormat = m_sourceImage.GetTextureFormat();
	p_renderer->SelectTextureFormat(sourceFormat, &textureFormat, m_flags & c_flagBit5);
	PackGlyphTextures(p_renderer, &textureFormat);
	VTable0x04(p_renderer, &textureFormat);
	CopyGlyphsToTextures(p_renderer, &sourceFormat, &textureFormat);
}

// STUB: GOLDP 0x100047b0
void GolFont::VTable0x04(GolD3DRenderDevice* p_renderer, GolSurfaceFormat* p_textureFormat)
{
	STUB(0x100047b0);

	m_textures = new PurpleDune0x7c[m_surfaceCount];
	if (m_textures == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_materials = new DuskwindBananaRelic0x30[m_surfaceCount];
	if (m_materials == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;
	PurpleDune0x7c* texture = m_textures;
	DuskwindBananaRelic0x30* material = m_materials;

	for (; i < m_surfaceCount - 1; i++) {
		if (m_flags & c_flagBit5) {
			texture->SetColorKey(m_colorKey);
		}

		texture->FUN_10015d00(*p_renderer, *p_textureFormat, m_maxTextureWidth, m_maxTextureHeight);

		DuskWindBananaRelicParams params;
		params.m_unk0x00 = c_fontMaterialFlags;
		params.m_unk0x04 = texture;
		params.m_unk0x08.m_unk0x0 = 0xff;
		params.m_unk0x08.m_unk0x1 = 0xff;
		params.m_unk0x08.m_unk0x2 = 0xff;
		params.m_unk0x08.m_unk0x3 = 0xff;
		params.m_unk0x0c.m_unk0x0 = 0xff;
		params.m_unk0x0c.m_unk0x1 = 0xff;
		params.m_unk0x0c.m_unk0x2 = 0xff;
		params.m_unk0x0c.m_unk0x3 = 0xff;
		params.m_unk0x10 = 2;
		params.m_unk0x11 = 0;
		params.m_unk0x12 = 1;
		params.m_unk0x13 = 0;

		material->FUN_100257e0(p_renderer, params);
		material->FUN_10006320(*p_renderer);

		texture++;
		material++;
	}

	i = m_surfaceCount - 1;
	texture = &m_textures[i];
	material = &m_materials[i];

	if (m_flags & c_flagBit5) {
		texture->SetColorKey(m_colorKey);
	}

	texture->FUN_10015d00(*p_renderer, *p_textureFormat, m_textureWidth, m_textureHeight);
	texture->SetName(m_name);

	DuskWindBananaRelicParams params;
	params.m_unk0x00 = c_fontMaterialFlags;
	params.m_unk0x04 = texture;
	params.m_unk0x08.m_unk0x0 = 0xff;
	params.m_unk0x08.m_unk0x1 = 0xff;
	params.m_unk0x08.m_unk0x2 = 0xff;
	params.m_unk0x08.m_unk0x3 = 0xff;
	params.m_unk0x0c.m_unk0x0 = 0xff;
	params.m_unk0x0c.m_unk0x1 = 0xff;
	params.m_unk0x0c.m_unk0x2 = 0xff;
	params.m_unk0x0c.m_unk0x3 = 0xff;
	params.m_unk0x10 = 2;
	params.m_unk0x11 = 0;
	params.m_unk0x12 = 1;
	params.m_unk0x13 = 0;

	material->FUN_100257e0(p_renderer, params);
	material->FUN_10006320(*p_renderer);
}

// FUNCTION: GOLDP 0x10004b60
PurpleDune0x7c* GolFont::GetTexture(LegoU32 p_index)
{
	return &m_textures[p_index];
}

// FUNCTION: GOLDP 0x10004b80
void GolFont::VTable0x0c(GolRenderDevice* p_renderer, LegoU32)
{
	m_renderer = static_cast<GolD3DRenderDevice*>(p_renderer);
}

// FUNCTION: GOLDP 0x10004b90
void GolFont::SelectSurface(LegoU32 p_index)
{
	LegoU32 index = p_index;
	DuskwindBananaRelic0x30* material = &m_materials[index];
	(m_renderer->*m_renderer->m_unk0xc876c)(material);

	GoldDune0x38* texture = &m_textures[index];
	m_renderer->FUN_1000ac00(texture);
	m_inverseTextureWidth = 1.0f / static_cast<LegoFloat>(m_textures[index].GetWidth());
	m_inverseTextureHeight = 1.0f / static_cast<LegoFloat>(m_textures[index].GetHeight());
}

// STUB: GOLDP 0x10004c20
void GolFont::VTable0x14(Rect* p_sourceRect, Rect* p_destRect)
{
	STUB(0x10004c20);

	LegoS32 sourceBottom = p_sourceRect->m_bottom - 1;
	D3DTLVERTEX vertices[4];

	vertices[0].sz = 0.0f;
	vertices[1].sz = 0.0f;
	vertices[2].sz = 0.0f;

	vertices[0].sx = static_cast<LegoFloat>(p_destRect->m_left);
	vertices[3].sz = 0.0f;
	vertices[0].rhw = 1.0f;
	vertices[0].sy = static_cast<LegoFloat>(p_destRect->m_top);
	vertices[1].rhw = 1.0f;
	vertices[2].rhw = 1.0f;
	vertices[1].sx = vertices[0].sx;
	vertices[1].sy = static_cast<LegoFloat>(p_destRect->m_bottom);
	vertices[2].sx = static_cast<LegoFloat>(p_destRect->m_right);
	vertices[3].sx = vertices[2].sx;
	vertices[2].sy = vertices[0].sy;
	vertices[3].rhw = 1.0f;
	vertices[3].sy = vertices[1].sy;

	vertices[0].tu =
		static_cast<LegoFloat>(p_sourceRect->m_left) * m_inverseTextureWidth + (m_inverseTextureWidth * 0.25f);
	vertices[0].tv = static_cast<LegoFloat>(p_sourceRect->m_top) * m_inverseTextureHeight;
	vertices[1].tu = vertices[0].tu;
	vertices[1].tv = static_cast<LegoFloat>(sourceBottom) * m_inverseTextureHeight;
	vertices[2].tu =
		static_cast<LegoFloat>(p_sourceRect->m_right) * m_inverseTextureWidth + (m_inverseTextureWidth * 0.25f);
	vertices[2].tv = vertices[0].tv;
	vertices[3].tu = vertices[2].tu;
	vertices[3].tv = vertices[1].tv;

	LegoU32 color =
		(m_color.m_alp << 24) | (m_color.m_red << 16) | (m_color.m_grn << 8) | static_cast<LegoU32>(m_color.m_blu);
	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;

	vertices[0].specular = 0xffffffff;
	vertices[1].specular = 0xffffffff;
	vertices[2].specular = 0xffffffff;
	vertices[3].specular = 0xffffffff;

	m_renderer->FUN_10009fd0(vertices, sizeOfArray(vertices));
}

// FUNCTION: GOLDP 0x10004d70
void GolFont::CopyGlyphsToTextures(
	GolD3DRenderDevice* p_renderer,
	const GolSurfaceFormat* p_sourceFormat,
	GolSurfaceFormat* p_textureFormat
)
{
	GolFont* font = this;
	LegoU32 currentSurface = 0;
	PurpleDune0x7c* texture = font->GetTexture(currentSurface);

	ColorRGBA* paletteEntries;
	LegoU32 paletteSize;
	if (p_sourceFormat->m_paletteMask) {
		paletteEntries = font->m_sourceImage.GetPaletteEntries();
		paletteSize = font->m_sourceImage.GetPaletteSize();
	}
	else {
		paletteEntries = NULL;
		paletteSize = 0;
	}

	ColorRGBA* colorKey;
	if (font->m_flags & c_flagBit5) {
		if (p_renderer->GetFlags() & GolRenderDevice::c_flagBit9) {
			g_unk0x10062568.SetUnk0x0a0(g_unk0x10057668);
		}
		else {
			g_unk0x10062568.SetUnk0x0a0(font->m_colorKey);
		}
		colorKey = &font->m_colorKey;
	}
	else {
		colorKey = NULL;
	}

	LegoU8* sourcePixels;
	LegoU32 sourcePitch;
	font->m_sourceImage.LockPixels(&sourcePixels, &sourcePitch, SilverDune0x30::c_lockRequestRead);

	LegoU8* destPixels;
	LegoU32 destPitch;
	texture->LockPixels(&destPixels, &destPitch, SilverDune0x30::c_lockRequestWrite);

	for (LegoU32 i = 0; i < font->m_glyphCount; i++) {
		if (font->m_glyphs[i].m_surfaceIndex != currentSurface) {
			texture->UnlockPixels();
			currentSurface = font->m_glyphs[i].m_surfaceIndex;
			texture = font->GetTexture(currentSurface);
			texture->LockPixels(&destPixels, &destPitch, SilverDune0x30::c_lockRequestWrite);
		}

		g_unk0x10062568.FUN_100226c0(
			*p_sourceFormat,
			font->m_glyphs[i].m_width,
			font->m_fontHeight,
			sourcePitch,
			paletteEntries,
			paletteSize
		);

		LegoU8* source =
			sourcePixels +
			((static_cast<LegoU32>(p_sourceFormat->m_bitsPerPixel) * font->m_glyphs[i].m_sourceX + 7) >> 3);
		LegoU8* dest =
			destPixels + destPitch * font->m_glyphs[i].m_textureY +
			((static_cast<LegoU32>(p_textureFormat->m_bitsPerPixel) * font->m_glyphs[i].m_textureX + 7) >> 3);

		GolPaletteBase* palette = p_textureFormat->m_paletteMask ? texture->GetPalette() : NULL;
		g_unk0x10062568.FUN_10022730(
			source,
			dest,
			font->m_glyphs[i].m_width,
			font->m_fontHeight,
			destPitch,
			*p_textureFormat,
			palette,
			0,
			colorKey
		);
	}

	texture->UnlockPixels();
	font->m_sourceImage.UnlockPixels();
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolFont::VTable0x18()
{
	// empty
}
