#include "tanzanitewisp0x88.h"

#include "../../GolDP/src/gdbmodelindexarray0xc.h"
#include "amberhaze0x1c.h"
#include "bronzefalcon0xc8770.h"
#include "color.h"
#include "garnetflare0x60.h"
#include "gdbvertexarray0xc.h"
#include "gol.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golhashtable.h"
#include "golmath.h"
#include "golname.h"
#include "golstream.h"
#include "igdbmodel0x40.h"
#include "igdbmodelindexarray0x8.h"
#include "lavendervault0x764.h"
#include "magentaribbon0x20.h"
#include "purpledune0x7c.h"
#include "shadowwolf0xc.h"
#include "turquoiseglowcolor.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(TanzaniteWisp0x88, 0x88)
DECOMP_SIZE_ASSERT(TanzaniteWisp0x88::ModelSummary0x14, 0x14)

// GLOBAL: LEGORACERS 0x004c217c
static const LegoChar g_legsMaterialName[] = "legs";

// GLOBAL: LEGORACERS 0x004c2184
static const LegoChar g_torsoMaterialName[] = "torso";

// GLOBAL: LEGORACERS 0x004c218c
static const LegoChar g_faceMaterialName[] = "face";

// FUNCTION: LEGORACERS 0x0049d120
TanzaniteWisp0x88::TanzaniteWisp0x88()
{
	ResetMenuState();
}

// FUNCTION: LEGORACERS 0x0049d130
TanzaniteWisp0x88::~TanzaniteWisp0x88()
{
	ReleaseMenuResources();
}

// FUNCTION: LEGORACERS 0x0049d140
void TanzaniteWisp0x88::ResetMenuState()
{
	m_unk0x10 = 1;
	m_menuId = 0;
	m_golExport = NULL;
	m_renderer = NULL;
	m_menuResource0 = NULL;
	m_menuResource1 = NULL;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x38 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x0049d170
void TanzaniteWisp0x88::CreateMenuResources()
{
	m_menuResource0 = m_golExport->CreateTextureList();
	m_menuResource1 = m_golExport->CreateMaterialList();
	if (m_menuResource0 == NULL || m_menuResource1 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_menuResource0->VTable0x1c(m_renderer, m_menuId);
	m_menuResource1->VTable0x1c(m_renderer, m_menuId);
}

// FUNCTION: LEGORACERS 0x0049d1d0
undefined4 TanzaniteWisp0x88::FUN_0049d1d0(const LoadParams* p_params)
{
	ReleaseMenuResources();
	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_menuId = p_params->m_menuId;
	m_unk0x38 = p_params->m_unk0x0c;
	CreateMenuResources();
	InitializeDefaultMaterialParams();

	return m_menuId;
}

// FUNCTION: LEGORACERS 0x0049d210
LegoBool32 TanzaniteWisp0x88::ReleaseMenuResources()
{
	if (!m_menuId) {
		return TRUE;
	}

	if (m_menuResource0) {
		m_golExport->DestroyTextureList(m_menuResource0);
	}

	if (m_menuResource1) {
		m_golExport->DestroyMaterialList(m_menuResource1);
	}

	ResetMenuState();
	return m_menuId == 0;
}

// FUNCTION: LEGORACERS 0x0049d260
void TanzaniteWisp0x88::RefreshMenuResources()
{
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_menuResource0->Clear();
	m_menuResource1->Clear();
	m_menuResource0->VTable0x1c(m_renderer, m_menuId);
	m_menuResource1->VTable0x1c(m_renderer, m_menuId);
}

// FUNCTION: LEGORACERS 0x0049d2a0
void TanzaniteWisp0x88::InitializeDefaultMaterialParams()
{
	DuskwindBananaRelic0x24* material = m_unk0x38->FUN_00498640(0);
	material->CopyParamsTo(&m_unk0x24);
	m_unk0x24.m_unk0x08.m_unk0x3 = 0xff;
	m_unk0x24.m_unk0x08.m_unk0x0 = 200;
	m_unk0x24.m_unk0x08.m_unk0x2 = 200;
	m_unk0x24.m_unk0x08.m_unk0x1 = 200;
	m_unk0x24.m_unk0x0c.m_unk0x3 = 0xff;
	m_unk0x24.m_unk0x0c.m_unk0x0 = 200;
	m_unk0x24.m_unk0x0c.m_unk0x2 = 200;
	m_unk0x24.m_unk0x0c.m_unk0x1 = 200;
}

// FUNCTION: LEGORACERS 0x0049d2e0
void TanzaniteWisp0x88::FUN_0049d2e0(const LegoChar* p_name, GolBmpFile* p_imageFile)
{
	PurpleDune0x7c* texture = m_menuResource0->GetItem(m_unk0x04++);

	LegoChar fileName[16] = {0};
	::strncpy(fileName, p_name, sizeof(GolName));
	::strcat(fileName, ".bmp");
	p_imageFile->VTable0x08(fileName);

	texture->SetNameFromBuffer(p_name);
	texture->SetTextureFlags(GoldDune0x38::c_unk0x36Bit2);
	texture->VTable0x30(*m_renderer, p_imageFile);
	m_menuResource0->AddName(p_name, texture);
	p_imageFile->Destroy();
}

// FUNCTION: LEGORACERS 0x0049d3a0
void TanzaniteWisp0x88::FUN_0049d3a0(const LegoChar* p_name)
{
	DuskwindBananaRelic0x24* sourceMaterial = m_unk0x38->FUN_00498640(0);
	DuskWindBananaRelicParams params;
	sourceMaterial->CopyParamsTo(&params);

	DuskwindBananaRelic0x24* material = m_menuResource1->GetItem(m_unk0x08++);
	params.m_unk0x04 = m_renderer->FindTextureByName(p_name);
	material->SetName(p_name);
	material->FUN_100257e0(m_renderer, params);
	m_menuResource1->AddName(p_name, material);
}

// FUNCTION: LEGORACERS 0x0049d420
void TanzaniteWisp0x88::FUN_0049d420(LegoS32 p_faceIndex)
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
		if (m_unk0x10 & (1 << expressionIndex)) {
			GolName name;
			m_unk0x38->GetPartConfig()->BuildFaceExpressionName(p_faceIndex, expressionIndex, name);
			if (m_renderer->FindMaterialByName(name) == NULL) {
				FUN_0049d2e0(name, imageFile);
				FUN_0049d3a0(name);
			}
		}
	}

	if (g_hashTable != NULL) {
		g_hashTable->SetCurrentEntryFromString(previousPath);
	}

	delete imageFile;
}

// FUNCTION: LEGORACERS 0x0049d570
void TanzaniteWisp0x88::FUN_0049d570(IGdbModel0x40* p_model, ModelSummary0x14* p_summary)
{
	p_summary->m_model = p_model;

	GdbVertexArray0xc* vertexArray;
	p_model->VTable0x28(&vertexArray);
	p_summary->m_unk0x00 = vertexArray->GetCount();
	p_model->VTable0x2c(0, FALSE);
	p_summary->m_unk0x04 = p_model->GetIndexArray()->GetCount();
	p_summary->m_unk0x08 = p_model->GetGroupCount();
	p_summary->m_unk0x0c = p_model->GetMaterialTable()->GetCount();
}

// FUNCTION: LEGORACERS 0x0049d5c0
LegoBool32 TanzaniteWisp0x88::FUN_0049d5c0() const
{
	if (m_unk0x50.m_unk0x00 + m_unk0x3c.m_unk0x00 > m_unk0x64.m_unk0x00) {
		return FALSE;
	}
	if (m_unk0x50.m_unk0x04 + m_unk0x3c.m_unk0x04 > m_unk0x64.m_unk0x04) {
		return FALSE;
	}

	return m_unk0x50.m_unk0x0c + m_unk0x3c.m_unk0x0c <= m_unk0x64.m_unk0x0c;
}

// STUB: LEGORACERS 0x0049d600
void TanzaniteWisp0x88::FUN_0049d600()
{
	STUB(0x0049d600);

	ShadowWolf0xc* outputMaterials = m_unk0x64.m_model->GetMaterialTable();
	ShadowWolf0xc* headMaterials = m_unk0x50.m_model->GetMaterialTable();
	LegoU32 outputIndex = static_cast<LegoU32>(m_unk0x3c.m_unk0x0c);

	for (LegoS32 i = 0; i < m_unk0x50.m_unk0x0c; i++) {
		DuskwindBananaRelic0x24* material = headMaterials->GetMaterial(i);
		if (material == NULL) {
			continue;
		}

		LegoS32 existingIndex = outputMaterials->FindEntryIndexByName(material->GetName());
		if (existingIndex == -1 || static_cast<LegoU32>(existingIndex) >= outputIndex) {
			outputMaterials->SetPosition(outputIndex, material);
			outputIndex++;
		}
	}
}

// STUB: LEGORACERS 0x0049d670
LegoBool32 TanzaniteWisp0x88::FUN_0049d670(IGdbModel0x40* p_model) const
{
	STUB(0x0049d670);

	if (p_model == NULL || p_model->GetGroups() == NULL) {
		return TRUE;
	}

	GdbVertexArray0xc* existingVertexArray;
	GdbVertexArray0xc* bodyVertexArray;
	p_model->VTable0x28(&existingVertexArray);
	m_unk0x3c.m_model->VTable0x28(&bodyVertexArray);
	LegoBool32 needsNewModel = existingVertexArray->GetVertexType() != bodyVertexArray->GetVertexType();
	p_model->VTable0x2c(0, FALSE);
	m_unk0x3c.m_model->VTable0x2c(0, FALSE);

	return needsNewModel;
}

// STUB: LEGORACERS 0x0049d6e0
IGdbModel0x40* TanzaniteWisp0x88::FUN_0049d6e0(undefined2 p_vertexType)
{
	STUB(0x0049d6e0);

	IGdbModel0x40* model = m_golExport->VTable0x14();
	if (model == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	if (p_vertexType == 0) {
		GdbVertexArray0xc* vertexArray;
		m_unk0x3c.m_model->VTable0x28(&vertexArray);
		p_vertexType = vertexArray->GetVertexType();
		m_unk0x3c.m_model->VTable0x2c(0, FALSE);
	}

	model->VTable0x18(
		m_renderer,
		p_vertexType,
		m_unk0x50.m_unk0x00 + m_unk0x3c.m_unk0x00 + 9,
		m_unk0x50.m_unk0x04 + m_unk0x3c.m_unk0x04 + 9,
		m_unk0x50.m_unk0x08 + m_unk0x3c.m_unk0x08 + 9,
		m_unk0x50.m_unk0x0c + m_unk0x3c.m_unk0x0c + 2
	);
	m_unk0x3c.m_model->VTable0x2c(0, FALSE);

	return model;
}

// STUB: LEGORACERS 0x0049d790
void TanzaniteWisp0x88::CopyModelVertices(
	IGdbModel0x40* p_sourceModel,
	IGdbModel0x40* p_destModel,
	LegoU32 p_vertexOffset
)
{
	STUB(0x0049d790);

	GdbVertexArray0xc* sourceVertices;
	GdbVertexArray0xc* destVertices;
	p_sourceModel->VTable0x28(&sourceVertices);
	p_destModel->VTable0x28(&destVertices);

	for (LegoU32 i = 0; i < sourceVertices->GetCount(); i++) {
		LegoU32 destIndex = i + p_vertexOffset;

		GolVec3 position;
		sourceVertices->VTable0x14(i, &position);
		destVertices->VTable0x24(destIndex, position);

		GolVec2 texCoord;
		sourceVertices->VTable0x18(i, &texCoord);
		destVertices->VTable0x28(destIndex, texCoord);

		GolVec3 normal;
		sourceVertices->VTable0x1c(i, &normal);
		destVertices->VTable0x2c(destIndex, normal);

		ColorRGBA color;
		sourceVertices->VTable0x20(i, &color);
		destVertices->VTable0x30(destIndex, color);
	}

	p_sourceModel->VTable0x2c(0, FALSE);
	p_destModel->VTable0x2c(0, FALSE);
}

// STUB: LEGORACERS 0x0049d880
void TanzaniteWisp0x88::FUN_0049d880(IGdbModel0x40* p_sourceModel, IGdbModel0x40* p_destModel, LegoU32 p_indexOffset)
{
	STUB(0x0049d880);

	IGdbModelIndexArray0x8* sourceIndexArrayBase;
	IGdbModelIndexArray0x8* destIndexArrayBase;
	p_sourceModel->VTable0x30(&sourceIndexArrayBase);
	p_destModel->VTable0x30(&destIndexArrayBase);

	const GdbModelIndexArray0xc::Indices* sourceIndices =
		static_cast<GdbModelIndexArray0xc*>(sourceIndexArrayBase)->GetIndices();
	GdbModelIndexArray0xc::Indices* destIndices =
		static_cast<GdbModelIndexArray0xc*>(destIndexArrayBase)->GetMutableIndices();

	for (LegoU32 i = 0; i < sourceIndexArrayBase->GetCount(); i++) {
		destIndices[p_indexOffset + i].m_a = sourceIndices[i].m_a;
		destIndices[p_indexOffset + i].m_b = sourceIndices[i].m_b;
		destIndices[p_indexOffset + i].m_c = sourceIndices[i].m_c;
		destIndices[p_indexOffset + i].m_x = 0;
	}

	p_sourceModel->VTable0x34(0);
	p_destModel->VTable0x34(0);
}

// STUB: LEGORACERS 0x0049d920
void TanzaniteWisp0x88::FUN_0049d920()
{
	STUB(0x0049d920);

	IGdbModel0x40* bodyModel = m_unk0x3c.m_model;
	IGdbModel0x40* outputModel = m_unk0x64.m_model;
	CopyModelVertices(bodyModel, outputModel, 0);
	FUN_0049d880(bodyModel, outputModel, 0);

	ShadowWolf0xc* bodyMaterials = bodyModel->GetMaterialTable();
	ShadowWolf0xc* outputMaterials = outputModel->GetMaterialTable();
	for (LegoU32 i = 0; i < bodyMaterials->GetCount(); i++) {
		outputMaterials->SetPosition(i, bodyMaterials->GetMaterial(i));
	}
}

// FUNCTION: LEGORACERS 0x0049d970
void TanzaniteWisp0x88::FUN_0049d970()
{
	CopyModelVertices(m_unk0x50.m_model, m_unk0x64.m_model, m_unk0x3c.m_unk0x00);
	FUN_0049d880(m_unk0x50.m_model, m_unk0x64.m_model, m_unk0x3c.m_unk0x04);
	FUN_0049d600();
}

// STUB: LEGORACERS 0x0049d9b0
void TanzaniteWisp0x88::FUN_0049d9b0(DuskwindBananaRelic0x24* p_material, const LegoChar* p_name)
{
	STUB(0x0049d9b0);

	if (p_material == NULL) {
		return;
	}

	ShadowWolf0xc* materialTable = m_unk0x64.m_model->GetMaterialTable();
	LegoS32 materialIndex = materialTable->FindEntryIndexByName(p_name);
	if (materialIndex < 0) {
		return;
	}

	DuskWindBananaRelicParams params;
	p_material->CopyParamsTo(&params);
	params.m_unk0x08 = m_unk0x24.m_unk0x08;
	params.m_unk0x0c = m_unk0x24.m_unk0x0c;
	p_material->FUN_100257e0(m_renderer, params);
	materialTable->SetPosition(materialIndex, p_material);
}

// FUNCTION: LEGORACERS 0x0049dab0
IGdbModel0x40* TanzaniteWisp0x88::FUN_0049dab0(
	TurquoiseGlowColor* p_color,
	IGdbModel0x40* p_model,
	undefined4 p_vertexType
)
{
	if (FUN_0049d670(p_model)) {
		if (p_model != NULL && p_model->GetGroups() != NULL) {
			return NULL;
		}

		p_model = FUN_0049d6e0(static_cast<undefined2>(p_vertexType));
	}

	FUN_0049d570(p_model, &m_unk0x64);
	if (!FUN_0049d5c0()) {
		return NULL;
	}

	FUN_0049d920();
	FUN_0049d970();
	FUN_0049dd50();
	FUN_0049d420(p_color->m_unk0x01);

	p_model->SetScale(m_unk0x3c.m_model->GetScale());
	FUN_0049d9b0(m_unk0x38->FUN_00498640(p_color->m_unk0x01), g_faceMaterialName);
	FUN_0049d9b0(m_unk0x38->FUN_00498680(p_color->m_unk0x02), g_torsoMaterialName);
	FUN_0049d9b0(m_unk0x38->FUN_004986c0(p_color->m_unk0x03), g_legsMaterialName);

	return p_model;
}

// FUNCTION: LEGORACERS 0x0049db90
IGdbModel0x40* TanzaniteWisp0x88::FUN_0049db90(
	TurquoiseGlowColor* p_color,
	IGdbModel0x40* p_model,
	undefined4 p_unk0x0c
)
{
	LavenderVault0x764* partConfig = m_unk0x38->GetPartConfig();
	LegoS32 torsoLegIndex =
		2 * partConfig->GetLegVariant(p_color->m_unk0x03) + partConfig->GetTorsoVariant(p_color->m_unk0x02);
	IGdbModel0x40* torsoLegModel = m_unk0x38->FUN_00498510(torsoLegIndex);
	IGdbModel0x40* headModel = m_unk0x38->FUN_004984d0(p_color->m_unk0x00);

	FUN_0049d570(torsoLegModel, &m_unk0x3c);
	FUN_0049d570(headModel, &m_unk0x50);

	return FUN_0049dab0(p_color, p_model, p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x0049dc10
WhiteFalconNode0x18* TanzaniteWisp0x88::FUN_0049dc10(TurquoiseGlowColor* p_color)
{
	LavenderVault0x764* partConfig = m_unk0x38->GetPartConfig();
	LegoS32 torsoLegIndex =
		2 * partConfig->GetLegVariant(p_color->m_unk0x03) + partConfig->GetTorsoVariant(p_color->m_unk0x02);
	return m_unk0x38->FUN_00498570(torsoLegIndex);
}

// FUNCTION: LEGORACERS 0x0049dc90
void TanzaniteWisp0x88::FUN_0049dc90(undefined4* p_dest)
{
	p_dest[0] = m_unk0x38->GetUnk0x48() + m_unk0x38->GetUnk0x44() + 9;
	p_dest[1] = m_unk0x38->GetUnk0x40() + m_unk0x38->GetUnk0x3c() + 9;
	p_dest[2] = m_unk0x38->GetUnk0x50() + m_unk0x38->GetUnk0x4c() + 10;
	p_dest[3] = m_unk0x38->GetUnk0x58() + m_unk0x38->GetUnk0x54() + 2;
}

// FUNCTION: LEGORACERS 0x0049dce0
void TanzaniteWisp0x88::FUN_0049dce0(IGdbModel0x40* p_model, TurquoiseGlowColor* p_color)
{
	GolName materialName;
	m_unk0x38->GetPartConfig()->FUN_00498f70(p_color->m_unk0x01, materialName, materialName);
	LegoS32 materialIndex = p_model->GetMaterialTable()->FindEntryIndexByName(materialName);
	m_unk0x38->GetPartConfig()->BuildFaceExpressionName(p_color->m_unk0x01, p_color->m_unk0x04, materialName);
	p_model->GetMaterialTable()->AssignEntryByName(materialIndex, materialName);
}

// STUB: LEGORACERS 0x0049dd50
void TanzaniteWisp0x88::FUN_0049dd50()
{
	STUB(0x0049dd50);

	IGdbModel0x40* bodyModel = m_unk0x3c.m_model;
	IGdbModel0x40* headModel = m_unk0x50.m_model;
	IGdbModel0x40* outputModel = m_unk0x64.m_model;
	LegoU32* outputGroups = outputModel->GetMutableGroups();
	ShadowWolf0xc* outputMaterials = outputModel->GetMaterialTable();
	LegoU32 outputIndex = 0;
	LegoU32 vertexOffset = static_cast<LegoU32>(m_unk0x3c.m_unk0x00);
	LegoU32 indexOffset = static_cast<LegoU32>(m_unk0x3c.m_unk0x04);
	LegoS32 i;

	const LegoU32* bodyGroups = bodyModel->GetGroups();
	for (i = 0; i < m_unk0x3c.m_unk0x08 && bodyGroups[i] != 0xc0000000; i++) {
		outputGroups[outputIndex++] = bodyGroups[i];
	}

	const LegoU32* headGroups = headModel->GetGroups();
	for (i = 0; i < m_unk0x50.m_unk0x08 && headGroups[i] != 0xc0000000; i++) {
		LegoU32 command = headGroups[i];
		LegoU32 tag = command & 0xe0000000;
		if (tag == 0x00000000) {
			LegoU32 vertexCount = command & 0x003f0000;
			LegoU32 sourceVertex = (command + vertexOffset) & 0xffff;
			LegoU32 flags = command & 0x0fc00000;
			command = flags | vertexCount | sourceVertex;
		}
		else if (tag == 0x20000000) {
			LegoU32 indexCount = command & 0x007f0000;
			LegoU32 sourceIndex = (command + indexOffset) & 0xffff;
			command = 0x20000000 | indexCount | sourceIndex;
		}
		else if (tag == 0x80000000) {
			LegoU32 materialIndex = command & 0x00ffffff;
			DuskwindBananaRelic0x24* material = headModel->GetMaterialTable()->GetMaterial(materialIndex);
			if (material != NULL) {
				LegoS32 destIndex = outputMaterials->FindEntryIndexByName(material->GetName());
				if (destIndex >= 0) {
					command = 0x80000000 | (static_cast<LegoU32>(destIndex) & 0x00ffffff);
				}
			}
		}

		outputGroups[outputIndex++] = command;
	}

	outputGroups[outputIndex] = 0xc0000000;
	outputModel->SetDirty(TRUE);
}
