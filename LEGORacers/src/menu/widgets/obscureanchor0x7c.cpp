#include "menu/widgets/obscureanchor0x7c.h"

#include "image/utopianpan0xa4.h"

DECOMP_SIZE_ASSERT(ObscureAnchor0x7c, 0x7c)

// FUNCTION: LEGORACERS 0x0046f200
ObscureAnchor0x7c::ObscureAnchor0x7c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046f270
ObscureAnchor0x7c::~ObscureAnchor0x7c()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046f2c0
void ObscureAnchor0x7c::FUN_0046f2c0(Rect* p_rect)
{
	if (m_unk0x6c.m_top < p_rect->m_top) {
		LegoS32 delta = p_rect->m_top - m_unk0x6c.m_top;
		m_unk0x5c.m_top = delta;
		m_unk0x6c.m_top += delta;
	}

	if (m_unk0x6c.m_left < p_rect->m_left) {
		LegoS32 delta = p_rect->m_left - m_unk0x6c.m_left;
		m_unk0x5c.m_left = delta;
		m_unk0x6c.m_left += delta;
	}

	if (m_unk0x6c.m_right > p_rect->m_right) {
		LegoS32 delta = m_unk0x6c.m_right - p_rect->m_right;
		m_unk0x5c.m_right -= delta;
		m_unk0x6c.m_right -= delta;
	}

	if (m_unk0x6c.m_bottom > p_rect->m_bottom) {
		LegoS32 delta = m_unk0x6c.m_bottom - p_rect->m_bottom;
		m_unk0x5c.m_bottom -= delta;
		m_unk0x6c.m_bottom -= delta;
	}
}

// FUNCTION: LEGORACERS 0x0046f330
ObscureVantage0x58* ObscureAnchor0x7c::VTable0x38(Rect* p_rect, Rect* p_arg)
{
	LegoS32 imageWidth = m_unk0x58->GetWidth();
	LegoS32 imageHeight = m_unk0x58->GetHeight();
	LegoS32 top = p_rect->m_top;

	if (top < p_rect->m_bottom) {
		do {
			if (p_rect->m_left < p_rect->m_right) {
				LegoS32 left = p_rect->m_left;
				do {
					m_unk0x5c.m_top = 0;
					m_unk0x5c.m_left = 0;
					m_unk0x5c.m_right = imageWidth;
					m_unk0x5c.m_bottom = imageHeight;

					m_unk0x6c.m_top = p_arg->m_top + top;
					m_unk0x6c.m_left = p_arg->m_left + left;
					m_unk0x6c.m_right = p_arg->m_left + left + imageWidth;
					m_unk0x6c.m_bottom = p_arg->m_top + top + imageHeight;

					FUN_0046f2c0(p_arg);
					FUN_00472d70(&m_unk0x6c, &m_unk0x5c, m_unk0x58);

					left += imageWidth;
				} while (left < p_rect->m_right);
			}

			top += imageHeight;
		} while (top < p_rect->m_bottom);
	}

	return NULL;
}
