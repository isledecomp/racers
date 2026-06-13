#ifndef GOLFONTBASE_H
#define GOLFONTBASE_H

#include "compat.h"
#include "decomp.h"
#include "golname.h"
#include "image/whitebaffoon0x50.h"
#include "surface/color.h"
#include "types.h"

class GolD3DRenderDevice;
class GolRenderDevice;
class GolString;
class PurpleDune0x7c;
struct Rect;

// VTABLE: GOLDP 0x10056ea8
// SIZE 0x40
class GolFontBase {
public:
	enum Flags {
		c_flagBit2 = 0x0004,
		c_flagBit3 = 0x0008,
		c_flagBit4 = 0x0010,
		c_flagBit5 = 0x0020,
		c_flagBit11 = 0x0800,
		c_allFlags = 0xffff,
		c_flagsWithoutBit3 = c_allFlags & ~c_flagBit3,
		c_flagsWithoutBit4 = c_allFlags & ~c_flagBit4
	};

	GolFontBase();

	virtual void Load(const LegoChar* p_name, GolD3DRenderDevice* p_renderer);                      // vtable+0x00
	virtual void VTable0x04(GolD3DRenderDevice* p_renderer, GolSurfaceFormat* p_textureFormat) = 0; // vtable+0x04
	virtual PurpleDune0x7c* GetTexture(LegoU32 p_index) = 0;                                        // vtable+0x08
	virtual void VTable0x0c(GolRenderDevice* p_unk0x04, LegoU32 p_count) = 0;                       // vtable+0x0c
	virtual void SelectSurface(LegoU32 p_index) = 0;                                                // vtable+0x10
	virtual void VTable0x14(Rect* p_sourceRect, Rect* p_destRect) = 0;                              // vtable+0x14
	virtual void VTable0x18() = 0;                                                                  // vtable+0x18
	virtual ~GolFontBase();                                                                         // vtable+0x1c
	virtual void Clear();                                                                           // vtable+0x20

	// SYNTHETIC: GOLDP 0x1001dee0
	// GolFontBase::`scalar deleting destructor'

	void DrawString(const LegoChar*, GolRenderDevice*, LegoS32, LegoS32, LegoFloat, LegoFloat, Rect*, undefined4);
	void CreateGlyphs(GolD3DRenderDevice* p_renderer, GolString* p_string, LegoU32 p_count);
	void ScanGlyphs(const LegoChar* p_name);
	void ReadSeparatorSignature(LegoU32* p_rowSignature, LegoU8* p_pixels, LegoU32 p_pitch);
	LegoBool32 IsSeparatorColumn(LegoU32* p_rowSignature, LegoU8* p_pixels, LegoU32 p_pitch, LegoBool32 p_highNibble);
	LegoU32 PackGlyphTextures(GolD3DRenderDevice* p_renderer, GolSurfaceFormat* p_textureFormat);
	LegoS32 DrawString(GolString*, GolRenderDevice*, LegoS32, LegoS32, LegoFloat, LegoFloat, Rect*, undefined4);
	LegoS32 DrawStringFitted(GolString*, GolRenderDevice*, LegoS32, LegoS32, LegoFloat, LegoFloat, Rect*, undefined4);
	LegoS32 DrawGlyphRun(LegoU32, GolRenderDevice*, LegoS32, LegoS32, LegoFloat, LegoFloat, Rect*, undefined4);
	LegoBool32 ComputeClipRect(GolRenderDevice*, Rect*, Rect*);
	void ClipRects(Rect*, Rect*, Rect*, LegoFloat, LegoFloat);
	static LegoS32 __cdecl CompareGlyphChars(const void* p_left, const void* p_right);
	void MeasureString(GolString* p_string, LegoS32* p_width, LegoS32* p_height);
	void MeasureString(const LegoChar* p_string, LegoS32* p_width, LegoS32* p_height);
	void FUN_00408d50(
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
		GolRenderDevice* p_renderer,
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
	LegoU32 FindGlyphIndex(LegoU16 p_char);

	LegoBool32 HasLoadedData() const { return m_glyphs != NULL; }
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
	void SetColor(const ColorRGBA& p_color) { m_color = p_color; }

protected:
	friend class GolFontLibrary;

	// SIZE 0x0c
	struct Glyph {
		LegoU16 m_char;            // 0x00
		undefined2 m_sourceX;      // 0x02
		undefined2 m_surfaceIndex; // 0x04
		undefined2 m_textureX;     // 0x06
		undefined2 m_textureY;     // 0x08
		LegoU16 m_width;           // 0x0a
	};

	LegoU32 m_surfaceCount;     // 0x04
	LegoU32 m_maxTextureWidth;  // 0x08
	LegoU32 m_maxTextureHeight; // 0x0c
	LegoU32 m_textureWidth;     // 0x10
	LegoU32 m_textureHeight;    // 0x14
	LegoS32 m_spaceWidth;       // 0x18
	LegoS32 m_fontHeight;       // 0x1c
	LegoS32 m_charSpacing;      // 0x20
	LegoS32 m_glyphCount;       // 0x24
	Glyph* m_glyphs;            // 0x28
	LegoU32 m_flags;            // 0x2c
	union {
		GolName m_name;           // 0x30
		FourBytes m_nameParts[2]; // 0x30
	};
	union {
		ColorRGBA m_colorKey;     // 0x38
		LegoU32 m_colorKeyPacked; // 0x38
	};
	union {
		ColorRGBA m_color;     // 0x3c
		LegoU32 m_colorPacked; // 0x3c
	};
};

#endif // GOLFONTBASE_H
