#include "menu/widgets/sablecrest0xc0.h"

DECOMP_SIZE_ASSERT(SableCrest0xc0, 0xc0)

// FUNCTION: LEGORACERS 0x00467e70
SableCrest0xc0::SableCrest0xc0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00467ee0
SableCrest0xc0::~SableCrest0xc0()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00467f30
void SableCrest0xc0::Reset()
{
	m_unk0xb0 = 0;
	m_unk0xa8 = 0;
	m_unk0xac = 0;
	m_unk0xb8 = 0;
	m_unk0xbc = 0;
	m_unk0xb4 = 1;
	m_unk0xa4 = 1;
	ObscureVantage0x58::Reset();
}

// FUNCTION: LEGORACERS 0x00468080
void SableCrest0xc0::VTable0x10(Rect* p_rect)
{
	m_unk0xb8 = p_rect->m_right - p_rect->m_left;
	m_unk0xbc = p_rect->m_bottom - p_rect->m_top;
	ObscureVantage0x58::VTable0x10(p_rect);
}

// FUNCTION: LEGORACERS 0x004680b0
ObscureVantage0x58* SableCrest0xc0::VTable0x38(Rect* p_param1, Rect* p_param2)
{
	if (!m_unk0xa4) {
		return NULL;
	}

	return ObscureZebra0xa4::VTable0x38(p_param1, p_param2);
}

// FUNCTION: LEGORACERS 0x004680e0
undefined4 SableCrest0xc0::VTable0x3c(undefined4 p_param)
{
	if (m_unk0xb4) {
		if (p_param < m_unk0xb0) {
			m_unk0xb0 -= p_param;
		}
		else {
			m_unk0xa4 = (m_unk0xa4 == 0);

			if (m_unk0xa4) {
				m_unk0xb0 = m_unk0xa8;
			}
			else {
				m_unk0xb0 = m_unk0xac;
			}
		}
	}

	return 0;
}
