#include "world/golworlddatabaseex.h"

#include "camera/golcamera.h"
#include "camera/golscenetransformnode.h"
#include "cmbmodelpart.h"
#include "golanimatedentity.h"
#include "golboundingshape.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golmodelentity.h"
#include "golmodelmaterialtable.h"
#include "mabmaterialanimation.h"
#include "material/gold3dtexturelist.h"
#include "material/golsoftwaremateriallibrary.h"
#include "mesh/golmodel.h"
#include "render/gold3drenderdevice.h"
#include "scene/golbillboardex.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolWorldDatabaseEx, 0x118)

inline static void BuildResourceFileName(LegoChar* p_dest, const LegoChar* p_name, const LegoChar* p_suffix)
{
	::memcpy(p_dest, p_name, sizeof(GolName));
	p_dest[sizeof(GolName)] = '\0';
	::strcat(p_dest, p_suffix);
}

// FUNCTION: GOLDP 0x10017190
GolWorldDatabaseEx::GolWorldDatabaseEx()
{
	m_textureLists = NULL;
	m_materialLibraries = NULL;
	m_modelParts = NULL;
	m_models = NULL;
	m_materialTables = NULL;
	m_sceneNodes = NULL;
	m_boundingShapes = NULL;
	m_billboards = NULL;
	m_materialAnimations = NULL;
	m_cameras = NULL;
}

// FUNCTION: GOLDP 0x10017200
GolWorldDatabaseEx::~GolWorldDatabaseEx()
{
	Destroy();
}

// FUNCTION: GOLDP 0x10017250
GolTextureList* GolWorldDatabaseEx::GetTextureList(LegoU32 p_index) const
{
	return &m_textureLists[p_index];
}

// FUNCTION: GOLDP 0x10017270
GolMaterialLibrary* GolWorldDatabaseEx::GetMaterialLibrary(LegoU32 p_index) const
{
	return &m_materialLibraries[p_index];
}

// FUNCTION: GOLDP 0x10017290
CmbModelPart* GolWorldDatabaseEx::GetModelPart(LegoU32 p_index) const
{
	return &m_modelParts[p_index];
}

// FUNCTION: GOLDP 0x100172b0
GolModelBase* GolWorldDatabaseEx::GetModel(LegoU32 p_index) const
{
	return &m_models[p_index];
}

// FUNCTION: GOLDP 0x100172d0
GolModelMaterialTable* GolWorldDatabaseEx::GetMaterialTable(LegoU32 p_index) const
{
	return &m_materialTables[p_index];
}

// FUNCTION: GOLDP 0x100172f0
GolSceneNode* GolWorldDatabaseEx::GetSceneNode(LegoU32 p_index) const
{
	return &m_sceneNodes[p_index];
}

// FUNCTION: GOLDP 0x10017310
GolBoundingShape* GolWorldDatabaseEx::GetBoundingShape(LegoU32 p_index) const
{
	return &m_boundingShapes[p_index];
}

// FUNCTION: GOLDP 0x10017330
GolWorldEntity* GolWorldDatabaseEx::GetWorldEntity(LegoU32 p_index) const
{
	return &m_billboards[p_index];
}

// FUNCTION: GOLDP 0x10017350
MabMaterialAnimation* GolWorldDatabaseEx::GetMaterialAnimation(LegoU32 p_index) const
{
	return &m_materialAnimations[p_index];
}

// FUNCTION: GOLDP 0x10017370
GolCameraBase* GolWorldDatabaseEx::GetCamera(LegoU32 p_index) const
{
	return &m_cameras[p_index];
}

// FUNCTION: GOLDP 0x10017390
void GolWorldDatabaseEx::AllocateResources()
{
	if (GetTextureListCount() != 0) {
		m_textureLists = new GolD3DTextureList[GetTextureListCount()];
		if (m_textureLists == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetMaterialLibraryCount() != 0) {
		m_materialLibraries = new GolSoftwareMaterialLibrary[GetMaterialLibraryCount()];
		if (m_materialLibraries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetModelPartCount() != 0) {
		m_modelParts = new CmbModelPart[GetModelPartCount()];
		if (m_modelParts == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetModelEventCount() != 0) {
		m_models = new GolModel[GetModelEventCount()];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetMaterialTableCount() != 0) {
		m_materialTables = new GolModelMaterialTable[GetMaterialTableCount()];
		if (m_materialTables == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetSceneNodeCount() != 0) {
		m_sceneNodes = new GolSceneTransformNode[GetSceneNodeCount()];
		if (m_sceneNodes == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetBoundingShapeCount() != 0) {
		m_boundingShapes = new GolBoundingShape[GetBoundingShapeCount()];
		if (m_boundingShapes == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetSpriteCount() != 0) {
		m_billboards = new GolBillboardEx[GetSpriteCount()];
		if (m_billboards == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetMaterialAnimationCount() != 0) {
		m_materialAnimations = new MabMaterialAnimation[GetMaterialAnimationCount()];
		if (m_materialAnimations == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetCameraCount()) {
		m_cameras = new GolCamera[GetCameraCount()];
		if (m_cameras == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// STUB: GOLDP 0x10017ac0
undefined4* GolWorldDatabaseEx::LoadResources()
{
	LegoU32 i;
	GolD3DRenderDevice* textureRenderer = static_cast<GolD3DRenderDevice*>(m_renderer);

	for (i = 0; i < m_textureListCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_textureListNames[i], ".tdf");
		GetTextureList(i)->Load(textureRenderer, fileName, m_binary);
	}

	for (i = 0; i < m_materialLibraryCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_materialLibraryNames[i], ".mdf");
		GetMaterialLibrary(i)->Load(m_renderer, fileName, m_binary);
	}

	for (i = 0; i < m_modelPartCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_modelPartNames[i], ".adf");
		GetModelPart(i)->Load(fileName, m_binary);
	}

	for (i = 0; i < m_modelCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_modelNames[i], ".gdf");
		GetModel(i)->Load(m_renderer, fileName, m_binary);
	}

	for (i = 0; i < m_materialTableCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_materialTableNames[i], ".gdf");
		GetMaterialTable(i)->Load(m_renderer, fileName, m_binary);
	}

	for (i = 0; i < m_sceneNodeCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_sceneNodeNames[i], ".sdf");
		GetSceneNode(i)->Load(fileName, m_binary);
	}

	for (i = 0; i < m_boundingShapeCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_boundingShapeNames[i], ".bdf");
		GetBoundingShape(i)->Deserialize(fileName, m_binary);
	}

	for (i = 0; i < m_materialAnimationCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_materialAnimationNames[i], ".maf");
		GetMaterialAnimation(i)->Load(m_renderer, fileName, m_binary);
	}

	for (i = 0; i < m_spriteCount; i++) {
		WdbBillboardSprite* sprite = &m_spriteRecords[i];
		GolBillboardEx* billboard = &m_billboards[i];
		LegoFloat maxDistanceSquared = sprite->m_maxDistance * sprite->m_maxDistance;

		if (sprite->m_flags & WdbBillboardSprite::c_flagMaterialAssignment) {
			LegoU32 materialTableIndex = sprite->m_materialTableIndex;
			if (materialTableIndex >= m_materialTableCount) {
				GOL_FATALERROR_MESSAGE("Illegal mat assign reference");
			}

			billboard->ConfigureFromMaterialTable(
				&m_materialTables[materialTableIndex],
				sprite->m_materialIndex,
				sprite->m_width,
				sprite->m_height,
				maxDistanceSquared
			);
		}
		else {
			if (sprite->m_materialName[0] == '\0') {
				GOL_FATALERROR_MESSAGE("Sprite is missing material name");
			}

			GolMaterial* material = m_renderer->FindMaterialByName(sprite->m_materialName);
			if (material == NULL) {
				LegoChar message[64];
				::memset(message, 0, sizeof(message));
				::strncpy(message, sprite->m_materialName, sizeof(GolName));
				::strcat(message, " sprite material not found");
				GOL_FATALERROR_MESSAGE(message);
			}

			billboard->Configure(material, sprite->m_width, sprite->m_height, maxDistanceSquared);
		}

		billboard->SetPosition(sprite->m_position);
		if (sprite->m_flags & WdbBillboardSprite::c_flagAxisLocked) {
			billboard->EnableAxisLock();
			billboard->SetAxis(sprite->m_axis);
		}

		BindSpriteMaterialAnimation(billboard, sprite);
	}

	return NULL;
}

// FUNCTION: GOLDP 0x100180a0
void GolWorldDatabaseEx::Destroy()
{
	if (m_cameras) {
		delete[] m_cameras;
		m_cameras = NULL;
	}
	if (m_billboards) {
		delete[] m_billboards;
		m_billboards = NULL;
	}
	if (m_boundingShapes) {
		delete[] m_boundingShapes;
		m_boundingShapes = NULL;
	}
	if (m_sceneNodes) {
		delete[] m_sceneNodes;
		m_sceneNodes = NULL;
	}
	if (m_materialTables) {
		delete[] m_materialTables;
		m_materialTables = NULL;
	}
	if (m_models) {
		delete[] m_models;
		m_models = NULL;
	}
	if (m_modelParts) {
		delete[] m_modelParts;
		m_modelParts = NULL;
	}
	if (m_materialLibraries) {
		delete[] m_materialLibraries;
		m_materialLibraries = NULL;
	}
	if (m_textureLists) {
		delete[] m_textureLists;
		m_textureLists = NULL;
	}
	if (m_materialAnimations) {
		delete[] m_materialAnimations;
		m_materialAnimations = NULL;
	}

	GolWorldDatabase::Destroy();
}

// FUNCTION: GOLDP 0x100181b0
void GolWorldDatabaseEx::DrawCollidableEntities(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_collidableEntityCount; i++) {
		p_renderer->DrawCollidableEntity(&m_collidableEntities[i]);
	}
}

// FUNCTION: GOLDP 0x100181f0
void GolWorldDatabaseEx::DrawModelEntities(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_modelEntityCount; i++) {
		m_modelEntities[i].Draw(*p_renderer);
	}
}

// FUNCTION: GOLDP 0x10018230
void GolWorldDatabaseEx::DrawAnimatedEntities(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_animatedEntityCount; i++) {
		m_animatedEntities[i].Draw(*p_renderer);
	}
}

// FUNCTION: GOLDP 0x10018270
void GolWorldDatabaseEx::DrawSprites(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_spriteCount; i++) {
		p_renderer->DrawBillboard(m_billboards[i]);
	}
}
