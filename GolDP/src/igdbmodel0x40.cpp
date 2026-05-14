#include "igdbmodel0x40.h"

#include "gdbmodelindexarray0xc.h"
#include "gdbvertexarray0xc.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(IGdbModel0x40, 0x40)

// FUNCTION: GOLDP 0x10027020
IGdbModel0x40::IGdbModel0x40()
{
	m_unk0x10 = NULL;
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_countGroups = 0;
	m_unk0x24 = NULL;
	m_unk0x28.m_x = 0.0f;
	m_unk0x28.m_y = 0.0f;
	m_unk0x28.m_z = 0.0f;
	m_unk0x3c = FALSE;
	m_unk0x34 = FLT_MAX / 2.0f;
	m_unk0x38 = 1.0f;
}

// FUNCTION: GOLDP 0x10027090
IGdbModel0x40::~IGdbModel0x40()
{
	VTable0x24();
}

// FUNCTION: GOLDP 0x100270e0
void IGdbModel0x40::VTable0x1c(WhiteFalcon0x140* p_renderer, const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_unk0x24 != NULL) {
		VTable0x24();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".gdb");
	}
	else {
		parser = new GdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			if (m_unk0x04.GetRenderer() != NULL) {
				parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
			}
			m_unk0x04.FUN_10025f90(p_renderer, *parser);
			break;
		case GolFileParser::e_unknown0x28:
			VTable0x0c(*parser);
			break;
		case GolFileParser::e_unknown0x2a:
			VTable0x10(*parser);
			break;
		case GolFileParser::e_unknown0x29:
			VTable0x14(*parser);
			break;
		case GolFileParser::e_unknown0x2d:
			VTable0x04(*parser);
			break;
		case GolFileParser::e_unknown0x2e:
			if (m_unk0x24 != NULL) {
				parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
			}
			VTable0x00(*parser);
			break;
		case GolFileParser::e_unknown0x33:
			m_unk0x38 = parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x34:
			VTable0x08(*parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	if (m_unk0x10 != 0) {
		VTable0x38(&m_unk0x28, &m_unk0x34, m_unk0x38);
	}

	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x100272e0
void IGdbModel0x40::FUN_100272e0(LegoU32 p_countVertices, LegoU32 p_countGroups)
{
	m_countGroups = p_countGroups;

	m_unk0x18 = new GdbModelIndexArray0xc;
	m_unk0x24 = new LegoU32[m_countGroups];
	if (m_unk0x18 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	static_cast<GdbModelIndexArray0xc*>(m_unk0x18)->VTable0x0c(p_countVertices);
	if (m_unk0x24 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x24[0] = 0x6 << 29;
}

// FUNCTION: GOLDP 0x100273b0
void IGdbModel0x40::VTable0x24()
{
	if (m_unk0x14 != NULL) {
		m_unk0x14->VTable0x0c();
		delete m_unk0x14;
		m_unk0x14 = NULL;
		m_unk0x10 = NULL;
	}
	if (m_unk0x1c != NULL) {
		delete m_unk0x1c;
		m_unk0x1c = NULL;
	}
	if (m_unk0x18 != NULL) {
		m_unk0x18->VTable0x08();
		delete m_unk0x18;
		m_unk0x18 = NULL;
	}
	if (m_unk0x24 != NULL) {
		delete[] m_unk0x24;
		m_unk0x24 = NULL;
	}

	m_unk0x04.Destroy();
	m_countGroups = 0;
}

// FUNCTION: GOLDP 0x10027430
void IGdbModel0x40::VTable0x00(GolFileParser& p_parser)
{
	m_countGroups = p_parser.ReadBracketedCountAndLeftCurly();

	LegoU32 count = 0;
	if (m_countGroups == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x24 = new LegoU32[m_countGroups];
	if (m_unk0x24 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 field0;
	LegoU32 field1;
	LegoU32 field2;
	LegoU32 colorStack[10];
	LegoU32 i;
	LegoU32 stackSize;
	LegoBool32 seen;
	LegoU32* colorStackPointer;

	stackSize = 0;
	i = 0;
	seen = FALSE;

	if (i < m_countGroups) {
		colorStackPointer = colorStack;

		for (; i < m_countGroups; i++) {
			switch (p_parser.GetNextToken()) {
			case GolFileParser::e_unknown0x31:
				if (seen) {
					count += 1;
					seen = FALSE;
				}
				field1 = p_parser.ReadInteger();
				if (field1 >= 0x40) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuported);
				}
				field0 = p_parser.ReadInteger();
				field2 = p_parser.ReadInteger();
				if (field2 + field1 > 0x40) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuported);
				}
				m_unk0x24[count] = 0x0 << 29;
				m_unk0x24[count] |= (field1 & 0x3f) << 22;
				m_unk0x24[count] |= ((field2 + 0xffff) & 0x3f) << 16;
				m_unk0x24[count++] |= (field0 & 0xffff);
				break;

			case GolFileParser::e_unknown0x2d:
				if (seen) {
					count += 1;
					seen = FALSE;
				}
				field0 = p_parser.ReadInteger();
				field1 = p_parser.ReadInteger();
				if (field1 > 0xff) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuported);
				}
				m_unk0x24[count] = 0x1 << 29;
				m_unk0x24[count] |= ((field1 & 0x7f) << 16);
				m_unk0x24[count++] |= (field0 & 0xffff);
				break;

			case GolFileParser::e_unknown0x2f:
				field1 = p_parser.ReadInteger();
				if (stackSize >= sizeOfArray(colorStack)) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
				}
				seen = TRUE;
				stackSize += 1;
				*colorStackPointer++ = field1;
				m_unk0x24[count] = 0x5 << 29;
				m_unk0x24[count] |= field1 & 0xffffff;
				break;

			case GolFileParser::e_unknown0x30:
				if (stackSize < 1) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
				}
				stackSize -= 1;
				seen = TRUE;
				m_unk0x24[count] = 0x5 << 29;
				colorStackPointer--;
				m_unk0x24[count] |= colorStackPointer[-1] & 0xffffff;
				break;

			case GolFileParser::e_unknown0x32:
				field1 = p_parser.ReadInteger();
				seen = TRUE;
				m_unk0x24[count] = 0x5 << 29;
				m_unk0x24[count] |= field1 & 0xffffff;
				break;

			case GolFileParser::e_unknown0x27:
				if (seen) {
					count += 1;
					seen = FALSE;
				}
				field0 = p_parser.ReadInteger();
				m_unk0x24[count] = 0x4 << 29;
				m_unk0x24[count++] |= (field0 & 0x00ffffff);
				break;

			default:
				p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		}
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}

	m_countGroups = count;
}

// FUNCTION: GOLDP 0x10027740
void IGdbModel0x40::VTable0x04(GolFileParser& p_parser)
{
	if (m_unk0x18 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x18 = new GdbModelIndexArray0xc;
	if (m_unk0x18 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x18->VTable0x04(p_parser);
}

// FUNCTION: GOLDP 0x100277d0
void IGdbModel0x40::VTable0x28(GdbVertexArray0xc** p_dest) const
{
	*p_dest = m_unk0x10;
}

// FUNCTION: GOLDP 0x100277e0
void IGdbModel0x40::VTable0x2c(LegoU32 p_arg1, LegoBool32 p_arg2)
{
	m_unk0x3c |= p_arg1;
	if (p_arg2) {
		VTable0x38(&m_unk0x28, &m_unk0x34, m_unk0x38);
	}
}

// FUNCTION: GOLDP 0x10027810
void IGdbModel0x40::VTable0x30(IGdbModelIndexArray0x8** p_dest) const
{
	*p_dest = m_unk0x18;
}

// FUNCTION: GOLDP 0x10027820
void IGdbModel0x40::VTable0x34(LegoU32 p_arg1)
{
	m_unk0x3c |= p_arg1;
}

// FUNCTION: GOLDP 0x10027830
void IGdbModel0x40::VTable0x08(GolFileParser& p_parser)
{
	if (m_unk0x14 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x14 = new GdbVertexArray0xc;
	m_unk0x10 = m_unk0x14;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x14->VTable0x08(p_parser);
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void IGdbModel0x40::VTable0x14(GolFileParser& p_parser)
{
	// empty
}

// FUNCTION: GOLDP 0x100278c0
void IGdbModel0x40::VTable0x38(GolVec3* p_center, LegoFloat* p_radius, LegoFloat p_scale) const
{
	LegoU32 countGroups;
	GolVec3 vertex;
	GolVec3 max;
	GolVec3 min;
	LegoU32* maskPtr;
	LegoU32* endMaskPtr;

	min.m_x = FLT_MAX;
	min.m_y = FLT_MAX;
	min.m_z = FLT_MAX;
	max.m_x = -FLT_MAX;
	max.m_y = -FLT_MAX;
	max.m_z = -FLT_MAX;
	countGroups = 0;
	maskPtr = m_unk0x24;
	endMaskPtr = m_unk0x24 + m_countGroups;

	for (; maskPtr < endMaskPtr; maskPtr++) {
		LegoU32 mask = *maskPtr;
		if ((mask & (0x7 << 29)) == 0) {
			LegoU32 vertexIndex = mask & 0xffff;
			LegoU32 endVertexIndex = vertexIndex + 1 + ((mask >> 16) & 0x3f);
			for (; vertexIndex < endVertexIndex; vertexIndex++) {
				m_unk0x10->VTable0x14(vertexIndex, &vertex);
				if (vertex.m_x < min.m_x) {
					min.m_x = vertex.m_x;
				}
				if (vertex.m_x > max.m_x) {
					max.m_x = vertex.m_x;
				}
				if (vertex.m_y < min.m_y) {
					min.m_y = vertex.m_y;
				}
				if (vertex.m_y > max.m_y) {
					max.m_y = vertex.m_y;
				}
				if (vertex.m_z < min.m_z) {
					min.m_z = vertex.m_z;
				}
				if (vertex.m_z > max.m_z) {
					max.m_z = vertex.m_z;
				}
			}
			countGroups += 1;
		}
		else if ((mask & (0x7 << 29)) == (0x6 << 29)) {
			break;
		}
	}

	if (countGroups != 0) {
		GolVec3* center = p_center;
		center->m_x = (max.m_x + min.m_x) / 2.0f;
		center->m_y = (max.m_y + min.m_y) / 2.0f;
		center->m_z = (max.m_z + min.m_z) / 2.0f;

		LegoFloat radiusSquared = -FLT_MAX;
		maskPtr = m_unk0x24;
		endMaskPtr = m_unk0x24 + m_countGroups;

		for (; maskPtr < endMaskPtr; maskPtr++) {
			LegoU32 mask = *maskPtr;
			if ((mask & (0x7 << 29)) == 0) {
				LegoU32 vertexIndex = mask & 0xffff;
				LegoU32 endVertexIndex = vertexIndex + 1 + ((mask >> 16) & 0x3f);
				for (; vertexIndex < endVertexIndex; vertexIndex++) {
					m_unk0x10->VTable0x14(vertexIndex, &vertex);
					LegoFloat distSquared = center->DistanceSquaredTo(vertex);
					if (distSquared > radiusSquared) {
						radiusSquared = distSquared;
					}
				}
			}
			else if ((mask & (0x7 << 29)) == (0x6 << 29)) {
				break;
			}
		}

		center->m_x = p_scale * center->m_x;
		LegoFloat y = center->m_y;
		center->m_y = y * p_scale;
		LegoFloat z = center->m_z;
		center->m_z = z * p_scale;
		*p_radius = static_cast<LegoFloat>(sqrt(radiusSquared)) * p_scale;
	}
}

// FUNCTION: GOLDP 0x10027b30
void IGdbModel0x40::VTable0x3c(const PixelFormatMod& p_details)
{
	m_unk0x10->VTable0x34(p_details);
}

// FUNCTION: GOLDP 0x10027b40
void IGdbModel0x40::VTable0x40()
{
	m_unk0x10->VTable0x38();
}
