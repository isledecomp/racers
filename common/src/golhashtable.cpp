#include "golhashtable.h"

#include "decomp.h"
#include "golerror.h"

#include <string.h>
#include <windows.h>

DECOMP_SIZE_ASSERT(GolHashTable, 0x24)

// FUNCTION: LEGORACERS 0x0044c570
GolHashTable::GolHashTable()
{
	m_mutex = 0;
	Reset();
}

// FUNCTION: LEGORACERS 0x0044c590
GolHashTable::~GolHashTable()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0044c5a0
void GolHashTable::Reset()
{
	m_initialized = 0;
	m_buckets = 0;
	m_buffer = 0;
	m_bufferCursor = 0;
	m_numBuckets = 0;
	m_currentEntry = NULL;
}

// FUNCTION: LEGORACERS 0x0044c5c0
LegoS32 GolHashTable::Initialize(LegoS32 p_numBuckets, LegoU32 p_bufferSize)
{
	if (m_initialized) {
		Shutdown();
	}

	m_numBuckets = p_numBuckets;
	m_bufferSize = p_bufferSize;
	m_buckets = new Entry*[p_numBuckets];
	m_buffer = new LegoChar[p_bufferSize];
	m_mutex = CreateMutex(NULL, FALSE, NULL);

	if (!m_buckets || !m_buffer) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	memset(m_buckets, 0, 4 * p_numBuckets);
	memset(m_buffer, 0, p_bufferSize);
	m_bufferCursor = m_buffer;
	m_initialized = 1;
	return 1;
}

// FUNCTION: LEGORACERS 0x0044c670
LegoS32 GolHashTable::Shutdown()
{
	if (m_initialized) {
		WaitForSingleObject(m_mutex, INFINITE);

		if (m_buckets) {
			ClearEntries();
			delete[] m_buckets;
		}

		if (m_buffer) {
			delete[] m_buffer;
		}

		Reset();
		ReleaseMutex(m_mutex);
		CloseHandle(m_mutex);
		m_mutex = NULL;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044c6e0
void GolHashTable::ClearEntries()
{
	WaitForSingleObject(m_mutex, INFINITE);

	for (LegoS32 i = 0; i < m_numBuckets; i++) {
		Entry* entry = m_buckets[i];

		if (entry) {
			do {
				Entry* next = entry->m_next;
				delete entry;
				entry = next;
			} while (entry);

			m_buckets[i] = NULL;
		}
	}

	ReleaseMutex(m_mutex);
}

// FUNCTION: LEGORACERS 0x0044c740
LegoU32 GolHashTable::HashString(const LegoChar* p_string)
{
	LegoU32 hash = 0;

	while (*p_string) {
		hash = (hash << 4) + *p_string++;

		LegoU32 highBits = hash & 0xf0000000;
		if (highBits) {
			hash ^= highBits >> 24;
		}
		hash &= ~highBits;
	}

	return hash % m_numBuckets;
}

// FUNCTION: LEGORACERS 0x0044c780
GolHashTable::Entry* GolHashTable::FindEntry(const LegoChar* p_string)
{
	if (!m_initialized || !p_string || !p_string[0]) {
		return NULL;
	}

	WaitForSingleObject(m_mutex, INFINITE);

	Entry* entry = m_buckets[HashString(p_string)];
	while (entry) {
		if (!strcmp(p_string, entry->m_data)) {
			break;
		}

		entry = entry->m_next;
	}

	ReleaseMutex(m_mutex);
	return entry;
}

// FUNCTION: GOLDP 0x10031340
// FUNCTION: LEGORACERS 0x0044c810
GolHashTable::Entry* GolHashTable::AddString(const LegoChar* p_string)
{
	if (!m_initialized || !p_string || !p_string[0]) {
		return NULL;
	}

	WaitForSingleObject(m_mutex, INFINITE);

	Entry* entry = FindEntry(p_string);
	if (!entry) {
		LegoU32 bucket = HashString(p_string);
		entry = AddEntry(&m_buckets[bucket], p_string);
	}

	ReleaseMutex(m_mutex);
	return entry;
}

// FUNCTION: LEGORACERS 0x0044c880
GolHashTable::Entry* GolHashTable::AddEntry(Entry** p_bucket, const LegoChar* p_string)
{
	Entry* entry = new Entry;

	if (!entry) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	entry->m_data = m_bufferCursor;

	if (*p_bucket) {
		entry->m_next = *p_bucket;
	}
	else {
		entry->m_next = NULL;
	}

	*p_bucket = entry;
	strcpy(m_bufferCursor, p_string);
	m_bufferCursor += strlen(p_string) + 1;
	return entry;
}

// FUNCTION: GOLDP 0x10031480
// FUNCTION: LEGORACERS 0x0044c900
const LegoChar* STDMETHODCALLTYPE GolHashTable::GetEntryPath(Entry* p_entry)
{
	if (p_entry) {
		return p_entry->m_data;
	}

	return "\\";
}
