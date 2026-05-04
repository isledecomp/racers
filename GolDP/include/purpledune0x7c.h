#ifndef PURPLEDUNE0x7C_H
#define PURPLEDUNE0x7C_H

#include "bronzedunebag0xc.h"
#include "falcontextureformat.h"
#include "golddune0x38.h"

#include <ddraw.h>

class IPalette0x4;

// VTABLE: GOLDP 0x1005681c
// SIZE 0x7c
class PurpleDune0x7c : public GoldDune0x38 {
public:
	PurpleDune0x7c();
	~PurpleDune0x7c() override; // vtable+0x00

	void LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags) override; // vtable+0x04
	void UnlockPixels() override;                                                   // vtable+0x08
	IPalette0x4* GetPalette() override;                                             // vtable+0x1c
	void VTable0x30(WhiteFalcon0x140& p_renderer, undefined4*) override;            // vtable+0x30
	void VTable0x34(
		WhiteFalcon0x140& p_renderer,
		const FalconTextureFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) override;                 // vtable+0x34
	void VTable0x38() override; // vtable+0x38

	void FUN_10015fb0();
	void FUN_10016100();
	void FUN_10016380();
	void FUN_10016440(BronzeFalcon0xc8770& p_renderer);
	void FUN_10016460(BronzeFalcon0xc8770& p_renderer);

	// SYNTHETIC: GOLDP 0x10004aa0
	// PurpleDune0x7c::`vector deleting destructor'

private:
	// SIZE 0x18
	struct UnkField0x44 {
		// Unsure about size, might be a union
		LegoU8* m_pixels;                 // 0x00
		LegoU32 m_pitch;                  // 0x04
		undefined m_unk0x08[0x18 - 0x08]; // 0x08
	};

	undefined4 m_unk0x38;                 // 0x38
	undefined4 m_unk0x3c;                 // 0x3c
	IPalette0x4* m_unk0x40;               // 0x40
	UnkField0x44* m_unk0x44;              // 0x44
	LPDIRECTDRAWSURFACE4 m_surface;       // 0x48
	undefined4* m_unk0x4c;                // 0x4c
	BronzeDuneBag0xc m_unk0x50;           // 0x50
	FalconTextureFormat m_textureFormat2; // 0x5c
	undefined4 m_unk0x74;                 // 0x74
	undefined4 m_unk0x78;                 // 0x78
};

#endif // PURPLEDUNE0x7C_H
