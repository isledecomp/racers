#include "model/carbuildmodel.h"

#include "audio/directsoundconversions.h"
#include "core/gol.h"
#include "duskwindbananarelic0x24.h"
#include "gdbmodelindexarray0xc.h"
#include "gdbvertexarray0xc.h"
#include "golanimatedentity.h"
#include "golmodelbase.h"
#include "material/golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "model/legocolortable.h"
#include "render/gold3drenderdevice.h"
#include "surface/color.h"
#include "surface/golddune0x38.h"
#include "surface/purpledune0x7c.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(CarBuildModel, 0x2030)
DECOMP_SIZE_ASSERT(CarBuildModel::Placement, 0x30)
DECOMP_SIZE_ASSERT(CarBuildModel::PieceGrid, 0x14)
DECOMP_SIZE_ASSERT(CarBuildModel::PieceGrid::Entry0x0c, 0x0c)
DECOMP_SIZE_ASSERT(CarBuildModel::BuildVertex, 0x28)
DECOMP_SIZE_ASSERT(CarBuildModel::BuildPrimitive, 0x10)
DECOMP_SIZE_ASSERT(CarBuildModel::BuildPrimitiveBounds, 0x18)
DECOMP_SIZE_ASSERT(CarBuildModel::VertexUse, 0x04)
DECOMP_SIZE_ASSERT(CarBuildModel::OverlayCell, 0x01)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

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
static const LegoFloat g_carBuildModelTextureCoordinateScale = 0.25f;

// GLOBAL: LEGORACERS 0x004b4938
static const LegoFloat g_carBuildModelNegativeHeightScale = -0.4f;

// GLOBAL: LEGORACERS 0x004b4940
static const LegoFloat g_carBuildModelCenterYOffset = 2.5f;

// GLOBAL: LEGORACERS 0x004b4944
static const LegoFloat g_carBuildModelCenterXOffset = 4.5f;

// FUNCTION: LEGORACERS 0x00495020
LegoS32 CarBuildModel::FUN_00495020()
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
LegoS32 CarBuildModel::FUN_00495440()
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
			m_unk0xdc |= c_buildStatusOverflow;                                                                        \
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
		m_unk0xdc |= c_buildStatusOverflow;                                                                            \
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
LegoS32 CarBuildModel::FUN_00497360(LegoS8 p_buildFlags)
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
void CarBuildModel::FUN_00497690(LegoU8 p_buildFlags)
{
	LegoS32 i;

	for (i = m_buildPrimitiveCount; i < c_buildPrimitiveCapacity; i++) {
		m_buildPrimitiveOrder[i] = &m_buildPrimitives[i];
	}

	g_carBuildModelSortVertices = m_buildVertices;

	if (p_buildFlags & c_finalizeResolveIntersectionsFlag) {
		FUN_00495440();
		if (m_unk0xdc & c_buildStatusOverflow) {
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
				m_unk0xdc |= c_buildStatusOverflow;
				return;
			}
		}
	}

	::qsort(m_buildPrimitiveOrder, m_buildPrimitiveCount, sizeof(BuildPrimitive*), ComparePrimitiveDrawOrder);

	if (p_buildFlags & c_finalizePostSortFlag) {
		FUN_00497360(p_buildFlags);
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
void CarBuildModel::Placement::FUN_00499570()
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
void CarBuildModel::Placement::FUN_00499640()
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
void CarBuildModel::Placement::FUN_004997e0()
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
	LegoS32 p_unk0x08,
	LegoS32 p_partType
)
{
	m_width = p_pieceRecord->GetWidth();
	m_height = p_pieceRecord->GetHeight();
	m_colorRecordIndex = p_unk0x08;
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
	FUN_00499640();
	FUN_004997e0();
}

// FUNCTION: LEGORACERS 0x00499a60
void CarBuildModel::Placement::FUN_00499a60()
{
	FUN_00499570();

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

	FUN_00499640();
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
	FUN_00499a60();
}

// FUNCTION: LEGORACERS 0x00499b40
void CarBuildModel::Placement::FUN_00499b40()
{
	if (m_rotation & 1) {
		if (m_gridX + m_height < 10) {
			m_gridX++;
			FUN_00499640();
			FUN_004997e0();
			return;
		}
	}
	else if (m_gridX + m_width < 10) {
		m_gridX++;
		FUN_00499640();
		FUN_004997e0();
	}
}

// FUNCTION: LEGORACERS 0x00499b90
void CarBuildModel::Placement::FUN_00499b90()
{
	if (m_gridX > 0) {
		m_gridX--;
		FUN_00499640();
		FUN_004997e0();
	}
}

// FUNCTION: LEGORACERS 0x00499bb0
void CarBuildModel::Placement::FUN_00499bb0()
{
	if (m_rotation & 1) {
		if (m_gridY + m_width < 6) {
			m_gridY++;
			FUN_00499640();
			FUN_004997e0();
			return;
		}
	}
	else if (m_gridY + m_height < 6) {
		m_gridY++;
		FUN_00499640();
		FUN_004997e0();
	}
}

// FUNCTION: LEGORACERS 0x00499c00
void CarBuildModel::Placement::FUN_00499c00()
{
	if (m_gridY > 0) {
		m_gridY--;
		FUN_00499640();
		FUN_004997e0();
	}
}

// FUNCTION: LEGORACERS 0x00499c20
void CarBuildModel::Placement::FUN_00499c20(LegoS32 p_delta)
{
	if (p_delta > 0) {
		for (LegoS32 i = p_delta; i != 0; i--) {
			FUN_00499b40();
		}
	}
	else if (p_delta < 0) {
		LegoS32 i = -p_delta;
		do {
			FUN_00499b90();
		} while (--i != 0);
	}
}

// FUNCTION: LEGORACERS 0x00499c60
void CarBuildModel::Placement::FUN_00499c60(LegoS32 p_delta)
{
	if (p_delta > 0) {
		for (LegoS32 i = p_delta; i != 0; i--) {
			FUN_00499bb0();
		}
	}
	else if (p_delta < 0) {
		LegoS32 i = -p_delta;
		do {
			FUN_00499c00();
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
	m_unk0xde = 0;
	m_auxModel = NULL;
	m_unk0x2028 = 0;
	m_unk0x202c = 0;
	m_verdantTide = NULL;
	FUN_0049b740(NULL);
	m_hasHighBasePiece = FALSE;
	m_unk0xda = TRUE;
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
void CarBuildModel::FUN_00499e80(LegoColorTable* p_verdantTide)
{
	m_verdantTide = p_verdantTide;
	if (p_verdantTide != NULL) {
		m_unk0x0c.SetPrimaryMaterialTable(p_verdantTide->GetMaterialTable());
	}
	else {
		m_unk0x0c.SetPrimaryMaterialTable(NULL);
	}
}

// FUNCTION: LEGORACERS 0x00499eb0
void CarBuildModel::FUN_00499eb0(GolModelBase* p_model)
{
	p_model->VTable0x18(m_renderer, 2, c_buildVertexCapacity, c_buildPrimitiveCapacity, 1610, 0);
}

// FUNCTION: LEGORACERS 0x00499ee0
void CarBuildModel::FUN_00499ee0()
{
	FUN_00499eb0(m_model);
	AllocateBuffers();
}

// FUNCTION: LEGORACERS 0x00499f00
void CarBuildModel::FUN_00499f00()
{
	m_model->VTable0x24();
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
	LegoColorTable* p_verdantTide
)
{
	GolD3DRenderDevice* renderer = p_renderer;

	if (IsInitialized()) {
		Destroy();
	}

	FUN_00499e80(p_verdantTide);
	m_pieceLibrary = p_pieceLibrary;
	m_golExport = p_golExport;
	m_model = m_golExport->VTable0x14();
	m_renderer = renderer;
	FUN_00499ee0();
	m_unk0x0c.VTable0x50(m_model, g_carBuildModelMaxFloat);

	m_auxModel = m_golExport->VTable0x14();
	m_auxModel->VTable0x18(renderer, 1, 384, 192, 112, 2);
	m_unk0x1f34.VTable0x50(m_auxModel, g_carBuildModelMaxFloat);
	m_unk0x1f34.SetPrimaryMaterialTable(m_auxModel->GetMaterialTable());

	GolMaterialLibrary* materialLibrary = m_verdantTide->GetWorldDatabase()->VTable0x30(1);
	m_auxModel->GetMaterialTable()->SetPosition(0, materialLibrary->GetItem(0));
	m_auxModel->GetMaterialTable()->SetPosition(1, materialLibrary->GetItem(1));

	FUN_0049b720();
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
	GetUnk0x0c()->VTable0x54();
	GetUnk0x1f34()->VTable0x54();

	if (m_golExport != NULL) {
		if (m_model != NULL) {
			m_golExport->VTable0x48(m_model);
		}
		if (m_auxModel != NULL) {
			m_golExport->VTable0x48(m_auxModel);
		}
	}

	FreeBuffers();
	Reset();
}

// FUNCTION: LEGORACERS 0x0049a160
LegoBool32 CarBuildModel::FUN_0049a160(
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
		g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
		allowEmpty = TRUE;
		colorRecordIndex = static_cast<LegoS32>(g_unk0x004befec[g_unk0x004c6ee4]) % 10;
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
LegoS32 CarBuildModel::FUN_0049a1e0(
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

	LegoS32 height = m_pieceGrid.FUN_0049e2d0(p_pieceRecord, p_x, p_y, p_rotation, allowEmpty);
	if (height >= 0) {
		if (m_pieceGrid.FUN_0049e450(p_pieceRecord, p_x, p_y, p_rotation, height)) {
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
void CarBuildModel::FUN_0049a290(GolModelBase* p_model)
{
	m_currentMaterialIndex = 0x7fffffff;
	m_modelGroupCount = 0;
	m_modelVertexCount = 0;
	m_modelTriangleCount = 0;
	m_batchFirstVertex = 0;
	m_batchFirstTriangle = 0;
	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;

	p_model->VTable0x28(&m_modelVertices);

	IGdbModelIndexArray0x8* indexArray;
	p_model->VTable0x30(&indexArray);
	m_modelTriangles = static_cast<GdbModelIndexArray0xc*>(indexArray)->GetMutableIndices();
}

// FUNCTION: LEGORACERS 0x0049a300
void CarBuildModel::FUN_0049a300(GolModelBase* p_model)
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
void CarBuildModel::FUN_0049a3e0(GolModelBase* p_model)
{
	if (m_batchVertexCount || m_batchTriangleCount) {
		FUN_0049a300(p_model);
	}

	p_model->GetMutableGroups()[m_modelGroupCount] = 0xc0000000;
	p_model->SetDirty(TRUE);
	p_model->VTable0x34(TRUE);
	p_model->VTable0x2c(TRUE, TRUE);
	m_modelVertices = NULL;
	m_modelTriangles = NULL;
}

// STUB: LEGORACERS 0x0049a450
LegoS16 CarBuildModel::FUN_0049a450(
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
		LegoS32 colorMaterialIndex = m_verdantTide->GetMaterialIndexForColorRecord(p_colorRecordIndex);
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

				if (mode == c_indexCommandMode0x2000) {
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
						!m_unk0xd9 && m_unk0xdb &&
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
						m_unk0xdc |= c_buildStatusOverflow;
						return static_cast<LegoS16>(m_buildPrimitiveCount);
					}
					primitive->m_vertexIndices[3] = AddBuildVertex(&vertex);
				}
				else {
					primitive = &m_buildPrimitives[primitiveCount];
					m_buildPrimitiveOrder[primitiveCount] = primitive;

					hasTextureIndex = mode == c_indexCommandMode0x1000;
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
						if (!m_unk0xd9 && m_unk0xdb && (command & c_buildPrimitiveCommandTextureBit)) {
							primitive->m_materialIndex = materialIndex + 1;
						}
					}
					else if (!m_unk0xd9 && m_unk0xdb && materialIndex == 2) {
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
							!m_unk0xd9 && m_unk0xdb &&
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
					m_unk0xdc |= c_buildStatusOverflow;
					return static_cast<LegoS16>(newPrimitiveCount);
				}

				remaining--;
			} while (remaining != 0);
		}

		return static_cast<LegoS16>(remaining);
	}

	m_unk0xdc |= c_buildStatusOverflow;
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
LegoS16 CarBuildModel::FUN_0049ad30(
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_height,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_unk0x14
)
{
	LegoS32 colorRecordIndex;
	if (p_unk0x14) {
		colorRecordIndex = m_verdantTide->FindColorRecordIndexByMaterialIndex(p_unk0x14);
	}
	else {
		colorRecordIndex = p_colorRecordIndex;
	}

	return FUN_0049a450(m_highBasePiece, p_x, p_y, 0, p_height, colorRecordIndex, 0);
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
	g_carBuildModelCellCallback->FUN_0049ad30(p_x, p_y, p_height, p_colorRecordIndex, p_delta);
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
		m_unk0xdc |= c_buildStatusOverflow;
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
		m_unk0xdc |= c_buildStatusOverflow;
		return;
	}

	if (static_cast<LegoU32>(m_batchVertexCount + newVertexCount) > c_modelBatchVertexCapacity) {
		FUN_0049a300(model);
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
			FUN_0049a300(model);
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
				m_modelVertices->VTable0x24(m_modelVertexCount, buildVertex->m_position);

				GolVec3 normal;
				normal.m_x = static_cast<LegoFloat>(buildVertex->m_normalX) * g_carBuildModelNormalScale;
				normal.m_y = static_cast<LegoFloat>(buildVertex->m_normalY) * g_carBuildModelNormalScale;
				normal.m_z = static_cast<LegoFloat>(buildVertex->m_normalZ) * g_carBuildModelNormalScale;
				m_modelVertices->VTable0x2c(m_modelVertexCount, normal);
				m_modelVertices->VTable0x28(m_modelVertexCount, buildVertex->m_textureCoordinate);
				m_modelVertices->VTable0x30(m_modelVertexCount, color);
				m_modelVertexCount++;
			}
		}
	}

	GdbModelIndexArray0xc::Indices* indices = &m_modelTriangles[m_modelTriangleCount++];
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
void CarBuildModel::FUN_0049b100(GolModelEntity* p_entity)
{
	for (LegoS32 i = 0; i < m_buildPrimitiveCount; i++) {
		EmitPrimitiveToModel(p_entity, m_buildPrimitiveOrder[i]);
		if (m_unk0xdc & 1) {
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
LegoS32 CarBuildModel::FUN_0049b170(
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
	m_unk0xd9 = m_hasHighBasePiece;
	m_unk0xdb = m_unk0xda;
	m_unk0xde = 0xef;
	m_unk0xdc = 0;

	if (m_verdantTide != NULL) {
		p_entity->SetPrimaryMaterialTable(m_verdantTide->GetMaterialTable());
	}

	FUN_00495020();
	m_buildPrimitiveCount = 0;
	FUN_0049a450(pieceRecord, p_x, p_y, p_rotation, p_height, p_colorRecordIndex, 0);

	if (m_unk0xd9) {
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
					FUN_0049ad30(p_x + x, p_y + y, p_height + (cellFlags & 0x3f), p_colorRecordIndex, 0);
				}
			}
		}
	}

	FUN_00497690(0xef);

	for (LegoS32 i = 0; i < m_buildVertexCount; i++) {
		m_buildVertices[i].m_position.m_x += m_unk0x1f04;
		m_buildVertices[i].m_position.m_y += m_unk0x1f08;
		m_buildVertices[i].m_position.m_z = (m_buildVertices[i].m_position.m_z * 0.4f) + m_unk0x1f0c;
	}

	FUN_0049a290(model);
	FUN_0049b100(p_entity);
	FUN_0049a3e0(model);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0049b340
void CarBuildModel::FUN_0049b340(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_rotation)
{
	LegoPieceLibrary* library = p_pieceRecord->m_library;
	const LegoU16* indexCursor = library->GetIndexCursor(p_pieceRecord->m_indexOffset);
	LegoS32 indexCount = p_pieceRecord->m_indexCommandCount;
	if (indexCount == 0) {
		m_unk0x1f30 = 0.0f;
		m_unk0x1f2c = 0.0f;
		m_unk0x1f28 = 0.0f;
		m_unk0x1f24 = 0.0f;
		m_unk0x1f20 = 0.0f;
		m_unk0x1f1c = 0.0f;
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
		if (mode == c_indexCommandMode0x2000) {
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
			hasExtraIndex = mode == c_indexCommandMode0x1000;
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
			m_unk0x1f1c = minY;
			m_unk0x1f20 = maxY;
			m_unk0x1f24 = width - maxX;
			m_unk0x1f28 = width - minX;
			break;
		case 2:
			m_unk0x1f1c = width - maxX;
			m_unk0x1f20 = width - minX;
			m_unk0x1f24 = height - maxY;
			m_unk0x1f28 = height - minY;
			break;
		case 3:
			m_unk0x1f1c = height - maxY;
			m_unk0x1f20 = height - minY;
			m_unk0x1f24 = minX;
			m_unk0x1f28 = maxX;
			break;
		}
	}
	else {
		m_unk0x1f1c = minX;
		m_unk0x1f20 = maxX;
		m_unk0x1f24 = minY;
		m_unk0x1f28 = maxY;
	}

	m_unk0x1f2c = minZ * 0.4f;
	m_unk0x1f30 = maxZ * 0.4f;
}

// FUNCTION: LEGORACERS 0x0049b6f0
void CarBuildModel::FUN_0049b6f0(LegoFloat p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c)
{
	m_unk0x1f04 = p_unk0x04;
	m_unk0x1f08 = p_unk0x08;
	m_unk0x1f0c = p_unk0x0c;
}

// FUNCTION: LEGORACERS 0x0049b720
void CarBuildModel::FUN_0049b720()
{
	m_unk0x1f04 = -5.0f;
	m_unk0x1f08 = -3.0f;
	m_unk0x1f0c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0049b740
void CarBuildModel::FUN_0049b740(LegoBool32 p_restoreCachedOffset)
{
	if (p_restoreCachedOffset) {
		FUN_0049b6f0(m_unk0x1f10, m_unk0x1f14, m_unk0x1f18);
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
		FUN_0049bce0(0, &pieceRecord, &x, &y, &height, &rotation, &colorRecordIndex, &partType);

		library = pieceRecord->m_library;
		partType = pieceRecord->FUN_0049f690();
		if (partType != 0xffff) {
			library->GetColor(partType, &m_unk0x1f04, &m_unk0x1f08, &m_unk0x1f0c);
			m_unk0x1f0c *= g_carBuildModelNegativeHeightScale;
			m_unk0x1f04 = -m_unk0x1f04;
			m_unk0x1f08 = -m_unk0x1f08;
		}
		else {
			FUN_0049b340(pieceRecord, rotation);
			LegoFloat xOffset = static_cast<LegoFloat>(x);
			m_unk0x1f04 = -((m_unk0x1f20 + m_unk0x1f1c) * 0.5f) - xOffset;

			LegoFloat yOffset = static_cast<LegoFloat>(y);
			m_unk0x1f08 = -((m_unk0x1f28 + m_unk0x1f24) * 0.5f) - yOffset;

			LegoFloat heightOffset = static_cast<LegoFloat>(height);
			m_unk0x1f0c = -m_unk0x1f2c - (heightOffset * g_carBuildModelHeightScale);
		}
	}
	else {
		FUN_0049b720();
	}

	m_unk0x1f10 = m_unk0x1f04;
	m_unk0x1f14 = m_unk0x1f08;
	m_unk0x1f18 = m_unk0x1f0c;
}

// FUNCTION: LEGORACERS 0x0049b8b0
void CarBuildModel::FUN_0049b8b0(LegoPieceLibrary::PieceRecord* p_pieceRecord, LegoS32 p_rotation)
{
	FUN_0049b340(p_pieceRecord, p_rotation);

	m_unk0x1f04 = -((m_unk0x1f20 + m_unk0x1f1c) * 0.5f);
	m_unk0x1f08 = -((m_unk0x1f28 + m_unk0x1f24) * 0.5f);
	m_unk0x1f0c = -((m_unk0x1f30 + m_unk0x1f2c) * 0.5f);
}

// STUB: LEGORACERS 0x0049b920
void CarBuildModel::FUN_0049b920(LegoS32 p_variant, LegoU32 p_buildFlags)
{
	LegoS32 activePieceCount = m_placedPieceCount;
	LegoS32 i;
	m_unk0xde = static_cast<LegoU16>(p_buildFlags);
	m_pieceList.SetVariant(p_variant, TRUE);
	m_unk0xdc = 0;
	m_buildPrimitiveCount = 0;

	LegoU8 startFlags;
	do {
		FUN_00495020();
		m_unk0xdc <<= 1;
		m_buildPrimitiveCount = 0;
		if ((m_unk0xdc & 0xf8) && activePieceCount > 1) {
			activePieceCount--;
			m_unk0xdc &= 7;
		}

		startFlags = m_unk0xdc;
		if (startFlags & 0xfc) {
			m_unk0xd9 = FALSE;
			m_unk0xdb = FALSE;
		}
		else if (startFlags & 0xfe) {
			m_unk0xd9 = FALSE;
			m_unk0xdb = m_hasHighBasePiece || m_unk0xda;
		}
		else {
			m_unk0xd9 = m_hasHighBasePiece;
			m_unk0xdb = m_unk0xda;
		}

		for (i = 0; i < activePieceCount; i++) {
			PieceList::Entry0x1c* entry = &m_pieceList.m_entries[i];
			LegoS32 x;
			LegoS32 y;
			LegoS32 height;
			LegoS32 rotation;
			entry->GetPlacement(&x, &y, &height, &rotation);
			FUN_0049a450(entry->m_pieceRecord, x, y, rotation, height, entry->m_colorRecordIndex, i);
		}

		if (!(m_unk0xdc & 1)) {
			g_carBuildModelCellCallback = this;
			if (m_unk0xd9) {
				m_pieceGrid.FUN_0049e7c0(AddHighBasePieceCallback);
				m_pieceGrid.FUN_0049e8c0(AddHighBasePieceCallback);
			}

			if (!(m_unk0xdc & 1)) {
				if (p_buildFlags) {
					FUN_00497690(static_cast<LegoU8>(p_buildFlags));
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

			if (!(m_unk0xdc & 1)) {
				for (i = 0; i < m_buildVertexCount; i++) {
					m_buildVertices[i].m_position.m_x = m_unk0x1f04 + m_buildVertices[i].m_position.m_x;
					m_buildVertices[i].m_position.m_y += m_unk0x1f08;
					m_buildVertices[i].m_position.m_z = (m_buildVertices[i].m_position.m_z * 0.4f) + m_unk0x1f0c;
				}

				FUN_0049a290(m_model);
				FUN_0049b100(&m_unk0x0c);
				FUN_0049a3e0(m_model);
			}
		}
	} while (m_unk0xdc != startFlags);

	if (activePieceCount != m_placedPieceCount) {
		m_unk0xdc |= 8;
	}

	if (m_verdantTide != NULL && m_buildPrimitiveCount != 0) {
		m_verdantTide->ResetMaterialUsage();
		m_currentMaterialIndex = m_buildPrimitiveOrder[0]->m_materialIndex;
		m_verdantTide->MarkMaterialUsed(m_currentMaterialIndex);

		for (i = 1; i < m_buildPrimitiveCount; i++) {
			LegoU32 materialIndex = m_buildPrimitiveOrder[i]->m_materialIndex;
			if (m_currentMaterialIndex != materialIndex) {
				m_currentMaterialIndex = materialIndex;
				m_verdantTide->MarkMaterialUsed(materialIndex);
			}
		}

		m_unk0x1ee8 = m_verdantTide->GetUsedMaterialCount();
		m_unk0x1eec = m_verdantTide->GetTransparentMaterialCount();
	}
	else {
		m_unk0x1eec = 0;
		m_unk0x1ee8 = 0;
	}

	m_unk0x1ef0 = m_modelGroupCount;
	m_unk0x1ef4 = m_modelTriangleCount;
	m_unk0x1ef8 = m_modelVertexCount;
}

// FUNCTION: LEGORACERS 0x0049bc60
void CarBuildModel::FUN_0049bc60(GolModelBase* p_model, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	GolModelBase* model = m_model;
	m_model = p_model;
	MaterialTable0x0c* materialTable = m_unk0x0c.GetPrimaryMaterialTable();
	m_unk0x0c.VTable0x50(p_model, g_carBuildModelMaxFloat);
	FUN_0049b920(p_unk0x08, p_unk0x0c);
	m_model = model;
	m_unk0x0c.VTable0x50(model, g_carBuildModelMaxFloat);
	m_unk0x0c.SetPrimaryMaterialTable(materialTable);
}

// FUNCTION: LEGORACERS 0x0049bcc0
LegoS32 CarBuildModel::FUN_0049bcc0(LegoS32 p_x, LegoS32 p_y) const
{
	return m_pieceGrid.m_entries[p_y + (p_x * m_pieceGrid.m_height)].m_entryIndex;
}

// FUNCTION: LEGORACERS 0x0049bce0
void CarBuildModel::FUN_0049bce0(
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
LegoS32 CarBuildModel::FUN_0049bd50(LegoS32 p_index) const
{
	return m_pieceList.m_entries[p_index].m_partType;
}

// FUNCTION: LEGORACERS 0x0049bd70
LegoPieceLibrary::PieceRecord* CarBuildModel::FUN_0049bd70(LegoS32 p_index)
{
	if (p_index >= 0 && p_index < m_placedPieceCount && m_pieceGrid.FUN_0049e8e0(p_index)) {
		LegoPieceLibrary::PieceRecord* result = m_pieceGrid.FUN_0049e9e0(p_index);
		m_placedPieceCount = m_pieceList.m_entryCount;

		return result;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0049bdc0
void CarBuildModel::FUN_0049bdc0()
{
	FUN_0049bd70(m_placedPieceCount - 1);
}

// FUNCTION: LEGORACERS 0x0049bdd0
void CarBuildModel::FUN_0049bdd0(GolD3DRenderDevice* p_renderer, LegoFloat p_unk0x08)
{
	GolVec3 position;
	m_unk0x0c.VTable0x04(&position);
	position.m_z += p_unk0x08;
	m_unk0x1f34.VTable0x08(position);

	GolMatrix3 matrix;
	m_unk0x0c.VTable0x44(&matrix);
	m_unk0x1f34.VTable0x3c(matrix);

	if (m_unk0x202c) {
		p_renderer->VTable0x94(&m_unk0x1f34);
	}
}

// FUNCTION: LEGORACERS 0x0049be50
void CarBuildModel::FUN_0049be50(LegoS32 p_x, LegoS32 p_y)
{
	if (m_overlayCells[p_x + 1][p_y + 1].m_flags & c_overlayCellFlagOccupied) {
		m_overlayCells[p_x + 1][p_y + 1].m_flags |= c_overlayCellFlagDraw;
	}
}

// FUNCTION: LEGORACERS 0x0049be70
void CarBuildModel::FUN_0049be70(LegoBool32 p_unk0x04, LegoS32 p_height)
{
	LegoS32 disabled = FALSE;
	LegoS32 enabled = TRUE;

	ColorRGBA color;
	color.m_red = 0xff;
	color.m_grn = 0xff;
	color.m_blu = 0xff;
	color.m_alp = 0xff;

	p_unk0x04 &= enabled;
	if (p_height < 0) {
		p_height = m_unk0x2028;
	}

	FUN_0049a290(m_auxModel);

	LegoU32 groupIndex = m_modelGroupCount;
	m_unk0x202c = disabled;
	m_modelGroupCount++;
	m_auxModel->GetMutableGroups()[groupIndex] = c_modelMaterialGroup;
	m_auxModel->GetMutableGroups()[groupIndex] |= enabled;
	m_auxModel->SetDirty(enabled);

	GolVec3 position;
	position.m_z = (static_cast<LegoFloat>(p_height) * 0.4f) + m_unk0x1f0c;
	GolVec2 texCoord;
	LegoS32 quadVertexCount = 4;
	LegoS32 quadTriangleCount = 2;

	LegoS32 x = disabled;
	for (; x < 12; x++) {
		for (LegoS32 y = disabled; y < 8; y++) {
			if ((m_overlayCells[x][y].m_flags & c_overlayCellFlagOccupied) &&
				(m_overlayCells[x][y].m_flags & c_overlayCellFlagDraw)) {
				if (static_cast<LegoU32>(m_batchVertexCount + quadVertexCount) > c_modelBatchVertexCapacity) {
					m_unk0x202c += m_batchTriangleCount;
					FUN_0049a300(m_auxModel);
				}

				position.m_x = static_cast<LegoFloat>(x - 1) + m_unk0x1f04;
				position.m_y = static_cast<LegoFloat>(y - 1) + m_unk0x1f08;
				texCoord.m_x = 0.5f;
				texCoord.m_y = 0.5f;
				if (!p_unk0x04) {
					texCoord.m_y = 0.0f;
				}

				m_modelVertices->VTable0x24(m_modelVertexCount, position);
				m_modelVertices->VTable0x28(m_modelVertexCount, texCoord);
				m_modelVertices->VTable0x30(m_modelVertexCount, color);

				m_modelVertexCount++;
				position.m_x += 1.0f;
				texCoord.m_x += 0.49f;
				m_modelVertices->VTable0x24(m_modelVertexCount, position);
				m_modelVertices->VTable0x28(m_modelVertexCount, texCoord);
				m_modelVertices->VTable0x30(m_modelVertexCount, color);

				m_modelVertexCount++;
				position.m_y += 1.0f;
				texCoord.m_y += 0.49f;
				m_modelVertices->VTable0x24(m_modelVertexCount, position);
				m_modelVertices->VTable0x28(m_modelVertexCount, texCoord);
				m_modelVertices->VTable0x30(m_modelVertexCount, color);

				m_modelVertexCount++;
				position.m_x -= 1.0f;
				texCoord.m_x -= 0.49f;
				m_modelVertices->VTable0x24(m_modelVertexCount, position);
				m_modelVertices->VTable0x28(m_modelVertexCount, texCoord);
				m_modelVertices->VTable0x30(m_modelVertexCount, color);

				m_modelVertexCount++;
				GdbModelIndexArray0xc::Indices* triangles = &m_modelTriangles[m_modelTriangleCount];
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
		m_unk0x202c += m_batchTriangleCount;
		FUN_0049a300(m_auxModel);
	}

	FUN_0049a3e0(m_auxModel);
}

// STUB: LEGORACERS 0x0049c230
void CarBuildModel::FUN_0049c230(Placement* p_placement, GolModelEntity* p_entity)
{
	GolModelBase* model = p_entity->GetModel(0);
	::memset(m_overlayCells, 0, sizeof(m_overlayCells));
	FUN_0049b740(TRUE);

	LegoS32 x;
	LegoS32 entryHeight;
	LegoPieceLibrary::PieceRecord* pieceRecord = p_placement->GetPieceRecord();
	LegoS32 rotation;
	if (pieceRecord != NULL) {
		LegoS32 y;
		p_placement->GetPlacement(&x, &y, &rotation);

		LegoS32 partType = p_placement->GetPartType();
		LegoS32 colorRecordIndex = p_placement->GetColorRecordIndex();
		FUN_0049b170(p_entity, pieceRecord, x, y, 21, rotation, colorRecordIndex, 239);

		if (pieceRecord->m_pieceType == 0x7ff) {
			LegoS32 entryIndex = FUN_0049bcc0(x, y);
			if (entryIndex >= 0) {
				FUN_0049bce0(entryIndex, &pieceRecord, &x, &y, &entryHeight, &rotation, &colorRecordIndex, &partType);
				if (pieceRecord->m_pieceType < g_highPieceTypeBase) {
					entryIndex = -1;
				}
			}

			m_unk0x2028 = 18;
			if (entryIndex < 0) {
				p_placement->GetPlacement(&x, &y, &rotation);
				m_overlayCells[x + 1][y + 1].m_flags |= c_overlayCellFlagOccupiedDraw;
				FUN_0049be70(FALSE, -1);
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
						if (entryIndex != FUN_0049bcc0(x + i, y + j)) {
							m_overlayCells[x + i + 1][y + j + 1].m_flags |= c_overlayCellFlagDraw;
						}
					}
				}
			}
		}
		else {
			m_unk0x2028 = 0;

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
						m_overlayCells[x + i + 1][y + j + 2].m_flags |= c_overlayCellFlag0x01;
						m_overlayCells[x + i + 2][y + j + 1].m_flags |= c_overlayCellFlag0x02;
						m_overlayCells[x + i + 1][y + j].m_flags |= c_overlayCellFlag0x04;
						m_overlayCells[x + i][y + j + 1].m_flags |= c_overlayCellFlag0x08;

						LegoS32 gridHeight = m_pieceGrid.m_entries[y + j + ((x + i) * m_pieceGrid.m_height)].m_height;
						if (m_unk0x2028 < gridHeight) {
							m_unk0x2028 = gridHeight;
						}
					}
				}
			}

			if (m_unk0x2028 > 15) {
				m_unk0x2028 = 15;
			}

			LegoS32 pieceHeight = FUN_0049a1e0(pieceRecord, x, y, rotation);
			if (pieceHeight == -5) {
				pieceHeight = m_pieceGrid.FUN_0049e2d0(pieceRecord, x, y, rotation, FALSE);
			}
			m_pieceGrid.FUN_0049e590(this, pieceRecord, x, y, rotation, pieceHeight);
		}

		FUN_0049be70(FALSE, -1);
	}
	else {
		FUN_0049a290(model);
		FUN_0049a3e0(model);
		GolModelBase* auxModel = m_auxModel;
		FUN_0049a290(auxModel);
		FUN_0049a3e0(auxModel);
	}
}

// STUB: LEGORACERS 0x0049c6a0
LegoS32 CarBuildModel::FUN_0049c6a0(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08, LegoFloat* p_unk0x0c)
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
			PieceList::Entry0x1c* entry = &m_pieceList.m_entries[entryIndex];
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
				LegoS32 count = pieceRecord->FUN_0049f560(x, y, height, rotation, &pieceX, &pieceY, &pieceZ);
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
		*p_unk0x04 = static_cast<LegoFloat>(xTotal) / count - g_carBuildModelCenterXOffset;
		*p_unk0x08 = static_cast<LegoFloat>(yTotal) / count - g_carBuildModelCenterYOffset;
		*p_unk0x0c = static_cast<LegoFloat>(zTotal) / count;
	}
	else {
		*p_unk0x0c = 0.0f;
		*p_unk0x08 = 0.0f;
		*p_unk0x04 = 0.0f;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049c7f0
LegoBool32 CarBuildModel::FUN_0049c7f0(LegoU8* p_source)
{
	LegoBool32 result = m_pieceList.Deserialize(p_source, m_pieceLibrary, 15);
	m_placedPieceCount = m_pieceList.m_entryCount;

	return result;
}

// FUNCTION: LEGORACERS 0x0049c820
void CarBuildModel::FUN_0049c820(LegoU8* p_dest)
{
	m_pieceList.Serialize(p_dest);
}

// STUB: LEGORACERS 0x0049c840
void CarBuildModel::FUN_0049c840(GolModelBase* p_model, GolMaterialLibrary* p_materials, GolTextureList* p_textures)
{
	GdbVertexArray0xc* sourceVertices;
	GdbVertexArray0xc* destVertices;
	LegoS32 i;
	LegoS32 materialCount = m_verdantTide->GetMaterialCount();
	const LegoColorTable::MaterialUsage* materialUsage = m_verdantTide->GetMaterialUsage();
	ColorRGBA color;
	MaterialTable0x0c* materialTable = m_verdantTide->GetMaterialTable();
	GolModelBase* outputModel = p_model;
	IGdbModelIndexArray0x8* sourceIndexArray;
	IGdbModelIndexArray0x8* destIndexArray;
	GolVec2 texCoord;
	GolVec3 position;
	GolVec3 normal;
	DuskWindBananaRelicParams params;

	LegoS32 outputMaterialIndex = 0;
	LegoS32 textureIndex = 0;
	for (i = 0; i < materialCount; i++) {
		if (materialUsage[i].m_used) {
			DuskwindBananaRelic0x24* sourceMaterial =
				static_cast<DuskwindBananaRelic0x24*>(materialTable->GetPosition(i));

			sourceMaterial->CopyParamsTo(&params);
			params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flagBit0;

			DuskwindBananaRelic0x24* outputMaterial = p_materials->GetItem(outputMaterialIndex);
			if (sourceMaterial->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
				PurpleDune0x7c* outputTexture = p_textures->GetItem(textureIndex);
				PurpleDune0x7c* sourceTexture = static_cast<PurpleDune0x7c*>(sourceMaterial->GetUnk0x04());

				outputTexture->CopySourceTextureDefinitionFrom(sourceTexture);
				params.m_unk0x04 = outputTexture;
				textureIndex++;
			}

			outputMaterial->FUN_100257e0(m_renderer, params);
			outputModel->GetMaterialTable()->SetPosition(outputMaterialIndex, outputMaterial);
			outputMaterialIndex++;
		}
	}

	for (i = 0; i < static_cast<LegoS32>(m_unk0x1ef0); i++) {
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

	m_model->VTable0x28(&sourceVertices);
	m_model->VTable0x30(&sourceIndexArray);
	const GdbModelIndexArray0xc::Indices* sourceIndices =
		static_cast<GdbModelIndexArray0xc*>(sourceIndexArray)->GetIndices();

	outputModel->VTable0x28(&destVertices);
	outputModel->VTable0x30(&destIndexArray);
	GdbModelIndexArray0xc::Indices* destIndices =
		static_cast<GdbModelIndexArray0xc*>(destIndexArray)->GetMutableIndices();
	::memcpy(destIndices, sourceIndices, sizeof(*destIndices) * m_unk0x1ef4);

	for (i = 0; i < static_cast<LegoS32>(m_unk0x1ef8); i++) {
		sourceVertices->VTable0x14(i, &position);
		destVertices->VTable0x24(i, position);
		sourceVertices->VTable0x18(i, &texCoord);
		destVertices->VTable0x28(i, texCoord);
		sourceVertices->VTable0x1c(i, &normal);
		destVertices->VTable0x2c(i, normal);
		sourceVertices->VTable0x20(i, &color);
		destVertices->VTable0x30(i, color);
	}

	m_model->VTable0x34(FALSE);
	m_model->VTable0x2c(FALSE, FALSE);
	outputModel->VTable0x34(TRUE);
	outputModel->VTable0x2c(TRUE, TRUE);
}

// FUNCTION: LEGORACERS 0x0049df20
void CarBuildModel::PieceGrid::Entry0x0c::Reset()
{
	m_entryIndex = -1;
	m_height = 0;
	m_occupied = FALSE;
	m_unk0x09 = 0;
}

// FUNCTION: LEGORACERS 0x0049df40
void CarBuildModel::PieceGrid::FUN_0049df40(
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
						PieceList::Entry0x1c& oldEntry = m_pieceList->m_entries[m_entries[index].m_entryIndex];
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
							delta = oldRecord->GetCell(oldX, oldY, static_cast<LegoU8>(oldRotation))->FUN_0049ea40();
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
	m_entries = new Entry0x0c[p_width * p_height];
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
LegoS32 CarBuildModel::PieceGrid::FUN_0049e2d0(
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
			Entry0x0c& gridEntry = m_entries[m_height * (p_x + x) + y + p_y];
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
LegoS32 CarBuildModel::PieceGrid::FUN_0049e450(
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
void CarBuildModel::PieceGrid::FUN_0049e590(
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
				p_model->FUN_0049be50(p_x + x, p_y + y);
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
						p_model->FUN_0049be50(p_x + x, p_y + y);
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
	LegoS32 height = FUN_0049e2d0(p_pieceRecord, p_x, p_y, p_rotation, p_allowEmpty);
	if (height < 0) {
		return FALSE;
	}

	if (FUN_0049e450(p_pieceRecord, p_x, p_y, p_rotation, height)) {
		return FALSE;
	}

	LegoS32 entryIndex =
		m_pieceList->AddEntry(p_pieceRecord, p_x, p_y, p_rotation, p_colorRecordIndex, p_partType, height);
	if (entryIndex == -1) {
		return FALSE;
	}

	FUN_0049df40(p_pieceRecord, p_x, p_y, p_rotation, height, entryIndex);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0049e7c0
void CarBuildModel::PieceGrid::FUN_0049e7c0(CellCallback p_callback)
{
	for (LegoS32 x = 0; x < m_width; x++) {
		for (LegoS32 y = 0; y < m_height; y++) {
			LegoS32 index = m_height * x + y;
			if (m_entries[index].m_occupied) {
				PieceList::Entry0x1c& oldEntry = m_pieceList->m_entries[m_entries[index].m_entryIndex];
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
					delta = oldRecord->GetCell(oldX, oldY, static_cast<LegoU8>(oldRotation))->FUN_0049ea40();
				}

				p_callback(x, y, m_entries[index].m_height, colorRecordIndex, delta);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0049e8c0
void CarBuildModel::PieceGrid::FUN_0049e8c0(CellCallback p_callback)
{
	m_cellCallback = p_callback;
	m_pieceList->FUN_0049f930();
	m_cellCallback = NULL;
}

// FUNCTION: LEGORACERS 0x0049e8e0
LegoPieceLibrary::PieceRecord* CarBuildModel::PieceGrid::FUN_0049e8e0(LegoS32 p_index)
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
LegoPieceLibrary::PieceRecord* CarBuildModel::PieceGrid::FUN_0049e9e0(LegoS32 p_index)
{
	LegoPieceLibrary::PieceRecord* result = FUN_0049e8e0(p_index);
	if (result != NULL) {
		m_pieceList->RemoveEntry(p_index);
	}

	return result;
}
