#include "aquamarinespirit0x3c.h"

#include "gol.h"
#include "golbinparser.h"
#include "golerror.h"
#include "opalhaven0xf4.h"

DECOMP_SIZE_ASSERT(AquamarineSpirit0x3c, 0x3c)
DECOMP_SIZE_ASSERT(AquamarineSpirit0x3c::Item0x104, 0x104)

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
	m_unk0x10 = 0;
	m_unk0x14 = 0;
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
			m_unk0x0c->VTable0x44(m_unk0x20[i]);
			m_unk0x20[i] = NULL;
		}
		delete[] m_unk0x20;
		m_unk0x20 = NULL;
	}

	if (m_unk0x1c != NULL) {
		for (LegoU32 i = 0; i < m_unk0x34; i++) {
			m_unk0x0c->VTable0x40(m_unk0x1c[i]);
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
	// TODO
	STUB(0x0041db10);
	// TODO: Replace this with the real array allocation at 0x0041e0b2 and construction at 0x0041e0de.
	// Keep the expression visible here so MSVC emits CmbModelPart0x34's vector deleting destructor.
	if (p_params == NULL) {
		CmbModelPart0x34* parts = new CmbModelPart0x34[1];
		delete[] parts;
		return;
	}
#if 0
	if (m_unk0x14 != NULL) {
		VTable0x08();
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
	} else {
		parser = new CmbTxtParser;
	}
	parser->VTable0x38(p_params->m_filename);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	LegoU32 count = parser->ReadBracketedCountAndLeftCurly();
	if (count != 0) {
		m_unk0x14 = new Item0x104[count];
		if (m_unk0x14 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		VTable0x04(count);
	}
	if (p_params->m_unk0x08 != -1) {
		m_unk0x30 = p_params->m_unk0x08;
	} else {
		m_unk0x30 = count;
	}
	::memset(m_unk0x14, 0, count * sizeof(Item0x104));
	for (LegoU32 i = 0; i < count; i++) {
		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		LegoChar name[8];
		::strncpy(name, parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		parser->ReadLeftCurly();
		m_unk0x14->m_unk0x100[0] = '2';
		m_unk0x14->m_unk0x100[1] = 'P';
		m_unk0x14->m_unk0x100[2] = '2';
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
				m_unk0x14[i].m_unk0xb8[0] = parser->ReadFloat();
				m_unk0x14[i].m_unk0xb8[1] = parser->ReadFloat();
				m_unk0x14[i].m_unk0xb8[2] = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2b:
				m_unk0x14[i].m_unk0xc4[0] = parser->ReadFloat();
				m_unk0x14[i].m_unk0xc4[1] = parser->ReadFloat();
				m_unk0x14[i].m_unk0xc4[2] = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2c:
				m_unk0x14[i].m_unk0xd0 = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2d:
				m_unk0x14[i].m_unk0xd4[0] = parser->ReadFloat();
				m_unk0x14[i].m_unk0xd4[1] = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2e:
				m_unk0x14[i].m_unk0xdc[0] = parser->ReadFloat();
				m_unk0x14[i].m_unk0xdc[1] = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x2f:
				m_unk0x14[i].m_unk0xec = parser->ReadFloat();
				break;
			case GolFileParser::e_unknown0x30:
				parser->ReadLeftCurly();
				m_unk0x14[i].m_unk0xe4[0] = parser->ReadFloat();
				m_unk0x14[i].m_unk0xe4[1] = parser->ReadFloat();
				for (LegoS32 j = 0; j < 4; j++) {
					m_unk0x14[i].m_unk0x58[j][0] = parser->ReadFloat();
					m_unk0x14[i].m_unk0x58[j][1] = parser->ReadFloat();
					m_unk0x14[i].m_unk0x58[j][2] = parser->ReadFloat();
				}
				parser->ReadRightCurly();
				break;
			case GolFileParser::e_unknown0x31:
				parser->ReadLeftCurly();
				for (LegoS32 j = 0; j < 4; j++) {
					m_unk0x14[i].m_unk0x88[j][0] = parser->ReadFloat();
					m_unk0x14[i].m_unk0x88[j][1] = parser->ReadFloat();
					m_unk0x14[i].m_unk0x88[j][2] = parser->ReadFloat();
				}
				parser->ReadRightCurly();
				break;
			case GolFileParser::e_unknown0x32:
				m_unk0x14[i].m_unk0xdc = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x33:
				m_unk0x14[i].m_unk0xf4 = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			case GolFileParser::e_unknown0x39:
				::strncpy(m_unk0x14[i].m_unk0x50, parser->ReadStringWithMaxLength(sizeof(m_unk0x14[i].m_unk0x50)), sizeof(m_unk0x14[i].m_unk0x50));
				break;
			case GolFileParser::e_unknown0x3a:
				m_unk0x14[i].m_unk0x100 = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x3b:
				m_unk0x14[i].m_unk0x102 = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x3c:
				m_unk0x14[i].m_unk0x101 = parser->ReadInteger();
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
	} else {
		m_unk0x2c = new OpalHaven0xf4[2*m_unk0x30];
		if (m_unk0x2c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x18 = new undefined4*[2 * m_unk0x30];
		if (m_unk0x18 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x1c = new MagentaRibbon0x20*[2 * m_unk0x30];
		// BUG: should check m_unk0x1c
		if (m_unk0x18 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x20 = new AmberHaze0x1c*[2 * m_unk0x30];
		// BUG: should check m_unk0x20
		if (m_unk0x18 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x24 = new undefined4*[2 * m_unk0x30];
		if (m_unk0x24 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		m_unk0x28 = new Item0x34[2 * m_unk0x30];
		if (m_unk0x28 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		for (LegoS32 i = 0; i < 2 * m_unk0x30; i++) {
			m_unk0x18[i] = NULL;
			m_unk0x1c[i] = NULL;
			m_unk0x20[i] = NULL;
		}
		m_unk0x34 = 0;
	}
#endif
}
