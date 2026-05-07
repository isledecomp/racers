#include "bronzefalcon0xc8770.h"

#include "amberlens0x344.h"
#include "bronzefalconsurface0x5c.h"
#include "falcondunebag0x10.h"
#include "falcontextureformat.h"
#include "goldrawdpstate.h"
#include "golerror.h"
#include "rectangle.h"

#include <stdio.h>

DECOMP_SIZE_ASSERT(BronzeFalcon0xc8770, 0xc8770)
DECOMP_SIZE_ASSERT(BronzeFalcon0xc8770::TextureFormat, 0x18)
DECOMP_SIZE_ASSERT(BronzeFalcon0xc8770::Field0xc83b4, 0x10)
DECOMP_SIZE_ASSERT(ColorRGBA, 0x4)
DECOMP_SIZE_ASSERT(Rect, 0x10)

// GLOBAL: GOLDP 0x10056560
LegoU32 g_blendCapsMasks[11] = {
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
LegoU32 g_blendCapsShifts[11] = {
	1,  // D3DPBLENDCAPS_ZERO			== (1 << (1 - 1))
	2,  // D3DPBLENDCAPS_ONE			== (1 << (2 - 1))
	3,  // D3DPBLENDCAPS_SRCCOLOR		== (1 << (3 - 1))
	9,  // D3DPBLENDCAPS_DESTCOLOR		== (1 << (9 - 1))
	4,  // D3DPBLENDCAPS_INVSRCCOLOR	== (1 << (4 - 1))
	10, // D3DPBLENDCAPS_INVDESTCOLOR	== (1 << (10 - 1))
	5,  // D3DPBLENDCAPS_SRCALPHA		== (1 << (5 - 1))
	7,  // D3DPBLENDCAPS_DESTALPHA		== (1 << (7 - 1))
	6,  // D3DPBLENDCAPS_INVSRCALPHA	== (1 << (6 - 1))
	8,  // D3DPBLENDCAPS_INVDESTALPHA	== (1 << (8 - 1))
	11, // D3DPBLENDCAPS_SRCALPHASAT	== (1 << (11 - 1))
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

// STUB: GOLDP 0x10007a00
void BronzeFalcon0xc8770::Reset()
{
	// TODO
	STUB(0x10007a00);
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
				if (m_d3dDeviceDesc.dpcTriCaps.dwSrcBlendCaps & g_blendCapsMasks[i]) {
					m_unk0xc8708[i] = g_blendCapsShifts[i];
				}
				else {
					m_unk0xc8708[i] = 5;
				}
			}

			for (i = 0; i < sizeOfArray(m_unk0xc8708); i++) {
				if (m_d3dDeviceDesc.dpcTriCaps.dwDestBlendCaps & g_blendCapsMasks[i]) {
					m_unk0xc8734[i] = g_blendCapsShifts[i];
				}
				else {
					m_unk0xc8734[i] = 6;
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

// STUB: GOLDP 0x100082e0
void BronzeFalcon0xc8770::FUN_100082e0()
{
	// TODO
	STUB(0x100082e0);
}

// STUB: GOLDP 0x10008680
void BronzeFalcon0xc8770::ReleaseResources()
{
	STUB(0x10008680);
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

// STUB: GOLDP 0x100087e0
void BronzeFalcon0xc8770::VTable0x5c()
{
	STUB(0x100087e0);
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

// STUB: GOLDP 0x10009420
void BronzeFalcon0xc8770::VTable0x54(undefined4)
{
	STUB(0x10009420);
}

// STUB: GOLDP 0x10009540
void BronzeFalcon0xc8770::VTable0xf0()
{
	STUB(0x10009540);
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

// STUB: GOLDP 0x10009960
undefined4 BronzeFalcon0xc8770::VTable0x7c(UtopianPan0xa4*, undefined4, Rect*, Rect*, undefined4)
{
	STUB(0x10009960);
	return 0;
}

// STUB: GOLDP 0x10009990
void BronzeFalcon0xc8770::VTable0x78()
{
	STUB(0x10009990);
}

// STUB: GOLDP 0x100099b0
void BronzeFalcon0xc8770::VTable0x74()
{
	STUB(0x100099b0);
}

// STUB: GOLDP 0x10009a20
void BronzeFalcon0xc8770::VTable0x70()
{
	STUB(0x10009a20);
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
			cmd->m_unk0x10 = m_unk0xc83b4.m_unk0x00;
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

// STUB: GOLDP 0x1000a2c0
void BronzeFalcon0xc8770::FUN_1000a2c0(DuskwindBananaRelic0x24*)
{
	// TODO
	STUB(0x1000a2c0);
}

// STUB: GOLDP 0x1000a950
void BronzeFalcon0xc8770::FUN_1000a950(DuskwindBananaRelic0x24*)
{
	// TODO
	STUB(0x1000a950);
}

// STUB: GOLDP 0x1000ac00
void BronzeFalcon0xc8770::FUN_1000ac00(undefined4*)
{
	// FIXME
	STUB(0x1000ac00);
}

// STUB: GOLDP 0x1000aeb0
void BronzeFalcon0xc8770::SetAlphaOverride(undefined4, undefined4)
{
	STUB(0x1000aeb0);
}

// STUB: GOLDP 0x1000aef0
void BronzeFalcon0xc8770::ClearAlphaOverride()
{
	STUB(0x1000aef0);
}

// STUB: GOLDP 0x1000af20
void BronzeFalcon0xc8770::VTable0xc0(undefined4*)
{
	STUB(0x1000af20);
}

// STUB: GOLDP 0x1000af70
void BronzeFalcon0xc8770::VTable0xc4()
{
	STUB(0x1000af70);
}

// STUB: GOLDP 0x1000af90
void BronzeFalcon0xc8770::VTable0x28()
{
	STUB(0x1000af90);
}

// STUB: GOLDP 0x1000b000
void BronzeFalcon0xc8770::VTable0x2c(undefined4)
{
	STUB(0x1000b000);
}

// STUB: GOLDP 0x1000b0c0
void BronzeFalcon0xc8770::VTable0x30(undefined4)
{
	STUB(0x1000b0c0);
}

// STUB: GOLDP 0x1000b1f0
void BronzeFalcon0xc8770::VTable0x60()
{
	STUB(0x1000b1f0);
}

// STUB: GOLDP 0x1000b240
void BronzeFalcon0xc8770::VTable0xc8()
{
	STUB(0x1000b240);
}

// STUB: GOLDP 0x1000b260
void BronzeFalcon0xc8770::VTable0xcc()
{
	STUB(0x1000b260);
}

// STUB: GOLDP 0x1000b280
void BronzeFalcon0xc8770::VTable0x3c(undefined4)
{
	STUB(0x1000b280);
}

// STUB: GOLDP 0x1000b2b0
void BronzeFalcon0xc8770::VTable0x40()
{
	STUB(0x1000b2b0);
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

// STUB: GOLDP 0x1000b350
void BronzeFalcon0xc8770::VTable0x50(undefined4)
{
	STUB(0x1000b350);
}

// STUB: GOLDP 0x1000b3d0
void BronzeFalcon0xc8770::VTable0x58(undefined4, undefined4)
{
	STUB(0x1000b3d0);
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
