#include "goldirentry.h"

#include "golerror.h"
#include "golstream.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolDirEntry, 0x24)
DECOMP_SIZE_ASSERT(GolDirEntry::FileEntry, 0x14)

extern const LegoChar* g_jamReadError;
extern LegoChar g_jamReadBuffer[20];

#define READ_LITTLE_ENDIAN_U32(p_data, p_value)                                                                        \
	do {                                                                                                               \
		LegoU32 result = (LegoU8) (p_data)[3];                                                                         \
		result <<= 8;                                                                                                  \
		result += (LegoU8) (p_data)[2];                                                                                \
		result <<= 8;                                                                                                  \
		result += (LegoU8) (p_data)[1];                                                                                \
		result <<= 8;                                                                                                  \
		result += (LegoU8) (p_data)[0];                                                                                \
		p_value = result;                                                                                              \
	} while (0)

// FUNCTION: LEGORACERS 0x0044dbe0
GolDirEntry::GolDirEntry()
{
	m_name[0] = '\0';
	m_loaded = FALSE;
	m_contentsOffset = 4;
	m_fileCount = 0;
	m_files = NULL;
	m_dirCount = 0;
	m_dirs = NULL;
}

// FUNCTION: LEGORACERS 0x0044dc00
void GolDirEntry::DeleteChildren()
{
	m_loaded = FALSE;

	if (m_dirs) {
		for (LegoU32 i = 0; i < m_dirCount; i++) {
			m_dirs[i].DeleteChildren();
		}

		delete m_dirs;
		m_dirs = NULL;
		m_dirCount = 0;
	}

	if (m_files) {
		delete m_files;
		m_files = NULL;
		m_fileCount = 0;
	}
}

// FUNCTION: LEGORACERS 0x0044dc60
GolDirEntry* GolDirEntry::FindDir(LegoChar* p_name, GolStream* p_stream)
{
	if (!m_loaded) {
		Load(p_stream);
	}

	for (LegoU32 i = 0; i < m_dirCount; i++) {
		if (!strncmp(m_dirs[i].m_name, p_name, GOL_NAME_LENGTH)) {
			return &m_dirs[i];
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0044dcc0
GolDirEntry::FileEntry* GolDirEntry::FindFile(LegoChar* p_name, GolStream* p_stream)
{
	if (!m_loaded) {
		Load(p_stream);
	}

	for (LegoU32 i = 0; i < m_fileCount; i++) {
		if (!strncmp(m_files[i].m_name, p_name, GOL_NAME_LENGTH)) {
			return &m_files[i];
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0044dd20
void GolDirEntry::Load(GolStream* p_stream)
{
	if (m_loaded) {
		return;
	}

	LegoS32 bytesRead;
	LegoU32 offset = m_contentsOffset;

	if (p_stream->BufferedRead(offset, g_jamReadBuffer, c_jamEntryCountSize, &bytesRead)) {
		GOL_FATALERROR_MESSAGE(g_jamReadError);
	}

	READ_LITTLE_ENDIAN_U32(g_jamReadBuffer, m_fileCount);
	offset += c_jamEntryCountSize;

	if (m_fileCount > c_maxJamEntryCount) {
		GOL_FATALERROR_MESSAGE(g_jamReadError);
	}

	if (m_fileCount) {
		m_files = new FileEntry[m_fileCount];
		if (!m_files) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_fileCount; i++) {
			if (p_stream->BufferedRead(offset, g_jamReadBuffer, c_jamFileRecordSize, &bytesRead)) {
				GOL_FATALERROR_MESSAGE(g_jamReadError);
			}

			offset += bytesRead;
			memcpy(m_files[i].m_name, g_jamReadBuffer, GOL_NAME_LENGTH);
			READ_LITTLE_ENDIAN_U32(&g_jamReadBuffer[12], m_files[i].m_position);
			READ_LITTLE_ENDIAN_U32(&g_jamReadBuffer[16], m_files[i].m_size);
		}
	}

	if (p_stream->BufferedRead(offset, g_jamReadBuffer, c_jamEntryCountSize, &bytesRead)) {
		GOL_FATALERROR_MESSAGE(g_jamReadError);
	}

	READ_LITTLE_ENDIAN_U32(g_jamReadBuffer, m_dirCount);
	offset += c_jamEntryCountSize;

	if (m_dirCount > c_maxJamEntryCount) {
		GOL_FATALERROR_MESSAGE(g_jamReadError);
	}

	if (m_dirCount) {
		m_dirs = new GolDirEntry[m_dirCount];
		if (!m_dirs) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		for (LegoU32 i = 0; i < m_dirCount; i++) {
			if (p_stream->BufferedRead(offset, g_jamReadBuffer, c_jamDirRecordSize, &bytesRead)) {
				GOL_FATALERROR_MESSAGE(g_jamReadError);
			}

			offset += bytesRead;
			memcpy(m_dirs[i].m_name, g_jamReadBuffer, GOL_NAME_LENGTH);
			m_dirs[i].m_loaded = FALSE;
			READ_LITTLE_ENDIAN_U32(&g_jamReadBuffer[12], m_dirs[i].m_contentsOffset);
		}
	}

	m_loaded = TRUE;
}

#undef READ_LITTLE_ENDIAN_U32
