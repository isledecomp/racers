#ifndef GOLFONT0XA0_H
#define GOLFONT0XA0_H

#include "bronzedune0x4c.h"
#include "golfontbase0x40.h"

class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x100562dc
// SIZE 0xa0
class GolFont0xa0 : public GolFontBase0x40 {
public:
	GolFont0xa0();

	void VTable0x00(undefined4 p_unk0x04, undefined4 p_unk0x08) override; // vtable+0x00
	void VTable0x04(undefined4 p_unk0x04) override;                       // vtable+0x04
	undefined4* VTable0x08(LegoU32 p_index) override;                     // vtable+0x08
	void VTable0x0c(undefined4 p_unk0x04, undefined4 p_unk0x08) override; // vtable+0x0c
	void VTable0x10(LegoU32 p_index) override;                            // vtable+0x10
	void VTable0x14(undefined4 p_unk0x04, undefined4 p_unk0x08) override; // vtable+0x14
	void VTable0x18() override;                                           // vtable+0x18
	~GolFont0xa0() override;                                              // vtable+0x1c
	void Clear() override;                                                // vtable+0x20

	// SYNTHETIC: GOLDP 0x10004190
	// GolFont0xa0::`vector deleting destructor'

	void ReleaseSurfaces();
	void RefreshSurfaces(BronzeFalcon0xc8770* p_renderer);

private:
	BronzeDune0x4c m_unk0x40; // 0x40
	undefined4 m_unk0x8c;     // 0x8c
	undefined4* m_unk0x90;    // 0x90
	LegoFloat m_unk0x94;      // 0x94
	LegoFloat m_unk0x98;      // 0x98
	undefined4* m_unk0x9c;    // 0x9c
};

#endif // GOLFONT0XA0_H
