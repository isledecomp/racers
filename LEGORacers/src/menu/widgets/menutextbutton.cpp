#include "menu/widgets/menutextbutton.h"

#include "font/golfont.h"
#include "golstringtable.h"
#include "image/golimage.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuTextButton, 0x2f0)
DECOMP_SIZE_ASSERT(MenuTextButton::CreateParams, 0xe0)

// FUNCTION: LEGORACERS 0x00482390
MenuTextButton::MenuTextButton()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00482420
MenuTextButton::~MenuTextButton()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00482490
void MenuTextButton::Reset()
{
	m_styleEntry = NULL;
	m_maxTextWidth = 0;
	::memset(m_stateFonts, 0, sizeof(m_stateFonts) + sizeof(m_stateImages) + sizeof(m_stateColors));
	::memset(m_unk0x2e0, 0, sizeof(m_unk0x2e0));
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x004824d0
LegoBool32 MenuTextButton::CreateImage(CreateParams* p_createParams)
{
	MenuImage::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	::memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));

	LegoU8 flags = createParams.m_flags;
	createParams.m_rect.m_left = 0;
	flags |= 1;
	createParams.m_rect.m_top = 0;
	createParams.m_flags = flags;
	createParams.m_rect.m_right = 0;
	createParams.m_image = m_stateImages[0];
	createParams.m_rect.m_bottom = 0;
	createParams.m_parent = this;
	createParams.m_color = m_stateImageColors[0];

	return m_image.Create(&createParams);
}

// FUNCTION: LEGORACERS 0x00482540
LegoBool32 MenuTextButton::CreateLabel(CreateParams* p_createParams, MenuStyleTable::TextButtonStyle*)
{
	GolString string;
	MenuTextLabel::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	::memcpy(&createParams, p_createParams, sizeof(MenuWidget::CreateParams));

	p_createParams->m_stringTable->CopyStringByIndex(&string, p_createParams->m_stringId);

	Rect source;
	p_createParams->m_stateFonts[0]->MeasureString(&string, &source.m_right, &source.m_bottom);

	if (m_maxTextWidth && source.m_right > m_maxTextWidth) {
		source.m_right = m_maxTextWidth;
	}

	source.m_top = 0;
	source.m_left = 0;
	source.m_bottom = m_image.GetRect()->m_bottom - m_image.GetRect()->m_top;

	MeasureText(m_stateFonts[m_visualStateIndex], &string, &source, &createParams.m_rect, 0);

	LegoS32 right = m_image.GetRect()->m_right;
	createParams.m_rect.m_right += right;
	createParams.m_flags |= 3;
	createParams.m_stringTable = p_createParams->m_stringTable;
	createParams.m_font = m_stateFonts[0];
	createParams.m_stringId = p_createParams->m_stringId;
	createParams.m_color = m_stateImageColors[0];
	createParams.m_rect.m_left += right;
	createParams.m_parent = this;
	m_textStyle.m_centered = 0;

	return m_label.Create(&createParams, &m_textStyle);
}

// FUNCTION: LEGORACERS 0x004826c0
LegoBool32 MenuTextButton::Create(CreateParams* p_createParams, MenuStyleTable::TextButtonStyle* p_styleEntry)
{
	Destroy();

	m_styleEntry = p_styleEntry;
	LegoS32 maxWidth;
	if (p_createParams->m_hasMaxTextWidth) {
		maxWidth = p_createParams->m_maxTextWidth;
	}
	else {
		maxWidth = p_styleEntry->m_maxTextWidth;
	}

	m_maxTextWidth = maxWidth;
	::memcpy(
		m_stateFonts,
		p_createParams->m_stateFonts,
		sizeof(m_stateFonts) + sizeof(m_stateImages) + sizeof(m_stateColors)
	);

	if (MenuIcon::Create(p_createParams, p_styleEntry) && CreateImage(p_createParams) &&
		CreateLabel(p_createParams, p_styleEntry)) {
		SetRect(&p_createParams->m_rect);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00482760
LegoBool32 MenuTextButton::Destroy()
{
	MenuWidget* labelWidget = &m_label;
	labelWidget->Destroy();

	MenuWidget* imageWidget = &m_image;
	imageWidget->Destroy();

	return MenuIcon::Destroy();
}

// FUNCTION: LEGORACERS 0x00482790
void MenuTextButton::SetTextByIndex(undefined4 p_stringId)
{
	m_label.SetStringByIndex(static_cast<undefined2>(p_stringId), TRUE);

	if (m_maxTextWidth && m_label.GetRect()->m_right - m_label.GetRect()->m_left > m_maxTextWidth) {
		Rect rect = *m_label.GetRect();
		rect.m_right = rect.m_left + m_maxTextWidth;
		m_label.SetRect(&rect);
	}

	SetRect(&m_rect);
}

// FUNCTION: LEGORACERS 0x00482810
void MenuTextButton::SetText(GolString* p_string)
{
	m_label.SetString(p_string, TRUE);

	if (m_maxTextWidth && m_label.GetRect()->m_right - m_label.GetRect()->m_left > m_maxTextWidth) {
		Rect rect = *m_label.GetRect();
		rect.m_right = rect.m_left + m_maxTextWidth;
		m_label.SetRect(&rect);
	}

	SetRect(&m_rect);
}

// FUNCTION: LEGORACERS 0x00482890
void MenuTextButton::SetRect(Rect* p_rect)
{
	LegoU8 flags = m_flags;
	Rect rect = *p_rect;

	if (flags & 1) {
		rect.m_right = m_label.GetRect()->m_right + rect.m_left;
		rect.m_bottom = m_stateImages[0]->GetHeight() + rect.m_top;
		MenuIcon::SetRect(&rect);
	}
}

// FUNCTION: LEGORACERS 0x004828f0
void MenuTextButton::SetIconEventHandler(MenuScreenInterface* p_eventHandler)
{
	MenuIcon::SetIconEventHandler(p_eventHandler);
	m_image.SetEventHandler(p_eventHandler);
	m_label.SetEventHandler(p_eventHandler);
}

// FUNCTION: LEGORACERS 0x00482910
MenuWidget* MenuTextButton::DrawSelf(Rect*, Rect*)
{
	m_image.SetImage(m_stateImages[m_visualStateIndex]);
	m_image.SetColor(&m_stateImageColors[m_visualStateIndex]);
	m_label.SetFont(m_stateFonts[m_visualStateIndex]);
	m_label.SetColor(&m_stateColors[m_visualStateIndex]);

	return NULL;
}

// FUNCTION: LEGORACERS 0x00482980
MenuWidget* MenuTextButton::OnKeyUp(InputEventQueue::Event* p_item, undefined4 p_cursorX, undefined4 p_cursorY)
{
	return MenuIcon::OnKeyUp(p_item, p_cursorX, p_cursorY);
}
