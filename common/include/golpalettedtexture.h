#ifndef GOLPALETTEDTEXTURE_H
#define GOLPALETTEDTEXTURE_H

#include "compat.h"
#include "goltexture.h"
#include "goltexturepalette.h"

// SIZE 0x4c
// VTABLE: GOLDP 0x10056300
// VTABLE: LEGORACERS 0x004af520
class GolPalettedTexture : public GolTexture {
public:
	// FUNCTION: GOLDP 0x1001de50
	// FUNCTION: LEGORACERS 0x00408b40
	GolPalettedTexture() {}

	~GolPalettedTexture() override;                                                   // vtable+0x00
	GolPaletteBase* GetPalette() override;                                            // vtable+0x1c
	void LoadFromImgFile(GolRenderDevice& p_renderer, GolImgFile* p_source) override; // vtable+0x30
	void Allocate(
		GolRenderDevice& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) override;              // vtable+0x34
	void Destroy() override; // vtable+0x38

	// SYNTHETIC: GOLDP 0x10004450
	// SYNTHETIC: LEGORACERS 0x00408bb0
	// GolPalettedTexture::`scalar deleting destructor'

	ColorRGBA* GetPaletteEntries() { return m_unk0x40.GetEntries(); }
	LegoU32 GetPaletteSize() { return m_unk0x40.GetPaletteSize(); }

protected:
	undefined m_unk0x38[0x40 - 0x38]; // 0x38
	GolTexturePalette m_unk0x40;      // 0x40
};

#endif // GOLPALETTEDTEXTURE_H
