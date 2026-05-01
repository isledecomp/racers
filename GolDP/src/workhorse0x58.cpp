#include "workhorse0x58.h"

#include "golcpu.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(WorkHorse0x58, 0x58)

// FUNCTION: GOLDP 0x100416a0
WorkHorse0x58::WorkHorse0x58()
{
	DetectCPU();
	m_unk0x4c = 0;
	m_unk0x44 = NULL;
	m_unk0x54 = 0;
}

// FUNCTION: GOLDP 0x10041770
WorkHorse0x58::~WorkHorse0x58()
{
	m_unk0x54 = 0;
	if (m_unk0x44 != NULL) {
		delete m_unk0x44;
		m_unk0x44 = NULL;
	}
}
