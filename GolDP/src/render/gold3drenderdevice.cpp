#include "render/gold3drenderdevice.h"

#include "camera/golcamera.h"
#include "camera/golscenetransformnode.h"
#include "camera/goltransform.h"
#include "font/golfontbase.h"
#include "golerror.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golsurfaceformat.h"
#include "image/utopianpan0xa4.h"
#include "mesh/gdbmodelindexarray0xc.h"
#include "mesh/gdbvertexarray0xc.h"
#include "mesh/gdbvertexarraytypetwo0x20.h"
#include "mesh/golmodel.h"
#include "mesh/golmodelbase.h"
#include "render/gold3drendersurface.h"
#include "render/goldrawdpstate.h"
#include "render/rectangle.h"
#include "scene/golbillboard.h"
#include "surface/falcondunebag0x10.h"
#include "surface/golddune0x38.h"
#include "surface/purpledune0x7c.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolD3DRenderDevice, 0xc8770)
DECOMP_SIZE_ASSERT(GolD3DRenderDevice::TextureFormat, 0x18)
DECOMP_SIZE_ASSERT(GolD3DRenderDevice::Field0xc83b4, 0x10)
DECOMP_SIZE_ASSERT(GolD3DRenderDevice::VertexCacheEntry, 0x20)
DECOMP_SIZE_ASSERT(GolD3DRenderDevice::CommandVertex, 0x20)
DECOMP_SIZE_ASSERT(ColorRGBA, 0x4)
DECOMP_SIZE_ASSERT(D3DTLVERTEX, 0x20)
DECOMP_SIZE_ASSERT(Rect, 0x10)

inline static LegoS32 ClampModelColorChannel(LegoS32 p_value, LegoS32 p_minimum)
{
	if (p_value < p_minimum) {
		p_value = p_minimum;
	}
	if (p_value > 0xff) {
		p_value = 0xff;
	}

	return p_value;
}

inline static LegoU32 BuildModelClipFlags(const GolD3DRenderDevice::VertexCacheEntry& p_vertex)
{
	const LegoU32 x = *reinterpret_cast<const LegoU32*>(&p_vertex.m_x);
	const LegoU32 y = *reinterpret_cast<const LegoU32*>(&p_vertex.m_y);
	const LegoU32 z = *reinterpret_cast<const LegoU32*>(&p_vertex.m_z);
	const LegoU32 w = *reinterpret_cast<const LegoU32*>(&p_vertex.m_w);

	LegoU32 lowFlags = (x >> 31) | ((y & 0x80000000) >> 29) | ((z & 0x80000000) >> 27);
	LegoU32 highFlags =
		(((w - x) & 0x80000000) >> 30) | (((w - y) & 0x80000000) >> 28) | (((w - z) & 0x80000000) >> 26);
	return lowFlags | (highFlags & ~(lowFlags << 1));
}

// GLOBAL: GOLDP 0x10056540
const D3DCMPFUNC g_d3dCmpFuncLookup[] = {
	D3DCMP_ALWAYS,
	D3DCMP_EQUAL,
	D3DCMP_GREATER,
	D3DCMP_GREATEREQUAL,
	D3DCMP_LESS,
	D3DCMP_LESSEQUAL,
	D3DCMP_NEVER,
	D3DCMP_NOTEQUAL,
};

// GLOBAL: GOLDP 0x10056560
LegoU32 g_d3dBlendOpMasks[11] = {
	D3DPBLENDCAPS_ZERO,
	D3DPBLENDCAPS_ONE,
	D3DPBLENDCAPS_SRCCOLOR,
	D3DPBLENDCAPS_DESTCOLOR,
	D3DPBLENDCAPS_INVSRCCOLOR,
	D3DPBLENDCAPS_INVDESTCOLOR,
	D3DPBLENDCAPS_SRCALPHA,
	D3DPBLENDCAPS_DESTALPHA,
	D3DPBLENDCAPS_INVSRCALPHA,
	D3DPBLENDCAPS_INVDESTALPHA,
	D3DPBLENDCAPS_SRCALPHASAT,
};

// GLOBAL: GOLDP 0x1005658c
D3DBLEND g_d3dBlendOps[11] = {
	D3DBLEND_ZERO,
	D3DBLEND_ONE,
	D3DBLEND_SRCCOLOR,
	D3DBLEND_DESTCOLOR,
	D3DBLEND_INVSRCCOLOR,
	D3DBLEND_INVDESTCOLOR,
	D3DBLEND_SRCALPHA,
	D3DBLEND_DESTALPHA,
	D3DBLEND_INVSRCALPHA,
	D3DBLEND_INVDESTALPHA,
	D3DBLEND_SRCALPHASAT,
};

// GLOBAL: GOLDP 0x1005c8a8
BronzeFalconDrawFunction GolD3DRenderDevice::g_unk0x1005c8a8[8] = {
	&GolD3DRenderDevice::FUN_10011e60,
	&GolD3DRenderDevice::FUN_10011ed0,
	&GolD3DRenderDevice::FUN_10012030,
	&GolD3DRenderDevice::FUN_100121e0,
	&GolD3DRenderDevice::FUN_100123e0,
	&GolD3DRenderDevice::FUN_10012640,
	&GolD3DRenderDevice::FUN_100128f0,
	&GolD3DRenderDevice::FUN_10012bf0,
};

// GLOBAL: GOLDP 0x1005c8c8
BronzeFalconDrawFunction GolD3DRenderDevice::g_unk0x1005c8c8[64] = {
	&GolD3DRenderDevice::FUN_1000c160, &GolD3DRenderDevice::FUN_1000c2d0, &GolD3DRenderDevice::FUN_1000bfb0,
	&GolD3DRenderDevice::FUN_1000c470, &GolD3DRenderDevice::FUN_1000be20, &GolD3DRenderDevice::FUN_1000c2d0,
	&GolD3DRenderDevice::FUN_1000bfb0, &GolD3DRenderDevice::FUN_1000c470, &GolD3DRenderDevice::FUN_1000caf0,
	&GolD3DRenderDevice::FUN_1000cd20, &GolD3DRenderDevice::FUN_1000c880, &GolD3DRenderDevice::FUN_1000cf90,
	&GolD3DRenderDevice::FUN_1000c630, &GolD3DRenderDevice::FUN_1000cd20, &GolD3DRenderDevice::FUN_1000c880,
	&GolD3DRenderDevice::FUN_1000cf90, &GolD3DRenderDevice::FUN_1000baa0, &GolD3DRenderDevice::FUN_1000bc40,
	&GolD3DRenderDevice::FUN_1000bfb0, &GolD3DRenderDevice::FUN_1000c470, &GolD3DRenderDevice::FUN_1000b8e0,
	&GolD3DRenderDevice::FUN_1000c2d0, &GolD3DRenderDevice::FUN_1000bfb0, &GolD3DRenderDevice::FUN_1000c470,
	&GolD3DRenderDevice::FUN_1000caf0, &GolD3DRenderDevice::FUN_1000cd20, &GolD3DRenderDevice::FUN_1000c880,
	&GolD3DRenderDevice::FUN_1000cf90, &GolD3DRenderDevice::FUN_1000c630, &GolD3DRenderDevice::FUN_1000cd20,
	&GolD3DRenderDevice::FUN_1000c880, &GolD3DRenderDevice::FUN_1000cf90, &GolD3DRenderDevice::FUN_1000e010,
	&GolD3DRenderDevice::FUN_1000e010, &GolD3DRenderDevice::FUN_1000e010, &GolD3DRenderDevice::FUN_1000e010,
	&GolD3DRenderDevice::FUN_1000e180, &GolD3DRenderDevice::FUN_1000e180, &GolD3DRenderDevice::FUN_1000e790,
	&GolD3DRenderDevice::FUN_1000e790, &GolD3DRenderDevice::FUN_1000e310, &GolD3DRenderDevice::FUN_1000e310,
	&GolD3DRenderDevice::FUN_1000e930, &GolD3DRenderDevice::FUN_1000e930, &GolD3DRenderDevice::FUN_1000e540,
	&GolD3DRenderDevice::FUN_1000e540, &GolD3DRenderDevice::FUN_1000e930, &GolD3DRenderDevice::FUN_1000e930,
	&GolD3DRenderDevice::FUN_1000e010, &GolD3DRenderDevice::FUN_1000e010, &GolD3DRenderDevice::FUN_1000e790,
	&GolD3DRenderDevice::FUN_1000e790, &GolD3DRenderDevice::FUN_1000e180, &GolD3DRenderDevice::FUN_1000e180,
	&GolD3DRenderDevice::FUN_1000e790, &GolD3DRenderDevice::FUN_1000e790, &GolD3DRenderDevice::FUN_1000e310,
	&GolD3DRenderDevice::FUN_1000e310, &GolD3DRenderDevice::FUN_1000e930, &GolD3DRenderDevice::FUN_1000e930,
	&GolD3DRenderDevice::FUN_1000e540, &GolD3DRenderDevice::FUN_1000e540, &GolD3DRenderDevice::FUN_1000e930,
	&GolD3DRenderDevice::FUN_1000e930,
};

// FUNCTION: GOLDP 0x100078e0
GolD3DRenderDevice::GolD3DRenderDevice()
{
	Reset();
}

// FUNCTION: GOLDP 0x10007980
GolD3DRenderDevice::~GolD3DRenderDevice()
{
	VTable0x18();
}

// FUNCTION: GOLDP 0x10007a00
void GolD3DRenderDevice::Reset()
{
	LegoU32 i;

	m_drawState = NULL;
	m_d3dDevice = NULL;
	::memset(&m_d3dDeviceDesc, 0, sizeof(m_d3dDeviceDesc));
	m_d3dDeviceDesc.dwSize = sizeof(m_d3dDeviceDesc);
	m_d3dViewport = NULL;

	::memset(&m_viewportParams, 0, sizeof(m_viewportParams));
	m_viewportParams.dwSize = sizeof(m_viewportParams);
	m_viewportParams.dwX = 0;
	m_viewportParams.dwY = 0;
	m_viewportParams.dwWidth = 640;
	m_viewportParams.dwHeight = 480;
	m_viewportParams.dvClipX = -1.0f;
	m_viewportParams.dvClipY = -0.75f;
	m_viewportParams.dvClipWidth = 2.0f;
	m_viewportParams.dvClipHeight = 1.5f;
	m_viewportParams.dvMinZ = 0.0f;
	m_viewportParams.dvMaxZ = 1.0f;

	::memset(&m_materialParams, 0, sizeof(m_materialParams));
	m_materialParams.dwSize = sizeof(m_materialParams);
	m_materialParams.dwRampSize = 1;
	m_backgroundMaterial = NULL;
	m_backgroundMaterialHandle = 0;
	m_clearColor.m_alp = 0;
	m_clearColor.m_red = 0;
	m_clearColor.m_grn = 0;
	m_clearColor.m_blu = 0;
	m_clearPixelValue = 0;
	m_unk0x304 = NULL;
	m_renderTargetInfo = NULL;
	m_unk0x30c = NULL;

	::memset(m_unk0x348, 0, 0xcc8 - 0x348);
	::memset(m_unk0xc38ec, 0, sizeof(m_unk0xc38ec));
	::memset(m_unk0xc428c, 0, sizeof(m_unk0xc428c));
	m_unk0xc86f0 = NULL;
	m_unk0xc86f4 = 0;
	m_unk0xc86f8 = 0;
	m_unk0xc83ac = 0;
	m_unk0xc83b0 = 0;
	m_unk0xc852c = 1.0f;
	::memset(&m_unk0xc83b4, 0, sizeof(m_unk0xc83b4));
	m_unk0xc83c4 = 0;
	m_unk0xc86fc = 0.0f;
	m_unk0xc3848 = 0;
	m_unk0xc384c = 0;
	m_unk0xc4c0c = 0;
	m_unk0xc4c10 = 0;
	m_unk0xc4c14 = 0;
	m_unk0xc4c18 = 0;
	m_unk0xc83e4 = 0;
	m_unk0xc83e8 = 0;
	m_unk0xc83f0 = 0;
	m_unk0xc83ec = 0;
	m_unk0xc876c = &GolD3DRenderDevice::FUN_1000a2c0;
	m_unk0xc83f4 = 0;
	m_unk0xc83a0 = 0;
	m_unk0xc83a4 = 0;
	m_currentTexture = 0;
	m_unk0xc83c8 = 0;
	m_unk0xc83cc = 0;
	m_alpha = 255;
	m_unk0xc8568 = 0;
	m_unk0xc83f8 = 0;
	m_unk0xc83fc = -1;
	::memset(m_unk0xc8400, 0, sizeof(m_unk0xc8400));
	m_unk0xc8490 = 0;
	m_unk0xc8494 = 0;
	m_unk0xc8518 = 0;
	m_unk0xc851c = 0;
	m_unk0xc8520 = 0;
	m_unk0xc8524 = 0;
	m_unk0xc8528 = 0;
	::memset(&m_unk0xc8530, 0, 0xc854c - 0xc8530);
	::memset(&m_unk0xc854c, 0, 0xc8568 - 0xc854c);
	m_unk0xc8530 = this;
	m_unk0xc853c = m_unk0xc428c;
	m_unk0xc8538 = NULL;
	m_unk0xc854c.m_unk0x00 = this;
	m_unk0xc854c.m_unk0x0c = m_unk0xc428c;
	m_unk0xc8410.m_m[0][0] = 1.0f;
	m_unk0xc8450.m_m[0][0] = 1.0f;
	m_unk0xc8410.m_m[0][1] = 0.0f;
	m_unk0xc8450.m_m[0][1] = 0.0f;
	m_unk0xc8410.m_m[0][2] = 0.0f;
	m_unk0xc8450.m_m[0][2] = 0.0f;
	m_unk0xc8410.m_m[0][3] = 0.0f;
	m_unk0xc8450.m_m[0][3] = 0.0f;
	m_unk0xc8410.m_m[1][0] = 0.0f;
	m_unk0xc8450.m_m[1][0] = 0.0f;
	m_unk0xc8410.m_m[1][1] = 1.0f;
	m_unk0xc8450.m_m[1][1] = 1.0f;
	m_unk0xc8410.m_m[1][2] = 0.0f;
	m_unk0xc8450.m_m[1][2] = 0.0f;
	m_unk0xc8410.m_m[1][3] = 0.0f;
	m_unk0xc8450.m_m[1][3] = 0.0f;
	m_unk0xc8410.m_m[2][0] = 0.0f;
	m_unk0xc8450.m_m[2][0] = 0.0f;
	m_unk0xc8410.m_m[2][1] = 0.0f;
	m_unk0xc8450.m_m[2][1] = 0.0f;
	m_unk0xc8410.m_m[2][2] = 1.0f;
	m_unk0xc8450.m_m[2][2] = 1.0f;
	m_unk0xc8410.m_m[2][3] = 0.0f;
	m_unk0xc8450.m_m[2][3] = 0.0f;
	m_unk0xc8410.m_m[3][0] = 0.0f;
	m_unk0xc8450.m_m[3][0] = 0.0f;
	m_unk0xc8410.m_m[3][1] = 0.0f;
	m_unk0xc8450.m_m[3][1] = 0.0f;
	m_unk0xc8410.m_m[3][2] = 0.0f;
	m_unk0xc8450.m_m[3][2] = 0.0f;
	m_unk0xc8410.m_m[3][3] = 1.0f;
	m_unk0xc8450.m_m[3][3] = 1.0f;
	m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000c630;
	m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000edf0;

	for (i = 0; i < (0xcc8 - 0x348) / sizeof(*m_unk0x348); i++) {
		m_unk0x348[i].color = 0xffffffff;
		m_unk0x348[i].specular = 0xffffffff;
	}

	for (i = 0; i < sizeOfArray(m_unk0xc53a0); i++) {
		m_unk0xc53a0[i].color = 0xffffffff;
		m_unk0xc53a0[i].specular = 0xffffffff;
	}

	m_unk0xc8704 = 0;
}

// FUNCTION: GOLDP 0x10007d80
GolCommonDrawState* GolD3DRenderDevice::GetDrawState()
{
	return m_drawState;
}

// FUNCTION: GOLDP 0x10007d90
LegoS32 GolD3DRenderDevice::FUN_10007d90(GolDrawDPState* p_drawState, SlatePeak0x58* p_parg2, LegoU32 p_flags)
{
	if (m_flags & c_flagBit0) {
		VTable0x18();
	}

	m_drawState = p_drawState;
	m_unk0x304 = p_parg2;
	m_renderTargetInfo = p_parg2;
	m_unk0x0c = NULL;
	p_drawState->AddRenderer(this);
	m_flags |= c_flagBit0 | c_flagBit5;
	m_viewportParams.dwX = 0;
	m_viewportParams.dwY = 0;
	m_viewportParams.dwWidth = m_renderTargetInfo->m_width;
	m_viewportParams.dwHeight = m_renderTargetInfo->m_height;

	LegoS32 result = FUN_10007e20(p_flags);
	if (result != 0) {
		return result;
	}

	VTable0x28();
	return 0;
}

// FUNCTION: GOLDP 0x10007e20
LegoS32 GolD3DRenderDevice::FUN_10007e20(LegoU32 p_flags)
{
	GolSurfaceFormat swTextureFormat;
	LegoU32 forceSoftware;
	LegoChar errorMessage[64];
	D3DDEVICEDESC helCaps;

	m_flags = c_flagBit0 | c_flagBit5;
	if (p_flags & GolDrawState::c_flagBit21) {
		m_flags |= c_flagBit20;
	}
	if (p_flags & GolDrawState::c_flagBit12) {
		m_flags |= c_flagBit1;
	}

	forceSoftware = p_flags & GolDrawState::c_flagBit16;
	if (!forceSoftware) {
		m_unk0xc384c = 0;
		m_unk0xc83c4 = 0;
		m_unk0xc876c = &GolD3DRenderDevice::FUN_1000a2c0;

		if (m_flags & c_flagBit1 && !m_drawState->SupportsZBufferlessHsr()) {
			LegoS32 r = m_depthBuffer.Create(m_drawState, m_unk0x304);
			if (r != 0) {
				return r;
			}
		}

		HRESULT hresult =
			m_drawState->m_d3d3
				->CreateDevice(m_drawState->m_deviceGuid, m_unk0x304->m_renderSurface, &m_d3dDevice, NULL);
		if (hresult != D3D_OK) {
			sprintf(errorMessage, "Unable to create Direct3D device\nerror %x", hresult);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		m_countTextureFormats = 0;
		m_d3dDevice->EnumTextureFormats(CountTextureFormatsCallback, &m_countTextureFormats);
		if (m_countTextureFormats != 0) {
			LegoU32 i;

			::memset(&helCaps, 0, sizeof(helCaps));
			helCaps.dwSize = sizeof(helCaps);
			if (m_d3dDevice->GetCaps(&m_d3dDeviceDesc, &helCaps) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to query device capabilities");
			}

			if (!(m_d3dDeviceDesc.dwFlags & D3DDD_TRICAPS)) {
				::memcpy(&m_d3dDeviceDesc, &helCaps, sizeof(helCaps));
			}

			for (i = 0; i < sizeOfArray(m_unk0xc8708); i++) {
				if (m_d3dDeviceDesc.dpcTriCaps.dwSrcBlendCaps & g_d3dBlendOpMasks[i]) {
					m_unk0xc8708[i] = g_d3dBlendOps[i];
				}
				else {
					m_unk0xc8708[i] = D3DBLEND_SRCALPHA;
				}
			}

			for (i = 0; i < sizeOfArray(m_unk0xc8708); i++) {
				if (m_d3dDeviceDesc.dpcTriCaps.dwDestBlendCaps & g_d3dBlendOpMasks[i]) {
					m_unk0xc8734[i] = g_d3dBlendOps[i];
				}
				else {
					m_unk0xc8734[i] = D3DBLEND_INVSRCALPHA;
				}
			}

			if ((m_flags & c_flagBit20) && (m_d3dDeviceDesc.dpcTriCaps.dwAlphaCmpCaps & D3DPCMPCAPS_GREATER)) {
				m_flags &= ~c_flagBit7;
				m_flags |= c_flagBit8;
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_TRANSPARENCY) {
				m_flags &= ~(c_flagBit7 | c_flagBit8);
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwAlphaCmpCaps & D3DPCMPCAPS_GREATER) {
				m_flags &= ~c_flagBit7;
				m_flags |= c_flagBit8;
			}
			else {
				m_flags &= ~c_flagBit8;
				m_flags |= c_flagBit7;
			}

			if (m_d3dDeviceDesc.dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATBLEND) {
				m_flags &= ~c_flagBit12;
				m_flags |= c_flagBit11;
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATSTIPPLED) {
				m_flags |= c_flagBit11 | c_flagBit12;
			}
			else {
				m_flags &= ~c_flagBit12;
			}

			if (m_drawState->m_d3d3->CreateViewport(&m_d3dViewport, NULL) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to create viewport");
			}

			if (m_d3dDevice->AddViewport(m_d3dViewport) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to add viewport");
			}

			if (m_d3dViewport->SetViewport2(&m_viewportParams) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to configure viewport");
			}

			if (m_d3dDevice->SetCurrentViewport(m_d3dViewport) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to set viewport");
			}

			if (m_drawState->m_d3d3->CreateMaterial(&m_backgroundMaterial, NULL) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to create background material");
			}

			m_textureFormats = new GolSurfaceFormat[m_countTextureFormats];
			if (m_textureFormats == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_unk0x2c = 0;
			m_d3dDevice->EnumTextureFormats(EnumerateTextureFormatsCallback, this);
			m_unk0xc8700 = 2;
			goto rendererCreated;
		}

		m_d3dDevice->Release();
		m_d3dDevice = NULL;
	}

	m_flags &= ~c_flagBit1;
	m_flags |= c_flagBit9 | c_flagBit16;
	m_unk0xc384c = -1;
	m_unk0xc83c4 = 1;
	m_unk0xc876c = &GolD3DRenderDevice::FUN_1000a950;
	::memcpy(&swTextureFormat, &m_unk0x304->m_textureFormat, sizeof(swTextureFormat));

	GolSoftwareRenderer::PixelFormat swPixelFormat;
	if (swTextureFormat.m_bitsPerPixel == 8) {
		swPixelFormat = GolSoftwareRenderer::PixelFormat::e_formatIndex8;
		if (m_drawState->m_flags & GolDrawState::c_flagBit18) {
			m_unk0xc8700 = 1;
		}
		else {
			m_unk0xc8700 = 0;
		}
	}
	else {
		swPixelFormat = swTextureFormat.GetGreenBitCount() == 6 ? GolSoftwareRenderer::PixelFormat::e_format565
																: GolSoftwareRenderer::PixelFormat::e_format555;
		m_unk0xc8700 = 2;
	}

	FalconDuneBag0x10::SetTextureFormat(swTextureFormat);
	if (!m_softwareRenderer.Initialize(swPixelFormat, 16000)) {
		GOL_FATALERROR_MESSAGE("Unable to initialize software renderer");
	}

	m_softwareRenderer.SetUnk0x4c(m_unk0x348);
	FUN_1000b4a0();
	::memset(&m_unk0xc83b4, 0, sizeof(m_unk0xc83b4));

rendererCreated:
	VTable0x1c(m_clearColor);
	FUN_100082e0();
	if (m_unk0x0c != NULL) {
		VTable0x20(m_unk0x0c);
	}

	m_unk0x2d4.FUN_10006320(*this);
	for (GolD3DRenderSurface* surface = m_unk0x30c; surface != NULL; surface = surface->m_next) {
		surface->FUN_100136a0(this);
	}

	GolRenderDevice::RestoreResources();
	return 0;
}

// FUNCTION: GOLDP 0x100082e0
void GolD3DRenderDevice::FUN_100082e0()
{
	m_unk0xc83f0 = FALSE;
	m_unk0xc83ec = 0;
	m_unk0xc83e8 = FALSE;
	if (m_flags & c_flagBit19) {
		m_unk0xc83fc = ARGBU32(m_alpha, m_unk0x118.m_red, m_unk0x118.m_grn, m_unk0x118.m_blu);
	}
	else {
		m_unk0xc83f8 = FALSE;
	}

	m_unk0xc83d0 = 0;
	m_unk0xc83d4 = 0;
	m_unk0xc83d8 = 6;
	m_unk0xc83dc = 8;
	m_unk0xc83c8 = DuskwindBananaRelic0x24::c_flag0x08Bit2 | DuskwindBananaRelic0x24::c_flag0x08Bit4 |
				   DuskwindBananaRelic0x24::c_flag0x08Bit7 | DuskwindBananaRelic0x24::c_flag0x08Bit9 |
				   DuskwindBananaRelic0x24::c_flag0x08Bit10 | DuskwindBananaRelic0x24::c_flag0x08Bit13 |
				   DuskwindBananaRelic0x24::c_flag0x08Bit15 | DuskwindBananaRelic0x24::c_flag0x08Bit20 |
				   DuskwindBananaRelic0x24::c_flag0x08Bit22;
	FUN_10012f50();

	if (m_flags & c_flagBit16) {
		return;
	}

	m_d3dDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_TEXTUREPERSPECTIVE,
		m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE
	);

	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_SUBPIXEL,
		(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_SUBPIXEL) && m_drawState->IsHwAccelerated()
	);

	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_DITHERENABLE,
		(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_DITHER) && m_drawState->IsHwAccelerated()
	);

	m_d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP);
	if ((m_drawState->m_flags & GolDrawState::c_flagBit3) && m_drawState->IsHwAccelerated()) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS, D3DANTIALIAS_SORTINDEPENDENT);
	}
	else {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS, D3DANTIALIAS_NONE);
	}

	if ((m_d3dDeviceDesc.dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_LINEAR) && m_drawState->IsHwAccelerated()) {
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
	}
	else {
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
	}

	if (m_flags & c_flagBit1) {
		if (m_drawState->VTable0x94()) {
			m_flags |= c_flagBit13;
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_USEW);
		}
		else {
			m_flags &= ~c_flagBit13;
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		}

		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
		m_flags |= c_flagBit5;
	}
	else {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	}

	m_d3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, FALSE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
	m_d3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, g_d3dCmpFuncLookup[0]);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, m_unk0xc8708[m_unk0xc83d8]);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, m_unk0xc8734[m_unk0xc83dc]);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

// FUNCTION: GOLDP 0x10008680
void GolD3DRenderDevice::ReleaseResources()
{
	GolRenderDevice::ReleaseResources();

	for (GolD3DRenderSurface* surface = m_unk0x30c; surface != NULL; surface = surface->m_next) {
		surface->ReleaseResources();
	}

	m_unk0x2d4.Destroy();

	if (m_flags & c_flagBit16) {
		m_softwareRenderer.~GolSoftwareRenderer();
	}

	if (m_depthBuffer.GetPixelFlags() & SilverDune0x30::c_lockRequestRead) {
		m_depthBuffer.Release();
	}

	if (m_d3dViewport != NULL) {
		m_d3dViewport->Release();
		m_d3dViewport = NULL;
	}

	if (m_d3dDevice != NULL) {
		if (m_backgroundMaterial != NULL) {
			m_backgroundMaterial->Release();
			m_backgroundMaterial = NULL;
			m_backgroundMaterialHandle = 0;
		}

		m_d3dDevice->Release();
		m_d3dDevice = NULL;
	}

	::memset(&m_d3dDeviceDesc, 0, sizeof(m_d3dDeviceDesc));
	m_d3dDeviceDesc.dwSize = sizeof(m_d3dDeviceDesc);
}

// FUNCTION: GOLDP 0x10008740
void GolD3DRenderDevice::VTable0x18()
{
	if (m_unk0x0c != NULL) {
		m_unk0x0c->FUN_10001f60(NULL);
		m_unk0x0c = NULL;
	}

	GolRenderDevice::Destroy();
	ReleaseResources();

	GolD3DRenderSurface* surface = m_unk0x30c;
	while (surface != NULL) {
		GolD3DRenderSurface* next = surface->m_next;
		surface->VTable0x34();
		delete surface;
		surface = next;
	}

	if (m_drawState != NULL) {
		m_drawState->RemoveRenderer(this);
	}

	Reset();
	m_flags = 0;
}

// FUNCTION: GOLDP 0x100087b0
void GolD3DRenderDevice::VTable0x20(GolCamera* p_lens)
{
	if (m_unk0x0c != NULL) {
		m_unk0x0c->FUN_10001f60(NULL);
	}

	m_unk0x0c = p_lens;
	p_lens->FUN_10001f60(this);
}

// FUNCTION: GOLDP 0x100087e0
void GolD3DRenderDevice::VTable0x5c()
{
	GolCamera* lens = m_unk0x0c;
	lens->VTable0x28();
	lens->FUN_10002860(&m_viewportParams);

	if (!(m_flags & c_flagBit16) && m_d3dViewport->SetViewport2(&m_viewportParams) != D3D_OK) {
		GOL_FATALERROR_MESSAGE("Unable to set viewport");
	}

	m_unk0xc8490 = &lens->m_unk0x120.m_unk0x190;
	m_unk0xc8494 = &lens->m_unk0x120.m_unk0x1d0;
	::memcpy(&m_unk0x4c, &lens->m_viewFrustum, sizeof(m_unk0x4c));
	::memcpy(m_unk0xc8400, &lens->m_unk0x120.m_unk0x210, sizeof(m_unk0xc8400));
}

// FUNCTION: GOLDP 0x10008880
void GolD3DRenderDevice::FUN_10008880(GolWorldEntity* p_model, LegoU32 p_lodIndex)
{
	GolModelEntity* canoe = static_cast<GolModelEntity*>(p_model);
	m_unk0xc8520 = canoe->VTable0x58(p_lodIndex);
	if (m_unk0xc8520 != NULL) {
		canoe->VTable0x5c(p_lodIndex);
		if (m_unk0xc83e4) {
			static_cast<GolSceneTransformNode*>(m_unk0xc8520)
				->FUN_10014a60(m_unk0xc8498[0], m_unk0xc8410, *m_unk0xc8490);
		}
		else {
			static_cast<GolSceneTransformNode*>(m_unk0xc8520)->FUN_10014a60(m_unk0xc84d8, m_unk0xc8410, *m_unk0xc8494);
		}

		if (m_unk0xc8568) {
			m_unk0xc8520->VTable0x20(m_unk0xc8450);
		}
	}
}

// FUNCTION: GOLDP 0x10008910
void GolD3DRenderDevice::VTable0x94(GolWorldEntity* p_model)
{
	GolWorldEntity::ResultStruct result;
	p_model->VTable0x14(m_unk0x4c, &result);
	if (!result.m_visibility) {
		return;
	}

	GolMatrix4* modelMatrix = &m_unk0xc8410;
	GolModelEntity* canoe = static_cast<GolModelEntity*>(p_model);
	canoe->FUN_10027e70(modelMatrix, result.m_lodIndex);

	const GolVec3& position = canoe->GetPosition();
	modelMatrix->m_m[3][0] = position.m_x;
	modelMatrix->m_m[3][1] = position.m_y;
	modelMatrix->m_m[3][2] = position.m_z;

	if (result.m_visibility == 1) {
		m_unk0xc83e4 = TRUE;
		m_unk0xc8518 = m_unk0xc8498;
		FUN_10012f50();
		GolMath::FUN_1002f3a0(*modelMatrix, *m_unk0xc8490, m_unk0xc8498);
	}
	else {
		m_unk0xc83e4 = FALSE;
		m_unk0xc8518 = &m_unk0xc84d8;
		FUN_10012f50();
		GolMath::FUN_1002f3a0(*modelMatrix, *m_unk0xc8494, &m_unk0xc84d8);
	}

	GolModel* model = static_cast<GolModel*>(canoe->GetModel(result.m_lodIndex));
	GdbVertexArray0xc* vertexArray = model->GetVertexArray();
	LegoU16 vertexType = vertexArray->GetVertexType();
	if (m_unk0xc8568 != (vertexType == 2 || vertexType == 3)) {
		m_unk0xc8568 = (vertexType == 2 || vertexType == 3);
		FUN_10012f50();
	}

	if (m_unk0xc8568) {
		FUN_1000add0(p_model, model);
	}

	MaterialTable0x0c* materialTable = canoe->GetMaterialTable(result.m_lodIndex);
	FUN_10008880(p_model, result.m_lodIndex);
	model->FUN_10006c50(this, materialTable);
}

// STUB: GOLDP 0x10008a50
void GolD3DRenderDevice::VTable0xac(undefined4, undefined4)
{
	STUB(0x10008a50);
}

// STUB: GOLDP 0x10008c30
void GolD3DRenderDevice::VTable0xb0(undefined4, undefined4)
{
	STUB(0x10008c30);
}

// STUB: GOLDP 0x10008dd0
void GolD3DRenderDevice::VTable0x8c(GolModelEntity*, AmethystBreeze0x104*, undefined4)
{
	STUB(0x10008dd0);
}

// STUB: GOLDP 0x10008f70
void GolD3DRenderDevice::VTable0xa8(GolWorldEntity* p_model, LegoFloat, LegoFloat)
{
	STUB(0x10008f70);
	VTable0x94(p_model);
}

// STUB: GOLDP 0x100090b0
void GolD3DRenderDevice::VTable0x88(GolModelEntity*, AmethystBreeze0x104*, undefined4)
{
	STUB(0x100090b0);
}

// FUNCTION: GOLDP 0x10009240
void GolD3DRenderDevice::VTable0x9c(GolModelEntity* p_arg1, AmethystBreeze0x104* p_arg2, undefined4 p_arg3)
{
	m_unk0xc8528 = TRUE;
	VTable0x8c(p_arg1, p_arg2, p_arg3);
}

// FUNCTION: GOLDP 0x10009270
void GolD3DRenderDevice::VTable0x98(GolModelEntity* p_arg1, AmethystBreeze0x104* p_arg2, undefined4 p_arg3)
{
	m_unk0xc8528 = TRUE;
	VTable0x88(p_arg1, p_arg2, p_arg3);
}

// STUB: GOLDP 0x100092a0
void GolD3DRenderDevice::VTable0x90(GolWorldEntity*)
{
	STUB(0x100092a0);
}

// FUNCTION: GOLDP 0x10009420
void GolD3DRenderDevice::VTable0x54(undefined4 p_flags)
{
	VTable0x5c();
	VTable0x60();

	m_unk0xc3848 = 0;

	if (m_renderTargetInfo->m_pixelFlags & SilverDune0x30::c_lockFlagUnknown0x04) {
		m_renderTargetInfo->VTable0x18();
	}

	if (p_flags & 0x05) {
		if (m_unk0xc83c4 == 0) {
			D3DRECT rect;
			rect.x1 = 0;
			rect.y1 = 0;

			rect.x2 = m_renderTargetInfo->m_width;
			rect.y2 = m_renderTargetInfo->m_height;

			LegoU32 clearFlags = ((~p_flags & 0xff) >> 2) & 1;
			if (m_flags & c_flagBit1) {
				clearFlags |= 2;
			}

			m_d3dViewport->Clear(1, &rect, clearFlags);
		}
		else if (p_flags & 0x01) {
			m_renderTargetInfo->Fill(m_clearPixelValue);
		}
	}

	if (m_unk0xc83c4 == 0) {
		HRESULT result = m_d3dDevice->BeginScene();
		if (result) {
			GOL_FATALERROR_MESSAGE("Unable to begin scene");
		}
	}
	else {
		m_unk0xc86f4 = 0;
		m_softwareRenderer.SetDimensions(m_renderTargetInfo->m_width, m_renderTargetInfo->m_height);
		m_unk0xc86f0 = m_softwareRenderer.GetCommands();
		m_unk0xc86f8 = m_softwareRenderer.GetNodeCapacity();
	}
}

// FUNCTION: GOLDP 0x10009540
void GolD3DRenderDevice::VTable0xf0()
{
	if (m_unk0xc83c4 == 0) {
		HRESULT result = m_d3dDevice->EndScene();
		if (result && result != DDERR_SURFACELOST) {
			GOL_FATALERROR_MESSAGE("Unable to end scene");
		}
	}
	else {
		m_softwareRenderer.FUN_10041830(m_unk0xc86f4, TRUE);
		if (m_unk0xc86f4 != 0) {
			m_softwareRenderer.SetUnk0x50(m_unk0xc3848);

			LegoU8* pixels;
			LegoU32 pitch;
			m_renderTargetInfo
				->LockPixels(&pixels, &pitch, SilverDune0x30::c_lockRequestRead | SilverDune0x30::c_lockRequestWrite);
			if (pixels != NULL) {
				m_softwareRenderer.SetRenderTarget(pixels, pitch);
				m_softwareRenderer.FUN_10041a20(FALSE);
				m_renderTargetInfo->UnlockPixels();
			}
		}
	}

	if (m_renderTargetInfo != m_unk0x304) {
		SlatePeak0x58* renderTargetInfo = m_unk0x304;
		m_renderTargetInfo = renderTargetInfo;

		Rect rect;
		rect.m_left = 0;
		rect.m_top = 0;
		rect.m_right = renderTargetInfo->m_width;
		rect.m_bottom = renderTargetInfo->m_height;

		VTable0x20(m_unk0x0c);
		m_unk0x0c->VTable0x0c(&rect);
	}

	m_unk0xc8538 = NULL;
}

// FUNCTION: GOLDP 0x10009640
void GolD3DRenderDevice::VTable0x1c(const ColorRGBA& p_color)
{
	GolSurfaceFormat textureFormat;

	m_clearColor = p_color;
	if (m_flags & c_flagBit16) {
		textureFormat = m_renderTargetInfo->m_textureFormat;
		if (textureFormat.m_paletteMask != 0) {
			m_clearPixelValue = m_renderTargetInfo->GetPalette()->FindEntry(m_clearColor);
		}
		else {
			m_clearPixelValue = textureFormat.MapRGBA(m_clearColor);
		}
	}
	else {
		LegoFloat c = static_cast<LegoFloat>(static_cast<double>(p_color.m_red) / 255.0);
		m_materialParams.ambient.r = c;
		m_materialParams.diffuse.r = c;
		c = static_cast<LegoFloat>(static_cast<double>(p_color.m_grn) / 255.0);
		m_materialParams.ambient.g = c;
		m_materialParams.diffuse.g = c;
		c = static_cast<LegoFloat>(static_cast<double>(p_color.m_blu) / 255.0);
		m_materialParams.ambient.b = c;
		m_materialParams.diffuse.b = c;
		m_backgroundMaterial->SetMaterial(&m_materialParams);
		m_backgroundMaterial->GetHandle(m_d3dDevice, &m_backgroundMaterialHandle);
		m_d3dViewport->SetBackground(m_backgroundMaterialHandle);
	}
}

// FUNCTION: GOLDP 0x10009780
void GolD3DRenderDevice::VTable0xd8()
{
	if (!m_unk0xc83c4) {
		if (!m_drawState->IsHwAccelerated()) {
			m_d3dDevice->SetRenderState(
				D3DRENDERSTATE_TEXTUREPERSPECTIVE,
				(m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE) ? TRUE : FALSE
			);
		}
	}
}

// FUNCTION: GOLDP 0x100097c0
void GolD3DRenderDevice::VTable0xd4()
{
	if (!m_unk0xc83c4) {
		if (!m_drawState->IsHwAccelerated()) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, FALSE);
		}
	}
}

// FUNCTION: GOLDP 0x100097f0
void GolD3DRenderDevice::VTable0xdc()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(
			D3DRENDERSTATE_DITHERENABLE,
			(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_DITHER) && m_drawState->IsHwAccelerated() ? TRUE
																												: FALSE
		);
	}
}

// FUNCTION: GOLDP 0x10009840
void GolD3DRenderDevice::VTable0xe0()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, FALSE);
	}
}

// FUNCTION: GOLDP 0x10009860
void GolD3DRenderDevice::VTable0xe4()
{
	if (!m_unk0xc83c4 && (m_flags & c_flagBit1)) {
		if (m_drawState->VTable0x94()) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_USEW);
		}
		else {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		}

		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
	}

	m_flags |= c_flagBit5;
}

// FUNCTION: GOLDP 0x100098d0
void GolD3DRenderDevice::VTable0xe8(LegoBool32 p_arg)
{
	m_flags &= ~c_flagBit5;

	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	}
	else {
		if (p_arg == 0) {
			m_unk0xc86fc = 0.0f;
		}
		else {
			m_unk0xc86fc = 1.0f;
		}
	}
}

// FUNCTION: GOLDP 0x10009930
LPDIRECT3D3 GolD3DRenderDevice::GetDirect3D3() const
{
	return m_drawState->m_d3d3;
}

// FUNCTION: GOLDP 0x10009940
LPDIRECTDRAW4 GolD3DRenderDevice::GetDirectDraw4() const
{
	return m_drawState->m_ddraw4;
}

// FUNCTION: GOLDP 0x10009950
const SlatePeak0x58* GolD3DRenderDevice::GetRenderTargetInfo()
{
	return m_renderTargetInfo;
}

// FUNCTION: GOLDP 0x10009960
void GolD3DRenderDevice::VTable0x7c(
	UtopianPan0xa4* p_image,
	undefined4 p_unk0x08,
	Rect* p_destRect,
	Rect* p_sourceRect,
	Rect* p_clipRect
)
{
	p_image->FUN_10005510(this, p_unk0x08, p_destRect, p_sourceRect, p_clipRect);
}

// FUNCTION: GOLDP 0x10009990
void GolD3DRenderDevice::VTable0x78(UtopianPan0xa4* p_image, undefined4 p_unk0x08, Rect* p_destRect, Rect* p_clipRect)
{
	p_image->FUN_100054d0(this, p_unk0x08, p_destRect, p_clipRect);
}

// FUNCTION: GOLDP 0x100099b0
void GolD3DRenderDevice::VTable0x74(
	UtopianPan0xa4* p_image,
	undefined4 p_unk0x08,
	LegoS32 p_destLeft,
	LegoS32 p_destTop,
	LegoS32 p_destWidth,
	LegoS32 p_destHeight,
	LegoS32 p_sourceLeft,
	LegoS32 p_sourceTop,
	LegoS32 p_sourceWidth,
	LegoS32 p_sourceHeight
)
{
	Rect destRect;
	destRect.m_left = p_destLeft;
	destRect.m_top = p_destTop;
	destRect.m_right = p_destLeft + p_destWidth;
	destRect.m_bottom = p_destTop + p_destHeight;

	Rect sourceRect;
	sourceRect.m_left = p_sourceLeft;
	sourceRect.m_top = p_sourceTop;
	sourceRect.m_right = p_sourceLeft + p_sourceWidth;
	sourceRect.m_bottom = p_sourceTop + p_sourceHeight;

	p_image->FUN_10005510(this, p_unk0x08, &destRect, &sourceRect, 0);
}

// FUNCTION: GOLDP 0x10009a20
void GolD3DRenderDevice::VTable0x70(
	UtopianPan0xa4* p_image,
	undefined4 p_unk0x08,
	LegoS32 p_destLeft,
	LegoS32 p_destTop,
	LegoS32 p_destWidth,
	LegoS32 p_destHeight
)
{
	Rect destRect;
	destRect.m_left = p_destLeft;
	destRect.m_top = p_destTop;
	destRect.m_right = p_destLeft + p_destWidth;
	destRect.m_bottom = p_destTop + p_destHeight;

	p_image->FUN_100054d0(this, p_unk0x08, &destRect, 0);
}

// STUB: GOLDP 0x10009a70
void GolD3DRenderDevice::VTable0xb4(GolBillboard& p_param)
{
	LegoBool32 visibility[2];
	p_param.FUN_10029fa0(m_unk0x4c.m_position, visibility);
	if (visibility[0]) {
		GolVec3 forward;
		GolVec3 right;
		GolTransformBase* orbit = m_unk0x0c->m_transform;
		orbit->VTable0x1c(&right, &forward);

		forward.m_x = -forward.m_x;
		forward.m_y = -forward.m_y;
		forward.m_z = -forward.m_z;

		LegoBool32 builtMatrix = p_param.FUN_10014e50(&right, &forward, &m_unk0xc8410);
		if (builtMatrix) {
			GolMath::FUN_1002f3a0(m_unk0xc8410, *m_unk0xc8490, m_unk0xc8498);
			m_unk0xc8568 = 0;
			m_unk0xc83e4 = 1;
			m_unk0xc8518 = m_unk0xc8498;
			FUN_10012f50();
			p_param.FUN_10014ff0(this);
		}
	}
}

// FUNCTION: GOLDP 0x10009b40
void GolD3DRenderDevice::VTable0x68(
	const LegoChar* p_unk0x04,
	GolFontBase* p_font,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18,
	Rect* p_unk0x1c,
	undefined4 p_unk0x20
)
{
	p_font->DrawString(p_unk0x04, this, p_unk0x0c, p_unk0x10, p_unk0x14, p_unk0x18, p_unk0x1c, p_unk0x20);
}

// FUNCTION: GOLDP 0x10009b70
LegoS32 GolD3DRenderDevice::VTable0x64(
	GolString* p_unk0x04,
	GolFontBase* p_font,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18,
	Rect* p_unk0x1c,
	undefined4 p_unk0x20
)
{
	return p_font->DrawString(p_unk0x04, this, p_unk0x0c, p_unk0x10, p_unk0x14, p_unk0x18, p_unk0x1c, p_unk0x20);
}

// FUNCTION: GOLDP 0x10009ba0
LegoS32 GolD3DRenderDevice::VTable0x6c(
	GolString* p_unk0x04,
	GolFontBase* p_font,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18,
	Rect* p_unk0x1c,
	undefined4 p_unk0x20
)
{
	return p_font->DrawStringFitted(p_unk0x04, this, p_unk0x0c, p_unk0x10, p_unk0x14, p_unk0x18, p_unk0x1c, p_unk0x20);
}

// FUNCTION: GOLDP 0x10009bd0
void GolD3DRenderDevice::DrawRectangle(
	const Rect& p_rect,
	LegoFloat p_z,
	const ColorRGBA& p_color1,
	const ColorRGBA& p_color2,
	const ColorRGBA& p_color3,
	const ColorRGBA& p_color4,
	undefined4 p_arg7
)
{
	TexturedVertex topLeft;
	TexturedVertex bottomRight;
	TexturedVertex bottomLeft;
	TexturedVertex topRight;

	LegoFloat left = static_cast<LegoFloat>(p_rect.m_left);
	topLeft.m_z = p_z;
	topLeft.m_color = p_color1;
	topLeft.m_x = left;

	LegoFloat top = static_cast<LegoFloat>(p_rect.m_top);
	bottomLeft.m_z = p_z;
	topLeft.m_y = top;
	bottomLeft.m_color = p_color2;
	bottomLeft.m_x = left;

	LegoFloat bottom = static_cast<LegoFloat>(p_rect.m_bottom);
	bottomLeft.m_y = bottom;

	LegoFloat right = static_cast<LegoFloat>(p_rect.m_right);
	topRight.m_z = p_z;
	topRight.m_y = top;
	topRight.m_color = p_color3;
	topRight.m_x = right;

	bottomRight.m_x = right;
	bottomRight.m_color = p_color4;
	bottomRight.m_y = bottom;
	bottomRight.m_z = p_z;

	topLeft.m_u = 0.0f;
	topLeft.m_v = 0.0f;
	bottomLeft.m_u = 0.0f;
	bottomLeft.m_v = 0.0f;
	topRight.m_u = 0.0f;
	topRight.m_v = 0.0f;
	bottomRight.m_u = 0.0f;
	bottomRight.m_v = 0.0f;

	DrawTriangle(&bottomLeft, &topLeft, &bottomRight, NULL, p_arg7);
	DrawTriangle(&bottomRight, &topLeft, &topRight, NULL, p_arg7);
}

// FUNCTION: GOLDP 0x10009ce0
void GolD3DRenderDevice::DrawTriangle(
	const TexturedVertex* p_vertex0,
	const TexturedVertex* p_vertex1,
	const TexturedVertex* p_vertex2,
	DuskwindBananaRelic0x24* p_material,
	undefined4
)
{
	if (p_material == NULL) {
		p_material = &m_unk0x2d4;
	}

	(this->*m_unk0xc876c)(p_material);
	FUN_1000ac00(p_material->GetUnk0x04());

	const TexturedVertex* v0;
	const TexturedVertex* v1;
	const TexturedVertex* v2;
	if (p_material->GetUnk0x08() & DuskwindBananaRelic0x24::c_flagBit14) {
		v2 = p_vertex0;
		v0 = p_vertex1;
		v1 = p_vertex2;
	}
	else {
		v2 = p_vertex2;
		v1 = p_vertex1;
		v0 = p_vertex0;
	}

	LegoU32 vertexIndexMask = m_unk0xc384c;
	LegoU32 vertexIndex = m_unk0xc3848 & vertexIndexMask;
	vertexIndexMask = ~vertexIndexMask;
	vertexIndexMask &= 0x40;
	D3DTLVERTEX* vertices = &m_unk0x348[vertexIndexMask + vertexIndex];

	vertices[0].sx = v0->m_x;
	vertices[0].sy = v0->m_y;
	vertices[0].sz = v0->m_z;
	if (vertices[0].sz > 0.0f) {
		LegoFloat z = v0->m_z;
		vertices[0].rhw = 1.0f / z;
	}
	else {
		vertices[0].rhw = 1.0f;
	}
	vertices[0].tu = v0->m_u;
	vertices[0].tv = v0->m_v;
	vertices[0].specular = 0;

	vertices[1].sx = v1->m_x;
	vertices[1].sy = v1->m_y;
	vertices[1].sz = v1->m_z;
	if (vertices[1].sz > 0.0f) {
		LegoFloat z = v1->m_z;
		vertices[1].rhw = 1.0f / z;
	}
	else {
		vertices[1].rhw = 1.0f;
	}
	vertices[1].tu = v1->m_u;
	vertices[1].tv = v1->m_v;
	vertices[1].specular = 0;

	vertices[2].sx = v2->m_x;
	vertices[2].sy = v2->m_y;
	vertices[2].sz = v2->m_z;
	if (vertices[2].sz > 0.0f) {
		LegoFloat z = v2->m_z;
		vertices[2].rhw = 1.0f / z;
	}
	else {
		vertices[2].rhw = 1.0f;
	}
	vertices[2].tu = v2->m_u;
	vertices[2].tv = v2->m_v;
	vertices[2].specular = 0;

	switch (m_unk0xc8700) {
	case 1: {
		LegoU32 color = v0->m_color.m_grn;
		color &= 0xe0;
		color |= v0->m_color.m_blu >> 3;
		color >>= 3;
		color |= v0->m_color.m_red & 0xe0;
		vertices[0].color = color;

		color = v0->m_color.m_grn;
		color &= 0xe0;
		color |= v0->m_color.m_blu >> 3;
		color >>= 3;
		color |= v0->m_color.m_red & 0xe0;
		vertices[1].color = color;

		color = v0->m_color.m_grn;
		color &= 0xe0;
		color |= v0->m_color.m_blu >> 3;
		color >>= 3;
		color |= v0->m_color.m_red & 0xe0;
		vertices[2].color = color;
		break;
	}
	case 2:
		vertices[0].color =
			(v0->m_color.m_alp << 24) | (v0->m_color.m_red << 16) | (v0->m_color.m_grn << 8) | v0->m_color.m_blu;
		vertices[1].color =
			(v1->m_color.m_alp << 24) | (v1->m_color.m_red << 16) | (v1->m_color.m_grn << 8) | v1->m_color.m_blu;
		vertices[2].color =
			(v2->m_color.m_alp << 24) | (v2->m_color.m_red << 16) | (v2->m_color.m_grn << 8) | v2->m_color.m_blu;
		break;
	}

	if (m_unk0xc83c4) {
		LegoS32 commandIndex = m_unk0xc86f4;
		LegoS32 nextCommandIndex = commandIndex + 1;
		if (nextCommandIndex < m_unk0xc86f8) {
			GolSoftwareRenderer::Command0x14* cmd = m_unk0xc86f0 + commandIndex;
			m_unk0xc86f4 = nextCommandIndex;
			cmd->m_unk0x08 = m_unk0xc3848++;
			cmd->m_unk0x0a = m_unk0xc3848++;
			cmd->m_unk0x0c = m_unk0xc3848++;
			cmd->m_unk0x10 = m_unk0xc83b4.m_unk0x00[0];
			if (m_flags & c_flagBit5) {
				m_softwareRenderer.FUN_100417c0(cmd, 1);
			}
			else {
				m_softwareRenderer.FUN_100417a0(cmd, 1, m_unk0xc86fc);
			}
		}
	}
	else {
		m_d3dDevice->DrawPrimitive(
			D3DPT_TRIANGLELIST,
			D3DFVF_TLVERTEX,
			vertices,
			3,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// FUNCTION: GOLDP 0x10009fd0
void GolD3DRenderDevice::FUN_10009fd0(D3DTLVERTEX* p_vertices, LegoU32 p_count)
{
	if (m_unk0xc83c4) {
		D3DTLVERTEX* vertices = &m_unk0x348[m_unk0xc3848];

		LegoU32 copyCount = p_count;
		D3DTLVERTEX* dest = vertices;
		for (; copyCount > 0; copyCount--) {
			*dest = *p_vertices;
			dest++;
			p_vertices++;
		}

		LegoS32 triangleCount = p_count - 2;
		if (triangleCount >= 0) {
			LegoS32 commandIndex = m_unk0xc86f4;
			LegoS32 nextCommandIndex = commandIndex + triangleCount;
			if (nextCommandIndex < m_unk0xc86f8) {
				GolSoftwareRenderer::Command0x14* cmd = m_unk0xc86f0 + commandIndex;
				m_unk0xc86f4 = nextCommandIndex;

				LegoS32 winding = 1;
				GolSoftwareRenderer::Command0x14* command = cmd;
				for (LegoS32 i = 0; i < triangleCount;) {
					i++;
					command->m_unk0x08 = static_cast<undefined2>(m_unk0xc3848 + i + winding);
					command->m_unk0x0a = static_cast<undefined2>(m_unk0xc3848 + i);
					command->m_unk0x0c = static_cast<undefined2>(m_unk0xc3848 + i - winding);
					command->m_unk0x10 = m_unk0xc83b4.m_unk0x00[0];
					winding = -winding;
					command++;
				}

				m_unk0xc3848 += p_count;
				if (m_flags & c_flagBit5) {
					m_softwareRenderer.FUN_100417c0(cmd, triangleCount);
				}
				else {
					m_softwareRenderer.FUN_100417a0(cmd, triangleCount, m_unk0xc86fc);
				}
			}
		}
	}
	else {
		m_d3dDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,
			D3DFVF_TLVERTEX,
			p_vertices,
			p_count,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// FUNCTION: GOLDP 0x1000a110
void GolD3DRenderDevice::SelectTextureFormat(
	const GolSurfaceFormat& p_requestedTextureFormat,
	GolSurfaceFormat* p_actualTextureFormat,
	LegoBool32 p_arg3
)
{
	GolSurfaceFormat reqTextureFormat;
	if (p_arg3 && (m_flags & (c_flagBit7 | c_flagBit8)) && p_requestedTextureFormat.GetAlphaBitCount() == 0) {
		reqTextureFormat.m_redBitMask = 0xf800;
		reqTextureFormat.m_grnBitMask = 0x07c0;
		reqTextureFormat.m_bluBitMask = 0x003e;
		reqTextureFormat.m_alpBitMask = 0x0001;
		reqTextureFormat.m_unk0x10 = 0;
		reqTextureFormat.m_paletteMask = 0;
		reqTextureFormat.m_bitsPerPixel = 16;
		GolRenderDevice::SelectTextureFormat(reqTextureFormat, p_actualTextureFormat, TRUE);
	}
	else {
		GolRenderDevice::SelectTextureFormat(p_requestedTextureFormat, p_actualTextureFormat, FALSE);
	}
}

// FUNCTION: GOLDP 0x1000a1c0
LegoU32 GolD3DRenderDevice::GetMinimumTextureWidth(undefined4) const
{
	if (m_unk0xc83c4) {
		return 8;
	}
	if (m_d3dDeviceDesc.dwMinTextureWidth != 0) {
		return m_d3dDeviceDesc.dwMinTextureWidth;
	}
	return 32;
}

// FUNCTION: GOLDP 0x1000a1f0
LegoU32 GolD3DRenderDevice::GetMaximumTextureWidth(undefined4) const
{
	if (m_unk0xc83c4) {
		return 256;
	}
	if (m_d3dDeviceDesc.dwMaxTextureWidth != 0) {
		return m_d3dDeviceDesc.dwMaxTextureWidth;
	}
	return 256;
}

// FUNCTION: GOLDP 0x1000a210
LegoU32 GolD3DRenderDevice::GetMinimumTextureHeight(undefined4) const
{
	if (m_unk0xc83c4) {
		return 8;
	}
	if (m_d3dDeviceDesc.dwMinTextureHeight != 0) {
		return m_d3dDeviceDesc.dwMinTextureHeight;
	}
	return 32;
}

// FUNCTION: GOLDP 0x1000a240
LegoU32 GolD3DRenderDevice::GetMaximumTextureHeight(undefined4) const
{
	if (m_unk0xc83c4) {
		return 256;
	}
	if (m_d3dDeviceDesc.dwMaxTextureHeight != 0) {
		return m_d3dDeviceDesc.dwMaxTextureHeight;
	}
	return 256;
}

// FUNCTION: GOLDP 0x1000a260
LegoBool32 GolD3DRenderDevice::TexturesMustBeSquare() const
{
	if (m_unk0xc83c4) {
		return FALSE;
	}
	else {
		LegoU32 textureCaps = m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps;
		LegoU32 result = static_cast<LegoU8>(~textureCaps);
		result &= 0xff;
		return (result >> 5) & 1;
	}
}

// FUNCTION: GOLDP 0x1000a290
LegoBool32 GolD3DRenderDevice::TextureSizesMustBePowersOfTwo() const
{
	if (m_unk0xc83c4) {
		return TRUE;
	}
	else {
		LegoU32 textureCaps = m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps;
		LegoU32 result = textureCaps & 0xff;
		return (result >> 1) & 1;
	}
}

// FUNCTION: GOLDP 0x1000a2c0
void GolD3DRenderDevice::FUN_1000a2c0(DuskwindBananaRelic0x24* p_material)
{
	LegoU32 newFlags = p_material->GetUnk0x08();

	m_unk0xc8538 = p_material;
	if (m_unk0xc8568 != 0) {
		DuskwindBananaRelicColor c = p_material->GetColor0x10();
		m_unk0xc8570 = static_cast<LegoU32>(m_unk0xc856c.m_red * c.m_unk0x0) >> 8;
		m_unk0xc8574 = static_cast<LegoU32>(m_unk0xc856c.m_grn * c.m_unk0x1) >> 8;
		m_unk0xc8578 = static_cast<LegoU32>(m_unk0xc856c.m_blu * c.m_unk0x2) >> 8;
		m_unk0xc857c = c.m_unk0x3 & 0xff;
		c = p_material->GetColor0x0c();
		for (LegoU32 i = 0; i < m_unk0x11c; i++) {
			m_unk0xc859c[i].m_red =
				static_cast<LegoFloat>(m_unk0xc8580[i].m_red) * static_cast<LegoFloat>(c.m_unk0x0 & 0xff) / 256.0f;
			m_unk0xc859c[i].m_grn =
				static_cast<LegoFloat>(m_unk0xc8580[i].m_grn) * static_cast<LegoFloat>(c.m_unk0x1 & 0xff) / 256.0f;
			m_unk0xc859c[i].m_blu =
				static_cast<LegoFloat>(m_unk0xc8580[i].m_blu) * static_cast<LegoFloat>(c.m_unk0x2 & 0xff) / 256.0f;
		}
	}

	if (m_flags & c_flagBit14) {
		newFlags &= ~(DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit13);
		newFlags |= DuskwindBananaRelic0x24::c_flag0x08Bit9 | DuskwindBananaRelic0x24::c_flag0x08Bit12;
	}
	else {
		if (newFlags & (DuskwindBananaRelic0x24::c_flag0x08Bit6 | DuskwindBananaRelic0x24::c_flag0x08Bit8 |
						DuskwindBananaRelic0x24::c_flag0x08Bit12)) {
			if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit6) {
				LegoU32 alphaFunc = p_material->GetAlphaFunc();
				if (m_unk0xc83d0 != alphaFunc) {
					m_unk0xc83d0 = alphaFunc;
					m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, g_d3dCmpFuncLookup[alphaFunc]);
				}

				LegoU32 alphaRef = p_material->GetAlphaRef();
				if (m_unk0xc83d4 != alphaRef) {
					m_unk0xc83d4 = alphaRef;
					// BUG? documentation specifies range from 0x00000000 to 0x000000FF.
					m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, alphaRef << 16);
				}
			}

			if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit12) {
				LegoU32 destBlend = p_material->GetDestBlend();
				m_alpha = destBlend;
				newFlags &= ~DuskwindBananaRelic0x24::c_flag0x08Bit4;
				newFlags |= DuskwindBananaRelic0x24::c_flag0x08Bit5;
				m_unk0xc83fc = (destBlend << 24) | (m_unk0xc83fc & 0x00ffffff);
			}
			else if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit8) {
				LegoU32 srcBlend = p_material->GetSrcBlend();
				if (m_unk0xc83d8 != srcBlend) {
					m_unk0xc83d8 = srcBlend;
					m_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, m_unk0xc8708[srcBlend]);
				}

				LegoU32 destBlend = p_material->GetDestBlend();
				if (m_unk0xc83dc != destBlend) {
					m_unk0xc83dc = destBlend;
					m_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, m_unk0xc8734[destBlend]);
				}
			}
		}
	}

	if (newFlags == m_unk0xc83c8) {
		return;
	}

	if ((newFlags ^ m_unk0xc83c8) &
		(DuskwindBananaRelic0x24::c_flag0x08Bit10 | DuskwindBananaRelic0x24::c_flag0x08Bit11)) {
		if (!(newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit11) && m_drawState->IsHwAccelerated()) {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTSS_COLORARG1);
			m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		}
		else {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTSS_COLOROP);
			m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		}
	}

	if ((newFlags ^ m_unk0xc83c8) &
		(DuskwindBananaRelic0x24::c_flag0x08Bit15 | DuskwindBananaRelic0x24::c_flag0x08Bit16)) {
		if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit16) {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_CLAMP);
		}
		else {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP);
		}
	}

	if ((newFlags ^ m_unk0xc83c8) &
		(DuskwindBananaRelic0x24::c_flag0x08Bit1 | DuskwindBananaRelic0x24::c_flag0x08Bit2)) {
		if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit2) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
		}
		else {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT);
		}
	}

	if ((newFlags ^ m_unk0xc83c8) & (DuskwindBananaRelic0x24::c_flag0x08Bit3 | DuskwindBananaRelic0x24::c_flag0x08Bit4 |
									 DuskwindBananaRelic0x24::c_flag0x08Bit5)) {
		if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
			if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit5) {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
				if (m_flags & c_flagBit19) {
					m_unk0xc83fc = ARGBU32(m_alpha, m_unk0x118.m_red, m_unk0x118.m_grn, m_unk0x118.m_blu);
				}
				else {
					m_unk0xc83f8 = FALSE;
				}
			}
			else {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
				m_unk0xc83f8 = TRUE;
				m_unk0xc83fc = ARGBU32(m_alpha, 0xff, 0xff, 0xff);
			}
			if (newFlags & (DuskwindBananaRelic0x24::c_flag0x08Bit12 | DuskwindBananaRelic0x24::c_flag0x08Bit5)) {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
				m_unk0xc83e8 = TRUE;
			}
			else {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
				m_unk0xc83e8 = TRUE;
			}
		}
		else {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
			m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
			m_unk0xc83e8 = FALSE;
			if (m_flags & c_flagBit19) {
				m_unk0xc83fc = ARGBU32(m_alpha, m_unk0x118.m_red, m_unk0x118.m_grn, m_unk0x118.m_blu);
			}
			else {
				m_unk0xc83f8 = FALSE;
			}
		}
		FUN_10012f50();
	}

	if ((newFlags ^ m_unk0xc83c8) &
		(DuskwindBananaRelic0x24::c_flag0x08Bit6 | DuskwindBananaRelic0x24::c_flag0x08Bit7)) {
		if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit6) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		}
		else {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		}
	}

	if ((newFlags ^ m_unk0xc83c8) &
		(DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit9 |
		 DuskwindBananaRelic0x24::c_flag0x08Bit12 | DuskwindBananaRelic0x24::c_flag0x08Bit13)) {
		if (newFlags & (DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit12)) {
			m_unk0xc83ec = 0;
			if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit12) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
				m_unk0xc83d8 = 6;
				m_unk0xc83dc = 8;
				m_unk0xc83ec = 1;
				if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
					m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
				}
				else {
					m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
				}
			}
			else {
				if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
					if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit5) {
						m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
					}
					else {
						m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
						m_unk0xc83fc = ARGBU32(0xff, 0xff, 0xff, 0xff);
					}
				}
				else {
					m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
				}
				m_alpha = 0xff;
			}
			if (m_flags & c_flagBit12) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, TRUE);
			}
			else {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			}
			m_unk0xc83c8 = newFlags;
			FUN_10012f50();
		}
		else {
			if (m_unk0xc83c8 & DuskwindBananaRelic0x24::c_flag0x08Bit12) {
				if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit3) {
					if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit5) {
						m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
					}
					else {
						m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
						m_unk0xc83fc = ARGBU32(0xff, 0xff, 0xff, 0xff);
					}
				}
				else {
					m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
				}
				m_alpha = 0xff;
			}
			if (m_flags & c_flagBit12) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, FALSE);
			}
			else {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
			}
			m_unk0xc83ec = 0;
			m_unk0xc83c8 = newFlags;
			FUN_10012f50();
		}
	}
	else {
		if ((m_unk0xc83c8 ^ newFlags) & DuskwindBananaRelic0x24::c_flag0x08Bit14) {
			m_unk0xc83c8 = newFlags;
			FUN_10012f50();
		}
		else {
			m_unk0xc83c8 = newFlags;
		}
	}
}

// FUNCTION: GOLDP 0x1000a950
void GolD3DRenderDevice::FUN_1000a950(DuskwindBananaRelic0x24* p_material)
{
	LegoU32 newFlags = p_material->GetUnk0x08();
	m_unk0xc8538 = p_material;

	LegoU32 textureCount;
	if (p_material->GetUnk0x04() == NULL) {
		textureCount = 1;
	}
	else {
		textureCount = p_material->GetUnk0x04()->GetUnk0x34();
	}
	m_unk0xc83ac = textureCount - 1;

	if (textureCount > 0) {
		for (LegoU32 i = 0; i < textureCount; i++) {
			m_unk0xc83b4.m_unk0x00[i] = static_cast<DuskwindBananaRelic0x30*>(p_material)->GetUnk0x2c() + i * 16;
		}
	}

	if (m_unk0xc8568 != 0) {
		DuskwindBananaRelicColor color = p_material->GetColor0x10();
		m_unk0xc8570 = (static_cast<LegoU32>(m_unk0xc856c.m_red) * static_cast<LegoU32>(color.m_unk0x0 & 0xff)) >> 8;
		m_unk0xc8574 = (static_cast<LegoU32>(m_unk0xc856c.m_grn) * static_cast<LegoU32>(color.m_unk0x1 & 0xff)) >> 8;
		m_unk0xc8578 = (static_cast<LegoU32>(m_unk0xc856c.m_blu) * static_cast<LegoU32>(color.m_unk0x2 & 0xff)) >> 8;
		m_unk0xc857c = color.m_unk0x3 & 0xff;

		color = p_material->GetColor0x0c();
		for (LegoU32 i = 0; i < m_unk0x11c; i++) {
			m_unk0xc859c[i].m_red = ScaleColorChannel(m_unk0xc8580[i].m_red, color.m_unk0x0 & 0xff);
			m_unk0xc859c[i].m_grn = ScaleColorChannel(m_unk0xc8580[i].m_grn, color.m_unk0x1 & 0xff);
			m_unk0xc859c[i].m_blu = ScaleColorChannel(m_unk0xc8580[i].m_blu, color.m_unk0x2 & 0xff);
		}
	}

	if (m_flags & c_flagBit14) {
		newFlags &= ~(DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit13);
		newFlags |= DuskwindBananaRelic0x24::c_flag0x08Bit9 | DuskwindBananaRelic0x24::c_flag0x08Bit12;
	}
	else if (
		newFlags & (DuskwindBananaRelic0x24::c_flag0x08Bit6 | DuskwindBananaRelic0x24::c_flag0x08Bit8 |
					DuskwindBananaRelic0x24::c_flag0x08Bit12)
	) {
		if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit6) {
			m_unk0xc83d0 = p_material->GetAlphaFunc();
			m_unk0xc83d4 = p_material->GetAlphaRef();
		}

		if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit12) {
			LegoU32 destBlend = p_material->GetDestBlend();
			m_alpha = destBlend;
			newFlags &= ~DuskwindBananaRelic0x24::c_flag0x08Bit4;
			newFlags |= DuskwindBananaRelic0x24::c_flag0x08Bit5;
			m_unk0xc83fc = (destBlend << 24) | (m_unk0xc83fc & 0x00ffffff);
		}
		else if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit8) {
			m_unk0xc83d8 = p_material->GetSrcBlend();
			m_unk0xc83dc = p_material->GetDestBlend();
		}
	}

	if (newFlags == m_unk0xc83c8) {
		return;
	}

	LegoU32 changedFlags = newFlags ^ m_unk0xc83c8;
	if (changedFlags & (DuskwindBananaRelic0x24::c_flag0x08Bit3 | DuskwindBananaRelic0x24::c_flag0x08Bit4 |
						DuskwindBananaRelic0x24::c_flag0x08Bit5)) {
		m_unk0xc83e8 = (newFlags >> 3) & 1;
		FUN_10012f50();
	}

	changedFlags = newFlags ^ m_unk0xc83c8;
	if (changedFlags & (DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit9 |
						DuskwindBananaRelic0x24::c_flag0x08Bit12 | DuskwindBananaRelic0x24::c_flag0x08Bit13)) {
		m_unk0xc83ec = 0;
		if (newFlags & (DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit12)) {
			if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit12) {
				m_unk0xc83d8 = 6;
				m_unk0xc83dc = 8;
				m_unk0xc83ec = 1;
				m_unk0xc83c8 = newFlags;
				FUN_10012f50();
				return;
			}
			m_alpha = 0xff;
		}

		m_unk0xc83c8 = newFlags;
		FUN_10012f50();
	}
	else {
		m_unk0xc83c8 = newFlags;
		if (changedFlags & DuskwindBananaRelic0x24::c_flag0x08Bit14) {
			FUN_10012f50();
		}
	}
}

// FUNCTION: GOLDP 0x1000ac00
void GolD3DRenderDevice::FUN_1000ac00(GoldDune0x38* p_texture)
{
	if (m_currentTexture == p_texture) {
		return;
	}

	m_currentTexture = p_texture;
	if (m_unk0xc83c4) {
		if (p_texture != NULL) {
			m_unk0xc83b0 = ~((p_texture->GetHeight() * p_texture->GetWidth() * 2) - 1);
		}
		return;
	}

	if (p_texture != NULL) {
		if (p_texture->GetUnk0x36() & GoldDune0x38::c_unk0x36Bit5) {
			if (m_unk0xc83f0 == 0) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
				m_unk0xc83f0 = TRUE;
			}
		}
		else if (m_unk0xc83f0 != 0) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
			m_unk0xc83f0 = FALSE;
		}

		m_d3dDevice->SetTexture(0, static_cast<PurpleDune0x7c*>(m_currentTexture)->GetDirect3DTexture());
	}
	else if (m_unk0xc83f0 != 0) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
		m_unk0xc83f0 = FALSE;
	}
}

// FUNCTION: GOLDP 0x1000acf0
void GolD3DRenderDevice::FUN_1000acf0(LegoU32 p_index)
{
	Field0xc8524* useMatrix = m_unk0xc8524;
	GolTransform** orbits = &static_cast<GolSceneTransformNode*>(m_unk0xc8520)->m_unk0x18;
	GolMatrix4* matrix;
	if (useMatrix != NULL) {
		matrix = &(*orbits)[p_index].m_unk0x90;
	}
	else {
		matrix = &(*orbits)[p_index].m_unk0x50;
	}
	m_unk0xc8518 = matrix;

	if (m_unk0xc8568 != 0) {
		GolMatrix4* lightMatrix = &(*orbits)[p_index].m_unk0x90;
		for (LegoU32 i = 0; i < m_unk0x11c; i++) {
			m_unk0xc8644[i].m_x = m_unk0xc85f0[i].m_x * lightMatrix->m_m[0][0];
			m_unk0xc8644[i].m_y = m_unk0xc85f0[i].m_x * lightMatrix->m_m[1][0];
			m_unk0xc8644[i].m_z = m_unk0xc85f0[i].m_x * lightMatrix->m_m[2][0];

			m_unk0xc8644[i].m_x += lightMatrix->m_m[0][1] * m_unk0xc85f0[i].m_y;
			m_unk0xc8644[i].m_y += lightMatrix->m_m[1][1] * m_unk0xc85f0[i].m_y;
			m_unk0xc8644[i].m_z += lightMatrix->m_m[2][1] * m_unk0xc85f0[i].m_y;

			m_unk0xc8644[i].m_x += m_unk0xc85f0[i].m_z * lightMatrix->m_m[0][2];
			m_unk0xc8644[i].m_y += m_unk0xc85f0[i].m_z * lightMatrix->m_m[1][2];
			m_unk0xc8644[i].m_z += m_unk0xc85f0[i].m_z * lightMatrix->m_m[2][2];
		}
	}
}

// STUB: GOLDP 0x1000add0
void GolD3DRenderDevice::FUN_1000add0(GolWorldEntity* p_model, GolModel* p_modelData)
{
	GolOrientedEntity* model = static_cast<GolOrientedEntity*>(p_model);
	model->FUN_10026c50(&m_unk0xc8450);

	const GolVec3& position = model->GetPosition();
	m_unk0xc8450.m_m[3][0] = position.m_x;
	m_unk0xc8450.m_m[3][1] = position.m_y;
	m_unk0xc8450.m_m[3][2] = position.m_z;

	GdbVertexArrayTypeTwo0x20* vertexArray =
		static_cast<GdbVertexArrayTypeTwo0x20*>(p_modelData->GetModelVertexArray());
	m_unk0xc4c1c = vertexArray->GetNormals();

	for (LegoU32 i = 0; i < m_unk0x11c; i++) {
		m_unk0xc8644[i].m_x = m_unk0xc85f0[i].m_x * m_unk0xc8450.m_m[0][0];
		m_unk0xc8644[i].m_y = m_unk0xc85f0[i].m_x * m_unk0xc8450.m_m[1][0];
		m_unk0xc8644[i].m_z = m_unk0xc85f0[i].m_x * m_unk0xc8450.m_m[2][0];

		m_unk0xc8644[i].m_x += m_unk0xc8450.m_m[0][1] * m_unk0xc85f0[i].m_y;
		m_unk0xc8644[i].m_y += m_unk0xc8450.m_m[1][1] * m_unk0xc85f0[i].m_y;
		m_unk0xc8644[i].m_z += m_unk0xc8450.m_m[2][1] * m_unk0xc85f0[i].m_y;

		m_unk0xc8644[i].m_x += m_unk0xc85f0[i].m_z * m_unk0xc8450.m_m[0][2];
		m_unk0xc8644[i].m_y += m_unk0xc85f0[i].m_z * m_unk0xc8450.m_m[1][2];
		m_unk0xc8644[i].m_z += m_unk0xc8450.m_m[2][2] * m_unk0xc85f0[i].m_z;
	}
}

// FUNCTION: GOLDP 0x1000aeb0
void GolD3DRenderDevice::SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags)
{
	GolRenderDevice::SetAlphaOverride(p_alpha, p_flags);
	m_alpha = p_alpha;
	m_unk0xc83fc = (m_unk0xc83fc & 0x00ffffff) | (p_alpha << 24);
}

// FUNCTION: GOLDP 0x1000aef0
void GolD3DRenderDevice::ClearAlphaOverride()
{
	GolRenderDevice::ClearAlphaOverride();
	m_alpha = 0xff;
	m_unk0xc83fc |= 0xff000000;
}

// FUNCTION: GOLDP 0x1000af20
void GolD3DRenderDevice::VTable0xc0(const ColorRGBA& p_color)
{
	GolRenderDevice::VTable0xc0(p_color);
	m_unk0xc83f8 = TRUE;
	m_unk0xc83fc = ARGBU32(m_alpha, p_color.m_red, p_color.m_grn, p_color.m_blu);
}

// FUNCTION: GOLDP 0x1000af70
void GolD3DRenderDevice::VTable0xc4()
{
	GolRenderDevice::VTable0xc4();
	m_unk0xc83f8 = FALSE;
}

// FUNCTION: GOLDP 0x1000af90
void GolD3DRenderDevice::VTable0x28()
{
	GolRenderDevice::VTable0x28();
	m_unk0xc856c.m_red = 0xff;
	m_unk0xc856c.m_grn = 0xff;
	m_unk0xc856c.m_blu = 0xff;
	m_unk0xc856c.m_alp = 0xff;

	if (m_unk0xc8538 != NULL) {
		DuskwindBananaRelicColor color = m_unk0xc8538->GetColor0x10();
		m_unk0xc8570 = color.m_unk0x0 & 0xff;
		m_unk0xc8574 = color.m_unk0x1 & 0xff;
		m_unk0xc8578 = color.m_unk0x2 & 0xff;
		m_unk0xc857c = color.m_unk0x3 & 0xff;
	}
}

// FUNCTION: GOLDP 0x1000b000
void GolD3DRenderDevice::VTable0x2c(const MaterialColor* p_param)
{
	GolRenderDevice::VTable0x2c(p_param);
	m_unk0xc856c = p_param->m_color;

	if (m_unk0xc8538 != NULL) {
		DuskwindBananaRelicColor color = m_unk0xc8538->GetColor0x10();
		m_unk0xc8570 = (static_cast<LegoU32>(m_unk0xc856c.m_red) * static_cast<LegoU32>(color.m_unk0x0 & 0xff)) >> 8;
		m_unk0xc8574 = (static_cast<LegoU32>(m_unk0xc856c.m_grn) * static_cast<LegoU32>(color.m_unk0x1 & 0xff)) >> 8;
		m_unk0xc8578 = (static_cast<LegoU32>(m_unk0xc856c.m_blu) * static_cast<LegoU32>(color.m_unk0x2 & 0xff)) >> 8;
		m_unk0xc857c = color.m_unk0x3 & 0xff;
	}
	else {
		m_unk0xc8570 = 0;
		m_unk0xc8574 = 0;
		m_unk0xc8578 = 0;
		m_unk0xc857c = 0xff;
	}
}

// FUNCTION: GOLDP 0x1000b0c0
void GolD3DRenderDevice::VTable0x30(const Light* p_param)
{
	LegoU32 index = m_unk0x11c;
	if (index < 7) {
		FUN_1000b0f0(index, p_param);
		GolRenderDevice::VTable0x30(p_param);
	}
}

// FUNCTION: GOLDP 0x1000b0f0
void GolD3DRenderDevice::FUN_1000b0f0(LegoU32 p_index, const Light* p_param)
{
	m_unk0xc8580[p_index] = p_param->m_color;
	m_unk0xc85f0[p_index] = p_param->m_direction;

	DuskwindBananaRelicColor color;
	if (m_unk0xc8538 != NULL) {
		color = m_unk0xc8538->GetColor0x0c();
	}
	else {
		color.m_unk0x0 = 0;
		color.m_unk0x1 = 0;
		color.m_unk0x2 = 0;
	}

	m_unk0xc859c[p_index].m_red = ScaleColorChannel(color.m_unk0x0 & 0xff, m_unk0xc8580[p_index].m_red);
	m_unk0xc859c[p_index].m_grn = ScaleColorChannel(m_unk0xc8580[p_index].m_grn, color.m_unk0x1 & 0xff);
	m_unk0xc859c[p_index].m_blu = ScaleColorChannel(m_unk0xc8580[p_index].m_blu, color.m_unk0x2 & 0xff);
}

// FUNCTION: GOLDP 0x1000b1f0
void GolD3DRenderDevice::VTable0x60()
{
	if (m_flags & c_flagBit15) {
		if (m_unk0x120 != NULL) {
			VTable0x2c(m_unk0x120);
		}

		for (LegoU32 i = 0; i < m_unk0x11c; i++) {
			FUN_1000b0f0(i, m_unk0x124[i]);
		}
	}
}

// FUNCTION: GOLDP 0x1000b240
void GolD3DRenderDevice::VTable0xc8()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
	}
}

// FUNCTION: GOLDP 0x1000b260
void GolD3DRenderDevice::VTable0xcc()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
	}
}

// FUNCTION: GOLDP 0x1000b280
void GolD3DRenderDevice::VTable0x3c(LegoU32 p_arg)
{
	m_flags |= c_flagBit17;
	m_unk0xc8704 = p_arg;
	if (m_unk0xc8704 > 4) {
		m_unk0xc8704 = 4;
	}
}

// FUNCTION: GOLDP 0x1000b2b0
void GolD3DRenderDevice::VTable0x40()
{
	m_flags &= ~c_flagBit17;
}

// FUNCTION: GOLDP 0x1000b2c0
SlatePeak0x58* GolD3DRenderDevice::VTable0x4c(undefined2 p_arg1, undefined2 p_arg2)
{
	GolD3DRenderSurface* surface = new GolD3DRenderSurface;
	if (surface == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	surface->FUN_10013600(this, p_arg1, p_arg2);
	surface->m_next = m_unk0x30c;
	m_unk0x30c = surface;
	return surface;
}

// FUNCTION: GOLDP 0x1000b350
void GolD3DRenderDevice::VTable0x50(SlatePeak0x58* p_surface)
{
	GolD3DRenderSurface* surface = m_unk0x30c;
	if (surface == NULL) {
		return;
	}

	GolD3DRenderSurface* target = static_cast<GolD3DRenderSurface*>(p_surface);
	if (target == surface) {
		m_unk0x30c = surface->m_next;
		target->VTable0x34();
		delete target;
		return;
	}

	GolD3DRenderSurface* previous = surface;
	surface = surface->m_next;
	if (surface == NULL) {
		return;
	}

	while (surface != NULL) {
		if (surface == target) {
			previous->m_next = surface->m_next;
			surface->m_next = NULL;
			target->VTable0x34();
			delete target;
			return;
		}

		previous = surface;
		surface = surface->m_next;
	}
}

// FUNCTION: GOLDP 0x1000b3d0
void GolD3DRenderDevice::VTable0x58(SlatePeak0x58* p_surface, undefined4 p_flags)
{
	m_renderTargetInfo = m_unk0x304;
	GolD3DRenderSurface* surface = m_unk0x30c;
	if (surface != NULL) {
		GolD3DRenderSurface* target = static_cast<GolD3DRenderSurface*>(p_surface);
		while (surface != NULL) {
			if (surface == target) {
				m_renderTargetInfo = surface;
				if (!m_unk0xc83c4 && m_d3dDevice->SetRenderTarget(m_renderTargetInfo->m_renderSurface, 0) != D3D_OK) {
					GOL_FATALERROR_MESSAGE("Unable to set secondary rendering target");
				}

				Rect rect;
				rect.m_left = 0;
				rect.m_top = 0;
				rect.m_right = m_renderTargetInfo->m_width;
				rect.m_bottom = m_renderTargetInfo->m_height;

				VTable0x20(m_unk0x0c);
				m_unk0x0c->VTable0x0c(&rect);
				VTable0x54(p_flags);
				return;
			}

			surface = surface->m_next;
		}

		VTable0x54(p_flags);
		return;
	}

	VTable0x54(p_flags);
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoBool32 GolD3DRenderDevice::VTable0x110() const
{
	MATCHING(0x100016f0);
	return FALSE;
}

// FUNCTION: GOLDP 0x1000b4a0
void GolD3DRenderDevice::FUN_1000b4a0()
{
	switch (m_unk0xc8700) {
	case 0: {
		m_countTextureFormats = 1;

		TextureFormat* textureFormats = new TextureFormat[m_countTextureFormats];
		m_textureFormats = textureFormats;
		if (m_textureFormats == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textureFormats[0].m_redBitMask = 0;
		m_textureFormats[0].m_grnBitMask = 0;
		m_textureFormats[0].m_bluBitMask = 0;
		m_textureFormats[0].m_alpBitMask = 0;
		m_textureFormats[0].m_paletteMask = 0xff;
		m_textureFormats[0].m_unk0x10 = 0;
		m_textureFormats[0].m_bitsPerPixel = 8;
		break;
	}
	case 1: {
		m_countTextureFormats = 1;

		TextureFormat* textureFormats = new TextureFormat[m_countTextureFormats];
		m_textureFormats = textureFormats;
		if (m_textureFormats == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textureFormats[0].m_redBitMask = 0xe0;
		m_textureFormats[0].m_grnBitMask = 0x1c;
		m_textureFormats[0].m_bluBitMask = 0x03;
		m_textureFormats[0].m_alpBitMask = 0;
		m_textureFormats[0].m_paletteMask = 0;
		m_textureFormats[0].m_unk0x10 = 0;
		m_textureFormats[0].m_bitsPerPixel = 8;
		break;
	}
	case 2: {
		m_countTextureFormats = 3;

		TextureFormat* textureFormats = new TextureFormat[m_countTextureFormats];
		m_textureFormats = textureFormats;
		if (m_textureFormats == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textureFormats[1].m_redBitMask = 0;
		m_textureFormats[1].m_grnBitMask = 0;
		m_textureFormats[1].m_bluBitMask = 0;
		m_textureFormats[1].m_alpBitMask = 0;
		m_textureFormats[1].m_paletteMask = 0xff;
		m_textureFormats[1].m_unk0x10 = 0;
		m_textureFormats[1].m_bitsPerPixel = 8;

		GolSurfaceFormat& textureFormat = m_renderTargetInfo->GetTextureFormat();
		if (textureFormat.GetGreenBitCount() == 6) {
			m_textureFormats[0].m_redBitMask = 0xf800;
			m_textureFormats[0].m_grnBitMask = 0x07e0;
			m_textureFormats[0].m_bluBitMask = 0x001f;
			m_textureFormats[0].m_alpBitMask = 0;
			m_textureFormats[0].m_paletteMask = 0;
			m_textureFormats[0].m_unk0x10 = 0;
			m_textureFormats[0].m_bitsPerPixel = 16;
			m_textureFormats[2].m_redBitMask = 0xf8000000;
			m_textureFormats[2].m_grnBitMask = 0x07e00000;
			m_textureFormats[2].m_bluBitMask = 0x001f0000;
			m_textureFormats[2].m_alpBitMask = 0x000003ff;
			m_textureFormats[2].m_paletteMask = 0;
			m_textureFormats[2].m_unk0x10 = 0;
			m_textureFormats[2].m_bitsPerPixel = 32;
		}
		else {
			m_textureFormats[0].m_redBitMask = 0x7c00;
			m_textureFormats[0].m_grnBitMask = 0x03e0;
			m_textureFormats[0].m_bluBitMask = 0x001f;
			m_textureFormats[0].m_alpBitMask = 0;
			m_textureFormats[0].m_paletteMask = 0;
			m_textureFormats[0].m_unk0x10 = 0;
			m_textureFormats[0].m_bitsPerPixel = 16;
			m_textureFormats[2].m_redBitMask = 0x7c000000;
			m_textureFormats[2].m_grnBitMask = 0x03e00000;
			m_textureFormats[2].m_bluBitMask = 0x001f0000;
			m_textureFormats[2].m_alpBitMask = 0x000003ff;
			m_textureFormats[2].m_paletteMask = 0;
			m_textureFormats[2].m_unk0x10 = 0;
			m_textureFormats[2].m_bitsPerPixel = 32;
		}
		break;
	}
	}
}

// FUNCTION: GOLDP 0x1000b7c0
GolD3DRenderDevice::TextureFormat::TextureFormat()
{
}

// FUNCTION: GOLDP 0x1000b7e0
HRESULT GolD3DRenderDevice::CountTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context)
{
	LegoU32* count = static_cast<LegoU32*>(p_context);
	*count += 1;
	return TRUE;
}

// FUNCTION: GOLDP 0x1000b800
HRESULT GolD3DRenderDevice::EnumerateTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context)
{
	GolD3DRenderDevice* self = static_cast<GolD3DRenderDevice*>(p_context);
	GolSurfaceFormat* format = &self->m_textureFormats[self->m_unk0x2c];
	self->m_unk0x2c += 1;

	if (p_format->dwFlags & DDPF_PALETTEINDEXED8) {
		format->m_paletteMask = 0xff;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_unk0x10 = 0;
		format->m_bitsPerPixel = 8;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED4) {
		format->m_paletteMask = 0xf;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_unk0x10 = 0;
		format->m_bitsPerPixel = 4;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED2) {
		format->m_paletteMask = 0x3;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_unk0x10 = 0;
		format->m_bitsPerPixel = 2;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED1) {
		format->m_paletteMask = 0x1;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_unk0x10 = 0;
		format->m_bitsPerPixel = 1;
	}
	else {
		format->m_redBitMask = p_format->dwRBitMask;
		format->m_grnBitMask = p_format->dwGBitMask;
		format->m_bluBitMask = p_format->dwBBitMask;
		format->m_paletteMask = 0;
		format->m_unk0x10 = 0;
		LegoU32 bitCount = p_format->dwRGBBitCount;
		format->m_bitsPerPixel = bitCount;
	}
	if (p_format->dwFlags & DDPF_ALPHAPIXELS) {
		format->m_alpBitMask = p_format->dwRGBAlphaBitMask;
	}
	else {
		format->m_alpBitMask = 0;
	}

	return TRUE;
}

// STUB: GOLDP 0x1000b8e0
void GolD3DRenderDevice::FUN_1000b8e0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_unk0xc4c0c + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
	LegoU32* color = m_unk0xc4c14 + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = m_unk0xc8518->m_m[0][0] * position->m_x;
		vertex->sy = m_unk0xc8518->m_m[0][1] * position->m_x;
		vertex->rhw = m_unk0xc8518->m_m[0][3] * position->m_x;

		vertex->sx += m_unk0xc8518->m_m[1][0] * position->m_y;
		vertex->sy += m_unk0xc8518->m_m[1][1] * position->m_y;
		vertex->rhw += m_unk0xc8518->m_m[1][3] * position->m_y;

		vertex->sx += m_unk0xc8518->m_m[2][0] * position->m_z;
		vertex->sy += m_unk0xc8518->m_m[2][1] * position->m_z;
		vertex->rhw += m_unk0xc8518->m_m[2][3] * position->m_z;

		vertex->sx += m_unk0xc8518->m_m[3][0];
		vertex->sy += m_unk0xc8518->m_m[3][1];
		vertex->rhw = 1.0f / (vertex->rhw + m_unk0xc8518->m_m[3][3]);

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = *color;
		color++;
		vertex->tu = uv->m_x;
		vertex->tv = uv->m_y;
		uv++;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000baa0
void GolD3DRenderDevice::FUN_1000baa0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_unk0xc4c0c + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	LegoU32* color = m_unk0xc4c14 + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = m_unk0xc8518->m_m[0][0] * position->m_x;
		vertex->sy = m_unk0xc8518->m_m[0][1] * position->m_x;
		vertex->rhw = m_unk0xc8518->m_m[0][3] * position->m_x;

		vertex->sx += m_unk0xc8518->m_m[1][0] * position->m_y;
		vertex->sy += m_unk0xc8518->m_m[1][1] * position->m_y;
		vertex->rhw += m_unk0xc8518->m_m[1][3] * position->m_y;

		vertex->sx += m_unk0xc8518->m_m[2][0] * position->m_z;
		vertex->sy += m_unk0xc8518->m_m[2][1] * position->m_z;
		vertex->rhw += m_unk0xc8518->m_m[2][3] * position->m_z;

		vertex->sx += m_unk0xc8518->m_m[3][0];
		vertex->sy += m_unk0xc8518->m_m[3][1];
		vertex->rhw = 1.0f / (vertex->rhw + m_unk0xc8518->m_m[3][3]);

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = *color;
		color++;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000bc40
void GolD3DRenderDevice::FUN_1000bc40(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_unk0xc4c0c + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
	LegoU32* color = m_unk0xc4c14 + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = m_unk0xc8518->m_m[0][0] * position->m_x;
		vertex->sy = m_unk0xc8518->m_m[0][1] * position->m_x;
		vertex->rhw = m_unk0xc8518->m_m[0][3] * position->m_x;

		vertex->sx += m_unk0xc8518->m_m[1][0] * position->m_y;
		vertex->sy += m_unk0xc8518->m_m[1][1] * position->m_y;
		vertex->rhw += m_unk0xc8518->m_m[1][3] * position->m_y;

		vertex->sx += m_unk0xc8518->m_m[2][0] * position->m_z;
		vertex->sy += m_unk0xc8518->m_m[2][1] * position->m_z;
		vertex->rhw += m_unk0xc8518->m_m[2][3] * position->m_z;

		vertex->sx += m_unk0xc8518->m_m[3][0];
		vertex->sy += m_unk0xc8518->m_m[3][1];
		vertex->rhw = 1.0f / (vertex->rhw + m_unk0xc8518->m_m[3][3]);

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = (*color & 0x00ffffff) | alpha;
		color++;
		vertex->tu = uv->m_x;
		vertex->tv = uv->m_y;
		uv++;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000be20
void GolD3DRenderDevice::FUN_1000be20(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		LegoFloat x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
					  matrix.m_m[3][0];
		LegoFloat y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
					  matrix.m_m[3][1];
		LegoFloat z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
					  matrix.m_m[3][2];
		LegoFloat w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
					  matrix.m_m[3][3];
		LegoFloat rhw = 1.0f / w;
		D3DTLVERTEX& vertex = vertices[i];

		vertex.sx = x * rhw;
		vertex.sy = y * rhw;
		vertex.sz = z * rhw;
		vertex.rhw = rhw;
		vertex.color = m_unk0xc4c14[sourceIndex];
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y;
		vertexMap[i + 1] = static_cast<LegoU16>(vertexMap[i] + 1);
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// STUB: GOLDP 0x1000bfb0
void GolD3DRenderDevice::FUN_1000bfb0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		LegoFloat x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
					  matrix.m_m[3][0];
		LegoFloat y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
					  matrix.m_m[3][1];
		LegoFloat z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
					  matrix.m_m[3][2];
		LegoFloat w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
					  matrix.m_m[3][3];
		LegoFloat rhw = 1.0f / w;
		D3DTLVERTEX& vertex = vertices[i];

		vertex.sx = x * rhw;
		vertex.sy = y * rhw;
		vertex.sz = z * rhw;
		vertex.rhw = rhw;
		vertex.color = m_unk0xc4c14[sourceIndex];
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x + m_unk0xc83a0;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y + m_unk0xc83a4;
		vertexMap[i + 1] = static_cast<LegoU16>(vertexMap[i] + 1);
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// STUB: GOLDP 0x1000c160
void GolD3DRenderDevice::FUN_1000c160(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		LegoFloat x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
					  matrix.m_m[3][0];
		LegoFloat y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
					  matrix.m_m[3][1];
		LegoFloat z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
					  matrix.m_m[3][2];
		LegoFloat w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
					  matrix.m_m[3][3];
		LegoFloat rhw = 1.0f / w;
		D3DTLVERTEX& vertex = vertices[i];

		vertex.sx = x * rhw;
		vertex.sy = y * rhw;
		vertex.sz = z * rhw;
		vertex.rhw = rhw;
		vertex.color = m_unk0xc4c14[sourceIndex];
		vertexMap[i + 1] = static_cast<LegoU16>(vertexMap[i] + 1);
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// STUB: GOLDP 0x1000c2d0
void GolD3DRenderDevice::FUN_1000c2d0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		LegoFloat x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
					  matrix.m_m[3][0];
		LegoFloat y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
					  matrix.m_m[3][1];
		LegoFloat z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
					  matrix.m_m[3][2];
		LegoFloat w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
					  matrix.m_m[3][3];
		LegoFloat rhw = 1.0f / w;
		D3DTLVERTEX& vertex = vertices[i];

		vertex.sx = x * rhw;
		vertex.sy = y * rhw;
		vertex.sz = z * rhw;
		vertex.rhw = rhw;
		vertex.color = (m_unk0xc4c14[sourceIndex] & 0x00ffffff) | alpha;
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y;
		vertexMap[i + 1] = static_cast<LegoU16>(vertexMap[i] + 1);
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// STUB: GOLDP 0x1000c470
void GolD3DRenderDevice::FUN_1000c470(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		LegoFloat x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
					  matrix.m_m[3][0];
		LegoFloat y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
					  matrix.m_m[3][1];
		LegoFloat z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
					  matrix.m_m[3][2];
		LegoFloat w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
					  matrix.m_m[3][3];
		LegoFloat rhw = 1.0f / w;
		D3DTLVERTEX& vertex = vertices[i];

		vertex.sx = x * rhw;
		vertex.sy = y * rhw;
		vertex.sz = z * rhw;
		vertex.rhw = rhw;
		vertex.color = (m_unk0xc4c14[sourceIndex] & 0x00ffffff) | alpha;
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x + m_unk0xc83a0;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y + m_unk0xc83a4;
		vertexMap[i + 1] = static_cast<LegoU16>(vertexMap[i] + 1);
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// STUB: GOLDP 0x1000c630
void GolD3DRenderDevice::FUN_1000c630(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
						 matrix.m_m[3][0];
		cacheEntry.m_y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
						 matrix.m_m[3][1];
		cacheEntry.m_z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
						 matrix.m_m[3][2];
		cacheEntry.m_w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
						 matrix.m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc4c14[sourceIndex];
		vertex.tu = uv[i].m_x;
		vertex.tv = uv[i].m_y;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000c880
void GolD3DRenderDevice::FUN_1000c880(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
						 matrix.m_m[3][0];
		cacheEntry.m_y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
						 matrix.m_m[3][1];
		cacheEntry.m_z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
						 matrix.m_m[3][2];
		cacheEntry.m_w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
						 matrix.m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc4c14[sourceIndex];
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x + m_unk0xc83a0;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y + m_unk0xc83a4;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000caf0
void GolD3DRenderDevice::FUN_1000caf0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
						 matrix.m_m[3][0];
		cacheEntry.m_y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
						 matrix.m_m[3][1];
		cacheEntry.m_z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
						 matrix.m_m[3][2];
		cacheEntry.m_w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
						 matrix.m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc4c14[sourceIndex];
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000cd20
void GolD3DRenderDevice::FUN_1000cd20(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
						 matrix.m_m[3][0];
		cacheEntry.m_y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
						 matrix.m_m[3][1];
		cacheEntry.m_z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
						 matrix.m_m[3][2];
		cacheEntry.m_w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
						 matrix.m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = (m_unk0xc4c14[sourceIndex] & 0x00ffffff) | alpha;
		vertex.tu = uv[i].m_x;
		vertex.tv = uv[i].m_y;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000cf90
void GolD3DRenderDevice::FUN_1000cf90(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
						 matrix.m_m[3][0];
		cacheEntry.m_y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
						 matrix.m_m[3][1];
		cacheEntry.m_z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
						 matrix.m_m[3][2];
		cacheEntry.m_w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
						 matrix.m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = (m_unk0xc4c14[sourceIndex] & 0x00ffffff) | alpha;
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x + m_unk0xc83a0;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y + m_unk0xc83a4;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// FUNCTION: GOLDP 0x1000d210
void GolD3DRenderDevice::FUN_1000d210(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_unk0xc4c0c + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
	const GolVec3* normal = m_unk0xc4c1c + p_firstVertex;
	CommandVertex* vertex = m_unk0xc428c + p_outputFirst;

	for (; position < positionEnd; position++, normal++, uv++, vertex++) {
		vertex->m_x = (m_unk0xc8518->m_m[0][0] * position->m_x) * m_unk0xc852c;
		vertex->m_y = (m_unk0xc8518->m_m[0][1] * position->m_x) * m_unk0xc852c;
		vertex->m_z = (m_unk0xc8518->m_m[0][2] * position->m_x) * m_unk0xc852c;

		vertex->m_x += (m_unk0xc8518->m_m[1][0] * position->m_y) * m_unk0xc852c;
		vertex->m_y += (m_unk0xc8518->m_m[1][1] * position->m_y) * m_unk0xc852c;
		vertex->m_z += (m_unk0xc8518->m_m[1][2] * position->m_y) * m_unk0xc852c;

		vertex->m_x += (m_unk0xc8518->m_m[2][0] * position->m_z) * m_unk0xc852c;
		vertex->m_y += (m_unk0xc8518->m_m[2][1] * position->m_z) * m_unk0xc852c;
		vertex->m_z += (m_unk0xc8518->m_m[2][2] * position->m_z) * m_unk0xc852c;

		vertex->m_x += m_unk0xc8518->m_m[3][0];
		vertex->m_y += m_unk0xc8518->m_m[3][1];
		vertex->m_z += m_unk0xc8518->m_m[3][2];

		vertex->m_nx = m_unk0xc8518->m_m[0][0] * normal->m_x;
		vertex->m_ny = m_unk0xc8518->m_m[0][1] * normal->m_y;
		vertex->m_nz = m_unk0xc8518->m_m[0][2] * normal->m_z;

		vertex->m_nx += m_unk0xc8518->m_m[1][0] * normal->m_x;
		vertex->m_ny += m_unk0xc8518->m_m[1][1] * normal->m_y;
		vertex->m_nz += m_unk0xc8518->m_m[1][2] * normal->m_z;

		vertex->m_nx += m_unk0xc8518->m_m[2][0] * normal->m_x;
		vertex->m_ny += m_unk0xc8518->m_m[2][1] * normal->m_y;
		vertex->m_nz += m_unk0xc8518->m_m[2][2] * normal->m_z;

		vertex->m_u = uv->m_x;
		vertex->m_v = uv->m_y;
	}

	m_unk0xc8540 = p_outputFirst;
	m_unk0xc8544 = p_firstVertex;
	m_unk0xc8548 = p_vertexCount;
	m_unk0xc8524->VTable0x08(&m_unk0xc8530);
}

// STUB: GOLDP 0x1000d440
void GolD3DRenderDevice::FUN_1000d440(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_unk0xc4c0c + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	LegoU32* color = m_unk0xc4c14 + p_firstVertex;
	const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
	CommandVertex* vertex = m_unk0xc428c + p_outputFirst;

	while (position < positionEnd) {
		vertex->m_x = m_unk0xc8518->m_m[0][0] * position->m_x;
		vertex->m_y = m_unk0xc8518->m_m[0][1] * position->m_x;
		vertex->m_z = m_unk0xc8518->m_m[0][2] * position->m_x;

		vertex->m_x += m_unk0xc8518->m_m[1][0] * position->m_y;
		vertex->m_y += m_unk0xc8518->m_m[1][1] * position->m_y;
		vertex->m_z += m_unk0xc8518->m_m[1][2] * position->m_y;

		vertex->m_x += m_unk0xc8518->m_m[2][0] * position->m_z;
		vertex->m_y += m_unk0xc8518->m_m[2][1] * position->m_z;
		vertex->m_z += m_unk0xc8518->m_m[2][2] * position->m_z;

		vertex->m_x += m_unk0xc8518->m_m[3][0];
		vertex->m_y += m_unk0xc8518->m_m[3][1];
		vertex->m_z += m_unk0xc8518->m_m[3][2];

		LegoU32 sourceColor = *color;
		LegoU8* destColor = reinterpret_cast<LegoU8*>(&vertex->m_color);
		destColor[0] = static_cast<LegoU8>(sourceColor >> 16);
		destColor[1] = static_cast<LegoU8>(sourceColor >> 8);
		destColor[2] = static_cast<LegoU8>(sourceColor);
		destColor[3] = static_cast<LegoU8>(sourceColor >> 24);
		vertex->m_u = uv->m_x;
		vertex->m_v = uv->m_y;

		position++;
		uv++;
		color++;
		vertex++;
	}

	m_unk0xc8540 = p_outputFirst;
	m_unk0xc8544 = p_firstVertex;
	m_unk0xc8548 = p_vertexCount;
	m_unk0xc8524->VTable0x08(&m_unk0xc8530);
}

// STUB: GOLDP 0x1000d5d0
void GolD3DRenderDevice::FUN_1000d5d0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_unk0xc4c0c + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	LegoU32* color = m_unk0xc4c14 + p_firstVertex;
	const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
	CommandVertex* vertex = m_unk0xc428c + p_outputFirst;

	while (position < positionEnd) {
		vertex->m_x = m_unk0xc8518->m_m[0][0] * position->m_x;
		vertex->m_y = m_unk0xc8518->m_m[0][1] * position->m_x;
		vertex->m_z = m_unk0xc8518->m_m[0][2] * position->m_x;

		vertex->m_x += m_unk0xc8518->m_m[1][0] * position->m_y;
		vertex->m_y += m_unk0xc8518->m_m[1][1] * position->m_y;
		vertex->m_z += m_unk0xc8518->m_m[1][2] * position->m_y;

		vertex->m_x += m_unk0xc8518->m_m[2][0] * position->m_z;
		vertex->m_y += m_unk0xc8518->m_m[2][1] * position->m_z;
		vertex->m_z += m_unk0xc8518->m_m[2][2] * position->m_z;

		vertex->m_x += m_unk0xc8518->m_m[3][0];
		vertex->m_y += m_unk0xc8518->m_m[3][1];
		vertex->m_z += m_unk0xc8518->m_m[3][2];

		LegoU32 sourceColor = *color;
		LegoU8* destColor = reinterpret_cast<LegoU8*>(&vertex->m_color);
		destColor[0] = static_cast<LegoU8>(sourceColor >> 16);
		destColor[1] = static_cast<LegoU8>(sourceColor >> 8);
		destColor[2] = static_cast<LegoU8>(sourceColor);
		destColor[3] = static_cast<LegoU8>(m_alpha);
		vertex->m_u = uv->m_x;
		vertex->m_v = uv->m_y;

		position++;
		uv++;
		color++;
		vertex++;
	}

	m_unk0xc8540 = p_outputFirst;
	m_unk0xc8544 = p_firstVertex;
	m_unk0xc8548 = p_vertexCount;
	m_unk0xc8524->VTable0x08(&m_unk0xc8530);
}

// STUB: GOLDP 0x1000d760
void GolD3DRenderDevice::FUN_1000d760(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	{
		const GolVec3* position = m_unk0xc4c0c + p_firstVertex;
		const GolVec3* positionEnd = position + p_vertexCount;
		LegoU32* color = m_unk0xc4c14 + p_firstVertex;
		const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
		CommandVertex* commandVertex = m_unk0xc428c + p_outputFirst;

		while (position < positionEnd) {
			commandVertex->m_x = m_unk0xc8518->m_m[0][0] * position->m_x;
			commandVertex->m_y = m_unk0xc8518->m_m[0][1] * position->m_x;
			commandVertex->m_z = m_unk0xc8518->m_m[0][2] * position->m_x;

			commandVertex->m_x += m_unk0xc8518->m_m[1][0] * position->m_y;
			commandVertex->m_y += m_unk0xc8518->m_m[1][1] * position->m_y;
			commandVertex->m_z += m_unk0xc8518->m_m[1][2] * position->m_y;

			commandVertex->m_x += m_unk0xc8518->m_m[2][0] * position->m_z;
			commandVertex->m_y += m_unk0xc8518->m_m[2][1] * position->m_z;
			commandVertex->m_z += m_unk0xc8518->m_m[2][2] * position->m_z;

			commandVertex->m_x += m_unk0xc8518->m_m[3][0];
			commandVertex->m_y += m_unk0xc8518->m_m[3][1];
			commandVertex->m_z += m_unk0xc8518->m_m[3][2];

			LegoU32 sourceColor = *color;
			LegoU8* destColor = reinterpret_cast<LegoU8*>(&commandVertex->m_color);
			destColor[0] = static_cast<LegoU8>(sourceColor >> 16);
			destColor[1] = static_cast<LegoU8>(sourceColor >> 8);
			destColor[2] = static_cast<LegoU8>(sourceColor);
			destColor[3] = static_cast<LegoU8>(sourceColor >> 24);
			commandVertex->m_u = uv->m_x;
			commandVertex->m_v = uv->m_y;

			position++;
			uv++;
			color++;
			commandVertex++;
		}
	}

	m_unk0xc8540 = p_outputFirst;
	m_unk0xc8544 = p_firstVertex;
	m_unk0xc8548 = p_vertexCount;
	m_unk0xc8524->VTable0x10(&m_unk0xc8530);

	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	m_unk0xc3848 = cacheIndex + p_vertexCount;
	D3DTLVERTEX* vertex = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	CommandVertex* source = m_unk0xc428c + p_outputFirst;
	CommandVertex* sourceEnd = source + p_vertexCount;

	for (; source < sourceEnd; source++, cache++, vertex++, cacheIndex++) {
		const GolMatrix4& matrix = *m_unk0xc8490;
		cache->m_x = source->m_x * matrix.m_m[0][0] + source->m_y * matrix.m_m[1][0] + source->m_z * matrix.m_m[2][0] +
					 matrix.m_m[3][0];
		cache->m_y = source->m_x * matrix.m_m[0][1] + source->m_y * matrix.m_m[1][1] + source->m_z * matrix.m_m[2][1] +
					 matrix.m_m[3][1];
		cache->m_z = source->m_x * matrix.m_m[0][2] + source->m_y * matrix.m_m[1][2] + source->m_z * matrix.m_m[2][2] +
					 matrix.m_m[3][2];
		cache->m_w = source->m_x * matrix.m_m[0][3] + source->m_y * matrix.m_m[1][3] + source->m_z * matrix.m_m[2][3] +
					 matrix.m_m[3][3];
		cache->m_unk0x10 = cacheIndex;
		cache->m_clipFlags = BuildModelClipFlags(*cache);

		vertex->rhw = 1.0f / cache->m_w;
		vertex->sx = cache->m_x * vertex->rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex->sy = cache->m_y * vertex->rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex->sz = cache->m_z * vertex->rhw;
		const LegoU8* sourceColor = reinterpret_cast<const LegoU8*>(&source->m_color);
		vertex->color = (sourceColor[3] << 24) | (sourceColor[0] << 16) | (sourceColor[1] << 8) | sourceColor[2];
		vertex->specular = m_unk0xc83fc;
		vertex->tu = source->m_u + m_unk0xc83a0;
		vertex->tv = source->m_v + m_unk0xc83a4;
	}
}

// STUB: GOLDP 0x1000dbb0
void GolD3DRenderDevice::FUN_1000dbb0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	{
		const GolVec3* position = m_unk0xc4c0c + p_firstVertex;
		const GolVec3* positionEnd = position + p_vertexCount;
		LegoU32* color = m_unk0xc4c14 + p_firstVertex;
		const GolVec2* uv = m_unk0xc4c10 + p_firstVertex;
		CommandVertex* commandVertex = m_unk0xc428c + p_outputFirst;

		while (position < positionEnd) {
			commandVertex->m_x = m_unk0xc8518->m_m[0][0] * position->m_x;
			commandVertex->m_y = m_unk0xc8518->m_m[0][1] * position->m_x;
			commandVertex->m_z = m_unk0xc8518->m_m[0][2] * position->m_x;

			commandVertex->m_x += m_unk0xc8518->m_m[1][0] * position->m_y;
			commandVertex->m_y += m_unk0xc8518->m_m[1][1] * position->m_y;
			commandVertex->m_z += m_unk0xc8518->m_m[1][2] * position->m_y;

			commandVertex->m_x += m_unk0xc8518->m_m[2][0] * position->m_z;
			commandVertex->m_y += m_unk0xc8518->m_m[2][1] * position->m_z;
			commandVertex->m_z += m_unk0xc8518->m_m[2][2] * position->m_z;

			commandVertex->m_x += m_unk0xc8518->m_m[3][0];
			commandVertex->m_y += m_unk0xc8518->m_m[3][1];
			commandVertex->m_z += m_unk0xc8518->m_m[3][2];

			LegoU32 sourceColor = *color;
			LegoU8* destColor = reinterpret_cast<LegoU8*>(&commandVertex->m_color);
			destColor[0] = static_cast<LegoU8>(sourceColor >> 16);
			destColor[1] = static_cast<LegoU8>(sourceColor >> 8);
			destColor[2] = static_cast<LegoU8>(sourceColor);
			destColor[3] = static_cast<LegoU8>(m_alpha);
			commandVertex->m_u = uv->m_x;
			commandVertex->m_v = uv->m_y;

			position++;
			uv++;
			color++;
			commandVertex++;
		}
	}

	m_unk0xc8540 = p_outputFirst;
	m_unk0xc8544 = p_firstVertex;
	m_unk0xc8548 = p_vertexCount;
	m_unk0xc8524->VTable0x10(&m_unk0xc8530);

	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	m_unk0xc3848 = cacheIndex + p_vertexCount;
	D3DTLVERTEX* vertex = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	CommandVertex* source = m_unk0xc428c + p_outputFirst;
	CommandVertex* sourceEnd = source + p_vertexCount;
	LegoU32 alpha = (m_alpha & 0xff) << 24;

	for (; source < sourceEnd; source++, cache++, vertex++, cacheIndex++) {
		const GolMatrix4& matrix = *m_unk0xc8490;
		cache->m_x = source->m_x * matrix.m_m[0][0] + source->m_y * matrix.m_m[1][0] + source->m_z * matrix.m_m[2][0] +
					 matrix.m_m[3][0];
		cache->m_y = source->m_x * matrix.m_m[0][1] + source->m_y * matrix.m_m[1][1] + source->m_z * matrix.m_m[2][1] +
					 matrix.m_m[3][1];
		cache->m_z = source->m_x * matrix.m_m[0][2] + source->m_y * matrix.m_m[1][2] + source->m_z * matrix.m_m[2][2] +
					 matrix.m_m[3][2];
		cache->m_w = source->m_x * matrix.m_m[0][3] + source->m_y * matrix.m_m[1][3] + source->m_z * matrix.m_m[2][3] +
					 matrix.m_m[3][3];
		cache->m_unk0x10 = cacheIndex;
		cache->m_clipFlags = BuildModelClipFlags(*cache);

		vertex->rhw = 1.0f / cache->m_w;
		vertex->sx = cache->m_x * vertex->rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex->sy = cache->m_y * vertex->rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex->sz = cache->m_z * vertex->rhw;
		const LegoU8* sourceColor = reinterpret_cast<const LegoU8*>(&source->m_color);
		vertex->color = alpha | (sourceColor[0] << 16) | (sourceColor[1] << 8) | sourceColor[2];
		vertex->specular = m_unk0xc83fc;
		vertex->tu = source->m_u + m_unk0xc83a0;
		vertex->tv = source->m_v + m_unk0xc83a4;
	}
}

// STUB: GOLDP 0x1000e010
void GolD3DRenderDevice::FUN_1000e010(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		LegoFloat x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
					  matrix.m_m[3][0];
		LegoFloat y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
					  matrix.m_m[3][1];
		LegoFloat z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
					  matrix.m_m[3][2];
		LegoFloat w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
					  matrix.m_m[3][3];
		LegoFloat rhw = 1.0f / w;
		D3DTLVERTEX& vertex = vertices[i];

		vertex.sx = x * rhw;
		vertex.sy = y * rhw;
		vertex.sz = z * rhw;
		vertex.rhw = rhw;
		vertex.color = m_unk0xc83fc;
		vertexMap[i + 1] = static_cast<LegoU16>(vertexMap[i] + 1);
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// STUB: GOLDP 0x1000e180
void GolD3DRenderDevice::FUN_1000e180(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		LegoFloat x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
					  matrix.m_m[3][0];
		LegoFloat y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
					  matrix.m_m[3][1];
		LegoFloat z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
					  matrix.m_m[3][2];
		LegoFloat w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
					  matrix.m_m[3][3];
		LegoFloat rhw = 1.0f / w;
		D3DTLVERTEX& vertex = vertices[i];

		vertex.sx = x * rhw;
		vertex.sy = y * rhw;
		vertex.sz = z * rhw;
		vertex.rhw = rhw;
		vertex.color = m_unk0xc83fc;
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y;
		vertexMap[i + 1] = static_cast<LegoU16>(vertexMap[i] + 1);
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// STUB: GOLDP 0x1000e310
void GolD3DRenderDevice::FUN_1000e310(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
						 matrix.m_m[3][0];
		cacheEntry.m_y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
						 matrix.m_m[3][1];
		cacheEntry.m_z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
						 matrix.m_m[3][2];
		cacheEntry.m_w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
						 matrix.m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc83fc;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000e540
void GolD3DRenderDevice::FUN_1000e540(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
						 matrix.m_m[3][0];
		cacheEntry.m_y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
						 matrix.m_m[3][1];
		cacheEntry.m_z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
						 matrix.m_m[3][2];
		cacheEntry.m_w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
						 matrix.m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc83fc;
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000e790
void GolD3DRenderDevice::FUN_1000e790(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		LegoFloat x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
					  matrix.m_m[3][0];
		LegoFloat y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
					  matrix.m_m[3][1];
		LegoFloat z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
					  matrix.m_m[3][2];
		LegoFloat w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
					  matrix.m_m[3][3];
		LegoFloat rhw = 1.0f / w;
		D3DTLVERTEX& vertex = vertices[i];

		vertex.sx = x * rhw;
		vertex.sy = y * rhw;
		vertex.sz = z * rhw;
		vertex.rhw = rhw;
		vertex.color = m_unk0xc83fc;
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x + m_unk0xc83a0;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y + m_unk0xc83a4;
		vertexMap[i + 1] = static_cast<LegoU16>(vertexMap[i] + 1);
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// STUB: GOLDP 0x1000e930
void GolD3DRenderDevice::FUN_1000e930(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_unk0xc8518;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_unk0xc4c0c[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * matrix.m_m[0][0] + source.m_y * matrix.m_m[1][0] + source.m_z * matrix.m_m[2][0] +
						 matrix.m_m[3][0];
		cacheEntry.m_y = source.m_x * matrix.m_m[0][1] + source.m_y * matrix.m_m[1][1] + source.m_z * matrix.m_m[2][1] +
						 matrix.m_m[3][1];
		cacheEntry.m_z = source.m_x * matrix.m_m[0][2] + source.m_y * matrix.m_m[1][2] + source.m_z * matrix.m_m[2][2] +
						 matrix.m_m[3][2];
		cacheEntry.m_w = source.m_x * matrix.m_m[0][3] + source.m_y * matrix.m_m[1][3] + source.m_z * matrix.m_m[2][3] +
						 matrix.m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_unk0xc8400[0] + m_unk0xc8400[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_unk0xc8400[1] + m_unk0xc8400[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc83fc;
		vertex.tu = m_unk0xc4c10[sourceIndex].m_x + m_unk0xc83a0;
		vertex.tv = m_unk0xc4c10[sourceIndex].m_y + m_unk0xc83a4;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000eb90
void GolD3DRenderDevice::FUN_1000eb90(undefined4 p_firstTriangle, undefined4 p_triangleCount, undefined4)
{
	DuskwindBananaRelic0x24* material = m_unk0xc8538;
	undefined4 firstTriangle = p_firstTriangle;
	m_unk0xc8560 = firstTriangle;
	m_unk0xc854c.m_material = material;
	m_unk0xc8564 = p_triangleCount;
	m_unk0xc8524->VTable0x0c(&m_unk0xc854c);
}

// FUNCTION: GOLDP 0x1000ebd0
void GolD3DRenderDevice::FUN_1000ebd0(LegoU32 p_firstTriangle, LegoU32 p_triangleCount, LegoU32 p_lastVertex)
{
	LegoU8* triangle = m_unk0xc4c18 + (p_firstTriangle * 4);
	LegoU8* end = m_unk0xc4c18 + ((p_firstTriangle + p_triangleCount) * 4);
	LegoU16* indices = m_unk0xc4c20;

	for (; triangle < end; triangle += 4) {
		LegoU32 index2 = triangle[2];
		LegoU32 index0 = triangle[0];
		LegoU32 index1 = triangle[1];
		D3DTLVERTEX* vertex2 = &m_unk0x348[index2];
		D3DTLVERTEX* vertex1 = &m_unk0x348[index1];
		D3DTLVERTEX* vertex0 = &m_unk0x348[index0];

		if (((vertex0->sy - vertex1->sy) * (vertex2->sx - vertex1->sx)) -
				((vertex2->sy - vertex1->sy) * (vertex0->sx - vertex1->sx)) <
			0.0f) {
			*indices++ = index2;
			*indices++ = index1;
			*indices++ = index0;
		}
	}

	if (indices != m_unk0xc4c20) {
		m_d3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			D3DFVF_TLVERTEX,
			m_unk0x348,
			p_lastVertex + 1,
			m_unk0xc4c20,
			indices - m_unk0xc4c20,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// FUNCTION: GOLDP 0x1000ece0
void GolD3DRenderDevice::FUN_1000ece0(LegoU32 p_firstTriangle, LegoU32 p_triangleCount, LegoU32 p_lastVertex)
{
	LegoU8* triangle = m_unk0xc4c18 + (p_firstTriangle * 4);
	LegoU8* end = m_unk0xc4c18 + ((p_firstTriangle + p_triangleCount) * 4);
	LegoU16* indices = m_unk0xc4c20;

	for (; triangle < end; triangle += 4) {
		LegoU32 index2 = triangle[2];
		LegoU32 index0 = triangle[0];
		LegoU32 index1 = triangle[1];
		D3DTLVERTEX* vertex2 = &m_unk0x348[index2];
		D3DTLVERTEX* vertex1 = &m_unk0x348[index1];
		D3DTLVERTEX* vertex0 = &m_unk0x348[index0];

		if (((vertex0->sy - vertex1->sy) * (vertex2->sx - vertex1->sx)) -
				((vertex2->sy - vertex1->sy) * (vertex0->sx - vertex1->sx)) >
			0.0f) {
			*indices++ = index2;
			*indices++ = index1;
			*indices++ = index0;
		}
	}

	if (indices != m_unk0xc4c20) {
		m_d3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			D3DFVF_TLVERTEX,
			m_unk0x348,
			p_lastVertex + 1,
			m_unk0xc4c20,
			indices - m_unk0xc4c20,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// STUB: GOLDP 0x1000edf0
void GolD3DRenderDevice::FUN_1000edf0(undefined4 p_firstTriangle, undefined4 p_triangleCount, undefined4 p_lastVertex)
{
	STUB(0x1000edf0);
	if ((m_unk0xc83c8 | m_unk0xc83cc) & DuskwindBananaRelic0x24::c_flag0x08Bit14) {
		FUN_1000ece0(p_firstTriangle, p_triangleCount, p_lastVertex);
	}
	else {
		FUN_1000ebd0(p_firstTriangle, p_triangleCount, p_lastVertex);
	}
}

// STUB: GOLDP 0x10010330
void GolD3DRenderDevice::FUN_10010330(undefined4, undefined4, undefined4)
{
	STUB(0x10010330);
}

// STUB: GOLDP 0x10010500
void GolD3DRenderDevice::FUN_10010500(undefined4, undefined4, undefined4)
{
	STUB(0x10010500);
}

// STUB: GOLDP 0x100106d0
void GolD3DRenderDevice::FUN_100106d0(undefined4, undefined4, undefined4)
{
	STUB(0x100106d0);
}

// FUNCTION: GOLDP 0x10011e60
void GolD3DRenderDevice::FUN_10011e60(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 color = m_unk0xc857c;
	LegoU32 red = m_unk0xc8570;
	color <<= 8;
	LegoU32 blue = m_unk0xc8578;
	LegoU32 firstVertex = p_firstVertex;
	color |= red;
	LegoU32 green = m_unk0xc8574;
	color <<= 8;
	color |= green;
	LegoU32 endIndex = firstVertex + vertexCount;
	color <<= 8;
	color |= blue;

	LegoU32* first = m_unk0xc4c14 + firstVertex;
	LegoU32* end = m_unk0xc4c14 + endIndex;
	for (; first < end; first++) {
		*first = color;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x10011ed0
void GolD3DRenderDevice::FUN_10011ed0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;
	LegoU32* color = m_unk0xc4c14 + firstVertex;
	LegoU32* colorEnd = color + vertexCount;
	const GolVec3* normal = m_unk0xc4c1c + firstVertex;
	LegoS32 baseRed = static_cast<LegoS32>(m_unk0xc8570);
	LegoS32 baseGreen = static_cast<LegoS32>(m_unk0xc8574);
	LegoS32 baseBlue = static_cast<LegoS32>(m_unk0xc8578);
	LegoU32 alpha = m_unk0xc857c << 8;

	for (; color < colorEnd; color++, normal++) {
		LegoFloat intensity =
			normal->m_z * m_unk0xc8644[0].m_z + normal->m_y * m_unk0xc8644[0].m_y + normal->m_x * m_unk0xc8644[0].m_x;
		LegoS32 red = baseRed - static_cast<LegoS32>(m_unk0xc859c[0].m_red * intensity);
		LegoS32 green = baseGreen - static_cast<LegoS32>(m_unk0xc859c[0].m_grn * intensity);
		LegoS32 blue = baseBlue - static_cast<LegoS32>(m_unk0xc859c[0].m_blu * intensity);

		red = ClampModelColorChannel(red, baseRed);
		green = ClampModelColorChannel(green, baseGreen);
		blue = ClampModelColorChannel(blue, baseBlue);
		LegoU32 finalColor = alpha | red;
		finalColor <<= 8;
		finalColor |= green;
		finalColor <<= 8;
		finalColor |= blue;
		*color = finalColor;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x10012030
void GolD3DRenderDevice::FUN_10012030(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;

	for (LegoU32 i = 0; i < vertexCount; i++) {
		LegoU32 sourceIndex = firstVertex + i;
		const GolVec3& normal = m_unk0xc4c1c[sourceIndex];
		LegoS32 red = static_cast<LegoS32>(m_unk0xc8570);
		LegoS32 green = static_cast<LegoS32>(m_unk0xc8574);
		LegoS32 blue = static_cast<LegoS32>(m_unk0xc8578);

		for (LegoU32 lightIndex = 0; lightIndex < 2; lightIndex++) {
			LegoFloat intensity = normal.m_x * m_unk0xc8644[lightIndex].m_x +
								  normal.m_y * m_unk0xc8644[lightIndex].m_y + normal.m_z * m_unk0xc8644[lightIndex].m_z;
			red -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_red * intensity);
			green -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_grn * intensity);
			blue -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_blu * intensity);
		}

		red = ClampModelColorChannel(red, static_cast<LegoS32>(m_unk0xc8570));
		green = ClampModelColorChannel(green, static_cast<LegoS32>(m_unk0xc8574));
		blue = ClampModelColorChannel(blue, static_cast<LegoS32>(m_unk0xc8578));
		m_unk0xc4c14[sourceIndex] = ((m_unk0xc857c & 0xff) << 24) | (red << 16) | (green << 8) | blue;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x100121e0
void GolD3DRenderDevice::FUN_100121e0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;

	for (LegoU32 i = 0; i < vertexCount; i++) {
		LegoU32 sourceIndex = firstVertex + i;
		const GolVec3& normal = m_unk0xc4c1c[sourceIndex];
		LegoS32 red = static_cast<LegoS32>(m_unk0xc8570);
		LegoS32 green = static_cast<LegoS32>(m_unk0xc8574);
		LegoS32 blue = static_cast<LegoS32>(m_unk0xc8578);

		for (LegoU32 lightIndex = 0; lightIndex < 3; lightIndex++) {
			LegoFloat intensity = normal.m_x * m_unk0xc8644[lightIndex].m_x +
								  normal.m_y * m_unk0xc8644[lightIndex].m_y + normal.m_z * m_unk0xc8644[lightIndex].m_z;
			red -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_red * intensity);
			green -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_grn * intensity);
			blue -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_blu * intensity);
		}

		red = ClampModelColorChannel(red, static_cast<LegoS32>(m_unk0xc8570));
		green = ClampModelColorChannel(green, static_cast<LegoS32>(m_unk0xc8574));
		blue = ClampModelColorChannel(blue, static_cast<LegoS32>(m_unk0xc8578));
		m_unk0xc4c14[sourceIndex] = ((m_unk0xc857c & 0xff) << 24) | (red << 16) | (green << 8) | blue;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x100123e0
void GolD3DRenderDevice::FUN_100123e0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;

	for (LegoU32 i = 0; i < vertexCount; i++) {
		LegoU32 sourceIndex = firstVertex + i;
		const GolVec3& normal = m_unk0xc4c1c[sourceIndex];
		LegoS32 red = static_cast<LegoS32>(m_unk0xc8570);
		LegoS32 green = static_cast<LegoS32>(m_unk0xc8574);
		LegoS32 blue = static_cast<LegoS32>(m_unk0xc8578);

		for (LegoU32 lightIndex = 0; lightIndex < 4; lightIndex++) {
			LegoFloat intensity = normal.m_x * m_unk0xc8644[lightIndex].m_x +
								  normal.m_y * m_unk0xc8644[lightIndex].m_y + normal.m_z * m_unk0xc8644[lightIndex].m_z;
			red -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_red * intensity);
			green -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_grn * intensity);
			blue -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_blu * intensity);
		}

		red = ClampModelColorChannel(red, static_cast<LegoS32>(m_unk0xc8570));
		green = ClampModelColorChannel(green, static_cast<LegoS32>(m_unk0xc8574));
		blue = ClampModelColorChannel(blue, static_cast<LegoS32>(m_unk0xc8578));
		m_unk0xc4c14[sourceIndex] = ((m_unk0xc857c & 0xff) << 24) | (red << 16) | (green << 8) | blue;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x10012640
void GolD3DRenderDevice::FUN_10012640(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;

	for (LegoU32 i = 0; i < vertexCount; i++) {
		LegoU32 sourceIndex = firstVertex + i;
		const GolVec3& normal = m_unk0xc4c1c[sourceIndex];
		LegoS32 red = static_cast<LegoS32>(m_unk0xc8570);
		LegoS32 green = static_cast<LegoS32>(m_unk0xc8574);
		LegoS32 blue = static_cast<LegoS32>(m_unk0xc8578);

		for (LegoU32 lightIndex = 0; lightIndex < 5; lightIndex++) {
			LegoFloat intensity = normal.m_x * m_unk0xc8644[lightIndex].m_x +
								  normal.m_y * m_unk0xc8644[lightIndex].m_y + normal.m_z * m_unk0xc8644[lightIndex].m_z;
			red -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_red * intensity);
			green -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_grn * intensity);
			blue -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_blu * intensity);
		}

		red = ClampModelColorChannel(red, static_cast<LegoS32>(m_unk0xc8570));
		green = ClampModelColorChannel(green, static_cast<LegoS32>(m_unk0xc8574));
		blue = ClampModelColorChannel(blue, static_cast<LegoS32>(m_unk0xc8578));
		m_unk0xc4c14[sourceIndex] = ((m_unk0xc857c & 0xff) << 24) | (red << 16) | (green << 8) | blue;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x100128f0
void GolD3DRenderDevice::FUN_100128f0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;

	for (LegoU32 i = 0; i < vertexCount; i++) {
		LegoU32 sourceIndex = firstVertex + i;
		const GolVec3& normal = m_unk0xc4c1c[sourceIndex];
		LegoS32 red = static_cast<LegoS32>(m_unk0xc8570);
		LegoS32 green = static_cast<LegoS32>(m_unk0xc8574);
		LegoS32 blue = static_cast<LegoS32>(m_unk0xc8578);

		for (LegoU32 lightIndex = 0; lightIndex < 6; lightIndex++) {
			LegoFloat intensity = normal.m_x * m_unk0xc8644[lightIndex].m_x +
								  normal.m_y * m_unk0xc8644[lightIndex].m_y + normal.m_z * m_unk0xc8644[lightIndex].m_z;
			red -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_red * intensity);
			green -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_grn * intensity);
			blue -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_blu * intensity);
		}

		red = ClampModelColorChannel(red, static_cast<LegoS32>(m_unk0xc8570));
		green = ClampModelColorChannel(green, static_cast<LegoS32>(m_unk0xc8574));
		blue = ClampModelColorChannel(blue, static_cast<LegoS32>(m_unk0xc8578));
		m_unk0xc4c14[sourceIndex] = ((m_unk0xc857c & 0xff) << 24) | (red << 16) | (green << 8) | blue;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x10012bf0
void GolD3DRenderDevice::FUN_10012bf0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;

	for (LegoU32 i = 0; i < vertexCount; i++) {
		LegoU32 sourceIndex = firstVertex + i;
		const GolVec3& normal = m_unk0xc4c1c[sourceIndex];
		LegoS32 red = static_cast<LegoS32>(m_unk0xc8570);
		LegoS32 green = static_cast<LegoS32>(m_unk0xc8574);
		LegoS32 blue = static_cast<LegoS32>(m_unk0xc8578);

		for (LegoU32 lightIndex = 0; lightIndex < 7; lightIndex++) {
			LegoFloat intensity = normal.m_x * m_unk0xc8644[lightIndex].m_x +
								  normal.m_y * m_unk0xc8644[lightIndex].m_y + normal.m_z * m_unk0xc8644[lightIndex].m_z;
			red -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_red * intensity);
			green -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_grn * intensity);
			blue -= static_cast<LegoS32>(m_unk0xc859c[lightIndex].m_blu * intensity);
		}

		red = ClampModelColorChannel(red, static_cast<LegoS32>(m_unk0xc8570));
		green = ClampModelColorChannel(green, static_cast<LegoS32>(m_unk0xc8574));
		blue = ClampModelColorChannel(blue, static_cast<LegoS32>(m_unk0xc8578));
		m_unk0xc4c14[sourceIndex] = ((m_unk0xc857c & 0xff) << 24) | (red << 16) | (green << 8) | blue;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// FUNCTION: GOLDP 0x10012f50
void GolD3DRenderDevice::FUN_10012f50()
{
	if (m_unk0xc8524) {
		if (m_unk0xc8528) {
			m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000eb90;
			if (m_unk0xc8568) {
				m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000d210;
				return;
			}
			if (m_unk0xc83ec) {
				m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000d5d0;
				return;
			}

			m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000d440;
			return;
		}

		if (m_unk0xc83c4) {
			m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_100106d0;
		}
		else {
			m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000edf0;
		}

		if (m_unk0xc83ec) {
			m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000dbb0;
		}
		else {
			m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000d760;
		}
	}
	else {
		LegoU32 index = m_unk0xc83f8;
		index <<= 3;
		index |= m_unk0xc83e8;
		index <<= 1;
		index |= m_unk0xc83f4;
		index <<= 1;
		index |= (m_flags >> 9) & 0x10;
		index |= m_unk0xc83ec;

		if (m_unk0xc83e4) {
			if (m_unk0xc83c4) {
				m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_100106d0;
				if (!m_unk0xc83e8 && m_unk0xc8700 == 0) {
					m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_100132f0;
					return;
				}
			}
			else {
				m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000edf0;
			}

			index |= 8;
		}
		else {
			LegoU32 flags = m_unk0xc83c8 | m_unk0xc83cc;
			if (flags & DuskwindBananaRelic0x24::c_flag0x08Bit14) {
				if (m_unk0xc83c4) {
					m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_10010500;
				}
				else {
					m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000ece0;
				}
			}
			else if (m_unk0xc83c4) {
				m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_10010330;
				if (!m_unk0xc83e8 && m_unk0xc8700 == 0) {
					m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_10013110;
					return;
				}
			}
			else {
				m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000ebd0;
			}
		}

		if (m_unk0xc8568) {
			m_drawTriangleFn1 = g_unk0x1005c8a8[m_unk0x11c];
			m_drawTriangleFn0 = g_unk0x1005c8c8[index];
		}
		else {
			m_drawTriangleFn1 = g_unk0x1005c8c8[index];
		}
	}
}

// STUB: GOLDP 0x10013110
void GolD3DRenderDevice::FUN_10013110(undefined4, undefined4, undefined4)
{
	STUB(0x10013110);
}

// STUB: GOLDP 0x100132f0
void GolD3DRenderDevice::FUN_100132f0(undefined4, undefined4, undefined4)
{
	STUB(0x100132f0);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolD3DRenderDevice::VTable0x38()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolD3DRenderDevice::VTable0xd0()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolD3DRenderDevice::VTable0x34(LegoS32, const LegoFloat*)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GolD3DRenderDevice::VTable0xec(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolD3DRenderDevice::VTable0xf4()
{
	// empty
}
