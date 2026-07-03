#include "core/gol.h"
#include "decomp.h"
#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golboundingshape.h"
#include "golcollidableentity.h"
#include "golmaterial.h"
#include "golmodelbase.h"
#include "race/racesession.h"
#include "render/golrenderdevice.h"
#include "util/decalgeometry.h"

#include <float.h>

DECOMP_SIZE_ASSERT(RaceDecalManager::Trail::Decal, 0x11c)
DECOMP_SIZE_ASSERT(RaceDecalManager::Trail::Decal::FloatBits, 0x04)
DECOMP_SIZE_ASSERT(RaceDecalManager::Trail::Decal::ProjectedCoordinates, 0x08)
DECOMP_SIZE_ASSERT(RaceDecalManager::Trail::Decal::ProjectedVertex, 0x20)

// GLOBAL: LEGORACERS 0x004c47a8
GolVec3 g_decalQueryPoints[5];

// GLOBAL: LEGORACERS 0x004c3de8
LegoFloat g_decalUAxisX;

// GLOBAL: LEGORACERS 0x004c3dec
LegoFloat g_decalVAxisX;

// GLOBAL: LEGORACERS 0x004c3df4
LegoFloat g_decalWAxisX;

// GLOBAL: LEGORACERS 0x004c3df8
LegoFloat g_decalUAxisY;

// GLOBAL: LEGORACERS 0x004c3dfc
LegoFloat g_decalVAxisY;

// GLOBAL: LEGORACERS 0x004c3e04
LegoFloat g_decalWAxisY;

// GLOBAL: LEGORACERS 0x004c3e08
LegoFloat g_decalUAxisZ;

// GLOBAL: LEGORACERS 0x004c3e0c
LegoFloat g_decalVAxisZ;

// GLOBAL: LEGORACERS 0x004c3e14
LegoFloat g_decalWAxisZ;

// GLOBAL: LEGORACERS 0x004c3e18
LegoFloat g_decalUOffset;

// GLOBAL: LEGORACERS 0x004c3e1c
LegoFloat g_decalVOffset;

// GLOBAL: LEGORACERS 0x004c3e24
LegoFloat g_decalWOffset;

// GLOBAL: LEGORACERS 0x004c3e28
RaceDecalManager::Trail::Decal::ProjectedVertex g_decalProjectedVertices[76];

DECOMP_SIZE_ASSERT(DecalGeometry, 0x114)

// GLOBAL: LEGORACERS 0x004af90c
const LegoFloat g_decalGeometryMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004af910
const LegoFloat g_decalGeometryDefaultDepth = 20.0f;

// GLOBAL: LEGORACERS 0x004af914
const LegoFloat g_decalGeometryDefaultLift = 0.4f;

extern LegoFloat g_decalWAxisX;
extern LegoFloat g_decalWAxisY;
extern LegoFloat g_decalWAxisZ;
extern LegoFloat g_decalWOffset;

// FUNCTION: LEGORACERS 0x00403cc0
void GolBoundingShape::CollectLeavesAtPoints(GolVec3* p_points, LegoU32 p_pointCount)
{
	LegoFloat planeOffset;
	m_visitStamp++;
	TreeNode* node = m_root;

	while (node->m_type == TreeNode::e_plane) {
		LegoFloat dot = node->m_data.m_plane.m_normalZ;
		dot *= p_points->m_z;
		dot += node->m_data.m_plane.m_normalY * p_points->m_y;
		LegoFloat dotX = p_points->m_x;
		dotX *= node->m_data.m_plane.m_normalX;
		dot += dotX;
		dot += node->m_data.m_plane.m_distance;

		LegoU32 nodeIndex;
		if (dot < 0.0f && node->m_data.m_plane.m_backChild != TreeNode::c_invalidIndex) {
			node->m_data.m_plane.m_backStamp = m_visitStamp;
			nodeIndex = node->m_data.m_plane.m_backChild;
		}
		else if (node->m_data.m_plane.m_frontChild == TreeNode::c_invalidIndex) {
			node->m_data.m_plane.m_backStamp = m_visitStamp;
			nodeIndex = node->m_data.m_plane.m_backChild;
		}
		else {
			node->m_data.m_plane.m_frontStamp = m_visitStamp;
			nodeIndex = node->m_data.m_plane.m_frontChild;
		}

		node = &m_nodes[nodeIndex];
	}

	node->m_data.m_node.m_previous = NULL;
	node->m_data.m_node.m_next = NULL;
	if (node->m_nextLeafIndex == TreeNode::c_invalidIndex) {
		TreeNode::Node* entry = &node->m_data.m_node;
		m_lastVisibleLeaf = entry;
		m_firstVisibleLeaf = entry;
		return;
	}

	LegoU32 count = p_pointCount;
	TreeNode* firstNode = node;
	TreeNode* previousNode = node;
	node = &m_nodes[node->m_nextLeafIndex];
	LegoU32 stamp;

	for (;;) {
		stamp = m_visitStamp;

		if (node->m_data.m_plane.m_frontStamp != stamp) {
			if (node->m_data.m_plane.m_backStamp != stamp) {
				LegoFloat dot = node->m_data.m_plane.m_normalZ;
				dot *= p_points->m_z;
				dot += node->m_data.m_plane.m_normalY * p_points->m_y;
				dot += node->m_data.m_plane.m_normalX * p_points->m_x;

				if (dot < -node->m_data.m_plane.m_distance) {
					node->m_data.m_plane.m_backStamp = stamp;
					if (node->m_data.m_plane.m_backChild == TreeNode::c_invalidIndex) {
						continue;
					}

					node = &m_nodes[node->m_data.m_plane.m_backChild];
				}
				else {
					node->m_data.m_plane.m_frontStamp = stamp;
					if (node->m_data.m_plane.m_frontChild == TreeNode::c_invalidIndex) {
						continue;
					}

					node = &m_nodes[node->m_data.m_plane.m_frontChild];
				}
			}
			else {
				node->m_data.m_plane.m_frontStamp = stamp;
				if (node->m_data.m_plane.m_frontChild == TreeNode::c_invalidIndex) {
					continue;
				}
				LegoU32 i = 1;
				if (count <= i) {
					continue;
				}

				planeOffset = -node->m_data.m_plane.m_distance;
				LegoFloat* vertexY = &p_points[i].m_y;
				while (i < count) {
					LegoFloat dot = vertexY[1] * node->m_data.m_plane.m_normalZ;
					dot += node->m_data.m_plane.m_normalY * vertexY[0];
					dot += vertexY[-1] * node->m_data.m_plane.m_normalX;
					if (dot > planeOffset) {
						break;
					}

					i++;
					vertexY += 3;
				}

				if (i >= count) {
					continue;
				}

				node = &m_nodes[node->m_data.m_plane.m_frontChild];
			}
		}
		else {
			if (node->m_data.m_plane.m_backStamp != stamp) {
				node->m_data.m_plane.m_backStamp = stamp;
				if (node->m_data.m_plane.m_backChild == TreeNode::c_invalidIndex) {
					continue;
				}
				LegoU32 i = 1;
				if (count <= i) {
					continue;
				}

				planeOffset = -node->m_data.m_plane.m_distance;
				LegoFloat* vertexY = &p_points[i].m_y;
				while (i < count) {
					LegoFloat dot = vertexY[1] * node->m_data.m_plane.m_normalZ;
					dot += node->m_data.m_plane.m_normalY * vertexY[0];
					dot += vertexY[-1] * node->m_data.m_plane.m_normalX;
					if (dot < planeOffset) {
						break;
					}

					i++;
					vertexY += 3;
				}

				if (i >= count) {
					continue;
				}

				node = &m_nodes[node->m_data.m_plane.m_backChild];
			}
			else {
				if (node->m_nextLeafIndex == TreeNode::c_invalidIndex) {
					break;
				}

				node = &m_nodes[node->m_nextLeafIndex];
				continue;
			}
		}

		if (node->m_type != TreeNode::e_plane) {
			previousNode->m_data.m_node.m_next = &node->m_data.m_node;
			node->m_data.m_node.m_previous = &previousNode->m_data.m_node;
			node->m_data.m_node.m_next = NULL;
			previousNode = node;
			node = &m_nodes[node->m_nextLeafIndex];
		}
	}

	m_firstVisibleLeaf = &firstNode->m_data.m_node;
	m_lastVisibleLeaf = &previousNode->m_data.m_node;
}

// FUNCTION: LEGORACERS 0x00414850
DecalGeometry::DecalGeometry()
{
	m_golExport = NULL;
	m_model = NULL;
	m_vertices = NULL;
	m_indexBytes = NULL;
	m_vertexCapacity = 0;
	m_triangleCapacity = 0;
	m_vertexCount = 0;
	m_triangleCount = 0;
	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;
	m_groupIndex = 0;
	m_batchFirstVertex = 0;
	m_batchFirstTriangle = 0;
	m_depth = g_decalGeometryDefaultDepth;
	m_widthAxis.m_x = 1.0f;
	m_widthAxis.m_y = 0.0f;
	m_widthAxis.m_z = 0.0f;
	m_lengthAxis.m_x = 0.0f;
	m_lengthAxis.m_y = 1.0f;
	m_lengthAxis.m_z = 0.0f;
	m_normal.m_x = 0.0f;
	m_normal.m_y = 0.0f;
	m_normal.m_z = 1.0f;
	m_center.m_x = 0.0f;
	m_center.m_y = 0.0f;
	m_center.m_z = 0.0f;
	m_width = 1.0f;
	m_length = 1.0f;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
	g_decalWAxisX = 0.0f;
	g_decalWAxisY = 0.0f;
	g_decalWAxisZ = 0.0f;
	g_decalWOffset = 1.0f;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00414940
DecalGeometry::~DecalGeometry()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00414950
void DecalGeometry::Initialize(GolExport* p_golExport, GolRenderDevice* p_renderer, LegoU32 p_count)
{
	if (m_flags & c_initialized) {
		Destroy();
	}

	m_golExport = p_golExport;
	m_model = p_golExport->CreateModel();
	m_triangleCapacity = p_count;
	m_vertexCapacity = p_count * 3;
	m_model->Allocate(p_renderer, 1, m_vertexCapacity, p_count, p_count * 2 + 2, 1);
	m_entity.SetPrimaryModel(m_model, g_decalGeometryMaxFloat);
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = g_decalGeometryDefaultLift;
	m_entity.SetPosition(m_position);
	m_flags = c_initialized;
}

// FUNCTION: LEGORACERS 0x004149f0
void DecalGeometry::Destroy()
{
	m_entity.ResetModelState();

	if (m_golExport != NULL) {
		if (m_model != 0) {
			m_golExport->DestroyModel(m_model);
		}
		m_golExport = NULL;
	}

	m_model = 0;
	m_vertices = 0;
	m_indexBytes = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00414a30
void RaceDecalManager::Trail::Decal::Project(GolCollidableEntity* p_collidable)
{
	ComputeQueryPoints();

	GolBoundingShape* boundingShape = p_collidable->GetBoundingShape(0);
	GolModelBase* model = p_collidable->GetModel(0);
	boundingShape->CollectLeavesAtPoints(g_decalQueryPoints, sizeOfArray(g_decalQueryPoints));
	BeginGeometry(model);

	GolBoundingShape::TreeNode::Node* entry = boundingShape->GetFirstVisibleLeaf();
	while (entry != NULL) {
		ProcessGroups(model, entry->m_firstGroup, entry->m_groupCount);
		entry = entry->m_next;
	}

	EndGeometry(model);
}

// FUNCTION: LEGORACERS 0x00414a90
void RaceDecalManager::Trail::Decal::BeginGeometry(GolModelBase* p_model)
{
	ComputeProjection();

	p_model->GetVertexArray(&m_sourceVertices);

	GdbModelIndexArrayBase* indexArrayBase;
	p_model->GetIndexArrayInto(&indexArrayBase);
	m_sourceIndexBytes = static_cast<GdbModelIndexArray*>(indexArrayBase)->GetIndexBytes();

	GolModelBase* model = m_model;
	model->GetVertexArray(&m_vertices);

	m_model->GetIndexArrayInto(&indexArrayBase);
	LegoU8* destIndexBytes = static_cast<GdbModelIndexArray*>(indexArrayBase)->GetIndexBytes();

	m_vertexCount = 0;
	m_batchFirstVertex = 0;
	m_triangleCount = 0;
	m_batchFirstTriangle = 0;
	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;

	model = m_model;
	m_indexBytes = destIndexBytes;
	LegoU32 one = 1;
	model->GetMutableGroups()[0] = c_commandModelFlags;
	model->SetDirty(one);
	m_groupIndex = one;
}

// FUNCTION: LEGORACERS 0x00414b30
void RaceDecalManager::Trail::Decal::ProcessGroups(
	GolModelBase* p_model,
	LegoU32 p_firstCommand,
	LegoU32 p_commandCount
)
{
	LegoU32 start = p_firstCommand;
	GolModelBase* model = p_model;
	LegoU32 count = p_commandCount;
	if (count == 0) {
		count = model->GetGroupCount();
	}

	LegoU32 enabled = 1;
	LegoU32 end = start + count;
	if (start < end) {
		do {
			LegoU32 command = model->GetMutableGroups()[start];
			start++;
			LegoU32 commandType = command & c_commandMask;
			if (commandType <= c_commandModelFlags) {
				if (commandType != c_commandModelFlags) {
					if (commandType != c_commandVertices) {
						if (commandType == c_commandPolygon && enabled) {
							EmitPolygon(command & c_commandVertexMask, (command >> 16) & 0x7f);
						}
					}
					else if (enabled) {
						TransformVertices(
							(command >> 22) & 0x3f,
							command & c_commandVertexMask,
							((command >> 16) & 0x3f) + 1
						);
					}
				}
				else {
					enabled = model->GetMaterialTable()->GetMaterial(command & c_commandVertexMask)->GetFlags() &
							  c_commandModelFlagBit17;
				}
			}
			else if (commandType == c_commandEnd) {
				return;
			}
		} while (start < end);
	}
}

// FUNCTION: LEGORACERS 0x00414c00
void RaceDecalManager::Trail::Decal::EndGeometry(GolModelBase* p_model)
{
	if (m_batchTriangleCount) {
		FlushBatch();
	}

	GolModelBase* model = m_model;
	LegoU32 groupIndex = m_groupIndex;
	model->GetMutableGroups()[groupIndex] = c_commandEnd;
	model->SetDirty(TRUE);
	GetModel()->AddFlags(TRUE);
	GetModel()->AddFlagsWithBounds(TRUE, FALSE);
	p_model->AddFlags(FALSE);
	p_model->AddFlagsWithBounds(FALSE, FALSE);

	if (m_triangleCount) {
		m_flags |= c_hasGeometry;
	}
	else {
		m_flags &= ~c_hasGeometry;
	}
}

// FUNCTION: LEGORACERS 0x00414c90
void RaceDecalManager::Trail::Decal::SetOrientation(GolVec3* p_normal, GolVec3* p_lengthAxis)
{
	GolVec3* normalized = &m_normal;
	GolMath::NormalizeVector3(*p_normal, normalized);

	GolVec3* perpendicular = &m_lengthAxis;
	LegoFloat dot = normalized->m_z * p_lengthAxis->m_z;
	dot += normalized->m_y * p_lengthAxis->m_y;
	dot += normalized->m_x * p_lengthAxis->m_x;

	GolVec3 scaled;
	scaled.m_x = dot * normalized->m_x;
	scaled.m_y = normalized->m_y * dot;
	scaled.m_z = dot * normalized->m_z;
	perpendicular->m_x = p_lengthAxis->m_x - scaled.m_x;
	perpendicular->m_y = p_lengthAxis->m_y - scaled.m_y;
	perpendicular->m_z = p_lengthAxis->m_z - scaled.m_z;
	GolMath::NormalizeVector3(*perpendicular, perpendicular);

	m_widthAxis.m_x = perpendicular->m_y * normalized->m_z - perpendicular->m_z * normalized->m_y;
	m_widthAxis.m_y = perpendicular->m_z * normalized->m_x - normalized->m_z * perpendicular->m_x;
	m_widthAxis.m_z = normalized->m_y * perpendicular->m_x - perpendicular->m_y * normalized->m_x;
}

// FUNCTION: LEGORACERS 0x00414d50
void RaceDecalManager::Trail::Decal::ComputeProjection()
{
	LegoFloat scaleX = m_width;
	scaleX = 0.99000001f / scaleX;
	LegoFloat scaleY = m_length;
	scaleY = 0.99000001f / scaleY;

	LegoFloat value = m_widthAxis.m_x;
	value *= scaleX;
	g_decalUAxisX = value;

	value = m_lengthAxis.m_x;
	value *= scaleY;
	g_decalVAxisX = value;

	value = m_widthAxis.m_y;
	value *= scaleX;
	g_decalUAxisY = value;

	value = m_lengthAxis.m_y;
	value *= scaleY;
	g_decalVAxisY = value;

	value = m_widthAxis.m_z;
	value *= scaleX;
	g_decalUAxisZ = value;

	value = m_lengthAxis.m_z;
	value *= scaleY;
	g_decalVAxisZ = value;

	LegoFloat dotX = m_widthAxis.m_z;
	dotX *= m_center.m_z;
	value = m_widthAxis.m_y;
	value *= m_center.m_y;
	dotX += value;
	value = m_widthAxis.m_x;
	value *= m_center.m_x;
	dotX += value;
	dotX = -dotX;
	dotX *= scaleX;
	g_decalUOffset = dotX + 0.5f;

	LegoFloat dotY = m_lengthAxis.m_z;
	dotY *= m_center.m_z;
	value = m_lengthAxis.m_y;
	value *= m_center.m_y;
	dotY += value;
	value = m_lengthAxis.m_x;
	value *= m_center.m_x;
	dotY += value;
	dotY = -dotY;
	dotY *= scaleY;
	g_decalVOffset = dotY + 0.5f;
}

// FUNCTION: LEGORACERS 0x00414e40
LegoU32 RaceDecalManager::Trail::Decal::TransformVertices(
	LegoU32 p_destIndex,
	LegoU32 p_firstVertex,
	LegoU32 p_vertexCount
)
{
	LegoU32 result = p_vertexCount;
	LegoU32 vertexIndex = p_firstVertex;
	ProjectedVertex* projected = &g_decalProjectedVertices[p_destIndex];
	LegoU32 end = p_firstVertex + p_vertexCount;
	while (vertexIndex < end) {
		m_sourceVertices->GetPosition(vertexIndex, &projected->m_position);

		projected->m_projected.m_x.m_float = g_decalUAxisX * projected->m_position.m_x;
		projected->m_projected.m_y.m_float = g_decalVAxisX * projected->m_position.m_x;
		projected->m_projected.m_x.m_float =
			projected->m_position.m_y * g_decalUAxisY + projected->m_projected.m_x.m_float;
		projected->m_projected.m_y.m_float =
			projected->m_position.m_y * g_decalVAxisY + projected->m_projected.m_y.m_float;
		projected->m_projected.m_x.m_float =
			projected->m_position.m_z * g_decalUAxisZ + projected->m_projected.m_x.m_float;
		projected->m_projected.m_y.m_float =
			projected->m_position.m_z * g_decalVAxisZ + projected->m_projected.m_y.m_float;
		projected->m_projected.m_x.m_float = g_decalUOffset + projected->m_projected.m_x.m_float;

		LegoU32 projectedXBits = projected->m_projected.m_x.m_bits;
		projected->m_projected.m_y.m_float = g_decalVOffset + projected->m_projected.m_y.m_float;
		result = ((projectedXBits >> 2) | (projected->m_projected.m_y.m_bits & c_clipYMinMask)) >> 29;

		LegoU32 projectedYBits = projected->m_projected.m_y.m_bits;
		LegoU32 highFlags = (((c_floatOneBits - projectedYBits) & c_clipYMaxMask) |
							 (((c_floatOneBits - projectedXBits) >> 2) & c_clipXMaxMask)) >>
							28;
		projected->m_clipFlags = result | (~(2 * result) & highFlags);

		vertexIndex++;
		projected++;
	}

	return result;
}

// STUB: LEGORACERS 0x00414f40
void RaceDecalManager::Trail::Decal::EmitPolygon(LegoU32 p_firstPolygon, LegoU32 p_polygonCount)
{
	LegoU8* indices = m_sourceIndexBytes + 4 * p_firstPolygon;
	LegoU8* end = m_sourceIndexBytes + 4 * (p_firstPolygon + p_polygonCount);

	while (indices < end) {
		LegoU32 index0 = indices[0];
		LegoU32 index1 = indices[1];
		LegoU32 index2 = indices[2];
		ProjectedVertex* vertex0 = &g_decalProjectedVertices[index0];
		ProjectedVertex* vertex1 = &g_decalProjectedVertices[index1];
		ProjectedVertex* vertex2 = &g_decalProjectedVertices[index2];
		LegoU32 flags0 = vertex0->m_clipFlags;
		LegoU32 flags1 = vertex1->m_clipFlags;
		LegoU32 flags2 = vertex2->m_clipFlags;

		if (!(flags0 & flags1 & flags2)) {
			LegoFloat cross = (vertex1->m_projected.m_x.m_float - vertex2->m_projected.m_x.m_float) *
								  (vertex0->m_projected.m_y.m_float - vertex2->m_projected.m_y.m_float) -
							  (vertex1->m_projected.m_y.m_float - vertex2->m_projected.m_y.m_float) *
								  (vertex0->m_projected.m_x.m_float - vertex2->m_projected.m_x.m_float);

			if (cross > 0.0f) {
				LegoU32 combinedFlags = flags0 | flags1 | flags2;
				if (combinedFlags) {
					LegoU32 indicesA[16];
					LegoU32 indicesB[16];
					LegoU32 flagsA[16];
					LegoU32 flagsB[16];
					LegoU32* inputIndices = indicesA;
					LegoU32* outputIndices = indicesB;
					LegoU32* inputFlags = flagsA;
					LegoU32* outputFlags = flagsB;
					LegoU32 generatedIndex = c_projectedVertexCount;
					LegoU32 inputCount = 3;
					LegoU32 i;

					inputIndices[0] = index0;
					inputIndices[1] = index1;
					inputIndices[2] = index2;
					inputFlags[0] = flags0;
					inputFlags[1] = flags1;
					inputFlags[2] = flags2;

					if (combinedFlags & c_clipXMinFlag) {
						LegoU32 outputCount = 0;
						LegoU32 previousIndex = inputCount - 1;
						LegoU32 previousOutside = inputFlags[previousIndex] & c_clipXMinFlag;
						for (i = 0; i < inputCount; i++) {
							LegoU32 currentOutside = inputFlags[i] & c_clipXMinFlag;
							if (previousOutside != currentOutside) {
								ProjectedVertex* previous = &g_decalProjectedVertices[inputIndices[previousIndex]];
								ProjectedVertex* current = &g_decalProjectedVertices[inputIndices[i]];
								ProjectedVertex* clipped = &g_decalProjectedVertices[generatedIndex];
								LegoFloat amount =
									previous->m_projected.m_x.m_float /
									(previous->m_projected.m_x.m_float - current->m_projected.m_x.m_float);

								clipped->m_projected.m_x.m_float = 0.0f;
								clipped->m_position.m_x =
									(current->m_position.m_x - previous->m_position.m_x) * amount +
									previous->m_position.m_x;
								clipped->m_position.m_y =
									(current->m_position.m_y - previous->m_position.m_y) * amount +
									previous->m_position.m_y;
								clipped->m_position.m_z =
									(current->m_position.m_z - previous->m_position.m_z) * amount +
									previous->m_position.m_z;
								clipped->m_projected.m_y.m_float =
									(current->m_projected.m_y.m_float - previous->m_projected.m_y.m_float) * amount +
									previous->m_projected.m_y.m_float;

								LegoU32 projectedYBits = clipped->m_projected.m_y.m_bits;
								clipped->m_clipFlags =
									(((projectedYBits >> 1) & 0x40000000) |
									 (~projectedYBits & (c_floatOneBits - projectedYBits) & c_clipYMaxMask)) >>
									28;

								outputIndices[outputCount] = generatedIndex;
								outputFlags[outputCount] = clipped->m_clipFlags;
								generatedIndex++;
								outputCount++;
							}
							if (!currentOutside) {
								outputIndices[outputCount] = inputIndices[i];
								outputFlags[outputCount] = inputFlags[i];
								outputCount++;
							}
							previousIndex = i;
							previousOutside = currentOutside;
						}

						LegoU32* tempIndices = inputIndices;
						inputIndices = outputIndices;
						outputIndices = tempIndices;
						LegoU32* tempFlags = inputFlags;
						inputFlags = outputFlags;
						outputFlags = tempFlags;
						inputCount = outputCount;
					}

					if ((combinedFlags & c_clipXMaxFlag) && inputCount > 0) {
						LegoU32 outputCount = 0;
						LegoU32 previousIndex = inputCount - 1;
						LegoU32 previousOutside = inputFlags[previousIndex] & c_clipXMaxFlag;
						for (i = 0; i < inputCount; i++) {
							LegoU32 currentOutside = inputFlags[i] & c_clipXMaxFlag;
							if (previousOutside != currentOutside) {
								ProjectedVertex* previous = &g_decalProjectedVertices[inputIndices[previousIndex]];
								ProjectedVertex* current = &g_decalProjectedVertices[inputIndices[i]];
								ProjectedVertex* clipped = &g_decalProjectedVertices[generatedIndex];
								LegoFloat amount =
									(1.0f - previous->m_projected.m_x.m_float) /
									(current->m_projected.m_x.m_float - previous->m_projected.m_x.m_float);

								clipped->m_projected.m_x.m_float = 0.99000001f;
								clipped->m_position.m_x =
									(current->m_position.m_x - previous->m_position.m_x) * amount +
									previous->m_position.m_x;
								clipped->m_position.m_y =
									(current->m_position.m_y - previous->m_position.m_y) * amount +
									previous->m_position.m_y;
								clipped->m_position.m_z =
									(current->m_position.m_z - previous->m_position.m_z) * amount +
									previous->m_position.m_z;
								clipped->m_projected.m_y.m_float =
									(current->m_projected.m_y.m_float - previous->m_projected.m_y.m_float) * amount +
									previous->m_projected.m_y.m_float;

								LegoU32 projectedYBits = clipped->m_projected.m_y.m_bits;
								clipped->m_clipFlags =
									(((projectedYBits >> 1) & 0x40000000) |
									 (~projectedYBits & (c_floatOneBits - projectedYBits) & c_clipYMaxMask)) >>
									28;

								outputIndices[outputCount] = generatedIndex;
								outputFlags[outputCount] = clipped->m_clipFlags;
								generatedIndex++;
								outputCount++;
							}
							if (!currentOutside) {
								outputIndices[outputCount] = inputIndices[i];
								outputFlags[outputCount] = inputFlags[i];
								outputCount++;
							}
							previousIndex = i;
							previousOutside = currentOutside;
						}

						LegoU32* tempIndices = inputIndices;
						inputIndices = outputIndices;
						outputIndices = tempIndices;
						LegoU32* tempFlags = inputFlags;
						inputFlags = outputFlags;
						outputFlags = tempFlags;
						inputCount = outputCount;
					}

					if ((combinedFlags & c_clipYMinFlag) && inputCount > 0) {
						LegoU32 outputCount = 0;
						LegoU32 previousIndex = inputCount - 1;
						LegoU32 previousOutside = inputFlags[previousIndex] & c_clipYMinFlag;
						for (i = 0; i < inputCount; i++) {
							LegoU32 currentOutside = inputFlags[i] & c_clipYMinFlag;
							if (previousOutside != currentOutside) {
								ProjectedVertex* previous = &g_decalProjectedVertices[inputIndices[previousIndex]];
								ProjectedVertex* current = &g_decalProjectedVertices[inputIndices[i]];
								ProjectedVertex* clipped = &g_decalProjectedVertices[generatedIndex];
								LegoFloat amount =
									previous->m_projected.m_y.m_float /
									(previous->m_projected.m_y.m_float - current->m_projected.m_y.m_float);

								clipped->m_projected.m_y.m_float = 0.0f;
								clipped->m_clipFlags = 0;
								clipped->m_position.m_x =
									(current->m_position.m_x - previous->m_position.m_x) * amount +
									previous->m_position.m_x;
								clipped->m_position.m_y =
									(current->m_position.m_y - previous->m_position.m_y) * amount +
									previous->m_position.m_y;
								clipped->m_position.m_z =
									(current->m_position.m_z - previous->m_position.m_z) * amount +
									previous->m_position.m_z;
								clipped->m_projected.m_x.m_float =
									(current->m_projected.m_x.m_float - previous->m_projected.m_x.m_float) * amount +
									previous->m_projected.m_x.m_float;

								outputIndices[outputCount] = generatedIndex;
								outputFlags[outputCount] = clipped->m_clipFlags;
								generatedIndex++;
								outputCount++;
							}
							if (!currentOutside) {
								outputIndices[outputCount] = inputIndices[i];
								outputFlags[outputCount] = inputFlags[i];
								outputCount++;
							}
							previousIndex = i;
							previousOutside = currentOutside;
						}

						LegoU32* tempIndices = inputIndices;
						inputIndices = outputIndices;
						outputIndices = tempIndices;
						LegoU32* tempFlags = inputFlags;
						inputFlags = outputFlags;
						outputFlags = tempFlags;
						inputCount = outputCount;
					}

					if ((combinedFlags & c_clipYMaxFlag) && inputCount > 0) {
						LegoU32 outputCount = 0;
						LegoU32 previousIndex = inputCount - 1;
						LegoU32 previousOutside = inputFlags[previousIndex] & c_clipYMaxFlag;
						for (i = 0; i < inputCount; i++) {
							LegoU32 currentOutside = inputFlags[i] & c_clipYMaxFlag;
							if (previousOutside != currentOutside) {
								ProjectedVertex* previous = &g_decalProjectedVertices[inputIndices[previousIndex]];
								ProjectedVertex* current = &g_decalProjectedVertices[inputIndices[i]];
								ProjectedVertex* clipped = &g_decalProjectedVertices[generatedIndex];
								LegoFloat amount =
									(1.0f - previous->m_projected.m_y.m_float) /
									(current->m_projected.m_y.m_float - previous->m_projected.m_y.m_float);

								clipped->m_projected.m_y.m_float = 0.99000001f;
								clipped->m_clipFlags = 0;
								clipped->m_position.m_x =
									(current->m_position.m_x - previous->m_position.m_x) * amount +
									previous->m_position.m_x;
								clipped->m_position.m_y =
									(current->m_position.m_y - previous->m_position.m_y) * amount +
									previous->m_position.m_y;
								clipped->m_position.m_z =
									(current->m_position.m_z - previous->m_position.m_z) * amount +
									previous->m_position.m_z;
								clipped->m_projected.m_x.m_float =
									(current->m_projected.m_x.m_float - previous->m_projected.m_x.m_float) * amount +
									previous->m_projected.m_x.m_float;

								outputIndices[outputCount] = generatedIndex;
								outputFlags[outputCount] = clipped->m_clipFlags;
								generatedIndex++;
								outputCount++;
							}
							if (!currentOutside) {
								outputIndices[outputCount] = inputIndices[i];
								outputFlags[outputCount] = inputFlags[i];
								outputCount++;
							}
							previousIndex = i;
							previousOutside = currentOutside;
						}

						inputIndices = outputIndices;
						inputCount = outputCount;
					}

					if (inputCount > 2) {
						for (i = 1; i < inputCount - 1; i++) {
							EmitTriangle(
								&g_decalProjectedVertices[inputIndices[0]],
								&g_decalProjectedVertices[inputIndices[i]],
								&g_decalProjectedVertices[inputIndices[i + 1]]
							);
						}
					}
				}
				else {
					EmitTriangle(vertex0, vertex1, vertex2);
				}
			}
		}

		indices += 4;
	}
}

// FUNCTION: LEGORACERS 0x00415810
void RaceDecalManager::Trail::Decal::EmitTriangle(
	ProjectedVertex* p_vertex0,
	ProjectedVertex* p_vertex1,
	ProjectedVertex* p_vertex2
)
{
	if (m_triangleCount < m_triangleCapacity) {
		if (m_batchTriangleCount >= 10) {
			FlushBatch();
			LegoU32 polygonIndex = m_triangleCount;
			m_batchFirstVertex = m_vertexCount;
			m_batchVertexCount = 0;
			m_batchTriangleCount = 0;
			m_batchFirstTriangle = polygonIndex;
		}

		m_vertices->SetPosition(m_vertexCount, p_vertex0->m_position);
		m_vertices->SetColor(m_vertexCount, m_color);
		LegoU32 vertexIndex = m_vertexCount;
		m_vertexCount = vertexIndex + 1;
		m_vertices->SetTextureCoordinate(vertexIndex, p_vertex0->m_projected.m_vec);

		m_vertices->SetPosition(m_vertexCount, p_vertex1->m_position);
		m_vertices->SetColor(m_vertexCount, m_color);
		vertexIndex = m_vertexCount;
		m_vertexCount = vertexIndex + 1;
		m_vertices->SetTextureCoordinate(vertexIndex, p_vertex1->m_projected.m_vec);

		m_vertices->SetPosition(m_vertexCount, p_vertex2->m_position);
		m_vertices->SetColor(m_vertexCount, m_color);
		vertexIndex = m_vertexCount;
		m_vertexCount = vertexIndex + 1;
		m_vertices->SetTextureCoordinate(vertexIndex, p_vertex2->m_projected.m_vec);

		LegoU32 polygonIndex = m_triangleCount;
		LegoU32 polygonCount = m_batchTriangleCount;
		LegoU8* indices = m_indexBytes + 4 * polygonIndex;
		polygonIndex++;
		m_triangleCount = polygonIndex;
		polygonIndex = m_batchVertexCount;
		m_batchTriangleCount = polygonCount + 1;
		indices[0] = static_cast<LegoU8>(polygonIndex);

		LegoU32 batchVertexIndex = m_batchVertexCount + 1;
		m_batchVertexCount = batchVertexIndex;
		indices[1] = static_cast<LegoU8>(batchVertexIndex);
		polygonIndex = m_batchVertexCount;
		polygonIndex++;
		m_batchVertexCount = polygonIndex;
		indices[2] = static_cast<LegoU8>(polygonIndex);
		m_batchVertexCount++;
	}
}

// FUNCTION: LEGORACERS 0x00415980
void RaceDecalManager::Trail::Decal::FlushBatch()
{
	LegoU32 groupIndex = m_groupIndex;
	LegoU32 vertexCount = m_batchVertexCount;
	LegoU32 firstVertex = m_batchFirstVertex;
	m_groupIndex = groupIndex + 1;

	GolModelBase* model = m_model;
	model->GetMutableGroups()[groupIndex] = c_commandVertices;
	model->GetMutableGroups()[groupIndex] |= ((vertexCount + 0xffff) << 16) & 0x3f0000;
	model->GetMutableGroups()[groupIndex] |= firstVertex & c_commandVertexMask;
	model->SetDirty(TRUE);

	groupIndex = m_groupIndex;
	LegoU32 polygonCount = m_batchTriangleCount & 0x7f;
	LegoU32 firstPolygon = m_batchFirstTriangle & c_commandVertexMask;
	m_groupIndex = groupIndex + 1;

	model = m_model;
	model->GetMutableGroups()[groupIndex] = c_commandPolygon;
	model->GetMutableGroups()[groupIndex] |= polygonCount << 16;
	model->GetMutableGroups()[groupIndex] |= firstPolygon;
	model->SetDirty(TRUE);
}

// FUNCTION: LEGORACERS 0x00415a40
void DecalGeometry::Draw(GolRenderDevice* p_renderer)
{
	if (m_flags & c_hasGeometry) {
		p_renderer->DrawModelEntity(&m_entity);
	}
}

// FUNCTION: LEGORACERS 0x00415a60
GolVec3* RaceDecalManager::Trail::Decal::ComputeQueryPoints()
{
	LegoFloat scratch[13];

	LegoFloat v1 = m_width * 0.5f;
	scratch[0] = m_length * 0.5f;
	GolVec3* result = &m_center;
	scratch[4] = v1 * m_widthAxis.m_x;
	scratch[5] = m_widthAxis.m_y;
	scratch[5] *= v1;
	LegoFloat v3 = v1 * m_widthAxis.m_z;
	LegoFloat v4 = scratch[0] * m_lengthAxis.m_x;
	scratch[8] = m_lengthAxis.m_y;
	scratch[8] *= scratch[0];
	scratch[9] = m_lengthAxis.m_z;
	scratch[9] *= scratch[0];
	LegoFloat v5 = m_depth;
	scratch[10] = v5 * m_normal.m_x;
	scratch[11] = m_normal.m_y;
	scratch[11] *= v5;
	LegoFloat v6 = v5 * m_normal.m_z;

	g_decalQueryPoints[0] = *result;

	scratch[1] = result->m_x - v4;
	scratch[2] = result->m_y - scratch[8];
	scratch[3] = result->m_z - scratch[9];
	scratch[1] = scratch[1] + scratch[10];
	scratch[2] = scratch[2] + scratch[11];
	LegoFloat v7 = v6 + scratch[3];
	g_decalQueryPoints[1].m_x = scratch[1] - scratch[4];
	g_decalQueryPoints[1].m_y = scratch[2] - scratch[5];
	g_decalQueryPoints[1].m_z = v7 - v3;
	g_decalQueryPoints[2].m_x = scratch[1] + scratch[4];
	g_decalQueryPoints[2].m_y = scratch[2] + scratch[5];
	g_decalQueryPoints[2].m_z = v7 + v3;

	LegoFloat v8 = v4 + result->m_x;
	scratch[2] = scratch[8] + result->m_y;
	scratch[3] = scratch[9] + result->m_z;
	g_decalQueryPoints[3].m_x = v8 - scratch[4];
	g_decalQueryPoints[3].m_y = scratch[2] - scratch[5];
	g_decalQueryPoints[3].m_z = scratch[3] - v3;
	g_decalQueryPoints[4].m_x = v8 + scratch[4];
	g_decalQueryPoints[4].m_y = scratch[2] + scratch[5];
	g_decalQueryPoints[4].m_z = scratch[3] + v3;

	return result;
}
// FUNCTION: LEGORACERS 0x00415bf0
LegoU8 DecalGeometry::SetColor(const ColorRGBA* p_color)
{
	m_color.m_red = p_color->m_red;
	m_color.m_grn = p_color->m_grn;
	m_color.m_blu = p_color->m_blu;
	LegoU8 result = p_color->m_alp;
	m_color.m_alp = result;

	return result;
}
