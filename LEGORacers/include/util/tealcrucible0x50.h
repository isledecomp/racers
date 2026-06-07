#ifndef TEALCRUCIBLE0X50_H
#define TEALCRUCIBLE0X50_H

#include "compat.h"
#include "decomp.h"
#include "scene/golbillboard.h"
#include "types.h"

class GdbPartLibrary;
class GolD3DRenderDevice;
class GolExport;
class GolModelBase;
class GolWorldDatabase;
class LavenderVault0x764;

// SIZE 0x50
class TealCrucible0x50 {
public:
	// SIZE 0x18
	struct LoadParams {
		GdbPartLibrary* m_partLibrary;       // 0x00
		GolExport* m_golExport;              // 0x04
		GolD3DRenderDevice* m_renderer;      // 0x08
		LavenderVault0x764* m_cosmeticTable; // 0x0c
		LegoBool32 m_binary;                 // 0x10
		undefined4 m_unk0x14;                // 0x14
	};

	TealCrucible0x50();
	~TealCrucible0x50();

	void Reset();
	LegoBool32 FUN_00499160(const LoadParams* p_params, LegoS32 p_resourceIndex);
	LegoBool32 FUN_004991c0();
	void FUN_00499210(LegoBool32 p_binary);
	void FUN_00499290();
	void FUN_004992f0(GolModelBase* p_model);
	GolModelBase* FUN_00499320(LegoS32 p_index);
	GolModelBase* FUN_00499380(LegoS32 p_index);
	GolModelBase* FUN_004993d0(LegoS32 p_index);
	GolModelBase* FUN_00499420(LegoS32 p_index);
	void* FUN_00499470(LegoS32 p_index);
	void* FUN_004994b0(LegoS32 p_index);
	void* FUN_004994f0(LegoS32 p_index);
	LegoBool32* GetUnk0x30() { return m_unk0x30; }

private:
	GdbPartLibrary* m_partLibrary;       // 0x00
	GolD3DRenderDevice* m_renderer;      // 0x04
	LavenderVault0x764* m_cosmeticTable; // 0x08
	GolExport* m_golExport;              // 0x0c
	GolWorldDatabase* m_worldDatabase;   // 0x10
	GolModelBase* m_unk0x14[7];          // 0x14
	LegoBool32 m_unk0x30[7];             // 0x30
	LegoS32 m_resourceIndex;             // 0x4c
};

#endif // TEALCRUCIBLE0X50_H
