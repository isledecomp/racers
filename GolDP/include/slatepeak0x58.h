#ifndef GOLDP_SLATEPEAK0X58_H
#define GOLDP_SLATEPEAK0X58_H

#include "azureridge0x38.h"
#include "compat.h"
#include "depthbuffer0x38.h"
#include "pearldew0x0c.h"

class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x1005627c
// SIZE 0x58
class SlatePeak0x58 : public AzureRidge0x38 {
public:
	SlatePeak0x58();
	~SlatePeak0x58() override;                                                         // vtable+0x00
	void LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags) override;    // vtable+0x04
	void UnlockPixels() override;                                                      // vtable+0x08
	void LockAuxPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags) override; // vtable+0x0c
	void UnlockAuxPixels() override;                                                   // vtable+0x10
	void VTable0x14(undefined4*) override;                                             // vtable+0x14
	void VTable0x18() override;                                                        // vtable+0x18
	IPalette0x4* GetPalette() override;                                                // vtable+0x1c
	void Fill(LegoU32 p_color) override;                                               // vtable+0x20
	void VTable0x28(undefined4, undefined4, undefined4*) override;                     // vtable+0x28
	void VTable0x2c() override;                                                        // vtable+0x2c
	void VTable0x30(
		GolDrawState* p_drawState,
		undefined4 p_width,
		undefined4 p_height,
		undefined4 p_bpp
	) override;                 // vtable+0x30
	void VTable0x34() override; // vtable+0x34

	// SYNTHETIC: GOLDP 0x10003170
	// SlatePeak0x58::`scalar deleting destructor'

protected:
	friend class DepthBuffer0x38;
	friend class BronzeFalcon0xc8770;

	LegoS32 AttachDepthBuffer(DepthBuffer0x38* p_depthBuffer);
	void DetachDepthBuffer(DepthBuffer0x38* p_depthBuffer);
	void SetDisplayPalette(BronzeFalcon0xc8770* p_renderer);

	PearlDew0x0c m_palette;                // 0x38
	GolDrawState* m_drawState;             // 0x44
	LPDIRECTDRAWSURFACE4 m_displaySurface; // 0x48
	LPDIRECTDRAWSURFACE4 m_renderSurface;  // 0x4c
	LPDIRECTDRAWCLIPPER m_clipper;         // 0x50
	DepthBuffer0x38* m_depthBuffer;        // 0x54
};

#endif // GOLDP_SLATEPEAK0X58_H
