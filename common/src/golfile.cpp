#include "golfile.h"

#include "types.h"

#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <sys/stat.h>

DECOMP_SIZE_ASSERT(GolFile, 0x30)

// FUNCTION: LEGORACERS 0x450a90
GolFile::GolFile()
{
	m_fd = -1;
}

// FUNCTION: LEGORACERS 0x450ad0
GolFile::~GolFile()
{
	GolStream::Dispose();
}

// FUNCTION: LEGORACERS 0x450b50
LegoS32 GolFile::Open(LegoChar* p_fileName)
{
	int openFlags = 0;
	int result = e_ioFileNotFound;
	int mode = m_mode;

	if ((mode & c_modeRead) != 0) {
		if ((mode & c_modeWrite) != 0) {
			result = e_ioBadParameter;
		}
	}
	else {
		openFlags = (mode & c_modeWrite) != 0 ? _O_WRONLY : _O_RDWR;
	}

	if ((mode & c_modeTextAppend) != 0) {
		openFlags |= _O_TEXT | _O_APPEND;

		if ((mode & (c_modeRead | c_modeWrite)) == 0) {
			result = e_ioBadParameter;
		}
	}
	else {
		openFlags |= _O_BINARY;
	}

	if ((mode & c_modeCreate) != 0) {
		openFlags |= _O_CREAT;

		if ((mode & c_modeExclusive) != 0) {
			openFlags |= _O_EXCL;
		}
		else {
			openFlags |= _O_TRUNC;
		}
	}

	if (result == e_ioFileNotFound) {
		m_fd = _open(p_fileName, openFlags, _S_IREAD | _S_IWRITE);

		if (m_fd < 0) {
			switch (errno) {
			case ENOENT:
				return e_ioFileNotFound;
			case ENOMEM:
				return e_ioOutOfMemory;
			case EEXIST:
				return e_ioFileExists;
			case EACCES:
				return e_ioAccessDenied;
			case EMFILE:
				return e_ioTooManyFiles;
			default:
				return e_ioGenericError;
			}
		}

		_lseek(m_fd, 0, SEEK_END);
		m_size = _tell(m_fd);
		_lseek(m_fd, 0, SEEK_SET);
		m_flags = c_flagOpen;
		return e_ioSuccess;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x450c90
LegoS32 GolFile::Close()
{
	if ((m_flags & c_flagOpen) == 0) {
		return e_ioNotOpen;
	}

	if ((m_flags & c_flagDirty) != 0) {
		FlushWriteBuffer();
	}

	_close(m_fd);
	m_fd = -1;
	return e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x450cd0
LegoS32 GolFile::Seek(LegoS32 p_offset)
{
	if (_lseek(m_fd, p_offset, SEEK_SET) < 0) {
		return e_ioSeekError;
	}

	m_position = p_offset;
	return e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x450d00
LegoS32 GolFile::Read(void* p_buf, LegoU32 p_size, LegoS32* p_lenRead)
{
	LegoS32 result = _read(m_fd, p_buf, p_size);
	*p_lenRead = result;

	if (result < 0) {
		return e_ioReadError;
	}

	return result != 0 ? e_ioSuccess : e_ioEndOfFile;
}

// FUNCTION: LEGORACERS 0x450d40
LegoS32 GolFile::Write(void* p_buf, LegoU32 p_size)
{
	return _write(m_fd, p_buf, p_size) < 0 ? e_ioWriteError : e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x450d70
LegoS32 GolFile::Flush()
{
	_commit(m_fd);
	return e_ioSuccess;
}
