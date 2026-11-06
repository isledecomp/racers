#include "audio/directsoundconversions.h"
#include "compat.h"
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
		LegoS32 compare = CompareBuildVertex(p_vertex, node);
		if (compare != 0) {
			do {
				if (compare > 0) {
					if (node->m_right == NULL) {
						p_vertex->m_parent = node;
						node->m_right = p_vertex;
						node = NULL;
						break;
					}

					node = node->m_right;
				}
				else {
					if (node->m_left == NULL) {
						p_vertex->m_parent = node;
						node->m_left = p_vertex;
						node = NULL;
						break;
					}

					node = node->m_left;
				}
			} while (node != NULL && (compare = CompareBuildVertex(p_vertex, node)) != 0);
		}

		if (node != NULL) {
			return node;
		}

		RebalanceBuildVertexInsert(p_root, p_vertex);
		return NULL;
	}

	p_vertex->m_parent = NULL;
	p_vertex->m_treeBlack = TRUE;
	*p_root = p_vertex;

	return NULL;
}

#ifdef COMPAT_MODE

LegoS32 __fastcall CarBuildModel::CompareBuildVertex(const BuildVertex* p_lhs, const BuildVertex* p_rhs)
{
	LegoS32 lhsKey;
	LegoS32 rhsKey;

	::memcpy(&lhsKey, &p_lhs->m_position.m_x, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_position.m_x, sizeof(rhsKey));
	lhsKey -= rhsKey;
	if (lhsKey != 0) {
		return lhsKey;
	}

	::memcpy(&lhsKey, &p_lhs->m_position.m_y, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_position.m_y, sizeof(rhsKey));
	lhsKey -= rhsKey;
	if (lhsKey != 0) {
		return lhsKey;
	}

	::memcpy(&lhsKey, &p_lhs->m_position.m_z, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_position.m_z, sizeof(rhsKey));
	lhsKey -= rhsKey;
	if (lhsKey != 0) {
		return lhsKey;
	}

	// Equal normal comparisons leave lhsKey zero; only the low byte is replaced.
	lhsKey = 0;
	rhsKey = 0;
	::memcpy(&lhsKey, &p_lhs->m_normalX, sizeof(LegoU8));
	::memcpy(&rhsKey, &p_rhs->m_normalX, sizeof(LegoU8));
	lhsKey -= rhsKey;
	if (lhsKey != 0) {
		return lhsKey;
	}

	::memcpy(&lhsKey, &p_lhs->m_normalY, sizeof(LegoU8));
	::memcpy(&rhsKey, &p_rhs->m_normalY, sizeof(LegoU8));
	lhsKey -= rhsKey;
	if (lhsKey != 0) {
		return lhsKey;
	}

	::memcpy(&lhsKey, &p_lhs->m_normalZ, sizeof(LegoU8));
	::memcpy(&rhsKey, &p_rhs->m_normalZ, sizeof(LegoU8));
	lhsKey -= rhsKey;
	if (lhsKey != 0) {
		return lhsKey;
	}

	::memcpy(&lhsKey, &p_lhs->m_textureCoordinate.m_x, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_textureCoordinate.m_x, sizeof(rhsKey));
	lhsKey -= rhsKey;
	if (lhsKey != 0) {
		return lhsKey;
	}

	::memcpy(&lhsKey, &p_lhs->m_textureCoordinate.m_y, sizeof(lhsKey));
	::memcpy(&rhsKey, &p_rhs->m_textureCoordinate.m_y, sizeof(rhsKey));
	lhsKey -= rhsKey;

	return lhsKey;
}

#else

// FUNCTION: LEGORACERS 0x00495160
__declspec(naked) LegoS32 __fastcall CarBuildModel::CompareBuildVertex(
	const BuildVertex* p_lhs,
	const BuildVertex* p_rhs
)
{
	// Compares the raw position bits, the normal bytes (unsigned) and the raw texture coordinate bits.
	// The normal bytes reuse the zero upper bits left by each equal comparison.
	__asm {
		push ebx
		mov eax, dword ptr [ecx + 0x14]
		mov ebx, dword ptr [edx + 0x14]
		sub eax, ebx
		jne L_CompareBuildVertex_done
		mov eax, dword ptr [ecx + 0x18]
		mov ebx, dword ptr [edx + 0x18]
		sub eax, ebx
		jne L_CompareBuildVertex_done
		mov eax, dword ptr [ecx + 0x1c]
		mov ebx, dword ptr [edx + 0x1c]
		sub eax, ebx
		jne L_CompareBuildVertex_done
		xor eax, eax
		xor ebx, ebx
		mov al, byte ptr [ecx + 0xf]
		mov bl, byte ptr [edx + 0xf]
		sub eax, ebx
		jne L_CompareBuildVertex_done
		mov al, byte ptr [ecx + 0x10]
		mov bl, byte ptr [edx + 0x10]
		sub eax, ebx
		jne L_CompareBuildVertex_done
		mov al, byte ptr [ecx + 0x11]
		mov bl, byte ptr [edx + 0x11]
		sub eax, ebx
		jne L_CompareBuildVertex_done
		mov eax, dword ptr [ecx + 0x20]
		mov ebx, dword ptr [edx + 0x20]
		sub eax, ebx
		jne L_CompareBuildVertex_done
		mov eax, dword ptr [ecx + 0x24]
		mov ebx, dword ptr [edx + 0x24]
		sub eax, ebx
	L_CompareBuildVertex_done:
		pop ebx
		ret
	}
}

#endif

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
void CarBuildModel::ResolvePrimitiveIntersections()
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
			return;                                                                                                    \
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
		return;                                                                                                        \
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
		BuildVertex* firstLowVertex = &m_buildVertices[primitive->m_vertexIndices[0]];                                 \
		rightScale = rightScale / (lhsBounds.maxField - lhsBounds.minField);                                           \
		BuildVertex* firstHighVertex = &m_buildVertices[primitive->m_vertexIndices[2]];                                \
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
		BuildVertex* firstLowVertex = &m_buildVertices[primitive->m_vertexIndices[0]];                                 \
		rightScale = rightScale / (lhsBounds.maxField - lhsBounds.minField);                                           \
		BuildVertex* firstHighVertex = &m_buildVertices[primitive->m_vertexIndices[2]];                                \
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
	LegoS32 planePrimitiveCount;
	LegoS32 lhsIndex;
	LegoS32 rhsIndex;
	LegoU16 splitFirstIndex;
	LegoU16 splitSecondIndex;
	LegoFloat leftScale;
	LegoFloat rightScale;
	BuildPrimitive* primitive;
	BuildPrimitive* outsidePrimitive;
	BuildPrimitive* swappedPrimitive;
	BuildPrimitive* lhs;
	BuildPrimitiveBounds swappedBounds;
	BuildVertex* secondLowVertex;
	BuildVertex* secondHighVertex;
	BuildVertex splitVertex;

	{
		for (i = 0, planePrimitiveCount = 0; i < m_buildPrimitiveCount; i++) {
			BuildPrimitive* primitive = m_buildPrimitiveOrder[i];
			if ((primitive->m_flags & 0x89) == 0x89 && primitive->m_vertexCount == 4) {
				m_buildPrimitiveOrder[i] = m_buildPrimitiveOrder[planePrimitiveCount++];
				m_buildPrimitiveOrder[planePrimitiveCount - 1] = primitive;
			}
		}

		for (lhsIndex = 0; lhsIndex < planePrimitiveCount - 1; lhsIndex++) {
			BuildPrimitiveBounds lhsBounds;
			GetBuildPrimitiveBounds(m_buildPrimitiveOrder[lhsIndex], &lhsBounds);

			for (rhsIndex = lhsIndex + 1; rhsIndex < planePrimitiveCount; rhsIndex++) {
				BuildPrimitiveBounds rhsBounds;
				GetBuildPrimitiveBounds(m_buildPrimitiveOrder[rhsIndex], &rhsBounds);

				LegoFloat planeDelta = lhsBounds.m_minZ - rhsBounds.m_minZ;
				lhs = m_buildPrimitiveOrder[lhsIndex];
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
		for (i = 0, planePrimitiveCount = 0; i < m_buildPrimitiveCount; i++) {
			BuildPrimitive* primitive = m_buildPrimitiveOrder[i];
			if ((primitive->m_flags & 0x85) == 0x85 && primitive->m_vertexCount == 4) {
				m_buildPrimitiveOrder[i] = m_buildPrimitiveOrder[planePrimitiveCount++];
				m_buildPrimitiveOrder[planePrimitiveCount - 1] = primitive;
			}
		}

		for (lhsIndex = 0; lhsIndex < planePrimitiveCount - 1; lhsIndex++) {
			BuildPrimitiveBounds lhsBounds;
			GetBuildPrimitiveBounds(m_buildPrimitiveOrder[lhsIndex], &lhsBounds);

			for (rhsIndex = lhsIndex + 1; rhsIndex < planePrimitiveCount; rhsIndex++) {
				BuildPrimitiveBounds rhsBounds;
				GetBuildPrimitiveBounds(m_buildPrimitiveOrder[rhsIndex], &rhsBounds);

				lhs = m_buildPrimitiveOrder[lhsIndex];
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

	{
		for (i = 0, planePrimitiveCount = 0; i < m_buildPrimitiveCount; i++) {
			BuildPrimitive* primitive = m_buildPrimitiveOrder[i];
			if ((primitive->m_flags & 0x83) == 0x83 && primitive->m_vertexCount == 4) {
				m_buildPrimitiveOrder[i] = m_buildPrimitiveOrder[planePrimitiveCount++];
				m_buildPrimitiveOrder[planePrimitiveCount - 1] = primitive;
			}
		}

		for (lhsIndex = 0; lhsIndex < planePrimitiveCount - 1; lhsIndex++) {
			BuildPrimitiveBounds lhsBounds;
			GetBuildPrimitiveBounds(m_buildPrimitiveOrder[lhsIndex], &lhsBounds);

			for (rhsIndex = lhsIndex + 1; rhsIndex < planePrimitiveCount; rhsIndex++) {
				BuildPrimitiveBounds rhsBounds;
				GetBuildPrimitiveBounds(m_buildPrimitiveOrder[rhsIndex], &rhsBounds);

				lhs = m_buildPrimitiveOrder[lhsIndex];
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

	LegoS32 accumulatedReferenceCount = 0;
	m_batchVertexCount = 0;
	LegoS32 vertexCount = 2;
	LegoS32 materialRunEnd = 0;
	LegoS32 materialIndex = -1;

	for (LegoS32 primitiveIndex = 0; primitiveIndex < m_buildPrimitiveCount - 1; primitiveIndex++) {
		LegoS32 batchVertexCount = m_batchVertexCount;
		LegoS32 bestAddedVertexCount = 0x42;
		LegoS32 bestPrimitiveIndex = 0;
		LegoS32 i;

		if (batchVertexCount != 0 && materialIndex == m_buildPrimitiveOrder[primitiveIndex]->m_materialIndex) {
			BuildPrimitive** primitiveOrder = m_buildPrimitiveOrder;
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
				vertexCount = primitive->m_vertexCount;
				LegoS32 addedVertexCount = vertexCount;

				for (i = 0; i < vertexCount; i++) {
					if (g_carBuildModelVertexUses[primitive->m_vertexIndices[i]].m_inBatch) {
						addedVertexCount--;
					}
				}

				if (addedVertexCount == 0) {
					bestPrimitiveIndex = candidate;
					bestAddedVertexCount = addedVertexCount;
					candidate = m_buildPrimitiveCount;
				}
				else if (addedVertexCount < bestAddedVertexCount) {
					bestAddedVertexCount = addedVertexCount;
					bestPrimitiveIndex = candidate;
				}
			}
		}
		else if (materialIndex != m_buildPrimitiveOrder[primitiveIndex]->m_materialIndex) {
			for (i = 0; i < m_batchVertexCount; i++) {
				g_carBuildModelVertexUses[m_batchBuildVertexIndices[i]].m_inBatch = FALSE;
			}

			materialIndex = m_buildPrimitiveOrder[primitiveIndex]->m_materialIndex;

			LegoS32 runEnd;
			for (runEnd = primitiveIndex; runEnd < m_buildPrimitiveCount; runEnd++) {
				if (materialIndex != m_buildPrimitiveOrder[runEnd]->m_materialIndex) {
					break;
				}

				vertexCount = m_buildPrimitiveOrder[runEnd]->m_vertexCount;
				for (i = 0; i < vertexCount; i++) {
					g_carBuildModelVertexUses[m_buildPrimitiveOrder[runEnd]->m_vertexIndices[i]].m_referenceCount++;
				}
			}

			materialRunEnd = runEnd;
		}

		if (static_cast<LegoU32>(m_batchVertexCount + bestAddedVertexCount) > c_modelBatchVertexCapacity) {
			bestPrimitiveIndex = 0;
			LegoS32 bestReferenceCount = 0x7fffffff;

			for (LegoS32 candidate = primitiveIndex; candidate < materialRunEnd; candidate++) {
				for (i = 0; i < vertexCount; i++) {
					accumulatedReferenceCount +=
						g_carBuildModelVertexUses[m_buildPrimitiveOrder[candidate]->m_vertexIndices[i]]
							.m_referenceCount;
				}

				if (bestReferenceCount > accumulatedReferenceCount) {
					bestReferenceCount = accumulatedReferenceCount;
					bestPrimitiveIndex = candidate;
				}
			}

			for (i = 0; i < m_batchVertexCount; i++) {
				g_carBuildModelVertexUses[m_batchBuildVertexIndices[i]].m_inBatch = FALSE;
			}
			m_batchVertexCount = 0;
		}

		if (bestPrimitiveIndex) {
			BuildPrimitive* primitive = m_buildPrimitiveOrder[primitiveIndex];
			m_buildPrimitiveOrder[primitiveIndex] = m_buildPrimitiveOrder[bestPrimitiveIndex];
			m_buildPrimitiveOrder[bestPrimitiveIndex] = primitive;
		}

		for (i = 0; i < m_buildPrimitiveOrder[primitiveIndex]->m_vertexCount; i++) {
			LegoS32 vertexIndex = m_buildPrimitiveOrder[primitiveIndex]->m_vertexIndices[i];
			g_carBuildModelVertexUses[vertexIndex].m_referenceCount--;
			if (!g_carBuildModelVertexUses[vertexIndex].m_inBatch) {
				g_carBuildModelVertexUses[vertexIndex].m_inBatch = TRUE;
				m_batchBuildVertexIndices[m_batchVertexCount] = vertexIndex;
				m_batchVertexCount++;
			}
		}
	}

	return m_buildPrimitiveCount - 1;
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
				BuildPrimitive* primitive = m_buildPrimitiveOrder[i--];
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
