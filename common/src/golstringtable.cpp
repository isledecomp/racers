#include "golstringtable.h"

#include "golstring.h"

DECOMP_SIZE_ASSERT(GolStringTable, 0x14)

// FUNCTION: LEGORACERS 0x0044e220
GolStringTable::GolStringTable()
{
	m_ownsBuffers = FALSE;
	m_stringOffsets = NULL;
	m_stringData = NULL;
}

// FUNCTION: LEGORACERS 0x0044e240
GolStringTable::~GolStringTable()
{
	if (m_ownsBuffers) {
		ReleaseOwnedBuffers();
	}
}

// FUNCTION: LEGORACERS 0x0044e260
LegoS32 GolStringTable::UseOwnedBuffers()
{
	if (m_ownsBuffers) {
		ReleaseOwnedBuffers();
	}

	m_ownsBuffers = TRUE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0044e280
LegoS32 GolStringTable::ReleaseOwnedBuffers()
{
	if (m_ownsBuffers) {
		if (m_stringData) {
			delete[] m_stringData;
		}

		if (m_stringOffsets) {
			delete[] m_stringOffsets;
		}

		m_stringData = NULL;
		m_stringOffsets = NULL;
	}

	return TRUE;
}

// STUB: LEGORACERS 0x0044e2c0
LegoS32 GolStringTable::Load(const LegoChar*)
{
	// TODO
	STUB(0x44e2c0);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0044e4d0
void GolStringTable::ReleaseBuffers()
{
	if (m_stringOffsets) {
		delete[] m_stringOffsets;
	}

	if (m_stringData) {
		delete[] m_stringData;
	}

	m_stringOffsets = NULL;
	m_stringData = NULL;
}

// FUNCTION: LEGORACERS 0x0044e500
LegoS32 GolStringTable::CopyStringByIndex(GolString* p_string, LegoU16 p_index)
{
	if (!m_stringData) {
		return 0;
	}
	else if (p_index > m_stringCount) {
		return 0;
	}

	return p_string->CopyFromBufSelection(&m_stringData[m_stringOffsets[p_index]], 0);
}
