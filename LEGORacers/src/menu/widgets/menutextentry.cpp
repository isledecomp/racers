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
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00471930
void MenuTextEntry::FUN_00471930(CreateParams*)
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

	m_unk0x23c.FUN_00468000(maxWidth);
	m_unk0x23c.FUN_00468040(4);
}

// FUNCTION: LEGORACERS 0x00471a30
void MenuTextEntry::FUN_00471a30()
{
	if (m_unk0x1f8 == 4) {
		m_text.SetCursorEnd(m_text.SelectionLength() - 1);
	}

	LegoS32 width;
	LegoS32 height;
	m_font->MeasureString(&m_text, &width, &height);

	m_text.FirstLine();
	m_unk0x23c.FUN_00467fc0(m_unk0x34.m_left + width, m_unk0x34.m_bottom - 6);
}

// FUNCTION: LEGORACERS 0x00471aa0
LegoBool32 MenuTextEntry::FUN_00471aa0(CreateParams* p_createParams)
{
	MenuColorBox::CreateParams createParams;
	memset(&createParams, 0, sizeof(createParams));
	memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));

	createParams.m_parent = MenuWidget::m_parent;
	createParams.m_unk0x20 = 0x400;
	createParams.m_unk0x38 = 1;
	createParams.m_flags |= 1;
	createParams.m_unk0x3c = 1000;
	createParams.m_unk0x40 = 1000;
	createParams.m_unk0x22.m_unk0x00 = -1;

	return m_unk0x23c.FUN_00467f70(&createParams);
}

// FUNCTION: LEGORACERS 0x00471b20
LegoBool32 MenuTextEntry::VTable0x70(CreateParams* p_createParams, const MenuIcon::CreateState* p_createState)
{
	VTable0x08();

	if (MenuTextField::VTable0x70(p_createParams, p_createState)) {
		if (FUN_00471aa0(p_createParams)) {
			FUN_00471930(p_createParams);
		}
		else {
			VTable0x08();
		}
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00471b70
MenuWidget* MenuTextEntry::VTable0x38(Rect* p_param1, Rect* p_param2)
{
	MenuWidget* result = MenuTextField::VTable0x38(p_param1, p_param2);
	FUN_00471a30();

	if (m_stateFlags & 2) {
		if (m_unk0x23c.GetParent() != MenuWidget::m_parent) {
			m_unk0x23c.SetParent(MenuWidget::m_parent);
		}

		if (m_length == m_maxLength) {
			m_unk0x23c.ClearFlags(2);
		}
		else {
			m_unk0x23c.SetFlags(2);
		}
	}
	else {
		m_unk0x23c.RemoveFromParent();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00471c00
MenuWidget* MenuTextEntry::VTable0x30(InputEventQueue::Event* p_param1, undefined4 p_param2, undefined4 p_param3)
{
	MenuWidget* result = MenuTextField::VTable0x30(p_param1, p_param2, p_param3);
	FUN_00471a30();

	return result;
}
