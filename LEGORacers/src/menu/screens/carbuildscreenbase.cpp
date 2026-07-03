#include "menu/screens/carbuildscreenbase.h"

#include "decomp.h"
#include "font/golfont.h"
#include "render/gold3drenderdevice.h"

#include <math.h>

DECOMP_SIZE_ASSERT(CarBuildScreenBase, 0x3b4)
DECOMP_SIZE_ASSERT(CarBuildScreenBase::EventItem, 0x40)

// FUNCTION: LEGORACERS 0x00474c40
void CarBuildScreenBase::Reset()
{
	m_layoutDirty = TRUE;
	m_hoverMs = 0;
	m_tooltipMs = 0;
	m_quickShowMs = 0;
	m_hoverIcon = NULL;
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00474c70
undefined4 CarBuildScreenBase::OnWidgetKeyUp(MenuWidget* p_vantage, void* p_item, undefined4, undefined4)
{
	EventItem* item = static_cast<EventItem*>(p_item);

	if (m_tooltipMs) {
		LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
		LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
		Rect rect = *m_hoverIcon->GetGlobalRect();

		if (!m_hoverIcon->PointInRect(&rect, x, y)) {
			HideTooltip();
		}
	}
	else {
		if (m_selectedIcon != m_hoverIcon) {
			m_hoverMs = 0;

			if (m_selectedIcon == p_vantage) {
				m_hoverIcon = m_selectedIcon;
			}
			else if (m_selectedIcon) {
				LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
				LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
				Rect rect = *m_selectedIcon->GetGlobalRect();

				if (m_selectedIcon->PointInRect(&rect, x, y)) {
					m_hoverIcon = m_selectedIcon;
				}
				else {
					m_hoverIcon = NULL;
				}
			}
			else {
				m_hoverIcon = NULL;
			}
		}

		if (m_selectedIcon != p_vantage && m_hoverIcon) {
			LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
			LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
			Rect rect = *m_hoverIcon->GetGlobalRect();

			if (!m_hoverIcon->PointInRect(&rect, x, y)) {
				m_hoverIcon = NULL;
				m_hoverMs = 0;
			}
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00474e00 FOLDED
LegoBool32 CarBuildScreenBase::HandleKeyDown(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_cursorX,
	undefined4 p_cursorY
)
{
	if (!m_tooltipMs) {
		ResetTooltip();
	}

	return MenuGameScreen::HandleKeyDown(p_source, p_event, p_cursorX, p_cursorY);
}

// FUNCTION: LEGORACERS 0x00474e00 FOLDED
LegoBool32 CarBuildScreenBase::HandleKeyUp(
	MenuWidget* p_source,
	InputEventQueue::Event* p_event,
	undefined4 p_cursorX,
	undefined4 p_cursorY
)
{
	if (!m_tooltipMs) {
		ResetTooltip();
	}

	return MenuGameScreen::HandleKeyUp(p_source, p_event, p_cursorX, p_cursorY);
}

// FUNCTION: LEGORACERS 0x00474e40
void CarBuildScreenBase::ResetTooltip()
{
	m_hoverMs = 0;
	m_hoverIcon = NULL;
	m_tooltipMs = 0;
	m_quickShowMs = 0;
	m_wasVisible = FALSE;
}

// FUNCTION: LEGORACERS 0x00474e70
void CarBuildScreenBase::ShowTooltip(MenuIcon* p_icon)
{
	if (m_tooltipMs) {
		HideTooltip();
	}

	m_tooltipStringId = 0;
	if (p_icon) {
		m_tooltipStringId = p_icon->GetHelpStringId();
	}

	m_tooltipIcon = p_icon;
	m_quickShowMs = 0;
	m_layoutDirty = TRUE;
	m_wasVisible = FALSE;

	if (m_tooltipStringId) {
		m_tooltipMs = TRUE;
		return;
	}

	m_tooltipMs = -1;
	SuppressTooltip();
}

// FUNCTION: LEGORACERS 0x00474ef0
void CarBuildScreenBase::HideTooltip()
{
	m_hoverIcon = NULL;
	m_hoverMs = 0;
	m_tooltipMs = 0;

	if (m_wasVisible) {
		m_quickShowMs = 1;
	}
	else {
		m_quickShowMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x00474f20
void CarBuildScreenBase::SuppressTooltip()
{
	m_tooltipMs = -1;
	m_hoverMs = 0;
	m_quickShowMs = 0;
	m_wasVisible = FALSE;
}

// FUNCTION: LEGORACERS 0x00474f40
LegoBool32 CarBuildScreenBase::Update(undefined4 p_elapsed)
{
	if (m_quickShowMs) {
		m_quickShowMs += p_elapsed;

		if (m_quickShowMs > 250) {
			m_quickShowMs = 0;
		}
	}

	if (m_hoverIcon) {
		if (m_tooltipMs == 0) {
			m_hoverMs += p_elapsed;

			if (m_hoverMs >= 3000 || m_quickShowMs) {
				m_hoverMs = 3000;
				ShowTooltip(m_hoverIcon);
				m_wasVisible = TRUE;
				return MenuGameScreen::Update(p_elapsed);
			}
		}
		else if (m_tooltipMs > 0) {
			m_tooltipMs += p_elapsed;

			if (m_tooltipMs > 20000) {
				SuppressTooltip();
				return MenuGameScreen::Update(p_elapsed);
			}
		}
	}
	else if (m_tooltipMs) {
		HideTooltip();
	}

	return MenuGameScreen::Update(p_elapsed);
}

// STUB: LEGORACERS 0x00475010
LegoBool32 CarBuildScreenBase::Draw(Rect* p_clipRect, Rect* p_sourceRect)
{
	LegoBool32 result = MenuScreen::Draw(p_clipRect, p_sourceRect);

	if (m_tooltipMs <= 0) {
		return result;
	}

	if (m_layoutDirty) {
		Rect* targetRect = m_hoverIcon->GetGlobalRect();
		LegoS32 targetLeft = targetRect->m_left;
		LegoS32 targetTop = targetRect->m_top;
		LegoS32 targetRight = targetRect->m_right;
		LegoS32 targetBottom = targetRect->m_bottom;
		m_tooltipFont = GetHelpFont(m_tooltipStringId);
		m_tooltipString = GetHelpString(m_tooltipStringId);

		if (m_tooltipFont == NULL || m_tooltipString == NULL) {
			SuppressTooltip();
			return result;
		}

		GetTooltipLayout(&m_tooltipX, &m_tooltipY, &m_tooltipWrapWidth, &m_tooltipLineSpacing);

		LegoS32 width;
		LegoS32 height;

		if (!m_tooltipWrapWidth) {
			LegoS32 fontHeight;
			m_tooltipFont->MeasureString(m_tooltipString, &width, &fontHeight);
			m_tooltipLineSpacing = 1;

			LegoFloat measuredWidth = static_cast<LegoFloat>(width);
			m_tooltipWrapWidth =
				static_cast<LegoS32>(::sqrt((static_cast<LegoFloat>(fontHeight + 1) * 3.0f) * measuredWidth));

			LegoS32 maxWidth = p_clipRect->m_right - (fontHeight * 2) - p_clipRect->m_left;
			if (m_tooltipWrapWidth > maxWidth) {
				m_tooltipWrapWidth = maxWidth;
			}

			LegoS32 minWidth = static_cast<LegoS32>(static_cast<LegoU32>(maxWidth) >> 3);
			if (m_tooltipWrapWidth < minWidth) {
				m_tooltipWrapWidth = minWidth;
			}

			m_tooltipFont
				->MeasureString(m_tooltipString, m_tooltipWrapWidth, m_tooltipLineSpacing, 1.0f, 1.0f, &width, &height);

			LegoU32 halfFontHeight = static_cast<LegoU32>(fontHeight) >> 1;
			LegoS32 negativeHalfFontHeight = -static_cast<LegoS32>(halfFontHeight);
			m_tooltipRect.m_top = negativeHalfFontHeight;
			m_tooltipRect.m_left = negativeHalfFontHeight;
			m_tooltipRect.m_right = width + halfFontHeight;
			m_tooltipRect.m_bottom = height + halfFontHeight;

			if (width + fontHeight * 2 < p_clipRect->m_right - targetRight) {
				m_tooltipX = targetRight + fontHeight;
				m_tooltipY = static_cast<LegoS32>((static_cast<LegoU32>((targetBottom - height) + targetTop)) >> 1);

				if (m_tooltipY < p_clipRect->m_top + fontHeight) {
					m_tooltipY = p_clipRect->m_top + fontHeight;
				}
				else if (m_tooltipY > p_clipRect->m_bottom - height - fontHeight) {
					m_tooltipY = p_clipRect->m_bottom - height - fontHeight;
				}
			}
			else if (height + fontHeight * 2 < p_clipRect->m_bottom - targetBottom) {
				m_tooltipY = targetBottom + fontHeight;
				m_tooltipX = static_cast<LegoS32>((static_cast<LegoU32>((targetRight - width) + targetLeft)) >> 1);

				if (m_tooltipX < p_clipRect->m_left + fontHeight) {
					m_tooltipX = p_clipRect->m_left + fontHeight;
				}
				else if (m_tooltipX > p_clipRect->m_right - width - fontHeight) {
					m_tooltipX = p_clipRect->m_right - width - fontHeight;
				}
			}
			else if (height + fontHeight * 2 < targetTop - p_clipRect->m_top) {
				m_tooltipY = targetTop - height - fontHeight;
				m_tooltipX = static_cast<LegoS32>((static_cast<LegoU32>((targetRight - width) + targetLeft)) >> 1);

				if (m_tooltipX < p_clipRect->m_left + fontHeight) {
					m_tooltipX = p_clipRect->m_left + fontHeight;
				}
				else if (m_tooltipX > p_clipRect->m_right - width - fontHeight) {
					m_tooltipX = p_clipRect->m_right - width - fontHeight;
				}
			}
			else if (width + fontHeight * 2 < targetLeft - p_clipRect->m_left) {
				m_tooltipX = targetLeft - width - fontHeight;
				m_tooltipY = static_cast<LegoS32>((static_cast<LegoU32>((targetBottom - height) + targetTop)) >> 1);

				if (m_tooltipY < p_clipRect->m_top + fontHeight) {
					m_tooltipY = p_clipRect->m_top + fontHeight;
				}
				else if (m_tooltipY > p_clipRect->m_bottom - height - fontHeight) {
					m_tooltipY = p_clipRect->m_bottom - height - fontHeight;
				}
			}
			else {
				m_tooltipX = static_cast<LegoS32>(
								 (static_cast<LegoU32>((p_clipRect->m_right - p_clipRect->m_left) - width)) >> 1
							 ) +
							 p_clipRect->m_left;
				m_tooltipY = static_cast<LegoS32>(
								 (static_cast<LegoU32>((p_clipRect->m_bottom - p_clipRect->m_top) - height)) >> 1
							 ) +
							 p_clipRect->m_top;
			}

			m_tooltipRect.m_left += m_tooltipX;
			m_tooltipRect.m_right += m_tooltipX;
			m_tooltipRect.m_top += m_tooltipY;
			m_tooltipRect.m_bottom += m_tooltipY;
		}
		else {
			m_tooltipFont
				->MeasureString(m_tooltipString, m_tooltipWrapWidth, m_tooltipLineSpacing, 1.0f, 1.0f, &width, &height);
		}

		m_layoutDirty = FALSE;
	}

	ColorRGBA color;
	color.m_red = 0x20;
	color.m_grn = 0x1c;
	color.m_blu = 0xe0;
	color.m_alp = 0xff;

	m_tooltipRect.m_top -= 4;
	m_tooltipRect.m_left -= 4;
	m_tooltipRect.m_right += 4;
	m_tooltipRect.m_bottom += 4;
	m_renderer->DrawRectangle(m_tooltipRect, 0.0f, color, color, color, color, 0);

	m_tooltipRect.m_left += 4;
	m_tooltipRect.m_top += 4;
	m_tooltipRect.m_right -= 4;
	m_tooltipRect.m_bottom -= 4;
	color.m_red = 0;
	color.m_grn = 0;
	color.m_blu = 0x38;
	m_renderer->DrawRectangle(m_tooltipRect, 0.0f, color, color, color, color, 0);

	m_tooltipFont->DrawString(
		m_tooltipString,
		m_renderer,
		m_tooltipX,
		m_tooltipY,
		m_tooltipWrapWidth,
		m_tooltipLineSpacing,
		1.0f,
		1.0f,
		NULL,
		NULL,
		0
	);
	return result;
}
