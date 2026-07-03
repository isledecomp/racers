#ifndef DRIVERMODELBUILDER_H
#define DRIVERMODELBUILDER_H

#include "decomp.h"
#include "golmaterial.h"
#include "types.h"

class GolExport;
class GolBmpFile;
class GolMaterialLibrary;
class GolD3DRenderDevice;
class GolTextureList;
class MusicInstance;
class MenuManager;
class MusicGroup;
class DriverPartResources;
class GolModelBase;
class GolSceneNode;
class CmbModelPart;
struct DriverCosmetics;

// SIZE 0x88
class DriverModelBuilder {
public:
	enum {
		c_menuFlowNewRacer = 1 << 0,
		c_menuFlowVersus = 1 << 1,
		c_menuFlowUnlockNotice = 1 << 2,
		c_menuFlowLoadRacer = 1 << 3,
		c_menuFlowSaveReminder = 1 << 4,
	};

	// SIZE 0x14
	struct ModelSummary {
		LegoS32 m_vertexCount;   // 0x00
		LegoS32 m_indexCount;    // 0x04
		LegoS32 m_groupCount;    // 0x08
		LegoS32 m_materialCount; // 0x0c
		GolModelBase* m_model;   // 0x10
	};

	// SIZE 0x10
	struct LoadParams {
		GolExport* m_golExport;               // 0x00
		GolD3DRenderDevice* m_renderer;       // 0x04
		LegoU32 m_menuId;                     // 0x08
		DriverPartResources* m_partResources; // 0x0c
	};

	DriverModelBuilder();
	~DriverModelBuilder();

	void ResetMenuState();
	undefined4 Load(const LoadParams* p_params);
	LegoBool32 ReleaseMenuResources();
	void RefreshMenuResources();
	GolModelBase* BuildDriverModel(DriverCosmetics* p_cosmetics, GolModelBase* p_model, undefined4 p_vertexType);
	GolSceneNode* GetBodySceneNode(DriverCosmetics* p_cosmetics);
	CmbModelPart* GetBodyModelPart(DriverCosmetics* p_cosmetics);
	void GetMaxMergedCounts(undefined4* p_dest);
	void ApplyFaceExpression(GolModelBase* p_model, DriverCosmetics* p_cosmetics);

	void Reset()
	{
		m_menuFlowFlags = 0;
		m_musicInstance = NULL;
	}

	MusicGroup* GetMusicGroup() { return m_musicGroup; }
	void SetMusicGroup(MusicGroup* p_musicGroup) { m_musicGroup = p_musicGroup; }
	MusicInstance* GetMusicInstance() { return m_musicInstance; }
	void SetMusicInstance(MusicInstance* p_musicInstance) { m_musicInstance = p_musicInstance; }
	LegoBool32 HasMenuResources() const { return m_menuId != 0; }
	void SetExpressionMask(undefined4 p_expressionMask) { m_expressionMask = p_expressionMask; }
	undefined4 GetMenuFlowFlags() const { return m_menuFlowFlags; }
	void SetMenuFlowFlags(undefined4 p_menuFlowFlags) { m_menuFlowFlags = p_menuFlowFlags; }
	LegoS32 GetSaveSlot() const { return m_saveSlot; }
	void SetSaveSlot(LegoS32 p_saveSlot) { m_saveSlot = p_saveSlot; }

private:
	friend class MenuManager;

	void CreateMenuResources();
	void InitializeDefaultMaterialParams();
	void LoadFaceTexture(const LegoChar* p_name, GolBmpFile* p_imageFile);
	void CreateFaceMaterial(const LegoChar* p_name);
	void LoadFaceExpressionMaterials(LegoS32 p_faceIndex);
	void SummarizeModel(GolModelBase* p_model, ModelSummary* p_summary);
	LegoBool32 FitsOutputModel() const;
	void MergeHeadMaterials();
	LegoBool32 NeedsNewOutputModel(GolModelBase* p_model) const;
	GolModelBase* CreateOutputModel(undefined4 p_vertexType);
	void CopyModelVertices(GolModelBase* p_sourceModel, GolModelBase* p_destModel, LegoU32 p_vertexOffset);
	void CopyModelIndices(GolModelBase* p_sourceModel, GolModelBase* p_destModel, LegoU32 p_indexOffset);
	void CopyBodyIntoOutput();
	void MergeHeadModel();
	void ReplaceMaterialTexture(GolMaterial* p_material, const LegoChar* p_name);
	GolModelBase* MergeModels(DriverCosmetics* p_cosmetics, GolModelBase* p_model, undefined4 p_vertexType);
	void CopyGroupsUntilFace();

	LegoU32 m_menuId;                          // 0x00
	LegoU32 m_textureCount;                    // 0x04
	LegoU32 m_materialCount;                   // 0x08
	undefined4 m_unk0x0c;                      // 0x0c
	undefined4 m_expressionMask;               // 0x10
	GolExport* m_golExport;                    // 0x14
	GolD3DRenderDevice* m_renderer;            // 0x18
	GolTextureList* m_textureList;             // 0x1c
	GolMaterialLibrary* m_materialList;        // 0x20
	GolMaterialParams m_defaultMaterialParams; // 0x24
	DriverPartResources* m_partResources;      // 0x38
	ModelSummary m_bodySummary;                // 0x3c
	ModelSummary m_headSummary;                // 0x50
	ModelSummary m_outputSummary;              // 0x64
	undefined4 m_menuFlowFlags;                // 0x78
	MusicGroup* m_musicGroup;                  // 0x7c
	MusicInstance* m_musicInstance;            // 0x80
	LegoS32 m_saveSlot;                        // 0x84
};

#endif // DRIVERMODELBUILDER_H
