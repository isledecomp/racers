#ifndef BRONZEFALCON0XC8770_H
#define BRONZEFALCON0XC8770_H

#include "compat.h"
#include "decomp.h"
#include "depthbuffer0x38.h"
#include "duskwindbananarelic0x30.h"
#include "types.h"
#include "whitefalcon0x140.h"
#include "workhorse0x58.h"

#include <d3d.h>

class BronzeFalconSurface0x5c;
class AmberLens0x344;
class GolDrawDPState;

// VTABLE: GOLDP 0x100565b8
// SIZE 0xc8770
class BronzeFalcon0xc8770 : public WhiteFalcon0x140 {
public:
	BronzeFalcon0xc8770();

	void ReleaseResources() override;                                        // vtable+0x04
	~BronzeFalcon0xc8770() override;                                         // vtable+0x08
	void VTable0x0c(undefined4, undefined4, undefined4) override;            // vtable+0x0c
	GolCommonDrawState* GetDrawState() override;                             // vtable+0x10
	const SlatePeak0x58* GetRenderTargetInfo() override;                     // vtable+0x14
	void VTable0x18() override;                                              // vtable+0x18
	void VTable0x1c(const ColorRGBA&) override;                              // vtable+0x1c
	void VTable0x20(AmberLens0x344*) override;                               // vtable+0x20
	void VTable0x28() override;                                              // vtable+0x28
	void VTable0x2c(undefined4) override;                                    // vtable+0x2c
	void VTable0x30(undefined4) override;                                    // vtable+0x30
	void VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08) override; // vtable+0x34
	void VTable0x38() override;                                              // vtable+0x38
	void VTable0x3c(undefined4) override;                                    // vtable+0x3c
	void VTable0x40() override;                                              // vtable+0x40
	SlatePeak0x58* VTable0x4c(undefined2, undefined2) override;              // vtable+0x4c
	void VTable0x50(undefined4) override;                                    // vtable+0x50
	void VTable0x54(undefined4) override;                                    // vtable+0x54
	void VTable0x58(undefined4, undefined4) override;                        // vtable+0x58
	void VTable0x5c() override;                                              // vtable+0x5c
	void VTable0x60() override;                                              // vtable+0x60
	void VTable0x64() override;                                              // vtable+0x64
	void VTable0x68() override;                                              // vtable+0x68
	void VTable0x6c() override;                                              // vtable+0x6c
	void VTable0x70() override;                                              // vtable+0x70
	void VTable0x74() override;                                              // vtable+0x74
	void VTable0x78() override;                                              // vtable+0x78
	void VTable0x7c() override;                                              // vtable+0x7c
	void VTable0x80() override;                                              // vtable+0x80
	void DrawTriangle(
		const TexturedVertex* p_vertex0,
		const TexturedVertex* p_vertex1,
		const TexturedVertex* p_vertex2,
		undefined4 p_material,
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
	void VTable0xb4() override;                                             // vtable+0xb4
	void SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags) override; // vtable+0xb8
	void ClearAlphaOverride() override;                                     // vtable+0xbc
	void VTable0xc0(undefined4*) override;                                  // vtable+0xc0
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
	void VTable0xf8() override;                                             // vtable+0xf8
	void VTable0xfc() override;                                             // vtable+0xfc
	void VTable0x100() override;                                            // vtable+0x100
	void VTable0x104() override;                                            // vtable+0x104
	void VTable0x108() override;                                            // vtable+0x108
	void VTable0x10c() override;                                            // vtable+0x10c
	LegoBool32 VTable0x110() const override;                                // vtable+0x110

	undefined4 FUN_10007d90(GolDrawDPState*, SlatePeak0x58*, LegoU32 p_flags);
	undefined4 FUN_10007e20(LegoU32 p_flags);

	LPDIRECT3D3 GetDirect3D3() const;
	LPDIRECTDRAW4 GetDirectDraw4() const;

	// SYNTHETIC: GOLDP 0x10007960
	// BronzeFalcon0xc8770::`scalar deleting destructor'

private:
	struct TextureFormat : public FalconTextureFormat {
		TextureFormat();
	};

	void FUN_100082e0();
	void FUN_1000a2c0(undefined*);
	void FUN_1000a950(undefined*);
	void FUN_1000b4a0();
	void Reset();
	static HRESULT CALLBACK CountTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context);
	static HRESULT CALLBACK EnumerateTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context);

	struct Field0xc83b4 {
		undefined4 m_unk0x00;
		undefined4 m_unk0x04;
		undefined4 m_unk0x08;
		undefined4 m_unk0x0c;
	};

	GolDrawDPState* m_drawState;                           // 0x140
	LPDIRECT3DDEVICE3 m_d3dDevice;                         // 0x144
	D3DDEVICEDESC m_d3dDeviceDesc;                         // 0x148
	LPDIRECT3DVIEWPORT3 m_d3dViewport;                     // 0x244
	D3DVIEWPORT2 m_viewportParams;                         // 0x248
	D3DMATERIAL m_materialParams;                          // 0x274
	LPDIRECT3DMATERIAL3 m_backgroundMaterial;              // 0x2c4
	D3DMATERIALHANDLE m_backgroundMaterialHandle;          // 0x2c8
	ColorRGBA m_unk0x2cc;                                  // 0x2cc
	LegoU32 m_unk0x2d0;                                    // 0x2d0
	DuskwindBananaRelic0x30 m_unk0x2d4;                    // 0x2d4
	SlatePeak0x58* m_unk0x304;                             // 0x304
	SlatePeak0x58* m_renderTargetInfo;                     // 0x308
	BronzeFalconSurface0x5c* m_unk0x30c;                   // 0x30c
	DepthBuffer0x38 m_depthBuffer;                         // 0x310
	undefined m_unk0x348[0xc384c - 0x348];                 // 0x348
	undefined4 m_unk0xc384c;                               // 0xc384c
	undefined m_unk0xc3850[0xc83b4 - 0xc3850];             // 0xc3850
	Field0xc83b4 m_unk0xc83b4;                             // 0xc83b4
	undefined4 m_unk0xc83c4;                               // 0xc83c4
	undefined m_unk0xc83c8[0xc8698 - 0xc83c8];             // 0xc83c8
	WorkHorse0x58 m_unk0xc8698;                            // 0xc8698
	undefined m_unk0xc86f0[0xc86fc - 0xc86f0];             // 0xc86f0
	float m_unk0xc86fc;                                    // 0xc86fc
	undefined4 m_unk0xc8700;                               // 0xc8700
	undefined m_unk0xc8704[0xc8708 - 0xc8704];             // 0xc8704
	undefined4 m_unk0xc8708[11];                           // 0xc8708
	undefined4 m_unk0xc8734[11];                           // 0xc8734
	undefined m_unk0xc8760[0xc876c - 0xc8760];             // 0xc8760
	void (BronzeFalcon0xc8770::*m_unk0xc876c)(undefined*); // 0xc876c
};

#endif // BRONZEFALCON0XC8770_H
