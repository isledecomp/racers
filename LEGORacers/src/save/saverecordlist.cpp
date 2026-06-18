#include "golerror.h"
#include "golstring.h"
#include "racer/drivercosmetics.h"
#include "save/savegame.h"

DECOMP_SIZE_ASSERT(SaveRecordList, 0x24)
DECOMP_SIZE_ASSERT(SaveRecordList::Record, 0x244)
DECOMP_SIZE_ASSERT(SaveRecordList::SerializedRecord, 0x241)
DECOMP_SIZE_ASSERT(ActiveRecordBuffer, 0x250)

// FUNCTION: LEGORACERS 0x0042b290
SaveRecordList::Record::Record()
{
	m_next = NULL;
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042b2b0
SaveRecordList::Record::~Record()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0042b2c0
void SaveRecordList::Record::Initialize()
{
	m_owner = NULL;
	::memset(m_data, 0, sizeof(m_data));
	m_recordSource = 0;
	m_saveIndex = 0;
	m_recordId = 0;
}

// FUNCTION: LEGORACERS 0x0042b2f0
void SaveRecordList::Record::FUN_0042b2f0(
	LegoU32 p_recordSource,
	LegoU32 p_saveIndex,
	LegoU32 p_recordId,
	SaveRecordList* p_owner
)
{
	if (m_recordSource) {
		Destroy();
	}

	m_owner = p_owner;
	m_recordSource = p_recordSource;
	m_saveIndex = p_saveIndex;
	m_recordId = p_recordId;
}

// FUNCTION: LEGORACERS 0x0042b320
void SaveRecordList::Record::Destroy()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042b330
void SaveRecordList::Record::GetCosmetics(DriverCosmetics* p_cosmetics) const
{
	p_cosmetics->m_faceIndex = m_data[0x1c];
	p_cosmetics->m_hatIndex = m_data[0x1d];
	p_cosmetics->m_legIndex = m_data[0x1e];
	p_cosmetics->m_torsoIndex = m_data[0x1f];
	p_cosmetics->m_expressionIndex = m_data[0x20] & 0x7f;
}

// FUNCTION: LEGORACERS 0x0042b360
void SaveRecordList::Record::CopyCarData(LegoU8* p_dest) const
{
	::memcpy(p_dest, &m_data[0x29], 0x202);
}

// FUNCTION: LEGORACERS 0x0042b380
void SaveRecordList::Record::GetChassisName(GolName p_dest) const
{
	::memcpy(p_dest, &m_data[0x21], 8);
}

// FUNCTION: LEGORACERS 0x0042b3a0
void SaveRecordList::Record::GetName(GolString* p_string) const
{
	ActiveRecordBuffer::CopyBufferToString(p_string, m_data, 0x0e);
}

// FUNCTION: LEGORACERS 0x0042b400
void ActiveRecordBuffer::CopyBufferToString(GolString* p_string, const LegoU8* p_source, LegoU32 p_count)
{
	LegoU32 i = 0;
	while (i < p_count) {
		undefined2 c = static_cast<undefined2>((p_source[1] << 8) + p_source[0]);
		if (!c) {
			break;
		}

		*p_string->FromCursor(i) = c;
		p_source += 2;
		i++;
	}

	*p_string->FromCursor(i) = 0;
	p_string->SetCursorEnd(static_cast<undefined2>(i));
	p_string->SetCursorStart(0);
}

// FUNCTION: LEGORACERS 0x0042b460
LegoBool32 SaveRecordList::Record::IsCarSaved() const
{
	return m_data[0x20] & 0x80;
}

// FUNCTION: LEGORACERS 0x0042b470
void SaveRecordList::Record::MarkCarSaved()
{
	MarkDirty();
	m_data[0x20] |= 0x80;
}

// FUNCTION: LEGORACERS 0x0042b490
void SaveRecordList::Record::MarkCarModified()
{
	MarkDirty();
	m_data[0x20] &= 0x7f;
}

// FUNCTION: LEGORACERS 0x0042b4b0
void SaveRecordList::Record::SetCosmetics(const DriverCosmetics* p_cosmetics)
{
	m_data[0x1c] = p_cosmetics->m_faceIndex;
	m_data[0x1d] = p_cosmetics->m_hatIndex;
	m_data[0x1e] = p_cosmetics->m_legIndex;
	m_data[0x1f] = p_cosmetics->m_torsoIndex;
	m_data[0x20] = (m_data[0x20] & 0x80) | p_cosmetics->m_expressionIndex;
	MarkDirty();
}

// FUNCTION: LEGORACERS 0x0042b4f0
void ActiveRecordBuffer::SetCarData(const LegoU8* p_source)
{
	memcpy(&m_data[0x29], p_source, 0x202);
	MarkDirty();
}

// FUNCTION: LEGORACERS 0x0042b510
void SaveRecordList::Record::SetChassisName(const GolName p_source)
{
	::memcpy(&m_data[0x21], p_source, 8);
	MarkDirty();
}

// FUNCTION: LEGORACERS 0x0042b530
void SaveRecordList::Record::SetName(GolString* p_string)
{
	ActiveRecordBuffer::CopyStringToBuffer(p_string, m_data, 0x0e);
	MarkDirty();
}

// FUNCTION: LEGORACERS 0x0042b560
void ActiveRecordBuffer::CopyStringToBuffer(GolString* p_string, LegoU8* p_dest, LegoU32 p_count)
{
	LegoU32 length = p_string->SelectionLength();
	if (length > p_count) {
		length = p_count;
	}

	LegoU32 i = 0;
	LegoU8* dest = p_dest;
	for (; i < length; i++) {
		undefined2 c = *p_string->FromCursor(i);

		dest[0] = static_cast<LegoU8>(c);
		dest[1] = static_cast<LegoU8>(c >> 8);
		dest += 2;
	}

	for (; i < p_count; i++) {
		*dest++ = 0;
		*dest++ = 0;
	}
}

// FUNCTION: LEGORACERS 0x0042b5c0
void SaveRecordList::Record::CopyFrom(const Record* p_source)
{
	if (m_recordSource == 0) {
		FUN_0042b2f0(p_source->m_recordSource, p_source->m_saveIndex, 0, NULL);
	}

	::memcpy(m_data, p_source->m_data, sizeof(m_data));
	MarkDirty();
}

// FUNCTION: LEGORACERS 0x0042b600
void SaveRecordList::Record::SetRecordId(LegoU32 p_recordId)
{
	m_recordId = p_recordId;
	MarkDirty();
}

// FUNCTION: LEGORACERS 0x0042b610
LegoU32 SaveRecordList::Record::GetTrophy(undefined4 p_raceIndex) const
{
	LegoU16 value = m_data[0x22c];
	LegoU16 low = m_data[0x22b];
	value <<= 8;
	value += low;

	LegoU8 shift = static_cast<LegoU8>(p_raceIndex);
	shift <<= 1;
	return (value >> shift) & 3;
}

// FUNCTION: LEGORACERS 0x0042b640
LegoBool32 SaveRecordList::Record::SetTrophy(LegoU32 p_raceIndex, LegoU32 p_trophy)
{
	Record* record = this;

	if (p_trophy > 3) {
		return FALSE;
	}

	LegoU16 value = record->m_data[0x22c];
	LegoU16 low = record->m_data[0x22b];
	value <<= 8;
	value += low;

	LegoU16 existing = value;
	LegoU16 shift = static_cast<LegoU16>(p_raceIndex);
	shift <<= 1;
	existing >>= shift;
	existing &= 3;
	if (existing && static_cast<LegoU16>(p_trophy) >= existing) {
		return FALSE;
	}

	LegoU32 bitShift = p_raceIndex << 1;
	LegoU32 mask = 3;
	mask <<= bitShift;
	p_trophy <<= bitShift;
	value &= ~mask;
	value |= static_cast<LegoU16>(p_trophy);
	record->m_data[0x22b] = static_cast<LegoU8>(value);
	record->m_data[0x22c] = static_cast<LegoU8>(value >> 8);
	record->MarkDirty();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0042b6d0
void SaveRecordList::Record::MarkDirty()
{
	if (m_owner) {
		m_owner->m_dirty = 1;
	}
}

// FUNCTION: LEGORACERS 0x0042b6e0
SaveRecordList::SaveRecordList()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042b6f0 FOLDED
SaveRecordList::~SaveRecordList()
{
	FreeRecords();
}

// FUNCTION: LEGORACERS 0x0042b6f0 FOLDED
void SaveRecordList::Destroy()
{
	FreeRecords();
}

// FUNCTION: LEGORACERS 0x0042b700
void SaveRecordList::Initialize()
{
	m_dirty = 0;
	m_recordCount = 0;
	m_recordCapacity = 0;
	m_records = 0;
	m_freeRecords = 0;
	m_usedRecords = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0042b720
void SaveRecordList::AllocateRecords(LegoU32 p_count, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	if (m_records) {
		FreeRecords();
	}

	m_dirty = 0;
	m_recordCapacity = p_count;
	m_records = new Record[p_count];
	if (!m_records) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x08 = p_unk0x08;
	m_unk0x0c = p_unk0x0c;
	RebuildFreeList();
}

// FUNCTION: LEGORACERS 0x0042b7f0
void SaveRecordList::FreeRecords()
{
	if (m_records) {
		delete[] m_records;
		m_records = NULL;
	}

	Initialize();
}

// FUNCTION: LEGORACERS 0x0042b830
void SaveRecordList::RebuildFreeList()
{
	m_freeRecords = m_records;

	LegoU32 i = 0;
	if (m_recordCapacity - 1 != 0) {
		Record* record = m_records;
		LegoU32 nextRecordIndex = 1;
		do {
			Record* nextRecord = &m_records[nextRecordIndex];
			i++;
			record->m_next = nextRecord;
			nextRecordIndex++;
			record++;
		} while (i < m_recordCapacity - 1);
	}

	m_usedRecords = NULL;
}

// FUNCTION: LEGORACERS 0x0042b880
SaveRecordList::Record* SaveRecordList::AllocateRecord()
{
	Record* record = m_freeRecords;
	if (!record) {
		return NULL;
	}

	m_recordCount++;
	m_dirty = 1;
	m_freeRecords = record->m_next;
	record->FUN_0042b2f0(m_unk0x08, m_unk0x0c, m_recordCount, this);
	record->m_next = NULL;

	if (m_usedRecords) {
		Record* tail = m_usedRecords;
		while (tail->m_next) {
			tail = tail->m_next;
		}

		tail->m_next = record;
	}
	else {
		m_usedRecords = record;
	}

	return record;
}

// FUNCTION: LEGORACERS 0x0042b8f0
SaveRecordList::Record* SaveRecordList::AllocateRecordCopy(Record* p_record)
{
	Record* copy = AllocateRecord();
	m_dirty = 1;
	copy->CopyFrom(p_record);
	return copy;
}

// FUNCTION: LEGORACERS 0x0042b920
void SaveRecordList::RemoveRecord(Record* p_record)
{
	Record* previous = NULL;
	Record* record = m_usedRecords;
	Record* head = record;
	LegoU32 recordId = 0;
	m_dirty = 1;

	while (record != NULL && record != p_record) {
		previous = record;
		record = record->m_next;
	}

	m_recordCount--;

	if (previous != NULL) {
		previous->m_next = record->m_next;
	}
	else {
		m_usedRecords = head->m_next;
	}

	record->m_next = m_freeRecords;
	m_freeRecords = record;
	p_record->Destroy();

	for (record = m_usedRecords; record != NULL; record = record->m_next) {
		record->SetRecordId(recordId++);
	}
}

// FUNCTION: LEGORACERS 0x0042b990
SaveRecordList::Record* SaveRecordList::GetRecord(LegoU32 p_index)
{
	Record* record = m_usedRecords;

	while (p_index-- != 0) {
		record = record->m_next;
	}

	return record;
}

// FUNCTION: LEGORACERS 0x0042b9b0
SaveRecordList::Record* SaveRecordList::FindRecordById(undefined4 p_recordId)
{
	Record* record = m_usedRecords;

	while (record != NULL) {
		if (record->m_recordId == p_recordId) {
			return record;
		}

		record = record->m_next;
	}

	return NULL;
}
