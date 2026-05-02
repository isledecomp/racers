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
LegoU32 GolCommonDrawState::VTable0x5c() const
{
	return 16;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
undefined4 GolCommonDrawState::VTable0x60()
{
	return 1;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x64() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x68() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x6c() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x70() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x74() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x78() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x7c() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x80() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x84() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x88() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x8c() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x90() const
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
LegoBool32 GolCommonDrawState::VTable0x98() const
{
	MATCHING(0x100016f0);
	return 0;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0x9c() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0xa0() const
{
	return TRUE;
}

// FUNCTION: GOLDP 0x1002fa30 FOLDED
LegoBool32 GolCommonDrawState::VTable0xa4() const
{
	return TRUE;
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoBool32 GolCommonDrawState::VTable0xa8() const
{
	MATCHING(0x100016f0);
	return FALSE;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
void* GolCommonDrawState::VTable0xac()
{
	return NULL;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
undefined4 GolCommonDrawState::VTable0xb0()
{
	return 0;
}

// FUNCTION: GOLDP 0x10018630 FOLDED
undefined4 GolCommonDrawState::VTable0xb4()
{
	return 0;
}
