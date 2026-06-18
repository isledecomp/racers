#ifndef GOLRENDERDEVICE_H
#define GOLRENDERDEVICE_H

#include "decomp.h"
#include "golmath.h"
#include "golsurfaceformat.h"
#include "golviewfrustum.h"
#include "render/gold3drenderstate.h"
#include "surface/color.h"
#include "surface/silverdune0x30.h"
#include "types.h"

class GolMaterialLibrary;
class GolCamera;
class GolD3DRenderDevice;
class GolFontLibrary;
class DuskwindBananaRelic0x24;
class GolModelEntity;
class GolWorldEntity;
class GolSurfaceFormat;
class GolFont;
class GolFontBase;
class GolString;
class GolCommonDrawState;
class GolNameTable;
class GolImageList;
class GolBillboard;
struct Rect;
class GolTextureList;
class SlatePeak0x58;
class UtopianPan0xa4;
class GoldDune0x38;

// VTABLE: GOLDP 0x10057338
// SIZE 0x140
class GolRenderDevice {
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

	// SIZE 0x04
	class MaterialColor {
	public:
		MaterialColor();
		void SetColor(ColorRGBA p_color);
		const ColorRGBA& GetColor() const { return m_color; }

		ColorRGBA m_color; // 0x00
	};

	// SIZE 0x10
	class Light : public MaterialColor {
	public:
		Light();
		void SetDirection(const GolVec3& p_direction);

		GolVec3 m_direction; // 0x04
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

	GolRenderDevice();

	virtual LegoS32 RestoreResources(); // vtable+0x00
	virtual void ReleaseResources();    // vtable+0x04
	virtual ~GolRenderDevice();         // vtable+0x08
	virtual void SelectTextureFormat(
		const GolSurfaceFormat& p_requestedTextureFormat,
		GolSurfaceFormat* p_actualTextureFormat,
		LegoBool32
	);                                                                      // vtable+0x0c
	virtual GolCommonDrawState* GetDrawState() = 0;                         // vtable+0x10
	virtual const SlatePeak0x58* GetRenderTargetInfo() = 0;                 // vtable+0x14
	virtual void VTable0x18() = 0;                                          // vtable+0x18
	virtual void VTable0x1c(const ColorRGBA&) = 0;                          // vtable+0x1c
	virtual void VTable0x20(GolCamera*) = 0;                                // vtable+0x20
	virtual void VTable0x24();                                              // vtable+0x24
	virtual void VTable0x28();                                              // vtable+0x28
	virtual void VTable0x2c(const MaterialColor* p_param);                  // vtable+0x2c
	virtual void VTable0x30(const Light* p_param);                          // vtable+0x30
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
	virtual LegoS32 VTable0x64(
		GolString*,
		GolFontBase*,
		LegoS32,
		LegoS32,
		LegoFloat,
		LegoFloat,
		Rect*,
		undefined4
	) = 0; // vtable+0x64
	virtual void VTable0x68(
		const LegoChar*,
		GolFontBase*,
		LegoS32,
		LegoS32,
		LegoFloat,
		LegoFloat,
		Rect*,
		undefined4
	) = 0; // vtable+0x68
	virtual LegoS32 VTable0x6c(
		GolString*,
		GolFontBase*,
		LegoS32,
		LegoS32,
		LegoFloat,
		LegoFloat,
		Rect*,
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
	) = 0;                                                                  // vtable+0x74
	virtual void VTable0x78(UtopianPan0xa4*, undefined4, Rect*, Rect*) = 0; // vtable+0x78
	virtual void VTable0x7c(
		UtopianPan0xa4* p_image,
		undefined4 p_unk0x08,
		Rect* p_destRect,
		Rect* p_sourceRect,
		Rect* p_clipRect
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
	) = 0;                                                                                    // vtable+0x84
	virtual void VTable0x88(GolModelEntity*, GolD3DRenderState*, undefined4);                 // vtable+0x88
	virtual void VTable0x8c(GolModelEntity*, GolD3DRenderState*, undefined4);                 // vtable+0x8c
	virtual void VTable0x90(GolWorldEntity*) = 0;                                             // vtable+0x90
	virtual void VTable0x94(GolWorldEntity*) = 0;                                             // vtable+0x94
	virtual void VTable0x98(GolModelEntity*, GolD3DRenderState*, undefined4);                 // vtable+0x98
	virtual void VTable0x9c(GolModelEntity*, GolD3DRenderState*, undefined4);                 // vtable+0x9c
	virtual void VTable0xa0(GolWorldEntity*, const GolVec3*, const GolVec3*, const GolVec3*); // vtable+0xa0
	virtual void VTable0xa4(GolWorldEntity*);                                                 // vtable+0xa4
	virtual void VTable0xa8(GolWorldEntity* p_param1, LegoFloat p_param2,
							LegoFloat p_param3);                           // vtable+0xa8
	virtual void VTable0xac(GolModelEntity*, undefined4);                  // vtable+0xac
	virtual void VTable0xb0(GolModelEntity*, undefined4);                  // vtable+0xb0
	virtual void VTable0xb4(GolBillboard&) = 0;                            // vtable+0xb4
	virtual void SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags); // vtable+0xb8
	virtual void ClearAlphaOverride();                                     // vtable+0xbc
	virtual void VTable0xc0(const ColorRGBA& p_param);                     // vtable+0xc0
	virtual void VTable0xc4();                                             // vtable+0xc4
	virtual void VTable0xc8();                                             // vtable+0xc8
	virtual void VTable0xcc();                                             // vtable+0xcc
	virtual void VTable0xd0() = 0;                                         // vtable+0xd0
	virtual void VTable0xd4() = 0;                                         // vtable+0xd4
	virtual void VTable0xd8() = 0;                                         // vtable+0xd8
	virtual void VTable0xdc() = 0;                                         // vtable+0xdc
	virtual void VTable0xe0() = 0;                                         // vtable+0xe0
	virtual void VTable0xe4() = 0;                                         // vtable+0xe4
	virtual void VTable0xe8(LegoBool32 p_arg) = 0;                         // vtable+0xe8
	virtual void VTable0xec(undefined4);                                   // vtable+0xec
	virtual void VTable0xf0() = 0;                                         // vtable+0xf0
	virtual void VTable0xf4();                                             // vtable+0xf4
	virtual LegoU32 GetMinimumTextureWidth(undefined4) const = 0;          // vtable+0xf8
	virtual LegoU32 GetMaximumTextureWidth(undefined4) const = 0;          // vtable+0xfc
	virtual LegoU32 GetMinimumTextureHeight(undefined4) const = 0;         // vtable+0x100
	virtual LegoU32 GetMaximumTextureHeight(undefined4) const = 0;         // vtable+0x104
	virtual LegoBool32 TexturesMustBeSquare() const = 0;                   // vtable+0x108
	virtual LegoBool32 TextureSizesMustBePowersOfTwo() const = 0;          // vtable+0x10c
	virtual LegoBool32 VTable0x110() const;

	void Destroy();
	void AddFontList(GolFontLibrary* p_param);
	void RemoveFontList(GolFontLibrary* p_param);
	void AddImageList(GolImageList* p_param);
	void RemoveImageList(GolImageList* p_param);
	void AddTextureList(GolTextureList* p_param);
	void RemoveTextureList(GolTextureList* p_param);
	GoldDune0x38* FindTextureByName(const LegoChar* p_name);
	void AddMaterialList(GolMaterialLibrary* p_param);
	void RemoveMaterialList(GolMaterialLibrary* p_param);
	DuskwindBananaRelic0x24* FindMaterialByName(const LegoChar* p_name);

#ifdef BUILDING_LEGORACERS
	GolFont* FindFontByName(const LegoChar* p_name);
	UtopianPan0xa4* FindImageByName(const LegoChar* p_name);
#endif

	// SYNTHETIC: GOLDP 0x100288b0
	// GolRenderDevice::`scalar deleting destructor'

	undefined4 GetFlags() { return m_flags; }
	GolCamera* GetUnk0x0c() { return m_unk0x0c; }
	MaterialColor* GetCurrentMaterialColor() { return const_cast<MaterialColor*>(m_unk0x120); }
	Light* GetCurrentLight(LegoU32 p_index) { return const_cast<Light*>(m_unk0x124[p_index]); }

protected:
	friend class GolCommonDrawState;

	undefined4 m_flags;                          // 0x04
	undefined2 m_unk0x08;                        // 0x08
	undefined2 m_unk0x0a;                        // 0x0a
	GolCamera* m_unk0x0c;                        // 0x0c
	LegoU32 m_textureFormatIndex;                // 0x10
	undefined4 m_requestedRedBitCount;           // 0x14
	undefined4 m_requestedGrnBitCount;           // 0x18
	undefined4 m_requestedBluBitCount;           // 0x1c
	undefined4 m_requestedAlpBitCount;           // 0x20
	undefined4 m_requestedUnk0x10BitCount;       // 0x24
	undefined4 m_requestedPaletteBitCount;       // 0x28
	undefined4 m_unk0x2c;                        // 0x2c
	LegoU32 m_countTextureFormats;               // 0x30
	GolSurfaceFormat* m_textureFormats;          // 0x34
	GolTextureList* m_textureLists;              // 0x38
	GolMaterialLibrary* m_materialLists;         // 0x3c
	GolImageList* m_imageLists;                  // 0x40
	GolFontLibrary* m_fontLists;                 // 0x44
	GolD3DRenderDevice* m_nextDrawStateRenderer; // 0x48
	GolViewFrustum m_unk0x4c;                    // 0x4c
	ColorRGBA m_unk0x118;                        // 0x118
	undefined4 m_unk0x11c;                       // 0x11c
	const MaterialColor* m_unk0x120;             // 0x120
	const Light* m_unk0x124[7];                  // 0x124
};

#endif // GOLRENDERDEVICE_H
