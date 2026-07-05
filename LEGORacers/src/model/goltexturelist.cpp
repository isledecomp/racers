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

	if (m_textureSource != NULL) {
		for (LegoU32 i = 0; i < m_itemCount; i++) {
			GolTexture* texture = GetItem(i);
			if (texture->GetPixelFlags() & GolSurface::c_lockRequestRead) {
				continue;
			}

			m_textureSource->GetTextureDefinition(i, &sourceItem);

			LegoU16 flags = sourceItem.m_flags;
			if (m_renderer->VTable0x110()) {
				flags |= GolTexture::c_textureFlagBit6;
			}
			if ((flags & GolTexture::c_textureFlagColorKeyed) &&
				(m_renderer->GetFlags() & GolD3DRenderDevice::c_flagBlackColorKey)) {
				flags |= GolTexture::c_textureFlagBlackColorKey;
			}

			LegoU16 textureFlags = flags;
			texture->m_textureFlags = flags;
			LegoU16 mipmapCount = sourceItem.m_mipmapCount;
			texture->m_mipmapCount = mipmapCount;
			textureFlags |= GolTexture::c_textureFlagColorKeyDirty;
			texture->m_textureFlags = textureFlags;
			texture->m_colorKey = sourceItem.m_colorKey;
			texture->m_colorKey.m_alp = 0;

			m_renderer->SelectTextureFormat(
				sourceItem.m_textureFormat,
				&textureFormat,
				textureFlags & GolTexture::c_textureFlagColorKeyed
			);
			AllocateTexture(i, textureFormat, sourceItem.m_width, sourceItem.m_height);
			m_textureSource->OnTextureLoaded(i, 0, texture);
		}
		return;
	}

	if (m_nameTableEntry != NULL && g_hashTable != NULL) {
		g_hashTable->SetCurrentEntry(m_nameTableEntry);
	}

	for (LegoU32 i = 0; i < m_itemCount; i++) {
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

		LegoU8 textureFlags = static_cast<LegoU8>(texture->m_textureFlags);
		GolImgFile* imageFile = &g_textureBmpFile;
		if (!(textureFlags & GolTexture::c_textureFlagBmpSource)) {
			imageFile = &g_textureTgaFile;
		}

		imageFile->Open(textureName);
		texture->LoadFromImgFile(*m_renderer, imageFile);
		imageFile->Destroy();
	}
}
