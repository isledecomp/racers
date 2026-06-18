#include "racer/driverpartresources.h"

#include "core/gol.h"
#include "duskwindbananarelic0x24.h"
#include "gdbvertexarray0xc.h"
#include "golanimatedentity.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golmodelbase.h"
#include "golmodelmaterialtable.h"
#include "golname.h"
#include "golstream.h"
#include "igdbmodelindexarray0x8.h"
#include "material/golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "racer/driverpartcatalog.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(DriverPartResources, 0x60)

// GLOBAL: LEGORACERS 0x004be390
static LegoS32 g_resourceBinaryMode = TRUE;

// FUNCTION: LEGORACERS 0x00414840
static LegoS32 SetResourceBinaryMode(LegoS32 p_binary)
{
	g_resourceBinaryMode = p_binary;
	return p_binary;
}

// FUNCTION: LEGORACERS 0x00497e40
DriverPartResources::DriverPartResources()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00497e90
DriverPartResources::~DriverPartResources()
{
	ReleaseResources();
}

// FUNCTION: LEGORACERS 0x00497ee0
LegoS32 DriverPartResources::Reset()
{
	m_golExport = NULL;
	m_renderer = NULL;
	m_partResource = NULL;
	m_partCatalog = NULL;
	m_hatModel = NULL;
	m_materialList = NULL;
	m_textureList = NULL;
	m_maxBodyIndexCount = 0;
	m_maxBodyVertexCount = 0;
	m_maxBodyGroupCount = 0;
	m_maxBodyMaterialCount = 0;
	m_maxHatIndexCount = 0;
	m_maxHatVertexCount = 0;
	m_maxHatGroupCount = 0;
	m_maxHatMaterialCount = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x00497f10
GolWorldDatabase* DriverPartResources::Load(const LoadParams* p_params, LegoS32 p_resourceIndex)
{
	ReleaseResources();
	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_resourceIndex = p_resourceIndex;
	m_partCatalog = p_params->m_partCatalog;
	m_textureBinaryMode = p_params->m_textureBinaryMode;

	LoadMaterialAndTextureLists(p_params->m_binary);
	LoadPartResource(p_params->m_binary);
	NormalizeHeadGroupOrder();

	m_hatModel = m_golExport->VTable0x14();
	m_hatModel->VTable0x18(m_renderer, 2, 600, 300, 100, 3);

	ComputeMaxVertexCounts();
	ComputeMaxIndexCounts();
	ComputeMaxGroupCounts();
	ComputeMaxMaterialCounts();
	return m_partResource;
}

// FUNCTION: LEGORACERS 0x00497fb0
LegoBool32 DriverPartResources::ReleaseResources()
{
	if (m_partResource == NULL) {
		return TRUE;
	}

	if (m_hatModel != NULL) {
		m_golExport->VTable0x48(m_hatModel);
	}
	if (m_materialList != NULL) {
		m_golExport->DestroyMaterialList(m_materialList);
	}
	if (m_textureList != NULL) {
		m_golExport->DestroyTextureList(m_textureList);
	}
	if (m_partResource != NULL) {
		m_golExport->VTable0x3c(m_partResource);
	}

	Reset();
	return m_partResource == NULL;
}

// FUNCTION: LEGORACERS 0x00498020
void DriverPartResources::LoadPartResource(LegoBool32 p_binary)
{
	LegoChar fileName[16];
	::strcpy(fileName, m_partCatalog->GetBodyModelFileName(m_resourceIndex));
	const LegoChar* directory = m_partCatalog->GetBodyModelDirectory(m_resourceIndex);

	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString(directory);
	}

	m_partResource = m_golExport->VTable0x08();
	if (m_partResource == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	m_partResource->VTable0x14(m_renderer, fileName, p_binary, 1.0f);

	fileName[::strlen(fileName) - 3] = 'g';
	fileName[::strlen(fileName) - 2] = 'c';
	m_partLibrary.Load(fileName, p_binary);

	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}
}

// FUNCTION: LEGORACERS 0x00498120
void DriverPartResources::LoadMaterialAndTextureLists(LegoBool32 p_binary)
{
	m_textureList = m_golExport->CreateTextureList();
	m_materialList = m_golExport->CreateMaterialList();
	if (m_textureList == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	SetResourceBinaryMode(m_textureBinaryMode);
	m_textureList->VTable0x24(m_renderer, "bodypart.tdf", p_binary);
	SetResourceBinaryMode(TRUE);
	m_materialList->VTable0x24(m_renderer, "bodypart.mdf", p_binary);
}

// FUNCTION: LEGORACERS 0x004981a0
static LegoU32 __stdcall ReplaceModelGroupMaterialIndex(
	GolAnimatedEntity* p_resourceModel,
	LegoU32 p_oldIndex,
	LegoU32 p_newIndex
)
{
	GolModelBase* model = p_resourceModel->GetModel(0);
	LegoU32 oldGroupTag = (p_oldIndex & 0x00ffffff) | 0x80000000;
	LegoS32 groupIndex = 0;
	LegoS32 groupCount = static_cast<LegoS32>(model->GetGroupCount());
	LegoU32* groups = model->GetMutableGroups();

	LegoS32 currentIndex;
	do {
		currentIndex = groupIndex;
		groupIndex++;
	} while (groups[currentIndex] != oldGroupTag && groupIndex < groupCount);

	if (groupIndex != groupCount) {
		oldGroupTag = (p_newIndex & 0x00ffffff) | 0x80000000;
		groups[groupIndex - 1] = oldGroupTag;
	}

	return oldGroupTag;
}

// STUB: LEGORACERS 0x004981f0
void DriverPartResources::NormalizeHeadGroupOrder()
{
	LegoS32 remainingModels = m_partResource->GetUnk0x54();
	if (remainingModels > 0) {
		GolAnimatedEntity* resourceModel = m_partResource->GetUnk0xa0();
		do {
			MaterialTable0x0c* materialTable = resourceModel->GetMaterialTable(0);
			if (materialTable == NULL) {
				materialTable = resourceModel->GetModel(0)->GetMaterialTable();
			}

			LegoS32 materialIndex = 1;
			LegoS32 materialCount = materialTable->m_count;
			if (materialCount > 1) {
				do {
					DuskwindBananaRelic0x24* material =
						static_cast<DuskwindBananaRelic0x24*>(materialTable->GetPosition(materialIndex));
					if (material != NULL) {
						DuskWindName0x8 materialName;
						materialName = material->GetNameRecord();

						if (::strncmp(materialName.m_unk0x0, "face", sizeof(GolName)) == 0) {
							DuskwindBananaRelic0x24* firstMaterial =
								static_cast<DuskwindBananaRelic0x24*>(materialTable->GetPosition(0));
							materialTable->SetPosition(0, material);
							materialTable->SetPosition(materialIndex, firstMaterial);
							ReplaceModelGroupMaterialIndex(resourceModel, materialIndex, 0xffff);
							ReplaceModelGroupMaterialIndex(resourceModel, 0, materialIndex);
							ReplaceModelGroupMaterialIndex(resourceModel, 0xffff, 0);
						}
					}

					materialIndex++;
				} while (materialIndex < materialCount);
			}

			resourceModel++;
			remainingModels--;
		} while (remainingModels != 0);
	}
}

// FUNCTION: LEGORACERS 0x00498300
void DriverPartResources::ComputeMaxVertexCounts()
{
	GdbVertexArray0xc* vertexArray;
	for (LegoS32 bodyIndex = 0; bodyIndex < static_cast<LegoS32>(m_partResource->GetUnk0x54()); bodyIndex++) {
		GolModelBase* model = GetBodyModel(bodyIndex);
		model->VTable0x28(&vertexArray);
		if (static_cast<LegoS32>(vertexArray->GetCount()) > m_maxBodyVertexCount) {
			m_maxBodyVertexCount = vertexArray->GetCount();
		}
		model->VTable0x2c(0, FALSE);
	}

	for (LegoS32 hatIndex = 0; hatIndex < m_partCatalog->GetHatCount(); hatIndex++) {
		GolModelBase* model = LoadHatModel(hatIndex);
		model->VTable0x28(&vertexArray);
		if (static_cast<LegoS32>(vertexArray->GetCount()) > m_maxHatVertexCount) {
			m_maxHatVertexCount = vertexArray->GetCount();
		}
		model->VTable0x2c(0, FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004983a0
void DriverPartResources::ComputeMaxIndexCounts()
{
	for (LegoS32 bodyIndex = 0; bodyIndex < static_cast<LegoS32>(m_partResource->GetUnk0x54()); bodyIndex++) {
		GolModelBase* model = GetBodyModel(bodyIndex);
		LegoS32 count = model->GetIndexArray()->GetCount();
		if (count > m_maxBodyIndexCount) {
			m_maxBodyIndexCount = count;
		}
	}

	for (LegoS32 hatIndex = 0; hatIndex < m_partCatalog->GetHatCount(); hatIndex++) {
		GolModelBase* model = LoadHatModel(hatIndex);
		LegoS32 count = model->GetIndexArray()->GetCount();
		if (count > m_maxHatIndexCount) {
			m_maxHatIndexCount = count;
		}
	}
}

// FUNCTION: LEGORACERS 0x00498410
void DriverPartResources::ComputeMaxGroupCounts()
{
	for (LegoS32 bodyIndex = 0; bodyIndex < static_cast<LegoS32>(m_partResource->GetUnk0x54()); bodyIndex++) {
		GolModelBase* model = GetBodyModel(bodyIndex);
		LegoS32 count = model->GetGroupCount();
		if (count > m_maxBodyGroupCount) {
			m_maxBodyGroupCount = count;
		}
	}

	for (LegoS32 hatIndex = 0; hatIndex < m_partCatalog->GetHatCount(); hatIndex++) {
		GolModelBase* model = LoadHatModel(hatIndex);
		LegoS32 count = model->GetGroupCount();
		if (count > m_maxHatGroupCount) {
			m_maxHatGroupCount = count;
		}
	}
}

// FUNCTION: LEGORACERS 0x00498470
void DriverPartResources::ComputeMaxMaterialCounts()
{
	for (LegoS32 bodyIndex = 0; bodyIndex < static_cast<LegoS32>(m_partResource->GetUnk0x54()); bodyIndex++) {
		GolModelBase* model = GetBodyModel(bodyIndex);
		LegoS32 count = model->GetMaterialTable()->GetCount();
		if (count > m_maxBodyMaterialCount) {
			m_maxBodyMaterialCount = count;
		}
	}

	for (LegoS32 hatIndex = 0; hatIndex < m_partCatalog->GetHatCount(); hatIndex++) {
		GolModelBase* model = LoadHatModel(hatIndex);
		LegoS32 count = model->GetMaterialTable()->GetCount();
		if (count > m_maxHatMaterialCount) {
			m_maxHatMaterialCount = count;
		}
	}
}

// FUNCTION: LEGORACERS 0x004984d0
GolModelBase* DriverPartResources::LoadHatModel(LegoS32 p_index)
{
	GolName name;
	m_partCatalog->CopyHeadHatName(p_index, name);
	m_partLibrary.CopyPartToModel(m_renderer, m_hatModel, name);
	return m_hatModel;
}

// FUNCTION: LEGORACERS 0x00498510
GolModelBase* DriverPartResources::GetBodyModel(LegoS32 p_index)
{
	GolName name;
	if (m_resourceIndex == 1) {
		m_partCatalog->CopyBodyModelName(4, name);
	}
	else {
		m_partCatalog->CopyBodyModelName(p_index, name);
	}

	GolAnimatedEntity* model = m_partResource->FindUnk0xc0(name);
	return model->GetModel(0);
}

// FUNCTION: LEGORACERS 0x00498570
GolSceneNode* DriverPartResources::GetBodySceneNode(LegoS32 p_index)
{
	GolName name;
	if (m_resourceIndex == 1) {
		m_partCatalog->CopyBodyModelName(4, name);
	}
	else {
		m_partCatalog->CopyBodyModelName(p_index, name);
	}

	GolAnimatedEntity* model = m_partResource->FindUnk0xc0(name);
	return model->VTable0x58(0);
}

// FUNCTION: LEGORACERS 0x004985e0
CmbModelPart0x34* DriverPartResources::GetBodyModelPart(LegoS32 p_index)
{
	GolName name;
	if (m_resourceIndex == 1) {
		m_partCatalog->CopyBodyModelName(4, name);
	}
	else {
		m_partCatalog->CopyBodyModelName(p_index, name);
	}

	GolAnimatedEntity* model = m_partResource->FindUnk0xc0(name);
	return model->GetModelPart(0);
}

// FUNCTION: LEGORACERS 0x00498640
DuskwindBananaRelic0x24* DriverPartResources::FindFaceMaterial(LegoS32 p_index)
{
	GolName unusedName;
	GolName materialName;
	m_partCatalog->CopyDefaultFaceName(p_index, unusedName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

// FUNCTION: LEGORACERS 0x00498680
DuskwindBananaRelic0x24* DriverPartResources::FindTorsoMaterial(LegoS32 p_index)
{
	GolName unusedName;
	GolName materialName;
	m_partCatalog->CopyTorsoName(p_index, unusedName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

// FUNCTION: LEGORACERS 0x004986c0
DuskwindBananaRelic0x24* DriverPartResources::FindLegMaterial(LegoS32 p_index)
{
	GolName unusedName;
	GolName materialName;
	m_partCatalog->CopyLegName(p_index, unusedName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}
