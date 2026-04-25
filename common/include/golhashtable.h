#ifndef GOLHASHTABLE_H
#define GOLHASHTABLE_H

#include "decomp.h"
#include "types.h"

#include <windows.h>

// VTABLE: LEGORACERS 0x004b0f28
// SIZE 0x24
class GolHashTable {
public:
	struct Entry {
		LegoChar* m_data; // 0x00
		Entry* m_next;    // 0x04
	};

	GolHashTable();
	~GolHashTable();

	virtual void ClearEntries();                                      // vtable+0x00
	virtual Entry* AddEntry(Entry**, const LegoChar*);                // vtable+0x04
	virtual LegoS32 Init(LegoS32 p_numBuckets, LegoU32 p_bufferSize); // vtable+0x08
	virtual LegoS32 Shutdown();                                       // vtable+0x0c

	void Reset();
	LegoU32 HashString(const LegoChar* p_string);
	Entry* FindEntry(const LegoChar* p_string);
	Entry* AddString(const LegoChar* p_string);

	void SetCurrentEntry(Entry* p_currentEntry) { m_currentEntry = p_currentEntry; }
	void SetCurrentEntryFromString(const LegoChar* p_string) { m_currentEntry = AddString(p_string); }

private:
	HANDLE m_mutex;           // 0x04
	Entry** m_buckets;        // 0x08
	LegoChar* m_buffer;       // 0x0c
	LegoChar* m_bufferCursor; // 0x10
	LegoS32 m_numBuckets;     // 0x14
	LegoU32 m_bufferSize;     // 0x18
	Entry* m_currentEntry;    // 0x1c
	undefined m_initialized;  // 0x20
};

#endif // GOLHASHTABLE_H
