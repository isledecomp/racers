#include "crimsonray0x20.h"

DECOMP_SIZE_ASSERT(OpalStar0x20, 0x20)
DECOMP_SIZE_ASSERT(CrimsonRay0x20, 0x20)

// FUNCTION: LEGORACERS 0x41c010
CrimsonRay0x20::CrimsonRay0x20()
{
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x41c070
CrimsonRay0x20::~CrimsonRay0x20()
{
	if (m_unk0x10) {
		m_next->m_prev = m_prev;
		m_prev->m_next = m_next;
	}
}
