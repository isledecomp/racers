#include "image/whitebaffoon0x50.h"

#include "golbmpfile.h"
#include "golddune0x38.h"
#include "golimgfile.h"
#include "goltgafile.h"
#include "render/gold3drenderdevice.h"
#include "surface/purpledune0x7c.h"

DECOMP_SIZE_ASSERT(FourBytes, 0x04)
DECOMP_SIZE_ASSERT(WhiteBaffoon0x50, 0x50)
DECOMP_SIZE_ASSERT(WhiteBaffoon0x50::WhiteBaffoonImageName, 0x09)

extern const ColorRGBA g_unk0x10057668;
extern GolTgaFile g_unk0x10063ca0;
extern GolBmpFile g_unk0x10064280;

// FUNCTION: GOLDP 0x1001f1e0
WhiteBaffoon0x50::WhiteBaffoon0x50()
{
	Reset();
}

// FUNCTION: GOLDP 0x1001f2a0
WhiteBaffoon0x50::~WhiteBaffoon0x50()
{
	Reset();
}

// FUNCTION: GOLDP 0x1001f2f0
void WhiteBaffoon0x50::Reset()
{
	m_renderer = NULL;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_width = 0;
	m_height = 0;
	m_unk0x3c = c_flagBit5 | c_flagBit1;
	m_flags = 0;
	m_colorKey.m_red = 0;
	m_colorKey.m_grn = 0;
	m_colorKey.m_blu = 0;
	m_colorKey.m_alp = 0xff;
	m_unk0x4a.m_uBytes[0] = 0xff;
	m_unk0x4a.m_uBytes[1] = 0xff;
	m_unk0x4a.m_uBytes[2] = 0xff;
	m_unk0x4a.m_uBytes[3] = 0xff;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
}

// STUB: GOLDP 0x1001f330
void WhiteBaffoon0x50::VTable0x10()
{
	WhiteBaffoon0x50::WhiteBaffoonImageName imageName;
	imageName.m_name[0] = m_name[0];
	imageName.m_name[1] = m_name[1];
	imageName.m_chars[8] = 0;

	GolImgFile* imageFile = &g_unk0x10063ca0;
	if (!(m_flags & c_flagBit4)) {
		imageFile = &g_unk0x10064280;
	}

	imageFile->VTable0x08(imageName.m_chars);

	GolSurfaceFormat imageFormat = imageFile->GetTextureFormat();
	m_renderer->SelectTextureFormat(imageFormat, &m_unk0x0c, m_flags & c_flagBit5);
	m_width = imageFile->GetWidth();
	m_height = imageFile->GetHeight();
	FUN_1001f430();

	ColorRGBA* colorKey = NULL;
	if (m_flags & c_flagBit5) {
		if (m_renderer->GetFlags() & GolRenderDevice::c_flagBit9) {
			imageFile->SetUnk0x0a0(g_unk0x10057668);
		}
		else {
			imageFile->SetUnk0x0a0(m_colorKey);
		}

		colorKey = &m_colorKey;
	}

	imageFile->VTable0x1c(this, m_flags & c_flagBit2, colorKey);
	imageFile->Destroy();
}

// STUB: GOLDP 0x1001f430
void WhiteBaffoon0x50::FUN_1001f430()
{
	// The legacy vtable name is inverted; renderer texture setup uses FALSE as square-only.
	LegoBool32 supportsNonSquareTextures = m_renderer->TexturesMustBeSquare();
	LegoBool32 mustBePowerOfTwo = m_renderer->TextureSizesMustBePowersOfTwo();
	if (mustBePowerOfTwo && !supportsNonSquareTextures) {
		FUN_1001f790();
		return;
	}

	LegoU32 bitsPerPixel = m_unk0x0c.m_bitsPerPixel;
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

		m_unk0x2c = (m_width + tileWidth - 1) / tileWidth;
		m_unk0x30 = (m_height + tileHeight - 1) / tileHeight;

		VTable0x00();
		VTable0x04();
		VTable0x08();

		for (i = 0; i < m_unk0x2c; i++) {
			LegoU32 size = tileWidth;
			if (i + 1 == m_unk0x2c) {
				LegoU32 used = tileWidth * i;
				if (used < m_width) {
					size = m_width - used;
				}
			}

			if (size < minWidth) {
				size = minWidth;
			}

			m_unk0x04[i] = size;
		}

		for (i = 0; i < m_unk0x30; i++) {
			LegoU32 size = tileHeight;
			if (i + 1 == m_unk0x30) {
				LegoU32 used = tileHeight * i;
				if (used < m_height) {
					size = m_height - used;
				}
			}

			if (size < minHeight) {
				size = minHeight;
			}

			m_unk0x08[i] = size;
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
		m_unk0x2c = 0;
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
			m_unk0x2c++;
		}

		position = 0;
		m_unk0x30 = 0;
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
			m_unk0x30++;
		}

		VTable0x00();
		VTable0x04();
		VTable0x08();

		position = 0;
		for (i = 0; i < m_unk0x2c; i++) {
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

			m_unk0x04[i] = size;
			position += size;
		}

		position = 0;
		for (i = 0; i < m_unk0x30; i++) {
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

			m_unk0x08[i] = size;
			position += size;
		}
	}

	FUN_1001fde0();
	m_unk0x3c |= 0x281;
}

// STUB: GOLDP 0x1001f790
void WhiteBaffoon0x50::FUN_1001f790()
{
	LegoU32 bitsPerPixel = m_unk0x0c.m_bitsPerPixel;
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

	m_unk0x2c = (m_width + tileSize - 1) / tileSize;
	m_unk0x30 = (m_height + tileSize - 1) / tileSize;

	VTable0x00();
	VTable0x04();
	VTable0x08();

	for (row = 0; row < m_unk0x2c; row++) {
		m_unk0x04[row] = tileSize;
	}
	for (column = 0; column < m_unk0x30; column++) {
		m_unk0x08[column] = tileSize;
	}

	FUN_1001fde0();
	m_unk0x3c |= 0x281;
}

// FUNCTION: GOLDP 0x1001fde0
void WhiteBaffoon0x50::FUN_1001fde0()
{
	for (LegoU32 row = 0; row < m_unk0x2c; row++) {
		for (LegoU32 column = 0; column < m_unk0x30; column++) {
			PurpleDune0x7c* texture = VTable0x1c(row, column);
			if (texture->GetPixelFlags() & SilverDune0x30::c_lockRequestRead) {
				continue;
			}

			LegoU16 flags = m_flags;
			if (m_renderer->VTable0x110()) {
				flags |= GoldDune0x38::c_unk0x36Bit6;
			}
			if ((flags & c_flagBit5) && (m_renderer->GetFlags() & GolRenderDevice::c_flagBit9)) {
				flags |= GoldDune0x38::c_unk0x36Bit7;
			}

			texture->m_unk0x36 = flags;
			texture->m_unk0x34 = 0;
			texture->m_colorKey = m_colorKey;
			flags |= GoldDune0x38::c_unk0x36Bit11;
			texture->m_colorKey.m_alp = 0;
			texture->m_unk0x36 = flags;
			VTable0x0c(row, column, &m_unk0x0c);
		}
	}
}
