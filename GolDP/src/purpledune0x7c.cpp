#include "purpledune0x7c.h"

#include "bronzefalcon0xc8770.h"
#include "ddrawutil.h"
#include "falcondunebag0x10.h"
#include "golerror.h"
#include "pearldew0x0c.h"

DECOMP_SIZE_ASSERT(PurpleDune0x7c, 0x7c)

// FUNCTION: GOLDP 0x10015b70
PurpleDune0x7c::PurpleDune0x7c()
	: m_unk0x40(NULL), m_unk0x44(NULL), m_surface(NULL), m_unk0x4c(NULL), m_unk0x74(0), m_unk0x78(0)
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

// STUB: GOLDP 0x10015c80
void PurpleDune0x7c::VTable0x30(WhiteFalcon0x140& p_renderer, undefined4*)
{
	// TODO
	STUB(0x10015c80);
}

// FUNCTION: GOLDP 0x10015d60
void PurpleDune0x7c::VTable0x34(
	WhiteFalcon0x140& p_renderer,
	const FalconTextureFormat& p_textureFormat,
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
		if (m_unk0x44 != NULL) {
			*p_pixels = m_unk0x44->m_pixels;
			*p_pitch = m_unk0x44->m_pitch;
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
		if (m_pixels == NULL && m_unk0x44 == NULL) {
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

	if (m_unk0x44 == NULL && (m_unk0x36 & c_unk0x36Bit5) && !(m_unk0x36 & c_unk0x36Bit10) &&
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
				LegoU32 red = (m_unk0x30.m_red >> redRightShift) << m_textureFormat2.GetRedBitShift();
				LegoU32 grn = (m_unk0x30.m_grn >> grnRightShift) << m_textureFormat2.GetGreenBitShift();
				LegoU32 blu = (m_unk0x30.m_blu >> bluRightShift) << m_textureFormat2.GetBlueBitShift();
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
				color = m_unk0x40->FindEntry(m_unk0x30);
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
		if (m_unk0x44 != NULL) {
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

// STUB: GOLDP 0x10016100
void PurpleDune0x7c::FUN_10016100()
{
	// TODO
	STUB(0x10016100);
}

// STUB: GOLDP 0x10016380
void PurpleDune0x7c::FUN_10016380()
{
	LegoU32 i;

	if (m_unk0x44 != NULL) {
		if (m_unk0x40 != NULL) {
			FalconDuneBag0x10* palette = static_cast<FalconDuneBag0x10*>(m_unk0x40);
			palette->Destroy();
			if (palette != NULL) {
				delete palette;
			}

			m_unk0x40 = NULL;
		}
		for (i = 0; i < m_unk0x34; i++) {
			if (m_unk0x44[i].m_pixels != NULL) {
				delete[] m_unk0x44[i].m_pixels;
				m_unk0x44[i].m_pixels = NULL;
			}
		}

		delete[] m_unk0x44;
		m_unk0x44 = NULL;
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

// STUB: GOLDP 0x10016460
void PurpleDune0x7c::FUN_10016460(BronzeFalcon0xc8770& p_renderer)
{
	p_renderer.GetDrawState();

	// TODO
	STUB(0x10016460);
}
