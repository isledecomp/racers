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
	m_unk0xf0 = NULL;
	m_unk0xf4 = NULL;
	m_unk0x10c = NULL;
	m_unk0xf8 = NULL;
	m_unk0x104 = NULL;
	m_unk0xfc = NULL;
	m_unk0x110 = NULL;
	m_unk0x100 = NULL;
	m_unk0x108 = NULL;
	m_unk0x114 = NULL;
}

// FUNCTION: GOLDP 0x10017200
GolWorldDatabaseEx::~GolWorldDatabaseEx()
{
	Destroy();
}

// FUNCTION: GOLDP 0x10017250
GolTextureList* GolWorldDatabaseEx::GetTextureList(LegoU32 p_index) const
{
	return &m_unk0xf0[p_index];
}

// FUNCTION: GOLDP 0x10017270
GolMaterialLibrary* GolWorldDatabaseEx::GetMaterialLibrary(LegoU32 p_index) const
{
	return &m_unk0xf4[p_index];
}

// FUNCTION: GOLDP 0x10017290
CmbModelPart* GolWorldDatabaseEx::GetModelPart(LegoU32 p_index) const
{
	return &m_unk0x10c[p_index];
}

// FUNCTION: GOLDP 0x100172b0
GolModelBase* GolWorldDatabaseEx::GetModel(LegoU32 p_index) const
{
	return &m_unk0xf8[p_index];
}

// FUNCTION: GOLDP 0x100172d0
GolModelMaterialTable* GolWorldDatabaseEx::GetMaterialTable(LegoU32 p_index) const
{
	return &m_unk0x104[p_index];
}

// FUNCTION: GOLDP 0x100172f0
GolSceneNode* GolWorldDatabaseEx::GetSceneNode(LegoU32 p_index) const
{
	return &m_unk0xfc[p_index];
}

// FUNCTION: GOLDP 0x10017310
GolBoundingShape* GolWorldDatabaseEx::GetBoundingShape(LegoU32 p_index) const
{
	return &m_unk0x110[p_index];
}

// FUNCTION: GOLDP 0x10017330
GolWorldEntity* GolWorldDatabaseEx::GetWorldEntity(LegoU32 p_index) const
{
	return &m_unk0x100[p_index];
}

// FUNCTION: GOLDP 0x10017350
MabMaterialAnimation* GolWorldDatabaseEx::GetMaterialAnimation(LegoU32 p_index) const
{
	return &m_unk0x108[p_index];
}

// FUNCTION: GOLDP 0x10017370
GolCameraBase* GolWorldDatabaseEx::GetCamera(LegoU32 p_index) const
{
	return &m_unk0x114[p_index];
}

// FUNCTION: GOLDP 0x10017390
void GolWorldDatabaseEx::AllocateResources()
{
	if (GetTextureListCount() != 0) {
		m_unk0xf0 = new GolD3DTextureList[GetTextureListCount()];
		if (m_unk0xf0 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetMaterialLibraryCount() != 0) {
		m_unk0xf4 = new GolSoftwareMaterialLibrary[GetMaterialLibraryCount()];
		if (m_unk0xf4 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetModelPartCount() != 0) {
		m_unk0x10c = new CmbModelPart[GetModelPartCount()];
		if (m_unk0x10c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetModelCount() != 0) {
		m_unk0xf8 = new GolModel[GetModelCount()];
		if (m_unk0xf8 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetMaterialTableCount() != 0) {
		m_unk0x104 = new GolModelMaterialTable[GetMaterialTableCount()];
		if (m_unk0x104 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetSceneNodeCount() != 0) {
		m_unk0xfc = new GolSceneTransformNode[GetSceneNodeCount()];
		if (m_unk0xfc == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetBoundingShapeCount() != 0) {
		m_unk0x110 = new GolBoundingShape[GetBoundingShapeCount()];
		if (m_unk0x110 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetSpriteCount() != 0) {
		m_unk0x100 = new GolBillboardEx[GetSpriteCount()];
		if (m_unk0x100 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetMaterialAnimationCount() != 0) {
		m_unk0x108 = new MabMaterialAnimation[GetMaterialAnimationCount()];
		if (m_unk0x108 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (GetCameraCount()) {
		m_unk0x114 = new GolCamera[GetCameraCount()];
		if (m_unk0x114 == NULL) {
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
		GetTextureList(i)->VTable0x24(textureRenderer, fileName, m_binary);
	}

	for (i = 0; i < m_materialLibraryCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_materialLibraryNames[i], ".mdf");
		GetMaterialLibrary(i)->VTable0x24(m_renderer, fileName, m_binary);
	}

	for (i = 0; i < m_modelPartCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_modelPartNames[i], ".adf");
		GetModelPart(i)->VTable0x14(fileName, m_binary);
	}

	for (i = 0; i < m_modelCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_modelNames[i], ".gdf");
		GetModel(i)->Load(m_renderer, fileName, m_binary);
	}

	for (i = 0; i < m_materialTableCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_materialTableNames[i], ".gdf");
		GetMaterialTable(i)->FUN_10025e60(m_renderer, fileName, m_binary);
	}

	for (i = 0; i < m_sceneNodeCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_sceneNodeNames[i], ".sdf");
		GetSceneNode(i)->VTable0x14(fileName, m_binary);
	}

	for (i = 0; i < m_boundingShapeCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_boundingShapeNames[i], ".bdf");
		GetBoundingShape(i)->Deserialize(fileName, m_binary);
	}

	for (i = 0; i < m_materialAnimationCount; i++) {
		LegoChar fileName[sizeof(GolName) + 5];
		BuildResourceFileName(fileName, m_materialAnimationNames[i], ".maf");
		GetMaterialAnimation(i)->VTable0x04(m_renderer, fileName, m_binary);
	}

	for (i = 0; i < m_spriteCount; i++) {
		WdbBillboardSprite* sprite = &m_spriteRecords[i];
		GolBillboardEx* billboard = &m_unk0x100[i];
		LegoFloat maxDistanceSquared = sprite->m_maxDistance * sprite->m_maxDistance;

		if (sprite->m_flags & WdbBillboardSprite::c_flagMaterialAssignment) {
			LegoU32 materialTableIndex = sprite->m_materialTableIndex;
			if (materialTableIndex >= m_materialTableCount) {
				GOL_FATALERROR_MESSAGE("Illegal mat assign reference");
			}

			billboard->ConfigureFromMaterialTable(
				&m_unk0x104[materialTableIndex],
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
	if (m_unk0x114) {
		delete[] m_unk0x114;
		m_unk0x114 = NULL;
	}
	if (m_unk0x100) {
		delete[] m_unk0x100;
		m_unk0x100 = NULL;
	}
	if (m_unk0x110) {
		delete[] m_unk0x110;
		m_unk0x110 = NULL;
	}
	if (m_unk0xfc) {
		delete[] m_unk0xfc;
		m_unk0xfc = NULL;
	}
	if (m_unk0x104) {
		delete[] m_unk0x104;
		m_unk0x104 = NULL;
	}
	if (m_unk0xf8) {
		delete[] m_unk0xf8;
		m_unk0xf8 = NULL;
	}
	if (m_unk0x10c) {
		delete[] m_unk0x10c;
		m_unk0x10c = NULL;
	}
	if (m_unk0xf4) {
		delete[] m_unk0xf4;
		m_unk0xf4 = NULL;
	}
	if (m_unk0xf0) {
		delete[] m_unk0xf0;
		m_unk0xf0 = NULL;
	}
	if (m_unk0x108) {
		delete[] m_unk0x108;
		m_unk0x108 = NULL;
	}

	GolWorldDatabase::Destroy();
}

// FUNCTION: GOLDP 0x100181b0
void GolWorldDatabaseEx::DrawCollidableEntities(GolRenderDevice* p_renderer)
{
	LegoU32 i;
	for (i = 0; i < m_collidableEntityCount; i++) {
		p_renderer->VTable0x90(&m_collidableEntities[i]);
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
		p_renderer->VTable0xb4(m_unk0x100[i]);
	}
}
