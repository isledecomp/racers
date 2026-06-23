#include "golimgfile.h"

#include "device/golpalettebase.h"
#include "golerror.h"

#include <limits.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolImgFile, 0x5b0)

// GLOBAL: GOLDP 0x1005cd90
// GLOBAL: LEGORACERS 0x004be258
ColorRGBA g_unk0x1005cd90 = {0x08, 0x08, 0x08, 0xff};

// FUNCTION: GOLDP 0x1001fe90
// FUNCTION: LEGORACERS 0x0040a8b0
GolImgFile::GolImgFile()
{
	m_width = 0;
	m_height = 0;
	m_rowByteStride = 0;
	m_hasColorKey = 0;
	m_paletteSize = 0;
	m_unk0x09c = 0;
	m_unk0x09d = 0;
	m_unk0x09e = 0;
	m_unk0x09f = 0;
	m_constPixelBits = 0;
	m_unk0x068 = 0;
	m_unk0x0a0.m_red = 0;
	m_unk0x0a0.m_grn = 0;
	m_unk0x0a0.m_blu = 0;
	m_unk0x0a0.m_alp = 0;
	m_colorKeyPixel = 0;
	m_unk0x5a8 = 0;
	m_unk0x5ac = 0;
	m_paletteCount = 0;
	m_paletteReservedEnd = 0;
	m_paletteCapacity = 0;
	m_paletteEntries = NULL;
}

// FUNCTION: GOLDP 0x1001ff50
// FUNCTION: LEGORACERS 0x0040a970
GolImgFile::~GolImgFile()
{
	Destroy();
}

// FUNCTION: GOLDP 0x1001ffc0
// FUNCTION: LEGORACERS 0x0040a9c0
void GolImgFile::VTable0x08(const LegoChar* p_fileName)
{
	LegoChar buffer[256];
	LegoS32 result;

	result = m_file.BufferedOpen(p_fileName, GolStream::c_modeRead, 8192);
	if (result != GolStream::e_ioSuccess) {
		::strcpy(buffer, GolStream::ErrorCodeToString(result));
		::strcat(buffer, "\nFile: ");
		::strcat(buffer, p_fileName);
		GOL_FATALERROR_MESSAGE(buffer);
	}

	m_format.m_redBitMask = 0;
	m_format.m_grnBitMask = 0;
	m_format.m_bluBitMask = 0;
	m_format.m_alpBitMask = 0;
	m_format.m_unk0x10 = 0;
	m_format.m_paletteMask = 0;
	m_unk0x5a8 = 0;
	m_unk0x5ac = 0;

	VTable0x00();
}

// FUNCTION: GOLDP 0x100200c0
// FUNCTION: LEGORACERS 0x0040aac0
void GolImgFile::Destroy()
{
	m_file.Dispose();
	if (m_paletteEntries != NULL) {
		delete[] m_paletteEntries;
		m_paletteEntries = NULL;
	}
}

// FUNCTION: GOLDP 0x100200f0
// FUNCTION: LEGORACERS 0x0040aaf0
void GolImgFile::FUN_100200f0(GolPaletteBase* p_palette, ColorRGBA* p_colorKey)
{
	LegoS32 colorKeyIndex = -1;
	LegoU32 sourcePaletteSize = 1 << m_format.m_bitsPerPixel;

	if (p_colorKey != NULL) {
		for (LegoU32 i = 0; i < sourcePaletteSize; i++) {
			if (p_colorKey->m_red == m_palette[i].m_red && p_colorKey->m_grn == m_palette[i].m_grn &&
				p_colorKey->m_blu == m_palette[i].m_blu) {
				colorKeyIndex = i;

				if (m_hasColorKey) {
					m_palette[i].m_red = m_unk0x0a0.m_red;
					m_palette[i].m_grn = m_unk0x0a0.m_grn;
					m_palette[i].m_blu = m_unk0x0a0.m_blu;
					m_palette[i].m_alp = 0;
				}
				break;
			}
		}
	}

	LegoU32 entryCount = p_palette->GetEntryCount();
	m_paletteCapacity = p_palette->GetPaletteSize();
	if (sourcePaletteSize > m_paletteCapacity) {
		sourcePaletteSize = m_paletteCapacity;
	}

	if (m_paletteCapacity == entryCount && p_colorKey == NULL) {
		for (LegoU32 i = 0; i < sourcePaletteSize; i++) {
			m_unk0x4a8[i] = static_cast<LegoU8>(i);
		}

		p_palette->SetEntries(m_palette, 0, sourcePaletteSize);
		return;
	}

	if (m_paletteEntries == NULL) {
		m_paletteEntries = new ColorRGBA[m_paletteCapacity];
		if (m_paletteEntries == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	LegoU32 firstEntry = p_palette->GetFirstEntry();
	m_paletteCount = firstEntry;
	if (firstEntry != 0) {
		p_palette->GetEntries(m_paletteEntries, 0, firstEntry);
	}

	m_paletteReservedEnd = m_paletteCapacity - firstEntry - entryCount;
	if (m_paletteReservedEnd != 0 && m_paletteCapacity > entryCount) {
		LegoU32 reservedStart = firstEntry + entryCount;
		p_palette->GetEntries(m_paletteEntries + reservedStart, reservedStart, m_paletteReservedEnd);
	}

	if (colorKeyIndex >= 0) {
		m_unk0x4a8[colorKeyIndex] = FUN_10020370(m_palette[colorKeyIndex]);
		for (LegoU32 i = 0; i < sourcePaletteSize; i++) {
			if (i != static_cast<LegoU32>(colorKeyIndex)) {
				m_unk0x4a8[i] = FUN_10020370(m_palette[i]);
			}
		}
	}
	else if (m_unk0x5ac) {
		for (LegoU32 i = 0; i < sourcePaletteSize; i++) {
			ColorRGBA* color = &m_palette[i];
			if (color->m_red == 0 && color->m_grn == 0 && color->m_blu == 0) {
				g_unk0x1005cd90.m_alp = color->m_alp;
				m_unk0x4a8[i] = FUN_10020370(g_unk0x1005cd90);
			}
			else {
				m_unk0x4a8[i] = FUN_10020370(*color);
			}
		}
	}
	else {
		for (LegoU32 i = 0; i < sourcePaletteSize; i++) {
			m_unk0x4a8[i] = FUN_10020370(m_palette[i]);
		}
	}

	p_palette->SetEntries(m_paletteEntries + firstEntry, firstEntry, m_paletteCount - firstEntry);
	delete[] m_paletteEntries;
	m_paletteEntries = NULL;
}

// FUNCTION: GOLDP 0x10020370
// FUNCTION: LEGORACERS 0x0040ad70
LegoU32 GolImgFile::FUN_10020370(const ColorRGBA& p_rgba)
{
	LegoU32 i;

	for (i = 0; i < m_paletteCount; i++) {
		if (p_rgba.m_red == m_paletteEntries[i].m_red && p_rgba.m_grn == m_paletteEntries[i].m_grn &&
			p_rgba.m_blu == m_paletteEntries[i].m_blu) {
			return i;
		}
	}

	for (i = m_paletteCapacity - m_paletteReservedEnd; i < m_paletteCapacity; i++) {
		if (p_rgba.m_red == m_paletteEntries[i].m_red && p_rgba.m_grn == m_paletteEntries[i].m_grn &&
			p_rgba.m_blu == m_paletteEntries[i].m_blu) {
			return i;
		}
	}

	if (m_paletteReservedEnd + m_paletteCount >= m_paletteCapacity) {
		LegoU32 bestMatch = 0;
		LegoS32 bestMatchDiff = INT_MAX;
		for (i = 0; i < m_paletteCapacity; i++) {
			LegoS32 dR = static_cast<LegoU32>(m_paletteEntries[i].m_red) - static_cast<LegoU32>(p_rgba.m_red);
			LegoS32 dG = static_cast<LegoU32>(m_paletteEntries[i].m_grn) - static_cast<LegoU32>(p_rgba.m_grn);
			LegoS32 dB = static_cast<LegoU32>(m_paletteEntries[i].m_blu) - static_cast<LegoU32>(p_rgba.m_blu);
			LegoS32 d = dR * dR + dG * dG + dB * dB;
			if (d < bestMatchDiff) {
				bestMatchDiff = d;
				bestMatch = i;
			}
		}
		return bestMatch;
	}
	else {
		LegoU32 idx = m_paletteCount;
		m_paletteEntries[idx].m_red = p_rgba.m_red;
		m_paletteEntries[idx].m_grn = p_rgba.m_grn;
		m_paletteEntries[idx].m_blu = p_rgba.m_blu;
		m_paletteEntries[idx].m_alp = p_rgba.m_alp;
		m_paletteCount++;
		return idx;
	}
}

// FUNCTION: GOLDP 0x100204d0
// FUNCTION: LEGORACERS 0x0040aed0
void GolImgFile::FUN_100204d0(const GolSurfaceFormat& p_format, ColorRGBA* p_colorKey)
{
	const GolSurfaceFormat& destFormat = p_format;
	m_hasColorKey = FALSE;

	if (destFormat.m_paletteMask != 0) {
		if (p_colorKey != NULL) {
			m_hasColorKey = TRUE;
		}
		return;
	}

	switch (m_format.m_bitsPerPixel) {
	case 4:
		m_srcStrideMask = 0x80;
		break;
	case 8:
		m_srcStrideMask = 0x88;
		break;
	case 16:
		m_srcStrideMask = 0x99;
		break;
	case 24:
		m_srcStrideMask = 0xbb;
		break;
	case 32:
		m_srcStrideMask = 0xff;
		break;
	default:
		GOL_FATALERROR_MESSAGE("Unsupported color depth.");
		break;
	}

	LegoU32 srcRedBitCount;
	LegoU32 srcGreenBitCount;
	LegoU32 srcBlueBitCount;
	LegoU32 srcAlphaBitCount;

	if (m_format.m_paletteMask > 0) {
		srcRedBitCount = 8;
		m_redSrcShift = 0;
		srcGreenBitCount = srcRedBitCount;
		m_grnSrcShift = 0;
		m_bluSrcShift = 0;
		srcBlueBitCount = srcRedBitCount;
		m_alpSrcShift = 0;
		srcAlphaBitCount = 0;
	}
	else {
		m_redSrcShift = m_format.GetRedBitShift();
		srcRedBitCount = m_format.GetRedBitCount();
		m_grnSrcShift = m_format.GetGreenBitShift();
		srcGreenBitCount = m_format.GetGreenBitCount();
		m_bluSrcShift = m_format.GetBlueBitShift();
		srcBlueBitCount = m_format.GetBlueBitCount();
		m_alpSrcShift = m_format.GetAlphaBitShift();
		srcAlphaBitCount = m_format.GetAlphaBitCount();
	}

	LegoU32 destRedBitCount = destFormat.GetRedBitCount();
	if (srcRedBitCount > destRedBitCount) {
		m_redSrcShift += srcRedBitCount - destRedBitCount;
	}
	m_redDstShift = destFormat.GetRedBitShift();
	if (destRedBitCount > srcRedBitCount) {
		m_redDstShift += destRedBitCount - srcRedBitCount;
	}

	LegoU32 destGreenBitCount = destFormat.GetGreenBitCount();
	if (srcGreenBitCount > destGreenBitCount) {
		m_grnSrcShift += srcGreenBitCount - destGreenBitCount;
	}
	m_grnDstShift = destFormat.GetGreenBitShift();
	if (destGreenBitCount > srcGreenBitCount) {
		m_grnDstShift += destGreenBitCount - srcGreenBitCount;
	}

	LegoU32 destBlueBitCount = destFormat.GetBlueBitCount();
	if (srcBlueBitCount > destBlueBitCount) {
		m_bluSrcShift += srcBlueBitCount - destBlueBitCount;
	}
	m_bluDstShift = destFormat.GetBlueBitShift();
	if (destBlueBitCount > srcBlueBitCount) {
		m_bluDstShift += destBlueBitCount - srcBlueBitCount;
	}

	if (p_colorKey != NULL) {
		m_hasColorKey = TRUE;
		m_unk0x09c = p_colorKey->m_red >> (8 - destRedBitCount);
		m_unk0x09d = p_colorKey->m_grn >> (8 - destGreenBitCount);
		m_unk0x09e = p_colorKey->m_blu >> (8 - destBlueBitCount);
		m_alpSrcShift = 0;
		m_alpDstShift = 0;

		LegoU32 red = (m_unk0x0a0.m_red >> (8 - destRedBitCount)) << m_redDstShift;
		LegoU32 grn = (m_unk0x0a0.m_grn >> (8 - destGreenBitCount)) << m_grnDstShift;
		LegoU32 blu = (m_unk0x0a0.m_blu >> (8 - destBlueBitCount)) << m_bluDstShift;
		m_colorKeyPixel = red | grn | blu;
		m_constPixelBits = destFormat.m_alpBitMask;
		return;
	}

	LegoU32 destAlphaBitCount = destFormat.GetAlphaBitCount();
	if (srcAlphaBitCount > destAlphaBitCount) {
		m_alpSrcShift += srcAlphaBitCount - destAlphaBitCount;
	}
	m_alpDstShift = destFormat.GetAlphaBitShift();
	if (destAlphaBitCount > srcAlphaBitCount) {
		m_alpDstShift += destAlphaBitCount - srcAlphaBitCount;
	}
}

// STUB: GOLDP 0x100207e0
// FUNCTION: LEGORACERS 0x0040b1e0
void GolImgFile::FUN_100207e0(const void* p_src, void* p_dst, const GolSurfaceFormat& p_format)
{
	const LegoU8* src = static_cast<const LegoU8*>(p_src);
	LegoU8* dst = static_cast<LegoU8*>(p_dst);

	if (m_format.m_paletteMask > 0) {
		if (p_format.m_paletteMask != 0) {
			if (m_format.m_bitsPerPixel == 4) {
				if (p_format.m_bitsPerPixel == 4) {
					if (m_unk0x5a8) {
						FUN_0040bbe0(src, dst);
					}
					else {
						FUN_0040bc30(src, dst);
					}
					return;
				}

				if (p_format.m_bitsPerPixel == 8) {
					FUN_0040bc80(src, dst);
					return;
				}
			}
			else if (m_format.m_bitsPerPixel == 8 && p_format.m_bitsPerPixel == 8) {
				FUN_0040bce0(src, dst);
				return;
			}
		}
		else if (m_format.m_bitsPerPixel == 4) {
			switch (p_format.m_bitsPerPixel) {
			case 8:
				FUN_100212f0(src, dst);
				return;
			case 16:
				FUN_10021660(src, reinterpret_cast<LegoU16*>(dst));
				return;
			case 24:
				FUN_100219e0(src, dst);
				return;
			case 32:
				FUN_10021e10(src, reinterpret_cast<LegoU32*>(dst));
				return;
			}
		}
		else {
			switch (p_format.m_bitsPerPixel) {
			case 8:
				FUN_10022180(src, dst);
				return;
			case 16:
				FUN_100222c0(src, reinterpret_cast<LegoU16*>(dst));
				return;
			case 24:
				FUN_10022400(src, dst);
				return;
			case 32:
				FUN_10022560(src, reinterpret_cast<LegoU32*>(dst));
				return;
			}
		}
	}
	else {
		if (m_paletteSize > 0) {
			GOL_FATALERROR_MESSAGE("Intensity formats not supported");
			return;
		}

		if (p_format.m_paletteMask != 0) {
			GOL_FATALERROR_MESSAGE("RGB to CI conversion not supported");
			return;
		}

		switch (p_format.m_bitsPerPixel) {
		case 8:
			FUN_10020b90(src, dst);
			return;
		case 16:
			FUN_10020d60(src, reinterpret_cast<LegoU16*>(dst));
			return;
		case 24:
			FUN_10020f20(src, dst);
			return;
		case 32:
			FUN_10021130(src, reinterpret_cast<LegoU32*>(dst));
			return;
		}
	}
}

// FUNCTION: GOLDP 0x10020b90
// FUNCTION: LEGORACERS 0x0040b480
void GolImgFile::FUN_10020b90(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* endDst = p_dst + m_width;
	if (m_hasColorKey) {
		for (; p_dst < endDst; p_dst++) {
			LegoU32 u32 = *p_src;
			p_src += (m_srcStrideMask >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_srcStrideMask >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_srcStrideMask >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_srcStrideMask >> 3) & 0x1;
			LegoU32 r = (m_format.m_redBitMask & u32) >> m_redSrcShift;
			LegoU32 g = (m_format.m_grnBitMask & u32) >> m_grnSrcShift;
			LegoU32 b = (m_format.m_bluBitMask & u32) >> m_bluSrcShift;
			LegoU8 pixel;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				pixel = static_cast<LegoU8>(m_colorKeyPixel);
			}
			else {
				pixel = r << m_redDstShift;
				pixel |= g << m_grnDstShift;
				pixel |= b << m_bluDstShift;
				pixel |= m_constPixelBits;
			}
			*p_dst = pixel;
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			LegoU32 u32 = *p_src;
			p_src += (m_srcStrideMask >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_srcStrideMask >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_srcStrideMask >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_srcStrideMask >> 3) & 0x1;
			LegoU32 alp = ((m_format.m_alpBitMask & u32) >> m_alpSrcShift) << m_alpDstShift;
			LegoU32 blu = ((m_format.m_bluBitMask & u32) >> m_bluSrcShift) << m_bluDstShift;
			LegoU32 grn = ((m_format.m_grnBitMask & u32) >> m_grnSrcShift) << m_grnDstShift;
			LegoU32 red = ((m_format.m_redBitMask & u32) >> m_redSrcShift) << m_redDstShift;
			*p_dst = alp | blu | grn | red;
		}
	}
}

// FUNCTION: GOLDP 0x10020d60
// FUNCTION: LEGORACERS 0x0040b650
void GolImgFile::FUN_10020d60(const LegoU8* p_src, LegoU16* p_dst)
{
	LegoU16* endDst = p_dst + m_width;
	LegoU32 u32;
	if (m_hasColorKey) {
		for (; p_dst < endDst; p_dst++) {
			u32 = *p_src;
			p_src += (m_srcStrideMask >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_srcStrideMask >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_srcStrideMask >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_srcStrideMask >> 3) & 0x1;
			LegoU32 r = (m_format.m_redBitMask & u32) >> m_redSrcShift;
			LegoU32 g = (m_format.m_grnBitMask & u32) >> m_grnSrcShift;
			LegoU32 b = (m_format.m_bluBitMask & u32) >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst = m_colorKeyPixel;
			}
			else {
				LegoU32 pixel = r << m_redDstShift;
				pixel |= g << m_grnDstShift;
				pixel |= b << m_bluDstShift;
				pixel |= m_constPixelBits;
				*p_dst = pixel;
			}
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			u32 = *p_src;
			p_src += (m_srcStrideMask >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_srcStrideMask >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_srcStrideMask >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_srcStrideMask >> 3) & 0x1;
			LegoU32 blu = ((m_format.m_bluBitMask & u32) >> m_bluSrcShift) << m_bluDstShift;
			LegoU32 grn = ((m_format.m_grnBitMask & u32) >> m_grnSrcShift) << m_grnDstShift;
			LegoU32 red = ((m_format.m_redBitMask & u32) >> m_redSrcShift) << m_redDstShift;
			LegoU32 alp = ((m_format.m_alpBitMask & u32) >> m_alpSrcShift) << m_alpDstShift;
			*p_dst = blu | grn | red | alp;
		}
	}
}

// FUNCTION: GOLDP 0x10020f20
// FUNCTION: LEGORACERS 0x0040b810
void GolImgFile::FUN_10020f20(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU32 i;
	LegoU32 u32;
	if (m_hasColorKey) {
		for (i = 0; i < m_width; i++) {
			u32 = *p_src;
			p_src += (m_srcStrideMask >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_srcStrideMask >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_srcStrideMask >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_srcStrideMask >> 3) & 0x1;
			LegoU32 r = (m_format.m_redBitMask & u32) >> m_redSrcShift;
			LegoU32 g = (m_format.m_grnBitMask & u32) >> m_grnSrcShift;
			LegoU32 b = (m_format.m_bluBitMask & u32) >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
				*p_dst++ = m_colorKeyPixel >> 8;
				*p_dst++ = m_colorKeyPixel >> 16;
			}
			else {
				LegoU32 rgb = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
				*p_dst++ = rgb;
				*p_dst++ = rgb >> 8;
				*p_dst++ = rgb >> 16;
			}
		}
	}
	else {
		for (i = 0; i < m_width; i++) {
			u32 = *p_src;
			p_src += (m_srcStrideMask >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_srcStrideMask >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_srcStrideMask >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_srcStrideMask >> 3) & 0x1;
			LegoU32 blu = ((m_format.m_bluBitMask & u32) >> m_bluSrcShift) << m_bluDstShift;
			LegoU32 grn = ((m_format.m_grnBitMask & u32) >> m_grnSrcShift) << m_grnDstShift;
			LegoU32 alp = ((m_format.m_alpBitMask & u32) >> m_alpSrcShift) << m_alpDstShift;
			LegoU32 red = ((m_format.m_redBitMask & u32) >> m_redSrcShift) << m_redDstShift;
			LegoU32 rgb = blu | grn | alp | red;
			*p_dst++ = rgb;
			*p_dst++ = rgb >> 8;
			*p_dst++ = rgb >> 16;
		}
	}
}

// FUNCTION: GOLDP 0x10021130
// FUNCTION: LEGORACERS 0x0040ba20
void GolImgFile::FUN_10021130(const LegoU8* p_src, LegoU32* p_dst)
{
	LegoU32* endDst = p_dst + m_width;
	LegoU32 u32;
	if (m_hasColorKey) {
		for (; p_dst < endDst; p_dst++) {
			u32 = *p_src << 0;
			p_src += (m_srcStrideMask >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_srcStrideMask >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_srcStrideMask >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_srcStrideMask >> 3) & 0x1;
			LegoU32 r = (m_format.m_redBitMask & u32) >> m_redSrcShift;
			LegoU32 g = (m_format.m_grnBitMask & u32) >> m_grnSrcShift;
			LegoU32 b = (m_format.m_bluBitMask & u32) >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst = m_colorKeyPixel;
			}
			else {
				*p_dst = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
			}
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			u32 = *p_src << 0;
			p_src += (m_srcStrideMask >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_srcStrideMask >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_srcStrideMask >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_srcStrideMask >> 3) & 0x1;
			*p_dst = (((m_format.m_redBitMask & u32) >> m_redSrcShift) << m_redDstShift) |
					 (((m_format.m_grnBitMask & u32) >> m_grnSrcShift) << m_grnDstShift) |
					 (((m_format.m_bluBitMask & u32) >> m_bluSrcShift) << m_bluDstShift) |
					 (((m_format.m_alpBitMask & u32) >> m_alpSrcShift) << m_alpDstShift);
		}
	}
}

// FUNCTION: LEGORACERS 0x0040bbe0
void GolImgFile::FUN_0040bbe0(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* end = p_dst + ((m_width + 1) >> 1);
	for (; p_dst < end; p_dst++) {
		LegoU8 low = m_unk0x4a8[*p_src & 0x0f];
		*p_dst = low;
		*p_dst = (m_unk0x4a8[*p_src >> 4] << 4) | low;
		p_src++;
	}
}

// FUNCTION: LEGORACERS 0x0040bc30
void GolImgFile::FUN_0040bc30(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* end = p_dst + ((m_width + 1) >> 1);
	for (; p_dst < end; p_dst++) {
		LegoU8 low = m_unk0x4a8[*p_src >> 4];
		*p_dst = low;
		*p_dst = (m_unk0x4a8[*p_src & 0x0f] << 4) | low;
		p_src++;
	}
}

// FUNCTION: LEGORACERS 0x0040bc80
void GolImgFile::FUN_0040bc80(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* end = p_dst + m_width;
	for (; p_dst + 1 < end; p_dst += 2) {
		*p_dst = m_unk0x4a8[*p_src >> 4];
		p_dst[1] = m_unk0x4a8[*p_src & 0x0f];
		p_src++;
	}
	if (p_dst < end) {
		*p_dst = m_unk0x4a8[*p_src & 0x0f];
	}
}

// FUNCTION: LEGORACERS 0x0040bce0
void GolImgFile::FUN_0040bce0(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* end = p_dst + m_width;
	for (; p_dst < end; p_dst++) {
		*p_dst = m_unk0x4a8[*p_src++];
	}
}

// STUB: GOLDP 0x100212f0
// STUB: LEGORACERS 0x0040bd10
void GolImgFile::FUN_100212f0(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* endDst = p_dst + m_width;
	LegoU8* dstOff1;
	if (m_hasColorKey) {
		for (dstOff1 = p_dst + 1; dstOff1 < endDst; p_dst += 2, dstOff1 += 2) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				p_dst[0] = m_colorKeyPixel;
			}
			else {
				p_dst[0] = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
			}

			c = &m_palette[*p_src & 0x0f];
			p_src++;
			r = c->m_red >> m_redSrcShift;
			g = c->m_grn >> m_grnSrcShift;
			b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				p_dst[1] = m_colorKeyPixel;
			}
			else {
				p_dst[1] = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
			}
		}
		if (p_dst < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				p_dst[0] = m_colorKeyPixel;
			}
			else {
				p_dst[0] = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
			}
		}
	}
	else {
		for (dstOff1 = p_dst + 1; dstOff1 < endDst; p_dst += 2, dstOff1 += 2) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			p_dst[0] = ((c->m_red >> m_redSrcShift) << m_redDstShift) | ((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
					   ((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
			c = &m_palette[*p_src & 0x0f];
			p_src++;
			p_dst[1] = ((c->m_red >> m_redSrcShift) << m_redDstShift) | ((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
					   ((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
		}
		if (p_dst < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			p_dst[0] = ((c->m_red >> m_redSrcShift) << m_redDstShift) | ((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
					   ((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
		}
	}
}

// FUNCTION: GOLDP 0x10021660
// STUB: LEGORACERS 0x0040c080
void GolImgFile::FUN_10021660(const LegoU8* p_src, LegoU16* p_dst)
{
	LegoU16* endDst = p_dst + m_width;
	LegoU8 index;

	if (m_hasColorKey) {
		while (p_dst + 1 < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
			}
			else {
				r <<= m_redDstShift;
				g <<= m_grnDstShift;
				b <<= m_bluDstShift;
				LegoU32 pixel = r | g;
				pixel |= b;
				pixel |= m_constPixelBits;
				*p_dst++ = pixel;
			}

			index = *p_src & 0x0f;
			p_src++;
			c = &m_palette[index];
			r = c->m_red >> m_redSrcShift;
			g = c->m_grn >> m_grnSrcShift;
			b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
			}
			else {
				r <<= m_redDstShift;
				g <<= m_grnDstShift;
				b <<= m_bluDstShift;
				LegoU32 pixel = r | g;
				pixel |= b;
				pixel |= m_constPixelBits;
				*p_dst++ = pixel;
			}
		}
		if (p_dst < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				p_dst[0] = m_colorKeyPixel;
			}
			else {
				r <<= m_redDstShift;
				g <<= m_grnDstShift;
				b <<= m_bluDstShift;
				LegoU32 pixel = r | g;
				pixel |= b;
				pixel |= m_constPixelBits;
				p_dst[0] = pixel;
			}
		}
	}
	else {
		while (p_dst + 1 < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			b <<= m_bluDstShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			g <<= m_grnDstShift;
			LegoU32 r = c->m_red >> m_redSrcShift;
			r <<= m_redDstShift;
			LegoU32 pixel = b | g;
			pixel |= r;
			*p_dst++ = pixel;

			index = *p_src & 0x0f;
			p_src++;
			c = &m_palette[index];
			b = c->m_blu >> m_bluSrcShift;
			b <<= m_bluDstShift;
			g = c->m_grn >> m_grnSrcShift;
			g <<= m_grnDstShift;
			r = c->m_red >> m_redSrcShift;
			r <<= m_redDstShift;
			pixel = b | g;
			pixel |= r;
			*p_dst++ = pixel;
		}
		if (p_dst < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			b <<= m_bluDstShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			g <<= m_grnDstShift;
			LegoU32 r = c->m_red >> m_redSrcShift;
			r <<= m_redDstShift;
			LegoU32 pixel = b | g;
			pixel |= r;
			p_dst[0] = pixel;
		}
	}
}

// STUB: GOLDP 0x100219e0
// FUNCTION: LEGORACERS 0x0040c400
void GolImgFile::FUN_100219e0(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU32 i = 1;
	LegoU32 pixelIndex = 0;

	if (m_hasColorKey) {
		while (i < m_width) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			LegoU32 pixel;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
				*p_dst++ = m_colorKeyPixel >> 8;
				*p_dst++ = m_colorKeyPixel >> 16;
			}
			else {
				pixel = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
				*p_dst++ = pixel;
				*p_dst++ = pixel >> 8;
				*p_dst++ = pixel >> 16;
			}

			c = &m_palette[*p_src & 0x0f];
			p_src++;
			r = c->m_red >> m_redSrcShift;
			g = c->m_grn >> m_grnSrcShift;
			b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
				*p_dst++ = m_colorKeyPixel >> 8;
				*p_dst++ = m_colorKeyPixel >> 16;
			}
			else {
				pixel = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
				*p_dst++ = pixel;
				*p_dst++ = pixel >> 8;
				*p_dst++ = pixel >> 16;
			}

			i += 2;
			pixelIndex += 2;
		}
		if (pixelIndex < m_width) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			LegoU32 pixel;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
				*p_dst++ = m_colorKeyPixel >> 8;
				*p_dst = m_colorKeyPixel >> 16;
			}
			else {
				pixel = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
				*p_dst++ = pixel;
				*p_dst++ = pixel >> 8;
				*p_dst = pixel >> 16;
			}
		}
	}
	else {
		while (i < m_width) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 pixel = ((c->m_red >> m_redSrcShift) << m_redDstShift) |
							((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
							((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
			*p_dst++ = pixel;
			*p_dst++ = pixel >> 8;
			*p_dst++ = pixel >> 16;

			LegoU8 index = *p_src & 0x0f;
			p_src++;
			c = &m_palette[index];
			pixel = ((c->m_red >> m_redSrcShift) << m_redDstShift) | ((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
					((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
			*p_dst++ = pixel;
			*p_dst++ = pixel >> 8;
			*p_dst++ = pixel >> 16;

			i += 2;
			pixelIndex += 2;
		}
		if (pixelIndex < m_width) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 pixel = ((c->m_red >> m_redSrcShift) << m_redDstShift) |
							((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
							((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
			*p_dst++ = pixel;
			*p_dst++ = pixel >> 8;
			*p_dst = pixel >> 16;
		}
	}
}

// STUB: GOLDP 0x10021e10
// FUNCTION: LEGORACERS 0x0040c830
void GolImgFile::FUN_10021e10(const LegoU8* p_src, LegoU32* p_dst)
{
	LegoU32* endDst = p_dst + m_width;
	LegoU8 index;

	if (m_hasColorKey) {
		while (p_dst + 1 < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
			}
			else {
				*p_dst++ = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
			}

			index = *p_src & 0x0f;
			p_src++;
			c = &m_palette[index];
			r = c->m_red >> m_redSrcShift;
			g = c->m_grn >> m_grnSrcShift;
			b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
			}
			else {
				*p_dst++ = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
			}
		}
		if (p_dst < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				p_dst[0] = m_colorKeyPixel;
			}
			else {
				p_dst[0] = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
			}
		}
	}
	else {
		while (p_dst + 1 < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			*p_dst++ = ((c->m_red >> m_redSrcShift) << m_redDstShift) | ((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
					   ((c->m_blu >> m_bluSrcShift) << m_bluDstShift);

			index = *p_src & 0x0f;
			p_src++;
			c = &m_palette[index];
			*p_dst++ = ((c->m_red >> m_redSrcShift) << m_redDstShift) | ((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
					   ((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
		}
		if (p_dst < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			p_dst[0] = ((c->m_red >> m_redSrcShift) << m_redDstShift) | ((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
					   ((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
		}
	}
}

// FUNCTION: GOLDP 0x10022180
// FUNCTION: LEGORACERS 0x0040cba0
void GolImgFile::FUN_10022180(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* endDst = p_dst + m_width;
	if (m_hasColorKey) {
		for (; p_dst < endDst; p_dst++) {
			const ColorRGBA* c = &m_palette[*p_src++];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst = m_colorKeyPixel;
			}
			else {
				b <<= m_bluDstShift;
				g <<= m_grnDstShift;
				r <<= m_redDstShift;
				LegoU32 pixel = b | g;
				pixel |= r;
				r = m_constPixelBits;
				pixel |= r;
				*p_dst = pixel;
			}
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			const ColorRGBA* c = &m_palette[*p_src++];
			*p_dst = ((c->m_red >> m_redSrcShift) << m_redDstShift) | ((c->m_blu >> m_bluSrcShift) << m_bluDstShift) |
					 ((c->m_grn >> m_grnSrcShift) << m_grnDstShift);
		}
	}
}

// FUNCTION: GOLDP 0x100222c0
// FUNCTION: LEGORACERS 0x0040cce0
void GolImgFile::FUN_100222c0(const LegoU8* p_src, LegoU16* p_dst)
{
	LegoU16* endDst = p_dst + m_width;
	if (m_hasColorKey) {
		for (; p_dst < endDst; p_dst++) {
			const ColorRGBA* c = &m_palette[*p_src++];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst = m_colorKeyPixel;
			}
			else {
				b <<= m_bluDstShift;
				g <<= m_grnDstShift;
				r <<= m_redDstShift;
				LegoU32 pixel = b | g;
				pixel |= r;
				r = m_constPixelBits;
				pixel |= r;
				*p_dst = pixel;
			}
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			const ColorRGBA* c = &m_palette[*p_src++];
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			b <<= m_bluDstShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			g <<= m_grnDstShift;
			LegoU32 r = c->m_red >> m_redSrcShift;
			r <<= m_redDstShift;
			LegoU32 pixel = b | g;
			pixel |= r;
			*p_dst = pixel;
		}
	}
}

// STUB: GOLDP 0x10022400
// FUNCTION: LEGORACERS 0x0040ce20
void GolImgFile::FUN_10022400(const LegoU8* p_src, LegoU8* p_dst)
{
	const LegoU8* endSrc = p_src + m_width;

	if (m_hasColorKey) {
		for (; p_src < endSrc;) {
			const ColorRGBA* c = &m_palette[*p_src++];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			LegoU32 pixel;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_colorKeyPixel;
				*p_dst++ = m_colorKeyPixel >> 8;
				*p_dst++ = m_colorKeyPixel >> 16;
			}
			else {
				pixel = (r << m_redDstShift) | (g << m_grnDstShift) | (b << m_bluDstShift) | m_constPixelBits;
				*p_dst++ = pixel;
				*p_dst++ = pixel >> 8;
				*p_dst++ = pixel >> 16;
			}
		}
	}
	else {
		for (; p_src < endSrc;) {
			const ColorRGBA* c = &m_palette[*p_src++];
			LegoU32 pixel = ((c->m_red >> m_redSrcShift) << m_redDstShift) |
							((c->m_grn >> m_grnSrcShift) << m_grnDstShift) |
							((c->m_blu >> m_bluSrcShift) << m_bluDstShift);
			*p_dst++ = pixel;
			*p_dst++ = pixel >> 8;
			*p_dst++ = pixel >> 16;
		}
	}
}

// FUNCTION: GOLDP 0x10022560
// FUNCTION: LEGORACERS 0x0040cf80
void GolImgFile::FUN_10022560(const LegoU8* p_src, LegoU32* p_dst)
{
	LegoU32* endDst = p_dst + m_width;
	if (m_hasColorKey) {
		for (; p_dst < endDst; p_dst++) {
			const ColorRGBA* c = &m_palette[*p_src++];
			LegoU32 r = c->m_red >> m_redSrcShift;
			LegoU32 g = c->m_grn >> m_grnSrcShift;
			LegoU32 b = c->m_blu >> m_bluSrcShift;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst = m_colorKeyPixel;
			}
			else {
				LegoU32 pixel = b << m_bluDstShift;
				pixel |= g << m_grnDstShift;
				pixel |= r << m_redDstShift;
				pixel |= m_constPixelBits;
				*p_dst = pixel;
			}
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			const ColorRGBA* c = &m_palette[*p_src++];
			LegoU32 pixel = (c->m_blu >> m_bluSrcShift) << m_bluDstShift;
			pixel |= (c->m_grn >> m_grnSrcShift) << m_grnDstShift;
			pixel |= (c->m_red >> m_redSrcShift) << m_redDstShift;
			*p_dst = pixel;
		}
	}
}

// FUNCTION: GOLDP 0x100226a0
// FUNCTION: LEGORACERS 0x0040d0c0
const LegoChar* GolImgFile::GetSuffix()
{
	return ".img";
}

void GolImgFile::VTable0x14(LegoU8*, SilverDune0x30*, LegoU32, ColorRGBA*)
{
	// empty
}

// FUNCTION: GOLDP 0x100226c0
void GolImgFile::FUN_100226c0(
	const GolSurfaceFormat& p_format,
	LegoU32 p_width,
	LegoU32 p_height,
	LegoU32 p_rowByteStride,
	ColorRGBA* p_paletteColors,
	LegoU32 p_paletteSize
)
{
	if (m_file.IsOpen()) {
		Destroy();
	}

	m_format = p_format;
	m_width = p_width;
	m_height = p_height;
	m_rowByteStride = p_rowByteStride;
	m_paletteSize = 1 << m_format.m_bitsPerPixel;
	m_unk0x5a8 = 0;
	m_unk0x5ac = 0;

	if (p_paletteColors != NULL && p_paletteSize != 0) {
		::memcpy(m_palette, p_paletteColors, p_paletteSize * sizeof(*p_paletteColors));
	}
}

// FUNCTION: GOLDP 0x10022730
void GolImgFile::FUN_10022730(
	LegoU8* p_src,
	LegoU8* p_dst,
	LegoU32 p_width,
	LegoU32 p_height,
	LegoU32 p_pitch,
	const GolSurfaceFormat& p_format,
	GolPaletteBase* p_palette,
	undefined4 p_unk0x20,
	ColorRGBA* p_colorKey
)
{
	LegoU32 xScale = 1;
	LegoU32 yScale = 1;
	LegoU32 height = p_height;
	LegoU32 width = p_width;

	if (m_height != height || m_width != width) {
		xScale = width / m_width;
		yScale = height / m_height;
	}

	if (m_height > height || m_width > width) {
		GOL_FATALERROR_MESSAGE("Invalid image size for given storage");
	}

	FUN_100204d0(p_format, p_colorKey);
	if (p_format.m_paletteMask != 0 && p_palette != NULL) {
		FUN_100200f0(p_palette, p_colorKey);
	}

	LegoS32 pitch;
	if (p_unk0x20 != 0) {
		pitch = p_pitch;
		p_dst += (height - 1) * pitch;
		pitch = -pitch;
	}
	else {
		pitch = p_pitch;
	}

	LegoU8* src = p_src;
	for (LegoU32 y = 0; y < m_height; y++) {
		FUN_100207e0(src, p_dst, p_format);

		if (xScale > 1) {
			FUN_100229b0(p_dst, xScale, width, p_format.m_bitsPerPixel);
		}

		for (LegoU32 repeat = 1; repeat < yScale; repeat++) {
			::memcpy(p_dst + pitch, p_dst, pitch);
			p_dst += pitch;
		}

		src += m_rowByteStride;
		p_dst += pitch;
	}
}

// STUB: GOLDP 0x10022880
void GolImgFile::FUN_10022880(
	LegoU8* p_src,
	LegoU8* p_dst,
	LegoU32 p_width,
	LegoU32 p_height,
	LegoU32 p_pitch,
	const GolSurfaceFormat& p_format,
	undefined4,
	ColorRGBA* p_colorKey
)
{
	if ((m_height >> 1) != p_height || (m_width >> 1) != p_width) {
		GOL_FATALERROR_MESSAGE("Invalid image size for given storage");
	}

	FUN_100204d0(p_format, p_colorKey);

	LegoU32 rows = m_height >> 1;
	LegoU32 srcPitch = m_rowByteStride << 1;

	if (p_format.m_paletteMask != 0) {
		for (; rows != 0; rows--) {
			LegoU8* end = p_dst + (m_width >> 1);
			if (p_dst < end) {
				LegoU8* dst = p_dst - 1;
				LegoU8* bottom = p_src + m_rowByteStride - 1;
				LegoU8* top = p_src - 1;

				for (; dst + 1 < end;) {
					top += 2;
					LegoU8 topLeft = top[-1];
					LegoU8 topRight = top[0];
					bottom += 2;
					dst++;

					if (topLeft == topRight) {
						*dst = topRight;
					}
					else {
						LegoU8 bottomLeft = bottom[-1];
						if (bottomLeft != topLeft && bottomLeft != topRight) {
							*dst = bottom[0];
						}
						else {
							*dst = bottomLeft;
						}
					}
				}
			}

			p_src += srcPitch;
			p_dst += p_pitch;
		}
	}
	else {
		for (; rows != 0; rows--) {
			FUN_10022b80(p_src, p_src + m_rowByteStride, p_dst);
			p_src += srcPitch;
			p_dst += p_pitch;
		}
	}
}

// FUNCTION: GOLDP 0x100229b0
// FUNCTION: LEGORACERS 0x0040d0d0
void GolImgFile::FUN_100229b0(LegoU8* p_row, LegoS32 p_xScale, LegoU32 p_scaledWidth, LegoU32 p_bitsPerPixel)
{
	LegoS32 x;
	LegoS32 i;

	switch (p_bitsPerPixel) {
	case 4: {
		LegoU32 width = m_width;
		LegoU8* dst = p_row + (p_scaledWidth >> 1) - 1;
		LegoU8* src = p_row + (width >> 1) - 1;
		LegoU32 dstNibble = 1;
		for (x = width - 1; x >= 0; x--) {
			LegoU32 pixel;
			if (x & 1) {
				pixel = *src & 0x0f;
			}
			else {
				pixel = *src >> 4;
				src--;
			}

			for (i = p_xScale; i > 0; i--) {
				if (dstNibble & 1) {
					*dst |= pixel << 4;
				}
				else {
					*dst = pixel;
					dst--;
				}
				dstNibble++;
			}
		}
		break;
	}
	case 8: {
		LegoU8* dst = p_row + p_scaledWidth - 1;
		LegoU8* src = p_row + m_width - 1;
		for (x = m_width; x > 0; x--) {
			for (i = p_xScale; i > 0; i--) {
				*dst-- = *src;
			}
			src--;
		}
		break;
	}
	case 15:
	case 16: {
		LegoU16* dst = reinterpret_cast<LegoU16*>(p_row) + p_scaledWidth - 1;
		LegoU16* src = reinterpret_cast<LegoU16*>(p_row) + m_width - 1;
		for (x = m_width; x > 0; x--) {
			for (i = p_xScale; i > 0; i--) {
				*dst-- = *src;
			}
			src--;
		}
		break;
	}
	case 24: {
		LegoU8* dst = p_row + p_scaledWidth * 3 - 3;
		LegoU8* src = p_row + m_width * 3 - 3;
		for (x = m_width; x > 0; x--) {
			for (i = p_xScale; i > 0; i--) {
				dst[0] = src[0];
				dst[1] = src[1];
				dst[2] = src[2];
				dst -= 3;
			}
			src -= 3;
		}
		break;
	}
	case 32: {
		LegoU32* dst = reinterpret_cast<LegoU32*>(p_row) + p_scaledWidth - 1;
		LegoU32* src = reinterpret_cast<LegoU32*>(p_row) + m_width - 1;
		for (x = m_width; x > 0; x--) {
			for (i = p_xScale; i > 0; i--) {
				*dst-- = *src;
			}
			src--;
		}
		break;
	}
	}
}

// STUB: GOLDP 0x10022b80
void GolImgFile::FUN_10022b80(LegoU8* p_top, LegoU8* p_bottom, LegoU8* p_dst)
{
	LegoU8* end = p_dst + (m_width >> 1) * sizeof(LegoU16);
	for (; p_dst < end; p_dst += sizeof(LegoU16)) {
		LegoU32 samples[4];
		LegoU8* src = p_top;

		samples[0] = *src;
		src += (m_srcStrideMask >> 0) & 1;
		samples[0] |= *src << 8;
		src += (m_srcStrideMask >> 1) & 1;
		samples[0] |= *src << 16;
		src += (m_srcStrideMask >> 2) & 1;
		samples[0] |= *src << 24;
		src += (m_srcStrideMask >> 3) & 1;

		samples[1] = *src;
		src += (m_srcStrideMask >> 0) & 1;
		samples[1] |= *src << 8;
		src += (m_srcStrideMask >> 1) & 1;
		samples[1] |= *src << 16;
		src += (m_srcStrideMask >> 2) & 1;
		samples[1] |= *src << 24;
		src += (m_srcStrideMask >> 3) & 1;

		p_top = src;
		src = p_bottom;

		samples[2] = *src;
		src += (m_srcStrideMask >> 0) & 1;
		samples[2] |= *src << 8;
		src += (m_srcStrideMask >> 1) & 1;
		samples[2] |= *src << 16;
		src += (m_srcStrideMask >> 2) & 1;
		samples[2] |= *src << 24;
		src += (m_srcStrideMask >> 3) & 1;

		samples[3] = *src;
		src += (m_srcStrideMask >> 0) & 1;
		samples[3] |= *src << 8;
		src += (m_srcStrideMask >> 1) & 1;
		samples[3] |= *src << 16;
		src += (m_srcStrideMask >> 2) & 1;
		samples[3] |= *src << 24;
		src += (m_srcStrideMask >> 3) & 1;

		p_bottom = src;

		LegoU32 red = 0;
		LegoU32 grn = 0;
		LegoU32 blu = 0;

		if (m_hasColorKey) {
			LegoBool32 foundColorKey = FALSE;
			for (LegoU32 i = 0; i < 4; i++) {
				LegoU32 sampleRed = (samples[i] & m_format.m_redBitMask) >> m_redSrcShift;
				LegoU32 sampleGrn = (samples[i] & m_format.m_grnBitMask) >> m_grnSrcShift;
				LegoU32 sampleBlu = (samples[i] & m_format.m_bluBitMask) >> m_bluSrcShift;

				if (sampleRed == m_unk0x09c && sampleGrn == m_unk0x09d && sampleBlu == m_unk0x09e) {
					*reinterpret_cast<LegoU16*>(p_dst) = static_cast<LegoU16>(m_colorKeyPixel);
					foundColorKey = TRUE;
					break;
				}

				red += sampleRed;
				grn += sampleGrn;
				blu += sampleBlu;
			}

			if (!foundColorKey) {
				LegoU32 pixel = ((red >> 2) << m_redDstShift) | ((grn >> 2) << m_grnDstShift) |
								((blu >> 2) << m_bluDstShift) | m_constPixelBits;
				*reinterpret_cast<LegoU16*>(p_dst) = static_cast<LegoU16>(pixel);
			}
		}
		else {
			LegoU32 alp = 0;
			for (LegoU32 i = 0; i < 4; i++) {
				red += (samples[i] & m_format.m_redBitMask) >> m_redSrcShift;
				grn += (samples[i] & m_format.m_grnBitMask) >> m_grnSrcShift;
				blu += (samples[i] & m_format.m_bluBitMask) >> m_bluSrcShift;
				alp += (samples[i] & m_format.m_alpBitMask) >> m_alpSrcShift;
			}

			LegoU32 pixel = ((red >> 2) << m_redDstShift) | ((grn >> 2) << m_grnDstShift) |
							((blu >> 2) << m_bluDstShift) | ((alp >> 2) << m_alpDstShift);
			*reinterpret_cast<LegoU16*>(p_dst) = static_cast<LegoU16>(pixel);
		}
	}
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
// FUNCTION: LEGORACERS 0x00416030 FOLDED
void GolImgFile::VTable0x1c(WhiteBaffoon0x50*, LegoU32, ColorRGBA*)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
// FUNCTION: LEGORACERS 0x00416030 FOLDED
void GolImgFile::VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, ColorRGBA* p_colorKey)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void GolImgFile::VTable0x00()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolImgFile::VTable0x18(LegoU8* p_buffer)
{
	// empty
}
