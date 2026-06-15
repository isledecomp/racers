#include "decomp.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc, 0x19a4)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x68, 0x68)
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

// FUNCTION: LEGORACERS 0x00451610
void RaceSession::Field0x6dc::Field0x18bc::Entry::FUN_00451610(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x10 == 2) {
		p_renderer->VTable0x94(m_unk0x0c);
	}
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
	m_unk0x1978[0] = 0;
	m_unk0x1978[1] = 0;
	m_unk0x1978[2] = 0;
	m_unk0x1978[3] = 0;
	m_unk0x1978[4] = 0;
	m_unk0x1978[5] = 0;
	m_unk0x1978[6] = 0;
	m_unk0x1978[7] = 0;
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

// STUB: LEGORACERS 0x0045a490
void RaceSession::Field0x6dc::FUN_0045a490(LegoU32)
{
	STUB(0x0045a490);
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

// STUB: LEGORACERS 0x0045b740
void RaceSession::Field0x6dc::FUN_0045b740(RaceState::Racer*)
{
	STUB(0x0045b740);
}

// STUB: LEGORACERS 0x0045b900
void RaceSession::Field0x6dc::FUN_0045b900()
{
	STUB(0x0045b900);
}
