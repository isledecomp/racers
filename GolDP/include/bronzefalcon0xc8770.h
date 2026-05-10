#ifndef BRONZEFALCON0XC8770_H
#define BRONZEFALCON0XC8770_H

#include "compat.h"
#include "decomp.h"
#include "depthbuffer0x38.h"
#include "duskwindbananarelic0x30.h"
#include "softwarerenderer0x58.h"
#include "types.h"
#include "whitefalcon0x140.h"

#include <d3d.h>

class BronzeFalconSurface0x5c;
class AmberLens0x344;
class GoldDune0x38;
class GolDrawDPState;
class BronzeFalcon0xc8770;

typedef void (BronzeFalcon0xc8770::*BronzeFalconDrawFunction)(undefined4, undefined4, undefined4);

// VTABLE: GOLDP 0x100565b8
// SIZE 0xc8770
class BronzeFalcon0xc8770 : public WhiteFalcon0x140 {
public:
	// SIZE 0x18
	struct TextureFormat : public GolSurfaceFormat {
		TextureFormat();
	};

	// SIZE 0x10
	struct Field0xc83b4 {
		LegoU8* m_unk0x00[4]; // 0x00
	};

	BronzeFalcon0xc8770();

	void ReleaseResources() override; // vtable+0x04
	~BronzeFalcon0xc8770() override;  // vtable+0x08
	void SelectTextureFormat(
		const GolSurfaceFormat& p_requestedTextureFormat,
		GolSurfaceFormat* p_actualTextureFormat,
		LegoBool32
	) override;                                                              // vtable+0x0c
	GolCommonDrawState* GetDrawState() override;                             // vtable+0x10
	const SlatePeak0x58* GetRenderTargetInfo() override;                     // vtable+0x14
	void VTable0x18() override;                                              // vtable+0x18
	void VTable0x1c(const ColorRGBA&) override;                              // vtable+0x1c
	void VTable0x20(AmberLens0x344*) override;                               // vtable+0x20
	void VTable0x28() override;                                              // vtable+0x28
	void VTable0x2c(const Field0x124*) override;                             // vtable+0x2c
	void VTable0x30(const Field0x124*) override;                             // vtable+0x30
	void VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08) override; // vtable+0x34
	void VTable0x38() override;                                              // vtable+0x38
	void VTable0x3c(LegoU32) override;                                       // vtable+0x3c
	void VTable0x40() override;                                              // vtable+0x40
	SlatePeak0x58* VTable0x4c(undefined2, undefined2) override;              // vtable+0x4c
	void VTable0x50(SlatePeak0x58*) override;                                // vtable+0x50
	void VTable0x54(undefined4) override;                                    // vtable+0x54
	void VTable0x58(SlatePeak0x58*, undefined4) override;                    // vtable+0x58
	void VTable0x5c() override;                                              // vtable+0x5c
	void VTable0x60() override;                                              // vtable+0x60
	undefined4 VTable0x64(
		undefined4,
		GolFontBase0x40*,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) override; // vtable+0x64
	undefined4 VTable0x68(
		undefined4,
		GolFontBase0x40*,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) override; // vtable+0x68
	undefined4 VTable0x6c(
		undefined4,
		GolFontBase0x40*,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	) override; // vtable+0x6c
	void VTable0x70(UtopianPan0xa4*, undefined4, LegoS32, LegoS32, LegoS32,
					LegoS32) override; // vtable+0x70
	void VTable0x74(
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
	) override;                                                               // vtable+0x74
	void VTable0x78(UtopianPan0xa4*, undefined4, Rect*, undefined4) override; // vtable+0x78
	undefined4 VTable0x7c(
		UtopianPan0xa4* p_image,
		undefined4 p_unk0x08,
		Rect* p_destRect,
		Rect* p_sourceRect,
		undefined4 p_unk0x14
	) override; // vtable+0x7c
	void DrawRectangle(
		const Rect& p_rect,
		LegoFloat p_z,
		const ColorRGBA& p_color1,
		const ColorRGBA& p_color2,
		const ColorRGBA& p_color3,
		const ColorRGBA& p_color4,
		undefined4 p_arg7
	) override; // vtable+0x80
	void DrawTriangle(
		const TexturedVertex* p_vertex0,
		const TexturedVertex* p_vertex1,
		const TexturedVertex* p_vertex2,
		DuskwindBananaRelic0x24* p_material,
		undefined4 p_flags
	) override;                                                             // vtable+0x84
	void VTable0x88(undefined4, undefined4, undefined4) override;           // vtable+0x88
	void VTable0x8c(undefined4, undefined4, undefined4) override;           // vtable+0x8c
	void VTable0x90() override;                                             // vtable+0x90
	void VTable0x94(undefined4) override;                                   // vtable+0x94
	void VTable0x98(undefined4, undefined4, undefined4) override;           // vtable+0x98
	void VTable0x9c(undefined4, undefined4, undefined4) override;           // vtable+0x9c
	void VTable0xa8(undefined4, undefined4, undefined4) override;           // vtable+0xa8
	void VTable0xac(undefined4, undefined4) override;                       // vtable+0xac
	void VTable0xb0(undefined4, undefined4) override;                       // vtable+0xb0
	void VTable0xb4(FloatyPontoon0x4c&) override;                           // vtable+0xb4
	void SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags) override; // vtable+0xb8
	void ClearAlphaOverride() override;                                     // vtable+0xbc
	void VTable0xc0(const ColorRGBA&) override;                             // vtable+0xc0
	void VTable0xc4() override;                                             // vtable+0xc4
	void VTable0xc8() override;                                             // vtable+0xc8
	void VTable0xcc() override;                                             // vtable+0xcc
	void VTable0xd0() override;                                             // vtable+0xd0
	void VTable0xd4() override;                                             // vtable+0xd4
	void VTable0xd8() override;                                             // vtable+0xd8
	void VTable0xdc() override;                                             // vtable+0xdc
	void VTable0xe0() override;                                             // vtable+0xe0
	void VTable0xe4() override;                                             // vtable+0xe4
	void VTable0xe8(LegoBool32 p_arg) override;                             // vtable+0xe8
	void VTable0xec(undefined4) override;                                   // vtable+0xec
	void VTable0xf0() override;                                             // vtable+0xf0
	void VTable0xf4() override;                                             // vtable+0xf4
	LegoU32 GetMinimumTextureWidth(undefined4) const override;              // vtable+0xf8
	LegoU32 GetMaximumTextureWidth(undefined4) const override;              // vtable+0xfc
	LegoU32 GetMinimumTextureHeight(undefined4) const override;             // vtable+0x100
	LegoU32 GetMaximumTextureHeight(undefined4) const override;             // vtable+0x104
	LegoBool32 TexturesMustBeSquare() const override;                       // vtable+0x108
	LegoBool32 TextureSizesMustBePowersOfTwo() const override;              // vtable+0x10c
	LegoBool32 VTable0x110() const override;                                // vtable+0x110

	undefined4 FUN_10007d90(GolDrawDPState*, SlatePeak0x58*, LegoU32 p_flags);
	undefined4 FUN_10007e20(LegoU32 p_flags);

	LPDIRECT3D3 GetDirect3D3() const;
	LPDIRECTDRAW4 GetDirectDraw4() const;
	LPDIRECT3DDEVICE3 GetDirect3DDevice() const { return m_d3dDevice; }
	SoftwareRenderer0x58& GetSoftwareRenderer() { return m_softwareRenderer; }
	undefined4 GetUnk0xc8704() const { return m_unk0xc8704; }

	// SYNTHETIC: GOLDP 0x10007960
	// BronzeFalcon0xc8770::`scalar deleting destructor'

	friend class PearlDew0x0c;
	friend class SlatePeak0x58;

private:
	static LegoFloat ScaleColorChannel(double p_color, double p_materialColor)
	{
		return static_cast<LegoFloat>(p_color * p_materialColor) * 0.00390625f;
	}

	void FUN_100082e0();
	void FUN_1000a2c0(DuskwindBananaRelic0x24*);
	void FUN_1000a950(DuskwindBananaRelic0x24*);
	void FUN_1000ac00(GoldDune0x38*);
	void FUN_1000b0f0(LegoU32 p_index, const Field0x124* p_param);
	void FUN_1000b4a0();
	void FUN_1000be20(undefined4, undefined4, undefined4);
	void FUN_1000bfb0(undefined4, undefined4, undefined4);
	void FUN_1000c160(undefined4, undefined4, undefined4);
	void FUN_1000c2d0(undefined4, undefined4, undefined4);
	void FUN_1000c470(undefined4, undefined4, undefined4);
	void FUN_1000c630(undefined4, undefined4, undefined4);
	void FUN_1000d210(undefined4, undefined4, undefined4);
	void FUN_1000d440(undefined4, undefined4, undefined4);
	void FUN_1000d5d0(undefined4, undefined4, undefined4);
	void FUN_1000d760(undefined4, undefined4, undefined4);
	void FUN_1000dbb0(undefined4, undefined4, undefined4);
	void FUN_1000eb90(undefined4, undefined4, undefined4);
	void FUN_1000ebd0(undefined4, undefined4, undefined4);
	void FUN_1000ece0(undefined4, undefined4, undefined4);
	void FUN_1000edf0(undefined4, undefined4, undefined4);
	void FUN_10010330(undefined4, undefined4, undefined4);
	void FUN_10010500(undefined4, undefined4, undefined4);
	void FUN_100106d0(undefined4, undefined4, undefined4);
	void FUN_10011e60(undefined4, undefined4, undefined4);
	void FUN_10011ed0(undefined4, undefined4, undefined4);
	void FUN_10012030(undefined4, undefined4, undefined4);
	void FUN_100121e0(undefined4, undefined4, undefined4);
	void FUN_100123e0(undefined4, undefined4, undefined4);
	void FUN_10012640(undefined4, undefined4, undefined4);
	void FUN_100128f0(undefined4, undefined4, undefined4);
	void FUN_10012bf0(undefined4, undefined4, undefined4);
	void FUN_10012f50();
	void FUN_10013110(undefined4, undefined4, undefined4);
	void FUN_100132f0(undefined4, undefined4, undefined4);
	void Reset();
	static HRESULT CALLBACK CountTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context);
	static HRESULT CALLBACK EnumerateTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context);
	static BronzeFalconDrawFunction g_unk0x1005c8a8[8];
	static BronzeFalconDrawFunction g_unk0x1005c8c8[8];

	GolDrawDPState* m_drawState;                                         // 0x140
	LPDIRECT3DDEVICE3 m_d3dDevice;                                       // 0x144
	D3DDEVICEDESC m_d3dDeviceDesc;                                       // 0x148
	LPDIRECT3DVIEWPORT3 m_d3dViewport;                                   // 0x244
	D3DVIEWPORT2 m_viewportParams;                                       // 0x248
	D3DMATERIAL m_materialParams;                                        // 0x274
	LPDIRECT3DMATERIAL3 m_backgroundMaterial;                            // 0x2c4
	D3DMATERIALHANDLE m_backgroundMaterialHandle;                        // 0x2c8
	ColorRGBA m_clearColor;                                              // 0x2cc
	LegoU32 m_clearPixelValue;                                           // 0x2d0
	DuskwindBananaRelic0x30 m_unk0x2d4;                                  // 0x2d4
	SlatePeak0x58* m_unk0x304;                                           // 0x304
	SlatePeak0x58* m_renderTargetInfo;                                   // 0x308
	BronzeFalconSurface0x5c* m_unk0x30c;                                 // 0x30c
	DepthBuffer0x38 m_depthBuffer;                                       // 0x310
	D3DTLVERTEX m_unk0x348[25000];                                       // 0x348
	undefined4 m_unk0xc3848;                                             // 0xc3848
	undefined4 m_unk0xc384c;                                             // 0xc384c
	undefined m_unk0xc3850[0xc38ec - 0xc3850];                           // 0xc3850
	undefined4 m_unk0xc38ec[(0xc426c - 0xc38ec) / sizeof(undefined4)];   // 0xc38ec
	undefined m_unk0xc426c[0xc428c - 0xc426c];                           // 0xc426c
	undefined4 m_unk0xc428c[(0xc4c0c - 0xc428c) / sizeof(undefined4)];   // 0xc428c
	undefined4 m_unk0xc4c0c;                                             // 0xc4c0c
	undefined4 m_unk0xc4c10;                                             // 0xc4c10
	undefined4 m_unk0xc4c14;                                             // 0xc4c14
	undefined4 m_unk0xc4c18;                                             // 0xc4c18
	undefined m_unk0xc4c1c[0xc53a0 - 0xc4c1c];                           // 0xc4c1c
	D3DTLVERTEX m_unk0xc53a0[(0xc83a0 - 0xc53a0) / sizeof(D3DTLVERTEX)]; // 0xc53a0
	undefined4 m_unk0xc83a0;                                             // 0xc83a0
	undefined4 m_unk0xc83a4;                                             // 0xc83a4
	GoldDune0x38* m_currentTexture;                                      // 0xc83a8
	undefined4 m_unk0xc83ac;                                             // 0xc83ac
	undefined4 m_unk0xc83b0;                                             // 0xc83b0
	Field0xc83b4 m_unk0xc83b4;                                           // 0xc83b4
	undefined4 m_unk0xc83c4;                                             // 0xc83c4
	undefined4 m_unk0xc83c8;                                             // 0xc83c8
	undefined4 m_unk0xc83cc;                                             // 0xc83cc
	undefined4 m_unk0xc83d0;                                             // 0xc83d0
	undefined4 m_unk0xc83d4;                                             // 0xc83d4
	undefined4 m_unk0xc83d8;                                             // 0xc83d8
	undefined4 m_unk0xc83dc;                                             // 0xc83dc
	undefined4 m_unk0xc83e0;                                             // 0xc83e0
	undefined4 m_unk0xc83e4;                                             // 0xc83e4
	LegoBool32 m_unk0xc83e8;                                             // 0xc83e8
	undefined4 m_unk0xc83ec;                                             // 0xc83ec
	undefined4 m_unk0xc83f0;                                             // 0xc83f0
	undefined4 m_unk0xc83f4;                                             // 0xc83f4
	LegoBool32 m_unk0xc83f8;                                             // 0xc83f8
	LegoU32 m_unk0xc83fc;                                                // 0xc83fc
	undefined4 m_unk0xc8400[4];                                          // 0xc8400
	GolMatrix4 m_unk0xc8410;                                             // 0xc8410
	GolMatrix4 m_unk0xc8450;                                             // 0xc8450
	GolMatrix4* m_unk0xc8490;                                            // 0xc8490
	GolMatrix4* m_unk0xc8494;                                            // 0xc8494
	GolMatrix4 m_unk0xc8498[1];                                          // 0xc8498
	LegoFloat m_unk0xc84d8[(0xc8518 - 0xc84d8) / sizeof(LegoFloat)];     // 0xc84d8
	GolMatrix4* m_unk0xc8518;                                            // 0xc8518
	undefined4 m_unk0xc851c;                                             // 0xc851c
	undefined4 m_unk0xc8520;                                             // 0xc8520
	undefined4 m_unk0xc8524;                                             // 0xc8524
	undefined4 m_unk0xc8528;                                             // 0xc8528
	LegoFloat m_unk0xc852c;                                              // 0xc852c
	void* m_unk0xc8530;                                                  // 0xc8530
	void* m_unk0xc8534;                                                  // 0xc8534
	DuskwindBananaRelic0x24* m_unk0xc8538;                               // 0xc8538
	void* m_unk0xc853c;                                                  // 0xc853c
	void* m_unk0xc8540;                                                  // 0xc8540
	void* m_unk0xc8544;                                                  // 0xc8544
	void* m_unk0xc8548;                                                  // 0xc8548
	void* m_unk0xc854c[(0xc8568 - 0xc854c) / sizeof(void*)];             // 0xc854c
	undefined4 m_unk0xc8568;                                             // 0xc8568
	ColorRGBA m_unk0xc856c;                                              // 0xc856c
	undefined4 m_unk0xc8570;                                             // 0xc8570
	undefined4 m_unk0xc8574;                                             // 0xc8574
	undefined4 m_unk0xc8578;                                             // 0xc8578
	undefined4 m_unk0xc857c;                                             // 0xc857c
	ColorRGBA m_unk0xc8580[7];                                           // 0xc8580
	FColorRGB m_unk0xc859c[7];                                           // 0xc859c
	FColorRGB m_unk0xc85f0[7];                                           // 0xc85f0
	undefined m_unk0xc8644[0xc8698 - 0xc8644];                           // 0xc8644
	SoftwareRenderer0x58 m_softwareRenderer;                             // 0xc8698
	SoftwareRenderer0x58::Command0x14* m_unk0xc86f0;                     // 0xc86f0
	LegoS32 m_unk0xc86f4;                                                // 0xc86f4
	LegoS32 m_unk0xc86f8;                                                // 0xc86f8
	float m_unk0xc86fc;                                                  // 0xc86fc
	undefined4 m_unk0xc8700;                                             // 0xc8700
	undefined4 m_unk0xc8704;                                             // 0xc8704
	D3DBLEND m_unk0xc8708[11];                                           // 0xc8708
	D3DBLEND m_unk0xc8734[11];                                           // 0xc8734
	BronzeFalconDrawFunction m_unk0xc8760;                               // 0xc8760
	BronzeFalconDrawFunction m_unk0xc8764;                               // 0xc8764
	BronzeFalconDrawFunction m_unk0xc8768;                               // 0xc8768
	void (BronzeFalcon0xc8770::*m_unk0xc876c)(DuskwindBananaRelic0x24*); // 0xc876c
};

#endif // BRONZEFALCON0XC8770_H
