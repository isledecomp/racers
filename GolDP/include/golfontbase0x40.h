#ifndef GOLFONTBASE0X40_H
#define GOLFONTBASE0X40_H

#include "color.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

class WhiteFalcon0x140;

// VTABLE: GOLDP 0x10056ea8
// SIZE 0x40
class GolFontBase0x40 {
public:
	GolFontBase0x40();

	virtual void VTable0x00(undefined4 p_unk0x04, undefined4 p_unk0x08);            // vtable+0x00
	virtual void VTable0x04(undefined4 p_unk0x04) = 0;                              // vtable+0x04
	virtual undefined4* VTable0x08(LegoU32 p_index) = 0;                            // vtable+0x08
	virtual void VTable0x0c(WhiteFalcon0x140* p_unk0x04, undefined4 p_unk0x08) = 0; // vtable+0x0c
	virtual void VTable0x10(LegoU32 p_index) = 0;                                   // vtable+0x10
	virtual void VTable0x14(undefined4 p_unk0x04, undefined4 p_unk0x08) = 0;        // vtable+0x14
	virtual void VTable0x18() = 0;                                                  // vtable+0x18
	virtual ~GolFontBase0x40();                                                     // vtable+0x1c
	virtual void Clear();                                                           // vtable+0x20

	// SYNTHETIC: GOLDP 0x1001dee0
	// GolFontBase0x40::`scalar deleting destructor'

	LegoBool32 HasLoadedData() const { return m_unk0x28 != NULL; }
	void SetColor(LegoU8 p_red, LegoU8 p_green, LegoU8 p_blue, LegoU8 p_alpha)
	{
		ColorRGBA color;

		color.m_red = p_red;
		color.m_grn = p_green;
		color.m_blu = p_blue;
		color.m_alp = p_alpha;
		m_color = color;
	}

protected:
	undefined4 m_unk0x04;             // 0x04
	undefined4 m_unk0x08;             // 0x08
	undefined4 m_unk0x0c;             // 0x0c
	undefined4 m_unk0x10;             // 0x10
	undefined4 m_unk0x14;             // 0x14
	undefined4 m_unk0x18;             // 0x18
	undefined4 m_unk0x1c;             // 0x1c
	undefined4 m_unk0x20;             // 0x20
	undefined4 m_unk0x24;             // 0x24
	undefined* m_unk0x28;             // 0x28
	undefined4 m_unk0x2c;             // 0x2c
	undefined m_unk0x30;              // 0x30
	undefined m_unk0x31[0x34 - 0x31]; // 0x31
	undefined4 m_unk0x34;             // 0x34
	undefined4 m_unk0x38;             // 0x38
	ColorRGBA m_color;                // 0x3c
};

#endif // GOLFONTBASE0X40_H
