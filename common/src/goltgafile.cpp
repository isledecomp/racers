#include "goltgafile.h"

#include "goldecompress.h"
#include "golerror.h"
#include "silverdune0x30.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolTgaFile, 0x5dc)

// GLOBAL: GOLDP 0x1005cf00
// GLOBAL: LEGORACERS 0x004be384
const LegoChar* g_tgaSuffix = ".tga";

// FUNCTION: GOLDP 0x1002a4b0
// FUNCTION: LEGORACERS 0x004137a0
GolTgaFile::GolTgaFile()
{
	m_imageByteSize = 0;
	m_posImageData = 0;
}

// FUNCTION: GOLDP 0x1002a4f0
// FUNCTION: LEGORACERS 0x004137c0
const LegoChar* GolTgaFile::GetSuffix()
{
	return g_tgaSuffix;
}

// FUNCTION: GOLDP 0x1002a500
// FUNCTION: LEGORACERS 0x004137d0
void GolTgaFile::VTable0x08(const LegoChar* p_fileName)
{
	size_t lenFileName = strlen(p_fileName);
	size_t lenSuffix = strlen(g_tgaSuffix);

	if (lenFileName > lenSuffix && ::memcmp(p_fileName + lenFileName - lenSuffix, g_tgaSuffix, lenSuffix) == 0) {
		GolImgFile::VTable0x08(p_fileName);
		return;
	}

	LegoChar* pathBuffer = new LegoChar[lenFileName + lenSuffix + 1];
	if (pathBuffer == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(pathBuffer, p_fileName);
	::strcat(pathBuffer, g_tgaSuffix);
	GolImgFile::VTable0x08(pathBuffer);
	delete[] pathBuffer;
}

// FUNCTION: GOLDP 0x1002a5e0
// FUNCTION: LEGORACERS 0x004138b0
void GolTgaFile::VTable0x00()
{
	LegoU8 header[0x12];
	LegoS32 result;
	LegoS32 amount;

	result = m_file.BufferedRead(0, header, 0x12, &amount);
	if (result != GolStream::e_ioSuccess) {
		GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
	}

	m_imageType = header[0x2]; // 1: type1 color-mapped image, 2: unmapped rgb, 9: RLE color-mapped, 10: RLE rgb
	m_colorMapFirstEntry = BUF_U16LE(header, 0x3);
	m_colorMapLength = BUF_U16LE(header, 0x5);
	m_xOrigin = BUF_U16LE(header, 0x8);
	m_yOrigin = BUF_U16LE(header, 0xa);
	m_identificationFieldSize = header[0];
	m_posImageData = m_identificationFieldSize + 0x12;
	m_width = BUF_U16LE(header, 0xc);
	m_height = BUF_U16LE(header, 0xe);

	LegoU32 bpp = header[0x10];
	m_rowByteStride = ((m_width * bpp + 31) >> 3) & 0x1ffffffc;
	m_colorMapType = header[1]; // 1: data type 1, 2: data type 2, 9: date type 9, 10: data type 10
	m_colorMapEntrySize = header[7];
	m_imageDescriptorByte = header[0x11];
	m_paletteSize = 0;
	m_imageByteSize = m_rowByteStride * m_height;

	if (m_colorMapType != 0 && bpp <= 8) {
		LegoU32 rawPaletteByteSize = ((m_colorMapEntrySize + 7) >> 3) * m_colorMapLength;
		LegoU8* buf = new LegoU8[rawPaletteByteSize];
		if (buf == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		result = m_file.BufferedRead(m_posImageData, buf, rawPaletteByteSize, &amount);
		if (result != GolStream::e_ioSuccess) {
			GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
		}

		m_paletteSize = m_colorMapLength;
		if (m_paletteSize > 256) {
			m_paletteSize = 256;
		}

		LegoU32 i;
		LegoU8* bufPtr;
		switch (m_colorMapEntrySize) {
		case 0xf:
			// xrgb1555
			for (i = 0, bufPtr = buf; i < m_paletteSize; i++) {
				LegoU16 col16 = *bufPtr++;
				col16 |= *bufPtr++ << 8;
				m_palette[i].m_blu = static_cast<LegoU8>(col16 << 3);
				m_palette[i].m_grn = static_cast<LegoU8>(col16 >> 2) & 0xf8;
				m_palette[i].m_red = static_cast<LegoU8>(col16 >> 7) & 0xf8;
				m_palette[i].m_alp = 0xff;
			}
			break;
		case 0x10:
			// argb1555
			for (i = 0, bufPtr = buf; i < m_paletteSize; i++) {
				LegoU16 col16 = *bufPtr++;
				col16 |= *bufPtr++ << 8;
				m_palette[i].m_blu = static_cast<LegoU8>(col16 << 3);
				m_palette[i].m_grn = static_cast<LegoU8>(col16 >> 2) & 0xf8;
				m_palette[i].m_red = static_cast<LegoU8>(col16 >> 7) & 0xf8;
				m_palette[i].m_alp = 0x00;
			}
			break;
		case 0x18:
			// bgr888
			for (i = 0, bufPtr = buf; i < m_paletteSize; i++, bufPtr += 3) {
				m_palette[i].m_blu = bufPtr[0];
				m_palette[i].m_grn = bufPtr[1];
				m_palette[i].m_red = bufPtr[2];
				m_palette[i].m_alp = 0xff;
			}
			break;
		case 0x20:
			// bgr888
			for (i = 0, bufPtr = buf; i < m_paletteSize; i++, bufPtr += 4) {
				m_palette[i].m_blu = bufPtr[0];
				m_palette[i].m_grn = bufPtr[1];
				m_palette[i].m_red = bufPtr[2];
				m_palette[i].m_alp = bufPtr[3];
			}
			break;
		}

		delete[] buf;
		m_posImageData += rawPaletteByteSize;
	}

	switch (bpp) {
	case 4:
		m_format.m_paletteMask = 0xf;
		m_format.m_bitsPerPixel = 4;
		break;
	case 8:
		m_format.m_paletteMask = 0xff;
		m_format.m_bitsPerPixel = 8;
		break;
	case 16:
		m_format.m_redBitMask = 0x7c00;
		m_format.m_grnBitMask = 0x03e0;
		m_format.m_bluBitMask = 0x001f;
		m_format.m_bitsPerPixel = 16;
		break;
	case 24:
		m_format.m_redBitMask = 0xff0000;
		m_format.m_grnBitMask = 0x00ff00;
		m_format.m_bluBitMask = 0x0000ff;
		m_format.m_bitsPerPixel = 24;
		break;
	case 32:
		m_format.m_redBitMask = 0x00ff0000;
		m_format.m_grnBitMask = 0x0000ff00;
		m_format.m_bluBitMask = 0x000000ff;
		m_format.m_alpBitMask = 0xff000000;
		m_format.m_bitsPerPixel = 32;
		break;
	default:
		GOL_FATALERROR_MESSAGE("Unsupported color depth encountered");
		break;
	}
}

// STUB: GOLDP 0x1002aa80
// STUB: LEGORACERS 0x00413d50
void GolTgaFile::VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, ColorRGBA* p_colorKey)
{
	LegoU8* rowBuffer2;
	LegoU8* rowBuffer1;
	LegoS32 widthScale = 1;
	LegoS32 heightScale = 1;
	LegoU32 pitch;
	LegoU32 fileOffset;
	LegoS32 amount;
	GolSurfaceFormat format;

	if (m_height > p_texture->GetHeight() || m_width > p_texture->GetWidth()) {
		GOL_FATALERROR_MESSAGE("Invalid image size for given storage");
	}
	if (m_height != p_texture->GetHeight() || m_width != p_texture->GetWidth()) {
		widthScale = p_texture->GetWidth() / m_width;
		heightScale = p_texture->GetHeight() / m_height;
	}

	format = p_texture->GetTextureFormat();
	FUN_100204d0(format, p_colorKey);
	if (format.m_paletteMask != 0) {
		FUN_100200f0(p_texture->GetPalette(), p_colorKey);
	}

	LegoU8* pixels;
	p_texture->LockPixels(&pixels, &pitch, SilverDune0x30::c_lockRequestRead | SilverDune0x30::c_lockRequestWrite);

	LegoS32 rowPitch = pitch;
	fileOffset = m_posImageData;
	rowBuffer1 = new LegoU8[m_rowByteStride + 2];
	if (rowBuffer1 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	rowBuffer2 = rowBuffer1;
	if (m_imageType >= 9) {
		rowBuffer2 = new LegoU8[m_rowByteStride + 2];
		if (rowBuffer2 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	if (p_flags == 0) {
		pixels += (p_texture->GetHeight() - 1) * pitch;
		rowPitch = -rowPitch;
	}

	for (LegoU32 y = 0; y < m_height; y++) {
		LegoS32 result = m_file.BufferedRead(fileOffset, rowBuffer1, m_rowByteStride, &amount);
		if (result != GolStream::e_ioSuccess) {
			p_texture->UnlockPixels();
			GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
		}

		if (m_imageType >= 9) {
			FUN_1002ad40(rowBuffer1, rowBuffer2);
		}

		FUN_100207e0(rowBuffer2, pixels, format);
		if (widthScale > 1) {
			FUN_100229b0(pixels, widthScale, p_texture->GetWidth(), format.m_bitsPerPixel);
		}

		for (LegoS32 repeat = 1; repeat < heightScale; repeat++) {
			::memcpy(pixels + rowPitch, pixels, pitch);
			pixels += rowPitch;
		}

		fileOffset += amount;
		pixels += rowPitch;
	}

	delete[] rowBuffer1;
	if (m_imageType >= 9) {
		delete[] rowBuffer2;
	}

	p_texture->UnlockPixels();
}

// STUB: GOLDP 0x1002ad40
void GolTgaFile::FUN_1002ad40(LegoU8* p_src, LegoU8* p_dst)
{
	LegoU32 bytesPerPixel = m_format.m_bitsPerPixel;
	LegoU32 pixelCount = 0;
	LegoU32 dstByteCount = 0;
	LegoU32 dstOffset = 0;

	bytesPerPixel += 7;
	bytesPerPixel >>= 3;
	LegoU8* dst = p_dst;
	LegoU8* src = p_src;

	while (pixelCount < m_width) {
		LegoU32 packet = *src++;
		LegoU32 newPixelCount = pixelCount + (packet & 0x7f) + 1;
		if (newPixelCount > m_width) {
			return;
		}

		if (packet & 0x80) {
			packet &= 0x7f;
			LegoU32 startOffset = dstOffset;
			pixelCount += packet + 1;
			dstByteCount += (packet + 1) * bytesPerPixel;

			for (LegoU32 i = bytesPerPixel; i > 0; i--) {
				dst[dstOffset++] = *src++;
			}

			for (; packet > 0; packet--) {
				for (LegoU32 i = 0; i < bytesPerPixel; i++) {
					dst[dstOffset++] = dst[startOffset + i];
				}
			}
		}
		else {
			pixelCount += packet + 1;
			dstByteCount += (packet + 1) * bytesPerPixel;

			do {
				for (LegoU32 i = bytesPerPixel; i > 0; i--) {
					dst[dstOffset++] = *src++;
				}
			} while (packet-- != 0);
		}
	}
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolTgaFile::VTable0x18(LegoU8* p_buffer)
{
	// empty
}

// STUB: GOLDP 0x1002ae50
// STUB: LEGORACERS 0x00414120
void GolTgaFile::VTable0x1c(undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x1002ae50);
}
