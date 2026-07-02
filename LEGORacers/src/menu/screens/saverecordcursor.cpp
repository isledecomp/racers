#include "menu/screens/saverecordcursor.h"

#include "save/memorycardsavegame.h"
#include "save/savesystem.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SaveRecordCursor, 0x28)

// FUNCTION: LEGORACERS 0x00442e20
SaveRecordCursor::SaveRecordCursor()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00442e30
void SaveRecordCursor::Reset()
{
	m_saveSystem = NULL;

	::memset(m_sources, 0, sizeof(m_sources));
	m_sourceIndex = 0;
	m_recordIndex = 0;
	m_sourceCount = 0;
	m_sourceMask = 0;
}

// FUNCTION: LEGORACERS 0x00442e60 FOLDED
void SaveRecordCursor::SetSaveSystem(SaveSystem* p_saveSystem)
{
	m_saveSystem = p_saveSystem;
}

// FUNCTION: LEGORACERS 0x00442e70
void SaveRecordCursor::Close()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00442e80
LegoU32 SaveRecordCursor::CountRecords(LegoU32 p_mask) const
{
	LegoU32 count = 0;
	const SaveRecordCursor* state = this;

	if (p_mask & 0x01) {
		SaveSystem* saveSystem = state->m_saveSystem;
		count = saveSystem->GetDefaultSave().GetRecordCount();
	}
	if (p_mask & 0x02) {
		SaveSystem* saveSystem = state->m_saveSystem;
		count += saveSystem->GetSessionSave().GetRecordCount();
	}
	if (p_mask & 0x04) {
		SaveSystem* saveSystem = state->m_saveSystem;
		count += saveSystem->GetQuickBuildSave().GetRecordCount();
	}

	SaveSystem* saveSystem = state->m_saveSystem;
	LegoU32 i = 0;
	LegoU32 memoryCardSaveCount = saveSystem->GetMemoryCardSaveCount();
	if (memoryCardSaveCount > 0) {
		MemoryCardSaveGame* saves = saveSystem->GetMemoryCardSaves();

		do {
			if (p_mask & (0x10 << i)) {
				count += saves[i].GetRecordCount();
			}
			i++;
		} while (i < memoryCardSaveCount);
	}

	return count;
}

// FUNCTION: LEGORACERS 0x00442ef0
SaveRecordList::Record* SaveRecordCursor::Begin(LegoU32 p_mask)
{
	m_sourceMask = p_mask;
	m_sourceIndex = 0;
	m_recordIndex = 0;
	m_sourceCount = 0;

	if (p_mask & 0x01) {
		m_sources[m_sourceCount++] = &m_saveSystem->GetDefaultSave();
	}
	if (p_mask & 0x02) {
		m_sources[m_sourceCount++] = &m_saveSystem->GetSessionSave();
	}
	if (p_mask & 0x04) {
		m_sources[m_sourceCount++] = &m_saveSystem->GetQuickBuildSave();
	}

	for (LegoU32 i = 0; i < m_saveSystem->GetMemoryCardSaveCount(); i++) {
		if (p_mask & (0x10 << i)) {
			m_sources[m_sourceCount++] = &m_saveSystem->GetMemoryCardSaves()[i];
		}
	}

	if (m_sourceCount != 0) {
		while (m_sources[m_sourceIndex]->GetRecordCount() == 0) {
			m_sourceIndex++;
			if (m_sourceIndex >= m_sourceCount) {
				m_sourceIndex = 0;
				return NULL;
			}
		}

		return m_sources[m_sourceIndex]->GetRecord(0);
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00442fe0
SaveRecordList::Record* SaveRecordCursor::SelectNext()
{
	LegoU32 count = m_sourceCount;
	if (count == 0) {
		return NULL;
	}

	LegoU32 startIndex = m_sourceIndex;
	m_recordIndex++;

	if (m_recordIndex >= m_sources[m_sourceIndex]->GetRecordCount()) {
		m_recordIndex = 0;

		for (;;) {
			m_sourceIndex++;
			if (m_sourceIndex >= count) {
				m_sourceIndex = 0;
			}

			if (m_sources[m_sourceIndex]->GetRecordCount()) {
				break;
			}

			if (m_sourceIndex == startIndex) {
				return NULL;
			}
		}
	}

	return m_sources[m_sourceIndex]->GetRecord(m_recordIndex);
}

// FUNCTION: LEGORACERS 0x00443050
SaveRecordList::Record* SaveRecordCursor::SelectPrevious()
{
	LegoU32 count = m_sourceCount;
	if (count == 0) {
		return NULL;
	}

	LegoU32 startIndex = m_sourceIndex;
	if (m_recordIndex == 0) {
		do {
			if (m_sourceIndex == 0) {
				m_sourceIndex = count;
			}

			m_sourceIndex--;
			m_recordIndex = m_sources[m_sourceIndex]->GetRecordCount();
			if (m_recordIndex != 0) {
				break;
			}
		} while (m_sourceIndex != startIndex);

		if (m_recordIndex == 0) {
			return NULL;
		}
	}

	m_recordIndex--;
	return m_sources[m_sourceIndex]->GetRecord(m_recordIndex);
}

// FUNCTION: LEGORACERS 0x004430b0
SaveRecordList::Record* SaveRecordCursor::GetSelectedRecord()
{
	if (m_sourceCount == 0) {
		return NULL;
	}

	SaveRecordList* records = m_sources[m_sourceIndex];
	if (m_recordIndex >= records->GetRecordCount()) {
		return NULL;
	}

	return records->GetRecord(m_recordIndex);
}

// FUNCTION: LEGORACERS 0x004430e0
SaveRecordList::Record* SaveRecordCursor::SeekTo(SaveRecordList::Record* p_record)
{
	if (m_sourceCount != 0) {
		SaveRecordList::Record* firstRecord = GetSelectedRecord();
		SaveRecordList::Record* targetRecord = p_record;
		SaveRecordList::Record* record;

		do {
			record = SelectNext();
		} while (firstRecord != record && record != targetRecord);

		if (record == targetRecord) {
			return record;
		}
	}

	return NULL;
}
