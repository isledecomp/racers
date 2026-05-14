#include "bronzefalconsurface0x5c.h"

#include "bronzefalcon0xc8770.h"
#include "golcommondrawstate.h"
#include "goldrawdpstate.h"
#include "goldrawstate.h"
#include "golerror.h"

#include <stdio.h>
#include <string.h>

// FUNCTION: GOLDP 0x10013540
BronzeFalconSurface0x5c::BronzeFalconSurface0x5c()
{
	m_next = NULL;
}

// FUNCTION: GOLDP 0x10013580
BronzeFalconSurface0x5c::~BronzeFalconSurface0x5c()
{
	ReleaseResources();
	m_next = NULL;
	m_drawState = NULL;
}

// FUNCTION: GOLDP 0x10013600
void BronzeFalconSurface0x5c::FUN_10013600(BronzeFalcon0xc8770* p_renderer, undefined2 p_width, undefined2 p_height)
{
	if (m_pixelFlags & c_lockRequestRead) {
		VTable0x34();
	}

	GolCommonDrawState* drawState = p_renderer->GetDrawState();
	m_unk0x30 = drawState;
	m_drawState = drawState;
	m_width = p_width;
	m_height = p_height;
	m_textureFormat = p_renderer->GetRenderTargetInfo()->GetTextureFormat();

	FUN_100136a0(p_renderer);
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void BronzeFalconSurface0x5c::VTable0x14(undefined4*)
{
	// empty
}

// FUNCTION: GOLDP 0x10013660
void BronzeFalconSurface0x5c::VTable0x34()
{
	ReleaseResources();
	m_next = NULL;
	m_drawState = NULL;
}

// FUNCTION: GOLDP 0x100136a0
void BronzeFalconSurface0x5c::FUN_100136a0(BronzeFalcon0xc8770* p_renderer)
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

	if ((m_drawState->m_flags & GolDrawState::c_flagBit19) || (p_renderer->m_flags & WhiteFalcon0x140::c_flagBit16)) {
		surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		m_unk0x34 &= ~(c_surfaceFlagWindowed | c_surfaceFlagFlip);
	}
	else {
		surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		m_unk0x34 &= ~(c_surfaceFlagWindowed | c_surfaceFlagFlip);
		m_unk0x34 |= c_surfaceFlagFlip;
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
void BronzeFalconSurface0x5c::ReleaseResources()
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
	AzureRidge0x38::VTable0x34();
}
