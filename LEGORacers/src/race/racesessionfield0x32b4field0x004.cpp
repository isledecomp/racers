#include "race/raceeventtable0x90.h"

DECOMP_SIZE_ASSERT(RaceEventTable0x90, 0x90)

// STUB: LEGORACERS 0x0045c660
LegoU32 RaceEventTable0x90::Field0x24::FUN_0045c660(undefined4 p_unk0x04)
{
	LegoU32 i = 0;
	if (m_count > 0) {
		Field0x24Entry* entry = m_entries;
		while (i < m_count) {
			if (entry->m_unk0x0c == p_unk0x04 && (entry->m_flags0x10 & 2)) {
				entry->m_flags0x10 &= ~2;
			}

			i++;
			entry++;
		}
	}

	return m_count;
}

// FUNCTION: LEGORACERS 0x0045ee50
void RaceEventTable0x90::EntryBase::FUN_0045ee50(GolVec3* p_unk0x04)
{
	if (!(m_flags0x1c & 4) && (m_unk0x18 == 1 || m_unk0x18 == 4)) {
		VTable0x04(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x0045ee70
void RaceEventTable0x90::EntryBase::FUN_0045ee70(GolVec3* p_unk0x04)
{
	if (m_flags0x1c & 4) {
		if (m_unk0x18 == 1 || m_unk0x18 == 4) {
			VTable0x04(p_unk0x04);

			if (!(m_flags0x1c & 2)) {
				VTable0x0c();
			}

			return;
		}
	}

	if (m_unk0x18 != 1 && !(m_flags0x1c & 2)) {
		VTable0x0c();
	}
}

// FUNCTION: LEGORACERS 0x00461ef0
LegoU32 RaceEventTable0x90::FUN_00461ef0(undefined4 p_unk0x04, GolVec3* p_unk0x08)
{
	if (m_unk0x5c) {
		for (LegoU32 i = 0; i < m_count0x5c; i++) {
			if (m_unk0x5c[i].m_unk0x14 == p_unk0x04) {
				m_unk0x5c[i].FUN_0045ee50(p_unk0x08);
			}
		}
	}

	if (m_unk0x60) {
		for (LegoU32 i = 0; i < m_count0x60; i++) {
			if (m_unk0x60[i].m_unk0x14 == p_unk0x04) {
				m_unk0x60[i].FUN_0045ee50(p_unk0x08);
			}
		}
	}

	if (m_unk0x64) {
		for (LegoU32 i = 0; i < m_count0x64; i++) {
			if (m_unk0x64[i].m_unk0x14 == p_unk0x04) {
				m_unk0x64[i].FUN_0045ee50(p_unk0x08);
			}
		}
	}

	if (m_unk0x68) {
		for (LegoU32 i = 0; i < m_count0x68; i++) {
			if (m_unk0x68[i].m_unk0x14 == p_unk0x04) {
				m_unk0x68[i].FUN_0045ee50(p_unk0x08);
			}
		}
	}

	if (m_unk0x70) {
		for (LegoU32 i = 0; i < m_count0x70; i++) {
			if (m_unk0x70[i].m_unk0x14 == p_unk0x04) {
				m_unk0x70[i].FUN_0045ee50(p_unk0x08);
			}
		}
	}

	if (m_unk0x74) {
		for (LegoU32 i = 0; i < m_count0x74; i++) {
			if (m_unk0x74[i].m_unk0x14 == p_unk0x04) {
				m_unk0x74[i].FUN_0045ee50(p_unk0x08);
			}

			if (m_unk0x74[i].m_unk0x20 == p_unk0x04) {
				m_unk0x74[i].m_flags0x2c |= 1;
			}
		}
	}

	if (m_unk0x78) {
		for (LegoU32 i = 0; i < m_count0x78; i++) {
			if (m_unk0x78[i].m_unk0x14 == p_unk0x04) {
				m_unk0x78[i].FUN_0045ee50(p_unk0x08);
			}
		}
	}

	if (m_unk0x84) {
		for (LegoU32 i = 0; i < m_count0x84; i++) {
			if (m_unk0x84[i].m_unk0x14 == p_unk0x04) {
				m_unk0x84[i].FUN_0045ee50(p_unk0x08);
			}
		}
	}

	if (m_unk0x6c) {
		for (LegoU32 i = 0; i < m_count0x6c; i++) {
			if (m_unk0x6c[i].m_unk0x00 == p_unk0x04) {
				FUN_00462350(m_unk0x6c[i].m_unk0x04);
			}
		}
	}

	if (m_unk0x8c) {
		for (LegoU32 i = 0; i < m_count0x8c; i++) {
			if (m_unk0x8c[i].m_unk0x30 == p_unk0x04) {
				m_unk0x8c[i].m_flags0x34 |= 1;
			}
		}
	}

	m_unk0x14->FUN_0048aad0(p_unk0x04, p_unk0x08);
	return m_unk0x24->FUN_0045c660(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00462140
void RaceEventTable0x90::FUN_00462140(undefined4 p_unk0x04, GolVec3* p_unk0x08)
{
	if (m_unk0x5c) {
		for (LegoU32 i = 0; i < m_count0x5c; i++) {
			if (m_unk0x5c[i].m_unk0x14 == p_unk0x04) {
				m_unk0x5c[i].FUN_0045ee70(p_unk0x08);
			}
		}
	}

	if (m_unk0x60) {
		for (LegoU32 i = 0; i < m_count0x60; i++) {
			if (m_unk0x60[i].m_unk0x14 == p_unk0x04) {
				m_unk0x60[i].FUN_0045ee70(p_unk0x08);
			}
		}
	}

	if (m_unk0x64) {
		for (LegoU32 i = 0; i < m_count0x64; i++) {
			if (m_unk0x64[i].m_unk0x14 == p_unk0x04) {
				m_unk0x64[i].FUN_0045ee70(p_unk0x08);
			}
		}
	}

	if (m_unk0x68) {
		for (LegoU32 i = 0; i < m_count0x68; i++) {
			if (m_unk0x68[i].m_unk0x14 == p_unk0x04) {
				m_unk0x68[i].FUN_0045ee70(p_unk0x08);
			}
		}
	}

	if (m_unk0x70) {
		for (LegoU32 i = 0; i < m_count0x70; i++) {
			if (m_unk0x70[i].m_unk0x14 == p_unk0x04) {
				m_unk0x70[i].FUN_0045ee70(p_unk0x08);
			}
		}
	}

	if (m_unk0x74) {
		for (LegoU32 i = 0; i < m_count0x74; i++) {
			if (m_unk0x74[i].m_unk0x14 == p_unk0x04) {
				m_unk0x74[i].FUN_0045ee70(p_unk0x08);
			}

			if (m_unk0x74[i].m_unk0x20 == p_unk0x04) {
				m_unk0x74[i].m_flags0x2c &= ~1;
			}
		}
	}

	if (m_unk0x78) {
		for (LegoU32 i = 0; i < m_count0x78; i++) {
			if (m_unk0x78[i].m_unk0x14 == p_unk0x04) {
				m_unk0x78[i].FUN_0045ee70(p_unk0x08);
			}
		}
	}

	if (m_unk0x84) {
		for (LegoU32 i = 0; i < m_count0x84; i++) {
			if (m_unk0x84[i].m_unk0x14 == p_unk0x04) {
				m_unk0x84[i].FUN_0045ee70(p_unk0x08);
			}
		}
	}

	if (m_unk0x8c) {
		for (LegoU32 i = 0; i < m_count0x8c; i++) {
			if (m_unk0x8c[i].m_unk0x30 == p_unk0x04) {
				m_unk0x8c[i].m_flags0x34 &= ~1;
			}
		}
	}

	m_unk0x14->FUN_0048ab20(p_unk0x04, p_unk0x08);
}

// FUNCTION: LEGORACERS 0x00462350
void RaceEventTable0x90::FUN_00462350(undefined4 p_unk0x04)
{
	if (m_unk0x5c) {
		for (LegoU32 i = 0; i < m_count0x5c; i++) {
			if (m_unk0x5c[i].m_unk0x14 == p_unk0x04) {
				m_unk0x5c[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x60) {
		for (LegoU32 i = 0; i < m_count0x60; i++) {
			if (m_unk0x60[i].m_unk0x14 == p_unk0x04) {
				m_unk0x60[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x64) {
		for (LegoU32 i = 0; i < m_count0x64; i++) {
			if (m_unk0x64[i].m_unk0x14 == p_unk0x04) {
				m_unk0x64[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x68) {
		for (LegoU32 i = 0; i < m_count0x68; i++) {
			if (m_unk0x68[i].m_unk0x14 == p_unk0x04) {
				m_unk0x68[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x70) {
		for (LegoU32 i = 0; i < m_count0x70; i++) {
			if (m_unk0x70[i].m_unk0x14 == p_unk0x04) {
				m_unk0x70[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x74) {
		for (LegoU32 i = 0; i < m_count0x74; i++) {
			if (m_unk0x74[i].m_unk0x14 == p_unk0x04) {
				m_unk0x74[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x78) {
		for (LegoU32 i = 0; i < m_count0x78; i++) {
			if (m_unk0x78[i].m_unk0x14 == p_unk0x04) {
				m_unk0x78[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x7c) {
		for (LegoU32 i = 0; i < m_count0x7c; i++) {
			if (m_unk0x7c[i].m_unk0x14 == p_unk0x04) {
				m_unk0x7c[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x80) {
		for (LegoU32 i = 0; i < m_count0x80; i++) {
			if (m_unk0x80[i].m_unk0x14 == p_unk0x04) {
				m_unk0x80[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x84) {
		for (LegoU32 i = 0; i < m_count0x84; i++) {
			if (m_unk0x84[i].m_unk0x14 == p_unk0x04) {
				m_unk0x84[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x88) {
		for (LegoU32 i = 0; i < m_count0x88; i++) {
			if (m_unk0x88[i].m_unk0x14 == p_unk0x04) {
				m_unk0x88[i].m_unk0x18 = 5;
			}
		}
	}

	if (m_unk0x8c) {
		for (LegoU32 i = 0; i < m_count0x8c; i++) {
			if (m_unk0x8c[i].m_unk0x14 == p_unk0x04) {
				m_unk0x8c[i].m_unk0x18 = 5;
			}
		}
	}

	m_unk0x14->FUN_0048ab70(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00462580
void RaceEventTable0x90::FUN_00462580(undefined4 p_unk0x04, undefined4 p_unk0x08, GolVec3* p_unk0x0c)
{
	if (m_unk0x5c) {
		for (LegoU32 i = 0; i < m_count0x5c; i++) {
			if (m_unk0x5c[i].m_unk0x14 == p_unk0x04) {
				m_unk0x5c[i].FUN_0045ee50(p_unk0x0c);
			}

			if (m_unk0x5c[i].m_unk0x14 == p_unk0x08) {
				m_unk0x5c[i].FUN_0045ee70(p_unk0x0c);
			}
		}
	}

	if (m_unk0x60) {
		for (LegoU32 i = 0; i < m_count0x60; i++) {
			if (m_unk0x60[i].m_unk0x14 == p_unk0x04) {
				m_unk0x60[i].FUN_0045ee50(p_unk0x0c);
			}

			if (m_unk0x60[i].m_unk0x14 == p_unk0x08) {
				m_unk0x60[i].FUN_0045ee70(p_unk0x0c);
			}
		}
	}

	if (m_unk0x64) {
		for (LegoU32 i = 0; i < m_count0x64; i++) {
			if (m_unk0x64[i].m_unk0x14 == p_unk0x04) {
				m_unk0x64[i].FUN_0045ee50(p_unk0x0c);
			}

			if (m_unk0x64[i].m_unk0x14 == p_unk0x08) {
				m_unk0x64[i].FUN_0045ee70(p_unk0x0c);
			}
		}
	}

	if (m_unk0x68) {
		for (LegoU32 i = 0; i < m_count0x68; i++) {
			if (m_unk0x68[i].m_unk0x14 == p_unk0x04) {
				m_unk0x68[i].FUN_0045ee50(p_unk0x0c);
			}

			if (m_unk0x68[i].m_unk0x14 == p_unk0x08) {
				m_unk0x68[i].FUN_0045ee70(p_unk0x0c);
			}
		}
	}

	if (m_unk0x70) {
		for (LegoU32 i = 0; i < m_count0x70; i++) {
			if (m_unk0x70[i].m_unk0x14 == p_unk0x04) {
				m_unk0x70[i].FUN_0045ee50(p_unk0x0c);
			}

			if (m_unk0x70[i].m_unk0x14 == p_unk0x08) {
				m_unk0x70[i].FUN_0045ee70(p_unk0x0c);
			}
		}
	}

	if (m_unk0x74) {
		for (LegoU32 i = 0; i < m_count0x74; i++) {
			if (m_unk0x74[i].m_unk0x14 == p_unk0x04) {
				m_unk0x74[i].FUN_0045ee50(p_unk0x0c);
			}

			if (m_unk0x74[i].m_unk0x20 == p_unk0x04) {
				m_unk0x74[i].m_flags0x2c |= 1;
			}

			if (m_unk0x74[i].m_unk0x14 == p_unk0x08) {
				m_unk0x74[i].FUN_0045ee70(p_unk0x0c);
			}

			if (m_unk0x74[i].m_unk0x20 == p_unk0x08) {
				m_unk0x74[i].m_flags0x2c &= ~1;
			}
		}
	}

	if (m_unk0x78) {
		for (LegoU32 i = 0; i < m_count0x78; i++) {
			if (m_unk0x78[i].m_unk0x14 == p_unk0x04) {
				m_unk0x78[i].FUN_0045ee50(p_unk0x0c);
			}

			if (m_unk0x78[i].m_unk0x14 == p_unk0x08) {
				m_unk0x78[i].FUN_0045ee70(p_unk0x0c);
			}
		}
	}

	if (m_unk0x84) {
		for (LegoU32 i = 0; i < m_count0x84; i++) {
			if (m_unk0x84[i].m_unk0x14 == p_unk0x04) {
				m_unk0x84[i].FUN_0045ee50(p_unk0x0c);
			}

			if (m_unk0x84[i].m_unk0x14 == p_unk0x08) {
				m_unk0x84[i].FUN_0045ee70(p_unk0x0c);
			}
		}
	}

	if (m_unk0x6c) {
		for (LegoU32 i = 0; i < m_count0x6c; i++) {
			if (m_unk0x6c[i].m_unk0x00 == p_unk0x04) {
				FUN_00462350(m_unk0x6c[i].m_unk0x04);
			}
		}
	}

	if (m_unk0x8c) {
		for (LegoU32 i = 0; i < m_count0x8c; i++) {
			if (m_unk0x8c[i].m_unk0x30 == p_unk0x04) {
				m_unk0x8c[i].m_flags0x34 |= 1;
			}

			if (m_unk0x8c[i].m_unk0x30 == p_unk0x08) {
				m_unk0x8c[i].m_flags0x34 &= ~1;
			}
		}
	}

	m_unk0x14->FUN_0048abb0(p_unk0x04, p_unk0x08, p_unk0x0c);
}
