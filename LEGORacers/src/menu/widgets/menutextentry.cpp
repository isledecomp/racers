#include "menu/widgets/menutextentry.h"

#include "golfontbase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuTextEntry, 0x330)

// FUNCTION: LEGORACERS 0x00471850
MenuTextEntry::MenuTextEntry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004718d0
MenuTextEntry::~MenuTextEntry()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00471930
void MenuTextEntry::Create(CreateParams*)
{
	GolString localStr;
	undefined2 buf[2];
	LegoU32 maxWidth = 0;

	buf[0] = *m_charset.FromCursor(0);
	buf[1] = 0;
	localStr.CopyFromBufSelection(buf, 2);
	localStr.ResetCursors();

	for (LegoS32 i = 0; i < m_charset.SelectionLength(); i++) {
		LegoS32 width;
		LegoS32 height;
		buf[0] = *m_charset.FromCursor(i);
		m_font->MeasureString(&localStr, &width, &height);
		if (width > maxWidth) {
			maxWidth = width;
		}
	}

	m_caret.SetWidth(maxWidth);
	m_caret.SetHeight(4);
}

// FUNCTION: LEGORACERS 0x00471a30
void MenuTextEntry::UpdateCaret()
{
	if (m_inputMode == 4) {
		m_text.SetCursorEnd(m_text.SelectionLength() - 1);
	}

	LegoS32 width;
	LegoS32 height;
	m_font->MeasureString(&m_text, &width, &height);

	m_text.FirstLine();
	m_caret.SetPosition(m_rect.m_left + width, m_rect.m_bottom - 6);
}

// FUNCTION: LEGORACERS 0x00471aa0
LegoBool32 MenuTextEntry::CreateColorBox(CreateParams* p_createParams)
{
	MenuColorBox::CreateParams createParams;
	memset(&createParams, 0, sizeof(createParams));
	memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));

	createParams.m_parent = MenuWidget::m_parent;
	createParams.m_id = 0x400;
	createParams.m_blinkEnabled = 1;
	createParams.m_flags |= 1;
	createParams.m_onDurationMs = 1000;
	createParams.m_offDurationMs = 1000;
	createParams.m_color.m_packed = -1;

	return m_caret.Create(&createParams);
}

// FUNCTION: LEGORACERS 0x00471b20
LegoBool32 MenuTextEntry::CreateField(CreateParams* p_createParams, const MenuIcon::CreateState* p_createState)
{
	Destroy();

	if (MenuTextField::CreateField(p_createParams, p_createState)) {
		if (CreateColorBox(p_createParams)) {
			Create(p_createParams);
		}
		else {
			Destroy();
		}
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00471b70
MenuWidget* MenuTextEntry::DrawSelf(Rect* p_param1, Rect* p_param2)
{
	MenuWidget* result = MenuTextField::DrawSelf(p_param1, p_param2);
	UpdateCaret();

	if (m_stateFlags & 2) {
		if (m_caret.GetParent() != MenuWidget::m_parent) {
			m_caret.SetParent(MenuWidget::m_parent);
		}

		if (m_length == m_maxLength) {
			m_caret.ClearFlags(2);
		}
		else {
			m_caret.SetFlags(2);
		}
	}
	else {
		m_caret.RemoveFromParent();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00471c00
MenuWidget* MenuTextEntry::OnKeyDown(InputEventQueue::Event* p_param1, undefined4 p_param2, undefined4 p_param3)
{
	MenuWidget* result = MenuTextField::OnKeyDown(p_param1, p_param2, p_param3);
	UpdateCaret();

	return result;
}
