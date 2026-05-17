#include "peridottrace0x4e0.h"

DECOMP_SIZE_ASSERT(PeridotTraceActionFile0x30, 0x30)
DECOMP_SIZE_ASSERT(PeridotTraceActionBase0x34, 0x34)
DECOMP_SIZE_ASSERT(PeridotTraceAction0x34, 0x34)

// FUNCTION: LEGORACERS 0x0044e0a0
PeridotTraceActionFile0x30::~PeridotTraceActionFile0x30()
{
	if (m_buffer) {
		delete[] m_buffer;
		m_buffer = NULL;
	}

	Dispose();
}

// STUB: LEGORACERS 0x0044e130
LegoS32 PeridotTraceActionFile0x30::BufferedOpen(const LegoChar* p_fileName, LegoS32 p_mode, LegoU32 p_bufferSize)
{
	STUB(0x0044e130);
	return GolStream::BufferedOpen(p_fileName, p_mode, p_bufferSize);
}

// FUNCTION: LEGORACERS 0x0044e1e0
LegoS32 PeridotTraceActionFile0x30::Dispose()
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
PeridotTraceActionBase0x34::PeridotTraceActionBase0x34()
{
	m_unk0x30 = 0;
}
