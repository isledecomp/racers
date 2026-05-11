#include "depthbuffer0x38.h"

#include "goldrawdpstate.h"
#include "slatepeak0x58.h"

#include <string.h>

DECOMP_SIZE_ASSERT(DepthBuffer0x38, 0x38)

// FUNCTION: GOLDP 0x100182b0
DepthBuffer0x38::DepthBuffer0x38()
{
	m_surface = NULL;
}

// FUNCTION: GOLDP 0x100182f0
DepthBuffer0x38::~DepthBuffer0x38()
{
	Release();
}

// FUNCTION: GOLDP 0x10018370
LegoS32 DepthBuffer0x38::Create(GolDrawDPState* p_arg1, SlatePeak0x58* p_surface)
{
	LPDIRECTDRAW4 ddraw = p_arg1->m_ddraw4;
	DDSURFACEDESC2 ddSurfaceDesc;

	::memset(&ddSurfaceDesc, 0, sizeof(ddSurfaceDesc));
	ddSurfaceDesc.dwHeight = p_surface->m_height;
	ddSurfaceDesc.dwSize = sizeof(ddSurfaceDesc);
	ddSurfaceDesc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT;
	ddSurfaceDesc.dwWidth = p_surface->m_width;
	ddSurfaceDesc.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
	if (p_arg1->IsHwAccelerated()) {
		ddSurfaceDesc.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
	}
	else {
		ddSurfaceDesc.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}
	::memcpy(&ddSurfaceDesc.ddpfPixelFormat, &p_arg1->m_depthBufferPixelformat, sizeof(ddSurfaceDesc.ddpfPixelFormat));
	if (ddraw->CreateSurface(&ddSurfaceDesc, &m_surface, NULL) != DD_OK) {
		return -1;
	}

	m_pixelFlags = c_lockRequestRead;
	m_width = p_surface->m_width;
	m_height = p_surface->m_height;
	m_textureFormat.m_bitsPerPixel = static_cast<LegoU16>(ddSurfaceDesc.ddpfPixelFormat.dwZBufferBitDepth);

	LegoS32 result = p_surface->AttachDepthBuffer(this);
	if (result == 0) {
		m_attachedSurface = p_surface;
	}

	return result;
}

// FUNCTION: GOLDP 0x10018460
void DepthBuffer0x38::Release()
{
	if (m_attachedSurface != NULL) {
		m_attachedSurface->DetachDepthBuffer(this);
		m_attachedSurface = NULL;
	}

	if (m_surface != NULL) {
		m_surface->Release();
		m_surface = NULL;
	}

	m_pixelFlags = 0;
	m_width = 0;
	m_height = 0;
	m_attachedSurface = NULL;
}
