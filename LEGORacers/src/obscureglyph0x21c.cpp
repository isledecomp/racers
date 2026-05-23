#include "obscureglyph0x21c.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ObscureGlyph0x21c, 0x21c)

// FUNCTION: LEGORACERS 0x00466260
ObscureGlyph0x21c::ObscureGlyph0x21c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004662e0
ObscureGlyph0x21c::~ObscureGlyph0x21c()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00466340
void ObscureGlyph0x21c::Reset()
{
	::memset(m_unk0x1a8, 0, sizeof(m_unk0x1a8));

	m_unk0x1c0.VTable0x08();
	ObscureIcon0x1a8::Reset();
}

// FUNCTION: LEGORACERS 0x00466450
LegoBool32 ObscureGlyph0x21c::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (m_flags & 1) {
		return ObscureIcon0x1a8::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00466470
undefined4 ObscureGlyph0x21c::VTable0x38(Rect*, Rect*)
{
	Rect rect;
	rect.m_top = 0;
	rect.m_left = 0;
	rect.m_right = m_unk0x34.m_right - m_unk0x34.m_left;
	rect.m_bottom = m_unk0x34.m_bottom - m_unk0x34.m_top;

	m_unk0x1c0.VTable0x10(&rect);
	m_unk0x1c0.SetUnk0x58(m_unk0x1a8[m_visualStateIndex]);
	m_unk0x1c0.VTable0x14(&m_unk0x174[m_visualStateIndex]);

	return 0;
}
