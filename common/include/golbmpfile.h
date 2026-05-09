#ifndef GOLBMPFILE_H
#define GOLBMPFILE_H

#include "golimgfile.h"

// SIZE 0xed8
// VTABLE: GOLDP 0x10056ae0
// VTABLE: LEGORACERS 0x004af2b4
class GolBmpFile : public GolImgFile {
public:
	GolBmpFile();

	void VTable0x00() override;                                               // vtable+0x00
	void VTable0x08(const LegoChar* p_fileName) override;                     // vtable+0x08
	const LegoChar* GetSuffix() override;                                     // vtable+0x10
	void VTable0x14(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x14
	void VTable0x18(LegoU8* p_buffer) override;                               // vtable+0x18
	void VTable0x1c(undefined4, undefined4, undefined4) override;             // vtable+0x1c
	void VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, undefined4*) override;

	// SYNTHETIC: GOLDP 0x1002a4d0 FOLDED
	// SYNTHETIC: LEGORACERS 0x004016a0 FOLDED
	// GolBmpFile::`scalar deleting destructor'

private:
	LegoChar m_unk0x5b0[0x40];  // 0x5b0
	LegoU8 m_unk0x5f0[3 * 256]; // 0x5f0
	undefined m_unk0x8f0[1500]; // 0x8f0
	LegoU32 m_bitmapOffset;     // 0xecc
	undefined4 m_imageByteSize; // 0xed0
	undefined4 m_unk0xed4;      // 0xed4
};

#endif // GOLBMPFILE_H
