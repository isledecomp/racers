#include "zoweeblubberworth0xf0.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golmath.h"

#include <float.h>

DECOMP_SIZE_ASSERT(ZoweeBlubberworth0xf0, 0xf0)
DECOMP_SIZE_ASSERT(WdbStaticModel0x8c, 0x8c)
DECOMP_SIZE_ASSERT(WdbTxtParser, 0x1fc)

// GLOBAL: GOLDP 0x100576e4
LegoFloat g_fltMax0x100576e4 = FLT_MAX;

// FUNCTION: GOLDP 0x1002c030
ZoweeBlubberworth0xf0::ZoweeBlubberworth0xf0()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002c0e0
void ZoweeBlubberworth0xf0::Reset()
{
	m_unk0x94 = 1.0;
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
	m_unk0x50 = 0;
	m_unk0x54 = 0;
	m_unk0x58 = 0;
	m_unk0x5c = 0;
	m_unk0x60 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	m_unk0x6c = 0;
	m_unk0x70 = 0;
	m_unk0x74 = 0;
	m_unk0x78 = 0;
	m_unk0x7c = 0;
	m_unk0x80 = 0;
	m_unk0x84 = 0;
	m_unk0x88 = 0;
	m_unk0x8c = 0;
	m_unk0x90 = 0;
	m_unk0x08 = FALSE;
	m_unk0x98 = 0;
	m_unk0x9c = 0;
	m_unk0xa0 = 0;
	m_unk0xa4 = 0;
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
void ZoweeBlubberworth0xf0::VTable0x14(undefined4 p_arg1, const LegoChar* p_name, LegoBool32 p_binary, float p_arg4)
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
	m_unk0x08 = p_binary;
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

// STUB: GOLDP 0x1002c4d0
void ZoweeBlubberworth0xf0::VTable0x00()
{
	// TODO
	STUB(0x1002c240);
}

// STUB: GOLDP 0x1002c6b0
void ZoweeBlubberworth0xf0::VTable0x18()
{
	// TODO
	STUB(0x1002c6b0);
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
	m_unk0x50 = new WdbStaticModel0x8c[m_unk0x4c];
	if (m_unk0x50 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memset(m_unk0x50, 0, sizeof(*m_unk0x50) * m_unk0x4c);
	WdbStaticModel0x8c* item = m_unk0x50;
	for (i = 0; i < m_unk0x4c; item++, i++) {
		LegoU32 cnt = 0;
		p_parser.AssertNextTokenIs(GolFileParser::e_unknown0x2e);
		if (p_parser.GetNextToken() != GolFileParser::e_string) {
			p_parser.SetUnk0x30(1);
			item->m_unk0x00[0] = '\0';
		}
		else {
			::strncpy(item->m_unk0x00, p_parser.GetUnk0x44(), sizeof(item->m_unk0x00));
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
				if (static_cast<LegoU32>(p_parser.GetUnk0x38()) >= m_unk0x24 && m_unk0x24 != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x08[cnt] = p_parser.GetUnk0x38();
				if (p_parser.GetNextToken() != GolFileParser::e_float) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_float);
				}
				if (p_parser.GetUnk0x40() < 0.0f) {
					item->m_unk0x38[cnt] = g_fltMax0x100576e4;
				}
				else {
					item->m_unk0x38[cnt] = p_parser.GetUnk0x40();
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
				if (static_cast<LegoU32>(p_parser.GetUnk0x38()) >= m_unk0x2c && m_unk0x2c != 0) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				v = p_parser.GetUnk0x38();
				if (p_parser.GetNextToken() != GolFileParser::e_int) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_int);
				}
				if (p_parser.GetUnk0x38() >= static_cast<LegoS32>(sizeOfArray(item->m_unk0x2c))) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_invalidValue);
				}
				item->m_unk0x2c[p_parser.GetUnk0x38()] = v;
				break;
			case GolFileParser::e_unknown0x36:
				item->m_unk0x74 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x3e:
				FUN_1002dbe0(p_parser, &item->m_unk0x78, &item->m_unk0x7c);
				break;
			case GolFileParser::e_unknown0x3f:
				item->m_flags |= WdbStaticModel0x8c::e_flagBit3;
				item->m_unk0x80 = p_parser.ReadFloat();
				item->m_unk0x84 = p_parser.ReadFloat();
				break;
			case GolFileParser::e_unknown0x42:
				item->m_flags |= WdbStaticModel0x8c::e_flagBit1;
				break;
			case GolFileParser::e_unknown0x4c:
				item->m_flags |= WdbStaticModel0x8c::e_flagBit2;
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}
	p_parser.ReadRightCurly();
}

// STUB: GOLDP 0x1002cfa0
void ZoweeBlubberworth0xf0::FUN_1002cfa0(GolFileParser& p_parser)
{
	// TODO
	STUB(0x1002cfa0);
}

// STUB: GOLDP 0x1002d400
void ZoweeBlubberworth0xf0::FUN_1002d400(GolFileParser& p_parser)
{
	// TODO
	STUB(0x1002d400);
}

// STUB: GOLDP 0x1002d720
void ZoweeBlubberworth0xf0::FUN_1002d720(GolFileParser& p_parser)
{
	// TODO
	STUB(0x1002d720);
}

// STUB: GOLDP 0x1002d950
void ZoweeBlubberworth0xf0::FUN_1002d950(GolFileParser& p_parser)
{
	// TODO
	STUB(0x1002d950);
}

// STUB: GOLDP 0x1002db50
void ZoweeBlubberworth0xf0::FUN_1002db50(GolFileParser& p_parser)
{
	// TODO
	STUB(0x1002db50);
}

// STUB: GOLDP 0x1002dbe0
void ZoweeBlubberworth0xf0::FUN_1002dbe0(GolFileParser& p_parser, LegoU32* p_count, undefined4**)
{
	// TODO
	STUB(0x1002dbe0);
}

// STUB: GOLDP 0x1002dc80
void ZoweeBlubberworth0xf0::FUN_1002dc80(GolFileParser& p_parser)
{
	// TODO
	STUB(0x1002dc80);
}

// STUB: GOLDP 0x1002df90
void ZoweeBlubberworth0xf0::FUN_1002df90(GolFileParser& p_parser)
{
	// TODO
	STUB(0x1002df90);
}

// STUB: GOLDP 0x1002e0d0
void ZoweeBlubberworth0xf0::FUN_1002e0d0(GolFileParser& p_parser)
{
	// TODO
	STUB(0x1002e0d0);
}

// STUB: GOLDP 0x1002e250
void ZoweeBlubberworth0xf0::FUN_1002e250(undefined4*, undefined4*)
{
	// TODO
	STUB(0x1002e250);
}

// STUB: GOLDP 0x1002e2c0
void ZoweeBlubberworth0xf0::VTable0x04()
{
	// TODO
	STUB(0x1002e2c0);
}

// STUB: GOLDP 0x1002e640
void ZoweeBlubberworth0xf0::FUN_1002e640()
{
	// TODO
	STUB(0x1002e640);
}

// STUB: GOLDP 0x1002f210
void ZoweeBlubberworth0xf0::FUN_1002f210(undefined4, undefined4*)
{
	// TODO
	STUB(0x1002f210);
}

// STUB: GOLDP 0x1002f350
void ZoweeBlubberworth0xf0::VTable0x54()
{
	// TODO
	STUB(0x1002f350);
}
