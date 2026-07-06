#include "save/savegamefile.h"

DECOMP_SIZE_ASSERT(SaveGameFile, 0x30)

// FUNCTION: LEGORACERS 0x0044e0a0
SaveGameFile::~SaveGameFile()
{
	if (m_buffer) {
		delete[] m_buffer;
		m_buffer = NULL;
	}

	Dispose();
}

// FUNCTION: LEGORACERS 0x0044e130
LegoS32 SaveGameFile::BufferedOpen(const LegoChar*, LegoS32, LegoU32)
{
	return e_ioFileNotFound;
}

// FUNCTION: LEGORACERS 0x0044e140
LegoS32 SaveGameFile::BufferedOpenSlotFile(
	SaveSlot* p_slot,
	const LegoChar* p_fileName,
	LegoS32 p_mode,
	LegoU32 p_bufferSize,
	undefined4 p_createSize
)
{
	m_mode = p_mode;
	m_flags = 0;
	m_unk0x10 = 0;
	m_bufferStart = 0;
	m_bufferEnd = 0;
	m_position = 0;

	LegoS32 result = OpenSlotFile(p_slot, p_fileName, p_createSize);
	if (result != e_ioSuccess) {
		return result;
	}

	m_flags = c_flagOpen;
	if ((p_mode & c_modeKeepBuffer) && m_buffer) {
		return e_ioSuccess;
	}

	if (m_buffer) {
		delete[] m_buffer;
		m_buffer = NULL;
	}

	if (p_bufferSize) {
		p_bufferSize += p_bufferSize & 1;
		m_buffer = new LegoU8[p_bufferSize];
		if (!m_buffer) {
			Dispose();
			return e_ioOutOfMemory;
		}
	}

	m_bufferCapacity = p_bufferSize;
	return e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x0044e1e0
LegoS32 SaveGameFile::Dispose()
{
	if (!(m_mode & c_modeKeepBuffer) && m_buffer) {
		delete[] m_buffer;
		m_buffer = NULL;
	}

	LegoS32 result = Close();

	m_bufferStart = 0;
	m_bufferEnd = 0;
	m_mode = 0;
	m_flags = 0;
	return result;
}
