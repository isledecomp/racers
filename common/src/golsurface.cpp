#include "golsurface.h"

#include "device/goldirectdrawpalette.h"

DECOMP_SIZE_ASSERT(GolSurface, 0x30)

// FUNCTION: GOLDP 0x1001cf00
// FUNCTION: LEGORACERS 0x00408490
GolSurface::GolSurface()
{
	m_pixels = NULL;
	m_auxPixels = NULL;
	m_pitch = 0;
	m_pixelFlags = 0;
	m_auxFlags = 0;
	m_width = 0;
	m_height = 0;
}

// FUNCTION: GOLDP 0x1001cf60
// FUNCTION: LEGORACERS 0x004084f0
GolSurface::~GolSurface()
{
}

// FUNCTION: GOLDP 0x1001cf70
// FUNCTION: LEGORACERS 0x00408500
void GolSurface::LockPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags)
{
	*p_pitch = m_pitch;
	*p_pixels = m_pixels;

	m_pixelFlags |= c_lockFlagLocked;
	if (p_flags & c_lockRequestRead) {
		m_pixelFlags |= c_lockFlagRead;
	}
	if (p_flags & c_lockRequestWrite) {
		m_pixelFlags |= c_lockFlagWrite;
	}
}

// FUNCTION: GOLDP 0x1001cfb0
// FUNCTION: LEGORACERS 0x00408540
void GolSurface::UnlockPixels()
{
	LegoU16 flags = m_pixelFlags;
	if (((LegoU8) flags) & c_lockFlagLocked) {
		flags &= ~c_lockStateMask;
		m_pixelFlags = flags;
	}
}

// FUNCTION: GOLDP 0x1001cfd0
// FUNCTION: LEGORACERS 0x00408560
void GolSurface::LockAuxPixels(LegoU8** p_pixels, LegoU32* p_pitch, LegoU32 p_flags)
{
	*p_pitch = m_pitch;
	*p_pixels = m_auxPixels;

	m_auxFlags |= c_lockFlagLocked;
	if (p_flags & c_lockRequestRead) {
		m_auxFlags |= c_lockFlagRead;
	}
	if (p_flags & c_lockRequestWrite) {
		m_auxFlags |= c_lockFlagWrite;
	}
}

// FUNCTION: GOLDP 0x1001d010
// FUNCTION: LEGORACERS 0x004085a0
void GolSurface::UnlockAuxPixels()
{
	if (m_auxFlags & c_lockFlagLocked) {
		m_auxFlags &= ~c_lockStateMask;
	}
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolSurface::Present(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolSurface::FinishPendingFlip()
{
	// empty
}

// FUNCTION: GOLDP 0x100016f0 FOLDED
// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
GolPaletteBase* GolSurface::GetPalette()
{
	return NULL;
}

// FUNCTION: GOLDP 0x1001d030
// FUNCTION: LEGORACERS 0x004085c0
void GolSurface::Fill(LegoU32 p_color)
{
	LegoU8* pixels;
	LegoU32 pitch;
	LegoBool32 unlockPixels;

	if (m_pixelFlags & c_lockFlagLocked) {
		pixels = m_pixels;
		pitch = m_pitch;
		unlockPixels = FALSE;
	}
	else {
		LockPixels(&pixels, &pitch, c_lockRequestWrite);
		unlockPixels = TRUE;
	}

	LegoU32 height = m_height;
	LegoU32 width = m_width;

	switch (m_textureFormat.m_bitsPerPixel) {
	case 4:
		p_color &= 0x0f;
		width >>= 1;
		p_color |= p_color << 4;
		// fall through
	case 8:
		if (height > 0) {
			LegoU32 rows = height;
			do {
				LegoU8* rowEnd = pixels + width;
				LegoU8* row = pixels;
				while (row < rowEnd) {
					*row++ = (LegoU8) p_color;
				}
				pixels += pitch;
			} while (--rows);
		}
		break;
	case 16:
		if (height > 0) {
			LegoU32 rows = height;
			do {
				LegoU16* row = (LegoU16*) pixels;
				LegoU16* rowEnd = row + width;
				while (row < rowEnd) {
					*row++ = (LegoU16) p_color;
				}
				pixels += pitch;
			} while (--rows);
		}
		break;
	case 24: {
		LegoU8 color0 = p_color;
		LegoU8 color1 = p_color >> 8;
		LegoU8 color2 = p_color >> 16;
		width *= 3;
		if (height > 0) {
			LegoU32 rows = height;
			do {
				LegoU8* rowEnd = pixels + width;
				LegoU8* row = pixels;
				while (row < rowEnd) {
					*row++ = color0;
					*row++ = color1;
					*row++ = color2;
				}
				pixels += pitch;
			} while (--rows);
		}
		break;
	}
	case 32:
		if (height > 0) {
			LegoU32 rows = height;
			do {
				LegoU32* row = (LegoU32*) pixels;
				LegoU32* rowEnd = row + width;
				while (row < rowEnd) {
					*row++ = p_color;
				}
				pixels += pitch;
			} while (--rows);
		}
		break;
	}

	if (unlockPixels) {
		UnlockPixels();
	}
}

// FUNCTION: GOLDP 0x1001d240
// STUB: LEGORACERS 0x004087d0
void GolSurface::Blit(LegoU32 p_x, LegoU32 p_y, GolSurface* p_source, Rect* p_sourceRect)
{
	LegoU8* destPixels;
	LegoU32 destPitch;
	LegoU32 copyWidth;
	LegoU32 sourcePitch;
	GolSurface* destSurface = this;
	LegoU32 copyHeight;
	LegoBool32 unlockSource;
	LegoBool32 unlockDest;
	LegoU8* sourcePixels;

	if (destSurface->m_textureFormat.m_bitsPerPixel != p_source->m_textureFormat.m_bitsPerPixel) {
		return;
	}

	if (p_sourceRect->m_right > p_source->m_width) {
		p_sourceRect->m_right = p_source->m_width;
	}
	if (p_sourceRect->m_bottom > p_source->m_height) {
		p_sourceRect->m_bottom = p_source->m_height;
	}
	if (p_sourceRect->m_left >= p_sourceRect->m_right) {
		return;
	}
	if (p_sourceRect->m_top >= p_sourceRect->m_bottom) {
		return;
	}

	copyHeight = p_sourceRect->m_bottom - p_sourceRect->m_top;
	LegoU32 destWidth = destSurface->m_width;
	copyWidth = p_sourceRect->m_right - p_sourceRect->m_left;

	if (p_x >= destWidth) {
		return;
	}

	LegoU32 destHeight = destSurface->m_height;
	if (p_y >= destHeight) {
		return;
	}
	if (p_x + copyWidth > destWidth) {
		copyWidth = destWidth - p_x;
	}
	if (p_y + copyHeight > destHeight) {
		copyHeight = destHeight - p_y;
	}

	if (destSurface->m_textureFormat.m_paletteMask) {
		GolPaletteBase* palette = destSurface->GetPalette();
		palette->CopyEntriesFrom(p_source->GetPalette());
	}

	if (destSurface->m_pixelFlags & c_lockFlagLocked) {
		destPixels = destSurface->m_pixels;
		unlockDest = FALSE;
		destPitch = destSurface->m_pitch;
	}
	else {
		destSurface->LockPixels(&destPixels, &destPitch, c_lockRequestWrite);
		unlockDest = TRUE;
	}

	if (p_source->m_pixelFlags & c_lockFlagLocked) {
		sourcePitch = p_source->m_pitch;
		sourcePixels = p_source->m_pixels;
		unlockSource = FALSE;
	}
	else {
		p_source->LockPixels(&sourcePixels, &sourcePitch, c_lockRequestRead);
		unlockSource = TRUE;
	}

	if (destSurface->m_textureFormat.m_bitsPerPixel == 4) {
		sourcePixels += sourcePitch * p_sourceRect->m_top;
		destPixels += p_y * destPitch;

		LegoU32 destMask;
		LegoU32 destShift;
		if (p_x & 1) {
			destMask = 0x0f;
			destShift = 4;
		}
		else {
			destMask = 0xf0;
			destShift = 0;
		}

		LegoU32 sourceMask;
		LegoU32 sourceShift;
		if (p_sourceRect->m_left & 1) {
			sourceMask = 0xf0;
			sourceShift = 4;
		}
		else {
			sourceMask = 0x0f;
			sourceShift = 0;
		}

		if (copyHeight > 0) {
			LegoU32 rows = copyHeight;
			do {
				LegoU32 rowDestMask = destMask;
				LegoU32 rowSourceMask = sourceMask;
				LegoU32 rowSourceShift = sourceShift;
				LegoU32 x = 0;
				LegoU32 rowDestShift = destShift;
				while (x < copyWidth) {
					LegoU8* dest = &destPixels[(x + p_x) >> 1];
					LegoU32 color = (sourcePixels[(x + p_sourceRect->m_left) >> 1] & rowSourceMask) >> rowSourceShift;
					color <<= rowDestShift;
					rowDestShift ^= 4;
					rowSourceMask = ~rowSourceMask;
					*dest = (*dest & rowDestMask) | (LegoU8) color;
					rowDestMask = ~rowDestMask;
					++x;
					rowSourceShift ^= 4;
				}
				destPixels += destPitch;
				sourcePixels += sourcePitch;
			} while (--rows);
		}
	}
	else {
		LegoU32 bytesPerPixel = destSurface->m_textureFormat.m_bitsPerPixel >> 3;
		sourcePixels += (sourcePitch * p_sourceRect->m_top) + (bytesPerPixel * p_sourceRect->m_left);
		destPixels += (p_y * destPitch) + (p_x * bytesPerPixel);

		LegoU32 rowBytes = copyWidth * bytesPerPixel;
		for (LegoU32 rows = copyHeight; rows; --rows) {
			LegoU8* source = sourcePixels;
			LegoU8* destEnd = destPixels + rowBytes;
			LegoU8* dest = destPixels;
			while (dest < destEnd) {
				*dest++ = *source++;
			}
			destPixels += destPitch;
			sourcePixels += sourcePitch;
		}
	}

	if (unlockSource) {
		p_source->UnlockPixels();
	}
	if (unlockDest) {
		destSurface->UnlockPixels();
	}
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
// FUNCTION: LEGORACERS 0x00416030 FOLDED
void GolSurface::BlitStretched(Rect*, GolSurface*, Rect*)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolSurface::CopyFromDisplay()
{
	// empty
}
