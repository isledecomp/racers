#include "aquamarinespirit0x3c.h"

#include "amberhaze0x1c.h"
#include "bronzefalcon0xc8770.h"
#include "gol.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"
#include "igdbmodel0x40.h"
#include "magentaribbon0x20.h"
#include "opalhaven0xf4.h"
#include "whitefalconnode0x18.h"

#include <string.h>

DECOMP_SIZE_ASSERT(AquamarineSpirit0x3c, 0x3c)
DECOMP_SIZE_ASSERT(AquamarineSpirit0x3c::Item0x104, 0x104)

// GLOBAL: LEGORACERS 0x004afe6c
static const LegoFloat g_unk0x004afe6c = 250000.0f;

// FUNCTION: LEGORACERS 0x0041d8c0
AquamarineSpirit0x3c::AquamarineSpirit0x3c()
{
	FUN_0041d980();
}

// FUNCTION: LEGORACERS 0x0041d930
AquamarineSpirit0x3c::~AquamarineSpirit0x3c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0041d980
void AquamarineSpirit0x3c::FUN_0041d980()
{
	m_unk0x0c = NULL;
	m_unk0x10 = NULL;
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
	m_unk0x2c = NULL;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
}

// FUNCTION: LEGORACERS 0x0041d9b0
void AquamarineSpirit0x3c::Clear()
{
	FUN_0041dae0();

	if (m_unk0x28 != NULL) {
		delete[] m_unk0x28;
		m_unk0x28 = NULL;
	}

	if (m_unk0x24 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x34; i++) {
			m_unk0x0c->VTable0x4c(m_unk0x24[i]);
			m_unk0x24[i] = NULL;
		}
		delete[] m_unk0x24;
		m_unk0x24 = NULL;
	}

	if (m_unk0x20 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x34; i++) {
			m_unk0x0c->DestroyMaterialList(m_unk0x20[i]);
			m_unk0x20[i] = NULL;
		}
		delete[] m_unk0x20;
		m_unk0x20 = NULL;
	}

	if (m_unk0x1c != NULL) {
		for (LegoU32 i = 0; i < m_unk0x34; i++) {
			m_unk0x0c->DestroyTextureList(m_unk0x1c[i]);
			m_unk0x1c[i] = NULL;
		}
		delete[] m_unk0x1c;
		m_unk0x1c = NULL;
	}

	if (m_unk0x18 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x34; i++) {
			m_unk0x0c->VTable0x48(m_unk0x18[i]);
			m_unk0x18[i] = NULL;
		}
		delete[] m_unk0x18;
		m_unk0x18 = NULL;
	}

	if (m_unk0x2c != NULL) {
		delete[] m_unk0x2c;
		m_unk0x2c = NULL;
	}

	FUN_0041d980();
}

// FUNCTION: LEGORACERS 0x0041dae0 FOLDED
void AquamarineSpirit0x3c::FUN_0041dae0()
{
	GolNameTable::Clear();

	if (m_unk0x14 != NULL) {
		delete[] m_unk0x14;
		m_unk0x14 = NULL;
	}
}

// STUB: LEGORACERS 0x0041db10
void AquamarineSpirit0x3c::FUN_0041db10(const Params* p_params)
{
	STUB(0x0041db10);

	if (m_unk0x14 != NULL) {
		Clear();
	}

	m_unk0x0c = p_params->m_unk0x00;
	m_unk0x10 = p_params->m_unk0x04;
	m_unk0x38 = p_params->m_unk0x10;
	GolFileParser* parser;
	if (m_unk0x38) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".cmb");
	}
	else {
		parser = new CmbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_params->m_filename);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	LegoU32 count = parser->ReadBracketedCountAndLeftCurly();
	if (count != 0) {
		m_unk0x14 = new Item0x104[count];
		if (m_unk0x14 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		GolNameTable::Allocate(count);
	}

	if (p_params->m_unk0x08 != -1) {
		m_unk0x30 = static_cast<LegoU32>(p_params->m_unk0x08);
	}
	else {
		m_unk0x30 = count;
	}
	::memset(m_unk0x14, 0, count * sizeof(Item0x104));
	for (LegoU32 i = 0; i < count; i++) {
		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		GolName name;
		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		parser->ReadLeftCurly();
		m_unk0x14[i].m_unk0x100 = '2';
		m_unk0x14[i].m_unk0x102 = '2';
		m_unk0x14[i].m_unk0x101 = 'P';
		GolFileParser::ParserTokenType token;
		while ((token = parser->GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				FUN_0041e210(parser, i, 0);
				break;
			case GolFileParser::e_unknown0x29:
				FUN_0041e210(parser, i, 1);
				break;
			case GolFileParser::e_unknown0x2a:
				m_unk0x14[i].m_unk0xb8.m_x = parser->ReadFloat();
				m_unk0x14[i].m_unk0xb8.m_y = parser->ReadFloat();
				m_unk0x14[i].m_unk0xb8.m_z = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2b:
				m_unk0x14[i].m_unk0xc4.m_x = parser->ReadFloat();
				m_unk0x14[i].m_unk0xc4.m_y = parser->ReadFloat();
				m_unk0x14[i].m_unk0xc4.m_z = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2c:
				m_unk0x14[i].m_unk0xd0 = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2d:
				m_unk0x14[i].m_unk0xd4.m_x = parser->ReadFloat();
				m_unk0x14[i].m_unk0xd4.m_y = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2e:
				m_unk0x14[i].m_unk0xdc.m_x = parser->ReadFloat();
				m_unk0x14[i].m_unk0xdc.m_y = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2f:
				m_unk0x14[i].m_unk0xec = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x30: {
				parser->ReadLeftCurly();
				m_unk0x14[i].m_unk0xe4.m_x = parser->ReadFloat();
				m_unk0x14[i].m_unk0xe4.m_y = parser->ReadFloat();
				for (LegoS32 j = 0; j < 4; j++) {
					m_unk0x14[i].m_unk0x58[j].m_x = parser->ReadFloat();
					m_unk0x14[i].m_unk0x58[j].m_y = parser->ReadFloat();
					m_unk0x14[i].m_unk0x58[j].m_z = parser->ReadFloat();
				}
				parser->ReadRightCurly();
				break;
			}
			case GolFileParser::e_unknown0x31: {
				parser->ReadLeftCurly();
				for (LegoS32 j = 0; j < 4; j++) {
					m_unk0x14[i].m_unk0x88[j].m_x = parser->ReadFloat();
					m_unk0x14[i].m_unk0x88[j].m_y = parser->ReadFloat();
					m_unk0x14[i].m_unk0x88[j].m_z = parser->ReadFloat();
				}
				parser->ReadRightCurly();
				break;
			}
			case GolFileParser::e_unknown0x32:
				m_unk0x14[i].m_unk0xf0 = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x33:
				m_unk0x14[i].m_unk0xf4 = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			case GolFileParser::e_unknown0x39:
				::strncpy(
					m_unk0x14[i].m_unk0x50,
					parser->ReadStringWithMaxLength(sizeof(m_unk0x14[i].m_unk0x50)),
					sizeof(m_unk0x14[i].m_unk0x50)
				);
				break;
			case GolFileParser::e_unknown0x3a:
				m_unk0x14[i].m_unk0x100 = static_cast<LegoU8>(parser->ReadInteger());
				break;
			case GolFileParser::e_unknown0x3b:
				m_unk0x14[i].m_unk0x102 = static_cast<LegoU8>(parser->ReadInteger());
				break;
			case GolFileParser::e_unknown0x3c:
				m_unk0x14[i].m_unk0x101 = static_cast<LegoU8>(parser->ReadInteger());
				break;
			}
		}
		AddName(name, &m_unk0x14[i]);
	}
	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;
	if (m_unk0x30 == 0) {
		m_unk0x34 = 0;
	}
	else {
		LegoU32 modelCount = 2 * m_unk0x30;
		m_unk0x2c = new OpalHaven0xf4[modelCount];
		if (m_unk0x2c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x18 = new IGdbModel0x40*[modelCount];
		if (m_unk0x18 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x1c = new MagentaRibbon0x20*[modelCount];
		if (m_unk0x1c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x20 = new AmberHaze0x1c*[modelCount];
		if (m_unk0x20 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x24 = new WhiteFalconNode0x18*[modelCount];
		if (m_unk0x24 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x28 = new CmbModelPart0x34[modelCount];
		if (m_unk0x28 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		for (LegoU32 i = 0; i < modelCount; i++) {
			m_unk0x18[i] = NULL;
			m_unk0x1c[i] = NULL;
			m_unk0x20[i] = NULL;
			m_unk0x24[i] = NULL;
		}
		m_unk0x34 = 0;
	}
}

// FUNCTION: LEGORACERS 0x0041e210
void AquamarineSpirit0x3c::FUN_0041e210(GolFileParser* p_parser, LegoU32 p_index, LegoU32 p_variant)
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
					m_unk0x14[index].m_materialNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			case GolFileParser::e_unknown0x35:
				::strncpy(
					m_unk0x14[index].m_textureNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			case GolFileParser::e_unknown0x36:
				::strncpy(
					m_unk0x14[index].m_modelNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			case GolFileParser::e_unknown0x37:
				::strncpy(
					m_unk0x14[index].m_nodeNames[variant],
					p_parser->ReadStringWithMaxLength(sizeof(GolName)),
					sizeof(GolName)
				);
				break;
			case GolFileParser::e_unknown0x38:
				::strncpy(
					m_unk0x14[index].m_modelPartNames[variant],
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
LegoU32 AquamarineSpirit0x3c::FUN_0041e330(
	const LegoChar* p_name,
	OpalHaven0xf4** p_primary,
	OpalHaven0xf4** p_secondary
)
{
	Item0x104* item = static_cast<Item0x104*>(GetName(p_name));
	return FUN_0041e360(item, p_primary, p_secondary);
}

// FUNCTION: LEGORACERS 0x0041e360
LegoU32 AquamarineSpirit0x3c::FUN_0041e360(Item0x104* p_item, OpalHaven0xf4** p_primary, OpalHaven0xf4** p_secondary)
{
	*p_primary = &m_unk0x2c[m_unk0x34];
	if (!p_item->m_modelNames[1][0]) {
		*p_secondary = NULL;
	}
	else {
		*p_secondary = &m_unk0x2c[m_unk0x34 + 1];
	}
	p_item->m_primaryModel = *p_primary;
	p_item->m_secondaryModel = *p_secondary;

	LegoChar name[sizeof(GolName) + 1];
	for (LegoU32 i = 0; i < 2; i++) {
		if (i == 1 && *p_secondary == NULL) {
			break;
		}

		m_unk0x1c[m_unk0x34] = m_unk0x0c->CreateTextureList();
		::strncpy(name, p_item->m_textureNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_unk0x1c[m_unk0x34]->VTable0x24(m_unk0x10, name, m_unk0x38);

		m_unk0x20[m_unk0x34] = m_unk0x0c->CreateMaterialList();
		::strncpy(name, p_item->m_materialNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_unk0x20[m_unk0x34]->VTable0x24(m_unk0x10, name, m_unk0x38);

		m_unk0x24[m_unk0x34] = m_unk0x0c->VTable0x18();
		::strncpy(name, p_item->m_nodeNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_unk0x24[m_unk0x34]->VTable0x14(name, m_unk0x38);

		::strncpy(name, p_item->m_modelPartNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_unk0x28[m_unk0x34].VTable0x14(name, m_unk0x38);

		m_unk0x18[m_unk0x34] = m_unk0x0c->VTable0x14();
		::strncpy(name, p_item->m_modelNames[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_unk0x18[m_unk0x34]->VTable0x1c(m_unk0x10, name, m_unk0x38);

		m_unk0x2c[m_unk0x34]
			.FUN_0040d550(m_unk0x18[m_unk0x34], m_unk0x24[m_unk0x34], &m_unk0x28[m_unk0x34], g_unk0x004afe6c);
	}

	m_unk0x34++;
	return m_unk0x34;
}

// FUNCTION: LEGORACERS 0x0041e570
void AquamarineSpirit0x3c::FUN_0041e570()
{
	for (LegoU32 i = 0; i < m_unk0x30; i++) {
		OpalHaven0xf4* primary;
		OpalHaven0xf4* secondary;
		FUN_0041e360(&m_unk0x14[i], &primary, &secondary);
	}
}

// FUNCTION: LEGORACERS 0x0041e5b0
OpalHaven0xf4* AquamarineSpirit0x3c::FUN_0041e5b0(const LegoChar* p_name)
{
	if (*p_name) {
		Item0x104* item = static_cast<Item0x104*>(GetName(p_name));
		if (item != NULL) {
			return item->m_primaryModel;
		}
	}

	return NULL;
}
