#ifndef SAVERECORDCURSOR_H
#define SAVERECORDCURSOR_H

#include "compat.h"
#include "decomp.h"
#include "save/saverecordlist.h"
#include "types.h"

class SaveSystem;

// SIZE 0x28
class SaveRecordCursor {
public:
	SaveRecordCursor();

	void SetSaveSystem(SaveSystem* p_saveSystem);
	void Reset();
	void Close();
	LegoU32 CountRecords(LegoU32 p_mask) const;
	SaveRecordList::Record* Begin(LegoU32 p_mask);
	SaveRecordList::Record* SelectNext();
	SaveRecordList::Record* SelectPrevious();
	SaveRecordList::Record* GetSelectedRecord();
	SaveRecordList::Record* SeekTo(SaveRecordList::Record* p_record);
	undefined4 GetSourceMask() const { return m_sourceMask; }

private:
	SaveSystem* m_saveSystem;     // 0x00
	SaveRecordList* m_sources[5]; // 0x04
	LegoU32 m_sourceIndex;        // 0x18
	LegoU32 m_recordIndex;        // 0x1c
	LegoU32 m_sourceCount;        // 0x20
	undefined4 m_sourceMask;      // 0x24
};

#endif // SAVERECORDCURSOR_H
