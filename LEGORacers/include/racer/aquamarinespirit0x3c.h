#ifndef AQUAMARINESPIRIT0X3C_H
#define AQUAMARINESPIRIT0X3C_H

#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004afe7c
// SIZE 0x1fc
class CmbTxtParser : public GolTxtParser {};

class GolExport;
class AmberHaze0x1c;
class BronzeFalcon0xc8770;
class IGdbModel0x40;
class MagentaRibbon0x20;
class OpalHaven0xf4;
class WhiteFalconNode0x18;
class GolFileParser;

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
		GolExport* m_unk0x00;           // 0x00
		BronzeFalcon0xc8770* m_unk0x04; // 0x04
		LegoS32 m_unk0x08;              // 0x08
		const LegoChar* m_filename;     // 0x0c
		LegoBool32 m_unk0x10;           // 0x10
	};

	void FUN_0041db10(const Params* p_params);
	LegoU32 FUN_0041e330(const LegoChar* p_name, OpalHaven0xf4** p_primary, OpalHaven0xf4** p_secondary);
	void FUN_0041e570();
	OpalHaven0xf4* FUN_0041e5b0(const LegoChar* p_name);

	// SIZE 0x104
	struct Item0x104 {
		GolName m_materialNames[2];      // 0x000
		GolName m_textureNames[2];       // 0x010
		GolName m_modelNames[2];         // 0x020
		GolName m_modelPartNames[2];     // 0x030
		GolName m_nodeNames[2];          // 0x040
		GolName m_unk0x50;               // 0x050
		GolVec3 m_unk0x58[4];            // 0x058
		GolVec3 m_unk0x88[4];            // 0x088
		GolVec3 m_unk0xb8;               // 0x0b8
		GolVec3 m_unk0xc4;               // 0x0c4
		LegoFloat m_unk0xd0;             // 0x0d0
		GolVec2 m_unk0xd4;               // 0x0d4
		GolVec2 m_unk0xdc;               // 0x0dc
		GolVec2 m_unk0xe4;               // 0x0e4
		LegoFloat m_unk0xec;             // 0x0ec
		LegoS32 m_unk0xf0;               // 0x0f0
		LegoS32 m_unk0xf4;               // 0x0f4
		OpalHaven0xf4* m_primaryModel;   // 0x0f8
		OpalHaven0xf4* m_secondaryModel; // 0x0fc
		LegoU8 m_unk0x100;               // 0x100
		LegoU8 m_unk0x101;               // 0x101
		LegoU8 m_unk0x102;               // 0x102
		undefined m_unk0x103[0x104 - 0x103];
	};

private:
	void FUN_0041d980();
	void FUN_0041dae0();
	void FUN_0041e210(GolFileParser* p_parser, LegoU32 p_index, LegoU32 p_variant);
	LegoU32 FUN_0041e360(Item0x104* p_item, OpalHaven0xf4** p_primary, OpalHaven0xf4** p_secondary);

	GolExport* m_unk0x0c;            // 0x0c
	BronzeFalcon0xc8770* m_unk0x10;  // 0x10
	Item0x104* m_unk0x14;            // 0x14
	IGdbModel0x40** m_unk0x18;       // 0x18
	MagentaRibbon0x20** m_unk0x1c;   // 0x1c
	AmberHaze0x1c** m_unk0x20;       // 0x20
	WhiteFalconNode0x18** m_unk0x24; // 0x24
	CmbModelPart0x34* m_unk0x28;     // 0x28
	OpalHaven0xf4* m_unk0x2c;        // 0x2c
	LegoU32 m_unk0x30;               // 0x30
	LegoU32 m_unk0x34;               // 0x34
	LegoBool32 m_unk0x38;            // 0x38
};

#endif // AQUAMARINESPIRIT0X3C_H
