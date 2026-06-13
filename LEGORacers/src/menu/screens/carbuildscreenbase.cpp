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
	m_unk0x37d = TRUE;
	m_unk0x368 = 0;
	m_unk0x36c = 0;
	m_unk0x370 = 0;
	m_unk0x374 = NULL;
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00474c70
undefined4 CarBuildScreenBase::VTable0x14(MenuWidget* p_vantage, void* p_item, undefined4, undefined4)
{
	EventItem* item = static_cast<EventItem*>(p_item);

	if (m_unk0x36c) {
		LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
		LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
		Rect rect = *m_unk0x374->GetGlobalRect();

		if (!m_unk0x374->FUN_00473a20(&rect, x, y)) {
			FUN_00474ef0();
		}
	}
	else {
		if (m_unk0x358 != m_unk0x374) {
			m_unk0x368 = 0;

			if (m_unk0x358 == p_vantage) {
				m_unk0x374 = m_unk0x358;
			}
			else if (m_unk0x358) {
				LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
				LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
				Rect rect = *m_unk0x358->GetGlobalRect();

				if (m_unk0x358->FUN_00473a20(&rect, x, y)) {
					m_unk0x374 = m_unk0x358;
				}
				else {
					m_unk0x374 = NULL;
				}
			}
			else {
				m_unk0x374 = NULL;
			}
		}

		if (m_unk0x358 != p_vantage && m_unk0x374) {
			LegoS32 x = item->m_rect.m_right + item->m_rect.m_left;
			LegoS32 y = item->m_rect.m_bottom + item->m_rect.m_top;
			Rect rect = *m_unk0x374->GetGlobalRect();

			if (!m_unk0x374->FUN_00473a20(&rect, x, y)) {
				m_unk0x374 = NULL;
				m_unk0x368 = 0;
			}
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00474e00 FOLDED
LegoBool32 CarBuildScreenBase::VTable0x18(
	MenuWidget* p_unk0x04,
	InputEventQueue::Event* p_unk0x08,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (!m_unk0x36c) {
		FUN_00474e40();
	}

	return MenuGameScreen::VTable0x18(p_unk0x04, p_unk0x08, p_unk0x0c, p_unk0x10);
}

// FUNCTION: LEGORACERS 0x00474e00 FOLDED
LegoBool32 CarBuildScreenBase::VTable0x1c(
	MenuWidget* p_unk0x04,
	InputEventQueue::Event* p_unk0x08,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (!m_unk0x36c) {
		FUN_00474e40();
	}

	return MenuGameScreen::VTable0x1c(p_unk0x04, p_unk0x08, p_unk0x0c, p_unk0x10);
}

// FUNCTION: LEGORACERS 0x00474e40
void CarBuildScreenBase::FUN_00474e40()
{
	m_unk0x368 = 0;
	m_unk0x374 = NULL;
	m_unk0x36c = 0;
	m_unk0x370 = 0;
	m_unk0x37c = FALSE;
}

// FUNCTION: LEGORACERS 0x00474e70
void CarBuildScreenBase::FUN_00474e70(MenuIcon* p_icon)
{
	if (m_unk0x36c) {
		FUN_00474ef0();
	}

	m_unk0x37e = 0;
	if (p_icon) {
		m_unk0x37e = p_icon->GetUnk0x168();
	}

	m_unk0x378 = p_icon;
	m_unk0x370 = 0;
	m_unk0x37d = TRUE;
	m_unk0x37c = FALSE;

	if (m_unk0x37e) {
		m_unk0x36c = TRUE;
		return;
	}

	m_unk0x36c = -1;
	FUN_00474f20();
}

// FUNCTION: LEGORACERS 0x00474ef0
void CarBuildScreenBase::FUN_00474ef0()
{
	m_unk0x374 = NULL;
	m_unk0x368 = 0;
	m_unk0x36c = 0;

	if (m_unk0x37c) {
		m_unk0x370 = 1;
	}
	else {
		m_unk0x370 = 0;
	}
}

// FUNCTION: LEGORACERS 0x00474f20
void CarBuildScreenBase::FUN_00474f20()
{
	m_unk0x36c = -1;
	m_unk0x368 = 0;
	m_unk0x370 = 0;
	m_unk0x37c = FALSE;
}

// FUNCTION: LEGORACERS 0x00474f40
LegoBool32 CarBuildScreenBase::VTable0x78(undefined4 p_elapsed)
{
	if (m_unk0x370) {
		m_unk0x370 += p_elapsed;

		if (m_unk0x370 > 250) {
			m_unk0x370 = 0;
		}
	}

	if (m_unk0x374) {
		if (m_unk0x36c == 0) {
			m_unk0x368 += p_elapsed;

			if (m_unk0x368 >= 3000 || m_unk0x370) {
				m_unk0x368 = 3000;
				FUN_00474e70(m_unk0x374);
				m_unk0x37c = TRUE;
				return MenuGameScreen::VTable0x78(p_elapsed);
			}
		}
		else if (m_unk0x36c > 0) {
			m_unk0x36c += p_elapsed;

			if (m_unk0x36c > 20000) {
				FUN_00474f20();
				return MenuGameScreen::VTable0x78(p_elapsed);
			}
		}
	}
	else if (m_unk0x36c) {
		FUN_00474ef0();
	}

	return MenuGameScreen::VTable0x78(p_elapsed);
}

// STUB: LEGORACERS 0x00475010
LegoBool32 CarBuildScreenBase::VTable0x7c(Rect* p_clipRect, Rect* p_sourceRect)
{
	LegoBool32 result = MenuScreen::VTable0x7c(p_clipRect, p_sourceRect);

	if (m_unk0x36c <= 0) {
		return result;
	}

	if (m_unk0x37d) {
		Rect* targetRect = m_unk0x374->GetGlobalRect();
		LegoS32 targetLeft = targetRect->m_left;
		LegoS32 targetTop = targetRect->m_top;
		LegoS32 targetRight = targetRect->m_right;
		LegoS32 targetBottom = targetRect->m_bottom;
		m_unk0x3a4 = VTable0x9c(m_unk0x37e);
		m_unk0x3a0 = VTable0x98(m_unk0x37e);

		if (m_unk0x3a4 == NULL || m_unk0x3a0 == NULL) {
			FUN_00474f20();
			return result;
		}

		VTable0xa0(&m_unk0x390, &m_unk0x394, &m_unk0x398, &m_unk0x39c);

		LegoS32 width;
		LegoS32 height;

		if (!m_unk0x398) {
			LegoS32 fontHeight;
			m_unk0x3a4->MeasureString(m_unk0x3a0, &width, &fontHeight);
			m_unk0x39c = 1;

			m_unk0x398 = static_cast<LegoS32>(
				::sqrt(static_cast<LegoFloat>(fontHeight + 1) * 3.0f * static_cast<LegoFloat>(width))
			);

			LegoS32 maxWidth = p_clipRect->m_right - (fontHeight * 2) - p_clipRect->m_left;
			if (m_unk0x398 > maxWidth) {
				m_unk0x398 = maxWidth;
			}

			LegoS32 minWidth = static_cast<LegoS32>(static_cast<LegoU32>(maxWidth) >> 3);
			if (m_unk0x398 < minWidth) {
				m_unk0x398 = minWidth;
			}

			m_unk0x3a4->FUN_00408d50(m_unk0x3a0, m_unk0x398, m_unk0x39c, 1.0f, 1.0f, &width, &height);

			LegoU32 halfFontHeight = static_cast<LegoU32>(fontHeight) >> 1;
			LegoS32 negativeHalfFontHeight = -static_cast<LegoS32>(halfFontHeight);
			m_unk0x380.m_top = negativeHalfFontHeight;
			m_unk0x380.m_left = negativeHalfFontHeight;
			m_unk0x380.m_right = width + halfFontHeight;
			m_unk0x380.m_bottom = height + halfFontHeight;

			if (width + fontHeight * 2 < p_clipRect->m_right - targetRight) {
				m_unk0x390 = targetRight + fontHeight;
				m_unk0x394 = static_cast<LegoS32>((static_cast<LegoU32>((targetBottom - height) + targetTop)) >> 1);

				if (m_unk0x394 < p_clipRect->m_top + fontHeight) {
					m_unk0x394 = p_clipRect->m_top + fontHeight;
				}
				else if (m_unk0x394 > p_clipRect->m_bottom - height - fontHeight) {
					m_unk0x394 = p_clipRect->m_bottom - height - fontHeight;
				}
			}
			else if (height + fontHeight * 2 < p_clipRect->m_bottom - targetBottom) {
				m_unk0x394 = targetBottom + fontHeight;
				m_unk0x390 = static_cast<LegoS32>((static_cast<LegoU32>((targetRight - width) + targetLeft)) >> 1);

				if (m_unk0x390 < p_clipRect->m_left + fontHeight) {
					m_unk0x390 = p_clipRect->m_left + fontHeight;
				}
				else if (m_unk0x390 > p_clipRect->m_right - width - fontHeight) {
					m_unk0x390 = p_clipRect->m_right - width - fontHeight;
				}
			}
			else if (height + fontHeight * 2 < targetTop - p_clipRect->m_top) {
				m_unk0x394 = targetTop - height - fontHeight;
				m_unk0x390 = static_cast<LegoS32>((static_cast<LegoU32>((targetRight - width) + targetLeft)) >> 1);

				if (m_unk0x390 < p_clipRect->m_left + fontHeight) {
					m_unk0x390 = p_clipRect->m_left + fontHeight;
				}
				else if (m_unk0x390 > p_clipRect->m_right - width - fontHeight) {
					m_unk0x390 = p_clipRect->m_right - width - fontHeight;
				}
			}
			else if (width + fontHeight * 2 < targetLeft - p_clipRect->m_left) {
				m_unk0x390 = targetLeft - width - fontHeight;
				m_unk0x394 = static_cast<LegoS32>((static_cast<LegoU32>((targetBottom - height) + targetTop)) >> 1);

				if (m_unk0x394 < p_clipRect->m_top + fontHeight) {
					m_unk0x394 = p_clipRect->m_top + fontHeight;
				}
				else if (m_unk0x394 > p_clipRect->m_bottom - height - fontHeight) {
					m_unk0x394 = p_clipRect->m_bottom - height - fontHeight;
				}
			}
			else {
				m_unk0x390 = static_cast<LegoS32>(
								 (static_cast<LegoU32>((p_clipRect->m_right - p_clipRect->m_left) - width)) >> 1
							 ) +
							 p_clipRect->m_left;
				m_unk0x394 = static_cast<LegoS32>(
								 (static_cast<LegoU32>((p_clipRect->m_bottom - p_clipRect->m_top) - height)) >> 1
							 ) +
							 p_clipRect->m_top;
			}

			m_unk0x380.m_left += m_unk0x390;
			m_unk0x380.m_right += m_unk0x390;
			m_unk0x380.m_top += m_unk0x394;
			m_unk0x380.m_bottom += m_unk0x394;
		}
		else {
			m_unk0x3a4->FUN_00408d50(m_unk0x3a0, m_unk0x398, m_unk0x39c, 1.0f, 1.0f, &width, &height);
		}

		m_unk0x37d = FALSE;
	}

	ColorRGBA color;
	color.m_red = 0x20;
	color.m_grn = 0x1c;
	color.m_blu = 0xe0;
	color.m_alp = 0xff;

	m_unk0x380.m_top -= 4;
	m_unk0x380.m_left -= 4;
	m_unk0x380.m_right += 4;
	m_unk0x380.m_bottom += 4;
	m_renderer->DrawRectangle(m_unk0x380, 0.0f, color, color, color, color, 0);

	m_unk0x380.m_left += 4;
	m_unk0x380.m_top += 4;
	m_unk0x380.m_right -= 4;
	m_unk0x380.m_bottom -= 4;
	color.m_red = 0;
	color.m_grn = 0;
	color.m_blu = 0x38;
	m_renderer->DrawRectangle(m_unk0x380, 0.0f, color, color, color, color, 0);

	m_unk0x3a4->FUN_00408fe0(
		m_unk0x3a0,
		m_renderer,
		m_unk0x390,
		m_unk0x394,
		m_unk0x398,
		m_unk0x39c,
		1.0f,
		1.0f,
		NULL,
		NULL,
		0
	);
	return result;
}
