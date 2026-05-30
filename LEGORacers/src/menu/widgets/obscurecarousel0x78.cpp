#include "menu/widgets/obscurecarousel0x78.h"

#include "audio/soundgroupbinding.h"

DECOMP_SIZE_ASSERT(ObscureCarousel0x78, 0x78)
DECOMP_SIZE_ASSERT(ObscureCarousel0x78::CreateParams0x38, 0x38)
DECOMP_SIZE_ASSERT(ObscureCarousel0x78::StyleEntry0x18, 0x18)
DECOMP_SIZE_ASSERT(ObscureCarousel0x94, 0x94)
DECOMP_SIZE_ASSERT(ObscureCarouselNavigator0x94, 0x94)

// FUNCTION: LEGORACERS 0x0046c880
ObscureCarousel0x78::ObscureCarousel0x78()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c8f0
ObscureCarousel0x78::~ObscureCarousel0x78()
{
	VTable0x08();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c950
void ObscureCarousel0x78::Reset()
{
	m_unk0x6c = 0;
	m_unk0x68 = 0;
	m_unk0x60 = 0;
	m_unk0x58 = NULL;
	m_unk0x70 = 0;
	m_unk0x74 = 0;
	ObscureVantage0x58::Reset();
}

// FUNCTION: LEGORACERS 0x0046c970
LegoBool32 ObscureCarousel0x78::FUN_0046c970(CreateParams0x38* p_createParams, StyleEntry0x18* p_styleEntry)
{
	VTable0x08();
	m_unk0x58 = p_styleEntry;
	m_unk0x5c = p_createParams->m_soundGroupBinding;

	return FUN_00472a60(p_createParams);
}

// FUNCTION: LEGORACERS 0x0046c9a0
LegoS32 ObscureCarousel0x78::FUN_0046c9a0(LegoS32 p_index)
{
	if (p_index >= 0) {
		return p_index % m_unk0x68;
	}

	return m_unk0x68 + p_index;
}

// FUNCTION: LEGORACERS 0x0046c9c0
void ObscureCarousel0x78::VTable0x14(VisualState0x4* p_visualState)
{
	for (ObscureVantage0x58* child = m_firstChild; child; child = child->GetNextSibling()) {
		child->VTable0x14(p_visualState);
	}

	ObscureVantage0x58::VTable0x14(p_visualState);
}

#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
ObscureVantage0x58* ObscureCarousel0x78::VTable0x30(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void ObscureCarousel0x78::VTable0x48(undefined4*, undefined4*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void ObscureCarousel0x78::VTable0x4c(undefined4*, undefined4*)
{
}

// FUNCTION: LEGORACERS 0x0046d820
ObscureCarousel0x94::ObscureCarousel0x94()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d890
ObscureCarousel0x94::~ObscureCarousel0x94()
{
	VTable0x08();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d8f0
void ObscureCarousel0x94::Reset()
{
	ObscureCarousel0x78::Reset();
	m_unk0x60 = 1;
	m_unk0x78 = NULL;
	m_unk0x90 = 0.0f;
	m_unk0x8c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0046d960
void ObscureCarousel0x94::VTable0x50(undefined4 p_unk0x04)
{
	m_unk0x78 = FUN_00472ef0(p_unk0x04);
	m_unk0x6c = p_unk0x04;
	if (!m_unk0x70) {
		VTable0x40();
	}
}

// FUNCTION: LEGORACERS 0x0046d990
void ObscureCarousel0x94::VTable0x40()
{
	m_unk0x4c = m_unk0x78->GetRect()->m_left;

	if (m_unk0x58->m_unk0x10) {
		LegoS32 width = m_unk0x34.m_right - m_unk0x34.m_left;
		m_unk0x4c = (m_unk0x4c / width) * width;
	}
}

// FUNCTION: LEGORACERS 0x0046d9c0
void ObscureCarousel0x94::FUN_0046d9c0(ObscureVantage0x58* p_unk0x04)
{
	p_unk0x04->SetParent(this);
	p_unk0x04->VTable0x14(&m_visualState);
	m_unk0x68++;
	VTable0x5c(p_unk0x04);

	if (m_unk0x68 == 1) {
		VTable0x50(m_unk0x6c);
	}
}

// STUB: LEGORACERS 0x0046da80
void ObscureCarouselNavigator0x94::VTable0x5c(ObscureVantage0x58* p_child)
{
	Rect rect = *p_child->GetRect();

	StyleEntry0x18* style = m_unk0x58;

	LegoS32 right = rect.m_right;
	LegoS32 left = rect.m_left;
	if (style->m_unk0x10) {
		right = m_unk0x34.m_right;
		left = m_unk0x34.m_left;
	}

	LegoS32 width = right - left;

	Rect slot;
	ObscureVantage0x58* prev = p_child->GetPrevSibling();
	if (prev) {
		left = prev->GetRect()->m_right;
		slot.m_left = left;

		if (style->m_unk0x10) {
			left = ((left + width - 1) / width) * width;
			slot.m_left = left;
		}
	}
	else {
		left = 0;
		slot.m_left = left;
	}

	slot.m_top = rect.m_top;
	slot.m_bottom = rect.m_bottom;
	slot.m_right = left + width;

	if (style->m_unk0x10) {
		FUN_00472c80(&slot, &rect);
	}
	else {
		rect = slot;
	}

	p_child->VTable0x10(&rect);
}

// FUNCTION: LEGORACERS 0x0046db40
void ObscureCarouselNavigator0x94::VTable0x44(undefined4 p_unk0x04)
{
	LegoS32 count = m_unk0x58->m_unk0x0c;

	m_unk0x74 = count;
	m_unk0x54 |= 1;
	m_unk0x70 = 1;
	m_unk0x8c = (LegoFloat) (LegoS32) p_unk0x04 / count;
	m_unk0x90 = (LegoFloat) m_unk0x4c;
}

// FUNCTION: LEGORACERS 0x0046db80
LegoS32 ObscureCarouselNavigator0x94::VTable0x54()
{
	if (!m_unk0x68) {
		return 0;
	}

	if (!m_unk0x70) {
		if (m_unk0x6c >= m_unk0x68 - 1 && !m_unk0x58->m_unk0x14) {
			m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x08);
			return m_unk0x6c;
		}

		VTable0x44(m_unk0x34.m_right - m_unk0x34.m_left);
		VTable0x50(FUN_0046c9a0(m_unk0x6c + 1));
		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00);
	}

	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x0046dbf0
LegoS32 ObscureCarouselNavigator0x94::VTable0x58()
{
	if (!m_unk0x68) {
		return 0;
	}

	if (!m_unk0x70) {
		if (m_unk0x6c == 0 && !m_unk0x58->m_unk0x14) {
			m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x08);
			return m_unk0x6c;
		}

		VTable0x44(m_unk0x34.m_left - m_unk0x34.m_right);
		VTable0x50(FUN_0046c9a0(m_unk0x6c - 1));
		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x04);
	}

	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x0046dc70
ObscureVantage0x58* ObscureCarouselNavigator0x94::VTable0x38(Rect* p_param1, Rect* p_param2)
{
	Rect* lastChildRect = m_lastChild->GetRect();
	ObscureVantage0x58* child = m_firstChild;

	if (!m_unk0x58->m_unk0x14 || !child) {
		return NULL;
	}

	do {
		child->VTable0x1c(p_param1, p_param2);
		child = child->GetNextSibling();
	} while (child);

	LegoS32 width;
	if (m_unk0x58->m_unk0x10) {
		width = m_unk0x34.m_right - m_unk0x34.m_left;
	}
	else {
		width = lastChildRect->m_right - lastChildRect->m_left;
	}

	LegoS32 savedLeft = m_unk0x4c;
	LegoS32 roundedExtent = ((lastChildRect->m_right + width - 1) / width) * width;

	if (width + savedLeft > roundedExtent) {
		m_unk0x4c = 0;

		Rect local1 = *p_param1;
		Rect local2;
		local2.m_top = p_param2->m_top;
		local2.m_bottom = p_param2->m_bottom;
		local2.m_right = p_param2->m_right;
		local2.m_left = p_param2->m_left + (roundedExtent - savedLeft);

		local1.m_left = 0;
		local1.m_right = p_param2->m_right - local2.m_left;

		for (child = m_firstChild; child; child = child->GetNextSibling()) {
			child->VTable0x1c(&local1, &local2);
		}

		m_unk0x4c = savedLeft;
	}

	return this;
}

// FUNCTION: LEGORACERS 0x0046dd80
undefined4 ObscureCarouselNavigator0x94::VTable0x3c(undefined4 p_unk0x04)
{
	if (m_unk0x70) {
		LegoS32 remaining = m_unk0x74;

		if (remaining == 0) {
			m_unk0x70 = 0;
			m_unk0x54 &= 0xfe;
			VTable0x40();

			if (m_unk0x28) {
				m_unk0x28->VTable0x10(this);
			}

			return 0;
		}

		if (p_unk0x04 > (undefined4) remaining) {
			p_unk0x04 = remaining;
		}

		LegoFloat delta = m_unk0x8c * (LegoFloat) (LegoS32) p_unk0x04;

		m_unk0x74 = remaining - p_unk0x04;
		m_unk0x90 = m_unk0x90 + delta;

		if (m_unk0x90 < 0.0f) {
			LegoS32 extent;
			if (m_unk0x58->m_unk0x10) {
				LegoS32 left = m_unk0x34.m_left;
				LegoS32 width = m_unk0x34.m_right - left;
				extent = ((m_lastChild->GetRect()->m_right - left + m_unk0x34.m_right - 1) / width) * width;
			}
			else {
				extent = m_lastChild->GetRect()->m_right;
			}

			m_unk0x90 = m_unk0x90 + (LegoFloat) extent;
		}

		m_unk0x4c = (LegoS32) m_unk0x90;
	}

	return 0;
}
