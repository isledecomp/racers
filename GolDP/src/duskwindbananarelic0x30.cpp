#include "duskwindbananarelic0x30.h"

DECOMP_SIZE_ASSERT(DuskwindBananaRelic0x30, 0x30)

// FUNCTION: GOLDP 0x10006280
DuskwindBananaRelic0x30::DuskwindBananaRelic0x30()
{
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = NULL;
}

// STUB: GOLDP 0x100062a0
DuskwindBananaRelic0x30::~DuskwindBananaRelic0x30()
{
	if (m_unk0x2c != NULL) {
		delete m_unk0x2c;
		m_unk0x2c = NULL;
	}
#if 0
	if (m_unk0x24 != NULL) {
		m_unk0x24->VTable0x08();
		m_unk0x2c = NULL;
	}
#endif
	m_unk0x28 = 0;
	m_unk0x08 &= ~c_flagBit0;
	// TODO
	STUB(0x100062a0);
}

// STUB: GOLDP 0x10006320
void DuskwindBananaRelic0x30::FUN_10006320(BronzeFalcon0xc8770*)
{
	// TODO
	STUB(0x10006320);
}
