#include "golstream.h"

#include "golfilesource.h"
#include "types.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolStream, 0x30)

// GLOBAL: LEGORACERS 0x4c7394
GolFileSource* g_unk0x4c7394;

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
		LegoS32 result = g_unk0x4c7394[m_handle].Close();
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

// STUB: LEGORACERS 0x44cd00
LegoS32 GolStream::BufferedRead(LegoU32, void*, LegoU32, LegoS32*)
{
	// TODO: complex buffered read with cache and provider support
	STUB(0x44cd00);
	return 0;
}

// STUB: LEGORACERS 0x44cff0
LegoS32 GolStream::ReadLine(void*, LegoU32)
{
	// TODO: complex line reader with cache and provider support
	STUB(0x44cff0);
	return 0;
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
