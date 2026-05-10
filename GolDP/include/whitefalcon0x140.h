#ifndef WHITEFALCON0x140_H
#define WHITEFALCON0x140_H

#include "color.h"
#include "decomp.h"
#include "golmath.h"
#include "golsurfaceformat.h"
#include "silverdune0x30.h"
#include "types.h"

class AmberHaze0x1c;
class AmberLens0x344;
class BronzeFalcon0xc8770;
class CinderBasin0x28;
class DuskwindBananaRelic0x24;
class GolSurfaceFormat;
class GolFont0xa0;
class GolFontBase0x40;
class GolCommonDrawState;
class GolNameTable;
class HypnoticNoise0x1c;
class FloatyPontoon0x4c;
struct Rect;
class MagentaRibbon0x20;
class SlatePeak0x58;
class UtopianPan0xa4;
class GoldDune0x38;

// VTABLE: GOLDP 0x10057338
// SIZE 0x140
class WhiteFalcon0x140 {
public:
	// SIZE 0x18
	struct TexturedVertex {
		LegoFloat m_x;     // 0x00
		LegoFloat m_y;     // 0x04
		LegoFloat m_z;     // 0x08
		LegoFloat m_u;     // 0x0c
		LegoFloat m_v;     // 0x10
		ColorRGBA m_color; // 0x14
	};

	// SIZE 0x10
	struct Field0x124 {
		ColorRGBA m_unk0x00; // 0x00
		FColorRGB m_unk0x04; // 0x04
	};

	// SIZE 0xcc
	struct Field0x4c {
		GolVec3 m_position;               // 0x00
		undefined m_unk0x0c[0xcc - 0x0c]; // 0x0c
	};

	enum Flags {
		c_flagBit0 = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagBit5 = 1 << 5,
		c_flagBit7 = 1 << 7,
		c_flagBit8 = 1 << 8,
		c_flagBit9 = 1 << 9,
		c_flagBit11 = 1 << 11,
		c_flagBit12 = 1 << 12,
		c_flagBit13 = 1 << 13,
		c_flagBit14 = 1 << 14,
		c_flagBit15 = 1 << 15,
		c_flagBit16 = 1 << 16,
		c_flagBit17 = 1 << 17,
		c_flagBit18 = 1 << 18,
		c_flagBit19 = 1 << 19,
		c_flagBit20 = 1 << 20,
		c_flagBit24 = 1 << 24,
	};

	WhiteFalcon0x140();

	virtual LegoS32 RestoreResources(); // vtable+0x00
	virtual void ReleaseResources();    // vtable+0x04
	virtual ~WhiteFalcon0x140();        // vtable+0x08
	virtual void SelectTextureFormat(
		const GolSurfaceFormat& p_requestedTextureFormat,
		GolSurfaceFormat* p_actualTextureFormat,
		LegoBool32
	);                                                                      // vtable+0x0c
	virtual GolCommonDrawState* GetDrawState() = 0;                         // vtable+0x10
	virtual const SlatePeak0x58* GetRenderTargetInfo() = 0;                 // vtable+0x14
	virtual void VTable0x18() = 0;                                          // vtable+0x18
	virtual void VTable0x1c(const ColorRGBA&) = 0;                          // vtable+0x1c
	virtual void VTable0x20(AmberLens0x344*) = 0;                           // vtable+0x20
	virtual void VTable0x24();                                              // vtable+0x24
	virtual void VTable0x28();                                              // vtable+0x28
	virtual void VTable0x2c(const Field0x124* p_param);                     // vtable+0x2c
	virtual void VTable0x30(const Field0x124* p_param);                     // vtable+0x30
	virtual void VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08); // vtable+0x34
	virtual void VTable0x38();                                              // vtable+0x38
	virtual void VTable0x3c(LegoU32);                                       // vtable+0x3c
	virtual void VTable0x40();                                              // vtable+0x40
	virtual void VTable0x44();                                              // vtable+0x44
	virtual void VTable0x48();                                              // vtable+0x48
	virtual SlatePeak0x58* VTable0x4c(undefined2, undefined2);              // vtable+0x4c
	virtual void VTable0x50(SlatePeak0x58*);                                // vtable+0x50
	virtual void VTable0x54(undefined4) = 0;                                // vtable+0x54
	virtual void VTable0x58(SlatePeak0x58* p_param1, undefined4 p_param2);  // vtable+0x58
	virtual void VTable0x5c() = 0;                                          // vtable+0x5c
	virtual void VTable0x60();                                              // vtable+0x60
	virtual undefined4 VTable0x64(
		undefined4,
		GolFontBase0x40*,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) = 0; // vtable+0x64
	virtual undefined4 VTable0x68(
		undefined4,
		GolFontBase0x40*,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) = 0; // vtable+0x68
	virtual undefined4 VTable0x6c(
		undefined4,
		GolFontBase0x40*,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) = 0; // vtable+0x6c
	virtual void VTable0x70(UtopianPan0xa4*, undefined4, LegoS32, LegoS32, LegoS32,
							LegoS32) = 0; // vtable+0x70
	virtual void VTable0x74(
		UtopianPan0xa4*,
		undefined4,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32,
		LegoS32
	) = 0;                                                                       // vtable+0x74
	virtual void VTable0x78(UtopianPan0xa4*, undefined4, Rect*, undefined4) = 0; // vtable+0x78
	virtual undefined4 VTable0x7c(
		UtopianPan0xa4* p_image,
		undefined4 p_unk0x08,
		Rect* p_destRect,
		Rect* p_sourceRect,
		undefined4 p_unk0x14
	) = 0; // vtable+0x7c
	virtual void DrawRectangle(
		const Rect& p_rect,
		LegoFloat p_z,
		const ColorRGBA& p_color1,
		const ColorRGBA& p_color2,
		const ColorRGBA& p_color3,
		const ColorRGBA& p_color4,
		undefined4 p_arg7
	) = 0; // vtable+0x80
	virtual void DrawTriangle(
		const TexturedVertex* p_vertex0,
		const TexturedVertex* p_vertex1,
		const TexturedVertex* p_vertex2,
		DuskwindBananaRelic0x24* p_material,
		undefined4 p_flags
	) = 0;                                                                                  // vtable+0x84
	virtual void VTable0x88(undefined4, undefined4, undefined4);                            // vtable+0x88
	virtual void VTable0x8c(undefined4, undefined4, undefined4);                            // vtable+0x8c
	virtual void VTable0x90() = 0;                                                          // vtable+0x90
	virtual void VTable0x94(undefined4) = 0;                                                // vtable+0x94
	virtual void VTable0x98(undefined4, undefined4, undefined4);                            // vtable+0x98
	virtual void VTable0x9c(undefined4, undefined4, undefined4);                            // vtable+0x9c
	virtual void VTable0xa0();                                                              // vtable+0xa0
	virtual void VTable0xa4();                                                              // vtable+0xa4
	virtual void VTable0xa8(undefined4 p_param1, undefined4 p_param2, undefined4 p_param3); // vtable+0xa8
	virtual void VTable0xac(undefined4, undefined4);                                        // vtable+0xac
	virtual void VTable0xb0(undefined4, undefined4);                                        // vtable+0xb0
	virtual void VTable0xb4(FloatyPontoon0x4c&) = 0;                                        // vtable+0xb4
	virtual void SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags);                  // vtable+0xb8
	virtual void ClearAlphaOverride();                                                      // vtable+0xbc
	virtual void VTable0xc0(const ColorRGBA& p_param);                                      // vtable+0xc0
	virtual void VTable0xc4();                                                              // vtable+0xc4
	virtual void VTable0xc8();                                                              // vtable+0xc8
	virtual void VTable0xcc();                                                              // vtable+0xcc
	virtual void VTable0xd0() = 0;                                                          // vtable+0xd0
	virtual void VTable0xd4() = 0;                                                          // vtable+0xd4
	virtual void VTable0xd8() = 0;                                                          // vtable+0xd8
	virtual void VTable0xdc() = 0;                                                          // vtable+0xdc
	virtual void VTable0xe0() = 0;                                                          // vtable+0xe0
	virtual void VTable0xe4() = 0;                                                          // vtable+0xe4
	virtual void VTable0xe8(LegoBool32 p_arg) = 0;                                          // vtable+0xe8
	virtual void VTable0xec(undefined4);                                                    // vtable+0xec
	virtual void VTable0xf0() = 0;                                                          // vtable+0xf0
	virtual void VTable0xf4();                                                              // vtable+0xf4
	virtual LegoU32 GetMinimumTextureWidth(undefined4) const = 0;                           // vtable+0xf8
	virtual LegoU32 GetMaximumTextureWidth(undefined4) const = 0;                           // vtable+0xfc
	virtual LegoU32 GetMinimumTextureHeight(undefined4) const = 0;                          // vtable+0x100
	virtual LegoU32 GetMaximumTextureHeight(undefined4) const = 0;                          // vtable+0x104
	virtual LegoBool32 TexturesMustBeSquare() const = 0;                                    // vtable+0x108
	virtual LegoBool32 TextureSizesMustBePowersOfTwo() const = 0;                           // vtable+0x10c
	virtual LegoBool32 VTable0x110() const;

	void Destroy();
	void AddFontList(CinderBasin0x28* p_param);
	void RemoveFontList(CinderBasin0x28* p_param);
	void AddImageList(HypnoticNoise0x1c* p_param);
	void RemoveImageList(HypnoticNoise0x1c* p_param);
	void AddTextureList(MagentaRibbon0x20* p_param);
	void RemoveTextureList(MagentaRibbon0x20* p_param);
	GoldDune0x38* FindTextureByName(const LegoChar* p_name);
	void AddMaterialList(AmberHaze0x1c* p_param);
	void RemoveMaterialList(AmberHaze0x1c* p_param);
	undefined4* FindMaterialByName(const LegoChar* p_name);

#ifdef BUILDING_LEGORACERS
	GolFont0xa0* FindFontByName(const LegoChar* p_name);
	UtopianPan0xa4* FindImageByName(const LegoChar* p_name);
#endif

	// SYNTHETIC: GOLDP 0x100288b0
	// WhiteFalcon0x140::`scalar deleting destructor'

	undefined4 GetFlags() { return m_flags; }
	AmberLens0x344* GetUnk0x0c() { return m_unk0x0c; }

protected:
	friend class GolCommonDrawState;

	undefined4 m_flags;                           // 0x04
	undefined2 m_unk0x08;                         // 0x08
	undefined2 m_unk0x0a;                         // 0x0a
	AmberLens0x344* m_unk0x0c;                    // 0x0c
	LegoU32 m_textureFormatIndex;                 // 0x10
	undefined4 m_requestedRedBitCount;            // 0x14
	undefined4 m_requestedGrnBitCount;            // 0x18
	undefined4 m_requestedBluBitCount;            // 0x1c
	undefined4 m_requestedAlpBitCount;            // 0x20
	undefined4 m_requestedUnk0x10BitCount;        // 0x24
	undefined4 m_requestedPaletteBitCount;        // 0x28
	undefined4 m_unk0x2c;                         // 0x2c
	LegoU32 m_countTextureFormats;                // 0x30
	GolSurfaceFormat* m_textureFormats;           // 0x34
	MagentaRibbon0x20* m_textureLists;            // 0x38
	AmberHaze0x1c* m_materialLists;               // 0x3c
	HypnoticNoise0x1c* m_imageLists;              // 0x40
	CinderBasin0x28* m_fontLists;                 // 0x44
	BronzeFalcon0xc8770* m_nextDrawStateRenderer; // 0x48
	Field0x4c m_unk0x4c;                          // 0x4c
	ColorRGBA m_unk0x118;                         // 0x118
	undefined4 m_unk0x11c;                        // 0x11c
	const Field0x124* m_unk0x120;                 // 0x120
	const Field0x124* m_unk0x124[7];              // 0x124
};

#endif // WHITEFALCON0x140_H
