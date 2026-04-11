#include "indigostar0x18.h"

DECOMP_SIZE_ASSERT(IndigoStar0x18, 0x18)

// GLOBAL: LEGORACERS 0x4afa3c
LegoFloat g_unk0x4afa3c = 1.0f;

// FUNCTION: LEGORACERS 0x417a30
IndigoStar0x18::IndigoStar0x18()
{
	m_unk0x04 = 0;
	m_unk0x0c = 0;
	m_unk0x08 = 0;
	m_unk0x10 = g_unk0x4afa3c;
	m_unk0x14 = g_unk0x4afa3c;
}

// FUNCTION: LEGORACERS 0x417a80
IndigoStar0x18::~IndigoStar0x18()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x417a90
void IndigoStar0x18::VTable0x08()
{
	m_unk0x04 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = g_unk0x4afa3c;
	m_unk0x14 = g_unk0x4afa3c;
}

// STUB: LEGORACERS 0x417b30
void IndigoStar0x18::VTable0x2c()
{
	STUB(0x417b30);
}

// STUB: LEGORACERS 0x417b60
void IndigoStar0x18::VTable0x30()
{
	STUB(0x417b60);
}
