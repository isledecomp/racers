#include "golfilesource.h"

#include "golstream.h"

DECOMP_SIZE_ASSERT(GolFileSource, 0x34)

// GLOBAL: LEGORACERS 0x004c73a4
LegoChar g_nameBuffer[GOL_NAME_LENGTH];

// FUNCTION: LEGORACERS 0x0044d820
GolFileSource::GolFileSource()
{
	m_stream = NULL;
	m_state = 0;
	m_foundEntry = NULL;
}

// FUNCTION: LEGORACERS 0x0044d860
GolFileSource::~GolFileSource()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0044d8e0
void GolFileSource::Reset()
{
	m_rootDir.DeleteChildren();
	m_stream = NULL;
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x0044d900
LegoS32 GolFileSource::Open(LegoChar* p_fileName, LegoS32* p_position, LegoS32* p_size)
{
	GolDirEntry* node = &m_rootDir;
	LegoS32 pos = -1;

	while (TRUE) {
		LegoChar ch = p_fileName[pos + 1];
		LegoU32 nameLen = 0;
		pos++;

		while (ch && ch != '\\') {
			if (nameLen >= GOL_NAME_LENGTH) {
				return GolStream::e_ioNameTooLong;
			}

			g_nameBuffer[nameLen] = ch;
			ch = p_fileName[pos + 1];
			nameLen++;
			pos++;
		}

		if (nameLen < GOL_NAME_LENGTH) {
			g_nameBuffer[nameLen] = '\0';
		}

		if (p_fileName[pos] != '\\') {
			break;
		}

		node = node->FindDir(g_nameBuffer, m_stream);
		if (!node) {
			return GolStream::e_ioFileNotFound;
		}
	}

	GolDirEntry::FileEntry* entry = node->FindFile(g_nameBuffer, m_stream);
	if (!entry) {
		return GolStream::e_ioFileNotFound;
	}

	*p_position = entry->m_position;
	*p_size = entry->m_size;
	m_state = 1;
	return GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x0044d9c0
LegoS32 GolFileSource::Find(LegoChar* p_fileName)
{
	GolDirEntry* node = &m_rootDir;
	LegoS32 pos = -1;

	while (TRUE) {
		LegoChar ch = p_fileName[pos + 1];
		LegoU32 nameLen = 0;
		pos++;

		while (ch && ch != '\\') {
			if (nameLen >= GOL_NAME_LENGTH) {
				return GolStream::e_ioNameTooLong;
			}

			g_nameBuffer[nameLen] = ch;
			ch = p_fileName[pos + 1];
			nameLen++;
			pos++;
		}

		if (nameLen < GOL_NAME_LENGTH) {
			g_nameBuffer[nameLen] = '\0';
		}

		if (p_fileName[pos] != '\\') {
			break;
		}

		node = node->FindDir(g_nameBuffer, m_stream);
		if (!node) {
			return GolStream::e_ioFileNotFound;
		}
	}

	GolDirEntry::FileEntry* entry = node->FindFile(g_nameBuffer, m_stream);
	if (!entry) {
		return GolStream::e_ioFileNotFound;
	}

	m_foundEntry = entry;
	return 0;
}

// FUNCTION: LEGORACERS 0x0044da60
LegoS32 GolFileSource::Close()
{
	m_state = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x0044da70
LegoS32 GolFileSource::Read(LegoU32 p_offset, void* p_buf, LegoU32 p_size, LegoU32 p_maxSize, LegoS32* p_lenRead)
{
	*p_lenRead = 0;

	if (!p_size) {
		return GolStream::e_ioGenericError;
	}

	LegoU8* buf = (LegoU8*) p_buf;
	LegoU32 scanPos = 0;
	LegoU32 remaining = p_size;
	LegoS32 crFlag = 0;
	LegoU32 total = 0;

	while (TRUE) {
		LegoU32 chunkSize = remaining;
		if (remaining > GolStream::c_lineReadChunkSize) {
			chunkSize = GolStream::c_lineReadChunkSize;
		}

		LegoS32 result = m_stream->BufferedRead(scanPos + p_offset, &buf[scanPos], chunkSize, (LegoS32*) &p_buf);
		if (result) {
			return result;
		}

		total += (LegoU32) p_buf;

		if (scanPos < total) {
			while (TRUE) {
				LegoChar ch = buf[scanPos];

				if (ch == '\r') {
					crFlag = 1;
				}
				else if (ch == '\n') {
					*p_lenRead = scanPos + 1;

					if (crFlag) {
						buf[scanPos - 1] = 0;
						return 0;
					}

					buf[scanPos] = 0;
					return 0;
				}
				else if (ch == GolStream::c_dosEof || !ch) {
					*p_lenRead = scanPos + 1;
					buf[scanPos] = 0;
					return 0;
				}
				else {
					crFlag = 0;
				}

				if (++scanPos >= total) {
					break;
				}
			}
		}

		remaining -= chunkSize;

		if (!remaining && (LegoU32) p_buf >= chunkSize) {
			if (!total) {
				*p_lenRead = 0;
				buf[0] = 0;
				return GolStream::e_ioEndOfFile;
			}

			if (total < p_maxSize) {
				*p_lenRead = total;
				buf[total] = 0;
				return 0;
			}

			*p_lenRead = p_size;
			buf[p_size - 1] = 0;
			return 0;
		}
	}
}

// FUNCTION: LEGORACERS 0x0044dbb0
LegoS32 GolFileSource::ForwardRead(LegoU32 p_offset, void* p_buf, LegoU32 p_size, LegoS32* p_lenRead)
{
	return m_stream->BufferedRead(p_offset, p_buf, p_size, p_lenRead);
}
