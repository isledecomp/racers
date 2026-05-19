#include "turquoiseglow0x80.h"

#include "amberhaze0x1c.h"
#include "bronzefalcon0xc8770.h"
#include "gol.h"
#include "golbinparser.h"
#include "golerror.h"
#include "igdbmodel0x40.h"
#include "magentaribbon0x20.h"
#include "opalhaven0xf4.h"
#include "whitefalconnode0x18.h"

#include <string.h>

DECOMP_SIZE_ASSERT(TurquoiseGlow0x80, 0x80)
DECOMP_SIZE_ASSERT(TurquoiseGlowColor, 0x05)
DECOMP_SIZE_ASSERT(TurquoiseGlow0x80::LoadParams, 0x14)
DECOMP_SIZE_ASSERT(TurquoiseGlow0x80::Entry0x30, 0x30)

// GLOBAL: LEGORACERS 0x004b00a0
LegoFloat g_unk0x004b00a0 = 250000.0f;

// FUNCTION: LEGORACERS 0x00420680
TurquoiseGlow0x80::TurquoiseGlow0x80()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00420710
TurquoiseGlow0x80::~TurquoiseGlow0x80()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00420780
void TurquoiseGlow0x80::Reset()
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
void TurquoiseGlow0x80::Clear()
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
			m_golExport->VTable0x48(m_models[i]);
			m_models[i] = NULL;
		}

		delete[] m_models;
		m_models = NULL;
	}

	if (m_rootNode != NULL) {
		m_golExport->VTable0x4c(m_rootNode);
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
void TurquoiseGlow0x80::ClearEntries()
{
	GolNameTable::Clear();

	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004208f0
void TurquoiseGlow0x80::Load(LoadParams* p_params)
{
	m_golExport = p_params->m_golExport;
	m_renderer = p_params->m_renderer;
	m_binary = p_params->m_unk0x10;

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
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

	LegoU32 entryCount = parser->ReadBracketedCountAndLeftCurly();
	if (entryCount != 0) {
		m_entries = new Entry0x30[entryCount];
		if (m_entries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		GolNameTable::Allocate(entryCount);

		for (LegoU32 i = 0; i < entryCount; i++) {
			GolName name;

			m_entries[i].m_unk0x00 = 0;
			m_entries[i].m_unk0x02[0] = '\0';
			m_entries[i].m_unk0x0a[0] = '\0';
			m_entries[i].m_unk0x12[0] = '\0';
			m_entries[i].m_unk0x1a[0] = '\0';
			m_entries[i].m_unk0x22 = 0;
			m_entries[i].m_unk0x23 = 0;
			m_entries[i].m_unk0x24 = 0;
			m_entries[i].m_unk0x25 = 0;
			m_entries[i].m_unk0x26 = 0;
			m_entries[i].m_unk0x27 = 0;
			m_entries[i].m_unk0x28 = 0;
			m_entries[i].m_unk0x29 = 0;
			m_entries[i].m_unk0x2a = 0;
			m_entries[i].m_color.m_unk0x00 = 0;
			m_entries[i].m_color.m_unk0x01 = 0;
			m_entries[i].m_color.m_unk0x02 = 0;
			m_entries[i].m_color.m_unk0x03 = 0;
			m_entries[i].m_color.m_unk0x04 = 0;

			parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
			::strncpy(name, parser->ReadStringWithMaxLength(sizeOfArray(name)), sizeOfArray(name));
			parser->ReadLeftCurly();

			GolFileParser::ParserTokenType token;
			while ((token = parser->GetNextToken()) != GolFileParser::e_rightCurly) {
				switch (token) {
				case GolFileParser::e_unknown0x33:
					m_entries[i].m_unk0x00 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x28:
					::strncpy(
						m_entries[i].m_unk0x02,
						parser->ReadStringWithMaxLength(sizeOfArray(m_entries[i].m_unk0x02)),
						sizeOfArray(m_entries[i].m_unk0x02)
					);
					break;
				case GolFileParser::e_unknown0x29:
					::strncpy(
						m_entries[i].m_unk0x0a,
						parser->ReadStringWithMaxLength(sizeOfArray(m_entries[i].m_unk0x0a)),
						sizeOfArray(m_entries[i].m_unk0x0a)
					);
					break;
				case GolFileParser::e_unknown0x2a:
					::strncpy(
						m_entries[i].m_unk0x12,
						parser->ReadStringWithMaxLength(sizeOfArray(m_entries[i].m_unk0x12)),
						sizeOfArray(m_entries[i].m_unk0x12)
					);
					break;
				case GolFileParser::e_unknown0x2b:
					::strncpy(
						m_entries[i].m_unk0x1a,
						parser->ReadStringWithMaxLength(sizeOfArray(m_entries[i].m_unk0x1a)),
						sizeOfArray(m_entries[i].m_unk0x1a)
					);
					break;
				case GolFileParser::e_unknown0x2c:
					m_entries[i].m_unk0x24 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x2d:
					m_entries[i].m_unk0x25 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x2e:
					m_entries[i].m_unk0x26 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x2f:
					m_entries[i].m_unk0x27 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x30:
					m_entries[i].m_unk0x28 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x31:
					m_entries[i].m_unk0x29 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x34:
					m_entries[i].m_unk0x2a = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x35:
					m_entries[i].m_color.m_unk0x00 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x36:
					m_entries[i].m_color.m_unk0x01 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x37:
					m_entries[i].m_color.m_unk0x02 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x38:
					m_entries[i].m_color.m_unk0x03 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x39:
					m_entries[i].m_color.m_unk0x04 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x3a:
					m_entries[i].m_unk0x22 = parser->ReadInteger();
					m_entries[i].m_unk0x23 = parser->ReadInteger();
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

	if (p_params->m_unk0x08 == 0xffffffff) {
		m_entryCapacity = entryCount;
	}
	else {
		m_entryCapacity = p_params->m_unk0x08;
	}

	if (m_entryCapacity != 0) {
		m_loadedEntries = new OpalHaven0xf4[m_entryCapacity];
		if (m_loadedEntries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_models = new IGdbModel0x40*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textures = new MagentaRibbon0x20*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_materials = new AmberHaze0x1c*[m_entryCapacity];
		if (m_models == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_entryCapacity; i++) {
			m_models[i] = NULL;
			m_textures[i] = NULL;
			m_materials[i] = NULL;
		}

		m_rootNode = m_golExport->VTable0x18();
		m_rootNode->VTable0x14("pelvis", m_binary);
		m_modelParts.VTable0x14("pelvis", m_binary);
	}

	m_loadedEntryCount = 0;
}

// FUNCTION: LEGORACERS 0x00420eb0
void TurquoiseGlow0x80::LoadStrings()
{
	m_strings.UseOwnedBuffers();
	m_strings.Load("drivers.srf");
}

// FUNCTION: LEGORACERS 0x00420ed0
OpalHaven0xf4* TurquoiseGlow0x80::LoadEntry(const LegoChar* p_name)
{
	return LoadEntry(static_cast<Entry0x30*>(GetName(p_name)));
}

// FUNCTION: LEGORACERS 0x00420ef0
OpalHaven0xf4* TurquoiseGlow0x80::LoadEntry(Entry0x30* p_entry)
{
	LegoChar name[sizeof(GolName) + 1];

	m_textures[m_loadedEntryCount] = m_golExport->CreateTextureList();
	::strncpy(name, p_entry->m_unk0x0a, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_textures[m_loadedEntryCount]->VTable0x24(m_renderer, name, m_binary);

	m_materials[m_loadedEntryCount] = m_golExport->CreateMaterialList();
	::strncpy(name, p_entry->m_unk0x02, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_materials[m_loadedEntryCount]->VTable0x24(m_renderer, name, m_binary);

	m_models[m_loadedEntryCount] = m_golExport->VTable0x14();
	::strncpy(name, p_entry->m_unk0x12, sizeof(GolName));
	name[sizeof(GolName)] = '\0';
	m_models[m_loadedEntryCount]->VTable0x1c(m_renderer, name, m_binary);

	m_loadedEntries[m_loadedEntryCount]
		.FUN_0040d550(m_models[m_loadedEntryCount], m_rootNode, &m_modelParts, g_unk0x004b00a0);
	m_loadedEntryCount++;

	return &m_loadedEntries[m_loadedEntryCount - 1];
}

// FUNCTION: LEGORACERS 0x00421020
void TurquoiseGlow0x80::FUN_00421020(const LegoChar* p_name, TurquoiseGlowColor* p_color)
{
	Entry0x30* entry = static_cast<Entry0x30*>(GetName(p_name));

	p_color->m_unk0x00 = entry->m_color.m_unk0x00;
	p_color->m_unk0x01 = entry->m_color.m_unk0x01;
	p_color->m_unk0x02 = entry->m_color.m_unk0x02;
	p_color->m_unk0x03 = entry->m_color.m_unk0x03;
	p_color->m_unk0x04 = entry->m_color.m_unk0x04;
}

// FUNCTION: LEGORACERS 0x00421050
void TurquoiseGlow0x80::FUN_00421050(LegoU32 p_index, TurquoiseGlowColor* p_color)
{
	Entry0x30& entry = m_entries[p_index];

	p_color->m_unk0x00 = entry.m_color.m_unk0x00;
	p_color->m_unk0x01 = entry.m_color.m_unk0x01;
	p_color->m_unk0x02 = entry.m_color.m_unk0x02;
	p_color->m_unk0x03 = entry.m_color.m_unk0x03;
	p_color->m_unk0x04 = entry.m_color.m_unk0x04;
}
