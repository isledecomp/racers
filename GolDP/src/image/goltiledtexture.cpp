#include "image/goltiledtexture.h"

#include "golbmpfile.h"
#include "golimgfile.h"
#include "goltexture.h"
#include "goltgafile.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexture.h"

DECOMP_SIZE_ASSERT(FourBytes, 0x04)
DECOMP_SIZE_ASSERT(GolTiledTexture, 0x50)
DECOMP_SIZE_ASSERT(GolTiledTexture::TileImageName, 0x09)

extern const ColorRGBA g_transparentBlack;
extern GolTgaFile g_textureTgaFile;
extern GolBmpFile g_textureBmpFile;

// FUNCTION: GOLDP 0x1001f1e0
GolTiledTexture::GolTiledTexture()
{
	Reset();
}

// FUNCTION: GOLDP 0x1001f2a0
GolTiledTexture::~GolTiledTexture()
{
	Reset();
}

// FUNCTION: GOLDP 0x1001f2f0
void GolTiledTexture::Reset()
{
	m_renderer = NULL;
	m_tileColumnCount = 0;
	m_tileRowCount = 0;
	m_width = 0;
	m_height = 0;
	m_stateFlags = c_stateModulate | c_stateFlatShaded;
	m_flags = 0;
	m_colorKey.m_red = 0;
	m_colorKey.m_grn = 0;
	m_colorKey.m_blu = 0;
	m_colorKey.m_alp = 0xff;
	m_tintColor.m_uBytes[0] = 0xff;
	m_tintColor.m_uBytes[1] = 0xff;
	m_tintColor.m_uBytes[2] = 0xff;
	m_tintColor.m_uBytes[3] = 0xff;
	m_tileWidths = 0;
	m_tileHeights = 0;
}

// FUNCTION: GOLDP 0x1001f330
void GolTiledTexture::Load()
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

	imageFile->Open(imageName.m_chars);

	imageFormat = imageFile->GetTextureFormat();
	m_renderer->SelectTextureFormat(imageFormat, &m_format, m_flags & GolTexture::c_textureFlagColorKeyed);
	m_width = imageFile->GetWidth();
	m_height = imageFile->GetHeight();
	ComputeTileLayout();

	if (m_flags & GolTexture::c_textureFlagColorKeyed) {
		if (m_renderer->GetFlags() & GolRenderDevice::c_flagBlackColorKey) {
			imageFile->SetColorKeyReplacement(g_transparentBlack);
		}
		else {
			imageFile->SetColorKeyReplacement(m_colorKey);
		}

		imageFile->LoadTiledTexture(this, m_flags & GolTexture::c_textureFlagFlipVertically, &m_colorKey);
	}
	else {
		imageFile->LoadTiledTexture(this, m_flags & GolTexture::c_textureFlagFlipVertically, NULL);
	}

	imageFile->Destroy();
}

inline static LegoU32 RoundUpTileSize(LegoU32 p_size)
{
	LegoU32 size = 1;
	for (LegoS32 bit = 0; bit < 32; bit++) {
		if (size >= p_size) {
			return size;
		}
		size <<= 1;
	}

	return p_size;
}

inline static LegoU32 ChooseTileSize(LegoU32 p_remaining, LegoU32 p_minimum, LegoU32 p_maximum)
{
	LegoU32 minimum = p_minimum;
	if (minimum < 4) {
		minimum = 4;
	}
	if (p_remaining < minimum) {
		return minimum;
	}
	if (p_remaining > p_maximum) {
		return p_maximum;
	}

	LegoU32 size = RoundUpTileSize(p_remaining);
	if (p_remaining < size - minimum) {
		size >>= 1;
		if (size < minimum) {
			size = minimum;
		}
	}

	return size;
}

// FUNCTION: GOLDP 0x1001f430
void GolTiledTexture::ComputeTileLayout()
{
	LegoBool32 supportsNonSquareTextures = m_renderer->TexturesMustBeSquare();
	LegoBool32 mustBePowerOfTwo = m_renderer->TextureSizesMustBePowersOfTwo();
	if (mustBePowerOfTwo && supportsNonSquareTextures) {
		ComputeSquareTileLayout();
		return;
	}

	LegoU32 tileSize = 0;
	LegoU32 minWidth = m_renderer->GetMinimumTextureWidth(m_format.m_bitsPerPixel);
	LegoU32 maxWidth = m_renderer->GetMaximumTextureWidth(m_format.m_bitsPerPixel);
	LegoU32 minHeight = m_renderer->GetMinimumTextureHeight(m_format.m_bitsPerPixel);
	LegoU32 maxHeight = m_renderer->GetMaximumTextureHeight(m_format.m_bitsPerPixel);

	if (!mustBePowerOfTwo) {
		if (supportsNonSquareTextures) {
			m_tileColumnCount = (m_width - 1) / maxWidth + 1;
			m_tileRowCount = (m_height - 1) / maxHeight + 1;
		}
		else {
			tileSize = maxHeight < maxWidth ? maxHeight : maxWidth;
			m_tileColumnCount = (m_width - 1) / tileSize + 1;
			m_tileRowCount = (m_height - 1) / tileSize + 1;
		}
	}
	else if (!supportsNonSquareTextures) {
		tileSize = m_width > m_height ? m_height : m_width;
		tileSize = RoundUpTileSize(tileSize);
		if (tileSize < minHeight) {
			tileSize = minHeight;
		}
		if (tileSize > maxWidth) {
			tileSize = maxWidth;
		}
		m_tileColumnCount = (m_width - 1) / tileSize + 1;
		m_tileRowCount = (m_height - 1) / tileSize + 1;
	}

	AllocateTileWidths();
	AllocateTileHeights();
	AllocateTileArrays();

	LegoU32 x = 0;
	for (LegoU32 column = 0; column < m_tileColumnCount; column++) {
		LegoU32 width;
		if (mustBePowerOfTwo) {
			if (supportsNonSquareTextures) {
				width = ChooseTileSize(m_width - x, minWidth, maxWidth);
			}
			else {
				width = tileSize;
			}
		}
		else if (supportsNonSquareTextures) {
			if (column == m_tileColumnCount - 1) {
				width = m_width - maxWidth * (m_tileColumnCount - 1);
			}
			else {
				width = maxWidth;
			}
		}
		else {
			width = tileSize;
		}
		if (width < minWidth) {
			width = minWidth;
		}

		LegoU32 y = 0;
		for (LegoU32 row = 0; row < m_tileRowCount; row++) {
			LegoU32 height;
			if (mustBePowerOfTwo) {
				if (supportsNonSquareTextures) {
					height = ChooseTileSize(m_height - y, minWidth, maxWidth);
				}
				else {
					height = tileSize;
				}
			}
			else {
				if (!supportsNonSquareTextures) {
					height = tileSize;
				}
				else if (row == m_tileRowCount - 1) {
					height = m_height - maxHeight * (m_tileRowCount - 1);
				}
				else {
					height = maxHeight;
				}
			}
			if (height < minHeight) {
				height = minHeight;
			}

			if (mustBePowerOfTwo) {
				width = RoundUpTileSize(width);
				height = RoundUpTileSize(height);
			}
			if (!supportsNonSquareTextures && height != width) {
				if (height < width) {
					height = width;
				}
				else {
					width = height;
				}
			}
			if (row == 0) {
				m_tileWidths[column] = width;
			}
			if (column == 0) {
				m_tileHeights[row] = height;
			}
			y += height;
		}
		x += width;
	}

	CreateTiles();
	m_stateFlags |= c_stateCreated | c_stateFlagBit7 | c_stateFlagBit9;
}

// FUNCTION: GOLDP 0x1001f790
void GolTiledTexture::ComputeSquareTileLayout()
{
	LegoU32 minWidth = m_renderer->GetMinimumTextureWidth(m_format.m_bitsPerPixel);
	LegoU32 maxWidth = m_renderer->GetMaximumTextureWidth(m_format.m_bitsPerPixel);
	LegoU32 minHeight = m_renderer->GetMinimumTextureHeight(m_format.m_bitsPerPixel);
	LegoU32 maxHeight = m_renderer->GetMaximumTextureHeight(m_format.m_bitsPerPixel);
	LegoU32 sizes[7];
	LegoBool32 used[7];
	LegoU32 position;
	LegoU32 size;
	LegoU32 i;
	LegoU32 n;
	LegoS32 j;
	LegoS32 k;

	if (m_width < m_height) {
		m_tileColumnCount = 0;
		for (position = 0; position < m_width; m_tileColumnCount++) {
			position += ChooseTileSize(m_width - position, minWidth, maxWidth);
		}

		AllocateTileWidths();

		for (position = 0, i = 0; position < m_width; i++) {
			m_tileWidths[i] = ChooseTileSize(m_width - position, minWidth, maxWidth);
			position += m_tileWidths[i];
		}

		for (i = 0; i < m_tileColumnCount; i++) {
			::memset(used, 0, sizeof(used));

			for (k = 0; k < 7; k++) {
				LegoU32 scaled;
				if (k < 3) {
					scaled = (LegoU32) m_tileWidths[i] >> (3 - k);
				}
				else {
					scaled = (LegoU32) m_tileWidths[i] << (k - 3);
				}

				if (i == 0) {
					sizes[k] = scaled;
					used[k] = TRUE;
				}
				else {
					for (j = 0; j < 7; j++) {
						if (scaled == sizes[j]) {
							used[j] = TRUE;
						}
					}
				}
			}

			for (j = 0; j < 7; j++) {
				if (!used[j]) {
					sizes[j] = 0;
				}
			}
		}

		// The original scans for the first non-zero size and discards the result.
		for (n = 0; n < 7 && !sizes[n]; n++) {
		}

		m_tileRowCount = 0;
		size = 0;
		for (position = 0; position < m_height; m_tileRowCount++) {
			size = ChooseTileSize(m_height - position, minHeight, maxHeight);
			LegoU32 best = 7;
			LegoU32 bestDiff = 0xffffffff;
			for (n = 0; n < 7; n++) {
				LegoS32 diff = sizes[n] - size;
				if (diff < 0) {
					diff = -diff;
				}
				if (sizes[n] > 0 && (LegoU32) diff < bestDiff) {
					best = n;
					bestDiff = diff;
				}
			}
			position += sizes[best];
		}

		AllocateTileHeights();

		for (position = 0, i = 0; position < m_height; i++) {
			size = ChooseTileSize(m_height - position, minHeight, maxHeight);
			LegoU32 best = 7;
			LegoU32 bestDiff = 0xffffffff;
			for (n = 0; n < 7; n++) {
				LegoS32 diff = sizes[n] - size;
				if (diff < 0) {
					diff = -diff;
				}
				if (sizes[n] > 0 && (LegoU32) diff < bestDiff) {
					best = n;
					bestDiff = diff;
				}
			}
			m_tileHeights[i] = sizes[best];
			position += sizes[best];
		}
	}
	else {
		m_tileRowCount = 0;
		for (position = 0; position < m_height; m_tileRowCount++) {
			position += ChooseTileSize(m_height - position, minHeight, maxHeight);
		}

		AllocateTileHeights();

		for (position = 0, i = 0; position < m_height; i++) {
			m_tileHeights[i] = ChooseTileSize(m_height - position, minHeight, maxHeight);
			position += m_tileHeights[i];
		}

		for (i = 0; i < m_tileRowCount; i++) {
			::memset(used, 0, sizeof(used));

			for (k = 0; k < 7; k++) {
				LegoU32 scaled;
				if (k < 3) {
					scaled = (LegoU32) m_tileHeights[i] >> (3 - k);
				}
				else {
					scaled = (LegoU32) m_tileHeights[i] << (k - 3);
				}

				if (i == 0) {
					sizes[k] = scaled;
					used[k] = TRUE;
				}
				else {
					for (j = 0; j < 7; j++) {
						if (scaled == sizes[j]) {
							used[j] = TRUE;
						}
					}
				}
			}

			for (j = 0; j < 7; j++) {
				if (!used[j]) {
					sizes[j] = 0;
				}
			}
		}

		// The original scans for the first non-zero size and discards the result.
		for (n = 0; n < 7 && !sizes[n]; n++) {
		}

		m_tileColumnCount = 0;
		size = 0;
		for (position = 0; position < m_width; m_tileColumnCount++) {
			size = ChooseTileSize(m_width - position, minWidth, maxWidth);
			LegoU32 best = 7;
			LegoU32 bestDiff = 0xffffffff;
			for (n = 0; n < 7; n++) {
				LegoS32 diff = sizes[n] - size;
				if (diff < 0) {
					diff = -diff;
				}
				if (sizes[n] > 0 && (LegoU32) diff < bestDiff) {
					best = n;
					bestDiff = diff;
				}
			}
			position += sizes[best];
		}

		AllocateTileWidths();

		for (position = 0, i = 0; position < m_width; i++) {
			size = ChooseTileSize(m_width - position, minWidth, maxWidth);
			LegoU32 best = 7;
			LegoU32 bestDiff = 0xffffffff;
			for (n = 0; n < 7; n++) {
				LegoS32 diff = sizes[n] - size;
				if (diff < 0) {
					diff = -diff;
				}
				if (sizes[n] > 0 && (LegoU32) diff < bestDiff) {
					best = n;
					bestDiff = diff;
				}
			}
			m_tileWidths[i] = sizes[best];
			position += sizes[best];
		}
	}

	AllocateTileArrays();
	CreateTiles();
	m_stateFlags |= c_stateCreated | c_stateFlagBit7 | c_stateFlagBit9;
}

// FUNCTION: GOLDP 0x1001fde0
void GolTiledTexture::CreateTiles()
{
	for (LegoU32 row = 0; row < m_tileColumnCount; row++) {
		for (LegoU32 column = 0; column < m_tileRowCount; column++) {
			GolD3DTexture* texture = GetTile(row, column);
			if (texture->GetPixelFlags() & GolSurface::c_lockRequestRead) {
				continue;
			}

			LegoU16 flags = m_flags;
			if (m_renderer->VTable0x110()) {
				flags |= GolTexture::c_textureFlagBit6;
			}
			if ((flags & GolTexture::c_textureFlagColorKeyed) &&
				(m_renderer->GetFlags() & GolRenderDevice::c_flagBlackColorKey)) {
				flags |= GolTexture::c_textureFlagBlackColorKey;
			}

			texture->m_textureFlags = flags;
			texture->m_mipmapCount = 0;
			texture->m_colorKey = m_colorKey;
			flags |= GolTexture::c_textureFlagColorKeyDirty;
			texture->m_colorKey.m_alp = 0;
			texture->m_textureFlags = flags;
			CreateTile(row, column, &m_format);
		}
	}
}
