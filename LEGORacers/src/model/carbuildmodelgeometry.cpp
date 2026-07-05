#include "audio/directsoundconversions.h"
#include "core/gol.h"
#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golanimatedentity.h"
#include "golmaterial.h"
#include "golmateriallibrary.h"
#include "golmodelbase.h"
#include "goltexture.h"
#include "material/goltexturelist.h"
#include "model/carbuildmodel.h"
#include "model/legocolortable.h"
#include "render/gold3drenderdevice.h"
#include "surface/color.h"
#include "surface/gold3dtexture.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(CarBuildModel::BuildVertex, 0x28)
DECOMP_SIZE_ASSERT(CarBuildModel::BuildPrimitive, 0x10)
DECOMP_SIZE_ASSERT(CarBuildModel::BuildPrimitiveBounds, 0x18)
DECOMP_SIZE_ASSERT(CarBuildModel::VertexUse, 0x04)

// GLOBAL: LEGORACERS 0x004ceba4
static CarBuildModel::BuildVertex* g_carBuildModelSortVertices;

// GLOBAL: LEGORACERS 0x004c7674
static CarBuildModel::VertexUse g_carBuildModelVertexUses[CarBuildModel::c_buildVertexCapacity];

// GLOBAL: LEGORACERS 0x004b480c
static const LegoFloat g_carBuildModelNegativePlaneEpsilon = -0.0049999999f;

// FUNCTION: LEGORACERS 0x00495020
LegoS32 CarBuildModel::ResetBuildVertexTree()
{
	m_buildVertexTreeRoot = NULL;
	m_buildVertexCount = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x00495030
LegoS32 CarBuildModel::AddBuildVertex(BuildVertex* p_vertex)
{
	BuildVertex* vertex = &m_buildVertices[m_buildVertexCount];
	*vertex = *p_vertex;
	m_buildVertices[m_buildVertexCount].m_index = static_cast<LegoU16>(m_buildVertexCount);

	BuildVertex* existing = InsertOrFindBuildVertex(&m_buildVertexTreeRoot, &m_buildVertices[m_buildVertexCount]);
	if (existing != NULL) {
		return existing->m_index;
	}

	m_buildVertexCount++;

	return m_buildVertexCount - 1;
}

// FUNCTION: LEGORACERS 0x004950c0
CarBuildModel::BuildVertex* CarBuildModel::InsertOrFindBuildVertex(BuildVertex** p_root, BuildVertex* p_vertex)
{
	p_vertex->m_left = NULL;
	p_vertex->m_right = NULL;

	BuildVertex* node = *p_root;
	if (node != NULL) {
		for (;;) {
			LegoS32 compare = CompareBuildVertex(p_vertex, node);
			if (compare == 0) {
				return node;
			}

			if (compare > 0) {
				if (node->m_right == NULL) {
					p_vertex->m_parent = node;
					node->m_right = p_vertex;
					RebalanceBuildVertexInsert(p_root, p_vertex);
					return NULL;
				}

				node = node->m_right;
			}
			else {
				if (node->m_left == NULL) {
					p_vertex->m_parent = node;
					node->m_left = p_vertex;
					RebalanceBuildVertexInsert(p_root, p_vertex);
					return NULL;
				}

				node = node->m_left;
			}
		}
	}

	p_vertex->m_parent = NULL;
	p_vertex->m_treeBlack = TRUE;
	*p_root = p_vertex;

	return NULL;
}

// FUNCTION: LEGORACERS 0x00495160
LegoS32 __fastcall CarBuildModel::CompareBuildVertex(const BuildVertex* p_lhs, const BuildVertex* p_rhs)
{
	LegoS32 lhsKey;
	LegoS32 rhsKey;
	::memcpy(&lhsKey, &p_lhs->m_position.m_x, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_position.m_x, sizeof(rhsKey));
	LegoS32 result = lhsKey - rhsKey;
	if (result != 0) {
		return result;
	}

	::memcpy(&lhsKey, &p_lhs->m_position.m_y, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_position.m_y, sizeof(rhsKey));
	result = lhsKey - rhsKey;
	if (result != 0) {
		return result;
	}

	::memcpy(&lhsKey, &p_lhs->m_position.m_z, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_position.m_z, sizeof(rhsKey));
	result = lhsKey - rhsKey;
	if (result != 0) {
		return result;
	}

	result = static_cast<LegoU8>(p_lhs->m_normalX) - static_cast<LegoU8>(p_rhs->m_normalX);
	if (result != 0) {
		return result;
	}

	result = static_cast<LegoU8>(p_lhs->m_normalY) - static_cast<LegoU8>(p_rhs->m_normalY);
	if (result != 0) {
		return result;
	}

	result = static_cast<LegoU8>(p_lhs->m_normalZ) - static_cast<LegoU8>(p_rhs->m_normalZ);
	if (result != 0) {
		return result;
	}

	::memcpy(&lhsKey, &p_lhs->m_textureCoordinate.m_x, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_textureCoordinate.m_x, sizeof(rhsKey));
	result = lhsKey - rhsKey;
	if (result != 0) {
		return result;
	}

	::memcpy(&lhsKey, &p_lhs->m_textureCoordinate.m_y, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_textureCoordinate.m_y, sizeof(rhsKey));
	return lhsKey - rhsKey;
}

// FUNCTION: LEGORACERS 0x004951c0
void __fastcall CarBuildModel::RebalanceBuildVertexInsert(BuildVertex** p_root, BuildVertex* p_vertex)
{
	p_vertex->m_treeBlack = FALSE;

	while (p_vertex->m_parent != NULL && !p_vertex->m_parent->m_treeBlack) {
		if (p_vertex->m_parent == p_vertex->m_parent->m_parent->m_left) {
			BuildVertex* uncle = p_vertex->m_parent->m_parent->m_right;
			if (uncle != NULL && !uncle->m_treeBlack) {
				uncle->m_treeBlack = TRUE;
				p_vertex->m_parent->m_treeBlack = TRUE;
				p_vertex = p_vertex->m_parent->m_parent;
				p_vertex->m_treeBlack = FALSE;
			}
			else {
				if (p_vertex == p_vertex->m_parent->m_right) {
					p_vertex = p_vertex->m_parent;
					RotateBuildVertexLeft(p_root, p_vertex);
				}

				p_vertex->m_parent->m_treeBlack = TRUE;
				p_vertex->m_parent->m_parent->m_treeBlack = FALSE;
				RotateBuildVertexRight(p_root, p_vertex->m_parent->m_parent);
			}
		}
		else {
			BuildVertex* uncle = p_vertex->m_parent->m_parent->m_left;
			if (uncle != NULL && !uncle->m_treeBlack) {
				uncle->m_treeBlack = TRUE;
				p_vertex->m_parent->m_treeBlack = TRUE;
				p_vertex = p_vertex->m_parent->m_parent;
				p_vertex->m_treeBlack = FALSE;
			}
			else {
				if (p_vertex == p_vertex->m_parent->m_left) {
					p_vertex = p_vertex->m_parent;
					RotateBuildVertexRight(p_root, p_vertex);
				}

				p_vertex->m_parent->m_treeBlack = TRUE;
				p_vertex->m_parent->m_parent->m_treeBlack = FALSE;
				RotateBuildVertexLeft(p_root, p_vertex->m_parent->m_parent);
			}
		}
	}

	(*p_root)->m_treeBlack = TRUE;
}

// FUNCTION: LEGORACERS 0x00495290
void __fastcall CarBuildModel::RotateBuildVertexLeft(BuildVertex** p_root, BuildVertex* p_vertex)
{
	BuildVertex* pivot = p_vertex->m_right;
	BuildVertex* child = pivot->m_left;
	p_vertex->m_right = child;
	if (child != NULL) {
		child->m_parent = p_vertex;
	}

	BuildVertex* parent = p_vertex->m_parent;
	pivot->m_parent = parent;
	if (parent != NULL) {
		if (p_vertex == p_vertex->m_parent->m_left) {
			p_vertex->m_parent->m_left = pivot;
		}
		else {
			p_vertex->m_parent->m_right = pivot;
		}
	}
	else {
		*p_root = pivot;
	}

	pivot->m_left = p_vertex;
	p_vertex->m_parent = pivot;
}

// FUNCTION: LEGORACERS 0x004952d0
void __fastcall CarBuildModel::RotateBuildVertexRight(BuildVertex** p_root, BuildVertex* p_vertex)
{
	BuildVertex* pivot = p_vertex->m_left;
	BuildVertex* child = pivot->m_right;
	p_vertex->m_left = child;
	if (child != NULL) {
		child->m_parent = p_vertex;
	}

	BuildVertex* parent = p_vertex->m_parent;
	pivot->m_parent = parent;
	if (parent != NULL) {
		if (p_vertex == p_vertex->m_parent->m_left) {
			p_vertex->m_parent->m_left = pivot;
		}
		else {
			p_vertex->m_parent->m_right = pivot;
		}
	}
	else {
		*p_root = pivot;
	}

	pivot->m_right = p_vertex;
	p_vertex->m_parent = pivot;
}

// FUNCTION: LEGORACERS 0x00495310
LegoS32 CarBuildModel::ComparePrimitiveDrawOrder(const void* p_lhs, const void* p_rhs)
{
	const BuildPrimitive* lhs = *static_cast<BuildPrimitive* const*>(p_lhs);
	const BuildPrimitive* rhs = *static_cast<BuildPrimitive* const*>(p_rhs);

	LegoS32 result = lhs->m_materialIndex - rhs->m_materialIndex;
	if (result == 0) {
		LegoFloat delta = g_carBuildModelSortVertices[lhs->m_vertexIndices[0]].m_position.m_z -
						  g_carBuildModelSortVertices[rhs->m_vertexIndices[0]].m_position.m_z;
		::memcpy(&result, &delta, sizeof(result));
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00495360
void CarBuildModel::GetBuildPrimitiveBounds(BuildPrimitive* p_primitive, BuildPrimitiveBounds* p_bounds)
{
	BuildVertex* vertex = &g_carBuildModelSortVertices[p_primitive->m_vertexIndices[0]];

	p_bounds->m_minX = p_bounds->m_maxX = vertex->m_position.m_x;
	p_bounds->m_minY = p_bounds->m_maxY = vertex->m_position.m_y;
	p_bounds->m_minZ = p_bounds->m_maxZ = vertex->m_position.m_z;

	for (LegoS32 i = 1; i < p_primitive->m_vertexCount; i++) {
		vertex = &g_carBuildModelSortVertices[p_primitive->m_vertexIndices[i]];

		if (p_bounds->m_minX > vertex->m_position.m_x) {
			p_bounds->m_minX = vertex->m_position.m_x;
		}
		if (p_bounds->m_maxX < vertex->m_position.m_x) {
			p_bounds->m_maxX = vertex->m_position.m_x;
		}
		if (p_bounds->m_minY > vertex->m_position.m_y) {
			p_bounds->m_minY = vertex->m_position.m_y;
		}
		if (p_bounds->m_maxY < vertex->m_position.m_y) {
			p_bounds->m_maxY = vertex->m_position.m_y;
		}
		if (p_bounds->m_minZ > vertex->m_position.m_z) {
			p_bounds->m_minZ = vertex->m_position.m_z;
		}
		if (p_bounds->m_maxZ < vertex->m_position.m_z) {
			p_bounds->m_maxZ = vertex->m_position.m_z;
		}
	}
}

// FUNCTION: LEGORACERS 0x00495440
LegoS32 CarBuildModel::ResolvePrimitiveIntersections()
{
#define SWAP_ACTIVE_BUILD_PRIMITIVES()                                                                                 \
	do {                                                                                                               \
		swappedPrimitive = m_buildPrimitiveOrder[lhsIndex];                                                            \
		m_buildPrimitiveOrder[lhsIndex] = m_buildPrimitiveOrder[rhsIndex];                                             \
		m_buildPrimitiveOrder[rhsIndex] = swappedPrimitive;                                                            \
		swappedBounds = lhsBounds;                                                                                     \
		lhsBounds = rhsBounds;                                                                                         \
		rhsBounds = swappedBounds;                                                                                     \
	} while (0)

#define ROTATE_BUILD_PRIMITIVE_TO_MIN(coordMember, minField)                                                           \
	for (;;) {                                                                                                         \
		BuildVertex* vertices = m_buildVertices;                                                                       \
		LegoS32 old0 = primitive->m_vertexIndices[0];                                                                  \
		if (vertices[old0].m_position.coordMember == lhsBounds.minField &&                                             \
			vertices[primitive->m_vertexIndices[1]].m_position.coordMember == lhsBounds.minField) {                    \
			break;                                                                                                     \
		}                                                                                                              \
		LegoU16 old3 = primitive->m_vertexIndices[3];                                                                  \
		primitive->m_vertexIndices[0] = primitive->m_vertexIndices[1];                                                 \
		LegoU16 old2 = primitive->m_vertexIndices[2];                                                                  \
		primitive->m_vertexIndices[1] = old3;                                                                          \
		primitive->m_vertexIndices[3] = old2;                                                                          \
		primitive->m_vertexIndices[2] = old0;                                                                          \
	}

#define ROTATE_BUILD_PRIMITIVE_TO_MAX(coordMember, maxField)                                                           \
	while (m_buildVertices[primitive->m_vertexIndices[2]].m_position.coordMember != lhsBounds.maxField ||              \
		   m_buildVertices[primitive->m_vertexIndices[3]].m_position.coordMember != lhsBounds.maxField) {              \
		LegoU16 old2 = primitive->m_vertexIndices[2];                                                                  \
		LegoS32 old0 = primitive->m_vertexIndices[0];                                                                  \
		primitive->m_vertexIndices[0] = primitive->m_vertexIndices[1];                                                 \
		LegoU16 old3 = primitive->m_vertexIndices[3];                                                                  \
		primitive->m_vertexIndices[3] = old2;                                                                          \
		primitive->m_vertexIndices[1] = old3;                                                                          \
		primitive->m_vertexIndices[2] = old0;                                                                          \
	}

#define ALLOCATE_OUTSIDE_BUILD_PRIMITIVE_MIN()                                                                         \
	do {                                                                                                               \
		outsidePrimitive = m_buildPrimitiveOrder[m_buildPrimitiveCount];                                               \
		m_buildPrimitiveOrder[m_buildPrimitiveCount] = m_buildPrimitiveOrder[planePrimitiveCount];                     \
		m_buildPrimitiveOrder[planePrimitiveCount] = outsidePrimitive;                                                 \
		planePrimitiveCount++;                                                                                         \
		m_buildPrimitiveCount++;                                                                                       \
		*outsidePrimitive = *primitive;                                                                                \
		if (m_buildPrimitiveCount >= c_buildPrimitiveCapacity) {                                                       \
			m_buildStatus |= c_buildStatusOverflow;                                                                    \
			return m_buildPrimitiveCount;                                                                              \
		}                                                                                                              \
	} while (0)

#define ALLOCATE_OUTSIDE_BUILD_PRIMITIVE_MAX()                                                                         \
	outsidePrimitive = m_buildPrimitiveOrder[m_buildPrimitiveCount];                                                   \
	m_buildPrimitiveOrder[m_buildPrimitiveCount] = m_buildPrimitiveOrder[planePrimitiveCount];                         \
	m_buildPrimitiveOrder[planePrimitiveCount] = outsidePrimitive;                                                     \
	planePrimitiveCount++;                                                                                             \
	m_buildPrimitiveCount++;                                                                                           \
	*outsidePrimitive = *primitive;                                                                                    \
	if (m_buildPrimitiveCount >= c_buildPrimitiveCapacity) {                                                           \
		m_buildStatus |= c_buildStatusOverflow;                                                                        \
		return m_buildPrimitiveCount;                                                                                  \
	}

#define SET_SPLIT_VERTEX_POSITION_X(vertex, boundsField, splitCoordinate)                                              \
	lhsBounds.boundsField = (splitCoordinate);                                                                         \
	splitVertex.m_position.m_x = lhsBounds.boundsField;                                                                \
	splitVertex.m_position.m_y = (vertex)->m_position.m_y;                                                             \
	splitVertex.m_position.m_z = (vertex)->m_position.m_z

#define SET_SPLIT_VERTEX_POSITION_Y(vertex, boundsField, splitCoordinate)                                              \
	splitVertex.m_position.m_x = (vertex)->m_position.m_x;                                                             \
	lhsBounds.boundsField = (splitCoordinate);                                                                         \
	splitVertex.m_position.m_y = lhsBounds.boundsField;                                                                \
	splitVertex.m_position.m_z = (vertex)->m_position.m_z

#define SET_SPLIT_VERTEX_POSITION_Z(vertex, boundsField, splitCoordinate)                                              \
	splitVertex.m_position.m_x = (vertex)->m_position.m_x;                                                             \
	splitVertex.m_position.m_y = (vertex)->m_position.m_y;                                                             \
	lhsBounds.boundsField = (splitCoordinate);                                                                         \
	splitVertex.m_position.m_z = lhsBounds.boundsField

#define CLIP_BUILD_PRIMITIVE_MIN(coordMember, minField, maxField, secondCoordMember, setPosition)                      \
	if (lhsBounds.minField != rhsBounds.minField) {                                                                    \
		if (rhsBounds.minField < lhsBounds.minField) {                                                                 \
			SWAP_ACTIVE_BUILD_PRIMITIVES();                                                                            \
		}                                                                                                              \
		primitive = m_buildPrimitiveOrder[lhsIndex];                                                                   \
		ROTATE_BUILD_PRIMITIVE_TO_MIN(coordMember, minField);                                                          \
		ALLOCATE_OUTSIDE_BUILD_PRIMITIVE_MIN();                                                                        \
		rightScale = rhsBounds.minField - lhsBounds.minField;                                                          \
		firstLowVertex = &m_buildVertices[primitive->m_vertexIndices[0]];                                              \
		firstHighVertex = &m_buildVertices[primitive->m_vertexIndices[2]];                                             \
		rightScale = rightScale / (lhsBounds.maxField - lhsBounds.minField);                                           \
		setPosition(firstLowVertex, minField, rhsBounds.minField);                                                     \
		leftScale = 1.0f - rightScale;                                                                                 \
		InterpolateBuildVertex(&splitVertex, firstLowVertex, firstHighVertex, leftScale, rightScale);                  \
		splitFirstIndex = static_cast<LegoU16>(AddBuildVertex(&splitVertex));                                          \
		outsidePrimitive->m_vertexIndices[2] = splitFirstIndex;                                                        \
		primitive->m_vertexIndices[0] = splitFirstIndex;                                                               \
		secondLowVertex = &m_buildVertices[primitive->m_vertexIndices[1]];                                             \
		secondHighVertex = &m_buildVertices[primitive->m_vertexIndices[3]];                                            \
		splitVertex.m_position.secondCoordMember = secondLowVertex->m_position.secondCoordMember;                      \
		InterpolateBuildVertex(&splitVertex, secondLowVertex, secondHighVertex, leftScale, rightScale);                \
		splitSecondIndex = static_cast<LegoU16>(AddBuildVertex(&splitVertex));                                         \
		outsidePrimitive->m_vertexIndices[3] = splitSecondIndex;                                                       \
		primitive->m_vertexIndices[1] = splitSecondIndex;                                                              \
	}

#define CLIP_BUILD_PRIMITIVE_MAX(coordMember, minField, maxField, secondCoordMember, setPosition)                      \
	if (lhsBounds.maxField != rhsBounds.maxField) {                                                                    \
		if (rhsBounds.maxField > lhsBounds.maxField) {                                                                 \
			SWAP_ACTIVE_BUILD_PRIMITIVES();                                                                            \
		}                                                                                                              \
		primitive = m_buildPrimitiveOrder[lhsIndex];                                                                   \
		ROTATE_BUILD_PRIMITIVE_TO_MAX(coordMember, maxField);                                                          \
		ALLOCATE_OUTSIDE_BUILD_PRIMITIVE_MAX();                                                                        \
		rightScale = rhsBounds.maxField - lhsBounds.minField;                                                          \
		firstLowVertex = &m_buildVertices[primitive->m_vertexIndices[0]];                                              \
		firstHighVertex = &m_buildVertices[primitive->m_vertexIndices[2]];                                             \
		rightScale = rightScale / (lhsBounds.maxField - lhsBounds.minField);                                           \
		setPosition(firstLowVertex, maxField, rhsBounds.maxField);                                                     \
		leftScale = 1.0f - rightScale;                                                                                 \
		InterpolateBuildVertex(&splitVertex, firstLowVertex, firstHighVertex, leftScale, rightScale);                  \
		splitFirstIndex = static_cast<LegoU16>(AddBuildVertex(&splitVertex));                                          \
		outsidePrimitive->m_vertexIndices[0] = splitFirstIndex;                                                        \
		primitive->m_vertexIndices[2] = splitFirstIndex;                                                               \
		secondLowVertex = &m_buildVertices[primitive->m_vertexIndices[1]];                                             \
		secondHighVertex = &m_buildVertices[primitive->m_vertexIndices[3]];                                            \
		splitVertex.m_position.secondCoordMember = secondLowVertex->m_position.secondCoordMember;                      \
		InterpolateBuildVertex(&splitVertex, secondLowVertex, secondHighVertex, leftScale, rightScale);                \
		splitSecondIndex = static_cast<LegoU16>(AddBuildVertex(&splitVertex));                                         \
		outsidePrimitive->m_vertexIndices[1] = splitSecondIndex;                                                       \
		primitive->m_vertexIndices[3] = splitSecondIndex;                                                              \
	}

#define REMOVE_MATCHED_BUILD_PRIMITIVES()                                                                              \
	do {                                                                                                               \
		planePrimitiveCount--;                                                                                         \
		m_buildPrimitiveCount--;                                                                                       \
		BuildPrimitive* removedPrimitive = m_buildPrimitiveOrder[rhsIndex];                                            \
		m_buildPrimitiveOrder[rhsIndex] = m_buildPrimitiveOrder[planePrimitiveCount];                                  \
		m_buildPrimitiveOrder[planePrimitiveCount] = m_buildPrimitiveOrder[m_buildPrimitiveCount];                     \
		m_buildPrimitiveOrder[m_buildPrimitiveCount] = removedPrimitive;                                               \
		planePrimitiveCount--;                                                                                         \
		m_buildPrimitiveCount--;                                                                                       \
		removedPrimitive = m_buildPrimitiveOrder[lhsIndex];                                                            \
		m_buildPrimitiveOrder[lhsIndex] = m_buildPrimitiveOrder[planePrimitiveCount];                                  \
		m_buildPrimitiveOrder[planePrimitiveCount] = m_buildPrimitiveOrder[m_buildPrimitiveCount];                     \
		m_buildPrimitiveOrder[m_buildPrimitiveCount] = removedPrimitive;                                               \
		rhsIndex = lhsIndex;                                                                                           \
		GetBuildPrimitiveBounds(m_buildPrimitiveOrder[lhsIndex], &lhsBounds);                                          \
	} while (0)

	LegoS32 i;
	LegoU16 splitFirstIndex;
	LegoU16 splitSecondIndex;
	LegoFloat leftScale;
	LegoFloat rightScale;
	BuildPrimitive* primitive;
	BuildPrimitive* outsidePrimitive;
	BuildPrimitive* swappedPrimitive;
	BuildPrimitiveBounds swappedBounds;
	BuildVertex* firstLowVertex;
	BuildVertex* firstHighVertex;
	BuildVertex* secondLowVertex;
	BuildVertex* secondHighVertex;
	BuildVertex splitVertex;

	{
		LegoS32 planePrimitiveCount = 0;
		for (i = 0; i < m_buildPrimitiveCount; i++) {
			BuildPrimitive* primitive = m_buildPrimitiveOrder[i];
			if ((primitive->m_flags & 0x89) == 0x89 && primitive->m_vertexCount == 4) {
				m_buildPrimitiveOrder[i] = m_buildPrimitiveOrder[planePrimitiveCount++];
				m_buildPrimitiveOrder[planePrimitiveCount - 1] = primitive;
			}
		}

		for (LegoS32 lhsIndex = 0; lhsIndex < planePrimitiveCount - 1; lhsIndex++) {
			BuildPrimitiveBounds lhsBounds;
			GetBuildPrimitiveBounds(m_buildPrimitiveOrder[lhsIndex], &lhsBounds);

			for (LegoS32 rhsIndex = lhsIndex + 1; rhsIndex < planePrimitiveCount; rhsIndex++) {
				BuildPrimitiveBounds rhsBounds;
				GetBuildPrimitiveBounds(m_buildPrimitiveOrder[rhsIndex], &rhsBounds);

				LegoFloat planeDelta = lhsBounds.m_minZ - rhsBounds.m_minZ;
				BuildPrimitive* lhs = m_buildPrimitiveOrder[lhsIndex];
				BuildPrimitive* rhs = m_buildPrimitiveOrder[rhsIndex];
				if (g_carBuildModelNegativePlaneEpsilon < planeDelta && planeDelta < g_minAudibleSoundVolume &&
					lhs->m_partIndex != rhs->m_partIndex && lhsBounds.m_minX < rhsBounds.m_maxX &&
					rhsBounds.m_minX < lhsBounds.m_maxX && lhsBounds.m_minY < rhsBounds.m_maxY &&
					rhsBounds.m_minY < lhsBounds.m_maxY) {
					CLIP_BUILD_PRIMITIVE_MIN(m_y, m_minY, m_maxY, m_x, SET_SPLIT_VERTEX_POSITION_Y);
					CLIP_BUILD_PRIMITIVE_MAX(m_y, m_minY, m_maxY, m_x, SET_SPLIT_VERTEX_POSITION_Y);
					CLIP_BUILD_PRIMITIVE_MIN(m_x, m_minX, m_maxX, m_y, SET_SPLIT_VERTEX_POSITION_X);
					CLIP_BUILD_PRIMITIVE_MAX(m_x, m_minX, m_maxX, m_y, SET_SPLIT_VERTEX_POSITION_X);
					REMOVE_MATCHED_BUILD_PRIMITIVES();
				}
			}
		}
	}

	{
		LegoS32 planePrimitiveCount = 0;
		for (i = 0; i < m_buildPrimitiveCount; i++) {
			BuildPrimitive* primitive = m_buildPrimitiveOrder[i];
			if ((primitive->m_flags & 0x85) == 0x85 && primitive->m_vertexCount == 4) {
				m_buildPrimitiveOrder[i] = m_buildPrimitiveOrder[planePrimitiveCount++];
				m_buildPrimitiveOrder[planePrimitiveCount - 1] = primitive;
			}
		}

		for (LegoS32 lhsIndex = 0; lhsIndex < planePrimitiveCount - 1; lhsIndex++) {
			BuildPrimitiveBounds lhsBounds;
			GetBuildPrimitiveBounds(m_buildPrimitiveOrder[lhsIndex], &lhsBounds);

			for (LegoS32 rhsIndex = lhsIndex + 1; rhsIndex < planePrimitiveCount; rhsIndex++) {
				BuildPrimitiveBounds rhsBounds;
				GetBuildPrimitiveBounds(m_buildPrimitiveOrder[rhsIndex], &rhsBounds);

				BuildPrimitive* lhs = m_buildPrimitiveOrder[lhsIndex];
				BuildPrimitive* rhs = m_buildPrimitiveOrder[rhsIndex];
				if (lhsBounds.m_minY == rhsBounds.m_minY && lhs->m_partIndex != rhs->m_partIndex &&
					lhsBounds.m_minX < rhsBounds.m_maxX && rhsBounds.m_minX < lhsBounds.m_maxX &&
					lhsBounds.m_minZ < rhsBounds.m_maxZ && rhsBounds.m_minZ < lhsBounds.m_maxZ) {
					CLIP_BUILD_PRIMITIVE_MIN(m_z, m_minZ, m_maxZ, m_x, SET_SPLIT_VERTEX_POSITION_Z);
					CLIP_BUILD_PRIMITIVE_MAX(m_z, m_minZ, m_maxZ, m_x, SET_SPLIT_VERTEX_POSITION_Z);
					CLIP_BUILD_PRIMITIVE_MIN(m_x, m_minX, m_maxX, m_z, SET_SPLIT_VERTEX_POSITION_X);
					CLIP_BUILD_PRIMITIVE_MAX(m_x, m_minX, m_maxX, m_z, SET_SPLIT_VERTEX_POSITION_X);
					REMOVE_MATCHED_BUILD_PRIMITIVES();
				}
			}
		}
	}

	LegoS32 result = m_buildPrimitiveCount;
	{
		LegoS32 planePrimitiveCount = 0;
		for (i = 0; i < result; i++) {
			BuildPrimitive* primitive = m_buildPrimitiveOrder[i];
			if ((primitive->m_flags & 0x83) == 0x83 && primitive->m_vertexCount == 4) {
				m_buildPrimitiveOrder[i] = m_buildPrimitiveOrder[planePrimitiveCount++];
				m_buildPrimitiveOrder[planePrimitiveCount - 1] = primitive;
			}
			result = m_buildPrimitiveCount;
		}

		for (LegoS32 lhsIndex = 0; lhsIndex < planePrimitiveCount - 1; lhsIndex++) {
			BuildPrimitiveBounds lhsBounds;
			GetBuildPrimitiveBounds(m_buildPrimitiveOrder[lhsIndex], &lhsBounds);

			for (LegoS32 rhsIndex = lhsIndex + 1; rhsIndex < planePrimitiveCount; rhsIndex++) {
				BuildPrimitiveBounds rhsBounds;
				GetBuildPrimitiveBounds(m_buildPrimitiveOrder[rhsIndex], &rhsBounds);

				BuildPrimitive* lhs = m_buildPrimitiveOrder[lhsIndex];
				BuildPrimitive* rhs = m_buildPrimitiveOrder[rhsIndex];
				if (lhsBounds.m_minX == rhsBounds.m_minX && lhs->m_partIndex != rhs->m_partIndex &&
					lhsBounds.m_minY < rhsBounds.m_maxY && rhsBounds.m_minY < lhsBounds.m_maxY &&
					lhsBounds.m_minZ < rhsBounds.m_maxZ && rhsBounds.m_minZ < lhsBounds.m_maxZ) {
					CLIP_BUILD_PRIMITIVE_MIN(m_z, m_minZ, m_maxZ, m_y, SET_SPLIT_VERTEX_POSITION_Z);
					CLIP_BUILD_PRIMITIVE_MAX(m_z, m_minZ, m_maxZ, m_y, SET_SPLIT_VERTEX_POSITION_Z);
					CLIP_BUILD_PRIMITIVE_MIN(m_y, m_minY, m_maxY, m_z, SET_SPLIT_VERTEX_POSITION_Y);
					CLIP_BUILD_PRIMITIVE_MAX(m_y, m_minY, m_maxY, m_z, SET_SPLIT_VERTEX_POSITION_Y);
					REMOVE_MATCHED_BUILD_PRIMITIVES();
				}
			}

			result = planePrimitiveCount - 1;
		}
	}

#undef REMOVE_MATCHED_BUILD_PRIMITIVES
#undef CLIP_BUILD_PRIMITIVE_MAX
#undef CLIP_BUILD_PRIMITIVE_MIN
#undef SET_SPLIT_VERTEX_POSITION_Z
#undef SET_SPLIT_VERTEX_POSITION_Y
#undef SET_SPLIT_VERTEX_POSITION_X
#undef ALLOCATE_OUTSIDE_BUILD_PRIMITIVE_MAX
#undef ALLOCATE_OUTSIDE_BUILD_PRIMITIVE_MIN
#undef ROTATE_BUILD_PRIMITIVE_TO_MAX
#undef ROTATE_BUILD_PRIMITIVE_TO_MIN
#undef SWAP_ACTIVE_BUILD_PRIMITIVES

	return result;
}

// FUNCTION: LEGORACERS 0x004972a0
void CarBuildModel::InterpolateBuildVertex(
	BuildVertex* p_dest,
	BuildVertex* p_left,
	BuildVertex* p_right,
	LegoFloat p_leftScale,
	LegoFloat p_rightScale
)
{
	LegoFloat leftX = p_left->m_textureCoordinate.m_x;
	LegoFloat rightX = p_right->m_textureCoordinate.m_x;
	p_dest->m_textureCoordinate.m_x = leftX * p_leftScale + rightX * p_rightScale;

	LegoFloat leftY = p_left->m_textureCoordinate.m_y;
	LegoFloat rightY = p_right->m_textureCoordinate.m_y;
	p_dest->m_textureCoordinate.m_y = leftY * p_leftScale + rightY * p_rightScale;

	p_dest->m_normalX = static_cast<LegoS8>(p_left->m_normalX * p_leftScale + p_right->m_normalX * p_rightScale);
	p_dest->m_normalY = static_cast<LegoS8>(p_left->m_normalY * p_leftScale + p_right->m_normalY * p_rightScale);
	p_dest->m_normalZ = static_cast<LegoS8>(p_left->m_normalZ * p_leftScale + p_right->m_normalZ * p_rightScale);
}

// FUNCTION: LEGORACERS 0x00497360
LegoS32 CarBuildModel::BuildBatches(LegoS8 p_buildFlags)
{
	::memset(g_carBuildModelVertexUses, 0, sizeof(g_carBuildModelVertexUses));

	LegoS32 primitiveIndex = 0;
	LegoS32 previousMaterialIndex = -1;
	LegoS32 accumulatedReferenceCount = 0;
	m_batchVertexCount = 0;

	LegoS32 vertexCount = 2;
	LegoS32 materialRunEnd = primitiveIndex;
	LegoS32 currentMaterialIndex = previousMaterialIndex;
	LegoS32 lastPrimitiveIndex = m_buildPrimitiveCount - 1;

	if (lastPrimitiveIndex <= 0) {
		return lastPrimitiveIndex;
	}

	while (TRUE) {
		LegoS32 batchVertexCount = m_batchVertexCount;
		LegoS32 bestAddedVertexCount = 0x42;
		LegoS32 bestPrimitiveIndex = 0;

		if (batchVertexCount) {
			BuildPrimitive** primitiveOrder = m_buildPrimitiveOrder;
			if (previousMaterialIndex == primitiveOrder[primitiveIndex]->m_materialIndex) {
				LegoS32 searchEnd;
				if (p_buildFlags & 0x80) {
					searchEnd = materialRunEnd;
				}
				else {
					searchEnd = primitiveIndex + c_modelBatchVertexCapacity;
					if (searchEnd > materialRunEnd) {
						searchEnd = materialRunEnd;
					}
				}

				for (LegoS32 candidate = primitiveIndex; candidate < searchEnd; candidate++) {
					BuildPrimitive* primitive = primitiveOrder[candidate];
					LegoS32 addedVertexCount = primitive->m_vertexCount;
					vertexCount = addedVertexCount;

					for (LegoS32 i = 0; i < vertexCount; i++) {
						if (g_carBuildModelVertexUses[primitive->m_vertexIndices[i]].m_inBatch) {
							addedVertexCount--;
						}
					}

					if (addedVertexCount == 0) {
						bestPrimitiveIndex = candidate;
						bestAddedVertexCount = 0;
						candidate = m_buildPrimitiveCount;
					}
					else if (addedVertexCount < bestAddedVertexCount) {
						bestAddedVertexCount = addedVertexCount;
						bestPrimitiveIndex = candidate;
					}
				}
			}
		}

		if (previousMaterialIndex != m_buildPrimitiveOrder[primitiveIndex]->m_materialIndex) {
			if (batchVertexCount > 0) {
				for (LegoS32 i = 0; i < m_batchVertexCount; i++) {
					g_carBuildModelVertexUses[m_batchBuildVertexIndices[i]].m_inBatch = FALSE;
				}
			}

			currentMaterialIndex = m_buildPrimitiveOrder[primitiveIndex]->m_materialIndex;
			materialRunEnd = primitiveIndex;
			if (materialRunEnd < m_buildPrimitiveCount) {
				while (TRUE) {
					BuildPrimitive* primitive = m_buildPrimitiveOrder[materialRunEnd];
					if (currentMaterialIndex != primitive->m_materialIndex) {
						break;
					}

					vertexCount = primitive->m_vertexCount;
					for (LegoS32 i = 0; i < vertexCount; i++) {
						g_carBuildModelVertexUses[primitive->m_vertexIndices[i]].m_referenceCount++;
					}

					materialRunEnd++;
					if (materialRunEnd >= m_buildPrimitiveCount) {
						break;
					}
				}
			}
		}

		if (static_cast<LegoU32>(bestAddedVertexCount + m_batchVertexCount) > c_modelBatchVertexCapacity) {
			bestPrimitiveIndex = 0;
			LegoS32 bestReferenceCount = 0x7fffffff;
			for (LegoS32 candidate = primitiveIndex; candidate < materialRunEnd; candidate++) {
				BuildPrimitive* primitive = m_buildPrimitiveOrder[candidate];

				if (vertexCount > 0) {
					for (LegoS32 i = 0; i < vertexCount; i++) {
						accumulatedReferenceCount +=
							g_carBuildModelVertexUses[primitive->m_vertexIndices[i]].m_referenceCount;
					}
				}

				if (accumulatedReferenceCount < bestReferenceCount) {
					bestReferenceCount = accumulatedReferenceCount;
					bestPrimitiveIndex = candidate;
				}
			}

			if (m_batchVertexCount > 0) {
				for (LegoS32 i = 0; i < m_batchVertexCount; i++) {
					g_carBuildModelVertexUses[m_batchBuildVertexIndices[i]].m_inBatch = FALSE;
				}
			}
			m_batchVertexCount = 0;
		}

		if (bestPrimitiveIndex) {
			BuildPrimitive* primitive = m_buildPrimitiveOrder[primitiveIndex];
			m_buildPrimitiveOrder[primitiveIndex] = m_buildPrimitiveOrder[bestPrimitiveIndex];
			m_buildPrimitiveOrder[bestPrimitiveIndex] = primitive;
		}

		BuildPrimitive* primitive = m_buildPrimitiveOrder[primitiveIndex];
		for (LegoS32 i = 0; i < primitive->m_vertexCount; i++) {
			LegoS32 vertexIndex = primitive->m_vertexIndices[i];
			g_carBuildModelVertexUses[vertexIndex].m_referenceCount--;
			if (!g_carBuildModelVertexUses[vertexIndex].m_inBatch) {
				g_carBuildModelVertexUses[vertexIndex].m_inBatch = TRUE;
				m_batchBuildVertexIndices[m_batchVertexCount] = vertexIndex;
				m_batchVertexCount++;
			}
		}

		primitiveIndex++;
		if (primitiveIndex >= m_buildPrimitiveCount - 1) {
			return m_buildPrimitiveCount - 1;
		}
		previousMaterialIndex = currentMaterialIndex;
	}
}

// FUNCTION: LEGORACERS 0x00497690
void CarBuildModel::FinalizeBuild(LegoU8 p_buildFlags)
{
	LegoS32 i;

	for (i = m_buildPrimitiveCount; i < c_buildPrimitiveCapacity; i++) {
		m_buildPrimitiveOrder[i] = &m_buildPrimitives[i];
	}

	g_carBuildModelSortVertices = m_buildVertices;

	if (p_buildFlags & c_finalizeResolveIntersectionsFlag) {
		ResolvePrimitiveIntersections();
		if (m_buildStatus & c_buildStatusOverflow) {
			return;
		}
	}

	if (p_buildFlags & c_finalizeCullSingleMaterialFlag) {
		for (i = 0; i < m_buildPrimitiveCount; i++) {
			if (m_buildPrimitiveOrder[i]->m_commandFlags == c_buildPrimitiveCommandMaterial1) {
				m_buildPrimitiveCount--;
				i--;
				BuildPrimitive* primitive = m_buildPrimitiveOrder[i + 1];
				m_buildPrimitiveOrder[i + 1] = m_buildPrimitiveOrder[m_buildPrimitiveCount];
				m_buildPrimitiveOrder[m_buildPrimitiveCount] = primitive;
			}
		}
	}

	LegoS32 splitPrimitiveCount = m_buildPrimitiveCount;
	for (i = 0; i < splitPrimitiveCount; i++) {
		if (m_buildPrimitiveOrder[i]->m_vertexCount == 4) {
			m_buildPrimitiveOrder[i]->m_vertexCount = 3;

			*m_buildPrimitiveOrder[m_buildPrimitiveCount] = *m_buildPrimitiveOrder[i];
			m_buildPrimitiveOrder[m_buildPrimitiveCount]->m_vertexIndices[0] =
				m_buildPrimitiveOrder[i]->m_vertexIndices[2];
			m_buildPrimitiveOrder[m_buildPrimitiveCount]->m_vertexIndices[2] =
				m_buildPrimitiveOrder[i]->m_vertexIndices[3];
			m_buildPrimitiveCount++;

			if (m_buildPrimitiveCount >= c_buildPrimitiveCapacity) {
				m_buildStatus |= c_buildStatusOverflow;
				return;
			}
		}
	}

	::qsort(m_buildPrimitiveOrder, m_buildPrimitiveCount, sizeof(BuildPrimitive*), ComparePrimitiveDrawOrder);

	if (p_buildFlags & c_finalizePostSortFlag) {
		BuildBatches(p_buildFlags);
	}
}
