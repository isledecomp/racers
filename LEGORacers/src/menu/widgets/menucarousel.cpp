#include "menu/widgets/menucarousel.h"

#include "audio/soundgroupbinding.h"

DECOMP_SIZE_ASSERT(MenuCarousel, 0x78)
DECOMP_SIZE_ASSERT(MenuCarousel::CreateParams, 0x38)
DECOMP_SIZE_ASSERT(MenuScrollCarousel, 0x94)
DECOMP_SIZE_ASSERT(MenuCarouselNavigator, 0x94)

// FUNCTION: LEGORACERS 0x0046c880
MenuCarousel::MenuCarousel()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c8f0
MenuCarousel::~MenuCarousel()
{
	VTable0x08();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c950
void MenuCarousel::Reset()
{
	m_unk0x6c = 0;
	m_unk0x68 = 0;
	m_unk0x60 = 0;
	m_unk0x58 = NULL;
	m_unk0x70 = 0;
	m_unk0x74 = 0;
	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x0046c970
LegoBool32 MenuCarousel::FUN_0046c970(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry)
{
	VTable0x08();
	m_unk0x58 = p_styleEntry;
	m_unk0x5c = p_createParams->m_soundGroupBinding;

	return FUN_00472a60(p_createParams);
}

// FUNCTION: LEGORACERS 0x0046c9a0
LegoS32 MenuCarousel::FUN_0046c9a0(LegoS32 p_index)
{
	if (p_index >= 0) {
		return p_index % m_unk0x68;
	}

	return m_unk0x68 + p_index;
}

// FUNCTION: LEGORACERS 0x0046c9c0
void MenuCarousel::VTable0x14(VisualStateColor* p_visualState)
{
	for (MenuWidget* child = m_firstChild; child; child = child->GetNextSibling()) {
		child->VTable0x14(p_visualState);
	}

	MenuWidget::VTable0x14(p_visualState);
}

// Keep this null-return override in the scene-widget null-return fold group.
#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
MenuWidget* MenuCarousel::VTable0x30(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void MenuCarousel::VTable0x48(VisualStateColor*, VisualStateColor*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void MenuCarousel::VTable0x4c(VisualStateColor*, VisualStateColor*)
{
}

// FUNCTION: LEGORACERS 0x0046d820
MenuScrollCarousel::MenuScrollCarousel()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d890
MenuScrollCarousel::~MenuScrollCarousel()
{
	VTable0x08();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d8f0
void MenuScrollCarousel::Reset()
{
	MenuCarousel::Reset();
	m_unk0x60 = 1;
	m_unk0x78 = NULL;
	m_unk0x90 = 0.0f;
	m_unk0x8c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0046d920
void MenuScrollCarousel::FUN_0046d920(MenuWidget* p_child)
{
	MenuWidget* child = m_firstChild;
	MenuWidget* current = m_unk0x78;
	LegoS32 index = 0;

	if (p_child != current) {
		m_unk0x78 = NULL;

		while (child) {
			if (child == p_child) {
				m_unk0x78 = child;
				m_unk0x6c = index;
				break;
			}

			child = child->GetNextSibling();
			index++;
		}

		if (!m_unk0x70) {
			VTable0x40();
		}
	}
}

// FUNCTION: LEGORACERS 0x0046d960
void MenuScrollCarousel::VTable0x50(undefined4 p_unk0x04)
{
	m_unk0x78 = GetChildByIndex(p_unk0x04);
	m_unk0x6c = p_unk0x04;
	if (!m_unk0x70) {
		VTable0x40();
	}
}

// FUNCTION: LEGORACERS 0x0046d990
void MenuScrollCarousel::VTable0x40()
{
	m_unk0x4c = m_unk0x78->GetRect()->m_left;

	if (m_unk0x58->m_unk0x10) {
		LegoS32 width = m_unk0x34.m_right - m_unk0x34.m_left;
		m_unk0x4c = (m_unk0x4c / width) * width;
	}
}

// FUNCTION: LEGORACERS 0x0046d9c0
void MenuScrollCarousel::FUN_0046d9c0(MenuWidget* p_unk0x04)
{
	p_unk0x04->SetParent(this);
	p_unk0x04->VTable0x14(&m_visualState);
	m_unk0x68++;
	VTable0x5c(p_unk0x04);

	if (m_unk0x68 == 1) {
		VTable0x50(m_unk0x6c);
	}
}

// FUNCTION: LEGORACERS 0x0046da00
void MenuScrollCarousel::FUN_0046da00(MenuWidget* p_child)
{
	MenuWidget* child = p_child->GetNextSibling();
	p_child->RemoveFromParent();
	m_unk0x68--;

	while (child) {
		VTable0x5c(child);
		if (child == m_unk0x78) {
			VTable0x50(m_unk0x6c - 1);
		}

		child = child->GetNextSibling();
	}
}

// FUNCTION: LEGORACERS 0x0046da40
MenuWidget* MenuScrollCarousel::FUN_0046da40(LegoS32 p_index)
{
	MenuWidget* child = GetChildByIndex(p_index);
	FUN_0046da00(child);

	return child;
}

// FUNCTION: LEGORACERS 0x0046da60
void MenuScrollCarousel::FUN_0046da60()
{
	while (m_unk0x68) {
		FUN_0046da40(0);
	}
}

// FUNCTION: LEGORACERS 0x0046da80
void MenuCarouselNavigator::VTable0x5c(MenuWidget* p_child)
{
	Rect rect = *p_child->GetRect();

	MenuStyleTable::CarouselStyle* style = m_unk0x58;
	LegoS32 width = rect.m_right;
	if (style->m_unk0x10) {
		width = m_unk0x34.m_right;
		width -= m_unk0x34.m_left;
	}
	else {
		width -= rect.m_left;
	}

	Rect slot;
	MenuWidget* prev = p_child->GetPrevSibling();
	if (prev) {
		slot.m_left = prev->GetRect()->m_right;

		if (style->m_unk0x10) {
			slot.m_left = ((slot.m_left + width - 1) / width) * width;
		}
	}
	else {
		slot.m_left = 0;
	}

	slot.m_top = rect.m_top;
	slot.m_bottom = rect.m_bottom;
	slot.m_right = slot.m_left + width;

	if (style->m_unk0x10) {
		FUN_00472c80(&slot, &rect);
	}
	else {
		rect = slot;
	}

	p_child->VTable0x10(&rect);
}

// FUNCTION: LEGORACERS 0x0046db40
void MenuCarouselNavigator::VTable0x44(undefined4 p_unk0x04)
{
	LegoS32 count = m_unk0x58->m_unk0x0c;

	m_unk0x74 = count;
	m_unk0x54 |= 1;
	m_unk0x70 = 1;
	LegoFloat divisor = (LegoFloat) count;
	m_unk0x8c = (LegoFloat) (LegoS32) p_unk0x04 / divisor;
	m_unk0x90 = (LegoFloat) m_unk0x4c;
}

// FUNCTION: LEGORACERS 0x0046db80
LegoS32 MenuCarouselNavigator::VTable0x54()
{
	if (!m_unk0x68) {
		return 0;
	}

	if (!m_unk0x70) {
		if (m_unk0x6c >= m_unk0x68 - 1 && !m_unk0x58->m_unk0x14) {
			m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[2]);
			return m_unk0x6c;
		}

		VTable0x44(m_unk0x34.m_right - m_unk0x34.m_left);
		VTable0x50(FUN_0046c9a0(m_unk0x6c + 1));
		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[0]);
	}

	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x0046dbf0
LegoS32 MenuCarouselNavigator::VTable0x58()
{
	if (!m_unk0x68) {
		return 0;
	}

	if (!m_unk0x70) {
		if (m_unk0x6c == 0 && !m_unk0x58->m_unk0x14) {
			m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[2]);
			return m_unk0x6c;
		}

		VTable0x44(m_unk0x34.m_left - m_unk0x34.m_right);
		VTable0x50(FUN_0046c9a0(m_unk0x6c - 1));
		m_unk0x5c->FUN_0046e970(m_unk0x58->m_unk0x00[1]);
	}

	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x0046dc70
MenuWidget* MenuCarouselNavigator::VTable0x38(Rect* p_param1, Rect* p_param2)
{
	Rect* lastChildRect = m_lastChild->GetRect();
	MenuWidget* child = m_firstChild;

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
undefined4 MenuCarouselNavigator::VTable0x3c(undefined4 p_unk0x04)
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

		LegoFloat step = m_unk0x8c;
		LegoFloat scaled = (LegoFloat) (LegoS32) p_unk0x04;
		LegoFloat delta = step * scaled;

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
