#include "bronzefalcon0xc8770.h"

#include "amberlens0x344.h"
#include "bronzefalconsurface0x5c.h"
#include "falcondunebag0x10.h"
#include "falcontextureformat.h"
#include "golddune0x38.h"
#include "goldrawdpstate.h"
#include "golerror.h"
#include "purpledune0x7c.h"
#include "rectangle.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(BronzeFalcon0xc8770, 0xc8770)
DECOMP_SIZE_ASSERT(BronzeFalcon0xc8770::TextureFormat, 0x18)
DECOMP_SIZE_ASSERT(BronzeFalcon0xc8770::Field0xc83b4, 0x10)
DECOMP_SIZE_ASSERT(ColorRGBA, 0x4)
DECOMP_SIZE_ASSERT(D3DTLVERTEX, 0x20)
DECOMP_SIZE_ASSERT(Rect, 0x10)

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
BronzeFalconDrawFunction BronzeFalcon0xc8770::g_unk0x1005c8a8[8] = {
	&BronzeFalcon0xc8770::FUN_10011e60,
	&BronzeFalcon0xc8770::FUN_10011ed0,
	&BronzeFalcon0xc8770::FUN_10012030,
	&BronzeFalcon0xc8770::FUN_100121e0,
	&BronzeFalcon0xc8770::FUN_100123e0,
	&BronzeFalcon0xc8770::FUN_10012640,
	&BronzeFalcon0xc8770::FUN_100128f0,
	&BronzeFalcon0xc8770::FUN_10012bf0,
};

// GLOBAL: GOLDP 0x1005c8c8
BronzeFalconDrawFunction BronzeFalcon0xc8770::g_unk0x1005c8c8[8] = {
	&BronzeFalcon0xc8770::FUN_1000c160,
	&BronzeFalcon0xc8770::FUN_1000c2d0,
	&BronzeFalcon0xc8770::FUN_1000bfb0,
	&BronzeFalcon0xc8770::FUN_1000c470,
	&BronzeFalcon0xc8770::FUN_1000be20,
	&BronzeFalcon0xc8770::FUN_1000c2d0,
	&BronzeFalcon0xc8770::FUN_1000bfb0,
	&BronzeFalcon0xc8770::FUN_1000c470,
};

// FUNCTION: GOLDP 0x100078e0
BronzeFalcon0xc8770::BronzeFalcon0xc8770()
{
	Reset();
}

// FUNCTION: GOLDP 0x10007980
BronzeFalcon0xc8770::~BronzeFalcon0xc8770()
{
	VTable0x18();
}

// FUNCTION: GOLDP 0x10007a00
void BronzeFalcon0xc8770::Reset()
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
	m_unk0x2cc.m_alp = 0;
	m_unk0x2cc.m_red = 0;
	m_unk0x2cc.m_grn = 0;
	m_unk0x2cc.m_blu = 0;
	m_unk0x2d0 = 0;
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
	m_unk0xc876c = &BronzeFalcon0xc8770::FUN_1000a2c0;
	m_unk0xc83f4 = 0;
	m_unk0xc83a0 = 0;
	m_unk0xc83a4 = 0;
	m_unk0xc83a8 = 0;
	m_unk0xc83c8 = 0;
	m_unk0xc83cc = 0;
	m_unk0xc83e0 = 255;
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
	::memset(m_unk0xc854c, 0, sizeof(m_unk0xc854c));
	m_unk0xc8530 = this;
	m_unk0xc853c = m_unk0xc428c;
	m_unk0xc8538 = NULL;
	m_unk0xc854c[0] = this;
	m_unk0xc854c[3] = m_unk0xc428c;
	m_unk0xc8410._11 = 1.0f;
	m_unk0xc8450._11 = 1.0f;
	m_unk0xc8410._12 = 0.0f;
	m_unk0xc8450._12 = 0.0f;
	m_unk0xc8410._13 = 0.0f;
	m_unk0xc8450._13 = 0.0f;
	m_unk0xc8410._14 = 0.0f;
	m_unk0xc8450._14 = 0.0f;
	m_unk0xc8410._21 = 0.0f;
	m_unk0xc8450._21 = 0.0f;
	m_unk0xc8410._22 = 1.0f;
	m_unk0xc8450._22 = 1.0f;
	m_unk0xc8410._23 = 0.0f;
	m_unk0xc8450._23 = 0.0f;
	m_unk0xc8410._24 = 0.0f;
	m_unk0xc8450._24 = 0.0f;
	m_unk0xc8410._31 = 0.0f;
	m_unk0xc8450._31 = 0.0f;
	m_unk0xc8410._32 = 0.0f;
	m_unk0xc8450._32 = 0.0f;
	m_unk0xc8410._33 = 1.0f;
	m_unk0xc8450._33 = 1.0f;
	m_unk0xc8410._34 = 0.0f;
	m_unk0xc8450._34 = 0.0f;
	m_unk0xc8410._41 = 0.0f;
	m_unk0xc8450._41 = 0.0f;
	m_unk0xc8410._42 = 0.0f;
	m_unk0xc8450._42 = 0.0f;
	m_unk0xc8410._43 = 0.0f;
	m_unk0xc8450._43 = 0.0f;
	m_unk0xc8410._44 = 1.0f;
	m_unk0xc8450._44 = 1.0f;
	m_unk0xc8764 = &BronzeFalcon0xc8770::FUN_1000c630;
	m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_1000edf0;

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
GolCommonDrawState* BronzeFalcon0xc8770::GetDrawState()
{
	return m_drawState;
}

// FUNCTION: GOLDP 0x10007d90
undefined4 BronzeFalcon0xc8770::FUN_10007d90(GolDrawDPState* p_drawState, SlatePeak0x58* p_parg2, LegoU32 p_flags)
{
	if (m_unk0x04 & c_flagBit0) {
		VTable0x18();
	}

	m_drawState = p_drawState;
	m_unk0x304 = p_parg2;
	m_renderTargetInfo = p_parg2;
	m_unk0x0c = NULL;
	p_drawState->AddRenderer(this);
	m_unk0x04 |= c_flagBit0 | c_flagBit5;
	m_viewportParams.dwX = 0;
	m_viewportParams.dwY = 0;
	m_viewportParams.dwWidth = m_renderTargetInfo->m_width;
	m_viewportParams.dwHeight = m_renderTargetInfo->m_height;

	undefined4 result = FUN_10007e20(p_flags);
	if (result != 0) {
		return result;
	}

	VTable0x28();
	return 0;
}

// FUNCTION: GOLDP 0x10007e20
undefined4 BronzeFalcon0xc8770::FUN_10007e20(LegoU32 p_flags)
{
	FalconTextureFormat swTextureFormat;
	LegoU32 forceSoftware;
	LegoChar errorMessage[64];
	D3DDEVICEDESC helCaps;

	m_unk0x04 = c_flagBit0 | c_flagBit5;
	if (p_flags & GolDrawState::c_flagBit21) {
		m_unk0x04 |= c_flagBit20;
	}
	if (p_flags & GolDrawState::c_flagBit12) {
		m_unk0x04 |= c_flagBit1;
	}

	forceSoftware = p_flags & GolDrawState::c_flagBit16;
	if (!forceSoftware) {
		m_unk0xc384c = 0;
		m_unk0xc83c4 = 0;
		m_unk0xc876c = &BronzeFalcon0xc8770::FUN_1000a2c0;

		if (m_unk0x04 & c_flagBit1 && !m_drawState->VTable0x98()) {
			undefined4 r = m_depthBuffer.Create(m_drawState, m_unk0x304);
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

			if ((m_unk0x04 & c_flagBit20) && (m_d3dDeviceDesc.dpcTriCaps.dwAlphaCmpCaps & D3DPCMPCAPS_GREATER)) {
				m_unk0x04 &= ~c_flagBit7;
				m_unk0x04 |= c_flagBit8;
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_TRANSPARENCY) {
				m_unk0x04 &= ~(c_flagBit7 | c_flagBit8);
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwAlphaCmpCaps & D3DPCMPCAPS_GREATER) {
				m_unk0x04 &= ~c_flagBit7;
				m_unk0x04 |= c_flagBit8;
			}
			else {
				m_unk0x04 &= ~c_flagBit8;
				m_unk0x04 |= c_flagBit7;
			}

			if (m_d3dDeviceDesc.dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATBLEND) {
				m_unk0x04 &= ~c_flagBit12;
				m_unk0x04 |= c_flagBit11;
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATSTIPPLED) {
				m_unk0x04 |= c_flagBit11 | c_flagBit12;
			}
			else {
				m_unk0x04 &= ~c_flagBit12;
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

			m_textureFormats = new FalconTextureFormat[m_countTextureFormats];
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

	m_unk0x04 &= ~c_flagBit1;
	m_unk0x04 |= c_flagBit9 | c_flagBit16;
	m_unk0xc384c = -1;
	m_unk0xc83c4 = 1;
	m_unk0xc876c = &BronzeFalcon0xc8770::FUN_1000a950;
	::memcpy(&swTextureFormat, &m_unk0x304->m_textureFormat, sizeof(swTextureFormat));

	SoftwareRenderer0x58::PixelFormat swPixelFormat;
	if (swTextureFormat.m_bitsPerPixel == 8) {
		swPixelFormat = SoftwareRenderer0x58::PixelFormat::e_formatIndex8;
		if (m_drawState->m_flags & GolDrawState::c_flagBit18) {
			m_unk0xc8700 = 1;
		}
		else {
			m_unk0xc8700 = 0;
		}
	}
	else {
		swPixelFormat = swTextureFormat.GetGreenBitCount() == 6 ? SoftwareRenderer0x58::PixelFormat::e_format565
																: SoftwareRenderer0x58::PixelFormat::e_format555;
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
	VTable0x1c(m_unk0x2cc);
	FUN_100082e0();
	if (m_unk0x0c != NULL) {
		VTable0x20(m_unk0x0c);
	}

	m_unk0x2d4.FUN_10006320(*this);
	for (BronzeFalconSurface0x5c* surface = m_unk0x30c; surface != NULL; surface = surface->m_next) {
		surface->FUN_100136a0(this);
	}

	WhiteFalcon0x140::RestoreResources();
	return 0;
}

// FUNCTION: GOLDP 0x100082e0
void BronzeFalcon0xc8770::FUN_100082e0()
{
	m_unk0xc83f0 = FALSE;
	m_unk0xc83ec = 0;
	m_unk0xc83e8 = FALSE;
	if (m_unk0x04 & c_flagBit19) {
		m_unk0xc83fc = ARGBU32(m_unk0xc83e0, m_unk0x118.m_red, m_unk0x118.m_grn, m_unk0x118.m_blu);
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

	if (m_unk0x04 & c_flagBit16) {
		return;
	}

	m_d3dDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_TEXTUREPERSPECTIVE,
		m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE
	);

	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_SUBPIXEL,
		(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_SUBPIXEL) && m_drawState->VTable0x60()
	);

	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_DITHERENABLE,
		(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_DITHER) && m_drawState->VTable0x60()
	);

	m_d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP);
	if ((m_drawState->m_flags & GolDrawState::c_flagBit3) && m_drawState->VTable0x60()) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS, D3DANTIALIAS_SORTINDEPENDENT);
	}
	else {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS, D3DANTIALIAS_NONE);
	}

	if ((m_d3dDeviceDesc.dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_LINEAR) && m_drawState->VTable0x60()) {
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
	}
	else {
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
	}

	if (m_unk0x04 & c_flagBit1) {
		if (m_drawState->VTable0x94()) {
			m_unk0x04 |= c_flagBit13;
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_USEW);
		}
		else {
			m_unk0x04 &= ~c_flagBit13;
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		}

		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
		m_unk0x04 |= c_flagBit5;
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
void BronzeFalcon0xc8770::ReleaseResources()
{
	WhiteFalcon0x140::ReleaseResources();

	for (BronzeFalconSurface0x5c* surface = m_unk0x30c; surface != NULL; surface = surface->m_next) {
		surface->FUN_100137d0();
	}

	m_unk0x2d4.Destroy();

	if (m_unk0x04 & c_flagBit16) {
		m_softwareRenderer.~SoftwareRenderer0x58();
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
void BronzeFalcon0xc8770::VTable0x18()
{
	if (m_unk0x0c != NULL) {
		m_unk0x0c->FUN_10001f60(NULL);
		m_unk0x0c = NULL;
	}

	WhiteFalcon0x140::Destroy();
	ReleaseResources();

	BronzeFalconSurface0x5c* surface = m_unk0x30c;
	while (surface != NULL) {
		BronzeFalconSurface0x5c* next = surface->m_next;
		surface->VTable0x34();
		delete surface;
		surface = next;
	}

	if (m_drawState != NULL) {
		m_drawState->RemoveRenderer(this);
	}

	Reset();
	m_unk0x04 = 0;
}

// FUNCTION: GOLDP 0x100087b0
void BronzeFalcon0xc8770::VTable0x20(AmberLens0x344* p_lens)
{
	if (m_unk0x0c != NULL) {
		m_unk0x0c->FUN_10001f60(NULL);
	}

	m_unk0x0c = p_lens;
	p_lens->FUN_10001f60(this);
}

// FUNCTION: GOLDP 0x100087e0
void BronzeFalcon0xc8770::VTable0x5c()
{
	AmberLens0x344* lens = m_unk0x0c;
	lens->VTable0x28();
	lens->FUN_10002860(&m_viewportParams);

	if (!(m_unk0x04 & c_flagBit16) && m_d3dViewport->SetViewport2(&m_viewportParams) != D3D_OK) {
		GOL_FATALERROR_MESSAGE("Unable to set viewport");
	}

	m_unk0xc8490 = lens->m_unk0x120.m_unk0x190;
	m_unk0xc8494 = lens->m_unk0x120.m_unk0x1d0;
	::memcpy(m_unk0x4c, lens->m_unk0x34, sizeof(m_unk0x4c));
	::memcpy(m_unk0xc8400, &lens->m_unk0x120.m_unk0x210, sizeof(m_unk0xc8400));
}

// STUB: GOLDP 0x10008910
void BronzeFalcon0xc8770::VTable0x94(undefined4)
{
	STUB(0x10008910);
}

// STUB: GOLDP 0x10008a50
void BronzeFalcon0xc8770::VTable0xac(undefined4, undefined4)
{
	STUB(0x10008a50);
}

// STUB: GOLDP 0x10008c30
void BronzeFalcon0xc8770::VTable0xb0(undefined4, undefined4)
{
	STUB(0x10008c30);
}

// STUB: GOLDP 0x10008dd0
void BronzeFalcon0xc8770::VTable0x8c(undefined4, undefined4, undefined4)
{
	STUB(0x10008dd0);
}

// STUB: GOLDP 0x10008f70
void BronzeFalcon0xc8770::VTable0xa8(undefined4, undefined4, undefined4)
{
	STUB(0x10008f70);
}

// STUB: GOLDP 0x100090b0
void BronzeFalcon0xc8770::VTable0x88(undefined4, undefined4, undefined4)
{
	STUB(0x100090b0);
}

// STUB: GOLDP 0x10009240
void BronzeFalcon0xc8770::VTable0x9c(undefined4, undefined4, undefined4)
{
	STUB(0x10009240);
}

// STUB: GOLDP 0x10009270
void BronzeFalcon0xc8770::VTable0x98(undefined4, undefined4, undefined4)
{
	STUB(0x10009270);
}

// STUB: GOLDP 0x100092a0
void BronzeFalcon0xc8770::VTable0x90()
{
	STUB(0x100092a0);
}

// FUNCTION: GOLDP 0x10009420
void BronzeFalcon0xc8770::VTable0x54(undefined4 p_flags)
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
			if (m_unk0x04 & c_flagBit1) {
				clearFlags |= 2;
			}

			m_d3dViewport->Clear(1, &rect, clearFlags);
		}
		else if (p_flags & 0x01) {
			m_renderTargetInfo->Fill(m_unk0x2d0);
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
void BronzeFalcon0xc8770::VTable0xf0()
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
void BronzeFalcon0xc8770::VTable0x1c(const ColorRGBA& p_color)
{
	FalconTextureFormat textureFormat;

	m_unk0x2cc = p_color;
	if (m_unk0x04 & c_flagBit16) {
		textureFormat = m_renderTargetInfo->m_textureFormat;
		if (textureFormat.m_paletteMask != 0) {
			m_unk0x2d0 = m_renderTargetInfo->GetPalette()->FindEntry(m_unk0x2cc);
		}
		else {
			m_unk0x2d0 = textureFormat.MapRGBA(m_unk0x2cc);
		}
	}
	else {
		float c = static_cast<float>(static_cast<double>(p_color.m_red) / 255.0);
		m_materialParams.ambient.r = c;
		m_materialParams.diffuse.r = c;
		c = static_cast<float>(static_cast<double>(p_color.m_grn) / 255.0);
		m_materialParams.ambient.g = c;
		m_materialParams.diffuse.g = c;
		c = static_cast<float>(static_cast<double>(p_color.m_blu) / 255.0);
		m_materialParams.ambient.b = c;
		m_materialParams.diffuse.b = c;
		m_backgroundMaterial->SetMaterial(&m_materialParams);
		m_backgroundMaterial->GetHandle(m_d3dDevice, &m_backgroundMaterialHandle);
		m_d3dViewport->SetBackground(m_backgroundMaterialHandle);
	}
}

// FUNCTION: GOLDP 0x10009780
void BronzeFalcon0xc8770::VTable0xd8()
{
	if (!m_unk0xc83c4) {
		if (!m_drawState->VTable0x60()) {
			m_d3dDevice->SetRenderState(
				D3DRENDERSTATE_TEXTUREPERSPECTIVE,
				(m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE) ? TRUE : FALSE
			);
		}
	}
}

// FUNCTION: GOLDP 0x100097c0
void BronzeFalcon0xc8770::VTable0xd4()
{
	if (!m_unk0xc83c4) {
		if (!m_drawState->VTable0x60()) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, FALSE);
		}
	}
}

// FUNCTION: GOLDP 0x100097f0
void BronzeFalcon0xc8770::VTable0xdc()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(
			D3DRENDERSTATE_DITHERENABLE,
			(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_DITHER) && m_drawState->VTable0x60() ? TRUE
																										   : FALSE
		);
	}
}

// FUNCTION: GOLDP 0x10009840
void BronzeFalcon0xc8770::VTable0xe0()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, FALSE);
	}
}

// FUNCTION: GOLDP 0x10009860
void BronzeFalcon0xc8770::VTable0xe4()
{
	if (!m_unk0xc83c4 && (m_unk0x04 & c_flagBit1)) {
		if (m_drawState->VTable0x94()) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_USEW);
		}
		else {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		}

		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
	}

	m_unk0x04 |= c_flagBit5;
}

// FUNCTION: GOLDP 0x100098d0
void BronzeFalcon0xc8770::VTable0xe8(LegoBool32 p_arg)
{
	m_unk0x04 &= ~c_flagBit5;

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
LPDIRECT3D3 BronzeFalcon0xc8770::GetDirect3D3() const
{
	return m_drawState->m_d3d3;
}

// FUNCTION: GOLDP 0x10009940
LPDIRECTDRAW4 BronzeFalcon0xc8770::GetDirectDraw4() const
{
	return m_drawState->m_ddraw4;
}

// FUNCTION: GOLDP 0x10009950
const SlatePeak0x58* BronzeFalcon0xc8770::GetRenderTargetInfo()
{
	return m_renderTargetInfo;
}

// FUNCTION: GOLDP 0x10009960
undefined4 BronzeFalcon0xc8770::VTable0x7c(
	UtopianPan0xa4* p_image,
	undefined4 p_unk0x08,
	Rect* p_destRect,
	Rect* p_sourceRect,
	undefined4 p_unk0x14
)
{
	return p_image->FUN_10005510(this, p_unk0x08, p_destRect, p_sourceRect, p_unk0x14);
}

// FUNCTION: GOLDP 0x10009990
void BronzeFalcon0xc8770::VTable0x78(
	UtopianPan0xa4* p_image,
	undefined4 p_unk0x08,
	Rect* p_destRect,
	undefined4 p_unk0x14
)
{
	p_image->FUN_100054d0(this, p_unk0x08, p_destRect, p_unk0x14);
}

// FUNCTION: GOLDP 0x100099b0
void BronzeFalcon0xc8770::VTable0x74(
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
void BronzeFalcon0xc8770::VTable0x70(
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
void BronzeFalcon0xc8770::VTable0xb4()
{
	STUB(0x10009a70);
}

// STUB: GOLDP 0x10009b40
void BronzeFalcon0xc8770::VTable0x68()
{
	STUB(0x10009b40);
}

// STUB: GOLDP 0x10009b70
void BronzeFalcon0xc8770::VTable0x64()
{
	STUB(0x10009b70);
}

// STUB: GOLDP 0x10009ba0
void BronzeFalcon0xc8770::VTable0x6c()
{
	STUB(0x10009ba0);
}

// FUNCTION: GOLDP 0x10009bd0
void BronzeFalcon0xc8770::DrawRectangle(
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
void BronzeFalcon0xc8770::DrawTriangle(
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
			SoftwareRenderer0x58::Command0x14* cmd = m_unk0xc86f0 + commandIndex;
			m_unk0xc86f4 = nextCommandIndex;
			cmd->m_unk0x08 = m_unk0xc3848++;
			cmd->m_unk0x0a = m_unk0xc3848++;
			cmd->m_unk0x0c = m_unk0xc3848++;
			cmd->m_unk0x10 = m_unk0xc83b4.m_unk0x00[0];
			if (m_unk0x04 & c_flagBit5) {
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

// FUNCTION: GOLDP 0x1000a110
void BronzeFalcon0xc8770::SelectTextureFormat(
	const FalconTextureFormat& p_requestedTextureFormat,
	FalconTextureFormat* p_actualTextureFormat,
	LegoBool32 p_arg3
)
{
	FalconTextureFormat reqTextureFormat;
	if (p_arg3 && (m_unk0x04 & (c_flagBit7 | c_flagBit8)) && p_requestedTextureFormat.GetAlphaBitCount() == 0) {
		reqTextureFormat.m_redBitMask = 0xf800;
		reqTextureFormat.m_grnBitMask = 0x07c0;
		reqTextureFormat.m_bluBitMask = 0x003e;
		reqTextureFormat.m_alpBitMask = 0x0001;
		reqTextureFormat.m_unk0x10 = 0;
		reqTextureFormat.m_paletteMask = 0;
		reqTextureFormat.m_bitsPerPixel = 16;
		WhiteFalcon0x140::SelectTextureFormat(reqTextureFormat, p_actualTextureFormat, TRUE);
	}
	else {
		WhiteFalcon0x140::SelectTextureFormat(p_requestedTextureFormat, p_actualTextureFormat, FALSE);
	}
}

// FUNCTION: GOLDP 0x1000a1c0
LegoU32 BronzeFalcon0xc8770::GetMinimumTextureWidth(undefined4) const
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
LegoU32 BronzeFalcon0xc8770::GetMaximumTextureWidth(undefined4) const
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
LegoU32 BronzeFalcon0xc8770::GetMinimumTextureHeight(undefined4) const
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
LegoU32 BronzeFalcon0xc8770::GetMaximumTextureHeight(undefined4) const
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
LegoBool32 BronzeFalcon0xc8770::TexturesMustBeSquare() const
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
LegoBool32 BronzeFalcon0xc8770::TextureSizesMustBePowersOfTwo() const
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
void BronzeFalcon0xc8770::FUN_1000a2c0(DuskwindBananaRelic0x24* p_material)
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

	if (m_unk0x04 & c_flagBit14) {
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
				m_unk0xc83e0 = destBlend;
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
		if (!(newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit11) && m_drawState->VTable0x60()) {
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
				if (m_unk0x04 & c_flagBit19) {
					m_unk0xc83fc = ARGBU32(m_unk0xc83e0, m_unk0x118.m_red, m_unk0x118.m_grn, m_unk0x118.m_blu);
				}
				else {
					m_unk0xc83f8 = FALSE;
				}
			}
			else {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
				m_unk0xc83f8 = TRUE;
				m_unk0xc83fc = ARGBU32(m_unk0xc83e0, 0xff, 0xff, 0xff);
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
			if (m_unk0x04 & c_flagBit19) {
				m_unk0xc83fc = ARGBU32(m_unk0xc83e0, m_unk0x118.m_red, m_unk0x118.m_grn, m_unk0x118.m_blu);
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
				m_unk0xc83e0 = 0xff;
			}
			if (m_unk0x04 & c_flagBit12) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, TRUE);
			}
			else {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			}
			m_unk0xc83c8 = newFlags;
			FUN_10012f50();
		}
		else {
			if (newFlags & DuskwindBananaRelic0x24::c_flag0x08Bit12) {
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
				m_unk0xc83e0 = 0xff;
			}
			if (m_unk0x04 & c_flagBit12) {
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
void BronzeFalcon0xc8770::FUN_1000a950(DuskwindBananaRelic0x24* p_material)
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

	if (m_unk0x04 & c_flagBit14) {
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
			m_unk0xc83e0 = destBlend;
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
			m_unk0xc83e0 = 0xff;
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
void BronzeFalcon0xc8770::FUN_1000ac00(GoldDune0x38* p_texture)
{
	if (m_unk0xc83a8 == p_texture) {
		return;
	}

	m_unk0xc83a8 = p_texture;
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

		m_d3dDevice->SetTexture(0, static_cast<PurpleDune0x7c*>(m_unk0xc83a8)->GetDirect3DTexture());
	}
	else if (m_unk0xc83f0 != 0) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
		m_unk0xc83f0 = FALSE;
	}
}

// FUNCTION: GOLDP 0x1000aeb0
void BronzeFalcon0xc8770::SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags)
{
	WhiteFalcon0x140::SetAlphaOverride(p_alpha, p_flags);
	m_unk0xc83e0 = p_alpha;
	m_unk0xc83fc = (m_unk0xc83fc & 0x00ffffff) | (p_alpha << 24);
}

// FUNCTION: GOLDP 0x1000aef0
void BronzeFalcon0xc8770::ClearAlphaOverride()
{
	WhiteFalcon0x140::ClearAlphaOverride();
	m_unk0xc83e0 = 0xff;
	m_unk0xc83fc |= 0xff000000;
}

// FUNCTION: GOLDP 0x1000af20
void BronzeFalcon0xc8770::VTable0xc0(const ColorRGBA& p_color)
{
	WhiteFalcon0x140::VTable0xc0(p_color);
	m_unk0xc83f8 = TRUE;
	m_unk0xc83fc = ARGBU32(m_unk0xc83e0, p_color.m_red, p_color.m_grn, p_color.m_blu);
}

// FUNCTION: GOLDP 0x1000af70
void BronzeFalcon0xc8770::VTable0xc4()
{
	WhiteFalcon0x140::VTable0xc4();
	m_unk0xc83f8 = FALSE;
}

// FUNCTION: GOLDP 0x1000af90
void BronzeFalcon0xc8770::VTable0x28()
{
	WhiteFalcon0x140::VTable0x28();
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
void BronzeFalcon0xc8770::VTable0x2c(const Field0x124* p_param)
{
	WhiteFalcon0x140::VTable0x2c(p_param);
	m_unk0xc856c = p_param->m_unk0x00;

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
void BronzeFalcon0xc8770::VTable0x30(const Field0x124* p_param)
{
	LegoU32 index = m_unk0x11c;
	if (index < 7) {
		FUN_1000b0f0(index, p_param);
		WhiteFalcon0x140::VTable0x30(p_param);
	}
}

// FUNCTION: GOLDP 0x1000b0f0
void BronzeFalcon0xc8770::FUN_1000b0f0(LegoU32 p_index, const Field0x124* p_param)
{
	m_unk0xc8580[p_index] = p_param->m_unk0x00;
	m_unk0xc85f0[p_index] = p_param->m_unk0x04;

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
void BronzeFalcon0xc8770::VTable0x60()
{
	if (m_unk0x04 & c_flagBit15) {
		if (m_unk0x120 != NULL) {
			VTable0x2c(m_unk0x120);
		}

		for (LegoU32 i = 0; i < m_unk0x11c; i++) {
			FUN_1000b0f0(i, m_unk0x124[i]);
		}
	}
}

// FUNCTION: GOLDP 0x1000b240
void BronzeFalcon0xc8770::VTable0xc8()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
	}
}

// FUNCTION: GOLDP 0x1000b260
void BronzeFalcon0xc8770::VTable0xcc()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
	}
}

// FUNCTION: GOLDP 0x1000b280
void BronzeFalcon0xc8770::VTable0x3c(LegoU32 p_arg)
{
	m_unk0x04 |= c_flagBit17;
	m_unk0xc8704 = p_arg;
	if (m_unk0xc8704 > 4) {
		m_unk0xc8704 = 4;
	}
}

// FUNCTION: GOLDP 0x1000b2b0
void BronzeFalcon0xc8770::VTable0x40()
{
	m_unk0x04 &= ~c_flagBit17;
}

// FUNCTION: GOLDP 0x1000b2c0
SlatePeak0x58* BronzeFalcon0xc8770::VTable0x4c(undefined2 p_arg1, undefined2 p_arg2)
{
	BronzeFalconSurface0x5c* surface = new BronzeFalconSurface0x5c;
	if (surface == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	surface->FUN_10013600(this, p_arg1, p_arg2);
	surface->m_next = m_unk0x30c;
	m_unk0x30c = surface;
	return surface;
}

// FUNCTION: GOLDP 0x1000b350
void BronzeFalcon0xc8770::VTable0x50(SlatePeak0x58* p_surface)
{
	BronzeFalconSurface0x5c* surface = m_unk0x30c;
	if (surface == NULL) {
		return;
	}

	BronzeFalconSurface0x5c* target = static_cast<BronzeFalconSurface0x5c*>(p_surface);
	if (target == surface) {
		m_unk0x30c = surface->m_next;
		target->VTable0x34();
		delete target;
		return;
	}

	BronzeFalconSurface0x5c* previous = surface;
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
void BronzeFalcon0xc8770::VTable0x58(SlatePeak0x58* p_surface, undefined4 p_flags)
{
	m_renderTargetInfo = m_unk0x304;
	BronzeFalconSurface0x5c* surface = m_unk0x30c;
	if (surface != NULL) {
		BronzeFalconSurface0x5c* target = static_cast<BronzeFalconSurface0x5c*>(p_surface);
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
LegoBool32 BronzeFalcon0xc8770::VTable0x110() const
{
	MATCHING(0x100016f0);
	return FALSE;
}

// FUNCTION: GOLDP 0x1000b4a0
void BronzeFalcon0xc8770::FUN_1000b4a0()
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

		FalconTextureFormat& textureFormat = m_renderTargetInfo->GetTextureFormat();
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
BronzeFalcon0xc8770::TextureFormat::TextureFormat()
{
}

// FUNCTION: GOLDP 0x1000b7e0
HRESULT BronzeFalcon0xc8770::CountTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context)
{
	LegoU32* count = static_cast<LegoU32*>(p_context);
	*count += 1;
	return TRUE;
}

// FUNCTION: GOLDP 0x1000b800
HRESULT BronzeFalcon0xc8770::EnumerateTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context)
{
	BronzeFalcon0xc8770* self = static_cast<BronzeFalcon0xc8770*>(p_context);
	FalconTextureFormat* format = &self->m_textureFormats[self->m_unk0x2c];
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

// STUB: GOLDP 0x1000be20
void BronzeFalcon0xc8770::FUN_1000be20(undefined4, undefined4, undefined4)
{
	STUB(0x1000be20);
}

// STUB: GOLDP 0x1000bfb0
void BronzeFalcon0xc8770::FUN_1000bfb0(undefined4, undefined4, undefined4)
{
	STUB(0x1000bfb0);
}

// STUB: GOLDP 0x1000c160
void BronzeFalcon0xc8770::FUN_1000c160(undefined4, undefined4, undefined4)
{
	STUB(0x1000c160);
}

// STUB: GOLDP 0x1000c2d0
void BronzeFalcon0xc8770::FUN_1000c2d0(undefined4, undefined4, undefined4)
{
	STUB(0x1000c2d0);
}

// STUB: GOLDP 0x1000c470
void BronzeFalcon0xc8770::FUN_1000c470(undefined4, undefined4, undefined4)
{
	STUB(0x1000c470);
}

// STUB: GOLDP 0x1000c630
void BronzeFalcon0xc8770::FUN_1000c630(undefined4, undefined4, undefined4)
{
	STUB(0x1000c630);
}

// STUB: GOLDP 0x1000d210
void BronzeFalcon0xc8770::FUN_1000d210(undefined4, undefined4, undefined4)
{
	STUB(0x1000d210);
}

// STUB: GOLDP 0x1000d440
void BronzeFalcon0xc8770::FUN_1000d440(undefined4, undefined4, undefined4)
{
	STUB(0x1000d440);
}

// STUB: GOLDP 0x1000d5d0
void BronzeFalcon0xc8770::FUN_1000d5d0(undefined4, undefined4, undefined4)
{
	STUB(0x1000d5d0);
}

// STUB: GOLDP 0x1000d760
void BronzeFalcon0xc8770::FUN_1000d760(undefined4, undefined4, undefined4)
{
	STUB(0x1000d760);
}

// STUB: GOLDP 0x1000dbb0
void BronzeFalcon0xc8770::FUN_1000dbb0(undefined4, undefined4, undefined4)
{
	STUB(0x1000dbb0);
}

// STUB: GOLDP 0x1000eb90
void BronzeFalcon0xc8770::FUN_1000eb90(undefined4, undefined4, undefined4)
{
	STUB(0x1000eb90);
}

// STUB: GOLDP 0x1000ebd0
void BronzeFalcon0xc8770::FUN_1000ebd0(undefined4, undefined4, undefined4)
{
	STUB(0x1000ebd0);
}

// STUB: GOLDP 0x1000ece0
void BronzeFalcon0xc8770::FUN_1000ece0(undefined4, undefined4, undefined4)
{
	STUB(0x1000ece0);
}

// STUB: GOLDP 0x1000edf0
void BronzeFalcon0xc8770::FUN_1000edf0(undefined4, undefined4, undefined4)
{
	STUB(0x1000edf0);
}

// STUB: GOLDP 0x10010330
void BronzeFalcon0xc8770::FUN_10010330(undefined4, undefined4, undefined4)
{
	STUB(0x10010330);
}

// STUB: GOLDP 0x10010500
void BronzeFalcon0xc8770::FUN_10010500(undefined4, undefined4, undefined4)
{
	STUB(0x10010500);
}

// STUB: GOLDP 0x100106d0
void BronzeFalcon0xc8770::FUN_100106d0(undefined4, undefined4, undefined4)
{
	STUB(0x100106d0);
}

// STUB: GOLDP 0x10011e60
void BronzeFalcon0xc8770::FUN_10011e60(undefined4, undefined4, undefined4)
{
	STUB(0x10011e60);
}

// STUB: GOLDP 0x10011ed0
void BronzeFalcon0xc8770::FUN_10011ed0(undefined4, undefined4, undefined4)
{
	STUB(0x10011ed0);
}

// STUB: GOLDP 0x10012030
void BronzeFalcon0xc8770::FUN_10012030(undefined4, undefined4, undefined4)
{
	STUB(0x10012030);
}

// STUB: GOLDP 0x100121e0
void BronzeFalcon0xc8770::FUN_100121e0(undefined4, undefined4, undefined4)
{
	STUB(0x100121e0);
}

// STUB: GOLDP 0x100123e0
void BronzeFalcon0xc8770::FUN_100123e0(undefined4, undefined4, undefined4)
{
	STUB(0x100123e0);
}

// STUB: GOLDP 0x10012640
void BronzeFalcon0xc8770::FUN_10012640(undefined4, undefined4, undefined4)
{
	STUB(0x10012640);
}

// STUB: GOLDP 0x100128f0
void BronzeFalcon0xc8770::FUN_100128f0(undefined4, undefined4, undefined4)
{
	STUB(0x100128f0);
}

// STUB: GOLDP 0x10012bf0
void BronzeFalcon0xc8770::FUN_10012bf0(undefined4, undefined4, undefined4)
{
	STUB(0x10012bf0);
}

// FUNCTION: GOLDP 0x10012f50
void BronzeFalcon0xc8770::FUN_10012f50()
{
	if (m_unk0xc8524) {
		if (m_unk0xc8528) {
			m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_1000eb90;
			if (m_unk0xc8568) {
				m_unk0xc8764 = &BronzeFalcon0xc8770::FUN_1000d210;
				return;
			}
			if (m_unk0xc83ec) {
				m_unk0xc8764 = &BronzeFalcon0xc8770::FUN_1000d5d0;
				return;
			}

			m_unk0xc8764 = &BronzeFalcon0xc8770::FUN_1000d440;
			return;
		}

		if (m_unk0xc83c4) {
			m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_100106d0;
		}
		else {
			m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_1000edf0;
		}

		if (m_unk0xc83ec) {
			m_unk0xc8764 = &BronzeFalcon0xc8770::FUN_1000dbb0;
		}
		else {
			m_unk0xc8764 = &BronzeFalcon0xc8770::FUN_1000d760;
		}
	}
	else {
		LegoU32 index = m_unk0xc83f8;
		index <<= 3;
		index |= m_unk0xc83e8;
		index <<= 1;
		index |= m_unk0xc83f4;
		index <<= 1;
		index |= (m_unk0x04 >> 9) & 0x10;
		index |= m_unk0xc83ec;

		if (m_unk0xc83e4) {
			if (m_unk0xc83c4) {
				m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_100106d0;
				if (!m_unk0xc83e8 && m_unk0xc8700 == 0) {
					m_unk0xc8764 = &BronzeFalcon0xc8770::FUN_100132f0;
					return;
				}
			}
			else {
				m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_1000edf0;
			}

			index |= 8;
		}
		else {
			LegoU32 flags = m_unk0xc83c8 | m_unk0xc83cc;
			if (flags & DuskwindBananaRelic0x24::c_flag0x08Bit14) {
				if (m_unk0xc83c4) {
					m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_10010500;
				}
				else {
					m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_1000ece0;
				}
			}
			else if (m_unk0xc83c4) {
				m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_10010330;
				if (!m_unk0xc83e8 && m_unk0xc8700 == 0) {
					m_unk0xc8764 = &BronzeFalcon0xc8770::FUN_10013110;
					return;
				}
			}
			else {
				m_unk0xc8768 = &BronzeFalcon0xc8770::FUN_1000ebd0;
			}
		}

		if (m_unk0xc8568) {
			m_unk0xc8764 = g_unk0x1005c8a8[m_unk0x11c];
			m_unk0xc8760 = g_unk0x1005c8c8[index];
		}
		else {
			m_unk0xc8764 = g_unk0x1005c8c8[index];
		}
	}
}

// STUB: GOLDP 0x10013110
void BronzeFalcon0xc8770::FUN_10013110(undefined4, undefined4, undefined4)
{
	STUB(0x10013110);
}

// STUB: GOLDP 0x100132f0
void BronzeFalcon0xc8770::FUN_100132f0(undefined4, undefined4, undefined4)
{
	STUB(0x100132f0);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void BronzeFalcon0xc8770::VTable0x38()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void BronzeFalcon0xc8770::VTable0xd0()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void BronzeFalcon0xc8770::VTable0x34(LegoS32, const LegoFloat*)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void BronzeFalcon0xc8770::VTable0xec(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void BronzeFalcon0xc8770::VTable0xf4()
{
	// empty
}
