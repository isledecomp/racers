#include "jaspercore0xf0.h"

#include <string.h>

DECOMP_SIZE_ASSERT(JasperCore0xf0, 0xf0)

// FUNCTION: LEGORACERS 0x0044bf20
JasperCore0xf0::JasperCore0xf0()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x0044bf60
JasperCore0xf0::~JasperCore0xf0()
{
}

// FUNCTION: LEGORACERS 0x0044bf70
LegoS32 JasperCore0xf0::VTable0x00()
{
	LegoS32 result = 0;
	m_unk0x8c = 0;
	m_unk0x98 = 0;
	m_unk0x94 = 0;
	m_unk0x90 = 0;
	m_unk0xa0 = 0;
	m_unk0x9c = 0;
	memset(m_unk0xa4, 0, sizeof(m_unk0xa4));
	memset(m_unk0x04, 0, sizeof(m_unk0x04));
	memset(m_unk0x4c, 0, sizeof(m_unk0x4c));
	m_unk0x48 = 0;
	m_unk0x44 = 0;
	return result;
}

// STUB: LEGORACERS 0x0044c120
void JasperCore0xf0::VTable0x24()
{
	// TODO
	STUB(0x44c120);
}

// STUB: LEGORACERS 0x0044c430
LegoS32 JasperCore0xf0::VTable0x18()
{
	// TODO
	STUB(0x44c430);
	return 0;
}

// STUB: LEGORACERS 0x0044c4a0
LegoS32 JasperCore0xf0::VTable0x1c()
{
	// TODO
	STUB(0x44c4a0);
	return 0;
}

// STUB: LEGORACERS 0x0044c510
LegoS32 JasperCore0xf0::VTable0x20()
{
	// TODO
	STUB(0x44c510);
	return 0;
}
