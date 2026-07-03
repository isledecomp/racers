#include "material/goltexturelist.h"

#include "golbmpfile.h"
#include "golstream.h"
#include "goltgafile.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexture.h"

#include <string.h>

// GLOBAL: LEGORACERS 0x004c2930
GolTgaFile g_textureTgaFile;

// GLOBAL: LEGORACERS 0x004c2f10
GolBmpFile g_textureBmpFile;

// FUNCTION: LEGORACERS 0x004146a0
void GolTextureList::LoadTextures()
{
	GolTextureSourceItem sourceItem;
	GolSurfaceFormat textureFormat;
	LegoChar textureName[sizeof(GolName) + 1];

	if (m_unk0x14 != NULL) {
		for (LegoU32 i = 0; i < m_numItems; i++) {
			GolTexture* texture = GetItem(i);
			if (texture->GetPixelFlags() & GolSurface::c_lockRequestRead) {
				continue;
			}

			m_unk0x14->VTable0x00(i, &sourceItem);

			LegoU16 flags = sourceItem.m_flags;
			if (m_renderer->VTable0x110()) {
				flags |= GolTexture::c_unk0x36Bit6;
			}
			if ((flags & GolTexture::c_unk0x36Bit5) && (m_renderer->GetFlags() & GolD3DRenderDevice::c_flagBit9)) {
				flags |= GolTexture::c_unk0x36Bit7;
			}

			LegoU16 textureFlags = flags;
			texture->m_unk0x36 = flags;
			LegoU16 mipmapCount = sourceItem.m_mipmapCount;
			texture->m_unk0x34 = mipmapCount;
			textureFlags |= GolTexture::c_unk0x36Bit11;
			texture->m_unk0x36 = textureFlags;
			texture->m_colorKey = sourceItem.m_colorKey;
			texture->m_colorKey.m_alp = 0;

			m_renderer->SelectTextureFormat(
				sourceItem.m_textureFormat,
				&textureFormat,
				textureFlags & GolTexture::c_unk0x36Bit5
			);
			VTable0x18(i, textureFormat, sourceItem.m_width, sourceItem.m_height);
			m_unk0x14->VTable0x04(i, 0, texture);
		}
		return;
	}

	if (m_unk0x18 != NULL && g_hashTable != NULL) {
		g_hashTable->SetCurrentEntry(m_unk0x18);
	}

	for (LegoU32 i = 0; i < m_numItems; i++) {
		GolD3DTexture* texture = GetItem(i);
		if (texture->GetPixelFlags() & GolSurface::c_lockRequestRead) {
			continue;
		}

		LegoChar firstChar = texture->m_name[0];
		::memcpy(textureName, texture->m_name, sizeof(GolName));
		if (firstChar == '\0') {
			continue;
		}
		textureName[sizeof(GolName)] = '\0';

		LegoU8 textureFlags = static_cast<LegoU8>(texture->m_unk0x36);
		GolImgFile* imageFile = &g_textureBmpFile;
		if (!(textureFlags & GolTexture::c_unk0x36Bit3)) {
			imageFile = &g_textureTgaFile;
		}

		imageFile->VTable0x08(textureName);
		texture->VTable0x30(*m_renderer, imageFile);
		imageFile->Destroy();
	}
}
