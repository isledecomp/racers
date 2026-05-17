#include "utopianpan0xa4.h"

#include "bronzefalcon0xc8770.h"
#include "duskwindbananarelic0x30.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golimgfile.h"
#include "golsurfaceformat.h"
#include "goltgafile.h"
#include "ipalette0x4.h"
#include "purpledune0x7c.h"
#include "rectangle.h"
#include "slatepeak0x58.h"

DECOMP_SIZE_ASSERT(UtopianPan0xa4, 0xa4)

extern const ColorRGBA g_unk0x10057668;

// GLOBAL: GOLDP 0x10062b18
static GolImgFile g_unk0x10062b18;

// GLOBAL: GOLDP 0x100630c8
static D3DTLVERTEX g_unk0x100630c8[4];

// GLOBAL: GOLDP 0x10063ca0
static GolTgaFile g_unk0x10063ca0;

// GLOBAL: GOLDP 0x10064280
static GolBmpFile g_unk0x10064280;

// FUNCTION: GOLDP 0x10004fd0
UtopianPan0xa4::UtopianPan0xa4()
{
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x50 = 0;
}

// FUNCTION: GOLDP 0x10005040
UtopianPan0xa4::~UtopianPan0xa4()
{
	FUN_100051c0();
	m_unk0x58.VTable0x38();
	WhiteBaffoon0x50::Reset();
}

// FUNCTION: GOLDP 0x100050b0
void UtopianPan0xa4::VTable0x10()
{
	GolSurfaceFormat imageFormat;
	UtopianPanImageName imageName;
	imageName.m_name[0] = m_name[0];
	imageName.m_name[1] = m_name[1];
	imageName.m_chars[8] = 0;

	GolImgFile* imageFile = &g_unk0x10063ca0;
	if (!(m_flags & c_flagBit4)) {
		imageFile = &g_unk0x10064280;
	}

	m_unk0x3c = (m_unk0x3c & ~(c_flagBit1 | c_flagBit2)) | c_flagBit3;
	if (!(m_unk0x3c & (c_flagBit4 | c_flagBit5))) {
		m_unk0x3c |= c_flagBit4;
	}

	imageFile->VTable0x08(imageName.m_chars);
	imageFormat = imageFile->GetTextureFormat();
	m_width = imageFile->GetWidth();
	m_height = imageFile->GetHeight();

	m_unk0x58.VTable0x34(*m_renderer, imageFormat, m_width, m_height);
	imageFile->SetUnk0x5a8(TRUE);
	imageFile->SetUnk0x5ac(FALSE);
	imageFile->VTable0x20(&m_unk0x58, m_flags & c_flagBit2, NULL);
	imageFile->SetUnk0x5a8(FALSE);
	imageFile->Destroy();

	GolSurfaceFormat textureFormat = m_unk0x58.GetTextureFormat();
	m_renderer->SelectTextureFormat(textureFormat, &m_unk0x0c, m_flags & c_flagBit5);
	FUN_1001f430();
	FUN_10005b00();
}

// FUNCTION: GOLDP 0x100051c0
void UtopianPan0xa4::FUN_100051c0()
{
	if (m_unk0x54 != NULL) {
		delete[] m_unk0x54;
		m_unk0x54 = NULL;
	}
	if (m_unk0x50 != NULL) {
		delete[] m_unk0x50;
		m_unk0x50 = NULL;
	}
	if (m_unk0x08 != NULL) {
		delete[] m_unk0x08;
		m_unk0x08 = NULL;
	}
	if (m_unk0x04 != NULL) {
		delete[] m_unk0x04;
		m_unk0x04 = NULL;
	}
}

// FUNCTION: GOLDP 0x10005210
void UtopianPan0xa4::FUN_10005210()
{
	GolSurfaceFormat textureFormat = m_unk0x58.GetTextureFormat();

	m_renderer->SelectTextureFormat(textureFormat, &m_unk0x0c, m_flags & c_flagBit5);
	FUN_1001f430();
	FUN_10005b00();
}

// FUNCTION: GOLDP 0x10005260
void UtopianPan0xa4::Reset()
{
	FUN_100051c0();
	m_unk0x58.VTable0x38();
	WhiteBaffoon0x50::Reset();
}

// FUNCTION: GOLDP 0x10005280
void UtopianPan0xa4::VTable0x00()
{
	m_unk0x04 = new LegoS32[m_unk0x2c];
	if (m_unk0x04 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100052b0
void UtopianPan0xa4::VTable0x04()
{
	m_unk0x08 = new LegoS32[m_unk0x30];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100052e0
void UtopianPan0xa4::VTable0x08()
{
	LegoU32 count = m_unk0x30 * m_unk0x2c;

	m_unk0x50 = new PurpleDune0x7c[count];
	if (m_unk0x50 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x54 = new DuskwindBananaRelic0x30[count];
	if (m_unk0x54 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100053d0
void UtopianPan0xa4::VTable0x0c(LegoU32 p_row, LegoU32 p_column, GolSurfaceFormat* p_textureFormat)
{
	LegoU32 index = p_row * m_unk0x30 + p_column;

	m_unk0x50[index].FUN_10015d00(
		static_cast<BronzeFalcon0xc8770&>(*m_renderer),
		*p_textureFormat,
		m_unk0x04[p_row],
		m_unk0x08[p_column]
	);
	FUN_10005440(m_renderer, &m_unk0x54[index], &m_unk0x50[index]);
}

// FUNCTION: GOLDP 0x10005440
void UtopianPan0xa4::FUN_10005440(
	WhiteFalcon0x140* p_renderer,
	DuskwindBananaRelic0x30* p_material,
	GoldDune0x38* p_texture
)
{
	LegoU32 flags = (m_unk0x3c & c_flagBit1) ? 0x92a8a : 0x92a8c;
	if (m_unk0x3c & c_flagBit4) {
		flags |= c_flagBit4;
	}
	else {
		flags |= c_flagBit5;
	}

	DuskWindBananaRelicParams params;
	params.m_unk0x04 = p_texture;
	params.m_unk0x08.m_unk0x0 = 0xff;
	params.m_unk0x08.m_unk0x1 = 0xff;
	params.m_unk0x08.m_unk0x2 = 0xff;
	params.m_unk0x08.m_unk0x3 = 0xff;
	params.m_unk0x0c.m_unk0x0 = 0xff;
	params.m_unk0x0c.m_unk0x1 = 0xff;
	params.m_unk0x0c.m_unk0x2 = 0xff;
	params.m_unk0x0c.m_unk0x3 = 0xff;
	params.m_unk0x11 = 0;
	params.m_unk0x13 = 0;
	params.m_unk0x00 = flags;
	params.m_unk0x10 = 2;
	params.m_unk0x12 = 1;

	p_material->FUN_100257e0(p_renderer, params);
	p_material->FUN_10006320(*p_renderer);
}

// FUNCTION: GOLDP 0x100054d0
void UtopianPan0xa4::FUN_100054d0(
	BronzeFalcon0xc8770* p_renderer,
	undefined4 p_unk0x08,
	Rect* p_destRect,
	Rect* p_clipRect
)
{
	Rect sourceRect;
	sourceRect.m_left = 0;
	sourceRect.m_top = 0;
	sourceRect.m_right = m_width;
	sourceRect.m_bottom = m_height;

	FUN_10005510(p_renderer, p_unk0x08, p_destRect, &sourceRect, p_clipRect);
}

// STUB: GOLDP 0x10005510
void UtopianPan0xa4::FUN_10005510(
	BronzeFalcon0xc8770* p_renderer,
	undefined4,
	Rect* p_destRect,
	Rect* p_sourceRect,
	Rect* p_clipRect
)
{
	if (!(m_unk0x3c & c_flagBit3)) {
		return;
	}

	const SlatePeak0x58* renderTarget = p_renderer->GetRenderTargetInfo();
	LegoFloat clipLeft = 0.0f;
	LegoFloat clipTop = 0.0f;
	LegoFloat clipRight = static_cast<LegoFloat>(renderTarget->GetWidth());
	LegoFloat clipBottom = static_cast<LegoFloat>(renderTarget->GetHeight());

	if (p_clipRect != NULL) {
		if (p_clipRect->m_left > 0) {
			clipLeft = static_cast<LegoFloat>(p_clipRect->m_left);
		}
		if (p_clipRect->m_top > 0) {
			clipTop = static_cast<LegoFloat>(p_clipRect->m_top);
		}
		if (p_clipRect->m_right < renderTarget->GetWidth()) {
			clipRight = static_cast<LegoFloat>(p_clipRect->m_right);
		}
		if (p_clipRect->m_bottom < renderTarget->GetHeight()) {
			clipBottom = static_cast<LegoFloat>(p_clipRect->m_bottom);
		}

		if (clipRight <= clipLeft || clipBottom <= clipTop) {
			return;
		}
	}

	if (p_destRect->m_right <= p_destRect->m_left || p_destRect->m_bottom <= p_destRect->m_top) {
		return;
	}

	LegoFloat destLeft = static_cast<LegoFloat>(p_destRect->m_left);
	LegoFloat destTop = static_cast<LegoFloat>(p_destRect->m_top);
	LegoFloat destRight = static_cast<LegoFloat>(p_destRect->m_right);
	LegoFloat destBottom = static_cast<LegoFloat>(p_destRect->m_bottom);

	if (destLeft > clipRight || destTop > clipBottom || destRight <= clipLeft || destBottom <= clipTop) {
		return;
	}

	if (p_sourceRect->m_right <= p_sourceRect->m_left || p_sourceRect->m_bottom <= p_sourceRect->m_top) {
		return;
	}

	LegoFloat sourceLeft = static_cast<LegoFloat>(p_sourceRect->m_left);
	LegoFloat sourceTop = static_cast<LegoFloat>(p_sourceRect->m_top);
	LegoFloat sourceRight = static_cast<LegoFloat>(p_sourceRect->m_right);
	LegoFloat sourceBottom = static_cast<LegoFloat>(p_sourceRect->m_bottom);
	LegoFloat scaleX = (destRight - destLeft) / (sourceRight - sourceLeft);
	LegoFloat scaleY = (destBottom - destTop) / (sourceBottom - sourceTop);
	LegoFloat sourcePerDestX = 1.0f / scaleX;
	LegoFloat sourcePerDestY = 1.0f / scaleY;

	if (clipLeft > destLeft) {
		sourceLeft += (clipLeft - destLeft) * sourcePerDestX;
		destLeft = clipLeft;
	}
	if (clipTop > destTop) {
		sourceTop += (clipTop - destTop) * sourcePerDestY;
		destTop = clipTop;
	}
	if (clipRight < destRight) {
		sourceRight += (clipRight - destRight) * sourcePerDestX;
	}
	if (clipBottom < destBottom) {
		sourceBottom += (clipBottom - destBottom) * sourcePerDestY;
	}

	for (LegoU32 i = 0; i < sizeOfArray(g_unk0x100630c8); i++) {
		g_unk0x100630c8[i].sz = 0.0f;
		g_unk0x100630c8[i].rhw = 1.0f;
		g_unk0x100630c8[i].color = (m_unk0x4a.m_uBytes[3] << 24) | (m_unk0x4a.m_uBytes[0] << 16) |
								   (m_unk0x4a.m_uBytes[1] << 8) | m_unk0x4a.m_uBytes[2];
		g_unk0x100630c8[i].specular = 0xffffffff;
	}

	LegoFloat tileLeft = 0.0f;
	for (LegoU32 row = 0; row < m_unk0x2c; row++) {
		LegoFloat tileTop = 0.0f;

		for (LegoU32 column = 0; column < m_unk0x30; column++) {
			LegoFloat tileWidth = static_cast<LegoFloat>(m_unk0x04[row]);
			LegoFloat tileHeight = static_cast<LegoFloat>(m_unk0x08[column]);
			LegoFloat tileRight = tileLeft + tileWidth;
			LegoFloat tileBottom = tileTop + tileHeight;

			if (tileLeft < sourceRight && tileRight > sourceLeft && tileTop < sourceBottom && tileBottom > sourceTop) {
				LegoFloat clippedLeft = tileLeft;
				LegoFloat clippedTop = tileTop;
				LegoFloat clippedRight = tileRight;
				LegoFloat clippedBottom = tileBottom;

				if (clippedLeft < sourceLeft) {
					clippedLeft = sourceLeft;
				}
				if (clippedRight > sourceRight) {
					clippedRight = sourceRight;
				}
				if (clippedTop < sourceTop) {
					clippedTop = sourceTop;
				}
				if (clippedBottom > sourceBottom) {
					clippedBottom = sourceBottom;
				}

				LegoU32 index = row * m_unk0x30 + column;
				(p_renderer->*p_renderer->m_unk0xc876c)(&m_unk0x54[index]);
				p_renderer->FUN_1000ac00(&m_unk0x50[index]);

				LegoFloat invTileWidth = 1.0f / tileWidth;
				LegoFloat invTileHeight = 1.0f / tileHeight;
				LegoFloat left = (clippedLeft - sourceLeft) * scaleX + destLeft;
				LegoFloat top = (clippedTop - sourceTop) * scaleY + destTop;
				LegoFloat right = (clippedRight - sourceLeft) * scaleX + destLeft;
				LegoFloat bottom = (clippedBottom - sourceTop) * scaleY + destTop;
				LegoFloat uLeft = (clippedLeft - tileLeft) * invTileWidth;
				LegoFloat vTop = (clippedTop - tileTop) * invTileHeight;
				LegoFloat uRight = (clippedRight - tileLeft) * invTileWidth;
				LegoFloat vBottom = (clippedBottom - tileTop) * invTileHeight;

				g_unk0x100630c8[0].sx = left;
				g_unk0x100630c8[0].sy = top;
				g_unk0x100630c8[0].tu = uLeft;
				g_unk0x100630c8[0].tv = vTop;

				g_unk0x100630c8[1].sx = left;
				g_unk0x100630c8[1].sy = bottom;
				g_unk0x100630c8[1].tu = uLeft;
				g_unk0x100630c8[1].tv = vBottom;

				g_unk0x100630c8[2].sx = right;
				g_unk0x100630c8[2].sy = top;
				g_unk0x100630c8[2].tu = uRight;
				g_unk0x100630c8[2].tv = vTop;

				g_unk0x100630c8[3].sx = right;
				g_unk0x100630c8[3].sy = bottom;
				g_unk0x100630c8[3].tu = uRight;
				g_unk0x100630c8[3].tv = vBottom;

				p_renderer->FUN_10009fd0(g_unk0x100630c8, sizeOfArray(g_unk0x100630c8));
			}

			tileTop = tileBottom;
		}

		tileLeft += static_cast<LegoFloat>(m_unk0x04[row]);
	}
}

// FUNCTION: GOLDP 0x10005ae0
PurpleDune0x7c* UtopianPan0xa4::VTable0x1c(LegoU32 p_row, LegoU32 p_column)
{
	return &m_unk0x50[p_row * m_unk0x30 + p_column];
}

// STUB: GOLDP 0x10005b00
void UtopianPan0xa4::FUN_10005b00()
{
	GolSurfaceFormat textureFormat = m_unk0x58.GetTextureFormat();

	LegoU8* sourcePixels;
	LegoU32 sourcePitch;
	m_unk0x58.LockPixels(
		&sourcePixels,
		&sourcePitch,
		SilverDune0x30::c_lockRequestRead | SilverDune0x30::c_lockRequestWrite
	);

	ColorRGBA* paletteEntries;
	LegoU32 paletteSize;
	if (textureFormat.m_paletteMask != 0) {
		paletteEntries = m_unk0x58.GetPaletteEntries();
		paletteSize = m_unk0x58.GetPaletteSize();
	}
	else {
		paletteEntries = NULL;
		paletteSize = 0;
	}

	ColorRGBA* colorKey;
	if (m_flags & c_flagBit5) {
		ColorRGBA* sourceColorKey = reinterpret_cast<ColorRGBA*>(&m_unk0x28);
		if (m_renderer->GetFlags() & WhiteFalcon0x140::c_flagBit9) {
			g_unk0x10062b18.SetUnk0x0a0(g_unk0x10057668);
		}
		else {
			g_unk0x10062b18.SetUnk0x0a0(*sourceColorKey);
		}

		colorKey = sourceColorKey;
	}
	else {
		colorKey = NULL;
	}

	LegoU32 sourceX = 0;
	LegoU32 copyWidth = 0;
	LegoU32 copyHeight = 0;
	LegoU32 row;
	LegoU32 column;
	for (row = 0; row < m_unk0x2c; row++) {
		LegoU32 sourceY = 0;
		for (column = 0; column < m_unk0x30; column++) {
			PurpleDune0x7c* texture = VTable0x1c(row, column);
			copyWidth = texture->GetWidth();

			LegoU32 remainingWidth = m_unk0x58.GetWidth() - sourceX;
			if (copyWidth > remainingWidth) {
				copyWidth = remainingWidth;
			}

			copyHeight = texture->GetHeight();
			LegoU32 remainingHeight = m_unk0x58.GetHeight() - sourceY;
			if (copyHeight > remainingHeight) {
				copyHeight = remainingHeight;
			}

			LegoU8* source = sourcePixels + sourceY * sourcePitch + ((textureFormat.m_bitsPerPixel * sourceX + 7) >> 3);

			g_unk0x10062b18
				.FUN_100226c0(textureFormat, copyWidth, copyHeight, sourcePitch, paletteEntries, paletteSize);
			g_unk0x10062b18.SetUnk0x5ac(TRUE);

			LegoU8* destPixels;
			LegoU32 destPitch;
			texture->LockPixels(&destPixels, &destPitch, SilverDune0x30::c_lockRequestWrite);

			IPalette0x4* destPalette = NULL;
			if (m_unk0x0c.m_paletteMask != 0) {
				destPalette = texture->GetPalette();
			}

			g_unk0x10062b18.FUN_10022730(
				source,
				destPixels,
				destPitch,
				copyWidth,
				copyHeight,
				m_unk0x0c,
				destPalette,
				0,
				colorKey
			);
			texture->UnlockPixels();

			sourceY += copyHeight;
		}

		sourceX += copyWidth;
	}

	m_unk0x58.UnlockPixels();
}
