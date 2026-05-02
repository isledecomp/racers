#include "championdefinitionlist.h"

#include "gol.h"

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
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
	m_entryCount = 0;
	m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x0041d290
void ChampionDefinitionList::Clear()
{
	ClearDefinitions();

	if (m_unk0x20 != NULL) {
		for (LegoU32 i = 0; i < m_entryCount; i++) {
			m_golExport->VTable0x44(m_unk0x20[i]);
			m_unk0x20[i] = NULL;
		}

		delete[] m_unk0x20;
		m_unk0x20 = NULL;
	}

	if (m_unk0x1c != NULL) {
		for (LegoU32 i = 0; i < m_entryCount; i++) {
			m_golExport->VTable0x40(m_unk0x1c[i]);
			m_unk0x1c[i] = NULL;
		}

		delete[] m_unk0x1c;
		m_unk0x1c = NULL;
	}

	if (m_unk0x18 != NULL) {
		for (LegoU32 i = 0; i < m_entryCount; i++) {
			m_golExport->VTable0x48(m_unk0x18[i]);
			m_unk0x18[i] = NULL;
		}

		delete[] m_unk0x18;
		m_unk0x18 = NULL;
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
