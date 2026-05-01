#ifndef BRONZEFALCON0XC8770_H
#define BRONZEFALCON0XC8770_H

#include "compat.h"
#include "decomp.h"
#include "duskwindbananarelic0x30.h"
#include "moltenquillphantom0x38.h"
#include "types.h"
#include "whitefalcon0x140.h"
#include "workhorse0x58.h"

class GolCommonDrawState;
class AmberLens0x344;

// VTABLE: GOLDP 0x100565b8
// SIZE 0xc8770
class BronzeFalcon0xc8770 : public WhiteFalcon0x140 {
public:
	BronzeFalcon0xc8770();

	void VTable0x04() override;                                              // vtable+0x04
	~BronzeFalcon0xc8770() override;                                         // vtable+0x08
	void VTable0x0c(undefined4, undefined4, undefined4) override;            // vtable+0x0c
	GolCommonDrawState* GetDrawState() override;                             // vtable+0x10
	const RenderTargetInfo* GetRenderTargetInfo() override;                  // vtable+0x14
	void VTable0x18() override;                                              // vtable+0x18
	void VTable0x1c(JasperRipple0x4*) override;                              // vtable+0x1c
	void VTable0x20(AmberLens0x344*) override;                               // vtable+0x20
	void VTable0x28() override;                                              // vtable+0x28
	void VTable0x2c(undefined4) override;                                    // vtable+0x2c
	void VTable0x30(undefined4) override;                                    // vtable+0x30
	void VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08) override; // vtable+0x34
	void VTable0x38() override;                                              // vtable+0x38
	void VTable0x3c(undefined4) override;                                    // vtable+0x3c
	void VTable0x40() override;                                              // vtable+0x40
	undefined4 VTable0x4c(undefined4, undefined4) override;                  // vtable+0x4c
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
	void VTable0xe8(undefined4) override;                                   // vtable+0xe8
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

	undefined4* FUN_004131a0(const LegoChar* p_name);

	// SYNTHETIC: GOLDP 0x10007960
	// BronzeFalcon0xc8770::`scalar deleting destructor'

private:
	void Reset();

	GolCommonDrawState* m_drawState;          // 0x140
	undefined m_unk0x144[0x2d4 - 0x144];      // 0x144
	DuskwindBananaRelic0x30 m_unk0x2d4;       // 0x2d4
	undefined m_unk0x304[0x308 - 0x304];      // 0x304
	RenderTargetInfo* m_renderTargetInfo;     // 0x308
	undefined m_unk0x30c[0x310 - 0x30c];      // 0x30c
	MoltenQuillPhantom0x38 m_unk0x310;        // 0x310
	undefined m_unk0x348[0xc8698 - 0x348];    // 0x348
	WorkHorse0x58 m_unk0xc8698;               // 0xc8698
	undefined m_unk0x86f0[0xc8770 - 0xc86f0]; // 0xc86f0
};

#endif // BRONZEFALCON0XC8770_H
