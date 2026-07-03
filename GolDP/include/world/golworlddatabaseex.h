#ifndef GOLWORLDDATABASEEX_H
#define GOLWORLDDATABASEEX_H

#include "compat.h"
#include "decomp.h"
#include "world/golworlddatabase.h"

class GolSoftwareMaterialLibrary;
class GolCamera;
class GolCameraBase;
class GolBoundingShape;
class CmbModelPart;
class GolBillboardEx;
class GolWorldEntity;
class GolModel;
class GolSceneTransformNode;
class MabMaterialAnimation;
class GolD3DTextureList;
class GolModelMaterialTable;
class GolSceneNode;

// SIZE 0x118
// VTABLE: GOLDP 0x1005690c
class GolWorldDatabaseEx : public GolWorldDatabase {
public:
	GolWorldDatabaseEx();
	~GolWorldDatabaseEx() override;
	void AllocateResources() override;                                          // vtable+0x08
	undefined4* LoadResources() override;                                       // vtable+0x0c
	void Destroy() override;                                                    // vtable+0x18
	void DrawCollidableEntities(GolRenderDevice*) override;                     // vtable+0x1c
	void DrawModelEntities(GolRenderDevice*) override;                          // vtable+0x20
	void DrawAnimatedEntities(GolRenderDevice*) override;                       // vtable+0x24
	void DrawSprites(GolRenderDevice*) override;                                // vtable+0x28
	GolTextureList* GetTextureList(LegoU32 p_index) const override;             // vtable+0x2c
	GolMaterialLibrary* GetMaterialLibrary(LegoU32 p_index) const override;     // vtable+0x30
	CmbModelPart* GetModelPart(LegoU32 p_index) const override;                 // vtable+0x34
	GolModelBase* GetModel(LegoU32 p_index) const override;                     // vtable+0x38
	GolModelMaterialTable* GetMaterialTable(LegoU32 p_index) const override;    // vtable+0x3c
	GolSceneNode* GetSceneNode(LegoU32 p_index) const override;                 // vtable+0x40
	GolBoundingShape* GetBoundingShape(LegoU32 p_index) const override;         // vtable+0x44
	GolWorldEntity* GetWorldEntity(LegoU32 p_index) const override;             // vtable+0x48
	MabMaterialAnimation* GetMaterialAnimation(LegoU32 p_index) const override; // vtable+0x4c
	GolCameraBase* GetCamera(LegoU32 p_index) const override;                   // vtable+0x50

	// SYNTHETIC: GOLDP 0x100171e0
	// GolWorldDatabaseEx::`scalar deleting destructor'

private:
	GolD3DTextureList* m_textureLists;               // 0xf0
	GolSoftwareMaterialLibrary* m_materialLibraries; // 0xf4
	GolModel* m_models;                              // 0xf8
	GolSceneTransformNode* m_sceneNodes;             // 0xfc
	GolBillboardEx* m_billboards;                    // 0x100
	GolModelMaterialTable* m_materialTables;         // 0x104
	MabMaterialAnimation* m_materialAnimations;      // 0x108
	CmbModelPart* m_modelParts;                      // 0x10c
	GolBoundingShape* m_boundingShapes;              // 0x110
	GolCamera* m_cameras;                            // 0x114
};

#endif // GOLWORLDDATABASEEX_H
