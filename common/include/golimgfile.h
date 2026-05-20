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

	virtual void VTable0x00();                                                                  // vtable+0x00
	virtual ~GolImgFile();                                                                      // vtable+0x04
	virtual void VTable0x08(const LegoChar* p_fileName);                                        // vtable+0x08
	virtual void Destroy();                                                                     // vtable+0x0c
	virtual const LegoChar* GetSuffix();                                                        // vtable+0x10
	virtual void VTable0x14(undefined4, undefined4, undefined4, undefined4);                    // vtable+0x14
	virtual void VTable0x18(LegoU8* p_buffer);                                                  // vtable+0x18
	virtual void VTable0x1c(undefined4, undefined4, undefined4);                                // vtable+0x1c
	virtual void VTable0x20(SilverDune0x30* p_texture, LegoU32 p_flags, ColorRGBA* p_colorKey); // vtable+0x20

	// SYNTHETIC: GOLDP 0x1001ff30
	// SYNTHETIC: LEGORACERS 0x0040a950
	// GolImgFile::`scalar deleting destructor'

	const GolSurfaceFormat& GetTextureFormat() const { return m_format; }
	LegoU32 GetWidth() const { return m_width; }
	LegoU32 GetHeight() const { return m_height; }
	void SetUnk0x5a8(LegoBool32 p_unk0x5a8) { m_unk0x5a8 = p_unk0x5a8; }
	void SetUnk0x5ac(LegoBool32 p_unk0x5ac) { m_unk0x5ac = p_unk0x5ac; }
	void SetUnk0x0a0(const ColorRGBA& p_unk0x0a0) { m_unk0x0a0 = p_unk0x0a0; }

	void FUN_100200f0(IPalette0x4*, ColorRGBA* p_colorKey);
	LegoU32 FUN_10020370(const ColorRGBA&);
	void FUN_100204d0(const GolSurfaceFormat&, ColorRGBA* p_colorKey);
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
		LegoU8* p_src,
		LegoU8* p_dst,
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_pitch,
		const GolSurfaceFormat& p_format,
		IPalette0x4* p_palette,
		undefined4 p_unk0x20,
		ColorRGBA* p_colorKey
	);
	void FUN_10022880(
		LegoU8* p_src,
		LegoU8* p_dst,
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_pitch,
		const GolSurfaceFormat& p_format,
		undefined4 p_unk0x1c,
		ColorRGBA* p_colorKey
	);
	void FUN_100229b0(LegoU8* p_row, LegoS32 p_xScale, LegoU32 p_scaledWidth, LegoU32 p_bitsPerPixel);
	void FUN_10022b80(LegoU8* p_top, LegoU8* p_bottom, LegoU8* p_dst);

protected:
	LegoU32 m_paletteCount;              // 0x004
	LegoU32 m_paletteReservedEnd;        // 0x008
	LegoU32 m_paletteCapacity;           // 0x00c
	ColorRGBA* m_paletteEntries;         // 0x010
	GolFile m_file;                      // 0x014
	LegoU32 m_width;                     // 0x044
	LegoU32 m_height;                    // 0x048
	undefined4 m_rowByteStride;          // 0x04c
	GolSurfaceFormat m_format;           // 0x050
	undefined4 m_unk0x068;               // 0x068
	undefined4 m_paletteSize;            // 0x06c
	LegoU32 m_srcStrideMask;             // 0x070
	LegoU32 m_constPixelBits;            // 0x074
	LegoU32 m_redSrcShift;               // 0x078
	LegoU32 m_grnSrcShift;               // 0x07c
	LegoU32 m_bluSrcShift;               // 0x080
	LegoU32 m_alpSrcShift;               // 0x084
	LegoU32 m_redDstShift;               // 0x088
	LegoU32 m_grnDstShift;               // 0x08c
	LegoU32 m_bluDstShift;               // 0x090
	LegoU32 m_alpDstShift;               // 0x094
	LegoBool32 m_hasColorKey;            // 0x098
	undefined m_unk0x09c;                // 0x09c
	undefined m_unk0x09d;                // 0x09d
	undefined m_unk0x09e;                // 0x09e
	undefined m_unk0x09f;                // 0x09f
	ColorRGBA m_unk0x0a0;                // 0x0a0
	LegoU32 m_colorKeyPixel;             // 0x0a4
	ColorRGBA m_palette[256];            // 0x0a8
	undefined m_unk0x4a8[0x5a4 - 0x4a8]; // 0x4a8
	undefined4 m_unk0x5a4;               // 0x5a4
	LegoBool32 m_unk0x5a8;               // 0x5a8
	LegoBool32 m_unk0x5ac;               // 0x5ac
};

#endif // GOLIMGFILE_H
