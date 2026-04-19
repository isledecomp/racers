#include "ceruleansubject0x0c.h"

#include "golerror.h"

#include <memory.h>

DECOMP_SIZE_ASSERT(CeruleanSubject0x0c, 0x0c)

// FUNCTION: LEGORACERS 0x004117b0
CeruleanSubject0x0c::CeruleanSubject0x0c()
{
	m_unk0x04 = NULL;
	m_unk0x08 = 0;
}

// FUNCTION: LEGORACERS 0x004117f0
CeruleanSubject0x0c::~CeruleanSubject0x0c()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00411800
void CeruleanSubject0x0c::VTable0x04(undefined4 p_param)
{
	m_unk0x08 = p_param;
	m_unk0x04 = new undefined[12 * p_param];
	if (!m_unk0x04) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	memset(m_unk0x04, 0, 12 * m_unk0x08);
}

// FUNCTION: LEGORACERS 0x00411850
void CeruleanSubject0x0c::VTable0x08()
{
	if (m_unk0x04) {
		delete[] m_unk0x04;
		m_unk0x04 = NULL;
	}
}
