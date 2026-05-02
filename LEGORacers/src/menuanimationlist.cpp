#include "menuanimationlist.h"

#include "bronzefalcon0xc8770.h"
#include "golerror.h"
#include "slatepeak0x58.h"

DECOMP_SIZE_ASSERT(MenuAnimationList, 0x8)
DECOMP_SIZE_ASSERT(MenuAnimationList::Entry, 0x18)
DECOMP_SIZE_ASSERT(MenuAnimationList::Entry::ScreenRect, 0x10)
DECOMP_SIZE_ASSERT(MenuAnimationList::Entry::ScreenRectSource, 0x120)
DECOMP_SIZE_ASSERT(MenuAnimationList::Entry::DrawScratch, 0x78)

// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
MenuAnimationList::MenuAnimationList()
{
	m_entries = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00490500
MenuAnimationList::Entry::Entry()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00490510
MenuAnimationList::Entry::~Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00490520
void MenuAnimationList::Entry::Reset()
{
	Deactivate();
}

// FUNCTION: LEGORACERS 0x00490530
void MenuAnimationList::Entry::Clear()
{
	m_material = 0;
	m_rectSource = NULL;
	m_remainingMs = 0;
	m_durationMs = 0;
	m_flags = 0;
	m_red = 0;
	m_green = 0;
	m_blue = 0;
	m_unk0x0b = 0;
}

// FUNCTION: LEGORACERS 0x00490550
void MenuAnimationList::Entry::Activate(
	LegoU32 p_durationMs,
	LegoBool32 p_fadeOut,
	undefined4 p_material,
	const ScreenRectSource* p_rectSource
)
{
	m_material = p_material;
	m_remainingMs = p_durationMs;
	m_durationMs = p_durationMs;
	LegoU8 flags = m_flags | c_flagActive;
	m_rectSource = p_rectSource;
	m_flags = flags;

	if (p_fadeOut) {
		m_flags = flags | c_flagFadeOut;
	}
}

// FUNCTION: LEGORACERS 0x00490580
void MenuAnimationList::Entry::Deactivate()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00490590
void MenuAnimationList::Entry::Update(LegoU32 p_elapsedMs)
{
	if (m_flags & c_flagActive) {
		if (!m_remainingMs) {
			if (m_flags & c_flagExpired) {
				Deactivate();
			}
			else {
				m_flags |= c_flagExpired;
			}
		}

		if (p_elapsedMs > m_remainingMs) {
			m_remainingMs = 0;
			return;
		}

		m_remainingMs -= p_elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x004905e0
void MenuAnimationList::Entry::Draw(BronzeFalcon0xc8770* p_renderer)
{
	DrawScratch scratch;

	if (!(m_flags & c_flagActive)) {
		return;
	}

	if (m_rectSource) {
		scratch.m_rect = *m_rectSource->GetRect();
	}
	else {
		scratch.m_rect.m_top = 0;
		scratch.m_rect.m_left = 0;
		const SlatePeak0x58* renderTargetInfo = p_renderer->GetRenderTargetInfo();
		scratch.m_rect.m_bottom = renderTargetInfo->GetHeight();
		renderTargetInfo = p_renderer->GetRenderTargetInfo();
		scratch.m_rect.m_right = renderTargetInfo->GetWidth();
	}

	if (!(m_flags & c_flagFadeOut)) {
		LegoFloat duration = (LegoFloat) (LegoS32) m_durationMs;
		LegoFloat progress = (LegoFloat) (LegoS32) m_remainingMs / duration;
		progress = 1.0f - progress;
		scratch.m_alpha = progress * 255.0f;
	}
	else {
		LegoFloat duration = (LegoFloat) (LegoS32) m_durationMs;
		LegoFloat progress = (LegoFloat) (LegoS32) m_remainingMs / duration;
		scratch.m_alpha = progress * 255.0f;
	}

	scratch.m_topLeft.m_x = (LegoFloat) scratch.m_rect.m_left;
	scratch.m_topAsFloat = (LegoFloat) scratch.m_rect.m_top;
	scratch.m_topLeft.m_y = scratch.m_topAsFloat;
	scratch.m_topLeft.m_z = 0.0f;
	scratch.m_topLeft.m_u = 0.0f;
	scratch.m_topLeft.m_v = 0.0f;
	scratch.m_topLeft.m_red = m_red;
	scratch.m_topLeft.m_green = m_green;
	scratch.m_topLeft.m_blue = m_blue;
	scratch.m_topLeft.m_alpha = scratch.m_alpha;

	scratch.m_bottomLeft.m_x = scratch.m_topLeft.m_x;
	scratch.m_bottomLeft.m_y = (LegoFloat) scratch.m_rect.m_bottom;
	scratch.m_bottomLeft.m_z = 0.0f;
	scratch.m_bottomLeft.m_u = 0.0f;
	scratch.m_bottomLeft.m_v = 1.0f;
	scratch.m_bottomLeft.m_red = m_red;
	scratch.m_bottomLeft.m_green = m_green;
	scratch.m_bottomLeft.m_blue = m_blue;
	scratch.m_bottomLeft.m_alpha = scratch.m_alpha;

	scratch.m_topRight.m_x = (LegoFloat) scratch.m_rect.m_right;
	scratch.m_topRight.m_y = scratch.m_topAsFloat;
	scratch.m_topRight.m_z = 0.0f;
	scratch.m_topRight.m_u = 1.0f;
	scratch.m_topRight.m_v = 0.0f;
	scratch.m_topRight.m_red = m_red;
	scratch.m_topRight.m_green = m_green;
	scratch.m_topRight.m_blue = m_blue;
	scratch.m_topRight.m_alpha = scratch.m_alpha;

	scratch.m_bottomRight.m_x = scratch.m_topRight.m_x;
	scratch.m_bottomRight.m_y = scratch.m_bottomLeft.m_y;
	scratch.m_bottomRight.m_z = 0.0f;
	scratch.m_bottomRight.m_u = 1.0f;
	scratch.m_bottomRight.m_v = 1.0f;
	scratch.m_bottomRight.m_red = m_red;
	scratch.m_bottomRight.m_green = m_green;
	scratch.m_bottomRight.m_blue = m_blue;
	scratch.m_bottomRight.m_alpha = scratch.m_alpha;

	p_renderer->SetAlphaOverride(scratch.m_alpha, TRUE);
	p_renderer->DrawTriangle(&scratch.m_bottomLeft, &scratch.m_topLeft, &scratch.m_bottomRight, m_material, 0);
	p_renderer->DrawTriangle(&scratch.m_bottomRight, &scratch.m_topLeft, &scratch.m_topRight, m_material, 0);
	p_renderer->ClearAlphaOverride();
}

// FUNCTION: LEGORACERS 0x00494d90
MenuAnimationList::~MenuAnimationList()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00494da0
void MenuAnimationList::Reset()
{
	if (m_entries) {
		for (LegoU32 i = 0; i < m_count; i++) {
			m_entries[i].Reset();
		}

		delete[] m_entries;
		m_entries = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00494e10
void MenuAnimationList::Allocate(LegoU32 p_count)
{
	if (m_entries) {
		Reset();
	}

	if (p_count) {
		m_entries = new Entry[p_count];
		if (!m_entries) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_count = p_count;
	}
}

// FUNCTION: LEGORACERS 0x00494f60
void MenuAnimationList::Update(LegoU32 p_elapsedMs)
{
	for (LegoU32 i = 0; i < m_count; i++) {
		if (m_entries[i].IsActive()) {
			m_entries[i].Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x00494fa0
void MenuAnimationList::Draw(BronzeFalcon0xc8770* p_renderer)
{
	for (LegoU32 i = 0; i < m_count; i++) {
		if (m_entries[i].IsActive()) {
			m_entries[i].Draw(p_renderer);
		}
	}
}
