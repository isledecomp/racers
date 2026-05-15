#include "imaginarydrillfieldat0x498.h"

#include "utopianpan0xa4.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryDrillFieldAt0x498, 0x2f0)

// FUNCTION: LEGORACERS 0x00482390
ImaginaryDrillFieldAt0x498::ImaginaryDrillFieldAt0x498()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00482420
ImaginaryDrillFieldAt0x498::~ImaginaryDrillFieldAt0x498()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00482490
void ImaginaryDrillFieldAt0x498::Reset()
{
	m_unk0x1a8 = 0;
	m_unk0x2dc = 0;
	::memset(m_unk0x1c0, 0, sizeof(m_unk0x1c0) + sizeof(m_unk0x1d8) + sizeof(m_unk0x1f0));
	::memset(m_unk0x2e0, 0, sizeof(m_unk0x2e0));
	ObscureIcon0x1a8::Reset();
}

// FUNCTION: LEGORACERS 0x00482760
undefined4 ImaginaryDrillFieldAt0x498::VTable0x08()
{
	ObscureVantage0x58* fieldAt0x264 = &m_unk0x264;
	fieldAt0x264->VTable0x08();

	ObscureVantage0x58* fieldAt0x208 = &m_unk0x208;
	fieldAt0x208->VTable0x08();

	return ObscureIcon0x1a8::VTable0x08();
}

// STUB: LEGORACERS 0x00482890
void ImaginaryDrillFieldAt0x498::VTable0x10(Rect* p_rect)
{
	Rect rect = *p_rect;

	if (m_flags & 1) {
		rect.m_right = m_unk0x264.GetRect()->m_right + p_rect->m_left;
		rect.m_bottom = m_unk0x1d8[0]->GetHeight() + p_rect->m_top;
		ObscureIcon0x1a8::VTable0x10(&rect);
	}
}

// FUNCTION: LEGORACERS 0x004828f0
void ImaginaryDrillFieldAt0x498::VTable0x40(ImaginaryInterface* p_eventHandler)
{
	ObscureIcon0x1a8::VTable0x40(p_eventHandler);
	m_unk0x208.SetEventHandler(p_eventHandler);
	m_unk0x264.SetEventHandler(p_eventHandler);
}

// FUNCTION: LEGORACERS 0x00482910
undefined4 ImaginaryDrillFieldAt0x498::VTable0x38(Rect*, Rect*)
{
	m_unk0x208.SetUnk0x58(m_unk0x1d8[m_unk0x19c]);
	m_unk0x208.VTable0x14(&m_unk0x1f0[m_unk0x19c]);
	m_unk0x264.SetUnk0x60(m_unk0x1c0[m_unk0x19c]);
	m_unk0x264.VTable0x14(&m_unk0x174[m_unk0x19c]);

	return 0;
}

// FUNCTION: LEGORACERS 0x00482980
undefined4 ImaginaryDrillFieldAt0x498::VTable0x34(
	OnyxCircularBuffer0x1c::Item* p_item,
	undefined4 p_unk0x08,
	undefined4 p_unk0x0c
)
{
	return ObscureIcon0x1a8::VTable0x34(p_item, p_unk0x08, p_unk0x0c);
}
