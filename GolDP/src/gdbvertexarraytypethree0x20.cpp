#include "gdbvertexarraytypethree0x20.h"

#include "golmath.h"

// FUNCTION: GOLDP 0x10016ad0
GdbVertexArrayTypeThree0x20::GdbVertexArrayTypeThree0x20()
{
	m_unk0x06 = 1;
}

// FUNCTION: GOLDP 0x10016b10
void GdbVertexArrayTypeThree0x20::VTable0x08(GolFileParser& p_parser)
{
	GdbVertexArrayTypeTwo0x20::VTable0x08(p_parser);
	m_unk0x06 = 3;
}

// FUNCTION: GOLDP 0x10016b30
void GdbVertexArrayTypeThree0x20::VTable0x04(LegoU16 p_count)
{
	GdbVertexArrayTypeTwo0x20::VTable0x04(p_count);
	m_unk0x06 = 3;
}

// FUNCTION: GOLDP 0x10016b50
void GdbVertexArrayTypeThree0x20::VTable0x10()
{
	if (m_unk0x1c != NULL) {
		delete[] m_unk0x1c;
		m_unk0x1c = NULL;
	}
	m_unk0x06 = 1;
}
