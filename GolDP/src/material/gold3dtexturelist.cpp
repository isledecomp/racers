#include "material/gold3dtexturelist.h"

#include "golerror.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexture.h"

DECOMP_SIZE_ASSERT(GolD3DTextureList, 0x24)

// FUNCTION: GOLDP 0x10015920
GolD3DTextureList::GolD3DTextureList()
{
	m_items = NULL;
}

// FUNCTION: GOLDP 0x10015940
GolD3DTextureList::~GolD3DTextureList()
{
	Clear();
}

// FUNCTION: GOLDP 0x100159b0
void GolD3DTextureList::AllocateItems()
{
	if (GetItemCount() >= 1) {
		m_items = new GolD3DTexture[GetItemCount()];
		if (m_items == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// FUNCTION: GOLDP 0x10015a50
void GolD3DTextureList::ReleaseTextures()
{
	LegoU32 i;
	if (m_renderer != NULL) {
		for (i = 0; i < GetItemCount(); i++) {
			if (m_items[i].GetPixelFlags() & GolSurface::c_lockRequestRead) {
				m_items[i].ReleaseDeviceObjects();
			}
		}
	}
}

// FUNCTION: GOLDP 0x10015a90
void GolD3DTextureList::RestoreTextures()
{
	LegoU32 i;
	if (m_renderer != NULL) {
		for (i = 0; i < GetItemCount(); i++) {
			if (m_items[i].GetPixelFlags() & GolSurface::c_lockRequestRead) {
				m_items[i].RestoreDeviceObjects(*m_renderer);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10015ad0
void GolD3DTextureList::Clear()
{
	if (m_items != NULL) {
		delete[] m_items;
		m_items = NULL;
	}
	GolTextureList::Clear();
}

// FUNCTION: GOLDP 0x10015af0
GolD3DTexture* GolD3DTextureList::GetItem(LegoU32 p_index)
{
	return &m_items[p_index];
}

// FUNCTION: GOLDP 0x10015b10
void GolD3DTextureList::AllocateTexture(
	LegoU32 p_index,
	const GolSurfaceFormat& p_textureFormat,
	LegoU32 p_width,
	LegoU32 p_height
)
{
	m_items[p_index].Allocate(*m_renderer, p_textureFormat, p_width, p_height);
}
