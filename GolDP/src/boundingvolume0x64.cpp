#include "boundingvolume0x64.h"

#include "gdbvertexarray0xc.h"
#include "golbinparser.h"
#include "golerror.h"

DECOMP_SIZE_ASSERT(BoundingVolume0x64, 0x64)

// FUNCTION: GOLDP 0x1001b770
BoundingVolume0x64::BoundingVolume0x64() : m_unk0x24(&m_unk0x18)
{
	m_unk0x04 = 0;
	m_unk0x08 = NULL;
	m_unk0x0c = NULL;
	m_unk0x10 = 0;
	m_unk0x14 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = NULL;
}

// FUNCTION: GOLDP 0x1001b7b0
BoundingVolume0x64::~BoundingVolume0x64()
{
	VTable0x08();
}

// FUNCTION: GOLDP 0x1001b800
void BoundingVolume0x64::VTable0x04(undefined4* p_arg1, const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_unk0x08 != NULL) {
		VTable0x08();
	}
	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".bvb");
	}
	else {
		parser = new BvbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
	parser->OpenFileForRead(p_name);
	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			if (m_unk0x18.GetRenderer() != NULL) {
				parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
			}
			m_unk0x18.FUN_10025f90(reinterpret_cast<WhiteFalcon0x140*>(p_arg1), *parser);
			break;
		case GolFileParser::e_unknown0x34:
			if (m_unk0x0c != 0) {
				parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
			}
			m_unk0x0c = new GdbVertexArray0xc;
			if (m_unk0x0c == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			m_unk0x0c->VTable0x08(*parser);
			break;
		case GolFileParser::e_unknown0x2d:
			FUN_1001bb10(*parser);
			break;
		case GolFileParser::e_unknown0x8b:
			FUN_1001bbb0(*parser);
			break;
		case GolFileParser::e_unknown0x8e:
			FUN_1001bd00(*parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}
	}
	if (m_unk0x04 != 0) {
		m_unk0x28 = FUN_1001be50();
		m_unk0x2c = new GolVec3[m_unk0x28];
		if (m_unk0x2c == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x1001ba90
void BoundingVolume0x64::VTable0x08()
{
	if (m_unk0x08 != NULL) {
		if (m_unk0x0c != NULL) {
			m_unk0x0c->VTable0x0c();
			if (m_unk0x0c != NULL) {
				delete m_unk0x0c;
			}
		}
		if (m_unk0x14 != NULL) {
			delete[] m_unk0x14;
		}
		if (m_unk0x08 != NULL) {
			delete[] m_unk0x08;
		}
		if (m_unk0x2c != NULL) {
			delete[] m_unk0x2c;
		}
		m_unk0x04 = 0;
		m_unk0x08 = NULL;
		m_unk0x0c = 0;
		m_unk0x10 = 0;
		m_unk0x14 = NULL;
		m_unk0x24 = &m_unk0x18;
		m_unk0x28 = 0;
		m_unk0x2c = NULL;
	}
}

// FUNCTION: GOLDP 0x1001bb10
void BoundingVolume0x64::FUN_1001bb10(GolFileParser& p_parser)
{
	LegoU32 i;

	m_unk0x10 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x10 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x14 = new PolygonId0x08[m_unk0x10];
	if (m_unk0x14 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x10; i++) {
		m_unk0x14[i].m_unk0x00 = p_parser.ReadInteger();
		m_unk0x14[i].m_unk0x02 = p_parser.ReadInteger();
		m_unk0x14[i].m_unk0x04 = p_parser.ReadInteger();
		m_unk0x14[i].m_unk0x06 = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001bbb0
void BoundingVolume0x64::FUN_1001bbb0(GolFileParser& p_parser)
{
	LegoU32 i;

	m_unk0x04 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x04 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x08 = new PolygonRange0x14[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x04; i++) {
		LegoU32 j;
		for (j = 0; j < 2; j++) {
			switch (p_parser.GetNextToken()) {
			case GolFileParser::e_unknown0x8d:
				m_unk0x08[i].m_unk0x10[j] = -2;
				break;
			case GolFileParser::e_unknown0x8c:
				m_unk0x08[i].m_unk0x10[j] = -1;
				break;
			case GolFileParser::e_int:
				m_unk0x08[i].m_unk0x10[j] = p_parser.GetLastInt();
				break;
			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
		GolVec4 v;
		v.m_x = p_parser.ReadFloat();
		v.m_y = p_parser.ReadFloat();
		v.m_z = p_parser.ReadFloat();
		v.m_u = p_parser.ReadFloat();
		GolVec3* ptrVec = &m_unk0x08[i].m_unk0x00;
		ptrVec->m_x = v.m_x;
		ptrVec->m_y = v.m_y;
		ptrVec->m_z = v.m_z;
		m_unk0x08[i].m_unk0x0c = p_parser.ReadInteger();
		m_unk0x08[i].m_unk0x0e = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001bd00
void BoundingVolume0x64::FUN_1001bd00(GolFileParser& p_parser)
{
	LegoU32 i;

	m_unk0x04 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x04 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_unk0x08 = new PolygonRange0x14[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_unk0x04; i++) {
		LegoU32 j;
		for (j = 0; j < 2; j++) {
			LegoS32 v = p_parser.ReadInteger();
			if (v < 0) {
				if (v == -1) {
					m_unk0x08[i].m_unk0x10[j] = -1;
				}
				else if (v == -2) {
					m_unk0x08[i].m_unk0x10[j] = -2;
				}
				else {
					p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				}
			}
			else {
				m_unk0x08[i].m_unk0x10[j] = v;
			}
		}
		int i3[3];
		i3[0] = p_parser.ReadInteger();
		i3[1] = p_parser.ReadInteger();
		i3[2] = p_parser.ReadInteger();
		GolVec3* ptrVec = &m_unk0x08[i].m_unk0x00;
		ptrVec->m_x = static_cast<float>(i3[0]) / static_cast<float>(0x40000000);
		ptrVec->m_y = static_cast<float>(i3[1]) / static_cast<float>(0x40000000);
		ptrVec->m_z = static_cast<float>(i3[2]) / static_cast<float>(0x40000000);
		m_unk0x08[i].m_unk0x0c = p_parser.ReadInteger();
		m_unk0x08[i].m_unk0x0e = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001be50
undefined4 BoundingVolume0x64::FUN_1001be50()
{
	LegoU16* stack = new LegoU16[m_unk0x04];
	if (stack == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 index = 0;
	LegoU32 maxStackSize = 0;
	LegoU32 stackSize = 0;
	LegoU32 prevIndex = 0;
	*stack = 0;
	LegoU16* stackHead = stack;

	for (;;) {
		PolygonRange0x14* obj = &m_unk0x08[index];
		if (stackSize > maxStackSize) {
			maxStackSize = stackSize;
		}

		LegoU32 rightIndex = obj->m_unk0x10[1];
		if (prevIndex != rightIndex) {
			LegoU32 leftIndex = obj->m_unk0x10[0];
			if (prevIndex != leftIndex && leftIndex != 0xffff && leftIndex != 0xfffe) {
				stackSize++;
				stackHead++;
				prevIndex = index;
				index = leftIndex;
				*stackHead = leftIndex;
				continue;
			}
			if (rightIndex != 0xffff && rightIndex != 0xfffe) {
				stackSize++;
				stackHead++;
				prevIndex = index;
				index = rightIndex;
				*stackHead = rightIndex;
				continue;
			}
		}

		if (stackSize < 1) {
			break;
		}
		prevIndex = index;
		stackSize--;
		stackHead--;
		index = *stackHead;
	}
	delete[] stack;
	return maxStackSize + 1;
}
