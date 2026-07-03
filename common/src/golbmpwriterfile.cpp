#include "golbmpwriterfile.h"

#include "device/golpalettebase.h"
#include "golerror.h"
#include "surface/golrendertarget.h"

DECOMP_SIZE_ASSERT(GolBmpWriterFile, 0x5d4)

// FUNCTION: LEGORACERS 0x004036a0
GolBmpWriterFile::GolBmpWriterFile()
{
	m_imageOffset = 0;
	m_paletteEntryCount = 0;
}

// FUNCTION: LEGORACERS 0x00403720
const LegoChar* GolBmpWriterFile::GetSuffix()
{
	return ".bmp";
}

// FUNCTION: LEGORACERS 0x00403730
void GolBmpWriterFile::InitializeFromSurface(const GolRenderTarget* p_surface)
{
	m_width = p_surface->GetWidth();
	m_height = p_surface->GetHeight();
	m_format = p_surface->GetTextureFormat();

	switch (m_format.m_bitsPerPixel) {
	case 4:
		m_bmpFormat.m_paletteMask = 0x0f;
		m_bmpFormat.m_bitsPerPixel = 4;
		break;
	case 8:
		m_bmpFormat.m_paletteMask = 0xff;
		m_bmpFormat.m_bitsPerPixel = 8;
		break;
	case 16:
	case 24:
	case 32:
		m_bmpFormat.m_redBitMask = 0xff0000;
		m_bmpFormat.m_grnBitMask = 0x00ff00;
		m_bmpFormat.m_bluBitMask = 0x0000ff;
		m_bmpFormat.m_bitsPerPixel = 24;
		break;
	default:
		GOL_FATALERROR_MESSAGE("Unsupported color depth encountered");
		break;
	}

	LegoU32 rowByteStride = m_bmpFormat.m_bitsPerPixel;
	rowByteStride *= m_width;
	rowByteStride += 31;
	rowByteStride /= 32;
	rowByteStride *= 4;
	m_rowByteStride = rowByteStride;

	if (m_format.GetPaletteBitCount()) {
		m_paletteEntryCount = 1 << m_format.m_bitsPerPixel;

		GolPaletteBase* palette = const_cast<GolRenderTarget*>(p_surface)->GetPalette();
		palette->GetEntries(m_palette, 0, m_paletteEntryCount);
	}
}

// FUNCTION: LEGORACERS 0x00403870
void GolBmpWriterFile::WriteSurface(const GolRenderTarget* p_surface)
{
	LegoU8* pixels;
	LegoU32 pitch;

	InitializeFromSurface(p_surface);
	WriteHeader();
	WritePalette();
	SetupPixelConversion(m_bmpFormat, NULL);

	const_cast<GolRenderTarget*>(p_surface)->LockPixels(&pixels, &pitch, GolSurface::c_lockRequestRead);

	LegoU8* rowBuffer = new LegoU8[m_rowByteStride];
	if (!rowBuffer) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 fileOffset = m_imageOffset;
	pixels += (m_height - 1) * pitch;
	pitch = -pitch;

	for (LegoU32 y = 0; y < m_height; y++) {
		ConvertRow(pixels, rowBuffer, m_bmpFormat);
		pixels += pitch;

		LegoS32 result = m_file.BufferedWrite(fileOffset, rowBuffer, m_rowByteStride);
		if (result != GolStream::e_ioSuccess) {
			GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
		}

		fileOffset += m_rowByteStride;
	}

	const_cast<GolRenderTarget*>(p_surface)->UnlockPixels();

	rowBuffer[0] = 0;
	rowBuffer[1] = 0;
	LegoS32 result = m_file.BufferedWrite(fileOffset, rowBuffer, 2);
	if (result != GolStream::e_ioSuccess) {
		GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
	}

	delete[] rowBuffer;
}

// FUNCTION: LEGORACERS 0x004039c0
void GolBmpWriterFile::WriteHeader()
{
	LegoU8 header[0x36];
	LegoU32 imageByteSize;
	LegoU32 fileSize;

	header[0x00] = 'B';
	header[0x01] = 'M';
	m_imageOffset = sizeof(header) + m_paletteEntryCount * sizeof(LegoU32);
	imageByteSize = m_rowByteStride * m_height;
	fileSize = m_imageOffset + imageByteSize;
	header[0x02] = static_cast<LegoU8>(fileSize);
	header[0x03] = static_cast<LegoU8>(fileSize >> 8);
	header[0x04] = static_cast<LegoU8>(fileSize >> 16);
	header[0x05] = static_cast<LegoU8>(fileSize >> 24);
	header[0x06] = 0;
	header[0x07] = 0;
	header[0x08] = 0;
	header[0x09] = 0;
	header[0x0a] = static_cast<LegoU8>(m_imageOffset);
	header[0x0b] = static_cast<LegoU8>(m_imageOffset >> 8);
	header[0x0c] = static_cast<LegoU8>(m_imageOffset >> 16);
	header[0x0d] = static_cast<LegoU8>(m_imageOffset >> 24);
	header[0x0e] = 0x28;
	header[0x0f] = 0;
	header[0x10] = 0;
	header[0x11] = 0;
	header[0x12] = static_cast<LegoU8>(m_width);
	header[0x13] = static_cast<LegoU8>(m_width >> 8);
	header[0x14] = static_cast<LegoU8>(m_width >> 16);
	header[0x15] = static_cast<LegoU8>(m_width >> 24);
	header[0x16] = static_cast<LegoU8>(m_height);
	header[0x17] = static_cast<LegoU8>(m_height >> 8);
	header[0x18] = static_cast<LegoU8>(m_height >> 16);
	header[0x19] = static_cast<LegoU8>(m_height >> 24);
	header[0x1a] = 1;
	header[0x1b] = 0;
	header[0x1c] = static_cast<LegoU8>(m_bmpFormat.m_bitsPerPixel);
	header[0x1d] = static_cast<LegoU8>(m_bmpFormat.m_bitsPerPixel >> 8);
	header[0x1e] = 0;
	header[0x1f] = 0;
	header[0x20] = 0;
	header[0x21] = 0;
	header[0x22] = static_cast<LegoU8>(imageByteSize);
	header[0x23] = static_cast<LegoU8>(imageByteSize >> 8);
	header[0x24] = static_cast<LegoU8>(imageByteSize >> 16);
	header[0x25] = static_cast<LegoU8>(imageByteSize >> 24);
	header[0x26] = 0x12;
	header[0x27] = 0x0b;
	header[0x28] = 0;
	header[0x29] = 0;
	header[0x2a] = 0x12;
	header[0x2b] = 0x0b;
	header[0x2c] = 0;
	header[0x2d] = 0;

	if (m_bmpFormat.GetPaletteBitCount()) {
		header[0x2e] = 0;
		header[0x2f] = 0;
		header[0x30] = 0;
		header[0x31] = 0;
		header[0x32] = 0;
		header[0x33] = 0;
		header[0x34] = 0;
		header[0x35] = 0;
	}
	else {
		header[0x2e] = static_cast<LegoU8>(m_paletteEntryCount);
		header[0x2f] = static_cast<LegoU8>(m_paletteEntryCount >> 8);
		header[0x30] = static_cast<LegoU8>(m_paletteEntryCount >> 16);
		header[0x31] = static_cast<LegoU8>(m_paletteEntryCount >> 24);
		header[0x32] = static_cast<LegoU8>(m_paletteEntryCount);
		header[0x33] = static_cast<LegoU8>(m_paletteEntryCount >> 8);
		header[0x34] = static_cast<LegoU8>(m_paletteEntryCount >> 16);
		header[0x35] = static_cast<LegoU8>(m_paletteEntryCount >> 24);
	}

	LegoS32 result = m_file.BufferedWrite(0, header, sizeof(header));
	if (result != GolStream::e_ioSuccess) {
		GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
	}
}

// FUNCTION: LEGORACERS 0x00403bc0
void GolBmpWriterFile::WritePalette()
{
	LegoU8 paletteEntries[16 * sizeof(LegoU32)];

	if (m_bmpFormat.GetPaletteBitCount()) {
		LegoU8* writePtr = paletteEntries;

		if (m_paletteEntryCount > 0) {
			LegoU32 chunkEnd = 0x10;
			do {
				LegoU32 i = 0;
				LegoU32 n = chunkEnd;

				while (n > 0) {
					*writePtr++ = m_palette[i].m_blu;
					*writePtr++ = m_palette[i].m_grn;
					*writePtr++ = m_palette[i].m_red;
					*writePtr++ = 0xff;
					i++;
					n--;
				}

				chunkEnd += 0x10;
			} while (chunkEnd - 0x10 < m_paletteEntryCount);
		}

		LegoS32 result = m_file.BufferedWrite(0x40, paletteEntries, sizeof(paletteEntries));
		if (result != GolStream::e_ioSuccess) {
			GOL_FATALERROR_MESSAGE(GolStream::ErrorCodeToString(result));
		}
	}
}
