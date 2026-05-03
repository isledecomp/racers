#include "golstream.h"

#include "golerror.h"
#include "golfile.h"
#include "golfilesource.h"
#include "golfsutil.h"
#include "golhashtable.h"
#include "types.h"

#include <ctype.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolStream, 0x30)

// GLOBAL: GOLDP 0x10065d68
// GLOBAL: LEGORACERS 0x004c7284
LegoChar g_pathBuffer[256];

// GLOBAL: GOLDP 0x10065e68
// GLOBAL: LEGORACERS 0x004c7384
LegoChar* g_searchPaths[4];

// GLOBAL: GOLDP 0x10065e78
// GLOBAL: LEGORACERS 0x004c7394
GolFileSource* g_fileSources;

// GLOBAL: GOLDP 0x10065e7c
// GLOBAL: LEGORACERS 0x004c7398
LegoU32 g_fileSourceCount;

// GLOBAL: GOLDP 0x10065e80
// GLOBAL: LEGORACERS 0x004c739c
LegoU32 g_searchPathCount;

// GLOBAL: GOLDP 0x10065e84
// GLOBAL: LEGORACERS 0x004c73a0
GolHashTable* g_hashTable;

// GLOBAL: GOLDP 0x1005f04c
// GLOBAL: LEGORACERS 0x004c1848
static const LegoChar* const g_errorCodeStrings[] = {
	"Not a error",
	"General I/O error",
	"Invalid parameter",
	"Invalid value",
	"Out of memory error",
	"I/O Busy error",
	"Operation not supported",
	"File not open",
	"File not found",
	"Access denied",
	"File already exists",
	"Exceeded maximum files open",
	"Invalid name",
	"Unable to read",
	"Unable to write",
	"Unable to seek",
	"Attempt to read past file end",
	"Invalid character encoutered"
};

// FUNCTION: GOLDP 0x100314a0
// FUNCTION: LEGORACERS 0x0044c920
GolStream::GolStream()
{
	Init();
}

// FUNCTION: GOLDP 0x10031530
// FUNCTION: LEGORACERS 0x0044c960
GolStream::~GolStream()
{
	if (m_buffer) {
		delete[] m_buffer;
		m_buffer = NULL;
	}

	Init();
}

// FUNCTION: LEGORACERS 0x0044c990
void GolStream::Init()
{
	m_handle = -1;
	m_mode = 0;
	m_flags = 0;
	m_position = 0;
	m_size = 0;
	m_unk0x10 = 0;
	m_bufferCapacity = 0;
	m_bufferStart = 0;
	m_bufferEnd = 0;
	m_buffer = NULL;
}

// FUNCTION: LEGORACERS 0x0044c9c0
LegoS32 GolStream::FindFile(const LegoChar* p_fileName)
{
	LegoS32 result = e_ioFileNotFound;
	LegoS32 isAbsolute = IsAbsolutePath(p_fileName);

	GolFsLock();

	if (!isAbsolute) {
		BuildPathname(NULL, p_fileName);

		LegoU32 i = 0;
		while (result == e_ioFileNotFound) {
			if (i >= g_fileSourceCount) {
				break;
			}

			result = g_fileSources[i].Find(g_pathBuffer);
			i++;
		}

		if (result != e_ioFileNotFound) {
			GolFsUnlock();
			return result;
		}
	}

	if (g_searchPathCount && !isAbsolute) {
		result = e_ioFileNotFound;
		LegoU32 i = 0;

		while (result == e_ioFileNotFound) {
			if (i >= g_searchPathCount) {
				break;
			}

			BuildPathname(g_searchPaths[i], p_fileName);
			result = GolFile::Exists(g_pathBuffer);
			++i;
		}
	}
	else {
		BuildPathname(NULL, p_fileName);
		result = GolFile::Exists(g_pathBuffer);
	}

	GolFsUnlock();
	return result;
}

// FUNCTION: LEGORACERS 0x0044caa0
LegoS32 GolStream::OpenFileSource()
{
	LegoS32 result = e_ioFileNotFound;

	if (!g_fileSources) {
		return result;
	}

	if (m_mode & (c_modeCreate | c_modeWrite | c_unk0x40)) {
		return result;
	}

	for (LegoU32 i = 0; i < g_fileSourceCount; i++) {
		result = g_fileSources[i].Open(g_pathBuffer, &m_position, &m_size);
		if (result == e_ioSuccess) {
			m_handle = i;
			m_flags = c_flagOpen | c_flagMapped;
			break;
		}
	}

	return result;
}

// FUNCTION: GOLDP 0x10031580
// FUNCTION: LEGORACERS 0x0044cb30
LegoS32 GolStream::BufferedOpen(const LegoChar* p_fileName, LegoS32 p_mode, LegoU32 p_bufferSize)
{
	if (m_flags & c_flagOpen) {
		Dispose();
	}

	GolFsLock();

	m_mode = p_mode;
	m_flags = 0;
	m_unk0x10 = 0;
	m_bufferStart = 0;
	m_bufferEnd = 0;
	m_position = 0;

	LegoS32 isAbsolute = IsAbsolutePath(p_fileName);
	LegoS32 result;

	if (!isAbsolute) {
		BuildPathname(NULL, p_fileName);
		result = OpenFileSource();

		if (result != e_ioFileNotFound) {
			m_flags |= result == 0;
			GolFsUnlock();
			return result;
		}
	}

	if (!g_searchPathCount || isAbsolute) {
		BuildPathname(NULL, p_fileName);
		result = Open(g_pathBuffer);
	}
	else {
		result = e_ioFileNotFound;
		LegoU32 i = 0;

		while (result == e_ioFileNotFound) {
			if (i >= g_searchPathCount) {
				break;
			}

			BuildPathname(g_searchPaths[i], p_fileName);
			result = Open(g_pathBuffer);
			++i;
		}
	}

	if (result == e_ioSuccess) {
		m_flags = c_flagOpen;

		if (!(p_mode & c_modeKeepBuffer) || !m_buffer) {
			if (m_buffer) {
				delete m_buffer;
				m_buffer = NULL;
			}

			if (p_bufferSize) {
				p_bufferSize = (p_bufferSize & 1) + p_bufferSize;
				LegoU8* newBuf = new LegoU8[p_bufferSize];
				m_buffer = newBuf;

				if (!newBuf) {
					Dispose();
					GolFsUnlock();
					return e_ioOutOfMemory;
				}
			}

			m_bufferCapacity = p_bufferSize;
		}
	}
	else {
		GolFsUnlock();
		return result;
	}

	GolFsUnlock();
	return e_ioSuccess;
}

// FUNCTION: GOLDP 0x10031790
// FUNCTION: LEGORACERS 0x0044cc90
LegoS32 GolStream::Dispose()
{
	if (m_flags & c_flagMapped) {
		LegoS32 result = g_fileSources[m_handle].Close();
		m_handle = -1;
		m_mode = 0;
		m_flags = 0;
		return result;
	}
	else {
		Close();

		if (!(m_mode & c_modeKeepBuffer)) {
			if (m_buffer) {
				delete[] m_buffer;
				m_buffer = NULL;
			}
		}

		m_bufferStart = 0;
		m_bufferEnd = 0;
		m_mode = 0;
		m_flags = 0;
		m_handle = -1;
		return e_ioSuccess;
	}
}

// FUNCTION: GOLDP 0x10031800
// FUNCTION: LEGORACERS 0x0044cd00
LegoS32 GolStream::BufferedRead(LegoU32 p_offset, void* p_buf, LegoU32 p_size, LegoS32* p_lenRead)
{
	LegoS32* lenRead = p_lenRead;
	*lenRead = 0;

	if (!(m_flags & c_flagOpen)) {
		return e_ioNotOpen;
	}

	if (p_size < 1) {
		return e_ioBadParameter;
	}

	LegoU32 offset = p_offset;
	void* buf = p_buf;

	if (p_size > c_maxReadChunkSize) {
		LegoS32 chunkLen;

		while (TRUE) {
			LegoS32 result = BufferedRead(offset, buf, c_maxReadChunkSize, &chunkLen);
			if (result) {
				return result;
			}

			p_size -= chunkLen;
			buf = (LegoU8*) buf + chunkLen;
			offset += chunkLen;
			*lenRead += chunkLen;
			p_buf = buf;

			if (p_size <= c_maxReadChunkSize) {
				break;
			}
		}
	}

	LegoS32 flags = m_flags;
	if (flags & c_flagMapped) {
		if (offset >= (LegoU32) m_size) {
			return e_ioEndOfFile;
		}

		if (offset + p_size > (LegoU32) m_size) {
			p_size = m_size - offset;
		}

		LegoS32 savedLen = *lenRead;
		GolFsLock();
		LegoS32 result = g_fileSources[m_handle].ForwardRead(offset + m_position, buf, p_size, lenRead);
		GolFsUnlock();
		*lenRead += savedLen;
		return result;
	}

	if (flags & c_flagCached) {
		if (offset >= m_bufferStart && offset < m_bufferEnd) {
			LegoU8* src = m_buffer + offset - m_bufferStart;

			if (offset + p_size <= m_bufferEnd) {
				memcpy(buf, src, p_size);
				*lenRead += p_size;
				return e_ioSuccess;
			}

			LegoU32 available = m_bufferEnd - offset;
			offset += available;
			memcpy(buf, src, available);
			p_buf = (LegoU8*) p_buf + available;
			*lenRead += available;
			p_size -= available;
			buf = p_buf;
		}
	}

	if ((LegoU32) m_position != offset) {
		LegoS32 result = Seek(offset);
		if (result) {
			return result;
		}

		p_size = p_size;
	}

	LegoS32 result;

	if (m_buffer) {
		m_flags &= ~c_flagCached;
		result = Read(m_buffer, m_bufferCapacity, (LegoS32*) &p_offset);
		LegoS32 savedResult = result;

		if (!result) {
			while (TRUE) {
				LegoU32 bytesRead = p_offset;
				LegoU32 bufPtr = (LegoU32) m_buffer;
				m_flags |= c_flagCached;
				LegoS32 pos = m_position;
				m_bufferStart = pos;
				LegoU32 bufEnd = pos + bytesRead;
				LegoU32 srcOff = bufPtr - pos;
				LegoU8* src = (LegoU8*) (offset + srcOff);
				m_bufferEnd = bufEnd;

				if (offset + p_size <= bufEnd) {
					memcpy(buf, src, p_size);
					*lenRead += p_size;
					p_size = 0;
				}
				else {
					LegoU32 available = bufEnd - offset;
					offset += available;
					memcpy(buf, src, available);
					p_buf = (LegoU8*) p_buf + available;
					*lenRead += available;
					p_size -= available;
				}

				result = savedResult;
				m_position += p_offset;

				if (!p_size) {
					return result;
				}

				m_flags &= ~c_flagCached;
				result = Read(m_buffer, m_bufferCapacity, (LegoS32*) &p_offset);
				savedResult = result;

				if (result) {
					break;
				}

				buf = p_buf;
			}
		}
	}
	else {
		result = Read(buf, p_size, (LegoS32*) &p_offset);
		if (!result) {
			*lenRead += p_offset;
			m_position += p_offset;
			return result;
		}
	}

	if (result == e_ioEndOfFile && *lenRead) {
		return e_ioSuccess;
	}

	return result;
}

// FUNCTION: GOLDP 0x10031af0
// FUNCTION: LEGORACERS 0x0044cff0
LegoS32 GolStream::ReadLine(void* p_buf, LegoU32 p_size)
{
	LegoS32 flags = m_flags;

	if (!(flags & c_flagOpen)) {
		return e_ioNotOpen;
	}

	LegoU32 maxSize = p_size;

	if (!maxSize) {
		return e_ioBadParameter;
	}

	LegoS32 result;
	LegoS32 bytesRead;

	if (flags & c_flagMapped) {
		LegoU32 pos = m_unk0x10;
		LegoU32 size = m_size;

		if (pos >= size) {
			return e_ioEndOfFile;
		}

		if (pos + p_size > size) {
			p_size = size - pos;
		}

		result = g_fileSources[m_handle].Read(pos + m_position, p_buf, p_size, maxSize, (LegoS32*) &p_buf);

		if (!result) {
			m_unk0x10 += (LegoS32) p_buf;
			return e_ioSuccess;
		}
	}
	else {
		LegoU8* buf = (LegoU8*) p_buf;
		LegoU32 written = 0;

		while (TRUE) {
			LegoU32 pos = m_position;

			if (m_flags & c_flagCached) {
				LegoU32 start = m_bufferStart;

				if (pos >= start && pos < m_bufferEnd) {
					LegoU32 offset = pos - start;

					while (TRUE) {
						LegoU8 ch = m_buffer[offset];

						if (ch == '\n') {
							buf[written] = 0;

							if (written > 0 && buf[written - 1] == '\r') {
								buf[written - 1] = 0;
							}

							result = e_ioSuccess;
							m_position = m_bufferStart + offset + 1;
							return result;
						}

						if (written >= p_size) {
							buf[p_size - 1] = 0;
							m_position = offset + m_bufferStart;
							return e_ioSuccess;
						}

						buf[written] = ch;
						++written;
						++offset;

						if (++pos >= m_bufferEnd) {
							m_position = pos;
							break;
						}
					}
				}
			}

			m_flags &= ~c_flagCached;
			result = Read(m_buffer, m_bufferCapacity, &bytesRead);

			if (result) {
				if (result == e_ioEndOfFile && written) {
					buf[written] = 0;
					return e_ioSuccess;
				}

				return result;
			}

			m_flags |= c_flagCached;
			m_bufferStart = m_position;
			m_bufferEnd = bytesRead + m_position;
		}
	}

	return result;
}

// FUNCTION: GOLDP 0x10031c80
// FUNCTION: LEGORACERS 0x0044d180
const LegoChar* GolStream::ErrorCodeToString(LegoS32 p_code)
{

	return g_errorCodeStrings[p_code];
}

// FUNCTION: GOLDP 0x10031c90
// FUNCTION: LEGORACERS 0x0044d190
void GolStream::BuildPathname(const LegoChar* p_prefix, const LegoChar* p_path)
{
	g_pathBuffer[0] = '\0';

	LegoU32 pathLength = strlen(p_path);
	if (pathLength >= sizeOfArray(g_pathBuffer)) {
		GOL_FATALERROR_MESSAGE("Unable to build pathname, too many chars");
	}

	LegoU32 prefixLength = 0;
	LegoBool32 isAbsolutePath = FALSE;
	if (p_path[0] == '\\' && p_path[1] == '\\') {
		p_path++;
		isAbsolutePath = TRUE;
	}
	else if (isalpha(p_path[0]) && p_path[1] == ':') {
		isAbsolutePath = TRUE;
	}
	else if (p_prefix) {
		prefixLength = strlen(p_prefix);
		if (pathLength + prefixLength + 1 >= sizeOfArray(g_pathBuffer)) {
			GOL_FATALERROR_MESSAGE("Unable to build pathname, too many chars");
		}

		strcpy(g_pathBuffer, p_prefix);
		if (g_pathBuffer[prefixLength - 1] != '\\') {
			g_pathBuffer[prefixLength] = '\\';
			g_pathBuffer[prefixLength + 1] = '\0';
			prefixLength++;
		}
	}

	if (!g_hashTable) {
		if (p_path[0] == '\\' && prefixLength) {
			p_path++;
		}

		strcat(g_pathBuffer, p_path);
		TransformToUpper(g_pathBuffer);
		return;
	}

	LegoChar* slash = strrchr((LegoChar*) p_path, '\\');
	if (isAbsolutePath) {
		strcpy(g_pathBuffer, p_path);
		TransformToUpper(g_pathBuffer);

		if (slash) {
			LegoU32 slashOffset = slash - p_path;
			g_pathBuffer[slashOffset] = '\0';
			g_hashTable->AddString(g_pathBuffer);
			g_pathBuffer[slashOffset] = '\\';
		}

		return;
	}

	const LegoChar* currentEntryPath = NULL;
	if (g_hashTable) {
		GolHashTable::Entry* currentEntry = g_hashTable->GetCurrentEntry();
		if (currentEntry) {
			currentEntryPath = GolHashTable::GetEntryPath(currentEntry);
		}
	}

	if (slash) {
		LegoU32 directoryEnd;
		if (p_path[0] != '\\' && currentEntryPath) {
			LegoU32 currentEntryLength = strlen(currentEntryPath);
			if (pathLength + currentEntryLength + prefixLength + 1 >= sizeOfArray(g_pathBuffer)) {
				GOL_FATALERROR_MESSAGE("Unable to build pathname, too many chars");
			}

			if (currentEntryPath[0] == '\\') {
				currentEntryPath++;
			}

			strcat(g_pathBuffer, currentEntryPath);
			directoryEnd = strlen(g_pathBuffer);
			if (g_pathBuffer[directoryEnd - 1] != '\\') {
				g_pathBuffer[directoryEnd] = '\\';
				g_pathBuffer[directoryEnd + 1] = '\0';
				directoryEnd++;
			}
		}
		else if (p_path[0] == '\\') {
			directoryEnd = prefixLength;
			p_path++;
		}
		else {
			directoryEnd = prefixLength;
		}

		strcat(g_pathBuffer, p_path);
		TransformToUpper(g_pathBuffer);

		if (slash > p_path) {
			directoryEnd += slash - p_path;
			LegoChar* entryPath = g_pathBuffer + prefixLength;
			g_pathBuffer[directoryEnd] = '\0';
			g_hashTable->AddString(entryPath);
			g_pathBuffer[directoryEnd] = '\\';
		}

		return;
	}

	if (currentEntryPath && currentEntryPath[0]) {
		strcat(g_pathBuffer, currentEntryPath);
		strcat(g_pathBuffer, "\\");
	}

	strcat(g_pathBuffer, p_path);
	TransformToUpper(g_pathBuffer);
}

// FUNCTION: LEGORACERS 0x0044d4f0
void GolStream::TransformToUpper(LegoChar* p_str)
{
	size_t i;

	for (i = 0; *p_str != '\0' && i < sizeOfArray(g_pathBuffer); i++, p_str++) {
		*p_str = toupper(*p_str);
	}
}

// FUNCTION: LEGORACERS 0x0044d530
LegoS32 GolStream::IsAbsolutePath(const LegoChar* p_path)
{
	if (p_path[0] == '\\' && p_path[1] == '\\') {
		return TRUE;
	}

	return isalpha(p_path[0]) && p_path[1] == ':';
}

#ifdef BUILDING_GOL

// FUNCTION: GOLDP 0x100320d0
void GolStream::FUN_100320d0()
{
	for (LegoU32 i = 0; i < g_searchPathCount; i++) {
		if (g_searchPaths[i] != NULL) {
			delete[] g_searchPaths[i];
			g_searchPaths[i] = NULL;
		}
	}
}

// FUNCTION: GOLDP 0x10032110
void GolStream::FUN_10032110(const LegoChar* p_arg1)
{
	if (g_searchPathCount < sizeOfArray(g_searchPaths)) {
		g_searchPaths[g_searchPathCount] = new LegoChar[::strlen(p_arg1) + 1];

		if (g_searchPaths[g_searchPathCount] == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		strcpy(g_searchPaths[g_searchPathCount], p_arg1);
		g_searchPathCount++;
	}
}
#endif

// FUNCTION: GOLDP 0x10032190
// FUNCTION: LEGORACERS 0x0044d570
LegoS32 GolStream::BufferedWrite(LegoS32 p_offset, const void* p_buf, LegoU32 p_size)
{
	if (!(m_flags & c_flagOpen)) {
		return e_ioNotOpen;
	}

	if (m_buffer && p_size <= m_bufferCapacity) {
		if (m_flags & c_flagDirty) {
			LegoS32 bufferUsed = m_bufferEnd - m_bufferStart;

			if ((LegoU32) bufferUsed + p_size <= m_bufferCapacity && p_offset == (LegoS32) m_bufferEnd) {
				memcpy(m_buffer + m_bufferEnd - m_bufferStart, p_buf, p_size);
				m_bufferEnd += p_size;
				return e_ioSuccess;
			}

			if (m_position != (LegoS32) m_bufferStart) {
				if (Seek(m_bufferStart)) {
					return e_ioSeekError;
				}

				m_position = m_bufferStart;
			}

			LegoS32 result = Write(m_buffer, bufferUsed);
			if (result) {
				return result;
			}

			m_position += bufferUsed;
		}

		m_flags |= c_flagCached | c_flagDirty;
		m_bufferStart = p_offset;
		m_bufferEnd = p_size + p_offset;
		memcpy(m_buffer, p_buf, p_size);
		return e_ioSuccess;
	}
	else {
		if (m_position != p_offset) {
			if (Seek(p_offset)) {
				return e_ioSeekError;
			}

			m_position = p_offset;
		}

		LegoS32 result = Write((void*) p_buf, p_size);
		if (!result) {
			m_position += p_size;
			return e_ioSuccess;
		}

		return result;
	}
}

// FUNCTION: GOLDP 0x100322c0
// FUNCTION: LEGORACERS 0x0044d6a0
LegoS32 GolStream::WriteLine(const void* p_buf, LegoU32 p_size)
{
	LegoU8 newline = '\n';

	if (!(m_flags & c_flagOpen)) {
		return e_ioNotOpen;
	}

	if (m_buffer && p_size + 1 <= m_bufferCapacity) {
		if (m_flags & c_flagDirty && p_size + 1 > m_bufferCapacity + m_bufferStart - m_bufferEnd) {
			FlushWriteBuffer();
		}

		memcpy(m_buffer + m_bufferEnd - m_bufferStart, p_buf, p_size);
		m_bufferEnd += p_size;
		m_buffer[m_bufferEnd - m_bufferStart] = newline;
		m_bufferEnd++;
		m_flags |= c_flagCached | c_flagDirty;
		return e_ioSuccess;
	}
	else {
		if (m_flags & c_flagDirty) {
			FlushWriteBuffer();
		}

		LegoS32 result = Write((void*) p_buf, p_size);
		if (!result) {
			return Write(&newline, 1);
		}

		return result;
	}
}

// FUNCTION: GOLDP 0x100323a0
// FUNCTION: LEGORACERS 0x0044d780
LegoS32 GolStream::FlushWriteBuffer()
{
	if (!(m_flags & c_flagOpen)) {
		return e_ioNotOpen;
	}

	LegoS32 start = m_bufferStart;
	LegoS32 size = m_bufferEnd - start;

	if (!m_buffer || !(m_flags & c_flagDirty) || !size) {
		return e_ioSuccess;
	}

	if (!(m_mode & c_modeTextAppend) && m_position != start) {
		if (Seek(m_bufferStart)) {
			return e_ioSeekError;
		}

		m_position = m_bufferStart;
	}

	LegoS32 result = Write(m_buffer, size);
	if (!result) {
		if (m_mode & c_modeTextAppend) {
			m_bufferEnd = m_bufferStart;
		}
		else {
			m_position += size;
		}

		m_flags &= ~c_flagDirty;
		return Flush();
	}

	return result;
}

// FUNCTION: GOLDP 0x100016f0 FOLDED
// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
LegoS32 GolStream::Flush()
{
#ifdef BUILDING_GOL
	MATCHING(0x100016f0);
#endif
	return e_ioSuccess;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
// FUNCTION: LEGORACERS 0x0044e7f0 FOLDED
LegoS32 GolStream::Write(void*, LegoU32)
{
	return e_ioSuccess;
}
