#include "golboundingshape.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golviewfrustum.h"

DECOMP_SIZE_ASSERT(GolBoundingShape::BdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(GolBoundingShape::TreeNode, 0x20)
DECOMP_SIZE_ASSERT(GolBoundingShape::TreeNode::Node, 0x1c)
DECOMP_SIZE_ASSERT(GolBoundingShape::TreeNode::Payload, 0x1c)
DECOMP_SIZE_ASSERT(GolBoundingShape::Bounds, 0x18)
DECOMP_SIZE_ASSERT(GolBoundingShape, 0x2c)

static LegoFloat PlaneDot(const GolBoundingShape::TreeNode* p_entry, const GolVec3& p_point)
{
	return p_entry->m_unk0x04.m_t0.m_unk0x08 * p_point.m_z + p_entry->m_unk0x04.m_t0.m_unk0x04 * p_point.m_y +
		   p_entry->m_unk0x04.m_t0.m_unk0x00 * p_point.m_x;
}

static LegoBool32 HasPositiveCorner(const GolBoundingShape::TreeNode* p_entry, const GolViewFrustum* p_frustum)
{
	LegoFloat threshold = -p_entry->m_unk0x04.m_t0.m_unk0x0c;
	return PlaneDot(p_entry, p_frustum->m_corners[0]) >= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[3]) >= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[1]) >= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[2]) >= threshold;
}

static LegoBool32 HasNegativeCorner(const GolBoundingShape::TreeNode* p_entry, const GolViewFrustum* p_frustum)
{
	LegoFloat threshold = -p_entry->m_unk0x04.m_t0.m_unk0x0c;
	return PlaneDot(p_entry, p_frustum->m_corners[0]) <= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[3]) <= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[1]) <= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[2]) <= threshold;
}

// FUNCTION: GOLDP 0x1001adc0
GolBoundingShape::GolBoundingShape()
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
GolBoundingShape::~GolBoundingShape()
{
	Destroy();
}

// FUNCTION: GOLDP 0x1001ae50
void GolBoundingShape::Deserialize(const LegoChar* p_path, LegoBool32 p_binary)
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
			m_unk0x1c = parser->ReadBracketedCountAndLeftCurly();
			if (m_unk0x1c == 0) {
				parser->HandleUnexpectedToken(GolFileParser::ParserTokenType::e_int);
			}

			m_unk0x20 = new LegoU16[m_unk0x1c];
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
void GolBoundingShape::FUN_1001b010(GolFileParser& p_parser)
{
	LegoU32 i;

	m_unk0x04 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x04 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::ParserTokenType::e_int);
	}

	m_unk0x0c = m_unk0x08 = new TreeNode[m_unk0x04];
	if (m_unk0x08 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_unk0x04; i++) {
		GolFileParser::ParserTokenType type = p_parser.GetNextToken();
		TreeNode* obj = &m_unk0x08[i];

		if (type == GolFileParser::e_unknown0x28) {
			obj->m_type = TreeNode::e_type0;
			obj->m_unk0x04.m_t0.m_unk0x10 = 0;
			obj->m_unk0x04.m_t0.m_unk0x14 = 0;

			if (p_parser.ReadInteger() < 0) {
				obj->m_unk0x02 = TreeNode::c_invalidIndex;
				m_unk0x0c = obj;
			}
			else {
				obj->m_unk0x02 = p_parser.GetLastInt();
			}

			if (p_parser.ReadInteger() < 0) {
				obj->m_unk0x04.m_t0.m_unk0x18 = TreeNode::c_invalidIndex;
			}
			else {
				obj->m_unk0x04.m_t0.m_unk0x18 = p_parser.GetLastInt();
			}

			if (p_parser.ReadInteger() < 0) {
				obj->m_unk0x04.m_t0.m_unk0x1a = TreeNode::c_invalidIndex;
				if (obj->m_unk0x04.m_t0.m_unk0x18 == TreeNode::c_invalidIndex) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuported);
				}
			}
			else {
				obj->m_unk0x04.m_t0.m_unk0x1a = p_parser.GetLastInt();
			}

			obj->m_unk0x04.m_t0.m_unk0x00 = p_parser.ReadFloat();
			obj->m_unk0x04.m_t0.m_unk0x04 = p_parser.ReadFloat();
			obj->m_unk0x04.m_t0.m_unk0x08 = p_parser.ReadFloat();
			obj->m_unk0x04.m_t0.m_unk0x0c = p_parser.ReadFloat();
		}
		else if (type == GolFileParser::e_unknown0x29) {
			obj->m_type = TreeNode::e_type1;

			if (p_parser.ReadInteger() < 0) {
				obj->m_unk0x02 = TreeNode::c_invalidIndex;
				m_unk0x0c = obj;
			}
			else {
				obj->m_unk0x02 = p_parser.GetLastInt();
			}

			obj->m_unk0x04.m_t1.m_unk0x00 = p_parser.ReadInteger();
			obj->m_unk0x04.m_t1.m_unk0x04 = p_parser.ReadInteger();
			obj->m_unk0x04.m_t1.m_unk0x18 = p_parser.ReadInteger();
			obj->m_unk0x04.m_t1.m_unk0x14 = p_parser.ReadInteger();
			obj->m_unk0x04.m_t1.m_unk0x16 = p_parser.ReadInteger();
		}
		else {
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001b1a0
void GolBoundingShape::FUN_1001b1a0(GolFileParser& p_parser)
{
	LegoS32 i;

	m_unk0x14 = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_unk0x14 == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::ParserTokenType::e_int);
	}

	m_unk0x18 = new Bounds[m_unk0x14];
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
void GolBoundingShape::Destroy()
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

// FUNCTION: LEGORACERS 0x00403f20
void GolBoundingShape::FUN_00403f20()
{
	LegoU32 i;
	for (i = 0; i < m_unk0x04; i++) {
		TreeNode* entry = &m_unk0x08[i];
		if (entry->m_type == TreeNode::e_type0) {
			entry->m_unk0x04.m_t0.m_unk0x04 = -entry->m_unk0x04.m_t0.m_unk0x04;
		}
	}

	LegoS32 j;
	for (j = 0; j < m_unk0x14; j++) {
		m_unk0x18[j].m_unk0x04 = -m_unk0x18[j].m_unk0x04;
		m_unk0x18[j].m_unk0x10 = -m_unk0x18[j].m_unk0x10;
	}
}

// STUB: GOLDP 0x1001b2c0
void GolBoundingShape::FUN_1001b2c0(const GolViewFrustum* p_frustum, TreeNode::Node** p_first, TreeNode::Node** p_last)
{
	m_unk0x10++;
	LegoU32 stamp = m_unk0x10;
	TreeNode* entry = m_unk0x0c;

	while (entry->m_type == TreeNode::e_type0) {
		LegoFloat distance = PlaneDot(entry, p_frustum->m_position) + entry->m_unk0x04.m_t0.m_unk0x0c;
		LegoU16 childIndex;

		if (distance >= 0.0f || entry->m_unk0x04.m_t0.m_unk0x1a == TreeNode::c_invalidIndex) {
			if (entry->m_unk0x04.m_t0.m_unk0x18 == TreeNode::c_invalidIndex) {
				entry->m_unk0x04.m_t0.m_unk0x14 = stamp;
				childIndex = entry->m_unk0x04.m_t0.m_unk0x1a;
			}
			else {
				entry->m_unk0x04.m_t0.m_unk0x10 = stamp;
				childIndex = entry->m_unk0x04.m_t0.m_unk0x18;
			}
		}
		else {
			entry->m_unk0x04.m_t0.m_unk0x14 = stamp;
			childIndex = entry->m_unk0x04.m_t0.m_unk0x1a;
		}

		entry = &m_unk0x08[childIndex];
	}

	entry->m_unk0x04.m_node.m_next = NULL;
	entry->m_unk0x04.m_node.m_previous = NULL;
	entry->m_unk0x04.m_node.m_unk0x1a = 1;

	if (entry->m_unk0x02 == TreeNode::c_invalidIndex) {
		m_unk0x24 = &entry->m_unk0x04.m_node;
		m_unk0x28 = &entry->m_unk0x04.m_node;
		*p_first = &entry->m_unk0x04.m_node;
		*p_last = &entry->m_unk0x04.m_node;
		return;
	}

	if (m_unk0x20 != NULL) {
		FUN_1001b640(p_frustum, entry, p_first, p_last);
		m_unk0x24 = *p_first;
		m_unk0x28 = *p_last;
		return;
	}

	TreeNode* firstEntry = entry;
	TreeNode* lastEntry = entry;
	LegoU16 nextIndex = entry->m_unk0x02;

	while (nextIndex != TreeNode::c_invalidIndex) {
		TreeNode* current = &m_unk0x08[nextIndex];
		LegoBool32 advanced = TRUE;

		while (advanced) {
			advanced = FALSE;

			while (current->m_type == TreeNode::e_type0) {
				LegoU16 childIndex = TreeNode::c_invalidIndex;

				if (current->m_unk0x04.m_t0.m_unk0x10 != stamp) {
					if (current->m_unk0x04.m_t0.m_unk0x14 == stamp) {
						current->m_unk0x04.m_t0.m_unk0x10 = stamp;
						if (current->m_unk0x04.m_t0.m_unk0x18 != TreeNode::c_invalidIndex &&
							HasPositiveCorner(current, p_frustum)) {
							childIndex = current->m_unk0x04.m_t0.m_unk0x18;
						}
					}
					else if (PlaneDot(current, p_frustum->m_position) >= -current->m_unk0x04.m_t0.m_unk0x0c) {
						current->m_unk0x04.m_t0.m_unk0x10 = stamp;
						if (current->m_unk0x04.m_t0.m_unk0x18 != TreeNode::c_invalidIndex) {
							childIndex = current->m_unk0x04.m_t0.m_unk0x18;
						}
					}
					else {
						current->m_unk0x04.m_t0.m_unk0x14 = stamp;
						if (current->m_unk0x04.m_t0.m_unk0x1a != TreeNode::c_invalidIndex) {
							childIndex = current->m_unk0x04.m_t0.m_unk0x1a;
						}
					}

					if (childIndex != TreeNode::c_invalidIndex) {
						current = &m_unk0x08[childIndex];
						continue;
					}
				}

				if (current->m_unk0x04.m_t0.m_unk0x14 != stamp) {
					current->m_unk0x04.m_t0.m_unk0x14 = stamp;
					if (current->m_unk0x04.m_t0.m_unk0x1a != TreeNode::c_invalidIndex &&
						HasNegativeCorner(current, p_frustum)) {
						current = &m_unk0x08[current->m_unk0x04.m_t0.m_unk0x1a];
						continue;
					}
				}

				nextIndex = current->m_unk0x02;
				break;
			}

			if (current->m_type != TreeNode::e_type0) {
				current->m_unk0x04.m_node.m_unk0x1a = 1;
				LegoBool32 append = TRUE;

				if (current->m_unk0x04.m_node.m_unk0x18 != TreeNode::c_invalidIndex) {
					LegoS32 classification = GolViewFrustum::FUN_1002bc90(
						p_frustum,
						3 * current->m_unk0x04.m_node.m_unk0x18,
						&m_unk0x18[current->m_unk0x04.m_node.m_unk0x18].m_unk0x00
					);
					if (classification == 0) {
						append = FALSE;
					}
					else if (classification == 2) {
						current->m_unk0x04.m_node.m_unk0x1a = 0;
					}
				}

				if (append) {
					lastEntry->m_unk0x04.m_node.m_next = &current->m_unk0x04.m_node;
					current->m_unk0x04.m_node.m_previous = &lastEntry->m_unk0x04.m_node;
					current->m_unk0x04.m_node.m_next = NULL;
					lastEntry = current;
				}

				nextIndex = current->m_unk0x02;
				advanced = nextIndex != TreeNode::c_invalidIndex;
				if (advanced) {
					current = &m_unk0x08[nextIndex];
				}
			}
		}
	}

	m_unk0x24 = &firstEntry->m_unk0x04.m_node;
	*p_first = &firstEntry->m_unk0x04.m_node;
	m_unk0x28 = &lastEntry->m_unk0x04.m_node;
	*p_last = &lastEntry->m_unk0x04.m_node;
}

// STUB: GOLDP 0x1001b640
void GolBoundingShape::FUN_1001b640(
	const GolViewFrustum* p_frustum,
	TreeNode* p_entry,
	TreeNode::Node** p_first,
	TreeNode::Node** p_last
)
{
	LegoS16 indexListStart = p_entry->m_unk0x04.m_node.m_unk0x14;
	TreeNode::Node* first = &p_entry->m_unk0x04.m_node;
	p_entry->m_unk0x04.m_node.m_next = NULL;
	p_entry->m_unk0x04.m_node.m_previous = NULL;

	if (indexListStart < 0 || p_entry->m_unk0x04.m_node.m_unk0x16 == 0) {
		*p_last = first;
		*p_first = first;
		return;
	}

	TreeNode* previous = p_entry;
	LegoS32 i = 0;
	LegoU16* childIndex = &m_unk0x20[indexListStart];

	while (i < p_entry->m_unk0x04.m_node.m_unk0x16) {
		TreeNode* child = &m_unk0x08[*childIndex];
		child->m_unk0x04.m_node.m_unk0x1a = 1;

		if (child->m_unk0x04.m_node.m_unk0x18 == TreeNode::c_invalidIndex) {
			previous->m_unk0x04.m_node.m_next = &child->m_unk0x04.m_node;
			child->m_unk0x04.m_node.m_previous = &previous->m_unk0x04.m_node;
			child->m_unk0x04.m_node.m_next = NULL;
			previous = child;
		}
		else {
			LegoS32 classification =
				GolViewFrustum::FUN_1002bc90(p_frustum, 0, &m_unk0x18[child->m_unk0x04.m_node.m_unk0x18].m_unk0x00);
			if (classification != 0) {
				if (classification == 2) {
					child->m_unk0x04.m_node.m_unk0x1a = 0;
				}

				previous->m_unk0x04.m_node.m_next = &child->m_unk0x04.m_node;
				child->m_unk0x04.m_node.m_previous = &previous->m_unk0x04.m_node;
				child->m_unk0x04.m_node.m_next = NULL;
				previous = child;
			}
		}

		childIndex++;
		i++;
	}

	*p_first = first;
	*p_last = &previous->m_unk0x04.m_node;
}
