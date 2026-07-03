#include "golmodelbase.h"

#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "goltxtparser.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(GolModelBase, 0x40)
DECOMP_SIZE_ASSERT(GolModelBase::GdbTxtParser, 0x1fc)

// FUNCTION: GOLDP 0x10027020
GolModelBase::GolModelBase()
{
	m_vertexArray = NULL;
	m_ownedVertexArray = NULL;
	m_indexArray = NULL;
	m_unk0x1c = NULL;
	m_groupCount = 0;
	m_groups = NULL;
	m_center.m_x = 0.0f;
	m_center.m_y = 0.0f;
	m_center.m_z = 0.0f;
	m_dirty = FALSE;
	m_radius = FLT_MAX / 2.0f;
	m_scale = 1.0f;
}

// FUNCTION: GOLDP 0x10027090
GolModelBase::~GolModelBase()
{
	Destroy();
}

// FUNCTION: GOLDP 0x100270e0
void GolModelBase::Load(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_groups != NULL) {
		Destroy();
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
		case GdbTxtParser::e_material:
			if (m_materialTable.GetRenderer() != NULL) {
				parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
			}
			m_materialTable.Parse(p_renderer, *parser);
			break;
		case GdbTxtParser::e_uncoloredVertices:
			ParseUncoloredVertices(*parser);
			break;
		case GdbTxtParser::e_coloredVertices:
			ParseColoredVertices(*parser);
			break;
		case GdbTxtParser::e_normalVertices:
			ParseNormalVertices(*parser);
			break;
		case GdbTxtParser::e_indices:
			ParseIndices(*parser);
			break;
		case GdbTxtParser::e_groups:
			if (m_groups != NULL) {
				parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
			}
			ParseGroups(*parser);
			break;
		case GdbTxtParser::e_scale:
			m_scale = parser->ReadFloat();
			break;
		case GdbTxtParser::e_vertices:
			ParseVertices(*parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	if (m_vertexArray != 0) {
		ComputeBounds(&m_center, &m_radius, m_scale);
	}

	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x100272e0
void GolModelBase::AllocateIndices(LegoU32 p_countVertices, LegoU32 p_countGroups)
{
	m_groupCount = p_countGroups;

	m_indexArray = new GdbModelIndexArray;
	m_groups = new LegoU32[m_groupCount];
	if (m_indexArray == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	static_cast<GdbModelIndexArray*>(m_indexArray)->Allocate(p_countVertices);
	if (m_groups == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_groups[0] = 0x6 << 29;
}

// FUNCTION: GOLDP 0x100273b0
void GolModelBase::Destroy()
{
	if (m_ownedVertexArray != NULL) {
		m_ownedVertexArray->Destroy();
		delete m_ownedVertexArray;
		m_ownedVertexArray = NULL;
		m_vertexArray = NULL;
	}
	if (m_unk0x1c != NULL) {
		delete m_unk0x1c;
		m_unk0x1c = NULL;
	}
	if (m_indexArray != NULL) {
		m_indexArray->Destroy();
		delete m_indexArray;
		m_indexArray = NULL;
	}
	if (m_groups != NULL) {
		delete[] m_groups;
		m_groups = NULL;
	}

	m_materialTable.Destroy();
	m_groupCount = 0;
}

// FUNCTION: GOLDP 0x10027430
void GolModelBase::ParseGroups(GolFileParser& p_parser)
{
	m_groupCount = p_parser.ReadBracketedCountAndLeftCurly();

	LegoU32 count = 0;
	if (m_groupCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_groups = new LegoU32[m_groupCount];
	if (m_groups == NULL) {
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

	if (i < m_groupCount) {
		colorStackPointer = colorStack;

		for (; i < m_groupCount; i++) {
			switch (p_parser.GetNextToken()) {
			case GdbTxtParser::e_triangles:
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
				m_groups[count] = 0x0 << 29;
				m_groups[count] |= (field1 & 0x3f) << 22;
				m_groups[count] |= ((field2 + 0xffff) & 0x3f) << 16;
				m_groups[count++] |= (field0 & 0xffff);
				break;

			case GdbTxtParser::e_triangleBatch:
				if (seen) {
					count += 1;
					seen = FALSE;
				}
				field0 = p_parser.ReadInteger();
				field1 = p_parser.ReadInteger();
				if (field1 > 0xff) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuported);
				}
				m_groups[count] = 0x1 << 29;
				m_groups[count] |= ((field1 & 0x7f) << 16);
				m_groups[count++] |= (field0 & 0xffff);
				break;

			case GdbTxtParser::e_pushMatrix:
				field1 = p_parser.ReadInteger();
				if (stackSize >= sizeOfArray(colorStack)) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
				}
				seen = TRUE;
				stackSize += 1;
				*colorStackPointer++ = field1;
				m_groups[count] = 0x5 << 29;
				m_groups[count] |= field1 & 0xffffff;
				break;

			case GdbTxtParser::e_popMatrix:
				if (stackSize < 1) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
				}
				stackSize -= 1;
				seen = TRUE;
				m_groups[count] = 0x5 << 29;
				colorStackPointer--;
				m_groups[count] |= colorStackPointer[-1] & 0xffffff;
				break;

			case GdbTxtParser::e_setMatrix:
				field1 = p_parser.ReadInteger();
				seen = TRUE;
				m_groups[count] = 0x5 << 29;
				m_groups[count] |= field1 & 0xffffff;
				break;

			case GdbTxtParser::e_material:
				if (seen) {
					count += 1;
					seen = FALSE;
				}
				field0 = p_parser.ReadInteger();
				m_groups[count] = 0x4 << 29;
				m_groups[count++] |= (field0 & 0x00ffffff);
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

	m_groupCount = count;
}

// FUNCTION: GOLDP 0x10027740
void GolModelBase::ParseIndices(GolFileParser& p_parser)
{
	if (m_indexArray != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_indexArray = new GdbModelIndexArray;
	if (m_indexArray == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_indexArray->Parse(p_parser);
}

// FUNCTION: GOLDP 0x100277d0
void GolModelBase::GetVertexArray(GdbVertexArray** p_dest) const
{
	*p_dest = m_vertexArray;
}

// FUNCTION: GOLDP 0x100277e0
void GolModelBase::AddFlagsWithBounds(LegoU32 p_arg1, LegoBool32 p_arg2)
{
	m_dirty |= p_arg1;
	if (p_arg2) {
		ComputeBounds(&m_center, &m_radius, m_scale);
	}
}

// FUNCTION: GOLDP 0x10027810
void GolModelBase::GetIndexArrayInto(GdbModelIndexArrayBase** p_dest) const
{
	*p_dest = m_indexArray;
}

// FUNCTION: GOLDP 0x10027820
void GolModelBase::AddFlags(LegoU32 p_arg1)
{
	m_dirty |= p_arg1;
}

// FUNCTION: GOLDP 0x10027830
void GolModelBase::ParseVertices(GolFileParser& p_parser)
{
	if (m_ownedVertexArray != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_ownedVertexArray = new GdbVertexArray;
	m_vertexArray = m_ownedVertexArray;
	if (m_vertexArray == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_ownedVertexArray->Parse(p_parser);
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GolModelBase::ParseNormalVertices(GolFileParser& p_parser)
{
	// empty
}

// FUNCTION: GOLDP 0x100278c0
void GolModelBase::ComputeBounds(GolVec3* p_center, LegoFloat* p_radius, LegoFloat p_scale) const
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
	maskPtr = m_groups;
	endMaskPtr = m_groups + m_groupCount;

	for (; maskPtr < endMaskPtr; maskPtr++) {
		LegoU32 mask = *maskPtr;
		if ((mask & (0x7 << 29)) == 0) {
			LegoU32 vertexIndex = mask & 0xffff;
			LegoU32 endVertexIndex = vertexIndex + 1 + ((mask >> 16) & 0x3f);
			for (; vertexIndex < endVertexIndex; vertexIndex++) {
				m_vertexArray->GetPosition(vertexIndex, &vertex);
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
		maskPtr = m_groups;
		endMaskPtr = m_groups + m_groupCount;

		for (; maskPtr < endMaskPtr; maskPtr++) {
			LegoU32 mask = *maskPtr;
			if ((mask & (0x7 << 29)) == 0) {
				LegoU32 vertexIndex = mask & 0xffff;
				LegoU32 endVertexIndex = vertexIndex + 1 + ((mask >> 16) & 0x3f);
				for (; vertexIndex < endVertexIndex; vertexIndex++) {
					m_vertexArray->GetPosition(vertexIndex, &vertex);
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
void GolModelBase::ApplyColorTransform(const ColorTransform& p_details)
{
	m_vertexArray->ApplyColorTransform(p_details);
}

// FUNCTION: GOLDP 0x10027b40
void GolModelBase::ClearColorTransform()
{
	m_vertexArray->ClearColorTransform();
}

// FUNCTION: LEGORACERS 0x00411090
void GolModelBase::MirrorY()
{
	GdbModelIndexArrayBase* indexArray = NULL;
	GdbVertexArray* vertexArray = NULL;
	GetVertexArray(&vertexArray);

	LegoU32 vertexCount = vertexArray->GetCount();
	LegoU32 i;
	for (i = 0; i < vertexCount; i++) {
		GolVec3 vertex;
		vertexArray->GetPosition(i, &vertex);
		vertex.m_y = -vertex.m_y;
		vertexArray->SetPosition(i, vertex);
	}

	AddFlagsWithBounds(1, TRUE);

	GetIndexArrayInto(&indexArray);

	GdbModelIndexArray* modelIndexArray = static_cast<GdbModelIndexArray*>(indexArray);
	GdbModelIndexArray::Indices* indices = modelIndexArray->GetMutableIndices();
	LegoU32 indexCount = indexArray->GetCount();
	for (i = 0; i < indexCount; i++) {
		LegoU8 value = indices[i].m_b;
		indices[i].m_b = indices[i].m_c;
		indices[i].m_c = value;
	}

	AddFlags(1);
}
