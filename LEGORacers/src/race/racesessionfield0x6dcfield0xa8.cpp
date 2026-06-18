#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0xa8, 0xa8)

// FUNCTION: LEGORACERS 0x00430ca0
RaceSession::Field0x6dc::Field0xa8::Field0xa8()
{
	Reset();
}

// STUB: LEGORACERS 0x00430cc0
RaceSession::Field0x6dc::Field0xa8* RaceSession::Field0x6dc::Field0xa8::VTable0x10(undefined4 p_flags)
{
	Field0xa8* result = this;
	this->~Field0xa8();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// STUB: LEGORACERS 0x00430ce0
RaceSession::Field0x6dc::Field0xa8::~Field0xa8()
{
	VTable0x14();
}

// FUNCTION: LEGORACERS 0x00430cf0
void RaceSession::Field0x6dc::Field0xa8::Reset()
{
	m_unk0x048 = 5.0f;
	m_unk0x004 = 0;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0x010 = 0;
	m_unk0x014 = 0;
	m_unk0x018 = 0;
	m_unk0x01c = 0;
	m_unk0x020 = 0;
	m_unk0x024 = 0;
	m_unk0x04c = 0;
	m_unk0x034 = 0;
	m_unk0x038 = 0;
	m_unk0x03c = 0;
	m_unk0x040 = 0;
	m_unk0x044 = NULL;
	m_unk0x050 = 0;
	m_unk0x054 = 0;
	m_unk0x058 = 0;
	m_unk0x0a4 = 0;
	m_unk0x09c = 0;
}

// STUB: LEGORACERS 0x00430d80
void RaceSession::Field0x6dc::Field0xa8::VTable0x0c(undefined4, undefined4, undefined4, undefined4, undefined4)
{
	STUB(0x00430d80);
}

// STUB: LEGORACERS 0x00431050
void RaceSession::Field0x6dc::Field0xa8::VTable0x08(undefined4, undefined4, undefined4, undefined4, undefined4)
{
	STUB(0x00431050);
}

// STUB: LEGORACERS 0x00431220
void RaceSession::Field0x6dc::Field0xa8::VTable0x04(undefined4, undefined4)
{
	STUB(0x00431220);
}

// FUNCTION: LEGORACERS 0x00431530
void RaceSession::Field0x6dc::Field0xa8::VTable0x14()
{
	if (m_unk0x044 != NULL) {
		m_unk0x044->m_unk0x24 = 0;
		m_unk0x044 = NULL;
	}

	Reset();
}

// STUB: LEGORACERS 0x00431550
LegoS32 RaceSession::Field0x6dc::Field0xa8::VTable0x18(undefined4)
{
	STUB(0x00431550);
	return 0;
}

// STUB: LEGORACERS 0x00431660
void RaceSession::Field0x6dc::Field0xa8::VTable0x00(undefined4)
{
	STUB(0x00431660);
}

// FUNCTION: LEGORACERS 0x004316a0
void RaceSession::Field0x6dc::Field0xa8::VTable0x1c(GolVec3* p_unk0x04)
{
	p_unk0x04->m_x = m_unk0x034;
	p_unk0x04->m_y = m_unk0x038;
	p_unk0x04->m_z = static_cast<LegoS32>(m_unk0x050) * 0.001f * m_unk0x040 + m_unk0x03c;
}
