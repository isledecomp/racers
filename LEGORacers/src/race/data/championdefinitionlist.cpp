#include "race/data/championdefinitionlist.h"

#include "core/gol.h"

DECOMP_SIZE_ASSERT(ChampionDefinitionList, 0x34)
DECOMP_SIZE_ASSERT(ChampionDefinitionList::CcbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(ChampionDefinitionList::ChampionDefinition, 0x30)

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
	m_unk0x10 = 0;
	m_definitions = NULL;
	m_models = NULL;
	m_textureLists = NULL;
	m_materialLists = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
	m_entryCount = 0;
	m_unk0x30 = 0;
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

	if (m_unk0x24 != NULL) {
		delete[] m_unk0x24;
		m_unk0x24 = NULL;
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
