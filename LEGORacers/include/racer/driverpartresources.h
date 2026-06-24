#ifndef DRIVERPARTRESOURCES_H
#define DRIVERPARTRESOURCES_H

#include "decomp.h"
#include "model/gdbpartlibrary.h"
#include "types.h"

class GolMaterialLibrary;
class GolD3DRenderDevice;
class DuskwindBananaRelic0x24;
class GolAnimatedEntity;
class GolExport;
class GolModelBase;
class DriverPartCatalog;
class GolTextureList;
class GolSceneNode;
class GolWorldDatabase;
class CmbModelPart0x34;

// SIZE 0x60
class DriverPartResources {
public:
	// SIZE 0x18
	struct LoadParams {
		undefined4 m_unk0x00;             // 0x00
		GolExport* m_golExport;           // 0x04
		GolD3DRenderDevice* m_renderer;   // 0x08
		DriverPartCatalog* m_partCatalog; // 0x0c
		undefined4 m_binary;              // 0x10
		undefined4 m_textureBinaryMode;   // 0x14
	};

	DriverPartResources();
	~DriverPartResources();
	GolWorldDatabase* Load(const LoadParams* p_params, LegoS32 p_resourceIndex);
	LegoBool32 ReleaseResources();
	GolModelBase* LoadHatModel(LegoS32 p_index);
	GolModelBase* GetBodyModel(LegoS32 p_index);
	GolSceneNode* GetBodySceneNode(LegoS32 p_index);
	CmbModelPart0x34* GetBodyModelPart(LegoS32 p_index);
	DuskwindBananaRelic0x24* FindFaceMaterial(LegoS32 p_index);
	DuskwindBananaRelic0x24* FindTorsoMaterial(LegoS32 p_index);
	DuskwindBananaRelic0x24* FindLegMaterial(LegoS32 p_index);
	GdbPartLibrary* GetPartLibrary() { return &m_partLibrary; }
	DriverPartCatalog* GetPartCatalog() const { return m_partCatalog; }
	LegoS32 GetMaxBodyIndexCount() const { return m_maxBodyIndexCount; }
	LegoS32 GetMaxHatIndexCount() const { return m_maxHatIndexCount; }
	LegoS32 GetMaxBodyVertexCount() const { return m_maxBodyVertexCount; }
	LegoS32 GetMaxHatVertexCount() const { return m_maxHatVertexCount; }
	LegoS32 GetMaxBodyGroupCount() const { return m_maxBodyGroupCount; }
	LegoS32 GetMaxHatGroupCount() const { return m_maxHatGroupCount; }
	LegoS32 GetMaxBodyMaterialCount() const { return m_maxBodyMaterialCount; }
	LegoS32 GetMaxHatMaterialCount() const { return m_maxHatMaterialCount; }
	void SetResourceIndex(LegoS32 p_resourceIndex) { m_resourceIndex = p_resourceIndex; }

private:
	LegoS32 Reset();
	void LoadPartResource(LegoBool32 p_binary);
	void LoadMaterialAndTextureLists(LegoBool32 p_binary);
	LegoU32 ReplaceModelGroupMaterialIndex(GolAnimatedEntity* p_resourceModel, LegoU32 p_oldIndex, LegoU32 p_newIndex);
	void NormalizeHeadGroupOrder();
	void ComputeMaxVertexCounts();
	void ComputeMaxIndexCounts();
	void ComputeMaxGroupCounts();
	void ComputeMaxMaterialCounts();

	GdbPartLibrary m_partLibrary;       // 0x00
	GolD3DRenderDevice* m_renderer;     // 0x1c
	GolExport* m_golExport;             // 0x20
	GolWorldDatabase* m_partResource;   // 0x24
	GolModelBase* m_hatModel;           // 0x28
	LegoBool32 m_textureBinaryMode;     // 0x2c
	GolMaterialLibrary* m_materialList; // 0x30
	GolTextureList* m_textureList;      // 0x34
	DriverPartCatalog* m_partCatalog;   // 0x38
	LegoS32 m_maxBodyIndexCount;        // 0x3c
	LegoS32 m_maxHatIndexCount;         // 0x40
	LegoS32 m_maxBodyVertexCount;       // 0x44
	LegoS32 m_maxHatVertexCount;        // 0x48
	LegoS32 m_maxBodyGroupCount;        // 0x4c
	LegoS32 m_maxHatGroupCount;         // 0x50
	LegoS32 m_maxBodyMaterialCount;     // 0x54
	LegoS32 m_maxHatMaterialCount;      // 0x58
	LegoS32 m_resourceIndex;            // 0x5c
};

#endif // DRIVERPARTRESOURCES_H
