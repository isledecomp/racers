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

DECOMP_SIZE_ASSERT(CarBuildModel::PieceGrid, 0x14)
DECOMP_SIZE_ASSERT(CarBuildModel::PieceGrid::Cell, 0x0c)

static const LegoS32 g_highPieceTypeBase = 0x800;

// FUNCTION: LEGORACERS 0x00415f40 FOLDED
void CarBuildModel::PieceGrid::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
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
				if (p_index != m_entries[y + j + ((x + i) * m_height)].m_entryIndex) {
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
