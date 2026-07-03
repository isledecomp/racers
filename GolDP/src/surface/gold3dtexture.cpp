#include "surface/gold3dtexture.h"

#include "device/ddrawutil.h"
#include "device/goldirectdrawpalette.h"
#include "golerror.h"
#include "golimgfile.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexturepalette.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolD3DTexture, 0x7c)
DECOMP_SIZE_ASSERT(MipmapLevel, 0x18)

extern const ColorRGBA g_transparentBlack;

// GLOBAL: GOLDP 0x100635c0
static GolImgFile g_uploadImgFile;

// FUNCTION: GOLDP 0x10015b70
GolD3DTexture::GolD3DTexture()
	: m_palette(NULL), m_mipmaps(NULL), m_surface(NULL), m_d3dTexture(NULL), m_deviceWidth(0), m_deviceHeight(0)
{
}

// FUNCTION: GOLDP 0x10015bf0
GolD3DTexture::~GolD3DTexture()
{
	ReleaseDeviceObjects();
	m_sourcePalette.Shutdown();

	if (m_pixels != NULL) {
		delete[] m_pixels;
		m_pixels = NULL;
	}

	m_pixelFlags = 0;
}

// FUNCTION: GOLDP 0x10015c80
void GolD3DTexture::LoadFromImgFile(GolRenderDevice& p_renderer, GolImgFile* p_source)
{
	GolSurfaceFormat textureFormat = p_source->GetTextureFormat();

	if (p_renderer.GetFlags() & GolRenderDevice::c_flagMipmapsEnabled) {
		m_mipmapCount = static_cast<LegoU16>(static_cast<GolD3DRenderDevice&>(p_renderer).GetDefaultMipmapCount());
	}

	Allocate(p_renderer, textureFormat, p_source->GetWidth(), p_source->GetHeight());
	p_source->SetKeepNibbleOrder(TRUE);
	p_source->SetRemapPureBlack(FALSE);
	p_source->LoadSurface(this, m_textureFlags & c_textureFlagFlipVertically, NULL);
	p_source->SetKeepNibbleOrder(FALSE);
}

// FUNCTION: GOLDP 0x10015d00
void GolD3DTexture::AllocateDeviceOnly(
	GolD3DRenderDevice& p_renderer,
	const GolSurfaceFormat& p_textureFormat,
	LegoU32 p_width,
	LegoU32 p_height
)
{
	if (m_pixelFlags & c_lockRequestRead) {
		Destroy();
	}

	m_pixelFlags |= c_lockRequestRead;
	m_height = static_cast<LegoU16>(p_height);
	m_width = static_cast<LegoU16>(p_width);
	m_textureFormat = p_textureFormat;
	m_pitch = (static_cast<LegoU32>(m_textureFormat.m_bitsPerPixel) * static_cast<LegoU16>(p_width) + 7) / 8;
	CreateDeviceObjects(p_renderer);
}

// FUNCTION: GOLDP 0x10015d60
void GolD3DTexture::Allocate(
	GolRenderDevice& p_renderer,
	const GolSurfaceFormat& p_textureFormat,
	LegoU32 p_width,
	LegoU32 p_height
)
{
	if (m_pixelFlags & c_lockRequestRead) {
		Destroy();
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
		m_sourcePalette.Initialize(p_textureFormat);
	}

	CreateDeviceObjects(static_cast<GolD3DRenderDevice&>(p_renderer));
}

// FUNCTION: GOLDP 0x10015e00
void GolD3DTexture::Destroy()
{
	ReleaseDeviceObjects();
	m_sourcePalette.Shutdown();

	if (m_pixels != NULL) {
		delete[] m_pixels;
		m_pixels = NULL;
	}

	m_pixelFlags = 0;
}

// FUNCTION: GOLDP 0x10015e30
void GolD3DTexture::LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags)
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
void GolD3DTexture::UnlockPixels()
{
	if (m_pixelFlags & c_lockRequestWrite) {
		if (m_pixels == NULL && m_mipmaps == NULL) {
			m_surface->Unlock(NULL);
			ApplyColorKey();
		}
		if (!(m_pixelFlags & c_lockFlagWrite) && (m_pixelFlags & c_lockFlagRead)) {
			m_pixelFlags &= ~(c_lockFlagWrite | c_lockFlagRead | c_lockFlagLocked);
		}
		else {
			m_pixelFlags &= ~(c_lockFlagWrite | c_lockFlagRead | c_lockFlagLocked);
			if (m_pixels != NULL) {
				UploadPixels();
			}
		}
	}
}

// FUNCTION: GOLDP 0x10015fb0
void GolD3DTexture::ApplyColorKey()
{
	DDCOLORKEY colorkey;
	ColorRGBA rgba;

	if (m_mipmaps == NULL && (m_textureFlags & c_textureFlagColorKeyed) &&
		!(m_textureFlags & c_textureFlagColorKeyInAlpha) && (m_textureFlags & c_textureFlagColorKeyDirty)) {
		if (m_deviceTextureFormat.m_paletteMask == 0) {
			LegoU32 color;

			if (m_textureFlags & c_textureFlagBlackColorKey) {
				color = 0;
			}
			else {
				LegoU32 redRightShift = 8 - m_deviceTextureFormat.GetRedBitCount();
				LegoU32 grnRightShift = 8 - m_deviceTextureFormat.GetGreenBitCount();
				LegoU32 bluRightShift = 8 - m_deviceTextureFormat.GetBlueBitCount();
				LegoU32 red = (m_colorKey.m_red >> redRightShift) << m_deviceTextureFormat.GetRedBitShift();
				LegoU32 grn = (m_colorKey.m_grn >> grnRightShift) << m_deviceTextureFormat.GetGreenBitShift();
				LegoU32 blu = (m_colorKey.m_blu >> bluRightShift) << m_deviceTextureFormat.GetBlueBitShift();
				color = blu | grn | red;
			}
			colorkey.dwColorSpaceHighValue = color;
			colorkey.dwColorSpaceLowValue = color;
		}
		else {
			LegoS32 color;

			if (m_textureFlags & c_textureFlagBlackColorKey) {
				rgba.m_red = 0;
				rgba.m_grn = 0;
				rgba.m_blu = 0;
				rgba.m_alp = 0;
				color = m_palette->FindEntry(rgba);
			}
			else {
				color = m_palette->FindEntry(m_colorKey);
			}
			colorkey.dwColorSpaceHighValue = color;
			colorkey.dwColorSpaceLowValue = colorkey.dwColorSpaceHighValue;

			if (color < 0) {
				return;
			}
		}
		m_surface->SetColorKey(DDCKEY_SRCBLT, &colorkey);
		m_textureFlags &= ~c_textureFlagColorKeyDirty;
	}
}

// FUNCTION: GOLDP 0x100160e0
GolPaletteBase* GolD3DTexture::GetPalette()
{
	if (m_pixels == NULL) {
		if (m_mipmaps != NULL) {
			return m_palette;
		}
		else {
			return m_palette;
		}
	}

	if (m_sourcePalette.HasEntries()) {
		return &m_sourcePalette;
	}

	return NULL;
}

// FUNCTION: GOLDP 0x10016100
void GolD3DTexture::UploadPixels()
{
	ColorRGBA* colorKey;
	LegoU8* dstPixels;
	LegoU32 dstPitch;
	LegoU32 paletteSize;
	ColorRGBA* paletteEntries;

	if (m_textureFormat.m_paletteMask != 0) {
		paletteEntries = m_sourcePalette.GetEntries();
		paletteSize = m_sourcePalette.GetPaletteSize();
	}
	else {
		paletteEntries = NULL;
		paletteSize = 0;
	}

	g_uploadImgFile.SetImageInfo(m_textureFormat, m_width, m_height, m_pitch, paletteEntries, paletteSize);

	if (m_textureFlags & c_textureFlagColorKeyed) {
		if (m_textureFlags & c_textureFlagBlackColorKey) {
			g_uploadImgFile.SetColorKeyReplacement(g_transparentBlack);
		}
		else {
			g_uploadImgFile.SetColorKeyReplacement(m_colorKey);
		}

		colorKey = &m_colorKey;
	}
	else {
		colorKey = NULL;
	}

	if (m_mipmaps != NULL) {
		g_uploadImgFile.SetRemapPureBlack(TRUE);
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

	g_uploadImgFile.ConvertImage(
		m_pixels,
		dstPixels,
		m_deviceWidth,
		m_deviceHeight,
		dstPitch,
		m_deviceTextureFormat,
		m_palette,
		0,
		colorKey
	);
	g_uploadImgFile.Destroy();

	if (m_mipmaps == NULL) {
		m_surface->Unlock(NULL);
		ApplyColorKey();
	}
	else {
		GenerateMipmaps();
	}
}

// FUNCTION: GOLDP 0x10016260
void GolD3DTexture::GenerateMipmaps()
{
	if (m_mipmaps != NULL) {
		if (m_mipmapCount > 1) {
			if (m_width == m_height) {
				ColorRGBA* colorKey;
				if (m_textureFlags & c_textureFlagColorKeyed) {
					if (m_textureFlags & c_textureFlagBlackColorKey) {
						g_uploadImgFile.SetColorKeyReplacement(g_transparentBlack);
					}
					else {
						g_uploadImgFile.SetColorKeyReplacement(m_colorKey);
					}

					colorKey = &m_colorKey;
				}
				else {
					colorKey = NULL;
				}

				LegoU8* srcPixels = m_mipmaps[0].m_pixels;
				LegoU32 srcPitch = m_mipmaps[0].m_pitch;
				LegoU32 width = m_deviceWidth;
				LegoU32 height = m_deviceHeight;

				for (LegoU32 i = 1; i < m_mipmapCount; i++) {
					g_uploadImgFile.SetImageInfo(m_deviceTextureFormat, width, height, srcPitch, NULL, 0);

					width >>= 1;
					height >>= 1;
					srcPitch = m_mipmaps[i].m_pitch;
					g_uploadImgFile.ConvertImageHalfSize(
						srcPixels,
						m_mipmaps[i].m_pixels,
						width,
						height,
						srcPitch,
						m_deviceTextureFormat,
						0,
						colorKey
					);

					srcPixels = m_mipmaps[i].m_pixels;
					g_uploadImgFile.Destroy();
				}
			}
		}
	}
}

// FUNCTION: GOLDP 0x10016380
void GolD3DTexture::ReleaseDeviceObjects()
{
	LegoU32 i;
	MipmapLevel* mipmaps = m_mipmaps;
	GolPaletteBase* palette = m_palette;

	if (mipmaps != NULL) {
		if (palette != NULL) {
			static_cast<GolD3DTexturePalette*>(palette)->Destroy();

			palette = m_palette;
			if (palette != NULL) {
				delete static_cast<GolD3DTexturePalette*>(palette);
			}

			m_palette = NULL;
		}
		for (i = 0; i < m_mipmapCount; i++) {
			if (m_mipmaps[i].m_pixels != NULL) {
				delete[] m_mipmaps[i].m_pixels;
				m_mipmaps[i].m_pixels = NULL;
			}
		}

		delete[] m_mipmaps;
		m_mipmaps = NULL;
	}
	else {
		if (palette != NULL) {
			static_cast<GolDirectDrawPalette*>(palette)->Release();

			palette = m_palette;
			if (palette != NULL) {
				delete static_cast<GolDirectDrawPalette*>(palette);
			}

			m_palette = NULL;
		}
		if (m_d3dTexture != NULL) {
			m_d3dTexture->Release();
			m_d3dTexture = NULL;
		}
	}

	if (m_surface != NULL) {
		m_surface->Release();
		m_surface = NULL;
	}
}

// FUNCTION: GOLDP 0x10016440
void GolD3DTexture::RestoreDeviceObjects(GolD3DRenderDevice& p_renderer)
{
	if (m_pixelFlags & c_lockRequestRead) {
		CreateDeviceObjects(p_renderer);
		UploadPixels();
	}
}

// FUNCTION: GOLDP 0x10016460
void GolD3DTexture::CreateDeviceObjects(GolD3DRenderDevice& p_renderer)
{
	GolSurfaceFormat textureFormat;

	GolCommonDrawState* drawState = p_renderer.GetDrawState();
	if (m_mipmapCount > 1) {
		textureFormat.m_redBitMask = 0xf800;
		textureFormat.m_grnBitMask = 0x07e0;
		textureFormat.m_bluBitMask = 0x001f;
		textureFormat.m_alpBitMask = 0;
		textureFormat.m_paletteMask = 0;
		textureFormat.m_intensityMask = 0;
		textureFormat.m_bitsPerPixel = 16;
	}
	else {
		textureFormat = m_textureFormat;
	}

	p_renderer.SelectTextureFormat(
		textureFormat,
		&m_deviceTextureFormat,
		static_cast<LegoU8>(m_textureFlags) & c_textureFlagColorKeyed
	);
	m_deviceWidth = m_width;
	m_deviceHeight = m_height;

	if (!p_renderer.TexturesMustBeSquare()) {
		if (m_width > m_height) {
			m_deviceHeight = m_width;
		}
		else {
			m_deviceWidth = m_height;
		}
	}

	if ((m_textureFlags & c_textureFlagColorKeyed) && (p_renderer.GetFlags() & GolRenderDevice::c_flagBlackColorKey)) {
		m_textureFlags |= c_textureFlagBlackColorKey;
	}
	else {
		m_textureFlags &= ~c_textureFlagBlackColorKey;
	}

	if (p_renderer.VTable0x110()) {
		m_textureFlags |= c_textureFlagBit6;
	}
	else {
		m_textureFlags &= ~c_textureFlagBit6;
	}

	if (p_renderer.GetFlags() &
		(GolRenderDevice::c_flagColorKeyAlphaBlend | GolRenderDevice::c_flagColorKeyAlphaTest)) {
		m_textureFlags |= c_textureFlagColorKeyInAlpha;
	}
	else {
		m_textureFlags &= ~c_textureFlagColorKeyInAlpha;
	}

	m_textureFlags |= c_textureFlagColorKeyDirty;
	if (p_renderer.GetFlags() & GolRenderDevice::c_flagSoftwareRenderer) {
		CreateMipmapBuffers(p_renderer);
	}
	else {
		CreateDirectDrawSurface(drawState, p_renderer);
	}
}

// FUNCTION: GOLDP 0x100165c0
void GolD3DTexture::CreateDirectDrawSurface(GolCommonDrawState* p_drawState, GolD3DRenderDevice& p_renderer)
{
	LPDIRECTDRAW4 ddraw = p_renderer.GetDirectDraw4();

	DDSURFACEDESC2 surfaceDesc;
	::memset(&surfaceDesc, 0, sizeof(surfaceDesc));
	surfaceDesc.dwSize = sizeof(surfaceDesc);
	surfaceDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	surfaceDesc.dwHeight = m_deviceHeight;
	surfaceDesc.dwWidth = m_deviceWidth;
	surfaceDesc.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
	surfaceDesc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	surfaceDesc.ddpfPixelFormat.dwFlags = DDPF_RGB;

	if (m_deviceTextureFormat.m_paletteMask != 0) {
		surfaceDesc.ddpfPixelFormat.dwRGBBitCount = m_deviceTextureFormat.m_bitsPerPixel;
		switch (surfaceDesc.ddpfPixelFormat.dwRGBBitCount) {
		case 1:
			surfaceDesc.ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_PALETTEINDEXED1;
			break;
		case 2:
			surfaceDesc.ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_PALETTEINDEXED2;
			break;
		case 4:
			surfaceDesc.ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_PALETTEINDEXED4;
			break;
		case 8:
			surfaceDesc.ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_PALETTEINDEXED8;
			break;
		}

		if ((m_palette = new GolDirectDrawPalette) == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		static_cast<GolDirectDrawPalette*>(m_palette)->CreateDirectDrawPalette(&p_renderer, &m_deviceTextureFormat);
	}
	else {
		surfaceDesc.ddpfPixelFormat.dwRGBBitCount = m_deviceTextureFormat.m_bitsPerPixel;
		surfaceDesc.ddpfPixelFormat.dwRBitMask = m_deviceTextureFormat.m_redBitMask;
		surfaceDesc.ddpfPixelFormat.dwGBitMask = m_deviceTextureFormat.m_grnBitMask;
		surfaceDesc.ddpfPixelFormat.dwBBitMask = m_deviceTextureFormat.m_bluBitMask;
		if (m_deviceTextureFormat.m_alpBitMask != 0) {
			surfaceDesc.ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_ALPHAPIXELS;
			surfaceDesc.ddpfPixelFormat.dwRGBAlphaBitMask = m_deviceTextureFormat.m_alpBitMask;
		}
	}

	if (m_textureFlags & c_textureFlagBit1) {
		surfaceDesc.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
	}
	if (m_textureFlags & c_textureFlagMipmapped) {
		if (p_drawState->IsHwAccelerated() && p_drawState->SupportsMipmap()) {
			DWORD flags = surfaceDesc.dwFlags;
			DWORD caps = surfaceDesc.ddsCaps.dwCaps;
			flags |= DDSD_MIPMAPCOUNT;
			caps |= DDSCAPS_COMPLEX | DDSCAPS_MIPMAP;
			surfaceDesc.dwFlags = flags;
			surfaceDesc.ddsCaps.dwCaps = caps;
			surfaceDesc.dwMipMapCount = m_mipmapCount;
		}
		else {
			m_textureFlags &= ~c_textureFlagMipmapped;
		}
	}

	surfaceDesc.ddsCaps.dwCaps2 |= DDSCAPS2_TEXTUREMANAGE;
	HRESULT result = ddraw->CreateSurface(&surfaceDesc, &m_surface, NULL);
	if (result) {
		if (result == DDERR_OUTOFVIDEOMEMORY) {
			GOL_FATALERROR_MESSAGE("Cannot create texture surface\nOut of video memory");
		}
		else {
			LegoChar errorMessage[64];
			::sprintf(errorMessage, "Error creating texture surface\nerror code = 0x%x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}

	result = m_surface->QueryInterface(IID_IDirect3DTexture2, (LPVOID*) &m_d3dTexture);
	if (result) {
		LegoChar errorMessage[64];
		::sprintf(errorMessage, "Unable to query surface texture interface\nerror %x", result);
		GOL_FATALERROR_MESSAGE(errorMessage);
	}

	if (m_deviceTextureFormat.m_paletteMask == 0) {
		result = m_surface->GetSurfaceDesc(&surfaceDesc);
		if (!result) {
			LegoU32 redBitMask = surfaceDesc.ddpfPixelFormat.dwRBitMask;
			LegoU32 grnBitMask = surfaceDesc.ddpfPixelFormat.dwGBitMask;
			LegoU32 bluBitMask = surfaceDesc.ddpfPixelFormat.dwBBitMask;
			LegoU32 alpBitMask = surfaceDesc.ddpfPixelFormat.dwRGBAlphaBitMask;
			m_deviceTextureFormat.m_redBitMask = redBitMask;
			m_deviceTextureFormat.m_grnBitMask = grnBitMask;
			m_deviceTextureFormat.m_bluBitMask = bluBitMask;
			m_deviceTextureFormat.m_alpBitMask = alpBitMask;
		}
	}
	else {
		result = m_surface->SetPalette(static_cast<GolDirectDrawPalette*>(m_palette)->GetPalette());
		if (result) {
			LegoChar errorMessage[64];
			::sprintf(errorMessage, "Unable to set texture palette\nerror %x", result);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}
	}
}

// FUNCTION: GOLDP 0x100168c0
void GolD3DTexture::CreateMipmapBuffers(GolD3DRenderDevice& p_renderer)
{
	LegoU32 width;
	LegoU32 height;
	LegoU32 minWidth;
	LegoU32 minHeight;
	LegoU32 i;

	if (m_mipmapCount < 1 || p_renderer.GetPaletteMode() == 1) {
		m_mipmapCount = 1;
	}

	if (m_deviceTextureFormat.m_bitsPerPixel != 8 && m_deviceTextureFormat.m_bitsPerPixel != 16) {
		m_mipmapCount = 1;
	}

	if (m_mipmapCount > 4) {
		m_mipmapCount = 4;
	}

	height = m_deviceHeight;
	width = m_deviceWidth;
	minWidth = p_renderer.GetMinimumTextureWidth(m_deviceTextureFormat.m_bitsPerPixel);
	minHeight = p_renderer.GetMinimumTextureHeight(m_deviceTextureFormat.m_bitsPerPixel);

	m_mipmaps = new MipmapLevel[m_mipmapCount];
	if (m_mipmaps == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_mipmapCount; i++) {
		if (width < minWidth || height < minHeight) {
			break;
		}

		MipmapLevel* mipmap = &m_mipmaps[i];

		mipmap->m_width = width;
		mipmap->m_height = height;
		mipmap->m_pitch = (m_deviceTextureFormat.m_bitsPerPixel * width + 7) >> 3;
		mipmap->m_bitsPerPixel = static_cast<LegoU8>(m_deviceTextureFormat.m_bitsPerPixel);
		mipmap->m_unk0x11 = 0xff;
		mipmap->m_bytesPerPixel =
			static_cast<LegoU8>((static_cast<LegoU32>(m_deviceTextureFormat.m_bitsPerPixel) + 7) >> 3);
		mipmap->m_sizeLog2 = 0xff;
		mipmap->m_pixels = NULL;

		if (m_deviceTextureFormat.m_paletteMask != 0 && p_renderer.GetPaletteMode() != 0) {
			m_palette = new GolD3DTexturePalette;
			if (m_palette == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			static_cast<GolD3DTexturePalette*>(m_palette)->Initialize(m_deviceTextureFormat);
			mipmap->m_paletteData = static_cast<GolD3DTexturePalette*>(m_palette)->m_mappedEntries;
		}
		else {
			mipmap->m_paletteData = NULL;
		}

		mipmap->m_pixels = new LegoU8[mipmap->m_pitch * mipmap->m_height];
		if (mipmap->m_pixels == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		width >>= 1;
		height >>= 1;
	}

	m_mipmapCount = static_cast<LegoU16>(i);
}
