#ifndef ACTIVERECORDBUFFER_H
#define ACTIVERECORDBUFFER_H

#include "save/saverecordlist.h"

class GolString;

// SIZE 0x250
class ActiveRecordBuffer : public SaveRecordList::Record {
public:
	static void CopyBufferToString(GolString* p_string, const LegoU8* p_source, LegoU32 p_count);
	static void CopyStringToBuffer(GolString* p_string, LegoU8* p_dest, LegoU32 p_count);

	void SetCarData(const LegoU8* p_source);
	void Reset() { m_selectedRecordCount = 0; }
	undefined4 GetSelectedRecordCount() const { return m_selectedRecordCount; }
	undefined2 GetSelectedRecordCountAsU16() const { return static_cast<undefined2>(m_selectedRecordCount); }
	SaveRecordList::Record* GetSelectedRecord() const { return m_selectedRecords[0]; }
	SaveRecordList::Record* GetSelectedRecord(LegoU32 p_index) const { return m_selectedRecords[p_index]; }
	void SetSelectedRecordCount(undefined4 p_count) { m_selectedRecordCount = p_count; }
	void SetSelectedRecord(SaveRecordList::Record* p_record) { m_selectedRecords[0] = p_record; }
	void SetSelectedRecord(LegoU32 p_index, SaveRecordList::Record* p_record) { m_selectedRecords[p_index] = p_record; }

private:
	LegoU32 m_selectedRecordCount;                // 0x244
	SaveRecordList::Record* m_selectedRecords[2]; // 0x248
};

#endif // ACTIVERECORDBUFFER_H
