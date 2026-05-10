#include "golimgfile.h"

#include "golerror.h"

#include <limits.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolImgFile, 0x5b0)

// FUNCTION: GOLDP 0x1001fe90
// FUNCTION: LEGORACERS 0x0040a8b0
GolImgFile::GolImgFile()
{
	m_width = 0;
	m_height = 0;
	m_rowByteStride = 0;
	m_unk0x098 = 0;
	m_paletteSize = 0;
	m_unk0x09c = 0;
	m_unk0x09d = 0;
	m_unk0x09e = 0;
	m_unk0x09f = 0;
	m_unk0x074 = 0;
	m_unk0x068 = 0;
	m_unk0x0a0 = 0;
	m_unk0x0a1 = 0;
	m_unk0x0a2 = 0;
	m_unk0x0a3 = 0;
	m_unk0x0a4 = 0;
	m_unk0x5a8 = 0;
	m_unk0x5ac = 0;
	m_unk0x004 = 0;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0x010 = NULL;
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
	if (m_unk0x010 != NULL) {
		delete[] m_unk0x010;
		m_unk0x010 = NULL;
	}
}

// STUB: GOLDP 0x100200f0
void GolImgFile::FUN_100200f0(IPalette0x4*, undefined4*)
{
	// TODO
	STUB(0x100200f0);
}

// FUNCTION: GOLDP 0x10020370
LegoU32 GolImgFile::FUN_10020370(const ColorRGBA& p_rgba)
{
	LegoU32 i;
	for (i = 0; i < m_unk0x004; i++) {
		if (p_rgba.m_red == m_unk0x010[i].m_red && p_rgba.m_grn == m_unk0x010[i].m_grn &&
			p_rgba.m_blu == m_unk0x010[i].m_blu) {
			return i;
		}
	}
	for (i = m_unk0x00c - m_unk0x008; i < m_unk0x00c; i++) {
		if (p_rgba.m_red == m_unk0x010[i].m_red && p_rgba.m_grn == m_unk0x010[i].m_grn &&
			p_rgba.m_blu == m_unk0x010[i].m_blu) {
			return i;
		}
	}
	if (m_unk0x008 + m_unk0x004 >= m_unk0x00c) {
		LegoU32 bestMatch = 0;
		LegoS32 bestMatchDiff = INT_MAX;
		for (i = 0; i < m_unk0x00c; i++) {
			LegoS32 dR = static_cast<LegoU32>(m_unk0x010[i].m_red) - static_cast<LegoU32>(p_rgba.m_red);
			LegoS32 dG = static_cast<LegoU32>(m_unk0x010[i].m_grn) - static_cast<LegoU32>(p_rgba.m_grn);
			LegoS32 dB = static_cast<LegoU32>(m_unk0x010[i].m_blu) - static_cast<LegoU32>(p_rgba.m_blu);
			LegoS32 d = dR * dR + dG * dG + dB * dB;
			if (d < bestMatchDiff) {
				bestMatchDiff = d;
				bestMatch = i;
			}
		}
		return bestMatch;
	}
	else {
		LegoU32 idx = m_unk0x004;
		m_unk0x010[idx].m_red = p_rgba.m_red;
		m_unk0x010[idx].m_grn = p_rgba.m_grn;
		m_unk0x010[idx].m_blu = p_rgba.m_blu;
		m_unk0x010[idx].m_alp = p_rgba.m_alp;
		m_unk0x004++;
		return idx;
	}
}

// STUB: GOLDP 0x100204d0
void GolImgFile::FUN_100204d0(const GolSurfaceFormat&, undefined4*)
{
	// TODO
	STUB(0x100204d0);
}

// STUB: GOLDP 0x100207e0
void GolImgFile::FUN_100207e0(const void* p_src, void* p_dst, const GolSurfaceFormat& p_format)
{
	// TODO
	STUB(0x100207e0);
}

// FUNCTION: GOLDP 0x10020b90
void GolImgFile::FUN_10020b90(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* endDst = p_dst + m_width;
	if (m_unk0x098) {
		for (; p_dst < endDst; p_dst++) {
			LegoU32 u32 = *p_src;
			p_src += (m_unk0x070 >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_unk0x070 >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_unk0x070 >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_unk0x070 >> 3) & 0x1;
			LegoU32 r = (m_format.m_redBitMask & u32) >> m_unk0x078;
			LegoU32 g = (m_format.m_grnBitMask & u32) >> m_unk0x07c;
			LegoU32 b = (m_format.m_bluBitMask & u32) >> m_unk0x080;
			LegoU8 pixel;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				pixel = static_cast<LegoU8>(m_unk0x0a4);
			}
			else {
				pixel = r << m_unk0x088;
				pixel |= g << m_unk0x08c;
				pixel |= b << m_unk0x090;
				pixel |= m_unk0x074;
			}
			*p_dst = pixel;
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			LegoU32 u32 = *p_src;
			p_src += (m_unk0x070 >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_unk0x070 >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_unk0x070 >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_unk0x070 >> 3) & 0x1;
			LegoU32 alp = ((m_format.m_alpBitMask & u32) >> m_unk0x084) << m_unk0x094;
			LegoU32 blu = ((m_format.m_bluBitMask & u32) >> m_unk0x080) << m_unk0x090;
			LegoU32 grn = ((m_format.m_grnBitMask & u32) >> m_unk0x07c) << m_unk0x08c;
			LegoU32 red = ((m_format.m_redBitMask & u32) >> m_unk0x078) << m_unk0x088;
			*p_dst = alp | blu | grn | red;
		}
	}
}

// FUNCTION: GOLDP 0x10020d60
void GolImgFile::FUN_10020d60(const LegoU8* p_src, LegoU16* p_dst)
{
	LegoU16* endDst = p_dst + m_width;
	if (m_unk0x098) {
		for (; p_dst < endDst; p_dst++) {
			LegoU32 u32 = *p_src;
			p_src += (m_unk0x070 >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_unk0x070 >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_unk0x070 >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_unk0x070 >> 3) & 0x1;
			LegoU32 r = (m_format.m_redBitMask & u32) >> m_unk0x078;
			LegoU32 g = (m_format.m_grnBitMask & u32) >> m_unk0x07c;
			LegoU32 b = (m_format.m_bluBitMask & u32) >> m_unk0x080;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst = m_unk0x0a4;
			}
			else {
				LegoU32 pixel = r << m_unk0x088;
				pixel |= g << m_unk0x08c;
				pixel |= b << m_unk0x090;
				pixel |= m_unk0x074;
				*p_dst = pixel;
			}
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			LegoU32 u32 = *p_src;
			p_src += (m_unk0x070 >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_unk0x070 >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_unk0x070 >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_unk0x070 >> 3) & 0x1;
			LegoU32 blu = ((m_format.m_bluBitMask & u32) >> m_unk0x080) << m_unk0x090;
			LegoU32 grn = ((m_format.m_grnBitMask & u32) >> m_unk0x07c) << m_unk0x08c;
			LegoU32 red = ((m_format.m_redBitMask & u32) >> m_unk0x078) << m_unk0x088;
			LegoU32 alp = ((m_format.m_alpBitMask & u32) >> m_unk0x084) << m_unk0x094;
			*p_dst = blu | grn | red | alp;
		}
	}
}

// FUNCTION: GOLDP 0x10020f20
void GolImgFile::FUN_10020f20(const LegoU8* p_src, LegoU8* p_dst)
{
	LegoU32 i;
	if (m_unk0x098) {
		for (i = 0; i < m_width; i++) {
			LegoU32 u32 = *p_src;
			p_src += (m_unk0x070 >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_unk0x070 >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_unk0x070 >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_unk0x070 >> 3) & 0x1;
			LegoU32 r = (m_format.m_redBitMask & u32) >> m_unk0x078;
			LegoU32 g = (m_format.m_grnBitMask & u32) >> m_unk0x07c;
			LegoU32 b = (m_format.m_bluBitMask & u32) >> m_unk0x080;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst++ = m_unk0x0a4;
				*p_dst++ = m_unk0x0a4 >> 8;
				*p_dst++ = m_unk0x0a4 >> 16;
			}
			else {
				LegoU32 rgb = (r << m_unk0x088) | (g << m_unk0x08c) | (b << m_unk0x090) | m_unk0x074;
				*p_dst++ = rgb;
				*p_dst++ = rgb >> 8;
				*p_dst++ = rgb >> 16;
			}
		}
	}
	else {
		for (i = 0; i < m_width; i++) {
			LegoU32 u32 = *p_src;
			p_src += (m_unk0x070 >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_unk0x070 >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_unk0x070 >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_unk0x070 >> 3) & 0x1;
			LegoU32 blu = ((m_format.m_bluBitMask & u32) >> m_unk0x080) << m_unk0x090;
			LegoU32 grn = ((m_format.m_grnBitMask & u32) >> m_unk0x07c) << m_unk0x08c;
			LegoU32 alp = ((m_format.m_alpBitMask & u32) >> m_unk0x084) << m_unk0x094;
			LegoU32 red = ((m_format.m_redBitMask & u32) >> m_unk0x078) << m_unk0x088;
			LegoU32 rgb = blu | grn | alp | red;
			*p_dst++ = rgb;
			*p_dst++ = rgb >> 8;
			*p_dst++ = rgb >> 16;
		}
	}
}

// FUNCTION: GOLDP 0x10021130
void GolImgFile::FUN_10021130(const LegoU8* p_src, LegoU32* p_dst)
{
	LegoU32* endDst = p_dst + m_width;
	if (m_unk0x098) {
		for (; p_dst < endDst; p_dst++) {
			LegoU32 u32 = *p_src << 0;
			p_src += (m_unk0x070 >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_unk0x070 >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_unk0x070 >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_unk0x070 >> 3) & 0x1;
			LegoU32 r = (m_format.m_redBitMask & u32) >> m_unk0x078;
			LegoU32 g = (m_format.m_grnBitMask & u32) >> m_unk0x07c;
			LegoU32 b = (m_format.m_bluBitMask & u32) >> m_unk0x080;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				*p_dst = m_unk0x0a4;
			}
			else {
				*p_dst = (r << m_unk0x088) | (g << m_unk0x08c) | (b << m_unk0x090) | m_unk0x074;
			}
		}
	}
	else {
		for (; p_dst < endDst; p_dst++) {
			LegoU32 u32 = *p_src << 0;
			p_src += (m_unk0x070 >> 0) & 0x1;
			u32 |= *p_src << 8;
			p_src += (m_unk0x070 >> 1) & 0x1;
			u32 |= *p_src << 16;
			p_src += (m_unk0x070 >> 2) & 0x1;
			u32 |= *p_src << 24;
			p_src += (m_unk0x070 >> 3) & 0x1;
			*p_dst = (((m_format.m_redBitMask & u32) >> m_unk0x078) << m_unk0x088) |
					 (((m_format.m_grnBitMask & u32) >> m_unk0x07c) << m_unk0x08c) |
					 (((m_format.m_bluBitMask & u32) >> m_unk0x080) << m_unk0x090) |
					 (((m_format.m_alpBitMask & u32) >> m_unk0x084) << m_unk0x094);
		}
	}
}

// STUB: GOLDP 0x100212f0
void GolImgFile::FUN_100212f0(const LegoU8* p_src, LegoU8* p_dst)
{
	// TODO
	STUB(0x100212f0);
}

// FUNCTION: GOLDP 0x10021660
void GolImgFile::FUN_10021660(const LegoU8* p_src, LegoU16* p_dst)
{
	LegoU16* endDst = p_dst + m_width;
	LegoU16* dstOff1;
	if (m_unk0x098) {
		for (dstOff1 = p_dst + 1; dstOff1 < endDst; p_dst += 2, dstOff1 += 2) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_unk0x078;
			LegoU32 g = c->m_grn >> m_unk0x07c;
			LegoU32 b = c->m_blu >> m_unk0x080;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				p_dst[0] = m_unk0x0a4;
			}
			else {
				p_dst[0] = (r << m_unk0x088) | (g << m_unk0x08c) | (b << m_unk0x090) | m_unk0x074;
			}
			c = &m_palette[*p_src & 0x0f];
			p_src++;
			r = c->m_red >> m_unk0x078;
			g = c->m_grn >> m_unk0x07c;
			b = c->m_blu >> m_unk0x080;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				p_dst[1] = m_unk0x0a4;
			}
			else {
				p_dst[1] = (r << m_unk0x088) | (g << m_unk0x08c) | (b << m_unk0x090) | m_unk0x074;
			}
		}
		if (p_dst < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			LegoU32 r = c->m_red >> m_unk0x078;
			LegoU32 g = c->m_grn >> m_unk0x07c;
			LegoU32 b = c->m_blu >> m_unk0x080;
			if (r == m_unk0x09c && g == m_unk0x09d && b == m_unk0x09e) {
				p_dst[0] = m_unk0x0a4;
			}
			else {
				p_dst[0] = (r << m_unk0x088) | (g << m_unk0x08c) | (b << m_unk0x090) | m_unk0x074;
			}
		}
	}
	else {
		for (dstOff1 = p_dst + 1; dstOff1 < endDst; p_dst += 2, dstOff1 += 2) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			p_dst[0] = ((c->m_red >> m_unk0x078) << m_unk0x088) | ((c->m_grn >> m_unk0x07c) << m_unk0x08c) |
					   ((c->m_blu >> m_unk0x080) << m_unk0x090);
			c = &m_palette[*p_src & 0x0f];
			p_src++;
			p_dst[1] = ((c->m_red >> m_unk0x078) << m_unk0x088) | ((c->m_grn >> m_unk0x07c) << m_unk0x08c) |
					   ((c->m_blu >> m_unk0x080) << m_unk0x090);
		}
		if (p_dst < endDst) {
			const ColorRGBA* c = &m_palette[*p_src >> 4];
			p_dst[0] = ((c->m_red >> m_unk0x078) << m_unk0x088) | ((c->m_grn >> m_unk0x07c) << m_unk0x08c) |
					   ((c->m_blu >> m_unk0x080) << m_unk0x090);
		}
	}
}

// STUB: GOLDP 0x100219e0
void GolImgFile::FUN_100219e0(const LegoU8* p_src, LegoU8* p_dst)
{
	// TODO
	STUB(0x100219e0);
}

// STUB: GOLDP 0x10021e10
void GolImgFile::FUN_10021e10(const LegoU8* p_src, LegoU32* p_dst)
{
	// TODO
	STUB(0x10021e10);
}

// STUB: GOLDP 0x10022180
void GolImgFile::FUN_10022180(const LegoU8* p_src, LegoU8* p_dst)
{
	// TODO
	STUB(0x10022180);
}

// STUB: GOLDP 0x100222c0
void GolImgFile::FUN_100222c0(const LegoU8* p_src, LegoU16* p_dst)
{
	// TODO
	STUB(0x100222c0);
}

// STUB: GOLDP 0x10022400
void GolImgFile::FUN_10022400(const LegoU8* p_src, LegoU8* p_dst)
{
	// TODO
	STUB(0x10022400);
}

// STUB: GOLDP 0x10022560
void GolImgFile::FUN_10022560(const LegoU8* p_src, LegoU32* p_dst)
{
	// TODO
	STUB(0x10022560);
}

// FUNCTION: GOLDP 0x100226a0
// FUNCTION: LEGORACERS 0x0040d0c0
const LegoChar* GolImgFile::GetSuffix()
{
	return ".img";
}

// FUNCTION: GOLDP 0x100226b0
// FUNCTION: LEGORACERS 0x00413790
void GolImgFile::VTable0x14(undefined4, undefined4, undefined4, undefined4)
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

// STUB: GOLDP 0x10022730
void GolImgFile::FUN_10022730(
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4
)
{
	// TODO
	STUB(0x10022730);
}

// STUB: GOLDP 0x10022800
void GolImgFile::FUN_10022800(
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4,
	undefined4
)
{
	// TODO
	STUB(0x10022800);
}

// STUB: GOLDP 0x100229b0
void GolImgFile::FUN_100229b0(undefined4, undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x100229b0);
}

// STUB: GOLDP 0x10022b80
void GolImgFile::FUN_10022b80(undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x10022b80);
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
// FUNCTION: LEGORACERS 0x00416030 FOLDED
void GolImgFile::VTable0x1c(undefined4, undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
// FUNCTION: LEGORACERS 0x00416030 FOLDED
void GolImgFile::VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, undefined4*)
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
