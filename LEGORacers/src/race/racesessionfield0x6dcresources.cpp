#include "decomp.h"
#include "race/racesession.h"

// FUNCTION: LEGORACERS 0x00451a10
void RaceSession::Field0x6dc::Field0x18a0::FUN_00451a10()
{
	VTable0x1c();

	if (m_unk0x1c != NULL && m_unk0xd8 != NULL) {
		(*m_unk0x1c)->VTable0x64(m_unk0xd8);
		m_unk0xd8 = NULL;
		m_unk0x1c = NULL;
	}

	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x004524f0
void RaceSession::Field0x6dc::Field0x189c::FUN_004524f0()
{
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x18 = 0;
	m_unk0x20 = 0;
	m_unk0x64 = 0;
}

// FUNCTION: LEGORACERS 0x00452510
void RaceSession::Field0x6dc::Field0x189c::FUN_00452510()
{
	VTable0x1c();
	FUN_004524f0();
}

// FUNCTION: LEGORACERS 0x00452eb0
void RaceSession::Field0x6dc::Field0x1898::FUN_00452eb0()
{
	VTable0x1c();
	m_unk0x02c.VTable0x54();
	m_unk0x164 = 0;
	m_unk0x168 = 0;
	m_unk0x16c = 0;
	m_unk0x170 = 0;
}

// FUNCTION: LEGORACERS 0x00453d90
void RaceSession::Field0x6dc::Field0x18a4::FUN_00453d90()
{
	VTable0x1c();

	if (m_unk0x01c != NULL && m_unk0x270 != NULL) {
		(*m_unk0x01c)->VTable0x64(m_unk0x270);
		m_unk0x270 = NULL;
		m_unk0x01c = NULL;
	}

	m_unk0x030.VTable0x14();
	m_unk0x004 = 0;
}

// FUNCTION: LEGORACERS 0x00454ab0
void RaceSession::Field0x6dc::Field0x18a8::FUN_00454ab0()
{
	if (m_unk0x238 != NULL) {
		m_unk0x010->FUN_00443c10(m_unk0x238);
		m_unk0x238 = NULL;
	}

	VTable0x1c();

	if (m_unk0x248 != NULL) {
		m_unk0x248->VTable0x50();
		(*m_unk0x01c)->VTable0x64(m_unk0x248);
		m_unk0x248 = NULL;
	}

	m_unk0x030.FUN_00493e60();
	m_unk0x004 = 0;
	m_unk0x244 = 0;
	m_unk0x23c = 0;
}

// FUNCTION: LEGORACERS 0x004557c0
void RaceSession::Field0x6dc::Field0x1890::FUN_004557c0()
{
	VTable0x1c();
	FUN_004557e0();
}

// FUNCTION: LEGORACERS 0x004557e0
void RaceSession::Field0x6dc::Field0x1890::FUN_004557e0()
{
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x38 = 0;
	m_unk0x70 = 0;
	m_unk0x78 = 0;
	m_unk0x7c = 0;
	m_unk0x80 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
}

// FUNCTION: LEGORACERS 0x00456540
void RaceSession::Field0x6dc::Field0x18ac::FUN_00456540()
{
	VTable0x1c();
	m_unk0x004 = 0;
	m_unk0x21c = 0;
}

// FUNCTION: LEGORACERS 0x00457170
void RaceSession::Field0x6dc::Field0x1894::FUN_00457170()
{
	VTable0x1c();
	m_unk0x064.FUN_004149f0();
	m_unk0x180.Clear();
	m_unk0x02c = 0;
	m_unk0x058 = 0;
	m_unk0x05c = 0;
	m_unk0x060 = 0;
	m_unk0x18c = 0;
}

// FUNCTION: LEGORACERS 0x0045bd10
void RaceSession::Field0x6dc::Field0x18b0::FUN_0045bd10()
{
	VTable0x1c();
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x0045c8b0
void RaceSession::Field0x6dc::Field0x18b4::FUN_0045c8b0()
{
	VTable0x1c();
	FUN_0045c8d0();
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x0045c8d0
void RaceSession::Field0x6dc::Field0x18b4::FUN_0045c8d0()
{
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x0045d4b0
void RaceSession::Field0x6dc::Field0x18b8::FUN_0045d4b0()
{
	m_unk0x004 = 0;
	m_unk0x0e0 = 0;
	m_unk0x0a8 = 0;
	m_unk0x0ac = 0;
	m_unk0x0b0 = 0;
	m_unk0x0b4 = 0;
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0c4 = 0;
	m_unk0x0c8 = 0;
	m_unk0x0cc = 0;
	m_unk0x0d0 = 0;
	m_unk0x0d4 = 0;
	m_unk0x0d8 = 0;
	m_unk0x0dc = 0;
}

// FUNCTION: LEGORACERS 0x0045d540
void RaceSession::Field0x6dc::Field0x18b8::FUN_0045d540()
{
	VTable0x1c();
	FUN_0045d4b0();
}
