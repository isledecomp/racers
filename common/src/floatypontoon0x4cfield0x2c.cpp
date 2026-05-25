#include "floatypontoon0x4c.h"
#include "golerror.h"

#include <string.h>

// FUNCTION: LEGORACERS 0x004a00b0 FOLDED
// FUNCTION: GOLDP 0x10025de0 FOLDED
FloatyPontoon0x4c::Field0x2c::Field0x2c()
{
	m_renderer = NULL;
	m_count = 0;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x004105c0 FOLDED
// FUNCTION: GOLDP 0x100260d0 FOLDED
FloatyPontoon0x4c::Field0x2c::~Field0x2c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004105d0
// FUNCTION: GOLDP 0x10025df0 FOLDED
void FloatyPontoon0x4c::Field0x2c::Initialize(WhiteFalcon0x140* p_renderer, LegoU32 p_count)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	m_count = p_count;
	m_entries = new void*[p_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_entries, 0, sizeof(*m_entries) * m_count);
}

// FUNCTION: LEGORACERS 0x00410630
// FUNCTION: GOLDP 0x100260d0 FOLDED
void FloatyPontoon0x4c::Field0x2c::Clear()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_renderer = NULL;
	m_count = 0;
}
