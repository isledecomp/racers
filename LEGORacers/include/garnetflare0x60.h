#ifndef GARNETFLARE0X60_H
#define GARNETFLARE0X60_H

#include "decomp.h"
#include "gdbpartlibrary0x1c.h"
#include "types.h"

class AmberHaze0x1c;
class BronzeFalcon0xc8770;
class DuskwindBananaRelic0x24;
class FloatyFerry0xf4;
class GolExport;
class IGdbModel0x40;
class LavenderVault0x764;
class MagentaRibbon0x20;
class WhiteFalconNode0x18;
class ZoweeBlubberworth0xf0;

// SIZE 0x60
class GarnetFlare0x60 {
public:
	// SIZE 0x18
	struct LoadParams {
		undefined4 m_unk0x00;            // 0x00
		GolExport* m_golExport;          // 0x04
		BronzeFalcon0xc8770* m_renderer; // 0x08
		LavenderVault0x764* m_unk0x0c;   // 0x0c
		undefined4 m_binary;             // 0x10
		undefined4 m_unk0x14;            // 0x14
	};

	GarnetFlare0x60();
	~GarnetFlare0x60();
	ZoweeBlubberworth0xf0* FUN_00497f10(const LoadParams* p_params, LegoS32 p_resourceIndex);
	LegoBool32 ReleaseResources();
	IGdbModel0x40* FUN_004984d0(LegoS32 p_index);
	IGdbModel0x40* FUN_00498510(LegoS32 p_index);
	WhiteFalconNode0x18* FUN_00498570(LegoS32 p_index);
	DuskwindBananaRelic0x24* FUN_00498640(LegoS32 p_index);
	DuskwindBananaRelic0x24* FUN_00498680(LegoS32 p_index);
	DuskwindBananaRelic0x24* FUN_004986c0(LegoS32 p_index);
	LavenderVault0x764* GetPartConfig() const { return m_partConfig; }
	LegoS32 GetUnk0x3c() const { return m_unk0x3c; }
	LegoS32 GetUnk0x40() const { return m_unk0x40; }
	LegoS32 GetUnk0x44() const { return m_unk0x44; }
	LegoS32 GetUnk0x48() const { return m_unk0x48; }
	LegoS32 GetUnk0x4c() const { return m_unk0x4c; }
	LegoS32 GetUnk0x50() const { return m_unk0x50; }
	LegoS32 GetUnk0x54() const { return m_unk0x54; }
	LegoS32 GetUnk0x58() const { return m_unk0x58; }

private:
	LegoS32 Reset();
	void LoadPartResource(LegoBool32 p_binary);
	void LoadMaterialAndTextureLists(LegoBool32 p_binary);
	void NormalizeHeadGroupOrder();
	void ComputeMaxVertexCounts();
	void ComputeMaxIndexCounts();
	void ComputeMaxGroupCounts();
	void ComputeMaxMaterialCounts();

	GdbPartLibrary0x1c m_partLibrary;      // 0x00
	BronzeFalcon0xc8770* m_renderer;       // 0x1c
	GolExport* m_golExport;                // 0x20
	ZoweeBlubberworth0xf0* m_partResource; // 0x24
	IGdbModel0x40* m_unk0x28;              // 0x28
	LegoBool32 m_binary;                   // 0x2c
	AmberHaze0x1c* m_materialList;         // 0x30
	MagentaRibbon0x20* m_textureList;      // 0x34
	LavenderVault0x764* m_partConfig;      // 0x38
	LegoS32 m_unk0x3c;                     // 0x3c
	LegoS32 m_unk0x40;                     // 0x40
	LegoS32 m_unk0x44;                     // 0x44
	LegoS32 m_unk0x48;                     // 0x48
	LegoS32 m_unk0x4c;                     // 0x4c
	LegoS32 m_unk0x50;                     // 0x50
	LegoS32 m_unk0x54;                     // 0x54
	LegoS32 m_unk0x58;                     // 0x58
	LegoS32 m_resourceIndex;               // 0x5c
};

#endif // GARNETFLARE0X60_H
