#ifndef GOLDP_UTOPIANPAN_H
#define GOLDP_UTOPIANPAN_H

#include "bronzedune0x4c.h"
#include "decomp.h"
#include "types.h"
#include "whitebaffoon0x50.h"

class BronzeFalcon0xc8770;
class DuskwindBananaRelic0x30;
class GolSurfaceFormat;
class GoldDune0x38;
class PurpleDune0x7c;
class WhiteFalcon0x140;
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
	void FUN_10005440(WhiteFalcon0x140* p_renderer, DuskwindBananaRelic0x30* p_material, GoldDune0x38* p_texture);
	void FUN_100054d0(BronzeFalcon0xc8770*, undefined4, Rect*, undefined4);
	undefined4 FUN_10005510(BronzeFalcon0xc8770*, undefined4, Rect*, Rect*, undefined4);
	void FUN_10005b00();

	// SYNTHETIC: GOLDP 0x10005e60
	// UtopianPan0xa4::`vector deleting destructor'

protected:
	PurpleDune0x7c* m_unk0x50;          // 0x50
	DuskwindBananaRelic0x30* m_unk0x54; // 0x54
	BronzeDune0x4c m_unk0x58;           // 0x58
};

#endif // GOLDP_UTOPIANPAN_H
