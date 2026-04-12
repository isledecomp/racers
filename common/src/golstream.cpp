#include "golstream.h"

#include "golfilesource.h"
#include "golfsutil.h"
#include "types.h"

#include <ctype.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolStream, 0x30)

// GLOBAL: LEGORACERS 0x4c7394
GolFileSource* g_fileSources;

// FUNCTION: LEGORACERS 0x44c920
GolStream::GolStream()
{
	Init();
}

// FUNCTION: LEGORACERS 0x44c960
GolStream::~GolStream()
{
	if (m_buffer) {
		delete[] m_buffer;
		m_buffer = NULL;
	}

	Init();
}

// FUNCTION: LEGORACERS 0x44c990
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

// STUB: LEGORACERS 0x44cb30
LegoS32 GolStream::BufferedOpen(LegoChar*, LegoS32, LegoU32)
{
	// TODO: needs path helper functions and search path globals
	STUB(0x44cb30);
	return 0;
}

// FUNCTION: LEGORACERS 0x44cc90
LegoS32 GolStream::Dispose()
{
	if ((m_flags & c_flagMapped) != 0) {
		LegoS32 result = g_fileSources[m_handle].Close();
		m_handle = -1;
		m_mode = 0;
		m_flags = 0;
		return result;
	}
	else {
		Close();

		if ((m_mode & c_modeKeepBuffer) == 0) {
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

// FUNCTION: LEGORACERS 0x44cd00
LegoS32 GolStream::BufferedRead(LegoU32 p_offset, void* p_buf, LegoU32 p_size, LegoS32* p_lenRead)
{
	LegoS32* lenRead = p_lenRead;
	*lenRead = 0;

	if ((m_flags & c_flagOpen) == 0) {
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
	if ((flags & c_flagMapped) != 0) {
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

	if ((flags & c_flagCached) != 0) {
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

// FUNCTION: LEGORACERS 0x44cff0
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

			if ((m_flags & c_flagCached) != 0) {
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

// FUNCTION: LEGORACERS 0x44d530
LegoS32 GolIsAbsolutePath(LegoChar* p_path)
{
	if (p_path[0] == '\\' && p_path[1] == '\\') {
		return TRUE;
	}

	return isalpha(p_path[0]) && p_path[1] == ':';
}

// FUNCTION: LEGORACERS 0x44d570
LegoS32 GolStream::BufferedWrite(LegoS32 p_offset, const void* p_buf, LegoU32 p_size)
{
	if ((m_flags & c_flagOpen) == 0) {
		return e_ioNotOpen;
	}

	if (m_buffer && p_size <= m_bufferCapacity) {
		if ((m_flags & c_flagDirty) != 0) {
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

// FUNCTION: LEGORACERS 0x44d6a0
LegoS32 GolStream::WriteLine(const void* p_buf, LegoU32 p_size)
{
	LegoU8 newline = '\n';

	if ((m_flags & c_flagOpen) == 0) {
		return e_ioNotOpen;
	}

	if (m_buffer && p_size + 1 <= m_bufferCapacity) {
		if ((m_flags & c_flagDirty) != 0 && p_size + 1 > m_bufferCapacity + m_bufferStart - m_bufferEnd) {
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
		if ((m_flags & c_flagDirty) != 0) {
			FlushWriteBuffer();
		}

		LegoS32 result = Write((void*) p_buf, p_size);
		if (!result) {
			return Write(&newline, 1);
		}

		return result;
	}
}

// FUNCTION: LEGORACERS 0x44d780
LegoS32 GolStream::FlushWriteBuffer()
{
	if ((m_flags & c_flagOpen) == 0) {
		return e_ioNotOpen;
	}

	LegoS32 start = m_bufferStart;
	LegoS32 size = m_bufferEnd - start;

	if (!m_buffer || (m_flags & c_flagDirty) == 0 || !size) {
		return e_ioSuccess;
	}

	if ((m_mode & c_modeTextAppend) == 0 && m_position != start) {
		if (Seek(m_bufferStart)) {
			return e_ioSeekError;
		}

		m_position = m_bufferStart;
	}

	LegoS32 result = Write(m_buffer, size);
	if (!result) {
		if ((m_mode & c_modeTextAppend) != 0) {
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

// FUNCTION: LEGORACERS 0x44e7e0
LegoS32 GolStream::Flush()
{
	return e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x44e7f0
LegoS32 GolStream::Write(void*, LegoU32)
{
	return e_ioSuccess;
}
