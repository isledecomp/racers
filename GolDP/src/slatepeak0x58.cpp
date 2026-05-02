#include "slatepeak0x58.h"

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

// STUB: GOLDP 0x100031f0
void SlatePeak0x58::VTable0x30(GolDrawState*, undefined4, undefined4, undefined4)
{
	STUB(0x100031f0);
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

// STUB: GOLDP 0x100036e0
void SlatePeak0x58::LockPixels(LegoU8**, LegoU32*, LegoU32)
{
	STUB(0x100036e0);
}

// STUB: GOLDP 0x10003820
void SlatePeak0x58::UnlockPixels()
{
	STUB(0x10003820);
}

// STUB: GOLDP 0x10003900
void SlatePeak0x58::LockAuxPixels(LegoU8**, LegoU32*, LegoU32)
{
	STUB(0x10003900);
}

// STUB: GOLDP 0x10003a40
void SlatePeak0x58::UnlockAuxPixels()
{
	STUB(0x10003a40);
}

// STUB: GOLDP 0x10003a80
void SlatePeak0x58::VTable0x14(undefined4*)
{
	STUB(0x10003a80);
}

// STUB: GOLDP 0x10003bf0
void SlatePeak0x58::VTable0x18()
{
	STUB(0x10003bf0);
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

// STUB: GOLDP 0x10003d80
void SlatePeak0x58::VTable0x28(undefined4, undefined4, undefined4*)
{
	STUB(0x10003d80);
}

// STUB: GOLDP 0x10003e90
void SlatePeak0x58::VTable0x2c()
{
	STUB(0x10003e90);
}
