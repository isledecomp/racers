#include "menu/widgets/menucarousel.h"

#include "audio/soundgroupbinding.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menuscrollcarousel.h"

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
	Destroy();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c950
void MenuCarousel::Reset()
{
	m_selectedIndex = 0;
	m_itemCount = 0;
	m_slotCount = 0;
	m_style = NULL;
	m_scrolling = 0;
	m_scrollDurationMs = 0;
	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x0046c970
LegoBool32 MenuCarousel::Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry)
{
	Destroy();
	m_style = p_styleEntry;
	m_soundGroupBinding = p_createParams->m_soundGroupBinding;

	return CreateWidget(p_createParams);
}

// FUNCTION: LEGORACERS 0x0046c9a0
LegoS32 MenuCarousel::WrapIndex(LegoS32 p_index)
{
	if (p_index >= 0) {
		return p_index % m_itemCount;
	}

	return m_itemCount + p_index;
}

// FUNCTION: LEGORACERS 0x0046c9c0
void MenuCarousel::SetColor(VisualStateColor* p_visualState)
{
	for (MenuWidget* child = m_firstChild; child; child = child->GetNextSibling()) {
		child->SetColor(p_visualState);
	}

	MenuWidget::SetColor(p_visualState);
}

// Keep this null-return override in the scene-widget null-return fold group.
#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
MenuWidget* MenuCarousel::OnKeyDown(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void MenuCarousel::SetItemColors(VisualStateColor*, VisualStateColor*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void MenuCarousel::SetFocusedItemColors(VisualStateColor*, VisualStateColor*)
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
	Destroy();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d8f0
void MenuScrollCarousel::Reset()
{
	MenuCarousel::Reset();
	m_slotCount = 1;
	m_selectedChild = NULL;
	m_scrollPosition = 0.0f;
	m_scrollSpeed = 0.0f;
}

// FUNCTION: LEGORACERS 0x0046d920
void MenuScrollCarousel::SelectChild(MenuWidget* p_child)
{
	MenuWidget* child = m_firstChild;
	MenuWidget* current = m_selectedChild;
	LegoS32 index = 0;

	if (p_child != current) {
		m_selectedChild = NULL;

		while (child) {
			if (child == p_child) {
				m_selectedChild = child;
				m_selectedIndex = index;
				break;
			}

			child = child->GetNextSibling();
			index++;
		}

		if (!m_scrolling) {
			SnapToSelection();
		}
	}
}

// FUNCTION: LEGORACERS 0x0046d960
void MenuScrollCarousel::SetSelection(undefined4 p_index)
{
	m_selectedChild = GetChildByIndex(p_index);
	m_selectedIndex = p_index;
	if (!m_scrolling) {
		SnapToSelection();
	}
}

// FUNCTION: LEGORACERS 0x0046d990
void MenuScrollCarousel::SnapToSelection()
{
	m_offsetX = m_selectedChild->GetRect()->m_left;

	if (m_style->m_pageMode) {
		LegoS32 width = m_rect.m_right - m_rect.m_left;
		m_offsetX = (m_offsetX / width) * width;
	}
}

// FUNCTION: LEGORACERS 0x0046d9c0
void MenuScrollCarousel::AddItem(MenuWidget* p_item)
{
	p_item->SetParent(this);
	p_item->SetColor(&m_visualState);
	m_itemCount++;
	LayoutItem(p_item);

	if (m_itemCount == 1) {
		SetSelection(m_selectedIndex);
	}
}

// FUNCTION: LEGORACERS 0x0046da00
void MenuScrollCarousel::RemoveItem(MenuWidget* p_child)
{
	MenuWidget* child = p_child->GetNextSibling();
	p_child->RemoveFromParent();
	m_itemCount--;

	while (child) {
		LayoutItem(child);
		if (child == m_selectedChild) {
			SetSelection(m_selectedIndex - 1);
		}

		child = child->GetNextSibling();
	}
}

// FUNCTION: LEGORACERS 0x0046da40
MenuWidget* MenuScrollCarousel::RemoveItemByIndex(LegoS32 p_index)
{
	MenuWidget* child = GetChildByIndex(p_index);
	RemoveItem(child);

	return child;
}

// FUNCTION: LEGORACERS 0x0046da60
void MenuScrollCarousel::RemoveAllItems()
{
	while (m_itemCount) {
		RemoveItemByIndex(0);
	}
}

// FUNCTION: LEGORACERS 0x0046da80
void MenuCarouselNavigator::LayoutItem(MenuWidget* p_child)
{
	Rect rect = *p_child->GetRect();

	MenuStyleTable::CarouselStyle* style = m_style;
	LegoS32 width = rect.m_right;
	if (style->m_pageMode) {
		width = m_rect.m_right;
		width -= m_rect.m_left;
	}
	else {
		width -= rect.m_left;
	}

	Rect slot;
	MenuWidget* prev = p_child->GetPrevSibling();
	if (prev) {
		slot.m_left = prev->GetRect()->m_right;

		if (style->m_pageMode) {
			slot.m_left = ((slot.m_left + width - 1) / width) * width;
		}
	}
	else {
		slot.m_left = 0;
	}

	slot.m_top = rect.m_top;
	slot.m_bottom = rect.m_bottom;
	slot.m_right = slot.m_left + width;

	if (style->m_pageMode) {
		CenterRectIn(&slot, &rect);
	}
	else {
		rect = slot;
	}

	p_child->SetRect(&rect);
}

// FUNCTION: LEGORACERS 0x0046db40
void MenuCarouselNavigator::StartScroll(undefined4 p_distance)
{
	LegoS32 count = m_style->m_scrollDurationMs;

	m_scrollDurationMs = count;
	m_animFlags |= 1;
	m_scrolling = 1;
	LegoFloat divisor = (LegoFloat) count;
	m_scrollSpeed = (LegoFloat) (LegoS32) p_distance / divisor;
	m_scrollPosition = (LegoFloat) m_offsetX;
}

// FUNCTION: LEGORACERS 0x0046db80
LegoS32 MenuCarouselNavigator::ScrollNext()
{
	if (!m_itemCount) {
		return 0;
	}

	if (!m_scrolling) {
		if (m_selectedIndex >= m_itemCount - 1 && !m_style->m_wrap) {
			m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[2]);
			return m_selectedIndex;
		}

		StartScroll(m_rect.m_right - m_rect.m_left);
		SetSelection(WrapIndex(m_selectedIndex + 1));
		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[0]);
	}

	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x0046dbf0
LegoS32 MenuCarouselNavigator::ScrollPrevious()
{
	if (!m_itemCount) {
		return 0;
	}

	if (!m_scrolling) {
		if (m_selectedIndex == 0 && !m_style->m_wrap) {
			m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[2]);
			return m_selectedIndex;
		}

		StartScroll(m_rect.m_left - m_rect.m_right);
		SetSelection(WrapIndex(m_selectedIndex - 1));
		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[1]);
	}

	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x0046dc70
MenuWidget* MenuCarouselNavigator::DrawSelf(Rect* p_param1, Rect* p_param2)
{
	Rect* lastChildRect = m_lastChild->GetRect();
	MenuWidget* child = m_firstChild;

	if (!m_style->m_wrap || !child) {
		return NULL;
	}

	do {
		child->Draw(p_param1, p_param2);
		child = child->GetNextSibling();
	} while (child);

	LegoS32 width;
	if (m_style->m_pageMode) {
		width = m_rect.m_right - m_rect.m_left;
	}
	else {
		width = lastChildRect->m_right - lastChildRect->m_left;
	}

	LegoS32 savedLeft = m_offsetX;
	LegoS32 roundedExtent = ((lastChildRect->m_right + width - 1) / width) * width;

	if (width + savedLeft > roundedExtent) {
		m_offsetX = 0;

		Rect local1 = *p_param1;
		Rect local2;
		local2.m_top = p_param2->m_top;
		local2.m_bottom = p_param2->m_bottom;
		local2.m_right = p_param2->m_right;
		local2.m_left = p_param2->m_left + (roundedExtent - savedLeft);

		local1.m_left = 0;
		local1.m_right = p_param2->m_right - local2.m_left;

		for (child = m_firstChild; child; child = child->GetNextSibling()) {
			child->Draw(&local1, &local2);
		}

		m_offsetX = savedLeft;
	}

	return this;
}

// FUNCTION: LEGORACERS 0x0046dd80
undefined4 MenuCarouselNavigator::OnEvent(undefined4 p_elapsedMs)
{
	if (m_scrolling) {
		LegoS32 remaining = m_scrollDurationMs;

		if (remaining == 0) {
			m_scrolling = 0;
			m_animFlags &= 0xfe;
			SnapToSelection();

			if (m_notifyHandler) {
				m_notifyHandler->OnCarouselSettled(this);
			}

			return 0;
		}

		if (p_elapsedMs > (undefined4) remaining) {
			p_elapsedMs = remaining;
		}

		LegoFloat step = m_scrollSpeed;
		LegoFloat scaled = (LegoFloat) (LegoS32) p_elapsedMs;
		LegoFloat delta = step * scaled;

		m_scrollDurationMs = remaining - p_elapsedMs;
		m_scrollPosition = m_scrollPosition + delta;

		if (m_scrollPosition < 0.0f) {
			LegoS32 extent;
			if (m_style->m_pageMode) {
				LegoS32 left = m_rect.m_left;
				LegoS32 width = m_rect.m_right - left;
				extent = ((m_lastChild->GetRect()->m_right - left + m_rect.m_right - 1) / width) * width;
			}
			else {
				extent = m_lastChild->GetRect()->m_right;
			}

			m_scrollPosition = m_scrollPosition + (LegoFloat) extent;
		}

		m_offsetX = (LegoS32) m_scrollPosition;
	}

	return 0;
}
