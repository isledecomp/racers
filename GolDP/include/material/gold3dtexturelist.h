#ifndef GOLD3DTEXTURELIST_H
#define GOLD3DTEXTURELIST_H

#include "decomp.h"
#include "material/goltexturelist.h"

class GolD3DTexture;

// VTABLE: GOLDP 0x100567f0
// SIZE 0x24
class GolD3DTextureList : public GolTextureList {
public:
	GolD3DTextureList();
	~GolD3DTextureList() override;   // vtable+0x00
	void Clear() override;           // vtable+0x08
	void ReleaseTextures() override; // vtable+0x0c
	void RestoreTextures() override; // vtable+0x10
	void AllocateItems() override;   // vtable+0x14
	void AllocateTexture(
		LegoU32 p_index,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) override;
	GolD3DTexture* GetItem(LegoU32 p_index) override; // vtable+0x28

	// SYNTHETIC: GOLDP 0x100177c0
	// GolD3DTextureList::`vector deleting destructor'

private:
	GolD3DTexture* m_items; // 0x20
};

#endif // GOLD3DTEXTURELIST_H
