#include "golbmpfile.h"

#include "goldecompress.h"
#include "golerror.h"
#include "image/whitebaffoon0x50.h"
#include "silverdune0x30.h"
#include "surface/purpledune0x7c.h"

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
	LegoU32 compression = 0;
	LegoU32 bpp = 0;
	LegoU32 imageOffset;
	LegoU8* paletteBuffer;

	LegoS32 result = m_file.BufferedRead(0, header, sizeof(header), &amountRead);
	if (result != GolStream::e_ioSuccess) {
		GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
	}

	LegoU16 magic = BUF_U16LE(header, 0);
	if (magic != TWOCC('B', 'M')) {
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

		imageOffset = 6;
		m_width = BUF_U16LE(header, 0x2);
		m_height = BUF_U16LE(header, 0x4);

		if (bpp <= 8) {
			LegoU32 paletteBytes = 3 * m_paletteSize;
			if (paletteBytes > sizeof(m_unk0x5f0)) {
				paletteBuffer = new LegoU8[paletteBytes];
			}
			else {
				paletteBuffer = m_unk0x5f0;
			}
			if (paletteBuffer == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			result = m_file.BufferedRead(6, paletteBuffer, paletteBytes, &amountRead);
			if (result != GolStream::e_ioSuccess) {
				GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
			}
			imageOffset += paletteBytes;

			LegoU8* palettePtr = paletteBuffer;
			for (i = 0; i < m_paletteSize; i++) {
				m_palette[i].m_blu = *palettePtr++;
				m_palette[i].m_grn = *palettePtr++;
				m_palette[i].m_red = *palettePtr++;
				m_palette[i].m_alp = 0xff;
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

				LegoU8* palettePtr = paletteBuffer;
				for (i = 0; i < m_paletteSize; i++) {
					m_palette[i].m_blu = *palettePtr++;
					m_palette[i].m_grn = *palettePtr++;
					m_palette[i].m_red = *palettePtr++;
					m_palette[i].m_alp = 0xff;
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

				LegoU8* palettePtr = paletteBuffer;
				for (i = 0; i < m_paletteSize; i++) {
					m_palette[i].m_blu = *palettePtr++;
					m_palette[i].m_grn = *palettePtr++;
					m_palette[i].m_red = *palettePtr++;
					palettePtr++;
					m_palette[i].m_alp = 0xff;
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

				// Original reads four bytes per palette entry after sizing this buffer with three-byte entries.
				result = m_file.BufferedRead(dataOffset, paletteBuffer, 4 * m_paletteSize, &amountRead);
				if (result != GolStream::e_ioSuccess) {
					GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
				}

				LegoU8* palettePtr = paletteBuffer;
				for (i = 0; i < m_paletteSize; i++) {
					m_palette[i].m_blu = *palettePtr++;
					m_palette[i].m_grn = *palettePtr++;
					m_palette[i].m_red = *palettePtr++;
					palettePtr++;
					m_palette[i].m_alp = 0xff;
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
void GolBmpFile::VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, ColorRGBA* p_colorKey)
{
	LegoU32 heightScale = 1;
	LegoU32 widthScale = 1;
	LegoU32 scaledHeight = 1;
	GolSurfaceFormat format;

	if (m_height > p_texture->GetHeight() || m_width > p_texture->GetWidth()) {
		GOL_FATALERROR_MESSAGE("Invalid image size for given storage");
	}
	if (m_height != p_texture->GetHeight() || m_width != p_texture->GetWidth()) {
		widthScale = p_texture->GetWidth() / m_width;
		heightScale = p_texture->GetHeight() / m_height;
	}
	scaledHeight = m_height * heightScale;

	format = p_texture->GetTextureFormat();
	FUN_100204d0(format, p_colorKey);
	if (format.m_paletteMask != 0 && m_paletteSize != 0) {
		FUN_100200f0(p_texture->GetPalette(), p_colorKey);
	}

	LegoU8* pixels;
	LegoU32 pitch;
	p_texture->LockPixels(&pixels, &pitch, SilverDune0x30::c_lockRequestRead | SilverDune0x30::c_lockRequestWrite);

	LegoS32 rowPitch = pitch;
	LegoU32 fileOffset = m_bitmapOffset;
	if (m_unk0xed4 == 0x80) {
		if (p_flags != 0) {
			pixels += (scaledHeight - 1) * pitch;
			rowPitch = -rowPitch;
		}

		LegoU8* decompBuffer = m_unk0x8f0;
		if (decompBuffer == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoU8* rowBuffer;
		if (m_rowByteStride + 2 <= sizeof(m_unk0x5f0)) {
			rowBuffer = m_unk0x5f0;
		}
		else {
			rowBuffer = new LegoU8[m_rowByteStride + 2];
		}
		if (rowBuffer == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoS32 rowByteCount;
		if (m_format.m_bitsPerPixel == 4) {
			rowByteCount = (m_width * 4 + 4) >> 3;
		}
		else {
			rowByteCount = (m_format.m_bitsPerPixel * m_width) >> 3;
		}

		LegoU8* availableDecompressedPtr = NULL;
		LegoS32 availableDecompressedSize = 0;

		for (LegoU32 y = 0; y < m_height; y++) {
			if (availableDecompressedSize < rowByteCount) {
				LegoS32 rowAmount = availableDecompressedSize;
				if (rowAmount != 0) {
					::memcpy(rowBuffer, availableDecompressedPtr, rowAmount);
				}

				while (rowAmount < rowByteCount) {
					LegoS32 amount;
					LegoS32 result = m_file.BufferedRead(fileOffset, decompBuffer, 4, &amount);
					if (result != GolStream::e_ioSuccess) {
						p_texture->UnlockPixels();
						GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
					}

					fileOffset += 4;
					LegoS32 decompressedSize = BUF_U16LE(decompBuffer, 0);
					LegoS32 compressedSize = BUF_U16LE(decompBuffer, 2);
					if (compressedSize < decompressedSize) {
						LegoU8* compressedBuffer = decompBuffer + sizeof(m_unk0x8f0) - compressedSize;
						result = m_file.BufferedRead(fileOffset, compressedBuffer, compressedSize, &amount);
						if (result != GolStream::e_ioSuccess) {
							p_texture->UnlockPixels();
							GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
						}
						GolDecompress(compressedBuffer, decompBuffer);
					}
					else {
						result = m_file.BufferedRead(fileOffset, decompBuffer, decompressedSize, &amount);
						if (result != GolStream::e_ioSuccess) {
							p_texture->UnlockPixels();
							GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
						}
					}

					fileOffset += compressedSize;
					LegoS32 copySize = rowByteCount - rowAmount;
					if (decompressedSize < copySize) {
						copySize = decompressedSize;
					}

					::memcpy(rowBuffer + rowAmount, decompBuffer, copySize);
					availableDecompressedSize = decompressedSize - copySize;
					availableDecompressedPtr = decompBuffer + copySize;
					rowAmount += copySize;
				}
			}
			else {
				::memcpy(rowBuffer, availableDecompressedPtr, rowByteCount);
				availableDecompressedPtr += rowByteCount;
				availableDecompressedSize -= rowByteCount;
			}

			FUN_100207e0(rowBuffer, pixels, format);
			if (widthScale > 1) {
				FUN_100229b0(pixels, widthScale, p_texture->GetWidth(), format.m_bitsPerPixel);
			}

			for (LegoU32 repeat = 1; repeat < heightScale; repeat++) {
				::memcpy(pixels + rowPitch, pixels, pitch);
				pixels += rowPitch;
			}

			pixels += rowPitch;
		}

		if (rowBuffer != m_unk0x5f0) {
			delete[] rowBuffer;
		}
	}
	else {
		LegoU8* rowBuffer1 = new LegoU8[m_rowByteStride + 2];
		if (rowBuffer1 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoU8* rowBuffer2 = rowBuffer1;
		if (m_unk0xed4 != 0) {
			rowBuffer2 = new LegoU8[m_rowByteStride + 2];
			if (rowBuffer2 == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
		}

		if (p_flags == 0) {
			pixels += (scaledHeight - 1) * pitch;
			rowPitch = -rowPitch;
		}

		for (LegoU32 y = 0; y < m_height; y++) {
			LegoS32 amount;
			LegoS32 result = m_file.BufferedRead(fileOffset, rowBuffer1, m_rowByteStride, &amount);
			if (result != GolStream::e_ioSuccess) {
				p_texture->UnlockPixels();
				GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
			}

			FUN_100207e0(rowBuffer2, pixels, format);
			if (widthScale > 1) {
				FUN_100229b0(pixels, widthScale, p_texture->GetWidth(), format.m_bitsPerPixel);
			}

			for (LegoU32 repeat = 1; repeat < heightScale; repeat++) {
				::memcpy(pixels + rowPitch, pixels, pitch);
				pixels += rowPitch;
			}

			fileOffset += amount;
			pixels += rowPitch;
		}

		if (m_unk0xed4 != 0) {
			delete[] rowBuffer2;
		}
		delete[] rowBuffer1;
	}

	p_texture->UnlockPixels();
}

// STUB: GOLDP 0x10019da0
// STUB: LEGORACERS 0x004027d0
void GolBmpFile::VTable0x14(LegoU8* p_buffer, SilverDune0x30* p_texture, LegoU32 p_flags, ColorRGBA* p_colorKey)
{
	LegoU32 widthScale = 1;
	LegoU32 heightScale = 1;
	GolSurfaceFormat format;

	if (m_height > p_texture->GetHeight() || m_width > p_texture->GetWidth()) {
		GOL_FATALERROR_MESSAGE("Invalid image size for given storage");
	}
	if (m_height != p_texture->GetHeight() || m_width != p_texture->GetWidth()) {
		widthScale = p_texture->GetWidth() / m_width;
		heightScale = p_texture->GetHeight() / m_height;
	}

	LegoU32 scaledHeight = m_height * heightScale;
	format = p_texture->GetTextureFormat();
	FUN_100204d0(format, p_colorKey);
	if (format.m_paletteMask != 0 && m_paletteSize != 0) {
		FUN_100200f0(p_texture->GetPalette(), p_colorKey);
	}

	LegoU8* pixels;
	LegoU32 pitch;
	p_texture->LockPixels(&pixels, &pitch, SilverDune0x30::c_lockRequestRead | SilverDune0x30::c_lockRequestWrite);

	LegoS32 rowPitch = pitch;
	if (p_flags == 0) {
		pixels += (scaledHeight - 1) * pitch;
		rowPitch = -rowPitch;
	}

	for (LegoU32 y = 0; y < m_height; y++) {
		FUN_100207e0(p_buffer, pixels, format);

		if (widthScale > 1) {
			if (format.m_bitsPerPixel > 14 && format.m_bitsPerPixel <= 16) {
				LegoU8* dst = pixels + (p_texture->GetWidth() * 2) - 2;
				LegoU8* src = pixels + (m_width * 2) - 2;
				for (LegoS32 x = m_width; x > 0; x--) {
					for (LegoS32 repeat = widthScale; repeat > 0; repeat--) {
						::memcpy(dst, src, sizeof(LegoU16));
						dst -= 2;
					}
					src -= 2;
				}
			}
			else if (format.m_bitsPerPixel == 8) {
				LegoU8* dst = pixels + p_texture->GetWidth() - 1;
				LegoU8* src = pixels + m_width - 1;
				for (LegoS32 x = m_width; x > 0; x--) {
					for (LegoS32 repeat = widthScale; repeat > 0; repeat--) {
						*dst-- = *src;
					}
					src--;
				}
			}
		}

		LegoU8* row = pixels;
		for (LegoU32 repeat = 1; repeat < heightScale; repeat++) {
			::memcpy(row + rowPitch, row, pitch);
			row += rowPitch;
			pixels += rowPitch;
		}

		p_buffer += m_rowByteStride;
		pixels = row + rowPitch;
	}

	p_texture->UnlockPixels();
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

			// The original copies from rowBuffer2; for reachable uncompressed BMPs it aliases rowBuffer1.
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
void GolBmpFile::VTable0x1c(WhiteBaffoon0x50* p_image, LegoU32 p_flags, ColorRGBA* p_colorKey)
{
	LegoU32 tileColumnCount = p_image->GetTileColumnCount();
	LegoU32 tileRowCount = p_image->GetTileRowCount();
	LegoU32 tileCount = tileColumnCount * tileRowCount;
	GolSurfaceFormat format;
	LegoU32 column;
	LegoU32 row;
	LegoU32 y;

	if (m_height != p_image->GetHeight() || m_width != p_image->GetWidth()) {
		GOL_FATALERROR_MESSAGE("Invalid image size for given storage");
	}

	format = p_image->VTable0x1c(0, 0)->GetTextureFormat();
	FUN_100204d0(format, p_colorKey);
	if (format.m_paletteMask != 0 && m_paletteSize != 0) {
		for (column = 0; column < tileColumnCount; column++) {
			for (row = 0; row < tileRowCount; row++) {
				FUN_100200f0(p_image->VTable0x1c(column, row)->GetPalette(), p_colorKey);
			}
		}
	}

	LegoU8** tilePixels = new LegoU8*[tileCount];
	if (tilePixels == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32* tilePitches = new LegoU32[tileCount];
	if (tilePitches == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (column = 0; column < tileColumnCount; column++) {
		for (row = 0; row < tileRowCount; row++) {
			LegoU32 index = row + column * tileRowCount;
			p_image->VTable0x1c(column, row)
				->LockPixels(
					&tilePixels[index],
					&tilePitches[index],
					SilverDune0x30::c_lockRequestRead | SilverDune0x30::c_lockRequestWrite
				);
		}
	}

	LegoU32 fileOffset = m_bitmapOffset;
	LegoS32 tileRow = 0;
	LegoS32 rowInTile = 0;
	LegoS32 rowStep = 1;
	if ((m_unk0xed4 != 0x80 && !p_flags) || (m_unk0xed4 == 0x80 && p_flags)) {
		rowStep = -1;
		tileRow = tileRowCount - 1;

		LegoS32 totalTileHeight = 0;
		LegoS32 lastTileHeight = 0;
		for (row = 0; row < tileRowCount; row++) {
			lastTileHeight = p_image->GetTileHeight(row);
			totalTileHeight += lastTileHeight;
		}

		rowInTile = lastTileHeight - totalTileHeight + m_height - 1;
	}

	LegoU8* convertedRow = new LegoU8[4 * m_width + 8];
	if (convertedRow == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 pixelByteStep = format.m_bitsPerPixel >> 2;
	if (m_unk0xed4 != 0x80) {
		LegoU8* rowBuffer1 = new LegoU8[m_rowByteStride + 2];
		if (rowBuffer1 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoU8* rowBuffer2 = rowBuffer1;
		if (m_unk0xed4 != 0) {
			rowBuffer2 = new LegoU8[m_rowByteStride + 2];
			if (rowBuffer2 == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}
		}

		for (y = 0; y < m_height; y++) {
			LegoS32 amount;
			LegoS32 result = m_file.BufferedRead(fileOffset, rowBuffer1, m_rowByteStride, &amount);
			if (result != GolStream::e_ioSuccess) {
				for (column = 0; column < tileColumnCount; column++) {
					for (row = 0; row < tileRowCount; row++) {
						p_image->VTable0x1c(column, row)->UnlockPixels();
					}
				}
				GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
			}

			FUN_100207e0(rowBuffer2, convertedRow, format);

			LegoU32 sourceOffset = 0;
			for (column = 0; column < tileColumnCount; column++) {
				if (rowInTile == 0x7fffffff) {
					rowInTile = p_image->GetTileHeight(tileRow) - 1;
				}

				LegoU32 rowBytes = (pixelByteStep * p_image->GetTileWidth(column) + 1) >> 1;
				LegoU32 totalRowBytes = (pixelByteStep * m_width + 1) >> 1;
				if (rowBytes + sourceOffset > totalRowBytes) {
					rowBytes = totalRowBytes - sourceOffset;
				}

				LegoU32 index = tileRow + column * tileRowCount;
				::memcpy(tilePixels[index] + rowInTile * tilePitches[index], convertedRow + sourceOffset, rowBytes);
				sourceOffset += rowBytes;
			}

			fileOffset += amount;
			rowInTile += rowStep;
			if (rowInTile == p_image->GetTileHeight(tileRow)) {
				rowInTile = 0;
				tileRow++;
			}
			else if (rowInTile == -1) {
				rowInTile = 0x7fffffff;
				tileRow--;
			}
		}

		if (m_unk0xed4 != 0) {
			delete[] rowBuffer2;
		}
		delete[] rowBuffer1;
	}
	else {
		LegoU8* decompBuffer = m_unk0x8f0;
		if (decompBuffer == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoU8* rowBuffer = new LegoU8[m_rowByteStride + 2];
		if (rowBuffer == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoU32 rowByteCount;
		if (m_format.m_bitsPerPixel == 4) {
			rowByteCount = (m_width * 4 + 4) >> 3;
		}
		else {
			rowByteCount = (m_format.m_bitsPerPixel * m_width) >> 3;
		}

		LegoU8* availableDecompressedPtr = NULL;
		LegoS32 availableDecompressedSize = 0;
		for (y = 0; y < m_height; y++) {
			if (availableDecompressedSize < static_cast<LegoS32>(rowByteCount)) {
				LegoS32 rowAmount = availableDecompressedSize;
				if (rowAmount != 0) {
					::memcpy(rowBuffer, availableDecompressedPtr, rowAmount);
				}

				while (rowAmount < static_cast<LegoS32>(rowByteCount)) {
					LegoS32 amount;
					LegoS32 result = m_file.BufferedRead(fileOffset, decompBuffer, 4, &amount);
					if (result != GolStream::e_ioSuccess) {
						for (column = 0; column < tileColumnCount; column++) {
							for (row = 0; row < tileRowCount; row++) {
								p_image->VTable0x1c(column, row)->UnlockPixels();
							}
						}
						GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
					}

					fileOffset += 4;
					LegoS32 decompressedSize = BUF_U16LE(decompBuffer, 0);
					LegoS32 compressedSize = BUF_U16LE(decompBuffer, 2);
					if (compressedSize < decompressedSize) {
						LegoU8* compressedBuffer = decompBuffer + sizeof(m_unk0x8f0) - compressedSize;
						result = m_file.BufferedRead(fileOffset, compressedBuffer, compressedSize, &amount);
						if (result != GolStream::e_ioSuccess) {
							for (column = 0; column < tileColumnCount; column++) {
								for (row = 0; row < tileRowCount; row++) {
									p_image->VTable0x1c(column, row)->UnlockPixels();
								}
							}
							GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
						}
						GolDecompress(compressedBuffer, decompBuffer);
					}
					else {
						result = m_file.BufferedRead(fileOffset, decompBuffer, decompressedSize, &amount);
						if (result != GolStream::e_ioSuccess) {
							for (column = 0; column < tileColumnCount; column++) {
								for (row = 0; row < tileRowCount; row++) {
									p_image->VTable0x1c(column, row)->UnlockPixels();
								}
							}
							GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
						}
					}

					fileOffset += compressedSize;
					LegoS32 copySize = rowByteCount - rowAmount;
					if (decompressedSize < copySize) {
						copySize = decompressedSize;
					}

					::memcpy(rowBuffer + rowAmount, decompBuffer, copySize);
					availableDecompressedSize = decompressedSize - copySize;
					availableDecompressedPtr = decompBuffer + copySize;
					rowAmount += copySize;
				}
			}
			else {
				::memcpy(rowBuffer, availableDecompressedPtr, rowByteCount);
				availableDecompressedPtr += rowByteCount;
				availableDecompressedSize -= rowByteCount;
			}

			FUN_100207e0(rowBuffer, convertedRow, format);

			LegoU32 sourceOffset = 0;
			for (column = 0; column < tileColumnCount; column++) {
				LegoS32 targetRow = rowInTile;
				if (targetRow == 0x7fffffff) {
					targetRow = p_image->GetTileHeight(tileRow) - 1;
					rowInTile = targetRow;
				}

				LegoU32 rowBytes = (pixelByteStep * p_image->GetTileWidth(column) + 1) >> 1;
				LegoU32 totalRowBytes = (pixelByteStep * m_width + 1) >> 1;
				if (rowBytes + sourceOffset > totalRowBytes) {
					rowBytes = totalRowBytes - sourceOffset;
				}

				LegoU32 index = tileRow + column * tileRowCount;
				::memcpy(tilePixels[index] + targetRow * tilePitches[index], convertedRow + sourceOffset, rowBytes);
				sourceOffset += rowBytes;
			}

			rowInTile += rowStep;
			if (rowInTile == p_image->GetTileHeight(tileRow)) {
				rowInTile = 0;
				tileRow++;
			}
			else if (rowInTile == -1) {
				rowInTile = 0x7fffffff;
				tileRow--;
			}
		}

		delete[] rowBuffer;
	}

	delete[] convertedRow;

	delete[] tilePixels;
	delete[] tilePitches;

	for (column = 0; column < tileColumnCount; column++) {
		for (row = 0; row < tileRowCount; row++) {
			p_image->VTable0x1c(column, row)->UnlockPixels();
		}
	}

	LegoU32 flags = p_image->GetUnk0x3c();
	flags = (flags & 0xfffffff1) | WhiteBaffoon0x50::c_flagBit3;
	p_image->m_unk0x3c = flags;
	if ((flags & (WhiteBaffoon0x50::c_flagBit4 | WhiteBaffoon0x50::c_flagBit5)) == 0) {
		p_image->m_unk0x3c = flags | WhiteBaffoon0x50::c_flagBit4;
	}
}
