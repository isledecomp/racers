#ifndef WHITEFALCON0x140_H
#define WHITEFALCON0x140_H

#include "color.h"
#include "decomp.h"
#include "falcontextureformat.h"
#include "types.h"

class AmberHaze0x1c;
class AmberLens0x344;
class BronzeFalcon0xc8770;
class CinderBasin0x28;
class FalconTextureFormat;
class GolCommonDrawState;
class GolNameTable;
class HypnoticNoise0x1c;
class MagentaRibbon0x20;
class SlatePeak0x58;

// VTABLE: GOLDP 0x10057338
// SIZE 0x140
class WhiteFalcon0x140 {
public:
	// SIZE 0x18
	struct TexturedVertex {
		LegoFloat m_x;  // 0x00
		LegoFloat m_y;  // 0x04
		LegoFloat m_z;  // 0x08
		LegoFloat m_u;  // 0x0c
		LegoFloat m_v;  // 0x10
		LegoU8 m_red;   // 0x14
		LegoU8 m_green; // 0x15
		LegoU8 m_blue;  // 0x16
		LegoU8 m_alpha; // 0x17
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
		c_flagBit14 = 1 << 14,
		c_flagBit15 = 1 << 15,
		c_flagBit16 = 1 << 16,
		c_flagBit18 = 1 << 18,
		c_flagBit19 = 1 << 19,
		c_flagBit20 = 1 << 20,
		c_flagBit24 = 1 << 24,
	};

	WhiteFalcon0x140();

	virtual void VTable0x00();                                              // vtable+0x00
	virtual void VTable0x04();                                              // vtable+0x04
	virtual ~WhiteFalcon0x140();                                            // vtable+0x08
	virtual void VTable0x0c(undefined4, undefined4, undefined4);            // vtable+0x0c
	virtual GolCommonDrawState* GetDrawState() = 0;                         // vtable+0x10
	virtual const SlatePeak0x58* GetRenderTargetInfo() = 0;                 // vtable+0x14
	virtual void VTable0x18() = 0;                                          // vtable+0x18
	virtual void VTable0x1c(const ColorRGBA&) = 0;                          // vtable+0x1c
	virtual void VTable0x20(AmberLens0x344*) = 0;                           // vtable+0x20
	virtual void VTable0x24();                                              // vtable+0x24
	virtual void VTable0x28();                                              // vtable+0x28
	virtual void VTable0x2c(undefined4 p_param);                            // vtable+0x2c
	virtual void VTable0x30(undefined4 p_param);                            // vtable+0x30
	virtual void VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08); // vtable+0x34
	virtual void VTable0x38();                                              // vtable+0x38
	virtual void VTable0x3c(undefined4);                                    // vtable+0x3c
	virtual void VTable0x40();                                              // vtable+0x40
	virtual void VTable0x44();                                              // vtable+0x44
	virtual void VTable0x48();                                              // vtable+0x48
	virtual SlatePeak0x58* VTable0x4c(undefined2, undefined2);              // vtable+0x4c
	virtual void VTable0x50(undefined4);                                    // vtable+0x50
	virtual void VTable0x54(undefined4) = 0;                                // vtable+0x54
	virtual void VTable0x58(undefined4 p_param1, undefined4 p_param2);      // vtable+0x58
	virtual void VTable0x5c() = 0;                                          // vtable+0x5c
	virtual void VTable0x60();                                              // vtable+0x60
	virtual void VTable0x64() = 0;                                          // vtable+0x64
	virtual void VTable0x68() = 0;                                          // vtable+0x68
	virtual void VTable0x6c() = 0;                                          // vtable+0x6c
	virtual void VTable0x70() = 0;                                          // vtable+0x70
	virtual void VTable0x74() = 0;                                          // vtable+0x74
	virtual void VTable0x78() = 0;                                          // vtable+0x78
	virtual void VTable0x7c() = 0;                                          // vtable+0x7c
	virtual void VTable0x80() = 0;                                          // vtable+0x80
	virtual void DrawTriangle(
		const TexturedVertex* p_vertex0,
		const TexturedVertex* p_vertex1,
		const TexturedVertex* p_vertex2,
		undefined4 p_material,
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
	virtual void VTable0xb4() = 0;                                                          // vtable+0xb4
	virtual void SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags);                  // vtable+0xb8
	virtual void ClearAlphaOverride();                                                      // vtable+0xbc
	virtual void VTable0xc0(undefined4* p_param);                                           // vtable+0xc0
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
	virtual void VTable0xf8() = 0;                                                          // vtable+0xf8
	virtual void VTable0xfc() = 0;                                                          // vtable+0xfc
	virtual void VTable0x100() = 0;                                                         // vtable+0x100
	virtual void VTable0x104() = 0;                                                         // vtable+0x104
	virtual void VTable0x108() = 0;                                                         // vtable+0x108
	virtual void VTable0x10c() = 0;                                                         // vtable+0x10c
	virtual LegoBool32 VTable0x110() const;

	void Destroy();
	void FUN_10028a70(CinderBasin0x28* p_param);
	void FUN_10028a80(CinderBasin0x28* p_param);
	void FUN_10028ad0(HypnoticNoise0x1c* p_param);
	void FUN_10028ae0(HypnoticNoise0x1c* p_param);
	void FUN_10028b30(MagentaRibbon0x20* p_param);
	void FUN_10028b40(MagentaRibbon0x20* p_param);
	void* FUN_10028b90(const LegoChar* p_name);
	void FUN_10028bc0(AmberHaze0x1c* p_param);
	void FUN_10028bd0(AmberHaze0x1c* p_param);
	void* FUN_10028c20(const LegoChar* p_name);

	// SYNTHETIC: GOLDP 0x100288b0
	// WhiteFalcon0x140::`scalar deleting destructor'

	undefined4 GetUnk0x04() { return m_unk0x04; }
	AmberLens0x344* GetUnk0x0c() { return m_unk0x0c; }

protected:
	friend class GolCommonDrawState;

	undefined4 m_unk0x04;                         // 0x04
	undefined2 m_unk0x08;                         // 0x08
	undefined2 m_unk0x0a;                         // 0x0a
	AmberLens0x344* m_unk0x0c;                    // 0x0c
	undefined4 m_unk0x10;                         // 0x10
	undefined4 m_unk0x14;                         // 0x14
	undefined4 m_unk0x18;                         // 0x18
	undefined4 m_unk0x1c;                         // 0x1c
	undefined4 m_unk0x20;                         // 0x20
	undefined4 m_unk0x24;                         // 0x24
	undefined4 m_unk0x28;                         // 0x28
	undefined4 m_unk0x2c;                         // 0x2c
	undefined4 m_countTextureFormats;             // 0x30
	FalconTextureFormat* m_textureFormats;        // 0x34
	MagentaRibbon0x20* m_unk0x38;                 // 0x38
	AmberHaze0x1c* m_unk0x3c;                     // 0x3c
	HypnoticNoise0x1c* m_unk0x40;                 // 0x40
	CinderBasin0x28* m_unk0x44;                   // 0x44
	BronzeFalcon0xc8770* m_nextDrawStateRenderer; // 0x48
	undefined m_unk0x4c[0x118 - 0x4c];            // 0x4c
	undefined4 m_unk0x118;                        // 0x118
	undefined4 m_unk0x11c;                        // 0x11c
	undefined4 m_unk0x120;                        // 0x120
	undefined4 m_unk0x124[7];                     // 0x124
};

#endif // WHITEFALCON0x140_H
