#include "decomp.h"
#include "golworldentity.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc, 0x19a4)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x68, 0x68)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x1958Resource, 0x30)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18bc, 0x80)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18bc::Entry, 0x14)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x1890, 0x84)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x1894, 0x190)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x1898, 0x17c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x189c, 0x68)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18a0, 0xe8)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18a4, 0x290)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18a8, 0x24c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18ac, 0x224)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18b0, 0x2c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18b4, 0x34)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x18b8, 0xe4)

// GLOBAL: LEGORACERS 0x004b1874
extern const LegoFloat g_unk0x004b1874 = 0.0040000002f;

// GLOBAL: LEGORACERS 0x004b1878
extern const LegoFloat g_unk0x004b1878 = 6.2831855f;

// GLOBAL: LEGORACERS 0x004c7644
LegoFloat g_unk0x004c7644;

// FUNCTION: LEGORACERS 0x004513f0
RaceSession::Field0x6dc::Field0x18bc::Entry::Entry()
{
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x00451410
RaceSession::Field0x6dc::Field0x18bc::Entry::~Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00451460
void RaceSession::Field0x6dc::Field0x18bc::Entry::Reset()
{
	m_unk0x00.Clear();
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x004515d0
void RaceSession::Field0x6dc::Field0x18bc::Entry::FUN_004515d0(LegoU32 p_elapsedMs)
{
	if (m_unk0x10 == 2) {
		m_unk0x0c->VTable0x10(p_elapsedMs);
		if (m_unk0x0c->FUN_0040e360()) {
			m_unk0x0c->VTable0x54();
			m_unk0x10 = 3;
		}
	}
}

// FUNCTION: LEGORACERS 0x00451610
void RaceSession::Field0x6dc::Field0x18bc::Entry::FUN_00451610(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x10 == 2) {
		p_renderer->VTable0x94(m_unk0x0c);
	}
}

// FUNCTION: LEGORACERS 0x00451630
void RaceSession::Field0x6dc::Field0x18bc::Entry::FUN_00451630()
{
	m_unk0x0c = NULL;
	m_unk0x10 = 1;
}

// FUNCTION: LEGORACERS 0x00451640
RaceSession::Field0x6dc::Field0x18bc::Field0x18bc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004516a0
RaceSession::Field0x6dc::Field0x18bc::~Field0x18bc()
{
	FUN_00451700();
}

// FUNCTION: LEGORACERS 0x00451700
LegoS32 RaceSession::Field0x6dc::Field0x18bc::FUN_00451700()
{
	LegoS32 i;

	for (i = 0; i < sizeOfArray(m_entries); i++) {
		m_entries[i].Reset();
	}

	return Reset();
}

// FUNCTION: LEGORACERS 0x00451730
LegoS32 RaceSession::Field0x6dc::Field0x18bc::Reset()
{
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	m_unk0x6c = 0;
	m_unk0x70 = 0;
	m_unk0x74 = 0;
	m_unk0x78 = 0;
	m_unk0x7c = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x00451860
void RaceSession::Field0x6dc::Field0x18bc::FUN_00451860(LegoU32 p_elapsedMs)
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_004515d0(p_elapsedMs);
		if (entry->GetUnk0x10() == 3) {
			m_unk0x74->FUN_0045ba40(entry->GetUnk0x0c());
			entry->FUN_00451630();
		}

		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004518a0
void RaceSession::Field0x6dc::Field0x18bc::FUN_004518a0(GolD3DRenderDevice* p_renderer)
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_00451610(p_renderer);
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x004518d0
void RaceSession::Field0x6dc::Field0x18bc::FUN_004518d0()
{
	Entry* entry = m_entries;
	LegoS32 i;

	for (i = 5; i != 0; i--) {
		entry->FUN_00451630();
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00457990
RaceSession::Field0x6dc::Field0x6dc()
{
	FUN_00457a90();
}

// FUNCTION: LEGORACERS 0x00457a20
RaceSession::Field0x6dc::~Field0x6dc()
{
	FUN_00459e20();
}

// FUNCTION: LEGORACERS 0x00457a90
void RaceSession::Field0x6dc::FUN_00457a90()
{
	m_unk0x000 = 0;
	m_renderer = NULL;
	m_unk0x028 = NULL;
	m_unk0x030 = NULL;
	m_unk0x034 = 0;
	m_unk0x02c = NULL;
	m_unk0x038 = 0;
	m_unk0x074 = 0;
	m_unk0x068 = 0;
	m_unk0x06c = 0;
	m_unk0x03c = 0;
	m_unk0x040 = 0;
	m_unk0x1958 = 0;
	m_unk0x195c = 0;
	m_unk0x1960 = 0;
	m_unk0x1964 = 0;
	m_unk0x078 = 0;
	m_unk0x07c = 0;
	m_unk0x080 = 0;
	m_unk0x084 = 0;
	m_unk0x088 = 0;
	m_unk0x08c = 0;
	m_unk0x090 = 0;
	m_unk0x094 = 0;
	m_unk0x098 = 0;
	m_unk0x09c = 0;
	m_unk0x0a0 = 0;
	m_unk0x199c = 0;
	m_unk0x19a0 = 0;
	m_unk0x064 = 0;
	m_unk0x070 = 0;
	m_unk0x048 = 0;
	m_unk0x060 = 0;
	m_unk0x1884[0] = 0;
	m_unk0x1884[1] = 0;
	m_unk0x1884[2] = 0;
	m_unk0x1884[3] = 0;
	m_unk0x1884[4] = 0;
	m_unk0x1884[5] = 0;
	m_unk0x1884[6] = 0;
	m_unk0x1884[7] = 0;
	m_unk0x1884[8] = 0;
	m_unk0x1884[9] = 0;
	m_unk0x1884[10] = 0;
	m_unk0x194c = 0;
	m_unk0x194d = 0;
	m_unk0x193c = NULL;
	m_unk0x1940 = NULL;
	m_unk0x1944 = 0;
	m_unk0x1948 = 0;
	m_unk0x1998 = 0;
	m_unk0x1950 = NULL;
	m_unk0x1954 = NULL;
	m_unk0x1890 = 0;
	m_unk0x1894 = 0;
	m_unk0x1898 = 0;
	m_unk0x189c = 0;
	m_unk0x18a0 = 0;
	m_unk0x18a4 = 0;
	m_unk0x18a8 = 0;
	m_unk0x18ac = 0;
	m_unk0x18b0 = 0;
	m_unk0x18b4 = 0;
	m_unk0x18b8 = 0;
	m_unk0x04c = 0;
	m_unk0x050 = 0;
	m_unk0x1878 = 0;
	m_unk0x187c = 0;
	m_unk0x054 = 0;
	m_unk0x1968 = 0;
	m_unk0x196c = 0;
	m_unk0x1970 = 0;
	m_unk0x1974 = 0;

	undefined4* entry = m_unk0x1978;
	LegoS32 count;
	for (count = 8; count != 0; count--) {
		*entry = 0;
		entry++;
	}
}

// FUNCTION: LEGORACERS 0x00459e20
void RaceSession::Field0x6dc::FUN_00459e20()
{
	if (m_unk0x1964 != NULL) {
		m_unk0x03c->FUN_00443c10(m_unk0x1964);
		m_unk0x1964 = NULL;
	}

	if (m_unk0x1960 != NULL) {
		m_unk0x03c->FUN_00443c10(m_unk0x1960);
		m_unk0x1960 = NULL;
	}

	if (m_unk0x195c != NULL) {
		m_unk0x03c->FUN_00443c10(m_unk0x195c);
		m_unk0x195c = NULL;
	}

	if (m_unk0x1958 != NULL) {
		m_unk0x03c->FUN_00443c10(m_unk0x1958);
		m_unk0x1958 = NULL;
	}

	m_unk0x008.Clear();

	if (m_unk0x1954 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x194d; i++) {
			m_unk0x1954[i].FUN_004214b0();
		}

		if (m_unk0x1954 != NULL) {
			m_unk0x1954->VTable0x04(3);
		}
		m_unk0x1954 = NULL;
	}

	if (m_unk0x1950 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x194c; i++) {
			m_unk0x1950[i].FUN_004214b0();
		}

		if (m_unk0x1950 != NULL) {
			m_unk0x1950->VTable0x04(3);
		}
		m_unk0x1950 = NULL;
	}

	if (m_unk0x18b8 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[10]; i++) {
			m_unk0x18b8[i].FUN_0045d540();
		}

		if (m_unk0x18b8 != NULL) {
			m_unk0x18b8->VTable0x04(3);
		}
		m_unk0x18b8 = NULL;
	}

	if (m_unk0x18b4 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[9]; i++) {
			m_unk0x18b4[i].FUN_0045c8b0();
		}

		if (m_unk0x18b4 != NULL) {
			m_unk0x18b4->VTable0x04(3);
		}
		m_unk0x18b4 = NULL;
	}

	if (m_unk0x18b0 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[8]; i++) {
			m_unk0x18b0[i].FUN_0045bd10();
		}

		if (m_unk0x18b0 != NULL) {
			m_unk0x18b0->VTable0x04(3);
		}
		m_unk0x18b0 = NULL;
	}

	if (m_unk0x18ac != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[7]; i++) {
			m_unk0x18ac[i].FUN_00456540();
		}

		if (m_unk0x18ac != NULL) {
			m_unk0x18ac->VTable0x04(3);
		}
		m_unk0x18ac = NULL;
	}

	if (m_unk0x18a8 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[6]; i++) {
			m_unk0x18a8[i].FUN_00454ab0();
		}

		if (m_unk0x18a8 != NULL) {
			m_unk0x18a8->VTable0x04(3);
		}
		m_unk0x18a8 = NULL;
	}

	if (m_unk0x18a4 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[5]; i++) {
			m_unk0x18a4[i].FUN_00453d90();
		}

		if (m_unk0x18a4 != NULL) {
			m_unk0x18a4->VTable0x04(3);
		}
		m_unk0x18a4 = NULL;
	}

	if (m_unk0x18a0 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[4]; i++) {
			m_unk0x18a0[i].FUN_00451a10();
		}

		if (m_unk0x18a0 != NULL) {
			m_unk0x18a0->VTable0x04(3);
		}
		m_unk0x18a0 = NULL;
	}

	if (m_unk0x189c != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[3]; i++) {
			m_unk0x189c[i].FUN_00452510();
		}

		if (m_unk0x189c != NULL) {
			m_unk0x189c->VTable0x04(3);
		}
		m_unk0x189c = NULL;
	}

	if (m_unk0x1898 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[2]; i++) {
			m_unk0x1898[i].FUN_00452eb0();
		}

		if (m_unk0x1898 != NULL) {
			m_unk0x1898->VTable0x04(3);
		}
		m_unk0x1898 = NULL;
	}

	if (m_unk0x1894 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[1]; i++) {
			m_unk0x1894[i].FUN_00457170();
		}

		if (m_unk0x1894 != NULL) {
			m_unk0x1894->VTable0x04(3);
		}
		m_unk0x1894 = NULL;
	}

	if (m_unk0x1890 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x1884[0]; i++) {
			m_unk0x1890[i].FUN_004557c0();
		}

		if (m_unk0x1890 != NULL) {
			m_unk0x1890->VTable0x04(3);
		}
		m_unk0x1890 = NULL;
	}

	if (m_unk0x000 != NULL && m_unk0x05c != 0) {
		m_unk0x000->VTable0x3c(m_unk0x05c);
		m_unk0x05c = 0;
	}

	m_unk0x014.VTable0x08();
	m_unk0x060 = 0;

	if (m_unk0x000 != NULL && m_unk0x064 != 0) {
		m_unk0x000->VTable0x3c(m_unk0x064);
		m_unk0x064 = 0;
	}

	if (m_unk0x030 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x034 + m_unk0x038; i++) {
			if (m_unk0x030[i] != NULL) {
				m_unk0x030[i]->ClearUnk0x24();
			}
		}

		delete[] m_unk0x030;
		m_unk0x030 = NULL;
	}

	if (m_unk0x02c != NULL) {
		m_unk0x02c->VTable0x08(3);
		m_unk0x02c = NULL;
	}

	if (m_unk0x028 != NULL) {
		m_unk0x028->VTable0x08(3);
		m_unk0x028 = NULL;
	}

	LegoS32 i;
	for (i = 25; i != 0; i--) {
		m_unk0x0a4[25 - i].VTable0x54();
	}

	FUN_00457a90();
}

// FUNCTION: LEGORACERS 0x0045a3f0
void RaceSession::Field0x6dc::FUN_0045a3f0(LegoU32 p_elapsedMs)
{
	if (m_unk0x1968 != NULL) {
		m_unk0x1968->VTable0x10(p_elapsedMs);
	}
	if (m_unk0x196c != NULL) {
		m_unk0x196c->VTable0x10(p_elapsedMs);
	}
	if (m_unk0x1970 != NULL) {
		m_unk0x1970->VTable0x10(p_elapsedMs);
	}
	if (m_unk0x1974 != NULL) {
		m_unk0x1974->VTable0x10(p_elapsedMs);
	}

	if (m_unk0x028 != NULL) {
		LegoU32 i;

		for (i = 0; i < m_unk0x034; i++) {
			m_unk0x028[i].FUN_00457710(p_elapsedMs);
		}

		for (i = 0; i < m_unk0x038; i++) {
			m_unk0x02c[i].FUN_00453690(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x0045a490
void RaceSession::Field0x6dc::FUN_0045a490(LegoU32 p_elapsedMs)
{
	FUN_0045a3f0(p_elapsedMs);

	m_unk0x199c += static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * g_unk0x004b1874;
	if (m_unk0x199c > g_unk0x004b1878) {
		m_unk0x199c -= g_unk0x004b1878;
	}

	Field0x1880* node0x1880;
	for (node0x1880 = m_unk0x1880; node0x1880 != NULL; node0x1880 = node0x1880->GetNext()) {
		node0x1880->VTable0x08(p_elapsedMs);
	}

	Field0x270* node0x270;
	for (node0x270 = m_unk0x193c; node0x270 != NULL; node0x270 = node0x270->GetNext()) {
		node0x270->FUN_004217d0(p_elapsedMs);
	}

	for (node0x270 = m_unk0x1940; node0x270 != NULL; node0x270 = node0x270->GetNext()) {
		node0x270->FUN_004217d0(p_elapsedMs);
	}

	m_unk0x18bc.FUN_00451860(p_elapsedMs);

	node0x1880 = m_unk0x1880;
	Field0x1880* previous0x1880 = NULL;
	while (node0x1880 != NULL) {
		Field0x1880* next0x1880 = node0x1880->GetNext();
		if (node0x1880->GetUnk0x04() == 6) {
			if (previous0x1880 == NULL) {
				m_unk0x1880 = next0x1880;
			}
			else {
				previous0x1880->SetNext(next0x1880);
			}

			node0x1880->VTable0x1c();

			switch (node0x1880->VTable0x18()) {
			case 1:
				switch (node0x1880->GetState()) {
				case 0:
					node0x1880->SetNext(m_unk0x088);
					m_unk0x088 = node0x1880;
					break;
				case 1:
					node0x1880->SetNext(m_unk0x08c);
					m_unk0x08c = node0x1880;
					break;
				case 2:
					node0x1880->SetNext(m_unk0x090);
					m_unk0x090 = node0x1880;
					break;
				case 3:
					node0x1880->SetNext(m_unk0x094);
					m_unk0x094 = node0x1880;
					break;
				}
				break;
			case 4:
				switch (node0x1880->GetState()) {
				case 0:
					node0x1880->SetNext(m_unk0x07c);
					m_unk0x07c = node0x1880;
					break;
				case 1:
					node0x1880->SetNext(m_unk0x080);
					m_unk0x080 = node0x1880;
					break;
				case 2:
					node0x1880->SetNext(m_unk0x078);
					m_unk0x078 = node0x1880;
					break;
				case 3:
					node0x1880->SetNext(m_unk0x084);
					m_unk0x084 = node0x1880;
					break;
				}
				break;
			case 2:
				node0x1880->SetNext(m_unk0x098);
				m_unk0x098 = node0x1880;
				break;
			case 3:
				if (node0x1880->GetState() > 2) {
					if (node0x1880->GetState() == 3) {
						node0x1880->SetNext(m_unk0x0a0);
						m_unk0x0a0 = node0x1880;
					}
				}
				else {
					node0x1880->SetNext(m_unk0x09c);
					m_unk0x09c = node0x1880;
				}
				break;
			}
		}
		else {
			previous0x1880 = node0x1880;
		}

		node0x1880 = next0x1880;
	}

	node0x270 = m_unk0x193c;
	Field0x270* previous0x270 = NULL;
	while (node0x270 != NULL) {
		Field0x270* next0x270 = node0x270->GetNext();
		if (node0x270->GetUnk0x04() == 1) {
			if (previous0x270 == NULL) {
				m_unk0x193c = next0x270;
			}
			else {
				previous0x270->SetNext(next0x270);
			}

			node0x270->SetNext(m_unk0x1944);
			m_unk0x1944 = node0x270;
		}
		else {
			previous0x270 = node0x270;
		}

		node0x270 = next0x270;
	}

	node0x270 = m_unk0x1940;
	previous0x270 = NULL;
	while (node0x270 != NULL) {
		Field0x270* next0x270 = node0x270->GetNext();
		if (node0x270->GetUnk0x04() == 1) {
			if (previous0x270 == NULL) {
				m_unk0x1940 = next0x270;
			}
			else {
				previous0x270->SetNext(next0x270);
			}

			node0x270->SetNext(m_unk0x1948);
			m_unk0x1948 = node0x270;
		}
		else {
			previous0x270 = node0x270;
		}

		node0x270 = next0x270;
	}

	if (m_unk0x060 != NULL) {
		m_unk0x060->FUN_00416090(p_elapsedMs);
	}

	if (m_unk0x1958 != NULL) {
		FUN_0045b7a0(m_unk0x1958, 0, 3);
	}
	if (m_unk0x195c != NULL) {
		FUN_0045b7a0(m_unk0x195c, 3, 3);
	}
	if (m_unk0x1960 != NULL) {
		FUN_0045b7a0(m_unk0x1960, 1, 3);
	}
	if (m_unk0x1964 != NULL) {
		FUN_0045b7a0(m_unk0x1964, 1, 4);
	}
}

// FUNCTION: LEGORACERS 0x0045a7b0
void RaceSession::Field0x6dc::FUN_0045a7b0(LegoBool32 p_unk0x04)
{
	if (!p_unk0x04) {
		LegoU32 i;

		for (i = 0; i < m_unk0x034; i++) {
			m_unk0x028[i].VTable0x10(m_renderer);
		}

		for (i = 0; i < m_unk0x038; i++) {
			m_unk0x02c[i].VTable0x10(m_renderer);
		}
	}

	Field0x1880* node0x1880 = m_unk0x1880;
	while (node0x1880 != NULL) {
		if (!p_unk0x04 || (node0x1880->VTable0x18() == 3 && node0x1880->GetState() == 3)) {
			node0x1880->VTable0x0c(m_renderer);
		}

		node0x1880 = node0x1880->GetNext();
	}

	if (!p_unk0x04) {
		Field0x270* node0x193c = m_unk0x193c;
		while (node0x193c != NULL) {
			node0x193c->FUN_004513d0(m_renderer);
			node0x193c = node0x193c->GetNext();
		}

		Field0x270* node0x1940 = m_unk0x1940;
		while (node0x1940 != NULL) {
			node0x1940->FUN_004513d0(m_renderer);
			node0x1940 = node0x1940->GetNext();
		}
	}

	m_unk0x18bc.FUN_004518a0(m_renderer);
}

// FUNCTION: LEGORACERS 0x0045a8a0
void RaceSession::Field0x6dc::FUN_0045a8a0()
{
	LegoU32 i;

	for (i = 0; i < m_unk0x034; i++) {
		m_unk0x028[i].VTable0x14(m_renderer);
	}

	for (i = 0; i < m_unk0x038; i++) {
		m_unk0x02c[i].VTable0x14(m_renderer);
	}

	Field0x1880* node0x1880 = m_unk0x1880;
	while (node0x1880 != NULL) {
		node0x1880->VTable0x10(m_renderer);
		node0x1880 = node0x1880->GetNext();
	}

	Field0x270* node0x193c = m_unk0x193c;
	while (node0x193c != NULL) {
		node0x193c->FUN_00421ae0(m_renderer);
		node0x193c = node0x193c->GetNext();
	}

	Field0x270* node0x1940 = m_unk0x1940;
	while (node0x1940 != NULL) {
		node0x1940->FUN_00421ae0(m_renderer);
		node0x1940 = node0x1940->GetNext();
	}
}

// FUNCTION: LEGORACERS 0x0045b740
void RaceSession::Field0x6dc::FUN_0045b740(RaceState::Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x1884[10]; i++) {
		Field0x18b8* item = &m_unk0x18b8[i];
		if (item->m_unk0x0a8 == p_racer) {
			if (item->m_unk0x004 == 2) {
				item->m_unk0x004 = 6;
			}
			else if (item->m_unk0x004 == 3) {
				item->m_unk0x008 = 0;
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b7a0
void RaceSession::Field0x6dc::FUN_0045b7a0(Field0x1958Resource* p_resource, LegoU32 p_unk0x08, LegoS32 p_unk0x0c)
{
	Field0x074::Field0x170* field = m_unk0x074->GetUnk0x170();
	if (field == NULL) {
		if (p_resource->VTable0x0c()) {
			p_resource->VTable0x08();
		}
		return;
	}

	Field0x1880* nearest = NULL;
	LegoFloat nearestDistanceSquared = FLT_MAX;
	GolVec3 referencePosition;
	GolVec3 position;
	GolVec3 direction;

	field->GetUnk0x5c()->VTable0x04(&referencePosition);

	for (Field0x1880* node = m_unk0x1880; node != NULL; node = node->GetNext()) {
		if (node->VTable0x18() == 1 && node->GetState() == p_unk0x08 && node->GetUnk0x04() == p_unk0x0c) {
			node->VTable0x24(&position);

			LegoFloat dx = referencePosition.m_x - position.m_x;
			LegoFloat dy = referencePosition.m_y - position.m_y;
			LegoFloat dz = referencePosition.m_z - position.m_z;
			LegoFloat distanceSquared = dz * dz + dy * dy + dx * dx;
			if (distanceSquared < nearestDistanceSquared) {
				nearestDistanceSquared = distanceSquared;
				nearest = node;
			}
		}
	}

	if (nearestDistanceSquared < g_unk0x004c7644) {
		if (!p_resource->VTable0x0c()) {
			p_resource->VTable0x04(1);
		}

		nearest->VTable0x24(&referencePosition);
		nearest->VTable0x28(&direction);

		p_resource->m_unk0x18 = referencePosition;
		p_resource->m_unk0x24.m_x = direction.m_x;
		p_resource->m_unk0x24.m_y = direction.m_y;
		p_resource->m_unk0x24.m_z = direction.m_z;
	}
	else if (p_resource->VTable0x0c()) {
		p_resource->VTable0x08();
	}
}

// FUNCTION: LEGORACERS 0x0045b900
void RaceSession::Field0x6dc::FUN_0045b900()
{
	LegoU32 i;

	for (i = 0; i < m_unk0x034; i++) {
		m_unk0x028[i].SetFlags0x50Bit0();
	}

	for (i = 0; i < m_unk0x038; i++) {
		m_unk0x02c[i].SetFlags0x50Bit0();
	}
}

// FUNCTION: LEGORACERS 0x0045ba40
LegoU32 RaceSession::Field0x6dc::FUN_0045ba40(GolAnimatedEntity* p_entity)
{
	LegoS32 index = p_entity - m_unk0x0a4;

	m_unk0x1878 &= ~(1 << index);
	m_unk0x187c--;

	return m_unk0x187c;
}

// FUNCTION: LEGORACERS 0x0045bb30
void RaceSession::Field0x6dc::FUN_0045bb30()
{
	LegoU32 i;

	for (i = 0; i < m_unk0x034; i++) {
		m_unk0x028[i].VTable0x0c();
	}

	for (i = 0; i < m_unk0x038; i++) {
		m_unk0x02c[i].VTable0x0c();
	}

	Field0x270* node0x193c = m_unk0x193c;
	while (node0x193c != NULL) {
		node0x193c->FUN_004217b0();
		node0x193c = node0x193c->GetNext();
	}

	Field0x270* node0x1940 = m_unk0x1940;
	while (node0x1940 != NULL) {
		node0x1940->FUN_004217b0();
		node0x1940 = node0x1940->GetNext();
	}

	m_unk0x18bc.FUN_004518d0();

	Field0x1880* node0x1880 = m_unk0x1880;
	while (node0x1880 != NULL) {
		node0x1880->SetUnk0x04(6);
		node0x1880 = node0x1880->GetNext();
	}

	FUN_0045a490(0);
}
