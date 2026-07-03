#include "model/carbuildmodel.h"

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
#include "model/legocolortable.h"
#include "render/gold3drenderdevice.h"
#include "surface/color.h"
#include "surface/gold3dtexture.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(CarBuildModel, 0x2030)
DECOMP_SIZE_ASSERT(CarBuildModel::Placement, 0x30)
DECOMP_SIZE_ASSERT(CarBuildModel::PieceGrid, 0x14)
DECOMP_SIZE_ASSERT(CarBuildModel::PieceGrid::Cell, 0x0c)
DECOMP_SIZE_ASSERT(CarBuildModel::BuildVertex, 0x28)
DECOMP_SIZE_ASSERT(CarBuildModel::BuildPrimitive, 0x10)
DECOMP_SIZE_ASSERT(CarBuildModel::BuildPrimitiveBounds, 0x18)
DECOMP_SIZE_ASSERT(CarBuildModel::VertexUse, 0x04)
DECOMP_SIZE_ASSERT(CarBuildModel::OverlayCell, 0x01)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

static const LegoS32 g_highPieceTypeBase = 0x800;

// GLOBAL: LEGORACERS 0x004ceba4
static CarBuildModel::BuildVertex* g_carBuildModelSortVertices;

// GLOBAL: LEGORACERS 0x004ceba8
static CarBuildModel* g_carBuildModelCellCallback;

// GLOBAL: LEGORACERS 0x004c7674
static CarBuildModel::VertexUse g_carBuildModelVertexUses[CarBuildModel::c_buildVertexCapacity];

// GLOBAL: LEGORACERS 0x004b4930
static const LegoFloat g_carBuildModelMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b4934
static const LegoFloat g_carBuildModelNormalScale = 1.0f / 127.0f;

// GLOBAL: LEGORACERS 0x004b480c
static const LegoFloat g_carBuildModelNegativePlaneEpsilon = -0.0049999999f;

// GLOBAL: LEGORACERS 0x004b0538
extern const LegoFloat g_carBuildModelHeightScale = 0.4f;

// GLOBAL: LEGORACERS 0x004b053c
extern const LegoFloat g_carBuildModelTextureCoordinateScale = 0.25f;

// GLOBAL: LEGORACERS 0x004b4938
static const LegoFloat g_carBuildModelNegativeHeightScale = -0.4f;

// GLOBAL: LEGORACERS 0x004b4940
static const LegoFloat g_carBuildModelCenterYOffset = 2.5f;

// GLOBAL: LEGORACERS 0x004b4944
static const LegoFloat g_carBuildModelCenterXOffset = 4.5f;

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

// STUB: LEGORACERS 0x00495160
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

// STUB: LEGORACERS 0x00497360
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

// FUNCTION: LEGORACERS 0x00499530
void CarBuildModel::Placement::Reset()
{
	m_unk0x00 = 0;
	m_pieceRecord = NULL;
	m_rotation = 0;
	m_anchor = 0;
}

// FUNCTION: LEGORACERS 0x00499540
CarBuildModel::Placement::Placement()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00499550
CarBuildModel::Placement::~Placement()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00499560
void CarBuildModel::Placement::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CarBuildModel::Placement::FUN_004513d0(CarBuildModel*)
{
}

// FUNCTION: LEGORACERS 0x00499570
void CarBuildModel::Placement::ToGridPosition()
{
	if (m_rotation & 1) {
		switch (m_anchor) {
		case 0:
			m_gridX = m_x;
			m_gridY = m_y;
			return;
		case 1:
			m_gridX = m_x;
			m_gridY = m_y - m_width;
			return;
		case 2:
			m_gridX = m_x - m_height;
			m_gridY = m_y;
			return;
		case 3:
			m_gridX = m_x - m_height;
			m_gridY = m_y - m_width;
			return;
		}
	}
	else {
		switch (m_anchor) {
		case 0:
			m_gridX = m_x;
			m_gridY = m_y;
			return;
		case 1:
			m_gridX = m_x;
			m_gridY = m_y - m_height;
			return;
		case 2:
			m_gridX = m_x - m_width;
			m_gridY = m_y;
			return;
		case 3:
			m_gridX = m_x - m_width;
			m_gridY = m_y - m_height;
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x00499640
void CarBuildModel::Placement::FromGridPosition()
{
	if (m_rotation & 1) {
		switch (m_anchor) {
		case 0:
			m_x = m_gridX;
			m_y = m_gridY;
			return;
		case 1:
			m_x = m_gridX;
			m_y = m_gridY + m_width;
			return;
		case 2:
			m_x = m_gridX + m_height;
			m_y = m_gridY;
			return;
		case 3:
			m_x = m_gridX + m_height;
			m_y = m_gridY + m_width;
			return;
		}
	}
	else {
		switch (m_anchor) {
		case 0:
			m_x = m_gridX;
			m_y = m_gridY;
			return;
		case 1:
			m_x = m_gridX;
			m_y = m_gridY + m_height;
			return;
		case 2:
			m_x = m_gridX + m_width;
			m_y = m_gridY;
			return;
		case 3:
			m_x = m_gridX + m_width;
			m_y = m_gridY + m_height;
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x00499710
void CarBuildModel::Placement::SetAnchor(LegoS32 p_anchor)
{
	LegoS32 isRotated = m_rotation & 1;

	if (isRotated) {
		switch (m_anchor) {
		case 1:
			m_y -= m_width;
			break;
		case 2:
			m_x -= m_height;
			break;
		case 3:
			m_x -= m_height;
			m_y -= m_width;
			break;
		}
	}
	else {
		switch (m_anchor) {
		case 1:
			m_y -= m_height;
			break;
		case 2:
			m_x -= m_width;
			break;
		case 3:
			m_x -= m_width;
			m_y -= m_height;
			break;
		}
	}

	m_anchor = p_anchor;

	if (isRotated) {
		switch (p_anchor) {
		case 3:
			m_x += m_height;
			// fall through
		case 1:
			m_y = m_y + m_width;
			return;
		case 2:
			m_x += m_height;
			return;
		}
	}
	else {
		switch (p_anchor) {
		case 3:
			m_x += m_width;
			// fall through
		case 1:
			m_y = m_y + m_height;
			return;
		case 2:
			m_x += m_width;
			return;
		}
	}
}

// FUNCTION: LEGORACERS 0x004997e0
void CarBuildModel::Placement::SelectAnchorQuadrant()
{
	switch (m_anchor) {
	case 0:
		if (m_x >= 5) {
			if (m_y >= 3) {
				SetAnchor(3);
			}
			else {
				SetAnchor(2);
			}
		}
		else if (m_y >= 3) {
			SetAnchor(1);
		}
		break;
	case 1:
		if (m_x >= 5) {
			if (m_y >= 3) {
				SetAnchor(3);
			}
			else {
				SetAnchor(2);
			}
		}
		else if (m_y < 3) {
			SetAnchor(0);
		}
		break;
	case 2:
		if (m_x < 5) {
			if (m_y >= 3) {
				SetAnchor(1);
			}
			else {
				SetAnchor(0);
			}
		}
		else if (m_y >= 3) {
			SetAnchor(3);
		}
		break;
	case 3:
		if (m_x < 5) {
			if (m_y >= 3) {
				SetAnchor(1);
			}
			else {
				SetAnchor(0);
			}
		}
		else if (m_y < 3) {
			SetAnchor(2);
		}
		break;
	}
}

// FUNCTION: LEGORACERS 0x00499890
void CarBuildModel::Placement::SetPiece(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_partType
)
{
	m_width = p_pieceRecord->GetWidth();
	m_height = p_pieceRecord->GetHeight();
	m_colorRecordIndex = p_colorRecordIndex;
	m_partType = p_partType;

	if (m_pieceRecord == NULL) {
		m_anchor = 0;
		m_rotation = 0;
		m_gridX = (10 - m_width) >> 1;
		m_gridY = (6 - m_height) >> 1;
		if (m_gridX < 0 || m_gridY < 0) {
			m_rotation = 1;
			m_gridX = (10 - m_height) >> 1;
			m_gridY = (6 - m_width) >> 1;
		}
	}
	else {
		if (m_rotation & 1) {
			if (m_width > 6 || m_height > 10) {
				m_rotation++;
			}
		}
		else if (m_width > 10 || m_height > 6) {
			m_rotation++;
		}

		m_rotation &= 3;

		if (m_rotation & 1) {
			switch (m_anchor) {
			case 0:
				m_gridX = m_x;
				m_gridY = m_y;
				break;
			case 1:
				m_gridX = m_x;
				m_gridY = m_y - m_width;
				break;
			case 2:
				m_gridX = m_x - m_height;
				m_gridY = m_y;
				break;
			case 3:
				m_gridX = m_x - m_height;
				m_gridY = m_y - m_width;
				break;
			}

			if (m_gridX + m_height > 10) {
				m_gridX = 10 - m_height;
			}
			if (m_gridY + m_width > 6) {
				m_gridY = 6 - m_width;
			}
		}
		else {
			switch (m_anchor) {
			case 0:
				m_gridX = m_x;
				m_gridY = m_y;
				break;
			case 1:
				m_gridX = m_x;
				m_gridY = m_y - m_height;
				break;
			case 2:
				m_gridX = m_x - m_width;
				m_gridY = m_y;
				break;
			case 3:
				m_gridX = m_x - m_width;
				m_gridY = m_y - m_height;
				break;
			}

			if (m_gridX + m_width > 10) {
				m_gridX = 10 - m_width;
			}
			if (m_gridY + m_height > 6) {
				m_gridY = 6 - m_height;
			}
		}
	}

	if (m_gridX < 0) {
		m_gridX = 0;
	}
	if (m_gridY < 0) {
		m_gridY = 0;
	}

	m_pieceRecord = p_pieceRecord;
	FromGridPosition();
	SelectAnchorQuadrant();
}

// FUNCTION: LEGORACERS 0x00499a60
void CarBuildModel::Placement::ClampToGrid()
{
	ToGridPosition();

	if (m_gridX < 0) {
		m_gridX = 0;
	}
	if (m_gridY < 0) {
		m_gridY = 0;
	}

	if (m_rotation & 1) {
		if (m_gridX + m_height > 10) {
			m_gridX = 10 - m_height;
		}
		if (m_gridY + m_width > 6) {
			m_gridY = 6 - m_width;
		}
	}
	else {
		if (m_gridX + m_width > 10) {
			m_gridX = 10 - m_width;
		}
		if (m_gridY + m_height > 6) {
			m_gridY = 6 - m_height;
		}
	}

	FromGridPosition();
}

// FUNCTION: LEGORACERS 0x00499b00
void CarBuildModel::Placement::Rotate()
{
	if (m_rotation & 1) {
		if (m_height > 6 || m_width > 10) {
			m_rotation++;
		}
	}
	else if (m_width > 6 || m_height > 10) {
		m_rotation++;
	}

	m_rotation = (m_rotation + 1) & 3;
	ClampToGrid();
}

// FUNCTION: LEGORACERS 0x00499b40
void CarBuildModel::Placement::MoveRight()
{
	if (m_rotation & 1) {
		if (m_gridX + m_height < 10) {
			m_gridX++;
			FromGridPosition();
			SelectAnchorQuadrant();
			return;
		}
	}
	else if (m_gridX + m_width < 10) {
		m_gridX++;
		FromGridPosition();
		SelectAnchorQuadrant();
	}
}

// FUNCTION: LEGORACERS 0x00499b90
void CarBuildModel::Placement::MoveLeft()
{
	if (m_gridX > 0) {
		m_gridX--;
		FromGridPosition();
		SelectAnchorQuadrant();
	}
}

// FUNCTION: LEGORACERS 0x00499bb0
void CarBuildModel::Placement::MoveForward()
{
	if (m_rotation & 1) {
		if (m_gridY + m_width < 6) {
			m_gridY++;
			FromGridPosition();
			SelectAnchorQuadrant();
			return;
		}
	}
	else if (m_gridY + m_height < 6) {
		m_gridY++;
		FromGridPosition();
		SelectAnchorQuadrant();
	}
}

// FUNCTION: LEGORACERS 0x00499c00
void CarBuildModel::Placement::MoveBackward()
{
	if (m_gridY > 0) {
		m_gridY--;
		FromGridPosition();
		SelectAnchorQuadrant();
	}
}

// FUNCTION: LEGORACERS 0x00499c20
void CarBuildModel::Placement::MoveX(LegoS32 p_delta)
{
	if (p_delta > 0) {
		for (LegoS32 i = p_delta; i != 0; i--) {
			MoveRight();
		}
	}
	else if (p_delta < 0) {
		LegoS32 i = -p_delta;
		do {
			MoveLeft();
		} while (--i != 0);
	}
}

// FUNCTION: LEGORACERS 0x00499c60
void CarBuildModel::Placement::MoveY(LegoS32 p_delta)
{
	if (p_delta > 0) {
		for (LegoS32 i = p_delta; i != 0; i--) {
			MoveForward();
		}
	}
	else if (p_delta < 0) {
		LegoS32 i = -p_delta;
		do {
			MoveBackward();
		} while (--i != 0);
	}
}

// FUNCTION: LEGORACERS 0x00499ca0
void CarBuildModel::Placement::GetPlacement(LegoS32* p_x, LegoS32* p_y, LegoS32* p_rotation)
{
	*p_x = m_gridX;
	*p_y = m_gridY;
	*p_rotation = m_rotation;
}

// FUNCTION: LEGORACERS 0x00499cc0
void CarBuildModel::Placement::SetPlacement(LegoS32 p_x, LegoS32 p_y, LegoS32 p_rotation, LegoS32 p_anchor)
{
	m_x = p_x;
	m_y = p_y;
	m_rotation = p_rotation & 3;
	m_anchor = p_anchor & 3;
	SetPiece(m_pieceRecord, m_colorRecordIndex, m_partType);
}

// FUNCTION: LEGORACERS 0x00415f40 FOLDED
void CarBuildModel::PieceGrid::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00499d00
void CarBuildModel::Reset()
{
	m_pieceLibrary = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_model = NULL;
	m_modelVertices = 0;
	m_modelTriangles = 0;
	m_unk0xd0 = 0;
	m_placedPieceCount = 0;
	m_buildFlags = 0;
	m_overlayModel = NULL;
	m_overlayHeight = 0;
	m_overlayVisible = 0;
	m_colorTable = NULL;
	UpdateOffset(NULL);
	m_hasHighBasePiece = FALSE;
	m_baseTextureEnabled = TRUE;
	m_highBasePiece = NULL;
}

// FUNCTION: LEGORACERS 0x00499d70
CarBuildModel::CarBuildModel()
{
	m_pieceList.m_pieceGrid = &m_pieceGrid;
	m_pieceGrid.m_pieceList = &m_pieceList;
	m_buildVertices = NULL;
	m_buildPrimitives = NULL;
	m_buildPrimitiveOrder = NULL;
	::memset(m_batchVertexSlotByBuildVertex, 0, sizeof(m_batchVertexSlotByBuildVertex));
	Reset();
}

// FUNCTION: LEGORACERS 0x00499e20
CarBuildModel::~CarBuildModel()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00499e80
void CarBuildModel::SetColorTable(LegoColorTable* p_colorTable)
{
	m_colorTable = p_colorTable;
	if (p_colorTable != NULL) {
		m_modelEntity.SetPrimaryMaterialTable(p_colorTable->GetMaterialTable());
	}
	else {
		m_modelEntity.SetPrimaryMaterialTable(NULL);
	}
}

// FUNCTION: LEGORACERS 0x00499eb0
void CarBuildModel::InitializeModel(GolModelBase* p_model)
{
	p_model->Allocate(m_renderer, 2, c_buildVertexCapacity, c_buildPrimitiveCapacity, 1610, 0);
}

// FUNCTION: LEGORACERS 0x00499ee0
void CarBuildModel::AcquireBuffers()
{
	InitializeModel(m_model);
	AllocateBuffers();
}

// FUNCTION: LEGORACERS 0x00499f00
void CarBuildModel::ReleaseBuffers()
{
	m_model->Destroy();
	FreeBuffers();
}

// FUNCTION: LEGORACERS 0x00499f20
void CarBuildModel::AllocateBuffers()
{
	m_buildVertices = new BuildVertex[c_buildVertexCapacity];
	m_buildPrimitives = new BuildPrimitive[c_buildPrimitiveCapacity];
	m_buildPrimitiveOrder = new BuildPrimitive*[c_buildPrimitiveCapacity];

	for (LegoS32 i = 0; i < c_buildVertexCapacity; i++) {
		m_buildVertices[i].m_index = static_cast<LegoU16>(i);
	}
}

// FUNCTION: LEGORACERS 0x00499f80
void CarBuildModel::FreeBuffers()
{
	delete[] m_buildVertices;
	delete[] m_buildPrimitives;
	delete[] m_buildPrimitiveOrder;
	m_buildVertices = NULL;
	m_buildPrimitives = NULL;
	m_buildPrimitiveOrder = NULL;
}

// FUNCTION: LEGORACERS 0x00499fc0
LegoBool32 CarBuildModel::Initialize(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	LegoPieceLibrary* p_pieceLibrary,
	LegoColorTable* p_colorTable
)
{
	GolD3DRenderDevice* renderer = p_renderer;

	if (IsInitialized()) {
		Destroy();
	}

	SetColorTable(p_colorTable);
	m_pieceLibrary = p_pieceLibrary;
	m_golExport = p_golExport;
	m_model = m_golExport->CreateModel();
	m_renderer = renderer;
	AcquireBuffers();
	m_modelEntity.SetPrimaryModel(m_model, g_carBuildModelMaxFloat);

	m_overlayModel = m_golExport->CreateModel();
	m_overlayModel->Allocate(renderer, 1, 384, 192, 112, 2);
	m_overlayEntity.SetPrimaryModel(m_overlayModel, g_carBuildModelMaxFloat);
	m_overlayEntity.SetPrimaryMaterialTable(m_overlayModel->GetMaterialTable());

	GolMaterialLibrary* materialLibrary = m_colorTable->GetWorldDatabase()->GetMaterialLibrary(1);
	m_overlayModel->GetMaterialTable()->SetEntry(0, materialLibrary->GetItem(0));
	m_overlayModel->GetMaterialTable()->SetEntry(1, materialLibrary->GetItem(1));

	SetDefaultOffset();
	m_pieceGrid.Initialize(10, 6);

	return m_pieceList.Initialize(64);
}

// FUNCTION: LEGORACERS 0x0049a0e0
LegoBool32 CarBuildModel::IsInitialized()
{
	return m_golExport != NULL;
}

// FUNCTION: LEGORACERS 0x0049a0f0
void CarBuildModel::Destroy()
{
	m_pieceGrid.Clear();
	m_pieceList.Clear();
	GetModelEntity()->ResetModelState();
	GetOverlayEntity()->ResetModelState();

	if (m_golExport != NULL) {
		if (m_model != NULL) {
			m_golExport->DestroyModel(m_model);
		}
		if (m_overlayModel != NULL) {
			m_golExport->DestroyModel(m_overlayModel);
		}
	}

	FreeBuffers();
	Reset();
}

// FUNCTION: LEGORACERS 0x0049a160
LegoBool32 CarBuildModel::PlacePiece(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_partType
)
{
	LegoBool32 allowEmpty;
	LegoS32 colorRecordIndex;

	if (p_pieceRecord->m_pieceType < g_highPieceTypeBase) {
		g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
		allowEmpty = TRUE;
		colorRecordIndex = static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % 10;
	}
	else {
		colorRecordIndex = p_colorRecordIndex;
		allowEmpty = FALSE;
	}

	LegoBool32 result =
		m_pieceGrid.AddPiece(p_pieceRecord, p_x, p_y, p_rotation, colorRecordIndex, p_partType, allowEmpty);
	if (result) {
		m_placedPieceCount++;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049a1e0
LegoS32 CarBuildModel::TestPlacement(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation
)
{
	if (p_pieceRecord == NULL) {
		return -1;
	}

	LegoBool32 allowEmpty = p_pieceRecord->m_pieceType < g_highPieceTypeBase;

	LegoS32 height = m_pieceGrid.FindPlacementHeight(p_pieceRecord, p_x, p_y, p_rotation, allowEmpty);
	if (height >= 0) {
		if (m_pieceGrid.HasCollision(p_pieceRecord, p_x, p_y, p_rotation, height)) {
			return -5;
		}

		if (height + p_pieceRecord->GetMaxCellValue() > 15) {
			return -6;
		}

		if (m_placedPieceCount >= 64) {
			return -7;
		}
	}

	return height;
}

// FUNCTION: LEGORACERS 0x0049a290
void CarBuildModel::BeginModelWrite(GolModelBase* p_model)
{
	m_currentMaterialIndex = 0x7fffffff;
	m_modelGroupCount = 0;
	m_modelVertexCount = 0;
	m_modelTriangleCount = 0;
	m_batchFirstVertex = 0;
	m_batchFirstTriangle = 0;
	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;

	p_model->GetVertexArray(&m_modelVertices);

	GdbModelIndexArrayBase* indexArray;
	p_model->GetIndexArrayInto(&indexArray);
	m_modelTriangles = static_cast<GdbModelIndexArray*>(indexArray)->GetMutableIndices();
}

// FUNCTION: LEGORACERS 0x0049a300
void CarBuildModel::FlushBatch(GolModelBase* p_model)
{
	LegoU32 groupIndex = m_modelGroupCount;
	LegoU32 batchVertexCount = m_batchVertexCount;
	LegoU32 batchFirstVertex = m_batchFirstVertex;
	m_modelGroupCount++;

	p_model->GetMutableGroups()[groupIndex] = 0;
	p_model->GetMutableGroups()[groupIndex] |= ((batchVertexCount + 0xffff) << 16) & 0x003f0000;
	p_model->GetMutableGroups()[groupIndex] |= batchFirstVertex & 0xffff;
	p_model->SetDirty(TRUE);

	LegoU32 batchTriangleCount = m_batchTriangleCount;
	LegoU32 groupIndex2 = m_modelGroupCount;
	LegoU32 batchFirstTriangle = m_batchFirstTriangle;
	m_modelGroupCount++;
	p_model->GetMutableGroups()[groupIndex2] = 0x20000000;
	p_model->GetMutableGroups()[groupIndex2] |= (batchTriangleCount & 0x7f) << 16;
	p_model->GetMutableGroups()[groupIndex2] |= batchFirstTriangle & 0xffff;
	p_model->SetDirty(TRUE);

	LegoU32 modelTriangleCount = m_modelTriangleCount;
	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;
	LegoU32 modelVertexCount = m_modelVertexCount;
	m_batchFirstVertex = modelVertexCount;
	m_batchFirstTriangle = modelTriangleCount;
}

// FUNCTION: LEGORACERS 0x0049a3e0
void CarBuildModel::EndModelWrite(GolModelBase* p_model)
{
	if (m_batchVertexCount || m_batchTriangleCount) {
		FlushBatch(p_model);
	}

	p_model->GetMutableGroups()[m_modelGroupCount] = 0xc0000000;
	p_model->SetDirty(TRUE);
	p_model->AddFlags(TRUE);
	p_model->AddFlagsWithBounds(TRUE, TRUE);
	m_modelVertices = NULL;
	m_modelTriangles = NULL;
}

// STUB: LEGORACERS 0x0049a450
LegoS16 CarBuildModel::EmitPieceGeometry(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_height,
	LegoS32 p_colorRecordIndex,
	LegoU16 p_partIndex
)
{
	BuildPrimitive* primitive = NULL;
	LegoFloat sourceX;
	LegoFloat sourceY;
	LegoFloat sourceZ;
	LegoS32 i;
	LegoS32 normalIndex = -1;
	LegoBool32 hasTextureIndex = FALSE;
	LegoBool32 hasNormalIndex = FALSE;
	LegoS32 result = m_buildPrimitiveCount;

	if (result < c_buildPrimitiveCapacity) {
		LegoS32 colorMaterialIndex = m_colorTable->GetMaterialIndexForColorRecord(p_colorRecordIndex);
		LegoFloat xOrigin = static_cast<LegoFloat>(p_x);
		LegoFloat yOrigin = static_cast<LegoFloat>(p_y);
		LegoFloat zOrigin = static_cast<LegoFloat>(p_height);
		LegoS32 rotation = p_rotation & 3;
		LegoPieceLibrary* library = p_pieceRecord->m_library;

		BuildVertex vertex;
		vertex.m_position.m_x = 0.0f;
		vertex.m_position.m_y = 0.0f;
		vertex.m_position.m_z = 0.0f;
		vertex.m_textureCoordinate.m_x = 0.0f;
		vertex.m_textureCoordinate.m_y = 0.0f;
		vertex.m_normalX = 127;
		vertex.m_normalY = 0;
		vertex.m_normalZ = 0;

		LegoFloat width = static_cast<LegoFloat>(p_pieceRecord->GetWidth());
		LegoFloat pieceHeight = static_cast<LegoFloat>(p_pieceRecord->GetHeight());
		LegoS32 remaining = p_pieceRecord->m_indexCommandCount;
		const LegoU16* cursor = library->GetIndexCursor(p_pieceRecord->m_indexOffset);

		if (remaining != 0) {
			do {
				LegoS32 primitiveCount = m_buildPrimitiveCount;
				LegoU32 command = *cursor++;
				LegoS32 mode = command & c_indexCommandModeMask;

				if (mode == c_indexCommandQuad) {
					m_buildPrimitiveCount = primitiveCount - 1;
					primitive->m_vertexCount = 4;

					LegoS32 coordinateIndex = *cursor++;
					if (!library->IsColorBlack(coordinateIndex)) {
						primitive->m_flags &= ~c_buildPrimitiveFlagAllBlack;
					}

					library->GetColor(coordinateIndex, &sourceX, &sourceY, &sourceZ);

					switch (rotation) {
					case 0:
						vertex.m_position.m_x = sourceX + xOrigin;
						vertex.m_position.m_y = sourceY + yOrigin;
						break;
					case 1:
						vertex.m_position.m_x = sourceY + xOrigin;
						vertex.m_position.m_y = (width - sourceX) + yOrigin;
						break;
					case 2:
						vertex.m_position.m_x = (width - sourceX) + xOrigin;
						vertex.m_position.m_y = (pieceHeight - sourceY) + yOrigin;
						break;
					case 3:
						vertex.m_position.m_x = (pieceHeight - sourceY) + xOrigin;
						vertex.m_position.m_y = sourceX + yOrigin;
						break;
					}
					vertex.m_position.m_z = sourceZ + zOrigin;

					LegoFloat missingX =
						m_buildVertices[primitive->m_vertexIndices[1]].m_position.m_x +
						m_buildVertices[primitive->m_vertexIndices[2]].m_position.m_x -
						(vertex.m_position.m_x + m_buildVertices[primitive->m_vertexIndices[0]].m_position.m_x);
					LegoFloat missingY =
						m_buildVertices[primitive->m_vertexIndices[1]].m_position.m_y +
						m_buildVertices[primitive->m_vertexIndices[2]].m_position.m_y -
						(vertex.m_position.m_y + m_buildVertices[primitive->m_vertexIndices[0]].m_position.m_y);
					LegoFloat missingZ =
						m_buildVertices[primitive->m_vertexIndices[1]].m_position.m_z +
						m_buildVertices[primitive->m_vertexIndices[2]].m_position.m_z -
						(vertex.m_position.m_z + m_buildVertices[primitive->m_vertexIndices[0]].m_position.m_z);

					if (missingX == 0.0f && missingY == 0.0f && missingZ == 0.0f) {
						primitive->m_flags |= c_buildPrimitiveFlagParallelogram;
					}

					if (vertex.m_position.m_x != m_buildVertices[primitive->m_vertexIndices[0]].m_position.m_x ||
						vertex.m_position.m_x != m_buildVertices[primitive->m_vertexIndices[1]].m_position.m_x ||
						vertex.m_position.m_x != m_buildVertices[primitive->m_vertexIndices[2]].m_position.m_x) {
						primitive->m_flags &= ~c_buildPrimitiveFlagSameX;
					}
					if (vertex.m_position.m_y != m_buildVertices[primitive->m_vertexIndices[0]].m_position.m_y ||
						vertex.m_position.m_y != m_buildVertices[primitive->m_vertexIndices[1]].m_position.m_y ||
						vertex.m_position.m_y != m_buildVertices[primitive->m_vertexIndices[2]].m_position.m_y) {
						primitive->m_flags &= ~c_buildPrimitiveFlagSameY;
					}
					if (vertex.m_position.m_z != m_buildVertices[primitive->m_vertexIndices[0]].m_position.m_z ||
						vertex.m_position.m_z != m_buildVertices[primitive->m_vertexIndices[1]].m_position.m_z ||
						vertex.m_position.m_z != m_buildVertices[primitive->m_vertexIndices[2]].m_position.m_z) {
						primitive->m_flags &= ~c_buildPrimitiveFlagSameZ;
					}

					if (hasNormalIndex) {
						normalIndex = *cursor++;
					}

					const LegoU8* normal = library->GetColorTriple(normalIndex);
					LegoS8 normalX = static_cast<LegoS8>(normal[0]);
					LegoS8 normalY = static_cast<LegoS8>(normal[1]);
					vertex.m_normalZ = static_cast<LegoS8>(normal[2]);

					switch (rotation) {
					case 0:
						vertex.m_normalX = normalX;
						vertex.m_normalY = normalY;
						break;
					case 1:
						vertex.m_normalX = normalY;
						vertex.m_normalY = -normalX;
						break;
					case 2:
						vertex.m_normalX = -normalX;
						vertex.m_normalY = -normalY;
						break;
					case 3:
						vertex.m_normalX = -normalY;
						vertex.m_normalY = normalX;
						break;
					}

					if (hasTextureIndex) {
						LegoS32 textureIndex = *cursor++;
						library->GetTextureCoordinate(
							textureIndex,
							&vertex.m_textureCoordinate.m_x,
							&vertex.m_textureCoordinate.m_y
						);
					}
					else if (
						!m_savedHasHighBasePiece && m_applyBaseTexture &&
						(primitive->m_commandFlags == c_buildPrimitiveCommandMaterial2 ||
						 primitive->m_commandFlags & c_buildPrimitiveCommandTextureBit)
					) {
						vertex.m_textureCoordinate.m_x =
							(vertex.m_position.m_x - xOrigin) * g_carBuildModelTextureCoordinateScale;
						vertex.m_textureCoordinate.m_y =
							(vertex.m_position.m_y - yOrigin) * g_carBuildModelTextureCoordinateScale;
					}
					else {
						vertex.m_textureCoordinate.m_x = 0.0f;
						vertex.m_textureCoordinate.m_y = 0.0f;
					}

					if (m_buildPrimitiveCount >= c_buildPrimitiveCapacity) {
						m_buildStatus |= c_buildStatusOverflow;
						return static_cast<LegoS16>(m_buildPrimitiveCount);
					}
					primitive->m_vertexIndices[3] = AddBuildVertex(&vertex);
				}
				else {
					primitive = &m_buildPrimitives[primitiveCount];
					m_buildPrimitiveOrder[primitiveCount] = primitive;

					hasTextureIndex = mode == c_indexCommandTextured;
					hasNormalIndex = (command >> 14) & 1;
					LegoBool32 hasSharedNormalIndex = (command >> 15) & 1;
					LegoU16 commandFlags = command & c_buildPrimitiveCommandMask;
					LegoU16 materialIndex = command & 0x07ff;

					primitive->m_vertexCount = 3;
					primitive->m_flags = c_buildPrimitiveInitialFlags;
					primitive->m_commandFlags = commandFlags;
					primitive->m_materialIndex = materialIndex;
					primitive->m_partIndex = p_partIndex;

					if (materialIndex >= 3) {
						if (!m_savedHasHighBasePiece && m_applyBaseTexture &&
							(command & c_buildPrimitiveCommandTextureBit)) {
							primitive->m_materialIndex = materialIndex + 1;
						}
					}
					else if (!m_savedHasHighBasePiece && m_applyBaseTexture && materialIndex == 2) {
						primitive->m_materialIndex = static_cast<LegoU16>(colorMaterialIndex + 1);
					}
					else {
						primitive->m_materialIndex = static_cast<LegoU16>(colorMaterialIndex);
					}

					LegoU16* vertexIndex = primitive->m_vertexIndices;
					for (i = 0; i < 3; i++) {
						LegoS32 coordinateIndex = *cursor++;
						if (!library->IsColorBlack(coordinateIndex)) {
							primitive->m_flags &= ~c_buildPrimitiveFlagAllBlack;
						}

						library->GetColor(coordinateIndex, &sourceX, &sourceY, &sourceZ);

						switch (rotation) {
						case 0:
							vertex.m_position.m_x = sourceX + xOrigin;
							vertex.m_position.m_y = sourceY + yOrigin;
							break;
						case 1:
							vertex.m_position.m_x = sourceY + xOrigin;
							vertex.m_position.m_y = (width - sourceX) + yOrigin;
							break;
						case 2:
							vertex.m_position.m_x = (width - sourceX) + xOrigin;
							vertex.m_position.m_y = (pieceHeight - sourceY) + yOrigin;
							break;
						case 3:
							vertex.m_position.m_x = (pieceHeight - sourceY) + xOrigin;
							vertex.m_position.m_y = sourceX + yOrigin;
							break;
						}
						vertex.m_position.m_z = sourceZ + zOrigin;

						for (LegoS32 j = 0; j < i; j++) {
							if (vertex.m_position.m_x !=
								m_buildVertices[primitive->m_vertexIndices[j]].m_position.m_x) {
								primitive->m_flags &= ~c_buildPrimitiveFlagSameX;
							}
							if (vertex.m_position.m_y !=
								m_buildVertices[primitive->m_vertexIndices[j]].m_position.m_y) {
								primitive->m_flags &= ~c_buildPrimitiveFlagSameY;
							}
							if (vertex.m_position.m_z !=
								m_buildVertices[primitive->m_vertexIndices[j]].m_position.m_z) {
								primitive->m_flags &= ~c_buildPrimitiveFlagSameZ;
							}
						}

						if (!hasSharedNormalIndex && (hasNormalIndex || i == 0)) {
							normalIndex = *cursor++;
						}

						const LegoU8* normal = library->GetColorTriple(normalIndex);
						LegoS8 normalX = static_cast<LegoS8>(normal[0]);
						LegoS8 normalY = static_cast<LegoS8>(normal[1]);
						vertex.m_normalZ = static_cast<LegoS8>(normal[2]);

						switch (rotation) {
						case 0:
							vertex.m_normalX = normalX;
							vertex.m_normalY = normalY;
							break;
						case 1:
							vertex.m_normalX = normalY;
							vertex.m_normalY = -normalX;
							break;
						case 2:
							vertex.m_normalX = -normalX;
							vertex.m_normalY = -normalY;
							break;
						case 3:
							vertex.m_normalX = -normalY;
							vertex.m_normalY = normalX;
							break;
						}

						if (hasTextureIndex) {
							LegoS32 textureIndex = *cursor++;
							library->GetTextureCoordinate(
								textureIndex,
								&vertex.m_textureCoordinate.m_x,
								&vertex.m_textureCoordinate.m_y
							);
						}
						else if (
							!m_savedHasHighBasePiece && m_applyBaseTexture &&
							(primitive->m_commandFlags == c_buildPrimitiveCommandMaterial2 ||
							 primitive->m_commandFlags & c_buildPrimitiveCommandTextureBit)
						) {
							vertex.m_textureCoordinate.m_x =
								(vertex.m_position.m_x - xOrigin) * g_carBuildModelTextureCoordinateScale;
							vertex.m_textureCoordinate.m_y =
								(vertex.m_position.m_y - yOrigin) * g_carBuildModelTextureCoordinateScale;
						}
						else {
							vertex.m_textureCoordinate.m_x = 0.0f;
							vertex.m_textureCoordinate.m_y = 0.0f;
						}

						*vertexIndex = AddBuildVertex(&vertex);
						vertexIndex++;
					}
				}

				LegoS32 newPrimitiveCount = m_buildPrimitiveCount + 1;
				m_buildPrimitiveCount = newPrimitiveCount;
				if (m_buildPrimitiveCount >= c_buildPrimitiveCapacity) {
					m_buildStatus |= c_buildStatusOverflow;
					return static_cast<LegoS16>(newPrimitiveCount);
				}

				remaining--;
			} while (remaining != 0);
		}

		return static_cast<LegoS16>(remaining);
	}

	m_buildStatus |= c_buildStatusOverflow;
	return static_cast<LegoS16>(result);
}

// FUNCTION: LEGORACERS 0x0049ad00
void CarBuildModel::FindHighBasePiece()
{
	if (m_pieceLibrary != NULL) {
		m_highBasePiece = m_pieceLibrary->FindPieceRecord(0x800, 1);
		if (m_highBasePiece != NULL) {
			m_hasHighBasePiece = TRUE;
		}
	}
}

// FUNCTION: LEGORACERS 0x0049ad30
LegoS16 CarBuildModel::EmitCellGeometry(
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_height,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_materialIndex
)
{
	LegoS32 colorRecordIndex;
	if (p_materialIndex) {
		colorRecordIndex = m_colorTable->FindColorRecordIndexByMaterialIndex(p_materialIndex);
	}
	else {
		colorRecordIndex = p_colorRecordIndex;
	}

	return EmitPieceGeometry(m_highBasePiece, p_x, p_y, 0, p_height, colorRecordIndex, 0);
}

// FUNCTION: LEGORACERS 0x0049ad80
void CarBuildModel::AddHighBasePieceCallback(
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_height,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_delta
)
{
	g_carBuildModelCellCallback->EmitCellGeometry(p_x, p_y, p_height, p_colorRecordIndex, p_delta);
}

// FUNCTION: LEGORACERS 0x0049adb0
LegoS32 CarBuildModel::GetBatchVertexIndex(LegoS32 p_vertexIndex)
{
	LegoS32 batchIndex = m_batchVertexSlotByBuildVertex[p_vertexIndex];
	if (batchIndex < m_batchVertexCount) {
		LegoS32 buildVertexIndex = m_batchBuildVertexIndices[batchIndex];
		if (buildVertexIndex == p_vertexIndex) {
			return batchIndex;
		}
	}

	return -1;
}

// FUNCTION: LEGORACERS 0x0049ade0
void CarBuildModel::EmitPrimitiveToModel(GolModelEntity* p_entity, BuildPrimitive* p_primitive)
{
	ColorRGBA color;
	color.m_red = 0xff;
	color.m_grn = 0xff;
	color.m_blu = 0xff;
	color.m_alp = 0xff;

	GolModelBase* model = p_entity->GetModel(0);
	if (m_modelTriangleCount + p_primitive->m_vertexCount > c_modelTriangleCapacity) {
		m_buildStatus |= c_buildStatusOverflow;
		return;
	}

	LegoS32 batchIndices[4];
	LegoS32 newVertexCount = 0;

	{
		LegoS32 i;
		for (i = 0; i < p_primitive->m_vertexCount; i++) {
			batchIndices[i] = GetBatchVertexIndex(p_primitive->m_vertexIndices[i]);
			if (batchIndices[i] == -1) {
				newVertexCount++;
			}
		}
	}

	if (m_modelVertexCount + newVertexCount > c_buildVertexCapacity) {
		m_buildStatus |= c_buildStatusOverflow;
		return;
	}

	if (static_cast<LegoU32>(m_batchVertexCount + newVertexCount) > c_modelBatchVertexCapacity) {
		FlushBatch(model);
		{
			LegoS32 i;
			for (i = 0; i < sizeOfArray(batchIndices); i++) {
				batchIndices[i] = -1;
			}
		}
	}

	LegoU32 materialIndex = p_primitive->m_materialIndex;
	if (m_currentMaterialIndex != materialIndex) {
		if (m_batchTriangleCount) {
			FlushBatch(model);
		}

		LegoU32 groupIndex = m_modelGroupCount++;
		m_currentMaterialIndex = materialIndex;
		model->GetMutableGroups()[groupIndex] = c_modelMaterialGroup;
		model->GetMutableGroups()[groupIndex] |= materialIndex & 0x00ffffff;
		model->SetDirty(TRUE);

		{
			LegoS32 i;
			for (i = 0; i < sizeOfArray(batchIndices); i++) {
				batchIndices[i] = -1;
			}
		}
	}

	{
		LegoS32 i;
		for (i = 0; i < p_primitive->m_vertexCount; i++) {
			if (batchIndices[i] == -1) {
				LegoS32 buildVertexIndex = p_primitive->m_vertexIndices[i];

				m_batchBuildVertexIndices[m_batchVertexCount] = static_cast<LegoU16>(buildVertexIndex);
				m_batchVertexSlotByBuildVertex[buildVertexIndex] = static_cast<LegoU8>(m_batchVertexCount);
				batchIndices[i] = m_batchVertexCount;
				m_batchVertexCount++;

				BuildVertex* buildVertex = &m_buildVertices[buildVertexIndex];
				m_modelVertices->SetPosition(m_modelVertexCount, buildVertex->m_position);

				GolVec3 normal;
				normal.m_x = static_cast<LegoFloat>(buildVertex->m_normalX) * g_carBuildModelNormalScale;
				normal.m_y = static_cast<LegoFloat>(buildVertex->m_normalY) * g_carBuildModelNormalScale;
				normal.m_z = static_cast<LegoFloat>(buildVertex->m_normalZ) * g_carBuildModelNormalScale;
				m_modelVertices->SetNormal(m_modelVertexCount, normal);
				m_modelVertices->SetTextureCoordinate(m_modelVertexCount, buildVertex->m_textureCoordinate);
				m_modelVertices->SetColor(m_modelVertexCount, color);
				m_modelVertexCount++;
			}
		}
	}

	GdbModelIndexArray::Indices* indices = &m_modelTriangles[m_modelTriangleCount++];
	indices->m_a = static_cast<LegoU8>(batchIndices[0]);
	indices->m_b = static_cast<LegoU8>(batchIndices[1]);
	indices->m_c = static_cast<LegoU8>(batchIndices[2]);

	if (p_primitive->m_vertexCount == 4) {
		indices++;
		m_modelTriangleCount++;
		m_batchTriangleCount += 2;
		indices->m_a = static_cast<LegoU8>(batchIndices[2]);
		indices->m_b = static_cast<LegoU8>(batchIndices[1]);
		indices->m_c = static_cast<LegoU8>(batchIndices[3]);
	}
	else {
		m_batchTriangleCount++;
	}
}

// FUNCTION: LEGORACERS 0x0049b100
void CarBuildModel::EmitPrimitives(GolModelEntity* p_entity)
{
	for (LegoS32 i = 0; i < m_buildPrimitiveCount; i++) {
		EmitPrimitiveToModel(p_entity, m_buildPrimitiveOrder[i]);
		if (m_buildStatus & 1) {
			return;
		}
	}
}

// STUB: LEGORACERS 0x0049b150
LegoS32 CarBuildModel::ComparePrimitiveMaterial(const void* p_lhs, const void* p_rhs)
{
	const BuildPrimitive* lhs = *static_cast<BuildPrimitive* const*>(p_lhs);
	const BuildPrimitive* rhs = *static_cast<BuildPrimitive* const*>(p_rhs);

	return lhs->m_materialIndex - rhs->m_materialIndex;
}

// FUNCTION: LEGORACERS 0x0049b170
LegoS32 CarBuildModel::BuildPieceModel(
	GolModelEntity* p_entity,
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_height,
	LegoS32 p_rotation,
	LegoS32 p_colorRecordIndex,
	LegoS32
)
{
	GolModelBase* model = p_entity->GetModel(0);
	LegoPieceLibrary::PieceRecord* pieceRecord = p_pieceRecord->GetVariant(1);
	m_savedHasHighBasePiece = m_hasHighBasePiece;
	m_applyBaseTexture = m_baseTextureEnabled;
	m_buildFlags = 0xef;
	m_buildStatus = 0;

	if (m_colorTable != NULL) {
		p_entity->SetPrimaryMaterialTable(m_colorTable->GetMaterialTable());
	}

	ResetBuildVertexTree();
	m_buildPrimitiveCount = 0;
	EmitPieceGeometry(pieceRecord, p_x, p_y, p_rotation, p_height, p_colorRecordIndex, 0);

	if (m_savedHasHighBasePiece) {
		LegoS32 width;
		LegoS32 height;
		if (p_rotation & 1) {
			width = pieceRecord->GetHeight();
			height = pieceRecord->GetWidth();
		}
		else {
			width = pieceRecord->GetWidth();
			height = pieceRecord->GetHeight();
		}

		for (LegoS32 x = 0; x < width; x++) {
			for (LegoS32 y = 0; y < height; y++) {
				LegoU8 cellFlags = pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation))->m_first;
				if (cellFlags & 0x80) {
					EmitCellGeometry(p_x + x, p_y + y, p_height + (cellFlags & 0x3f), p_colorRecordIndex, 0);
				}
			}
		}
	}

	FinalizeBuild(0xef);

	for (LegoS32 i = 0; i < m_buildVertexCount; i++) {
		m_buildVertices[i].m_position.m_x += m_offsetX;
		m_buildVertices[i].m_position.m_y += m_offsetY;
		m_buildVertices[i].m_position.m_z = (m_buildVertices[i].m_position.m_z * 0.4f) + m_offsetZ;
	}

	BeginModelWrite(model);
	EmitPrimitives(p_entity);
	EndModelWrite(model);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0049b340
void CarBuildModel::ComputePieceBounds(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_rotation)
{
	LegoPieceLibrary* library = p_pieceRecord->m_library;
	const LegoU16* indexCursor = library->GetIndexCursor(p_pieceRecord->m_indexOffset);
	LegoS32 indexCount = p_pieceRecord->m_indexCommandCount;
	if (indexCount == 0) {
		m_pieceMaxZ = 0.0f;
		m_pieceMinZ = 0.0f;
		m_pieceMaxY = 0.0f;
		m_pieceMinY = 0.0f;
		m_pieceMaxX = 0.0f;
		m_pieceMinX = 0.0f;
		return;
	}

	LegoFloat x;
	LegoFloat y;
	LegoFloat z;
	LegoFloat minX;
	LegoFloat minY;
	LegoFloat minZ;
	library->GetColor(indexCursor[1], &minX, &minY, &minZ);
	LegoFloat maxX = minX;
	LegoFloat maxY = minY;
	LegoFloat maxZ = minZ;

	LegoBool32 hasExtraIndex = FALSE;
	LegoBool32 hasTextureIndex = FALSE;
	do {
		LegoU32 command = *indexCursor++;
		LegoS32 mode = command & c_indexCommandModeMask;
		if (mode == c_indexCommandQuad) {
			library->GetColor(*indexCursor++, &x, &y, &z);

			if (minX > x) {
				minX = x;
			}
			if (maxX < x) {
				maxX = x;
			}
			if (minY > y) {
				minY = y;
			}
			if (maxY < y) {
				maxY = y;
			}
			if (minZ > z) {
				minZ = z;
			}
			if (maxZ < z) {
				maxZ = z;
			}

			if (hasTextureIndex) {
				indexCursor++;
			}
			if (hasExtraIndex) {
				indexCursor++;
			}
		}
		else {
			hasExtraIndex = mode == c_indexCommandTextured;
			hasTextureIndex = (command >> 14) & 1;
			LegoBool32 hasSharedIndex = (command >> 15) & 1;

			for (LegoS32 i = 0; i < 3; i++) {
				library->GetColor(*indexCursor++, &x, &y, &z);

				if (minX > x) {
					minX = x;
				}
				if (maxX < x) {
					maxX = x;
				}
				if (minY > y) {
					minY = y;
				}
				if (maxY < y) {
					maxY = y;
				}
				if (minZ > z) {
					minZ = z;
				}
				if (maxZ < z) {
					maxZ = z;
				}

				if (!hasSharedIndex && (hasTextureIndex || i == 0)) {
					indexCursor++;
				}
				if (hasExtraIndex) {
					indexCursor++;
				}
			}
		}
	} while (--indexCount != 0);

	LegoS32 rotation = p_rotation & 3;
	if (rotation) {
		LegoFloat width = static_cast<LegoFloat>(p_pieceRecord->GetWidth());
		LegoFloat height = static_cast<LegoFloat>(p_pieceRecord->GetHeight());

		switch (rotation) {
		case 1:
			m_pieceMinX = minY;
			m_pieceMaxX = maxY;
			m_pieceMinY = width - maxX;
			m_pieceMaxY = width - minX;
			break;
		case 2:
			m_pieceMinX = width - maxX;
			m_pieceMaxX = width - minX;
			m_pieceMinY = height - maxY;
			m_pieceMaxY = height - minY;
			break;
		case 3:
			m_pieceMinX = height - maxY;
			m_pieceMaxX = height - minY;
			m_pieceMinY = minX;
			m_pieceMaxY = maxX;
			break;
		}
	}
	else {
		m_pieceMinX = minX;
		m_pieceMaxX = maxX;
		m_pieceMinY = minY;
		m_pieceMaxY = maxY;
	}

	m_pieceMinZ = minZ * 0.4f;
	m_pieceMaxZ = maxZ * 0.4f;
}

// FUNCTION: LEGORACERS 0x0049b6f0
void CarBuildModel::SetOffset(LegoFloat p_offsetX, LegoFloat p_offsetY, LegoFloat p_offsetZ)
{
	m_offsetX = p_offsetX;
	m_offsetY = p_offsetY;
	m_offsetZ = p_offsetZ;
}

// FUNCTION: LEGORACERS 0x0049b720
void CarBuildModel::SetDefaultOffset()
{
	m_offsetX = -5.0f;
	m_offsetY = -3.0f;
	m_offsetZ = 0.0f;
}

// FUNCTION: LEGORACERS 0x0049b740
void CarBuildModel::UpdateOffset(LegoBool32 p_restoreCachedOffset)
{
	if (p_restoreCachedOffset) {
		SetOffset(m_cachedOffsetX, m_cachedOffsetY, m_cachedOffsetZ);
		return;
	}

	if (m_placedPieceCount) {
		LegoS32 partType;
		LegoPieceLibrary* library;
		LegoS32 rotation;
		LegoS32 x;
		LegoS32 y;
		LegoS32 height;
		LegoS32 colorRecordIndex;
		LegoPieceLibrary::PieceRecord* pieceRecord;
		GetPieceInfo(0, &pieceRecord, &x, &y, &height, &rotation, &colorRecordIndex, &partType);

		library = pieceRecord->m_library;
		partType = pieceRecord->GetPartType();
		if (partType != 0xffff) {
			library->GetColor(partType, &m_offsetX, &m_offsetY, &m_offsetZ);
			m_offsetZ *= g_carBuildModelNegativeHeightScale;
			m_offsetX = -m_offsetX;
			m_offsetY = -m_offsetY;
		}
		else {
			ComputePieceBounds(pieceRecord, rotation);
			LegoFloat xOffset = static_cast<LegoFloat>(x);
			m_offsetX = -((m_pieceMaxX + m_pieceMinX) * 0.5f) - xOffset;

			LegoFloat yOffset = static_cast<LegoFloat>(y);
			m_offsetY = -((m_pieceMaxY + m_pieceMinY) * 0.5f) - yOffset;

			LegoFloat heightOffset = static_cast<LegoFloat>(height);
			m_offsetZ = -m_pieceMinZ - (heightOffset * g_carBuildModelHeightScale);
		}
	}
	else {
		SetDefaultOffset();
	}

	m_cachedOffsetX = m_offsetX;
	m_cachedOffsetY = m_offsetY;
	m_cachedOffsetZ = m_offsetZ;
}

// FUNCTION: LEGORACERS 0x0049b8b0
void CarBuildModel::CenterOnPiece(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_rotation)
{
	ComputePieceBounds(p_pieceRecord, p_rotation);

	m_offsetX = -((m_pieceMaxX + m_pieceMinX) * 0.5f);
	m_offsetY = -((m_pieceMaxY + m_pieceMinY) * 0.5f);
	m_offsetZ = -((m_pieceMaxZ + m_pieceMinZ) * 0.5f);
}

// STUB: LEGORACERS 0x0049b920
void CarBuildModel::RebuildModel(LegoS32 p_variant, LegoU32 p_buildFlags)
{
	LegoS32 activePieceCount = m_placedPieceCount;
	LegoS32 i;
	m_buildFlags = static_cast<LegoU16>(p_buildFlags);
	m_pieceList.SetVariant(p_variant, TRUE);
	m_buildStatus = 0;
	m_buildPrimitiveCount = 0;

	LegoU8 startFlags;
	do {
		ResetBuildVertexTree();
		m_buildStatus <<= 1;
		m_buildPrimitiveCount = 0;
		if ((m_buildStatus & 0xf8) && activePieceCount > 1) {
			activePieceCount--;
			m_buildStatus &= 7;
		}

		startFlags = m_buildStatus;
		if (startFlags & 0xfc) {
			m_savedHasHighBasePiece = FALSE;
			m_applyBaseTexture = FALSE;
		}
		else if (startFlags & 0xfe) {
			m_savedHasHighBasePiece = FALSE;
			m_applyBaseTexture = m_hasHighBasePiece || m_baseTextureEnabled;
		}
		else {
			m_savedHasHighBasePiece = m_hasHighBasePiece;
			m_applyBaseTexture = m_baseTextureEnabled;
		}

		for (i = 0; i < activePieceCount; i++) {
			PieceList::Entry* entry = &m_pieceList.m_entries[i];
			LegoS32 x;
			LegoS32 y;
			LegoS32 height;
			LegoS32 rotation;
			entry->GetPlacement(&x, &y, &height, &rotation);
			EmitPieceGeometry(entry->m_pieceRecord, x, y, rotation, height, entry->m_colorRecordIndex, i);
		}

		if (!(m_buildStatus & 1)) {
			g_carBuildModelCellCallback = this;
			if (m_savedHasHighBasePiece) {
				m_pieceGrid.ForEachOccupiedCell(AddHighBasePieceCallback);
				m_pieceGrid.RebuildGridWithCallback(AddHighBasePieceCallback);
			}

			if (!(m_buildStatus & 1)) {
				if (p_buildFlags) {
					FinalizeBuild(static_cast<LegoU8>(p_buildFlags));
				}
				else {
					::qsort(
						m_buildPrimitiveOrder,
						m_buildPrimitiveCount,
						sizeof(BuildPrimitive*),
						ComparePrimitiveMaterial
					);
				}
			}

			if (!(m_buildStatus & 1)) {
				for (i = 0; i < m_buildVertexCount; i++) {
					m_buildVertices[i].m_position.m_x = m_offsetX + m_buildVertices[i].m_position.m_x;
					m_buildVertices[i].m_position.m_y += m_offsetY;
					m_buildVertices[i].m_position.m_z = (m_buildVertices[i].m_position.m_z * 0.4f) + m_offsetZ;
				}

				BeginModelWrite(m_model);
				EmitPrimitives(&m_modelEntity);
				EndModelWrite(m_model);
			}
		}
	} while (m_buildStatus != startFlags);

	if (activePieceCount != m_placedPieceCount) {
		m_buildStatus |= 8;
	}

	if (m_colorTable != NULL && m_buildPrimitiveCount != 0) {
		m_colorTable->ResetMaterialUsage();
		m_currentMaterialIndex = m_buildPrimitiveOrder[0]->m_materialIndex;
		m_colorTable->MarkMaterialUsed(m_currentMaterialIndex);

		for (i = 1; i < m_buildPrimitiveCount; i++) {
			LegoU32 materialIndex = m_buildPrimitiveOrder[i]->m_materialIndex;
			if (m_currentMaterialIndex != materialIndex) {
				m_currentMaterialIndex = materialIndex;
				m_colorTable->MarkMaterialUsed(materialIndex);
			}
		}

		m_finalMaterialCount = m_colorTable->GetUsedMaterialCount();
		m_finalTextureCount = m_colorTable->GetTransparentMaterialCount();
	}
	else {
		m_finalTextureCount = 0;
		m_finalMaterialCount = 0;
	}

	m_finalGroupCount = m_modelGroupCount;
	m_finalTriangleCount = m_modelTriangleCount;
	m_finalVertexCount = m_modelVertexCount;
}

// FUNCTION: LEGORACERS 0x0049bc60
void CarBuildModel::BuildIntoModel(GolModelBase* p_model, undefined4 p_variant, undefined4 p_buildFlags)
{
	GolModelBase* model = m_model;
	m_model = p_model;
	MaterialTable* materialTable = m_modelEntity.GetPrimaryMaterialTable();
	m_modelEntity.SetPrimaryModel(p_model, g_carBuildModelMaxFloat);
	RebuildModel(p_variant, p_buildFlags);
	m_model = model;
	m_modelEntity.SetPrimaryModel(model, g_carBuildModelMaxFloat);
	m_modelEntity.SetPrimaryMaterialTable(materialTable);
}

// FUNCTION: LEGORACERS 0x0049bcc0
LegoS32 CarBuildModel::GetCellEntryIndex(LegoS32 p_x, LegoS32 p_y) const
{
	return m_pieceGrid.m_entries[p_y + (p_x * m_pieceGrid.m_height)].m_entryIndex;
}

// FUNCTION: LEGORACERS 0x0049bce0
void CarBuildModel::GetPieceInfo(
	LegoS32 p_index,
	LegoPieceLibrary::PieceRecord** p_pieceRecord,
	LegoS32* p_x,
	LegoS32* p_y,
	LegoS32* p_height,
	LegoS32* p_rotation,
	LegoS32* p_colorRecordIndex,
	LegoS32* p_partType
)
{
	*p_pieceRecord = m_pieceList.m_entries[p_index].m_pieceRecord;
	m_pieceList.m_entries[p_index].GetPlacement(p_x, p_y, p_height, p_rotation);
	*p_colorRecordIndex = m_pieceList.m_entries[p_index].m_colorRecordIndex;
	*p_partType = m_pieceList.m_entries[p_index].m_partType;
}

// FUNCTION: LEGORACERS 0x0049bd50
LegoS32 CarBuildModel::GetPiecePartType(LegoS32 p_index) const
{
	return m_pieceList.m_entries[p_index].m_partType;
}

// FUNCTION: LEGORACERS 0x0049bd70
LegoPieceLibrary::PieceRecord* CarBuildModel::RemovePiece(LegoS32 p_index)
{
	if (p_index >= 0 && p_index < m_placedPieceCount && m_pieceGrid.UnstampPiece(p_index)) {
		LegoPieceLibrary::PieceRecord* result = m_pieceGrid.RemovePiece(p_index);
		m_placedPieceCount = m_pieceList.m_entryCount;

		return result;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0049bdc0
void CarBuildModel::RemoveLastPiece()
{
	RemovePiece(m_placedPieceCount - 1);
}

// FUNCTION: LEGORACERS 0x0049bdd0
void CarBuildModel::DrawOverlay(GolD3DRenderDevice* p_renderer, LegoFloat p_zOffset)
{
	GolVec3 position;
	m_modelEntity.GetPosition(&position);
	position.m_z += p_zOffset;
	m_overlayEntity.SetPosition(position);

	GolMatrix3 matrix;
	m_modelEntity.CopyOrientation(&matrix);
	m_overlayEntity.SetOrientationMatrix(matrix);

	if (m_overlayVisible) {
		p_renderer->DrawModelEntity(&m_overlayEntity);
	}
}

// FUNCTION: LEGORACERS 0x0049be50
void CarBuildModel::MarkOverlayCell(LegoS32 p_x, LegoS32 p_y)
{
	if (m_overlayCells[p_x + 1][p_y + 1].m_flags & c_overlayCellFlagOccupied) {
		m_overlayCells[p_x + 1][p_y + 1].m_flags |= c_overlayCellFlagDraw;
	}
}

// FUNCTION: LEGORACERS 0x0049be70
void CarBuildModel::BuildOverlay(LegoBool32 p_visible, LegoS32 p_height)
{
	LegoS32 disabled = FALSE;
	LegoS32 enabled = TRUE;

	ColorRGBA color;
	color.m_red = 0xff;
	color.m_grn = 0xff;
	color.m_blu = 0xff;
	color.m_alp = 0xff;

	p_visible &= enabled;
	if (p_height < 0) {
		p_height = m_overlayHeight;
	}

	BeginModelWrite(m_overlayModel);

	LegoU32 groupIndex = m_modelGroupCount;
	m_overlayVisible = disabled;
	m_modelGroupCount++;
	m_overlayModel->GetMutableGroups()[groupIndex] = c_modelMaterialGroup;
	m_overlayModel->GetMutableGroups()[groupIndex] |= enabled;
	m_overlayModel->SetDirty(enabled);

	GolVec3 position;
	position.m_z = (static_cast<LegoFloat>(p_height) * 0.4f) + m_offsetZ;
	GolVec2 texCoord;
	LegoS32 quadVertexCount = 4;
	LegoS32 quadTriangleCount = 2;

	LegoS32 x = disabled;
	for (; x < 12; x++) {
		for (LegoS32 y = disabled; y < 8; y++) {
			if ((m_overlayCells[x][y].m_flags & c_overlayCellFlagOccupied) &&
				(m_overlayCells[x][y].m_flags & c_overlayCellFlagDraw)) {
				if (static_cast<LegoU32>(m_batchVertexCount + quadVertexCount) > c_modelBatchVertexCapacity) {
					m_overlayVisible += m_batchTriangleCount;
					FlushBatch(m_overlayModel);
				}

				position.m_x = static_cast<LegoFloat>(x - 1) + m_offsetX;
				position.m_y = static_cast<LegoFloat>(y - 1) + m_offsetY;
				texCoord.m_x = 0.5f;
				texCoord.m_y = 0.5f;
				if (!p_visible) {
					texCoord.m_y = 0.0f;
				}

				m_modelVertices->SetPosition(m_modelVertexCount, position);
				m_modelVertices->SetTextureCoordinate(m_modelVertexCount, texCoord);
				m_modelVertices->SetColor(m_modelVertexCount, color);

				m_modelVertexCount++;
				position.m_x += 1.0f;
				texCoord.m_x += 0.49f;
				m_modelVertices->SetPosition(m_modelVertexCount, position);
				m_modelVertices->SetTextureCoordinate(m_modelVertexCount, texCoord);
				m_modelVertices->SetColor(m_modelVertexCount, color);

				m_modelVertexCount++;
				position.m_y += 1.0f;
				texCoord.m_y += 0.49f;
				m_modelVertices->SetPosition(m_modelVertexCount, position);
				m_modelVertices->SetTextureCoordinate(m_modelVertexCount, texCoord);
				m_modelVertices->SetColor(m_modelVertexCount, color);

				m_modelVertexCount++;
				position.m_x -= 1.0f;
				texCoord.m_x -= 0.49f;
				m_modelVertices->SetPosition(m_modelVertexCount, position);
				m_modelVertices->SetTextureCoordinate(m_modelVertexCount, texCoord);
				m_modelVertices->SetColor(m_modelVertexCount, color);

				m_modelVertexCount++;
				GdbModelIndexArray::Indices* triangles = &m_modelTriangles[m_modelTriangleCount];
				triangles[0].m_a = static_cast<LegoU8>(m_batchVertexCount);
				triangles[0].m_b = static_cast<LegoU8>(m_batchVertexCount + 1);
				triangles[0].m_c = static_cast<LegoU8>(m_batchVertexCount + 3);
				triangles++;
				triangles[0].m_a = static_cast<LegoU8>(m_batchVertexCount + 3);
				triangles[0].m_b = static_cast<LegoU8>(m_batchVertexCount + 1);
				triangles[0].m_c = static_cast<LegoU8>(m_batchVertexCount + 2);

				m_batchVertexCount += quadVertexCount;
				m_modelTriangleCount += quadTriangleCount;
				m_batchTriangleCount += quadTriangleCount;
			}
		}
	}

	if (m_batchVertexCount) {
		m_overlayVisible += m_batchTriangleCount;
		FlushBatch(m_overlayModel);
	}

	EndModelWrite(m_overlayModel);
}

// STUB: LEGORACERS 0x0049c230
void CarBuildModel::RefreshOverlay(Placement* p_placement, GolModelEntity* p_entity)
{
	GolModelBase* model = p_entity->GetModel(0);
	::memset(m_overlayCells, 0, sizeof(m_overlayCells));
	UpdateOffset(TRUE);

	LegoS32 x;
	LegoS32 entryHeight;
	LegoPieceLibrary::PieceRecord* pieceRecord = p_placement->GetPieceRecord();
	LegoS32 rotation;
	if (pieceRecord != NULL) {
		LegoS32 y;
		p_placement->GetPlacement(&x, &y, &rotation);

		LegoS32 partType = p_placement->GetPartType();
		LegoS32 colorRecordIndex = p_placement->GetColorRecordIndex();
		BuildPieceModel(p_entity, pieceRecord, x, y, 21, rotation, colorRecordIndex, 239);

		if (pieceRecord->m_pieceType == 0x7ff) {
			LegoS32 entryIndex = GetCellEntryIndex(x, y);
			if (entryIndex >= 0) {
				GetPieceInfo(entryIndex, &pieceRecord, &x, &y, &entryHeight, &rotation, &colorRecordIndex, &partType);
				if (pieceRecord->m_pieceType < g_highPieceTypeBase) {
					entryIndex = -1;
				}
			}

			m_overlayHeight = 18;
			if (entryIndex < 0) {
				p_placement->GetPlacement(&x, &y, &rotation);
				m_overlayCells[x + 1][y + 1].m_flags |= c_overlayCellFlagOccupiedDraw;
				BuildOverlay(FALSE, -1);
				return;
			}

			LegoPieceLibrary::PieceRecord* overlayPieceRecord = pieceRecord;
			LegoS32 width;
			LegoS32 height;
			if (rotation & 1) {
				width = overlayPieceRecord->GetHeight();
				height = overlayPieceRecord->GetWidth();
			}
			else {
				width = overlayPieceRecord->GetWidth();
				height = overlayPieceRecord->GetHeight();
			}

			for (LegoS32 i = 0; i < width; i++) {
				for (LegoS32 j = 0; j < height; j++) {
					LegoPieceLibrary::ShapeCell* cell = pieceRecord->GetCell(i, j, static_cast<LegoU8>(rotation));
					if ((cell->m_first | cell->m_second) & 0x3f) {
						m_overlayCells[x + i + 1][y + j + 1].m_flags |= c_overlayCellFlagOccupied;
						if (entryIndex != GetCellEntryIndex(x + i, y + j)) {
							m_overlayCells[x + i + 1][y + j + 1].m_flags |= c_overlayCellFlagDraw;
						}
					}
				}
			}
		}
		else {
			m_overlayHeight = 0;

			LegoPieceLibrary::PieceRecord* overlayPieceRecord = pieceRecord;
			LegoS32 width;
			LegoS32 height;
			if (rotation & 1) {
				width = overlayPieceRecord->GetHeight();
				height = overlayPieceRecord->GetWidth();
			}
			else {
				width = overlayPieceRecord->GetWidth();
				height = overlayPieceRecord->GetHeight();
			}

			for (LegoS32 i = 0; i < width; i++) {
				for (LegoS32 j = 0; j < height; j++) {
					LegoPieceLibrary::ShapeCell* cell = pieceRecord->GetCell(i, j, static_cast<LegoU8>(rotation));
					if ((cell->m_first | cell->m_second) & 0x3f) {
						m_overlayCells[x + i + 1][y + j + 1].m_flags |= c_overlayCellFlagOccupied;
						m_overlayCells[x + i + 1][y + j + 2].m_flags |= c_overlayCellNeighborPosY;
						m_overlayCells[x + i + 2][y + j + 1].m_flags |= c_overlayCellNeighborPosX;
						m_overlayCells[x + i + 1][y + j].m_flags |= c_overlayCellNeighborNegY;
						m_overlayCells[x + i][y + j + 1].m_flags |= c_overlayCellNeighborNegX;

						LegoS32 gridHeight = m_pieceGrid.m_entries[y + j + ((x + i) * m_pieceGrid.m_height)].m_height;
						if (m_overlayHeight < gridHeight) {
							m_overlayHeight = gridHeight;
						}
					}
				}
			}

			if (m_overlayHeight > 15) {
				m_overlayHeight = 15;
			}

			LegoS32 pieceHeight = TestPlacement(pieceRecord, x, y, rotation);
			if (pieceHeight == -5) {
				pieceHeight = m_pieceGrid.FindPlacementHeight(pieceRecord, x, y, rotation, FALSE);
			}
			m_pieceGrid.MarkOverlayCells(this, pieceRecord, x, y, rotation, pieceHeight);
		}

		BuildOverlay(FALSE, -1);
	}
	else {
		BeginModelWrite(model);
		EndModelWrite(model);
		GolModelBase* auxModel = m_overlayModel;
		BeginModelWrite(auxModel);
		EndModelWrite(auxModel);
	}
}

// STUB: LEGORACERS 0x0049c6a0
LegoS32 CarBuildModel::ComputeHighPieceCentroid(LegoFloat* p_centroidX, LegoFloat* p_centroidY, LegoFloat* p_centroidZ)
{
	LegoS32 zTotal = 0;
	LegoS32 yTotal = 0;
	LegoS32 xTotal = 0;
	LegoS32 result = 0;

	LegoS32 entryCount = m_pieceList.m_entryCount;
	if (entryCount > 0) {
		LegoS32 entryIndex = 0;
		LegoS32 remaining = entryCount;
		do {
			PieceList::Entry* entry = &m_pieceList.m_entries[entryIndex];
			LegoPieceLibrary::PieceRecord* pieceRecord = entry->m_pieceRecord;
			if (pieceRecord->m_pieceType >= g_highPieceTypeBase) {
				LegoS32 x;
				LegoS32 y;
				LegoS32 height;
				LegoS32 rotation;
				entry->GetPlacement(&x, &y, &height, &rotation);

				LegoS32 pieceX;
				LegoS32 pieceY;
				LegoS32 pieceZ;
				LegoS32 count = pieceRecord->ComputeVolumeMoments(x, y, height, rotation, &pieceX, &pieceY, &pieceZ);
				result += count;
				xTotal += pieceX;
				yTotal += pieceY;
				zTotal += pieceZ;
			}

			entryIndex++;
		} while (--remaining != 0);
	}

	if (result) {
		LegoFloat count = static_cast<LegoFloat>(result);
		*p_centroidX = static_cast<LegoFloat>(xTotal) / count - g_carBuildModelCenterXOffset;
		*p_centroidY = static_cast<LegoFloat>(yTotal) / count - g_carBuildModelCenterYOffset;
		*p_centroidZ = static_cast<LegoFloat>(zTotal) / count;
	}
	else {
		*p_centroidZ = 0.0f;
		*p_centroidY = 0.0f;
		*p_centroidX = 0.0f;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049c7f0
LegoBool32 CarBuildModel::Deserialize(LegoU8* p_source)
{
	LegoBool32 result = m_pieceList.Deserialize(p_source, m_pieceLibrary, 15);
	m_placedPieceCount = m_pieceList.m_entryCount;

	return result;
}

// FUNCTION: LEGORACERS 0x0049c820
void CarBuildModel::Serialize(LegoU8* p_dest)
{
	m_pieceList.Serialize(p_dest);
}

// STUB: LEGORACERS 0x0049c840
void CarBuildModel::ExportModel(GolModelBase* p_model, GolMaterialLibrary* p_materials, GolTextureList* p_textures)
{
	GdbVertexArray* sourceVertices;
	GdbVertexArray* destVertices;
	LegoS32 i;
	LegoS32 materialCount = m_colorTable->GetMaterialCount();
	const LegoColorTable::MaterialUsage* materialUsage = m_colorTable->GetMaterialUsage();
	ColorRGBA color;
	MaterialTable* materialTable = m_colorTable->GetMaterialTable();
	GolModelBase* outputModel = p_model;
	GdbModelIndexArrayBase* sourceIndexArray;
	GdbModelIndexArrayBase* destIndexArray;
	GolVec2 texCoord;
	GolVec3 position;
	GolVec3 normal;
	GolMaterialParams params;

	LegoS32 outputMaterialIndex = 0;
	LegoS32 textureIndex = 0;
	for (i = 0; i < materialCount; i++) {
		if (materialUsage[i].m_used) {
			GolMaterial* sourceMaterial = static_cast<GolMaterial*>(materialTable->GetEntry(i));

			sourceMaterial->CopyParamsTo(&params);
			params.m_flags &= ~GolMaterial::c_flagCreated;

			GolMaterial* outputMaterial = p_materials->GetItem(outputMaterialIndex);
			if (sourceMaterial->GetFlags() & GolMaterial::c_flagTextured) {
				GolD3DTexture* outputTexture = p_textures->GetItem(textureIndex);
				GolD3DTexture* sourceTexture = static_cast<GolD3DTexture*>(sourceMaterial->GetTexture());

				outputTexture->CopySourceTextureDefinitionFrom(sourceTexture);
				params.m_texture = outputTexture;
				textureIndex++;
			}

			outputMaterial->SetParams(m_renderer, params);
			outputModel->GetMaterialTable()->SetEntry(outputMaterialIndex, outputMaterial);
			outputMaterialIndex++;
		}
	}

	for (i = 0; i < static_cast<LegoS32>(m_finalGroupCount); i++) {
		LegoU32 group = m_model->GetGroups()[i];
		if ((group & 0xe0000000) == 0x80000000) {
			LegoU32 materialIndex = group & 0xffff;
			outputModel->GetMutableGroups()[i] = 0x80000000;
			outputModel->GetMutableGroups()[i] |= materialUsage[materialIndex].m_order & 0xffffff;
			outputModel->SetDirty(TRUE);
		}
		else {
			outputModel->GetMutableGroups()[i] = group;
		}
	}

	m_model->GetVertexArray(&sourceVertices);
	m_model->GetIndexArrayInto(&sourceIndexArray);
	const GdbModelIndexArray::Indices* sourceIndices = static_cast<GdbModelIndexArray*>(sourceIndexArray)->GetIndices();

	outputModel->GetVertexArray(&destVertices);
	outputModel->GetIndexArrayInto(&destIndexArray);
	GdbModelIndexArray::Indices* destIndices = static_cast<GdbModelIndexArray*>(destIndexArray)->GetMutableIndices();
	::memcpy(destIndices, sourceIndices, sizeof(*destIndices) * m_finalTriangleCount);

	for (i = 0; i < static_cast<LegoS32>(m_finalVertexCount); i++) {
		sourceVertices->GetPosition(i, &position);
		destVertices->SetPosition(i, position);
		sourceVertices->GetTextureCoordinate(i, &texCoord);
		destVertices->SetTextureCoordinate(i, texCoord);
		sourceVertices->GetNormal(i, &normal);
		destVertices->SetNormal(i, normal);
		sourceVertices->GetColor(i, &color);
		destVertices->SetColor(i, color);
	}

	m_model->AddFlags(FALSE);
	m_model->AddFlagsWithBounds(FALSE, FALSE);
	outputModel->AddFlags(TRUE);
	outputModel->AddFlagsWithBounds(TRUE, TRUE);
}

// FUNCTION: LEGORACERS 0x0049df20
void CarBuildModel::PieceGrid::Cell::Reset()
{
	m_entryIndex = -1;
	m_height = 0;
	m_occupied = FALSE;
	m_unk0x09 = 0;
}

// FUNCTION: LEGORACERS 0x0049df40
void CarBuildModel::PieceGrid::StampPiece(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_height,
	LegoS32 p_entryIndex
)
{
	LegoS32 width;
	LegoPieceLibrary::ShapeCell* cell;
	LegoS32 height;
	if (p_rotation & 1) {
		width = p_pieceRecord->GetHeight();
		height = p_pieceRecord->GetWidth();
	}
	else {
		width = p_pieceRecord->GetWidth();
		height = p_pieceRecord->GetHeight();
	}

	if (m_cellCallback) {
		for (LegoS32 x = 0; x < width; x++) {
			for (LegoS32 y = 0; y < height; y++) {
				cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				if (!((cell->m_first | cell->m_second) & 0x3f)) {
					continue;
				}

				LegoS32 index = m_height * (p_x + x) + y + p_y;
				if (m_entries[index].m_occupied) {
					LegoS32 oldHeight = m_entries[index].m_height;

					if (oldHeight != p_height + cell->GetClampedLower() ||
						(oldHeight == p_height + cell->GetClampedLower() && (cell->m_second & 0x40))) {
						PieceList::Entry& oldEntry = m_pieceList->m_entries[m_entries[index].m_entryIndex];
						LegoS32 colorRecordIndex = oldEntry.m_colorRecordIndex;
						LegoPieceLibrary::PieceRecord* oldRecord = oldEntry.m_pieceRecord;
						LegoS32 delta = 0;

						if (oldRecord->m_pieceType < g_highPieceTypeBase) {
							LegoS32 oldX;
							LegoS32 oldY;
							LegoS32 oldEntryHeight;
							LegoS32 oldRotation;
							oldEntry.GetPlacement(&oldX, &oldY, &oldEntryHeight, &oldRotation);

							oldX = p_x + x - oldX;
							oldY = p_y + y - oldY;
							delta = oldRecord->GetCell(oldX, oldY, static_cast<LegoU8>(oldRotation))
										->GetRaisedBottomHeight();
						}

						m_cellCallback(p_x + x, p_y + y, oldHeight, colorRecordIndex, delta);
					}
				}

				m_entries[index].SetOccupied(cell->m_first);

				m_entries[index].m_height = p_height + (cell->m_first & 0x3f);
				m_entries[index].m_entryIndex = p_entryIndex;
			}
		}
	}
	else {
		for (LegoS32 x = 0; x < width; x++) {
			for (LegoS32 y = 0; y < height; y++) {
				cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				if (!((cell->m_first | cell->m_second) & 0x3f)) {
					continue;
				}

				LegoS32 index = (p_x + x) * m_height + y + p_y;
				m_entries[index].SetOccupied(cell->m_first);

				m_entries[index].m_height = p_height + (cell->m_first & 0x3f);
				m_entries[index].m_entryIndex = p_entryIndex;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e210
CarBuildModel::PieceGrid::PieceGrid()
{
	m_cellCallback = NULL;
	m_pieceList = NULL;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x0049e220
CarBuildModel::PieceGrid::~PieceGrid()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0049e230
LegoBool32 CarBuildModel::PieceGrid::Initialize(LegoS32 p_width, LegoS32 p_height)
{
	Clear();
	m_width = p_width;
	m_height = p_height;
	m_entries = new Cell[p_width * p_height];
	if (m_entries) {
		ResetEntries();
		return TRUE;
	}
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0049e280
void CarBuildModel::PieceGrid::ResetEntries()
{
	if (m_entries != NULL) {
		for (LegoS32 x = 0; x < m_width; x++) {
			for (LegoS32 y = 0; y < m_height; y++) {
				m_entries[y + (x * m_height)].Reset();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e2d0
LegoS32 CarBuildModel::PieceGrid::FindPlacementHeight(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoBool32 p_allowEmpty
)
{
	LegoS32 result = -1;

	if (p_x < 0 || p_y < 0) {
		return -2;
	}

	LegoS32 width;
	LegoS32 height;
	if (p_rotation & 1) {
		width = p_pieceRecord->GetHeight();
		height = p_pieceRecord->GetWidth();
	}
	else {
		width = p_pieceRecord->GetWidth();
		height = p_pieceRecord->GetHeight();
	}

	if (width + p_x > m_width) {
		return -3;
	}
	if (height + p_y > m_height) {
		return -4;
	}

	for (LegoS32 x = 0; x < width; x++) {
		for (LegoS32 y = 0; y < height; y++) {
			Cell& gridEntry = m_entries[m_height * (p_x + x) + y + p_y];
			if (gridEntry.m_occupied) {
				LegoS32 candidate = gridEntry.m_height;
				LegoPieceLibrary::ShapeCell* cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				if (cell->m_second & 0x80) {
					LegoS32 lower = cell->m_second & 0x3f;
					if (lower > (cell->m_first & 0x3f)) {
						lower = 0;
					}

					candidate -= lower;
					if (result < candidate) {
						result = candidate;
					}
				}
			}
			else if (p_allowEmpty && !gridEntry.m_height) {
				LegoPieceLibrary::ShapeCell* cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				LegoS32 lower = cell->m_second & 0x3f;
				if (lower > (cell->m_first & 0x3f)) {
					lower = 0;
				}

				if (result < -lower) {
					result = -lower;
				}
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049e450
LegoS32 CarBuildModel::PieceGrid::HasCollision(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_height
)
{
	LegoS32 result = 0;

	LegoS32 width;
	LegoS32 height;
	if (p_rotation & 1) {
		width = p_pieceRecord->GetHeight();
		height = p_pieceRecord->GetWidth();
	}
	else {
		width = p_pieceRecord->GetWidth();
		height = p_pieceRecord->GetHeight();
	}

	if (p_height < 0) {
		return (p_pieceRecord->GetHeight() * p_pieceRecord->GetWidth()) + 1;
	}

	for (LegoS32 x = 0; x < width; x++) {
		for (LegoS32 y = 0; y < height; y++) {
			LegoS32 index = (x + p_x) * m_height + y + p_y;
			LegoS32 entryHeight = m_entries[index].m_height - p_height;
			LegoPieceLibrary::ShapeCell* cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
			if (!((cell->m_first | cell->m_second) & 0x3f)) {
				continue;
			}

			LegoS32 lower = cell->m_second & 0x3f;
			if (lower > (cell->m_first & 0x3f)) {
				lower = 0;
			}

			if (entryHeight > lower ||
				(entryHeight == lower && m_entries[index].m_occupied && !(cell->m_second & 0xc0))) {
				result++;
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049e590
void CarBuildModel::PieceGrid::MarkOverlayCells(
	CarBuildModel* p_model,
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_height
)
{
	LegoS32 width;
	LegoS32 height;
	if (p_rotation & 1) {
		width = p_pieceRecord->GetHeight();
		height = p_pieceRecord->GetWidth();
	}
	else {
		width = p_pieceRecord->GetWidth();
		height = p_pieceRecord->GetHeight();
	}

	LegoS32 x;
	LegoS32 y;
	if (p_height < 0) {
		for (x = 0; x < width; x++) {
			for (y = 0; y < height; y++) {
				p_model->MarkOverlayCell(p_x + x, p_y + y);
			}
		}
	}
	else {
		for (x = 0; x < width; x++) {
			for (y = 0; y < height; y++) {
				LegoS32 index = m_height * (p_x + x) + y + p_y;
				LegoS32 entryHeight = m_entries[index].m_height;
				LegoPieceLibrary::ShapeCell* cell = p_pieceRecord->GetCell(x, y, static_cast<LegoU8>(p_rotation));
				LegoS32 lower = cell->m_second & 0x3f;
				if (lower > (cell->m_first & 0x3f)) {
					lower = 0;
				}

				lower += p_height;
				if ((cell->m_first | cell->m_second) & 0x3f) {
					if (entryHeight > lower ||
						(entryHeight == lower && m_entries[index].m_occupied && !(cell->m_second & 0xc0))) {
						p_model->MarkOverlayCell(p_x + x, p_y + y);
					}
				}
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e710
LegoBool32 CarBuildModel::PieceGrid::AddPiece(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_partType,
	LegoBool32 p_allowEmpty
)
{
	LegoS32 height = FindPlacementHeight(p_pieceRecord, p_x, p_y, p_rotation, p_allowEmpty);
	if (height < 0) {
		return FALSE;
	}

	if (HasCollision(p_pieceRecord, p_x, p_y, p_rotation, height)) {
		return FALSE;
	}

	LegoS32 entryIndex =
		m_pieceList->AddEntry(p_pieceRecord, p_x, p_y, p_rotation, p_colorRecordIndex, p_partType, height);
	if (entryIndex == -1) {
		return FALSE;
	}

	StampPiece(p_pieceRecord, p_x, p_y, p_rotation, height, entryIndex);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0049e7c0
void CarBuildModel::PieceGrid::ForEachOccupiedCell(CellCallback p_callback)
{
	for (LegoS32 x = 0; x < m_width; x++) {
		for (LegoS32 y = 0; y < m_height; y++) {
			LegoS32 index = m_height * x + y;
			if (m_entries[index].m_occupied) {
				PieceList::Entry& oldEntry = m_pieceList->m_entries[m_entries[index].m_entryIndex];
				LegoS32 colorRecordIndex = oldEntry.m_colorRecordIndex;
				LegoPieceLibrary::PieceRecord* oldRecord = oldEntry.m_pieceRecord;
				LegoS32 delta = 0;

				if (oldRecord->m_pieceType < g_highPieceTypeBase) {
					LegoS32 oldX;
					LegoS32 oldY;
					LegoS32 oldEntryHeight;
					LegoS32 oldRotation;
					oldEntry.GetPlacement(&oldX, &oldY, &oldEntryHeight, &oldRotation);

					oldX = x - oldX;
					oldY = y - oldY;
					delta = oldRecord->GetCell(oldX, oldY, static_cast<LegoU8>(oldRotation))->GetRaisedBottomHeight();
				}

				p_callback(x, y, m_entries[index].m_height, colorRecordIndex, delta);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e8c0
void CarBuildModel::PieceGrid::RebuildGridWithCallback(CellCallback p_callback)
{
	m_cellCallback = p_callback;
	m_pieceList->RebuildGrid();
	m_cellCallback = NULL;
}

// FUNCTION: LEGORACERS 0x0049e8e0
LegoPieceLibrary::PieceRecord* CarBuildModel::PieceGrid::UnstampPiece(LegoS32 p_index)
{
	if (p_index < 0) {
		return NULL;
	}

	LegoPieceLibrary::PieceRecord* pieceRecord = m_pieceList->m_entries[p_index].m_pieceRecord;
	LegoPieceLibrary::PieceRecord* result = pieceRecord;

	LegoS32 x;
	LegoS32 y;
	LegoS32 entryHeight;
	LegoS32 rotation;
	m_pieceList->m_entries[p_index].GetPlacement(&x, &y, &entryHeight, &rotation);

	LegoS32 width;
	LegoS32 height;
	if (rotation & 1) {
		width = pieceRecord->GetHeight();
		height = pieceRecord->GetWidth();
	}
	else {
		width = pieceRecord->GetWidth();
		height = pieceRecord->GetHeight();
	}

	for (LegoS32 i = 0; i < width; i++) {
		for (LegoS32 j = 0; j < height; j++) {
			LegoPieceLibrary::ShapeCell* cell = pieceRecord->GetCell(i, j, static_cast<LegoU8>(rotation));
			if ((cell->m_first | cell->m_second) & 0x3f) {
				if (m_entries[y + j + ((x + i) * m_height)].m_entryIndex != p_index) {
					result = NULL;
				}
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049e9e0
LegoPieceLibrary::PieceRecord* CarBuildModel::PieceGrid::RemovePiece(LegoS32 p_index)
{
	LegoPieceLibrary::PieceRecord* result = UnstampPiece(p_index);
	if (result != NULL) {
		m_pieceList->RemoveEntry(p_index);
	}

	return result;
}
