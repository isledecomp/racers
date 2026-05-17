#ifndef GOLFONTBASE0X40_H
#define GOLFONTBASE0X40_H

#include "color.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

class WhiteFalcon0x140;
class GolString;
class PurpleDune0x7c;
struct Rect;

// VTABLE: GOLDP 0x10056ea8
// SIZE 0x40
class GolFontBase0x40 {
public:
	GolFontBase0x40();

	virtual void VTable0x00(undefined4 p_unk0x04, undefined4 p_unk0x08);            // vtable+0x00
	virtual void VTable0x04(undefined4 p_unk0x04) = 0;                              // vtable+0x04
	virtual PurpleDune0x7c* VTable0x08(LegoU32 p_index) = 0;                        // vtable+0x08
	virtual void VTable0x0c(WhiteFalcon0x140* p_unk0x04, undefined4 p_unk0x08) = 0; // vtable+0x0c
	virtual void VTable0x10(LegoU32 p_index) = 0;                                   // vtable+0x10
	virtual void VTable0x14(Rect* p_sourceRect, Rect* p_destRect) = 0;              // vtable+0x14
	virtual void VTable0x18() = 0;                                                  // vtable+0x18
	virtual ~GolFontBase0x40();                                                     // vtable+0x1c
	virtual void Clear();                                                           // vtable+0x20

	// SYNTHETIC: GOLDP 0x1001dee0
	// GolFontBase0x40::`scalar deleting destructor'

	undefined4 FUN_1001eaa0(GolString*, WhiteFalcon0x140*, LegoS32, LegoS32, LegoFloat, LegoFloat, Rect*, undefined4);
	undefined4 FUN_1001eb70(GolString*, WhiteFalcon0x140*, LegoS32, LegoS32, LegoFloat, LegoFloat, Rect*, undefined4);
	undefined4 FUN_1001eca0(GolString*, WhiteFalcon0x140*, LegoS32, LegoS32, LegoFloat, LegoFloat, Rect*, undefined4);
	undefined4 FUN_00408be0(GolString* p_string, LegoS32* p_width, LegoS32* p_height);
	undefined4 FUN_00408d50(
		GolString* p_string,
		LegoS32 p_wrapWidth,
		LegoS32 p_unk0x10,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY,
		LegoS32* p_width,
		LegoS32* p_height
	);
	undefined2 FUN_00408fe0(
		GolString* p_string,
		WhiteFalcon0x140* p_renderer,
		LegoS32 p_x,
		LegoS32 p_y,
		LegoS32 p_wrapWidth,
		LegoS32 p_unk0x18,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY,
		Rect* p_rect,
		ColorRGBA* p_color,
		LegoS32 p_unk0x2c
	);
	LegoU32 FUN_004092b0(LegoU16 p_char);

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

	void SetColor(LegoU32 p_color) { m_colorPacked = p_color; }

protected:
	// SIZE 0x0c
	struct Glyph0x0c {
		LegoU16 m_char;       // 0x00
		undefined2 m_unk0x02; // 0x02
		undefined2 m_unk0x04; // 0x04
		undefined2 m_unk0x06; // 0x06
		undefined2 m_unk0x08; // 0x08
		LegoU16 m_width;      // 0x0a
	};

	undefined4 m_unk0x04;             // 0x04
	undefined4 m_unk0x08;             // 0x08
	undefined4 m_unk0x0c;             // 0x0c
	undefined4 m_unk0x10;             // 0x10
	undefined4 m_unk0x14;             // 0x14
	LegoS32 m_unk0x18;                // 0x18
	LegoS32 m_unk0x1c;                // 0x1c
	LegoS32 m_unk0x20;                // 0x20
	LegoS32 m_unk0x24;                // 0x24
	Glyph0x0c* m_unk0x28;             // 0x28
	undefined4 m_unk0x2c;             // 0x2c
	undefined m_unk0x30;              // 0x30
	undefined m_unk0x31[0x34 - 0x31]; // 0x31
	undefined4 m_unk0x34;             // 0x34
	undefined4 m_unk0x38;             // 0x38
	union {
		ColorRGBA m_color;     // 0x3c
		LegoU32 m_colorPacked; // 0x3c
	};
};

#endif // GOLFONTBASE0X40_H
