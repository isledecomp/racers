#include "menu/screens/racerunlockstate.h"

#include "save/savesystem.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerUnlockState, 0x28)

// FUNCTION: LEGORACERS 0x00442e20
RacerUnlockState::RacerUnlockState()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00442e30
void RacerUnlockState::Reset()
{
	m_unk0x00 = NULL;

	::memset(m_unk0x04, 0, sizeof(m_unk0x04));
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
}

// FUNCTION: LEGORACERS 0x00442e60 FOLDED
void RacerUnlockState::FUN_00442e60(SaveSystem* p_saveSystem)
{
	m_unk0x00 = p_saveSystem;
}

// FUNCTION: LEGORACERS 0x00442e70
void RacerUnlockState::FUN_00442e70()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00442e80
LegoU32 RacerUnlockState::FUN_00442e80(LegoU32 p_mask) const
{
	LegoU32 count = 0;
	const RacerUnlockState* state = this;

	if (p_mask & 0x01) {
		SaveSystem* saveSystem = state->m_unk0x00;
		count = saveSystem->GetDefaultSave().GetRecordCount();
	}
	if (p_mask & 0x02) {
		SaveSystem* saveSystem = state->m_unk0x00;
		count += saveSystem->GetSessionSave().GetRecordCount();
	}
	if (p_mask & 0x04) {
		SaveSystem* saveSystem = state->m_unk0x00;
		count += saveSystem->GetQuickBuildSave().GetRecordCount();
	}

	SaveSystem* saveSystem = state->m_unk0x00;
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
SaveRecordList::Record* RacerUnlockState::FUN_00442ef0(LegoU32 p_mask)
{
	m_unk0x24 = p_mask;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;

	if (p_mask & 0x01) {
		m_unk0x04[m_unk0x20++] = &m_unk0x00->GetDefaultSave();
	}
	if (p_mask & 0x02) {
		m_unk0x04[m_unk0x20++] = &m_unk0x00->GetSessionSave();
	}
	if (p_mask & 0x04) {
		m_unk0x04[m_unk0x20++] = &m_unk0x00->GetQuickBuildSave();
	}

	for (LegoU32 i = 0; i < m_unk0x00->GetMemoryCardSaveCount(); i++) {
		if (p_mask & (0x10 << i)) {
			m_unk0x04[m_unk0x20++] = &m_unk0x00->GetMemoryCardSaves()[i];
		}
	}

	if (m_unk0x20 != 0) {
		while (m_unk0x04[m_unk0x18]->GetRecordCount() == 0) {
			m_unk0x18++;
			if (m_unk0x18 >= m_unk0x20) {
				m_unk0x18 = 0;
				return NULL;
			}
		}

		return m_unk0x04[m_unk0x18]->GetRecord(0);
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00442fe0
SaveRecordList::Record* RacerUnlockState::FUN_00442fe0()
{
	LegoU32 count = m_unk0x20;
	if (count == 0) {
		return NULL;
	}

	LegoU32 startIndex = m_unk0x18;
	m_unk0x1c++;

	if (m_unk0x1c >= m_unk0x04[m_unk0x18]->GetRecordCount()) {
		m_unk0x1c = 0;

		for (;;) {
			m_unk0x18++;
			if (m_unk0x18 >= count) {
				m_unk0x18 = 0;
			}

			if (m_unk0x04[m_unk0x18]->GetRecordCount()) {
				break;
			}

			if (m_unk0x18 == startIndex) {
				return NULL;
			}
		}
	}

	return m_unk0x04[m_unk0x18]->GetRecord(m_unk0x1c);
}

// FUNCTION: LEGORACERS 0x00443050
SaveRecordList::Record* RacerUnlockState::FUN_00443050()
{
	LegoU32 count = m_unk0x20;
	if (count == 0) {
		return NULL;
	}

	LegoU32 startIndex = m_unk0x18;
	if (m_unk0x1c == 0) {
		do {
			if (m_unk0x18 == 0) {
				m_unk0x18 = count;
			}

			m_unk0x18--;
			m_unk0x1c = m_unk0x04[m_unk0x18]->GetRecordCount();
			if (m_unk0x1c != 0) {
				break;
			}
		} while (m_unk0x18 != startIndex);

		if (m_unk0x1c == 0) {
			return NULL;
		}
	}

	m_unk0x1c--;
	return m_unk0x04[m_unk0x18]->GetRecord(m_unk0x1c);
}

// FUNCTION: LEGORACERS 0x004430b0
SaveRecordList::Record* RacerUnlockState::FUN_004430b0()
{
	if (m_unk0x20 == 0) {
		return NULL;
	}

	SaveRecordList* records = m_unk0x04[m_unk0x18];
	if (m_unk0x1c >= records->GetRecordCount()) {
		return NULL;
	}

	return records->GetRecord(m_unk0x1c);
}

// FUNCTION: LEGORACERS 0x004430e0
SaveRecordList::Record* RacerUnlockState::FUN_004430e0(SaveRecordList::Record* p_record)
{
	if (m_unk0x20 != 0) {
		SaveRecordList::Record* firstRecord = FUN_004430b0();
		SaveRecordList::Record* targetRecord = p_record;
		SaveRecordList::Record* record;

		do {
			record = FUN_00442fe0();
		} while (firstRecord != record && record != targetRecord);

		if (record == targetRecord) {
			return record;
		}
	}

	return NULL;
}
