#include "model/carbuildmodel.h"

DECOMP_SIZE_ASSERT(CarBuildModel::PieceList, 0x18)
DECOMP_SIZE_ASSERT(CarBuildModel::PieceList::Entry0x1c, 0x1c)

// FUNCTION: LEGORACERS 0x0049f6b0
void CarBuildModel::PieceList::Entry0x1c::GetPlacement(
	LegoS32* p_x,
	LegoS32* p_y,
	LegoS32* p_height,
	LegoS32* p_rotation
)
{
	*p_x = m_x;
	*p_y = m_y;
	*p_height = m_height;
	*p_rotation = m_rotation;
}

// FUNCTION: LEGORACERS 0x0049f6e0
void CarBuildModel::PieceList::Entry0x1c::SetPlacement(LegoS32 p_x, LegoS32 p_y, LegoS32 p_height, LegoS32 p_rotation)
{
	m_x = p_x;
	m_y = p_y;
	m_height = p_height;
	m_rotation = p_rotation & 3;
}

// FUNCTION: LEGORACERS 0x0049f710
LegoS32 CarBuildModel::PieceList::AddEntry(
	LegoPieceLibrary::PieceRecord* p_pieceRecord,
	LegoS32 p_x,
	LegoS32 p_y,
	LegoS32 p_rotation,
	LegoS32 p_colorRecordIndex,
	LegoS32 p_partType,
	LegoS32 p_height
)
{
	m_entries[m_entryCount].m_pieceRecord = p_pieceRecord;
	m_entries[m_entryCount].m_colorRecordIndex = p_colorRecordIndex;
	m_entries[m_entryCount].m_partType = p_partType;
	m_entries[m_entryCount].SetPlacement(p_x, p_y, p_height, p_rotation);
	m_entryCount++;

	return m_entryCount - 1;
}

// FUNCTION: LEGORACERS 0x0049f7a0
LegoBool32 CarBuildModel::PieceList::RemoveEntry(LegoS32 p_index)
{
	if (p_index < m_entryCount && p_index >= 0) {
		Entry0x1c saved = m_entries[p_index];
		LegoS32 i;

		m_entryCount--;
		for (i = p_index; i < m_entryCount; i++) {
			m_entries[i] = m_entries[i + 1];
		}

		if (FUN_0049f930()) {
			return TRUE;
		}

		for (i = m_entryCount++; i > p_index; i--) {
			m_entries[i] = m_entries[i - 1];
		}

		m_entries[p_index] = saved;
		FUN_0049f930();
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0049f880
CarBuildModel::PieceList::PieceList()
{
	m_pieceGrid = NULL;
	m_entries = NULL;
	m_entryCount = 0;
	m_capacity = 0;
	m_variant = 0;
}

// FUNCTION: LEGORACERS 0x0049f8a0
CarBuildModel::PieceList::~PieceList()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0049f8b0
void CarBuildModel::PieceList::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
	m_entryCount = 0;
	m_capacity = 0;
	m_variant = 0;
}

// FUNCTION: LEGORACERS 0x0049f8e0
LegoBool32 CarBuildModel::PieceList::Initialize(LegoS32 p_capacity)
{
	Clear();
	m_entries = new Entry0x1c[p_capacity];
	if (m_entries != NULL) {
		m_capacity = p_capacity;
		return TRUE;
	}

	m_capacity = 0;
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0049f930
LegoBool32 CarBuildModel::PieceList::FUN_0049f930()
{
	LegoBool32 result = TRUE;
	m_pieceGrid->ResetEntries();

	for (LegoS32 i = 0; i < m_entryCount; i++) {
		LegoPieceLibrary::PieceRecord* pieceRecord = m_entries[i].m_pieceRecord;
		LegoS32 x;
		LegoS32 y;
		LegoS32 entryHeight;
		LegoS32 rotation;
		m_entries[i].GetPlacement(&x, &y, &entryHeight, &rotation);

		LegoS32 height = m_pieceGrid->FUN_0049e2d0(pieceRecord, x, y, rotation, FALSE);
		if (height == -1 && (height = m_pieceGrid->FUN_0049e2d0(pieceRecord, x, y, rotation, TRUE)) == -1) {
			result = FALSE;
		}
		else {
			if (entryHeight == -1) {
				m_entries[i].SetPlacement(x, y, height, rotation);
			}
			else if (height != entryHeight) {
				result = FALSE;
			}

			if (!m_pieceGrid->FUN_0049e450(pieceRecord, x, y, rotation, height)) {
				m_pieceGrid->FUN_0049df40(pieceRecord, x, y, rotation, height, i);
			}
			else {
				result = FALSE;
			}
		}
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0049fa70
void CarBuildModel::PieceList::SetVariant(LegoS32 p_variant, LegoBool32 p_force)
{
	if (p_force || m_variant != p_variant) {
		for (LegoS32 i = 0; i < m_entryCount; i++) {
			m_entries[i].m_pieceRecord = m_entries[i].m_pieceRecord->GetVariant(p_variant);
		}
	}

	m_variant = p_variant;
}

// FUNCTION: LEGORACERS 0x0049fac0
LegoS32 CarBuildModel::PieceList::ReadU16()
{
	LegoU8 high = *m_cursor++;
	LegoU8 low = *m_cursor++;

	return (high << 8) + low;
}

// FUNCTION: LEGORACERS 0x0049fb00
void CarBuildModel::PieceList::WriteU16(LegoS32 p_value)
{
	*m_cursor = static_cast<LegoU8>(p_value >> 8);
	m_cursor++;
	*m_cursor = static_cast<LegoU8>(p_value);
	m_cursor++;
}

// FUNCTION: LEGORACERS 0x0049fb30
LegoBool32 CarBuildModel::PieceList::Deserialize(
	LegoU8* p_source,
	LegoPieceLibrary* p_pieceLibrary,
	LegoS32 p_maxHeight
)
{
	Clear();
	m_cursor = p_source;

	LegoS32 count = ReadU16();
	if (count > 64 || (!Initialize(64) && (Clear(), TRUE))) {
		return FALSE;
	}
	else {
		m_entryCount = 0;
		FUN_0049f930();

		for (; count > 0; count--) {
			LegoS32 pieceType = ReadU16();
			LegoU8 xByte = *m_cursor++;
			LegoS32 x = xByte;
			LegoU8 yByte = *m_cursor++;
			LegoS32 y = yByte;
			LegoU8 rotationByte = *m_cursor++;
			LegoS32 rotation = rotationByte;
			LegoU8 colorByte = *m_cursor++;
			LegoS32 colorRecordIndex = colorByte;
			LegoS32 partType = ReadU16();

			LegoPieceLibrary::PieceRecord* pieceRecord = p_pieceLibrary->FindPieceRecord(pieceType, 1);
			if (pieceRecord != NULL) {
				LegoS32 height = m_pieceGrid->FUN_0049e2d0(pieceRecord, x, y, rotation, FALSE);
				if (height >= 0 && height + pieceRecord->GetMaxCellValue() > p_maxHeight) {
					continue;
				}

				if (!m_pieceGrid->AddPiece(pieceRecord, x, y, rotation, colorRecordIndex, partType, FALSE)) {
					m_pieceGrid->AddPiece(pieceRecord, x, y, rotation, colorRecordIndex, partType, TRUE);
				}
			}
		}

		return TRUE;
	}
}

// FUNCTION: LEGORACERS 0x0049fca0
void CarBuildModel::PieceList::Serialize(LegoU8* p_dest)
{
	m_cursor = p_dest;
	WriteU16(m_entryCount);

	for (LegoS32 i = 0; i < m_entryCount; i++) {
		WriteU16(m_entries[i].m_pieceRecord->m_pieceType);

		LegoS32 x;
		LegoS32 y;
		LegoS32 height;
		LegoS32 rotation;
		m_entries[i].GetPlacement(&x, &y, &height, &rotation);

		*m_cursor = static_cast<LegoU8>(x);
		m_cursor++;
		*m_cursor = static_cast<LegoU8>(y);
		m_cursor++;
		*m_cursor = static_cast<LegoU8>(rotation);
		m_cursor++;
		LegoS32 colorRecordIndex = m_entries[i].m_colorRecordIndex;
		*m_cursor = static_cast<LegoU8>(colorRecordIndex);
		m_cursor++;
		WriteU16(m_entries[i].m_partType);
	}
}

// FUNCTION: LEGORACERS 0x0049fd60
void CarBuildModel::PieceList::FUN_0049fd60()
{
	m_entryCount = 0;
	FUN_0049f930();
}
