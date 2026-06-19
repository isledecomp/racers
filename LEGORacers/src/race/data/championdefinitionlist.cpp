#include "race/data/championdefinitionlist.h"

#include "core/gol.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmateriallibrary.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "material/goltexturelist.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ChampionDefinitionList, 0x34)
DECOMP_SIZE_ASSERT(ChampionDefinitionList::CcbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(ChampionDefinitionList::ChampionDefinition, 0x30)
DECOMP_SIZE_ASSERT(ChampionDefinitionList::LoadParams, 0x14)

// GLOBAL: LEGORACERS 0x004afde4
extern const LegoFloat g_unk0x004afde4 = 250000.0f;

// FUNCTION: LEGORACERS 0x0041d1a0
ChampionDefinitionList::ChampionDefinitionList()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041d210
ChampionDefinitionList::~ChampionDefinitionList()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041d260
void ChampionDefinitionList::Reset()
{
	m_golExport = NULL;
	m_renderer = NULL;
	m_definitions = NULL;
	m_models = NULL;
	m_textureLists = NULL;
	m_materialLists = NULL;
	m_modelEntities = NULL;
	m_entryCapacity = 0;
	m_entryCount = 0;
	m_binary = 0;
}

// FUNCTION: LEGORACERS 0x0041d290
void ChampionDefinitionList::Clear()
{
	ClearDefinitions();

	if (m_materialLists != NULL) {
		for (LegoU32 i = 0; i < m_entryCount; i++) {
			m_golExport->DestroyMaterialList(m_materialLists[i]);
			m_materialLists[i] = NULL;
		}

		delete[] m_materialLists;
		m_materialLists = NULL;
	}

	if (m_textureLists != NULL) {
		for (LegoU32 i = 0; i < m_entryCount; i++) {
			m_golExport->DestroyTextureList(m_textureLists[i]);
			m_textureLists[i] = NULL;
		}

		delete[] m_textureLists;
		m_textureLists = NULL;
	}

	if (m_models != NULL) {
		for (LegoU32 i = 0; i < m_entryCount; i++) {
			m_golExport->VTable0x48(m_models[i]);
			m_models[i] = NULL;
		}

		delete[] m_models;
		m_models = NULL;
	}

	if (m_modelEntities != NULL) {
		delete[] m_modelEntities;
		m_modelEntities = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0041dae0 FOLDED
void ChampionDefinitionList::ClearDefinitions()
{
	GolNameTable::Clear();
	if (m_definitions != NULL) {
		delete[] m_definitions;
		m_definitions = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0041d370
void ChampionDefinitionList::FUN_0041d370(const LoadParams* p_params)
{
	if (m_definitions != NULL) {
		Clear();
	}

	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_binary = p_params->m_binary;

	GolFileParser* parser;
	if (m_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".ccb");
	}
	else {
		parser = new CcbTxtParser;
	}

	parser->OpenFileForRead(p_params->m_fileName);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

	LegoU32 count = parser->ReadBracketedCountAndLeftCurly();
	if (count != 0) {
		m_definitions = new ChampionDefinition[count];
		if (m_definitions == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		GolNameTable::Allocate(count);

		for (LegoU32 i = 0; i < count; i++) {
			GolName name;
			m_definitions[i].m_unk0x00[0] = '\0';
			m_definitions[i].m_unk0x08[0] = '\0';
			m_definitions[i].m_unk0x10[0] = '\0';
			m_definitions[i].m_unk0x18[0] = '\0';
			m_definitions[i].m_unk0x20 = 0.0f;
			m_definitions[i].m_unk0x24 = 0.0f;
			m_definitions[i].m_unk0x28 = 0.0f;
			m_definitions[i].m_unk0x2c = 0.0f;

			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			::strncpy(name, parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token;
			while ((token = parser->GetNextToken()) != GolFileParser::e_rightCurly) {
				switch (token) {
				case GolFileParser::e_unknown0x28:
					::strncpy(
						m_definitions[i].m_unk0x00,
						parser->ReadStringWithMaxLength(sizeof(m_definitions[i].m_unk0x00)),
						sizeof(m_definitions[i].m_unk0x00)
					);
					break;
				case GolFileParser::e_unknown0x29:
					::strncpy(
						m_definitions[i].m_unk0x08,
						parser->ReadStringWithMaxLength(sizeof(m_definitions[i].m_unk0x08)),
						sizeof(m_definitions[i].m_unk0x08)
					);
					break;
				case GolFileParser::e_unknown0x2a:
					::strncpy(
						m_definitions[i].m_unk0x10,
						parser->ReadStringWithMaxLength(sizeof(m_definitions[i].m_unk0x10)),
						sizeof(m_definitions[i].m_unk0x10)
					);
					break;
				case GolFileParser::e_unknown0x2b:
					::strncpy(
						m_definitions[i].m_unk0x18,
						parser->ReadStringWithMaxLength(sizeof(m_definitions[i].m_unk0x18)),
						sizeof(m_definitions[i].m_unk0x18)
					);
					break;
				case GolFileParser::e_unknown0x2c:
					m_definitions[i].m_unk0x20 = parser->ReadFloat();
					break;
				case GolFileParser::e_unknown0x2d:
					m_definitions[i].m_unk0x24 = parser->ReadFloat();
					m_definitions[i].m_unk0x28 = parser->ReadFloat();
					m_definitions[i].m_unk0x2c = parser->ReadFloat();
					break;
				default:
					parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}
			}

			AddName(name, &m_definitions[i]);
		}
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}

	if (p_params->m_entryCapacity == -1) {
		m_entryCapacity = count;
	}
	else {
		m_entryCapacity = p_params->m_entryCapacity;
	}

	if (m_entryCapacity != 0) {
		m_modelEntities = new GolModelEntity[m_entryCapacity];
		if (m_modelEntities == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_models = new GolModelBase*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textureLists = new GolTextureList*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_materialLists = new GolMaterialLibrary*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_entryCapacity; i++) {
			m_models[i] = NULL;
			m_textureLists[i] = NULL;
			m_materialLists[i] = NULL;
		}
	}

	m_entryCount = 0;
}

// FUNCTION: LEGORACERS 0x0041d780
GolModelEntity* ChampionDefinitionList::FUN_0041d780(const LegoChar* p_name)
{
	ChampionDefinition* definition = static_cast<ChampionDefinition*>(GetName(p_name));
	return FUN_0041d7a0(definition);
}

// FUNCTION: LEGORACERS 0x0041d7a0
GolModelEntity* ChampionDefinitionList::FUN_0041d7a0(ChampionDefinition* p_definition)
{
	LegoChar name[sizeof(GolName) + 1];

	m_textureLists[m_entryCount] = m_golExport->CreateTextureList();
	::strncpy(name, p_definition->m_unk0x08, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_textureLists[m_entryCount]->VTable0x24(m_renderer, p_definition->m_unk0x08, m_binary);

	m_materialLists[m_entryCount] = m_golExport->CreateMaterialList();
	::strncpy(name, p_definition->m_unk0x00, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_materialLists[m_entryCount]->VTable0x24(m_renderer, name, m_binary);

	m_models[m_entryCount] = m_golExport->VTable0x14();
	::strncpy(name, p_definition->m_unk0x10, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_models[m_entryCount]->VTable0x1c(m_renderer, name, m_binary);

	m_modelEntities[m_entryCount].VTable0x50(m_models[m_entryCount], g_unk0x004afde4);
	m_entryCount++;

	return &m_modelEntities[m_entryCount - 1];
}
