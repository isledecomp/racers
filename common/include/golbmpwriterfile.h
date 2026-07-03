#ifndef GOLBMPWRITERFILE_H
#define GOLBMPWRITERFILE_H

#include "golimgfilewriter.h"
#include "golsurfaceformat.h"

// VTABLE: LEGORACERS 0x004af2d8
// SIZE 0x5d4
class GolBmpWriterFile : public GolImgFileWriter {
public:
	GolBmpWriterFile();

	const LegoChar* GetSuffix() override;                         // vtable+0x10
	void WriteSurface(const GolRenderTarget* p_surface) override; // vtable+0x24

	// SYNTHETIC: LEGORACERS 0x004036f0
	// GolBmpWriterFile::`scalar deleting destructor'

	// FUNCTION: LEGORACERS 0x00403710
	// GolBmpWriterFile::~GolBmpWriterFile

private:
	void InitializeFromSurface(const GolRenderTarget* p_surface);
	void WriteHeader();
	void WritePalette();

	LegoU32 m_imageOffset;        // 0x5b4
	LegoU32 m_paletteEntryCount;  // 0x5b8
	GolSurfaceFormat m_bmpFormat; // 0x5bc
};

#endif // GOLBMPWRITERFILE_H
