#include "golboundingvolume.h"

#include "gdbvertexarray0xc.h"
#include "golbinparser.h"
#include "golcamerabase.h"
#include "golerror.h"
#include "golmath.h"

DECOMP_SIZE_ASSERT(GolBoundingVolume::Field0x0c, 0x34)
DECOMP_SIZE_ASSERT(GolBoundingVolume::PolygonId0x08, 0x08)
DECOMP_SIZE_ASSERT(GolBoundingVolume::PolygonRange0x14, 0x14)
DECOMP_SIZE_ASSERT(GolBoundingVolume::TraversalEntry0x0c, 0x0c)
DECOMP_SIZE_ASSERT(GolBoundingVolume, 0x64)
DECOMP_SIZE_ASSERT(GolBoundingVolume::BvbTxtParser, 0x1fc)

// GLOBAL: LEGORACERS 0x004c26f8
GolVec3 g_unk0x004c26f8;

// GLOBAL: LEGORACERS 0x004c2704
undefined4 g_unk0x004c2704;

// GLOBAL: LEGORACERS 0x004c2708
GolVec3 g_unk0x004c2708;

// GLOBAL: LEGORACERS 0x004c2714
undefined4 g_unk0x004c2714;

// GLOBAL: LEGORACERS 0x004c2718
GolVec3 g_unk0x004c2718;

// GLOBAL: LEGORACERS 0x004c2724
undefined4 g_unk0x004c2724;

// GLOBAL: LEGORACERS 0x004c2728
GolVec3 g_unk0x004c2728;

// FUNCTION: GOLDP 0x1001b770
GolBoundingVolume::GolBoundingVolume() : m_unk0x24(&m_unk0x18)
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
GolBoundingVolume::~GolBoundingVolume()
{
	VTable0x08();
}

// FUNCTION: GOLDP 0x1001b800
void GolBoundingVolume::VTable0x04(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoBool32 p_binary)
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
			m_unk0x18.FUN_10025f90(p_renderer, *parser);
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
		m_unk0x2c = new TraversalEntry0x0c[m_unk0x28];
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
void GolBoundingVolume::VTable0x08()
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
void GolBoundingVolume::FUN_1001bb10(GolFileParser& p_parser)
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
void GolBoundingVolume::FUN_1001bbb0(GolFileParser& p_parser)
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
				m_unk0x08[i].GetChildIndexSlot(j) = -2;
				break;
			case GolFileParser::e_unknown0x8c:
				m_unk0x08[i].GetChildIndexSlot(j) = -1;
				break;
			case GolFileParser::e_int:
				m_unk0x08[i].GetChildIndexSlot(j) = p_parser.GetLastInt();
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
void GolBoundingVolume::FUN_1001bd00(GolFileParser& p_parser)
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
					m_unk0x08[i].GetChildIndexSlot(j) = -1;
				}
				else if (v == -2) {
					m_unk0x08[i].GetChildIndexSlot(j) = -2;
				}
				else {
					p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				}
			}
			else {
				m_unk0x08[i].GetChildIndexSlot(j) = v;
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
undefined4 GolBoundingVolume::FUN_1001be50()
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

// FUNCTION: LEGORACERS 0x00403fa0
LegoBool32 GolBoundingVolume::FUN_00403fa0(
	GolVec3* p_start,
	GolVec3* p_end,
	Field0x0c* p_record,
	GolVec3* p_hit,
	RaceEventRecord** p_hitRecord,
	LegoFloat* p_amountOut
)
{
	GolVec3* start = p_start;
	GolVec3 delta;
	GolVec3 scaledDelta;
	LegoU32 childIndex;

	m_unk0x30 = *start;
	m_unk0x3c = *p_end;
	m_unk0x54 = p_record;
	m_unk0x58 = p_hit;
	m_unk0x5c = p_hitRecord;
	m_unk0x60 = p_amountOut;

	TraversalEntry0x0c* stack = m_unk0x2c;
	stack->m_unk0x0a = 0;
	stack->m_unk0x08 = 0;

	PolygonRange0x14* node = m_unk0x08;
	GolVec3* vertices = m_unk0x0c->GetPositions();

	for (;;) {
		LegoU32 stage = stack->m_unk0x0a;
		if (stage == 0) {
			PolygonId0x08* firstTriangle = &m_unk0x14[node->m_unk0x0c];
			GolVec3* planePoint = &vertices[firstTriangle->m_unk0x00];
			stack->m_unk0x00 = planePoint;

			delta.m_x = start->m_x - planePoint->m_x;
			delta.m_y = start->m_y - planePoint->m_y;
			delta.m_z = start->m_z - planePoint->m_z;

			LegoFloat startDistance = GolCameraBase::FUN_00404680(&node->m_unk0x00, &delta);
			stack->m_unk0x04 = startDistance;

			if (startDistance > 0.0f) {
				childIndex = node->m_unk0x10[0];
			}
			else {
				childIndex = node->m_unk0x10[1];
			}

			stack->m_unk0x0a++;
			if (childIndex < c_invalidChildIndex) {
				stack++;
				stack->m_unk0x08 = childIndex;
				stack->m_unk0x0a = 0;
				node = &m_unk0x08[childIndex];
			}
		}
		else if (stage == 1) {
			stack->m_unk0x0a++;

			GolVec3* planePoint = stack->m_unk0x00;
			delta.m_x = p_end->m_x - planePoint->m_x;
			delta.m_y = p_end->m_y - planePoint->m_y;
			delta.m_z = p_end->m_z - planePoint->m_z;

			LegoFloat endDistance = GolCameraBase::FUN_00404680(&node->m_unk0x00, &delta);
			LegoFloat startDistance = stack->m_unk0x04;

			if (endDistance <= 0.0f) {
				if (startDistance <= 0.0f) {
					continue;
				}

				m_unk0x48 = startDistance;
				m_unk0x4c = -endDistance;
				childIndex = node->m_unk0x10[1];
			}
			else {
				if (startDistance > 0.0f) {
					continue;
				}

				m_unk0x48 = -startDistance;
				m_unk0x4c = endDistance;
				childIndex = node->m_unk0x10[0];
			}

			m_unk0x50 = node;
			g_unk0x004c2728.m_x = m_unk0x3c.m_x - m_unk0x30.m_x;
			g_unk0x004c2728.m_y = m_unk0x3c.m_y - m_unk0x30.m_y;
			g_unk0x004c2728.m_z = m_unk0x3c.m_z - m_unk0x30.m_z;

			LegoFloat amount = m_unk0x48 / (m_unk0x48 + m_unk0x4c);
			GolCameraBase::FUN_004045b0(&g_unk0x004c2728, amount, &scaledDelta);
			GolCameraBase::FUN_00404550(&m_unk0x30, &scaledDelta, m_unk0x58);

			vertices = m_unk0x0c->GetPositions();
			node = m_unk0x50;

			PolygonId0x08* triangle = &m_unk0x14[node->m_unk0x0c];
			PolygonId0x08* end = triangle + node->m_unk0x0e;
			PolygonId0x08* candidate = NULL;

			node->FUN_00404660(&g_unk0x004c2718);
			m_unk0x54->m_unk0x24.m_x = g_unk0x004c2718.m_x;
			m_unk0x54->m_unk0x24.m_y = g_unk0x004c2718.m_y;
			m_unk0x54->m_unk0x24.m_z = g_unk0x004c2718.m_z;

			while (triangle < end) {
				m_unk0x54->m_unk0x00 = vertices[triangle->m_unk0x00];
				m_unk0x54->m_unk0x0c = vertices[triangle->m_unk0x02];
				m_unk0x54->m_unk0x18 = vertices[triangle->m_unk0x04];

				if (GolMath::FUN_004497f0(m_unk0x58, m_unk0x54->GetFloatData())) {
					GolCameraBase::FUN_00404580(&m_unk0x54->m_unk0x00, &m_unk0x54->m_unk0x0c, &g_unk0x004c26f8);
					GolCameraBase::FUN_00404580(&m_unk0x54->m_unk0x18, &m_unk0x54->m_unk0x0c, &g_unk0x004c2708);
					GolCameraBase::FUN_00404510(&g_unk0x004c2708, &g_unk0x004c26f8, &g_unk0x004c2718);

					if (GolCameraBase::FUN_004044f0(&g_unk0x004c2718, &g_unk0x004c2728) <= 0.0f) {
						GolMath::NormalizeVector3(g_unk0x004c2718, &g_unk0x004c2718);
						m_unk0x54->m_unk0x24.m_x = g_unk0x004c2718.m_x;
						m_unk0x54->m_unk0x24.m_y = g_unk0x004c2718.m_y;
						m_unk0x54->m_unk0x24.m_z = g_unk0x004c2718.m_z;
						m_unk0x54->m_unk0x30 =
							-(m_unk0x54->m_unk0x00.m_z * g_unk0x004c2718.m_z +
							  m_unk0x54->m_unk0x00.m_y * g_unk0x004c2718.m_y +
							  m_unk0x54->m_unk0x00.m_x * g_unk0x004c2718.m_x);

						if (m_unk0x5c) {
							*m_unk0x5c = static_cast<RaceEventRecord*>(m_unk0x24->m_entries[triangle->m_unk0x06]);
						}

						if (m_unk0x60) {
							*m_unk0x60 = amount;
							return TRUE;
						}

						goto successReturn;
					}

					candidate = triangle;
				}

				triangle++;
			}

			if (candidate) {
				m_unk0x54->m_unk0x00 = vertices[candidate->m_unk0x00];
				m_unk0x54->m_unk0x0c = vertices[candidate->m_unk0x02];
				m_unk0x54->m_unk0x18 = vertices[candidate->m_unk0x04];

				GolMath::NormalizeVector3(g_unk0x004c2718, &g_unk0x004c2718);
				m_unk0x54->m_unk0x24.m_x = g_unk0x004c2718.m_x;
				m_unk0x54->m_unk0x24.m_y = g_unk0x004c2718.m_y;
				m_unk0x54->m_unk0x24.m_z = g_unk0x004c2718.m_z;
				m_unk0x54->m_unk0x30 =
					-(m_unk0x54->m_unk0x00.m_z * g_unk0x004c2718.m_z + m_unk0x54->m_unk0x00.m_y * g_unk0x004c2718.m_y +
					  m_unk0x54->m_unk0x00.m_x * g_unk0x004c2718.m_x);

				if (m_unk0x5c) {
					*m_unk0x5c = static_cast<RaceEventRecord*>(m_unk0x24->m_entries[candidate->m_unk0x06]);
				}

				if (m_unk0x60) {
					*m_unk0x60 = amount;
				}

				goto successReturn;
			}

			if (childIndex < c_invalidChildIndex) {
				stack++;
				stack->m_unk0x08 = childIndex;
				stack->m_unk0x0a = 0;
				node = &m_unk0x08[childIndex];
			}

			start = p_start;
		}
		else {
			stack--;
			if (stack < m_unk0x2c) {
				return FALSE;
			}

			node = &m_unk0x08[stack->m_unk0x08];
		}
	}

successReturn:
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004045e0
void GolBoundingVolume::FUN_004045e0()
{
	LegoU32 i;
	for (i = 0; i < m_unk0x04; i++) {
		m_unk0x08[i].m_unk0x00.m_y = -m_unk0x08[i].m_unk0x00.m_y;
	}

	GolVec3* vertices = m_unk0x0c->GetPositions();
	for (i = 0; i < m_unk0x0c->GetCount(); i++) {
		vertices[i].m_y = -vertices[i].m_y;
	}

	for (i = 0; i < m_unk0x10; i++) {
		LegoU16 value = m_unk0x14[i].m_unk0x02;
		m_unk0x14[i].m_unk0x02 = m_unk0x14[i].m_unk0x04;
		m_unk0x14[i].m_unk0x04 = value;
	}
}

// FUNCTION: LEGORACERS 0x00404660
GolVec3* GolBoundingVolume::PolygonRange0x14::FUN_00404660(GolVec3* p_dest) const
{
	p_dest->m_x = m_unk0x00.m_x;
	p_dest->m_y = m_unk0x00.m_y;
	p_dest->m_z = m_unk0x00.m_z;

	return p_dest;
}
