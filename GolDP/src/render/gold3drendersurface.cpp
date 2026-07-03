#include "render/gold3drendersurface.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GolD3DRenderSurface, 0x5c)

#include "golerror.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "render/goldrawdpstate.h"
#include "render/goldrawstate.h"

#include <stdio.h>
#include <string.h>

// FUNCTION: GOLDP 0x10013540
GolD3DRenderSurface::GolD3DRenderSurface()
{
	m_next = NULL;
}

// FUNCTION: GOLDP 0x10013580
GolD3DRenderSurface::~GolD3DRenderSurface()
{
	ReleaseResources();
	m_next = NULL;
	m_drawState = NULL;
}

// FUNCTION: GOLDP 0x10013600
void GolD3DRenderSurface::FUN_10013600(GolD3DRenderDevice* p_renderer, undefined2 p_width, undefined2 p_height)
{
	if (m_pixelFlags & c_lockRequestRead) {
		Destroy();
	}

	GolCommonDrawState* drawState = p_renderer->GetDrawState();
	m_displayDrawState = drawState;
	m_drawState = drawState;
	m_width = p_width;
	m_height = p_height;
	m_textureFormat = p_renderer->GetRenderTargetInfo()->GetTextureFormat();

	FUN_100136a0(p_renderer);
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GolD3DRenderSurface::Present(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10013660
void GolD3DRenderSurface::Destroy()
{
	ReleaseResources();
	m_next = NULL;
	m_drawState = NULL;
}

// FUNCTION: GOLDP 0x100136a0
void GolD3DRenderSurface::FUN_100136a0(GolD3DRenderDevice* p_renderer)
{
	LPDIRECTDRAW4 ddraw = static_cast<GolDrawDPState*>(m_drawState)->m_ddraw4;

	DDSURFACEDESC2 surfaceDesc;
	LegoChar errorMessage[100];

	m_renderSurface = NULL;
	::memset(&surfaceDesc, 0, sizeof(surfaceDesc));
	surfaceDesc.dwSize = sizeof(surfaceDesc);

	HRESULT result = p_renderer->m_renderTargetInfo->GetRenderSurface()->GetSurfaceDesc(&surfaceDesc);
	if (result) {
		::sprintf(errorMessage, "Unable to get surface desc\nerror %x", result);
		GOL_FATALERROR_MESSAGE(errorMessage);
	}

	surfaceDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	surfaceDesc.dwWidth = m_width;
	surfaceDesc.dwHeight = m_height;
	surfaceDesc.ddpfPixelFormat.dwSize = sizeof(surfaceDesc.ddpfPixelFormat);

	if ((m_drawState->m_flags & GolDrawState::c_flagBit19) ||
		(p_renderer->m_flags & GolRenderDevice::c_flagSoftwareRenderer)) {
		surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		m_surfaceFlags &= ~(c_surfaceFlagWindowed | c_surfaceFlagFlip);
	}
	else {
		surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		m_surfaceFlags &= ~(c_surfaceFlagWindowed | c_surfaceFlagFlip);
		m_surfaceFlags |= c_surfaceFlagFlip;
	}

	result = ddraw->CreateSurface(&surfaceDesc, &m_displaySurface, NULL);
	if (result) {
		::sprintf(errorMessage, "Unable to create rendering surface\nerror %x", result);
		GOL_FATALERROR_MESSAGE(errorMessage);
	}

	m_pixelFlags = c_lockRequestRead;
	m_renderSurface = m_displaySurface;
}

// FUNCTION: GOLDP 0x100137d0
void GolD3DRenderSurface::ReleaseResources()
{
	m_palette.Release();

	if (m_depthBuffer != NULL) {
		m_depthBuffer->Release();
	}

	if (m_displaySurface != NULL) {
		m_displaySurface->Release();
		m_displaySurface = NULL;
	}

	m_renderSurface = NULL;
	GolDisplaySurface::Destroy();
}
