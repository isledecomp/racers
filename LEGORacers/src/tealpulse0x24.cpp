#include "tealpulse0x24.h"

#include "decomp.h"
#include "golerror.h"

#include <string.h>
#include <windows.h>

DECOMP_SIZE_ASSERT(TealPulse0x24, 0x24)

// FUNCTION: LEGORACERS 0x0044c570
TealPulse0x24::TealPulse0x24()
{
	m_unk0x04 = 0;
	FUN_0044c5a0();
}

// FUNCTION: LEGORACERS 0x0044c590
TealPulse0x24::~TealPulse0x24()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x0044c5a0
void TealPulse0x24::FUN_0044c5a0()
{
	m_unk0x20 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x1c = 0;
}

// FUNCTION: LEGORACERS 0x0044c5c0
LegoS32 TealPulse0x24::VTable0x08(LegoS32 p_unk0x14, LegoU32 p_unk0x18)
{
	if (m_unk0x20) {
		VTable0x0c();
	}

	m_unk0x14 = p_unk0x14;
	m_unk0x18 = p_unk0x18;
	m_unk0x08 = new Entry*[p_unk0x14];
	m_unk0x0c = new LegoChar[p_unk0x18];
	m_unk0x04 = CreateMutexA(NULL, FALSE, NULL);

	if (!m_unk0x08 || !m_unk0x0c) {
		GolFatalError(c_golErrorOutOfMemory, 0, 0);
	}

	memset(m_unk0x08, 0, 4 * p_unk0x14);
	memset(m_unk0x0c, 0, p_unk0x18);
	m_unk0x10 = m_unk0x0c;
	m_unk0x20 = 1;
	return 1;
}

// FUNCTION: LEGORACERS 0x0044c670
LegoS32 TealPulse0x24::VTable0x0c()
{
	if (m_unk0x20) {
		WaitForSingleObject(m_unk0x04, INFINITE);

		if (m_unk0x08) {
			VTable0x00();
			delete[] m_unk0x08;
		}

		if (m_unk0x0c) {
			delete[] m_unk0x0c;
		}

		FUN_0044c5a0();
		ReleaseMutex(m_unk0x04);
		CloseHandle(m_unk0x04);
		m_unk0x04 = NULL;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0044c6e0
void TealPulse0x24::VTable0x00()
{
	WaitForSingleObject(m_unk0x04, INFINITE);

	for (LegoS32 i = 0; i < m_unk0x14; i++) {
		Entry* entry = m_unk0x08[i];

		if (entry) {
			do {
				Entry* next = entry->m_next;
				delete entry;
				entry = next;
			} while (entry);

			m_unk0x08[i] = NULL;
		}
	}

	ReleaseMutex(m_unk0x04);
}

// FUNCTION: LEGORACERS 0x0044c880
TealPulse0x24::Entry* TealPulse0x24::VTable0x04(Entry** p_bucket, const LegoChar* p_string)
{
	Entry* entry = new Entry;

	if (!entry) {
		GolFatalError(c_golErrorOutOfMemory, 0, 0);
	}

	entry->m_data = m_unk0x10;

	if (*p_bucket) {
		entry->m_next = *p_bucket;
	}
	else {
		entry->m_next = NULL;
	}

	*p_bucket = entry;
	strcpy(m_unk0x10, p_string);
	m_unk0x10 += strlen(p_string) + 1;
	return entry;
}
