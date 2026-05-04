#include "boundingshape0x2c.h"

#include "golbinparser.h"
#include "golerror.h"

DECOMP_SIZE_ASSERT(BdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(BoundingShape0x2c::StructField0x08, 0x20)
DECOMP_SIZE_ASSERT(BoundingShape0x2c::StructField0x18, 0x18)
DECOMP_SIZE_ASSERT(BoundingShape0x2c, 0x2c)

// FUNCTION: GOLDP 0x1001adc0
BoundingShape0x2c::BoundingShape0x2c()
{
	m_unk0x04 = 0;
	m_unk0x08 = NULL;
	m_unk0x0c = NULL;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
	m_unk0x20 = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
}

// FUNCTION: GOLDP 0x1001adf0
BoundingShape0x2c::~BoundingShape0x2c()
{
	Destroy();
}

// FUNCTION: GOLDP 0x1001ae50
void BoundingShape0x2c::Deserialize(const LegoChar* p_path, LegoBool32 p_binary)
{
	LegoS32 i;

	if (m_unk0x08 != NULL) {
		Destroy();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".bdb");
	}
	else {
		parser = new BdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
	parser->OpenFileForRead(p_path);

	GolFileParser::ParserTokenType token;

	while ((token = parser->GetNextToken()) != 0) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			FUN_1001b010(*parser);
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_1001b1a0(*parser);
			break;
		case GolFileParser::e_unknown0x2b:
			m_unk0x1c = parser->FUN_100327e0();
			if (m_unk0x1c == 0) {
				parser->HandleUnexpectedToken(GolFileParser::ParserTokenType::e_int);
			}

			m_unk0x20 = new LegoS16[m_unk0x1c];
			if (m_unk0x20 == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (i = 0; i < m_unk0x1c; i++) {
				m_unk0x20[i] = parser->ReadInteger();
			}

			parser->ReadRightCurly();
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::ParserTokenType::e_syntaxerror);
			break;
		}
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: GOLDP 0x1001b010
void BoundingShape0x2c::FUN_1001b010(GolFileParser& p_parser)
{
	LegoU32 i;

	m_unk0x04 = p_parser.FUN_100327e0();
	if (m_unk0x04 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::ParserTokenType::e_int);
	}

	m_unk0x0c = m_unk0x08 = new StructField0x08[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_unk0x04; i++) {
		GolFileParser::ParserTokenType type = p_parser.GetNextToken();
		StructField0x08* obj = &m_unk0x08[i];

		if (type == GolFileParser::e_unknown0x28) {
			obj->m_type = StructField0x08::e_type0;
			obj->m_unk0x04.t0.m_unk0x10 = 0;
			obj->m_unk0x04.t0.m_unk0x14 = 0;

			if (p_parser.ReadInteger() < 0) {
				obj->m_unk0x02 = StructField0x08::c_invalidIndex;
				m_unk0x0c = obj;
			}
			else {
				obj->m_unk0x02 = p_parser.GetUnk0x38();
			}

			if (p_parser.ReadInteger() < 0) {
				obj->m_unk0x04.t0.m_unk0x18 = StructField0x08::c_invalidIndex;
			}
			else {
				obj->m_unk0x04.t0.m_unk0x18 = p_parser.GetUnk0x38();
			}

			if (p_parser.ReadInteger() < 0) {
				obj->m_unk0x04.t0.m_unk0x1a = StructField0x08::c_invalidIndex;
				if (obj->m_unk0x04.t0.m_unk0x18 == StructField0x08::c_invalidIndex) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuported);
				}
			}
			else {
				obj->m_unk0x04.t0.m_unk0x1a = p_parser.GetUnk0x38();
			}

			obj->m_unk0x04.t0.m_unk0x00 = p_parser.ReadFloat();
			obj->m_unk0x04.t0.m_unk0x04 = p_parser.ReadFloat();
			obj->m_unk0x04.t0.m_unk0x08 = p_parser.ReadFloat();
			obj->m_unk0x04.t0.m_unk0x0c = p_parser.ReadFloat();
		}
		else if (type == GolFileParser::e_unknown0x29) {
			obj->m_type = StructField0x08::e_type1;

			if (p_parser.ReadInteger() < 0) {
				obj->m_unk0x02 = StructField0x08::c_invalidIndex;
				m_unk0x0c = obj;
			}
			else {
				obj->m_unk0x02 = p_parser.GetUnk0x38();
			}

			obj->m_unk0x04.t1.m_unk0x00 = p_parser.ReadInteger();
			obj->m_unk0x04.t1.m_unk0x04 = p_parser.ReadInteger();
			obj->m_unk0x04.t1.m_unk0x18 = p_parser.ReadInteger();
			obj->m_unk0x04.t1.m_unk0x14 = p_parser.ReadInteger();
			obj->m_unk0x04.t1.m_unk0x16 = p_parser.ReadInteger();
		}
		else {
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001b1a0
void BoundingShape0x2c::FUN_1001b1a0(GolFileParser& p_parser)
{
	LegoS32 i;

	m_unk0x14 = p_parser.FUN_100327e0();
	if (m_unk0x14 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::ParserTokenType::e_int);
	}

	m_unk0x18 = new StructField0x18[m_unk0x14];
	if (m_unk0x18 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_unk0x14; i++) {
		m_unk0x18[i].m_unk0x00 = p_parser.ReadFloat();
		m_unk0x18[i].m_unk0x04 = p_parser.ReadFloat();
		m_unk0x18[i].m_unk0x08 = p_parser.ReadFloat();
		m_unk0x18[i].m_unk0x0c = p_parser.ReadFloat();
		m_unk0x18[i].m_unk0x10 = p_parser.ReadFloat();
		m_unk0x18[i].m_unk0x14 = p_parser.ReadFloat();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001b260
void BoundingShape0x2c::Destroy()
{
	m_unk0x04 = 0;
	m_unk0x10 = 0;

	if (m_unk0x08 != NULL) {
		delete[] m_unk0x08;
		m_unk0x08 = NULL;
	}

	m_unk0x14 = 0;

	if (m_unk0x18 != NULL) {
		delete[] m_unk0x18;
		m_unk0x18 = NULL;
	}

	m_unk0x1c = 0;

	if (m_unk0x20 != NULL) {
		delete[] m_unk0x20;
		m_unk0x20 = NULL;
	}

	m_unk0x24 = 0;
	m_unk0x28 = 0;
}

// STUB: GOLDP 0x1001b2c0
void BoundingShape0x2c::FUN_1001b2c0(undefined4*, undefined4*, undefined4*)
{
	// TODO
	STUB(0x1001b2c0);
}

// STUB: GOLDP 0x1001b640
void BoundingShape0x2c::FUN_1001b640(undefined4*, undefined4*, undefined4*, undefined4*)
{
	// TODO
	STUB(0x1001b640);
}
