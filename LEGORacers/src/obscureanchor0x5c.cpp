#include "obscureanchor0x5c.h"

#include "utopianpan0xa4.h"

DECOMP_SIZE_ASSERT(ObscureAnchor0x5c, 0x5c)
DECOMP_SIZE_ASSERT(ObscureAnchor0x5c::CreateParams0x3c, 0x3c)

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
	m_unk0x58 = NULL;
	ObscureVantage0x58::Reset();
}

// FUNCTION: LEGORACERS 0x0046f150
LegoBool32 ObscureAnchor0x5c::FUN_0046f150(CreateParams0x3c* p_createParams)
{
	VTable0x08();

	m_unk0x58 = p_createParams->m_unk0x38;

	if (!p_createParams->m_rect.m_right) {
		p_createParams->m_rect.m_right = m_unk0x58->GetWidth() + p_createParams->m_rect.m_left;
	}

	if (!p_createParams->m_rect.m_bottom) {
		p_createParams->m_rect.m_bottom = m_unk0x58->GetHeight() + p_createParams->m_rect.m_top;
	}

	return FUN_00472a60(p_createParams);
}

// FUNCTION: LEGORACERS 0x0046f1a0
undefined4 ObscureAnchor0x5c::VTable0x38(Rect* p_rect, Rect* p_arg)
{
	Rect sourceRect;
	sourceRect.m_top = 0;
	sourceRect.m_left = 0;
	sourceRect.m_right = m_unk0x58->GetWidth();
	sourceRect.m_bottom = m_unk0x58->GetHeight();

	FUN_00472fd0(&sourceRect, &m_unk0x34);
	FUN_00473050(p_rect, &sourceRect);
	FUN_00472d70(p_arg, &sourceRect, m_unk0x58);

	return 0;
}
