#ifndef GOLIMGFILE_H
#define GOLIMGFILE_H

#include "color.h"
#include "decomp.h"
#include "golfile.h"
#include "golsurfaceformat.h"

#define BUF_U16LE(BUF, POS) ((BUF)[0 + (POS)] + ((BUF)[1 + (POS)] << 8))
#define BUF_U32LE(BUF, POS)                                                                                            \
	((BUF)[0 + (POS)] + (((BUF)[1 + (POS)] + (((BUF)[2 + (POS)] + ((BUF)[3 + (POS)] << 8)) << 8)) << 8))

class IPalette0x4;
class SilverDune0x30;

// SIZE 0x5b0
// VTABLE: GOLDP 0x10056f04
// VTABLE: LEGORACERS 0x004af59c
class GolImgFile {
public:
	GolImgFile();

	virtual void VTable0x00();                                                        // vtable+0x00
	virtual ~GolImgFile();                                                            // vtable+0x04
	virtual void VTable0x08(const LegoChar* p_fileName);                              // vtable+0x08
	virtual void Destroy();                                                           // vtable+0x0c
	virtual const LegoChar* GetSuffix();                                              // vtable+0x10
	virtual void VTable0x14(undefined4, undefined4, undefined4, undefined4);          // vtable+0x14
	virtual void VTable0x18(LegoU8* p_buffer);                                        // vtable+0x18
	virtual void VTable0x1c(undefined4, undefined4, undefined4);                      // vtable+0x1c
	virtual void VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, undefined4*); // vtable+0x20

	// SYNTHETIC: GOLDP 0x1001ff30
	// SYNTHETIC: LEGORACERS 0x0040a950
	// GolImgFile::`scalar deleting destructor'

	const GolSurfaceFormat& GetTextureFormat() const { return m_format; }
	LegoU32 GetWidth() const { return m_width; }
	LegoU32 GetHeight() const { return m_height; }
	void SetUnk0x5a8(undefined4 p_unk0x5a8) { m_unk0x5a8 = p_unk0x5a8; }
	void SetUnk0x5ac(undefined4 p_unk0x5ac) { m_unk0x5ac = p_unk0x5ac; }

	void FUN_100200f0(IPalette0x4*, undefined4*);
	LegoU32 FUN_10020370(const ColorRGBA&);
	void FUN_100204d0(const GolSurfaceFormat&, undefined4*);
	void FUN_100207e0(const void* p_src, void* p_dst, const GolSurfaceFormat& p_format);
	void FUN_10020b90(const LegoU8* p_src, LegoU8* p_dst);
	void FUN_10020d60(const LegoU8* p_src, LegoU16* p_dst);
	void FUN_10020f20(const LegoU8* p_src, LegoU8* p_dst);
	void FUN_10021130(const LegoU8* p_src, LegoU32* p_dst);
	void FUN_100212f0(const LegoU8* p_src, LegoU8* p_dst);
	void FUN_10021660(const LegoU8* p_src, LegoU16* p_dst);
	void FUN_100219e0(const LegoU8* p_src, LegoU8* p_dst);
	void FUN_10021e10(const LegoU8* p_src, LegoU32* p_dst);
	void FUN_10022180(const LegoU8* p_src, LegoU8* p_dst);
	void FUN_100222c0(const LegoU8* p_src, LegoU16* p_dst);
	void FUN_10022400(const LegoU8* p_src, LegoU8* p_dst);
	void FUN_10022560(const LegoU8* p_src, LegoU32* p_dst);
	void FUN_100226c0(
		const GolSurfaceFormat& p_format,
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_rowByteStride,
		ColorRGBA* p_paletteColors,
		LegoU32 p_paletteSize
	);
	void FUN_10022730(
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4,
		undefined4
	);
	void FUN_10022800(undefined4, undefined4, undefined4, undefined4, undefined4, undefined4, undefined4, undefined4);
	void FUN_100229b0(undefined4, undefined4, undefined4, undefined4);
	void FUN_10022b80(undefined4, undefined4, undefined4);

protected:
	undefined4 m_unk0x004;               // 0x004
	undefined4 m_unk0x008;               // 0x008
	undefined4 m_unk0x00c;               // 0x00c
	ColorRGBA* m_unk0x010;               // 0x010
	GolFile m_file;                      // 0x014
	LegoU32 m_width;                     // 0x044
	LegoU32 m_height;                    // 0x048
	undefined4 m_rowByteStride;          // 0x04c
	GolSurfaceFormat m_format;           // 0x050
	undefined4 m_unk0x068;               // 0x068
	undefined4 m_paletteSize;            // 0x06c
	undefined4 m_unk0x070;               // 0x070
	undefined4 m_unk0x074;               // 0x074
	undefined4 m_unk0x078;               // 0x078
	undefined4 m_unk0x07c;               // 0x07c
	undefined4 m_unk0x080;               // 0x080
	undefined4 m_unk0x084;               // 0x084
	undefined4 m_unk0x088;               // 0x088
	undefined4 m_unk0x08c;               // 0x08c
	undefined4 m_unk0x090;               // 0x090
	undefined4 m_unk0x094;               // 0x094
	undefined4 m_unk0x098;               // 0x098
	undefined m_unk0x09c;                // 0x09c
	undefined m_unk0x09d;                // 0x09d
	undefined m_unk0x09e;                // 0x09e
	undefined m_unk0x09f;                // 0x09f
	undefined m_unk0x0a0;                // 0x0a0
	undefined m_unk0x0a1;                // 0x0a1
	undefined m_unk0x0a2;                // 0x0a2
	undefined m_unk0x0a3;                // 0x0a3
	undefined4 m_unk0x0a4;               // 0x0a4
	ColorRGBA m_palette[256];            // 0x0a8
	undefined m_unk0x4a8[0x5a4 - 0x4a8]; // 0x4a8
	undefined4 m_unk0x5a4;               // 0x5a4
	undefined4 m_unk0x5a8;               // 0x5a8
	undefined4 m_unk0x5ac;               // 0x5ac
};

#endif // GOLIMGFILE_H
