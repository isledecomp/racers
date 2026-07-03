#include "golboundingvolume.h"

#include "gdbvertexarray.h"
#include "golbinparser.h"
#include "golcamerabase.h"
#include "golerror.h"
#include "golmath.h"

DECOMP_SIZE_ASSERT(GolBoundingVolume::HitTriangle, 0x34)
DECOMP_SIZE_ASSERT(GolBoundingVolume::Triangle, 0x08)
DECOMP_SIZE_ASSERT(GolBoundingVolume::BspNode, 0x14)
DECOMP_SIZE_ASSERT(GolBoundingVolume::TraversalEntry, 0x0c)
DECOMP_SIZE_ASSERT(GolBoundingVolume, 0x64)
DECOMP_SIZE_ASSERT(GolBoundingVolume::BvbTxtParser, 0x1fc)

// GLOBAL: LEGORACERS 0x004c26f8
GolVec3 g_edge0;

// GLOBAL: LEGORACERS 0x004c2704
undefined4 g_unk0x004c2704;

// GLOBAL: LEGORACERS 0x004c2708
GolVec3 g_edge1;

// GLOBAL: LEGORACERS 0x004c2714
undefined4 g_unk0x004c2714;

// GLOBAL: LEGORACERS 0x004c2718
GolVec3 g_hitNormal;

// GLOBAL: LEGORACERS 0x004c2724
undefined4 g_unk0x004c2724;

// GLOBAL: LEGORACERS 0x004c2728
GolVec3 g_segmentDelta;

// FUNCTION: GOLDP 0x1001b770
GolBoundingVolume::GolBoundingVolume() : m_activeMaterialTable(&m_materialTable)
{
	m_nodeCount = 0;
	m_nodes = NULL;
	m_vertices = NULL;
	m_triangleCount = 0;
	m_triangles = NULL;
	m_traversalDepth = 0;
	m_traversalStack = NULL;
}

// FUNCTION: GOLDP 0x1001b7b0
GolBoundingVolume::~GolBoundingVolume()
{
	Destroy();
}

// FUNCTION: GOLDP 0x1001b800
void GolBoundingVolume::Load(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_nodes != NULL) {
		Destroy();
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
		case c_bvbMaterials:
			if (m_materialTable.GetRenderer() != NULL) {
				parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
			}
			m_materialTable.Parse(p_renderer, *parser);
			break;
		case c_bvbVertices:
			if (m_vertices != 0) {
				parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
			}
			m_vertices = new GdbVertexArray;
			if (m_vertices == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			m_vertices->Parse(*parser);
			break;
		case c_bvbTriangles:
			ParseTriangles(*parser);
			break;
		case c_bvbNodes:
			ParseNodes(*parser);
			break;
		case c_bvbNodesFixedPoint:
			ParseNodesFixedPoint(*parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}
	}
	if (m_nodeCount != 0) {
		m_traversalDepth = ComputeTraversalDepth();
		m_traversalStack = new TraversalEntry[m_traversalDepth];
		if (m_traversalStack == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x1001ba90
void GolBoundingVolume::Destroy()
{
	if (m_nodes != NULL) {
		if (m_vertices != NULL) {
			m_vertices->Destroy();
			if (m_vertices != NULL) {
				delete m_vertices;
			}
		}
		if (m_triangles != NULL) {
			delete[] m_triangles;
		}
		if (m_nodes != NULL) {
			delete[] m_nodes;
		}
		if (m_traversalStack != NULL) {
			delete[] m_traversalStack;
		}
		m_nodeCount = 0;
		m_nodes = NULL;
		m_vertices = 0;
		m_triangleCount = 0;
		m_triangles = NULL;
		m_activeMaterialTable = &m_materialTable;
		m_traversalDepth = 0;
		m_traversalStack = NULL;
	}
}

// FUNCTION: GOLDP 0x1001bb10
void GolBoundingVolume::ParseTriangles(GolFileParser& p_parser)
{
	LegoU32 i;

	m_triangleCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_triangleCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_triangles = new Triangle[m_triangleCount];
	if (m_triangles == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_triangleCount; i++) {
		m_triangles[i].m_vertex0 = p_parser.ReadInteger();
		m_triangles[i].m_vertex1 = p_parser.ReadInteger();
		m_triangles[i].m_vertex2 = p_parser.ReadInteger();
		m_triangles[i].m_materialIndex = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001bbb0
void GolBoundingVolume::ParseNodes(GolFileParser& p_parser)
{
	LegoU32 i;

	m_nodeCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_nodeCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_nodes = new BspNode[m_nodeCount];
	if (m_nodes == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_nodeCount; i++) {
		LegoU32 j;
		for (j = 0; j < 2; j++) {
			switch (p_parser.GetNextToken()) {
			case c_bvbChildLeaf:
				m_nodes[i].GetChildIndexSlot(j) = -2;
				break;
			case c_bvbChildNone:
				m_nodes[i].GetChildIndexSlot(j) = -1;
				break;
			case GolFileParser::e_int:
				m_nodes[i].GetChildIndexSlot(j) = p_parser.GetLastInt();
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
		GolVec3* ptrVec = &m_nodes[i].m_planeNormal;
		ptrVec->m_x = v.m_x;
		ptrVec->m_y = v.m_y;
		ptrVec->m_z = v.m_z;
		m_nodes[i].m_firstTriangle = p_parser.ReadInteger();
		m_nodes[i].m_triangleCount = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001bd00
void GolBoundingVolume::ParseNodesFixedPoint(GolFileParser& p_parser)
{
	LegoU32 i;

	m_nodeCount = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_nodeCount == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}
	m_nodes = new BspNode[m_nodeCount];
	if (m_nodes == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	for (i = 0; i < m_nodeCount; i++) {
		LegoU32 j;
		for (j = 0; j < 2; j++) {
			LegoS32 v = p_parser.ReadInteger();
			if (v < 0) {
				if (v == -1) {
					m_nodes[i].GetChildIndexSlot(j) = -1;
				}
				else if (v == -2) {
					m_nodes[i].GetChildIndexSlot(j) = -2;
				}
				else {
					p_parser.HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				}
			}
			else {
				m_nodes[i].GetChildIndexSlot(j) = v;
			}
		}
		int i3[3];
		i3[0] = p_parser.ReadInteger();
		i3[1] = p_parser.ReadInteger();
		i3[2] = p_parser.ReadInteger();
		GolVec3* ptrVec = &m_nodes[i].m_planeNormal;
		ptrVec->m_x = static_cast<float>(i3[0]) / static_cast<float>(0x40000000);
		ptrVec->m_y = static_cast<float>(i3[1]) / static_cast<float>(0x40000000);
		ptrVec->m_z = static_cast<float>(i3[2]) / static_cast<float>(0x40000000);
		m_nodes[i].m_firstTriangle = p_parser.ReadInteger();
		m_nodes[i].m_triangleCount = p_parser.ReadInteger();
	}
	p_parser.ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001be50
undefined4 GolBoundingVolume::ComputeTraversalDepth()
{
	LegoU16* stack = new LegoU16[m_nodeCount];
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
		BspNode* obj = &m_nodes[index];
		if (stackSize > maxStackSize) {
			maxStackSize = stackSize;
		}

		LegoU32 rightIndex = obj->m_childIndices[1];
		if (prevIndex != rightIndex) {
			LegoU32 leftIndex = obj->m_childIndices[0];
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
LegoBool32 GolBoundingVolume::IntersectSegment(
	GolVec3* p_start,
	GolVec3* p_end,
	HitTriangle* p_record,
	GolVec3* p_hit,
	RaceEventRecord** p_hitRecord,
	LegoFloat* p_amountOut
)
{
	GolVec3* start = p_start;
	GolVec3 delta;
	GolVec3 scaledDelta;
	LegoU32 childIndex;

	m_segmentStart = *start;
	m_segmentEnd = *p_end;
	m_hitTriangle = p_record;
	m_hitPoint = p_hit;
	m_hitRecord = p_hitRecord;
	m_hitAmount = p_amountOut;

	TraversalEntry* stack = m_traversalStack;
	stack->m_stage = 0;
	stack->m_nodeIndex = 0;

	BspNode* node = m_nodes;
	GolVec3* vertices = m_vertices->GetPositions();

	for (;;) {
		LegoU32 stage = stack->m_stage;
		if (stage == 0) {
			Triangle* firstTriangle = &m_triangles[node->m_firstTriangle];
			GolVec3* planePoint = &vertices[firstTriangle->m_vertex0];
			stack->m_planePoint = planePoint;

			delta.m_x = start->m_x - planePoint->m_x;
			delta.m_y = start->m_y - planePoint->m_y;
			delta.m_z = start->m_z - planePoint->m_z;

			LegoFloat startDistance = GolCameraBase::Dot(&node->m_planeNormal, &delta);
			stack->m_startDistance = startDistance;

			if (startDistance > 0.0f) {
				childIndex = node->m_childIndices[0];
			}
			else {
				childIndex = node->m_childIndices[1];
			}

			stack->m_stage++;
			if (childIndex < c_invalidChildIndex) {
				stack++;
				stack->m_nodeIndex = childIndex;
				stack->m_stage = 0;
				node = &m_nodes[childIndex];
			}
		}
		else if (stage == 1) {
			stack->m_stage++;

			GolVec3* planePoint = stack->m_planePoint;
			delta.m_x = p_end->m_x - planePoint->m_x;
			delta.m_y = p_end->m_y - planePoint->m_y;
			delta.m_z = p_end->m_z - planePoint->m_z;

			LegoFloat endDistance = GolCameraBase::Dot(&node->m_planeNormal, &delta);
			LegoFloat startDistance = stack->m_startDistance;

			if (endDistance <= 0.0f) {
				if (startDistance <= 0.0f) {
					continue;
				}

				m_startDistance = startDistance;
				m_endDistance = -endDistance;
				childIndex = node->m_childIndices[1];
			}
			else {
				if (startDistance > 0.0f) {
					continue;
				}

				m_startDistance = -startDistance;
				m_endDistance = endDistance;
				childIndex = node->m_childIndices[0];
			}

			m_hitNode = node;
			g_segmentDelta.m_x = m_segmentEnd.m_x - m_segmentStart.m_x;
			g_segmentDelta.m_y = m_segmentEnd.m_y - m_segmentStart.m_y;
			g_segmentDelta.m_z = m_segmentEnd.m_z - m_segmentStart.m_z;

			LegoFloat amount = m_startDistance / (m_startDistance + m_endDistance);
			GolCameraBase::Scale(&g_segmentDelta, amount, &scaledDelta);
			GolCameraBase::Add(&m_segmentStart, &scaledDelta, m_hitPoint);

			vertices = m_vertices->GetPositions();
			node = m_hitNode;

			Triangle* triangle = &m_triangles[node->m_firstTriangle];
			Triangle* end = triangle + node->m_triangleCount;
			Triangle* candidate = NULL;

			node->GetPlaneNormal(&g_hitNormal);
			m_hitTriangle->m_normal.m_x = g_hitNormal.m_x;
			m_hitTriangle->m_normal.m_y = g_hitNormal.m_y;
			m_hitTriangle->m_normal.m_z = g_hitNormal.m_z;

			while (triangle < end) {
				m_hitTriangle->m_vertex0 = vertices[triangle->m_vertex0];
				m_hitTriangle->m_vertex1 = vertices[triangle->m_vertex1];
				m_hitTriangle->m_vertex2 = vertices[triangle->m_vertex2];

				if (GolMath::PointInTriangle(m_hitPoint, m_hitTriangle->GetFloatData())) {
					GolCameraBase::Subtract(&m_hitTriangle->m_vertex0, &m_hitTriangle->m_vertex1, &g_edge0);
					GolCameraBase::Subtract(&m_hitTriangle->m_vertex2, &m_hitTriangle->m_vertex1, &g_edge1);
					GolCameraBase::Cross(&g_edge1, &g_edge0, &g_hitNormal);

					if (GolCameraBase::Dot2(&g_hitNormal, &g_segmentDelta) <= 0.0f) {
						GolMath::NormalizeVector3(g_hitNormal, &g_hitNormal);
						m_hitTriangle->m_normal.m_x = g_hitNormal.m_x;
						m_hitTriangle->m_normal.m_y = g_hitNormal.m_y;
						m_hitTriangle->m_normal.m_z = g_hitNormal.m_z;
						m_hitTriangle->m_planeDistance =
							-(m_hitTriangle->m_vertex0.m_z * g_hitNormal.m_z +
							  m_hitTriangle->m_vertex0.m_y * g_hitNormal.m_y +
							  m_hitTriangle->m_vertex0.m_x * g_hitNormal.m_x);

						if (m_hitRecord) {
							*m_hitRecord = static_cast<RaceEventRecord*>(
								m_activeMaterialTable->m_entries[triangle->m_materialIndex]
							);
						}

						if (m_hitAmount) {
							*m_hitAmount = amount;
							return TRUE;
						}

						goto successReturn;
					}

					candidate = triangle;
				}

				triangle++;
			}

			if (candidate) {
				m_hitTriangle->m_vertex0 = vertices[candidate->m_vertex0];
				m_hitTriangle->m_vertex1 = vertices[candidate->m_vertex1];
				m_hitTriangle->m_vertex2 = vertices[candidate->m_vertex2];

				GolMath::NormalizeVector3(g_hitNormal, &g_hitNormal);
				m_hitTriangle->m_normal.m_x = g_hitNormal.m_x;
				m_hitTriangle->m_normal.m_y = g_hitNormal.m_y;
				m_hitTriangle->m_normal.m_z = g_hitNormal.m_z;
				m_hitTriangle->m_planeDistance =
					-(m_hitTriangle->m_vertex0.m_z * g_hitNormal.m_z + m_hitTriangle->m_vertex0.m_y * g_hitNormal.m_y +
					  m_hitTriangle->m_vertex0.m_x * g_hitNormal.m_x);

				if (m_hitRecord) {
					*m_hitRecord =
						static_cast<RaceEventRecord*>(m_activeMaterialTable->m_entries[candidate->m_materialIndex]);
				}

				if (m_hitAmount) {
					*m_hitAmount = amount;
				}

				goto successReturn;
			}

			if (childIndex < c_invalidChildIndex) {
				stack++;
				stack->m_nodeIndex = childIndex;
				stack->m_stage = 0;
				node = &m_nodes[childIndex];
			}

			start = p_start;
		}
		else {
			stack--;
			if (stack < m_traversalStack) {
				return FALSE;
			}

			node = &m_nodes[stack->m_nodeIndex];
		}
	}

successReturn:
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004045e0
void GolBoundingVolume::MirrorY()
{
	LegoU32 i;
	for (i = 0; i < m_nodeCount; i++) {
		m_nodes[i].m_planeNormal.m_y = -m_nodes[i].m_planeNormal.m_y;
	}

	GolVec3* vertices = m_vertices->GetPositions();
	for (i = 0; i < m_vertices->GetCount(); i++) {
		vertices[i].m_y = -vertices[i].m_y;
	}

	for (i = 0; i < m_triangleCount; i++) {
		LegoU16 value = m_triangles[i].m_vertex1;
		m_triangles[i].m_vertex1 = m_triangles[i].m_vertex2;
		m_triangles[i].m_vertex2 = value;
	}
}

// FUNCTION: LEGORACERS 0x00404660
GolVec3* GolBoundingVolume::BspNode::GetPlaneNormal(GolVec3* p_dest) const
{
	p_dest->m_x = m_planeNormal.m_x;
	p_dest->m_y = m_planeNormal.m_y;
	p_dest->m_z = m_planeNormal.m_z;

	return p_dest;
}
