#include "obscurevantage0x58.h"

DECOMP_SIZE_ASSERT(ObscureVantage0x58, 0x58)
DECOMP_SIZE_ASSERT(ObscureVantage0x58::Struct0x34, 0x10)

// GLOBAL: LEGORACERS 0x004c7650
SilverDune0x30::Rect g_unk0x4c7650;

// FUNCTION: LEGORACERS 0x004729b0
ObscureVantage0x58::ObscureVantage0x58()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x004729f0
ObscureVantage0x58::~ObscureVantage0x58()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00472a00
void ObscureVantage0x58::VTable0x00()
{
	m_unk0x54 &= 0xfe;
	m_unk0x1c = (m_unk0x1c & 0xf2) | 2;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x18 = 0;
	m_unk0x14 = 0;
	m_unk0x10 = 0;
	m_unk0x0c = 0;
	m_unk0x08 = 0;
	m_unk0x04 = 0;
	m_unk0x30 = 0;
	m_unk0x28 = 0;
	m_unk0x48 = 1.0;
	m_unk0x44 = 1.0;
	m_unk0x50 = 0;
	m_unk0x4c = 0;
	m_unk0x34.m_unk0x00 = 0;
	m_unk0x34.m_unk0x04 = 0;
	m_unk0x34.m_unk0x08 = 0;
	m_unk0x34.m_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x00472ad0
undefined4 ObscureVantage0x58::VTable0x08()
{
	if (m_unk0x1c & 1) {
		FUN_00472b50();
		if (m_unk0x28) {
			m_unk0x28->VTable0x04(this);
		}

		VTable0x00();
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 ObscureVantage0x58::VTable0x3c(undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0044e7f0 FOLDED
undefined4 ObscureVantage0x58::VTable0x38(undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x00472b00
void ObscureVantage0x58::VTable0x0c(ObscureVantage0x58* p_param)
{
	if (m_unk0x1c & 4) {
		FUN_00472b50();
	}

	m_unk0x1c |= 4;
	m_unk0x04 = p_param;

	if (m_unk0x04 == NULL) {
		return;
	}

	if (m_unk0x04->m_unk0x0c == NULL) {
		m_unk0x04->m_unk0x08 = this;
		m_unk0x04->m_unk0x0c = this;
		return;
	}

	m_unk0x10 = m_unk0x04->m_unk0x0c;
	m_unk0x10->m_unk0x14 = this;
	m_unk0x04->m_unk0x0c = this;
}

// FUNCTION: LEGORACERS 0x00472b50
void ObscureVantage0x58::FUN_00472b50()
{
	if (!(m_unk0x1c & 4)) {
		return;
	}

	if (m_unk0x10) {
		m_unk0x10->m_unk0x14 = m_unk0x14;
	}
	else if (m_unk0x04) {
		m_unk0x04->m_unk0x08 = m_unk0x14;
	}

	if (m_unk0x14) {
		m_unk0x14->m_unk0x10 = m_unk0x10;
		m_unk0x14 = 0;
		m_unk0x10 = 0;
		m_unk0x04 = 0;
		m_unk0x1c &= 0xfb;
		return;
	}

	if (m_unk0x04) {
		m_unk0x04->m_unk0x0c = m_unk0x10;
	}

	m_unk0x14 = 0;
	m_unk0x10 = 0;
	m_unk0x04 = 0;
	m_unk0x1c &= 0xfb;
}

// FUNCTION: LEGORACERS 0x00472e40
ObscureVantage0x58* ObscureVantage0x58::FUN_00472e40()
{
	ObscureVantage0x58* result = this;

	while (result->m_unk0x04) {
		result = result->m_unk0x04;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00472e60
ObscureVantage0x58* ObscureVantage0x58::FUN_00472e60()
{
	ObscureVantage0x58* result = FUN_00472e40();
	ObscureVantage0x58* child = result->m_unk0x18;

	if (!child) {
		return (result->m_unk0x1c & 0x08) ? result : NULL;
	}

	do {
		result = child;
		child = result->m_unk0x18;
	} while (child);

	return result;
}

// FUNCTION: LEGORACERS 0x00472e90
SilverDune0x30::Rect* ObscureVantage0x58::FUN_00472e90()
{
	ObscureVantage0x58* node = this;

	g_unk0x4c7650.m_top = 0;
	g_unk0x4c7650.m_left = 0;

	while (node) {
		g_unk0x4c7650.m_left += node->m_unk0x34.m_unk0x00;
		g_unk0x4c7650.m_top += node->m_unk0x34.m_unk0x04;
		node = node->m_unk0x04;
	}

	g_unk0x4c7650.m_right = (m_unk0x34.m_unk0x08 - m_unk0x34.m_unk0x00) + g_unk0x4c7650.m_left;
	g_unk0x4c7650.m_bottom = (m_unk0x34.m_unk0x0c - m_unk0x34.m_unk0x04) + g_unk0x4c7650.m_top;

	return &g_unk0x4c7650;
}

// STUB: LEGORACERS 0x00472f40
void ObscureVantage0x58::VTable0x10(undefined4)
{
	// TODO
	STUB(0x00472f40);
}

// STUB: LEGORACERS 0x00472fc0
void ObscureVantage0x58::VTable0x14(undefined4)
{
	// TODO
	STUB(0x00472fc0);
}

// FUNCTION: LEGORACERS 0x004731b0
void ObscureVantage0x58::FUN_004731b0(undefined4& p_param1, undefined4& p_param2)
{
	p_param1 -= m_unk0x34.m_unk0x00;
	p_param2 -= m_unk0x34.m_unk0x04;
}

// FUNCTION: LEGORACERS 0x004731d0
undefined4 ObscureVantage0x58::VTable0x18(undefined4 p_unk0x04)
{
	ObscureVantage0x58* child = m_unk0x08;
	if (VTable0x3c(p_unk0x04)) {
		return TRUE;
	}

	while (child) {
		if (child->VTable0x18(p_unk0x04)) {
			return TRUE;
		}

		child = child->m_unk0x14;
	}

	return FALSE;
}

// STUB: LEGORACERS 0x00473210
undefined4 ObscureVantage0x58::VTable0x1c(SilverDune0x30::Rect*, SilverDune0x30::Rect*)
{
	// TODO
	STUB(0x00473210);
	return 0;
}

// STUB: LEGORACERS 0x004732d0
undefined4 ObscureVantage0x58::VTable0x20(void*, undefined4, undefined4)
{
	// TODO
	STUB(0x004732d0);
	return 0;
}

// STUB: LEGORACERS 0x00473370
undefined4 ObscureVantage0x58::VTable0x24(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	// TODO
	STUB(0x00473370);
	return 0;
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
