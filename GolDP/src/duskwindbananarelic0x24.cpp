#include "duskwindbananarelic0x24.h"

#include "golddune0x38.h"
#include "whitefalcon0x140.h"

DECOMP_SIZE_ASSERT(DuskWindName0x8, 0x8)
DECOMP_SIZE_ASSERT(DuskwindBananaRelic0x24, 0x24)
DECOMP_SIZE_ASSERT(DuskWindBananaRelicParams, 0x14)

// FUNCTION: GOLDP 0x10025770
DuskwindBananaRelic0x24::DuskwindBananaRelic0x24()
	: m_unk0x0c(0xff, 0xff, 0xff, 0xff), m_unk0x10(0xff, 0xff, 0xff, 0xff)
{
	m_unk0x14 = 0;
	m_unk0x08 = 0x50a694;
	m_unk0x04 = NULL;
	m_unk0x21 = 0;
	m_unk0x20 = 0;
	m_unk0x22 = 1;
	m_unk0x23 = 0;
}

// FUNCTION: GOLDP 0x100257d0
DuskwindBananaRelic0x24::~DuskwindBananaRelic0x24()
{
}

// STUB: GOLDP 0x100257e0
void DuskwindBananaRelic0x24::FUN_100257e0(WhiteFalcon0x140* p_renderer, const DuskWindBananaRelicParams& p_params)
{
	m_unk0x10 = p_params.m_unk0x08;
	m_unk0x0c = p_params.m_unk0x0c;
	m_unk0x08 = p_params.m_unk0x00;
	m_unk0x20 = p_params.m_unk0x10;
	m_unk0x21 = p_params.m_unk0x11;
	m_unk0x22 = p_params.m_unk0x12;
	m_unk0x22 = p_params.m_unk0x12;
	m_unk0x23 = p_params.m_unk0x13;
	m_unk0x23 = p_params.m_unk0x13;
	if (m_unk0x08 & c_flag0x08Bit3) {
		m_unk0x04 = p_params.m_unk0x04;
#if 0
		// p_params.m_unk0x04 is probably GoldDune0x30. But this is a pure guess.
		if (reinterpret_cast<GoldDune0x38*>(p_params.m_unk0x04)->GetUnk0x36() & GoldDune0x38::c_unk0x36Bit5) {
#else
		// TODO
		STUB(0x100257e0);
		if (1) {
#endif
			if (p_renderer->GetUnk0x04() & (WhiteFalcon0x140::c_flagBit7 | WhiteFalcon0x140::c_flagBit8)) {
				if ((p_renderer->GetUnk0x04() & WhiteFalcon0x140::c_flagBit7) && !(m_unk0x08 & c_flag0x08Bit12)) {
					m_unk0x22 = 6;
					m_unk0x23 = 8;
					m_unk0x08 &= ~(c_flag0x08Bit9 | c_flag0x08Bit5 | c_flag0x08Bit2);
					m_unk0x08 |= c_flag0x08Bit8 | c_flag0x08Bit4 | c_flag0x08Bit1;
				}
				if (p_renderer->GetUnk0x04() & WhiteFalcon0x140::c_flagBit8) {
					m_unk0x20 = 2;
					m_unk0x21 = 0;
					m_unk0x08 &= ~c_flag0x08Bit7;
					m_unk0x08 |= c_flag0x08Bit6;
				}
			}
		}
	}
	else {
		m_unk0x04 = NULL;
	}
}
