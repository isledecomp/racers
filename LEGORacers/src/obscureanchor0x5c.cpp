#include "obscureanchor0x5c.h"

DECOMP_SIZE_ASSERT(ObscureAnchor0x5c, 0x5c)

// FUNCTION: LEGORACERS 0x0046f080
ObscureAnchor0x5c::ObscureAnchor0x5c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046f0f0
ObscureAnchor0x5c::~ObscureAnchor0x5c()
{
	ObscureVantage0x58::VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046f140
void ObscureAnchor0x5c::Reset()
{
	m_unk0x58 = 0;
	ObscureVantage0x58::Reset();
}

// STUB: LEGORACERS 0x0046f1a0
undefined4 ObscureAnchor0x5c::VTable0x38(Rect*, Rect*)
{
	STUB(0x0046f1a0);
	return 0;
}
