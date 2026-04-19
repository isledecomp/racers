#include "jaspercore0xf0.h"

#include <string.h>

DECOMP_SIZE_ASSERT(JasperCore0xf0, 0xf0)

// FUNCTION: LEGORACERS 0x0044bf20
JasperCore0xf0::JasperCore0xf0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0044bf60
JasperCore0xf0::~JasperCore0xf0()
{
}

// FUNCTION: LEGORACERS 0x0044bf70
LegoS32 JasperCore0xf0::Reset()
{
	LegoS32 result = 0;
	m_unk0x8c = 0;
	m_countJoysticks = 0;
	m_mouseAvailable = FALSE;
	m_keyboardAvailable = FALSE;
	m_mouse = NULL;
	m_keyboard = NULL;
	memset(m_joysticks, 0, sizeof(m_joysticks));
	memset(m_unk0x04, 0, sizeof(m_unk0x04));
	memset(m_unk0x4c, 0, sizeof(m_unk0x4c));
	m_unk0x48 = 0;
	m_unk0x44 = 0;
	return result;
}

// STUB: LEGORACERS 0x0044bfd0
void JasperCore0xf0::FUN_0044bfd0()
{
	// TODO
	STUB(0x44bfd0);
}

// STUB: LEGORACERS 0x0044c040
void JasperCore0xf0::FUN_0044c040()
{
	// TODO
	STUB(0x44c040);
}
