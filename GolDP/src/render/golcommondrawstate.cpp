#include "render/golcommondrawstate.h"

DECOMP_SIZE_ASSERT(GolCommonDrawState, 0x20)

// FUNCTION: GOLDP 0x100184a0
GolCommonDrawState::GolCommonDrawState()
{
	m_rendererList = NULL;
	m_currentRenderer = NULL;
}

// FUNCTION: GOLDP 0x100184e0
LegoS32 GolCommonDrawState::RecreateDisplay(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp, LegoU32 p_flags)
{
	LegoS32 result = GolDrawState::RecreateDisplay(p_width, p_height, p_bpp, p_flags);
	if (!result) {
		result = CreateDirect3D();
	}

	return result;
}

// FUNCTION: GOLDP 0x10018510
void GolCommonDrawState::DestroyDisplay()
{
	GolD3DRenderDevice* next;
	for (GolD3DRenderDevice* renderer = m_rendererList; renderer; renderer = next) {
		next = renderer->m_nextDrawStateRenderer;
		renderer->Shutdown();
	}

	GolDrawState::DestroyDisplay();
}

// FUNCTION: GOLDP 0x10018540
void GolCommonDrawState::ReleaseDisplay()
{
	for (GolD3DRenderDevice* renderer = m_rendererList; renderer; renderer = renderer->m_nextDrawStateRenderer) {
		renderer->ReleaseResources();
	}

	GolDrawState::ReleaseDisplay();
}

// FUNCTION: GOLDP 0x10018570
LegoS32 GolCommonDrawState::CreateDisplay(LegoS32 p_width, LegoS32 p_height, undefined4 p_bp, LegoU32 p_flags)
{
	GolDrawState::CreateDisplay(p_width, p_height, p_bp, p_flags);
	LegoS32 result = CreateDirect3D();
	if (!result) {
		for (GolD3DRenderDevice* renderer = m_rendererList; renderer; renderer = renderer->m_nextDrawStateRenderer) {
			if (renderer != m_currentRenderer) {
				renderer->RestoreResources();
			}
		}

		return 0;
	}

	return result;
}

// FUNCTION: GOLDP 0x100185c0
GolD3DRenderDevice* GolCommonDrawState::AddRenderer(GolD3DRenderDevice* p_renderer)
{
	p_renderer->m_nextDrawStateRenderer = m_rendererList;
	m_rendererList = p_renderer;
	return p_renderer;
}

// FUNCTION: GOLDP 0x100185d0
GolD3DRenderDevice* GolCommonDrawState::RemoveRenderer(GolD3DRenderDevice* p_renderer)
{
	GolD3DRenderDevice* result = m_rendererList;
	if (result) {
		if (p_renderer == result) {
			result = result->m_nextDrawStateRenderer;
			m_rendererList = result;
		}
		else {
			GolD3DRenderDevice* previous = m_rendererList;
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

// FUNCTION: GOLDP 0x100016f0 FOLDED
undefined4 GolCommonDrawState::SupportsWBuffer()
{
	return 0;
}

// FUNCTION: GOLDP 0x100016f0 FOLDED
LegoBool32 GolCommonDrawState::SupportsZBufferlessHsr() const
{
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

// FUNCTION: GOLDP 0x100016f0 FOLDED
LegoBool32 GolCommonDrawState::SupportsRenderingInWindow() const
{
	return FALSE;
}

// TODO: This section keeps the 0x10018630 zero-return fold group from folding into 0x100016f0.
#pragma code_seg(".text$goldp_10018630")

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

#pragma code_seg()
