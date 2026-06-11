#ifndef DRIVERHEADBUILDER_H
#define DRIVERHEADBUILDER_H

#include "compat.h"
#include "decomp.h"
#include "scene/golbillboard.h"
#include "types.h"

class GdbPartLibrary;
class GolD3DRenderDevice;
class GolExport;
class GolModelBase;
class GolWorldDatabase;
class DriverPartCatalog;

// SIZE 0x50
class DriverHeadBuilder {
public:
	// SIZE 0x18
	struct LoadParams {
		GdbPartLibrary* m_partLibrary;    // 0x00
		GolExport* m_golExport;           // 0x04
		GolD3DRenderDevice* m_renderer;   // 0x08
		DriverPartCatalog* m_partCatalog; // 0x0c
		LegoBool32 m_binary;              // 0x10
		undefined4 m_unk0x14;             // 0x14
	};

	DriverHeadBuilder();
	~DriverHeadBuilder();

	void Reset();
	LegoBool32 Load(const LoadParams* p_params, LegoS32 p_resourceIndex);
	LegoBool32 ReleaseResources();
	void LoadHeadResource(LegoBool32 p_binary);
	void CreateHatModels();
	void MarkHatModelUsed(GolModelBase* p_model);
	GolModelBase* LoadHatModel(LegoS32 p_index);
	GolModelBase* GetFaceModel(LegoS32 p_index);
	GolModelBase* GetTorsoModel(LegoS32 p_index);
	GolModelBase* GetLegModel(LegoS32 p_index);
	void* FindFaceMaterial(LegoS32 p_index);
	void* FindTorsoMaterial(LegoS32 p_index);
	void* FindLegMaterial(LegoS32 p_index);
	LegoBool32* GetHatModelUsedFlags() { return m_hatModelUsed; }

private:
	GdbPartLibrary* m_partLibrary;     // 0x00
	GolD3DRenderDevice* m_renderer;    // 0x04
	DriverPartCatalog* m_partCatalog;  // 0x08
	GolExport* m_golExport;            // 0x0c
	GolWorldDatabase* m_worldDatabase; // 0x10
	GolModelBase* m_hatModels[7];      // 0x14
	LegoBool32 m_hatModelUsed[7];      // 0x30
	LegoS32 m_resourceIndex;           // 0x4c
};

#endif // DRIVERHEADBUILDER_H
