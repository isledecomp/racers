#ifndef GOLTGAFILE_H
#define GOLTGAFILE_H

#include "golimgfile.h"

// SIZE 0x5dc
// VTABLE: GOLDP 0x10057578
// VTABLE: LEGORACERS 0x004af89c
class GolTgaFile : public GolImgFile {
public:
	GolTgaFile();

	void VTable0x00() override;                                   // vtable+0x00
	void VTable0x08(const LegoChar* p_fileName) override;         // vtable+0x08
	const LegoChar* GetSuffix() override;                         // vtable+0x10
	void VTable0x18(LegoU8* p_buffer) override;                   // vtable+0x18
	void VTable0x1c(undefined4, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, undefined4*) override;

	// SYNTHETIC: GOLDP 0x1002a4d0 FOLDED
	// SYNTHETIC: LEGORACERS 0x004016a0 FOLDED
	// GolTgaFile::`scalar deleting destructor'

	void FUN_1002ad40(undefined4, undefined4);

private:
	undefined4 m_identificationFieldSize; // 0x5b0
	undefined4 m_colorMapType;            // 0x5b4
	undefined4 m_imageType;               // 0x5b8
	undefined4 m_colorMapFirstEntry;      // 0x5bc
	undefined4 m_colorMapLength;          // 0x5c0
	undefined4 m_colorMapEntrySize;       // 0x5c4
	undefined4 m_xOrigin;                 // 0x5c8
	undefined4 m_yOrigin;                 // 0x5cc
	undefined4 m_imageDescriptorByte;     // 0x5d0
	undefined4 m_posImageData;            // 0x5d4
	undefined4 m_imageByteSize;           // 0x5d8
};

#endif // GOLTGAFILE_H
