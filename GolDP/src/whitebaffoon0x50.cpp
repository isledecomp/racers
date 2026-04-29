#include "whitebaffoon0x50.h"

DECOMP_SIZE_ASSERT(WhiteBaffoon0x50, 0x50)

// FUNCTION: GOLDP 0x1001f1e0
WhiteBaffoon0x50::WhiteBaffoon0x50()
{
	Reset();
}

// FUNCTION: GOLDP 0x1001f2a0
WhiteBaffoon0x50::~WhiteBaffoon0x50()
{
	Reset();
}

// FUNCTION: GOLDP 0x1001f2f0
void WhiteBaffoon0x50::Reset()
{

	m_renderer = NULL;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = c_flagBit5 | c_flagBit1;
	m_flags = 0;
	m_unk0x28.m_bytes[0] = 0;
	m_unk0x28.m_bytes[1] = 0;
	m_unk0x28.m_bytes[2] = 0;
	m_unk0x28.m_bytes[3] = (LegoChar) 0xff;
	m_unk0x4a.m_bytes[0] = (LegoChar) 0xff;
	m_unk0x4a.m_bytes[1] = (LegoChar) 0xff;
	m_unk0x4a.m_bytes[2] = (LegoChar) 0xff;
	m_unk0x4a.m_bytes[3] = (LegoChar) 0xff;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
}

// STUB: GOLDP 0x1001f330
void WhiteBaffoon0x50::VTable0x10()
{
	// TODO
	STUB(0x1001f330);
}

// STUB: GOLDP 0x1001f430
void WhiteBaffoon0x50::FUN_1001f430()
{
	// TODO
	STUB(0x1001f430);
}

// STUB: GOLDP 0x1001f790
void WhiteBaffoon0x50::FUN_1001f790()
{
	// TODO
	STUB(0x1001f790);
}
