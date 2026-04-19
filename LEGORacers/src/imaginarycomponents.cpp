#include "imaginarycomponents.h"

DECOMP_SIZE_ASSERT(CeruleanSubject, 0x0c)
DECOMP_SIZE_ASSERT(CeruleanKnight, 0x20)
DECOMP_SIZE_ASSERT(CeruleanQueen, 0x58)
DECOMP_SIZE_ASSERT(CeruleanEmperor, 0x50)

// FUNCTION: LEGORACERS 0x004117b0
CeruleanSubject::CeruleanSubject()
{
	m_unk0x04 = 0;
	m_unk0x08 = 0;
}

// FUNCTION: LEGORACERS 0x004117f0
CeruleanSubject::~CeruleanSubject()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x00411800
void CeruleanSubject::VTable0x04(undefined4)
{
	// TODO
	STUB(0x00411800);
}

// STUB: LEGORACERS 0x00411850
void CeruleanSubject::VTable0x08()
{
	// TODO
	STUB(0x00411850);
}

// STUB: LEGORACERS 0x004695b0
CeruleanQueen::CeruleanQueen()
{
	// TODO
}

// STUB: LEGORACERS 0x00469620
CeruleanQueen::~CeruleanQueen()
{
	// TODO
}

// FUNCTION: LEGORACERS 0x00469670
void CeruleanQueen::VTable0x0c()
{
	m_unk0x54 = 2;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	m_unk0x50 = 0;
	CeruleanKnight::VTable0x0c();
}

// STUB: LEGORACERS 0x004696f0
void CeruleanQueen::VTable0x08()
{
	// TODO
	STUB(0x004696f0);
}

// STUB: LEGORACERS 0x00469810
void CeruleanQueen::VTable0x10(undefined4)
{
	// TODO
	STUB(0x00469810);
}

// STUB: LEGORACERS 0x00469950
void CeruleanQueen::VTable0x14(undefined4)
{
	// TODO
	STUB(0x00469950);
}

// FUNCTION: LEGORACERS 0x0046b020
CeruleanKnight::CeruleanKnight()
{
	VTable0x0c();
}

// STUB: LEGORACERS 0x0046b090
CeruleanKnight::~CeruleanKnight()
{
	// TODO
}

// FUNCTION: LEGORACERS 0x0046b0e0
void CeruleanKnight::VTable0x0c()
{
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x1c = 0;
	m_unk0x18 = 0;
	m_unk0x0c = 0;
}

// STUB: LEGORACERS 0x0046b110
void CeruleanKnight::VTable0x08()
{
	// TODO
	STUB(0x0046b110);
}

// STUB: LEGORACERS 0x0046fa50
CeruleanEmperor::CeruleanEmperor()
{
	VTable0x0c();
}

// STUB: LEGORACERS 0x0046fac0
CeruleanEmperor::~CeruleanEmperor()
{
	// TODO
}

// STUB: LEGORACERS 0x0046fb10
void CeruleanEmperor::VTable0x0c()
{
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x48 = 0;
}

// STUB: LEGORACERS 0x0046fb80
void CeruleanEmperor::VTable0x08()
{
	// TODO
	STUB(0x0046fb80);
}

// STUB: LEGORACERS 0x0046fc40
void CeruleanEmperor::VTable0x10(undefined4)
{
	// TODO
	STUB(0x0046fc40);
}

// STUB: LEGORACERS 0x0046fd80
void CeruleanEmperor::VTable0x14(undefined4)
{
	// TODO
	STUB(0x0046fd80);
}
