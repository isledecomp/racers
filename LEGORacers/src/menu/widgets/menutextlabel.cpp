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
	MenuWidget::VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046f4f0
void MenuTextLabel::Reset()
{
	m_unk0x64.Reset();
	m_unk0x5c = 0;
	m_unk0x60 = NULL;
	m_unk0x58 = 0;
	m_unk0x70 = 0;
	m_unk0x74 = 0;
	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x0046f520
LegoBool32 MenuTextLabel::FUN_0046f520(CreateParams* p_createParams, MenuStyleTable::TextStyle* p_unk0x08)
{
	VTable0x08();

	m_unk0x60 = p_createParams->m_unk0x3c;
	m_unk0x5c = p_createParams->m_unk0x38;
	m_unk0x58 = p_unk0x08;
	LegoS32 unk0x44 = p_createParams->m_unk0x44;
	m_unk0x70 = unk0x44;
	if (unk0x44) {
		m_unk0x74 = TRUE;
	}

	if (FUN_00472a60(p_createParams)) {
		VTable0x44(p_createParams->m_unk0x40, 0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046f580
void MenuTextLabel::VTable0x44(undefined2 p_unk0x04, undefined4 p_unk0x08)
{
	GolString string;

	m_unk0x5c->CopyStringByIndex(&string, p_unk0x04);
	VTable0x40(&string, p_unk0x08);
}

// FUNCTION: LEGORACERS 0x0046f600
void MenuTextLabel::VTable0x40(GolString* p_string, LegoS32 p_unk0x08)
{
	m_unk0x64.CopyFromGolString(p_string);
	m_unk0x64.ToUpperCase();

	if (!m_unk0x34.m_right || !m_unk0x34.m_bottom || p_unk0x08) {
		LegoS32 height;

		m_unk0x64.FirstLine();
		m_unk0x34.m_bottom = m_unk0x34.m_top;
		m_unk0x34.m_right = m_unk0x34.m_left;

		for (LegoS32 i = 0; i < m_unk0x64.CountLines(); i++) {
			m_unk0x60->MeasureString(&m_unk0x64, &p_unk0x08, &height);

			LegoU32 right = m_unk0x34.m_left + p_unk0x08;
			LegoU32 currentRight = m_unk0x34.m_right;
			if (right > currentRight) {
				m_unk0x34.m_right = right;
			}

			m_unk0x34.m_bottom += height;
			m_unk0x64.NextLine();
		}

		m_unk0x64.FirstLine();
	}
}

// FUNCTION: LEGORACERS 0x0046f6b0
void MenuTextLabel::FUN_0046f6b0(LegoS32 p_rightMargin)
{
	LegoS32 right;
	LegoS32 left;

	if (m_parent) {
		right = m_parent->GetRect()->m_right - m_parent->GetRect()->m_left - p_rightMargin;
		left = m_unk0x34.m_left;
	}
	else {
		right = m_unk0x34.m_right;
		left = m_unk0x34.m_left;
	}

	LegoS32 width = m_unk0x34.m_right - left;
	m_unk0x34.m_right = right;
	m_unk0x34.m_left = right - width;
}

// FUNCTION: LEGORACERS 0x0046f6f0
MenuWidget* MenuTextLabel::VTable0x38(Rect* p_rect, Rect* p_arg)
{
	LegoS32 lineCount = m_unk0x64.CountLines();
	LegoFloat lineCountFloat = static_cast<LegoFloat>(lineCount);
	LegoFloat lineHeight = static_cast<LegoFloat>(m_unk0x34.m_bottom - m_unk0x34.m_top) / lineCountFloat;
	LegoS32 xOffset = p_arg->m_left - p_rect->m_left;
	LegoS32 yOffset = p_arg->m_top - p_rect->m_top;
	LegoFloat lineBottom = 0.0f;

	m_unk0x64.FirstLine();
	if (lineCount > 0) {
		LegoS32 lineTop = 0;
		for (; lineCount > 0; lineCount--) {
			Rect source;
			source.m_left = 0;
			source.m_top = lineTop;

			lineBottom += lineHeight;
			lineTop = (LegoS32) lineBottom;
			source.m_bottom = lineTop;
			source.m_right = m_unk0x34.m_right - m_unk0x34.m_left;

			Rect dest;
			MeasureText(m_unk0x60, &m_unk0x64, &source, &dest, 0);
			dest.m_left += xOffset;
			dest.m_top += yOffset;
			dest.m_right += xOffset;
			dest.m_bottom += yOffset;
			DrawString(&dest, p_arg, m_unk0x60, &m_unk0x64, 0, 0);
			m_unk0x64.NextLine();
		}
	}

	return NULL;
}
