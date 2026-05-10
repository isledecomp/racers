#include "golbmpfile.h"

#include "goldecompress.h"
#include "golerror.h"
#include "silverdune0x30.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolBmpFile, 0xed8)

#define TWOCC(A, B) (((A) << 0) | ((B) << 8))

// GLOBAL: GOLDP 0x1005cbe4
// GLOBAL: LEGORACERS 0x004be098
const LegoChar* g_bmpSuffix = ".bmp";

// FUNCTION: GOLDP 0x10018c60
// FUNCTION: LEGORACERS 0x00401670
GolBmpFile::GolBmpFile()
{
	m_bitmapOffset = 0;
	m_imageByteSize = 0;
	m_unk0xed4 = 0;
}

// FUNCTION: GOLDP 0x10018c90
// FUNCTION: LEGORACERS 0x004016c0
const LegoChar* GolBmpFile::GetSuffix()
{
	return g_bmpSuffix;
}

// FUNCTION: GOLDP 0x10018ca0
// FUNCTION: LEGORACERS 0x004016d0
void GolBmpFile::VTable0x08(const LegoChar* p_fileName)
{
	m_bitmapOffset = 0;
	m_imageByteSize = 0;
	m_unk0xed4 = 0;
	size_t lenFileName = strlen(p_fileName);
	size_t lenSuffix = strlen(g_bmpSuffix);
	if (lenFileName > lenSuffix && ::memcmp(p_fileName + lenFileName - lenSuffix, g_bmpSuffix, lenSuffix) == 0) {
		GolImgFile::VTable0x08(p_fileName);
		return;
	}
	LegoChar* pathBuffer;
	if (lenFileName + lenSuffix + 1 > sizeOfArray(m_unk0x5b0)) {
		pathBuffer = new LegoChar[lenFileName + lenSuffix + 1];
	}
	else {
		pathBuffer = m_unk0x5b0;
	}
	if (pathBuffer == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::strcpy(pathBuffer, p_fileName);
	::strcat(pathBuffer, g_bmpSuffix);
	GolImgFile::VTable0x08(pathBuffer);
	if (pathBuffer != m_unk0x5b0) {
		delete[] pathBuffer;
	}
}

// FUNCTION: GOLDP 0x10018da0
// FUNCTION: LEGORACERS 0x004017d0
void GolBmpFile::VTable0x00()
{
	LegoU8 header[0xe];
	LegoS32 amountRead;
	LegoU32 i;
	LegoU32 bpp = 0;
	LegoU32 compression = 0;
	LegoU8* paletteBuffer;
	LegoS32 result = m_file.BufferedRead(0, header, sizeof(header), &amountRead);
	if (result != GolStream::e_ioSuccess) {
		GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
	}
	if (BUF_U16LE(header, 0) != TWOCC('B', 'M')) {
		bpp = header[0] & 0x3c;
		if (bpp != 4 && bpp != 8 && bpp != 24 && bpp != 32) {
			GOL_FATALERROR_MESSAGE("Invalid BMP file");
		}
		if (bpp > 8 || (header[0x0] & 0x80)) {
			m_paletteSize = 0;
		}
		else {
			m_paletteSize = header[0x1] + 1;
		}
		LegoU32 imageOffset = 6;
		m_width = BUF_U16LE(header, 0x2);
		m_height = BUF_U16LE(header, 0x4);
		if (bpp <= 8) {
			if (3 * m_paletteSize > sizeof(m_unk0x5f0)) {
				paletteBuffer = new LegoU8[3 * m_paletteSize];
			}
			else {
				paletteBuffer = m_unk0x5f0;
			}
			if (paletteBuffer == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
			result = m_file.BufferedRead(6, paletteBuffer, 3 * m_paletteSize, &amountRead);
			if (result != GolStream::e_ioSuccess) {
				GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
			}
			imageOffset += 3 * m_paletteSize;
			LegoU8* palettePtr;
			ColorRGBA* paletteColor;
			for (palettePtr = paletteBuffer, paletteColor = m_palette, i = 0; i < m_paletteSize; i++, paletteColor++) {
				paletteColor->m_blu = *palettePtr++;
				paletteColor->m_grn = *palettePtr++;
				paletteColor->m_red = *palettePtr++;
				paletteColor->m_alp = 0xff;
			}
			if (paletteBuffer != m_unk0x5f0) {
				delete[] paletteBuffer;
			}
		}
		m_bitmapOffset = imageOffset;
		m_unk0xed4 = 0x80;
		m_rowByteStride = ((m_width * bpp + 31) >> 3) & 0x1ffffffc;
		m_imageByteSize = m_rowByteStride * m_height;
	}
	else {
		LegoU8 header2[64];
		m_bitmapOffset = BUF_U32LE(header, 0xa);
		result = m_file.BufferedRead(14, header2, sizeof(header2), &amountRead);
		if (result != GolStream::e_ioSuccess) {
			GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
		}
		result = BUF_U32LE(header2, 0);
		LegoU32 dataOffset = 0xe + result;
		if (result == 0xc) {
			m_width = BUF_U16LE(header2, 0x4);  // bcWidth
			m_height = BUF_U16LE(header2, 0x6); // bcHeight
			bpp = BUF_U16LE(header2, 0xa);
			m_paletteSize = 0;
			if (bpp <= 8) {
				m_paletteSize = 1 << (header2[0x8] * bpp); // bcPlanes
				if (m_paletteSize > 256) {
					GOL_FATALERROR_MESSAGE("Palettes larger than 256 colors not supported");
				}
				if (3 * m_paletteSize > sizeof(m_unk0x5f0)) {
					paletteBuffer = new LegoU8[3 * m_paletteSize];
				}
				else {
					paletteBuffer = m_unk0x5f0;
				}
				if (paletteBuffer == NULL) {
					GOL_FATALERROR(c_golErrorOutOfMemory);
				}
				result = m_file.BufferedRead(dataOffset, paletteBuffer, 3 * m_paletteSize, &amountRead);
				if (result != GolStream::e_ioSuccess) {
					GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
				}
				LegoU8* palettePtr;
				ColorRGBA* paletteColor;
				for (palettePtr = paletteBuffer, paletteColor = m_palette, i = 0; i < m_paletteSize;
					 i++, paletteColor++) {
					paletteColor->m_blu = *palettePtr++;
					paletteColor->m_grn = *palettePtr++;
					paletteColor->m_red = *palettePtr++;
					paletteColor->m_alp = 0xff;
				}
				if (paletteBuffer != m_unk0x5f0) {
					delete[] paletteBuffer;
				}
				if (m_paletteSize < 256) {
					::memset(&m_palette[m_paletteSize], 0, sizeof(ColorRGBA) * (256 - m_paletteSize));
				}
			}
			m_rowByteStride = ((m_width * bpp + 31) >> 3) & 0x1ffffffc;
			m_imageByteSize = m_height * m_rowByteStride;
		}
		else if (result == 0x28) {
			m_width = BUF_U32LE(header2, 0x4);          // biWidth
			m_height = BUF_U32LE(header2, 0x8);         // biHeight
			bpp = BUF_U16LE(header2, 0xe);              // biBitCount
			compression = BUF_U32LE(header2, 0x10);     // biCompression
			m_imageByteSize = BUF_U32LE(header2, 0x14); // biSizeImage
			m_paletteSize = BUF_U32LE(header2, 0x20);   // biClrUsed
			if (bpp <= 8) {
				if (m_paletteSize == 0) {
					m_paletteSize = 1 << (header2[0xc] * bpp); // biPlanes
				}
				if (m_paletteSize * 4 > sizeof(m_unk0x5f0)) {
					paletteBuffer = new LegoU8[m_paletteSize * 4];
				}
				else {
					paletteBuffer = m_unk0x5f0;
				}
				if (paletteBuffer == NULL) {
					GOL_FATALERROR(c_golErrorOutOfMemory);
				}
				result = m_file.BufferedRead(dataOffset, paletteBuffer, m_paletteSize * 4, &amountRead);
				if (result != GolStream::e_ioSuccess) {
					GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
				}
				LegoU8* palettePtr;
				ColorRGBA* paletteColor;
				for (palettePtr = paletteBuffer, paletteColor = m_palette, i = 0; i < m_paletteSize;
					 i++, paletteColor++) {
					paletteColor->m_blu = *palettePtr++;
					paletteColor->m_grn = *palettePtr++;
					paletteColor->m_red = *palettePtr++;
					palettePtr++;
					paletteColor->m_alp = 0xff;
				}
				if (paletteBuffer != m_unk0x5f0) {
					delete[] paletteBuffer;
				}
				if (m_paletteSize < 256) {
					::memset(m_palette + m_paletteSize, 0, sizeof(ColorRGBA) * (256 - m_paletteSize));
				}
			}
			m_rowByteStride = ((m_width * bpp + 31) >> 3) & 0x1ffffffc;
		}
		else if (result == 0x40) {
			m_width = BUF_U32LE(header2, 0x4);
			m_height = BUF_U32LE(header2, 0x8);
			bpp = BUF_U16LE(header2, 0xe);
			compression = BUF_U32LE(header2, 0x10);
			m_imageByteSize = BUF_U32LE(header2, 0x14);
			m_paletteSize = BUF_U32LE(header2, 0x20);
			if (bpp <= 8) {
				if (m_paletteSize == 0) {
					m_paletteSize = 1 << (header2[0xc] * bpp);
				}
				if (3 * m_paletteSize > sizeof(m_unk0x5f0)) {
					paletteBuffer = new LegoU8[3 * m_paletteSize];
				}
				else {
					paletteBuffer = m_unk0x5f0;
				}
				if (paletteBuffer == NULL) {
					GOL_FATALERROR(c_golErrorOutOfMemory);
				}
				// BUG: buffer might be too small (3 vs 4)
				result = m_file.BufferedRead(dataOffset, paletteBuffer, 4 * m_paletteSize, &amountRead);
				if (result != GolStream::e_ioSuccess) {
					GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
				}
				LegoU8* palettePtr;
				ColorRGBA* paletteColor;
				for (palettePtr = paletteBuffer, paletteColor = m_palette, i = 0; i < m_paletteSize;
					 i++, paletteColor++) {
					paletteColor->m_blu = *palettePtr++;
					paletteColor->m_grn = *palettePtr++;
					paletteColor->m_red = *palettePtr++;
					palettePtr++;
					paletteColor->m_alp = 0xff;
				}
				if (paletteBuffer != m_unk0x5f0) {
					delete[] paletteBuffer;
				}
				if (m_paletteSize < 256) {
					::memset(m_palette + m_paletteSize, 0, sizeof(ColorRGBA) * (256 - m_paletteSize));
				}
			}
			m_rowByteStride = ((m_width * bpp + 31) >> 3) & 0x1ffffffc;
		}
		m_unk0xed4 = compression;
		if (m_unk0xed4 != 0) {
			GOL_FATALERROR_MESSAGE("Invalid BMP file");
		}
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

// STUB: GOLDP 0x100197a0
// STUB: LEGORACERS 0x004021d0
void GolBmpFile::VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, undefined4* p_arg3)
{
	LegoU32 widthScale = 1;
	LegoU32 heightScale = 1;
	if (p_texture->GetWidth() < m_height || p_texture->GetHeight() < m_width) {
		GOL_FATALERROR_MESSAGE("Invalid image size for given storage");
	}
	if (p_texture->GetWidth() != m_height || p_texture->GetHeight() != m_width) {
		widthScale = p_texture->GetWidth() / m_width;
		heightScale = p_texture->GetHeight() / m_height;
	}
	GolSurfaceFormat format = p_texture->GetTextureFormat();
	FUN_100204d0(format, p_arg3);
	if (format.m_paletteMask != 0 && m_paletteSize != 0) {
		FUN_100200f0(p_texture->GetPalette(), p_arg3);
	}
	LegoU8* pixels;
	LegoU32 pitch;
	p_texture->LockPixels(&pixels, &pitch, SilverDune0x30::c_lockRequestRead | SilverDune0x30::c_lockRequestWrite);
	if (m_unk0xed4 != 0x80) {
		LegoU8* buf1 = new LegoU8[m_rowByteStride + 2];
		if (buf1 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		LegoU8* buf2 = buf1;
		if (m_unk0xed4 != 0) {
			buf2 = new LegoU8[m_rowByteStride + 2];
			if (buf2 == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
		}
		(void) widthScale;
		(void) heightScale;
		// ...
	}
	// ...
	// TODO
	STUB(0x100197a0);
}

// STUB: GOLDP 0x10019da0
// STUB: LEGORACERS 0x004027d0
void GolBmpFile::VTable0x14(undefined4, undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x10019da0);
}

// FUNCTION: GOLDP 0x10019fe0
// FUNCTION: LEGORACERS 0x00402a10
void GolBmpFile::VTable0x18(LegoU8* p_buffer)
{
	LegoU32 y;
	LegoS32 amount;
	LegoS32 result;
	LegoU32 fileOffset = m_bitmapOffset;
	if (m_unk0xed4 == 0x80) {
		LegoU32 availableDecompressedSize = 0;
		LegoU8* availableDecompressedPtr = NULL;
		LegoU8* decompBuffer = m_unk0x8f0;
		LegoU8* writePtr = p_buffer + m_rowByteStride * m_height;
		if (decompBuffer == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		LegoU32 rowByteCount;
		if (m_format.m_bitsPerPixel == 4) {
			rowByteCount = (m_width * 4 + 4) / 8;
		}
		else {
			rowByteCount = m_format.m_bitsPerPixel / 8;
		}
		for (y = 0; y < m_height; y++) {
			writePtr -= m_rowByteStride;
			if (availableDecompressedSize < rowByteCount) {
				if (availableDecompressedSize != 0) {
					::memcpy(writePtr, availableDecompressedPtr, availableDecompressedSize);
				}
				LegoU32 rowAmount = availableDecompressedSize;
				while (rowAmount < rowByteCount) {
					result = m_file.BufferedRead(fileOffset, decompBuffer, 4, &amount);
					if (result != GolStream::e_ioSuccess) {
						GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
					}
					fileOffset += 4;
					LegoU32 decompressedSize = static_cast<LegoU16>((m_unk0x8f0[0] << 0) | (m_unk0x8f0[1] << 8));
					LegoU32 compressedSize = static_cast<LegoU16>((m_unk0x8f0[2] << 0) | (m_unk0x8f0[3] << 8));
					if (compressedSize < decompressedSize) {
						result = m_file.BufferedRead(
							fileOffset,
							decompBuffer + (sizeof(m_unk0x8f0) - compressedSize),
							compressedSize,
							&amount
						);
						if (result != GolStream::e_ioSuccess) {
							GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
						}
						GolDecompress(decompBuffer + (sizeof(m_unk0x8f0) - compressedSize), decompBuffer);
					}
					else {
						result = m_file.BufferedRead(fileOffset, decompBuffer, decompressedSize, &amount);
						if (result != GolStream::e_ioSuccess) {
							GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
						}
					}
					fileOffset += compressedSize;
					compressedSize = rowByteCount - rowAmount;
					if (decompressedSize < compressedSize) {
						compressedSize = decompressedSize;
					}
					::memcpy(writePtr + rowAmount, decompBuffer, compressedSize);
					availableDecompressedSize = decompressedSize - compressedSize;
					availableDecompressedPtr = decompBuffer + compressedSize;
					rowAmount += compressedSize;
				}
			}
			else {
				::memcpy(writePtr, availableDecompressedPtr, rowByteCount);
				availableDecompressedPtr += rowByteCount;
				availableDecompressedSize -= rowByteCount;
			}
		}
	}
	else {
		LegoU8* rowBuffer1 = new LegoU8[m_rowByteStride + 2];
		if (rowBuffer1 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		LegoU8* rowBuffer2 = rowBuffer1;
		if (m_unk0xed4) {
			rowBuffer2 = new LegoU8[m_rowByteStride + 2];
			if (rowBuffer2 == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
		}
		for (y = 0; y < m_height; y++) {
			result = m_file.BufferedRead(fileOffset, rowBuffer1, m_rowByteStride, &amount);
			if (result != GolStream::e_ioSuccess) {
				GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
			}
			// FIXME/BUG: using correct source buffer?
			::memcpy(p_buffer, rowBuffer2, m_rowByteStride);
			p_buffer += m_rowByteStride;
		}
		if (m_unk0xed4) {
			delete[] rowBuffer2;
		}
		delete[] rowBuffer1;
	}
}

// STUB: GOLDP 0x1001a340
// STUB: LEGORACERS 0x00402d70
void GolBmpFile::VTable0x1c(undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x1001a340);
}
