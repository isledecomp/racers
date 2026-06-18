#include "racer/chassismodeltable.h"

#include "core/gol.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmodelbase.h"
#include "golname.h"
#include "golscenenode.h"
#include "material/golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ChassisModelTable, 0x3c)
DECOMP_SIZE_ASSERT(ChassisModelTable::CmbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(ChassisModelTable::Item, 0x104)

// GLOBAL: LEGORACERS 0x004afe6c
static const LegoFloat g_unk0x004afe6c = 250000.0f;

// FUNCTION: LEGORACERS 0x0041d8c0
ChassisModelTable::ChassisModelTable()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041d930
ChassisModelTable::~ChassisModelTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041d980
void ChassisModelTable::Reset()
{
	m_golExport = NULL;
	m_renderer = NULL;
	m_items = NULL;
	m_models = NULL;
	m_textureLists = NULL;
	m_materialLists = NULL;
	m_sceneNodes = NULL;
	m_modelParts = NULL;
	m_animatedEntities = NULL;
	m_instantiateCount = 0;
	m_instantiatedCount = 0;
	m_binary = 0;
}

// FUNCTION: LEGORACERS 0x0041d9b0
void ChassisModelTable::Clear()
{
	FUN_0041dae0();

	if (m_modelParts != NULL) {
		delete[] m_modelParts;
		m_modelParts = NULL;
	}

	if (m_sceneNodes != NULL) {
		for (LegoU32 i = 0; i < m_instantiatedCount; i++) {
			m_golExport->VTable0x4c(m_sceneNodes[i]);
			m_sceneNodes[i] = NULL;
		}
		delete[] m_sceneNodes;
		m_sceneNodes = NULL;
	}

	if (m_materialLists != NULL) {
		for (LegoU32 i = 0; i < m_instantiatedCount; i++) {
			m_golExport->DestroyMaterialList(m_materialLists[i]);
			m_materialLists[i] = NULL;
		}
		delete[] m_materialLists;
		m_materialLists = NULL;
	}

	if (m_textureLists != NULL) {
		for (LegoU32 i = 0; i < m_instantiatedCount; i++) {
			m_golExport->DestroyTextureList(m_textureLists[i]);
			m_textureLists[i] = NULL;
		}
		delete[] m_textureLists;
		m_textureLists = NULL;
	}

	if (m_models != NULL) {
		for (LegoU32 i = 0; i < m_instantiatedCount; i++) {
			m_golExport->VTable0x48(m_models[i]);
			m_models[i] = NULL;
		}
		delete[] m_models;
		m_models = NULL;
	}

	if (m_animatedEntities != NULL) {
		delete[] m_animatedEntities;
		m_animatedEntities = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x0041dae0 FOLDED
void ChassisModelTable::FUN_0041dae0()
{
	GolNameTable::Clear();

	if (m_items != NULL) {
		delete[] m_items;
		m_items = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0041db10
LegoU32 ChassisModelTable::FUN_0041db10(const Params* p_params)
{
	if (m_items != NULL) {
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
		parser->SetSuffix(".cmb");
	}
	else {
		parser = new CmbTxtParser;
	}

	parser->OpenFileForRead(p_params->m_filename);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	LegoU32 count = parser->ReadBracketedCountAndLeftCurly();
	if (count != 0) {
		m_items = new Item[count];
		if (m_items == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		GolNameTable::Allocate(count);
	}

	if (p_params->m_instantiateCount == -1) {
		m_instantiateCount = count;
	}
	else {
		m_instantiateCount = static_cast<LegoU32>(p_params->m_instantiateCount);
	}
	::memset(m_items, 0, count * sizeof(Item));
	LegoU32 i;
	for (i = 0; i < count; i++) {
		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		GolName name;
		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		parser->ReadLeftCurly();
		m_items[i].m_unk0x100 = '2';
		m_items[i].m_unk0x102 = '2';
		m_items[i].m_unk0x101 = 'P';
		GolFileParser::ParserTokenType token;
		while ((token = parser->GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				ParseVariantNames(parser, i, 0);
				break;
			case GolFileParser::e_unknown0x29:
				ParseVariantNames(parser, i, 1);
				break;
			case GolFileParser::e_unknown0x39:
				::strncpy(
					m_items[i].m_unk0x50,
					parser->ReadStringWithMaxLength(sizeof(m_items[i].m_unk0x50)),
					sizeof(m_items[i].m_unk0x50)
				);
				break;
			case GolFileParser::e_unknown0x2a:
				m_items[i].m_unk0xb8.m_x = parser->ReadFloat();
				m_items[i].m_unk0xb8.m_y = parser->ReadFloat();
				m_items[i].m_unk0xb8.m_z = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2b:
				m_items[i].m_unk0xc4.m_x = parser->ReadFloat();
				m_items[i].m_unk0xc4.m_y = parser->ReadFloat();
				m_items[i].m_unk0xc4.m_z = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2c:
				m_items[i].m_unk0xd0 = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2d:
				m_items[i].m_unk0xd4.m_x = parser->ReadFloat();
				m_items[i].m_unk0xd4.m_y = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2e:
				m_items[i].m_unk0xdc.m_x = parser->ReadFloat();
				m_items[i].m_unk0xdc.m_y = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2f:
				m_items[i].m_unk0xec = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x30: {
				parser->ReadLeftCurly();
				m_items[i].m_unk0xe4.m_x = parser->ReadFloat();
				m_items[i].m_unk0xe4.m_y = parser->ReadFloat();
				for (LegoS32 j = 0; j < 4; j++) {
					m_items[i].m_unk0x58[j].m_x = parser->ReadFloat();
					m_items[i].m_unk0x58[j].m_y = parser->ReadFloat();
					m_items[i].m_unk0x58[j].m_z = parser->ReadFloat();
				}
				parser->ReadRightCurly();
				break;
			}
			case GolFileParser::e_unknown0x31: {
				parser->ReadLeftCurly();
				for (LegoS32 j = 0; j < 4; j++) {
					m_items[i].m_unk0x88[j].m_x = parser->ReadFloat();
					m_items[i].m_unk0x88[j].m_y = parser->ReadFloat();
					m_items[i].m_unk0x88[j].m_z = parser->ReadFloat();
				}
				parser->ReadRightCurly();
				break;
			}
			case GolFileParser::e_unknown0x32:
				m_items[i].m_unk0xf0 = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x33:
				m_items[i].m_unk0xf4 = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x3a:
				m_items[i].m_unk0x100 = static_cast<LegoU8>(parser->ReadInteger());
				break;
			case GolFileParser::e_unknown0x3b:
				m_items[i].m_unk0x102 = static_cast<LegoU8>(parser->ReadInteger());
				break;
			case GolFileParser::e_unknown0x3c:
				m_items[i].m_unk0x101 = static_cast<LegoU8>(parser->ReadInteger());
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
		AddName(name, &m_items[i]);
	}
	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;

	LegoU32 result = m_instantiateCount;
	if (result != 0) {
		LegoU32 modelCount = 2 * result;
		m_animatedEntities = new GolAnimatedEntity[modelCount];
		if (m_animatedEntities == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_models = new GolModelBase*[modelCount];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_textureLists = new GolTextureList*[modelCount];
		if (m_textureLists == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_materialLists = new GolMaterialLibrary*[modelCount];
		if (m_materialLists == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_sceneNodes = new GolSceneNode*[modelCount];
		if (m_sceneNodes == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_modelParts = new CmbModelPart0x34[modelCount];
		if (m_modelParts == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		result = 0;
		if ((m_instantiateCount & 0x7fffffff) != 0) {
			do {
				result++;
				m_models[result - 1] = NULL;
				m_textureLists[result - 1] = NULL;
				m_materialLists[result - 1] = NULL;
			} while (result < 2 * m_instantiateCount);
		}
	}
	m_instantiatedCount = 0;

	return result;
}

// FUNCTION: LEGORACERS 0x0041e210
void ChassisModelTable::ParseVariantNames(GolFileParser* p_parser, LegoU32 p_index, LegoU32 p_variant)
{
	p_parser->ReadLeftCurly();
	GolFileParser::ParserTokenType token = p_parser->GetNextToken();

	if (token != GolFileParser::e_rightCurly) {
		LegoU32 variant = p_variant;
		LegoU32 index = p_index;
		do {
			switch (token) {
			case GolFileParser::e_unknown0x34:
				::strncpy(
					m_items[index].m_materialNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			case GolFileParser::e_unknown0x35:
				::strncpy(
					m_items[index].m_textureNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			case GolFileParser::e_unknown0x36:
				::strncpy(
					m_items[index].m_modelNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			case GolFileParser::e_unknown0x37:
				::strncpy(
					m_items[index].m_nodeNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			case GolFileParser::e_unknown0x38:
				::strncpy(
					m_items[index].m_modelPartNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			default:
				continue;
			}
		} while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0041e330
LegoU32 ChassisModelTable::InstantiateModels(
	const LegoChar* p_name,
	GolAnimatedEntity** p_primary,
	GolAnimatedEntity** p_secondary
)
{
	Item* item = static_cast<Item*>(GetName(p_name));
	return InstantiateModels(item, p_primary, p_secondary);
}

// FUNCTION: LEGORACERS 0x0041e360
LegoU32 ChassisModelTable::InstantiateModels(
	Item* p_item,
	GolAnimatedEntity** p_primary,
	GolAnimatedEntity** p_secondary
)
{
	*p_primary = &m_animatedEntities[m_instantiatedCount];
	if (!p_item->m_modelNames[1][0]) {
		*p_secondary = NULL;
	}
	else {
		*p_secondary = &m_animatedEntities[m_instantiatedCount + 1];
	}
	p_item->m_primaryModel = *p_primary;
	p_item->m_secondaryModel = *p_secondary;

	LegoChar name[sizeof(GolName) + 1];
	for (LegoU32 i = 0; i < 2; i++) {
		if (i == 1 && *p_secondary == NULL) {
			break;
		}

		m_textureLists[m_instantiatedCount] = m_golExport->CreateTextureList();
		::strncpy(name, p_item->m_textureNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_textureLists[m_instantiatedCount]->VTable0x24(m_renderer, name, m_binary);

		m_materialLists[m_instantiatedCount] = m_golExport->CreateMaterialList();
		::strncpy(name, p_item->m_materialNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_materialLists[m_instantiatedCount]->VTable0x24(m_renderer, name, m_binary);

		m_sceneNodes[m_instantiatedCount] = m_golExport->VTable0x18();
		::strncpy(name, p_item->m_nodeNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_sceneNodes[m_instantiatedCount]->VTable0x14(name, m_binary);

		::strncpy(name, p_item->m_modelPartNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_modelParts[m_instantiatedCount].VTable0x14(name, m_binary);

		m_models[m_instantiatedCount] = m_golExport->VTable0x14();
		::strncpy(name, p_item->m_modelNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_models[m_instantiatedCount]->VTable0x1c(m_renderer, name, m_binary);

		m_animatedEntities[m_instantiatedCount].FUN_0040d550(
			m_models[m_instantiatedCount],
			m_sceneNodes[m_instantiatedCount],
			&m_modelParts[m_instantiatedCount],
			g_unk0x004afe6c
		);
	}

	m_instantiatedCount++;
	return m_instantiatedCount;
}

// FUNCTION: LEGORACERS 0x0041e570
void ChassisModelTable::InstantiateAllModels()
{
	for (LegoU32 i = 0; i < m_instantiateCount; i++) {
		GolAnimatedEntity* primary;
		GolAnimatedEntity* secondary;
		InstantiateModels(&m_items[i], &primary, &secondary);
	}
}

// FUNCTION: LEGORACERS 0x0041e5b0
GolAnimatedEntity* ChassisModelTable::GetPrimaryModel(const LegoChar* p_name)
{
	if (*p_name) {
		Item* item = static_cast<Item*>(GetName(p_name));
		if (item != NULL) {
			return item->m_primaryModel;
		}
	}

	return NULL;
}
