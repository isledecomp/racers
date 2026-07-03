#include "menu/widgets/menuclippedimage.h"

#include "image/golimage.h"

DECOMP_SIZE_ASSERT(MenuClippedImage, 0x7c)

// FUNCTION: LEGORACERS 0x0046f200
MenuClippedImage::MenuClippedImage()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046f270
MenuClippedImage::~MenuClippedImage()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046f2c0
void MenuClippedImage::ClipToRect(Rect* p_rect)
{
	if (m_clippedRect.m_top < p_rect->m_top) {
		LegoS32 delta = p_rect->m_top - m_clippedRect.m_top;
		m_sourceRect.m_top = delta;
		m_clippedRect.m_top += delta;
	}

	if (m_clippedRect.m_left < p_rect->m_left) {
		LegoS32 delta = p_rect->m_left - m_clippedRect.m_left;
		m_sourceRect.m_left = delta;
		m_clippedRect.m_left += delta;
	}

	if (m_clippedRect.m_right > p_rect->m_right) {
		LegoS32 delta = m_clippedRect.m_right - p_rect->m_right;
		m_sourceRect.m_right -= delta;
		m_clippedRect.m_right -= delta;
	}

	if (m_clippedRect.m_bottom > p_rect->m_bottom) {
		LegoS32 delta = m_clippedRect.m_bottom - p_rect->m_bottom;
		m_sourceRect.m_bottom -= delta;
		m_clippedRect.m_bottom -= delta;
	}
}

// FUNCTION: LEGORACERS 0x0046f330
MenuWidget* MenuClippedImage::DrawSelf(Rect* p_rect, Rect* p_arg)
{
	LegoS32 imageWidth = m_image->GetWidth();
	LegoS32 imageHeight = m_image->GetHeight();
	LegoS32 top = p_rect->m_top;

	if (top < p_rect->m_bottom) {
		do {
			if (p_rect->m_left < p_rect->m_right) {
				LegoS32 left = p_rect->m_left;
				do {
					m_sourceRect.m_top = 0;
					m_sourceRect.m_left = 0;
					m_sourceRect.m_right = imageWidth;
					m_sourceRect.m_bottom = imageHeight;

					m_clippedRect.m_top = p_arg->m_top + top;
					m_clippedRect.m_left = p_arg->m_left + left;
					m_clippedRect.m_right = p_arg->m_left + left + imageWidth;
					m_clippedRect.m_bottom = p_arg->m_top + top + imageHeight;

					ClipToRect(p_arg);
					DrawImage(&m_clippedRect, &m_sourceRect, m_image);

					left += imageWidth;
				} while (left < p_rect->m_right);
			}

			top += imageHeight;
		} while (top < p_rect->m_bottom);
	}

	return NULL;
}
