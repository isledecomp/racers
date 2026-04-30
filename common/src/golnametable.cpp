#include "golnametable.h"

#include "golerror.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolNameTable, 0x0c)
DECOMP_SIZE_ASSERT(GolNameTable::Entry, 0x0c)

// FUNCTION: GOLDP 0x100281c0
// FUNCTION: LEGORACERS 0x004117b0
GolNameTable::GolNameTable()
{
	m_nameEntries = NULL;
	m_capacity = 0;
}

// FUNCTION: GOLDP 0x10028220
// FUNCTION: LEGORACERS 0x004117f0
GolNameTable::~GolNameTable()
{
	Clear();
}

// FUNCTION: GOLDP 0x10028250 FOLDED
// FUNCTION: LEGORACERS 0x00411800
void GolNameTable::Allocate(LegoU32 p_capacity)
{
	m_capacity = p_capacity;
	m_nameEntries = new Entry[p_capacity];

	if (m_nameEntries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_nameEntries, 0, sizeof(Entry) * m_capacity);
}

// FUNCTION: GOLDP 0x100282a0
// FUNCTION: LEGORACERS 0x00411850
void GolNameTable::Clear()
{
	if (m_nameEntries != NULL) {
		delete[] m_nameEntries;
		m_nameEntries = NULL;
	}
}

// FUNCTION: GOLDP 0x100282c0
// FUNCTION: LEGORACERS 0x00411870
void GolNameTable::AddName(const LegoChar* p_name, void* p_value)
{
	LegoU32 startIndex = 0;
	LegoU32 shift = 0;
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_nameEntries[0].m_name); i++) {
		LegoChar c = p_name[i];
		if (c == '\0') {
			break;
		}

		startIndex += c << shift;
		shift += 7;
		shift &= 0x1f;
	}

	startIndex %= m_capacity;
	for (i = startIndex; m_nameEntries[i].m_value != NULL;) {
		if (::strncmp(m_nameEntries[i].m_name, p_name, sizeOfArray(m_nameEntries[i].m_name)) == 0) {
			char buffer[40];
			::strncpy(buffer, p_name, sizeOfArray(m_nameEntries[i].m_name));
			buffer[sizeOfArray(m_nameEntries[i].m_name)] = '\0';
			::strcat(buffer, ": Duplicate name encountered");
			GOL_FATALERROR_MESSAGE(buffer);
		}

		i += 1;
		if (i >= m_capacity) {
			i = 0;
		}

		if (i == startIndex) {
			GOL_FATALERROR_MESSAGE("AddName caused hash table overflow");
		}
	}

	::strncpy(m_nameEntries[i].m_name, p_name, sizeOfArray(m_nameEntries[i].m_name));
	m_nameEntries[i].m_value = p_value;
}

// FUNCTION: GOLDP 0x100283e0
// FUNCTION: LEGORACERS 0x004119a0
void* GolNameTable::GetName(const LegoChar* p_name) const
{
	LegoU32 startIndex = 0;
	LegoU32 shift = 0;
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_nameEntries[0].m_name); i++) {
		LegoChar c = p_name[i];
		if (c == '\0') {
			break;
		}

		startIndex += c << shift;
		shift += 7;
		shift &= 0x1f;
	}

	startIndex %= m_capacity;

	for (i = startIndex; m_nameEntries[i].m_value != NULL;) {
		if (::strncmp(m_nameEntries[i].m_name, p_name, sizeOfArray(m_nameEntries[i].m_name)) == 0) {
			return m_nameEntries[i].m_value;
		}

		i += 1;
		if (i >= m_capacity) {
			i = 0;
		}

		if (i == startIndex) {
			return NULL;
		}
	}

	return NULL;
}

// FUNCTION: GOLDP 0x10028470
LegoChar* GolNameTable::GetNameByValue(const void* p_value, LegoChar* p_buffer) const
{
	for (LegoU32 i = 0; i < m_capacity; i++) {
		if (m_nameEntries[i].m_value == p_value) {
			return ::strncpy(p_buffer, m_nameEntries[i].m_name, sizeOfArray(m_nameEntries[i].m_name));
		}
	}

	p_buffer[0] = '\0';
	return p_buffer;
}
