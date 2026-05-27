#ifndef BRONZEDUNE0X4C_H
#define BRONZEDUNE0X4C_H

#include "compat.h"
#include "surface/bronzedunebag0xc.h"
#include "surface/golddune0x38.h"

// SIZE 0x4c
// VTABLE: GOLDP 0x10056300
class BronzeDune0x4c : public GoldDune0x38 {
public:
	// FUNCTION: GOLDP 0x1001de50
	BronzeDune0x4c() {}

	~BronzeDune0x4c() override;                                                  // vtable+0x00
	GolPaletteBase* GetPalette() override;                                       // vtable+0x1c
	void VTable0x30(GolRenderDevice& p_renderer, GolImgFile* p_source) override; // vtable+0x30
	void VTable0x34(
		GolRenderDevice& p_renderer,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) override;                 // vtable+0x34
	void VTable0x38() override; // vtable+0x38

	// SYNTHETIC: GOLDP 0x10004450
	// BronzeDune0x4c::`scalar deleting destructor'

	ColorRGBA* GetPaletteEntries() { return m_unk0x40.GetEntries(); }
	LegoU32 GetPaletteSize() { return m_unk0x40.GetPaletteSize(); }

protected:
	undefined m_unk0x38[0x40 - 0x38];
	BronzeDuneBag0xc m_unk0x40;
};

#endif // BRONZEDUNE0X4C_H
