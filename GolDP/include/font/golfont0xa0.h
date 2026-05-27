#ifndef GOLFONT0XA0_H
#define GOLFONT0XA0_H

#include "font/golfontbase0x40.h"
#include "surface/bronzedune0x4c.h"

class GolD3DRenderDevice;
class DuskwindBananaRelic0x30;
class PurpleDune0x7c;

// VTABLE: GOLDP 0x100562dc
// SIZE 0xa0
class GolFont0xa0 : public GolFontBase0x40 {
public:
	GolFont0xa0();

	void VTable0x00(const LegoChar* p_name, GolD3DRenderDevice* p_renderer) override;            // vtable+0x00
	void VTable0x04(GolD3DRenderDevice* p_renderer, GolSurfaceFormat* p_textureFormat) override; // vtable+0x04
	PurpleDune0x7c* VTable0x08(LegoU32 p_index) override;                                        // vtable+0x08
	void VTable0x0c(GolRenderDevice* p_unk0x04, LegoU32 p_count) override;                       // vtable+0x0c
	void VTable0x10(LegoU32 p_index) override;                                                   // vtable+0x10
	void VTable0x14(Rect* p_sourceRect, Rect* p_destRect) override;                              // vtable+0x14
	void VTable0x18() override;                                                                  // vtable+0x18
	~GolFont0xa0() override;                                                                     // vtable+0x1c
	void Clear() override;                                                                       // vtable+0x20

	// SYNTHETIC: GOLDP 0x10004190
	// GolFont0xa0::`vector deleting destructor'

	void ReleaseSurfaces();
	void RefreshSurfaces(GolD3DRenderDevice* p_renderer);

private:
	enum {
		c_fontMaterialFlags = 0x92aaa
	};

	void FUN_10004d70(
		GolD3DRenderDevice* p_renderer,
		const GolSurfaceFormat* p_sourceFormat,
		GolSurfaceFormat* p_textureFormat
	);

	BronzeDune0x4c m_unk0x40;           // 0x40
	GolD3DRenderDevice* m_renderer;     // 0x8c
	PurpleDune0x7c* m_unk0x90;          // 0x90
	LegoFloat m_unk0x94;                // 0x94
	LegoFloat m_unk0x98;                // 0x98
	DuskwindBananaRelic0x30* m_unk0x9c; // 0x9c
};

#endif // GOLFONT0XA0_H
