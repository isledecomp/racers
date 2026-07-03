#include "racer/drivercosmetictable.h"

#include "core/gol.h"
#include "golanimatedentity.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmateriallibrary.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "material/goltexturelist.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(DriverCosmeticTable, 0x80)
DECOMP_SIZE_ASSERT(DriverCosmeticTable::DdfTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(DriverCosmetics, 0x05)
DECOMP_SIZE_ASSERT(DriverCosmeticTable::LoadParams, 0x14)
DECOMP_SIZE_ASSERT(DriverCosmeticTable::Entry, 0x30)

// GLOBAL: LEGORACERS 0x004b00a0
LegoFloat g_unk0x004b00a0 = 250000.0f;

// FUNCTION: LEGORACERS 0x00420680
DriverCosmeticTable::DriverCosmeticTable()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00420710
DriverCosmeticTable::~DriverCosmeticTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00420780
void DriverCosmeticTable::Reset()
{
	m_golExport = NULL;
	m_renderer = NULL;
	m_entries = NULL;
	m_models = NULL;
	m_textures = NULL;
	m_materials = NULL;
	m_loadedEntries = NULL;
	m_rootNode = NULL;
	m_entryCapacity = 0;
	m_loadedEntryCount = 0;
	m_binary = FALSE;
}

// FUNCTION: LEGORACERS 0x004207b0
void DriverCosmeticTable::Clear()
{
	ClearEntries();

	if (m_materials != NULL) {
		for (LegoU32 i = 0; i < m_loadedEntryCount; i++) {
			m_golExport->DestroyMaterialList(m_materials[i]);
			m_materials[i] = NULL;
		}

		delete[] m_materials;
		m_materials = NULL;
	}

	if (m_textures != NULL) {
		for (LegoU32 i = 0; i < m_loadedEntryCount; i++) {
			m_golExport->DestroyTextureList(m_textures[i]);
			m_textures[i] = NULL;
		}

		delete[] m_textures;
		m_textures = NULL;
	}

	if (m_models != NULL) {
		for (LegoU32 i = 0; i < m_loadedEntryCount; i++) {
			m_golExport->DestroyModel(m_models[i]);
			m_models[i] = NULL;
		}

		delete[] m_models;
		m_models = NULL;
	}

	if (m_rootNode != NULL) {
		m_golExport->DestroySceneNode(m_rootNode);
		m_rootNode = NULL;
	}

	if (m_loadedEntries != NULL) {
		delete[] m_loadedEntries;
		m_loadedEntries = NULL;
	}

	m_modelParts.Clear();
	m_strings.ReleaseOwnedBuffers();
	Reset();
}

// FUNCTION: LEGORACERS 0x004208c0
void DriverCosmeticTable::ClearEntries()
{
	GolNameTable::Clear();

	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004208f0
void DriverCosmeticTable::Load(LoadParams* p_params)
{
	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_binary = p_params->m_binary;

	GolFileParser* parser;
	if (m_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".ddb");
	}
	else {
		parser = new DdfTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_params->m_filename);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(DdfTxtParser::e_driver));

	LegoU32 entryCount = parser->ReadBracketedCountAndLeftCurly();
	if (entryCount != 0) {
		m_entries = new Entry[entryCount];
		if (m_entries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		GolNameTable::Allocate(entryCount);

		for (LegoU32 i = 0; i < entryCount; i++) {
			GolName name;

			m_entries[i].m_unk0x00 = 0;
			m_entries[i].m_materialName[0] = '\0';
			m_entries[i].m_textureName[0] = '\0';
			m_entries[i].m_modelName[0] = '\0';
			m_entries[i].m_championName[0] = '\0';
			m_entries[i].m_aiChargeColor = 0;
			m_entries[i].m_aiChargeTarget = 0;
			m_entries[i].m_redStat = 0;
			m_entries[i].m_yellowStat = 0;
			m_entries[i].m_greenStat = 0;
			m_entries[i].m_blueStat = 0;
			m_entries[i].m_stat4 = 0;
			m_entries[i].m_stat5 = 0;
			m_entries[i].m_voiceBankIndex = 0;
			m_entries[i].m_cosmetics.m_hatIndex = 0;
			m_entries[i].m_cosmetics.m_faceIndex = 0;
			m_entries[i].m_cosmetics.m_torsoIndex = 0;
			m_entries[i].m_cosmetics.m_legIndex = 0;
			m_entries[i].m_cosmetics.m_expressionIndex = 0;

			parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(DdfTxtParser::e_driver));
			::strncpy(name, parser->ReadStringWithMaxLength(sizeOfArray(name)), sizeOfArray(name));
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token;
			while ((token = parser->GetNextToken()) != GolFileParser::e_rightCurly) {
				switch (token) {
				case DdfTxtParser::e_unknown0x33:
					m_entries[i].m_unk0x00 = parser->ReadInteger();
					break;
				case DdfTxtParser::e_material:
					::strncpy(
						m_entries[i].m_materialName,
						parser->ReadStringWithMaxLength(sizeOfArray(m_entries[i].m_materialName)),
						sizeOfArray(m_entries[i].m_materialName)
					);
					break;
				case DdfTxtParser::e_texture:
					::strncpy(
						m_entries[i].m_textureName,
						parser->ReadStringWithMaxLength(sizeOfArray(m_entries[i].m_textureName)),
						sizeOfArray(m_entries[i].m_textureName)
					);
					break;
				case DdfTxtParser::e_model:
					::strncpy(
						m_entries[i].m_modelName,
						parser->ReadStringWithMaxLength(sizeOfArray(m_entries[i].m_modelName)),
						sizeOfArray(m_entries[i].m_modelName)
					);
					break;
				case DdfTxtParser::e_champion:
					::strncpy(
						m_entries[i].m_championName,
						parser->ReadStringWithMaxLength(sizeOfArray(m_entries[i].m_championName)),
						sizeOfArray(m_entries[i].m_championName)
					);
					break;
				case DdfTxtParser::e_redStat:
					m_entries[i].m_redStat = parser->ReadInteger();
					break;
				case DdfTxtParser::e_yellowStat:
					m_entries[i].m_yellowStat = parser->ReadInteger();
					break;
				case DdfTxtParser::e_greenStat:
					m_entries[i].m_greenStat = parser->ReadInteger();
					break;
				case DdfTxtParser::e_blueStat:
					m_entries[i].m_blueStat = parser->ReadInteger();
					break;
				case DdfTxtParser::e_stat4:
					m_entries[i].m_stat4 = parser->ReadInteger();
					break;
				case DdfTxtParser::e_stat5:
					m_entries[i].m_stat5 = parser->ReadInteger();
					break;
				case DdfTxtParser::e_voiceBank:
					m_entries[i].m_voiceBankIndex = parser->ReadInteger();
					break;
				case DdfTxtParser::e_hat:
					m_entries[i].m_cosmetics.m_hatIndex = parser->ReadInteger();
					break;
				case DdfTxtParser::e_face:
					m_entries[i].m_cosmetics.m_faceIndex = parser->ReadInteger();
					break;
				case DdfTxtParser::e_torso:
					m_entries[i].m_cosmetics.m_torsoIndex = parser->ReadInteger();
					break;
				case DdfTxtParser::e_legs:
					m_entries[i].m_cosmetics.m_legIndex = parser->ReadInteger();
					break;
				case DdfTxtParser::e_expression:
					m_entries[i].m_cosmetics.m_expressionIndex = parser->ReadInteger();
					break;
				case DdfTxtParser::e_aiCharge:
					m_entries[i].m_aiChargeColor = parser->ReadInteger();
					m_entries[i].m_aiChargeTarget = parser->ReadInteger();
					break;
				default:
					parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
					break;
				}
			}

			GolNameTable::AddName(name, &m_entries[i]);
		}
	}

	parser->ReadRightCurly();
	parser->Dispose();

	if (parser != NULL) {
		delete parser;
	}

	if (p_params->m_entryCapacity == 0xffffffff) {
		m_entryCapacity = entryCount;
	}
	else {
		m_entryCapacity = p_params->m_entryCapacity;
	}

	if (m_entryCapacity != 0) {
		m_loadedEntries = new GolAnimatedEntity[m_entryCapacity];
		if (m_loadedEntries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_models = new GolModelBase*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textures = new GolTextureList*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_materials = new GolMaterialLibrary*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_entryCapacity; i++) {
			m_models[i] = NULL;
			m_textures[i] = NULL;
			m_materials[i] = NULL;
		}

		m_rootNode = m_golExport->CreateSceneNode();
		m_rootNode->Load("pelvis", m_binary);
		m_modelParts.Load("pelvis", m_binary);
	}

	m_loadedEntryCount = 0;
}

// FUNCTION: LEGORACERS 0x00420eb0
void DriverCosmeticTable::LoadStrings()
{
	m_strings.UseOwnedBuffers();
	m_strings.Load("drivers.srf");
}

// FUNCTION: LEGORACERS 0x00420ed0
GolAnimatedEntity* DriverCosmeticTable::LoadEntry(const LegoChar* p_name)
{
	return LoadEntry(static_cast<Entry*>(GetName(p_name)));
}

// FUNCTION: LEGORACERS 0x00420ef0
GolAnimatedEntity* DriverCosmeticTable::LoadEntry(Entry* p_entry)
{
	LegoChar name[sizeof(GolName) + 1];

	m_textures[m_loadedEntryCount] = m_golExport->CreateTextureList();
	::strncpy(name, p_entry->m_textureName, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_textures[m_loadedEntryCount]->Load(m_renderer, name, m_binary);

	m_materials[m_loadedEntryCount] = m_golExport->CreateMaterialList();
	::strncpy(name, p_entry->m_materialName, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_materials[m_loadedEntryCount]->Load(m_renderer, name, m_binary);

	m_models[m_loadedEntryCount] = m_golExport->CreateModel();
	::strncpy(name, p_entry->m_modelName, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_models[m_loadedEntryCount]->Load(m_renderer, name, m_binary);

	m_loadedEntries[m_loadedEntryCount]
		.SetModel(m_models[m_loadedEntryCount], m_rootNode, &m_modelParts, g_unk0x004b00a0);
	m_loadedEntryCount++;

	return &m_loadedEntries[m_loadedEntryCount - 1];
}

// FUNCTION: LEGORACERS 0x00421020
void DriverCosmeticTable::CopyCosmetics(const LegoChar* p_name, DriverCosmetics* p_cosmetics)
{
	Entry* entry = static_cast<Entry*>(GetName(p_name));

	p_cosmetics->m_hatIndex = entry->m_cosmetics.m_hatIndex;
	p_cosmetics->m_faceIndex = entry->m_cosmetics.m_faceIndex;
	p_cosmetics->m_torsoIndex = entry->m_cosmetics.m_torsoIndex;
	p_cosmetics->m_legIndex = entry->m_cosmetics.m_legIndex;
	p_cosmetics->m_expressionIndex = entry->m_cosmetics.m_expressionIndex;
}

// FUNCTION: LEGORACERS 0x00421050
void DriverCosmeticTable::CopyCosmetics(LegoU32 p_index, DriverCosmetics* p_cosmetics)
{
	Entry& entry = m_entries[p_index];

	p_cosmetics->m_hatIndex = entry.m_cosmetics.m_hatIndex;
	p_cosmetics->m_faceIndex = entry.m_cosmetics.m_faceIndex;
	p_cosmetics->m_torsoIndex = entry.m_cosmetics.m_torsoIndex;
	p_cosmetics->m_legIndex = entry.m_cosmetics.m_legIndex;
	p_cosmetics->m_expressionIndex = entry.m_cosmetics.m_expressionIndex;
}

// FUNCTION: LEGORACERS 0x00421090
undefined2* DriverCosmeticTable::GetStringBuffer(const LegoChar* p_name)
{
	Entry* entry = static_cast<Entry*>(GetName(p_name));
	return m_strings.GetStringBuffer(entry->m_unk0x00);
}
