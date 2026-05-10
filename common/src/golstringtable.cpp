#include "golstringtable.h"

#include "golerror.h"
#include "golfile.h"
#include "golstring.h"

DECOMP_SIZE_ASSERT(GolStringTable, 0x14)

inline static undefined2 ReadLittleEndianWord(const LegoU8* p_bytes)
{
	return p_bytes[0] + (p_bytes[1] << 8);
}

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

// FUNCTION: LEGORACERS 0x0044e2c0
LegoS32 GolStringTable::Load(const LegoChar* p_fileName)
{
	LegoS32 bytesRead;
	LegoS32 i;
	LegoU32 wordBuffer[2];
	GolFile file;

	if (m_stringOffsets) {
		ReleaseBuffers();
	}

	if (file.BufferedOpen(p_fileName, GolStream::c_modeRead, 0)) {
		return FALSE;
	}

	if (file.BufferedRead(0, wordBuffer, sizeof(undefined2), &bytesRead)) {
		return FALSE;
	}

	if (bytesRead != sizeof(undefined2)) {
		return FALSE;
	}

	m_stringCount = ReadLittleEndianWord((LegoU8*) wordBuffer);

	if (file.BufferedRead(sizeof(undefined2), wordBuffer, sizeof(undefined2), &bytesRead) ||
		bytesRead != sizeof(undefined2)) {
		return FALSE;
	}

	undefined2 stringDataLength = ReadLittleEndianWord((LegoU8*) wordBuffer);
	m_stringOffsets = new undefined2[m_stringCount];
	m_stringData = new undefined2[stringDataLength];

	if (!m_stringOffsets || !m_stringData) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	if (file.BufferedRead(2 * sizeof(undefined2), m_stringOffsets, sizeof(undefined2) * m_stringCount, &bytesRead)) {
		return FALSE;
	}

	LegoU32 stringDataOffset = bytesRead + 2 * sizeof(undefined2);
	LegoU8* bytes = (LegoU8*) m_stringOffsets;

	for (i = 0; i < m_stringCount; i++) {
		undefined2 word = bytes[0] + (bytes[1] << 8);
		bytes += sizeof(undefined2);
		m_stringOffsets[i] = word;
	}

	if (file.BufferedRead(stringDataOffset, m_stringData, sizeof(undefined2) * stringDataLength, &bytesRead)) {
		return FALSE;
	}

	file.Dispose();
	bytes = (LegoU8*) m_stringData;

	for (i = 0; i < stringDataLength; i++) {
		undefined2 word = bytes[0] + (bytes[1] << 8);
		bytes += sizeof(undefined2);
		m_stringData[i] = word;
	}

	return TRUE;
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
