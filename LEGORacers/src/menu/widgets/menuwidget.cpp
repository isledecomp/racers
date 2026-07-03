#include "menu/widgets/menuwidget.h"

#include "golfontbase.h"
#include "golstring.h"
#include "image/golimage.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(MenuWidget, 0x58)
DECOMP_SIZE_ASSERT(VisualStateColor, 0x04)
DECOMP_SIZE_ASSERT(MenuWidget::CreateParams, 0x38)

// GLOBAL: LEGORACERS 0x004c7650
Rect g_globalRect;

// FUNCTION: LEGORACERS 0x004729b0
MenuWidget::MenuWidget()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004729f0
MenuWidget::~MenuWidget()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00472a00
void MenuWidget::Reset()
{
	m_golExport = NULL;
	m_animFlags &= 0xfe;
	m_renderer = NULL;
	m_flags = (m_flags & 0xf2) | 2;
	m_focusedChild = 0;
	m_nextSibling = 0;
	m_prevSibling = 0;
	m_lastChild = 0;
	m_firstChild = 0;
	m_parent = 0;
	m_id = 0;
	m_notifyHandler = 0;
	m_scaleY = 1.0;
	m_scaleX = 1.0;
	m_offsetY = 0;
	m_offsetX = 0;
	m_rect.m_left = 0;
	m_rect.m_top = 0;
	m_rect.m_right = 0;
	m_rect.m_bottom = 0;
}

// FUNCTION: LEGORACERS 0x00472a60
LegoBool32 MenuWidget::CreateWidget(CreateParams* p_createParams)
{
	Destroy();

	m_golExport = p_createParams->m_golExport;
	m_renderer = p_createParams->m_renderer;
	m_id = p_createParams->m_id;
	m_notifyHandler = p_createParams->m_eventHandler;
	SetRect(&p_createParams->m_rect);
	SetColor(&p_createParams->m_color);

	if (p_createParams->m_parent && (p_createParams->m_flags & 1)) {
		SetParent(p_createParams->m_parent);
	}

	m_flags |= 0x11;

	if (m_notifyHandler) {
		m_notifyHandler->OnWidgetCreated(this);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00472ad0
LegoBool32 MenuWidget::Destroy()
{
	if (m_flags & 1) {
		RemoveFromParent();
		if (m_notifyHandler) {
			m_notifyHandler->OnWidgetDestroyed(this);
		}

		Reset();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 MenuWidget::OnEvent(undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0044e7f0 FOLDED
MenuWidget* MenuWidget::DrawSelf(Rect*, Rect*)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x00472b00
void MenuWidget::SetParent(MenuWidget* p_param)
{
	if (m_flags & 4) {
		RemoveFromParent();
	}

	m_flags |= 4;
	m_parent = p_param;

	if (m_parent == NULL) {
		return;
	}

	if (m_parent->m_lastChild == NULL) {
		m_parent->m_firstChild = this;
		m_parent->m_lastChild = this;
		return;
	}

	m_prevSibling = m_parent->m_lastChild;
	m_prevSibling->m_nextSibling = this;
	m_parent->m_lastChild = this;
}

// FUNCTION: LEGORACERS 0x00472b50
void MenuWidget::RemoveFromParent()
{
	if (!(m_flags & 4)) {
		return;
	}

	if (m_prevSibling) {
		m_prevSibling->m_nextSibling = m_nextSibling;
	}
	else if (m_parent) {
		m_parent->m_firstChild = m_nextSibling;
	}

	if (m_nextSibling) {
		m_nextSibling->m_prevSibling = m_prevSibling;
		m_nextSibling = 0;
		m_prevSibling = 0;
		m_parent = 0;
		m_flags &= 0xfb;
		return;
	}

	if (m_parent) {
		m_parent->m_lastChild = m_prevSibling;
	}

	m_nextSibling = 0;
	m_prevSibling = 0;
	m_parent = 0;
	m_flags &= 0xfb;
}

// FUNCTION: LEGORACERS 0x00472bc0
void MenuWidget::SetFocus()
{
	MenuWidget* node = this;

	if (node->FindRoot()->m_focusedChild) {
		node->FindFocusedLeaf()->ClearFocus();
	}

	node->m_flags |= 8;

	if (node->m_notifyHandler) {
		node->m_notifyHandler->OnWidgetFocused(node);
	}

	while (node) {
		if (node->m_parent) {
			node->m_parent->m_focusedChild = node;
		}

		node = node->m_parent;
	}
}

// FUNCTION: LEGORACERS 0x00472c10
void MenuWidget::ClearFocus()
{
	MenuWidget* node = this;
	LegoU8 flags = node->m_flags;

	if (flags & 8) {
		node->m_flags = flags & 0xf7;

		if (node->m_notifyHandler) {
			node->m_notifyHandler->OnWidgetUnfocused(node);
		}

		while (node) {
			node->m_focusedChild = NULL;
			node = node->m_parent;
		}
	}
}

// FUNCTION: LEGORACERS 0x00472c40
undefined4 MenuWidget::HitTest(LegoS32 p_x, LegoS32 p_y)
{
	return p_x >= 0 && p_x <= (m_rect.m_right - m_rect.m_left) && p_y >= 0 && p_y <= (m_rect.m_bottom - m_rect.m_top);
}

// STUB: LEGORACERS 0x00472c80
void MenuWidget::CenterRectIn(const Rect* p_source, Rect* p_dest) const
{
	const Rect* source = p_source;
	LegoU32 sourceTop = source->m_top;
	LegoU32 sourceHeight = source->m_bottom;
	LegoS32 sourceLeft = source->m_left;
	LegoU32 sourceWidth = source->m_right;
	sourceHeight -= sourceTop;
	sourceWidth -= sourceLeft;

	Rect* dest = p_dest;
	LegoU32 destWidth = dest->m_right;
	LegoS32 destLeft = dest->m_left;
	destWidth -= destLeft;

	LegoU32 destHeight = dest->m_bottom;
	destHeight -= dest->m_top;

	if (sourceWidth > destWidth) {
		LegoU32 inset = (sourceWidth - destWidth) >> 1;
		dest->m_left = sourceLeft + inset;
		dest->m_right = source->m_right - inset;
	}
	else {
		dest->m_left = sourceLeft;
		dest->m_right = source->m_right;
	}

	if (sourceHeight > destHeight) {
		LegoU32 inset = (sourceHeight - destHeight) >> 1;
		dest->m_top = source->m_top + inset;
		dest->m_bottom = source->m_bottom - inset;
	}
	else {
		dest->m_top = source->m_top;
		dest->m_bottom = source->m_bottom;
	}
}

// FUNCTION: LEGORACERS 0x00472d00
void MenuWidget::MeasureText(
	GolFontBase* p_font,
	GolString* p_string,
	Rect* p_source,
	Rect* p_dest,
	LegoS32 p_wrapWidth
)
{
	LegoS32 width;
	LegoS32 height;

	if (p_wrapWidth) {
		p_font->MeasureString(p_string, p_wrapWidth, 0, m_scaleX, m_scaleY, &width, &height);
	}
	else {
		p_font->MeasureString(p_string, &width, &height);
	}

	p_dest->m_left = 0;
	p_dest->m_top = 0;
	p_dest->m_right = width;
	p_dest->m_bottom = height;
	CenterRectIn(p_source, p_dest);
}

// FUNCTION: LEGORACERS 0x00472d70
void MenuWidget::DrawImage(Rect* p_destRect, Rect* p_sourceRect, GolImage* p_image)
{
	p_image->m_tintColor.m_u32 = m_colorPacked;
	m_renderer->DrawImageClipped(p_image, 0, p_destRect, p_sourceRect, NULL);
}

// FUNCTION: LEGORACERS 0x00472da0
void MenuWidget::DrawString(
	Rect* p_source,
	Rect* p_dest,
	GolFontBase* p_font,
	GolString* p_string,
	LegoS32 p_wrapWidth,
	LegoS32 p_centered
)
{
	LegoU32 color = m_colorPacked;
	p_font->SetColor(color);

	if (p_wrapWidth) {
		p_font->DrawString(
			p_string,
			m_renderer,
			p_source->m_left,
			p_source->m_top,
			p_wrapWidth,
			0,
			m_scaleX,
			m_scaleY,
			p_dest,
			&m_color,
			p_centered
		);
	}
	else {
		LegoS32 y = p_source->m_top;
		LegoS32 x = p_source->m_left;
		m_renderer->DrawStringFitted(
			p_string,
			p_font,
			x,
			y,
			static_cast<LegoFloat>(p_source->m_right - x),
			static_cast<LegoFloat>(p_source->m_bottom - y),
			p_dest,
			0
		);
	}
}

// FUNCTION: LEGORACERS 0x00472e40
MenuWidget* MenuWidget::FindRoot()
{
	MenuWidget* result = this;

	while (result->m_parent) {
		result = result->m_parent;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00472e60
MenuWidget* MenuWidget::FindFocusedLeaf()
{
	MenuWidget* result = FindRoot();
	MenuWidget* child = result->m_focusedChild;

	if (!child) {
		return (result->m_flags & 0x08) ? result : NULL;
	}

	do {
		result = child;
		child = result->m_focusedChild;
	} while (child);

	return result;
}

// FUNCTION: LEGORACERS 0x00472e90
Rect* MenuWidget::GetGlobalRect()
{
	MenuWidget* node = this;

	g_globalRect.m_top = 0;
	g_globalRect.m_left = 0;

	while (node) {
		g_globalRect.m_left += node->m_rect.m_left;
		g_globalRect.m_top += node->m_rect.m_top;
		node = node->m_parent;
	}

	g_globalRect.m_right = (m_rect.m_right - m_rect.m_left) + g_globalRect.m_left;
	g_globalRect.m_bottom = (m_rect.m_bottom - m_rect.m_top) + g_globalRect.m_top;

	return &g_globalRect;
}

// FUNCTION: LEGORACERS 0x00472ef0
MenuWidget* MenuWidget::GetChildByIndex(LegoS32 p_index)
{
	MenuWidget* child = m_firstChild;

	while (p_index-- && child) {
		child = child->m_nextSibling;
	}

	return child;
}

// FUNCTION: LEGORACERS 0x00472f10
MenuWidget* MenuWidget::FindChildById(undefined2 p_id)
{
	MenuWidget* child = m_firstChild;

	if (m_id == p_id) {
		return this;
	}

	while (child) {
		MenuWidget* result = child->FindChildById(p_id);
		if (result) {
			return result;
		}

		child = child->m_nextSibling;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00472f40
void MenuWidget::SetRect(Rect* p_rect)
{
	if (m_notifyHandler) {
		if ((((m_rect.m_right - p_rect->m_right) - m_rect.m_left) + p_rect->m_left != 0) ||
			(((m_rect.m_bottom - m_rect.m_top) - p_rect->m_bottom) + p_rect->m_top != 0)) {
			m_notifyHandler->OnWidgetResized(this);
		}

		if ((m_rect.m_left - p_rect->m_left) || (m_rect.m_top - p_rect->m_top)) {
			m_notifyHandler->OnWidgetMoved(this);
		}
	}

	m_rect = *p_rect;
	return;
}

// FUNCTION: LEGORACERS 0x00472fc0
void MenuWidget::SetColor(VisualStateColor* p_param)
{
	m_color = p_param->m_color;
}

// FUNCTION: LEGORACERS 0x00472fd0
void MenuWidget::ComputeScale(Rect* p_sourceRect, Rect* p_destRect)
{
	if (p_destRect->m_left >= p_destRect->m_right) {
		m_scaleX = 0.0f;
	}
	else {
		LegoFloat sourceWidth = static_cast<LegoFloat>(p_sourceRect->m_right - p_sourceRect->m_left);
		LegoFloat destWidth = static_cast<LegoFloat>(p_destRect->m_right - p_destRect->m_left);
		m_scaleX = sourceWidth / destWidth;
	}

	if (p_destRect->m_top >= p_destRect->m_bottom) {
		m_scaleY = 0.0f;
	}
	else {
		LegoFloat sourceHeight = static_cast<LegoFloat>(p_sourceRect->m_bottom - p_sourceRect->m_top);
		LegoFloat destHeight = static_cast<LegoFloat>(p_destRect->m_bottom - p_destRect->m_top);
		m_scaleY = sourceHeight / destHeight;
	}
}

// FUNCTION: LEGORACERS 0x00473050
void MenuWidget::ScaleRect(Rect* p_sourceRect, Rect* p_destRect)
{
	p_destRect->m_top = static_cast<LegoS32>(p_sourceRect->m_top * m_scaleY);
	p_destRect->m_left = static_cast<LegoS32>(p_sourceRect->m_left * m_scaleX);
	p_destRect->m_right = static_cast<LegoS32>(p_sourceRect->m_right * m_scaleX);
	p_destRect->m_bottom = static_cast<LegoS32>(p_sourceRect->m_bottom * m_scaleY);
}

// FUNCTION: LEGORACERS 0x004730a0
LegoBool32 MenuWidget::ClipRect(Rect* p_rect, Rect* p_arg)
{
	if (p_rect->m_left >= m_rect.m_right) {
		return FALSE;
	}

	if (p_rect->m_right <= m_rect.m_left) {
		return FALSE;
	}

	if (p_rect->m_top >= m_rect.m_bottom) {
		return FALSE;
	}

	if (p_rect->m_bottom <= m_rect.m_top) {
		return FALSE;
	}

	if (p_rect->m_left < m_rect.m_left) {
		p_arg->m_left += m_rect.m_left - p_rect->m_left;
		p_rect->m_left = m_rect.m_left;
	}

	if (p_rect->m_top < m_rect.m_top) {
		p_arg->m_top += m_rect.m_top - p_rect->m_top;
		p_rect->m_top = m_rect.m_top;
	}

	if (p_rect->m_right > m_rect.m_right) {
		p_arg->m_right += m_rect.m_right - p_rect->m_right;
		p_rect->m_right = m_rect.m_right;
	}

	if (p_rect->m_bottom > m_rect.m_bottom) {
		p_arg->m_bottom += m_rect.m_bottom - p_rect->m_bottom;
		p_rect->m_bottom = m_rect.m_bottom;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00473160
Rect* MenuWidget::TranslateRectByOffset(Rect* p_rect)
{
	LegoS32 top = m_offsetY - m_rect.m_top + p_rect->m_top;
	LegoS32 left = m_offsetX - m_rect.m_left + p_rect->m_left;
	LegoS32 right = p_rect->m_right - p_rect->m_left + left;
	LegoS32 bottom = p_rect->m_bottom - p_rect->m_top + top;

	p_rect->m_left = left;
	p_rect->m_top = top;
	p_rect->m_right = right;
	p_rect->m_bottom = bottom;

	return p_rect;
}

// FUNCTION: LEGORACERS 0x004731b0
void MenuWidget::ScreenToLocal(undefined4& p_x, undefined4& p_y)
{
	p_x -= m_rect.m_left;
	p_y -= m_rect.m_top;
}

// FUNCTION: LEGORACERS 0x004731d0
LegoBool32 MenuWidget::BroadcastEvent(undefined4 p_elapsedMs)
{
	MenuWidget* child = m_firstChild;

	if (OnEvent(p_elapsedMs)) {
		return TRUE;
	}

	while (child) {
		if (child->BroadcastEvent(p_elapsedMs)) {
			return TRUE;
		}

		child = child->m_nextSibling;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00473210
undefined4 MenuWidget::Draw(Rect* p_rect, Rect* p_arg)
{
	Rect rect = *p_rect;
	MenuWidget* child = m_firstChild;
	Rect arg = *p_arg;

	if (ClipRect(&rect, &arg)) {
		TranslateRectByOffset(&rect);

		undefined flags = m_flags;
		if ((flags & 2) && (!(flags & 0x10) || !DrawSelf(&rect, &arg))) {
			for (; child; child = child->m_nextSibling) {
				if (child->Draw(&rect, &arg)) {
					break;
				}
			}
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x004732d0
LegoBool32 MenuWidget::DispatchCursorEvent(MenuInputDispatcher::Cursor* p_cursor, undefined4 p_x, undefined4 p_y)
{
	MenuWidget* child = m_firstChild;
	undefined4 x = p_x;
	undefined4 y = p_y;

	ScreenToLocal(x, y);

	if ((m_flags & 2) && HitTest(x, y)) {
		while (child) {
			if (child->DispatchCursorEvent(p_cursor, x, y)) {
				return TRUE;
			}

			child = child->m_nextSibling;
		}

		if (OnCursorEvent(p_cursor, x, y)) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00473370
LegoBool32 MenuWidget::DispatchKeyDown(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	MenuWidget* child = m_firstChild;
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	while (child) {
		if (child->DispatchKeyDown(p_param1, x, y)) {
			return TRUE;
		}

		child = child->m_nextSibling;
	}

	return MenuEventResult(OnKeyDown(p_param1, x, y));
}

// FUNCTION: LEGORACERS 0x00473400
LegoBool32 MenuWidget::DispatchKeyUp(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	MenuWidget* child = m_firstChild;
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	ScreenToLocal(x, y);

	while (child) {
		if (child->DispatchKeyUp(p_param1, x, y)) {
			return TRUE;
		}

		child = child->m_nextSibling;
	}

	return MenuEventResult(OnKeyUp(p_param1, x, y));
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
MenuWidget* MenuWidget::OnCursorEvent(void*, undefined4, undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
MenuWidget* MenuWidget::OnKeyDown(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
MenuWidget* MenuWidget::OnKeyUp(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x00473a20 FOLDED
LegoBool32 MenuWidget::PointInRect(Rect* p_rect, LegoS32 p_x, LegoS32 p_y)
{
	return p_x >= p_rect->m_left && p_x <= p_rect->m_right && p_y >= p_rect->m_top && p_y <= p_rect->m_bottom;
}
