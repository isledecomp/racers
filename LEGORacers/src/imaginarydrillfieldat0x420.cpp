#include "imaginarydrillfieldat0x420.h"

DECOMP_SIZE_ASSERT(ImaginaryDrillFieldAt0x420, 0x78)

// FUNCTION: LEGORACERS 0x0046f410
ImaginaryDrillFieldAt0x420::ImaginaryDrillFieldAt0x420()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046f490
ImaginaryDrillFieldAt0x420::~ImaginaryDrillFieldAt0x420()
{
	ObscureVantage0x58::VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046f4f0
void ImaginaryDrillFieldAt0x420::Reset()
{
	m_unk0x64.Reset();
	m_unk0x5c = 0;
	m_unk0x60 = NULL;
	m_unk0x58 = 0;
	m_unk0x70 = 0;
	m_unk0x74 = 0;
	ObscureVantage0x58::Reset();
}

// STUB: LEGORACERS 0x0046f580
void ImaginaryDrillFieldAt0x420::VTable0x44(undefined4, undefined4)
{
	STUB(0x0046f580);
}

// STUB: LEGORACERS 0x0046f600
void ImaginaryDrillFieldAt0x420::VTable0x40(undefined4, undefined4)
{
	STUB(0x0046f600);
}

// STUB: LEGORACERS 0x0046f6f0
undefined4 ImaginaryDrillFieldAt0x420::VTable0x38(Rect*, Rect*)
{
	STUB(0x0046f6f0);
	return 0;
}
