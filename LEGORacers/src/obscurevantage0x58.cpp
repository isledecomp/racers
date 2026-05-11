#include "obscurevantage0x58.h"

DECOMP_SIZE_ASSERT(ObscureVantage0x58, 0x58)

// GLOBAL: LEGORACERS 0x004c7650
Rect g_unk0x4c7650;

// FUNCTION: LEGORACERS 0x004729b0
ObscureVantage0x58::ObscureVantage0x58()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004729f0
ObscureVantage0x58::~ObscureVantage0x58()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00472a00
void ObscureVantage0x58::Reset()
{
	m_unk0x54 &= 0xfe;
	m_flags = (m_flags & 0xf2) | 2;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x18 = 0;
	m_nextSibling = 0;
	m_prevSibling = 0;
	m_lastChild = 0;
	m_firstChild = 0;
	m_parent = 0;
	m_unk0x30 = 0;
	m_unk0x28 = 0;
	m_unk0x48 = 1.0;
	m_unk0x44 = 1.0;
	m_unk0x50 = 0;
	m_unk0x4c = 0;
	m_unk0x34.m_left = 0;
	m_unk0x34.m_top = 0;
	m_unk0x34.m_right = 0;
	m_unk0x34.m_bottom = 0;
}

// FUNCTION: LEGORACERS 0x00472ad0
undefined4 ObscureVantage0x58::VTable0x08()
{
	if (m_flags & 1) {
		RemoveFromParent();
		if (m_unk0x28) {
			m_unk0x28->VTable0x04(this);
		}

		Reset();
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 ObscureVantage0x58::VTable0x3c(undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0044e7f0 FOLDED
undefined4 ObscureVantage0x58::VTable0x38(Rect*, Rect*)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x00472b00
void ObscureVantage0x58::SetParent(ObscureVantage0x58* p_param)
{
	if (m_flags & 4) {
		RemoveFromParent();
	}

	m_flags |= 4;
	m_parent = p_param;

	if (m_parent == NULL) {
		return;
	}

	if (m_parent->m_lastChild == NULL) {
		m_parent->m_firstChild = this;
		m_parent->m_lastChild = this;
		return;
	}

	m_prevSibling = m_parent->m_lastChild;
	m_prevSibling->m_nextSibling = this;
	m_parent->m_lastChild = this;
}

// FUNCTION: LEGORACERS 0x00472b50
void ObscureVantage0x58::RemoveFromParent()
{
	if (!(m_flags & 4)) {
		return;
	}

	if (m_prevSibling) {
		m_prevSibling->m_nextSibling = m_nextSibling;
	}
	else if (m_parent) {
		m_parent->m_firstChild = m_nextSibling;
	}

	if (m_nextSibling) {
		m_nextSibling->m_prevSibling = m_prevSibling;
		m_nextSibling = 0;
		m_prevSibling = 0;
		m_parent = 0;
		m_flags &= 0xfb;
		return;
	}

	if (m_parent) {
		m_parent->m_lastChild = m_prevSibling;
	}

	m_nextSibling = 0;
	m_prevSibling = 0;
	m_parent = 0;
	m_flags &= 0xfb;
}

// FUNCTION: LEGORACERS 0x00472c40
undefined4 ObscureVantage0x58::FUN_00472c40(LegoS32 p_x, LegoS32 p_y)
{
	return p_x >= 0 && p_x <= (m_unk0x34.m_right - m_unk0x34.m_left) && p_y >= 0 &&
		   p_y <= (m_unk0x34.m_bottom - m_unk0x34.m_top);
}

// FUNCTION: LEGORACERS 0x00472e40
ObscureVantage0x58* ObscureVantage0x58::FindRoot()
{
	ObscureVantage0x58* result = this;

	while (result->m_parent) {
		result = result->m_parent;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00472e60
ObscureVantage0x58* ObscureVantage0x58::FUN_00472e60()
{
	ObscureVantage0x58* result = FindRoot();
	ObscureVantage0x58* child = result->m_unk0x18;

	if (!child) {
		return (result->m_flags & 0x08) ? result : NULL;
	}

	do {
		result = child;
		child = result->m_unk0x18;
	} while (child);

	return result;
}

// FUNCTION: LEGORACERS 0x00472e90
Rect* ObscureVantage0x58::GetGlobalRect()
{
	ObscureVantage0x58* node = this;

	g_unk0x4c7650.m_top = 0;
	g_unk0x4c7650.m_left = 0;

	while (node) {
		g_unk0x4c7650.m_left += node->m_unk0x34.m_left;
		g_unk0x4c7650.m_top += node->m_unk0x34.m_top;
		node = node->m_parent;
	}

	g_unk0x4c7650.m_right = (m_unk0x34.m_right - m_unk0x34.m_left) + g_unk0x4c7650.m_left;
	g_unk0x4c7650.m_bottom = (m_unk0x34.m_bottom - m_unk0x34.m_top) + g_unk0x4c7650.m_top;

	return &g_unk0x4c7650;
}

// FUNCTION: LEGORACERS 0x00472f40
void ObscureVantage0x58::VTable0x10(Rect* p_rect)
{
	if (m_unk0x28) {
		if ((((m_unk0x34.m_right - p_rect->m_right) - m_unk0x34.m_left) + p_rect->m_left != 0) ||
			(((m_unk0x34.m_bottom - m_unk0x34.m_top) - p_rect->m_bottom) + p_rect->m_top != 0)) {
			m_unk0x28->VTable0x0c(this);
		}

		if ((m_unk0x34.m_left - p_rect->m_left) || (m_unk0x34.m_top - p_rect->m_top)) {
			m_unk0x28->VTable0x08(this);
		}
	}

	m_unk0x34 = *p_rect;
	return;
}

// FUNCTION: LEGORACERS 0x00472fc0
void ObscureVantage0x58::VTable0x14(Rect* p_param)
{
	m_unk0x2c = p_param->m_left;
}

// FUNCTION: LEGORACERS 0x004730a0
LegoBool32 ObscureVantage0x58::ClipRect(Rect* p_rect, Rect* p_arg)
{
	if (p_rect->m_left >= m_unk0x34.m_right) {
		return FALSE;
	}

	if (p_rect->m_right <= m_unk0x34.m_left) {
		return FALSE;
	}

	if (p_rect->m_top >= m_unk0x34.m_bottom) {
		return FALSE;
	}

	if (p_rect->m_bottom <= m_unk0x34.m_top) {
		return FALSE;
	}

	if (p_rect->m_left < m_unk0x34.m_left) {
		p_arg->m_left += m_unk0x34.m_left - p_rect->m_left;
		p_rect->m_left = m_unk0x34.m_left;
	}

	if (p_rect->m_top < m_unk0x34.m_top) {
		p_arg->m_top += m_unk0x34.m_top - p_rect->m_top;
		p_rect->m_top = m_unk0x34.m_top;
	}

	if (p_rect->m_right > m_unk0x34.m_right) {
		p_arg->m_right += m_unk0x34.m_right - p_rect->m_right;
		p_rect->m_right = m_unk0x34.m_right;
	}

	if (p_rect->m_bottom > m_unk0x34.m_bottom) {
		p_arg->m_bottom += m_unk0x34.m_bottom - p_rect->m_bottom;
		p_rect->m_bottom = m_unk0x34.m_bottom;
	}

	return TRUE;
}

// STUB: LEGORACERS 0x00473160
Rect* ObscureVantage0x58::FUN_00473160(Rect* p_rect)
{
	Rect* result = p_rect;
	LegoS32 oldTop = p_rect->m_top;
	LegoS32 oldLeft = p_rect->m_left;
	LegoS32 translatedLeft = oldLeft + m_unk0x4c - m_unk0x34.m_left;
	LegoS32 translatedTop = oldTop + m_unk0x50 - m_unk0x34.m_top;
	LegoS32 height = p_rect->m_bottom - oldTop;
	LegoS32 translatedRight = translatedLeft + p_rect->m_right - oldLeft;

	p_rect->m_left = translatedLeft;
	p_rect->m_top = translatedTop;
	p_rect->m_right = translatedRight;
	p_rect->m_bottom = translatedTop + height;

	return result;
}

// FUNCTION: LEGORACERS 0x004731b0
void ObscureVantage0x58::FUN_004731b0(undefined4& p_x, undefined4& p_y)
{
	p_x -= m_unk0x34.m_left;
	p_y -= m_unk0x34.m_top;
}

// FUNCTION: LEGORACERS 0x004731d0
undefined4 ObscureVantage0x58::VTable0x18(undefined4 p_unk0x04)
{
	ObscureVantage0x58* child = m_firstChild;
	if (VTable0x3c(p_unk0x04)) {
		return TRUE;
	}

	while (child) {
		if (child->VTable0x18(p_unk0x04)) {
			return TRUE;
		}

		child = child->m_nextSibling;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00473210
undefined4 ObscureVantage0x58::VTable0x1c(Rect* p_rect, Rect* p_arg)
{
	Rect rect = *p_rect;
	ObscureVantage0x58* child = m_firstChild;
	Rect arg = *p_arg;

	if (ClipRect(&rect, &arg)) {
		FUN_00473160(&rect);

		undefined flags = m_flags;
		if ((flags & 2) && (!(flags & 0x10) || !VTable0x38(&rect, &arg))) {
			for (; child; child = child->m_nextSibling) {
				if (child->VTable0x1c(&rect, &arg)) {
					break;
				}
			}
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x004732d0
undefined4 ObscureVantage0x58::VTable0x20(CopperCrest0x40::Helper0x44* p_param1, undefined4 p_x, undefined4 p_y)
{
	ObscureVantage0x58* child = m_firstChild;
	undefined4 x = p_x;
	undefined4 y = p_y;

	FUN_004731b0(x, y);

	if ((m_flags & 2) && FUN_00472c40(x, y)) {
		while (child) {
			if (child->VTable0x20(p_param1, x, y)) {
				return TRUE;
			}

			child = child->m_nextSibling;
		}

		if (VTable0x2c(p_param1, x, y)) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00473370
undefined4 ObscureVantage0x58::VTable0x24(OnyxCircularBuffer0x1c::Item* p_param1, undefined4 p_x, undefined4 p_y)
{
	ObscureVantage0x58* child = m_firstChild;
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	FUN_004731b0(x, y);

	while (child) {
		if (child->VTable0x24(p_param1, x, y)) {
			return TRUE;
		}

		child = child->m_nextSibling;
	}

	return VTable0x30(p_param1, x, y);
}

// STUB: LEGORACERS 0x00473400
undefined4 ObscureVantage0x58::VTable0x28(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	// TODO
	STUB(0x00473400);
	return 0;
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
undefined4 ObscureVantage0x58::VTable0x2c(void*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
undefined4 ObscureVantage0x58::VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
undefined4 ObscureVantage0x58::VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return 0;
}
