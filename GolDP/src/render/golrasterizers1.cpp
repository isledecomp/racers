#include "render/golrasterizers1.h"

#include "decomp.h"
#include "golcpu.h"
#include "render/golsoftwarerenderer.h"

// GLOBAL: GOLDP 0x1005799c
const LegoFloat g_floatConst65536 = 65536.0f;

// GLOBAL: GOLDP 0x100579e0
__int64 g_unk0x100579e0 = 0x00FFFF0000FFFF00i64;

// GLOBAL: GOLDP 0x100579e8
__int64 g_unk0x100579e8 = 0x8000800080008000i64;

// GLOBAL: GOLDP 0x100579f0
__int64 g_unk0x100579f0 = 0x001F001F001F001Fi64;

// GLOBAL: GOLDP 0x100579f8
__int64 g_unk0x100579f8 = 0x0040000000010800i64;

// GLOBAL: GOLDP 0x10057a00
__int64 g_unk0x10057a00 = 0x0020000000010400i64;

// GLOBAL: GOLDP 0x10057a08
GolSoftwareRenderer::SpanRasterizerCallback g_spanRasterizers[84] = {
	FUN_10034db0, FUN_10036330, FUN_100378b0, FUN_10038e30, FUN_1003a3b0, FUN_1003b930, FUN_10034c40, FUN_100361c0,
	FUN_10037740, FUN_10038cc0, FUN_1003a240, FUN_1003b7c0, FUN_10034b10, FUN_10036090, FUN_10037610, FUN_10038b90,
	FUN_1003a110, FUN_1003b690, FUN_10034980, FUN_10035f00, FUN_10037480, FUN_10038a00, FUN_10039f80, FUN_1003b500,
	FUN_100345e0, FUN_10035b60, FUN_100370e0, FUN_10038660, FUN_10039be0, FUN_1003b160, FUN_100344a0, FUN_10035a20,
	FUN_10036fa0, FUN_10038520, FUN_10039aa0, FUN_1003b020, FUN_10034850, FUN_10035dd0, FUN_10037350, FUN_100388d0,
	FUN_10039e50, FUN_1003b3d0, FUN_10034720, FUN_10035ca0, FUN_10037220, FUN_100387a0, FUN_10039d20, FUN_1003b2a0,
	FUN_10033a20, FUN_10034fc0, FUN_10036540, FUN_10037ac0, FUN_10039040, FUN_1003a5c0, FUN_10033900, FUN_10034ea0,
	FUN_10036420, FUN_100379a0, FUN_10038f20, FUN_1003a4a0, FUN_10033d90, FUN_10035330, FUN_100368b0, FUN_10037e30,
	FUN_100393b0, FUN_1003a930, FUN_10033b40, FUN_100350e0, FUN_10036660, FUN_10037be0, FUN_10039160, FUN_1003a6e0,
	FUN_10034240, FUN_100357d0, FUN_10036d50, FUN_100382d0, FUN_10039850, FUN_1003add0, FUN_10033fe0, FUN_10035580,
	FUN_10036b00, FUN_10038080, FUN_10039600, FUN_1003ab80,
};

// GLOBAL: GOLDP 0x10057b58
LegoU8 g_unk0x10057b58[0x100] = {
	0x00, 0x80, 0x20, 0xA0, 0x08, 0x88, 0x28, 0xA8, 0x02, 0x82, 0x22, 0xA2, 0x0A, 0x8A, 0x2A, 0xAA, 0xC0, 0x40, 0xE0,
	0x60, 0xC8, 0x48, 0xE8, 0x68, 0xC2, 0x42, 0xE2, 0x62, 0xCA, 0x4A, 0xEA, 0x6A, 0x30, 0xB0, 0x10, 0x90, 0x38, 0xB8,
	0x18, 0x98, 0x32, 0xB2, 0x12, 0x92, 0x3A, 0xBA, 0x1A, 0x9A, 0xF0, 0x70, 0xD0, 0x50, 0xF8, 0x78, 0xD8, 0x58, 0xF2,
	0x72, 0xD2, 0x52, 0xFA, 0x7A, 0xDA, 0x5A, 0x0C, 0x8C, 0x2C, 0xAC, 0x04, 0x84, 0x24, 0xA4, 0x0E, 0x8E, 0x2E, 0xAE,
	0x06, 0x86, 0x26, 0xA6, 0xCC, 0x4C, 0xEC, 0x6C, 0xC4, 0x44, 0xE4, 0x64, 0xCE, 0x4E, 0xEE, 0x6E, 0xC6, 0x46, 0xE6,
	0x66, 0x3C, 0xBC, 0x1C, 0x9C, 0x34, 0xB4, 0x14, 0x94, 0x3E, 0xBE, 0x1E, 0x9E, 0x36, 0xB6, 0x16, 0x96, 0xFC, 0x7C,
	0xDC, 0x5C, 0xF4, 0x74, 0xD4, 0x54, 0xFE, 0x7E, 0xDE, 0x5E, 0xF6, 0x76, 0xD6, 0x56, 0x03, 0x83, 0x23, 0xA3, 0x0B,
	0x8B, 0x2B, 0xAB, 0x01, 0x81, 0x21, 0xA1, 0x09, 0x89, 0x29, 0xA9, 0xC3, 0x43, 0xE3, 0x63, 0xCB, 0x4B, 0xEB, 0x6B,
	0xC1, 0x41, 0xE1, 0x61, 0xC9, 0x49, 0xE9, 0x69, 0x33, 0xB3, 0x13, 0x93, 0x3B, 0xBB, 0x1B, 0x9B, 0x31, 0xB1, 0x11,
	0x91, 0x39, 0xB9, 0x19, 0x99, 0xF3, 0x73, 0xD3, 0x53, 0xFB, 0x7B, 0xDB, 0x5B, 0xF1, 0x71, 0xD1, 0x51, 0xF9, 0x79,
	0xD9, 0x59, 0x0F, 0x8F, 0x2F, 0xAF, 0x07, 0x87, 0x27, 0xA7, 0x0D, 0x8D, 0x2D, 0xAD, 0x05, 0x85, 0x25, 0xA5, 0xCF,
	0x4F, 0xEF, 0x6F, 0xC7, 0x47, 0xE7, 0x67, 0xCD, 0x4D, 0xED, 0x6D, 0xC5, 0x45, 0xE5, 0x65, 0x3F, 0xBF, 0x1F, 0x9F,
	0x37, 0xB7, 0x17, 0x97, 0x3D, 0xBD, 0x1D, 0x9D, 0x35, 0xB5, 0x15, 0x95, 0xFF, 0x7F, 0xDF, 0x5F, 0xF7, 0x77, 0xD7,
	0x57, 0xFD, 0x7D, 0xDD, 0x5D, 0xF5, 0x75, 0xD5, 0x55,
};

// GLOBAL: GOLDP 0x10057c58
LegoU8 g_unk0x10057c58[1088] = {
	0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
	0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
	0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
	0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x1,  0x1,  0x1,
	0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,
	0x2,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x2,  0x2,
	0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x0,  0x0,  0x0,  0x0,  0x1,
	0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x3,  0x3,  0x3,  0x3,
	0x3,  0x3,  0x3,  0x4,  0x4,  0x4,  0x4,  0x4,  0x0,  0x0,  0x0,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x2,
	0x2,  0x2,  0x2,  0x2,  0x2,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x4,  0x4,  0x4,  0x4,  0x4,  0x4,  0x5,  0x5,
	0x5,  0x5,  0x0,  0x0,  0x0,  0x1,  0x1,  0x1,  0x1,  0x1,  0x2,  0x2,  0x2,  0x2,  0x2,  0x3,  0x3,  0x3,  0x3,
	0x3,  0x4,  0x4,  0x4,  0x4,  0x4,  0x4,  0x5,  0x5,  0x5,  0x5,  0x5,  0x6,  0x6,  0x6,  0x0,  0x0,  0x0,  0x1,
	0x1,  0x1,  0x1,  0x2,  0x2,  0x2,  0x2,  0x3,  0x3,  0x3,  0x3,  0x3,  0x4,  0x4,  0x4,  0x4,  0x5,  0x5,  0x5,
	0x5,  0x5,  0x6,  0x6,  0x6,  0x6,  0x7,  0x7,  0x7,  0x0,  0x0,  0x1,  0x1,  0x1,  0x1,  0x2,  0x2,  0x2,  0x2,
	0x3,  0x3,  0x3,  0x3,  0x4,  0x4,  0x4,  0x4,  0x5,  0x5,  0x5,  0x5,  0x6,  0x6,  0x6,  0x6,  0x7,  0x7,  0x7,
	0x8,  0x8,  0x8,  0x0,  0x0,  0x1,  0x1,  0x1,  0x1,  0x2,  0x2,  0x2,  0x3,  0x3,  0x3,  0x4,  0x4,  0x4,  0x4,
	0x5,  0x5,  0x5,  0x6,  0x6,  0x6,  0x6,  0x7,  0x7,  0x7,  0x8,  0x8,  0x8,  0x8,  0x9,  0x9,  0x0,  0x0,  0x1,
	0x1,  0x1,  0x2,  0x2,  0x2,  0x3,  0x3,  0x3,  0x4,  0x4,  0x4,  0x5,  0x5,  0x5,  0x6,  0x6,  0x6,  0x6,  0x7,
	0x7,  0x7,  0x8,  0x8,  0x8,  0x9,  0x9,  0x9,  0xA,  0xA,  0x0,  0x0,  0x1,  0x1,  0x1,  0x2,  0x2,  0x3,  0x3,
	0x3,  0x4,  0x4,  0x4,  0x5,  0x5,  0x5,  0x6,  0x6,  0x6,  0x7,  0x7,  0x7,  0x8,  0x8,  0x9,  0x9,  0x9,  0xA,
	0xA,  0xA,  0xB,  0xB,  0x0,  0x0,  0x1,  0x1,  0x2,  0x2,  0x2,  0x3,  0x3,  0x4,  0x4,  0x4,  0x5,  0x5,  0x5,
	0x6,  0x6,  0x7,  0x7,  0x7,  0x8,  0x8,  0x9,  0x9,  0x9,  0xA,  0xA,  0xA,  0xB,  0xB,  0xC,  0xC,  0x0,  0x0,
	0x1,  0x1,  0x2,  0x2,  0x3,  0x3,  0x3,  0x4,  0x4,  0x5,  0x5,  0x5,  0x6,  0x6,  0x7,  0x7,  0x8,  0x8,  0x8,
	0x9,  0x9,  0xA,  0xA,  0xB,  0xB,  0xB,  0xC,  0xC,  0xD,  0xD,  0x0,  0x0,  0x1,  0x1,  0x2,  0x2,  0x3,  0x3,
	0x4,  0x4,  0x5,  0x5,  0x5,  0x6,  0x6,  0x7,  0x7,  0x8,  0x8,  0x9,  0x9,  0xA,  0xA,  0xA,  0xB,  0xB,  0xC,
	0xC,  0xD,  0xD,  0xE,  0xE,  0x0,  0x1,  0x1,  0x1,  0x2,  0x2,  0x3,  0x3,  0x4,  0x4,  0x5,  0x5,  0x6,  0x6,
	0x7,  0x7,  0x8,  0x8,  0x9,  0x9,  0xA,  0xA,  0xB,  0xB,  0xC,  0xC,  0xD,  0xD,  0xE,  0xE,  0xF,  0xF,  0x0,
	0x1,  0x1,  0x2,  0x2,  0x3,  0x3,  0x4,  0x4,  0x5,  0x5,  0x6,  0x6,  0x7,  0x7,  0x8,  0x8,  0x9,  0x9,  0xA,
	0xA,  0xB,  0xB,  0xC,  0xC,  0xD,  0xD,  0xE,  0xE,  0xF,  0x10, 0x10, 0x0,  0x1,  0x1,  0x2,  0x2,  0x3,  0x3,
	0x4,  0x4,  0x5,  0x6,  0x6,  0x7,  0x7,  0x8,  0x8,  0x9,  0x9,  0xA,  0xA,  0xB,  0xC,  0xC,  0xD,  0xD,  0xE,
	0xE,  0xF,  0xF,  0x10, 0x10, 0x11, 0x0,  0x1,  0x1,  0x2,  0x2,  0x3,  0x4,  0x4,  0x5,  0x5,  0x6,  0x6,  0x7,
	0x8,  0x8,  0x9,  0x9,  0xA,  0xA,  0xB,  0xC,  0xC,  0xD,  0xD,  0xE,  0xF,  0xF,  0x10, 0x10, 0x11, 0x11, 0x12,
	0x0,  0x1,  0x1,  0x2,  0x2,  0x3,  0x4,  0x4,  0x5,  0x6,  0x6,  0x7,  0x7,  0x8,  0x9,  0x9,  0xA,  0xA,  0xB,
	0xC,  0xC,  0xD,  0xE,  0xE,  0xF,  0xF,  0x10, 0x11, 0x11, 0x12, 0x12, 0x13, 0x0,  0x1,  0x1,  0x2,  0x3,  0x3,
	0x4,  0x5,  0x5,  0x6,  0x6,  0x7,  0x8,  0x8,  0x9,  0xA,  0xA,  0xB,  0xC,  0xC,  0xD,  0xE,  0xE,  0xF,  0x10,
	0x10, 0x11, 0x11, 0x12, 0x13, 0x13, 0x14, 0x0,  0x1,  0x1,  0x2,  0x3,  0x3,  0x4,  0x5,  0x5,  0x6,  0x7,  0x7,
	0x8,  0x9,  0xA,  0xA,  0xB,  0xC,  0xC,  0xD,  0xE,  0xE,  0xF,  0x10, 0x10, 0x11, 0x12, 0x12, 0x13, 0x14, 0x14,
	0x15, 0x0,  0x1,  0x1,  0x2,  0x3,  0x4,  0x4,  0x5,  0x6,  0x6,  0x7,  0x8,  0x9,  0x9,  0xA,  0xB,  0xB,  0xC,
	0xD,  0xE,  0xE,  0xF,  0x10, 0x10, 0x11, 0x12, 0x12, 0x13, 0x14, 0x15, 0x15, 0x16, 0x0,  0x1,  0x2,  0x2,  0x3,
	0x4,  0x4,  0x5,  0x6,  0x7,  0x7,  0x8,  0x9,  0xA,  0xA,  0xB,  0xC,  0xD,  0xD,  0xE,  0xF,  0x10, 0x10, 0x11,
	0x12, 0x13, 0x13, 0x14, 0x15, 0x16, 0x16, 0x17, 0x0,  0x1,  0x2,  0x2,  0x3,  0x4,  0x5,  0x5,  0x6,  0x7,  0x8,
	0x9,  0x9,  0xA,  0xB,  0xC,  0xC,  0xD,  0xE,  0xF,  0x10, 0x10, 0x11, 0x12, 0x13, 0x13, 0x14, 0x15, 0x16, 0x16,
	0x17, 0x18, 0x0,  0x1,  0x2,  0x2,  0x3,  0x4,  0x5,  0x6,  0x6,  0x7,  0x8,  0x9,  0xA,  0xB,  0xB,  0xC,  0xD,
	0xE,  0xF,  0xF,  0x10, 0x11, 0x12, 0x13, 0x13, 0x14, 0x15, 0x16, 0x17, 0x17, 0x18, 0x19, 0x0,  0x1,  0x2,  0x3,
	0x3,  0x4,  0x5,  0x6,  0x7,  0x8,  0x8,  0x9,  0xA,  0xB,  0xC,  0xD,  0xD,  0xE,  0xF,  0x10, 0x11, 0x12, 0x12,
	0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x18, 0x19, 0x1A, 0x0,  0x1,  0x2,  0x3,  0x4,  0x4,  0x5,  0x6,  0x7,  0x8,
	0x9,  0xA,  0xA,  0xB,  0xC,  0xD,  0xE,  0xF,  0x10, 0x11, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x18,
	0x19, 0x1A, 0x1B, 0x0,  0x1,  0x2,  0x3,  0x4,  0x5,  0x5,  0x6,  0x7,  0x8,  0x9,  0xA,  0xB,  0xC,  0xD,  0xE,
	0xE,  0xF,  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x0,  0x1,  0x2,
	0x3,  0x4,  0x5,  0x6,  0x7,  0x8,  0x8,  0x9,  0xA,  0xB,  0xC,  0xD,  0xE,  0xF,  0x10, 0x11, 0x12, 0x13, 0x14,
	0x15, 0x16, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x0,  0x1,  0x2,  0x3,  0x4,  0x5,  0x6,  0x7,  0x8,
	0x9,  0xA,  0xB,  0xC,  0xD,  0xE,  0xF,  0x10, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A,
	0x1B, 0x1C, 0x1D, 0x1E, 0x0,  0x1,  0x2,  0x3,  0x4,  0x5,  0x6,  0x7,  0x8,  0x9,  0xA,  0xB,  0xC,  0xD,  0xE,
	0xF,  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0xE0, 0xE,
	0xB7, 0xD7, 0x40, 0x43, 0xCF, 0x11, 0xB0, 0x63, 0x0,  0x20, 0xAF, 0xC2, 0xCD, 0x35, 0xA0, 0x17, 0x38, 0x59, 0xB3,
	0x7D, 0xCF, 0x11, 0xA2, 0xDE, 0x0,  0xAA, 0x0,  0xB9, 0x33, 0x56, 0x80, 0xDB, 0x14, 0x6C, 0x33, 0xA7, 0xCE, 0x11,
	0xA5, 0x21, 0x0,  0x20, 0xAF, 0xB,  0xE5, 0x60, 0xE0, 0xF3, 0xA6, 0xB3, 0x43, 0x2B, 0xCF, 0x11, 0xA2, 0xDE, 0x0,
	0xAA, 0x0,  0xB9, 0x33, 0x56
};

inline void SelectMipmapRasterizers(GolSoftwareRenderer* p_renderer)
{
	if (p_renderer->GetCurrentMipmap()->m_paletteData) {
		if (p_renderer->GetRasterizerFlags() & 0x200) {
			p_renderer->SetTriangleRasterizer(FUN_1003e590);
			p_renderer->SetSpanRasterizer(FUN_10033890);
			p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
		}
		else {
			p_renderer->SetTriangleRasterizer(FUN_1003c780);
			p_renderer->SetSpanRasterizer(FUN_10033890);
			p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
		}
	}
	else {
		if (p_renderer->GetRasterizerFlags() & 0x200) {
			p_renderer->SetTriangleRasterizer(FUN_1003ee90);
			p_renderer->SetSpanRasterizer(FUN_100336d0);
			p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
		}
		else {
			p_renderer->SetTriangleRasterizer(FUN_1003cf40);
			p_renderer->SetSpanRasterizer(FUN_100336d0);
			p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
		}
	}
}

// FUNCTION: GOLDP 0x10032c80
void FUN_10032c80(GolSoftwareRenderer* p_renderer)
{
	LegoU32 sizeLog2;

	p_renderer->SetRasterizerFlags(p_renderer->GetRasterizerFlags() & ~0x80000000);
	if (p_renderer->GetPixelFormat()) {
		if (p_renderer->GetPixelFormat() != 1) {
			p_renderer->SetCurrentTriangleRasterizer(NoopTriangleRasterizer);
			p_renderer->SetTriangleRasterizer(NoopTriangleRasterizer);
			// The original stores the rasterizer twice.
			p_renderer->SetCurrentTriangleRasterizer(NoopTriangleRasterizer);
			return;
		}
		if ((p_renderer->GetCurrentMipmap() == NULL) || ((p_renderer->GetRasterizerFlags() & 0x100) == 0)) {
			if (p_renderer->GetRasterizerFlags() & 1) {
				p_renderer->SetTriangleRasterizer(FUN_10040670);
				p_renderer->SetSpanRasterizer(FUN_100334d0);
				p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
			}
			else {
				p_renderer->SetTriangleRasterizer(FUN_1003f790);
				p_renderer->SetSpanRasterizer(FUN_100332a0);
				p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
			}
		}
		else if (sizeLog2 = p_renderer->GetCurrentMipmap()->m_sizeLog2, sizeLog2 != 0) {
			if (p_renderer->GetCurrentMipmap()->m_paletteData) {
				if (p_renderer->GetRasterizerFlags() & 4) {
					if (p_renderer->GetRasterizerFlags() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003d700);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003ba30);
					}
					if (p_renderer->GetRasterizerFlags() & 2) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[80 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[68 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
				else if (p_renderer->GetRasterizerFlags() & 8) {
					if (p_renderer->GetRasterizerFlags() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003d700);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003ba30);
					}
					if (g_cpuSupportsMMX != 0) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[44 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[32 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
				else {
					if (p_renderer->GetRasterizerFlags() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003e590);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003c780);
					}
					if (p_renderer->GetRasterizerFlags() & 2) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[24 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
						STUB(0x01); // FIXME: to prevent mismatching code folding
					}
					else {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[20 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
						STUB(0x02); // FIXME: to prevent mismatching code folding
					}
				}
			}
			else {
				if (p_renderer->GetRasterizerFlags() & 0x200) {
					p_renderer->SetTriangleRasterizer(FUN_1003e590);
				}
				else {
					p_renderer->SetTriangleRasterizer(FUN_1003c780);
				}

				if ((p_renderer->GetRasterizerFlags() & 4) && (p_renderer->GetCurrentMipmap()->m_bytesPerPixel == 4)) {
					p_renderer->SetSpanRasterizer(g_spanRasterizers[56 - sizeLog2]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
				}
				else if (p_renderer->GetRasterizerFlags() & 2) {
					p_renderer->SetSpanRasterizer(g_spanRasterizers[14 - sizeLog2]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					STUB(0x03); // FIXME: to prevent mismatching code folding
				}
				else {
					// LINE: GOLDP 0x10032e37
					p_renderer->SetSpanRasterizer(g_spanRasterizers[8 - sizeLog2]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					STUB(0x04); // FIXME: to prevent mismatching code folding
				}
			}
		}
		else {
			SelectMipmapRasterizers(p_renderer);
		}
	}
	else {
		if ((p_renderer->GetCurrentMipmap() == NULL) || ((p_renderer->GetRasterizerFlags() & 0x100) == 0)) {
			if (p_renderer->GetRasterizerFlags() & 1) {
				p_renderer->SetTriangleRasterizer(FUN_1003fce0);
				p_renderer->SetSpanRasterizer(FUN_100332d0);
				p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
			}
			else {
				p_renderer->SetTriangleRasterizer(FUN_1003f790);
				p_renderer->SetSpanRasterizer(FUN_10033270);
				p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
			}
		}
		else if (sizeLog2 = p_renderer->GetCurrentMipmap()->m_sizeLog2, sizeLog2 != 0) {
			if (p_renderer->GetCurrentMipmap()->m_paletteData) {
				if (p_renderer->GetRasterizerFlags() & 4) {
					if (p_renderer->GetRasterizerFlags() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003d700);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003ba30);
					}
					if (p_renderer->GetRasterizerFlags() & 2) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[84 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						// LINE: GOLDP 0x10032f55
						p_renderer->SetSpanRasterizer(g_spanRasterizers[74 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
				else if (p_renderer->GetRasterizerFlags() & 8) {
					if (p_renderer->GetRasterizerFlags() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003d700);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003ba30);
					}
					if (g_cpuSupportsMMX) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[50 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						// LINE: GOLDP 0x10032fad
						p_renderer->SetSpanRasterizer(g_spanRasterizers[38 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
				else {
					if (p_renderer->GetRasterizerFlags() & 0x200) {
						p_renderer->SetTriangleRasterizer(FUN_1003e590);
					}
					else {
						p_renderer->SetTriangleRasterizer(FUN_1003c780);
					}
					if (p_renderer->GetRasterizerFlags() & 2) {
						p_renderer->SetSpanRasterizer(g_spanRasterizers[26 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
					else {
						// LINE: GOLDP 0x10032ffb
						p_renderer->SetSpanRasterizer(g_spanRasterizers[20 - sizeLog2]);
						p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
					}
				}
			}
			else {
				if (p_renderer->GetRasterizerFlags() & 0x200) {
					p_renderer->SetTriangleRasterizer(FUN_1003e590);
				}
				else {
					p_renderer->SetTriangleRasterizer(FUN_1003c780);
				}
				if ((p_renderer->GetRasterizerFlags() & 4) && (p_renderer->GetCurrentMipmap()->m_bytesPerPixel == 4)) {
					// LINE: GOLDP 0x10033030
					p_renderer->SetSpanRasterizer(g_spanRasterizers[62 - sizeLog2]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
				}
				// LINE: GOLDP 0x10033048
				else if (p_renderer->GetRasterizerFlags() & 2) {
					p_renderer->SetSpanRasterizer(g_spanRasterizers[14 - sizeLog2]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
				}
				else {
					// LINE: GOLDP 0x1003306c
					p_renderer->SetSpanRasterizer(g_spanRasterizers[8 - sizeLog2]);
					p_renderer->SetCurrentTriangleRasterizer(p_renderer->GetTriangleRasterizer());
				}
			}
		}
		else {
			SelectMipmapRasterizers(p_renderer);
		}
	}
}

// FUNCTION: GOLDP 0x100330d0
void FUN_100330d0(GolSoftwareRenderer* p_renderer, MipmapLevel* p_mipmap)
{
	LegoU32 previousSizeLog2;

	if (p_renderer->GetCurrentMipmap() == p_mipmap) {
		return;
	}
	// LINE: GOLDP 0x100330e3
	previousSizeLog2 = p_renderer->GetCurrentMipmap() ? p_renderer->GetCurrentMipmap()->m_sizeLog2 : -1;

	p_renderer->SetCurrentMipmap(p_mipmap);

	if (!p_mipmap) {
#pragma inline_depth(0)
		FUN_10032c80(p_renderer);
#pragma inline_depth()
		return;
	}

	if (p_mipmap) {
		// LINE: GOLDP 0x100330f7
		if (p_mipmap->m_width == p_mipmap->m_height) {
			switch (p_mipmap->m_width) {
			case 0x08:
				p_mipmap->m_sizeLog2 = MipmapLevel::c_size8;
				break;
			case 0x10:
				p_mipmap->m_sizeLog2 = MipmapLevel::c_size16;
				break;
			case 0x20:
				p_mipmap->m_sizeLog2 = MipmapLevel::c_size32;
				break;
			case 0x40:
				p_mipmap->m_sizeLog2 = MipmapLevel::c_size64;
				break;
			case 0x80:
				p_mipmap->m_sizeLog2 = MipmapLevel::c_size128;
				break;
			case 0x100:
				p_mipmap->m_sizeLog2 = MipmapLevel::c_size256;
				break;
			default:
				p_mipmap->m_sizeLog2 = MipmapLevel::c_sizeGeneric;
			}
		}
	}

	if (previousSizeLog2 != p_mipmap->m_sizeLog2) {
#pragma inline_depth(0)
		FUN_10032c80(p_renderer);
#pragma inline_depth()
	}
}

#ifdef COMPAT_MODE

void FUN_10033270()
{
	STUB(0x10033270);
}

void FUN_100332a0()
{
	STUB(0x100332a0);
}

void FUN_100332d0()
{
	STUB(0x100332d0);
}

void FUN_100334d0()
{
	STUB(0x100334d0);
}

void FUN_100336d0()
{
	STUB(0x100336d0);
}

void FUN_10033890()
{
	STUB(0x10033890);
}

void FUN_10033900()
{
	STUB(0x10033900);
}

void FUN_10033a20()
{
	STUB(0x10033a20);
}

void FUN_10033b40()
{
	STUB(0x10033b40);
}

void FUN_10033d90()
{
	STUB(0x10033d90);
}

void FUN_10033fe0()
{
	STUB(0x10033fe0);
}

void FUN_10034240()
{
	STUB(0x10034240);
}

void FUN_100344a0()
{
	STUB(0x100344a0);
}

void FUN_100345e0()
{
	STUB(0x100345e0);
}

void FUN_10034720()
{
	STUB(0x10034720);
}

void FUN_10034850()
{
	STUB(0x10034850);
}

void FUN_10034980()
{
	STUB(0x10034980);
}

void FUN_10034b10()
{
	STUB(0x10034b10);
}

void FUN_10034c40()
{
	STUB(0x10034c40);
}

void FUN_10034db0()
{
	STUB(0x10034db0);
}

void FUN_10034ea0()
{
	STUB(0x10034ea0);
}

void FUN_10034fc0()
{
	STUB(0x10034fc0);
}

void FUN_100350e0()
{
	STUB(0x100350e0);
}

void FUN_10035330()
{
	STUB(0x10035330);
}

void FUN_10035580()
{
	STUB(0x10035580);
}

void FUN_100357d0()
{
	STUB(0x100357d0);
}

void FUN_10035a20()
{
	STUB(0x10035a20);
}

void FUN_10035b60()
{
	STUB(0x10035b60);
}

void FUN_10035ca0()
{
	STUB(0x10035ca0);
}

void FUN_10035dd0()
{
	STUB(0x10035dd0);
}

void FUN_10035f00()
{
	STUB(0x10035f00);
}

void FUN_10036090()
{
	STUB(0x10036090);
}

void FUN_100361c0()
{
	STUB(0x100361c0);
}

void FUN_10036330()
{
	STUB(0x10036330);
}

void FUN_10036420()
{
	STUB(0x10036420);
}

void FUN_10036540()
{
	STUB(0x10036540);
}

void FUN_10036660()
{
	STUB(0x10036660);
}

void FUN_100368b0()
{
	STUB(0x100368b0);
}

void FUN_10036b00()
{
	STUB(0x10036b00);
}

void FUN_10036d50()
{
	STUB(0x10036d50);
}

void FUN_10036fa0()
{
	STUB(0x10036fa0);
}

void FUN_100370e0()
{
	STUB(0x100370e0);
}

void FUN_10037220()
{
	STUB(0x10037220);
}

void FUN_10037350()
{
	STUB(0x10037350);
}

void FUN_10037480()
{
	STUB(0x10037480);
}

void FUN_10037610()
{
	STUB(0x10037610);
}

void FUN_10037740()
{
	STUB(0x10037740);
}

void FUN_100378b0()
{
	STUB(0x100378b0);
}

void FUN_100379a0()
{
	STUB(0x100379a0);
}

void FUN_10037ac0()
{
	STUB(0x10037ac0);
}

void FUN_10037be0()
{
	STUB(0x10037be0);
}

void FUN_10037e30()
{
	STUB(0x10037e30);
}

void FUN_10038080()
{
	STUB(0x10038080);
}

void FUN_100382d0()
{
	STUB(0x100382d0);
}

void FUN_10038520()
{
	STUB(0x10038520);
}

void FUN_10038660()
{
	STUB(0x10038660);
}

void FUN_100387a0()
{
	STUB(0x100387a0);
}

void FUN_100388d0()
{
	STUB(0x100388d0);
}

void FUN_10038a00()
{
	STUB(0x10038a00);
}

void FUN_10038b90()
{
	STUB(0x10038b90);
}

void FUN_10038cc0()
{
	STUB(0x10038cc0);
}

void FUN_10038e30()
{
	STUB(0x10038e30);
}

void FUN_10038f20()
{
	STUB(0x10038f20);
}

void FUN_10039040()
{
	STUB(0x10039040);
}

void FUN_10039160()
{
	STUB(0x10039160);
}

void FUN_100393b0()
{
	STUB(0x100393b0);
}

void FUN_10039600()
{
	STUB(0x10039600);
}

void FUN_10039850()
{
	STUB(0x10039850);
}

void FUN_10039aa0()
{
	STUB(0x10039aa0);
}

void FUN_10039be0()
{
	STUB(0x10039be0);
}

void FUN_10039d20()
{
	STUB(0x10039d20);
}

void FUN_10039e50()
{
	STUB(0x10039e50);
}

void FUN_10039f80()
{
	STUB(0x10039f80);
}

void FUN_1003a110()
{
	STUB(0x1003a110);
}

void FUN_1003a240()
{
	STUB(0x1003a240);
}

void FUN_1003a3b0()
{
	STUB(0x1003a3b0);
}

void FUN_1003a4a0()
{
	STUB(0x1003a4a0);
}

void FUN_1003a5c0()
{
	STUB(0x1003a5c0);
}

void FUN_1003a6e0()
{
	STUB(0x1003a6e0);
}

void FUN_1003a930()
{
	STUB(0x1003a930);
}

void FUN_1003ab80()
{
	STUB(0x1003ab80);
}

void FUN_1003add0()
{
	STUB(0x1003add0);
}

void FUN_1003b020()
{
	STUB(0x1003b020);
}

void FUN_1003b160()
{
	STUB(0x1003b160);
}

void FUN_1003b2a0()
{
	STUB(0x1003b2a0);
}

void FUN_1003b3d0()
{
	STUB(0x1003b3d0);
}

void FUN_1003b500()
{
	STUB(0x1003b500);
}

void FUN_1003b690()
{
	STUB(0x1003b690);
}

void FUN_1003b7c0()
{
	STUB(0x1003b7c0);
}

void FUN_1003b930()
{
	STUB(0x1003b930);
	// no implementation for modern compilers yet
}

void FUN_1003ba30(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003ba30);
}

void FUN_1003c780(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003c780);
}

void FUN_1003cf40(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003cf40);
}

void FUN_1003d700(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003d700);
}

void FUN_1003e590(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003e590);
}

void FUN_1003ee90(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003ee90);
}

void FUN_1003f790(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003f790);
}

void FUN_1003fce0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1003fce0);
}

void FUN_10040670(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10040670);
}

#else

// FUNCTION: GOLDP 0x10033270
__declspec(naked) void FUN_10033270()
{
	__asm {
		lea edi, [ebx + edx*2]
		and edx, 1
		mov eax, dword ptr [esp + 0x168]
		je jmp_10033288
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		js jmp_1003329b
jmp_10033288:
		dec ecx
		js jmp_10033298
jmp_1003328b:
		mov dword ptr [edi], eax
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_1003328b
		inc ecx
		jne jmp_1003329b
jmp_10033298:
		mov word ptr [edi], ax
jmp_1003329b:
		ret
	}
}

// FUNCTION: GOLDP 0x100332a0
__declspec(naked) void FUN_100332a0()
{
	__asm {
		lea edi, [ebx + edx*2]
		and edx, 1
		mov eax, dword ptr [esp + 0x164]
		je jmp_100332b8
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		js jmp_100332cb
jmp_100332b8:
		dec ecx
		js jmp_100332c8
jmp_100332bb:
		mov dword ptr [edi], eax
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_100332bb
		inc ecx
		jne jmp_100332cb
jmp_100332c8:
		mov word ptr [edi], ax
jmp_100332cb:
		ret
	}
}

// FUNCTION: GOLDP 0x100332d0
__declspec(naked) void FUN_100332d0()
{
	__asm {
		mov eax, dword ptr [esp + 0x158]
		mov ebp, dword ptr [esp + 0x80]
		shl eax, 0x10
		lea edi, [ebx + edx*2]
		shl ebp, 7
		mov edx, dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 0x7c]
		mov esi, dword ptr [esp + 0x78]
		shl ebx, 2
		xor edx, eax
		sar esi, 3
		and edx, 0x10000
		mov eax, edi
		je jmp_100333e9
		and eax, 2
		je jmp_1003335c
		add ebx, 0x100000
		add ebp, 0x2000000
		add esi, 0x8000
		mov edx, ebp
		mov eax, ebx
		and edx, 0x7c000000
		and eax, 0x3e00000
		or edx, eax
		mov eax, dword ptr [esp + 0x16c]
		or edx, esi
		add ebp, eax
		shr edx, 0x10
		mov eax, dword ptr [esp + 0x168]
		add esi, dword ptr [esp + 0x164]
		add ebx, eax
		mov word ptr [edi], dx
		dec ecx
		lea edi, [edi + 2]
		js jmp_100333e8
jmp_1003335c:
		dec ecx
		js jmp_100333cf
jmp_1003335f:
		mov edx, ebp
		mov eax, ebx
		and edx, 0x7c000000
		and eax, 0x3e00000
		or edx, eax
		mov eax, dword ptr [esp + 0x178]
		or edx, esi
		add eax, ebp
		mov ebp, eax
		and eax, 0x7c000000
		shr edx, 0x10
		add ebx, dword ptr [esp + 0x174]
		or edx, eax
		mov eax, ebx
		and eax, 0x3e00000
		add esi, dword ptr [esp + 0x170]
		or edx, eax
		mov eax, esi
		and eax, 0x1f0000
		or edx, eax
		mov eax, dword ptr [esp + 0x164]
		mov dword ptr [edi], edx
		add esi, eax
		mov eax, dword ptr [esp + 0x168]
		mov edx, dword ptr [esp + 0x16c]
		add ebx, eax
		add ebp, edx
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_1003335f
		inc ecx
		jne jmp_100333e8
jmp_100333cf:
		mov edx, ebp
		mov eax, ebx
		and edx, 0x7c000000
		and eax, 0x3e00000
		or edx, eax
		or edx, esi
		shr edx, 0x10
		mov word ptr [edi], dx
jmp_100333e8:
		ret
jmp_100333e9:
		and eax, 2
		je jmp_1003342c
		mov edx, ebp
		mov eax, ebx
		and edx, 0x7c000000
		and eax, 0x3e00000
		or edx, eax
		mov eax, dword ptr [esp + 0x178]
		or edx, esi
		add ebp, eax
		shr edx, 0x10
		mov eax, dword ptr [esp + 0x174]
		add esi, dword ptr [esp + 0x170]
		add ebx, eax
		mov word ptr [edi], dx
		dec ecx
		lea edi, [edi + 2]
		js jmp_100334ca
		jmp jmp_1003343e
jmp_1003342c:
		add ebx, 0x100000
		add ebp, 0x2000000
		add esi, 0x8000
jmp_1003343e:
		dec ecx
		js jmp_100334b1
jmp_10033441:
		mov edx, ebp
		mov eax, ebx
		and edx, 0x7c000000
		and eax, 0x3e00000
		or edx, eax
		mov eax, dword ptr [esp + 0x16c]
		or edx, esi
		add eax, ebp
		mov ebp, eax
		and eax, 0x7c000000
		shr edx, 0x10
		add ebx, dword ptr [esp + 0x168]
		or edx, eax
		mov eax, ebx
		and eax, 0x3e00000
		add esi, dword ptr [esp + 0x164]
		or edx, eax
		mov eax, esi
		and eax, 0x1f0000
		or edx, eax
		mov eax, dword ptr [esp + 0x170]
		mov dword ptr [edi], edx
		add esi, eax
		mov eax, dword ptr [esp + 0x174]
		mov edx, dword ptr [esp + 0x178]
		add ebx, eax
		add ebp, edx
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_10033441
		inc ecx
		jne jmp_100334ca
jmp_100334b1:
		mov edx, ebp
		mov eax, ebx
		and edx, 0x7c000000
		and eax, 0x3e00000
		or edx, eax
		or edx, esi
		shr edx, 0x10
		mov word ptr [edi], dx
jmp_100334ca:
		ret
	}
}

// FUNCTION: GOLDP 0x100334d0
__declspec(naked) void FUN_100334d0()
{
	__asm {
		mov eax, dword ptr [esp + 0x158]
		mov ebp, dword ptr [esp + 0x80]
		shl eax, 0x10
		lea edi, [ebx + edx*2]
		shl ebp, 8
		mov edx, dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 0x7c]
		mov esi, dword ptr [esp + 0x78]
		shl ebx, 3
		xor edx, eax
		sar esi, 3
		and edx, 0x10000
		mov eax, edi
		je jmp_100335e9
		and eax, 2
		je jmp_1003355c
		add ebx, 0x100000
		add ebp, 0x4000000
		add esi, 0x8000
		mov edx, ebp
		mov eax, ebx
		and edx, 0xf8000000
		and eax, 0x7e00000
		or edx, eax
		mov eax, dword ptr [esp + 0x16c]
		or edx, esi
		add ebp, eax
		shr edx, 0x10
		mov eax, dword ptr [esp + 0x168]
		add esi, dword ptr [esp + 0x164]
		add ebx, eax
		mov word ptr [edi], dx
		dec ecx
		lea edi, [edi + 2]
		js jmp_100335e8
jmp_1003355c:
		dec ecx
		js jmp_100335cf
jmp_1003355f:
		mov edx, ebp
		mov eax, ebx
		and edx, 0xf8000000
		and eax, 0x7e00000
		or edx, eax
		mov eax, dword ptr [esp + 0x178]
		or edx, esi
		add eax, ebp
		mov ebp, eax
		and eax, 0xf8000000
		shr edx, 0x10
		add ebx, dword ptr [esp + 0x174]
		or edx, eax
		mov eax, ebx
		and eax, 0x7e00000
		add esi, dword ptr [esp + 0x170]
		or edx, eax
		mov eax, esi
		and eax, 0x1f0000
		or edx, eax
		mov eax, dword ptr [esp + 0x164]
		mov dword ptr [edi], edx
		add esi, eax
		mov eax, dword ptr [esp + 0x168]
		mov edx, dword ptr [esp + 0x16c]
		add ebx, eax
		add ebp, edx
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_1003355f
		inc ecx
		jne jmp_100335e8
jmp_100335cf:
		mov edx, ebp
		mov eax, ebx
		and edx, 0xf8000000
		and eax, 0x7e00000
		or edx, eax
		or edx, esi
		shr edx, 0x10
		mov word ptr [edi], dx
jmp_100335e8:
		ret
jmp_100335e9:
		and eax, 2
		je jmp_1003362c
		mov edx, ebp
		mov eax, ebx
		and edx, 0xf8000000
		and eax, 0x7e00000
		or edx, eax
		mov eax, dword ptr [esp + 0x178]
		or edx, esi
		add ebp, eax
		shr edx, 0x10
		mov eax, dword ptr [esp + 0x174]
		add esi, dword ptr [esp + 0x170]
		add ebx, eax
		mov word ptr [edi], dx
		dec ecx
		lea edi, [edi + 2]
		js jmp_100336ca
		jmp jmp_1003363e
jmp_1003362c:
		add ebx, 0x100000
		add ebp, 0x4000000
		add esi, 0x8000
jmp_1003363e:
		dec ecx
		js jmp_100336b1
jmp_10033641:
		mov edx, ebp
		mov eax, ebx
		and edx, 0xf8000000
		and eax, 0x7e00000
		or edx, eax
		mov eax, dword ptr [esp + 0x16c]
		or edx, esi
		add eax, ebp
		mov ebp, eax
		and eax, 0xf8000000
		shr edx, 0x10
		add ebx, dword ptr [esp + 0x168]
		or edx, eax
		mov eax, ebx
		and eax, 0x7e00000
		add esi, dword ptr [esp + 0x164]
		or edx, eax
		mov eax, esi
		and eax, 0x1f0000
		or edx, eax
		mov eax, dword ptr [esp + 0x170]
		mov dword ptr [edi], edx
		add esi, eax
		mov eax, dword ptr [esp + 0x174]
		mov edx, dword ptr [esp + 0x178]
		add ebx, eax
		add ebp, edx
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_10033641
		inc ecx
		jne jmp_100336ca
jmp_100336b1:
		mov edx, ebp
		mov eax, ebx
		and edx, 0xf8000000
		and eax, 0x7e00000
		or edx, eax
		or edx, esi
		shr edx, 0x10
		mov word ptr [edi], dx
jmp_100336ca:
		ret
	}
}

// FUNCTION: GOLDP 0x100336d0
__declspec(naked) void FUN_100336d0()
{
	__asm {
		mov eax, dword ptr [esp + 0x74]
		lea edi, [ebx + edx*2]
		mov ebx, eax
		mov esi, dword ptr [esp + 0x11c]
		sar eax, 0x10
		mov ebp, dword ptr [esp + 0x70]
		shl ebx, 0x10
		imul dword ptr [esp + 0x120]
		mov edx, ebp
		add esi, eax
		sar ebp, 0x10
		mov eax, edi
		shl edx, 0x10
		add esi, ebp
		and eax, 2
		mov ebp, dword ptr [esp + 0x108]
		je jmp_10033746
		mov ax, word ptr [esi*2]
		add ebx, ebp
		mov word ptr [edi], ax
		lea edi, [edi + 2]
		sbb ebp, ebp
		mov eax, dword ptr [esp + 0x100]
		add edx, eax
		mov eax, dword ptr [esp + 0xfc]
		adc esi, eax
		mov eax, dword ptr [esp + ebp*4 + 0x110]
		add esi, eax
		dec ecx
		mov ebp, dword ptr [esp + 0x108]
		js jmp_10033888
jmp_10033746:
		dec ecx
		js jmp_1003387d
jmp_1003374d:
		mov ax, word ptr [esi*2]
		add ebx, ebp
		mov ebp, dword ptr [esp + 0x100]
		jb jmp_100337f1
		add edx, ebp
		mov ebp, dword ptr [esp + 0xfc]
		adc esi, ebp
		mov ebp, dword ptr [esp + 0x108]
		shl eax, 0x10
		add esi, dword ptr [esp + 0x110]
		add ebx, ebp
		mov ebp, dword ptr [esp + 0x100]
		mov ax, word ptr [esi*2]
		jb jmp_100337c0
		add edx, ebp
		mov ebp, dword ptr [esp + 0xfc]
		adc esi, ebp
		mov ebp, dword ptr [esp + 0x110]
		rol eax, 0x10
		add esi, ebp
		mov dword ptr [edi], eax
		mov ebp, dword ptr [esp + 0x108]
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_1003374d
		jmp jmp_1003387a
jmp_100337c0:
		add edx, ebp
		mov ebp, dword ptr [esp + 0xfc]
		adc esi, ebp
		mov ebp, dword ptr [esp + 0x10c]
		rol eax, 0x10
		add esi, ebp
		mov dword ptr [edi], eax
		mov ebp, dword ptr [esp + 0x108]
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_1003374d
		jmp jmp_1003387a
jmp_100337f1:
		add edx, ebp
		mov ebp, dword ptr [esp + 0xfc]
		adc esi, ebp
		mov ebp, dword ptr [esp + 0x108]
		shl eax, 0x10
		add esi, dword ptr [esp + 0x10c]
		add ebx, ebp
		mov ebp, dword ptr [esp + 0x100]
		mov ax, word ptr [esi*2]
		jb jmp_1003384e
		add edx, ebp
		mov ebp, dword ptr [esp + 0xfc]
		adc esi, ebp
		mov ebp, dword ptr [esp + 0x110]
		rol eax, 0x10
		add esi, ebp
		mov dword ptr [edi], eax
		mov ebp, dword ptr [esp + 0x108]
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_1003374d
		jmp jmp_1003387a
jmp_1003384e:
		add edx, ebp
		mov ebp, dword ptr [esp + 0xfc]
		adc esi, ebp
		mov ebp, dword ptr [esp + 0x10c]
		rol eax, 0x10
		add esi, ebp
		mov dword ptr [edi], eax
		mov ebp, dword ptr [esp + 0x108]
		sub ecx, 2
		lea edi, [edi + 4]
		jns jmp_1003374d
jmp_1003387a:
		inc ecx
		jne jmp_10033888
jmp_1003387d:
		mov ax, word ptr [esi*2]
		mov word ptr [edi], ax
jmp_10033888:
		ret
	}
}

// FUNCTION: GOLDP 0x10033890
__declspec(naked) void FUN_10033890()
{
	__asm {
		mov eax, dword ptr [esp + 0x74]
		lea edi, [ebx + edx*2]
		mov ebx, eax
		mov esi, dword ptr [esp + 0x11c]
		sar eax, 0x10
		mov ebp, dword ptr [esp + 0x70]
		shl ebx, 0x10
		imul dword ptr [esp + 0x120]
		mov edx, ebp
		add esi, eax
		sar ebp, 0x10
		xor eax, eax
		shl edx, 0x10
		add esi, ebp
jmp_100338bf:
		mov ebp, dword ptr [esp + 0x124]
		mov al, byte ptr [esi]
		add ebx, dword ptr [esp + 0x108]
		mov ax, word ptr [ebp + eax*2]
		mov word ptr [edi], ax
		mov eax, dword ptr [esp + 0x100]
		sbb ebp, ebp
		add edx, eax
		mov eax, dword ptr [esp + 0xfc]
		lea edi, [edi + 2]
		adc esi, eax
		mov eax, dword ptr [esp + ebp*4 + 0x110]
		add esi, eax
		xor eax, eax
		dec ecx
		jns jmp_100338bf
		ret
	}
}

// FUNCTION: GOLDP 0x10033900
__declspec(naked) void FUN_10033900()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_1003392c:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 6
		and eax, 0x3fc
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10033a03 + 1]
jmp_10033985:
		mov word ptr [edi], ax
		jmp jmp_100339f8
jmp_1003398a:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100339f8
jmp_100339b7:
		mov bx, word ptr [edi]
		and eax, 0x7bde
		and ebx, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_100339f8
jmp_100339ce:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov bx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100339f8:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003392c
		ret
jmp_10033a03:
		mov eax, OFFSET jmp_100339f8
		mov eax, OFFSET jmp_100339ce
		mov eax, OFFSET jmp_100339b7
		mov eax, OFFSET jmp_1003398a
		mov eax, OFFSET jmp_10033985
	}
}

// FUNCTION: GOLDP 0x10033a20
__declspec(naked) void FUN_10033a20()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_10033a4c:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 6
		and eax, 0x3fc
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10033b23 + 1]
jmp_10033aa5:
		mov word ptr [edi], ax
		jmp jmp_10033b18
jmp_10033aaa:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10033b18
jmp_10033ad7:
		mov bx, word ptr [edi]
		and eax, 0xf7de
		and ebx, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_10033b18
jmp_10033aee:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov bx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10033b18:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10033a4c
		ret
jmp_10033b23:
		mov eax, OFFSET jmp_10033b18
		mov eax, OFFSET jmp_10033aee
		mov eax, OFFSET jmp_10033ad7
		mov eax, OFFSET jmp_10033aaa
		mov eax, OFFSET jmp_10033aa5
	}
}

// FUNCTION: GOLDP 0x10033b40
__declspec(naked) void FUN_10033b40()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10033c55
jmp_10033b74:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10033d37 + 1]
jmp_10033bc7:
		mov word ptr [edi], bx
		jmp jmp_10033c42
jmp_10033bcc:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10033c42
jmp_10033bf9:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10033c49
jmp_10033c17:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10033c42:
		mov eax, dword ptr [esp + 0xdc]
jmp_10033c49:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10033d36
jmp_10033c55:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10033d5f + 1]
jmp_10033ca8:
		mov word ptr [edi], bx
		jmp jmp_10033d23
jmp_10033cad:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10033d23
jmp_10033cda:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10033d2a
jmp_10033cf8:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10033d23:
		mov eax, dword ptr [esp + 0xdc]
jmp_10033d2a:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10033b74
jmp_10033d36:
		ret
jmp_10033d37:
		mov eax, OFFSET jmp_10033c42
		mov eax, OFFSET jmp_10033c17
		mov eax, OFFSET jmp_10033c17
		mov eax, OFFSET jmp_10033bf9
		mov eax, OFFSET jmp_10033bf9
		mov eax, OFFSET jmp_10033bcc
		mov eax, OFFSET jmp_10033bcc
		mov eax, OFFSET jmp_10033bc7
jmp_10033d5f:
		mov eax, OFFSET jmp_10033d23
		mov eax, OFFSET jmp_10033d23
		mov eax, OFFSET jmp_10033cf8
		mov eax, OFFSET jmp_10033cf8
		mov eax, OFFSET jmp_10033cda
		mov eax, OFFSET jmp_10033cad
		mov eax, OFFSET jmp_10033ca8
		mov eax, OFFSET jmp_10033ca8
	}
}

// FUNCTION: GOLDP 0x10033d90
__declspec(naked) void FUN_10033d90()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10033ea5
jmp_10033dc4:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10033f87 + 1]
jmp_10033e17:
		mov word ptr [edi], bx
		jmp jmp_10033e92
jmp_10033e1c:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10033e92
jmp_10033e49:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10033e99
jmp_10033e67:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10033e92:
		mov eax, dword ptr [esp + 0xdc]
jmp_10033e99:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10033f86
jmp_10033ea5:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10033faf + 1]
jmp_10033ef8:
		mov word ptr [edi], bx
		jmp jmp_10033f73
jmp_10033efd:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10033f73
jmp_10033f2a:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10033f7a
jmp_10033f48:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10033f73:
		mov eax, dword ptr [esp + 0xdc]
jmp_10033f7a:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10033dc4
jmp_10033f86:
		ret
jmp_10033f87:
		mov eax, OFFSET jmp_10033e92
		mov eax, OFFSET jmp_10033e67
		mov eax, OFFSET jmp_10033e67
		mov eax, OFFSET jmp_10033e49
		mov eax, OFFSET jmp_10033e49
		mov eax, OFFSET jmp_10033e1c
		mov eax, OFFSET jmp_10033e1c
		mov eax, OFFSET jmp_10033e17
jmp_10033faf:
		mov eax, OFFSET jmp_10033f73
		mov eax, OFFSET jmp_10033f73
		mov eax, OFFSET jmp_10033f48
		mov eax, OFFSET jmp_10033f48
		mov eax, OFFSET jmp_10033f2a
		mov eax, OFFSET jmp_10033efd
		mov eax, OFFSET jmp_10033ef8
		mov eax, OFFSET jmp_10033ef8
	}
}

// FUNCTION: GOLDP 0x10033fe0
__declspec(naked) void FUN_10033fe0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_100340fb
jmp_10034014:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_100340e8
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100341e3 + 1]
jmp_1003406d:
		mov word ptr [edi], bx
		jmp jmp_100340e8
jmp_10034072:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100340e8
jmp_1003409f:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100340ef
jmp_100340bd:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100340e8:
		mov eax, dword ptr [esp + 0xdc]
jmp_100340ef:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_100341e2
jmp_100340fb:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_100341cf
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003420b + 1]
jmp_10034154:
		mov word ptr [edi], bx
		jmp jmp_100341cf
jmp_10034159:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100341cf
jmp_10034186:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100341d6
jmp_100341a4:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100341cf:
		mov eax, dword ptr [esp + 0xdc]
jmp_100341d6:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10034014
jmp_100341e2:
		ret
jmp_100341e3:
		mov eax, OFFSET jmp_100340e8
		mov eax, OFFSET jmp_100340bd
		mov eax, OFFSET jmp_100340bd
		mov eax, OFFSET jmp_1003409f
		mov eax, OFFSET jmp_1003409f
		mov eax, OFFSET jmp_10034072
		mov eax, OFFSET jmp_10034072
		mov eax, OFFSET jmp_1003406d
jmp_1003420b:
		mov eax, OFFSET jmp_100341cf
		mov eax, OFFSET jmp_100341cf
		mov eax, OFFSET jmp_100341a4
		mov eax, OFFSET jmp_100341a4
		mov eax, OFFSET jmp_10034186
		mov eax, OFFSET jmp_10034159
		mov eax, OFFSET jmp_10034154
		mov eax, OFFSET jmp_10034154
	}
}

// FUNCTION: GOLDP 0x10034240
__declspec(naked) void FUN_10034240()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_1003435b
jmp_10034274:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10034348
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10034443 + 1]
jmp_100342cd:
		mov word ptr [edi], bx
		jmp jmp_10034348
jmp_100342d2:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10034348
jmp_100342ff:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003434f
jmp_1003431d:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10034348:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003434f:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10034442
jmp_1003435b:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_1003442f
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003446b + 1]
jmp_100343b4:
		mov word ptr [edi], bx
		jmp jmp_1003442f
jmp_100343b9:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003442f
jmp_100343e6:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10034436
jmp_10034404:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003442f:
		mov eax, dword ptr [esp + 0xdc]
jmp_10034436:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10034274
jmp_10034442:
		ret
jmp_10034443:
		mov eax, OFFSET jmp_10034348
		mov eax, OFFSET jmp_1003431d
		mov eax, OFFSET jmp_1003431d
		mov eax, OFFSET jmp_100342ff
		mov eax, OFFSET jmp_100342ff
		mov eax, OFFSET jmp_100342d2
		mov eax, OFFSET jmp_100342d2
		mov eax, OFFSET jmp_100342cd
jmp_1003446b:
		mov eax, OFFSET jmp_1003442f
		mov eax, OFFSET jmp_1003442f
		mov eax, OFFSET jmp_10034404
		mov eax, OFFSET jmp_10034404
		mov eax, OFFSET jmp_100343e6
		mov eax, OFFSET jmp_100343b9
		mov eax, OFFSET jmp_100343b4
		mov eax, OFFSET jmp_100343b4
	}
}

// FUNCTION: GOLDP 0x100344a0
__declspec(naked) void FUN_100344a0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_100344d6:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 5
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x3e0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xa
		mov ecx, dword ptr [esp + 0xd4]
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 5
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_100344d6
		ret
	}
}

// FUNCTION: GOLDP 0x100345e0
__declspec(naked) void FUN_100345e0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10034616:
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 6
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x7c0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xb
		mov ecx, dword ptr [esp + 0xd4]
		shr ebp, 1
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 6
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10034616
		ret
	}
}

// FUNCTION: GOLDP 0x10034720
__declspec(naked) void FUN_10034720()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x10057a00]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_100347b7:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xa
		movq mm3, mm4
		psllq mm4, 0x2b
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 8
		and eax, 0xff
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100347b7
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10034850
__declspec(naked) void FUN_10034850()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x100579f8]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_100348e7:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xb
		movq mm3, mm4
		psllq mm4, 0x2a
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 8
		and eax, 0xff
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100348e7
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10034980
__declspec(naked) void FUN_10034980()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0xff0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_100349ec
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		je jmp_100349d5
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi - 2], bx
jmp_100349d5:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0xff0000
		js jmp_10034b0b
jmp_100349ec:
		dec ecx
		js jmp_10034adc
jmp_100349f3:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov al, byte ptr [eax]
		add edx, ebx
		and eax, 0xff
		mov bl, byte ptr [esi]
		mov esi, dword ptr [esp + 0x124]
		je jmp_10034aaf
		and ebx, 0xff
		je jmp_10034a8b
		mov ax, word ptr [esi + eax*2]
		lea edi, [edi + 4]
		shl eax, 0x10
		sub ecx, 2
		mov ax, word ptr [esi + ebx*2]
		mov ebx, 0xff0000
		mov dword ptr [edi - 4], eax
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_100349f3
		jmp jmp_10034ad9
jmp_10034a8b:
		mov ax, word ptr [esi + eax*2]
		mov ebx, 0xff0000
		mov word ptr [edi + 2], ax
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_100349f3
		jmp jmp_10034ad9
jmp_10034aaf:
		and ebx, 0xff
		lea edi, [edi + 4]
		mov eax, ebp
		je jmp_10034ac4
		mov bx, word ptr [esi + ebx*2]
		mov word ptr [edi - 4], bx
jmp_10034ac4:
		sub ecx, 2
		mov ebx, 0xff0000
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_100349f3
jmp_10034ad9:
		inc ecx
		jne jmp_10034b0b
jmp_10034adc:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		je jmp_10034b0b
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_10034b0b:
		ret
	}
}

// FUNCTION: GOLDP 0x10034b10
__declspec(naked) void FUN_10034b10()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0xff0000
		je jmp_10034b7a
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov eax, dword ptr [esp + 0xcc]
		mov word ptr [edi - 2], bx
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0xff0000
		js jmp_10034c3a
jmp_10034b7a:
		dec ecx
		js jmp_10034c14
jmp_10034b81:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		add eax, esi
		mov esi, dword ptr [esp + 0xc8]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, esi
		add edx, ebx
		mov esi, ebp
		mov ebx, 0xff0000
		shr esi, 0x10
		and ebx, edx
		shr ebx, 8
		and esi, 0xff
		or ebx, esi
		mov esi, dword ptr [esp + 0x13c]
		add ebx, esi
		mov al, byte ptr [eax]
		and eax, 0xff
		mov esi, dword ptr [esp + 0xc8]
		mov bl, byte ptr [ebx]
		add ebp, esi
		and ebx, 0xff
		mov esi, dword ptr [esp + 0x124]
		add edx, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx*2]
		shl ebx, 0x10
		mov bx, word ptr [esi + eax*2]
		sub ecx, 2
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		mov ebx, 0xff0000
		jns jmp_10034b81
		inc ecx
		jne jmp_10034c3a
jmp_10034c14:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 8
		and eax, 0xff
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_10034c3a:
		ret
	}
}

// FUNCTION: GOLDP 0x10034c40
__declspec(naked) void FUN_10034c40()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0xff0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_10034ca2
		shr eax, 0xf
		and ebx, edx
		shr ebx, 7
		and eax, 0x1fe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		add edi, 2
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_10034c8b
		mov word ptr [edi - 2], bx
jmp_10034c8b:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0xff0000
		js jmp_10034da9
jmp_10034ca2:
		dec ecx
		js jmp_10034d7d
jmp_10034ca9:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 7
		and eax, 0x1fe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 7
		and eax, 0x1fe
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov ax, word ptr [eax]
		add edx, ebx
		and eax, 0xffff
		mov bx, word ptr [esi]
		je jmp_10034d55
		and ebx, 0xffff
		je jmp_10034d35
		shl eax, 0x10
		mov esi, dword ptr [esp + 0x13c]
		or eax, ebx
		mov ebx, 0xff0000
		mov dword ptr [edi], eax
		sub ecx, 2
		lea edi, [edi + 4]
		mov eax, ebp
		jns jmp_10034ca9
		jmp jmp_10034d7a
jmp_10034d35:
		mov word ptr [edi + 2], ax
		mov ebx, 0xff0000
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10034ca9
		jmp jmp_10034d7a
jmp_10034d55:
		and ebx, 0xffff
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		je jmp_10034d69
		mov word ptr [edi], bx
jmp_10034d69:
		sub ecx, 2
		lea edi, [edi + 4]
		mov ebx, 0xff0000
		jns jmp_10034ca9
jmp_10034d7a:
		inc ecx
		jne jmp_10034da9
jmp_10034d7d:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 7
		and eax, 0x1fe
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_10034da9
		mov word ptr [edi], bx
jmp_10034da9:
		ret
	}
}

// FUNCTION: GOLDP 0x10034db0
__declspec(naked) void FUN_10034db0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0xff0000
		je jmp_10034e09
		shr eax, 0xf
		and ebx, edx
		shr ebx, 7
		and eax, 0x1fe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx]
		add edx, eax
		mov word ptr [edi], bx
		add edi, 2
		dec ecx
		mov eax, ebp
		mov ebx, 0xff0000
		js jmp_10034e9a
jmp_10034e09:
		dec ecx
		js jmp_10034e84
jmp_10034e0c:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 7
		and eax, 0x1fe
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0xff0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 7
		and eax, 0x1fe
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [ebx]
		add edx, eax
		shl ebx, 0x10
		sub ecx, 2
		mov bx, word ptr [esi]
		mov eax, ebp
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, 0xff0000
		jns jmp_10034e0c
		inc ecx
		jne jmp_10034e9a
jmp_10034e84:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 7
		and eax, 0x1fe
		or ebx, eax
		mov bx, word ptr [esi + ebx]
		mov word ptr [edi], bx
jmp_10034e9a:
		ret
	}
}

// FUNCTION: GOLDP 0x10034ea0
__declspec(naked) void FUN_10034ea0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_10034ecc:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 7
		and eax, 0x1fc
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10034fa3 + 1]
jmp_10034f25:
		mov word ptr [edi], ax
		jmp jmp_10034f98
jmp_10034f2a:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10034f98
jmp_10034f57:
		mov bx, word ptr [edi]
		and eax, 0x7bde
		and ebx, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_10034f98
jmp_10034f6e:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov bx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10034f98:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10034ecc
		ret
jmp_10034fa3:
		mov eax, OFFSET jmp_10034f98
		mov eax, OFFSET jmp_10034f6e
		mov eax, OFFSET jmp_10034f57
		mov eax, OFFSET jmp_10034f2a
		mov eax, OFFSET jmp_10034f25
	}
}

// FUNCTION: GOLDP 0x10034fc0
__declspec(naked) void FUN_10034fc0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_10034fec:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 7
		and eax, 0x1fc
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_100350c3 + 1]
jmp_10035045:
		mov word ptr [edi], ax
		jmp jmp_100350b8
jmp_1003504a:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100350b8
jmp_10035077:
		mov bx, word ptr [edi]
		and eax, 0xf7de
		and ebx, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_100350b8
jmp_1003508e:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov bx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100350b8:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10034fec
		ret
jmp_100350c3:
		mov eax, OFFSET jmp_100350b8
		mov eax, OFFSET jmp_1003508e
		mov eax, OFFSET jmp_10035077
		mov eax, OFFSET jmp_1003504a
		mov eax, OFFSET jmp_10035045
	}
}

// FUNCTION: GOLDP 0x100350e0
__declspec(naked) void FUN_100350e0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_100351f3
jmp_10035114:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100352d3 + 1]
jmp_10035165:
		mov word ptr [edi], bx
		jmp jmp_100351e0
jmp_1003516a:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100351e0
jmp_10035197:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100351e7
jmp_100351b5:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100351e0:
		mov eax, dword ptr [esp + 0xdc]
jmp_100351e7:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_100352d2
jmp_100351f3:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100352fb + 1]
jmp_10035244:
		mov word ptr [edi], bx
		jmp jmp_100352bf
jmp_10035249:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100352bf
jmp_10035276:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100352c6
jmp_10035294:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100352bf:
		mov eax, dword ptr [esp + 0xdc]
jmp_100352c6:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10035114
jmp_100352d2:
		ret
jmp_100352d3:
		mov eax, OFFSET jmp_100351e0
		mov eax, OFFSET jmp_100351b5
		mov eax, OFFSET jmp_100351b5
		mov eax, OFFSET jmp_10035197
		mov eax, OFFSET jmp_10035197
		mov eax, OFFSET jmp_1003516a
		mov eax, OFFSET jmp_1003516a
		mov eax, OFFSET jmp_10035165
jmp_100352fb:
		mov eax, OFFSET jmp_100352bf
		mov eax, OFFSET jmp_100352bf
		mov eax, OFFSET jmp_10035294
		mov eax, OFFSET jmp_10035294
		mov eax, OFFSET jmp_10035276
		mov eax, OFFSET jmp_10035249
		mov eax, OFFSET jmp_10035244
		mov eax, OFFSET jmp_10035244
	}
}

// FUNCTION: GOLDP 0x10035330
__declspec(naked) void FUN_10035330()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10035443
jmp_10035364:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10035523 + 1]
jmp_100353b5:
		mov word ptr [edi], bx
		jmp jmp_10035430
jmp_100353ba:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10035430
jmp_100353e7:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10035437
jmp_10035405:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10035430:
		mov eax, dword ptr [esp + 0xdc]
jmp_10035437:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10035522
jmp_10035443:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003554b + 1]
jmp_10035494:
		mov word ptr [edi], bx
		jmp jmp_1003550f
jmp_10035499:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003550f
jmp_100354c6:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10035516
jmp_100354e4:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003550f:
		mov eax, dword ptr [esp + 0xdc]
jmp_10035516:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10035364
jmp_10035522:
		ret
jmp_10035523:
		mov eax, OFFSET jmp_10035430
		mov eax, OFFSET jmp_10035405
		mov eax, OFFSET jmp_10035405
		mov eax, OFFSET jmp_100353e7
		mov eax, OFFSET jmp_100353e7
		mov eax, OFFSET jmp_100353ba
		mov eax, OFFSET jmp_100353ba
		mov eax, OFFSET jmp_100353b5
jmp_1003554b:
		mov eax, OFFSET jmp_1003550f
		mov eax, OFFSET jmp_1003550f
		mov eax, OFFSET jmp_100354e4
		mov eax, OFFSET jmp_100354e4
		mov eax, OFFSET jmp_100354c6
		mov eax, OFFSET jmp_10035499
		mov eax, OFFSET jmp_10035494
		mov eax, OFFSET jmp_10035494
	}
}

// FUNCTION: GOLDP 0x10035580
__declspec(naked) void FUN_10035580()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10035699
jmp_100355b4:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10035686
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003577f + 1]
jmp_1003560b:
		mov word ptr [edi], bx
		jmp jmp_10035686
jmp_10035610:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10035686
jmp_1003563d:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003568d
jmp_1003565b:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10035686:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003568d:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_1003577e
jmp_10035699:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_1003576b
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100357a7 + 1]
jmp_100356f0:
		mov word ptr [edi], bx
		jmp jmp_1003576b
jmp_100356f5:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003576b
jmp_10035722:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10035772
jmp_10035740:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003576b:
		mov eax, dword ptr [esp + 0xdc]
jmp_10035772:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100355b4
jmp_1003577e:
		ret
jmp_1003577f:
		mov eax, OFFSET jmp_10035686
		mov eax, OFFSET jmp_1003565b
		mov eax, OFFSET jmp_1003565b
		mov eax, OFFSET jmp_1003563d
		mov eax, OFFSET jmp_1003563d
		mov eax, OFFSET jmp_10035610
		mov eax, OFFSET jmp_10035610
		mov eax, OFFSET jmp_1003560b
jmp_100357a7:
		mov eax, OFFSET jmp_1003576b
		mov eax, OFFSET jmp_1003576b
		mov eax, OFFSET jmp_10035740
		mov eax, OFFSET jmp_10035740
		mov eax, OFFSET jmp_10035722
		mov eax, OFFSET jmp_100356f5
		mov eax, OFFSET jmp_100356f0
		mov eax, OFFSET jmp_100356f0
	}
}

// FUNCTION: GOLDP 0x100357d0
__declspec(naked) void FUN_100357d0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_100358e9
jmp_10035804:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_100358d6
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100359cf + 1]
jmp_1003585b:
		mov word ptr [edi], bx
		jmp jmp_100358d6
jmp_10035860:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100358d6
jmp_1003588d:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100358dd
jmp_100358ab:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100358d6:
		mov eax, dword ptr [esp + 0xdc]
jmp_100358dd:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_100359ce
jmp_100358e9:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_100359bb
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100359f7 + 1]
jmp_10035940:
		mov word ptr [edi], bx
		jmp jmp_100359bb
jmp_10035945:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100359bb
jmp_10035972:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100359c2
jmp_10035990:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100359bb:
		mov eax, dword ptr [esp + 0xdc]
jmp_100359c2:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10035804
jmp_100359ce:
		ret
jmp_100359cf:
		mov eax, OFFSET jmp_100358d6
		mov eax, OFFSET jmp_100358ab
		mov eax, OFFSET jmp_100358ab
		mov eax, OFFSET jmp_1003588d
		mov eax, OFFSET jmp_1003588d
		mov eax, OFFSET jmp_10035860
		mov eax, OFFSET jmp_10035860
		mov eax, OFFSET jmp_1003585b
jmp_100359f7:
		mov eax, OFFSET jmp_100359bb
		mov eax, OFFSET jmp_100359bb
		mov eax, OFFSET jmp_10035990
		mov eax, OFFSET jmp_10035990
		mov eax, OFFSET jmp_10035972
		mov eax, OFFSET jmp_10035945
		mov eax, OFFSET jmp_10035940
		mov eax, OFFSET jmp_10035940
	}
}

// FUNCTION: GOLDP 0x10035a20
__declspec(naked) void FUN_10035a20()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10035a56:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 5
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x3e0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xa
		mov ecx, dword ptr [esp + 0xd4]
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 5
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10035a56
		ret
	}
}

// FUNCTION: GOLDP 0x10035b60
__declspec(naked) void FUN_10035b60()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10035b96:
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 6
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x7c0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xb
		mov ecx, dword ptr [esp + 0xd4]
		shr ebp, 1
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 6
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10035b96
		ret
	}
}

// FUNCTION: GOLDP 0x10035ca0
__declspec(naked) void FUN_10035ca0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x10057a00]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_10035d35:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xa
		movq mm3, mm4
		psllq mm4, 0x2b
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 9
		and eax, 0x7f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10035d35
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10035dd0
__declspec(naked) void FUN_10035dd0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x100579f8]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_10035e65:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xb
		movq mm3, mm4
		psllq mm4, 0x2a
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 9
		and eax, 0x7f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10035e65
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10035f00
__declspec(naked) void FUN_10035f00()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0x7f0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_10035f6a
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		je jmp_10035f53
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi - 2], bx
jmp_10035f53:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x7f0000
		js jmp_10036083
jmp_10035f6a:
		dec ecx
		js jmp_10036056
jmp_10035f71:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov al, byte ptr [eax]
		add edx, ebx
		and eax, 0xff
		mov bl, byte ptr [esi]
		mov esi, dword ptr [esp + 0x124]
		je jmp_10036029
		and ebx, 0xff
		je jmp_10036005
		mov ax, word ptr [esi + eax*2]
		lea edi, [edi + 4]
		shl eax, 0x10
		sub ecx, 2
		mov ax, word ptr [esi + ebx*2]
		mov ebx, 0x7f0000
		mov dword ptr [edi - 4], eax
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10035f71
		jmp jmp_10036053
jmp_10036005:
		mov ax, word ptr [esi + eax*2]
		mov ebx, 0x7f0000
		mov word ptr [edi + 2], ax
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10035f71
		jmp jmp_10036053
jmp_10036029:
		and ebx, 0xff
		lea edi, [edi + 4]
		mov eax, ebp
		je jmp_1003603e
		mov bx, word ptr [esi + ebx*2]
		mov word ptr [edi - 4], bx
jmp_1003603e:
		sub ecx, 2
		mov ebx, 0x7f0000
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10035f71
jmp_10036053:
		inc ecx
		jne jmp_10036083
jmp_10036056:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		je jmp_10036083
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_10036083:
		ret
	}
}

// FUNCTION: GOLDP 0x10036090
__declspec(naked) void FUN_10036090()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x7f0000
		je jmp_100360f8
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov eax, dword ptr [esp + 0xcc]
		mov word ptr [edi - 2], bx
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x7f0000
		js jmp_100361b1
jmp_100360f8:
		dec ecx
		js jmp_1003618d
jmp_100360ff:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		add eax, esi
		mov esi, dword ptr [esp + 0xc8]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, esi
		add edx, ebx
		mov esi, ebp
		mov ebx, 0x7f0000
		shr esi, 0x10
		and ebx, edx
		shr ebx, 9
		and esi, 0x7f
		or ebx, esi
		mov esi, dword ptr [esp + 0x13c]
		add ebx, esi
		mov al, byte ptr [eax]
		and eax, 0xff
		mov esi, dword ptr [esp + 0xc8]
		mov bl, byte ptr [ebx]
		add ebp, esi
		and ebx, 0xff
		mov esi, dword ptr [esp + 0x124]
		add edx, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx*2]
		shl ebx, 0x10
		mov bx, word ptr [esi + eax*2]
		sub ecx, 2
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		mov ebx, 0x7f0000
		jns jmp_100360ff
		inc ecx
		jne jmp_100361b1
jmp_1003618d:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 9
		and eax, 0x7f
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_100361b1:
		ret
	}
}

// FUNCTION: GOLDP 0x100361c0
__declspec(naked) void FUN_100361c0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0x7f0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_10036222
		shr eax, 0xf
		and ebx, edx
		shr ebx, 8
		and eax, 0xfe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		add edi, 2
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_1003620b
		mov word ptr [edi - 2], bx
jmp_1003620b:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x7f0000
		js jmp_10036329
jmp_10036222:
		dec ecx
		js jmp_100362fd
jmp_10036229:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 8
		and eax, 0xfe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 8
		and eax, 0xfe
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov ax, word ptr [eax]
		add edx, ebx
		and eax, 0xffff
		mov bx, word ptr [esi]
		je jmp_100362d5
		and ebx, 0xffff
		je jmp_100362b5
		shl eax, 0x10
		mov esi, dword ptr [esp + 0x13c]
		or eax, ebx
		mov ebx, 0x7f0000
		mov dword ptr [edi], eax
		sub ecx, 2
		lea edi, [edi + 4]
		mov eax, ebp
		jns jmp_10036229
		jmp jmp_100362fa
jmp_100362b5:
		mov word ptr [edi + 2], ax
		mov ebx, 0x7f0000
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10036229
		jmp jmp_100362fa
jmp_100362d5:
		and ebx, 0xffff
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		je jmp_100362e9
		mov word ptr [edi], bx
jmp_100362e9:
		sub ecx, 2
		lea edi, [edi + 4]
		mov ebx, 0x7f0000
		jns jmp_10036229
jmp_100362fa:
		inc ecx
		jne jmp_10036329
jmp_100362fd:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 8
		and eax, 0xfe
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_10036329
		mov word ptr [edi], bx
jmp_10036329:
		ret
	}
}

// FUNCTION: GOLDP 0x10036330
__declspec(naked) void FUN_10036330()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x7f0000
		je jmp_10036389
		shr eax, 0xf
		and ebx, edx
		shr ebx, 8
		and eax, 0xfe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx]
		add edx, eax
		mov word ptr [edi], bx
		add edi, 2
		dec ecx
		mov eax, ebp
		mov ebx, 0x7f0000
		js jmp_1003641a
jmp_10036389:
		dec ecx
		js jmp_10036404
jmp_1003638c:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 8
		and eax, 0xfe
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x7f0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 8
		and eax, 0xfe
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [ebx]
		add edx, eax
		shl ebx, 0x10
		sub ecx, 2
		mov bx, word ptr [esi]
		mov eax, ebp
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, 0x7f0000
		jns jmp_1003638c
		inc ecx
		jne jmp_1003641a
jmp_10036404:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 8
		and eax, 0xfe
		or ebx, eax
		mov bx, word ptr [esi + ebx]
		mov word ptr [edi], bx
jmp_1003641a:
		ret
	}
}

// FUNCTION: GOLDP 0x10036420
__declspec(naked) void FUN_10036420()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_1003644c:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 8
		and eax, 0xfc
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10036523 + 1]
jmp_100364a5:
		mov word ptr [edi], ax
		jmp jmp_10036518
jmp_100364aa:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10036518
jmp_100364d7:
		mov bx, word ptr [edi]
		and eax, 0x7bde
		and ebx, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_10036518
jmp_100364ee:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov bx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10036518:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003644c
		ret
jmp_10036523:
		mov eax, OFFSET jmp_10036518
		mov eax, OFFSET jmp_100364ee
		mov eax, OFFSET jmp_100364d7
		mov eax, OFFSET jmp_100364aa
		mov eax, OFFSET jmp_100364a5
	}
}

// FUNCTION: GOLDP 0x10036540
__declspec(naked) void FUN_10036540()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_1003656c:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 8
		and eax, 0xfc
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10036643 + 1]
jmp_100365c5:
		mov word ptr [edi], ax
		jmp jmp_10036638
jmp_100365ca:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10036638
jmp_100365f7:
		mov bx, word ptr [edi]
		and eax, 0xf7de
		and ebx, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_10036638
jmp_1003660e:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov bx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10036638:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003656c
		ret
jmp_10036643:
		mov eax, OFFSET jmp_10036638
		mov eax, OFFSET jmp_1003660e
		mov eax, OFFSET jmp_100365f7
		mov eax, OFFSET jmp_100365ca
		mov eax, OFFSET jmp_100365c5
	}
}

// FUNCTION: GOLDP 0x10036660
__declspec(naked) void FUN_10036660()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10036773
jmp_10036694:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10036853 + 1]
jmp_100366e5:
		mov word ptr [edi], bx
		jmp jmp_10036760
jmp_100366ea:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10036760
jmp_10036717:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10036767
jmp_10036735:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10036760:
		mov eax, dword ptr [esp + 0xdc]
jmp_10036767:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10036852
jmp_10036773:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003687b + 1]
jmp_100367c4:
		mov word ptr [edi], bx
		jmp jmp_1003683f
jmp_100367c9:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003683f
jmp_100367f6:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10036846
jmp_10036814:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003683f:
		mov eax, dword ptr [esp + 0xdc]
jmp_10036846:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10036694
jmp_10036852:
		ret
jmp_10036853:
		mov eax, OFFSET jmp_10036760
		mov eax, OFFSET jmp_10036735
		mov eax, OFFSET jmp_10036735
		mov eax, OFFSET jmp_10036717
		mov eax, OFFSET jmp_10036717
		mov eax, OFFSET jmp_100366ea
		mov eax, OFFSET jmp_100366ea
		mov eax, OFFSET jmp_100366e5
jmp_1003687b:
		mov eax, OFFSET jmp_1003683f
		mov eax, OFFSET jmp_1003683f
		mov eax, OFFSET jmp_10036814
		mov eax, OFFSET jmp_10036814
		mov eax, OFFSET jmp_100367f6
		mov eax, OFFSET jmp_100367c9
		mov eax, OFFSET jmp_100367c4
		mov eax, OFFSET jmp_100367c4
	}
}

// FUNCTION: GOLDP 0x100368b0
__declspec(naked) void FUN_100368b0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_100369c3
jmp_100368e4:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10036aa3 + 1]
jmp_10036935:
		mov word ptr [edi], bx
		jmp jmp_100369b0
jmp_1003693a:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100369b0
jmp_10036967:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100369b7
jmp_10036985:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100369b0:
		mov eax, dword ptr [esp + 0xdc]
jmp_100369b7:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10036aa2
jmp_100369c3:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10036acb + 1]
jmp_10036a14:
		mov word ptr [edi], bx
		jmp jmp_10036a8f
jmp_10036a19:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10036a8f
jmp_10036a46:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10036a96
jmp_10036a64:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10036a8f:
		mov eax, dword ptr [esp + 0xdc]
jmp_10036a96:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100368e4
jmp_10036aa2:
		ret
jmp_10036aa3:
		mov eax, OFFSET jmp_100369b0
		mov eax, OFFSET jmp_10036985
		mov eax, OFFSET jmp_10036985
		mov eax, OFFSET jmp_10036967
		mov eax, OFFSET jmp_10036967
		mov eax, OFFSET jmp_1003693a
		mov eax, OFFSET jmp_1003693a
		mov eax, OFFSET jmp_10036935
jmp_10036acb:
		mov eax, OFFSET jmp_10036a8f
		mov eax, OFFSET jmp_10036a8f
		mov eax, OFFSET jmp_10036a64
		mov eax, OFFSET jmp_10036a64
		mov eax, OFFSET jmp_10036a46
		mov eax, OFFSET jmp_10036a19
		mov eax, OFFSET jmp_10036a14
		mov eax, OFFSET jmp_10036a14
	}
}

// FUNCTION: GOLDP 0x10036b00
__declspec(naked) void FUN_10036b00()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10036c19
jmp_10036b34:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10036c06
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10036cff + 1]
jmp_10036b8b:
		mov word ptr [edi], bx
		jmp jmp_10036c06
jmp_10036b90:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10036c06
jmp_10036bbd:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10036c0d
jmp_10036bdb:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10036c06:
		mov eax, dword ptr [esp + 0xdc]
jmp_10036c0d:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10036cfe
jmp_10036c19:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10036ceb
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10036d27 + 1]
jmp_10036c70:
		mov word ptr [edi], bx
		jmp jmp_10036ceb
jmp_10036c75:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10036ceb
jmp_10036ca2:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10036cf2
jmp_10036cc0:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10036ceb:
		mov eax, dword ptr [esp + 0xdc]
jmp_10036cf2:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10036b34
jmp_10036cfe:
		ret
jmp_10036cff:
		mov eax, OFFSET jmp_10036c06
		mov eax, OFFSET jmp_10036bdb
		mov eax, OFFSET jmp_10036bdb
		mov eax, OFFSET jmp_10036bbd
		mov eax, OFFSET jmp_10036bbd
		mov eax, OFFSET jmp_10036b90
		mov eax, OFFSET jmp_10036b90
		mov eax, OFFSET jmp_10036b8b
jmp_10036d27:
		mov eax, OFFSET jmp_10036ceb
		mov eax, OFFSET jmp_10036ceb
		mov eax, OFFSET jmp_10036cc0
		mov eax, OFFSET jmp_10036cc0
		mov eax, OFFSET jmp_10036ca2
		mov eax, OFFSET jmp_10036c75
		mov eax, OFFSET jmp_10036c70
		mov eax, OFFSET jmp_10036c70
	}
}

// FUNCTION: GOLDP 0x10036d50
__declspec(naked) void FUN_10036d50()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10036e69
jmp_10036d84:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10036e56
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10036f4f + 1]
jmp_10036ddb:
		mov word ptr [edi], bx
		jmp jmp_10036e56
jmp_10036de0:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10036e56
jmp_10036e0d:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10036e5d
jmp_10036e2b:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10036e56:
		mov eax, dword ptr [esp + 0xdc]
jmp_10036e5d:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10036f4e
jmp_10036e69:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10036f3b
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10036f77 + 1]
jmp_10036ec0:
		mov word ptr [edi], bx
		jmp jmp_10036f3b
jmp_10036ec5:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10036f3b
jmp_10036ef2:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10036f42
jmp_10036f10:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10036f3b:
		mov eax, dword ptr [esp + 0xdc]
jmp_10036f42:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10036d84
jmp_10036f4e:
		ret
jmp_10036f4f:
		mov eax, OFFSET jmp_10036e56
		mov eax, OFFSET jmp_10036e2b
		mov eax, OFFSET jmp_10036e2b
		mov eax, OFFSET jmp_10036e0d
		mov eax, OFFSET jmp_10036e0d
		mov eax, OFFSET jmp_10036de0
		mov eax, OFFSET jmp_10036de0
		mov eax, OFFSET jmp_10036ddb
jmp_10036f77:
		mov eax, OFFSET jmp_10036f3b
		mov eax, OFFSET jmp_10036f3b
		mov eax, OFFSET jmp_10036f10
		mov eax, OFFSET jmp_10036f10
		mov eax, OFFSET jmp_10036ef2
		mov eax, OFFSET jmp_10036ec5
		mov eax, OFFSET jmp_10036ec0
		mov eax, OFFSET jmp_10036ec0
	}
}

// FUNCTION: GOLDP 0x10036fa0
__declspec(naked) void FUN_10036fa0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10036fd6:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 5
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x3e0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xa
		mov ecx, dword ptr [esp + 0xd4]
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 5
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10036fd6
		ret
	}
}

// FUNCTION: GOLDP 0x100370e0
__declspec(naked) void FUN_100370e0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10037116:
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 6
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x7c0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xb
		mov ecx, dword ptr [esp + 0xd4]
		shr ebp, 1
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 6
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10037116
		ret
	}
}

// FUNCTION: GOLDP 0x10037220
__declspec(naked) void FUN_10037220()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x10057a00]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_100372b5:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xa
		movq mm3, mm4
		psllq mm4, 0x2b
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 0xa
		and eax, 0x3f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100372b5
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10037350
__declspec(naked) void FUN_10037350()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x100579f8]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_100373e5:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xb
		movq mm3, mm4
		psllq mm4, 0x2a
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 0xa
		and eax, 0x3f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100373e5
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10037480
__declspec(naked) void FUN_10037480()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0x3f0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_100374ea
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		je jmp_100374d3
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi - 2], bx
jmp_100374d3:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x3f0000
		js jmp_10037603
jmp_100374ea:
		dec ecx
		js jmp_100375d6
jmp_100374f1:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov al, byte ptr [eax]
		add edx, ebx
		and eax, 0xff
		mov bl, byte ptr [esi]
		mov esi, dword ptr [esp + 0x124]
		je jmp_100375a9
		and ebx, 0xff
		je jmp_10037585
		mov ax, word ptr [esi + eax*2]
		lea edi, [edi + 4]
		shl eax, 0x10
		sub ecx, 2
		mov ax, word ptr [esi + ebx*2]
		mov ebx, 0x3f0000
		mov dword ptr [edi - 4], eax
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_100374f1
		jmp jmp_100375d3
jmp_10037585:
		mov ax, word ptr [esi + eax*2]
		mov ebx, 0x3f0000
		mov word ptr [edi + 2], ax
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_100374f1
		jmp jmp_100375d3
jmp_100375a9:
		and ebx, 0xff
		lea edi, [edi + 4]
		mov eax, ebp
		je jmp_100375be
		mov bx, word ptr [esi + ebx*2]
		mov word ptr [edi - 4], bx
jmp_100375be:
		sub ecx, 2
		mov ebx, 0x3f0000
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_100374f1
jmp_100375d3:
		inc ecx
		jne jmp_10037603
jmp_100375d6:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		je jmp_10037603
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_10037603:
		ret
	}
}

// FUNCTION: GOLDP 0x10037610
__declspec(naked) void FUN_10037610()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x3f0000
		je jmp_10037678
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov eax, dword ptr [esp + 0xcc]
		mov word ptr [edi - 2], bx
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x3f0000
		js jmp_10037731
jmp_10037678:
		dec ecx
		js jmp_1003770d
jmp_1003767f:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		add eax, esi
		mov esi, dword ptr [esp + 0xc8]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, esi
		add edx, ebx
		mov esi, ebp
		mov ebx, 0x3f0000
		shr esi, 0x10
		and ebx, edx
		shr ebx, 0xa
		and esi, 0x3f
		or ebx, esi
		mov esi, dword ptr [esp + 0x13c]
		add ebx, esi
		mov al, byte ptr [eax]
		and eax, 0xff
		mov esi, dword ptr [esp + 0xc8]
		mov bl, byte ptr [ebx]
		add ebp, esi
		and ebx, 0xff
		mov esi, dword ptr [esp + 0x124]
		add edx, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx*2]
		shl ebx, 0x10
		mov bx, word ptr [esi + eax*2]
		sub ecx, 2
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		mov ebx, 0x3f0000
		jns jmp_1003767f
		inc ecx
		jne jmp_10037731
jmp_1003770d:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3f
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_10037731:
		ret
	}
}

// FUNCTION: GOLDP 0x10037740
__declspec(naked) void FUN_10037740()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0x3f0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_100377a0
		shr eax, 0xf
		and ebx, edx
		shr ebx, 9
		and eax, 0x7e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		add edi, 2
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_10037789
		mov word ptr [edi - 2], bx
jmp_10037789:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x3f0000
		js jmp_100378a1
jmp_100377a0:
		dec ecx
		js jmp_10037877
jmp_100377a7:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 9
		and eax, 0x7e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 9
		and eax, 0x7e
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov ax, word ptr [eax]
		add edx, ebx
		and eax, 0xffff
		mov bx, word ptr [esi]
		je jmp_1003784f
		and ebx, 0xffff
		je jmp_1003782f
		shl eax, 0x10
		mov esi, dword ptr [esp + 0x13c]
		or eax, ebx
		mov ebx, 0x3f0000
		mov dword ptr [edi], eax
		sub ecx, 2
		lea edi, [edi + 4]
		mov eax, ebp
		jns jmp_100377a7
		jmp jmp_10037874
jmp_1003782f:
		mov word ptr [edi + 2], ax
		mov ebx, 0x3f0000
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_100377a7
		jmp jmp_10037874
jmp_1003784f:
		and ebx, 0xffff
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		je jmp_10037863
		mov word ptr [edi], bx
jmp_10037863:
		sub ecx, 2
		lea edi, [edi + 4]
		mov ebx, 0x3f0000
		jns jmp_100377a7
jmp_10037874:
		inc ecx
		jne jmp_100378a1
jmp_10037877:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 9
		and eax, 0x7e
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_100378a1
		mov word ptr [edi], bx
jmp_100378a1:
		ret
	}
}

// FUNCTION: GOLDP 0x100378b0
__declspec(naked) void FUN_100378b0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x3f0000
		je jmp_10037907
		shr eax, 0xf
		and ebx, edx
		shr ebx, 9
		and eax, 0x7e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx]
		add edx, eax
		mov word ptr [edi], bx
		add edi, 2
		dec ecx
		mov eax, ebp
		mov ebx, 0x3f0000
		js jmp_10037992
jmp_10037907:
		dec ecx
		js jmp_1003797e
jmp_1003790a:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 9
		and eax, 0x7e
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x3f0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 9
		and eax, 0x7e
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [ebx]
		add edx, eax
		shl ebx, 0x10
		sub ecx, 2
		mov bx, word ptr [esi]
		mov eax, ebp
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, 0x3f0000
		jns jmp_1003790a
		inc ecx
		jne jmp_10037992
jmp_1003797e:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 9
		and eax, 0x7e
		or ebx, eax
		mov bx, word ptr [esi + ebx]
		mov word ptr [edi], bx
jmp_10037992:
		ret
	}
}

// FUNCTION: GOLDP 0x100379a0
__declspec(naked) void FUN_100379a0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_100379cc:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 9
		and eax, 0x7c
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10037aa1 + 1]
jmp_10037a23:
		mov word ptr [edi], ax
		jmp jmp_10037a96
jmp_10037a28:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10037a96
jmp_10037a55:
		mov bx, word ptr [edi]
		and eax, 0x7bde
		and ebx, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_10037a96
jmp_10037a6c:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov bx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10037a96:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100379cc
		ret
jmp_10037aa1:
		mov eax, OFFSET jmp_10037a96
		mov eax, OFFSET jmp_10037a6c
		mov eax, OFFSET jmp_10037a55
		mov eax, OFFSET jmp_10037a28
		mov eax, OFFSET jmp_10037a23
	}
}

// FUNCTION: GOLDP 0x10037ac0
__declspec(naked) void FUN_10037ac0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_10037aec:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 9
		and eax, 0x7c
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10037bc1 + 1]
jmp_10037b43:
		mov word ptr [edi], ax
		jmp jmp_10037bb6
jmp_10037b48:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10037bb6
jmp_10037b75:
		mov bx, word ptr [edi]
		and eax, 0xf7de
		and ebx, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_10037bb6
jmp_10037b8c:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov bx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10037bb6:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10037aec
		ret
jmp_10037bc1:
		mov eax, OFFSET jmp_10037bb6
		mov eax, OFFSET jmp_10037b8c
		mov eax, OFFSET jmp_10037b75
		mov eax, OFFSET jmp_10037b48
		mov eax, OFFSET jmp_10037b43
	}
}

// FUNCTION: GOLDP 0x10037be0
__declspec(naked) void FUN_10037be0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10037cf3
jmp_10037c14:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10037dd3 + 1]
jmp_10037c65:
		mov word ptr [edi], bx
		jmp jmp_10037ce0
jmp_10037c6a:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10037ce0
jmp_10037c97:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10037ce7
jmp_10037cb5:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10037ce0:
		mov eax, dword ptr [esp + 0xdc]
jmp_10037ce7:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10037dd2
jmp_10037cf3:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10037dfb + 1]
jmp_10037d44:
		mov word ptr [edi], bx
		jmp jmp_10037dbf
jmp_10037d49:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10037dbf
jmp_10037d76:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10037dc6
jmp_10037d94:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10037dbf:
		mov eax, dword ptr [esp + 0xdc]
jmp_10037dc6:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10037c14
jmp_10037dd2:
		ret
jmp_10037dd3:
		mov eax, OFFSET jmp_10037ce0
		mov eax, OFFSET jmp_10037cb5
		mov eax, OFFSET jmp_10037cb5
		mov eax, OFFSET jmp_10037c97
		mov eax, OFFSET jmp_10037c97
		mov eax, OFFSET jmp_10037c6a
		mov eax, OFFSET jmp_10037c6a
		mov eax, OFFSET jmp_10037c65
jmp_10037dfb:
		mov eax, OFFSET jmp_10037dbf
		mov eax, OFFSET jmp_10037dbf
		mov eax, OFFSET jmp_10037d94
		mov eax, OFFSET jmp_10037d94
		mov eax, OFFSET jmp_10037d76
		mov eax, OFFSET jmp_10037d49
		mov eax, OFFSET jmp_10037d44
		mov eax, OFFSET jmp_10037d44
	}
}

// FUNCTION: GOLDP 0x10037e30
__declspec(naked) void FUN_10037e30()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10037f43
jmp_10037e64:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10038023 + 1]
jmp_10037eb5:
		mov word ptr [edi], bx
		jmp jmp_10037f30
jmp_10037eba:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10037f30
jmp_10037ee7:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10037f37
jmp_10037f05:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10037f30:
		mov eax, dword ptr [esp + 0xdc]
jmp_10037f37:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10038022
jmp_10037f43:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003804b + 1]
jmp_10037f94:
		mov word ptr [edi], bx
		jmp jmp_1003800f
jmp_10037f99:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003800f
jmp_10037fc6:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10038016
jmp_10037fe4:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003800f:
		mov eax, dword ptr [esp + 0xdc]
jmp_10038016:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10037e64
jmp_10038022:
		ret
jmp_10038023:
		mov eax, OFFSET jmp_10037f30
		mov eax, OFFSET jmp_10037f05
		mov eax, OFFSET jmp_10037f05
		mov eax, OFFSET jmp_10037ee7
		mov eax, OFFSET jmp_10037ee7
		mov eax, OFFSET jmp_10037eba
		mov eax, OFFSET jmp_10037eba
		mov eax, OFFSET jmp_10037eb5
jmp_1003804b:
		mov eax, OFFSET jmp_1003800f
		mov eax, OFFSET jmp_1003800f
		mov eax, OFFSET jmp_10037fe4
		mov eax, OFFSET jmp_10037fe4
		mov eax, OFFSET jmp_10037fc6
		mov eax, OFFSET jmp_10037f99
		mov eax, OFFSET jmp_10037f94
		mov eax, OFFSET jmp_10037f94
	}
}

// FUNCTION: GOLDP 0x10038080
__declspec(naked) void FUN_10038080()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10038199
jmp_100380b4:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10038186
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003827f + 1]
jmp_1003810b:
		mov word ptr [edi], bx
		jmp jmp_10038186
jmp_10038110:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10038186
jmp_1003813d:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003818d
jmp_1003815b:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10038186:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003818d:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_1003827e
jmp_10038199:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_1003826b
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100382a7 + 1]
jmp_100381f0:
		mov word ptr [edi], bx
		jmp jmp_1003826b
jmp_100381f5:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003826b
jmp_10038222:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10038272
jmp_10038240:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003826b:
		mov eax, dword ptr [esp + 0xdc]
jmp_10038272:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100380b4
jmp_1003827e:
		ret
jmp_1003827f:
		mov eax, OFFSET jmp_10038186
		mov eax, OFFSET jmp_1003815b
		mov eax, OFFSET jmp_1003815b
		mov eax, OFFSET jmp_1003813d
		mov eax, OFFSET jmp_1003813d
		mov eax, OFFSET jmp_10038110
		mov eax, OFFSET jmp_10038110
		mov eax, OFFSET jmp_1003810b
jmp_100382a7:
		mov eax, OFFSET jmp_1003826b
		mov eax, OFFSET jmp_1003826b
		mov eax, OFFSET jmp_10038240
		mov eax, OFFSET jmp_10038240
		mov eax, OFFSET jmp_10038222
		mov eax, OFFSET jmp_100381f5
		mov eax, OFFSET jmp_100381f0
		mov eax, OFFSET jmp_100381f0
	}
}

// FUNCTION: GOLDP 0x100382d0
__declspec(naked) void FUN_100382d0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_100383e9
jmp_10038304:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_100383d6
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100384cf + 1]
jmp_1003835b:
		mov word ptr [edi], bx
		jmp jmp_100383d6
jmp_10038360:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100383d6
jmp_1003838d:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100383dd
jmp_100383ab:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100383d6:
		mov eax, dword ptr [esp + 0xdc]
jmp_100383dd:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_100384ce
jmp_100383e9:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_100384bb
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100384f7 + 1]
jmp_10038440:
		mov word ptr [edi], bx
		jmp jmp_100384bb
jmp_10038445:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100384bb
jmp_10038472:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100384c2
jmp_10038490:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100384bb:
		mov eax, dword ptr [esp + 0xdc]
jmp_100384c2:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10038304
jmp_100384ce:
		ret
jmp_100384cf:
		mov eax, OFFSET jmp_100383d6
		mov eax, OFFSET jmp_100383ab
		mov eax, OFFSET jmp_100383ab
		mov eax, OFFSET jmp_1003838d
		mov eax, OFFSET jmp_1003838d
		mov eax, OFFSET jmp_10038360
		mov eax, OFFSET jmp_10038360
		mov eax, OFFSET jmp_1003835b
jmp_100384f7:
		mov eax, OFFSET jmp_100384bb
		mov eax, OFFSET jmp_100384bb
		mov eax, OFFSET jmp_10038490
		mov eax, OFFSET jmp_10038490
		mov eax, OFFSET jmp_10038472
		mov eax, OFFSET jmp_10038445
		mov eax, OFFSET jmp_10038440
		mov eax, OFFSET jmp_10038440
	}
}

// FUNCTION: GOLDP 0x10038520
__declspec(naked) void FUN_10038520()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10038556:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 5
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x3e0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xa
		mov ecx, dword ptr [esp + 0xd4]
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 5
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10038556
		ret
	}
}

// FUNCTION: GOLDP 0x10038660
__declspec(naked) void FUN_10038660()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10038696:
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 6
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x7c0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xb
		mov ecx, dword ptr [esp + 0xd4]
		shr ebp, 1
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 6
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10038696
		ret
	}
}

// FUNCTION: GOLDP 0x100387a0
__declspec(naked) void FUN_100387a0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x10057a00]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_10038835:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xa
		movq mm3, mm4
		psllq mm4, 0x2b
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 0xb
		and eax, 0x1f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10038835
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x100388d0
__declspec(naked) void FUN_100388d0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x100579f8]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_10038965:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xb
		movq mm3, mm4
		psllq mm4, 0x2a
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 0xb
		and eax, 0x1f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10038965
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10038a00
__declspec(naked) void FUN_10038a00()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0x1f0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_10038a6a
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		je jmp_10038a53
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi - 2], bx
jmp_10038a53:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x1f0000
		js jmp_10038b83
jmp_10038a6a:
		dec ecx
		js jmp_10038b56
jmp_10038a71:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov al, byte ptr [eax]
		add edx, ebx
		and eax, 0xff
		mov bl, byte ptr [esi]
		mov esi, dword ptr [esp + 0x124]
		je jmp_10038b29
		and ebx, 0xff
		je jmp_10038b05
		mov ax, word ptr [esi + eax*2]
		lea edi, [edi + 4]
		shl eax, 0x10
		sub ecx, 2
		mov ax, word ptr [esi + ebx*2]
		mov ebx, 0x1f0000
		mov dword ptr [edi - 4], eax
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10038a71
		jmp jmp_10038b53
jmp_10038b05:
		mov ax, word ptr [esi + eax*2]
		mov ebx, 0x1f0000
		mov word ptr [edi + 2], ax
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10038a71
		jmp jmp_10038b53
jmp_10038b29:
		and ebx, 0xff
		lea edi, [edi + 4]
		mov eax, ebp
		je jmp_10038b3e
		mov bx, word ptr [esi + ebx*2]
		mov word ptr [edi - 4], bx
jmp_10038b3e:
		sub ecx, 2
		mov ebx, 0x1f0000
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10038a71
jmp_10038b53:
		inc ecx
		jne jmp_10038b83
jmp_10038b56:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		je jmp_10038b83
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_10038b83:
		ret
	}
}

// FUNCTION: GOLDP 0x10038b90
__declspec(naked) void FUN_10038b90()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x1f0000
		je jmp_10038bf8
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov eax, dword ptr [esp + 0xcc]
		mov word ptr [edi - 2], bx
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x1f0000
		js jmp_10038cb1
jmp_10038bf8:
		dec ecx
		js jmp_10038c8d
jmp_10038bff:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		add eax, esi
		mov esi, dword ptr [esp + 0xc8]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, esi
		add edx, ebx
		mov esi, ebp
		mov ebx, 0x1f0000
		shr esi, 0x10
		and ebx, edx
		shr ebx, 0xb
		and esi, 0x1f
		or ebx, esi
		mov esi, dword ptr [esp + 0x13c]
		add ebx, esi
		mov al, byte ptr [eax]
		and eax, 0xff
		mov esi, dword ptr [esp + 0xc8]
		mov bl, byte ptr [ebx]
		add ebp, esi
		and ebx, 0xff
		mov esi, dword ptr [esp + 0x124]
		add edx, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx*2]
		shl ebx, 0x10
		mov bx, word ptr [esi + eax*2]
		sub ecx, 2
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		mov ebx, 0x1f0000
		jns jmp_10038bff
		inc ecx
		jne jmp_10038cb1
jmp_10038c8d:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1f
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_10038cb1:
		ret
	}
}

// FUNCTION: GOLDP 0x10038cc0
__declspec(naked) void FUN_10038cc0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0x1f0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_10038d20
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		add edi, 2
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_10038d09
		mov word ptr [edi - 2], bx
jmp_10038d09:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x1f0000
		js jmp_10038e21
jmp_10038d20:
		dec ecx
		js jmp_10038df7
jmp_10038d27:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3e
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov ax, word ptr [eax]
		add edx, ebx
		and eax, 0xffff
		mov bx, word ptr [esi]
		je jmp_10038dcf
		and ebx, 0xffff
		je jmp_10038daf
		shl eax, 0x10
		mov esi, dword ptr [esp + 0x13c]
		or eax, ebx
		mov ebx, 0x1f0000
		mov dword ptr [edi], eax
		sub ecx, 2
		lea edi, [edi + 4]
		mov eax, ebp
		jns jmp_10038d27
		jmp jmp_10038df4
jmp_10038daf:
		mov word ptr [edi + 2], ax
		mov ebx, 0x1f0000
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10038d27
		jmp jmp_10038df4
jmp_10038dcf:
		and ebx, 0xffff
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		je jmp_10038de3
		mov word ptr [edi], bx
jmp_10038de3:
		sub ecx, 2
		lea edi, [edi + 4]
		mov ebx, 0x1f0000
		jns jmp_10038d27
jmp_10038df4:
		inc ecx
		jne jmp_10038e21
jmp_10038df7:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3e
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_10038e21
		mov word ptr [edi], bx
jmp_10038e21:
		ret
	}
}

// FUNCTION: GOLDP 0x10038e30
__declspec(naked) void FUN_10038e30()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x1f0000
		je jmp_10038e87
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx]
		add edx, eax
		mov word ptr [edi], bx
		add edi, 2
		dec ecx
		mov eax, ebp
		mov ebx, 0x1f0000
		js jmp_10038f12
jmp_10038e87:
		dec ecx
		js jmp_10038efe
jmp_10038e8a:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3e
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x1f0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3e
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [ebx]
		add edx, eax
		shl ebx, 0x10
		sub ecx, 2
		mov bx, word ptr [esi]
		mov eax, ebp
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, 0x1f0000
		jns jmp_10038e8a
		inc ecx
		jne jmp_10038f12
jmp_10038efe:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xa
		and eax, 0x3e
		or ebx, eax
		mov bx, word ptr [esi + ebx]
		mov word ptr [edi], bx
jmp_10038f12:
		ret
	}
}

// FUNCTION: GOLDP 0x10038f20
__declspec(naked) void FUN_10038f20()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_10038f4c:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3c
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10039021 + 1]
jmp_10038fa3:
		mov word ptr [edi], ax
		jmp jmp_10039016
jmp_10038fa8:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10039016
jmp_10038fd5:
		mov bx, word ptr [edi]
		and eax, 0x7bde
		and ebx, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_10039016
jmp_10038fec:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov bx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10039016:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10038f4c
		ret
jmp_10039021:
		mov eax, OFFSET jmp_10039016
		mov eax, OFFSET jmp_10038fec
		mov eax, OFFSET jmp_10038fd5
		mov eax, OFFSET jmp_10038fa8
		mov eax, OFFSET jmp_10038fa3
	}
}

// FUNCTION: GOLDP 0x10039040
__declspec(naked) void FUN_10039040()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_1003906c:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 0xa
		and eax, 0x3c
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_10039141 + 1]
jmp_100390c3:
		mov word ptr [edi], ax
		jmp jmp_10039136
jmp_100390c8:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10039136
jmp_100390f5:
		mov bx, word ptr [edi]
		and eax, 0xf7de
		and ebx, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_10039136
jmp_1003910c:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov bx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10039136:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003906c
		ret
jmp_10039141:
		mov eax, OFFSET jmp_10039136
		mov eax, OFFSET jmp_1003910c
		mov eax, OFFSET jmp_100390f5
		mov eax, OFFSET jmp_100390c8
		mov eax, OFFSET jmp_100390c3
	}
}

// FUNCTION: GOLDP 0x10039160
__declspec(naked) void FUN_10039160()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10039273
jmp_10039194:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10039353 + 1]
jmp_100391e5:
		mov word ptr [edi], bx
		jmp jmp_10039260
jmp_100391ea:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10039260
jmp_10039217:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10039267
jmp_10039235:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10039260:
		mov eax, dword ptr [esp + 0xdc]
jmp_10039267:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10039352
jmp_10039273:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003937b + 1]
jmp_100392c4:
		mov word ptr [edi], bx
		jmp jmp_1003933f
jmp_100392c9:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003933f
jmp_100392f6:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10039346
jmp_10039314:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003933f:
		mov eax, dword ptr [esp + 0xdc]
jmp_10039346:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10039194
jmp_10039352:
		ret
jmp_10039353:
		mov eax, OFFSET jmp_10039260
		mov eax, OFFSET jmp_10039235
		mov eax, OFFSET jmp_10039235
		mov eax, OFFSET jmp_10039217
		mov eax, OFFSET jmp_10039217
		mov eax, OFFSET jmp_100391ea
		mov eax, OFFSET jmp_100391ea
		mov eax, OFFSET jmp_100391e5
jmp_1003937b:
		mov eax, OFFSET jmp_1003933f
		mov eax, OFFSET jmp_1003933f
		mov eax, OFFSET jmp_10039314
		mov eax, OFFSET jmp_10039314
		mov eax, OFFSET jmp_100392f6
		mov eax, OFFSET jmp_100392c9
		mov eax, OFFSET jmp_100392c4
		mov eax, OFFSET jmp_100392c4
	}
}

// FUNCTION: GOLDP 0x100393b0
__declspec(naked) void FUN_100393b0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_100394c3
jmp_100393e4:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100395a3 + 1]
jmp_10039435:
		mov word ptr [edi], bx
		jmp jmp_100394b0
jmp_1003943a:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100394b0
jmp_10039467:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100394b7
jmp_10039485:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100394b0:
		mov eax, dword ptr [esp + 0xdc]
jmp_100394b7:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_100395a2
jmp_100394c3:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100395cb + 1]
jmp_10039514:
		mov word ptr [edi], bx
		jmp jmp_1003958f
jmp_10039519:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003958f
jmp_10039546:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10039596
jmp_10039564:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003958f:
		mov eax, dword ptr [esp + 0xdc]
jmp_10039596:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_100393e4
jmp_100395a2:
		ret
jmp_100395a3:
		mov eax, OFFSET jmp_100394b0
		mov eax, OFFSET jmp_10039485
		mov eax, OFFSET jmp_10039485
		mov eax, OFFSET jmp_10039467
		mov eax, OFFSET jmp_10039467
		mov eax, OFFSET jmp_1003943a
		mov eax, OFFSET jmp_1003943a
		mov eax, OFFSET jmp_10039435
jmp_100395cb:
		mov eax, OFFSET jmp_1003958f
		mov eax, OFFSET jmp_1003958f
		mov eax, OFFSET jmp_10039564
		mov eax, OFFSET jmp_10039564
		mov eax, OFFSET jmp_10039546
		mov eax, OFFSET jmp_10039519
		mov eax, OFFSET jmp_10039514
		mov eax, OFFSET jmp_10039514
	}
}

// FUNCTION: GOLDP 0x10039600
__declspec(naked) void FUN_10039600()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10039719
jmp_10039634:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10039706
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_100397ff + 1]
jmp_1003968b:
		mov word ptr [edi], bx
		jmp jmp_10039706
jmp_10039690:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10039706
jmp_100396bd:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003970d
jmp_100396db:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10039706:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003970d:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_100397fe
jmp_10039719:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_100397eb
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10039827 + 1]
jmp_10039770:
		mov word ptr [edi], bx
		jmp jmp_100397eb
jmp_10039775:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_100397eb
jmp_100397a2:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_100397f2
jmp_100397c0:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_100397eb:
		mov eax, dword ptr [esp + 0xdc]
jmp_100397f2:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10039634
jmp_100397fe:
		ret
jmp_100397ff:
		mov eax, OFFSET jmp_10039706
		mov eax, OFFSET jmp_100396db
		mov eax, OFFSET jmp_100396db
		mov eax, OFFSET jmp_100396bd
		mov eax, OFFSET jmp_100396bd
		mov eax, OFFSET jmp_10039690
		mov eax, OFFSET jmp_10039690
		mov eax, OFFSET jmp_1003968b
jmp_10039827:
		mov eax, OFFSET jmp_100397eb
		mov eax, OFFSET jmp_100397eb
		mov eax, OFFSET jmp_100397c0
		mov eax, OFFSET jmp_100397c0
		mov eax, OFFSET jmp_100397a2
		mov eax, OFFSET jmp_10039775
		mov eax, OFFSET jmp_10039770
		mov eax, OFFSET jmp_10039770
	}
}

// FUNCTION: GOLDP 0x10039850
__declspec(naked) void FUN_10039850()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_10039969
jmp_10039884:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10039956
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10039a4f + 1]
jmp_100398db:
		mov word ptr [edi], bx
		jmp jmp_10039956
jmp_100398e0:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10039956
jmp_1003990d:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003995d
jmp_1003992b:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10039956:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003995d:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_10039a4e
jmp_10039969:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_10039a3b
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_10039a77 + 1]
jmp_100399c0:
		mov word ptr [edi], bx
		jmp jmp_10039a3b
jmp_100399c5:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_10039a3b
jmp_100399f2:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_10039a42
jmp_10039a10:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_10039a3b:
		mov eax, dword ptr [esp + 0xdc]
jmp_10039a42:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10039884
jmp_10039a4e:
		ret
jmp_10039a4f:
		mov eax, OFFSET jmp_10039956
		mov eax, OFFSET jmp_1003992b
		mov eax, OFFSET jmp_1003992b
		mov eax, OFFSET jmp_1003990d
		mov eax, OFFSET jmp_1003990d
		mov eax, OFFSET jmp_100398e0
		mov eax, OFFSET jmp_100398e0
		mov eax, OFFSET jmp_100398db
jmp_10039a77:
		mov eax, OFFSET jmp_10039a3b
		mov eax, OFFSET jmp_10039a3b
		mov eax, OFFSET jmp_10039a10
		mov eax, OFFSET jmp_10039a10
		mov eax, OFFSET jmp_100399f2
		mov eax, OFFSET jmp_100399c5
		mov eax, OFFSET jmp_100399c0
		mov eax, OFFSET jmp_100399c0
	}
}

// FUNCTION: GOLDP 0x10039aa0
__declspec(naked) void FUN_10039aa0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10039ad6:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 5
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x3e0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xa
		mov ecx, dword ptr [esp + 0xd4]
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 5
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10039ad6
		ret
	}
}

// FUNCTION: GOLDP 0x10039be0
__declspec(naked) void FUN_10039be0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_10039c16:
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 6
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x7c0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xb
		mov ecx, dword ptr [esp + 0xd4]
		shr ebp, 1
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 6
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_10039c16
		ret
	}
}

// FUNCTION: GOLDP 0x10039d20
__declspec(naked) void FUN_10039d20()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x10057a00]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_10039db5:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xa
		movq mm3, mm4
		psllq mm4, 0x2b
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 0xc
		and eax, 0xf
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10039db5
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10039e50
__declspec(naked) void FUN_10039e50()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x100579f8]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_10039ee5:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xb
		movq mm3, mm4
		psllq mm4, 0x2a
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 0xc
		and eax, 0xf
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_10039ee5
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x10039f80
__declspec(naked) void FUN_10039f80()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0xf0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_10039fea
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		je jmp_10039fd3
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi - 2], bx
jmp_10039fd3:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0xf0000
		js jmp_1003a103
jmp_10039fea:
		dec ecx
		js jmp_1003a0d6
jmp_10039ff1:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov al, byte ptr [eax]
		add edx, ebx
		and eax, 0xff
		mov bl, byte ptr [esi]
		mov esi, dword ptr [esp + 0x124]
		je jmp_1003a0a9
		and ebx, 0xff
		je jmp_1003a085
		mov ax, word ptr [esi + eax*2]
		lea edi, [edi + 4]
		shl eax, 0x10
		sub ecx, 2
		mov ax, word ptr [esi + ebx*2]
		mov ebx, 0xf0000
		mov dword ptr [edi - 4], eax
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10039ff1
		jmp jmp_1003a0d3
jmp_1003a085:
		mov ax, word ptr [esi + eax*2]
		mov ebx, 0xf0000
		mov word ptr [edi + 2], ax
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10039ff1
		jmp jmp_1003a0d3
jmp_1003a0a9:
		and ebx, 0xff
		lea edi, [edi + 4]
		mov eax, ebp
		je jmp_1003a0be
		mov bx, word ptr [esi + ebx*2]
		mov word ptr [edi - 4], bx
jmp_1003a0be:
		sub ecx, 2
		mov ebx, 0xf0000
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_10039ff1
jmp_1003a0d3:
		inc ecx
		jne jmp_1003a103
jmp_1003a0d6:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		je jmp_1003a103
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_1003a103:
		ret
	}
}

// FUNCTION: GOLDP 0x1003a110
__declspec(naked) void FUN_1003a110()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0xf0000
		je jmp_1003a178
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov eax, dword ptr [esp + 0xcc]
		mov word ptr [edi - 2], bx
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0xf0000
		js jmp_1003a231
jmp_1003a178:
		dec ecx
		js jmp_1003a20d
jmp_1003a17f:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		add eax, esi
		mov esi, dword ptr [esp + 0xc8]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, esi
		add edx, ebx
		mov esi, ebp
		mov ebx, 0xf0000
		shr esi, 0x10
		and ebx, edx
		shr ebx, 0xc
		and esi, 0xf
		or ebx, esi
		mov esi, dword ptr [esp + 0x13c]
		add ebx, esi
		mov al, byte ptr [eax]
		and eax, 0xff
		mov esi, dword ptr [esp + 0xc8]
		mov bl, byte ptr [ebx]
		add ebp, esi
		and ebx, 0xff
		mov esi, dword ptr [esp + 0x124]
		add edx, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx*2]
		shl ebx, 0x10
		mov bx, word ptr [esi + eax*2]
		sub ecx, 2
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		mov ebx, 0xf0000
		jns jmp_1003a17f
		inc ecx
		jne jmp_1003a231
jmp_1003a20d:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xf
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_1003a231:
		ret
	}
}

// FUNCTION: GOLDP 0x1003a240
__declspec(naked) void FUN_1003a240()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0xf0000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_1003a2a0
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		add edi, 2
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_1003a289
		mov word ptr [edi - 2], bx
jmp_1003a289:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0xf0000
		js jmp_1003a3a1
jmp_1003a2a0:
		dec ecx
		js jmp_1003a377
jmp_1003a2a7:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1e
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov ax, word ptr [eax]
		add edx, ebx
		and eax, 0xffff
		mov bx, word ptr [esi]
		je jmp_1003a34f
		and ebx, 0xffff
		je jmp_1003a32f
		shl eax, 0x10
		mov esi, dword ptr [esp + 0x13c]
		or eax, ebx
		mov ebx, 0xf0000
		mov dword ptr [edi], eax
		sub ecx, 2
		lea edi, [edi + 4]
		mov eax, ebp
		jns jmp_1003a2a7
		jmp jmp_1003a374
jmp_1003a32f:
		mov word ptr [edi + 2], ax
		mov ebx, 0xf0000
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_1003a2a7
		jmp jmp_1003a374
jmp_1003a34f:
		and ebx, 0xffff
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		je jmp_1003a363
		mov word ptr [edi], bx
jmp_1003a363:
		sub ecx, 2
		lea edi, [edi + 4]
		mov ebx, 0xf0000
		jns jmp_1003a2a7
jmp_1003a374:
		inc ecx
		jne jmp_1003a3a1
jmp_1003a377:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1e
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_1003a3a1
		mov word ptr [edi], bx
jmp_1003a3a1:
		ret
	}
}

// FUNCTION: GOLDP 0x1003a3b0
__declspec(naked) void FUN_1003a3b0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0xf0000
		je jmp_1003a407
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1e
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx]
		add edx, eax
		mov word ptr [edi], bx
		add edi, 2
		dec ecx
		mov eax, ebp
		mov ebx, 0xf0000
		js jmp_1003a492
jmp_1003a407:
		dec ecx
		js jmp_1003a47e
jmp_1003a40a:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1e
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0xf0000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1e
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [ebx]
		add edx, eax
		shl ebx, 0x10
		sub ecx, 2
		mov bx, word ptr [esi]
		mov eax, ebp
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, 0xf0000
		jns jmp_1003a40a
		inc ecx
		jne jmp_1003a492
jmp_1003a47e:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xb
		and eax, 0x1e
		or ebx, eax
		mov bx, word ptr [esi + ebx]
		mov word ptr [edi], bx
jmp_1003a492:
		ret
	}
}

// FUNCTION: GOLDP 0x1003a4a0
__declspec(naked) void FUN_1003a4a0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_1003a4cc:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1c
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_1003a5a1 + 1]
jmp_1003a523:
		mov word ptr [edi], ax
		jmp jmp_1003a596
jmp_1003a528:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003a596
jmp_1003a555:
		mov bx, word ptr [edi]
		and eax, 0x7bde
		and ebx, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_1003a596
jmp_1003a56c:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov bx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003a596:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003a4cc
		ret
jmp_1003a5a1:
		mov eax, OFFSET jmp_1003a596
		mov eax, OFFSET jmp_1003a56c
		mov eax, OFFSET jmp_1003a555
		mov eax, OFFSET jmp_1003a528
		mov eax, OFFSET jmp_1003a523
	}
}

// FUNCTION: GOLDP 0x1003a5c0
__declspec(naked) void FUN_1003a5c0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov eax, dword ptr [esp + 0x158]
		mov ebx, dword ptr [esp + 4]
		mov esi, dword ptr [esp + 0x74]
		shr ebx, 0xc
		lea eax, [eax + eax*8]
		and ebx, 0xfff0
		add edx, eax
		mov ebp, dword ptr [esp + 0x70]
		add edx, ebx
		and edx, 0xff
jmp_1003a5ec:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0xe
		and ebx, esi
		shr ebx, 0xb
		and eax, 0x1c
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		add esi, eax
		xor eax, eax
		mov al, byte ptr [edx + g_unk0x10057b58]
		mov ebx, dword ptr [ebx]
		inc edx
		add ebx, eax
		mov eax, ebx
		and ebx, 0xffff
		shr ebx, 8
		and edx, 0xff
		shr eax, 0x10
		jmp dword ptr [ebx + ebx*4 + jmp_1003a6c1 + 1]
jmp_1003a643:
		mov word ptr [edi], ax
		jmp jmp_1003a6b6
jmp_1003a648:
		mov dword ptr [esp + 0x164], edx
		mov ebx, eax
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003a6b6
jmp_1003a675:
		mov bx, word ptr [edi]
		and eax, 0xf7de
		and ebx, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov word ptr [edi], bx
		jmp jmp_1003a6b6
jmp_1003a68c:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov bx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, ebx
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003a6b6:
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003a5ec
		ret
jmp_1003a6c1:
		mov eax, OFFSET jmp_1003a6b6
		mov eax, OFFSET jmp_1003a68c
		mov eax, OFFSET jmp_1003a675
		mov eax, OFFSET jmp_1003a648
		mov eax, OFFSET jmp_1003a643
	}
}

// FUNCTION: GOLDP 0x1003a6e0
__declspec(naked) void FUN_1003a6e0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_1003a7f3
jmp_1003a714:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003a8d3 + 1]
jmp_1003a765:
		mov word ptr [edi], bx
		jmp jmp_1003a7e0
jmp_1003a76a:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003a7e0
jmp_1003a797:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003a7e7
jmp_1003a7b5:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003a7e0:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003a7e7:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_1003a8d2
jmp_1003a7f3:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003a8fb + 1]
jmp_1003a844:
		mov word ptr [edi], bx
		jmp jmp_1003a8bf
jmp_1003a849:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003a8bf
jmp_1003a876:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003a8c6
jmp_1003a894:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003a8bf:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003a8c6:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003a714
jmp_1003a8d2:
		ret
jmp_1003a8d3:
		mov eax, OFFSET jmp_1003a7e0
		mov eax, OFFSET jmp_1003a7b5
		mov eax, OFFSET jmp_1003a7b5
		mov eax, OFFSET jmp_1003a797
		mov eax, OFFSET jmp_1003a797
		mov eax, OFFSET jmp_1003a76a
		mov eax, OFFSET jmp_1003a76a
		mov eax, OFFSET jmp_1003a765
jmp_1003a8fb:
		mov eax, OFFSET jmp_1003a8bf
		mov eax, OFFSET jmp_1003a8bf
		mov eax, OFFSET jmp_1003a894
		mov eax, OFFSET jmp_1003a894
		mov eax, OFFSET jmp_1003a876
		mov eax, OFFSET jmp_1003a849
		mov eax, OFFSET jmp_1003a844
		mov eax, OFFSET jmp_1003a844
	}
}

// FUNCTION: GOLDP 0x1003a930
__declspec(naked) void FUN_1003a930()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_1003aa43
jmp_1003a964:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003ab23 + 1]
jmp_1003a9b5:
		mov word ptr [edi], bx
		jmp jmp_1003aa30
jmp_1003a9ba:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003aa30
jmp_1003a9e7:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003aa37
jmp_1003aa05:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003aa30:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003aa37:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_1003ab22
jmp_1003aa43:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003ab4b + 1]
jmp_1003aa94:
		mov word ptr [edi], bx
		jmp jmp_1003ab0f
jmp_1003aa99:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003ab0f
jmp_1003aac6:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003ab16
jmp_1003aae4:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003ab0f:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003ab16:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003a964
jmp_1003ab22:
		ret
jmp_1003ab23:
		mov eax, OFFSET jmp_1003aa30
		mov eax, OFFSET jmp_1003aa05
		mov eax, OFFSET jmp_1003aa05
		mov eax, OFFSET jmp_1003a9e7
		mov eax, OFFSET jmp_1003a9e7
		mov eax, OFFSET jmp_1003a9ba
		mov eax, OFFSET jmp_1003a9ba
		mov eax, OFFSET jmp_1003a9b5
jmp_1003ab4b:
		mov eax, OFFSET jmp_1003ab0f
		mov eax, OFFSET jmp_1003ab0f
		mov eax, OFFSET jmp_1003aae4
		mov eax, OFFSET jmp_1003aae4
		mov eax, OFFSET jmp_1003aac6
		mov eax, OFFSET jmp_1003aa99
		mov eax, OFFSET jmp_1003aa94
		mov eax, OFFSET jmp_1003aa94
	}
}

// FUNCTION: GOLDP 0x1003ab80
__declspec(naked) void FUN_1003ab80()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_1003ac99
jmp_1003abb4:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_1003ac86
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003ad7f + 1]
jmp_1003ac0b:
		mov word ptr [edi], bx
		jmp jmp_1003ac86
jmp_1003ac10:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003ac86
jmp_1003ac3d:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003ac8d
jmp_1003ac5b:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003ac86:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003ac8d:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_1003ad7e
jmp_1003ac99:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_1003ad6b
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003ada7 + 1]
jmp_1003acf0:
		mov word ptr [edi], bx
		jmp jmp_1003ad6b
jmp_1003acf5:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0x739c
		shr eax, 2
		and edx, 0x739c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003ad6b
jmp_1003ad22:
		mov ax, word ptr [edi]
		and ebx, 0x7bde
		and eax, 0x7bde
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003ad72
jmp_1003ad40:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0x739c
		mov ax, word ptr [edi]
		and ebx, 0x739c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003ad6b:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003ad72:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003abb4
jmp_1003ad7e:
		ret
jmp_1003ad7f:
		mov eax, OFFSET jmp_1003ac86
		mov eax, OFFSET jmp_1003ac5b
		mov eax, OFFSET jmp_1003ac5b
		mov eax, OFFSET jmp_1003ac3d
		mov eax, OFFSET jmp_1003ac3d
		mov eax, OFFSET jmp_1003ac10
		mov eax, OFFSET jmp_1003ac10
		mov eax, OFFSET jmp_1003ac0b
jmp_1003ada7:
		mov eax, OFFSET jmp_1003ad6b
		mov eax, OFFSET jmp_1003ad6b
		mov eax, OFFSET jmp_1003ad40
		mov eax, OFFSET jmp_1003ad40
		mov eax, OFFSET jmp_1003ad22
		mov eax, OFFSET jmp_1003acf5
		mov eax, OFFSET jmp_1003acf0
		mov eax, OFFSET jmp_1003acf0
	}
}

// FUNCTION: GOLDP 0x1003add0
__declspec(naked) void FUN_1003add0()
{
	__asm {
		mov eax, dword ptr [esp + 4]
		lea edi, [ebx + edx*2]
		shr eax, 0x10
		mov ebx, dword ptr [esp + 0x158]
		mov esi, dword ptr [esp + 0x74]
		xor eax, edx
		mov ebp, dword ptr [esp + 0x70]
		xor eax, ebx
		mov edx, dword ptr [esp + 0x84]
		and eax, 1
		mov dword ptr [esp + 0x160], ecx
		jne jmp_1003aee9
jmp_1003ae04:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_1003aed6
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003afcf + 1]
jmp_1003ae5b:
		mov word ptr [edi], bx
		jmp jmp_1003aed6
jmp_1003ae60:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003aed6
jmp_1003ae8d:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003aedd
jmp_1003aeab:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003aed6:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003aedd:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		js jmp_1003afce
jmp_1003aee9:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, esi
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bl, byte ptr [ebx]
		add esi, eax
		and ebx, 0xff
		mov eax, dword ptr [esp + 0x124]
		add ebx, ebx
		je jmp_1003afbb
		add ebx, eax
		mov eax, edx
		shr eax, 0x15
		mov bx, word ptr [ebx]
		jmp dword ptr [eax + eax*4 + jmp_1003aff7 + 1]
jmp_1003af40:
		mov word ptr [edi], bx
		jmp jmp_1003afbb
jmp_1003af45:
		mov dword ptr [esp + 0x164], edx
		mov eax, ebx
		mov dx, word ptr [edi]
		and eax, 0xe79c
		shr eax, 2
		and edx, 0xe79c
		shr edx, 2
		sub ebx, eax
		add ebx, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], bx
		jmp jmp_1003afbb
jmp_1003af72:
		mov ax, word ptr [edi]
		and ebx, 0xf7de
		and eax, 0xf7de
		add ebx, eax
		shr ebx, 1
		mov eax, dword ptr [esp + 0xdc]
		mov word ptr [edi], bx
		jmp jmp_1003afc2
jmp_1003af90:
		mov dword ptr [esp + 0x164], edx
		mov edx, 0xe79c
		mov ax, word ptr [edi]
		and ebx, 0xe79c
		shr ebx, 2
		and edx, eax
		shr edx, 2
		add eax, ebx
		sub eax, edx
		mov edx, dword ptr [esp + 0x164]
		mov word ptr [edi], ax
jmp_1003afbb:
		mov eax, dword ptr [esp + 0xdc]
jmp_1003afc2:
		add edx, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003ae04
jmp_1003afce:
		ret
jmp_1003afcf:
		mov eax, OFFSET jmp_1003aed6
		mov eax, OFFSET jmp_1003aeab
		mov eax, OFFSET jmp_1003aeab
		mov eax, OFFSET jmp_1003ae8d
		mov eax, OFFSET jmp_1003ae8d
		mov eax, OFFSET jmp_1003ae60
		mov eax, OFFSET jmp_1003ae60
		mov eax, OFFSET jmp_1003ae5b
jmp_1003aff7:
		mov eax, OFFSET jmp_1003afbb
		mov eax, OFFSET jmp_1003afbb
		mov eax, OFFSET jmp_1003af90
		mov eax, OFFSET jmp_1003af90
		mov eax, OFFSET jmp_1003af72
		mov eax, OFFSET jmp_1003af45
		mov eax, OFFSET jmp_1003af40
		mov eax, OFFSET jmp_1003af40
	}
}

// FUNCTION: GOLDP 0x1003b020
__declspec(naked) void FUN_1003b020()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_1003b056:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 5
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x3e0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xa
		mov ecx, dword ptr [esp + 0xd4]
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 5
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_1003b056
		ret
	}
}

// FUNCTION: GOLDP 0x1003b160
__declspec(naked) void FUN_1003b160()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov dword ptr [esp + 0x160], ecx
		mov eax, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x78]
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebx
		mov dword ptr [esp + 0x16c], edx
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
jmp_1003b196:
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, edx
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xcc]
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		xor eax, eax
		add ebp, esi
		mov esi, dword ptr [esp + 0x124]
		mov al, byte ptr [ebx]
		add edx, ecx
		mov dword ptr [esp + 0x170], ebp
		mov dword ptr [esp + 0x174], edx
		mov ecx, dword ptr [esp + 0x164]
		mov edx, dword ptr [esp + 0xd8]
		mov ax, word ptr [esi + eax*2]
		mov ebp, ecx
		shr ecx, 0x13
		mov ebx, eax
		shr eax, 6
		add ebp, edx
		mov dword ptr [esp + 0x164], ebp
		and eax, 0x3e0
		mov edx, dword ptr [esp + 0x16c]
		or eax, ecx
		mov esi, dword ptr [esp + 0xd0]
		mov ecx, edx
		mov ebp, ebx
		and ebx, 0x1f
		shr edx, 0x13
		add ecx, esi
		shl ebx, 5
		and ebp, 0x7c0
		or ebx, edx
		mov edx, dword ptr [esp + 0x168]
		mov al, byte ptr [eax + g_unk0x10057c58]
		mov dword ptr [esp + 0x16c], ecx
		shl eax, 0xb
		mov ecx, dword ptr [esp + 0xd4]
		shr ebp, 1
		mov esi, edx
		shr edx, 0x13
		mov al, byte ptr [ebx + g_unk0x10057c58]
		or ebp, edx
		add esi, ecx
		xor edx, edx
		mov dword ptr [esp + 0x168], esi
		mov dl, byte ptr [ebp + g_unk0x10057c58]
		mov ecx, dword ptr [esp + 0x160]
		shl edx, 6
		mov ebp, dword ptr [esp + 0x170]
		or eax, edx
		mov edx, dword ptr [esp + 0x174]
		mov word ptr [edi], ax
		dec ecx
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x160], ecx
		jns jmp_1003b196
		ret
	}
}

// FUNCTION: GOLDP 0x1003b2a0
__declspec(naked) void FUN_1003b2a0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x10057a00]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_1003b335:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xa
		movq mm3, mm4
		psllq mm4, 0x2b
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 0xd
		and eax, 7
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003b335
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x1003b3d0
__declspec(naked) void FUN_1003b3d0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov esi, dword ptr [esp + 0x13c]
		movq mm4, qword ptr [g_unk0x100579e0]
		movq mm0, qword ptr [esp + 0x78]
		movq mm2, qword ptr [esp + 0x80]
		pand mm0, mm4
		movq mm1, qword ptr [esp + 0xd0]
		psllq mm0, 8
		movq mm3, qword ptr [esp + 0xd8]
		pand mm2, mm4
		movq mm7, qword ptr [g_unk0x100579f8]
		psrlq mm2, 8
		pand mm1, mm4
		por mm0, mm2
		pand mm3, mm4
		psllq mm1, 8
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlq mm3, 8
		movq mm5, qword ptr [g_unk0x100579f0]
		pxor mm0, mm6
		por mm1, mm3
		mov ebp, dword ptr [esp + 0x70]
		mov edx, dword ptr [esp + 0x74]
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		xor eax, eax
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		pxor mm6, mm0
		paddsw mm0, mm1
jmp_1003b465:
		mov al, byte ptr [ebx]
		mov ebx, dword ptr [esp + 0x124]
		add ebp, esi
		mov esi, dword ptr [esp + 0xcc]
		mov ax, word ptr [ebx + eax*2]
		add edx, esi
		movd mm2, eax
		movq mm4, mm2
		psrlq mm2, 0xb
		movq mm3, mm4
		psllq mm4, 0x2a
		psllq mm3, 0x10
		por mm4, mm2
		psrlw mm6, 6
		por mm3, mm4
		pand mm3, mm5
		pmullw mm3, mm6
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, edx
		movq mm6, qword ptr [g_unk0x100579e8]
		psrlw mm3, 0xa
		pmaddwd mm3, mm7
		shr ebx, 0xd
		and eax, 7
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		movq mm2, mm3
		psrlq mm3, 0x20
		por mm2, mm3
		pxor mm6, mm0
		add ebx, esi
		mov esi, dword ptr [esp + 0xc8]
		movd eax, mm2
		paddsw mm0, mm1
		mov word ptr [edi], ax
		xor eax, eax
		dec ecx
		lea edi, [edi + 2]
		jns jmp_1003b465
		emms
		ret
	}
}

// FUNCTION: GOLDP 0x1003b500
__declspec(naked) void FUN_1003b500()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0x70000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_1003b56a
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		je jmp_1003b553
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi - 2], bx
jmp_1003b553:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x70000
		js jmp_1003b683
jmp_1003b56a:
		dec ecx
		js jmp_1003b656
jmp_1003b571:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov al, byte ptr [eax]
		add edx, ebx
		and eax, 0xff
		mov bl, byte ptr [esi]
		mov esi, dword ptr [esp + 0x124]
		je jmp_1003b629
		and ebx, 0xff
		je jmp_1003b605
		mov ax, word ptr [esi + eax*2]
		lea edi, [edi + 4]
		shl eax, 0x10
		sub ecx, 2
		mov ax, word ptr [esi + ebx*2]
		mov ebx, 0x70000
		mov dword ptr [edi - 4], eax
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_1003b571
		jmp jmp_1003b653
jmp_1003b605:
		mov ax, word ptr [esi + eax*2]
		mov ebx, 0x70000
		mov word ptr [edi + 2], ax
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_1003b571
		jmp jmp_1003b653
jmp_1003b629:
		and ebx, 0xff
		lea edi, [edi + 4]
		mov eax, ebp
		je jmp_1003b63e
		mov bx, word ptr [esi + ebx*2]
		mov word ptr [edi - 4], bx
jmp_1003b63e:
		sub ecx, 2
		mov ebx, 0x70000
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_1003b571
jmp_1003b653:
		inc ecx
		jne jmp_1003b683
jmp_1003b656:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		je jmp_1003b683
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_1003b683:
		ret
	}
}

// FUNCTION: GOLDP 0x1003b690
__declspec(naked) void FUN_1003b690()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x70000
		je jmp_1003b6f8
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		add edi, 2
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov eax, dword ptr [esp + 0xcc]
		mov word ptr [edi - 2], bx
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x70000
		js jmp_1003b7b1
jmp_1003b6f8:
		dec ecx
		js jmp_1003b78d
jmp_1003b6ff:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		add eax, esi
		mov esi, dword ptr [esp + 0xc8]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, esi
		add edx, ebx
		mov esi, ebp
		mov ebx, 0x70000
		shr esi, 0x10
		and ebx, edx
		shr ebx, 0xd
		and esi, 7
		or ebx, esi
		mov esi, dword ptr [esp + 0x13c]
		add ebx, esi
		mov al, byte ptr [eax]
		and eax, 0xff
		mov esi, dword ptr [esp + 0xc8]
		mov bl, byte ptr [ebx]
		add ebp, esi
		and ebx, 0xff
		mov esi, dword ptr [esp + 0x124]
		add edx, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx*2]
		shl ebx, 0x10
		mov bx, word ptr [esi + eax*2]
		sub ecx, 2
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		mov ebx, 0x70000
		jns jmp_1003b6ff
		inc ecx
		jne jmp_1003b7b1
jmp_1003b78d:
		shr eax, 0x10
		and ebx, edx
		shr ebx, 0xd
		and eax, 7
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bl, byte ptr [esi + ebx]
		and ebx, 0xff
		mov bx, word ptr [eax + ebx*2]
		mov word ptr [edi], bx
jmp_1003b7b1:
		ret
	}
}

// FUNCTION: GOLDP 0x1003b7c0
__declspec(naked) void FUN_1003b7c0()
{
	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov eax, edi
		mov edx, dword ptr [esp + 0x74]
		and eax, 2
		mov ebx, 0x70000
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		je jmp_1003b820
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		add edi, 2
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_1003b809
		mov word ptr [edi - 2], bx
jmp_1003b809:
		mov eax, dword ptr [esp + 0xcc]
		add edx, eax
		dec ecx
		mov eax, ebp
		mov ebx, 0x70000
		js jmp_1003b921
jmp_1003b820:
		dec ecx
		js jmp_1003b8f7
jmp_1003b827:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add eax, ebx
		mov ebx, dword ptr [esp + 0xc8]
		add ebp, ebx
		mov ebx, dword ptr [esp + 0xcc]
		mov ax, word ptr [eax]
		add edx, ebx
		and eax, 0xffff
		mov bx, word ptr [esi]
		je jmp_1003b8cf
		and ebx, 0xffff
		je jmp_1003b8af
		shl eax, 0x10
		mov esi, dword ptr [esp + 0x13c]
		or eax, ebx
		mov ebx, 0x70000
		mov dword ptr [edi], eax
		sub ecx, 2
		lea edi, [edi + 4]
		mov eax, ebp
		jns jmp_1003b827
		jmp jmp_1003b8f4
jmp_1003b8af:
		mov word ptr [edi + 2], ax
		mov ebx, 0x70000
		add edi, 4
		sub ecx, 2
		mov eax, ebp
		mov esi, dword ptr [esp + 0x13c]
		jns jmp_1003b827
		jmp jmp_1003b8f4
jmp_1003b8cf:
		and ebx, 0xffff
		mov esi, dword ptr [esp + 0x13c]
		mov eax, ebp
		je jmp_1003b8e3
		mov word ptr [edi], bx
jmp_1003b8e3:
		sub ecx, 2
		lea edi, [edi + 4]
		mov ebx, 0x70000
		jns jmp_1003b827
jmp_1003b8f4:
		inc ecx
		jne jmp_1003b921
jmp_1003b8f7:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		mov esi, dword ptr [esp + 0x13c]
		or ebx, eax
		mov eax, dword ptr [esp + 0x124]
		mov bx, word ptr [esi + ebx]
		and ebx, 0xffff
		je jmp_1003b921
		mov word ptr [edi], bx
jmp_1003b921:
		ret
	}
}

// FUNCTION: GOLDP 0x1003b930
__declspec(naked) void FUN_1003b930()
{
	/*
	This function does not really fit any known calling convention; see also the invocation sites in `FUN_1003ba30`.
	It gets passed arguments in ebx, ecx, and edx, the stack cleanup is (technically) done by the caller.
	Both this and the calling function share a sizable fraction of the present stack (at least 320 bytes),
	but the stack looks more like shared memory than a proper function call.
	We are still investigating more niche calling conventions like `watcall`, but it may be possible
	that this was actually hand-written assembly with a custom calling convention.
	*/

	__asm {
		lea edi, [ebx + edx*2]
		mov ebp, dword ptr [esp + 0x70]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, edi
		mov edx, dword ptr [esp + 0x74]
		and ebx, 2
		mov eax, ebp
		mov ebx, 0x70000
		je jmp_1003b987
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [esi + ebx]
		add edx, eax
		mov word ptr [edi], bx
		add edi, 2
		dec ecx
		mov eax, ebp
		mov ebx, 0x70000
		js jmp_1003ba12
jmp_1003b987:
		dec ecx
		js jmp_1003b9fe
jmp_1003b98a:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		add esi, ebx
		mov ebx, dword ptr [esp + 0xcc]
		add ebp, eax
		add edx, ebx
		mov eax, ebp
		mov ebx, 0x70000
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov eax, dword ptr [esp + 0x13c]
		add ebx, eax
		mov eax, dword ptr [esp + 0xc8]
		add ebp, eax
		mov eax, dword ptr [esp + 0xcc]
		mov bx, word ptr [ebx]
		add edx, eax
		shl ebx, 0x10
		sub ecx, 2
		mov bx, word ptr [esi]
		mov eax, ebp
		mov dword ptr [edi], ebx
		lea edi, [edi + 4]
		mov esi, dword ptr [esp + 0x13c]
		mov ebx, 0x70000
		jns jmp_1003b98a
		inc ecx
		jne jmp_1003ba12
jmp_1003b9fe:
		shr eax, 0xf
		and ebx, edx
		shr ebx, 0xc
		and eax, 0xe
		or ebx, eax
		mov bx, word ptr [esi + ebx]
		mov word ptr [edi], bx
jmp_1003ba12:
		ret
	}
}

// FUNCTION: GOLDP 0x1003ba30
__declspec(naked) void FUN_1003ba30(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	// We are fairly certain that this was not compiled with MSVC. It is not clear if this code was written
	// using inline assembly or using a different C compiler. See also FUN_1003b930.
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp_1003ba5f
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1003ba5f:
		cmp esi, ebp
		jle jmp_1003ba6f
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_1003ba6f:
		cmp edi, ebp
		jg jmp_1003ba81
		mov ebx, dword ptr [ecx]
		jne jmp_1003ba8d
		cmp ebx, dword ptr [edx]
		je jmp_1003c761
		jg jmp_1003ba8d
jmp_1003ba81:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_1003ba8d:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_1003baac
		cmp ebx, dword ptr [eax]
		jg jmp_1003baac
		mov ebx, eax
		je jmp_1003c770
		mov eax, ecx
		mov ecx, ebx
jmp_1003baac:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_1003c761
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		mov ebp, dword ptr [ebp + 0x34]
		or ebp, ebp
		je jmp_1003c76c
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_1003bbdd
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_1003bbc5
		dec edi
jmp_1003bbc5:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_1003bbd4
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_1003bbd4:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_1003bc02
jmp_1003bbdd:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_1003bc02:
		fild dword ptr [ebp + 8]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x18]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x18]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x18]
		fxch st(2)
		fstp dword ptr [esp + 0x98]
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0xc4]
		fild dword ptr [ebp + 0xc]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x1c]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x1c]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x1c]
		fxch st(2)
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0xc8]
		mov esi, dword ptr [eax + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0x74], ebx
		mov dword ptr [esp + 0x80], ebp
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], esi
		mov esi, dword ptr [ecx + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0xac], ebp
		mov dword ptr [esp + 0xa4], edi
		mov dword ptr [esp + 0xa8], esi
		mov esi, dword ptr [edx + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0xcc], ebx
		mov dword ptr [esp + 0xd8], ebp
		mov dword ptr [esp + 0xd0], edi
		mov dword ptr [esp + 0xd4], esi
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_1003beea
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x98]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x9c]
		fxch st(1)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x98]
		fsub dword ptr [esp + 0x6c]
		fxch st(2)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x9c]
		fsub dword ptr [esp + 0x70]
		fxch st(3)
		fmul dword ptr [esp + 0x128]
		fld dword ptr [esp + 0x128]
		fmulp st(4), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x44]
		fistp dword ptr [esp + 0x40]
		fistp dword ptr [esp + 0x18]
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0xa0]
		mov edx, dword ptr [esp + 0x74]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		mov dword ptr [esp + 0x13c], ecx
		mov ebx, dword ptr [esp + 0xd0]
		mov ecx, dword ptr [esp + 0xa4]
		mov edx, dword ptr [esp + 0x78]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		mov ebx, dword ptr [esp + 0xd4]
		mov ecx, dword ptr [esp + 0xa8]
		mov edx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		fmul dword ptr [esp + 0x128]
		fxch st(5)
		fistp dword ptr [esp + 0x48]
		fistp dword ptr [esp + 0x50]
		fistp dword ptr [esp + 0x20]
		fistp dword ptr [esp + 0x4c]
		fistp dword ptr [esp + 0x1c]
		fistp dword ptr [esp + 0x24]
		mov ebx, dword ptr [esp + 0xd8]
		mov ecx, dword ptr [esp + 0xac]
		mov edx, dword ptr [esp + 0x80]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		fmul dword ptr [esp + 0x128]
		fxch st(1)
		fistp dword ptr [esp + 0x54]
		fistp dword ptr [esp + 0x28]
		jmp jmp_1003bfb7
jmp_1003beea:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fxch st(1)
		fmul dword ptr [esp + 0x124]
		fld dword ptr [esp + 0x124]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x18]
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0x74]
		sub ebx, ecx
		mov edx, dword ptr [esp + 0xd0]
		mov dword ptr [esp + 0x138], ebx
		mov esi, dword ptr [esp + 0x78]
		fild dword ptr [esp + 0x138]
		sub edx, esi
		mov ebx, dword ptr [esp + 0xd4]
		mov dword ptr [esp + 0x138], edx
		mov ecx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		sub ebx, ecx
		mov dword ptr [esp + 0x138], ebx
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x124]
		fxch st(2)
		fistp dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0xd8]
		mov ecx, dword ptr [esp + 0x80]
		fistp dword ptr [esp + 0x20]
		sub ebx, ecx
		fistp dword ptr [esp + 0x24]
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x124]
		fistp dword ptr [esp + 0x28]
jmp_1003bfb7:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x6c]
		fist dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x98]
		fist dword ptr [esp + 0x98]
		fsubp st(1), st(0)
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x70]
		fist dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x9c]
		fist dword ptr [esp + 0x9c]
		fsubp st(1), st(0)
		fxch st(3)
		fmul dword ptr [esp + 0x12c]
		fld dword ptr [esp + 0x12c]
		fmulp st(2), st(0)
		faddp st(2), st(0)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fld dword ptr [esp + 0x130]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0xc4]
		fistp dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xc4]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc4]
		sar eax, 0x10
		mov dword ptr [esp + 0xfc], ecx
		mov dword ptr [esp + 0xf8], eax
		mov ebp, dword ptr [esp + 0x18c]
		mov ecx, dword ptr [esp + 0xc8]
		mov ebp, dword ptr [ebp + 0x34]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc8]
		sar eax, 0x10
		mov ebx, dword ptr [ebp + 4]
		mov edx, dword ptr [ebp]
		mov dword ptr [esp + 0x104], ecx
		mov dword ptr [esp + 0x138], edx
		mov ecx, dword ptr [ebp + 0x14]
		mov dword ptr [esp + 0x100], eax
		mov dword ptr [esp + 0x11c], ebx
		mov dword ptr [esp + 0x118], edx
		mov dword ptr [esp + 0x120], ecx
		fild dword ptr [esp + 0x74]
		fild dword ptr [esp + 0xcc]
		fild dword ptr [esp + 0xa0]
		fild dword ptr [esp + 0xd0]
		fild dword ptr [esp + 0x78]
		fild dword ptr [esp + 0xa4]
		fxch st(5)
		fsub st(4), st(0)
		fsubrp st(3), st(0)
		fsub st(1), st(0)
		fsubrp st(4), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x12c]
		fild dword ptr [esp + 0xd4]
		fild dword ptr [esp + 0xa8]
		fild dword ptr [esp + 0x7c]
		fld dword ptr [esp + 0x12c]
		fmulp st(6), st(0)
		fsubr st(1), st(0)
		fsubp st(2), st(0)
		fxch st(5)
		faddp st(4), st(0)
		fmul dword ptr [esp + 0x12c]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x130]
		fxch st(3)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fxch st(1)
		fmul dword ptr [esp + 0x130]
		fxch st(2)
		fistp dword ptr [esp + 0xd0]
		fistp dword ptr [esp + 0xcc]
		fistp dword ptr [esp + 0xd4]
		fild dword ptr [esp + 0x80]
		fild dword ptr [esp + 0xd8]
		fsub st(0), st(1)
		fmul dword ptr [esp + 0x12c]
		faddp st(1), st(0)
		fild dword ptr [esp + 0xac]
		fsubp st(1), st(0)
		fmul dword ptr [esp + 0x130]
		fistp dword ptr [esp + 0xd8]
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		mov ebp, 0x3000
		je jmp_1003c245
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x6c]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x6c], edi
		mov eax, dword ptr [esp + 0x18]
		mov edi, dword ptr [esp + 0x70]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x70], edi
		mov eax, dword ptr [esp + 0x1c]
		mov edi, dword ptr [esp + 0x74]
		add eax, eax
		mov esi, dword ptr [esp + 0x20]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x74], edi
		mov esi, dword ptr [esp + 0x24]
		mov edi, dword ptr [esp + 0x78]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x78], edi
		mov esi, dword ptr [esp + 0x28]
		mov edi, dword ptr [esp + 0x7c]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x7c], edi
		mov edi, dword ptr [esp + 0x80]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x80], edi
		jmp jmp_1003c273
jmp_1003c245:
		mov ebx, dword ptr [esp + 0x74]
		mov ecx, dword ptr [esp + 0x7c]
		mov esi, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x80]
		add ebx, ebp
		add ecx, ebp
		mov dword ptr [esp + 0x74], ebx
		mov dword ptr [esp + 0x7c], ecx
		add esi, ebp
		add edi, ebp
		mov dword ptr [esp + 0x78], esi
		mov dword ptr [esp + 0x80], edi
jmp_1003c273:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
jmp_1003c297:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003c36c
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003c2cb
		; See the explanation in FUN_1003b930
		call ebp
jmp_1003c2cb:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x28]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003c297
jmp_1003c36c:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_1003c761
		or ebx, ebx
		je jmp_1003c5d0
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		mov ebp, 0x3000
		je jmp_1003c491
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x98]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x6c], edx
		mov eax, dword ptr [esp + 0x44]
		mov ebx, dword ptr [esp + 0x9c]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x70], edx
		mov esi, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0xa0]
		mov edi, dword ptr [esp + 0x4c]
		add ebx, ebp
		lea eax, [esi*2]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa4]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x74], edx
		add ebx, ebp
		mov edi, dword ptr [esp + 0x50]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa8]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x78], edx
		add ebx, ebp
		mov edi, dword ptr [esp + 0x54]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xac]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x7c], edx
		add ebx, ebp
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x80], edx
		jmp jmp_1003c4de
jmp_1003c491:
		mov ebx, dword ptr [esp + 0x98]
		mov ecx, dword ptr [esp + 0x9c]
		mov dword ptr [esp + 0x6c], ebx
		mov dword ptr [esp + 0x70], ecx
		mov eax, dword ptr [esp + 0xa0]
		mov ebx, dword ptr [esp + 0xa4]
		mov ecx, dword ptr [esp + 0xa8]
		add eax, ebp
		add ebx, ebp
		add ecx, ebp
		mov dword ptr [esp + 0x74], eax
		mov edx, dword ptr [esp + 0xac]
		mov dword ptr [esp + 0x78], ebx
		add edx, ebp
		mov dword ptr [esp + 0x7c], ecx
		mov dword ptr [esp + 0x80], edx
jmp_1003c4de:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_1003c4ef:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003c5cb ; this jump to a `jmp` instruction is quite untypical for hand-written assembly I think
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003c523
		call ebp
jmp_1003c523:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x44]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0x4c]
		mov ecx, dword ptr [esp + 0x50]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003c4ef
jmp_1003c5cb:
		jmp jmp_1003c761
jmp_1003c5d0:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_1003c635
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_1003c635:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003c761
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003c669
		call ebp
jmp_1003c669:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x28]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov esi, dword ptr [esp + 0x84]
		mov edi, dword ptr [esp + 0x88]
		mov ebp, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x2c]
		mov ebx, dword ptr [esp + 0x30]
		mov ecx, dword ptr [esp + 0x34]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x84], esi
		mov edx, dword ptr [esp + 0x90]
		mov ebx, dword ptr [esp + 0x38]
		mov dword ptr [esp + 0x88], edi
		add edx, ebx
		mov dword ptr [esp + 0x8c], ebp
		mov dword ptr [esp + 0x90], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003c635
jmp_1003c761:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_1003c76c:
		fstp dword ptr [esp + 4]
jmp_1003c770:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x1003c780
__declspec(naked) void FUN_1003c780(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp_1003c7af
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1003c7af:
		cmp esi, ebp
		jle jmp_1003c7bf
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_1003c7bf:
		cmp edi, ebp
		jg jmp_1003c7d1
		mov ebx, dword ptr [ecx]
		jne jmp_1003c7dd
		cmp ebx, dword ptr [edx]
		je jmp_1003cf1a
		jg jmp_1003c7dd
jmp_1003c7d1:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_1003c7dd:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_1003c7fc
		cmp ebx, dword ptr [eax]
		jg jmp_1003c7fc
		mov ebx, eax
		je jmp_1003cf29
		mov eax, ecx
		mov ecx, ebx
jmp_1003c7fc:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_1003cf1a
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		mov ebp, dword ptr [ebp + 0x34]
		or ebp, ebp
		je jmp_1003cf25
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_1003c92d
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_1003c915
		dec edi
jmp_1003c915:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_1003c924
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_1003c924:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_1003c952
jmp_1003c92d:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_1003c952:
		fild dword ptr [ebp + 8]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x18]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x18]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x18]
		fxch st(2)
		fstp dword ptr [esp + 0x98]
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0xc4]
		fild dword ptr [ebp + 0xc]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x1c]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x1c]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x1c]
		fxch st(2)
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0xc8]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_1003ca4c
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x98]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x9c]
		fxch st(1)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x98]
		fsub dword ptr [esp + 0x6c]
		fxch st(2)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x9c]
		fsub dword ptr [esp + 0x70]
		fxch st(3)
		fmul dword ptr [esp + 0x128]
		fld dword ptr [esp + 0x128]
		fmulp st(4), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x44]
		fistp dword ptr [esp + 0x40]
		fistp dword ptr [esp + 0x18]
		jmp jmp_1003ca7c
jmp_1003ca4c:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fxch st(1)
		fmul dword ptr [esp + 0x124]
		fld dword ptr [esp + 0x124]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x18]
jmp_1003ca7c:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x6c]
		fist dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x98]
		fist dword ptr [esp + 0x98]
		fsubp st(1), st(0)
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x70]
		fist dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x9c]
		fist dword ptr [esp + 0x9c]
		fsubp st(1), st(0)
		fxch st(3)
		fmul dword ptr [esp + 0x12c]
		fld dword ptr [esp + 0x12c]
		fmulp st(2), st(0)
		faddp st(2), st(0)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fld dword ptr [esp + 0x130]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0xc4]
		fistp dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xc4]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc4]
		sar eax, 0x10
		mov dword ptr [esp + 0xfc], ecx
		mov dword ptr [esp + 0xf8], eax
		mov ecx, dword ptr [esp + 0xc8]
		mov ebp, dword ptr [esp + 0x18c]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc8]
		sar eax, 0x10
		mov ebp, dword ptr [ebp + 0x34]
		mov dword ptr [esp + 0x104], ecx
		mov ecx, dword ptr [ebp + 0x14]
		mov dword ptr [esp + 0x100], eax
		mov ebx, dword ptr [ebp + 4]
		mov dword ptr [esp + 0x120], ecx
		imul ebx
		mov ecx, dword ptr [ebp]
		mov dword ptr [esp + 0x10c], eax
		add eax, ebx
		mov dword ptr [esp + 0x138], ecx
		mov dword ptr [esp + 0x108], eax
		mov dword ptr [esp + 0x11c], ebx
		mov dword ptr [esp + 0x118], ecx
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		je jmp_1003cbed
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x6c]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x6c], edi
		mov eax, dword ptr [esp + 0x18]
		mov edi, dword ptr [esp + 0x70]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x70], edi
		jmp jmp_1003cbed
jmp_1003cbed:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
jmp_1003cc11:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003cca4
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003cc41
		call ebp
jmp_1003cc41:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003cc11
jmp_1003cca4:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_1003cf1a
		or ebx, ebx
		je jmp_1003ce17
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		je jmp_1003cd4d
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x98]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x6c], edx
		mov eax, dword ptr [esp + 0x44]
		mov ebx, dword ptr [esp + 0x9c]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x70], edx
		jmp jmp_1003cd63
jmp_1003cd4d:
		mov ebx, dword ptr [esp + 0x98]
		mov ecx, dword ptr [esp + 0x9c]
		mov dword ptr [esp + 0x6c], ebx
		mov dword ptr [esp + 0x70], ecx
jmp_1003cd63:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_1003cd74:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003ce12
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003cda8
		call ebp
jmp_1003cda8:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x44]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003cd74
jmp_1003ce12:
		jmp jmp_1003cf1a
jmp_1003ce17:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_1003ce7c
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_1003ce7c:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003cf1a
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003ceb0
		call ebp
jmp_1003ceb0:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003ce7c
jmp_1003cf1a:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_1003cf25:
		fstp dword ptr [esp + 4]
jmp_1003cf29:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x1003cf40
__declspec(naked) void FUN_1003cf40(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp_1003cf6f
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1003cf6f:
		cmp esi, ebp
		jle jmp_1003cf7f
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_1003cf7f:
		cmp edi, ebp
		jg jmp_1003cf91
		mov ebx, dword ptr [ecx]
		jne jmp_1003cf9d
		cmp ebx, dword ptr [edx]
		je jmp_1003d6de
		jg jmp_1003cf9d
jmp_1003cf91:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_1003cf9d:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_1003cfbc
		cmp ebx, dword ptr [eax]
		jg jmp_1003cfbc
		mov ebx, eax
		je jmp_1003d6ed
		mov eax, ecx
		mov ecx, ebx
jmp_1003cfbc:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_1003d6de
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		mov ebp, dword ptr [ebp + 0x34]
		or ebp, ebp
		je jmp_1003d6e9
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_1003d0ed
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_1003d0d5
		dec edi
jmp_1003d0d5:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_1003d0e4
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_1003d0e4:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_1003d112
jmp_1003d0ed:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_1003d112:
		fild dword ptr [ebp + 8]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x18]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x18]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x18]
		fxch st(2)
		fstp dword ptr [esp + 0x98]
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0xc4]
		fild dword ptr [ebp + 0xc]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x1c]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x1c]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x1c]
		fxch st(2)
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0xc8]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_1003d20c
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x98]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x9c]
		fxch st(1)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x98]
		fsub dword ptr [esp + 0x6c]
		fxch st(2)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x9c]
		fsub dword ptr [esp + 0x70]
		fxch st(3)
		fmul dword ptr [esp + 0x128]
		fld dword ptr [esp + 0x128]
		fmulp st(4), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x44]
		fistp dword ptr [esp + 0x40]
		fistp dword ptr [esp + 0x18]
		jmp jmp_1003d23c
jmp_1003d20c:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fxch st(1)
		fmul dword ptr [esp + 0x124]
		fld dword ptr [esp + 0x124]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x18]
jmp_1003d23c:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x6c]
		fist dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x98]
		fist dword ptr [esp + 0x98]
		fsubp st(1), st(0)
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x70]
		fist dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x9c]
		fist dword ptr [esp + 0x9c]
		fsubp st(1), st(0)
		fxch st(3)
		fmul dword ptr [esp + 0x12c]
		fld dword ptr [esp + 0x12c]
		fmulp st(2), st(0)
		faddp st(2), st(0)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fld dword ptr [esp + 0x130]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0xc4]
		fistp dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xc4]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc4]
		sar eax, 0x10
		mov dword ptr [esp + 0xfc], ecx
		mov dword ptr [esp + 0xf8], eax
		mov ecx, dword ptr [esp + 0xc8]
		mov ebp, dword ptr [esp + 0x18c]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc8]
		sar eax, 0x10
		mov ebp, dword ptr [ebp + 0x34]
		mov dword ptr [esp + 0x104], ecx
		mov ecx, dword ptr [ebp + 0x14]
		mov dword ptr [esp + 0x100], eax
		mov ebx, dword ptr [ebp + 4]
		mov dword ptr [esp + 0x120], ecx
		sar ebx, 1
		imul ebx
		mov ecx, dword ptr [ebp]
		mov dword ptr [esp + 0x10c], eax
		add eax, ebx
		mov dword ptr [esp + 0x138], ecx
		sar ecx, 1
		mov dword ptr [esp + 0x108], eax
		mov dword ptr [esp + 0x11c], ebx
		mov dword ptr [esp + 0x118], ecx
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		je jmp_1003d3b1
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x6c]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x6c], edi
		mov eax, dword ptr [esp + 0x18]
		mov edi, dword ptr [esp + 0x70]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x70], edi
		jmp jmp_1003d3b1
jmp_1003d3b1:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
jmp_1003d3d5:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003d468
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003d405
		call ebp
jmp_1003d405:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003d3d5
jmp_1003d468:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_1003d6de
		or ebx, ebx
		je jmp_1003d5db
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		je jmp_1003d511
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x98]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x6c], edx
		mov eax, dword ptr [esp + 0x44]
		mov ebx, dword ptr [esp + 0x9c]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x70], edx
		jmp jmp_1003d527
jmp_1003d511:
		mov ebx, dword ptr [esp + 0x98]
		mov ecx, dword ptr [esp + 0x9c]
		mov dword ptr [esp + 0x6c], ebx
		mov dword ptr [esp + 0x70], ecx
jmp_1003d527:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_1003d538:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003d5d6
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003d56c
		call ebp
jmp_1003d56c:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x44]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003d538
jmp_1003d5d6:
		jmp jmp_1003d6de
jmp_1003d5db:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_1003d640
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_1003d640:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003d6de
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003d674
		call ebp
jmp_1003d674:
		mov esi, dword ptr [esp + 0x6c]
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0x6c], esi
		mov dword ptr [esp + 0x70], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003d640
jmp_1003d6de:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_1003d6e9:
		fstp dword ptr [esp + 4]
jmp_1003d6ed:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x1003d700
__declspec(naked) void FUN_1003d700(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp_1003d72f
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1003d72f:
		cmp esi, ebp
		jle jmp_1003d73f
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_1003d73f:
		cmp edi, ebp
		jg jmp_1003d751
		mov ebx, dword ptr [ecx]
		jne jmp_1003d75d
		cmp ebx, dword ptr [edx]
		je jmp_1003e56a
		jg jmp_1003d75d
jmp_1003d751:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_1003d75d:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_1003d77c
		cmp ebx, dword ptr [eax]
		jg jmp_1003d77c
		mov ebx, eax
		je jmp_1003e579
		mov eax, ecx
		mov ecx, ebx
jmp_1003d77c:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_1003e56a
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		mov ebp, dword ptr [ebp + 0x34]
		or ebp, ebp
		je jmp_1003e575
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_1003d8ad
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_1003d895
		dec edi
jmp_1003d895:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_1003d8a4
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_1003d8a4:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_1003d8d2
jmp_1003d8ad:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_1003d8d2:
		fild dword ptr [ebp + 8]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x18]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x18]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x18]
		fxch st(2)
		fstp dword ptr [esp + 0x98]
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0xc4]
		fild dword ptr [ebp + 0xc]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x1c]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x1c]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x1c]
		fxch st(2)
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0xc8]
		mov esi, dword ptr [eax + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0x74], ebx
		mov dword ptr [esp + 0x80], ebp
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], esi
		mov esi, dword ptr [ecx + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0xac], ebp
		mov dword ptr [esp + 0xa4], edi
		mov dword ptr [esp + 0xa8], esi
		mov esi, dword ptr [edx + 0x10]
		mov ebx, 0xff
		and ebx, esi
		mov edi, 0xff00
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov ebp, 0xff000000
		and ebp, esi
		and esi, 0xff0000
		shr ebp, 8
		mov dword ptr [esp + 0xcc], ebx
		mov dword ptr [esp + 0xd8], ebp
		mov dword ptr [esp + 0xd0], edi
		mov dword ptr [esp + 0xd4], esi
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_1003dbba
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x98]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x9c]
		fxch st(1)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x98]
		fsub dword ptr [esp + 0x6c]
		fxch st(2)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x9c]
		fsub dword ptr [esp + 0x70]
		fxch st(3)
		fmul dword ptr [esp + 0x128]
		fld dword ptr [esp + 0x128]
		fmulp st(4), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x44]
		fistp dword ptr [esp + 0x40]
		fistp dword ptr [esp + 0x18]
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0xa0]
		mov edx, dword ptr [esp + 0x74]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		mov dword ptr [esp + 0x13c], ecx
		mov ebx, dword ptr [esp + 0xd0]
		mov ecx, dword ptr [esp + 0xa4]
		mov edx, dword ptr [esp + 0x78]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		mov ebx, dword ptr [esp + 0xd4]
		mov ecx, dword ptr [esp + 0xa8]
		mov edx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		fmul dword ptr [esp + 0x128]
		fxch st(5)
		fistp dword ptr [esp + 0x48]
		fistp dword ptr [esp + 0x50]
		fistp dword ptr [esp + 0x20]
		fistp dword ptr [esp + 0x4c]
		fistp dword ptr [esp + 0x1c]
		fistp dword ptr [esp + 0x24]
		mov ebx, dword ptr [esp + 0xd8]
		mov ecx, dword ptr [esp + 0xac]
		mov edx, dword ptr [esp + 0x80]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		fmul dword ptr [esp + 0x128]
		fxch st(1)
		fistp dword ptr [esp + 0x54]
		fistp dword ptr [esp + 0x28]
		jmp jmp_1003dc87
jmp_1003dbba:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fxch st(1)
		fmul dword ptr [esp + 0x124]
		fld dword ptr [esp + 0x124]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x18]
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0x74]
		sub ebx, ecx
		mov edx, dword ptr [esp + 0xd0]
		mov dword ptr [esp + 0x138], ebx
		mov esi, dword ptr [esp + 0x78]
		fild dword ptr [esp + 0x138]
		sub edx, esi
		mov ebx, dword ptr [esp + 0xd4]
		mov dword ptr [esp + 0x138], edx
		mov ecx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		sub ebx, ecx
		mov dword ptr [esp + 0x138], ebx
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x124]
		fxch st(2)
		fistp dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0xd8]
		mov ecx, dword ptr [esp + 0x80]
		fistp dword ptr [esp + 0x20]
		sub ebx, ecx
		fistp dword ptr [esp + 0x24]
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x124]
		fistp dword ptr [esp + 0x28]
jmp_1003dc87:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x6c]
		fist dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x98]
		fist dword ptr [esp + 0x98]
		fsubp st(1), st(0)
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x70]
		fist dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x9c]
		fist dword ptr [esp + 0x9c]
		fsubp st(1), st(0)
		fxch st(3)
		fmul dword ptr [esp + 0x12c]
		fld dword ptr [esp + 0x12c]
		fmulp st(2), st(0)
		faddp st(2), st(0)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fld dword ptr [esp + 0x130]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0xc4]
		fistp dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xc4]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc4]
		sar eax, 0x10
		mov dword ptr [esp + 0xfc], ecx
		mov dword ptr [esp + 0xf8], eax
		mov ebp, dword ptr [esp + 0x18c]
		mov ecx, dword ptr [esp + 0xc8]
		mov ebp, dword ptr [ebp + 0x34]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc8]
		sar eax, 0x10
		mov ebx, dword ptr [ebp + 4]
		mov edx, dword ptr [ebp]
		mov dword ptr [esp + 0x104], ecx
		mov dword ptr [esp + 0x138], edx
		mov ecx, dword ptr [ebp + 0x14]
		mov dword ptr [esp + 0x100], eax
		mov dword ptr [esp + 0x11c], ebx
		mov dword ptr [esp + 0x118], edx
		mov dword ptr [esp + 0x120], ecx
		fild dword ptr [esp + 0x74]
		fild dword ptr [esp + 0xcc]
		fild dword ptr [esp + 0xa0]
		fild dword ptr [esp + 0xd0]
		fild dword ptr [esp + 0x78]
		fild dword ptr [esp + 0xa4]
		fxch st(5)
		fsub st(4), st(0)
		fsubrp st(3), st(0)
		fsub st(1), st(0)
		fsubrp st(4), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x12c]
		fild dword ptr [esp + 0xd4]
		fild dword ptr [esp + 0xa8]
		fild dword ptr [esp + 0x7c]
		fld dword ptr [esp + 0x12c]
		fmulp st(6), st(0)
		fsubr st(1), st(0)
		fsubp st(2), st(0)
		fxch st(5)
		faddp st(4), st(0)
		fmul dword ptr [esp + 0x12c]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x130]
		fxch st(3)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fxch st(1)
		fmul dword ptr [esp + 0x130]
		fxch st(2)
		fistp dword ptr [esp + 0xd0]
		fistp dword ptr [esp + 0xcc]
		fistp dword ptr [esp + 0xd4]
		fild dword ptr [esp + 0x80]
		fild dword ptr [esp + 0xd8]
		fsub st(0), st(1)
		fmul dword ptr [esp + 0x12c]
		faddp st(1), st(0)
		fild dword ptr [esp + 0xac]
		fsubp st(1), st(0)
		fmul dword ptr [esp + 0x130]
		fistp dword ptr [esp + 0xd8]
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		mov ebp, 0x3000
		je jmp_1003df15
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x6c]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x6c], edi
		mov eax, dword ptr [esp + 0x18]
		mov edi, dword ptr [esp + 0x70]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x70], edi
		mov eax, dword ptr [esp + 0x1c]
		mov edi, dword ptr [esp + 0x74]
		add eax, eax
		mov esi, dword ptr [esp + 0x20]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x74], edi
		mov esi, dword ptr [esp + 0x24]
		mov edi, dword ptr [esp + 0x78]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x78], edi
		mov esi, dword ptr [esp + 0x28]
		mov edi, dword ptr [esp + 0x7c]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x7c], edi
		mov edi, dword ptr [esp + 0x80]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x80], edi
		jmp jmp_1003df43
jmp_1003df15:
		mov ebx, dword ptr [esp + 0x74]
		mov ecx, dword ptr [esp + 0x7c]
		mov esi, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x80]
		add ebx, ebp
		add ecx, ebp
		mov dword ptr [esp + 0x74], ebx
		mov dword ptr [esp + 0x7c], ecx
		add esi, ebp
		add edi, ebp
		mov dword ptr [esp + 0x78], esi
		mov dword ptr [esp + 0x80], edi
jmp_1003df43:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
		mov edx, dword ptr [esp + 0x6c]
		mov eax, dword ptr [esp + 0x70]
		mov dword ptr [esp + 0xf0], edx
		mov dword ptr [esp + 0xf4], eax
jmp_1003df7d:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003e0af
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003e002
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003e002:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x28]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003df7d
jmp_1003e0af:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_1003e56a
		or ebx, ebx
		je jmp_1003e37c
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		mov ebp, 0x3000
		je jmp_1003e1da
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x98]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0xf0], edx
		mov eax, dword ptr [esp + 0x44]
		mov ebx, dword ptr [esp + 0x9c]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0xf4], edx
		mov esi, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0xa0]
		mov edi, dword ptr [esp + 0x4c]
		add ebx, ebp
		lea eax, [esi*2]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa4]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x74], edx
		add ebx, ebp
		mov edi, dword ptr [esp + 0x50]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa8]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x78], edx
		add ebx, ebp
		mov edi, dword ptr [esp + 0x54]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xac]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x7c], edx
		add ebx, ebp
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x80], edx
		jmp jmp_1003e22d
jmp_1003e1da:
		mov ebx, dword ptr [esp + 0x98]
		mov ecx, dword ptr [esp + 0x9c]
		mov dword ptr [esp + 0xf0], ebx
		mov dword ptr [esp + 0xf4], ecx
		mov eax, dword ptr [esp + 0xa0]
		mov ebx, dword ptr [esp + 0xa4]
		mov ecx, dword ptr [esp + 0xa8]
		add eax, ebp
		add ebx, ebp
		add ecx, ebp
		mov dword ptr [esp + 0x74], eax
		mov edx, dword ptr [esp + 0xac]
		mov dword ptr [esp + 0x78], ebx
		add edx, ebp
		mov dword ptr [esp + 0x7c], ecx
		mov dword ptr [esp + 0x80], edx
jmp_1003e22d:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_1003e23e:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003e377
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003e2c3
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003e2c3:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x44]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0x4c]
		mov ecx, dword ptr [esp + 0x50]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003e23e
jmp_1003e377:
		jmp jmp_1003e56a
jmp_1003e37c:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_1003e3e1
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_1003e3e1:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003e56a
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003e466
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003e466:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov edx, dword ptr [esp + 0x80]
		mov ebx, dword ptr [esp + 0x28]
		mov dword ptr [esp + 0x78], edi
		add edx, ebx
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], edx
		mov esi, dword ptr [esp + 0x84]
		mov edi, dword ptr [esp + 0x88]
		mov ebp, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x2c]
		mov ebx, dword ptr [esp + 0x30]
		mov ecx, dword ptr [esp + 0x34]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x84], esi
		mov edx, dword ptr [esp + 0x90]
		mov ebx, dword ptr [esp + 0x38]
		mov dword ptr [esp + 0x88], edi
		add edx, ebx
		mov dword ptr [esp + 0x8c], ebp
		mov dword ptr [esp + 0x90], edx
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003e3e1
jmp_1003e56a:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_1003e575:
		fstp dword ptr [esp + 4]
jmp_1003e579:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x1003e590
__declspec(naked) void FUN_1003e590(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp_1003e5bf
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1003e5bf:
		cmp esi, ebp
		jle jmp_1003e5cf
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_1003e5cf:
		cmp edi, ebp
		jg jmp_1003e5e1
		mov ebx, dword ptr [ecx]
		jne jmp_1003e5ed
		cmp ebx, dword ptr [edx]
		je jmp_1003ee67
		jg jmp_1003e5ed
jmp_1003e5e1:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_1003e5ed:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_1003e60c
		cmp ebx, dword ptr [eax]
		jg jmp_1003e60c
		mov ebx, eax
		je jmp_1003ee76
		mov eax, ecx
		mov ecx, ebx
jmp_1003e60c:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_1003ee67
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		mov ebp, dword ptr [ebp + 0x34]
		or ebp, ebp
		je jmp_1003ee72
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_1003e73d
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_1003e725
		dec edi
jmp_1003e725:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_1003e734
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_1003e734:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_1003e762
jmp_1003e73d:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_1003e762:
		fild dword ptr [ebp + 8]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x18]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x18]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x18]
		fxch st(2)
		fstp dword ptr [esp + 0x98]
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0xc4]
		fild dword ptr [ebp + 0xc]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x1c]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x1c]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x1c]
		fxch st(2)
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0xc8]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_1003e85c
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x98]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x9c]
		fxch st(1)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x98]
		fsub dword ptr [esp + 0x6c]
		fxch st(2)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x9c]
		fsub dword ptr [esp + 0x70]
		fxch st(3)
		fmul dword ptr [esp + 0x128]
		fld dword ptr [esp + 0x128]
		fmulp st(4), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x44]
		fistp dword ptr [esp + 0x40]
		fistp dword ptr [esp + 0x18]
		jmp jmp_1003e88c
jmp_1003e85c:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fxch st(1)
		fmul dword ptr [esp + 0x124]
		fld dword ptr [esp + 0x124]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x18]
jmp_1003e88c:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x6c]
		fist dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x98]
		fist dword ptr [esp + 0x98]
		fsubp st(1), st(0)
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x70]
		fist dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x9c]
		fist dword ptr [esp + 0x9c]
		fsubp st(1), st(0)
		fxch st(3)
		fmul dword ptr [esp + 0x12c]
		fld dword ptr [esp + 0x12c]
		fmulp st(2), st(0)
		faddp st(2), st(0)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fld dword ptr [esp + 0x130]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0xc4]
		fistp dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xc4]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc4]
		sar eax, 0x10
		mov dword ptr [esp + 0xfc], ecx
		mov dword ptr [esp + 0xf8], eax
		mov ecx, dword ptr [esp + 0xc8]
		mov ebp, dword ptr [esp + 0x18c]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc8]
		sar eax, 0x10
		mov ebp, dword ptr [ebp + 0x34]
		mov dword ptr [esp + 0x104], ecx
		mov ecx, dword ptr [ebp + 0x14]
		mov dword ptr [esp + 0x100], eax
		mov ebx, dword ptr [ebp + 4]
		mov dword ptr [esp + 0x120], ecx
		imul ebx
		mov ecx, dword ptr [ebp]
		mov dword ptr [esp + 0x10c], eax
		add eax, ebx
		mov dword ptr [esp + 0x138], ecx
		mov dword ptr [esp + 0x108], eax
		mov dword ptr [esp + 0x11c], ebx
		mov dword ptr [esp + 0x118], ecx
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		je jmp_1003e9fd
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x6c]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x6c], edi
		mov eax, dword ptr [esp + 0x18]
		mov edi, dword ptr [esp + 0x70]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x70], edi
		jmp jmp_1003e9fd
jmp_1003e9fd:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
		mov edx, dword ptr [esp + 0x6c]
		mov eax, dword ptr [esp + 0x70]
		mov dword ptr [esp + 0xf0], edx
		mov dword ptr [esp + 0xf4], eax
jmp_1003ea37:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003eb2b
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003eabc
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003eabc:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003ea37
jmp_1003eb2b:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_1003ee67
		or ebx, ebx
		je jmp_1003ed07
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		je jmp_1003ebda
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x98]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0xf0], edx
		mov eax, dword ptr [esp + 0x44]
		mov ebx, dword ptr [esp + 0x9c]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0xf4], edx
		jmp jmp_1003ebf6
jmp_1003ebda:
		mov ebx, dword ptr [esp + 0x98]
		mov ecx, dword ptr [esp + 0x9c]
		mov dword ptr [esp + 0xf0], ebx
		mov dword ptr [esp + 0xf4], ecx
jmp_1003ebf6:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_1003ec07:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003ed02
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003ec8c
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003ec8c:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x44]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003ec07
jmp_1003ed02:
		jmp jmp_1003ee67
jmp_1003ed07:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_1003ed6c
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_1003ed6c:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003ee67
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003edf1
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003edf1:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003ed6c
jmp_1003ee67:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_1003ee72:
		fstp dword ptr [esp + 4]
jmp_1003ee76:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x1003ee90
__declspec(naked) void FUN_1003ee90(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp_1003eebf
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1003eebf:
		cmp esi, ebp
		jle jmp_1003eecf
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_1003eecf:
		cmp edi, ebp
		jg jmp_1003eee1
		mov ebx, dword ptr [ecx]
		jne jmp_1003eeed
		cmp ebx, dword ptr [edx]
		je jmp_1003f76b
		jg jmp_1003eeed
jmp_1003eee1:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_1003eeed:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_1003ef0c
		cmp ebx, dword ptr [eax]
		jg jmp_1003ef0c
		mov ebx, eax
		je jmp_1003f77a
		mov eax, ecx
		mov ecx, ebx
jmp_1003ef0c:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_1003f76b
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		mov ebp, dword ptr [ebp + 0x34]
		or ebp, ebp
		je jmp_1003f776
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_1003f03d
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_1003f025
		dec edi
jmp_1003f025:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_1003f034
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_1003f034:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_1003f062
jmp_1003f03d:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_1003f062:
		fild dword ptr [ebp + 8]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x18]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x18]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x18]
		fxch st(2)
		fstp dword ptr [esp + 0x98]
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0xc4]
		fild dword ptr [ebp + 0xc]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [eax + 0x1c]
		fmul st(0), st(1)
		fld dword ptr [ecx + 0x1c]
		fmul st(0), st(2)
		fxch st(2)
		fmul dword ptr [edx + 0x1c]
		fxch st(2)
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0xc8]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_1003f15c
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x98]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x9c]
		fxch st(1)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x98]
		fsub dword ptr [esp + 0x6c]
		fxch st(2)
		fmul dword ptr [esp + 0x134]
		fld dword ptr [esp + 0x9c]
		fsub dword ptr [esp + 0x70]
		fxch st(3)
		fmul dword ptr [esp + 0x128]
		fld dword ptr [esp + 0x128]
		fmulp st(4), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x44]
		fistp dword ptr [esp + 0x40]
		fistp dword ptr [esp + 0x18]
		jmp jmp_1003f18c
jmp_1003f15c:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fxch st(1)
		fmul dword ptr [esp + 0x124]
		fld dword ptr [esp + 0x124]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x14]
		fistp dword ptr [esp + 0x18]
jmp_1003f18c:
		fld dword ptr [esp + 0xc4]
		fsub dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x6c]
		fist dword ptr [esp + 0x6c]
		fld dword ptr [esp + 0x98]
		fist dword ptr [esp + 0x98]
		fsubp st(1), st(0)
		fld dword ptr [esp + 0xc8]
		fsub dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x70]
		fist dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x9c]
		fist dword ptr [esp + 0x9c]
		fsubp st(1), st(0)
		fxch st(3)
		fmul dword ptr [esp + 0x12c]
		fld dword ptr [esp + 0x12c]
		fmulp st(2), st(0)
		faddp st(2), st(0)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fld dword ptr [esp + 0x130]
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0xc4]
		fistp dword ptr [esp + 0xc8]
		mov ecx, dword ptr [esp + 0xc4]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc4]
		sar eax, 0x10
		mov dword ptr [esp + 0xfc], ecx
		mov dword ptr [esp + 0xf8], eax
		mov ecx, dword ptr [esp + 0xc8]
		mov ebp, dword ptr [esp + 0x18c]
		shl ecx, 0x10
		mov eax, dword ptr [esp + 0xc8]
		sar eax, 0x10
		mov ebp, dword ptr [ebp + 0x34]
		mov dword ptr [esp + 0x104], ecx
		mov ecx, dword ptr [ebp + 0x14]
		mov dword ptr [esp + 0x100], eax
		mov ebx, dword ptr [ebp + 4]
		mov dword ptr [esp + 0x120], ecx
		sar ebx, 1
		imul ebx
		mov ecx, dword ptr [ebp]
		mov dword ptr [esp + 0x10c], eax
		add eax, ebx
		mov dword ptr [esp + 0x138], ecx
		sar ecx, 1
		mov dword ptr [esp + 0x108], eax
		mov dword ptr [esp + 0x11c], ebx
		mov dword ptr [esp + 0x118], ecx
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		je jmp_1003f301
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x6c]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x6c], edi
		mov eax, dword ptr [esp + 0x18]
		mov edi, dword ptr [esp + 0x70]
		add eax, eax
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x70], edi
		jmp jmp_1003f301
jmp_1003f301:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
		mov edx, dword ptr [esp + 0x6c]
		mov eax, dword ptr [esp + 0x70]
		mov dword ptr [esp + 0xf0], edx
		mov dword ptr [esp + 0xf4], eax
jmp_1003f33b:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003f42f
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003f3c0
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003f3c0:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003f33b
jmp_1003f42f:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_1003f76b
		or ebx, ebx
		je jmp_1003f60b
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		je jmp_1003f4de
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x98]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0xf0], edx
		mov eax, dword ptr [esp + 0x44]
		mov ebx, dword ptr [esp + 0x9c]
		add eax, eax
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0xf4], edx
		jmp jmp_1003f4fa
jmp_1003f4de:
		mov ebx, dword ptr [esp + 0x98]
		mov ecx, dword ptr [esp + 0x9c]
		mov dword ptr [esp + 0xf0], ebx
		mov dword ptr [esp + 0xf4], ecx
jmp_1003f4fa:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_1003f50b:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003f606
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003f590
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003f590:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x40]
		mov ebx, dword ptr [esp + 0x44]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003f50b
jmp_1003f606:
		jmp jmp_1003f76b
jmp_1003f60b:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_1003f670
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_1003f670:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003f76b
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003f6f5
		mov edi, edx
		mov dword ptr [esp + 0x158], edx
		shl edi, 0x10
		mov eax, dword ptr [esp + 4]
		sub edi, eax
		mov eax, dword ptr [esp + 0xc4]
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf0]
		rol eax, 0x10
		add esi, eax
		mov eax, dword ptr [esp + 0xc8]
		mov dword ptr [esp + 0x6c], esi
		imul edi
		mov ax, dx
		mov esi, dword ptr [esp + 0xf4]
		rol eax, 0x10
		mov edx, dword ptr [esp + 0x158]
		add esi, eax
		mov dword ptr [esp + 0x70], esi
		call ebp
jmp_1003f6f5:
		mov esi, dword ptr [esp + 0xf0]
		mov edi, dword ptr [esp + 0xf4]
		mov eax, dword ptr [esp + 0x14]
		mov ebx, dword ptr [esp + 0x18]
		add esi, eax
		add edi, ebx
		mov dword ptr [esp + 0xf0], esi
		mov dword ptr [esp + 0xf4], edi
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003f670
jmp_1003f76b:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_1003f776:
		fstp dword ptr [esp + 4]
jmp_1003f77a:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x1003f790
__declspec(naked) void FUN_1003f790(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebx, dword ptr [eax + 0x10]
		mov ebp, dword ptr [edx + 4]
		mov dword ptr [esp + 0x114], ebx
		jle jmp_1003f7c9
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1003f7c9:
		cmp esi, ebp
		jle jmp_1003f7d9
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_1003f7d9:
		cmp edi, ebp
		jg jmp_1003f7eb
		mov ebx, dword ptr [ecx]
		jne jmp_1003f7f7
		cmp ebx, dword ptr [edx]
		je jmp_1003fcc6
		jg jmp_1003f7f7
jmp_1003f7eb:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_1003f7f7:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_1003f816
		cmp ebx, dword ptr [eax]
		jg jmp_1003f816
		mov ebx, eax
		je jmp_1003fcd1
		mov eax, ecx
		mov ecx, ebx
jmp_1003f816:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_1003fcc6
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_1003f93c
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_1003f924
		dec edi
jmp_1003f924:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_1003f933
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_1003f933:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_1003f961
jmp_1003f93c:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_1003f961:
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_1003f99d
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		jmp jmp_1003f99d
jmp_1003f99d:
		mov eax, dword ptr [esp + 0x114]
		mov ebx, 0xf8
		mov ecx, 0xfc00
		and ebx, eax
		shr ebx, 3
		and ecx, eax
		shr ecx, 5
		mov edx, 0xf800
		and edx, eax
		and eax, 0xf80000
		shr edx, 6
		or ecx, ebx
		shr eax, 9
		or edx, ebx
		or edx, eax
		add eax, eax
		or ecx, eax
		mov ebx, edx
		shl edx, 0x10
		mov eax, ecx
		shl ecx, 0x10
		or edx, ebx
		or ecx, eax
		mov dword ptr [esp + 0x164], edx
		mov dword ptr [esp + 0x160], ecx
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		je jmp_1003fa3e
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		jmp jmp_1003fa3e
jmp_1003fa3e:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
jmp_1003fa62:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003fad6
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003fa92
		call ebp
jmp_1003fa92:
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003fa62
jmp_1003fad6:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_1003fcc6
		or ebx, ebx
		je jmp_1003fbe6
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		je jmp_1003fb55
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		jmp jmp_1003fb55
jmp_1003fb55:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_1003fb66:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003fbe1
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003fb96
		call ebp
jmp_1003fb96:
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003fb66
jmp_1003fbe1:
		jmp jmp_1003fcc6
jmp_1003fbe6:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_1003fc4b
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_1003fc4b:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1003fcc6
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_1003fc7b
		call ebp
jmp_1003fc7b:
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1003fc4b
jmp_1003fcc6:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_1003fcd1:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x1003fce0
__declspec(naked) void FUN_1003fce0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp_1003fd0f
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1003fd0f:
		cmp esi, ebp
		jle jmp_1003fd1f
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_1003fd1f:
		cmp edi, ebp
		jg jmp_1003fd31
		mov ebx, dword ptr [ecx]
		jne jmp_1003fd3d
		cmp ebx, dword ptr [edx]
		je jmp_1004064d
		jg jmp_1003fd3d
jmp_1003fd31:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_1003fd3d:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_1003fd5c
		cmp ebx, dword ptr [eax]
		jg jmp_1003fd5c
		mov ebx, eax
		je jmp_10040658
		mov eax, ecx
		mov ecx, ebx
jmp_1003fd5c:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_1004064d
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_1003fe82
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_1003fe6a
		dec edi
jmp_1003fe6a:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_1003fe79
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_1003fe79:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_1003fea7
jmp_1003fe82:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_1003fea7:
		mov esi, dword ptr [eax + 0x10]
		mov ebx, 0xf8
		and ebx, esi
		mov edi, 0xf800
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov dword ptr [esp + 0x74], ebx
		and esi, 0xf80000
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], esi
		mov esi, dword ptr [ecx + 0x10]
		mov ebx, 0xf8
		and ebx, esi
		mov edi, 0xf800
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov dword ptr [esp + 0xa0], ebx
		and esi, 0xf80000
		mov dword ptr [esp + 0xa4], edi
		mov dword ptr [esp + 0xa8], esi
		mov esi, dword ptr [edx + 0x10]
		mov ebx, 0xf8
		and ebx, esi
		mov edi, 0xf800
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov dword ptr [esp + 0xcc], ebx
		and esi, 0xf80000
		mov dword ptr [esp + 0xd0], edi
		mov dword ptr [esp + 0xd4], esi
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_1004004e
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0xa0]
		mov edx, dword ptr [esp + 0x74]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		mov dword ptr [esp + 0x13c], ecx
		mov ebx, dword ptr [esp + 0xd0]
		mov ecx, dword ptr [esp + 0xa4]
		mov edx, dword ptr [esp + 0x78]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		mov ebx, dword ptr [esp + 0xd4]
		mov ecx, dword ptr [esp + 0xa8]
		mov edx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		fmul dword ptr [esp + 0x128]
		fxch st(5)
		fistp dword ptr [esp + 0x48]
		fistp dword ptr [esp + 0x50]
		fistp dword ptr [esp + 0x20]
		fistp dword ptr [esp + 0x4c]
		fistp dword ptr [esp + 0x1c]
		fistp dword ptr [esp + 0x24]
		jmp jmp_100400c2
jmp_1004004e:
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0x74]
		sub ebx, ecx
		mov edx, dword ptr [esp + 0xd0]
		mov dword ptr [esp + 0x138], ebx
		mov esi, dword ptr [esp + 0x78]
		fild dword ptr [esp + 0x138]
		sub edx, esi
		mov ebx, dword ptr [esp + 0xd4]
		mov dword ptr [esp + 0x138], edx
		mov ecx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		sub ebx, ecx
		mov dword ptr [esp + 0x138], ebx
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x124]
		fxch st(2)
		fistp dword ptr [esp + 0x1c]
		fistp dword ptr [esp + 0x20]
		fistp dword ptr [esp + 0x24]
jmp_100400c2:
		fild dword ptr [esp + 0x74]
		fild dword ptr [esp + 0xcc]
		fild dword ptr [esp + 0xa0]
		fild dword ptr [esp + 0xd0]
		fild dword ptr [esp + 0x78]
		fild dword ptr [esp + 0xa4]
		fxch st(5)
		fsub st(4), st(0)
		fsubrp st(3), st(0)
		fsub st(1), st(0)
		fsubrp st(4), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x12c]
		fild dword ptr [esp + 0xd4]
		fild dword ptr [esp + 0xa8]
		fild dword ptr [esp + 0x7c]
		fld dword ptr [esp + 0x12c]
		fmulp st(6), st(0)
		fsubr st(1), st(0)
		fsubp st(2), st(0)
		fxch st(5)
		faddp st(4), st(0)
		fmul dword ptr [esp + 0x12c]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x130]
		fxch st(3)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fxch st(1)
		fmul dword ptr [esp + 0x130]
		fxch st(2)
		fistp dword ptr [esp + 0xd0]
		fistp dword ptr [esp + 0xcc]
		fistp dword ptr [esp + 0xd4]
		mov edx, dword ptr [esp + 0xcc]
		mov eax, dword ptr [esp + 0xd0]
		sar edx, 3
		mov ebp, dword ptr [esp + 0xd4]
		shl eax, 2
		sub edx, 0x8000
		shl ebp, 7
		sub eax, 0x100000
		sub ebp, 0x2000000
		mov dword ptr [esp + 0x160], edx
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebp
		add edx, 0x10000
		add eax, 0x200000
		add ebp, 0x4000000
		mov dword ptr [esp + 0x16c], edx
		mov dword ptr [esp + 0x170], eax
		mov dword ptr [esp + 0x174], ebp
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		mov ebp, 0x3000
		je jmp_10040258
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x1c]
		mov edi, dword ptr [esp + 0x74]
		add eax, eax
		mov esi, dword ptr [esp + 0x20]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x74], edi
		mov esi, dword ptr [esp + 0x24]
		mov edi, dword ptr [esp + 0x78]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x78], edi
		mov edi, dword ptr [esp + 0x7c]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x7c], edi
		jmp jmp_10040276
jmp_10040258:
		mov ebx, dword ptr [esp + 0x74]
		mov ecx, dword ptr [esp + 0x7c]
		mov esi, dword ptr [esp + 0x78]
		add ebx, ebp
		add ecx, ebp
		add esi, ebp
		mov dword ptr [esp + 0x74], ebx
		mov dword ptr [esp + 0x7c], ecx
		mov dword ptr [esp + 0x78], esi
jmp_10040276:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
jmp_1004029a:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1004033f
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_100402ce
		call ebp
jmp_100402ce:
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], ebp
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1004029a
jmp_1004033f:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_1004064d
		or ebx, ebx
		je jmp_10040500
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		mov ebp, 0x3000
		je jmp_10040417
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov esi, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0xa0]
		mov edi, dword ptr [esp + 0x4c]
		add ebx, ebp
		lea eax, [esi*2]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa4]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x74], edx
		add ebx, ebp
		mov edi, dword ptr [esp + 0x50]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa8]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x78], edx
		add ebx, ebp
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x7c], edx
		jmp jmp_1004043e
jmp_10040417:
		mov eax, dword ptr [esp + 0xa0]
		mov ebx, dword ptr [esp + 0xa4]
		mov ecx, dword ptr [esp + 0xa8]
		add eax, ebp
		add ebx, ebp
		add ecx, ebp
		mov dword ptr [esp + 0x74], eax
		mov dword ptr [esp + 0x78], ebx
		mov dword ptr [esp + 0x7c], ecx
jmp_1004043e:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_1004044f:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_100404fb
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_10040483
		call ebp
jmp_10040483:
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0x4c]
		mov ecx, dword ptr [esp + 0x50]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], ebp
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_1004044f
jmp_100404fb:
		jmp jmp_1004064d
jmp_10040500:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_10040565
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_10040565:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_1004064d
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_10040599
		call ebp
jmp_10040599:
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], ebp
		mov esi, dword ptr [esp + 0x84]
		mov edi, dword ptr [esp + 0x88]
		mov ebp, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x2c]
		mov ebx, dword ptr [esp + 0x30]
		mov ecx, dword ptr [esp + 0x34]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x84], esi
		mov dword ptr [esp + 0x88], edi
		mov dword ptr [esp + 0x8c], ebp
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_10040565
jmp_1004064d:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_10040658:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10040670
__declspec(naked) void FUN_10040670(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov eax, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		push esi
		push edi
		push ebx
		push ebp
		mov esi, dword ptr [eax + 4]
		mov edi, dword ptr [ecx + 4]
		sub esp, 0x178
		cmp esi, edi
		mov ebp, dword ptr [edx + 4]
		jle jmp_1004069f
		mov ebx, eax
		mov eax, ecx
		mov ecx, ebx
		mov ebx, esi
		mov esi, edi
		mov edi, ebx
jmp_1004069f:
		cmp esi, ebp
		jle jmp_100406af
		mov ebx, eax
		mov eax, edx
		mov edx, ebx
		mov ebx, esi
		mov esi, ebp
		mov ebp, ebx
jmp_100406af:
		cmp edi, ebp
		jg jmp_100406c1
		mov ebx, dword ptr [ecx]
		jne jmp_100406cd
		cmp ebx, dword ptr [edx]
		je jmp_10040fdd
		jg jmp_100406cd
jmp_100406c1:
		mov ebx, ecx
		mov ecx, edx
		mov edx, ebx
		mov ebx, edi
		mov edi, ebp
		mov ebp, ebx
jmp_100406cd:
		fld dword ptr [edx + 4]
		fmul dword ptr [g_floatConst65536]
		cmp esi, edi
		mov ebx, dword ptr [ecx]
		jne jmp_100406ec
		cmp ebx, dword ptr [eax]
		jg jmp_100406ec
		mov ebx, eax
		je jmp_10040fe8
		mov eax, ecx
		mov ecx, ebx
jmp_100406ec:
		mov dword ptr [esp + 0x190], eax
		mov dword ptr [esp + 0x194], ecx
		mov dword ptr [esp + 0x198], edx
		fistp dword ptr [esp + 0x144]
		fld dword ptr [eax + 4]
		fmul dword ptr [g_floatConst65536]
		mov esi, dword ptr [esp + 0x144]
		mov edi, 0xffff
		dec esi
		fistp dword ptr [esp]
		add edi, dword ptr [esp]
		and esi, 0xffff0000
		and edi, 0xffff0000
		cmp esi, edi
		jl jmp_10040fdd
		fld dword ptr [eax]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ebx, dword ptr [esp + 4]
		mov dword ptr [esp + 8], ebx
		fistp dword ptr [esp + 0x140]
		fld dword ptr [edx + 4]
		fsub dword ptr [eax + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [eax + 4]
		fxch st(1)
		fld1
		fdivrp st(1), st(0)
		mov ebp, dword ptr [esp + 0x18c]
		mov dword ptr [esp + 0x110], ebp
		fst dword ptr [esp + 0x124]
		fmul st(0), st(1)
		fxch st(1)
		fstp dword ptr [esp + 0x128]
		mov ebx, dword ptr [esp + 0x128]
		fstp dword ptr [esp + 0x12c]
		or ebx, ebx
		je jmp_10040812
		fld1
		fdiv dword ptr [esp + 0x128]
		fst dword ptr [esp + 0x128]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ecx]
		fsub dword ptr [eax]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 0xc]
		fst dword ptr [esp + 0x134]
		mov esi, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 0x134]
		fistp dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x10]
		xor ebx, edi
		jns jmp_100407fa
		dec edi
jmp_100407fa:
		xor ebx, ebx
		cmp esi, edi
		jle jmp_10040809
		inc ebx
		mov dword ptr [esp + 0xc], edi
		mov dword ptr [esp + 0x10], esi
jmp_10040809:
		mov dword ptr [esp + 0x14c], ebx
		jmp jmp_10040837
jmp_10040812:
		mov dword ptr [esp + 0x14c], ebx
		mov dword ptr [esp + 0x148], edx
		fld dword ptr [esp + 0x124]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fmulp st(1), st(0)
		fistp dword ptr [esp + 0xc]
jmp_10040837:
		mov esi, dword ptr [eax + 0x10]
		mov ebx, 0xf8
		and ebx, esi
		mov edi, 0xf800
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov dword ptr [esp + 0x74], ebx
		and esi, 0xf80000
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], esi
		mov esi, dword ptr [ecx + 0x10]
		mov ebx, 0xf8
		and ebx, esi
		mov edi, 0xf800
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov dword ptr [esp + 0xa0], ebx
		and esi, 0xf80000
		mov dword ptr [esp + 0xa4], edi
		mov dword ptr [esp + 0xa8], esi
		mov esi, dword ptr [edx + 0x10]
		mov ebx, 0xf8
		and ebx, esi
		mov edi, 0xf800
		shl ebx, 0x10
		and edi, esi
		shl edi, 8
		mov dword ptr [esp + 0xcc], ebx
		and esi, 0xf80000
		mov dword ptr [esp + 0xd0], edi
		mov dword ptr [esp + 0xd4], esi
		fld dword ptr [edx]
		fsub dword ptr [eax]
		fld dword ptr [eax]
		fsub dword ptr [ecx]
		fxch st(1)
		fmul dword ptr [esp + 0x12c]
		mov ebx, dword ptr [esp + 0x14c]
		faddp st(1), st(0)
		fld1
		fdivrp st(1), st(0)
		or ebx, ebx
		fstp dword ptr [esp + 0x130]
		je jmp_100409de
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld1
		fdivrp st(1), st(0)
		fstp dword ptr [esp + 0x134]
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0xa0]
		mov edx, dword ptr [esp + 0x74]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		fild dword ptr [esp + 0x138]
		mov dword ptr [esp + 0x13c], ecx
		mov ebx, dword ptr [esp + 0xd0]
		mov ecx, dword ptr [esp + 0xa4]
		mov edx, dword ptr [esp + 0x78]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		mov ebx, dword ptr [esp + 0xd4]
		mov ecx, dword ptr [esp + 0xa8]
		mov edx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		sub ebx, ecx
		sub ecx, edx
		mov dword ptr [esp + 0x138], ebx
		mov dword ptr [esp + 0x13c], ecx
		fmul dword ptr [esp + 0x128]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x134]
		fild dword ptr [esp + 0x13c]
		fmul dword ptr [esp + 0x128]
		fxch st(5)
		fistp dword ptr [esp + 0x48]
		fistp dword ptr [esp + 0x50]
		fistp dword ptr [esp + 0x20]
		fistp dword ptr [esp + 0x4c]
		fistp dword ptr [esp + 0x1c]
		fistp dword ptr [esp + 0x24]
		jmp jmp_10040a52
jmp_100409de:
		mov ebx, dword ptr [esp + 0xcc]
		mov ecx, dword ptr [esp + 0x74]
		sub ebx, ecx
		mov edx, dword ptr [esp + 0xd0]
		mov dword ptr [esp + 0x138], ebx
		mov esi, dword ptr [esp + 0x78]
		fild dword ptr [esp + 0x138]
		sub edx, esi
		mov ebx, dword ptr [esp + 0xd4]
		mov dword ptr [esp + 0x138], edx
		mov ecx, dword ptr [esp + 0x7c]
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		sub ebx, ecx
		mov dword ptr [esp + 0x138], ebx
		fmul dword ptr [esp + 0x124]
		fild dword ptr [esp + 0x138]
		fmul dword ptr [esp + 0x124]
		fxch st(2)
		fistp dword ptr [esp + 0x1c]
		fistp dword ptr [esp + 0x20]
		fistp dword ptr [esp + 0x24]
jmp_10040a52:
		fild dword ptr [esp + 0x74]
		fild dword ptr [esp + 0xcc]
		fild dword ptr [esp + 0xa0]
		fild dword ptr [esp + 0xd0]
		fild dword ptr [esp + 0x78]
		fild dword ptr [esp + 0xa4]
		fxch st(5)
		fsub st(4), st(0)
		fsubrp st(3), st(0)
		fsub st(1), st(0)
		fsubrp st(4), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x12c]
		fild dword ptr [esp + 0xd4]
		fild dword ptr [esp + 0xa8]
		fild dword ptr [esp + 0x7c]
		fld dword ptr [esp + 0x12c]
		fmulp st(6), st(0)
		fsubr st(1), st(0)
		fsubp st(2), st(0)
		fxch st(5)
		faddp st(4), st(0)
		fmul dword ptr [esp + 0x12c]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x130]
		fxch st(3)
		faddp st(2), st(0)
		fmul dword ptr [esp + 0x130]
		fxch st(1)
		fmul dword ptr [esp + 0x130]
		fxch st(2)
		fistp dword ptr [esp + 0xd0]
		fistp dword ptr [esp + 0xcc]
		fistp dword ptr [esp + 0xd4]
		mov edx, dword ptr [esp + 0xcc]
		mov eax, dword ptr [esp + 0xd0]
		sar edx, 3
		mov ebp, dword ptr [esp + 0xd4]
		shl eax, 3
		sub edx, 0x8000
		shl ebp, 8
		sub eax, 0x100000
		sub ebp, 0x4000000
		mov dword ptr [esp + 0x160], edx
		mov dword ptr [esp + 0x164], eax
		mov dword ptr [esp + 0x168], ebp
		add edx, 0x10000
		add eax, 0x200000
		add ebp, 0x8000000
		mov dword ptr [esp + 0x16c], edx
		mov dword ptr [esp + 0x170], eax
		mov dword ptr [esp + 0x174], ebp
		mov ebx, dword ptr [esp]
		mov ecx, 0x10000
		mov edx, ebx
		and ebx, 0xffff
		mov ebp, 0x3000
		je jmp_10040be8
		mov esi, dword ptr [esp + 0xc]
		mov edi, dword ptr [esp + 4]
		add edx, ecx
		sub ecx, ebx
		shl ecx, 0xf
		sub edx, ebx
		mov dword ptr [esp], edx
		lea eax, [esi*2]
		mov esi, dword ptr [esp + 0x10]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 4], edi
		mov edi, dword ptr [esp + 8]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 8], edi
		mov eax, dword ptr [esp + 0x1c]
		mov edi, dword ptr [esp + 0x74]
		add eax, eax
		mov esi, dword ptr [esp + 0x20]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x74], edi
		mov esi, dword ptr [esp + 0x24]
		mov edi, dword ptr [esp + 0x78]
		imul ecx
		add edi, edx
		lea eax, [esi*2]
		mov dword ptr [esp + 0x78], edi
		mov edi, dword ptr [esp + 0x7c]
		imul ecx
		add edi, edx
		mov dword ptr [esp + 0x7c], edi
		jmp jmp_10040c06
jmp_10040be8:
		mov ebx, dword ptr [esp + 0x74]
		mov ecx, dword ptr [esp + 0x7c]
		mov esi, dword ptr [esp + 0x78]
		add ebx, ebp
		add ecx, ebp
		add esi, ebp
		mov dword ptr [esp + 0x74], ebx
		mov dword ptr [esp + 0x7c], ecx
		mov dword ptr [esp + 0x78], esi
jmp_10040c06:
		mov eax, dword ptr [esp]
		mov ebp, dword ptr [esp + 0x18c]
		sar eax, 0x10
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [ebp]
		mov ecx, dword ptr [ebp + 4]
		imul ecx
		mov edi, dword ptr [ebp + 0x30]
		add ebx, eax
		mov dword ptr [esp + 0x154], edi
jmp_10040c2a:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x140]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_10040ccf
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_10040c5e
		call ebp
jmp_10040c5e:
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], ebp
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_10040c2a
jmp_10040ccf:
		mov dword ptr [esp + 0x150], ebx
		mov ecx, dword ptr [esp + 0x144]
		mov ebx, dword ptr [esp + 0x14c]
		cmp esi, ecx
		jge jmp_10040fdd
		or ebx, ebx
		je jmp_10040e90
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		fld dword ptr [esp + 0x134]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fmulp st(1), st(0)
		fxch st(1)
		fistp dword ptr [esp + 4]
		mov ecx, dword ptr [esp]
		mov edx, dword ptr [esp + 0x140]
		sub ecx, edx
		fistp dword ptr [esp + 0xc]
		mov ebp, 0x3000
		je jmp_10040da7
		mov eax, dword ptr [esp + 0xc]
		mov ebx, dword ptr [esp + 4]
		shl ecx, 0xf
		add eax, eax
		imul ecx
		add ebx, edx
		mov dword ptr [esp + 4], ebx
		mov esi, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0xa0]
		mov edi, dword ptr [esp + 0x4c]
		add ebx, ebp
		lea eax, [esi*2]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa4]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x74], edx
		add ebx, ebp
		mov edi, dword ptr [esp + 0x50]
		imul ecx
		add edx, ebx
		mov ebx, dword ptr [esp + 0xa8]
		lea eax, [edi*2]
		mov dword ptr [esp + 0x78], edx
		add ebx, ebp
		imul ecx
		add edx, ebx
		mov dword ptr [esp + 0x7c], edx
		jmp jmp_10040dce
jmp_10040da7:
		mov eax, dword ptr [esp + 0xa0]
		mov ebx, dword ptr [esp + 0xa4]
		mov ecx, dword ptr [esp + 0xa8]
		add eax, ebp
		add ebx, ebp
		add ecx, ebp
		mov dword ptr [esp + 0x74], eax
		mov dword ptr [esp + 0x78], ebx
		mov dword ptr [esp + 0x7c], ecx
jmp_10040dce:
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
jmp_10040ddf:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_10040e8b
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_10040e13
		call ebp
jmp_10040e13:
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x48]
		mov ebx, dword ptr [esp + 0x4c]
		mov ecx, dword ptr [esp + 0x50]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], ebp
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_10040ddf
jmp_10040e8b:
		jmp jmp_10040fdd
jmp_10040e90:
		mov ecx, dword ptr [esp + 0x194]
		mov edx, dword ptr [esp + 0x198]
		mov ebp, dword ptr [esp + 0x18c]
		mov esi, dword ptr [esp]
		mov ebx, dword ptr [esp + 0x150]
		fld dword ptr [ecx]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edx]
		fsub dword ptr [ecx]
		fxch st(2)
		fistp dword ptr [esp + 8]
		fdivr dword ptr [g_floatConst65536]
		mov edx, esi
		mov ecx, dword ptr [esp + 0x140]
		sub edx, ecx
		shl edx, 0xf
		fmulp st(1), st(0)
		mov ecx, dword ptr [esp + 8]
		fistp dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 0x10]
		je jmp_10040ef5
		add eax, eax
		imul edx
		add ecx, edx
		mov dword ptr [esp + 8], ecx
jmp_10040ef5:
		mov edx, dword ptr [esp + 4]
		mov eax, dword ptr [esp + 0x144]
		add edx, 0xffff
		cmp esi, eax
		mov ecx, dword ptr [esp + 8]
		jge jmp_10040fdd
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov ebp, dword ptr [ebp + 0x28]
		sub ecx, edx
		mov dword ptr [esp + 0x150], ebx
		jl jmp_10040f29
		call ebp
jmp_10040f29:
		mov esi, dword ptr [esp + 0x74]
		mov edi, dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x7c]
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x20]
		mov ecx, dword ptr [esp + 0x24]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x74], esi
		mov dword ptr [esp + 0x78], edi
		mov dword ptr [esp + 0x7c], ebp
		mov esi, dword ptr [esp + 0x84]
		mov edi, dword ptr [esp + 0x88]
		mov ebp, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x2c]
		mov ebx, dword ptr [esp + 0x30]
		mov ecx, dword ptr [esp + 0x34]
		add esi, eax
		add edi, ebx
		add ebp, ecx
		mov dword ptr [esp + 0x84], esi
		mov dword ptr [esp + 0x88], edi
		mov dword ptr [esp + 0x8c], ebp
		mov ebp, dword ptr [esp + 0x18c]
		mov ebp, dword ptr [esp + 0x18c]
		mov ebx, dword ptr [esp + 0x150]
		mov esi, dword ptr [esp + 4]
		mov edi, dword ptr [esp + 8]
		mov ecx, dword ptr [esp + 0xc]
		mov edx, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 4]
		add esi, ecx
		add edi, edx
		mov dword ptr [esp + 4], esi
		mov dword ptr [esp + 8], edi
		mov esi, dword ptr [esp]
		add ebx, eax
		add esi, 0x10000
		mov dword ptr [esp + 0x150], ebx
		mov dword ptr [esp], esi
		jmp jmp_10040ef5
jmp_10040fdd:
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_10040fe8:
		fstp dword ptr [esp]
		add esp, 0x178
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

#endif
