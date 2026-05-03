#include "slatepeak0x58.h"

#include "bronzefalcon0xc8770.h"
#include "golcommondrawstate.h"
#include "goldrawdpstate.h"
#include "golerror.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(SlatePeak0x58, 0x58)

// FUNCTION: GOLDP 0x10003110
SlatePeak0x58::SlatePeak0x58()
{
	m_drawState = NULL;
	m_displaySurface = NULL;
	m_renderSurface = NULL;
	m_depthBuffer = NULL;
	m_clipper = NULL;
}

// FUNCTION: GOLDP 0x10003190
SlatePeak0x58::~SlatePeak0x58()
{
	SlatePeak0x58::VTable0x34();
}

// FUNCTION: GOLDP 0x100031f0
void SlatePeak0x58::VTable0x30(GolDrawState* p_drawState, undefined4 p_width, undefined4 p_height, undefined4)
{
	DDSURFACEDESC2 surfaceDesc;
	LegoChar errorMessage[100];

	if (m_pixelFlags & c_lockRequestRead) {
		VTable0x34();
	}

	m_unk0x30 = p_drawState;
	m_drawState = p_drawState;
	LPDIRECTDRAW4 ddraw = static_cast<GolDrawDPState*>(p_drawState)->m_ddraw4;
	LPDIRECTDRAWSURFACE4* renderSurface = &m_renderSurface;
	*renderSurface = NULL;

	::memset(&surfaceDesc, 0, sizeof(surfaceDesc));
	surfaceDesc.dwSize = sizeof(surfaceDesc);

	if (!(p_drawState->m_flags & GolDrawState::c_flagBit9)) {
		m_unk0x34 |= c_surfaceFlagWindowed;

		DWORD memoryCaps;
		if (static_cast<GolDrawDPState*>(p_drawState)->VTable0x60()) {
			m_unk0x34 |= c_surfaceFlagFlip;
			memoryCaps = DDSCAPS_VIDEOMEMORY;
		}
		else {
			m_unk0x34 &= ~c_surfaceFlagFlip;
			memoryCaps = DDSCAPS_SYSTEMMEMORY;
		}

		surfaceDesc.dwFlags = DDSD_CAPS;
		surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		LPDIRECTDRAWSURFACE4* displaySurface = &m_displaySurface;
		HRESULT result = ddraw->CreateSurface(&surfaceDesc, displaySurface, NULL);
		if (result) {
			::sprintf(errorMessage, "Unable to create display surface\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		result = (*displaySurface)->GetSurfaceDesc(&surfaceDesc);
		if (result) {
			::sprintf(errorMessage, "Unable to get surface desc\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		surfaceDesc.dwHeight = p_height;
		surfaceDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		surfaceDesc.dwWidth = p_width;
		surfaceDesc.ddpfPixelFormat.dwSize = sizeof(surfaceDesc.ddpfPixelFormat);
		surfaceDesc.ddsCaps.dwCaps = memoryCaps | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		result = ddraw->CreateSurface(&surfaceDesc, renderSurface, NULL);
		if (result) {
			::sprintf(errorMessage, "Unable to create video memory rendering surface\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		result = ::DirectDrawCreateClipper(0, &m_clipper, NULL);
		if (result) {
			::sprintf(errorMessage, "Unable to create clipper\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		result = m_clipper->SetHWnd(0, static_cast<GolDrawDPState*>(m_drawState)->m_hWnd);
		if (result) {
			::sprintf(errorMessage, "Unable to set window to clipper\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		result = (*displaySurface)->SetClipper(m_clipper);
		if (result) {
			::sprintf(errorMessage, "Unable to set clipper to surface\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}
	else if (p_drawState->m_flags & GolDrawState::c_flagBit19) {
		m_unk0x34 &= ~(c_surfaceFlagWindowed | c_surfaceFlagFlip);
		surfaceDesc.dwFlags = DDSD_CAPS;
		surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		LPDIRECTDRAWSURFACE4* displaySurface = &m_displaySurface;
		HRESULT result = ddraw->CreateSurface(&surfaceDesc, displaySurface, NULL);
		if (result) {
			::sprintf(errorMessage, "Unable to create display surface\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		result = (*displaySurface)->GetSurfaceDesc(&surfaceDesc);
		if (result) {
			::sprintf(errorMessage, "Unable to get surface desc\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		surfaceDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		surfaceDesc.dwWidth = p_width;
		surfaceDesc.dwHeight = p_height;
		surfaceDesc.ddpfPixelFormat.dwSize = sizeof(surfaceDesc.ddpfPixelFormat);
		surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		result = ddraw->CreateSurface(&surfaceDesc, renderSurface, NULL);
		if (result) {
			::sprintf(errorMessage, "Unable to create system memory rendering surface\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}
	else {
		m_unk0x34 &= ~c_surfaceFlagWindowed;
		surfaceDesc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;
		surfaceDesc.dwBackBufferCount = 1;
		LPDIRECTDRAWSURFACE4* displaySurface = &m_displaySurface;
		HRESULT result = ddraw->CreateSurface(&surfaceDesc, displaySurface, NULL);
		if (result) {
			::sprintf(errorMessage, "Unable to create primary drawing surface\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		DDSCAPS2 backBufferCaps;
		backBufferCaps.dwCaps = DDSCAPS_BACKBUFFER;
		LegoU32 restoreCount = 0;
		for (;;) {
			result = (*displaySurface)->GetAttachedSurface(&backBufferCaps, renderSurface);
			if (result) {
				if (result == DDERR_SURFACELOST && restoreCount < 1000) {
					(*displaySurface)->Restore();
					restoreCount++;
				}
				else if (result == DDERR_SURFACEBUSY || result == DDERR_WASSTILLDRAWING) {
					continue;
				}
				else {
					::sprintf(errorMessage, "Unable to get attached back buffer\nerror %x", result);
					GOL_FATALERROR_MESSAGE(errorMessage);
					continue;
				}
			}
			else {
				m_unk0x34 |= c_surfaceFlagFlip;
				break;
			}
		}
	}

	m_pixelFlags = c_lockRequestRead;
	HRESULT result = m_renderSurface->GetSurfaceDesc(&surfaceDesc);
	if (result) {
		::sprintf(errorMessage, "Unable to get surface desc\nerror %x", result);
		GOL_FATALERROR_MESSAGE(errorMessage);
	}

	m_width = (LegoU16) surfaceDesc.dwWidth;
	m_height = (LegoU16) surfaceDesc.dwHeight;
	m_textureFormat.m_redBitMask = surfaceDesc.ddpfPixelFormat.dwRBitMask;
	m_textureFormat.m_grnBitMask = surfaceDesc.ddpfPixelFormat.dwGBitMask;
	m_textureFormat.m_bluBitMask = surfaceDesc.ddpfPixelFormat.dwBBitMask;
	m_textureFormat.m_bitsPerPixel = (LegoU16) surfaceDesc.ddpfPixelFormat.dwRGBBitCount;
}

// FUNCTION: GOLDP 0x10003680
void SlatePeak0x58::VTable0x34()
{
	m_palette.Release();

	if (m_clipper) {
		m_clipper->Release();
		m_clipper = NULL;
	}

	if (m_depthBuffer) {
		m_depthBuffer->Release();
	}

	if (m_renderSurface) {
		m_renderSurface->Release();
	}
	m_renderSurface = NULL;

	if (m_displaySurface) {
		m_displaySurface->Release();
		m_displaySurface = NULL;
	}

	m_drawState = NULL;
	AzureRidge0x38::VTable0x34();
}

// FUNCTION: GOLDP 0x100036e0
void SlatePeak0x58::LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags)
{
	DDSURFACEDESC2 surfaceDesc;

	if (m_pixelFlags & c_lockFlagLocked) {
		*p_pixels = m_pixels;
		*p_pitch = m_pitch;
		return;
	}

	DWORD lockFlags = 0;
	if (p_flags & c_lockRequestRead) {
		m_pixelFlags |= c_lockFlagRead;
		if (!(p_flags & c_lockRequestWrite)) {
			lockFlags = DDLOCK_READONLY;
		}
	}

	if (p_flags & c_lockRequestWrite) {
		m_pixelFlags |= c_lockFlagWrite;
		if (!(p_flags & c_lockRequestRead)) {
			lockFlags |= DDLOCK_WRITEONLY;
		}
	}

	::memset(&surfaceDesc, 0, sizeof(surfaceDesc));
	surfaceDesc.dwSize = sizeof(surfaceDesc);

	for (;;) {
		LPDIRECTDRAWSURFACE4 renderSurface = m_renderSurface;
		HRESULT result;
		while ((result = renderSurface->Lock(NULL, &surfaceDesc, lockFlags, NULL)) == DDERR_SURFACEBUSY ||
			   result == DDERR_WASSTILLDRAWING) {
			::Sleep(1);
		}

		if (result) {
			if (result == DDERR_SURFACELOST) {
				if (m_renderSurface->Restore()) {
					m_pixels = NULL;
					*p_pixels = NULL;
					m_pitch = 0;
					*p_pitch = 0;
					m_pixelFlags &= ~c_lockFlagLocked;
					return;
				}
			}
			else {
				GOL_FATALERROR_MESSAGE("Unable to lock surface");
			}
		}
		else {
			m_pixels = (LegoU8*) surfaceDesc.lpSurface;
			*p_pitch = surfaceDesc.lPitch;
			m_pitch = (LegoU16) surfaceDesc.lPitch;
			*p_pixels = m_pixels;
			m_pixelFlags |= c_lockFlagLocked;
			return;
		}
	}
}

// FUNCTION: GOLDP 0x10003820
void SlatePeak0x58::UnlockPixels()
{
	if (m_pixelFlags & c_lockFlagLocked) {
		if (m_textureFormat.m_bitsPerPixel == 8 && m_palette.GetPalette() == NULL) {
			SetDisplayPalette(static_cast<GolCommonDrawState*>(m_drawState)->m_currentRenderer);
		}

		if (m_renderSurface->Unlock(NULL)) {
			GOL_FATALERROR_MESSAGE("Failed to Unlock display surface");
		}

		m_pixelFlags &= ~c_lockStateMask;
		m_pixels = NULL;
	}
}

// FUNCTION: GOLDP 0x10003880
void SlatePeak0x58::SetDisplayPalette(BronzeFalcon0xc8770* p_renderer)
{
	LegoChar errorMessage[64];

	if (m_textureFormat.m_bitsPerPixel <= 8) {
		if (m_palette.GetPalette() == NULL) {
			m_palette.CreateDirectDrawPalette(p_renderer, &m_textureFormat);
		}

		if (p_renderer->m_unk0xc8700 == 1) {
			m_palette.Set332PaletteEntries();
		}

		m_displaySurface->SetPalette(NULL);
		HRESULT result = m_displaySurface->SetPalette(m_palette.GetPalette());
		if (result) {
			::sprintf(errorMessage, "Unable to set display surface palette\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}
}

// FUNCTION: GOLDP 0x10003900
void SlatePeak0x58::LockAuxPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags)
{
	DDSURFACEDESC2 surfaceDesc;

	if (m_auxFlags & c_lockFlagLocked) {
		*p_pixels = m_auxPixels;
		*p_pitch = m_pitch;
		return;
	}

	DWORD lockFlags = 0;
	if (p_flags & c_lockRequestRead) {
		m_auxFlags |= c_lockFlagRead;
		if (!(p_flags & c_lockRequestWrite)) {
			lockFlags = DDLOCK_READONLY;
		}
	}

	if (p_flags & c_lockRequestWrite) {
		m_auxFlags |= c_lockFlagWrite;
		if (!(p_flags & c_lockRequestRead)) {
			lockFlags |= DDLOCK_WRITEONLY;
		}
	}

	::memset(&surfaceDesc, 0, sizeof(surfaceDesc));
	surfaceDesc.dwSize = sizeof(surfaceDesc);

	for (;;) {
		LPDIRECTDRAWSURFACE4 displaySurface = m_displaySurface;
		HRESULT result;
		while ((result = displaySurface->Lock(NULL, &surfaceDesc, lockFlags, NULL)) == DDERR_SURFACEBUSY ||
			   result == DDERR_WASSTILLDRAWING) {
			::Sleep(1);
		}

		if (result) {
			if (result == DDERR_SURFACELOST) {
				if (m_displaySurface->Restore()) {
					m_pixels = NULL;
					*p_pixels = NULL;
					m_pitch = 0;
					*p_pitch = 0;
					m_auxFlags &= ~c_lockFlagLocked;
					return;
				}
			}
			else {
				GOL_FATALERROR_MESSAGE("Unable to lock surface");
			}
		}
		else {
			m_auxPixels = (LegoU8*) surfaceDesc.lpSurface;
			*p_pitch = surfaceDesc.lPitch;
			m_pitch = (LegoU16) surfaceDesc.lPitch;
			*p_pixels = m_auxPixels;
			m_auxFlags |= c_lockFlagLocked;
			return;
		}
	}
}

// FUNCTION: GOLDP 0x10003a40
void SlatePeak0x58::UnlockAuxPixels()
{
	if (m_auxFlags & c_lockFlagLocked) {
		if (m_displaySurface->Unlock(NULL)) {
			GOL_FATALERROR_MESSAGE("Failed to Unlock display surface");
		}

		m_auxFlags &= ~c_lockStateMask;
		m_auxPixels = NULL;
	}
}

// FUNCTION: GOLDP 0x10003a80
void SlatePeak0x58::VTable0x14(undefined4* p_wait)
{
	RECT destRect;

	if (m_unk0x34 & 1) {
		HWND hWnd = static_cast<GolDrawDPState*>(m_drawState)->m_hWnd;
		::GetClientRect(hWnd, &destRect);

		LegoS32 width = destRect.right - destRect.left;
		LegoS32 height = destRect.bottom - destRect.top;
		POINT topLeft;
		topLeft.y = 0;
		topLeft.x = 0;
		::ClientToScreen(hWnd, &topLeft);

		destRect.left = topLeft.x;
		destRect.top = topLeft.y;
		destRect.right = topLeft.x + width;
		destRect.bottom = topLeft.y + height;
	}
	else {
		destRect.left = 0;
		destRect.top = 0;
		destRect.right = m_width;
		destRect.bottom = m_height;
	}

	if ((m_unk0x34 & 2) && !(m_unk0x34 & 1)) {
		if (p_wait != NULL) {
			LPDIRECTDRAWSURFACE4 displaySurface = m_displaySurface;
			HRESULT result;
			while ((result = displaySurface->Flip(NULL, 0)) == DDERR_SURFACEBUSY || result == DDERR_WASSTILLDRAWING) {
				::Sleep(1);
			}

			m_pixelFlags &= ~c_lockFlagUnknown0x04;
		}
		else {
			HRESULT result = m_displaySurface->Flip(NULL, 0);
			if (result == DDERR_WASSTILLDRAWING) {
				m_pixelFlags |= c_lockFlagUnknown0x04;
			}
			else {
				m_pixelFlags &= ~c_lockFlagUnknown0x04;
			}
		}

		return;
	}

	RECT sourceRect;
	sourceRect.top = 0;
	sourceRect.left = 0;
	sourceRect.right = m_width;
	sourceRect.bottom = m_height;

	for (;;) {
		LPDIRECTDRAWSURFACE4 renderSurface = m_renderSurface;
		LPDIRECTDRAWSURFACE4 displaySurface = m_displaySurface;
		HRESULT result;
		while ((result = displaySurface->Blt(&destRect, renderSurface, &sourceRect, 0, NULL)) == DDERR_SURFACEBUSY ||
			   result == DDERR_WASSTILLDRAWING) {
			::Sleep(1);
		}

		if (result != DD_OK && result != DDERR_INVALIDRECT && result != DDERR_SURFACELOST) {
			GOL_FATALERROR_MESSAGE("Unable to blit back buffer to screen");
		}

		return;
	}
}

// FUNCTION: GOLDP 0x10003bf0
void SlatePeak0x58::VTable0x18()
{
	if (m_pixelFlags & c_lockFlagUnknown0x04) {
		LegoChar errorMessage[100];

		m_pixelFlags &= ~c_lockFlagUnknown0x04;

		for (;;) {
			LPDIRECTDRAWSURFACE4 displaySurface = m_displaySurface;
			HRESULT result;
			while ((result = displaySurface->Flip(NULL, 0)) == DDERR_SURFACEBUSY || result == DDERR_WASSTILLDRAWING) {
				::Sleep(1);
			}

			if (result != DD_OK && result != DDERR_SURFACELOST) {
				::sprintf(errorMessage, "Error flipping display surface\nError code = %x", result);
				GOL_FATALERROR_MESSAGE(errorMessage);
				continue;
			}

			return;
		}
	}
}

// FUNCTION: GOLDP 0x10003c70
LegoS32 SlatePeak0x58::AttachDepthBuffer(DepthBuffer0x38* p_depthBuffer)
{
	LPDIRECTDRAWSURFACE4 surface = p_depthBuffer->m_surface;
	if (m_renderSurface->AddAttachedSurface(surface)) {
		return -1;
	}

	m_depthBuffer = p_depthBuffer;
	return 0;
}

// FUNCTION: GOLDP 0x10003ca0
void SlatePeak0x58::DetachDepthBuffer(DepthBuffer0x38* p_depthBuffer)
{
	m_renderSurface->DeleteAttachedSurface(0, p_depthBuffer->m_surface);
	m_depthBuffer = NULL;
}

// FUNCTION: GOLDP 0x10003cd0
IPalette0x4* SlatePeak0x58::GetPalette()
{
	if (m_palette.GetPalette()) {
		return &m_palette;
	}

	return NULL;
}

// FUNCTION: GOLDP 0x10003ce0
void SlatePeak0x58::Fill(LegoU32 p_color)
{
	DDBLTFX bltFx;
	LegoChar errorMessage[100];

	::memset(&bltFx, 0, sizeof(bltFx));
	bltFx.dwSize = sizeof(bltFx);
	bltFx.dwFillColor = p_color;

	for (;;) {
		LPDIRECTDRAWSURFACE4 renderSurface = m_renderSurface;
		HRESULT result;

		while ((result = renderSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &bltFx)) == DDERR_SURFACEBUSY ||
			   result == DDERR_WASSTILLDRAWING) {
			::Sleep(1);
		}

		if (result == DD_OK || result == DDERR_SURFACELOST) {
			return;
		}

		::sprintf(errorMessage, "Error filling display surface\nError code = %x", result);
		GOL_FATALERROR_MESSAGE(errorMessage);
	}
}

// FUNCTION: GOLDP 0x10003d80
void SlatePeak0x58::VTable0x28(Rect* p_destRect, SilverDune0x30* p_source, Rect* p_sourceRect)
{
	RECT destRect;
	RECT sourceRect;
	DDBLTFX bltFx;
	LegoChar errorMessage[100];

	destRect.left = p_destRect->m_left;
	destRect.right = p_destRect->m_right;
	destRect.top = p_destRect->m_top;
	destRect.bottom = p_destRect->m_bottom;

	sourceRect.left = p_sourceRect->m_left;
	sourceRect.right = p_sourceRect->m_right;
	sourceRect.top = p_sourceRect->m_top;
	sourceRect.bottom = p_sourceRect->m_bottom;

	::memset(&bltFx, 0, sizeof(bltFx));
	bltFx.dwSize = sizeof(bltFx);

	if (m_pixelFlags & c_lockFlagUnknown0x04) {
		VTable0x18();
	}

	SlatePeak0x58* source = static_cast<SlatePeak0x58*>(p_source);
	if (source->m_pixelFlags & c_lockFlagUnknown0x04) {
		source->VTable0x18();
	}

	for (;;) {
		LPDIRECTDRAWSURFACE4 sourceSurface = source->m_renderSurface;
		LPDIRECTDRAWSURFACE4 renderSurface = m_renderSurface;
		HRESULT result;

		while ((result = renderSurface->Blt(&destRect, sourceSurface, &sourceRect, 0, &bltFx)) == DDERR_SURFACEBUSY ||
			   result == DDERR_WASSTILLDRAWING) {
			::Sleep(1);
		}

		if (result == DD_OK || result == DDERR_SURFACELOST) {
			return;
		}

		::sprintf(errorMessage, "Error in blit of display surface\nError code = %x", result);
		GOL_FATALERROR_MESSAGE(errorMessage);
	}
}

// STUB: GOLDP 0x10003e90
void SlatePeak0x58::VTable0x2c()
{
	STUB(0x10003e90);
}
