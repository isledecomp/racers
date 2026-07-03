#ifndef GOLIMGFILE_H
#define GOLIMGFILE_H

#include "decomp.h"
#include "golfile.h"
#include "golsurfaceformat.h"
#include "surface/color.h"

#define BUF_U16LE(BUF, POS) ((BUF)[0 + (POS)] + ((BUF)[1 + (POS)] << 8))
#define BUF_U32LE(BUF, POS)                                                                                            \
	((BUF)[0 + (POS)] + (((BUF)[1 + (POS)] + (((BUF)[2 + (POS)] + ((BUF)[3 + (POS)] << 8)) << 8)) << 8))

class GolPaletteBase;
class GolSurface;
class GolTiledTexture;

// SIZE 0x5b0
// VTABLE: GOLDP 0x10056f04
// VTABLE: LEGORACERS 0x004af59c
class GolImgFile {
public:
	GolImgFile();

	virtual void ReadHeader();                     // vtable+0x00
	virtual ~GolImgFile();                         // vtable+0x04
	virtual void Open(const LegoChar* p_fileName); // vtable+0x08
	virtual void Destroy();                        // vtable+0x0c
	virtual const LegoChar* GetSuffix();           // vtable+0x10
	virtual void LoadSurfaceFromBuffer(
		LegoU8* p_buffer,
		GolSurface* p_texture,
		LegoU32 p_flags,
		ColorRGBA* p_colorKey
	);                                         // vtable+0x14
	virtual void ReadPixels(LegoU8* p_buffer); // vtable+0x18
	virtual void LoadTiledTexture(GolTiledTexture* p_image, LegoU32 p_flags,
								  ColorRGBA* p_colorKey);                                    // vtable+0x1c
	virtual void LoadSurface(GolSurface* p_texture, LegoU32 p_flags, ColorRGBA* p_colorKey); // vtable+0x20

	// FUNCTION: GOLDP 0x100226b0
	// FUNCTION: LEGORACERS 0x00413790
	// GolImgFile::LoadSurfaceFromBuffer

	// SYNTHETIC: GOLDP 0x1001ff30
	// SYNTHETIC: LEGORACERS 0x0040a950
	// GolImgFile::`scalar deleting destructor'

	const GolSurfaceFormat& GetTextureFormat() const { return m_format; }
	LegoU32 GetWidth() const { return m_width; }
	LegoU32 GetHeight() const { return m_height; }
	void SetKeepNibbleOrder(LegoBool32 p_keepNibbleOrder) { m_keepNibbleOrder = p_keepNibbleOrder; }
	void SetRemapPureBlack(LegoBool32 p_remapPureBlack) { m_remapPureBlack = p_remapPureBlack; }
	void SetColorKeyReplacement(const ColorRGBA& p_colorKeyReplacement)
	{
		m_colorKeyReplacement = p_colorKeyReplacement;
	}

	void BuildPaletteRemap(GolPaletteBase*, ColorRGBA* p_colorKey);
	LegoU32 FindOrAddPaletteEntry(const ColorRGBA&);
	void SetupPixelConversion(const GolSurfaceFormat&, ColorRGBA* p_colorKey);
	void ConvertRow(const void* p_src, void* p_dst, const GolSurfaceFormat& p_format);
	void RemapRow4To4(const LegoU8* p_src, LegoU8* p_dst);
	void RemapRow4To4Swapped(const LegoU8* p_src, LegoU8* p_dst);
	void RemapRow4To8(const LegoU8* p_src, LegoU8* p_dst);
	void RemapRow8To8(const LegoU8* p_src, LegoU8* p_dst);
	void ConvertRowRgbTo8(const LegoU8* p_src, LegoU8* p_dst);
	void ConvertRowRgbTo16(const LegoU8* p_src, LegoU16* p_dst);
	void ConvertRowRgbTo24(const LegoU8* p_src, LegoU8* p_dst);
	void ConvertRowRgbTo32(const LegoU8* p_src, LegoU32* p_dst);
	void ConvertRowIndexed4To8(const LegoU8* p_src, LegoU8* p_dst);
	void ConvertRowIndexed4To16(const LegoU8* p_src, LegoU16* p_dst);
	void ConvertRowIndexed4To24(const LegoU8* p_src, LegoU8* p_dst);
	void ConvertRowIndexed4To32(const LegoU8* p_src, LegoU32* p_dst);
	void ConvertRowIndexed8To8(const LegoU8* p_src, LegoU8* p_dst);
	void ConvertRowIndexed8To16(const LegoU8* p_src, LegoU16* p_dst);
	void ConvertRowIndexed8To24(const LegoU8* p_src, LegoU8* p_dst);
	void ConvertRowIndexed8To32(const LegoU8* p_src, LegoU32* p_dst);
	void SetImageInfo(
		const GolSurfaceFormat& p_format,
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_rowByteStride,
		ColorRGBA* p_paletteColors,
		LegoU32 p_paletteSize
	);
	void ConvertImage(
		LegoU8* p_src,
		LegoU8* p_dst,
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_pitch,
		const GolSurfaceFormat& p_format,
		GolPaletteBase* p_palette,
		undefined4 p_flipVertical,
		ColorRGBA* p_colorKey
	);
	void ConvertImageHalfSize(
		LegoU8* p_src,
		LegoU8* p_dst,
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_pitch,
		const GolSurfaceFormat& p_format,
		undefined4 p_flipVertical,
		ColorRGBA* p_colorKey
	);
	void UpscaleRow(LegoU8* p_row, LegoS32 p_xScale, LegoU32 p_scaledWidth, LegoU32 p_bitsPerPixel);
	void DownsampleRowPair(LegoU8* p_top, LegoU8* p_bottom, LegoU8* p_dst);

protected:
	LegoU32 m_paletteCount;          // 0x004
	LegoU32 m_paletteReservedEnd;    // 0x008
	LegoU32 m_paletteCapacity;       // 0x00c
	ColorRGBA* m_paletteEntries;     // 0x010
	GolFile m_file;                  // 0x014
	LegoU32 m_width;                 // 0x044
	LegoU32 m_height;                // 0x048
	undefined4 m_rowByteStride;      // 0x04c
	GolSurfaceFormat m_format;       // 0x050
	undefined4 m_unk0x068;           // 0x068
	undefined4 m_paletteSize;        // 0x06c
	LegoU32 m_srcStrideMask;         // 0x070
	LegoU32 m_constPixelBits;        // 0x074
	LegoU32 m_redSrcShift;           // 0x078
	LegoU32 m_grnSrcShift;           // 0x07c
	LegoU32 m_bluSrcShift;           // 0x080
	LegoU32 m_alpSrcShift;           // 0x084
	LegoU32 m_redDstShift;           // 0x088
	LegoU32 m_grnDstShift;           // 0x08c
	LegoU32 m_bluDstShift;           // 0x090
	LegoU32 m_alpDstShift;           // 0x094
	LegoBool32 m_hasColorKey;        // 0x098
	undefined m_colorKeyRed;         // 0x09c
	undefined m_colorKeyGrn;         // 0x09d
	undefined m_colorKeyBlu;         // 0x09e
	undefined m_unk0x09f;            // 0x09f
	ColorRGBA m_colorKeyReplacement; // 0x0a0
	LegoU32 m_colorKeyPixel;         // 0x0a4
	ColorRGBA m_palette[256];        // 0x0a8
	LegoU8 m_paletteRemap[0x100];    // 0x4a8
	LegoBool32 m_keepNibbleOrder;    // 0x5a8
	LegoBool32 m_remapPureBlack;     // 0x5ac
};

#endif // GOLIMGFILE_H
