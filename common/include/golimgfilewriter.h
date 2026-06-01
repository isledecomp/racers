#ifndef GOLIMGFILEWRITER_H
#define GOLIMGFILEWRITER_H

#include "golimgfile.h"

class SlatePeak0x58;

// VTABLE: LEGORACERS 0x004af5c0
// SIZE 0x5b4
class GolImgFileWriter : public GolImgFile {
public:
	GolImgFileWriter();
	~GolImgFileWriter() override;

	void VTable0x08(const LegoChar* p_fileName) override;          // vtable+0x08
	void Destroy() override;                                       // vtable+0x0c
	const LegoChar* GetSuffix() override = 0;                      // vtable+0x10
	virtual void WriteSurface(const SlatePeak0x58* p_surface) = 0; // vtable+0x24

	// SYNTHETIC: LEGORACERS 0x0040d2c0
	// GolImgFileWriter::`scalar deleting destructor'

protected:
	LegoChar* m_filePath; // 0x5b0
};

#endif // GOLIMGFILEWRITER_H
