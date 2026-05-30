#include "menu/widgets/sablecrest0xc0.h"

DECOMP_SIZE_ASSERT(SableCrest0xc0, 0xc0)
DECOMP_SIZE_ASSERT(SableCrest0xc0::CreateParams0x44, 0x44)

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

// FUNCTION: LEGORACERS 0x00467f70
LegoBool32 SableCrest0xc0::FUN_00467f70(CreateParams0x44* p_createParams)
{
	VTable0x08();

	m_unk0xa8 = p_createParams->m_unk0x3c;
	m_unk0xac = p_createParams->m_unk0x40;
	m_unk0xb4 = p_createParams->m_unk0x38;
	m_unk0xb8 = p_createParams->m_rect.m_right - p_createParams->m_rect.m_left;
	m_unk0xbc = p_createParams->m_rect.m_bottom - p_createParams->m_rect.m_top;

	return ObscureZebra0xa4::FUN_004735a0(p_createParams);
}

// FUNCTION: LEGORACERS 0x00467fc0
void SableCrest0xc0::FUN_00467fc0(LegoS32 p_x, LegoS32 p_y)
{
	Rect rect;
	rect.m_left = p_x;
	rect.m_right = p_x + m_unk0xb8;
	rect.m_top = p_y;
	rect.m_bottom = p_y + m_unk0xbc;

	ObscureVantage0x58::VTable0x10(&rect);
}

// STUB: LEGORACERS 0x00468000
void SableCrest0xc0::FUN_00468000(LegoS32 p_width)
{
	Rect rect;
	rect.m_left = m_unk0x34.m_left;
	rect.m_right = m_unk0x34.m_left + p_width;
	m_unk0xb8 = p_width;
	rect.m_top = m_unk0x34.m_top;
	rect.m_bottom = m_unk0x34.m_top + m_unk0xbc;

	ObscureVantage0x58::VTable0x10(&rect);
}

// STUB: LEGORACERS 0x00468040
void SableCrest0xc0::FUN_00468040(LegoS32 p_height)
{
	m_unk0xbc = p_height;

	Rect rect;
	rect.m_left = m_unk0x34.m_left;
	rect.m_right = m_unk0x34.m_left + m_unk0xb8;
	rect.m_top = m_unk0x34.m_top;
	rect.m_bottom = m_unk0x34.m_top + p_height;

	ObscureVantage0x58::VTable0x10(&rect);
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
