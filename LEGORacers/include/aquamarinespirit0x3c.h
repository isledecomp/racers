#ifndef AQUAMARINESPIRIT0X3C_H
#define AQUAMARINESPIRIT0X3C_H

#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004afe7c
// SIZE 0x1fc
class CmbTxtParser : public GolTxtParser {};

class GolExport;
class AmberHaze0x1c;
class MagentaRibbon0x20;
class OpalHaven0xf4;

// VTABLE: LEGORACERS 0x004afe70
// SIZE 0x3c
class AquamarineSpirit0x3c : public GolNameTable {
public:
	AquamarineSpirit0x3c();
	~AquamarineSpirit0x3c() override; // vtable+0x00
	void Clear() override;

	// SYNTHETIC: LEGORACERS 0x0041d910
	// AquamarineSpirit0x3c::`scalar deleting destructor'

	struct Params {
		GolExport* m_unk0x00;
		undefined4 m_unk0x04;
		LegoS32 m_unk0x08;
		const LegoChar* m_filename;
		undefined4 m_unk0x10;
	};

	void FUN_0041db10(const Params* p_params);

	// SIZE 0x104
	struct Item0x104 {
		undefined m_unk0x00[0xb8 - 0x00];
		LegoFloat m_unk0xb8[3];
		LegoFloat m_unk0xc4[3];
		LegoFloat m_unk0xd0;
		LegoFloat m_unk0xd4[2];
		LegoFloat m_unk0xdc[2];
		LegoFloat m_unk0xe4[2];
		LegoFloat m_unk0xec;
		undefined4 m_unk0xf0;
		undefined4 m_unk0xf4;
		undefined4* m_unk0xf8;
		undefined4* m_unk0xfc;
		LegoU8 m_unk0x100;
		LegoU8 m_unk0x101;
		LegoU8 m_unk0x102;
		undefined m_unk0x103[0x104 - 0x103];
	};

private:
	void FUN_0041d980();
	void FUN_0041dae0();

	GolExport* m_unk0x0c;          // 0x0c
	undefined4 m_unk0x10;          // 0x10
	Item0x104* m_unk0x14;          // 0x14
	undefined4** m_unk0x18;        // 0x18
	MagentaRibbon0x20** m_unk0x1c; // 0x1c
	AmberHaze0x1c** m_unk0x20;     // 0x20
	undefined4** m_unk0x24;        // 0x24
	CmbModelPart0x34* m_unk0x28;   // 0x28
	OpalHaven0xf4* m_unk0x2c;      // 0x2c
	undefined4 m_unk0x30;          // 0x30
	LegoU32 m_unk0x34;             // 0x34
	undefined4 m_unk0x38;          // 0x38
};

#endif // AQUAMARINESPIRIT0X3C_H
