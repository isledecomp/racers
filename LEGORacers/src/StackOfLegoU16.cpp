#include "stackoflegou16.h"

#include "golerror.h"

DECOMP_SIZE_ASSERT(StackOfLegoU16, 0x0c)

// FUNCTION: LEGORACERS 0x0047f9d0
StackOfLegoU16::StackOfLegoU16()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047f9e0
StackOfLegoU16::~StackOfLegoU16()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0047f9f0
LegoS32 StackOfLegoU16::Reset()
{
	m_size = 0;
	m_capacity = 0;
	m_buffer = NULL;
	return 0;
}

// FUNCTION: LEGORACERS 0x0047fa00
LegoBool32 StackOfLegoU16::Allocate(LegoS32 p_size)
{
	Clear();
	m_capacity = p_size;
	m_buffer = new LegoU16[p_size];

	if (!m_buffer) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047fa40
LegoBool32 StackOfLegoU16::Clear()
{
	if (m_buffer) {
		delete[] m_buffer;
		Reset();
	}

	return m_buffer == 0;
}

// FUNCTION: LEGORACERS 0x0047fa70
LegoBool32 StackOfLegoU16::Push(LegoU16 p_value)
{
	if (m_size != m_capacity) {
		m_buffer[m_size] = p_value;
		m_size++;
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0047faa0
LegoU16 StackOfLegoU16::Pop()
{
	if (m_size != 0) {
		return m_buffer[m_size-- - 1];
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0047fac0
LegoU16 StackOfLegoU16::Peek()
{
	if (m_size) {
		return m_buffer[m_size - 1];
	}

	return 0;
}
