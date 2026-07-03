#include "image/golimage.h"

#include "device/golpalettebase.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golimgfile.h"
#include "golsurfaceformat.h"
#include "goltgafile.h"
#include "material/golsoftwarematerial.h"
#include "render/gold3drenderdevice.h"
#include "render/rectangle.h"
#include "surface/gold3dtexture.h"
#include "surface/golrendertarget.h"

DECOMP_SIZE_ASSERT(GolImage, 0xa4)
DECOMP_SIZE_ASSERT(ColorBGR, 0x3)
DECOMP_SIZE_ASSERT(FColorRGB, 0xc)

extern const ColorRGBA g_transparentBlack;

// GLOBAL: GOLDP 0x10062b18
static GolImgFile g_tileImgFile;

// GLOBAL: GOLDP 0x100630c8
static D3DTLVERTEX g_imageQuad[4];

// GLOBAL: GOLDP 0x10063ca0
GolTgaFile g_textureTgaFile;

// GLOBAL: GOLDP 0x10064280
GolBmpFile g_textureBmpFile;

// FUNCTION: GOLDP 0x10004fd0
GolImage::GolImage()
{
	m_tileWidths = 0;
	m_tileHeights = 0;
	m_texture = 0;
}

// FUNCTION: GOLDP 0x10005040
GolImage::~GolImage()
{
	DestroyTiles();
	m_surface.Destroy();
	GolTiledTexture::Reset();
}

// FUNCTION: GOLDP 0x100050b0
void GolImage::Load()
{
	GolSurfaceFormat imageFormat;
	GolTiledTexture::TileImageName imageName;
	imageName.m_name[0] = m_name[0];
	imageName.m_name[1] = m_name[1];
	imageName.m_chars[8] = 0;

	GolImgFile* imageFile = &g_textureTgaFile;
	if (!(m_flags & GolTexture::c_textureFlagTgaSource)) {
		imageFile = &g_textureBmpFile;
	}

	m_stateFlags = (m_stateFlags & ~(c_stateFlatShaded | c_stateFlagBit2)) | c_stateHasContent;
	if (!(m_stateFlags & (c_stateDecal | c_stateModulate))) {
		m_stateFlags |= c_stateDecal;
	}

	imageFile->Open(imageName.m_chars);
	imageFormat = imageFile->GetTextureFormat();
	m_width = imageFile->GetWidth();
	m_height = imageFile->GetHeight();

	m_surface.Allocate(*m_renderer, imageFormat, m_width, m_height);
	imageFile->SetKeepNibbleOrder(TRUE);
	imageFile->SetRemapPureBlack(FALSE);
	imageFile->LoadSurface(&m_surface, m_flags & GolTexture::c_textureFlagFlipVertically, NULL);
	imageFile->SetKeepNibbleOrder(FALSE);
	imageFile->Destroy();

	GolSurfaceFormat textureFormat = m_surface.GetTextureFormat();
	m_renderer->SelectTextureFormat(textureFormat, &m_format, m_flags & GolTexture::c_textureFlagColorKeyed);
	ComputeTileLayout();
	UploadTiles();
}

// FUNCTION: GOLDP 0x100051c0
void GolImage::DestroyTiles()
{
	if (m_materials != NULL) {
		delete[] m_materials;
		m_materials = NULL;
	}
	if (m_texture != NULL) {
		delete[] m_texture;
		m_texture = NULL;
	}
	if (m_tileHeights != NULL) {
		delete[] m_tileHeights;
		m_tileHeights = NULL;
	}
	if (m_tileWidths != NULL) {
		delete[] m_tileWidths;
		m_tileWidths = NULL;
	}
}

// FUNCTION: GOLDP 0x10005210
void GolImage::RebuildTiles()
{
	GolSurfaceFormat textureFormat = m_surface.GetTextureFormat();

	m_renderer->SelectTextureFormat(textureFormat, &m_format, m_flags & GolTexture::c_textureFlagColorKeyed);
	ComputeTileLayout();
	UploadTiles();
}

// FUNCTION: GOLDP 0x10005260
void GolImage::Reset()
{
	DestroyTiles();
	m_surface.Destroy();
	GolTiledTexture::Reset();
}

// FUNCTION: GOLDP 0x10005280
void GolImage::AllocateTileWidths()
{
	m_tileWidths = new LegoS32[m_tileColumnCount];
	if (m_tileWidths == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100052b0
void GolImage::AllocateTileHeights()
{
	m_tileHeights = new LegoS32[m_tileRowCount];
	if (m_tileHeights == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100052e0
void GolImage::AllocateTileArrays()
{
	LegoU32 count = m_tileRowCount * m_tileColumnCount;

	m_texture = new GolD3DTexture[count];
	if (m_texture == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_materials = new GolSoftwareMaterial[count];
	if (m_materials == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: GOLDP 0x100053d0
void GolImage::CreateTile(LegoU32 p_row, LegoU32 p_column, GolSurfaceFormat* p_textureFormat)
{
	LegoU32 index = p_row * m_tileRowCount + p_column;

	m_texture[index].AllocateDeviceOnly(
		static_cast<GolD3DRenderDevice&>(*m_renderer),
		*p_textureFormat,
		m_tileWidths[p_row],
		m_tileHeights[p_column]
	);
	CreateTileMaterial(m_renderer, &m_materials[index], &m_texture[index]);
}

// FUNCTION: GOLDP 0x10005440
void GolImage::CreateTileMaterial(GolRenderDevice* p_renderer, GolSoftwareMaterial* p_material, GolTexture* p_texture)
{
	LegoU32 flags = (m_stateFlags & c_stateFlatShaded) ? 0x92a8a : 0x92a8c;
	if (m_stateFlags & c_stateDecal) {
		flags |= GolMaterial::c_flagDecal;
	}
	else {
		flags |= GolMaterial::c_flagModulate;
	}

	GolMaterialParams params;
	params.m_texture = p_texture;
	params.m_ambient.m_red = 0xff;
	params.m_ambient.m_grn = 0xff;
	params.m_ambient.m_blu = 0xff;
	params.m_ambient.m_alp = 0xff;
	params.m_diffuse.m_red = 0xff;
	params.m_diffuse.m_grn = 0xff;
	params.m_diffuse.m_blu = 0xff;
	params.m_diffuse.m_alp = 0xff;
	params.m_alphaRef = 0;
	params.m_destBlend = 0;
	params.m_flags = flags;
	params.m_alphaFunc = 2;
	params.m_srcBlend = 1;

	p_material->SetParams(p_renderer, params);
	p_material->Create(*p_renderer);
}

// FUNCTION: GOLDP 0x100054d0
void GolImage::Draw(GolD3DRenderDevice* p_renderer, undefined4 p_unk0x08, Rect* p_destRect, Rect* p_clipRect)
{
	Rect sourceRect;
	sourceRect.m_left = 0;
	sourceRect.m_top = 0;
	sourceRect.m_right = m_width;
	sourceRect.m_bottom = m_height;

	DrawStretched(p_renderer, p_unk0x08, p_destRect, &sourceRect, p_clipRect);
}

// STUB: GOLDP 0x10005510
void GolImage::DrawStretched(
	GolD3DRenderDevice* p_renderer,
	undefined4,
	Rect* p_destRect,
	Rect* p_sourceRect,
	Rect* p_clipRect
)
{
	if (!(m_stateFlags & c_stateHasContent)) {
		return;
	}

	LegoS32 renderTargetWidth = p_renderer->GetRenderTargetInfo()->GetWidth();
	LegoS32 renderTargetHeight = p_renderer->GetRenderTargetInfo()->GetHeight();
	LegoFloat clipLeft = 0.0f;
	LegoFloat clipTop = 0.0f;
	LegoFloat clipRight = static_cast<LegoFloat>(renderTargetWidth);
	LegoFloat clipBottom = static_cast<LegoFloat>(renderTargetHeight);

	if (p_clipRect != NULL) {
		if (p_clipRect->m_left > 0) {
			clipLeft = static_cast<LegoFloat>(p_clipRect->m_left);
		}
		if (p_clipRect->m_top > 0) {
			clipTop = static_cast<LegoFloat>(p_clipRect->m_top);
		}
		if (p_clipRect->m_right < renderTargetWidth) {
			clipRight = static_cast<LegoFloat>(p_clipRect->m_right);
		}
		if (p_clipRect->m_bottom < renderTargetHeight) {
			clipBottom = static_cast<LegoFloat>(p_clipRect->m_bottom);
		}

		if (clipRight <= clipLeft || clipBottom <= clipTop) {
			return;
		}
	}

	LegoS32 destRightInt = p_destRect->m_right;
	LegoS32 destLeftInt = p_destRect->m_left;
	if (destRightInt <= destLeftInt) {
		return;
	}

	LegoS32 destBottomInt = p_destRect->m_bottom;
	LegoS32 destTopInt = p_destRect->m_top;
	if (destBottomInt <= destTopInt) {
		return;
	}

	LegoFloat destLeft = static_cast<LegoFloat>(destLeftInt);
	LegoFloat destTop = static_cast<LegoFloat>(destTopInt);
	LegoFloat destRight = static_cast<LegoFloat>(destRightInt);
	LegoFloat destBottom = static_cast<LegoFloat>(destBottomInt);

	if (destLeft > clipRight || destTop > clipBottom || destRight <= clipLeft || destBottom <= clipTop) {
		return;
	}

	LegoS32 sourceRightInt = p_sourceRect->m_right;
	LegoS32 sourceLeftInt = p_sourceRect->m_left;
	if (sourceRightInt <= sourceLeftInt) {
		return;
	}

	LegoS32 sourceBottomInt = p_sourceRect->m_bottom;
	LegoS32 sourceTopInt = p_sourceRect->m_top;
	if (sourceBottomInt <= sourceTopInt) {
		return;
	}

	LegoFloat sourceLeft = static_cast<LegoFloat>(sourceLeftInt);
	LegoFloat sourceTop = static_cast<LegoFloat>(sourceTopInt);
	LegoFloat sourceRight = static_cast<LegoFloat>(sourceRightInt);
	LegoFloat sourceBottom = static_cast<LegoFloat>(sourceBottomInt);
	LegoFloat scaleX = (destRight - destLeft) / (sourceRight - sourceLeft);
	LegoFloat scaleY = (destBottom - destTop) / (sourceBottom - sourceTop);
	LegoFloat sourcePerDestX = 1.0f / scaleX;
	LegoFloat sourcePerDestY = 1.0f / scaleY;

	if (clipLeft - destLeft > 0.0f) {
		sourceLeft += (clipLeft - destLeft) * sourcePerDestX;
		destLeft = clipLeft;
	}
	if (clipTop - destTop > 0.0f) {
		sourceTop += (clipTop - destTop) * sourcePerDestY;
		destTop = clipTop;
	}
	if (clipRight - destRight < 0.0f) {
		sourceRight += (clipRight - destRight) * sourcePerDestX;
	}
	if (clipBottom - destBottom < 0.0f) {
		sourceBottom += (clipBottom - destBottom) * sourcePerDestY;
	}

	g_imageQuad[0].sz = 0.0f;
	g_imageQuad[1].sz = 0.0f;
	g_imageQuad[2].sz = 0.0f;
	g_imageQuad[3].sz = 0.0f;

	g_imageQuad[0].rhw = 1.0f;
	g_imageQuad[1].rhw = 1.0f;
	g_imageQuad[2].rhw = 1.0f;
	g_imageQuad[3].rhw = 1.0f;

	LegoU32 color = (m_tintColor.m_uBytes[3] << 24) | (m_tintColor.m_uBytes[0] << 16) | (m_tintColor.m_uBytes[1] << 8) |
					m_tintColor.m_uBytes[2];
	g_imageQuad[0].color = color;
	g_imageQuad[1].color = color;
	g_imageQuad[2].color = color;
	g_imageQuad[3].color = color;

	g_imageQuad[0].specular = 0xffffffff;
	g_imageQuad[1].specular = 0xffffffff;
	g_imageQuad[2].specular = 0xffffffff;
	g_imageQuad[3].specular = 0xffffffff;

	LegoFloat tileLeft = 0.0f;
	for (LegoU32 row = 0; row < m_tileColumnCount; row++) {
		LegoFloat tileTop = 0.0f;
		LegoFloat tileRight;

		for (LegoU32 column = 0; column < m_tileRowCount; column++) {
			LegoFloat tileBottom;
			LegoFloat tileWidth = static_cast<LegoFloat>(m_tileWidths[row]);
			LegoFloat tileHeight = static_cast<LegoFloat>(m_tileHeights[column]);
			tileRight = tileLeft + tileWidth;
			tileBottom = tileTop + tileHeight;

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

				LegoU32 index = row * m_tileRowCount + column;
				(p_renderer->*p_renderer->m_applyMaterialFn)(&m_materials[index]);
				p_renderer->SetCurrentTexture(&m_texture[index]);

				LegoFloat invTileWidth = 1.0f / tileWidth;
				LegoFloat invTileHeight = 1.0f / tileHeight;

				g_imageQuad[0].sx = (clippedLeft - sourceLeft) * scaleX + destLeft;
				g_imageQuad[0].sy = (clippedTop - sourceTop) * scaleY + destTop;
				g_imageQuad[0].tu = (clippedLeft - tileLeft) * invTileWidth;
				g_imageQuad[0].tv = (clippedTop - tileTop) * invTileHeight;

				g_imageQuad[1].sx = (clippedLeft - sourceLeft) * scaleX + destLeft;
				g_imageQuad[1].sy = (clippedBottom - sourceTop) * scaleY + destTop;
				g_imageQuad[1].tu = (clippedLeft - tileLeft) * invTileWidth;
				g_imageQuad[1].tv = (clippedBottom - tileTop) * invTileHeight;

				g_imageQuad[2].sx = (clippedRight - sourceLeft) * scaleX + destLeft;
				g_imageQuad[2].sy = (clippedTop - sourceTop) * scaleY + destTop;
				g_imageQuad[2].tu = (clippedRight - tileLeft) * invTileWidth;
				g_imageQuad[2].tv = (clippedTop - tileTop) * invTileHeight;

				g_imageQuad[3].sx = (clippedRight - sourceLeft) * scaleX + destLeft;
				g_imageQuad[3].sy = (clippedBottom - sourceTop) * scaleY + destTop;
				g_imageQuad[3].tu = (clippedRight - tileLeft) * invTileWidth;
				g_imageQuad[3].tv = (clippedBottom - tileTop) * invTileHeight;

				p_renderer->DrawTriangleStrip(g_imageQuad, sizeOfArray(g_imageQuad));
			}

			tileTop = tileBottom;
		}

		tileLeft = tileRight;
	}
}

// FUNCTION: GOLDP 0x10005ae0
GolD3DTexture* GolImage::GetTile(LegoU32 p_row, LegoU32 p_column)
{
	return &m_texture[p_row * m_tileRowCount + p_column];
}

// STUB: GOLDP 0x10005b00
void GolImage::UploadTiles()
{
	GolSurfaceFormat textureFormat = m_surface.GetTextureFormat();

	LegoU8* sourcePixels;
	LegoU32 sourcePitch;
	m_surface.LockPixels(&sourcePixels, &sourcePitch, GolSurface::c_lockRequestRead | GolSurface::c_lockRequestWrite);

	ColorRGBA* paletteEntries;
	LegoU32 paletteSize;
	if (textureFormat.m_paletteMask != 0) {
		paletteEntries = m_surface.GetPaletteEntries();
		paletteSize = m_surface.GetPaletteSize();
	}
	else {
		paletteEntries = NULL;
		paletteSize = 0;
	}

	ColorRGBA* colorKey;
	if (m_flags & GolTexture::c_textureFlagColorKeyed) {
		colorKey = &m_colorKey;
		if (m_renderer->GetFlags() & GolRenderDevice::c_flagBlackColorKey) {
			g_tileImgFile.SetColorKeyReplacement(g_transparentBlack);
		}
		else {
			g_tileImgFile.SetColorKeyReplacement(*colorKey);
		}
	}
	else {
		colorKey = NULL;
	}

	LegoU32 sourceX = 0;
	LegoU32 copyWidth = 0;
	LegoU32 copyHeight = 0;
	LegoU32 row;
	LegoU32 column;
	for (row = 0; row < m_tileColumnCount; row++) {
		LegoU32 sourceY = 0;
		for (column = 0; column < m_tileRowCount; column++) {
			GolD3DTexture* texture = GetTile(row, column);
			copyWidth = texture->GetWidth();

			LegoU32 remainingWidth = m_surface.GetWidth() - sourceX;
			if (copyWidth > remainingWidth) {
				copyWidth = remainingWidth;
			}

			copyHeight = texture->GetHeight();
			LegoU32 remainingHeight = m_surface.GetHeight() - sourceY;
			if (copyHeight > remainingHeight) {
				copyHeight = remainingHeight;
			}

			LegoU8* source = sourcePixels + sourceY * sourcePitch + ((textureFormat.m_bitsPerPixel * sourceX + 7) >> 3);

			g_tileImgFile.SetImageInfo(textureFormat, copyWidth, copyHeight, sourcePitch, paletteEntries, paletteSize);
			g_tileImgFile.SetRemapPureBlack(TRUE);

			LegoU8* destPixels;
			LegoU32 destPitch;
			texture->LockPixels(&destPixels, &destPitch, GolSurface::c_lockRequestWrite);

			GolPaletteBase* destPalette = NULL;
			if (m_format.m_paletteMask != 0) {
				destPalette = texture->GetPalette();
			}

			g_tileImgFile
				.ConvertImage(source, destPixels, copyWidth, copyHeight, destPitch, m_format, destPalette, 0, colorKey);
			texture->UnlockPixels();

			sourceY += copyHeight;
		}

		sourceX += copyWidth;
	}

	m_surface.UnlockPixels();
}
