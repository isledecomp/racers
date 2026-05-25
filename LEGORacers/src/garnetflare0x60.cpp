#include "garnetflare0x60.h"

#include "amberhaze0x1c.h"
#include "bronzefalcon0xc8770.h"
#include "duskwindbananarelic0x24.h"
#include "floatyferry0xf4.h"
#include "gdbvertexarray0xc.h"
#include "gol.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golname.h"
#include "golstream.h"
#include "igdbmodel0x40.h"
#include "igdbmodelindexarray0x8.h"
#include "lavendervault0x764.h"
#include "magentaribbon0x20.h"
#include "shadowwolf0xc.h"
#include "zoweeblubberworth0xf0.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GarnetFlare0x60, 0x60)

static const LegoChar g_gdbFaceMaterialName[] = "face";

// GLOBAL: LEGORACERS 0x004be390
static LegoS32 g_resourceBinaryMode = TRUE;

// FUNCTION: LEGORACERS 0x00414840
static LegoS32 SetResourceBinaryMode(LegoS32 p_binary)
{
	g_resourceBinaryMode = p_binary;
	return p_binary;
}

// FUNCTION: LEGORACERS 0x00497e40
GarnetFlare0x60::GarnetFlare0x60()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00497e90
GarnetFlare0x60::~GarnetFlare0x60()
{
	ReleaseResources();
}

// FUNCTION: LEGORACERS 0x00497ee0
LegoS32 GarnetFlare0x60::Reset()
{
	m_golExport = NULL;
	m_renderer = NULL;
	m_partResource = NULL;
	m_partConfig = NULL;
	m_unk0x28 = NULL;
	m_materialList = NULL;
	m_textureList = NULL;
	m_unk0x3c = 0;
	m_unk0x44 = 0;
	m_unk0x4c = 0;
	m_unk0x54 = 0;
	m_unk0x40 = 0;
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0x58 = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x00497f10
ZoweeBlubberworth0xf0* GarnetFlare0x60::FUN_00497f10(const LoadParams* p_params, LegoS32 p_resourceIndex)
{
	ReleaseResources();
	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_resourceIndex = p_resourceIndex;
	m_partConfig = p_params->m_unk0x0c;
	m_binary = p_params->m_unk0x14;

	LoadMaterialAndTextureLists(p_params->m_binary);
	LoadPartResource(p_params->m_binary);
	NormalizeHeadGroupOrder();

	m_unk0x28 = m_golExport->VTable0x14();
	m_unk0x28->VTable0x18(m_renderer, 2, 600, 300, 100, 3);

	ComputeMaxVertexCounts();
	ComputeMaxIndexCounts();
	ComputeMaxGroupCounts();
	ComputeMaxMaterialCounts();
	return m_partResource;
}

// FUNCTION: LEGORACERS 0x00497fb0
LegoBool32 GarnetFlare0x60::ReleaseResources()
{
	if (m_partResource == NULL) {
		return TRUE;
	}

	if (m_unk0x28 != NULL) {
		m_golExport->VTable0x48(m_unk0x28);
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
void GarnetFlare0x60::LoadPartResource(LegoBool32 p_binary)
{
	LegoChar fileName[16];
	::strcpy(fileName, m_partConfig->GetBodyModelFileName(m_resourceIndex));
	const LegoChar* directory = m_partConfig->GetBodyModelDirectory(m_resourceIndex);

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
void GarnetFlare0x60::LoadMaterialAndTextureLists(LegoBool32 p_binary)
{
	m_textureList = m_golExport->CreateTextureList();
	m_materialList = m_golExport->CreateMaterialList();
	if (m_textureList == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	SetResourceBinaryMode(m_binary);
	m_textureList->VTable0x24(m_renderer, "bodypart.tdf", p_binary);
	SetResourceBinaryMode(TRUE);
	m_materialList->VTable0x24(m_renderer, "bodypart.mdf", p_binary);
}

// STUB: LEGORACERS 0x004981a0
static LegoU32 __stdcall ReplaceModelGroupMaterialIndex(
	FloatyFerry0xf4* p_resourceModel,
	LegoU32 p_oldIndex,
	LegoU32 p_newIndex
)
{
	STUB(0x004981a0);

	IGdbModel0x40* model = p_resourceModel->GetModel(0);
	LegoU32 oldGroupTag = (p_oldIndex & 0x00ffffff) | 0x80000000;
	LegoU32 result = oldGroupTag;
	LegoU32 groupIndex = 0;
	LegoU32 groupCount = model->GetGroupCount();
	LegoU32* groups = model->GetMutableGroups();

	do {
		groupIndex++;
	} while (groups[groupIndex - 1] != oldGroupTag && groupIndex < groupCount);

	if (groupIndex != groupCount) {
		result = (p_newIndex & 0x00ffffff) | 0x80000000;
		groups[groupIndex - 1] = result;
	}

	return result;
}

// STUB: LEGORACERS 0x004981f0
void GarnetFlare0x60::NormalizeHeadGroupOrder()
{
	STUB(0x004981f0);

	LegoS32 remainingModels = m_partResource->GetUnk0x54();
	if (remainingModels > 0) {
		FloatyFerry0xf4* resourceModel = m_partResource->GetUnk0xa0();
		do {
			ShadowWolf0xc* materialTable = resourceModel->GetMaterialTable(0);
			if (materialTable == NULL) {
				materialTable = resourceModel->GetModel(0)->GetMaterialTable();
			}

			LegoS32 materialIndex = 1;
			LegoS32 materialCount = materialTable->GetCount();
			if (materialCount > 1) {
				do {
					DuskwindBananaRelic0x24* material = materialTable->GetMaterial(materialIndex);
					if (material != NULL) {
						GolName materialName;
						::memcpy(materialName, material->GetName(), sizeof(materialName));

						if (::strncmp(materialName, g_gdbFaceMaterialName, sizeof(materialName)) == 0) {
							DuskwindBananaRelic0x24* firstMaterial = materialTable->GetMaterial(0);
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
void GarnetFlare0x60::ComputeMaxVertexCounts()
{
	GdbVertexArray0xc* vertexArray;
	for (LegoS32 bodyIndex = 0; bodyIndex < static_cast<LegoS32>(m_partResource->GetUnk0x54()); bodyIndex++) {
		IGdbModel0x40* model = FUN_00498510(bodyIndex);
		model->VTable0x28(&vertexArray);
		if (static_cast<LegoS32>(vertexArray->GetCount()) > m_unk0x44) {
			m_unk0x44 = vertexArray->GetCount();
		}
		model->VTable0x2c(0, FALSE);
	}

	for (LegoS32 hatIndex = 0; hatIndex < m_partConfig->GetHatCount(); hatIndex++) {
		IGdbModel0x40* model = FUN_004984d0(hatIndex);
		model->VTable0x28(&vertexArray);
		if (static_cast<LegoS32>(vertexArray->GetCount()) > m_unk0x48) {
			m_unk0x48 = vertexArray->GetCount();
		}
		model->VTable0x2c(0, FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004983a0
void GarnetFlare0x60::ComputeMaxIndexCounts()
{
	for (LegoS32 bodyIndex = 0; bodyIndex < static_cast<LegoS32>(m_partResource->GetUnk0x54()); bodyIndex++) {
		IGdbModel0x40* model = FUN_00498510(bodyIndex);
		LegoS32 count = model->GetIndexArray()->GetCount();
		if (count > m_unk0x3c) {
			m_unk0x3c = count;
		}
	}

	for (LegoS32 hatIndex = 0; hatIndex < m_partConfig->GetHatCount(); hatIndex++) {
		IGdbModel0x40* model = FUN_004984d0(hatIndex);
		LegoS32 count = model->GetIndexArray()->GetCount();
		if (count > m_unk0x40) {
			m_unk0x40 = count;
		}
	}
}

// FUNCTION: LEGORACERS 0x00498410
void GarnetFlare0x60::ComputeMaxGroupCounts()
{
	for (LegoS32 bodyIndex = 0; bodyIndex < static_cast<LegoS32>(m_partResource->GetUnk0x54()); bodyIndex++) {
		IGdbModel0x40* model = FUN_00498510(bodyIndex);
		LegoS32 count = model->GetGroupCount();
		if (count > m_unk0x4c) {
			m_unk0x4c = count;
		}
	}

	for (LegoS32 hatIndex = 0; hatIndex < m_partConfig->GetHatCount(); hatIndex++) {
		IGdbModel0x40* model = FUN_004984d0(hatIndex);
		LegoS32 count = model->GetGroupCount();
		if (count > m_unk0x50) {
			m_unk0x50 = count;
		}
	}
}

// FUNCTION: LEGORACERS 0x00498470
void GarnetFlare0x60::ComputeMaxMaterialCounts()
{
	for (LegoS32 bodyIndex = 0; bodyIndex < static_cast<LegoS32>(m_partResource->GetUnk0x54()); bodyIndex++) {
		IGdbModel0x40* model = FUN_00498510(bodyIndex);
		LegoS32 count = model->GetMaterialTable()->GetCount();
		if (count > m_unk0x54) {
			m_unk0x54 = count;
		}
	}

	for (LegoS32 hatIndex = 0; hatIndex < m_partConfig->GetHatCount(); hatIndex++) {
		IGdbModel0x40* model = FUN_004984d0(hatIndex);
		LegoS32 count = model->GetMaterialTable()->GetCount();
		if (count > m_unk0x58) {
			m_unk0x58 = count;
		}
	}
}

// FUNCTION: LEGORACERS 0x004984d0
IGdbModel0x40* GarnetFlare0x60::FUN_004984d0(LegoS32 p_index)
{
	GolName name;
	m_partConfig->CopyHeadHatName(p_index, name);
	m_partLibrary.CopyPartToModel(m_renderer, m_unk0x28, name);
	return m_unk0x28;
}

// FUNCTION: LEGORACERS 0x00498510
IGdbModel0x40* GarnetFlare0x60::FUN_00498510(LegoS32 p_index)
{
	GolName name;
	if (m_resourceIndex == 1) {
		m_partConfig->FUN_00499070(4, name);
	}
	else {
		m_partConfig->FUN_00499070(p_index, name);
	}

	FloatyFerry0xf4* model = m_partResource->FindUnk0xc0(name);
	return model->GetModel(0);
}

// FUNCTION: LEGORACERS 0x00498570
WhiteFalconNode0x18* GarnetFlare0x60::FUN_00498570(LegoS32 p_index)
{
	GolName name;
	if (m_resourceIndex == 1) {
		m_partConfig->FUN_00499070(4, name);
	}
	else {
		m_partConfig->FUN_00499070(p_index, name);
	}

	FloatyFerry0xf4* model = m_partResource->FindUnk0xc0(name);
	return model->VTable0x58(0);
}

// FUNCTION: LEGORACERS 0x00498640
DuskwindBananaRelic0x24* GarnetFlare0x60::FUN_00498640(LegoS32 p_index)
{
	GolName unusedName;
	GolName materialName;
	m_partConfig->FUN_00498f70(p_index, unusedName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

// FUNCTION: LEGORACERS 0x00498680
DuskwindBananaRelic0x24* GarnetFlare0x60::FUN_00498680(LegoS32 p_index)
{
	GolName unusedName;
	GolName materialName;
	m_partConfig->FUN_00498fd0(p_index, unusedName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}

// FUNCTION: LEGORACERS 0x004986c0
DuskwindBananaRelic0x24* GarnetFlare0x60::FUN_004986c0(LegoS32 p_index)
{
	GolName unusedName;
	GolName materialName;
	m_partConfig->FUN_00499020(p_index, unusedName, materialName);
	return m_renderer->FindMaterialByName(materialName);
}
