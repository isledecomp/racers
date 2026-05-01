#include "bronzefalcon0xc8770.h"

#include "bronzefalconsurface0x5c.h"
#include "falcondunebag0x10.h"
#include "falcontextureformat.h"
#include "goldrawdpstate.h"
#include "golerror.h"

#include <stdio.h>

DECOMP_SIZE_ASSERT(BronzeFalcon0xc8770, 0xc8770)
DECOMP_SIZE_ASSERT(BronzeFalcon0xc8770::JasperRipple0x4, 0x4)

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
	::memcpy(&swTextureFormat, &m_unk0x304->m_unk0x04, sizeof(swTextureFormat));

	WorkHorse0x58::Pixelformat swPixelformat;
	if (swTextureFormat.m_rgbBitCount == 8) {
		swPixelformat = WorkHorse0x58::Pixelformat::e_formatIndex8;
		if (m_drawState->m_flags & GolDrawState::c_flagBit18) {
			m_unk0xc8700 = 1;
		}
		else {
			m_unk0xc8700 = 0;
		}
	}
	else {
		swPixelformat = swTextureFormat.GetGreenBitCount() == 6 ? WorkHorse0x58::Pixelformat::e_format565
																: WorkHorse0x58::Pixelformat::e_format555;
		m_unk0xc8700 = 2;
	}

	FalconDuneBag0x10::SetTextureFormat(swTextureFormat);
	if (!m_unk0xc8698.Initialize(swPixelformat, 16000)) {
		GOL_FATALERROR_MESSAGE("Unable to initialize software renderer");
	}

	m_unk0xc8698.SetUnk0x4c(m_unk0x348);
	FUN_1000b4a0();
	::memset(&m_unk0xc83b4, 0, sizeof(m_unk0xc83b4));

rendererCreated:
	VTable0x1c(&m_unk0x2cc);
	FUN_100082e0();
	if (m_unk0x0c != NULL) {
		VTable0x20(m_unk0x0c);
	}

	m_unk0x2d4.FUN_10006320(this);
	for (BronzeFalconSurface0x5c* surface = m_unk0x30c; surface != NULL; surface = surface->m_next) {
		surface->FUN_100136a0(this);
	}

	WhiteFalcon0x140::VTable0x00();
	return 0;
}

// STUB: GOLDP 0x10008680
void BronzeFalcon0xc8770::VTable0x04()
{
	STUB(0x10008680);
}

// STUB: GOLDP 0x10008740
void BronzeFalcon0xc8770::VTable0x18()
{
	STUB(0x10008740);
}

// STUB: GOLDP 0x100087b0
void BronzeFalcon0xc8770::VTable0x20(AmberLens0x344*)
{
	STUB(0x100087b0);
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

// STUB: GOLDP 0x10009640
void BronzeFalcon0xc8770::VTable0x1c(JasperRipple0x4*)
{
	STUB(0x10009640);
}

// STUB: GOLDP 0x10009780
void BronzeFalcon0xc8770::VTable0xd8()
{
	STUB(0x10009780);
}

// STUB: GOLDP 0x100097c0
void BronzeFalcon0xc8770::VTable0xd4()
{
	STUB(0x100097c0);
}

// STUB: GOLDP 0x100097f0
void BronzeFalcon0xc8770::VTable0xdc()
{
	STUB(0x100097f0);
}

// STUB: GOLDP 0x10009840
void BronzeFalcon0xc8770::VTable0xe0()
{
	STUB(0x10009840);
}

// STUB: GOLDP 0x10009860
void BronzeFalcon0xc8770::VTable0xe4()
{
	STUB(0x10009860);
}

// STUB: GOLDP 0x100098d0
void BronzeFalcon0xc8770::VTable0xe8(undefined4)
{
	STUB(0x100098d0);
}

// FUNCTION: GOLDP 0x10009950
const WhiteFalcon0x140::RenderTargetInfo* BronzeFalcon0xc8770::GetRenderTargetInfo()
{
	return m_renderTargetInfo;
}

// STUB: GOLDP 0x10009960
void BronzeFalcon0xc8770::VTable0x7c()
{
	STUB(0x10009960);
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

// STUB: GOLDP 0x10009bd0
void BronzeFalcon0xc8770::VTable0x80()
{
	STUB(0x10009bd0);
}

// STUB: GOLDP 0x10009ce0
void BronzeFalcon0xc8770::DrawTriangle(
	const TexturedVertex*,
	const TexturedVertex*,
	const TexturedVertex*,
	undefined4,
	undefined4
)
{
	STUB(0x10009ce0);
}

// STUB: GOLDP 0x1000a110
void BronzeFalcon0xc8770::VTable0x0c(undefined4, undefined4, undefined4)
{
	STUB(0x1000a110);
}

// STUB: GOLDP 0x1000a1c0
void BronzeFalcon0xc8770::VTable0xf8()
{
	STUB(0x1000a1c0);
}

// STUB: GOLDP 0x1000a1f0
void BronzeFalcon0xc8770::VTable0xfc()
{
	STUB(0x1000a1f0);
}

// STUB: GOLDP 0x1000a210
void BronzeFalcon0xc8770::VTable0x100()
{
	STUB(0x1000a210);
}

// STUB: GOLDP 0x1000a240
void BronzeFalcon0xc8770::VTable0x104()
{
	STUB(0x1000a240);
}

// STUB: GOLDP 0x1000a260
void BronzeFalcon0xc8770::VTable0x108()
{
	STUB(0x1000a260);
}

// STUB: GOLDP 0x1000a290
void BronzeFalcon0xc8770::VTable0x10c()
{
	STUB(0x1000a290);
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

// FUNCTION: GOLDP 0x100016f0 FOLDED
LegoBool32 BronzeFalcon0xc8770::VTable0x110() const
{
	MATCHING(0x100016f0);
	return FALSE;
}

// STUB: GOLDP 0x100082e0 FOLDED
void BronzeFalcon0xc8770::FUN_100082e0()
{
	// TODO
	STUB(0x100082e0);
}

// STUB: GOLDP 0x1000a2c0 FOLDED
void BronzeFalcon0xc8770::FUN_1000a2c0(undefined*)
{
	// TODO
	STUB(0x1000a2c0);
}

// STUB: GOLDP 0x1000a950 FOLDED
void BronzeFalcon0xc8770::FUN_1000a950(undefined*)
{
	// TODO
	STUB(0x1000a950);
}

// STUB: GOLDP 0x1000b4a0 FOLDED
void BronzeFalcon0xc8770::FUN_1000b4a0()
{
	// TODO
	STUB(0x1000b4a0);
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
		format->m_unk0x14 = 0xff;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_unk0x10 = 0;
		format->m_rgbBitCount = 8;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED4) {
		format->m_unk0x14 = 0xf;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_unk0x10 = 0;
		format->m_rgbBitCount = 4;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED2) {
		format->m_unk0x14 = 0x3;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_unk0x10 = 0;
		format->m_rgbBitCount = 2;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED1) {
		format->m_unk0x14 = 0x1;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_unk0x10 = 0;
		format->m_rgbBitCount = 1;
	}
	else {
		format->m_redBitMask = p_format->dwRBitMask;
		format->m_grnBitMask = p_format->dwGBitMask;
		format->m_bluBitMask = p_format->dwBBitMask;
		format->m_unk0x14 = 0;
		format->m_unk0x10 = 0;
		LegoU32 bitCount = p_format->dwRGBBitCount;
		format->m_rgbBitCount = bitCount;
	}
	if (p_format->dwFlags & DDPF_ALPHAPIXELS) {
		format->m_alpBitMask = p_format->dwRGBAlphaBitMask;
	}
	else {
		format->m_alpBitMask = 0;
	}

	return TRUE;
}
