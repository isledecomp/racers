#include "racer/drivermodelbuilder.h"

#include "core/gol.h"
#include "gdbmodelindexarray0xc.h"
#include "gdbvertexarray0xc.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golmateriallibrary.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golmodelmaterialtable.h"
#include "golname.h"
#include "golstream.h"
#include "igdbmodelindexarray0x8.h"
#include "material/goltexturelist.h"
#include "mesh/golmodel.h"
#include "racer/drivercosmetics.h"
#include "racer/driverpartcatalog.h"
#include "racer/driverpartresources.h"
#include "render/gold3drenderdevice.h"
#include "surface/color.h"
#include "surface/purpledune0x7c.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(DriverModelBuilder, 0x88)
DECOMP_SIZE_ASSERT(DriverModelBuilder::ModelSummary, 0x14)

// FUNCTION: LEGORACERS 0x0049d120
DriverModelBuilder::DriverModelBuilder()
{
	ResetMenuState();
}

// FUNCTION: LEGORACERS 0x0049d130
DriverModelBuilder::~DriverModelBuilder()
{
	ReleaseMenuResources();
}

// FUNCTION: LEGORACERS 0x0049d140
void DriverModelBuilder::ResetMenuState()
{
	m_expressionMask = 1;
	m_menuId = 0;
	m_golExport = NULL;
	m_renderer = NULL;
	m_textureList = NULL;
	m_materialList = NULL;
	m_textureCount = 0;
	m_materialCount = 0;
	m_partResources = 0;
	m_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x0049d170
void DriverModelBuilder::CreateMenuResources()
{
	m_textureList = m_golExport->CreateTextureList();
	m_materialList = m_golExport->CreateMaterialList();
	if (m_textureList == NULL || m_materialList == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_textureList->VTable0x1c(m_renderer, m_menuId);
	m_materialList->VTable0x1c(m_renderer, m_menuId);
}

// FUNCTION: LEGORACERS 0x0049d1d0
undefined4 DriverModelBuilder::Load(const LoadParams* p_params)
{
	ReleaseMenuResources();
	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_menuId = p_params->m_menuId;
	m_partResources = p_params->m_partResources;
	CreateMenuResources();
	InitializeDefaultMaterialParams();

	return m_menuId;
}

// FUNCTION: LEGORACERS 0x0049d210
LegoBool32 DriverModelBuilder::ReleaseMenuResources()
{
	if (!m_menuId) {
		return TRUE;
	}

	if (m_textureList) {
		m_golExport->DestroyTextureList(m_textureList);
	}

	if (m_materialList) {
		m_golExport->DestroyMaterialList(m_materialList);
	}

	ResetMenuState();
	return m_menuId == 0;
}

// FUNCTION: LEGORACERS 0x0049d260
void DriverModelBuilder::RefreshMenuResources()
{
	m_textureCount = 0;
	m_materialCount = 0;
	m_textureList->Clear();
	m_materialList->Clear();
	m_textureList->VTable0x1c(m_renderer, m_menuId);
	m_materialList->VTable0x1c(m_renderer, m_menuId);
}

// FUNCTION: LEGORACERS 0x0049d2a0
void DriverModelBuilder::InitializeDefaultMaterialParams()
{
	DuskwindBananaRelic0x24* material = m_partResources->FindFaceMaterial(0);
	material->CopyParamsTo(&m_defaultMaterialParams);
	m_defaultMaterialParams.m_unk0x08.m_unk0x3 = 0xff;
	m_defaultMaterialParams.m_unk0x08.m_unk0x0 = 200;
	m_defaultMaterialParams.m_unk0x08.m_unk0x2 = 200;
	m_defaultMaterialParams.m_unk0x08.m_unk0x1 = 200;
	m_defaultMaterialParams.m_unk0x0c.m_unk0x3 = 0xff;
	m_defaultMaterialParams.m_unk0x0c.m_unk0x0 = 200;
	m_defaultMaterialParams.m_unk0x0c.m_unk0x2 = 200;
	m_defaultMaterialParams.m_unk0x0c.m_unk0x1 = 200;
}

// FUNCTION: LEGORACERS 0x0049d2e0
void DriverModelBuilder::LoadFaceTexture(const LegoChar* p_name, GolBmpFile* p_imageFile)
{
	PurpleDune0x7c* texture = m_textureList->GetItem(m_textureCount++);

	LegoChar fileName[13];
	::memset(fileName, 0, sizeof(fileName));
	::strncpy(fileName, p_name, sizeof(GolName));
	::strcat(fileName, ".bmp");
	p_imageFile->VTable0x08(fileName);

	texture->SetNameFromBuffer(p_name);
	texture->SetTextureFlags(GoldDune0x38::c_unk0x36Bit2);
	texture->VTable0x30(*m_renderer, p_imageFile);
	m_textureList->AddName(p_name, texture);
	p_imageFile->Destroy();
}

// FUNCTION: LEGORACERS 0x0049d3a0
void DriverModelBuilder::CreateFaceMaterial(const LegoChar* p_name)
{
	DuskwindBananaRelic0x24* sourceMaterial = m_partResources->FindFaceMaterial(0);
	DuskWindBananaRelicParams params;
	sourceMaterial->CopyParamsTo(&params);

	DuskwindBananaRelic0x24* material = m_materialList->GetItem(m_materialCount++);
	params.m_unk0x04 = m_renderer->FindTextureByName(p_name);
	material->SetName(p_name);
	material->FUN_100257e0(m_renderer, params);
	m_materialList->AddName(p_name, material);
}

// FUNCTION: LEGORACERS 0x0049d420
void DriverModelBuilder::LoadFaceExpressionMaterials(LegoS32 p_faceIndex)
{
	GolBmpFile* imageFile = new GolBmpFile;
	if (imageFile == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoChar previousPath[48];
	if (g_hashTable != NULL) {
		::strcpy(previousPath, g_hashTable->GetCurrentEntry()->m_data);
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\PARTDB");
	}

	for (LegoS32 expressionIndex = 0; expressionIndex < 6; expressionIndex++) {
		if (m_expressionMask & (1 << expressionIndex)) {
			GolName name;
			m_partResources->GetPartCatalog()->BuildFaceExpressionName(p_faceIndex, expressionIndex, name);
			if (m_renderer->FindMaterialByName(name) == NULL) {
				LoadFaceTexture(name, imageFile);
				CreateFaceMaterial(name);
			}
		}
	}

	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString(previousPath);
	}

	delete imageFile;
}

// FUNCTION: LEGORACERS 0x0049d570
void DriverModelBuilder::SummarizeModel(GolModelBase* p_model, ModelSummary* p_summary)
{
	p_summary->m_model = p_model;

	GdbVertexArray0xc* vertexArray;
	p_model->VTable0x28(&vertexArray);
	p_summary->m_vertexCount = vertexArray->GetCount();
	p_model->VTable0x2c(0, FALSE);
	p_summary->m_indexCount = p_model->GetIndexArray()->GetCount();
	p_summary->m_groupCount = p_model->GetGroupCount();
	p_summary->m_materialCount = p_model->GetMaterialTable()->GetCount();
}

// FUNCTION: LEGORACERS 0x0049d5c0
LegoBool32 DriverModelBuilder::FitsOutputModel() const
{
	if (m_headSummary.m_vertexCount + m_bodySummary.m_vertexCount > m_outputSummary.m_vertexCount) {
		return FALSE;
	}
	if (m_headSummary.m_indexCount + m_bodySummary.m_indexCount > m_outputSummary.m_indexCount) {
		return FALSE;
	}

	return m_headSummary.m_materialCount + m_bodySummary.m_materialCount <= m_outputSummary.m_materialCount;
}

// FUNCTION: LEGORACERS 0x0049d600
void DriverModelBuilder::FUN_0049d600()
{
	LegoS32 outputIndex = m_bodySummary.m_materialCount;

	for (LegoS32 i = 0; i < m_headSummary.m_materialCount; i++) {
		DuskwindBananaRelic0x24* material = m_headSummary.m_model->GetMaterialTable()->GetMaterial(i);
		if (material == NULL) {
			continue;
		}

		DuskWindName0x8 materialName;
		materialName = material->GetNameRecord();
		LegoS32 existingIndex =
			m_outputSummary.m_model->GetMaterialTable()->FindEntryIndexByName(materialName.m_unk0x0);
		if (existingIndex == -1 || existingIndex >= outputIndex) {
			LegoS32 setIndex = outputIndex++;
			m_outputSummary.m_model->GetMaterialTable()->SetPosition(setIndex, material);
		}
	}
}

// FUNCTION: LEGORACERS 0x0049d670
LegoBool32 DriverModelBuilder::FUN_0049d670(GolModelBase* p_model) const
{
	GolModelBase* bodyModel = m_bodySummary.m_model;
	LegoBool32 result = TRUE;

	if (p_model != NULL && p_model->GetGroups() != NULL) {
		GdbVertexArray0xc* bodyVertexArray;
		GdbVertexArray0xc* existingVertexArray;
		bodyModel->VTable0x28(&bodyVertexArray);
		p_model->VTable0x28(&existingVertexArray);
		result = bodyVertexArray->GetVertexType() != existingVertexArray->GetVertexType();
		bodyModel->VTable0x2c(0, FALSE);
		p_model->VTable0x2c(0, FALSE);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049d6e0
GolModelBase* DriverModelBuilder::FUN_0049d6e0(undefined4 p_vertexType)
{
	GolModelBase* model = m_golExport->VTable0x14();
	if (model == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoS32 indexCount = m_headSummary.m_indexCount + m_bodySummary.m_indexCount + 9;
	LegoS32 vertexCount = m_headSummary.m_vertexCount + m_bodySummary.m_vertexCount + 9;
	LegoS32 groupCount = m_headSummary.m_groupCount + m_bodySummary.m_groupCount + 9;
	LegoS32 materialCount = m_headSummary.m_materialCount + m_bodySummary.m_materialCount + 2;

	GdbVertexArray0xc* vertexArray;
	m_bodySummary.m_model->VTable0x28(&vertexArray);
	if (static_cast<undefined2>(p_vertexType) == 0) {
		p_vertexType = vertexArray->GetVertexType();
	}

	model->VTable0x18(
		m_renderer,
		static_cast<undefined2>(p_vertexType),
		vertexCount,
		indexCount,
		groupCount,
		materialCount
	);
	m_bodySummary.m_model->VTable0x2c(0, FALSE);

	return model;
}

// FUNCTION: LEGORACERS 0x0049d790
void DriverModelBuilder::CopyModelVertices(
	GolModelBase* p_sourceModel,
	GolModelBase* p_destModel,
	LegoU32 p_vertexOffset
)
{
	GdbVertexArray0xc* sourceVertices;
	GdbVertexArray0xc* destVertices;
	ColorRGBA color;
	GolVec2 texCoord;
	GolVec3 position;
	GolVec3 normal;
	p_sourceModel->VTable0x28(&sourceVertices);
	p_destModel->VTable0x28(&destVertices);

	LegoS32 vertexCount = sourceVertices->GetCount();
	for (LegoS32 i = 0; i < vertexCount; i++) {
		LegoU32 destIndex = i + p_vertexOffset;

		sourceVertices->VTable0x14(i, &position);
		destVertices->VTable0x24(destIndex, position);

		sourceVertices->VTable0x18(i, &texCoord);
		destVertices->VTable0x28(destIndex, texCoord);

		sourceVertices->VTable0x1c(i, &normal);
		destVertices->VTable0x2c(destIndex, normal);

		sourceVertices->VTable0x20(i, &color);
		destVertices->VTable0x30(destIndex, color);
	}

	p_sourceModel->VTable0x2c(0, FALSE);
	p_destModel->VTable0x2c(0, FALSE);
}

// STUB: LEGORACERS 0x0049d880
void DriverModelBuilder::FUN_0049d880(GolModelBase* p_sourceModel, GolModelBase* p_destModel, LegoU32 p_indexOffset)
{
	IGdbModelIndexArray0x8* sourceIndexArrayBase;
	IGdbModelIndexArray0x8* destIndexArrayBase;
	p_sourceModel->VTable0x30(&sourceIndexArrayBase);
	p_destModel->VTable0x30(&destIndexArrayBase);

	GdbModelIndexArray0xc* sourceIndexArray = static_cast<GdbModelIndexArray0xc*>(sourceIndexArrayBase);
	GdbModelIndexArray0xc* destIndexArray = static_cast<GdbModelIndexArray0xc*>(destIndexArrayBase);

	for (LegoU32 i = 0; i < sourceIndexArrayBase->GetCount(); i++) {
		const GdbModelIndexArray0xc::Indices* sourceIndices = sourceIndexArray->GetIndex(i);
		if (sourceIndices != NULL) {
			GdbModelIndexArray0xc::Indices* destIndices = destIndexArray->GetMutableIndex(p_indexOffset + i);
			destIndices->m_a = sourceIndices->m_a;
			destIndices->m_b = sourceIndices->m_b;
			destIndices->m_c = sourceIndices->m_c;
		}
	}

	p_sourceModel->VTable0x34(0);
	p_destModel->VTable0x34(0);
}

// FUNCTION: LEGORACERS 0x0049d920
void DriverModelBuilder::FUN_0049d920()
{
	GolModelBase* bodyModel = m_bodySummary.m_model;
	GolModelBase* outputModel = m_outputSummary.m_model;
	GolModelMaterialTable* bodyMaterials = bodyModel->GetMaterialTable();
	LegoS32 bodyMaterialCount = bodyMaterials->GetCount();
	CopyModelVertices(bodyModel, outputModel, 0);
	FUN_0049d880(bodyModel, outputModel, 0);

	GolModelMaterialTable* outputMaterials = outputModel->GetMaterialTable();
	for (LegoS32 i = 0; i < bodyMaterialCount; i++) {
		outputMaterials->SetPosition(i, bodyMaterials->GetMaterial(i));
	}
}

// FUNCTION: LEGORACERS 0x0049d970
void DriverModelBuilder::MergeHeadModel()
{
	CopyModelVertices(m_headSummary.m_model, m_outputSummary.m_model, m_bodySummary.m_vertexCount);
	FUN_0049d880(m_headSummary.m_model, m_outputSummary.m_model, m_bodySummary.m_indexCount);
	FUN_0049d600();
}

// FUNCTION: LEGORACERS 0x0049d9b0
void DriverModelBuilder::FUN_0049d9b0(DuskwindBananaRelic0x24* p_material, const LegoChar* p_name)
{
	GolModelMaterialTable* materialTable = m_outputSummary.m_model->GetMaterialTable();
	DuskWindBananaRelicParams* params = new DuskWindBananaRelicParams;
	LegoS32 materialCount = materialTable->GetCount();
	if (params == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoS32 materialIndex = 0; materialIndex < materialCount; materialIndex++) {
		DuskwindBananaRelic0x24* material = materialTable->GetMaterial(materialIndex);
		if (material != NULL) {
			DuskWindName0x8 materialName;
			materialName = material->GetNameRecord();

			if (::strncmp(p_name, materialName.m_unk0x0, sizeof(GolName)) == 0) {
				p_material->CopyParamsTo(params);
				params->m_unk0x08.m_unk0x3 = m_defaultMaterialParams.m_unk0x08.m_unk0x3;
				params->m_unk0x08.m_unk0x0 = m_defaultMaterialParams.m_unk0x08.m_unk0x0;
				params->m_unk0x08.m_unk0x1 = m_defaultMaterialParams.m_unk0x08.m_unk0x1;
				params->m_unk0x08.m_unk0x2 = m_defaultMaterialParams.m_unk0x08.m_unk0x2;
				params->m_unk0x0c.m_unk0x3 = m_defaultMaterialParams.m_unk0x0c.m_unk0x3;
				params->m_unk0x0c.m_unk0x0 = m_defaultMaterialParams.m_unk0x0c.m_unk0x0;
				params->m_unk0x0c.m_unk0x1 = m_defaultMaterialParams.m_unk0x0c.m_unk0x1;
				params->m_unk0x0c.m_unk0x2 = m_defaultMaterialParams.m_unk0x0c.m_unk0x2;

				p_material->FUN_100257e0(m_renderer, *params);
				materialTable->SetPosition(materialIndex, p_material);
				delete params;
				return;
			}
		}
	}

	delete params;
}

// FUNCTION: LEGORACERS 0x0049dab0
GolModelBase* DriverModelBuilder::MergeModels(
	DriverCosmetics* p_cosmetics,
	GolModelBase* p_model,
	undefined4 p_vertexType
)
{
	if (FUN_0049d670(p_model)) {
		if (p_model != NULL && p_model->GetGroups() != NULL) {
			return NULL;
		}

		p_model = FUN_0049d6e0(p_vertexType);
	}

	SummarizeModel(p_model, &m_outputSummary);
	if (!FitsOutputModel()) {
		return NULL;
	}

	FUN_0049d920();
	MergeHeadModel();
	FUN_0049dd50();
	LoadFaceExpressionMaterials(p_cosmetics->m_faceIndex);

	p_model->SetScale(m_bodySummary.m_model->GetScale());
	FUN_0049d9b0(m_partResources->FindFaceMaterial(p_cosmetics->m_faceIndex), "face");
	FUN_0049d9b0(m_partResources->FindTorsoMaterial(p_cosmetics->m_torsoIndex), "torso");
	FUN_0049d9b0(m_partResources->FindLegMaterial(p_cosmetics->m_legIndex), "legs");

	return p_model;
}

// FUNCTION: LEGORACERS 0x0049db90
GolModelBase* DriverModelBuilder::BuildDriverModel(
	DriverCosmetics* p_cosmetics,
	GolModelBase* p_model,
	undefined4 p_unk0x0c
)
{
	DriverPartCatalog* partCatalog = m_partResources->GetPartCatalog();
	LegoS32 torsoLegIndex = 2 * partCatalog->GetLegVariant(p_cosmetics->m_legIndex) +
							partCatalog->GetTorsoVariant(p_cosmetics->m_torsoIndex);
	GolModelBase* torsoLegModel = m_partResources->GetBodyModel(torsoLegIndex);
	GolModelBase* headModel = m_partResources->LoadHatModel(p_cosmetics->m_hatIndex);

	SummarizeModel(torsoLegModel, &m_bodySummary);
	SummarizeModel(headModel, &m_headSummary);

	return MergeModels(p_cosmetics, p_model, p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x0049dc10
GolSceneNode* DriverModelBuilder::GetBodySceneNode(DriverCosmetics* p_cosmetics)
{
	DriverPartCatalog* partCatalog = m_partResources->GetPartCatalog();
	LegoS32 torsoLegIndex = 2 * partCatalog->GetLegVariant(p_cosmetics->m_legIndex) +
							partCatalog->GetTorsoVariant(p_cosmetics->m_torsoIndex);
	return m_partResources->GetBodySceneNode(torsoLegIndex);
}

// FUNCTION: LEGORACERS 0x0049dc50
CmbModelPart0x34* DriverModelBuilder::GetBodyModelPart(DriverCosmetics* p_cosmetics)
{
	DriverPartCatalog* partCatalog = m_partResources->GetPartCatalog();
	LegoS32 torsoLegIndex = 2 * partCatalog->GetLegVariant(p_cosmetics->m_legIndex) +
							partCatalog->GetTorsoVariant(p_cosmetics->m_torsoIndex);
	return m_partResources->GetBodyModelPart(torsoLegIndex);
}

// FUNCTION: LEGORACERS 0x0049dc90
void DriverModelBuilder::GetMaxMergedCounts(undefined4* p_dest)
{
	p_dest[0] = m_partResources->GetMaxHatVertexCount() + m_partResources->GetMaxBodyVertexCount() + 9;
	p_dest[1] = m_partResources->GetMaxHatIndexCount() + m_partResources->GetMaxBodyIndexCount() + 9;
	p_dest[2] = m_partResources->GetMaxHatGroupCount() + m_partResources->GetMaxBodyGroupCount() + 10;
	p_dest[3] = m_partResources->GetMaxHatMaterialCount() + m_partResources->GetMaxBodyMaterialCount() + 2;
}

// FUNCTION: LEGORACERS 0x0049dce0
void DriverModelBuilder::ApplyFaceExpression(GolModelBase* p_model, DriverCosmetics* p_cosmetics)
{
	GolName materialName;
	m_partResources->GetPartCatalog()->CopyDefaultFaceName(p_cosmetics->m_faceIndex, materialName, materialName);
	LegoS32 materialIndex = p_model->GetMaterialTable()->FindEntryIndexByName(materialName);
	m_partResources->GetPartCatalog()
		->BuildFaceExpressionName(p_cosmetics->m_faceIndex, p_cosmetics->m_expressionIndex, materialName);
	p_model->GetMaterialTable()->AssignEntryByName(materialIndex, materialName);
}

// STUB: LEGORACERS 0x0049dd50
void DriverModelBuilder::FUN_0049dd50()
{
	GolName faceName;
	::strncpy(faceName, "face", sizeof(GolName));
	LegoU32 faceGroup = GolModel::c_groupTypeMaterial |
						(m_bodySummary.m_model->GetMaterialTable()->FindEntryIndexByName(faceName) & 0x00ffffff);

	LegoS32 bodyIndex = 0;
	LegoU32 group;
	do {
		bodyIndex++;
		group = m_bodySummary.m_model->GetGroups()[bodyIndex - 1];
		m_outputSummary.m_model->GetMutableGroups()[bodyIndex - 1] = group;
	} while (group != faceGroup);

	LegoS32 outputIndex = bodyIndex - 1;
	LegoU32 groupType;
	do {
		group = m_bodySummary.m_model->GetGroups()[bodyIndex];
		bodyIndex++;
		groupType = group & GolModel::c_groupTypeMask;
		if (groupType == GolModel::c_groupTypeMatrix) {
			m_outputSummary.m_model->GetMutableGroups()[outputIndex++] = group;
		}
	} while (groupType != GolModel::c_groupTypeMaterial && groupType != GolModel::c_groupTypeEnd);

	LegoS32 headGroupCount = m_headSummary.m_groupCount;
	LegoS32 bodyCopyIndex = bodyIndex - 1;
	LegoS32 headIndex = 0;
	LegoS32 remainingBodyIndex = bodyIndex - 1;
	if (headGroupCount > 0) {
		while (TRUE) {
			group = m_headSummary.m_model->GetGroups()[headIndex];
			groupType = group & GolModel::c_groupTypeMask;
			if (groupType > GolModel::c_groupTypeMaterial) {
				if (groupType == GolModel::c_groupTypeEnd) {
					headIndex = headGroupCount;
				}
			}
			else if (groupType == GolModel::c_groupTypeMaterial) {
				DuskwindBananaRelic0x24* material =
					m_headSummary.m_model->GetMaterialTable()->GetMaterial(group & 0x0000ffff);
				DuskWindName0x8 materialName;
				materialName = material->GetNameRecord();
				group = GolModel::c_groupTypeMaterial |
						(m_outputSummary.m_model->GetMaterialTable()->FindEntryIndexByName(materialName.m_unk0x0) &
						 0x00ffffff);
			}
			else if (groupType) {
				if (groupType == GolModel::c_groupTypeTriangleBatch) {
					group = GolModel::c_groupTypeTriangleBatch | (group & 0x007f0000) |
							((group + m_bodySummary.m_indexCount) & 0x0000ffff);
				}
			}
			else {
				group =
					(group & 0x0fc00000) | (group & 0x003f0000) | ((group + m_bodySummary.m_vertexCount) & 0x0000ffff);
			}

			if (groupType != GolModel::c_groupTypeEnd) {
				m_outputSummary.m_model->GetMutableGroups()[outputIndex++] = group;
			}
			headGroupCount = m_headSummary.m_groupCount;
			if (++headIndex >= headGroupCount) {
				bodyCopyIndex = remainingBodyIndex;
				break;
			}
		}
	}

	while (bodyCopyIndex < m_bodySummary.m_groupCount) {
		m_outputSummary.m_model->GetMutableGroups()[outputIndex++] =
			m_bodySummary.m_model->GetGroups()[bodyCopyIndex++];
	}

	m_outputSummary.m_model->GetMutableGroups()[outputIndex] = GolModel::c_groupTypeEnd;
	m_outputSummary.m_model->SetDirty(TRUE);
}
