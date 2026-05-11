#ifndef GOLDP_GOLCOMMONSTATE_H
#define GOLDP_GOLCOMMONSTATE_H

#include "bronzefalcon0xc8770.h"
#include "compat.h"
#include "decomp.h"
#include "goldrawstate.h"

// VTABLE: GOLDP 0x10056994
// SIZE 0x20
class GolCommonDrawState : public GolDrawState {
protected:
	GolCommonDrawState();

public:
	// SYNTHETIC: GOLDP 0x100184c0
	// GolCommonDrawState::`scalar deleting destructor'

	LegoS32 VTable0x44(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp,
					   LegoU32 p_flags) override; // vtable+0x44
	void VTable0x48() override;                   // vtable+0x48
	void VTable0x50() override;                   // vtable+0x50
	LegoS32 VTable0x54(LegoS32, LegoS32, undefined4,
					   LegoU32) override;                     // vtable+0x54
	virtual undefined4 VTable0x58() = 0;                      // vtable+0x58
	virtual LegoU32 GetZBufferBitDepth() const;               // vtable+0x5c
	virtual LegoBool32 IsHwAccelerated();                     // vtable+0x60
	virtual LegoBool32 SupportsCulling() const;               // vtable+0x64
	virtual LegoBool32 SupportsPerspectiveCorrection() const; // vtable+0x68
	virtual LegoBool32 SupportsTextureWrap() const;           // vtable+0x6c
	virtual LegoBool32 SupportsCullCW() const;                // vtable+0x70
	virtual LegoBool32 SupportsCullCCW() const;               // vtable+0x74
	virtual LegoBool32 SupportsDither() const;                // vtable+0x78
	virtual LegoBool32 SupportsSubpixel() const;              // vtable+0x7c
	virtual LegoBool32 SupportsLinearFilter() const;          // vtable+0x80
	virtual LegoBool32 SupportsMipmap() const;                // vtable+0x84
	virtual LegoBool32 SupportsFogTable() const;              // vtable+0x88
	virtual LegoBool32 SupportsTextureAlpha() const;          // vtable+0x8c
	virtual LegoBool32 SupportsAdditiveBlend() const;         // vtable+0x90
	virtual undefined4 VTable0x94();                          // vtable+0x94
	virtual LegoBool32 SupportsZBufferlessHsr() const;        // vtable+0x98
	virtual LegoBool32 SupportsPaletteAlpha() const;          // vtable+0x9c
	virtual LegoBool32 SupportsTextureSystemMemory() const;   // vtable+0xa0
	virtual LegoBool32 SupportsTextureVideoMemory() const;    // vtable+0xa4
	virtual LegoBool32 SupportsRenderingInWindow() const;     // vtable+0xa8
	virtual LPDIRECTDRAW GetDirectDraw();                     // vtable+0xac
	virtual LPDIRECTDRAWSURFACE GetDisplaySurface();          // vtable+0xb0
	virtual LPDIRECTDRAWSURFACE GetRenderSurface();           // vtable+0xb4

	BronzeFalcon0xc8770* AddRenderer(BronzeFalcon0xc8770* p_renderer);
	BronzeFalcon0xc8770* RemoveRenderer(BronzeFalcon0xc8770* p_renderer);

	BronzeFalcon0xc8770* m_rendererList;    // 0x18
	BronzeFalcon0xc8770* m_currentRenderer; // 0x1c
};

#endif // GOLDP_GOLCOMMONSTATE_H
