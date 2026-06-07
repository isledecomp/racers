#include "menu/widgets/obscurevantage0x58.h"

#include "font/golfontbase0x40.h"
#include "golstring.h"
#include "image/utopianpan0xa4.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(ObscureVantage0x58, 0x58)
DECOMP_SIZE_ASSERT(VisualState0x4, 0x04)
DECOMP_SIZE_ASSERT(ObscureVantage0x58::CreateParams0x38, 0x38)

// GLOBAL: LEGORACERS 0x004c7650
Rect g_unk0x4c7650;

// FUNCTION: LEGORACERS 0x004729b0
ObscureVantage0x58::ObscureVantage0x58()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004729f0
ObscureVantage0x58::~ObscureVantage0x58()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00472a00
void ObscureVantage0x58::Reset()
{
	m_unk0x54 &= 0xfe;
	m_flags = (m_flags & 0xf2) | 2;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0x18 = 0;
	m_nextSibling = 0;
	m_prevSibling = 0;
	m_lastChild = 0;
	m_firstChild = 0;
	m_parent = 0;
	m_unk0x30 = 0;
	m_unk0x28 = 0;
	m_unk0x48 = 1.0;
	m_unk0x44 = 1.0;
	m_unk0x50 = 0;
	m_unk0x4c = 0;
	m_unk0x34.m_left = 0;
	m_unk0x34.m_top = 0;
	m_unk0x34.m_right = 0;
	m_unk0x34.m_bottom = 0;
}

// FUNCTION: LEGORACERS 0x00472a60
LegoBool32 ObscureVantage0x58::FUN_00472a60(CreateParams0x38* p_createParams)
{
	VTable0x08();

	m_golExport = p_createParams->m_golExport;
	m_renderer = p_createParams->m_renderer;
	m_unk0x30 = p_createParams->m_unk0x20;
	m_unk0x28 = p_createParams->m_eventHandler;
	VTable0x10(&p_createParams->m_rect);
	VTable0x14(&p_createParams->m_unk0x22);

	if (p_createParams->m_parent && (p_createParams->m_flags & 1)) {
		SetParent(p_createParams->m_parent);
	}

	m_flags |= 0x11;

	if (m_unk0x28) {
		m_unk0x28->VTable0x00(this);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00472ad0
LegoBool32 ObscureVantage0x58::VTable0x08()
{
	if (m_flags & 1) {
		RemoveFromParent();
		if (m_unk0x28) {
			m_unk0x28->VTable0x04(this);
		}

		Reset();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 ObscureVantage0x58::VTable0x3c(undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x0044e7f0 FOLDED
ObscureVantage0x58* ObscureVantage0x58::VTable0x38(Rect*, Rect*)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x00472b00
void ObscureVantage0x58::SetParent(ObscureVantage0x58* p_param)
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
void ObscureVantage0x58::RemoveFromParent()
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
void ObscureVantage0x58::FUN_00472bc0()
{
	ObscureVantage0x58* node = this;

	if (node->FindRoot()->m_unk0x18) {
		node->FUN_00472e60()->FUN_00472c10();
	}

	node->m_flags |= 8;

	if (node->m_unk0x28) {
		node->m_unk0x28->VTable0x20(node);
	}

	while (node) {
		if (node->m_parent) {
			node->m_parent->m_unk0x18 = node;
		}

		node = node->m_parent;
	}
}

// FUNCTION: LEGORACERS 0x00472c10
void ObscureVantage0x58::FUN_00472c10()
{
	ObscureVantage0x58* node = this;
	LegoU8 flags = node->m_flags;

	if (flags & 8) {
		node->m_flags = flags & 0xf7;

		if (node->m_unk0x28) {
			node->m_unk0x28->VTable0x24(node);
		}

		while (node) {
			node->m_unk0x18 = NULL;
			node = node->m_parent;
		}
	}
}

// FUNCTION: LEGORACERS 0x00472c40
undefined4 ObscureVantage0x58::FUN_00472c40(LegoS32 p_x, LegoS32 p_y)
{
	return p_x >= 0 && p_x <= (m_unk0x34.m_right - m_unk0x34.m_left) && p_y >= 0 &&
		   p_y <= (m_unk0x34.m_bottom - m_unk0x34.m_top);
}

// FUNCTION: LEGORACERS 0x00472c80
Rect* ObscureVantage0x58::FUN_00472c80(Rect* p_source, Rect* p_dest)
{
	LegoS32 sourceLeft = p_source->m_left;
	LegoU32 sourceHeight = p_source->m_bottom - p_source->m_top;
	LegoU32 sourceWidth = p_source->m_right - p_source->m_left;
	LegoU32 destWidth = p_dest->m_right - p_dest->m_left;
	LegoU32 destHeight = p_dest->m_bottom - p_dest->m_top;

	if (sourceWidth <= destWidth) {
		p_dest->m_left = sourceLeft;
		p_dest->m_right = p_source->m_right;
	}
	else {
		LegoU32 inset = (sourceWidth - destWidth) >> 1;
		p_dest->m_left = sourceLeft + inset;
		p_dest->m_right = p_source->m_right - inset;
	}

	if (sourceHeight <= destHeight) {
		p_dest->m_top = p_source->m_top;
		p_dest->m_bottom = p_source->m_bottom;
	}
	else {
		LegoU32 inset = (sourceHeight - destHeight) >> 1;
		p_dest->m_top = p_source->m_top + inset;
		p_dest->m_bottom = p_source->m_bottom - inset;
	}

	return p_dest;
}

// FUNCTION: LEGORACERS 0x00472d00
Rect* ObscureVantage0x58::FUN_00472d00(
	GolFontBase0x40* p_font,
	GolString* p_string,
	Rect* p_source,
	Rect* p_dest,
	LegoS32 p_wrapWidth
)
{
	LegoS32 width;
	LegoS32 height;

	if (p_wrapWidth) {
		p_font->FUN_00408d50(p_string, p_wrapWidth, 0, m_unk0x44, m_unk0x48, &width, &height);
	}
	else {
		p_font->FUN_00408be0(p_string, &width, &height);
	}

	p_dest->m_left = 0;
	p_dest->m_top = 0;
	p_dest->m_right = width;
	p_dest->m_bottom = height;
	return FUN_00472c80(p_source, p_dest);
}

// FUNCTION: LEGORACERS 0x00472d70
void ObscureVantage0x58::FUN_00472d70(Rect* p_destRect, Rect* p_sourceRect, UtopianPan0xa4* p_image)
{
	p_image->m_unk0x4a.m_u32 = m_colorPacked;
	m_renderer->VTable0x7c(p_image, 0, p_destRect, p_sourceRect, NULL);
}

// FUNCTION: LEGORACERS 0x00472da0
undefined2 ObscureVantage0x58::FUN_00472da0(
	Rect* p_source,
	Rect* p_dest,
	GolFontBase0x40* p_font,
	GolString* p_string,
	LegoS32 p_wrapWidth,
	LegoS32 p_unk0x18
)
{
	LegoU32 color = m_colorPacked;
	p_font->SetColor(color);

	if (p_wrapWidth) {
		return p_font->FUN_00408fe0(
			p_string,
			m_renderer,
			p_source->m_left,
			p_source->m_top,
			p_wrapWidth,
			0,
			m_unk0x44,
			m_unk0x48,
			p_dest,
			&m_color,
			p_unk0x18
		);
	}

	LegoS32 y = p_source->m_top;
	LegoS32 x = p_source->m_left;
	return m_renderer->VTable0x6c(
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

// FUNCTION: LEGORACERS 0x00472e40
ObscureVantage0x58* ObscureVantage0x58::FindRoot()
{
	ObscureVantage0x58* result = this;

	while (result->m_parent) {
		result = result->m_parent;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00472e60
ObscureVantage0x58* ObscureVantage0x58::FUN_00472e60()
{
	ObscureVantage0x58* result = FindRoot();
	ObscureVantage0x58* child = result->m_unk0x18;

	if (!child) {
		return (result->m_flags & 0x08) ? result : NULL;
	}

	do {
		result = child;
		child = result->m_unk0x18;
	} while (child);

	return result;
}

// FUNCTION: LEGORACERS 0x00472e90
Rect* ObscureVantage0x58::GetGlobalRect()
{
	ObscureVantage0x58* node = this;

	g_unk0x4c7650.m_top = 0;
	g_unk0x4c7650.m_left = 0;

	while (node) {
		g_unk0x4c7650.m_left += node->m_unk0x34.m_left;
		g_unk0x4c7650.m_top += node->m_unk0x34.m_top;
		node = node->m_parent;
	}

	g_unk0x4c7650.m_right = (m_unk0x34.m_right - m_unk0x34.m_left) + g_unk0x4c7650.m_left;
	g_unk0x4c7650.m_bottom = (m_unk0x34.m_bottom - m_unk0x34.m_top) + g_unk0x4c7650.m_top;

	return &g_unk0x4c7650;
}

// FUNCTION: LEGORACERS 0x00472ef0
ObscureVantage0x58* ObscureVantage0x58::FUN_00472ef0(LegoS32 p_unk0x04)
{
	ObscureVantage0x58* child = m_firstChild;

	while (p_unk0x04-- && child) {
		child = child->m_nextSibling;
	}

	return child;
}

// FUNCTION: LEGORACERS 0x00472f10
ObscureVantage0x58* ObscureVantage0x58::FUN_00472f10(undefined2 p_unk0x04)
{
	ObscureVantage0x58* child = m_firstChild;

	if (m_unk0x30 == p_unk0x04) {
		return this;
	}

	while (child) {
		ObscureVantage0x58* result = child->FUN_00472f10(p_unk0x04);
		if (result) {
			return result;
		}

		child = child->m_nextSibling;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00472f40
void ObscureVantage0x58::VTable0x10(Rect* p_rect)
{
	if (m_unk0x28) {
		if ((((m_unk0x34.m_right - p_rect->m_right) - m_unk0x34.m_left) + p_rect->m_left != 0) ||
			(((m_unk0x34.m_bottom - m_unk0x34.m_top) - p_rect->m_bottom) + p_rect->m_top != 0)) {
			m_unk0x28->VTable0x0c(this);
		}

		if ((m_unk0x34.m_left - p_rect->m_left) || (m_unk0x34.m_top - p_rect->m_top)) {
			m_unk0x28->VTable0x08(this);
		}
	}

	m_unk0x34 = *p_rect;
	return;
}

// FUNCTION: LEGORACERS 0x00472fc0
void ObscureVantage0x58::VTable0x14(VisualState0x4* p_param)
{
	m_color = p_param->m_color;
}

// FUNCTION: LEGORACERS 0x00472fd0
void ObscureVantage0x58::FUN_00472fd0(Rect* p_sourceRect, Rect* p_destRect)
{
	if (p_destRect->m_left >= p_destRect->m_right) {
		m_unk0x44 = 0.0f;
	}
	else {
		LegoFloat sourceWidth = static_cast<LegoFloat>(p_sourceRect->m_right - p_sourceRect->m_left);
		LegoFloat destWidth = static_cast<LegoFloat>(p_destRect->m_right - p_destRect->m_left);
		m_unk0x44 = sourceWidth / destWidth;
	}

	if (p_destRect->m_top >= p_destRect->m_bottom) {
		m_unk0x48 = 0.0f;
	}
	else {
		LegoFloat sourceHeight = static_cast<LegoFloat>(p_sourceRect->m_bottom - p_sourceRect->m_top);
		LegoFloat destHeight = static_cast<LegoFloat>(p_destRect->m_bottom - p_destRect->m_top);
		m_unk0x48 = sourceHeight / destHeight;
	}
}

// FUNCTION: LEGORACERS 0x00473050
void ObscureVantage0x58::FUN_00473050(Rect* p_sourceRect, Rect* p_destRect)
{
	p_destRect->m_top = static_cast<LegoS32>(p_sourceRect->m_top * m_unk0x48);
	p_destRect->m_left = static_cast<LegoS32>(p_sourceRect->m_left * m_unk0x44);
	p_destRect->m_right = static_cast<LegoS32>(p_sourceRect->m_right * m_unk0x44);
	p_destRect->m_bottom = static_cast<LegoS32>(p_sourceRect->m_bottom * m_unk0x48);
}

// FUNCTION: LEGORACERS 0x004730a0
LegoBool32 ObscureVantage0x58::ClipRect(Rect* p_rect, Rect* p_arg)
{
	if (p_rect->m_left >= m_unk0x34.m_right) {
		return FALSE;
	}

	if (p_rect->m_right <= m_unk0x34.m_left) {
		return FALSE;
	}

	if (p_rect->m_top >= m_unk0x34.m_bottom) {
		return FALSE;
	}

	if (p_rect->m_bottom <= m_unk0x34.m_top) {
		return FALSE;
	}

	if (p_rect->m_left < m_unk0x34.m_left) {
		p_arg->m_left += m_unk0x34.m_left - p_rect->m_left;
		p_rect->m_left = m_unk0x34.m_left;
	}

	if (p_rect->m_top < m_unk0x34.m_top) {
		p_arg->m_top += m_unk0x34.m_top - p_rect->m_top;
		p_rect->m_top = m_unk0x34.m_top;
	}

	if (p_rect->m_right > m_unk0x34.m_right) {
		p_arg->m_right += m_unk0x34.m_right - p_rect->m_right;
		p_rect->m_right = m_unk0x34.m_right;
	}

	if (p_rect->m_bottom > m_unk0x34.m_bottom) {
		p_arg->m_bottom += m_unk0x34.m_bottom - p_rect->m_bottom;
		p_rect->m_bottom = m_unk0x34.m_bottom;
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00473160
Rect* ObscureVantage0x58::FUN_00473160(Rect* p_rect)
{
	LegoS32 top = m_unk0x50 - m_unk0x34.m_top + p_rect->m_top;
	LegoS32 left = m_unk0x4c - m_unk0x34.m_left + p_rect->m_left;
	LegoS32 right = p_rect->m_right - p_rect->m_left + left;
	LegoS32 bottom = p_rect->m_bottom - p_rect->m_top + top;

	p_rect->m_left = left;
	p_rect->m_top = top;
	p_rect->m_right = right;
	p_rect->m_bottom = bottom;

	return p_rect;
}

// FUNCTION: LEGORACERS 0x004731b0
void ObscureVantage0x58::FUN_004731b0(undefined4& p_x, undefined4& p_y)
{
	p_x -= m_unk0x34.m_left;
	p_y -= m_unk0x34.m_top;
}

// FUNCTION: LEGORACERS 0x004731d0
LegoBool32 ObscureVantage0x58::VTable0x18(undefined4 p_unk0x04)
{
	ObscureVantage0x58* child = m_firstChild;

	if (VTable0x3c(p_unk0x04)) {
		return TRUE;
	}

	while (child) {
		if (child->VTable0x18(p_unk0x04)) {
			return TRUE;
		}

		child = child->m_nextSibling;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00473210
undefined4 ObscureVantage0x58::VTable0x1c(Rect* p_rect, Rect* p_arg)
{
	Rect rect = *p_rect;
	ObscureVantage0x58* child = m_firstChild;
	Rect arg = *p_arg;

	if (ClipRect(&rect, &arg)) {
		FUN_00473160(&rect);

		undefined flags = m_flags;
		if ((flags & 2) && (!(flags & 0x10) || !VTable0x38(&rect, &arg))) {
			for (; child; child = child->m_nextSibling) {
				if (child->VTable0x1c(&rect, &arg)) {
					break;
				}
			}
		}
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x004732d0
LegoBool32 ObscureVantage0x58::VTable0x20(CopperCrest0x40::Helper0x44* p_param1, undefined4 p_x, undefined4 p_y)
{
	ObscureVantage0x58* child = m_firstChild;
	undefined4 x = p_x;
	undefined4 y = p_y;

	FUN_004731b0(x, y);

	if ((m_flags & 2) && FUN_00472c40(x, y)) {
		while (child) {
			if (child->VTable0x20(p_param1, x, y)) {
				return TRUE;
			}

			child = child->m_nextSibling;
		}

		if (VTable0x2c(p_param1, x, y)) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00473370
LegoBool32 ObscureVantage0x58::VTable0x24(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	ObscureVantage0x58* child = m_firstChild;
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	FUN_004731b0(x, y);

	while (child) {
		if (child->VTable0x24(p_param1, x, y)) {
			return TRUE;
		}

		child = child->m_nextSibling;
	}

	return ObscureVantageEventResultValue(VTable0x30(p_param1, x, y));
}

// FUNCTION: LEGORACERS 0x00473400
LegoBool32 ObscureVantage0x58::VTable0x28(InputEventQueue::Event* p_param1, undefined4 p_x, undefined4 p_y)
{
	ObscureVantage0x58* child = m_firstChild;
	undefined4 x = p_x;
	undefined4 y = p_y;

	if (!(m_flags & 2)) {
		return FALSE;
	}

	FUN_004731b0(x, y);

	while (child) {
		if (child->VTable0x28(p_param1, x, y)) {
			return TRUE;
		}

		child = child->m_nextSibling;
	}

	return ObscureVantageEventResultValue(VTable0x34(p_param1, x, y));
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
ObscureVantage0x58* ObscureVantage0x58::VTable0x2c(void*, undefined4, undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
ObscureVantage0x58* ObscureVantage0x58::VTable0x30(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x00473490 FOLDED
ObscureVantage0x58* ObscureVantage0x58::VTable0x34(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x00473a20 FOLDED
LegoBool32 ObscureVantage0x58::FUN_00473a20(Rect* p_rect, LegoS32 p_x, LegoS32 p_y)
{
	return p_x >= p_rect->m_left && p_x <= p_rect->m_right && p_y >= p_rect->m_top && p_y <= p_rect->m_bottom;
}
