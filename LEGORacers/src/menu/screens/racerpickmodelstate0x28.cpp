#include "menu/screens/racerpickmodelstate0x28.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerPickModelState0x28, 0x28)

// FUNCTION: LEGORACERS 0x00442e20
RacerPickModelState0x28::RacerPickModelState0x28()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00442e30
void RacerPickModelState0x28::Reset()
{
	m_unk0x00 = 0;

	::memset(m_unk0x04, 0, sizeof(m_unk0x04));
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
}

// FUNCTION: LEGORACERS 0x00442fe0
PeridotTraceBase0x24::Record* RacerPickModelState0x28::FUN_00442fe0()
{
	LegoU32 count = m_unk0x20;
	if (count == 0) {
		return NULL;
	}

	LegoU32 startIndex = m_unk0x18;
	m_unk0x1c++;

	if (m_unk0x1c >= m_unk0x04[m_unk0x18]->GetUnk0x00()) {
		m_unk0x1c = 0;

		for (;;) {
			m_unk0x18++;
			if (m_unk0x18 >= count) {
				m_unk0x18 = 0;
			}

			if (m_unk0x04[m_unk0x18]->GetUnk0x00()) {
				break;
			}

			if (m_unk0x18 == startIndex) {
				return NULL;
			}
		}
	}

	return m_unk0x04[m_unk0x18]->FUN_0042b990(m_unk0x1c);
}

// FUNCTION: LEGORACERS 0x00443050
PeridotTraceBase0x24::Record* RacerPickModelState0x28::FUN_00443050()
{
	LegoU32 count = m_unk0x20;
	if (count == 0) {
		return NULL;
	}

	LegoU32 startIndex = m_unk0x18;
	if (m_unk0x1c == 0) {
		do {
			if (m_unk0x18 == 0) {
				m_unk0x18 = count;
			}

			m_unk0x18--;
			m_unk0x1c = m_unk0x04[m_unk0x18]->GetUnk0x00();
			if (m_unk0x1c != 0) {
				break;
			}
		} while (m_unk0x18 != startIndex);

		if (m_unk0x1c == 0) {
			return NULL;
		}
	}

	m_unk0x1c--;
	return m_unk0x04[m_unk0x18]->FUN_0042b990(m_unk0x1c);
}

// FUNCTION: LEGORACERS 0x004430b0
PeridotTraceBase0x24::Record* RacerPickModelState0x28::FUN_004430b0()
{
	if (m_unk0x20 == 0) {
		return NULL;
	}

	PeridotTraceBase0x24* trace = m_unk0x04[m_unk0x18];
	if (m_unk0x1c >= trace->GetUnk0x00()) {
		return NULL;
	}

	return trace->FUN_0042b990(m_unk0x1c);
}
