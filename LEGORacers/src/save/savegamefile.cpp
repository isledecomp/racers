#include "save/savegame.h"

DECOMP_SIZE_ASSERT(SaveGameFile, 0x30)
DECOMP_SIZE_ASSERT(MemoryCardFileBase, 0x34)
DECOMP_SIZE_ASSERT(MemoryCardFile, 0x34)

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

// FUNCTION: LEGORACERS 0x00450e30
MemoryCardFileBase::MemoryCardFileBase()
{
	m_unk0x30 = 0;
}
