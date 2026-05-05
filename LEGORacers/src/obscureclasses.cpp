#include "obscureclasses.h"

DECOMP_SIZE_ASSERT(ObscureAnchor, 0x5c)
DECOMP_SIZE_ASSERT(ObscureAnthem, 0x58)
DECOMP_SIZE_ASSERT(ObscureRune, 0x4d8)
DECOMP_SIZE_ASSERT(ObscureSigil, 0xdc)
DECOMP_SIZE_ASSERT(ObscureTome, 0x3dc)
DECOMP_SIZE_ASSERT(ObscureZebra, 0xa4)

// FUNCTION: LEGORACERS 0x004656e0
ObscureSigil::ObscureSigil()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x00465750
ObscureSigil::~ObscureSigil()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x004657a0
void ObscureSigil::VTable0x00()
{
	m_unk0x88 = 5;
	m_unk0x5c = 0;
	m_unk0x64 = 0;
	m_unk0x60 = 0;
	m_unk0x68 = 0;
	m_unk0x58 = 0;
	m_unk0x6c = 0;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xbc = 0;
	m_unk0xc0 = 0;
	m_unk0xc4 = 0;
	m_unk0xc8 = 0;
	m_unk0xcc = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xd8 = 0;
	m_unk0x94 = 0;
	m_unk0x90 = 0;
	m_unk0x98 = -1;

	ObscureVantage0x58::VTable0x00();
}

// STUB: LEGORACERS 0x00465890
undefined4 ObscureSigil::VTable0x08()
{
	STUB(0x00465890);
	return 0;
}

// STUB: LEGORACERS 0x00465f20
undefined4 ObscureSigil::VTable0x38(undefined4, undefined4)
{
	STUB(0x00465f20);
	return 0;
}

// STUB: LEGORACERS 0x00465fe0
undefined4 ObscureSigil::VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x00465fe0);
	return 0;
}

// STUB: LEGORACERS 0x00466010
undefined4 ObscureSigil::VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x00466010);
	return 0;
}

// STUB: LEGORACERS 0x00466040
undefined4 ObscureSigil::VTable0x3c(undefined4)
{
	STUB(0x00466040);
	return 0;
}

// STUB: LEGORACERS 0x00466090 FOLDED
undefined4 ObscureSigil::VTable0x2c(void*, undefined4, undefined4)
{
	STUB(0x00466090);
	return 0;
}

// FUNCTION: LEGORACERS 0x004660a0
ObscureRune::ObscureRune()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x00466120
ObscureRune::~ObscureRune()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046e9e0
ObscureAnthem::ObscureAnthem()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x0046ea50
ObscureAnthem::~ObscureAnthem()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x0046eaa0
undefined4 ObscureAnthem::VTable0x2c(void*, undefined4, undefined4)
{
	STUB(0x0046eaa0);
	return 0;
}

// STUB: LEGORACERS 0x0046eaf0
undefined4 ObscureAnthem::VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x0046eaf0);
	return 0;
}

// STUB: LEGORACERS 0x0046eb50
undefined4 ObscureAnthem::VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x0046eb50);
	return 0;
}

// FUNCTION: LEGORACERS 0x0046ebb0
ObscureTome::ObscureTome()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x0046ec50
ObscureTome::~ObscureTome()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x0046ee40
void ObscureTome::VTable0x10(undefined4)
{
	STUB(0x0046ee40);
}

// FUNCTION: LEGORACERS 0x0046f080
ObscureAnchor::ObscureAnchor()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x0046f0f0
ObscureAnchor::~ObscureAnchor()
{
	ObscureVantage0x58::VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046f140
void ObscureAnchor::VTable0x00()
{
	m_unk0x58 = 0;
	ObscureVantage0x58::VTable0x00();
}

// STUB: LEGORACERS 0x0046f1a0
undefined4 ObscureAnchor::VTable0x38(undefined4, undefined4)
{
	STUB(0x0046f1a0);
	return 0;
}

// FUNCTION: LEGORACERS 0x004734a0
ObscureZebra::ObscureZebra()
{
	VTable0x00();
}

// STUB: LEGORACERS 0x00473510
ObscureZebra::~ObscureZebra()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x00473560
void ObscureZebra::VTable0x00()
{
	STUB(0x00473560);
}

// STUB: LEGORACERS 0x004735c0
void ObscureZebra::VTable0x14(undefined4)
{
	STUB(0x004735c0);
}

// STUB: LEGORACERS 0x004735f0
undefined4 ObscureZebra::VTable0x38(undefined4, undefined4)
{
	STUB(0x004735f0);
	return 0;
}
