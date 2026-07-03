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

extern const ColorRGBA g_unk0x10057668;
extern GolTgaFile g_unk0x10063ca0;
extern GolBmpFile g_unk0x10064280;

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
	m_textureFlags = c_flagBit5 | c_flagBit1;
	m_flags = 0;
	m_colorKey.m_red = 0;
	m_colorKey.m_grn = 0;
	m_colorKey.m_blu = 0;
	m_colorKey.m_alp = 0xff;
	m_unk0x4a.m_uBytes[0] = 0xff;
	m_unk0x4a.m_uBytes[1] = 0xff;
	m_unk0x4a.m_uBytes[2] = 0xff;
	m_unk0x4a.m_uBytes[3] = 0xff;
	m_tileWidths = 0;
	m_tileHeights = 0;
}

// FUNCTION: GOLDP 0x1001f330
void GolTiledTexture::VTable0x10()
{
	GolSurfaceFormat imageFormat;
	GolTiledTexture::TileImageName imageName;
	imageName.m_name[0] = m_name[0];
	imageName.m_name[1] = m_name[1];
	imageName.m_chars[8] = 0;

	GolImgFile* imageFile = &g_unk0x10063ca0;
	if (!(m_flags & c_flagBit4)) {
		imageFile = &g_unk0x10064280;
	}

	imageFile->Open(imageName.m_chars);

	imageFormat = imageFile->GetTextureFormat();
	m_renderer->SelectTextureFormat(imageFormat, &m_format, m_flags & c_flagBit5);
	m_width = imageFile->GetWidth();
	m_height = imageFile->GetHeight();
	FUN_1001f430();

	if (m_flags & c_flagBit5) {
		if (m_renderer->GetFlags() & GolRenderDevice::c_flagBit9) {
			imageFile->SetColorKeyReplacement(g_unk0x10057668);
		}
		else {
			imageFile->SetColorKeyReplacement(m_colorKey);
		}

		imageFile->LoadTiledTexture(this, m_flags & c_flagBit2, &m_colorKey);
	}
	else {
		imageFile->LoadTiledTexture(this, m_flags & c_flagBit2, NULL);
	}

	imageFile->Destroy();
}

// STUB: GOLDP 0x1001f430
void GolTiledTexture::FUN_1001f430()
{
	// The legacy vtable name is inverted; renderer texture setup uses FALSE as square-only.
	LegoBool32 supportsNonSquareTextures = m_renderer->TexturesMustBeSquare();
	LegoBool32 mustBePowerOfTwo = m_renderer->TextureSizesMustBePowersOfTwo();
	if (mustBePowerOfTwo && !supportsNonSquareTextures) {
		FUN_1001f790();
		return;
	}

	LegoU32 bitsPerPixel = m_format.m_bitsPerPixel;
	LegoU32 minWidth = m_renderer->GetMinimumTextureWidth(bitsPerPixel);
	LegoU32 maxWidth = m_renderer->GetMaximumTextureWidth(bitsPerPixel);
	LegoU32 minHeight = m_renderer->GetMinimumTextureHeight(bitsPerPixel);
	LegoU32 maxHeight = m_renderer->GetMaximumTextureHeight(bitsPerPixel);
	LegoU32 i;
	LegoU32 j;

	if (!mustBePowerOfTwo) {
		LegoU32 tileWidth = maxWidth;
		LegoU32 tileHeight = maxHeight;

		if (!supportsNonSquareTextures) {
			tileWidth = maxWidth < maxHeight ? maxWidth : maxHeight;
			LegoU32 minimum = minWidth > minHeight ? minWidth : minHeight;
			if (tileWidth < minimum) {
				tileWidth = minimum;
			}

			tileHeight = tileWidth;
		}

		m_tileColumnCount = (m_width + tileWidth - 1) / tileWidth;
		m_tileRowCount = (m_height + tileHeight - 1) / tileHeight;

		VTable0x00();
		VTable0x04();
		VTable0x08();

		for (i = 0; i < m_tileColumnCount; i++) {
			LegoU32 size = tileWidth;
			if (i + 1 == m_tileColumnCount) {
				LegoU32 used = tileWidth * i;
				if (used < m_width) {
					size = m_width - used;
				}
			}

			if (size < minWidth) {
				size = minWidth;
			}

			m_tileWidths[i] = size;
		}

		for (i = 0; i < m_tileRowCount; i++) {
			LegoU32 size = tileHeight;
			if (i + 1 == m_tileRowCount) {
				LegoU32 used = tileHeight * i;
				if (used < m_height) {
					size = m_height - used;
				}
			}

			if (size < minHeight) {
				size = minHeight;
			}

			m_tileHeights[i] = size;
		}
	}
	else {
		if (minWidth < 4) {
			minWidth = 4;
		}
		if (maxWidth < minWidth) {
			maxWidth = minWidth;
		}
		if (minHeight < 4) {
			minHeight = 4;
		}
		if (maxHeight < minHeight) {
			maxHeight = minHeight;
		}

		LegoU32 position = 0;
		m_tileColumnCount = 0;
		while (position < m_width) {
			LegoU32 remaining = m_width - position;
			LegoU32 size;
			if (remaining < minWidth) {
				size = minWidth;
			}
			else if (remaining > maxWidth) {
				size = maxWidth;
			}
			else {
				size = 1;
				for (i = 0; i < 32 && size < remaining; i++) {
					size <<= 1;
				}

				if (size > maxWidth) {
					size = maxWidth;
				}
				if (remaining < size - minWidth) {
					size >>= 1;
					if (size < minWidth) {
						size = minWidth;
					}
				}
			}

			position += size;
			m_tileColumnCount++;
		}

		position = 0;
		m_tileRowCount = 0;
		while (position < m_height) {
			LegoU32 remaining = m_height - position;
			LegoU32 size;
			if (remaining < minHeight) {
				size = minHeight;
			}
			else if (remaining > maxHeight) {
				size = maxHeight;
			}
			else {
				size = 1;
				for (i = 0; i < 32 && size < remaining; i++) {
					size <<= 1;
				}

				if (size > maxHeight) {
					size = maxHeight;
				}
				if (remaining < size - minHeight) {
					size >>= 1;
					if (size < minHeight) {
						size = minHeight;
					}
				}
			}

			position += size;
			m_tileRowCount++;
		}

		VTable0x00();
		VTable0x04();
		VTable0x08();

		position = 0;
		for (i = 0; i < m_tileColumnCount; i++) {
			LegoU32 remaining = m_width - position;
			LegoU32 size;
			if (remaining < minWidth) {
				size = minWidth;
			}
			else if (remaining > maxWidth) {
				size = maxWidth;
			}
			else {
				size = 1;
				for (j = 0; j < 32 && size < remaining; j++) {
					size <<= 1;
				}

				if (size > maxWidth) {
					size = maxWidth;
				}
				if (remaining < size - minWidth) {
					size >>= 1;
					if (size < minWidth) {
						size = minWidth;
					}
				}
			}

			m_tileWidths[i] = size;
			position += size;
		}

		position = 0;
		for (i = 0; i < m_tileRowCount; i++) {
			LegoU32 remaining = m_height - position;
			LegoU32 size;
			if (remaining < minHeight) {
				size = minHeight;
			}
			else if (remaining > maxHeight) {
				size = maxHeight;
			}
			else {
				size = 1;
				for (j = 0; j < 32 && size < remaining; j++) {
					size <<= 1;
				}

				if (size > maxHeight) {
					size = maxHeight;
				}
				if (remaining < size - minHeight) {
					size >>= 1;
					if (size < minHeight) {
						size = minHeight;
					}
				}
			}

			m_tileHeights[i] = size;
			position += size;
		}
	}

	FUN_1001fde0();
	m_textureFlags |= 0x281;
}

// STUB: GOLDP 0x1001f790
void GolTiledTexture::FUN_1001f790()
{
	LegoU32 bitsPerPixel = m_format.m_bitsPerPixel;
	LegoU32 minWidth = m_renderer->GetMinimumTextureWidth(bitsPerPixel);
	LegoU32 maxWidth = m_renderer->GetMaximumTextureWidth(bitsPerPixel);
	LegoU32 minHeight = m_renderer->GetMinimumTextureHeight(bitsPerPixel);
	LegoU32 maxHeight = m_renderer->GetMaximumTextureHeight(bitsPerPixel);
	LegoU32 i;
	LegoU32 row;
	LegoU32 column;

	LegoU32 minimum = minWidth > minHeight ? minWidth : minHeight;
	if (minimum < 4) {
		minimum = 4;
	}

	LegoU32 maximum = maxWidth < maxHeight ? maxWidth : maxHeight;
	if (maximum < minimum) {
		maximum = minimum;
	}

	LegoU32 remaining = m_width > m_height ? m_width : m_height;
	LegoU32 tileSize;
	if (remaining < minimum) {
		tileSize = minimum;
	}
	else if (remaining > maximum) {
		tileSize = maximum;
	}
	else {
		tileSize = 1;
		for (i = 0; i < 32 && tileSize < remaining; i++) {
			tileSize <<= 1;
		}

		if (tileSize > maximum) {
			tileSize = maximum;
		}
		if (remaining < tileSize - minimum) {
			tileSize >>= 1;
			if (tileSize < minimum) {
				tileSize = minimum;
			}
		}
	}

	m_tileColumnCount = (m_width + tileSize - 1) / tileSize;
	m_tileRowCount = (m_height + tileSize - 1) / tileSize;

	VTable0x00();
	VTable0x04();
	VTable0x08();

	for (row = 0; row < m_tileColumnCount; row++) {
		m_tileWidths[row] = tileSize;
	}
	for (column = 0; column < m_tileRowCount; column++) {
		m_tileHeights[column] = tileSize;
	}

	FUN_1001fde0();
	m_textureFlags |= 0x281;
}

// FUNCTION: GOLDP 0x1001fde0
void GolTiledTexture::FUN_1001fde0()
{
	for (LegoU32 row = 0; row < m_tileColumnCount; row++) {
		for (LegoU32 column = 0; column < m_tileRowCount; column++) {
			GolD3DTexture* texture = VTable0x1c(row, column);
			if (texture->GetPixelFlags() & GolSurface::c_lockRequestRead) {
				continue;
			}

			LegoU16 flags = m_flags;
			if (m_renderer->VTable0x110()) {
				flags |= GolTexture::c_textureFlagBit6;
			}
			if ((flags & c_flagBit5) && (m_renderer->GetFlags() & GolRenderDevice::c_flagBit9)) {
				flags |= GolTexture::c_textureFlagBit7;
			}

			texture->m_textureFlags = flags;
			texture->m_mipmapCount = 0;
			texture->m_colorKey = m_colorKey;
			flags |= GolTexture::c_textureFlagBit11;
			texture->m_colorKey.m_alp = 0;
			texture->m_textureFlags = flags;
			VTable0x0c(row, column, &m_format);
		}
	}
}
