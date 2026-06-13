#include "model/carbuildmodel.h"

#include "core/gol.h"
#include "golanimatedentity.h"
#include "material/duskwindbananarelic0x24.h"
#include "material/golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "mesh/gdbmodelindexarray0xc.h"
#include "mesh/gdbvertexarray0xc.h"
#include "mesh/golmodelbase.h"
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
DECOMP_SIZE_ASSERT(CarBuildModel::VertexUse, 0x04)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

static const LegoS32 g_highPieceTypeBase = 0x800;

// GLOBAL: LEGORACERS 0x004ceba4
static CarBuildModel::BuildVertex* g_carBuildModelSortVertices;

// GLOBAL: LEGORACERS 0x004ceba8
static CarBuildModel* g_carBuildModelCellCallback;

// GLOBAL: LEGORACERS 0x004b4930
static const LegoFloat g_carBuildModelMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b4934
static const LegoFloat g_carBuildModelNormalScale = 1.0f / 127.0f;

// FUNCTION: LEGORACERS 0x00495020
LegoS32 CarBuildModel::FUN_00495020()
{
	m_buildVertexTreeRoot = NULL;
	m_unk0x1ec0 = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x00495030
LegoS32 CarBuildModel::AddBuildVertex(BuildVertex* p_vertex)
{
	BuildVertex* vertex = &m_unk0x1e30[m_unk0x1ec0];
	*vertex = *p_vertex;
	m_unk0x1e30[m_unk0x1ec0].m_index = static_cast<LegoU16>(m_unk0x1ec0);

	BuildVertex* existing = InsertOrFindBuildVertex(&m_buildVertexTreeRoot, &m_unk0x1e30[m_unk0x1ec0]);
	if (existing != NULL) {
		return existing->m_index;
	}

	m_unk0x1ec0++;

	return m_unk0x1ec0 - 1;
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
	STUB(0x00495160);

	if (p_lhs->m_position.m_x != p_rhs->m_position.m_x) {
		return p_lhs->m_position.m_x > p_rhs->m_position.m_x ? 1 : -1;
	}
	if (p_lhs->m_position.m_y != p_rhs->m_position.m_y) {
		return p_lhs->m_position.m_y > p_rhs->m_position.m_y ? 1 : -1;
	}
	if (p_lhs->m_position.m_z != p_rhs->m_position.m_z) {
		return p_lhs->m_position.m_z > p_rhs->m_position.m_z ? 1 : -1;
	}
	if (p_lhs->m_normalX != p_rhs->m_normalX) {
		return p_lhs->m_normalX - p_rhs->m_normalX;
	}
	if (p_lhs->m_normalY != p_rhs->m_normalY) {
		return p_lhs->m_normalY - p_rhs->m_normalY;
	}
	if (p_lhs->m_normalZ != p_rhs->m_normalZ) {
		return p_lhs->m_normalZ - p_rhs->m_normalZ;
	}
	if (p_lhs->m_textureCoordinate.m_x != p_rhs->m_textureCoordinate.m_x) {
		return p_lhs->m_textureCoordinate.m_x > p_rhs->m_textureCoordinate.m_x ? 1 : -1;
	}
	if (p_lhs->m_textureCoordinate.m_y != p_rhs->m_textureCoordinate.m_y) {
		return p_lhs->m_textureCoordinate.m_y > p_rhs->m_textureCoordinate.m_y ? 1 : -1;
	}

	return 0;
}

// STUB: LEGORACERS 0x004951c0
void __fastcall CarBuildModel::RebalanceBuildVertexInsert(BuildVertex** p_root, BuildVertex* p_vertex)
{
	STUB(0x004951c0);

	p_vertex->m_treeBlack = FALSE;

	while (p_vertex->m_parent != NULL && !p_vertex->m_parent->m_treeBlack) {
		BuildVertex* parent = p_vertex->m_parent;
		BuildVertex* grandparent = parent->m_parent;

		if (parent == grandparent->m_left) {
			BuildVertex* uncle = grandparent->m_right;
			if (uncle != NULL && !uncle->m_treeBlack) {
				uncle->m_treeBlack = TRUE;
				parent->m_treeBlack = TRUE;
				grandparent->m_treeBlack = FALSE;
				p_vertex = grandparent;
			}
			else {
				if (p_vertex == parent->m_right) {
					p_vertex = parent;
					RotateBuildVertexLeft(p_root, p_vertex);
				}

				p_vertex->m_parent->m_treeBlack = TRUE;
				p_vertex->m_parent->m_parent->m_treeBlack = FALSE;
				RotateBuildVertexRight(p_root, p_vertex->m_parent->m_parent);
			}
		}
		else {
			BuildVertex* uncle = grandparent->m_left;
			if (uncle != NULL && !uncle->m_treeBlack) {
				uncle->m_treeBlack = TRUE;
				parent->m_treeBlack = TRUE;
				grandparent->m_treeBlack = FALSE;
				p_vertex = grandparent;
			}
			else {
				if (p_vertex == parent->m_left) {
					p_vertex = parent;
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
	if (parent != NULL) {
		pivot->m_parent = parent;
		if (p_vertex == parent->m_left) {
			parent->m_left = pivot;
		}
		else {
			parent->m_right = pivot;
		}
	}
	else {
		pivot->m_parent = parent;
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
	if (parent != NULL) {
		pivot->m_parent = parent;
		if (p_vertex == parent->m_left) {
			parent->m_left = pivot;
		}
		else {
			parent->m_right = pivot;
		}
	}
	else {
		pivot->m_parent = parent;
		*p_root = pivot;
	}

	pivot->m_right = p_vertex;
	p_vertex->m_parent = pivot;
}

// STUB: LEGORACERS 0x00495310
LegoS32 CarBuildModel::ComparePrimitiveDrawOrder(const void* p_lhs, const void* p_rhs)
{
	STUB(0x00495310);

	const BuildPrimitive* lhs = *static_cast<BuildPrimitive* const*>(p_lhs);
	const BuildPrimitive* rhs = *static_cast<BuildPrimitive* const*>(p_rhs);

	LegoS32 result = lhs->m_materialIndex - rhs->m_materialIndex;
	if (result == 0) {
		LegoFloat zDiff = g_carBuildModelSortVertices[lhs->m_vertexIndices[0]].m_position.m_z -
						  g_carBuildModelSortVertices[rhs->m_vertexIndices[0]].m_position.m_z;
		if (zDiff < 0.0f) {
			result = -1;
		}
		else if (zDiff > 0.0f) {
			result = 1;
		}
	}

	return result;
}

// STUB: LEGORACERS 0x00495440
void CarBuildModel::FUN_00495440()
{
	STUB(0x00495440);
}

// STUB: LEGORACERS 0x00497360
void CarBuildModel::FUN_00497360(LegoU8)
{
	STUB(0x00497360);
}

// STUB: LEGORACERS 0x00497690
void CarBuildModel::FUN_00497690(LegoU8 p_buildFlags)
{
	STUB(0x00497690);

	LegoS32 i;

	for (i = m_unk0x1ebc; i < c_buildPrimitiveCapacity; i++) {
		m_unk0x1e38[i] = &m_unk0x1e34[i];
	}

	g_carBuildModelSortVertices = m_unk0x1e30;

	if (p_buildFlags & c_finalizeResolveIntersectionsFlag) {
		FUN_00495440();
		if (m_unk0xdc & c_buildStatusOverflow) {
			return;
		}
	}

	if (p_buildFlags & c_finalizeCullSingleMaterialFlag) {
		for (i = 0; i < m_unk0x1ebc; i++) {
			BuildPrimitive* primitive = m_unk0x1e38[i];
			if (primitive->m_unk0x06 == 1) {
				m_unk0x1ebc--;
				m_unk0x1e38[i] = m_unk0x1e38[m_unk0x1ebc];
				m_unk0x1e38[m_unk0x1ebc] = primitive;
				i--;
			}
		}
	}

	for (i = 0; i < m_unk0x1ebc; i++) {
		BuildPrimitive* primitive = m_unk0x1e38[i];
		if (primitive->m_vertexCount == 4) {
			primitive->m_vertexCount = 3;

			BuildPrimitive* splitPrimitive = m_unk0x1e38[m_unk0x1ebc];
			*splitPrimitive = *primitive;
			splitPrimitive->m_vertexIndices[0] = primitive->m_vertexIndices[2];
			splitPrimitive->m_vertexIndices[2] = primitive->m_vertexIndices[3];
			m_unk0x1ebc++;

			if (m_unk0x1ebc >= c_buildPrimitiveCapacity) {
				m_unk0xdc |= c_buildStatusOverflow;
				return;
			}
		}
	}

	::qsort(m_unk0x1e38, m_unk0x1ebc, sizeof(BuildPrimitive*), ComparePrimitiveDrawOrder);

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
	LegoS32 p_unk0x0c
)
{
	m_width = p_pieceRecord->GetWidth();
	m_height = p_pieceRecord->GetHeight();
	m_colorRecordIndex = p_unk0x08;
	m_unk0x14 = p_unk0x0c;

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
	SetPiece(m_pieceRecord, m_colorRecordIndex, m_unk0x14);
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
	m_unk0x1e30 = NULL;
	m_unk0x1e34 = NULL;
	m_unk0x1e38 = NULL;
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
	m_unk0x1e30 = new BuildVertex[c_buildVertexCapacity];
	m_unk0x1e34 = new BuildPrimitive[c_buildPrimitiveCapacity];
	m_unk0x1e38 = new BuildPrimitive*[c_buildPrimitiveCapacity];

	for (LegoS32 i = 0; i < c_buildVertexCapacity; i++) {
		m_unk0x1e30[i].m_index = static_cast<LegoU16>(i);
	}
}

// FUNCTION: LEGORACERS 0x00499f80
void CarBuildModel::FreeBuffers()
{
	delete[] m_unk0x1e30;
	delete[] m_unk0x1e34;
	delete[] m_unk0x1e38;
	m_unk0x1e30 = NULL;
	m_unk0x1e34 = NULL;
	m_unk0x1e38 = NULL;
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

// STUB: LEGORACERS 0x0049a300
void CarBuildModel::FUN_0049a300(GolModelBase* p_model)
{
	STUB(0x0049a300);

	LegoU32 groupIndex = m_modelGroupCount;
	m_modelGroupCount++;

	LegoU32* groups = p_model->GetMutableGroups();
	groups[groupIndex] = ((m_batchVertexCount + 0xffff) << 16) & 0x003f0000;
	groups[groupIndex] |= m_batchFirstVertex & 0xffff;
	p_model->SetDirty(TRUE);

	groupIndex = m_modelGroupCount;
	m_modelGroupCount++;
	groups[groupIndex] = 0x20000000;
	groups[groupIndex] |= (m_batchTriangleCount & 0x7f) << 16;
	groups[groupIndex] |= m_batchFirstTriangle & 0xffff;
	p_model->SetDirty(TRUE);

	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;
	m_batchFirstVertex = m_modelVertexCount;
	m_batchFirstTriangle = m_modelTriangleCount;
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
	LegoS32 p_partIndex
)
{
	STUB(0x0049a450);

	if (m_unk0x1ebc >= c_buildPrimitiveCapacity || p_pieceRecord->m_baseOffset == 0) {
		if (m_unk0x1ebc >= c_buildPrimitiveCapacity) {
			m_unk0xdc |= c_buildStatusOverflow;
		}
		return 0;
	}

	LegoPieceLibrary* library = p_pieceRecord->m_library;
	const LegoU16* cursor = library->GetIndexCursor(p_pieceRecord->m_unk0x18);
	LegoS32 remaining = p_pieceRecord->m_baseOffset;
	LegoS32 rotation = p_rotation & 3;
	LegoFloat xOrigin = static_cast<LegoFloat>(p_x);
	LegoFloat yOrigin = static_cast<LegoFloat>(p_y);
	LegoFloat zOrigin = static_cast<LegoFloat>(p_height);
	LegoFloat width = static_cast<LegoFloat>(p_pieceRecord->GetWidth());
	LegoFloat height = static_cast<LegoFloat>(p_pieceRecord->GetHeight());
	LegoS32 colorMaterialIndex =
		m_verdantTide != NULL ? m_verdantTide->GetMaterialIndexForColorRecord(p_colorRecordIndex) : p_colorRecordIndex;
	BuildPrimitive* primitive = NULL;
	LegoBool32 hasNormalIndex = FALSE;
	LegoBool32 hasTextureIndex = FALSE;
	LegoBool32 hasSharedNormalIndex = FALSE;
	LegoS32 normalIndex = -1;
	LegoS16 result = 0;

	while (remaining-- != 0 && !(m_unk0xdc & c_buildStatusOverflow)) {
		LegoU16 command = *cursor++;
		LegoS32 mode = command & c_indexCommandModeMask;
		LegoS32 vertexCount = 3;

		if (mode == c_indexCommandMode0x2000) {
			if (primitive == NULL) {
				continue;
			}

			primitive->m_vertexCount = 4;
			vertexCount = 1;
		}
		else {
			if (m_unk0x1ebc >= c_buildPrimitiveCapacity) {
				m_unk0xdc |= c_buildStatusOverflow;
				break;
			}

			primitive = &m_unk0x1e34[m_unk0x1ebc];
			m_unk0x1e38[m_unk0x1ebc] = primitive;
			m_unk0x1ebc++;

			hasTextureIndex = mode == c_indexCommandMode0x1000;
			hasNormalIndex = (command >> 14) & 1;
			hasSharedNormalIndex = (command >> 15) & 1;

			LegoU16 materialIndex = command & 0x07ff;
			primitive->m_vertexCount = 3;
			primitive->m_flags = 0x0f;
			primitive->m_unk0x04 = static_cast<undefined2>(p_partIndex);
			primitive->m_unk0x06 = command & 0x0fff;

			if (materialIndex < 3) {
				if (!m_unk0xd9 && m_unk0xdb && materialIndex == 2) {
					primitive->m_materialIndex = static_cast<LegoU16>(colorMaterialIndex + 1);
				}
				else {
					primitive->m_materialIndex = static_cast<LegoU16>(colorMaterialIndex);
				}
			}
			else if (!m_unk0xd9 && m_unk0xdb && (command & 0x0800)) {
				primitive->m_materialIndex = materialIndex + 1;
			}
			else {
				primitive->m_materialIndex = materialIndex;
			}
		}

		for (LegoS32 i = 0; i < vertexCount; i++) {
			LegoS32 coordinateIndex = *cursor++;
			if (!library->IsColorBlack(coordinateIndex)) {
				primitive->m_flags &= ~1;
			}

			LegoFloat sourceX;
			LegoFloat sourceY;
			LegoFloat sourceZ;
			library->GetColor(coordinateIndex, &sourceX, &sourceY, &sourceZ);

			BuildVertex vertex;
			::memset(&vertex, 0, sizeof(vertex));

			switch (rotation) {
			case 1:
				vertex.m_position.m_x = sourceY + xOrigin;
				vertex.m_position.m_y = (width - sourceX) + yOrigin;
				break;
			case 2:
				vertex.m_position.m_x = (width - sourceX) + xOrigin;
				vertex.m_position.m_y = (height - sourceY) + yOrigin;
				break;
			case 3:
				vertex.m_position.m_x = (height - sourceY) + xOrigin;
				vertex.m_position.m_y = sourceX + yOrigin;
				break;
			default:
				vertex.m_position.m_x = sourceX + xOrigin;
				vertex.m_position.m_y = sourceY + yOrigin;
				break;
			}
			vertex.m_position.m_z = sourceZ + zOrigin;

			if (!hasSharedNormalIndex && (hasNormalIndex || i == 0)) {
				normalIndex = *cursor++;
			}

			if (normalIndex >= 0) {
				const LegoU8* normal = library->GetColorTriple(normalIndex);
				LegoS8 normalX = static_cast<LegoS8>(normal[0]);
				LegoS8 normalY = static_cast<LegoS8>(normal[1]);
				vertex.m_normalZ = static_cast<LegoS8>(normal[2]);

				switch (rotation) {
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
				default:
					vertex.m_normalX = normalX;
					vertex.m_normalY = normalY;
					break;
				}
			}

			if (hasTextureIndex) {
				LegoS32 textureIndex = *cursor++;
				library->GetTextureCoordinate(
					textureIndex,
					&vertex.m_textureCoordinate.m_x,
					&vertex.m_textureCoordinate.m_y
				);
			}
			else if (!m_unk0xd9 && m_unk0xdb && (primitive->m_unk0x06 == 2 || (primitive->m_unk0x06 & 0x0800))) {
				vertex.m_textureCoordinate.m_x = (vertex.m_position.m_x - xOrigin) * 0.5f;
				vertex.m_textureCoordinate.m_y = (vertex.m_position.m_y - yOrigin) * 0.5f;
			}

			LegoS32 vertexIndex = mode == c_indexCommandMode0x2000 ? 3 : i;
			primitive->m_vertexIndices[vertexIndex] = AddBuildVertex(&vertex);
			result = primitive->m_vertexIndices[vertexIndex];
		}
	}

	return result;
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

// STUB: LEGORACERS 0x0049ad30
LegoS16 CarBuildModel::FUN_0049ad30(
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_height,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_unk0x14
)
{
	STUB(0x0049ad30);

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

// STUB: LEGORACERS 0x0049ade0
void CarBuildModel::EmitPrimitiveToModel(GolModelEntity* p_entity, BuildPrimitive* p_primitive)
{
	STUB(0x0049ade0);

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
	LegoS32 i;

	for (i = 0; i < p_primitive->m_vertexCount; i++) {
		batchIndices[i] = GetBatchVertexIndex(p_primitive->m_vertexIndices[i]);
		if (batchIndices[i] == -1) {
			newVertexCount++;
		}
	}

	if (m_modelVertexCount + newVertexCount > c_buildVertexCapacity) {
		m_unk0xdc |= c_buildStatusOverflow;
		return;
	}

	if (m_batchVertexCount + newVertexCount > c_modelBatchVertexCapacity) {
		FUN_0049a300(model);
		for (i = 0; i < sizeOfArray(batchIndices); i++) {
			batchIndices[i] = -1;
		}
	}

	if (m_currentMaterialIndex != p_primitive->m_materialIndex) {
		if (m_batchTriangleCount) {
			FUN_0049a300(model);
		}

		LegoU32 groupIndex = m_modelGroupCount++;
		m_currentMaterialIndex = p_primitive->m_materialIndex;
		model->GetMutableGroups()[groupIndex] = c_modelMaterialGroup | (m_currentMaterialIndex & 0x00ffffff);
		model->SetDirty(TRUE);

		for (i = 0; i < sizeOfArray(batchIndices); i++) {
			batchIndices[i] = -1;
		}
	}

	for (i = 0; i < p_primitive->m_vertexCount; i++) {
		if (batchIndices[i] == -1) {
			LegoU16 buildVertexIndex = p_primitive->m_vertexIndices[i];
			LegoU32 batchVertexIndex = m_batchVertexCount;
			BuildVertex* buildVertex = &m_unk0x1e30[buildVertexIndex];

			m_batchBuildVertexIndices[batchVertexIndex] = buildVertexIndex;
			m_batchVertexSlotByBuildVertex[buildVertexIndex] = static_cast<LegoU8>(batchVertexIndex);
			batchIndices[i] = batchVertexIndex;
			m_batchVertexCount++;

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

	GdbModelIndexArray0xc::Indices* indices = &m_modelTriangles[m_modelTriangleCount++];
	indices->m_a = static_cast<LegoU8>(batchIndices[0]);
	indices->m_b = static_cast<LegoU8>(batchIndices[1]);
	indices->m_c = static_cast<LegoU8>(batchIndices[2]);
	indices->m_x = 0;

	if (p_primitive->m_vertexCount == 4) {
		indices++;
		m_modelTriangleCount++;
		m_batchTriangleCount += 2;
		indices->m_a = static_cast<LegoU8>(batchIndices[2]);
		indices->m_b = static_cast<LegoU8>(batchIndices[1]);
		indices->m_c = static_cast<LegoU8>(batchIndices[3]);
		indices->m_x = 0;
	}
	else {
		m_batchTriangleCount++;
	}
}

// FUNCTION: LEGORACERS 0x0049b100
void CarBuildModel::FUN_0049b100(GolModelEntity* p_entity)
{
	for (LegoS32 i = 0; i < m_unk0x1ebc; i++) {
		EmitPrimitiveToModel(p_entity, m_unk0x1e38[i]);
		if (m_unk0xdc & 1) {
			return;
		}
	}
}

// STUB: LEGORACERS 0x0049b150
LegoS32 CarBuildModel::ComparePrimitiveMaterial(const void* p_lhs, const void* p_rhs)
{
	STUB(0x0049b150);

	const BuildPrimitive* rhs = *static_cast<BuildPrimitive* const*>(p_rhs);
	const BuildPrimitive* lhs = *static_cast<BuildPrimitive* const*>(p_lhs);
	LegoS32 result = lhs->m_materialIndex;
	result -= rhs->m_materialIndex;

	return result;
}

// STUB: LEGORACERS 0x0049b170
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
	STUB(0x0049b170);

	GolModelBase* model = p_entity->GetModel(0);
	LegoPieceLibrary::PieceRecord* pieceRecord = p_pieceRecord->GetVariant(1);
	m_unk0xdb = m_unk0xda;
	m_unk0xd9 = m_hasHighBasePiece;
	m_unk0xde = 0xef;
	m_unk0xdc = 0;

	if (m_verdantTide != NULL) {
		p_entity->SetPrimaryMaterialTable(m_verdantTide->GetMaterialTable());
	}

	FUN_00495020();
	m_unk0x1ebc = 0;
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
				if (static_cast<LegoS8>(cellFlags) < 0) {
					FUN_0049ad30(p_x + x, p_y + y, p_height + (cellFlags & 0x3f), p_colorRecordIndex, 0);
				}
			}
		}
	}

	FUN_00497690(0xef);

	for (LegoS32 i = 0; i < m_unk0x1ec0; i++) {
		m_unk0x1e30[i].m_position.m_x += m_unk0x1f04;
		m_unk0x1e30[i].m_position.m_y += m_unk0x1f08;
		m_unk0x1e30[i].m_position.m_z = (m_unk0x1e30[i].m_position.m_z * 0.4f) + m_unk0x1f0c;
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
	const LegoU16* indexCursor = library->GetIndexCursor(p_pieceRecord->m_unk0x18);
	LegoS32 indexCount = p_pieceRecord->m_baseOffset;
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
		LegoU16 command = *indexCursor++;
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

// STUB: LEGORACERS 0x0049b740
void CarBuildModel::FUN_0049b740(undefined4 p_unk0x04)
{
	STUB(0x0049b740);

	if (p_unk0x04 != NULL) {
		FUN_0049b6f0(m_unk0x1f10, m_unk0x1f14, m_unk0x1f18);
		return;
	}

	if (m_placedPieceCount) {
		LegoPieceLibrary::PieceRecord* pieceRecord;
		LegoS32 x;
		LegoS32 y;
		LegoS32 height;
		LegoS32 rotation;
		LegoS32 colorRecordIndex;
		LegoS32 partType;
		FUN_0049bce0(0, &pieceRecord, &x, &y, &height, &rotation, &colorRecordIndex, &partType);

		LegoS32 anchorColor = pieceRecord->FUN_0049f690();
		if (anchorColor != 0xffff) {
			pieceRecord->m_library->GetColor(anchorColor, &m_unk0x1f04, &m_unk0x1f08, &m_unk0x1f0c);
			m_unk0x1f0c *= -0.4f;
			m_unk0x1f04 = -m_unk0x1f04;
			m_unk0x1f08 = -m_unk0x1f08;
		}
		else {
			FUN_0049b340(pieceRecord, rotation);
			m_unk0x1f04 = -((m_unk0x1f20 + m_unk0x1f1c) * 0.5f) - static_cast<LegoFloat>(x);
			m_unk0x1f08 = -((m_unk0x1f28 + m_unk0x1f24) * 0.5f) - static_cast<LegoFloat>(y);
			m_unk0x1f0c = -m_unk0x1f2c - (static_cast<LegoFloat>(height) * 0.4f);
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
	STUB(0x0049b920);

	LegoS32 activePieceCount = m_placedPieceCount;
	m_unk0xde = static_cast<LegoU16>(p_buildFlags);
	m_pieceList.SetVariant(p_variant, TRUE);
	m_unk0xdc = 0;
	m_unk0x1ebc = 0;

	LegoU8 startFlags;
	do {
		FUN_00495020();
		m_unk0xdc <<= 1;
		m_unk0x1ebc = 0;
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

		for (LegoS32 i = 0; i < activePieceCount; i++) {
			PieceList::Entry0x1c* entry = &m_pieceList.m_entries[i];
			LegoS32 x;
			LegoS32 y;
			LegoS32 height;
			LegoS32 rotation;
			entry->GetPlacement(&x, &y, &height, &rotation);
			FUN_0049a450(entry->m_pieceRecord, x, y, rotation, height, entry->m_colorRecordIndex, entry->m_partType);
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
					::qsort(m_unk0x1e38, m_unk0x1ebc, sizeof(BuildPrimitive*), ComparePrimitiveMaterial);
				}
			}

			if (!(m_unk0xdc & 1)) {
				for (LegoS32 i = 0; i < m_unk0x1ec0; i++) {
					m_unk0x1e30[i].m_position.m_x += m_unk0x1f04;
					m_unk0x1e30[i].m_position.m_y += m_unk0x1f08;
					m_unk0x1e30[i].m_position.m_z = (m_unk0x1e30[i].m_position.m_z * 0.4f) + m_unk0x1f0c;
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

	if (m_verdantTide != NULL && m_unk0x1ebc != 0) {
		m_verdantTide->ResetMaterialUsage();
		m_currentMaterialIndex = m_unk0x1e38[0]->m_materialIndex;
		m_verdantTide->MarkMaterialUsed(m_currentMaterialIndex);

		for (LegoS32 i = 1; i < m_unk0x1ebc; i++) {
			LegoU32 materialIndex = m_unk0x1e38[i]->m_materialIndex;
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
	if (m_unk0x1fc8[p_x + 1][p_y + 1] & 0x10) {
		m_unk0x1fc8[p_x + 1][p_y + 1] |= 0x20;
	}
}

// STUB: LEGORACERS 0x0049be70
void CarBuildModel::FUN_0049be70(LegoBool p_unk0x04, LegoS32 p_height)
{
	STUB(0x0049be70);

	LegoBool useUpperTexCoord = p_unk0x04 & 1;
	if (p_height < 0) {
		p_height = m_unk0x2028;
	}

	FUN_0049a290(m_auxModel);

	LegoU32 groupIndex = m_unk0x1ef0;
	m_unk0x202c = 0;
	m_unk0x1ef0++;
	m_auxModel->GetMutableGroups()[groupIndex] = 0x80000001;
	m_auxModel->SetDirty(TRUE);

	LegoFloat z = (static_cast<LegoFloat>(p_height) * 0.4f) + m_unk0x1f0c;
	GolVec3 normal;
	normal.m_x = 0.0f;
	normal.m_y = 0.0f;
	normal.m_z = 1.0f;

	for (LegoS32 x = 0; x < 12; x++) {
		for (LegoS32 y = 0; y < 8; y++) {
			if ((m_unk0x1fc8[x][y] & 0x10) && (m_unk0x1fc8[x][y] & 0x20)) {
				if (m_batchVertexCount + 4 > 0x40) {
					m_unk0x202c += m_batchTriangleCount;
					FUN_0049a300(m_auxModel);
				}

				GolVec3 position;
				position.m_x = static_cast<LegoFloat>(x - 1) + m_unk0x1f04;
				position.m_y = static_cast<LegoFloat>(y - 1) + m_unk0x1f08;
				position.m_z = z;

				GolVec2 texCoord;
				texCoord.m_x = 0.5f;
				texCoord.m_y = useUpperTexCoord ? 0.5f : 0.0f;

				LegoU32 vertexIndex = m_unk0x1ef8;
				m_modelVertices->VTable0x24(vertexIndex, position);
				m_modelVertices->VTable0x28(vertexIndex, texCoord);
				m_modelVertices->VTable0x2c(vertexIndex, normal);

				vertexIndex++;
				position.m_x += 1.0f;
				texCoord.m_x += 0.49f;
				m_modelVertices->VTable0x24(vertexIndex, position);
				m_modelVertices->VTable0x28(vertexIndex, texCoord);
				m_modelVertices->VTable0x2c(vertexIndex, normal);

				vertexIndex++;
				position.m_y += 1.0f;
				texCoord.m_y += 0.49f;
				m_modelVertices->VTable0x24(vertexIndex, position);
				m_modelVertices->VTable0x28(vertexIndex, texCoord);
				m_modelVertices->VTable0x2c(vertexIndex, normal);

				vertexIndex++;
				position.m_x -= 1.0f;
				texCoord.m_x -= 0.49f;
				m_modelVertices->VTable0x24(vertexIndex, position);
				m_modelVertices->VTable0x28(vertexIndex, texCoord);
				m_modelVertices->VTable0x2c(vertexIndex, normal);

				m_modelTriangles[m_unk0x1ef4].m_a = static_cast<LegoU8>(m_batchVertexCount);
				m_modelTriangles[m_unk0x1ef4].m_b = static_cast<LegoU8>(m_batchVertexCount + 1);
				m_modelTriangles[m_unk0x1ef4].m_c = static_cast<LegoU8>(m_batchVertexCount + 3);
				m_modelTriangles[m_unk0x1ef4].m_x = 0;
				m_modelTriangles[m_unk0x1ef4 + 1].m_a = static_cast<LegoU8>(m_batchVertexCount + 3);
				m_modelTriangles[m_unk0x1ef4 + 1].m_b = static_cast<LegoU8>(m_batchVertexCount + 1);
				m_modelTriangles[m_unk0x1ef4 + 1].m_c = static_cast<LegoU8>(m_batchVertexCount + 2);
				m_modelTriangles[m_unk0x1ef4 + 1].m_x = 0;

				m_batchVertexCount += 4;
				m_unk0x1ef8 += 4;
				m_unk0x1ef4 += 2;
				m_batchTriangleCount += 2;
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
	STUB(0x0049c230);

	GolModelBase* model = p_entity->GetModel(0);
	::memset(m_unk0x1fc8, 0, sizeof(m_unk0x1fc8));
	FUN_0049b740(TRUE);

	LegoPieceLibrary::PieceRecord* pieceRecord = p_placement->GetPieceRecord();
	if (pieceRecord != NULL) {
		LegoS32 x;
		LegoS32 y;
		LegoS32 rotation;
		p_placement->GetPlacement(&x, &y, &rotation);

		FUN_0049b170(p_entity, pieceRecord, x, y, 21, rotation, p_placement->GetColorRecordIndex(), 239);

		if (pieceRecord->m_pieceType == 0x7ff) {
			LegoS32 entryIndex = FUN_0049bcc0(x, y);
			if (entryIndex >= 0) {
				LegoS32 height;
				LegoS32 colorRecordIndex;
				LegoS32 partType;
				FUN_0049bce0(entryIndex, &pieceRecord, &x, &y, &height, &rotation, &colorRecordIndex, &partType);
				if (pieceRecord->m_pieceType < g_highPieceTypeBase) {
					entryIndex = -1;
				}
			}

			m_unk0x2028 = 18;
			if (entryIndex < 0) {
				p_placement->GetPlacement(&x, &y, &rotation);
				m_unk0x1fc8[x + 1][y + 1] |= 0x30;
				FUN_0049be70(FALSE, -1);
				return;
			}

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
						m_unk0x1fc8[x + i + 1][y + j + 1] |= 0x10;
						if (entryIndex != FUN_0049bcc0(x + i, y + j)) {
							m_unk0x1fc8[x + i + 1][y + j + 1] |= 0x20;
						}
					}
				}
			}
		}
		else {
			m_unk0x2028 = 0;

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
						m_unk0x1fc8[x + i + 1][y + j + 1] |= 0x10;
						m_unk0x1fc8[x + i + 1][y + j + 2] |= 0x01;
						m_unk0x1fc8[x + i + 2][y + j + 1] |= 0x02;
						m_unk0x1fc8[x + i + 1][y + j] |= 0x04;
						m_unk0x1fc8[x + i][y + j + 1] |= 0x08;

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
		FUN_0049a290(m_auxModel);
		FUN_0049a3e0(m_auxModel);
	}
}

// STUB: LEGORACERS 0x0049c6a0
LegoS32 CarBuildModel::FUN_0049c6a0(LegoFloat* p_unk0x04, LegoFloat* p_unk0x08, LegoFloat* p_unk0x0c)
{
	STUB(0x0049c6a0);

	LegoS32 zTotal = 0;
	LegoS32 yTotal = 0;
	LegoS32 xTotal = 0;
	LegoS32 result = 0;

	LegoS32 remaining = m_pieceList.m_entryCount;
	if (remaining > 0) {
		PieceList::Entry0x1c* entry = m_pieceList.m_entries;
		do {
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
				xTotal += pieceX;
				yTotal += pieceY;
				zTotal += pieceZ;
				result += count;
			}

			entry++;
		} while (--remaining != 0);
	}

	if (result) {
		LegoFloat count = static_cast<LegoFloat>(result);
		*p_unk0x04 = static_cast<LegoFloat>(xTotal) / count - 4.5f;
		*p_unk0x08 = static_cast<LegoFloat>(yTotal) / count - 2.5f;
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
	STUB(0x0049c840);

	MaterialTable0x0c* materialTable = m_verdantTide->GetMaterialTable();
	const LegoU32* sourceGroups = m_model->GetGroups();
	LegoS32 materialCount = static_cast<LegoS32>(materialTable->m_count);
	LegoU16 materialOrders[256];
	LegoU8 materialUsed[256];

	::memset(materialOrders, 0, sizeof(materialOrders));
	::memset(materialUsed, 0, sizeof(materialUsed));

	LegoS32 i;
	LegoS32 usedMaterialCount = 0;
	for (i = 0; i < static_cast<LegoS32>(m_unk0x1ef0); i++) {
		LegoU32 group = sourceGroups[i];
		if ((group & 0xe0000000) == 0x80000000) {
			LegoU32 materialIndex = group & 0xffff;
			if (!materialUsed[materialIndex]) {
				materialUsed[materialIndex] = TRUE;
				materialOrders[materialIndex] = static_cast<LegoU16>(usedMaterialCount);
				usedMaterialCount++;
			}
		}
	}

	LegoS32 textureIndex = 0;
	LegoS32 outputMaterialIndex = 0;
	for (i = 0; i < materialCount; i++) {
		if (materialUsed[i]) {
			DuskwindBananaRelic0x24* sourceMaterial =
				static_cast<DuskwindBananaRelic0x24*>(materialTable->GetPosition(i));

			DuskWindBananaRelicParams params;
			sourceMaterial->CopyParamsTo(&params);
			params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flagBit0;

			DuskwindBananaRelic0x24* outputMaterial = p_materials->GetItem(outputMaterialIndex);
			if (sourceMaterial->GetUnk0x08() & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
				PurpleDune0x7c* outputTexture = p_textures->GetItem(textureIndex);
				GoldDune0x38* sourceTexture = sourceMaterial->GetUnk0x04();
				PurpleDune0x7c* sourcePurpleTexture = static_cast<PurpleDune0x7c*>(sourceTexture);

				outputTexture->SetName(sourcePurpleTexture->GetName());
				outputTexture->SetSourceTextureDefinition(
					sourceTexture->GetUnk0x34(),
					sourceTexture->GetUnk0x36(),
					sourceTexture->GetColorKey()
				);
				params.m_unk0x04 = outputTexture;
				textureIndex++;
			}

			outputMaterial->FUN_100257e0(m_renderer, params);
			p_model->GetMaterialTable()->SetPosition(outputMaterialIndex, outputMaterial);
			outputMaterialIndex++;
		}
	}

	LegoU32* destGroups = p_model->GetMutableGroups();
	for (i = 0; i < static_cast<LegoS32>(m_unk0x1ef0); i++) {
		LegoU32 group = sourceGroups[i];
		if ((group & 0xe0000000) == 0x80000000) {
			LegoU32 materialIndex = group & 0xffff;
			destGroups[i] = 0x80000000 | (materialOrders[materialIndex] & 0xffffff);
			p_model->SetDirty(TRUE);
		}
		else {
			destGroups[i] = group;
		}
	}

	IGdbModelIndexArray0x8* sourceIndexArray;
	IGdbModelIndexArray0x8* destIndexArray;
	m_model->VTable0x30(&sourceIndexArray);
	p_model->VTable0x30(&destIndexArray);
	const GdbModelIndexArray0xc::Indices* sourceIndices =
		static_cast<GdbModelIndexArray0xc*>(sourceIndexArray)->GetIndices();
	GdbModelIndexArray0xc::Indices* destIndices =
		static_cast<GdbModelIndexArray0xc*>(destIndexArray)->GetMutableIndices();
	::memcpy(destIndices, sourceIndices, sizeof(*destIndices) * m_unk0x1ef4);

	GdbVertexArray0xc* sourceVertices;
	GdbVertexArray0xc* destVertices;
	m_model->VTable0x28(&sourceVertices);
	p_model->VTable0x28(&destVertices);
	for (i = 0; i < static_cast<LegoS32>(m_unk0x1ef8); i++) {
		GolVec3 position;
		GolVec2 texCoord;
		GolVec3 normal;
		ColorRGBA color;

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
	p_model->VTable0x34(TRUE);
	p_model->VTable0x2c(TRUE, TRUE);
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
