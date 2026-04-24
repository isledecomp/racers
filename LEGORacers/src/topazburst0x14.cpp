#include "topazburst0x14.h"

DECOMP_SIZE_ASSERT(TopazBurst0x14, 0x14)
DECOMP_SIZE_ASSERT(TopazBurst0x14::Entry, 0x18)

// FUNCTION: LEGORACERS 0x0049cae0
TopazBurst0x14::Entry::Entry()
{
	m_unk0x00 = 0;
	m_unk0x08 = 0;
	m_unk0x10 = 0;
	m_unk0x14 = NULL;
}

// FUNCTION: LEGORACERS 0x0049caf0
TopazBurst0x14::Entry::~Entry()
{
	FUN_0049cb00();
}

// FUNCTION: LEGORACERS 0x0049cb00
void TopazBurst0x14::Entry::FUN_0049cb00()
{
	if (m_unk0x14 != NULL) {
		delete[] m_unk0x14;
		m_unk0x14 = NULL;
	}

	m_unk0x08 = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0049ce10
TopazBurst0x14::TopazBurst0x14()
{
	m_unk0x04 = 0;
	m_unk0x00 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = NULL;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0049ce30
TopazBurst0x14::~TopazBurst0x14()
{
	FUN_0049ce40();
}

// FUNCTION: LEGORACERS 0x0049ce40
void TopazBurst0x14::FUN_0049ce40()
{
	if (m_unk0x0c != NULL) {
		delete[] m_unk0x0c;
		m_unk0x0c = NULL;
	}

	m_unk0x08 = 0;
	m_unk0x04 = 0;
	m_unk0x00 = 0;
	m_unk0x10 = 0;
}
