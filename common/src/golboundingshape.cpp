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
	return p_entry->m_data.m_plane.m_normalZ * p_point.m_z + p_entry->m_data.m_plane.m_normalY * p_point.m_y +
		   p_entry->m_data.m_plane.m_normalX * p_point.m_x;
}

static LegoBool32 HasPositiveCorner(const GolBoundingShape::TreeNode* p_entry, const GolViewFrustum* p_frustum)
{
	LegoFloat threshold = -p_entry->m_data.m_plane.m_distance;
	return PlaneDot(p_entry, p_frustum->m_corners[0]) >= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[3]) >= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[1]) >= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[2]) >= threshold;
}

static LegoBool32 HasNegativeCorner(const GolBoundingShape::TreeNode* p_entry, const GolViewFrustum* p_frustum)
{
	LegoFloat threshold = -p_entry->m_data.m_plane.m_distance;
	return PlaneDot(p_entry, p_frustum->m_corners[0]) <= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[3]) <= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[1]) <= threshold ||
		   PlaneDot(p_entry, p_frustum->m_corners[2]) <= threshold;
}

// FUNCTION: GOLDP 0x1001adc0
GolBoundingShape::GolBoundingShape()
{
	m_nodeCount = 0;
	m_nodes = NULL;
	m_root = NULL;
	m_visitStamp = 0;
	m_boundsCount = 0;
	m_bounds = NULL;
	m_pvsIndexCount = 0;
	m_pvsIndices = NULL;
	m_firstVisibleLeaf = 0;
	m_lastVisibleLeaf = 0;
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

	if (m_nodes != NULL) {
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
		case BdbTxtParser::e_nodes:
			ParseNodes(*parser);
			break;
		case BdbTxtParser::e_bounds:
			ParseBounds(*parser);
			break;
		case BdbTxtParser::e_pvsIndices:
			m_pvsIndexCount = parser->ReadBracketedCountAndLeftCurly();
			if (m_pvsIndexCount == 0) {
				parser->HandleUnexpectedToken(GolFileParser::e_int);
			}

			m_pvsIndices = new LegoU16[m_pvsIndexCount];
			if (m_pvsIndices == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (i = 0; i < m_pvsIndexCount; i++) {
				m_pvsIndices[i] = parser->ReadInteger();
			}

			parser->ReadRightCurly();
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	parser->Dispose();
	delete parser;
}

// FUNCTION: GOLDP 0x1001b010
void GolBoundingShape::ParseNodes(GolFileParser& p_parser)
{
	LegoU32 i;

	m_nodeCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_nodeCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_root = m_nodes = new TreeNode[m_nodeCount];
	if (m_nodes == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_nodeCount; i++) {
		GolFileParser::ParserTokenType type = p_parser.GetNextToken();
		TreeNode* obj = &m_nodes[i];

		if (type == BdbTxtParser::e_plane) {
			obj->m_type = TreeNode::e_plane;
			obj->m_data.m_plane.m_frontStamp = 0;
			obj->m_data.m_plane.m_backStamp = 0;

			if (p_parser.ReadInteger() < 0) {
				obj->m_nextLeafIndex = TreeNode::c_invalidIndex;
				m_root = obj;
			}
			else {
				obj->m_nextLeafIndex = p_parser.GetLastInt();
			}

			if (p_parser.ReadInteger() < 0) {
				obj->m_data.m_plane.m_frontChild = TreeNode::c_invalidIndex;
			}
			else {
				obj->m_data.m_plane.m_frontChild = p_parser.GetLastInt();
			}

			if (p_parser.ReadInteger() < 0) {
				obj->m_data.m_plane.m_backChild = TreeNode::c_invalidIndex;
				if (obj->m_data.m_plane.m_frontChild == TreeNode::c_invalidIndex) {
					p_parser.HandleUnexpectedToken(GolFileParser::e_unsuported);
				}
			}
			else {
				obj->m_data.m_plane.m_backChild = p_parser.GetLastInt();
			}

			obj->m_data.m_plane.m_normalX = p_parser.ReadFloat();
			obj->m_data.m_plane.m_normalY = p_parser.ReadFloat();
			obj->m_data.m_plane.m_normalZ = p_parser.ReadFloat();
			obj->m_data.m_plane.m_distance = p_parser.ReadFloat();
		}
		else if (type == BdbTxtParser::e_leaf) {
			obj->m_type = TreeNode::e_leaf;

			if (p_parser.ReadInteger() < 0) {
				obj->m_nextLeafIndex = TreeNode::c_invalidIndex;
				m_root = obj;
			}
			else {
				obj->m_nextLeafIndex = p_parser.GetLastInt();
			}

			obj->m_data.m_node.m_firstGroup = p_parser.ReadInteger();
			obj->m_data.m_node.m_groupCount = p_parser.ReadInteger();
			obj->m_data.m_node.m_boundsIndex = p_parser.ReadInteger();
			obj->m_data.m_node.m_pvsStart = p_parser.ReadInteger();
			obj->m_data.m_node.m_pvsCount = p_parser.ReadInteger();
		}
		else {
			p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001b1a0
void GolBoundingShape::ParseBounds(GolFileParser& p_parser)
{
	LegoS32 i;

	m_boundsCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_boundsCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_bounds = new Bounds[m_boundsCount];
	if (m_bounds == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_boundsCount; i++) {
		m_bounds[i].m_minX = p_parser.ReadFloat();
		m_bounds[i].m_minY = p_parser.ReadFloat();
		m_bounds[i].m_minZ = p_parser.ReadFloat();
		m_bounds[i].m_maxX = p_parser.ReadFloat();
		m_bounds[i].m_maxY = p_parser.ReadFloat();
		m_bounds[i].m_maxZ = p_parser.ReadFloat();
	}

	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001b260
void GolBoundingShape::Destroy()
{
	m_nodeCount = 0;
	m_visitStamp = 0;

	if (m_nodes != NULL) {
		delete[] m_nodes;
		m_nodes = NULL;
	}

	m_boundsCount = 0;

	if (m_bounds != NULL) {
		delete[] m_bounds;
		m_bounds = NULL;
	}

	m_pvsIndexCount = 0;

	if (m_pvsIndices != NULL) {
		delete[] m_pvsIndices;
		m_pvsIndices = NULL;
	}

	m_firstVisibleLeaf = 0;
	m_lastVisibleLeaf = 0;
}

// FUNCTION: LEGORACERS 0x00403f20
void GolBoundingShape::MirrorY()
{
	LegoU32 i;
	for (i = 0; i < m_nodeCount; i++) {
		TreeNode* entry = &m_nodes[i];
		if (entry->m_type == TreeNode::e_plane) {
			entry->m_data.m_plane.m_normalY = -entry->m_data.m_plane.m_normalY;
		}
	}

	LegoS32 j;
	for (j = 0; j < m_boundsCount; j++) {
		m_bounds[j].m_minY = -m_bounds[j].m_minY;
		m_bounds[j].m_maxY = -m_bounds[j].m_maxY;
	}
}

// FUNCTION: GOLDP 0x1001b2c0
void GolBoundingShape::CollectVisibleLeaves(
	const GolViewFrustum* p_frustum,
	TreeNode::Node** p_first,
	TreeNode::Node** p_last
)
{
	m_visitStamp++;
	LegoU32 stamp = m_visitStamp;
	TreeNode* entry = m_root;

	while (entry->m_type == TreeNode::e_plane) {
		LegoFloat distance = PlaneDot(entry, p_frustum->m_position) + entry->m_data.m_plane.m_distance;
		LegoU16 childIndex;

		if (distance >= 0.0f || entry->m_data.m_plane.m_backChild == TreeNode::c_invalidIndex) {
			if (entry->m_data.m_plane.m_frontChild == TreeNode::c_invalidIndex) {
				entry->m_data.m_plane.m_backStamp = stamp;
				childIndex = entry->m_data.m_plane.m_backChild;
			}
			else {
				entry->m_data.m_plane.m_frontStamp = stamp;
				childIndex = entry->m_data.m_plane.m_frontChild;
			}
		}
		else {
			entry->m_data.m_plane.m_backStamp = stamp;
			childIndex = entry->m_data.m_plane.m_backChild;
		}

		entry = &m_nodes[childIndex];
	}

	entry->m_data.m_node.m_next = NULL;
	entry->m_data.m_node.m_previous = NULL;
	entry->m_data.m_node.m_linked = 1;

	if (entry->m_nextLeafIndex == TreeNode::c_invalidIndex) {
		m_firstVisibleLeaf = &entry->m_data.m_node;
		m_lastVisibleLeaf = &entry->m_data.m_node;
		*p_first = &entry->m_data.m_node;
		*p_last = &entry->m_data.m_node;
		return;
	}

	if (m_pvsIndices != NULL) {
		CollectLeavesFromPvs(p_frustum, entry, p_first, p_last);
		m_firstVisibleLeaf = *p_first;
		m_lastVisibleLeaf = *p_last;
		return;
	}

	TreeNode* firstEntry = entry;
	TreeNode* lastEntry = entry;
	LegoU16 nextIndex = entry->m_nextLeafIndex;

	while (nextIndex != TreeNode::c_invalidIndex) {
		TreeNode* current = &m_nodes[nextIndex];
		LegoBool32 advanced = TRUE;

		while (advanced) {
			advanced = FALSE;

			while (current->m_type == TreeNode::e_plane) {
				LegoU16 childIndex = TreeNode::c_invalidIndex;

				if (current->m_data.m_plane.m_frontStamp != stamp) {
					if (current->m_data.m_plane.m_backStamp == stamp) {
						current->m_data.m_plane.m_frontStamp = stamp;
						if (current->m_data.m_plane.m_frontChild != TreeNode::c_invalidIndex &&
							HasPositiveCorner(current, p_frustum)) {
							childIndex = current->m_data.m_plane.m_frontChild;
						}
					}
					else if (PlaneDot(current, p_frustum->m_position) >= -current->m_data.m_plane.m_distance) {
						current->m_data.m_plane.m_frontStamp = stamp;
						if (current->m_data.m_plane.m_frontChild != TreeNode::c_invalidIndex) {
							childIndex = current->m_data.m_plane.m_frontChild;
						}
					}
					else {
						current->m_data.m_plane.m_backStamp = stamp;
						if (current->m_data.m_plane.m_backChild != TreeNode::c_invalidIndex) {
							childIndex = current->m_data.m_plane.m_backChild;
						}
					}

					if (childIndex != TreeNode::c_invalidIndex) {
						current = &m_nodes[childIndex];
						continue;
					}
				}

				if (current->m_data.m_plane.m_backStamp != stamp) {
					current->m_data.m_plane.m_backStamp = stamp;
					if (current->m_data.m_plane.m_backChild != TreeNode::c_invalidIndex &&
						HasNegativeCorner(current, p_frustum)) {
						current = &m_nodes[current->m_data.m_plane.m_backChild];
						continue;
					}
				}

				nextIndex = current->m_nextLeafIndex;
				break;
			}

			if (current->m_type != TreeNode::e_plane) {
				current->m_data.m_node.m_linked = 1;
				LegoBool32 append = TRUE;

				if (current->m_data.m_node.m_boundsIndex != TreeNode::c_invalidIndex) {
					LegoS32 classification = GolViewFrustum::ClassifyBox(
						p_frustum,
						3 * current->m_data.m_node.m_boundsIndex,
						&m_bounds[current->m_data.m_node.m_boundsIndex].m_minX
					);
					if (classification == 0) {
						append = FALSE;
					}
					else if (classification == 2) {
						current->m_data.m_node.m_linked = 0;
					}
				}

				if (append) {
					lastEntry->m_data.m_node.m_next = &current->m_data.m_node;
					current->m_data.m_node.m_previous = &lastEntry->m_data.m_node;
					current->m_data.m_node.m_next = NULL;
					lastEntry = current;
				}

				nextIndex = current->m_nextLeafIndex;
				advanced = nextIndex != TreeNode::c_invalidIndex;
				if (advanced) {
					current = &m_nodes[nextIndex];
				}
			}
		}
	}

	m_firstVisibleLeaf = &firstEntry->m_data.m_node;
	*p_first = &firstEntry->m_data.m_node;
	m_lastVisibleLeaf = &lastEntry->m_data.m_node;
	*p_last = &lastEntry->m_data.m_node;
}

// FUNCTION: GOLDP 0x1001b640
void GolBoundingShape::CollectLeavesFromPvs(
	const GolViewFrustum* p_frustum,
	TreeNode* p_entry,
	TreeNode::Node** p_first,
	TreeNode::Node** p_last
)
{
	LegoS16 indexListStart = p_entry->m_data.m_node.m_pvsStart;
	TreeNode::Node* first = &p_entry->m_data.m_node;
	p_entry->m_data.m_node.m_next = NULL;
	p_entry->m_data.m_node.m_previous = NULL;

	if (indexListStart < 0 || p_entry->m_data.m_node.m_pvsCount == 0) {
		*p_last = first;
		*p_first = first;
		return;
	}

	TreeNode* previous = p_entry;
	LegoS32 i = 0;
	LegoU16* childIndex = &m_pvsIndices[indexListStart];

	while (i < p_entry->m_data.m_node.m_pvsCount) {
		TreeNode* child = &m_nodes[*childIndex];
		child->m_data.m_node.m_linked = 1;

		if (child->m_data.m_node.m_boundsIndex == TreeNode::c_invalidIndex) {
			previous->m_data.m_node.m_next = &child->m_data.m_node;
			child->m_data.m_node.m_previous = &previous->m_data.m_node;
			child->m_data.m_node.m_next = NULL;
			previous = child;
		}
		else {
			LegoS32 classification =
				GolViewFrustum::ClassifyBox(p_frustum, 0, &m_bounds[child->m_data.m_node.m_boundsIndex].m_minX);
			if (classification != 0) {
				if (classification == 2) {
					child->m_data.m_node.m_linked = 0;
				}

				previous->m_data.m_node.m_next = &child->m_data.m_node;
				child->m_data.m_node.m_previous = &previous->m_data.m_node;
				child->m_data.m_node.m_next = NULL;
				previous = child;
			}
		}

		childIndex++;
		i++;
	}

	*p_first = first;
	*p_last = &previous->m_data.m_node;
}
