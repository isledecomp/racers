#ifndef GOLDP_UTOPIANPAN_H
#define GOLDP_UTOPIANPAN_H

#include "decomp.h"
#include "image/whitebaffoon0x50.h"
#include "surface/bronzedune0x4c.h"
#include "types.h"

class GolD3DRenderDevice;
class DuskwindBananaRelic0x30;
class GolSurfaceFormat;
class GoldDune0x38;
class PurpleDune0x7c;
class GolRenderDevice;
struct Rect;

// SIZE 0xa4
// VTABLE: GOLDP 0x10056340
class UtopianPan0xa4 : public WhiteBaffoon0x50 {
public:
	// SIZE 0x09
	struct UtopianPanImageName {
		union {
			FourBytes m_name[2]; // 0x00
			LegoChar m_chars[9]; // 0x00
		};
	};

	UtopianPan0xa4();

	void VTable0x00() override;                                                                   // vtable+0x00
	void VTable0x04() override;                                                                   // vtable+0x04
	void VTable0x08() override;                                                                   // vtable+0x08
	void VTable0x0c(LegoU32 p_row, LegoU32 p_column, GolSurfaceFormat* p_textureFormat) override; // vtable+0x0c
	void VTable0x10() override;                                                                   // vtable+0x10
	~UtopianPan0xa4() override;                                                                   // vtable+0x14
	void Reset() override;                                                                        // vtable+0x18
	PurpleDune0x7c* VTable0x1c(LegoU32 p_row, LegoU32 p_column) override;                         // vtable+0x1c

	void FUN_100051c0();
	void FUN_10005210();
	void FUN_10005440(GolRenderDevice* p_renderer, DuskwindBananaRelic0x30* p_material, GoldDune0x38* p_texture);
	void FUN_100054d0(GolD3DRenderDevice*, undefined4, Rect*, Rect* p_clipRect);
	void FUN_10005510(GolD3DRenderDevice*, undefined4, Rect*, Rect*, Rect* p_clipRect);
	void FUN_10005b00();

	// SYNTHETIC: GOLDP 0x10005e60
	// UtopianPan0xa4::`vector deleting destructor'

protected:
	PurpleDune0x7c* m_unk0x50;          // 0x50
	DuskwindBananaRelic0x30* m_unk0x54; // 0x54
	BronzeDune0x4c m_unk0x58;           // 0x58
};

#endif // GOLDP_UTOPIANPAN_H
