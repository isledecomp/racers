#include "golfont0xa0.h"

#include "bronzefalcon0xc8770.h"
#include "decomp.h"
#include "duskwindbananarelic0x30.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golimgfile.h"
#include "goltgafile.h"
#include "ipalette0x4.h"
#include "purpledune0x7c.h"
#include "rectangle.h"
#include "silverdune0x30.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolFont0xa0, 0xa0)

// GLOBAL: GOLDP 0x10062568
static GolImgFile g_unk0x10062568;

extern SilverDune0x30* g_unk0x10063c9c;

extern GolTgaFile g_unk0x10063ca0;

extern GolBmpFile g_unk0x10064280;

extern const ColorRGBA g_unk0x10057668;

// FUNCTION: GOLDP 0x100043d0
GolFont0xa0::GolFont0xa0()
{
	m_unk0x90 = NULL;
	m_unk0x9c = NULL;
	m_renderer = NULL;
}

// FUNCTION: GOLDP 0x10004480
GolFont0xa0::~GolFont0xa0()
{
	Clear();
}

// FUNCTION: GOLDP 0x10004520
void GolFont0xa0::Clear()
{
	m_unk0x40.VTable0x38();
	ReleaseSurfaces();
	GolFontBase0x40::Clear();
}

// FUNCTION: GOLDP 0x10004570
void GolFont0xa0::VTable0x00(const LegoChar* p_name, BronzeFalcon0xc8770* p_renderer)
{
	GolSurfaceFormat sourceFormat;

	GolImgFile* imageFile = &g_unk0x10063ca0;
	if (!(m_unk0x2c & c_flagBit4)) {
		imageFile = &g_unk0x10064280;
	}

	imageFile->VTable0x08(p_name);
	LegoU32 sourceHeight = imageFile->GetHeight();
	sourceFormat = imageFile->GetTextureFormat();
	m_unk0x1c = sourceHeight;

	if (sourceFormat.m_paletteMask && sourceFormat.m_bitsPerPixel == 4) {
		::memset(&sourceFormat, 0, sizeof(sourceFormat));
		sourceFormat.m_bitsPerPixel = 8;
		sourceFormat.m_paletteMask = 0x00ff;
	}

	LegoU32 sourceWidth = imageFile->GetWidth();
	g_unk0x10063c9c = &m_unk0x40;
	m_unk0x40.VTable0x34(*p_renderer, sourceFormat, sourceWidth, m_unk0x1c);
	imageFile->VTable0x20(&m_unk0x40, m_unk0x2c & c_flagBit2, NULL);
	imageFile->Destroy();

	FUN_1001e190(p_name);

	GolSurfaceFormat textureFormat;
	g_unk0x10063c9c = &m_unk0x40;
	GolSurfaceFormat surfaceFormat = m_unk0x40.GetTextureFormat();
	LegoU32 selectFlags = m_unk0x2c & c_flagBit5;
	p_renderer->SelectTextureFormat(surfaceFormat, &textureFormat, selectFlags);
	FUN_1001e5e0(p_renderer, &textureFormat);
	VTable0x04(p_renderer, &textureFormat);
	FUN_10004d70(p_renderer, &surfaceFormat, &textureFormat);

	::qsort(m_unk0x28, m_unk0x24, sizeof(Glyph0x0c), GolFontBase0x40::CompareGlyphChars);
}

// FUNCTION: GOLDP 0x100046e0
void GolFont0xa0::ReleaseSurfaces()
{
	if (m_unk0x9c != NULL) {
		delete[] m_unk0x9c;
		m_unk0x9c = NULL;
	}

	if (m_unk0x90 != NULL) {
		delete[] m_unk0x90;
		m_unk0x90 = NULL;
	}
}

// FUNCTION: GOLDP 0x10004720
void GolFont0xa0::RefreshSurfaces(BronzeFalcon0xc8770* p_renderer)
{
	GolSurfaceFormat textureFormat;

	g_unk0x10063c9c = &m_unk0x40;
	GolSurfaceFormat sourceFormat = m_unk0x40.GetTextureFormat();
	p_renderer->SelectTextureFormat(sourceFormat, &textureFormat, m_unk0x2c & c_flagBit5);
	FUN_1001e5e0(p_renderer, &textureFormat);
	VTable0x04(p_renderer, &textureFormat);
	FUN_10004d70(p_renderer, &sourceFormat, &textureFormat);
}

// STUB: GOLDP 0x100047b0
void GolFont0xa0::VTable0x04(BronzeFalcon0xc8770* p_renderer, GolSurfaceFormat* p_textureFormat)
{
	STUB(0x100047b0);

	m_unk0x90 = new PurpleDune0x7c[m_unk0x04];
	if (m_unk0x90 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x9c = new DuskwindBananaRelic0x30[m_unk0x04];
	if (m_unk0x9c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;
	PurpleDune0x7c* texture = m_unk0x90;
	DuskwindBananaRelic0x30* material = m_unk0x9c;

	for (; i < m_unk0x04 - 1; i++) {
		if (m_unk0x2c & c_flagBit5) {
			texture->SetColorKey(m_colorKey);
		}

		texture->FUN_10015d00(*p_renderer, *p_textureFormat, m_unk0x08, m_unk0x0c);

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

	i = m_unk0x04 - 1;
	texture = &m_unk0x90[i];
	material = &m_unk0x9c[i];

	if (m_unk0x2c & c_flagBit5) {
		texture->SetColorKey(m_colorKey);
	}

	texture->FUN_10015d00(*p_renderer, *p_textureFormat, m_unk0x10, m_unk0x14);
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
PurpleDune0x7c* GolFont0xa0::VTable0x08(LegoU32 p_index)
{
	return &m_unk0x90[p_index];
}

// FUNCTION: GOLDP 0x10004b80
void GolFont0xa0::VTable0x0c(WhiteFalcon0x140* p_renderer, LegoU32)
{
	m_renderer = static_cast<BronzeFalcon0xc8770*>(p_renderer);
}

// FUNCTION: GOLDP 0x10004b90
void GolFont0xa0::VTable0x10(LegoU32 p_index)
{
	LegoU32 index = p_index;
	DuskwindBananaRelic0x30* material = &m_unk0x9c[index];
	(m_renderer->*m_renderer->m_unk0xc876c)(material);

	GoldDune0x38* texture = &m_unk0x90[index];
	m_renderer->FUN_1000ac00(texture);
	m_unk0x94 = 1.0f / static_cast<LegoFloat>(m_unk0x90[index].GetWidth());
	m_unk0x98 = 1.0f / static_cast<LegoFloat>(m_unk0x90[index].GetHeight());
}

// STUB: GOLDP 0x10004c20
void GolFont0xa0::VTable0x14(Rect* p_sourceRect, Rect* p_destRect)
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

	vertices[0].tu = static_cast<LegoFloat>(p_sourceRect->m_left) * m_unk0x94 + (m_unk0x94 * 0.25f);
	vertices[0].tv = static_cast<LegoFloat>(p_sourceRect->m_top) * m_unk0x98;
	vertices[1].tu = vertices[0].tu;
	vertices[1].tv = static_cast<LegoFloat>(sourceBottom) * m_unk0x98;
	vertices[2].tu = static_cast<LegoFloat>(p_sourceRect->m_right) * m_unk0x94 + (m_unk0x94 * 0.25f);
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
void GolFont0xa0::FUN_10004d70(
	BronzeFalcon0xc8770* p_renderer,
	const GolSurfaceFormat* p_sourceFormat,
	GolSurfaceFormat* p_textureFormat
)
{
	GolFont0xa0* font = this;
	LegoU32 currentSurface = 0;
	PurpleDune0x7c* texture = font->VTable0x08(currentSurface);

	ColorRGBA* paletteEntries;
	LegoU32 paletteSize;
	if (p_sourceFormat->m_paletteMask) {
		paletteEntries = font->m_unk0x40.GetPaletteEntries();
		paletteSize = font->m_unk0x40.GetPaletteSize();
	}
	else {
		paletteEntries = NULL;
		paletteSize = 0;
	}

	ColorRGBA* colorKey;
	if (font->m_unk0x2c & c_flagBit5) {
		if (p_renderer->GetFlags() & WhiteFalcon0x140::c_flagBit9) {
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
	font->m_unk0x40.LockPixels(&sourcePixels, &sourcePitch, SilverDune0x30::c_lockRequestRead);

	LegoU8* destPixels;
	LegoU32 destPitch;
	texture->LockPixels(&destPixels, &destPitch, SilverDune0x30::c_lockRequestWrite);

	for (LegoU32 i = 0; i < font->m_unk0x24; i++) {
		if (font->m_unk0x28[i].m_unk0x04 != currentSurface) {
			texture->UnlockPixels();
			currentSurface = font->m_unk0x28[i].m_unk0x04;
			texture = font->VTable0x08(currentSurface);
			texture->LockPixels(&destPixels, &destPitch, SilverDune0x30::c_lockRequestWrite);
		}

		g_unk0x10062568.FUN_100226c0(
			*p_sourceFormat,
			font->m_unk0x28[i].m_width,
			font->m_unk0x1c,
			sourcePitch,
			paletteEntries,
			paletteSize
		);

		LegoU8* source =
			sourcePixels +
			((static_cast<LegoU32>(p_sourceFormat->m_bitsPerPixel) * font->m_unk0x28[i].m_unk0x02 + 7) >> 3);
		LegoU8* dest =
			destPixels + destPitch * font->m_unk0x28[i].m_unk0x08 +
			((static_cast<LegoU32>(p_textureFormat->m_bitsPerPixel) * font->m_unk0x28[i].m_unk0x06 + 7) >> 3);

		IPalette0x4* palette = p_textureFormat->m_paletteMask ? texture->GetPalette() : NULL;
		g_unk0x10062568.FUN_10022730(
			source,
			dest,
			font->m_unk0x28[i].m_width,
			font->m_unk0x1c,
			destPitch,
			*p_textureFormat,
			palette,
			0,
			colorKey
		);
	}

	texture->UnlockPixels();
	font->m_unk0x40.UnlockPixels();
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolFont0xa0::VTable0x18()
{
	// empty
}
