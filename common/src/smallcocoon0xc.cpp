#include "smallcocoon0xc.h"

#include "golerror.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(SmallCocoon0xc, 0xc)
DECOMP_SIZE_ASSERT(SmallCocoon0xc::Item, 0xc)

// FUNCTION: GOLDP 0x100281c0
// FUNCTION: LEGORACERS 0x004117b0
SmallCocoon0xc::SmallCocoon0xc()
{
	m_data = NULL;
	m_size = 0;
}

// FUNCTION: GOLDP 0x10028250 FOLDED
// FUNCTION: LEGORACERS 0x00411800
void SmallCocoon0xc::VTable0x04(LegoU32 p_size)
{
	m_size = p_size;
	m_data = new Item[p_size];

	if (m_data == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_data, 0, sizeof(Item) * m_size);
}

// FUNCTION: GOLDP 0x100282c0
// FUNCTION: LEGORACERS 0x00411870
void SmallCocoon0xc::AddName(const LegoChar* p_str, UtopianPan0xa4* p_arg2)
{
	LegoU32 startIndex = 0;
	LegoU32 shift = 0;
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_data[0].m_key); i++) {
		LegoChar c = p_str[i];
		if (c == '\0') {
			break;
		}
		startIndex += c << shift;
		shift += 7;
		shift &= 0x1f;
	}

	startIndex %= m_size;
	for (i = startIndex; m_data[i].m_unk0x8 != NULL;) {
		if (::strncmp(m_data[i].m_key, p_str, sizeOfArray(m_data[i].m_key)) == 0) {
			char buffer[40];
			::strncpy(buffer, p_str, sizeOfArray(m_data[i].m_key));
			buffer[sizeOfArray(m_data[i].m_key)] = '\0';
			::strcat(buffer, ": Duplicate name encountered");
			GOL_FATALERROR_MESSAGE(buffer);
		}

		i += 1;
		if (i >= m_size) {
			i = 0;
		}

		if (i == startIndex) {
			GOL_FATALERROR_MESSAGE("AddName caused hash table overflow");
		}
	}

	::strncpy(m_data[i].m_key, p_str, sizeOfArray(m_data[i].m_key));
	m_data[i].m_unk0x8 = p_arg2;
}

// FUNCTION: GOLDP 0x100283e0
UtopianPan0xa4* SmallCocoon0xc::GetName(const LegoChar* p_str) const
{
	LegoU32 startIndex = 0;
	LegoU32 shift = 0;
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_data[0].m_key); i++) {
		LegoChar c = p_str[i];

		if (c == '\0') {
			break;
		}

		startIndex += c << shift;
		shift += 7;
		shift &= 0x1f;
	}

	startIndex %= m_size;

	for (i = startIndex; m_data[i].m_unk0x8 != NULL;) {
		if (::strncmp(m_data[i].m_key, p_str, sizeOfArray(m_data[i].m_key)) == 0) {
			return m_data[i].m_unk0x8;
		}

		i += 1;
		if (i >= m_size) {
			i = 0;
		}

		if (i == startIndex) {
			return NULL;
		}
	}

	return NULL;
}

// FUNCTION: GOLDP 0x10028470
void SmallCocoon0xc::FUN_10028470(const UtopianPan0xa4* p_needle, LegoChar* p_buffer) const
{
	for (LegoU32 i = 0; i < m_size; i++) {
		if (m_data[i].m_unk0x8 == p_needle) {
			::strncpy(p_buffer, m_data[i].m_key, sizeOfArray(m_data[i].m_key));
			return;
		}
	}

	p_buffer[0] = '\0';
}
