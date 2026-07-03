#include "golmodelmaterialtable.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golmodelbase.h"
#include "golname.h"
#include "goltxtparser.h"
#include "render/golrenderdevice.h"

#include <stddef.h>

DECOMP_SIZE_ASSERT(GolModelMaterialTable, 0x0c)

// FUNCTION: GOLDP 0x10025de0 FOLDED
// FUNCTION: LEGORACERS 0x004a00b0 FOLDED
GolModelMaterialTable::GolModelMaterialTable()
{
	m_renderer = NULL;
	m_count = 0;
	m_entries = NULL;
}

// FUNCTION: GOLDP 0x10025df0 FOLDED
// FUNCTION: LEGORACERS 0x004105d0 FOLDED
void GolModelMaterialTable::Initialize(GolRenderDevice* p_renderer, undefined4 p_arg2)
{
	if (m_renderer != NULL) {
		Destroy();
	}

	m_renderer = p_renderer;
	m_count = p_arg2;

	m_entries = new void*[p_arg2];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_entries, 0, sizeof(*m_entries) * m_count);
}

// FUNCTION: GOLDP 0x10025e60
void GolModelMaterialTable::Load(GolRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_renderer != NULL) {
		Destroy();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".gdb");
	}
	else {
		parser = new GolModelBase::GdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(GolModelMaterialTable::e_materials));
	Parse(p_renderer, *parser);

	parser->Dispose();
	delete parser;
}

// FUNCTION: GOLDP 0x10025f90
void GolModelMaterialTable::Parse(GolRenderDevice* p_renderer, GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_renderer != NULL) {
		Destroy();
	}

	m_renderer = p_renderer;
	m_count = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_entries = new void*[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_count; i++) {
		GolName materialName;
		::strncpy(materialName, p_parser.ReadString(), sizeof(materialName));
		GolMaterial* material = m_renderer->FindMaterialByName(materialName);
		m_entries[i] = material;
		if (m_entries[i] == NULL) {
			char message[64];
			::memset(message, 0, sizeof(materialName) + 1);
			::strncpy(message, materialName, sizeof(materialName));
			::strcat(message, ": Material assignment failed");
			GOL_FATALERROR_MESSAGE(message);
		}
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: GOLDP 0x100260d0 FOLDED
// FUNCTION: LEGORACERS 0x00410630 FOLDED
GolModelMaterialTable::~GolModelMaterialTable()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
	m_renderer = NULL;
	m_count = 0;
}

// FUNCTION: GOLDP 0x100260d0 FOLDED
// FUNCTION: LEGORACERS 0x00410630 FOLDED
void GolModelMaterialTable::Destroy()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
	m_renderer = NULL;
	m_count = 0;
}
