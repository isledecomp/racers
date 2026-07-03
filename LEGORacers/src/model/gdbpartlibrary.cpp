#include "model/gdbpartlibrary.h"

#include "gdbmodelindexarray.h"
#include "gdbmodelindexarraybase.h"
#include "gdbvertexarray.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmaterial.h"
#include "golmodelbase.h"
#include "golmodelmaterialtable.h"
#include "golname.h"
#include "goltxtparser.h"
#include "model/gdbpartdefinition.h"
#include "model/gdbpartfacegroup.h"
#include "model/gdbpartvertexpool.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GdbPartLibrary, 0x1c)
DECOMP_SIZE_ASSERT(GdbPartLibrary::GdbTxtParser, 0x1fc)

static const LegoU32 g_gdbPartBatchVertexCapacity = 0x40;
static const LegoU32 g_gdbPartModelDirty = 1;

// GLOBAL: LEGORACERS 0x004c2734
static LegoU16 g_copyBatchSourceVertices[g_gdbPartBatchVertexCapacity];

// GLOBAL: LEGORACERS 0x004c2834
static GolModelBase* g_copyModel;

// GLOBAL: LEGORACERS 0x004c2838
static GdbVertexArray* g_copyVertexArray;

// GLOBAL: LEGORACERS 0x004c283c
static GdbModelIndexArray::Indices* g_copyIndices;

// GLOBAL: LEGORACERS 0x004c2840
static LegoU32 g_copyBatchVertexStart;

// GLOBAL: LEGORACERS 0x004c2844
static LegoU32 g_copyBatchVertexCount;

// GLOBAL: LEGORACERS 0x004c2848
static LegoU32 g_copyIndexStart;

// GLOBAL: LEGORACERS 0x004c284c
static LegoU32 g_copyBatchIndexCount;

// GLOBAL: LEGORACERS 0x004c2850
static LegoU32 g_copyGroupWrite;

// FUNCTION: LEGORACERS 0x004075c0
GdbPartLibrary::GdbPartLibrary()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00407630
GdbPartLibrary::~GdbPartLibrary()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00407680
void GdbPartLibrary::Reset()
{
	m_vertexPool = NULL;
	m_partCount = 0;
	m_parts = NULL;
	m_unk0x18 = 0;
}

// FUNCTION: LEGORACERS 0x00407690
void GdbPartLibrary::Load(const LegoChar* p_filename, LegoBool32 p_binary)
{
	if (m_vertexPool != NULL) {
		Clear();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".gcb");
	}
	else {
		parser = new GdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	m_vertexPool = new GdbPartVertexPool;
	if (m_vertexPool == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	parser->OpenFileForRead(p_filename);
	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GdbPartLibrary::GdbTxtParser::e_uncoloredVertices:
			m_vertexPool->Read(*parser, 2);
			break;
		case GdbPartLibrary::GdbTxtParser::e_normalVertices:
			m_vertexPool->Read(*parser, 1);
			break;
		case GdbPartLibrary::GdbTxtParser::e_parts:
			ReadParts(*parser);
			break;
		default:
			break;
		}

		token = parser->GetNextToken();
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: LEGORACERS 0x00407810
void GdbPartLibrary::ReadParts(GolFileParser& p_parser)
{
	m_partCount = p_parser.ReadBracketedCountAndLeftCurly();
	GolNameTable::Allocate(m_partCount);

	m_parts = new GdbPartDefinition[m_partCount];
	for (LegoU32 i = 0; i < m_partCount; i++) {
		GolName name;
		p_parser.AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(GdbPartLibrary::GdbTxtParser::e_parts));
		p_parser.ReadString();
		::strncpy(name, p_parser.GetLastString(), sizeof(name));
		AddName(name, &m_parts[i]);
		m_parts[i].Read(p_parser);
	}
}

// FUNCTION: LEGORACERS 0x00407900
void GdbPartLibrary::Clear()
{
	if (m_parts != NULL) {
		delete[] m_parts;
	}
	if (m_vertexPool != NULL) {
		delete m_vertexPool;
	}

	GolNameTable::Clear();
	Reset();
}

// FUNCTION: LEGORACERS 0x00407950
void GdbPartLibrary::CopyPartToModel(GolD3DRenderDevice* p_renderer, GolModelBase* p_model, const LegoChar* p_name)
{
	GdbPartDefinition* part = static_cast<GdbPartDefinition*>(GetName(p_name));
	if (part == NULL) {
		LegoChar message[64];
		::strncpy(message, p_name, sizeof(GolName));
		message[sizeof(GolName)] = '\0';
		::strcat(message, ": unable to find named mesh");
		GOL_FATALERROR_MESSAGE(message);
	}

	GdbModelIndexArrayBase* indexArrayBase;
	g_copyModel = p_model;
	p_model->GetVertexArray(&g_copyVertexArray);
	g_copyModel->GetIndexArrayInto(&indexArrayBase);
	g_copyIndices = static_cast<GdbModelIndexArray*>(indexArrayBase)->GetMutableIndices();
	g_copyBatchVertexStart = 0;
	g_copyBatchVertexCount = 0;
	g_copyIndexStart = 0;
	g_copyBatchIndexCount = 0;
	g_copyGroupWrite = 0;
	g_copyModel->SetScale(part->m_scale);

	GolModelMaterialTable* materialTable = g_copyModel->GetMaterialTable();
	if (materialTable->GetCount() < part->m_groupCount) {
		materialTable->Clear();
		materialTable->Initialize(p_renderer, part->m_groupCount);
	}
	for (LegoU32 materialIndex = 0; materialIndex < materialTable->GetCount(); materialIndex++) {
		materialTable->m_entries[materialIndex] = NULL;
	}

	for (LegoU32 groupIndex = 0; groupIndex < part->m_groupCount; groupIndex++) {
		GdbPartFaceGroup& group = part->m_groups[groupIndex];
		GolName materialName;
		::memcpy(materialName, group.m_materialName, sizeof(materialName));
		CopyPartGroupStart(p_renderer, groupIndex, materialName);

		LegoU16* index = group.m_indices;
		LegoU16* indexEnd = index + (group.m_triangleCount * 3);
		while (index < indexEnd) {
			EmitCopyTriangle(index[0], index[1], index[2]);
			index += 3;
		}

		FlushCopyBatch();
	}

	LegoU32 groupWrite = g_copyGroupWrite++;
	GolModelBase* model = g_copyModel;
	model->GetMutableGroups()[groupWrite] = 0xc0000000;
	model->SetDirty(TRUE);
	g_copyModel->AddFlags(g_gdbPartModelDirty);
	g_copyModel->AddFlagsWithBounds(g_gdbPartModelDirty, TRUE);
}

// FUNCTION: LEGORACERS 0x00407b40
void GdbPartLibrary::CopyPartGroupStart(
	GolD3DRenderDevice* p_renderer,
	LegoU32 p_groupIndex,
	const LegoChar* p_materialName
)
{
	GolMaterial* material = p_renderer->FindMaterialByName(p_materialName);
	g_copyModel->GetMaterialTable()->SetEntry(p_groupIndex, material);

	LegoU32 groupWrite = g_copyGroupWrite++;
	GolModelBase* model = g_copyModel;
	model->GetMutableGroups()[groupWrite] = (p_groupIndex & 0x00ffffff) | 0x80000000;
	model->SetDirty(TRUE);
}

// FUNCTION: LEGORACERS 0x00407ba0
void GdbPartLibrary::EmitCopyTriangle(LegoU32 p_index0, LegoU32 p_index1, LegoU32 p_index2)
{
	LegoS32 addedCount = 0;
	LegoS32 batchIndex0 = FindCopyBatchVertex(p_index0);
	if (batchIndex0 < 0) {
		addedCount = 1;
	}

	LegoS32 batchIndex1 = FindCopyBatchVertex(p_index1);
	if (batchIndex1 < 0) {
		addedCount++;
	}

	LegoS32 batchIndex2 = FindCopyBatchVertex(p_index2);
	if (batchIndex2 < 0) {
		addedCount++;
	}

	if (g_copyBatchVertexCount + addedCount >= g_gdbPartBatchVertexCapacity) {
		FlushCopyBatch();
		batchIndex0 = -1;
		batchIndex1 = -1;
		batchIndex2 = -1;
	}

	GdbModelIndexArray::Indices* target = &g_copyIndices[g_copyIndexStart + g_copyBatchIndexCount];
	g_copyBatchIndexCount++;

	if (batchIndex0 < 0) {
		target->m_a = static_cast<LegoU8>(CopyBatchVertex(p_index0));
	}
	else {
		target->m_a = static_cast<LegoU8>(batchIndex0);
	}

	if (batchIndex1 < 0) {
		target->m_b = static_cast<LegoU8>(CopyBatchVertex(p_index1));
	}
	else {
		target->m_b = static_cast<LegoU8>(batchIndex1);
	}

	if (batchIndex2 < 0) {
		target->m_c = static_cast<LegoU8>(CopyBatchVertex(p_index2));
	}
	else {
		target->m_c = static_cast<LegoU8>(batchIndex2);
	}
}

// FUNCTION: LEGORACERS 0x00407c70
LegoS32 GdbPartLibrary::FindCopyBatchVertex(LegoU32 p_sourceVertex)
{
	for (LegoU32 index = 0; index < g_copyBatchVertexCount; index++) {
		if (g_copyBatchSourceVertices[index] == p_sourceVertex) {
			return index;
		}
	}

	return -1;
}

// FUNCTION: LEGORACERS 0x00407ca0
LegoS32 GdbPartLibrary::CopyBatchVertex(LegoU32 p_sourceVertex)
{
	g_copyBatchSourceVertices[g_copyBatchVertexCount] = static_cast<LegoU16>(p_sourceVertex);
	LegoU32 targetVertex = g_copyBatchVertexStart + g_copyBatchVertexCount;

	GolVec3 position;
	m_vertexPool->GetPosition(p_sourceVertex, &position);
	g_copyVertexArray->SetPosition(targetVertex, position);

	GolVec2 texCoord;
	m_vertexPool->GetTextureCoordinate(p_sourceVertex, &texCoord);
	g_copyVertexArray->SetTextureCoordinate(targetVertex, texCoord);

	if (m_vertexPool->GetVertexType() == 1) {
		ColorRGBA color;
		m_vertexPool->GetColor(p_sourceVertex, &color);
		g_copyVertexArray->SetColor(targetVertex, color);
	}
	else {
		GolVec3 normal;
		m_vertexPool->GetNormal(p_sourceVertex, &normal);
		g_copyVertexArray->SetNormal(targetVertex, normal);
	}

	return g_copyBatchVertexCount++;
}

// STUB: LEGORACERS 0x00407d60
void GdbPartLibrary::FlushCopyBatch()
{
	if (g_copyBatchIndexCount == 0) {
		return;
	}

	LegoU32 groupWrite = g_copyGroupWrite++;
	LegoU32 batchVertexStart = g_copyBatchVertexStart;
	LegoU32* groups = g_copyModel->GetMutableGroups();
	groups[groupWrite] = 0;
	groups[groupWrite] |= ((g_copyBatchVertexCount + 0xffff) << 16) & 0x003f0000;
	groups[groupWrite] |= batchVertexStart & 0xffff;
	g_copyModel->SetDirty(TRUE);

	groupWrite = g_copyGroupWrite++;
	groups[groupWrite] = 0x20000000;
	groups[groupWrite] |= (g_copyBatchIndexCount & 0x7f) << 16;
	groups[groupWrite] |= g_copyIndexStart & 0xffff;
	g_copyModel->SetDirty(TRUE);

	g_copyBatchVertexStart += g_copyBatchVertexCount;
	g_copyIndexStart += g_copyBatchIndexCount;
	g_copyBatchVertexCount = 0;
	g_copyBatchIndexCount = 0;
}
