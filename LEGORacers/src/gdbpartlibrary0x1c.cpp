#include "gdbpartlibrary0x1c.h"

#include "../../GolDP/src/gdbmodelindexarray0xc.h"
#include "bronzefalcon0xc8770.h"
#include "duskwindbananarelic0x24.h"
#include "gdbpartdefinition0x0c.h"
#include "gdbpartfacegroup0x14.h"
#include "gdbpartvertexpool0x14.h"
#include "gdbvertexarray0xc.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golname.h"
#include "goltxtparser.h"
#include "igdbmodel0x40.h"
#include "igdbmodelindexarray0x8.h"
#include "shadowwolf0xc.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GdbPartLibrary0x1c, 0x1c)

static const LegoU32 g_gdbPartBatchVertexCapacity = 0x40;
static const LegoU32 g_gdbPartModelDirty = 1;

// GLOBAL: LEGORACERS 0x004c2734
static LegoU16 g_copyBatchSourceVertices[g_gdbPartBatchVertexCapacity];

// GLOBAL: LEGORACERS 0x004c2834
static IGdbModel0x40* g_copyModel;

// GLOBAL: LEGORACERS 0x004c2838
static GdbVertexArray0xc* g_copyVertexArray;

// GLOBAL: LEGORACERS 0x004c283c
static GdbModelIndexArray0xc::Indices* g_copyIndices;

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

static LegoS32 __stdcall FindCopyBatchVertex(LegoU32 p_sourceVertex);

// FUNCTION: LEGORACERS 0x004075c0
GdbPartLibrary0x1c::GdbPartLibrary0x1c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00407630
GdbPartLibrary0x1c::~GdbPartLibrary0x1c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00407680
void GdbPartLibrary0x1c::Reset()
{
	m_vertexPool = NULL;
	m_partCount = 0;
	m_parts = NULL;
	m_unk0x18 = 0;
}

// FUNCTION: LEGORACERS 0x00407690
void GdbPartLibrary0x1c::Load(const LegoChar* p_filename, LegoBool32 p_binary)
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
		parser = new GolTxtParser2;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	m_vertexPool = new GdbPartVertexPool0x14;
	if (m_vertexPool == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	parser->OpenFileForRead(p_filename);
	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x28:
			m_vertexPool->Read(*parser, 2);
			break;
		case GolFileParser::e_unknown0x29:
			m_vertexPool->Read(*parser, 1);
			break;
		case GolFileParser::e_unknown0x2c:
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
void GdbPartLibrary0x1c::ReadParts(GolFileParser& p_parser)
{
	m_partCount = p_parser.ReadBracketedCountAndLeftCurly();
	GolNameTable::Allocate(m_partCount);

	m_parts = new GdbPartDefinition0x0c[m_partCount];
	for (LegoU32 i = 0; i < m_partCount; i++) {
		GolName name;
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x2c);
		p_parser.ReadString();
		::strncpy(name, p_parser.GetLastString(), sizeof(name));
		AddName(name, &m_parts[i]);
		m_parts[i].Read(p_parser);
	}
}

// FUNCTION: LEGORACERS 0x00407900
void GdbPartLibrary0x1c::Clear()
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

// STUB: LEGORACERS 0x00407950
void GdbPartLibrary0x1c::CopyPartToModel(
	BronzeFalcon0xc8770* p_renderer,
	IGdbModel0x40* p_model,
	const LegoChar* p_name
)
{
	STUB(0x00407950);

	GdbPartDefinition0x0c* part = static_cast<GdbPartDefinition0x0c*>(GetName(p_name));
	if (part == NULL) {
		LegoChar message[64];
		::strncpy(message, p_name, sizeof(GolName));
		message[sizeof(GolName)] = '\0';
		::strcat(message, ": unable to find named mesh");
		GOL_FATALERROR_MESSAGE(message);
	}

	IGdbModelIndexArray0x8* indexArrayBase;
	g_copyModel = p_model;
	p_model->VTable0x28(&g_copyVertexArray);
	p_model->VTable0x30(&indexArrayBase);
	g_copyIndices = static_cast<GdbModelIndexArray0xc*>(indexArrayBase)->GetMutableIndices();
	g_copyBatchVertexStart = 0;
	g_copyBatchVertexCount = 0;
	g_copyIndexStart = 0;
	g_copyBatchIndexCount = 0;
	g_copyGroupWrite = 0;
	p_model->SetScale(part->m_scale);

	ShadowWolf0xc* materialTable = p_model->GetMaterialTable();
	if (materialTable->GetCount() < part->m_groupCount) {
		if (materialTable->m_entries != NULL) {
			delete[] materialTable->m_entries;
			materialTable->m_entries = NULL;
		}
		materialTable->m_renderer = p_renderer;
		materialTable->m_count = part->m_groupCount;
		materialTable->m_entries = new void*[part->m_groupCount];
		if (materialTable->m_entries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		::memset(materialTable->m_entries, 0, sizeof(*materialTable->m_entries) * materialTable->m_count);
	}
	for (LegoU32 materialIndex = 0; materialIndex < materialTable->GetCount(); materialIndex++) {
		materialTable->m_entries[materialIndex] = NULL;
	}

	LegoU32* groups = p_model->GetMutableGroups();
	for (LegoU32 clearIndex = 0; clearIndex < p_model->GetGroupCount(); clearIndex++) {
		groups[clearIndex] = 0;
	}

	for (LegoU32 groupIndex = 0; groupIndex < part->m_groupCount; groupIndex++) {
		GdbPartFaceGroup0x14& group = part->m_groups[groupIndex];
		CopyPartGroupStart(p_renderer, groupIndex, group.m_materialName);

		LegoU16* index = group.m_indices;
		LegoU16* indexEnd = index + (group.m_triangleCount * 3);
		while (index < indexEnd) {
			EmitCopyTriangle(index[0], index[1], index[2]);
			index += 3;
		}

		FlushCopyBatch();
	}

	groups[g_copyGroupWrite++] = 0xc0000000;
	p_model->SetDirty(TRUE);
	p_model->VTable0x34(g_gdbPartModelDirty);
	p_model->VTable0x2c(g_gdbPartModelDirty, TRUE);
}

// STUB: LEGORACERS 0x00407b40
void GdbPartLibrary0x1c::CopyPartGroupStart(
	BronzeFalcon0xc8770* p_renderer,
	LegoU32 p_groupIndex,
	const LegoChar* p_materialName
)
{
	STUB(0x00407b40);

	DuskwindBananaRelic0x24* material = p_renderer->FindMaterialByName(p_materialName);
	g_copyModel->GetMaterialTable()->SetPosition(p_groupIndex, material);

	LegoU32 groupWrite = g_copyGroupWrite++;
	LegoU32* groups = g_copyModel->GetMutableGroups();
	groups[groupWrite] = 0x80000000 | (p_groupIndex & 0x00ffffff);
	g_copyModel->SetDirty(TRUE);
}

// STUB: LEGORACERS 0x00407ba0
void GdbPartLibrary0x1c::EmitCopyTriangle(LegoU32 p_index0, LegoU32 p_index1, LegoU32 p_index2)
{
	STUB(0x00407ba0);

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

	GdbModelIndexArray0xc::Indices* target = &g_copyIndices[g_copyIndexStart + g_copyBatchIndexCount];
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
static LegoS32 __stdcall FindCopyBatchVertex(LegoU32 p_sourceVertex)
{
	for (LegoU32 index = 0; index < g_copyBatchVertexCount; index++) {
		if (g_copyBatchSourceVertices[index] == p_sourceVertex) {
			return index;
		}
	}

	return -1;
}

// FUNCTION: LEGORACERS 0x00407ca0
LegoS32 GdbPartLibrary0x1c::CopyBatchVertex(LegoU32 p_sourceVertex)
{
	g_copyBatchSourceVertices[g_copyBatchVertexCount] = static_cast<LegoU16>(p_sourceVertex);
	LegoU32 targetVertex = g_copyBatchVertexStart + g_copyBatchVertexCount;

	GolVec3 position;
	m_vertexPool->GetPosition(p_sourceVertex, &position);
	g_copyVertexArray->VTable0x24(targetVertex, position);

	GolVec2 texCoord;
	m_vertexPool->GetTexCoord(p_sourceVertex, &texCoord);
	g_copyVertexArray->VTable0x28(targetVertex, texCoord);

	if (m_vertexPool->GetVertexType() == 1) {
		ColorRGBA color;
		m_vertexPool->GetColor(p_sourceVertex, &color);
		g_copyVertexArray->VTable0x30(targetVertex, color);
	}
	else {
		GolVec3 normal;
		m_vertexPool->GetNormal(p_sourceVertex, &normal);
		g_copyVertexArray->VTable0x2c(targetVertex, normal);
	}

	return g_copyBatchVertexCount++;
}

// STUB: LEGORACERS 0x00407d60
void GdbPartLibrary0x1c::FlushCopyBatch()
{
	STUB(0x00407d60);

	if (g_copyBatchIndexCount == 0) {
		return;
	}

	LegoU32* groups = g_copyModel->GetMutableGroups();
	LegoU32 groupWrite = g_copyGroupWrite++;
	LegoU32* group = &groups[groupWrite];
	*group = 0;
	LegoU32 groupTag = *group;
	groupTag |= ((g_copyBatchVertexCount + 0xffff) << 16) & 0x003f0000;
	*group = groupTag;
	groupTag = *group;
	groupTag |= g_copyBatchVertexStart & 0xffff;
	*group = groupTag;
	g_copyModel->SetDirty(TRUE);

	groupWrite = g_copyGroupWrite++;
	group = &groups[groupWrite];
	*group = 0x20000000;
	groupTag = *group;
	groupTag |= (g_copyBatchIndexCount & 0x7f) << 16;
	*group = groupTag;
	groupTag = *group;
	groupTag |= g_copyIndexStart & 0xffff;
	*group = groupTag;
	g_copyModel->SetDirty(TRUE);

	g_copyBatchVertexStart += g_copyBatchVertexCount;
	g_copyIndexStart += g_copyBatchIndexCount;
	g_copyBatchVertexCount = 0;
	g_copyBatchIndexCount = 0;
}
