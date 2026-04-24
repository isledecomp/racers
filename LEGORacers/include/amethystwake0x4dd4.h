#ifndef AMETHYSTWAKE0X4DD4_H
#define AMETHYSTWAKE0X4DD4_H

#include "azurespark0x0c.h"
#include "bronzefalcon0xc8770.h"
#include "cactusinterface0x4.h"
#include "compat.h"
#include "crimsonsun0xa4.h"
#include "decomp.h"
#include "golstring.h"
#include "legoracers.h"
#include "types.h"

class GolExport;

// VTABLE: LEGORACERS 0x004b05a4
// SIZE 0x4dd4
class AmethystWake0x4dd4 : public CactusInterface0x4 {
public:
	AmethystWake0x4dd4();
	void VTable0x00() override;                       // vtable+0x00
	void VTable0x1c(undefined4) override;             // vtable+0x1c
	void VTable0x24(undefined4, undefined4) override; // vtable+0x24
	void VTable0x28() override;                       // vtable+0x28
	void VTable0x2c() override;                       // vtable+0x2c
	virtual ~AmethystWake0x4dd4();                    // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0042c7c0
	// AmethystWake0x4dd4::`scalar deleting destructor'

	static void FUN_0042b1e0(LegoRacers::Context* p_context);

	LegoS32 FUN_0042cb90(LegoRacers::Context* p_context);
	LegoS32 FUN_0042ccc0();
	void FUN_0042cd60();
	void FUN_0042cde0();
	void FUN_0042ced0();
	void FUN_0042cf00();
	void FUN_0042d020();
	void FUN_0042d0e0();
	void FUN_0042d1e0();
	LegoBool FUN_0042d300(LegoU32 p_unk0x04, LegoBool p_unk0x08);
	void FUN_0042d3e0(LegoU16 p_unk0x04);
	void FUN_0042d510();
	void FUN_0042e1f0();
	LegoS32 FUN_0042e450();
	LegoS32 FUN_0042e490();
	LegoS32 FUN_0042e680();

private:
	LegoRacers::Context* m_context;         // 0x04
	AzureSpark0x0c m_unk0x08;               // 0x08
	undefined m_unk0x14[0x25c - 0x14];      // 0x14
	undefined m_unk0x25c[0x1b42 - 0x25c];   // 0x25c
	LegoU8 m_unk0x1b42;                     // 0x1b42
	undefined m_unk0x1b43[0x21a8 - 0x1b43]; // 0x1b43
	undefined m_unk0x21a8[0x21bc - 0x21a8]; // 0x21a8
	undefined m_unk0x21bc[0x21f8 - 0x21bc]; // 0x21bc
	undefined m_unk0x21f8[0x4228 - 0x21f8]; // 0x21f8
	undefined m_unk0x4228[0x4260 - 0x4228]; // 0x4228
	undefined m_unk0x4260[0x42e0 - 0x4260]; // 0x4260
	undefined m_unk0x42e0[0x431c - 0x42e0]; // 0x42e0
	undefined m_unk0x431c[0x4350 - 0x431c]; // 0x431c
	undefined m_unk0x4350[0x4364 - 0x4350]; // 0x4350
	undefined m_unk0x4364[0x4378 - 0x4364]; // 0x4364
	undefined m_unk0x4378[0x4380 - 0x4378]; // 0x4378
	undefined m_unk0x4380[0x4ae4 - 0x4380]; // 0x4380
	undefined m_unk0x4ae4[0x4b44 - 0x4ae4]; // 0x4ae4
	undefined m_unk0x4b44[0x4bcc - 0x4b44]; // 0x4b44
	undefined m_unk0x4bcc[0x4bd0 - 0x4bcc]; // 0x4bcc
	CrimsonSun0xa4 m_unk0x4bd0;             // 0x4bd0
	undefined m_unk0x4c74[0x4cb4 - 0x4c74]; // 0x4c74
	undefined4 m_unk0x4cb4;                 // 0x4cb4
	undefined4 m_unk0x4cb8;                 // 0x4cb8
	undefined4 m_unk0x4cbc;                 // 0x4cbc
	undefined4 m_unk0x4cc0;                 // 0x4cc0
	LegoU8 m_unk0x4cc4;                     // 0x4cc4
	undefined m_unk0x4cc5[0x4cd4 - 0x4cc5]; // 0x4cc5
	GolExport* m_unk0x4cd4;                 // 0x4cd4
	BronzeFalcon0xc8770* m_unk0x4cd8;       // 0x4cd8
	undefined m_unk0x4cdc[0x4ce4 - 0x4cdc]; // 0x4cdc
	undefined m_unk0x4ce4[0x4cf8 - 0x4ce4]; // 0x4ce4
	undefined m_unk0x4cf8[0x4d0c - 0x4cf8]; // 0x4cf8
	undefined m_unk0x4d0c[0x4d24 - 0x4d0c]; // 0x4d0c
	GolString m_unk0x4d24;                  // 0x4d24
	GolString m_unk0x4d30;                  // 0x4d30
	undefined m_unk0x4d3c[0x4d48 - 0x4d3c]; // 0x4d3c
	undefined m_unk0x4d48[0x4d98 - 0x4d48]; // 0x4d48
	undefined4 m_unk0x4d98[0x30 / 4];       // 0x4d98
	undefined m_unk0x4dc8[0x4dd0 - 0x4dc8]; // 0x4dc8
	undefined4 m_unk0x4dd0;                 // 0x4dd0
};

#endif // AMETHYSTWAKE0X4DD4_H
