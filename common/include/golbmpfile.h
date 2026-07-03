#ifndef GOLBMPFILE_H
#define GOLBMPFILE_H

#include "golimgfile.h"

// SIZE 0xed8
// VTABLE: GOLDP 0x10056ae0
// VTABLE: LEGORACERS 0x004af2b4
class GolBmpFile : public GolImgFile {
public:
	GolBmpFile();

	void ReadHeader() override;                     // vtable+0x00
	void Open(const LegoChar* p_fileName) override; // vtable+0x08
	const LegoChar* GetSuffix() override;           // vtable+0x10
	void LoadSurfaceFromBuffer(
		LegoU8* p_buffer,
		GolSurface* p_texture,
		LegoU32 p_flags,
		ColorRGBA* p_colorKey
	) override;                                                                                       // vtable+0x14
	void ReadPixels(LegoU8* p_buffer) override;                                                       // vtable+0x18
	void LoadTiledTexture(GolTiledTexture* p_image, LegoU32 p_flags, ColorRGBA* p_colorKey) override; // vtable+0x1c
	void LoadSurface(GolSurface* p_texture, LegoU32 p_flags, ColorRGBA* p_colorKey) override;         // vtable+0x20

	// SYNTHETIC: GOLDP 0x1002a4d0 FOLDED
	// SYNTHETIC: LEGORACERS 0x004016a0 FOLDED
	// GolBmpFile::`scalar deleting destructor'

	// SYNTHETIC: GOLDP 0x1001f1d0 FOLDED
	// SYNTHETIC: LEGORACERS 0x0040a8a0 FOLDED
	// GolBmpFile::~GolBmpFile

private:
	LegoChar m_pathBuffer[0x40];     // 0x5b0
	LegoU8 m_paletteBuffer[3 * 256]; // 0x5f0
	LegoU8 m_decompressBuffer[1500]; // 0x8f0
	LegoU32 m_bitmapOffset;          // 0xecc
	undefined4 m_imageByteSize;      // 0xed0
	undefined4 m_compression;        // 0xed4
};

#endif // GOLBMPFILE_H
