#include "golcommondrawstate.h"

DECOMP_SIZE_ASSERT(GolCommonDrawState, 0x20)

// FUNCTION: GOLDP 0x100184a0
GolCommonDrawState::GolCommonDrawState()
{
	m_rendererList = NULL;
	m_currentRenderer = NULL;
}

// FUNCTION: GOLDP 0x100184e0
LegoS32 GolCommonDrawState::VTable0x44(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp, LegoU32 p_flags)
{
	LegoS32 result = GolDrawState::VTable0x44(p_width, p_height, p_bpp, p_flags);
	if (!result) {
		result = VTable0x58();
	}

	return result;
}

// FUNCTION: GOLDP 0x10018510
void GolCommonDrawState::VTable0x48()
{
	BronzeFalcon0xc8770* next;
	for (BronzeFalcon0xc8770* renderer = m_rendererList; renderer; renderer = next) {
		next = renderer->m_nextDrawStateRenderer;
		renderer->VTable0x18();
	}

	GolDrawState::VTable0x48();
}

// FUNCTION: GOLDP 0x10018540
void GolCommonDrawState::VTable0x50()
{
	for (BronzeFalcon0xc8770* renderer = m_rendererList; renderer; renderer = renderer->m_nextDrawStateRenderer) {
		renderer->ReleaseResources();
	}

	GolDrawState::VTable0x50();
}

// FUNCTION: GOLDP 0x10018570
LegoS32 GolCommonDrawState::VTable0x54(LegoS32 p_width, LegoS32 p_height, undefined4 p_bp, LegoU32 p_flags)
{
	GolDrawState::VTable0x54(p_width, p_height, p_bp, p_flags);
	LegoS32 result = VTable0x58();
	if (!result) {
		for (BronzeFalcon0xc8770* renderer = m_rendererList; renderer; renderer = renderer->m_nextDrawStateRenderer) {
			if (renderer != m_currentRenderer) {
				renderer->RestoreResources();
			}
		}

		return 0;
	}

	return result;
}

// FUNCTION: GOLDP 0x100185c0
BronzeFalcon0xc8770* GolCommonDrawState::AddRenderer(BronzeFalcon0xc8770* p_renderer)
{
	p_renderer->m_nextDrawStateRenderer = m_rendererList;
	m_rendererList = p_renderer;
	return p_renderer;
}

// FUNCTION: GOLDP 0x100185d0
BronzeFalcon0xc8770* GolCommonDrawState::RemoveRenderer(BronzeFalcon0xc8770* p_renderer)
{
	BronzeFalcon0xc8770* result = m_rendererList;
	if (result) {
		if (p_renderer == result) {
			result = result->m_nextDrawStateRenderer;
			m_rendererList = result;
		}
		else {
			BronzeFalcon0xc8770* previous = m_rendererList;
			result = result->m_nextDrawStateRenderer;
			while (result) {
				if (result == p_renderer) {
					previous->m_nextDrawStateRenderer = result->m_nextDrawStateRenderer;
					result->m_nextDrawStateRenderer = NULL;
					break;
				}
				else {
					previous = result;
					result = result->m_nextDrawStateRenderer;
				}
			}
		}
	}

	return result;
}

// FUNCTION: GOLDP 0x10018620
LegoU32 GolCommonDrawState::GetZBufferBitDepth() const
{
	return 16;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::IsHwAccelerated()
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsCulling() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsPerspectiveCorrection() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsTextureWrap() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsCullCW() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsCullCCW() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsDither() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsSubpixel() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsLinearFilter() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsMipmap() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsFogTable() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsTextureAlpha() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsAdditiveBlend() const
{
	return TRUE;
}

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 GolCommonDrawState::VTable0x94()
{
	MATCHING(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoBool32 GolCommonDrawState::SupportsZBufferlessHsr() const
{
	MATCHING(0x100016f0);
	return 0;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsPaletteAlpha() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsTextureSystemMemory() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::SupportsTextureVideoMemory() const
{
	return TRUE;
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoBool32 GolCommonDrawState::SupportsRenderingInWindow() const
{
	MATCHING(0x100016f0);
	return FALSE;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
LPDIRECTDRAW GolCommonDrawState::GetDirectDraw()
{
	return NULL;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
LPDIRECTDRAWSURFACE GolCommonDrawState::GetDisplaySurface()
{
	return NULL;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
LPDIRECTDRAWSURFACE GolCommonDrawState::GetRenderSurface()
{
	return NULL;
}
