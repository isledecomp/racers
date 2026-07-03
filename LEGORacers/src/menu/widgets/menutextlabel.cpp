#include "menu/widgets/menutextlabel.h"

#include "font/golfont.h"
#include "golstringtable.h"

DECOMP_SIZE_ASSERT(MenuTextLabel, 0x78)
DECOMP_SIZE_ASSERT(MenuTextLabel::CreateParams, 0x48)

// FUNCTION: LEGORACERS 0x0046f410
MenuTextLabel::MenuTextLabel()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046f490
MenuTextLabel::~MenuTextLabel()
{
	MenuWidget::Destroy();
}

// FUNCTION: LEGORACERS 0x0046f4f0
void MenuTextLabel::Reset()
{
	m_string.Reset();
	m_stringTable = 0;
	m_font = NULL;
	m_style = 0;
	m_wrapWidth = 0;
	m_wrapped = 0;
	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x0046f520
LegoBool32 MenuTextLabel::Create(CreateParams* p_createParams, MenuStyleTable::TextStyle* p_style)
{
	Destroy();

	m_font = p_createParams->m_font;
	m_stringTable = p_createParams->m_stringTable;
	m_style = p_style;
	LegoS32 wrapWidth = p_createParams->m_wrapWidth;
	m_wrapWidth = wrapWidth;
	if (wrapWidth) {
		m_wrapped = TRUE;
	}

	if (CreateWidget(p_createParams)) {
		SetStringByIndex(p_createParams->m_stringId, 0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046f580
void MenuTextLabel::SetStringByIndex(undefined2 p_stringId, undefined4 p_remeasure)
{
	GolString string;

	m_stringTable->CopyStringByIndex(&string, p_stringId);
	SetString(&string, p_remeasure);
}

// FUNCTION: LEGORACERS 0x0046f600
void MenuTextLabel::SetString(GolString* p_string, LegoS32 p_remeasure)
{
	m_string.CopyFromGolString(p_string);
	m_string.ToUpperCase();

	if (!m_rect.m_right || !m_rect.m_bottom || p_remeasure) {
		LegoS32 height;

		m_string.FirstLine();
		m_rect.m_bottom = m_rect.m_top;
		m_rect.m_right = m_rect.m_left;

		for (LegoS32 i = 0; i < m_string.CountLines(); i++) {
			m_font->MeasureString(&m_string, &p_remeasure, &height);

			LegoU32 right = m_rect.m_left + p_remeasure;
			LegoU32 currentRight = m_rect.m_right;
			if (right > currentRight) {
				m_rect.m_right = right;
			}

			m_rect.m_bottom += height;
			m_string.NextLine();
		}

		m_string.FirstLine();
	}
}

// FUNCTION: LEGORACERS 0x0046f6b0
void MenuTextLabel::WrapText(LegoS32 p_rightMargin)
{
	LegoS32 right;
	LegoS32 left;

	if (m_parent) {
		right = m_parent->GetRect()->m_right - m_parent->GetRect()->m_left - p_rightMargin;
		left = m_rect.m_left;
	}
	else {
		right = m_rect.m_right;
		left = m_rect.m_left;
	}

	LegoS32 width = m_rect.m_right - left;
	m_rect.m_right = right;
	m_rect.m_left = right - width;
}

// STUB: LEGORACERS 0x0046f6f0
MenuWidget* MenuTextLabel::DrawSelf(Rect* p_rect, Rect* p_arg)
{
	LegoS32 lineCount = m_string.CountLines();
	LegoFloat lineCountFloat = static_cast<LegoFloat>(lineCount);
	LegoFloat lineHeight = static_cast<LegoFloat>(m_rect.m_bottom - m_rect.m_top) / lineCountFloat;
	LegoS32 xOffset = p_arg->m_left - p_rect->m_left;
	LegoS32 yOffset = p_arg->m_top - p_rect->m_top;
	LegoFloat lineBottom = 0.0f;

	m_string.FirstLine();
	if (lineCount > 0) {
		LegoS32 lineTop = 0;
		for (; lineCount > 0; lineCount--) {
			Rect source;
			source.m_left = 0;
			source.m_top = lineTop;

			lineBottom += lineHeight;
			lineTop = (LegoS32) lineBottom;
			source.m_bottom = lineTop;
			source.m_right = m_rect.m_right - m_rect.m_left;

			Rect dest;
			MeasureText(m_font, &m_string, &source, &dest, 0);
			dest.m_left += xOffset;
			dest.m_top += yOffset;
			dest.m_right += xOffset;
			dest.m_bottom += yOffset;
			DrawString(&dest, p_arg, m_font, &m_string, 0, 0);
			m_string.NextLine();
		}
	}

	return NULL;
}
