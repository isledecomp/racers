#include "purpledune0x7c.h"

#include "bronzefalcon0xc8770.h"
#include "ddrawutil.h"
#include "falcondunebag0x10.h"
#include "golcommondrawstate.h"
#include "golerror.h"
#include "golimgfile.h"
#include "pearldew0x0c.h"

#include <string.h>

DECOMP_SIZE_ASSERT(PurpleDune0x7c, 0x7c)

// GLOBAL: GOLDP 0x10057668
static const ColorRGBA g_unk0x10057668 = {0, 0, 0, 0};

// GLOBAL: GOLDP 0x100635c0
static GolImgFile g_unk0x100635c0;

// FUNCTION: GOLDP 0x10015b70
PurpleDune0x7c::PurpleDune0x7c()
	: m_unk0x40(NULL), m_mipmaps(NULL), m_surface(NULL), m_unk0x4c(NULL), m_unk0x74(0), m_unk0x78(0)
{
}

// FUNCTION: GOLDP 0x10015bf0
PurpleDune0x7c::~PurpleDune0x7c()
{
	FUN_10016380();
	m_unk0x50.FUN_1002a1b0();

	if (m_pixels != NULL) {
		delete[] m_pixels;
		m_pixels = NULL;
	}

	m_pixelFlags = 0;
}

// FUNCTION: GOLDP 0x10015c80
void PurpleDune0x7c::VTable0x30(WhiteFalcon0x140& p_renderer, GolImgFile* p_source)
{
	GolSurfaceFormat textureFormat = p_source->GetTextureFormat();

	if (p_renderer.GetUnk0x04() & WhiteFalcon0x140::c_flagBit17) {
		m_unk0x34 = static_cast<LegoU16>(static_cast<BronzeFalcon0xc8770&>(p_renderer).GetUnk0xc8704());
	}

	VTable0x34(p_renderer, textureFormat, p_source->GetWidth(), p_source->GetHeight());
	p_source->SetUnk0x5a8(TRUE);
	p_source->SetUnk0x5ac(0);
	p_source->VTable0x20(this, m_unk0x36 & c_unk0x36Bit2, 0);
	p_source->SetUnk0x5a8(0);
}

// FUNCTION: GOLDP 0x10015d60
void PurpleDune0x7c::VTable0x34(
	WhiteFalcon0x140& p_renderer,
	const GolSurfaceFormat& p_textureFormat,
	LegoU32 p_width,
	LegoU32 p_height
)
{
	if (m_pixelFlags & c_lockRequestRead) {
		VTable0x38();
	}

	m_pixelFlags |= c_lockRequestRead;
	m_width = p_width;
	m_height = p_height;
	m_textureFormat = p_textureFormat;
	m_pitch = ((LegoU32) (LegoU16) p_width * m_textureFormat.m_bitsPerPixel + 7) / 8;
	m_pixels = new LegoU8[m_pitch * p_height];

	if (m_pixels == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	if (p_textureFormat.m_paletteMask != 0) {
		m_unk0x50.FUN_1002a120(p_textureFormat);
	}

	FUN_10016460(static_cast<BronzeFalcon0xc8770&>(p_renderer));
}

// FUNCTION: GOLDP 0x10015e00
void PurpleDune0x7c::VTable0x38()
{
	FUN_10016380();
	m_unk0x50.FUN_1002a1b0();

	if (m_pixels != NULL) {
		delete[] m_pixels;
		m_pixels = NULL;
	}

	m_pixelFlags = 0;
}

// FUNCTION: GOLDP 0x10015e30
void PurpleDune0x7c::LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags)
{
	if (p_flags & c_lockRequestRead) {
		m_pixelFlags |= c_lockFlagRead;
	}
	if (p_flags & c_lockRequestWrite) {
		m_pixelFlags |= c_lockFlagWrite;
	}

	m_pixelFlags |= c_lockFlagLocked;
	if (m_pixels == NULL) {
		if (m_mipmaps != NULL) {
			*p_pixels = m_mipmaps->m_pixels;
			*p_pitch = m_mipmaps->m_pitch;
		}
		else {
			DWORD lockFlags = 0;
			if (m_pixelFlags & c_lockFlagRead) {
				if (!(m_pixelFlags & c_lockFlagWrite)) {
					lockFlags = DDLOCK_READONLY;
				}
			}
			else {
				if (m_pixelFlags & c_lockFlagWrite) {
					lockFlags = DDLOCK_WRITEONLY;
				}
			}

			DDSURFACEDESC2 surfaceDesc;
			::memset(&surfaceDesc, 0, sizeof(surfaceDesc));
			surfaceDesc.dwSize = sizeof(surfaceDesc);

			for (;;) {
				HRESULT hresult = LockDirectDrawSurface(m_surface, NULL, &surfaceDesc, lockFlags, NULL);
				switch (hresult) {
				case DD_OK:
					*p_pixels = static_cast<LegoU8*>(surfaceDesc.lpSurface);
					*p_pitch = surfaceDesc.lPitch;
					return;
				case DDERR_SURFACELOST:
					if (m_surface->Restore() != DD_OK) {
						GOL_FATALERROR_MESSAGE("Unable to restore lost surface");
					}
					break;
				default:
					GOL_FATALERROR_MESSAGE("Unable to lock surface");
					break;
				}
			}
		}
	}
	else {
		*p_pixels = m_pixels;
		*p_pitch = m_pitch;
	}
}

// FUNCTION: GOLDP 0x10015f50
void PurpleDune0x7c::UnlockPixels()
{
	if (m_pixelFlags & c_lockRequestWrite) {
		if (m_pixels == NULL && m_mipmaps == NULL) {
			m_surface->Unlock(NULL);
			FUN_10015fb0();
		}
		if (!(m_pixelFlags & c_lockFlagWrite) && (m_pixelFlags & c_lockFlagRead)) {
			m_pixelFlags &= ~(c_lockFlagWrite | c_lockFlagRead | c_lockFlagLocked);
		}
		else {
			m_pixelFlags &= ~(c_lockFlagWrite | c_lockFlagRead | c_lockFlagLocked);
			if (m_pixels != NULL) {
				FUN_10016100();
			}
		}
	}
}

// FUNCTION: GOLDP 0x10015fb0
void PurpleDune0x7c::FUN_10015fb0()
{
	DDCOLORKEY colorkey;
	ColorRGBA rgba;

	if (m_mipmaps == NULL && (m_unk0x36 & c_unk0x36Bit5) && !(m_unk0x36 & c_unk0x36Bit10) &&
		(m_unk0x36 & c_unk0x36Bit11)) {
		if (m_textureFormat2.m_paletteMask == 0) {
			LegoU32 color;

			if (m_unk0x36 & c_unk0x36Bit7) {
				color = 0;
			}
			else {
				LegoU32 redRightShift = 8 - m_textureFormat2.GetRedBitCount();
				LegoU32 grnRightShift = 8 - m_textureFormat2.GetGreenBitCount();
				LegoU32 bluRightShift = 8 - m_textureFormat2.GetBlueBitCount();
				LegoU32 red = (m_colorKey.m_red >> redRightShift) << m_textureFormat2.GetRedBitShift();
				LegoU32 grn = (m_colorKey.m_grn >> grnRightShift) << m_textureFormat2.GetGreenBitShift();
				LegoU32 blu = (m_colorKey.m_blu >> bluRightShift) << m_textureFormat2.GetBlueBitShift();
				color = blu | grn | red;
			}
			colorkey.dwColorSpaceHighValue = color;
			colorkey.dwColorSpaceLowValue = color;
		}
		else {
			LegoS32 color;

			if (m_unk0x36 & c_unk0x36Bit7) {
				rgba.m_red = 0;
				rgba.m_grn = 0;
				rgba.m_blu = 0;
				rgba.m_alp = 0;
				color = m_unk0x40->FindEntry(rgba);
			}
			else {
				color = m_unk0x40->FindEntry(m_colorKey);
			}
			colorkey.dwColorSpaceHighValue = color;
			colorkey.dwColorSpaceLowValue = colorkey.dwColorSpaceHighValue;

			if (color < 0) {
				return;
			}
		}
		m_surface->SetColorKey(DDCKEY_SRCBLT, &colorkey);
		m_unk0x36 &= ~c_unk0x36Bit11;
	}
}

// FUNCTION: GOLDP 0x100160e0
IPalette0x4* PurpleDune0x7c::GetPalette()
{
	if (m_pixels == NULL) {
		if (m_mipmaps != NULL) {
			return m_unk0x40;
		}
		else {
			return m_unk0x40;
		}
	}

	if (m_unk0x50.HasEntries()) {
		return &m_unk0x50;
	}

	return NULL;
}

// FUNCTION: GOLDP 0x10016100
void PurpleDune0x7c::FUN_10016100()
{
	ColorRGBA* colorKey;
	LegoU8* dstPixels;
	LegoU32 dstPitch;
	LegoU32 paletteSize;
	ColorRGBA* paletteEntries;

	if (m_textureFormat.m_paletteMask != 0) {
		paletteEntries = m_unk0x50.GetEntries();
		paletteSize = m_unk0x50.GetPaletteSize();
	}
	else {
		paletteEntries = NULL;
		paletteSize = 0;
	}

	g_unk0x100635c0.FUN_100226c0(m_textureFormat, m_width, m_height, m_pitch, paletteEntries, paletteSize);

	if (m_unk0x36 & c_unk0x36Bit5) {
		if (m_unk0x36 & c_unk0x36Bit7) {
			g_unk0x100635c0.SetUnk0x0a0(g_unk0x10057668);
		}
		else {
			g_unk0x100635c0.SetUnk0x0a0(m_colorKey);
		}

		colorKey = &m_colorKey;
	}
	else {
		colorKey = NULL;
	}

	if (m_mipmaps != NULL) {
		g_unk0x100635c0.SetUnk0x5ac(1);
		dstPixels = m_mipmaps->m_pixels;
		dstPitch = m_mipmaps->m_pitch;
	}
	else {
		DDSURFACEDESC2 surfaceDesc;
		::memset(&surfaceDesc, 0, sizeof(surfaceDesc));
		surfaceDesc.dwSize = sizeof(surfaceDesc);

		HRESULT hresult;
		do {
			hresult = LockDirectDrawSurface(m_surface, NULL, &surfaceDesc, DDLOCK_WRITEONLY, NULL);
			if (hresult == DD_OK) {
				dstPixels = static_cast<LegoU8*>(surfaceDesc.lpSurface);
				dstPitch = surfaceDesc.lPitch;
			}
			else {
				if (hresult == DDERR_SURFACELOST) {
					if (m_surface->Restore() != DD_OK) {
						GOL_FATALERROR_MESSAGE("Unable to restore lost surface");
					}
				}
				else {
					GOL_FATALERROR_MESSAGE("Unable to lock surface");
				}
			}
		} while (hresult != DD_OK);
	}

	g_unk0x100635c0
		.FUN_10022730(m_pixels, dstPixels, m_unk0x74, m_unk0x78, dstPitch, m_textureFormat2, m_unk0x40, 0, colorKey);
	g_unk0x100635c0.Destroy();

	if (m_mipmaps == NULL) {
		m_surface->Unlock(NULL);
		FUN_10015fb0();
	}
	else {
		FUN_10016260();
	}
}

// FUNCTION: GOLDP 0x10016260
void PurpleDune0x7c::FUN_10016260()
{
	if (m_mipmaps != NULL) {
		if (m_unk0x34 > 1) {
			if (m_width == m_height) {
				ColorRGBA* colorKey;
				if (m_unk0x36 & c_unk0x36Bit5) {
					if (m_unk0x36 & c_unk0x36Bit7) {
						g_unk0x100635c0.SetUnk0x0a0(g_unk0x10057668);
					}
					else {
						g_unk0x100635c0.SetUnk0x0a0(m_colorKey);
					}

					colorKey = &m_colorKey;
				}
				else {
					colorKey = NULL;
				}

				LegoU8* srcPixels = m_mipmaps[0].m_pixels;
				LegoU32 srcPitch = m_mipmaps[0].m_pitch;
				LegoU32 width = m_unk0x74;
				LegoU32 height = m_unk0x78;

				for (LegoU32 i = 1; i < m_unk0x34; i++) {
					g_unk0x100635c0.FUN_100226c0(m_textureFormat2, width, height, srcPitch, NULL, 0);

					width >>= 1;
					height >>= 1;
					srcPitch = m_mipmaps[i].m_pitch;
					g_unk0x100635c0.FUN_10022880(
						srcPixels,
						m_mipmaps[i].m_pixels,
						width,
						height,
						srcPitch,
						m_textureFormat2,
						0,
						colorKey
					);

					srcPixels = m_mipmaps[i].m_pixels;
					g_unk0x100635c0.Destroy();
				}
			}
		}
	}
}

// STUB: GOLDP 0x10016380
void PurpleDune0x7c::FUN_10016380()
{
	LegoU32 i;

	if (m_mipmaps != NULL) {
		if (m_unk0x40 != NULL) {
			FalconDuneBag0x10* palette = static_cast<FalconDuneBag0x10*>(m_unk0x40);
			palette->Destroy();
			if (palette != NULL) {
				delete palette;
			}

			m_unk0x40 = NULL;
		}
		for (i = 0; i < m_unk0x34; i++) {
			if (m_mipmaps[i].m_pixels != NULL) {
				delete[] m_mipmaps[i].m_pixels;
				m_mipmaps[i].m_pixels = NULL;
			}
		}

		delete[] m_mipmaps;
		m_mipmaps = NULL;
	}
	else {
		if (m_unk0x40 != NULL) {
			PearlDew0x0c* palette = static_cast<PearlDew0x0c*>(m_unk0x40);
			palette->Release();

			if (m_unk0x40 != NULL) {
				delete palette;
				m_unk0x40 = NULL;
			}
		}
		if (m_unk0x4c != NULL) {
			delete m_unk0x4c;
			m_unk0x4c = NULL;
		}
	}

	if (m_surface != NULL) {
		m_surface->Release();
		m_surface = NULL;
	}
}

// FUNCTION: GOLDP 0x10016440
void PurpleDune0x7c::FUN_10016440(BronzeFalcon0xc8770& p_renderer)
{
	if (m_pixelFlags & c_lockRequestRead) {
		FUN_10016460(p_renderer);
		FUN_10016100();
	}
}

// FUNCTION: GOLDP 0x10016460
undefined4 PurpleDune0x7c::FUN_10016460(BronzeFalcon0xc8770& p_renderer)
{
	GolSurfaceFormat textureFormat;

	GolCommonDrawState* drawState = p_renderer.GetDrawState();
	if (m_unk0x34 > 1) {
		textureFormat.m_redBitMask = 0xf800;
		textureFormat.m_grnBitMask = 0x07e0;
		textureFormat.m_bluBitMask = 0x001f;
		textureFormat.m_alpBitMask = 0;
		textureFormat.m_paletteMask = 0;
		textureFormat.m_unk0x10 = 0;
		textureFormat.m_bitsPerPixel = 16;
	}
	else {
		textureFormat = m_textureFormat;
	}

	p_renderer.SelectTextureFormat(textureFormat, &m_textureFormat2, static_cast<LegoU8>(m_unk0x36) & c_unk0x36Bit5);
	m_unk0x74 = m_width;
	m_unk0x78 = m_height;

	if (!p_renderer.TexturesMustBeSquare()) {
		if (m_width > m_height) {
			m_unk0x78 = m_width;
		}
		else {
			m_unk0x74 = m_height;
		}
	}

	if ((m_unk0x36 & c_unk0x36Bit5) && (p_renderer.GetUnk0x04() & WhiteFalcon0x140::c_flagBit9)) {
		m_unk0x36 |= c_unk0x36Bit7;
	}
	else {
		m_unk0x36 &= ~c_unk0x36Bit7;
	}

	if (p_renderer.VTable0x110()) {
		m_unk0x36 |= c_unk0x36Bit6;
	}
	else {
		m_unk0x36 &= ~c_unk0x36Bit6;
	}

	if (p_renderer.GetUnk0x04() & (WhiteFalcon0x140::c_flagBit7 | WhiteFalcon0x140::c_flagBit8)) {
		m_unk0x36 |= c_unk0x36Bit10;
	}
	else {
		m_unk0x36 &= ~c_unk0x36Bit10;
	}

	m_unk0x36 |= c_unk0x36Bit11;
	if (p_renderer.GetUnk0x04() & WhiteFalcon0x140::c_flagBit16) {
		return FUN_100168c0(p_renderer);
	}

	return FUN_100165c0(drawState, p_renderer);
}

// STUB: GOLDP 0x100165c0
undefined4 PurpleDune0x7c::FUN_100165c0(GolCommonDrawState*, BronzeFalcon0xc8770&)
{
	STUB(0x100165c0);
	return 0;
}

// STUB: GOLDP 0x100168c0
undefined4 PurpleDune0x7c::FUN_100168c0(BronzeFalcon0xc8770&)
{
	STUB(0x100168c0);
	return 0;
}
