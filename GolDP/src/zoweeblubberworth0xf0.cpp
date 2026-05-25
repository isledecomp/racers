#include "zoweeblubberworth0xf0.h"

#include "amberlensbase0x120.h"
#include "boundingshape0x2c.h"
#include "boundingvolume0x64.h"
#include "cmbmodelpart0x34.h"
#include "floatycanoe0x90.h"
#include "floatyferry0xf4.h"
#include "floatyfrigate0x9c.h"
#include "floatykajak0x64.h"
#include "floatypontoon0x4c.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmath.h"
#include "igdbmodel0x40.h"
#include "jadeorbit0xd0.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "rectangle.h"
#include "shadowwolf0xc.h"
#include "whitefalconnode0x18.h"

#include <float.h>

DECOMP_SIZE_ASSERT(ZoweeBlubberworth0xf0, 0xf0)
DECOMP_SIZE_ASSERT(WdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(WdbModel0x8c, 0x8c)
DECOMP_SIZE_ASSERT(WdbCamera0x4c, 0x4c)
DECOMP_SIZE_ASSERT(WdbLight0x10, 0x10)

// GLOBAL: GOLDP 0x100576e4
LegoFloat g_fltMax0x100576e4 = FLT_MAX;

static const LegoFloat g_floatyBoatMaxFloat = FLT_MAX;

// GLOBAL: GOLDP 0x100576e8
LegoFloat g_fltMax0x100576e8 = FLT_MAX;

// GLOBAL: GOLDP 0x1005cf0c
undefined4 g_unk0x1005cf0c = 1;

// FUNCTION: GOLDP 0x1002baf0
void FUN_1002baf0(undefined4 p_arg)
{
	g_unk0x1005cf0c = p_arg;
}

// FUNCTION: GOLDP 0x1002c030
ZoweeBlubberworth0xf0::ZoweeBlubberworth0xf0()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002c0e0
void ZoweeBlubberworth0xf0::Reset()
{
	m_unk0x94 = 1.0f;
	m_unk0x04 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
	m_unk0x20 = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_unk0x30 = NULL;
	m_unk0x34 = 0;
	m_unk0x38 = NULL;
	m_unk0x3c = 0;
	m_unk0x40 = NULL;
	m_unk0x44 = 0;
	m_unk0x48 = NULL;
	m_unk0x4c = 0;
	m_unk0x50 = NULL;
	m_unk0x54 = 0;
	m_unk0x58 = NULL;
	m_unk0x5c = 0;
	m_unk0x60 = NULL;
	m_unk0x64 = 0;
	m_unk0x68 = NULL;
	m_unk0x6c = 0;
	m_unk0x70 = NULL;
	m_unk0x74 = 0;
	m_unk0x78 = NULL;
	m_unk0x7c = 0;
	m_unk0x80 = NULL;
	m_unk0x84 = 0;
	m_unk0x88 = NULL;
	m_unk0x8c = 0;
	m_unk0x90 = NULL;
	m_binary = FALSE;
	m_unk0x98 = 0;
	m_unk0x9c = 0;
	m_unk0xa0 = 0;
	m_unk0xa4 = NULL;
	m_unk0xa8 = 0;
	m_unk0xac = 0;
	m_unk0xb0 = 0;
}

// FUNCTION: GOLDP 0x1002c1a0
ZoweeBlubberworth0xf0::~ZoweeBlubberworth0xf0()
{
	VTable0x18();
}

// FUNCTION: GOLDP 0x1002c240
void ZoweeBlubberworth0xf0::VTable0x14(
	WhiteFalcon0x140* p_arg1,
	const LegoChar* p_name,
	LegoBool32 p_binary,
	LegoFloat p_arg4
)
{
	if (m_unk0x04) {
		VTable0x18();
	}

	m_unk0x04 = p_arg1;
	m_unk0x94 = p_arg4;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".wdb");
	}
	else {
		parser = new WdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	m_binary = p_binary;

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			FUN_1002c7b0(*parser);
			break;
		case GolFileParser::e_unknown0x28:
			FUN_1002c840(*parser);
			break;
		case GolFileParser::e_unknown0x29:
			FUN_1002c8d0(*parser);
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_1002c960(*parser);
			break;
		case GolFileParser::e_unknown0x2b:
			FUN_1002c9f0(*parser);
			break;
		case GolFileParser::e_unknown0x2c:
			FUN_1002ca80(*parser);
			break;
		case GolFileParser::e_unknown0x2d:
			FUN_1002cb10(*parser);
			break;
		case GolFileParser::e_unknown0x40:
			FUN_1002cba0(*parser);
			break;
		case GolFileParser::e_unknown0x2e:
			FUN_1002cc30(*parser);
			break;
		case GolFileParser::e_unknown0x2f:
			FUN_1002cfa0(*parser);
			break;
		case GolFileParser::e_unknown0x30:
			FUN_1002d400(*parser);
			break;
		case GolFileParser::e_unknown0x41:
			FUN_1002d720(*parser);
			break;
		case GolFileParser::e_unknown0x37:
			FUN_1002d950(*parser);
			break;
		case GolFileParser::e_unknown0x3d:
			FUN_1002db50(*parser);
			break;
		case GolFileParser::e_unknown0x43:
			FUN_1002dc80(*parser);
			break;
		case GolFileParser::e_unknown0x48:
			FUN_1002df90(*parser);
			break;
		case GolFileParser::e_unknown0x49:
			FUN_1002e0d0(*parser);
			break;
		}
	}

	parser->Dispose();
	VTable0x08();
	VTable0x04();
	VTable0x0c();
	FUN_1002e640();

	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x1002c4d0
void ZoweeBlubberworth0xf0::VTable0x00()
{
	if (m_unk0x90 != NULL) {
		delete[] m_unk0x90;
		m_unk0x90 = NULL;
	}

	if (m_unk0x88 != NULL) {
		delete[] m_unk0x88;
		m_unk0x88 = NULL;
	}

	if (m_unk0x80 != NULL) {
		delete[] m_unk0x80;
		m_unk0x80 = NULL;
	}

	if (m_unk0x70 != NULL) {
		delete[] m_unk0x70;
		m_unk0x70 = NULL;
	}

	if (m_unk0x68 != NULL) {
		delete[] m_unk0x68;
		m_unk0x68 = NULL;
	}

	if (m_unk0x60 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x5c; i++) {
			if (m_unk0x60[i].m_unk0x78 != NULL) {
				delete[] m_unk0x60[i].m_unk0x78;
			}
		}

		delete[] m_unk0x60;
		m_unk0x60 = NULL;
	}

	if (m_unk0x58 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x54; i++) {
			if (m_unk0x58[i].m_unk0x78 != NULL) {
				delete[] m_unk0x58[i].m_unk0x78;
			}
		}

		delete[] m_unk0x58;
		m_unk0x58 = NULL;
	}

	if (m_unk0x50 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x4c; i++) {
			if (m_unk0x50[i].m_unk0x78 != NULL) {
				delete[] m_unk0x50[i].m_unk0x78;
			}
		}

		delete[] m_unk0x50;
		m_unk0x50 = NULL;
	}

	if (m_unk0x40 != NULL) {
		delete[] m_unk0x40;
		m_unk0x40 = NULL;
	}

	if (m_unk0x48 != NULL) {
		delete[] m_unk0x48;
		m_unk0x48 = NULL;
	}

	if (m_unk0x38 != NULL) {
		delete[] m_unk0x38;
		m_unk0x38 = NULL;
	}

	if (m_unk0x30 != NULL) {
		delete[] m_unk0x30;
		m_unk0x30 = NULL;
	}

	if (m_unk0x28 != NULL) {
		delete[] m_unk0x28;
		m_unk0x28 = NULL;
	}

	if (m_unk0x20 != NULL) {
		delete[] m_unk0x20;
		m_unk0x20 = NULL;
	}

	if (m_unk0x18 != NULL) {
		delete[] m_unk0x18;
		m_unk0x18 = NULL;
	}

	if (m_unk0x10 != NULL) {
		delete[] m_unk0x10;
		m_unk0x10 = NULL;
	}
}

// FUNCTION: GOLDP 0x1002c6b0
void ZoweeBlubberworth0xf0::VTable0x18()
{
	VTable0x00();

	if (m_unk0x78 != NULL) {
		delete[] m_unk0x78;
		m_unk0x78 = NULL;
	}

	m_unk0xe4.Clear();
	m_unk0xb4.Clear();
	m_unk0xc0.Clear();
	m_unk0xcc.Clear();
	m_unk0xd8.Clear();

	if (m_unk0xa8 != NULL) {
		delete[] m_unk0xa8;
	}

	if (m_unk0xa4 != NULL) {
		delete[] m_unk0xa4;
	}

	if (m_unk0xa0 != NULL) {
		delete[] m_unk0xa0;
	}

	if (m_unk0x9c != NULL) {
		delete[] m_unk0x9c;
	}

	if (m_unk0x98 != NULL) {
		delete[] m_unk0x98;
	}

	if (m_unk0xac != NULL) {
		delete[] m_unk0xac;
	}

	if (m_unk0xb0 != NULL) {
		delete[] m_unk0xb0;
	}

	Reset();
}

// FUNCTION: GOLDP 0x1002c7b0
void ZoweeBlubberworth0xf0::FUN_1002c7b0(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x10 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x0c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x0c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x10 = new GolName[m_unk0x0c];
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x0c; i++) {
		::strncpy(m_unk0x10[i], p_parser.ReadString(), sizeOfArray(m_unk0x10[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002c840
void ZoweeBlubberworth0xf0::FUN_1002c840(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x18 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x14 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x14 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x18 = new GolName[m_unk0x14];
	if (m_unk0x18 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x14; i++) {
		::strncpy(m_unk0x18[i], p_parser.ReadString(), sizeOfArray(m_unk0x18[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002c8d0
void ZoweeBlubberworth0xf0::FUN_1002c8d0(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x20 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x1c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x1c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x20 = new GolName[m_unk0x1c];
	if (m_unk0x20 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x1c; i++) {
		::strncpy(m_unk0x20[i], p_parser.ReadString(), sizeOfArray(m_unk0x20[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002c960
void ZoweeBlubberworth0xf0::FUN_1002c960(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x28 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x24 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x24 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x28 = new GolName[m_unk0x24];
	if (m_unk0x28 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x24; i++) {
		::strncpy(m_unk0x28[i], p_parser.ReadString(), sizeOfArray(m_unk0x28[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002c9f0
void ZoweeBlubberworth0xf0::FUN_1002c9f0(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x30 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x2c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x2c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x30 = new GolName[m_unk0x2c];
	if (m_unk0x30 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x2c; i++) {
		::strncpy(m_unk0x30[i], p_parser.ReadString(), sizeOfArray(m_unk0x30[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002ca80
void ZoweeBlubberworth0xf0::FUN_1002ca80(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x38 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x34 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x34 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x38 = new GolName[m_unk0x34];
	if (m_unk0x38 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x34; i++) {
		::strncpy(m_unk0x38[i], p_parser.ReadString(), sizeOfArray(m_unk0x38[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002cb10
void ZoweeBlubberworth0xf0::FUN_1002cb10(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x40 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x3c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x3c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x40 = new GolName[m_unk0x3c];
	if (m_unk0x40 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x3c; i++) {
		::strncpy(m_unk0x40[i], p_parser.ReadString(), sizeOfArray(m_unk0x40[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002cba0
void ZoweeBlubberworth0xf0::FUN_1002cba0(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x48 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x44 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x44 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x48 = new GolName[m_unk0x44];
	if (m_unk0x48 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x44; i++) {
		::strncpy(m_unk0x48[i], p_parser.ReadString(), sizeOfArray(m_unk0x48[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002cc30
void ZoweeBlubberworth0xf0::FUN_1002cc30(GolFileParser& p_parser)
{
	LegoU32 i;
	LegoS32 v;

	if (m_unk0x50 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x4c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x4c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x50 = new WdbModel0x8c[m_unk0x4c];
	if (m_unk0x50 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x50, 0, sizeof(*m_unk0x50) * m_unk0x4c);
	WdbModel0x8c* item = m_unk0x50;
	for (i = 0; i < m_unk0x4c; item++, i++) {
		LegoU32 cnt = 0;
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x2e);
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetUnk0x30(1);
			item->m_unk0x00[0] = '\0';
		}
		else {
			::strncpy(item->m_unk0x00, p_parser.GetLastString(), sizeof(item->m_unk0x00));
		}
		p_parser.ReadLeftCurly();
		LegoU32 j;
		for (j = 0; j < 3; j++) {
			item->m_unk0x08[j] = -1;
			item->m_unk0x2c[j] = -1;
		}
		item->m_unk0x5c.m_x = 1.0f;
		item->m_unk0x68.m_z = 1.0f;
		item->m_unk0x74 = 1.0f;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x2a:
				if (p_parser.GetNextToken() != GolFileParser::e_int) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_int);
				}
				if (static_cast<LegoU32>(p_parser.GetLastInt()) >= m_unk0x24 && m_unk0x24 != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x08[cnt] = p_parser.GetLastInt();
				if (p_parser.GetNextToken() != GolFileParser::e_float) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_float);
				}
				if (p_parser.GetLastFloat() < 0.0f) {
					item->m_unk0x38[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_unk0x38[cnt] = p_parser.GetLastFloat();
				}
				cnt++;
				break;
			case GolFileParser::e_unknown0x31:
				item->m_unk0x50.m_x = p_parser.ReadFloat();
				item->m_unk0x50.m_y = p_parser.ReadFloat();
				item->m_unk0x50.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x32:
				item->m_unk0x5c.m_x = p_parser.ReadFloat();
				item->m_unk0x5c.m_y = p_parser.ReadFloat();
				item->m_unk0x5c.m_z = p_parser.ReadFloat();
				item->m_unk0x68.m_x = p_parser.ReadFloat();
				item->m_unk0x68.m_y = p_parser.ReadFloat();
				item->m_unk0x68.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x2b:
				if (p_parser.GetNextToken() != GolFileParser::e_int) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_int);
				}
				if (static_cast<LegoU32>(p_parser.GetLastInt()) >= m_unk0x2c && m_unk0x2c != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				v = p_parser.GetLastInt();
				if (p_parser.GetNextToken() != GolFileParser::e_int) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_int);
				}
				if (p_parser.GetLastInt() >= static_cast<LegoS32>(sizeOfArray(item->m_unk0x2c))) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x2c[p_parser.GetLastInt()] = v;
				break;
			case GolFileParser::e_unknown0x36:
				item->m_unk0x74 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x3e:
				FUN_1002dbe0(p_parser, &item->m_unk0x78, &item->m_unk0x7c);
				break;
			case GolFileParser::e_unknown0x3f:
				item->m_flags |= WdbModel0x8c::e_flagBit3;
				item->m_unk0x80 = p_parser.ReadFloat();
				item->m_unk0x84 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x42:
				item->m_flags |= WdbModel0x8c::e_flagBit1;
				break;
			case GolFileParser::e_unknown0x4c:
				item->m_flags |= WdbModel0x8c::e_flagBit2;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002cfa0
void ZoweeBlubberworth0xf0::FUN_1002cfa0(GolFileParser& p_parser)
{
	LegoU32 i;
	LegoS32 v;

	if (m_unk0x58 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x54 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x54 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x58 = new WdbModel0x8c[m_unk0x54];
	if (m_unk0x58 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x58, 0, sizeof(*m_unk0x58) * m_unk0x54);
	WdbModel0x8c* item = m_unk0x58;
	for (i = 0; i < m_unk0x54; item++, i++) {
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x2f);
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetUnk0x30(1);
			item->m_unk0x00[0] = '\0';
		}
		else {
			::strncpy(item->m_unk0x00, p_parser.GetLastString(), sizeof(item->m_unk0x00));
		}
		p_parser.ReadLeftCurly();
		LegoU32 cnt = 0;
		for (cnt = 0; cnt < 3; cnt++) {
			item->m_unk0x08[cnt] = -1;
			item->m_unk0x14[cnt] = -1;
			item->m_unk0x2c[cnt] = -1;
		}
		cnt = 0;
		item->m_unk0x44 = -1;
		item->m_unk0x5c.m_x = 1.0f;
		item->m_unk0x68.m_z = 1.0f;
		item->m_unk0x74 = 1.0f;
		item->m_unk0x48[0] = '\0';
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x33:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x24 && m_unk0x24 != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x08[cnt] = p_parser.GetLastInt();
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x34 && m_unk0x34 != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x14[cnt] = p_parser.GetLastInt();
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x1c && m_unk0x1c != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x20[cnt] = p_parser.GetLastInt();
				if (p_parser.ReadFloat() < 0.0f) {
					item->m_unk0x38[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_unk0x38[cnt] = p_parser.GetLastFloat();
				}
				cnt += 1;
				break;
			case GolFileParser::e_unknown0x2c:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x34 && m_unk0x34 != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x14[cnt] = p_parser.GetLastInt();
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x1c && m_unk0x1c != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x20[cnt] = p_parser.GetLastInt();
				if (p_parser.ReadFloat() < 0.0f) {
					item->m_unk0x38[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_unk0x38[cnt] = p_parser.GetLastFloat();
				}
				cnt += 1;
				break;
			case GolFileParser::e_unknown0x31:
				item->m_unk0x50.m_x = p_parser.ReadFloat();
				item->m_unk0x50.m_y = p_parser.ReadFloat();
				item->m_unk0x50.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x32:
				item->m_unk0x5c.m_x = p_parser.ReadFloat();
				item->m_unk0x5c.m_y = p_parser.ReadFloat();
				item->m_unk0x5c.m_z = p_parser.ReadFloat();
				item->m_unk0x68.m_x = p_parser.ReadFloat();
				item->m_unk0x68.m_y = p_parser.ReadFloat();
				item->m_unk0x68.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x2b:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x2c && m_unk0x2c != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				v = p_parser.GetLastInt();
				if (p_parser.ReadInteger() >= static_cast<LegoS32>(sizeOfArray(item->m_unk0x2c))) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x2c[p_parser.GetLastInt()] = v;
				break;
			case GolFileParser::e_unknown0x35:
				token = p_parser.GetNextToken();
				if (token == GolFileParser::e_string) {
					item->m_unk0x44 = -1;
					::strncpy(item->m_unk0x48, p_parser.GetLastString(), sizeof(item->m_unk0x48));
				}
				else {
					if (token != GolFileParser::e_int) {
						p_parser.HandleUnexpectedToken(GolFileParser::e_int);
					}
					item->m_unk0x44 = p_parser.GetLastInt();
					item->m_unk0x48[0] = '\0';
				}
				break;
			case GolFileParser::e_unknown0x36:
				item->m_unk0x74 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x3e:
				FUN_1002dbe0(p_parser, &item->m_unk0x78, &item->m_unk0x7c);
				break;
			case GolFileParser::e_unknown0x3f:
				item->m_flags |= WdbModel0x8c::e_flagBit3;
				item->m_unk0x80 = p_parser.ReadFloat();
				item->m_unk0x84 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x42:
				item->m_flags |= WdbModel0x8c::e_flagBit1;
				break;
			case GolFileParser::e_unknown0x4c:
				item->m_flags |= WdbModel0x8c::e_flagBit2;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002d400
void ZoweeBlubberworth0xf0::FUN_1002d400(GolFileParser& p_parser)
{
	LegoU32 i;
	LegoS32 v;

	if (m_unk0x60 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x5c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x5c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x60 = new WdbModel0x8c[m_unk0x5c];
	if (m_unk0x60 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x60, 0, sizeof(*m_unk0x60) * m_unk0x5c);
	WdbModel0x8c* item = m_unk0x60;
	for (i = 0; i < m_unk0x5c; item++, i++) {
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x30);
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetUnk0x30(1);
			item->m_unk0x00[0] = '\0';
		}
		else {
			::strncpy(item->m_unk0x00, p_parser.GetLastString(), sizeof(item->m_unk0x00));
		}
		p_parser.ReadLeftCurly();
		LegoU32 cnt = 0;
		for (cnt = 0; cnt < 3; cnt++) {
			item->m_unk0x08[cnt] = -1;
			item->m_unk0x2c[cnt] = -1;
		}
		cnt = 0;
		item->m_unk0x5c.m_x = 1.0f;
		item->m_unk0x68.m_z = 1.0f;
		item->m_unk0x74 = 1.0f;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x34:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x24 && m_unk0x24 != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x08[cnt] = p_parser.GetLastInt();
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x3c && m_unk0x3c != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x14[cnt] = p_parser.GetLastInt();
				if (p_parser.ReadFloat() < 0.0f) {
					item->m_unk0x38[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_unk0x38[cnt] = p_parser.GetLastFloat();
				}
				cnt += 1;
				break;
			case GolFileParser::e_unknown0x31:
				item->m_unk0x50.m_x = p_parser.ReadFloat();
				item->m_unk0x50.m_y = p_parser.ReadFloat();
				item->m_unk0x50.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x32:
				item->m_unk0x5c.m_x = p_parser.ReadFloat();
				item->m_unk0x5c.m_y = p_parser.ReadFloat();
				item->m_unk0x5c.m_z = p_parser.ReadFloat();
				item->m_unk0x68.m_x = p_parser.ReadFloat();
				item->m_unk0x68.m_y = p_parser.ReadFloat();
				item->m_unk0x68.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x2b:
				if (static_cast<LegoU32>(p_parser.ReadInteger()) >= m_unk0x2c && m_unk0x2c != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				v = p_parser.GetLastInt();
				if (p_parser.ReadInteger() >= static_cast<LegoS32>(sizeOfArray(item->m_unk0x2c))) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x2c[p_parser.GetLastInt()] = v;
				break;
			case GolFileParser::e_unknown0x3e:
				FUN_1002dbe0(p_parser, &item->m_unk0x78, &item->m_unk0x7c);
				break;
			case GolFileParser::e_unknown0x3f:
				item->m_flags |= WdbModel0x8c::e_flagBit3;
				item->m_unk0x80 = p_parser.ReadFloat();
				item->m_unk0x84 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x42:
				item->m_flags |= WdbModel0x8c::e_flagBit1;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002d720
void ZoweeBlubberworth0xf0::FUN_1002d720(GolFileParser& p_parser)
{
	LegoU32 i;
	LegoS32 v;

	if (m_unk0x68 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x64 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x64 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x68 = new WdbModel0x8c[m_unk0x64];
	if (m_unk0x68 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x68, 0, sizeof(*m_unk0x68) * m_unk0x64);
	WdbModel0x8c* item = m_unk0x68;
	for (i = 0; i < m_unk0x64; item++, i++) {
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x41);
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetUnk0x30(1);
			item->m_unk0x00[0] = '\0';
		}
		else {
			::strncpy(item->m_unk0x00, p_parser.GetLastString(), sizeof(item->m_unk0x00));
		}
		p_parser.ReadLeftCurly();
		item->m_unk0x2c[0] = -1;
		item->m_unk0x5c.m_x = 1.0f;
		item->m_unk0x68.m_z = 1.0f;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x40:
				item->m_unk0x14[0] = v = p_parser.ReadInteger();
				if (static_cast<LegoU32>(v) >= m_unk0x44 && m_unk0x44 != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				break;
			case GolFileParser::e_unknown0x31:
				item->m_unk0x50.m_x = p_parser.ReadFloat();
				item->m_unk0x50.m_y = p_parser.ReadFloat();
				item->m_unk0x50.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x32:
				item->m_unk0x5c.m_x = p_parser.ReadFloat();
				item->m_unk0x5c.m_y = p_parser.ReadFloat();
				item->m_unk0x5c.m_z = p_parser.ReadFloat();
				item->m_unk0x68.m_x = p_parser.ReadFloat();
				item->m_unk0x68.m_y = p_parser.ReadFloat();
				item->m_unk0x68.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x2b:
				v = p_parser.ReadInteger();
				if (static_cast<LegoU32>(v) >= m_unk0x2c && m_unk0x2c != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x2c[0] = v;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002d950
void ZoweeBlubberworth0xf0::FUN_1002d950(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x70 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x6c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x6c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x70 = new WdbBillboardSprite0x38[m_unk0x6c];
	if (m_unk0x70 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x70, 0, sizeof(*m_unk0x70) * m_unk0x6c);
	WdbBillboardSprite0x38* item = m_unk0x70;
	for (i = 0; i < m_unk0x6c; item++, i++) {
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x37);
		p_parser.ReadLeftCurly();
		item->m_unk0x28 = g_fltMax0x100576e8;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x2b:
				item->m_flags |= WdbBillboardSprite0x38::c_flagBit2;
				item->m_unk0x34 = p_parser.ReadInteger();
				item->m_unk0x36 = p_parser.ReadInteger();
				break;
			case GolFileParser::e_unknown0x31:
				item->m_unk0x08.m_x = p_parser.ReadFloat();
				item->m_unk0x08.m_y = p_parser.ReadFloat();
				item->m_unk0x08.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x38:
				item->m_flags |= WdbBillboardSprite0x38::c_flagBit1;
				item->m_unk0x14.m_x = p_parser.ReadFloat();
				item->m_unk0x14.m_y = p_parser.ReadFloat();
				item->m_unk0x14.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x39:
				::strncpy(item->m_unk0x00, p_parser.ReadString(), sizeof(item->m_unk0x00));
				break;
			case GolFileParser::e_unknown0x3a:
				item->m_unk0x20 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x3b:
				item->m_unk0x24 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x3c:
				item->m_unk0x28 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x3e:
				item->m_unk0x32 = 1;
				item->m_unk0x2e = p_parser.ReadInteger();
				item->m_unk0x30 = p_parser.ReadInteger();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002db50
void ZoweeBlubberworth0xf0::FUN_1002db50(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x78 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x74 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x74 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x78 = new GolName[m_unk0x74];
	if (m_unk0x78 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x74; i++) {
		::strncpy(m_unk0x78[i], p_parser.ReadString(), sizeOfArray(m_unk0x78[i]));
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002dbe0
void ZoweeBlubberworth0xf0::FUN_1002dbe0(GolFileParser& p_parser, Rect** p_rects, LegoU32* p_count)
{
	LegoU32 i;
	LegoU32 count;
	Rect* rects;

	if (*p_rects != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	*p_count = count = p_parser.ReadBracketedCountAndLeftCurly();
	if (count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	*p_rects = rects = new Rect[count];
	if (rects == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	Rect* item = rects;
	for (i = 0; i < count; item++, i++) {
		item->m_left = p_parser.ReadInteger();
		item->m_top = p_parser.ReadInteger();
		item->m_right = p_parser.ReadInteger();
		item->m_bottom = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002dc80
void ZoweeBlubberworth0xf0::FUN_1002dc80(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x80 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x7c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x7c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x80 = new WdbCamera0x4c[m_unk0x7c];
	if (m_unk0x80 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	GolVec3 pos;
	pos.m_x = 0.0f;
	pos.m_y = 0.0f;
	pos.m_z = 0.0f;
	::memset(m_unk0x80, 0, sizeof(*m_unk0x80) * m_unk0x7c);
	WdbCamera0x4c* item = m_unk0x80;
	for (i = 0; i < m_unk0x7c; item++, i++) {
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x43);
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetUnk0x30(1);
			item->m_unk0x00[0] = '\0';
		}
		else {
			::strncpy(item->m_unk0x00, p_parser.GetLastString(), sizeof(item->m_unk0x00));
		}
		p_parser.ReadLeftCurly();
		item->m_unk0x08 = -1;
		item->m_unk0x28.m_x = 1.0f;
		item->m_unk0x34.m_z = -1.0f;
		item->m_unk0x40 = 1.0f;
		item->m_unk0x44 = 100.0f;
		item->m_unk0x48 = 65.0f;
		LegoBool32 seen = FALSE;
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x2f:
				item->m_unk0x08 = p_parser.ReadInteger();
				if (static_cast<LegoU32>(item->m_unk0x08) >= m_unk0x54 && m_unk0x54 != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x0c = p_parser.ReadInteger();
				break;
			case GolFileParser::e_unknown0x35:
				token = p_parser.GetNextToken();
				if (token == GolFileParser::e_string) {
					item->m_unk0x10 = -1;
					::strncpy(item->m_unk0x14, p_parser.GetLastString(), sizeof(item->m_unk0x14));
				}
				else {
					if (token != GolFileParser::e_int) {
						p_parser.HandleUnexpectedToken(GolFileParser::e_int);
					}
					item->m_unk0x10 = p_parser.GetLastInt();
					item->m_unk0x14[0] = '\0';
				}
				break;
			case GolFileParser::e_unknown0x31:
				item->m_unk0x1c.m_x = p_parser.ReadFloat();
				item->m_unk0x1c.m_y = p_parser.ReadFloat();
				item->m_unk0x1c.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x44:
				seen = TRUE;
				pos.m_x = p_parser.ReadFloat();
				pos.m_y = p_parser.ReadFloat();
				pos.m_z = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x32:
				item->m_unk0x28.m_x = p_parser.ReadFloat();
				item->m_unk0x28.m_y = p_parser.ReadFloat();
				item->m_unk0x28.m_z = p_parser.ReadFloat();
				item->m_unk0x34.m_x = -p_parser.ReadFloat();
				item->m_unk0x34.m_y = -p_parser.ReadFloat();
				item->m_unk0x34.m_z = -p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x45:
				item->m_unk0x40 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x46:
				item->m_unk0x44 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x47:
				item->m_unk0x48 = p_parser.ReadFloat();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
		if (seen) {
			item->m_unk0x28.m_x = pos.m_x - item->m_unk0x1c.m_x;
			item->m_unk0x28.m_y = pos.m_y - item->m_unk0x1c.m_y;
			item->m_unk0x28.m_z = pos.m_z - item->m_unk0x1c.m_z;
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002df90
void ZoweeBlubberworth0xf0::FUN_1002df90(GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_unk0x88 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x84 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x84 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x88 = new WdbLight0x10[m_unk0x84];
	if (m_unk0x88 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x88, 0, sizeof(*m_unk0x88) * m_unk0x84);
	for (i = 0; i < m_unk0x84; i++) {
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x48);
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetUnk0x30(1);
		}
		p_parser.ReadLeftCurly();
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x4a:
				m_unk0x88[i].m_color.m_red = p_parser.ReadInteger();
				m_unk0x88[i].m_color.m_grn = p_parser.ReadInteger();
				m_unk0x88[i].m_color.m_blu = p_parser.ReadInteger();
				m_unk0x88[i].m_color.m_alp = 0xff;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002e0d0
void ZoweeBlubberworth0xf0::FUN_1002e0d0(GolFileParser& p_parser)
{
	LegoU32 i;
	if (m_unk0x90 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}
	m_unk0x8c = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x8c == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x90 = new WdbLight0x10[m_unk0x8c];
	if (m_unk0x90 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x90, 0, sizeof(*m_unk0x90) * m_unk0x8c);
	for (i = 0; i < m_unk0x8c; i++) {
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x49);
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetUnk0x30(1);
		}
		p_parser.ReadLeftCurly();
		GolFileParser::ParserTokenType token;
		while ((token = p_parser.GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x4a:
				m_unk0x90[i].m_color.m_red = p_parser.ReadInteger();
				m_unk0x90[i].m_color.m_grn = p_parser.ReadInteger();
				m_unk0x90[i].m_color.m_blu = p_parser.ReadInteger();
				m_unk0x90[i].m_color.m_alp = 0xff;
				break;
			case GolFileParser::e_unknown0x4b:
				m_unk0x90[i].m_unk0x04.m_x = p_parser.ReadFloat();
				m_unk0x90[i].m_unk0x04.m_y = p_parser.ReadFloat();
				m_unk0x90[i].m_unk0x04.m_z = p_parser.ReadFloat();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1002e250
void ZoweeBlubberworth0xf0::FUN_1002e250(FloatyPontoon0x4c* p_billboard, WdbBillboardSprite0x38* p_sprite)
{
	if (p_sprite->m_unk0x32 == 0) {
		return;
	}

	if (!(p_billboard->GetFlags() & FloatyPontoon0x4c::c_flagBit2)) {
		GOL_FATALERROR_MESSAGE("Mat animation invalid for sprites without mat assignment");
	}

	LegoU32 animationIndex = p_sprite->m_unk0x2e;
	if (animationIndex >= m_unk0x74) {
		return;
	}

	LegoU32 materialIndex = p_sprite->m_unk0x30;
	MabMaterialAnimationItem0x18* item = VTable0x4c(animationIndex)->GetUnk0x0c();
	item[materialIndex].FUN_10025da0(p_billboard->GetPositionContainer(), p_sprite->m_unk0x36, TRUE);
}

// FUNCTION: GOLDP 0x1002e2c0
void ZoweeBlubberworth0xf0::VTable0x04()
{
	if (m_unk0x44 != 0) {
		m_unk0x98 = new BoundingVolume0x64[m_unk0x44];
		if (m_unk0x98 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_unk0x4c != 0) {
		m_unk0x9c = new FloatyCanoe0x90[m_unk0x4c];
		if (m_unk0x9c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_unk0x54 != 0) {
		m_unk0xa0 = new FloatyFerry0xf4[m_unk0x54];
		if (m_unk0xa0 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_unk0x5c != 0) {
		m_unk0xa4 = new FloatyFrigate0x9c[m_unk0x5c];
		if (m_unk0xa4 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_unk0x64 != 0) {
		m_unk0xa8 = new FloatyKajak0x64[m_unk0x64];
		if (m_unk0xa8 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_unk0x84 != 0) {
		m_unk0xac = new WhiteFalcon0x140::MaterialColor[m_unk0x84];
		if (m_unk0xac == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (m_unk0x8c != 0) {
		m_unk0xb0 = new WhiteFalcon0x140::Light[m_unk0x8c];
		if (m_unk0xb0 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// STUB: GOLDP 0x1002e640
void ZoweeBlubberworth0xf0::FUN_1002e640()
{
	LegoU32 i;
	LegoU32 j;
	LegoU32 lod;
	LegoFloat maxDistances[3];

	for (i = 0; i < m_unk0x4c; i++) {
		WdbModel0x8c* model = &m_unk0x50[i];
		FloatyCanoe0x90* runtime = &m_unk0x9c[i];

		if (static_cast<LegoU32>(model->m_unk0x08[0]) >= m_unk0x24) {
			GOL_FATALERROR_MESSAGE("Illegal mesh reference");
		}

		for (lod = 0; lod < 3; lod++) {
			if (model->m_unk0x08[lod] < 0) {
				break;
			}

			if (!(model->m_unk0x38[lod] < g_floatyBoatMaxFloat)) {
				maxDistances[lod] = g_fltMax0x100576e4;
			}
			else {
				maxDistances[lod] = model->m_unk0x38[lod] * model->m_unk0x38[lod];
			}

			if (model->m_unk0x2c[lod] >= 0) {
				if (model->m_unk0x2c[lod] >= static_cast<LegoS32>(m_unk0x2c)) {
					GOL_FATALERROR_MESSAGE("Illegal alt mat assign ref val");
				}
				runtime->m_materialTables[lod] = VTable0x3c(model->m_unk0x2c[lod]);
			}
			else {
				runtime->m_materialTables[lod] = NULL;
			}
		}

		runtime->VTable0x50(VTable0x38(model->m_unk0x08[0]), maxDistances[0]);
		for (lod = 1; lod < 3; lod++) {
			if (model->m_unk0x08[lod] < 0) {
				break;
			}
			runtime->FUN_10027c50(VTable0x38(model->m_unk0x08[lod]), maxDistances[lod]);
		}

		runtime->VTable0x08(model->m_unk0x50);
		runtime->VTable0x40(model->m_unk0x5c, model->m_unk0x68);
		runtime->m_radius = -1.0f;
		runtime->m_unk0x58 = model->m_unk0x74;

		if (model->m_flags & WdbModel0x8c::e_flagBit3) {
			runtime->FUN_00411700(model->m_unk0x80);
			runtime->FUN_00411730(model->m_unk0x84);
		}
		if (model->m_flags & WdbModel0x8c::e_flagBit1) {
			runtime->m_flags |= FloatyCanoe0x90::c_flagBit1;
		}
		if (model->m_flags & WdbModel0x8c::e_flagBit2) {
			runtime->m_flags |= FloatyCanoe0x90::c_flagBit2;
		}

		for (j = 0; j < model->m_unk0x7c; j++) {
			Rect* assignment = &model->m_unk0x78[j];
			if (static_cast<LegoU32>(assignment->m_left) >= m_unk0x74) {
				continue;
			}

			MabMaterialAnimationItem0x18* item = VTable0x4c(assignment->m_left)->GetUnk0x0c();
			LegoU32 targetIndex = assignment->m_bottom;
			MaterialTable0x0c* target = runtime->m_materialTables[targetIndex];
			if (target == NULL) {
				target = runtime->m_models[targetIndex]->GetMaterialTable();
			}
			item[assignment->m_top].FUN_10025da0(target, assignment->m_right, TRUE);
		}

		if (model->m_unk0x00[0] != '\0') {
			if (m_unk0xb4.GetNameEntries() == NULL) {
				m_unk0xb4.Allocate(m_unk0x4c);
			}
			m_unk0xb4.AddName(model->m_unk0x00, runtime);
		}
	}

	for (i = 0; i < m_unk0x54; i++) {
		WdbModel0x8c* model = &m_unk0x58[i];
		FloatyFerry0xf4* runtime = &m_unk0xa0[i];

		if (model->m_unk0x08[0] >= 0 && static_cast<LegoU32>(model->m_unk0x08[0]) >= m_unk0x24) {
			GOL_FATALERROR_MESSAGE("Illegal mesh reference");
		}
		if (static_cast<LegoU32>(model->m_unk0x14[0]) >= m_unk0x34) {
			GOL_FATALERROR_MESSAGE("Illegal skeleton reference");
		}

		for (lod = 0; lod < 3; lod++) {
			if (model->m_unk0x14[lod] < 0) {
				break;
			}

			if (!(model->m_unk0x38[lod] < g_floatyBoatMaxFloat)) {
				maxDistances[lod] = g_fltMax0x100576e4;
			}
			else {
				maxDistances[lod] = model->m_unk0x38[lod] * model->m_unk0x38[lod];
			}

			if (model->m_unk0x2c[lod] >= 0) {
				if (model->m_unk0x2c[lod] >= static_cast<LegoS32>(m_unk0x2c)) {
					GOL_FATALERROR_MESSAGE("Illegal alt mat assign ref val");
				}
				runtime->m_materialTables[lod] = VTable0x3c(model->m_unk0x2c[lod]);
			}
			else {
				runtime->m_materialTables[lod] = NULL;
			}
		}

		WhiteFalconNode0x18* node = VTable0x40(model->m_unk0x14[0]);
		CmbModelPart0x34* part = VTable0x34(model->m_unk0x20[0]);
		CmbModelPart0x34* partForPartName = part;

		if (model->m_unk0x08[0] < 0) {
			runtime->FUN_100234c0(node, part, maxDistances[0]);
			for (lod = 1; lod < 3; lod++) {
				if (model->m_unk0x14[lod] < 0) {
					break;
				}

				node = VTable0x40(model->m_unk0x14[lod]);
				part = VTable0x34(model->m_unk0x20[lod]);
				partForPartName = part;
				runtime->FUN_100239e0(node, part, maxDistances[lod]);
			}
		}
		else {
			runtime->FUN_10023490(VTable0x38(model->m_unk0x08[0]), node, part, maxDistances[0]);
			for (lod = 1; lod < 3; lod++) {
				if (model->m_unk0x08[lod] < 0) {
					break;
				}

				node = VTable0x40(model->m_unk0x14[lod]);
				part = VTable0x34(model->m_unk0x20[lod]);
				partForPartName = part;
				runtime->FUN_10023940(VTable0x38(model->m_unk0x08[lod]), node, part, maxDistances[lod]);
			}
		}

		runtime->VTable0x08(model->m_unk0x50);
		runtime->VTable0x40(model->m_unk0x5c, model->m_unk0x68);
		runtime->m_radius = -1.0f;
		runtime->m_unk0x58 = model->m_unk0x74;

		if (model->m_flags & WdbModel0x8c::e_flagBit3) {
			runtime->FUN_00411700(model->m_unk0x80);
			runtime->FUN_00411730(model->m_unk0x84);
		}

		if (model->m_unk0x48[0] != '\0') {
			model->m_unk0x44 = partForPartName->GetPartIndex(model->m_unk0x48);
		}

		if (model->m_unk0x44 >= 0) {
			runtime->FUN_10023a70(model->m_unk0x44);
			runtime->SetPartAnimationEnabled(TRUE);
		}
		else {
			runtime->SetPartAnimationEnabled(FALSE);
		}

		if (model->m_flags & WdbModel0x8c::e_flagBit1) {
			runtime->m_flags |= FloatyCanoe0x90::c_flagBit1;
		}
		if (model->m_flags & WdbModel0x8c::e_flagBit2) {
			runtime->m_flags |= FloatyCanoe0x90::c_flagBit2;
		}

		for (j = 0; j < model->m_unk0x7c; j++) {
			Rect* assignment = &model->m_unk0x78[j];
			if (static_cast<LegoU32>(assignment->m_left) >= m_unk0x74) {
				continue;
			}

			MabMaterialAnimationItem0x18* item = VTable0x4c(assignment->m_left)->GetUnk0x0c();
			LegoU32 targetIndex = assignment->m_bottom;
			MaterialTable0x0c* target = runtime->m_materialTables[targetIndex];
			if (target == NULL) {
				target = runtime->m_models[targetIndex]->GetMaterialTable();
			}
			item[assignment->m_top].FUN_10025da0(target, assignment->m_right, TRUE);
		}

		if (model->m_unk0x00[0] != '\0') {
			if (m_unk0xc0.GetNameEntries() == NULL) {
				m_unk0xc0.Allocate(m_unk0x54);
			}
			m_unk0xc0.AddName(model->m_unk0x00, runtime);
		}
	}

	for (i = 0; i < m_unk0x5c; i++) {
		WdbModel0x8c* model = &m_unk0x60[i];
		FloatyFrigate0x9c* runtime = &m_unk0xa4[i];

		if (static_cast<LegoU32>(model->m_unk0x08[0]) >= m_unk0x24) {
			GOL_FATALERROR_MESSAGE("Illegal mesh reference");
		}
		if (static_cast<LegoU32>(model->m_unk0x14[0]) >= m_unk0x3c) {
			GOL_FATALERROR_MESSAGE("Illegal bsp tree reference");
		}

		for (lod = 0; lod < 3; lod++) {
			if (model->m_unk0x08[lod] < 0) {
				break;
			}

			if (!(model->m_unk0x38[lod] < g_floatyBoatMaxFloat)) {
				maxDistances[lod] = g_fltMax0x100576e4;
			}
			else {
				maxDistances[lod] = model->m_unk0x38[lod] * model->m_unk0x38[lod];
			}

			if (model->m_unk0x2c[lod] >= 0) {
				if (model->m_unk0x2c[lod] >= static_cast<LegoS32>(m_unk0x2c)) {
					GOL_FATALERROR_MESSAGE("Illegal alt mat assign ref val");
				}
				runtime->m_materialTables[lod] = VTable0x3c(model->m_unk0x2c[lod]);
			}
			else {
				runtime->m_materialTables[lod] = NULL;
			}
		}

		runtime->VTable0x60(VTable0x38(model->m_unk0x08[0]), VTable0x44(model->m_unk0x14[0]), maxDistances[0]);
		for (lod = 1; lod < 3; lod++) {
			if (model->m_unk0x08[lod] < 0) {
				break;
			}
			runtime
				->FUN_1001acf0(VTable0x38(model->m_unk0x08[lod]), VTable0x44(model->m_unk0x14[lod]), maxDistances[lod]);
		}

		runtime->VTable0x08(model->m_unk0x50);
		runtime->VTable0x40(model->m_unk0x5c, model->m_unk0x68);

		if (model->m_flags & WdbModel0x8c::e_flagBit3) {
			runtime->FUN_00411700(model->m_unk0x80);
			runtime->FUN_00411730(model->m_unk0x84);
		}
		if (model->m_flags & WdbModel0x8c::e_flagBit1) {
			runtime->m_flags |= FloatyCanoe0x90::c_flagBit1;
		}

		for (j = 0; j < model->m_unk0x7c; j++) {
			Rect* assignment = &model->m_unk0x78[j];
			if (static_cast<LegoU32>(assignment->m_left) >= m_unk0x74) {
				continue;
			}

			MabMaterialAnimationItem0x18* item = VTable0x4c(assignment->m_left)->GetUnk0x0c();
			LegoU32 targetIndex = assignment->m_bottom;
			MaterialTable0x0c* target = runtime->m_materialTables[targetIndex];
			if (target == NULL) {
				target = runtime->m_models[targetIndex]->GetMaterialTable();
			}
			item[assignment->m_top].FUN_10025da0(target, assignment->m_right, TRUE);
		}

		if (model->m_unk0x00[0] != '\0') {
			if (m_unk0xcc.GetNameEntries() == NULL) {
				m_unk0xcc.Allocate(m_unk0x5c);
			}
			m_unk0xcc.AddName(model->m_unk0x00, runtime);
		}
	}

	for (i = 0; i < m_unk0x44; i++) {
		LegoChar name[sizeof(GolName) + 1];
		::memcpy(name, m_unk0x48[i], sizeof(GolName));
		name[sizeof(GolName)] = '\0';
		m_unk0x98[i].VTable0x04(m_unk0x04, name, m_binary);
	}

	for (i = 0; i < m_unk0x64; i++) {
		WdbModel0x8c* model = &m_unk0x68[i];
		FloatyKajak0x64* runtime = &m_unk0xa8[i];

		if (static_cast<LegoU32>(model->m_unk0x14[0]) >= m_unk0x44) {
			GOL_FATALERROR_MESSAGE("Illegal bsp volume reference");
		}

		if (model->m_unk0x2c[0] >= 0) {
			if (model->m_unk0x2c[0] >= static_cast<LegoS32>(m_unk0x2c)) {
				GOL_FATALERROR_MESSAGE("Illegal alt mat assign ref val");
			}
			runtime->m_unk0x5c = VTable0x3c(model->m_unk0x2c[0]);
		}
		else {
			runtime->m_unk0x5c = NULL;
		}

		runtime->FUN_1001b760(&m_unk0x98[model->m_unk0x14[0]]);
		runtime->VTable0x08(model->m_unk0x50);
		runtime->VTable0x40(model->m_unk0x5c, model->m_unk0x68);

		if (model->m_unk0x00[0] != '\0') {
			if (m_unk0xd8.GetNameEntries() == NULL) {
				m_unk0xd8.Allocate(m_unk0x64);
			}
			m_unk0xd8.AddName(model->m_unk0x00, runtime);
		}
	}

	for (i = 0; i < m_unk0x7c; i++) {
		FUN_1002f210(i, VTable0x50(i));
	}

	for (i = 0; i < m_unk0x84; i++) {
		m_unk0xac[i].SetColor(m_unk0x88[i].m_color);
	}

	for (i = 0; i < m_unk0x8c; i++) {
		m_unk0xb0[i].SetColor(m_unk0x90[i].m_color);
		m_unk0xb0[i].SetDirection(m_unk0x90[i].m_unk0x04);
	}
}

// FUNCTION: GOLDP 0x1002f210
void ZoweeBlubberworth0xf0::FUN_1002f210(LegoU32 p_cameraIndex, AmberLensBase0x120* p_lens)
{
	WdbCamera0x4c* camera = &m_unk0x80[p_cameraIndex];

	p_lens->m_unk0x10 = camera->GetUnk0x40();
	p_lens->m_flags |= 2;
	p_lens->m_unk0x14 = camera->GetUnk0x44();
	p_lens->m_flags |= 2;
	p_lens->m_unk0x08 = camera->GetUnk0x48();
	p_lens->m_flags |= 2;

	p_lens->m_unk0x04->SetPosition(&camera->m_unk0x1c);
	p_lens->m_flags |= 1;
	p_lens->m_unk0x04->VTable0x24(&camera->m_unk0x28, &camera->m_unk0x34);
	p_lens->m_flags |= 1;

	if (camera->m_unk0x08 >= 0) {
		FloatyFerry0xf4* model = &m_unk0xa0[camera->m_unk0x08];
		p_lens->FUN_1001cb30(model, camera->m_unk0x0c);

		if (camera->m_unk0x14[0] != '\0') {
			camera->m_unk0x10 = model->GetModelPart()->GetPartIndex(camera->m_unk0x14);
		}

		if (camera->m_unk0x10 >= 0) {
			model->FUN_10023a70(camera->m_unk0x10);
			model->SetPartAnimationEnabled(TRUE);
		}
		else {
			model->SetPartAnimationEnabled(FALSE);
		}
	}

	if (camera->m_unk0x00[0] != '\0') {
		if (m_unk0xe4.GetNameEntries() == NULL) {
			GolNameTable* nameTable = &m_unk0xe4;
			nameTable->Allocate(m_unk0x7c);
		}
		m_unk0xe4.AddName(camera->m_unk0x00, p_lens);
	}
}

// FUNCTION: GOLDP 0x1002f350
void ZoweeBlubberworth0xf0::VTable0x54(undefined4 p_arg)
{
	FUN_1002baf0(p_arg);
}
