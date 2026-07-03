#include "racer/driverheadbuilder.h"

#include "core/gol.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golstream.h"
#include "model/gdbpartlibrary.h"
#include "racer/driverpartcatalog.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(DriverHeadBuilder, 0x50)
DECOMP_SIZE_ASSERT(DriverHeadBuilder::LoadParams, 0x18)

// FUNCTION: LEGORACERS 0x00499110
DriverHeadBuilder::DriverHeadBuilder()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00499120
DriverHeadBuilder::~DriverHeadBuilder()
{
	ReleaseResources();
}

// FUNCTION: LEGORACERS 0x00499130
void DriverHeadBuilder::Reset()
{
	m_golExport = NULL;
	m_renderer = NULL;
	m_worldDatabase = NULL;
	m_partCatalog = NULL;
	m_partLibrary = NULL;
	m_resourceIndex = 0;
	::memset(m_hatModelUsed, 0, sizeof(m_hatModelUsed));
	::memset(m_hatModels, 0, sizeof(m_hatModels));
}

// FUNCTION: LEGORACERS 0x00499160
LegoBool32 DriverHeadBuilder::Load(const LoadParams* p_params, LegoS32 p_resourceIndex)
{
	ReleaseResources();

	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_partCatalog = p_params->m_partCatalog;
	m_resourceIndex = p_resourceIndex;
	m_partLibrary = p_params->m_partLibrary;

	LoadHeadResource(p_params->m_binary);
	CreateHatModels();

	GolModelBase* model = LoadHatModel(0);
	model->GetMutableGroups()[0] = 0xc0000000;
	model->SetDirty(TRUE);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004991c0
LegoBool32 DriverHeadBuilder::ReleaseResources()
{
	if (m_worldDatabase == NULL) {
		return TRUE;
	}

	m_golExport->DestroyWorldDatabase(m_worldDatabase);

	for (LegoS32 i = 0; i < 7; i++) {
		if (m_hatModels[i] != NULL) {
			m_golExport->DestroyModel(m_hatModels[i]);
		}
	}

	Reset();
	return m_worldDatabase == NULL;
}

// FUNCTION: LEGORACERS 0x00499210
void DriverHeadBuilder::LoadHeadResource(LegoBool32 p_binary)
{
	const LegoChar* headModelFileName = m_partCatalog->GetHeadModelFileName();
	const LegoChar* headModelDirectory = m_partCatalog->GetHeadModelDirectory();

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString(headModelDirectory);
	}

	m_worldDatabase = m_golExport->CreateWorldDatabase();
	if (m_worldDatabase == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_worldDatabase->Load(m_renderer, headModelFileName, p_binary, 1.0f);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x00499290
void DriverHeadBuilder::CreateHatModels()
{
	for (LegoS32 i = 0; i < 7; i++) {
		m_hatModels[i] = m_golExport->CreateModel();
		if (m_hatModels[i] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_hatModels[i]->Allocate(m_renderer, 2, 0x258, 0x12c, 0x64, 3);
	}

	::memset(m_hatModelUsed, 0, sizeof(m_hatModelUsed));
}

// FUNCTION: LEGORACERS 0x004992f0
void DriverHeadBuilder::MarkHatModelUsed(GolModelBase* p_model)
{
	for (LegoS32 i = 0; i < 7; i++) {
		if (m_hatModels[i] == p_model) {
			m_hatModelUsed[i] = TRUE;
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x00499320
GolModelBase* DriverHeadBuilder::LoadHatModel(LegoS32 p_index)
{
	GolName name;
	m_partCatalog->CopyHatName(p_index, name);

	for (LegoS32 modelIndex = 0; modelIndex < 7; modelIndex++) {
		if (m_hatModelUsed[modelIndex] == 0) {
			m_partLibrary->CopyPartToModel(m_renderer, m_hatModels[modelIndex], name);
			m_hatModelUsed[modelIndex] = TRUE;
			return m_hatModels[modelIndex];
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00499380
GolModelBase* DriverHeadBuilder::GetFaceModel(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_partCatalog->CopyDefaultFaceName(p_index, modelName, materialName);

	GolWorldDatabase* db = m_worldDatabase;
	GolModelEntity* entity;
	if (db->m_modelEntityNames.GetNameEntries() == NULL) {
		entity = NULL;
	}
	else {
		entity = static_cast<GolModelEntity*>(db->m_modelEntityNames.GetName(modelName));
	}

	return entity->GetModel(0);
}

// FUNCTION: LEGORACERS 0x004993d0
GolModelBase* DriverHeadBuilder::GetTorsoModel(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_partCatalog->CopyTorsoName(p_index, modelName, materialName);

	GolWorldDatabase* db = m_worldDatabase;
	GolModelEntity* entity;
	if (db->m_modelEntityNames.GetNameEntries() == NULL) {
		entity = NULL;
	}
	else {
		entity = static_cast<GolModelEntity*>(db->m_modelEntityNames.GetName(modelName));
	}

	return entity->GetModel(0);
}

// FUNCTION: LEGORACERS 0x00499420
GolModelBase* DriverHeadBuilder::GetLegModel(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_partCatalog->CopyLegName(p_index, modelName, materialName);

	GolWorldDatabase* db = m_worldDatabase;
	GolModelEntity* entity;
	if (db->m_modelEntityNames.GetNameEntries() == NULL) {
		entity = NULL;
	}
	else {
		entity = static_cast<GolModelEntity*>(db->m_modelEntityNames.GetName(modelName));
	}

	return entity->GetModel(0);
}

// FUNCTION: LEGORACERS 0x00499470
void* DriverHeadBuilder::FindFaceMaterial(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_partCatalog->CopyDefaultFaceName(p_index, modelName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

// FUNCTION: LEGORACERS 0x004994b0
void* DriverHeadBuilder::FindTorsoMaterial(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_partCatalog->CopyTorsoName(p_index, modelName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

// FUNCTION: LEGORACERS 0x004994f0
void* DriverHeadBuilder::FindLegMaterial(LegoS32 p_index)
{
	GolName modelName;
	GolName materialName;
	m_partCatalog->CopyLegName(p_index, modelName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}
