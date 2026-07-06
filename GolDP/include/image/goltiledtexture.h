#ifndef GOLTILEDTEXTURE_H
#define GOLTILEDTEXTURE_H

#include "decomp.h"
#include "fourbytes.h"
#include "golsurfaceformat.h"
#include "goltexture.h"
#include "surface/color.h"
#include "types.h"

class GolD3DRenderDevice;
class GolD3DTexture;

// VTABLE: GOLDP 0x10056ee4
// SIZE 0x50
class GolTiledTexture {
public:
	// m_flags uses the GolTexture::c_textureFlag* vocabulary (copied verbatim
	// into each tile's GolTexture::m_textureFlags by CreateTiles).
	enum {
		c_allSourceFlags = 0xffff,
		c_sourceFlagsWithoutBmp = c_allSourceFlags & ~GolTexture::c_textureFlagBmpSource,
		c_sourceFlagsWithoutTga = c_allSourceFlags & ~GolTexture::c_textureFlagTgaSource
	};

	enum StateFlags {
		c_stateCreated = 0x01,
		c_stateFlatShaded = 0x02,
		c_stateFlagBit2 = 0x04,
		c_stateHasContent = 0x08,
		c_stateDecal = 0x10,
		c_stateModulate = 0x20,
		c_stateFlagBit7 = 0x80,
		c_stateFlagBit9 = 0x200
	};

	// SIZE 0x09
	struct TileImageName {
		union {
			FourBytes m_name[2]; // 0x00
			LegoChar m_chars[9]; // 0x00
		};
	};

	GolTiledTexture();

	virtual void AllocateTileWidths() = 0;                            // vtable+0x00
	virtual void AllocateTileHeights() = 0;                           // vtable+0x04
	virtual void AllocateTileArrays() = 0;                            // vtable+0x08
	virtual void CreateTile(LegoU32, LegoU32, GolSurfaceFormat*) = 0; // vtable+0x0c
	virtual void Load();                                              // vtable+0x10
	virtual ~GolTiledTexture();                                       // vtable+0x14
	virtual void Reset();                                             // vtable+0x18
	virtual GolD3DTexture* GetTile(LegoU32, LegoU32) = 0;             // vtable+0x1c

	void ComputeTileLayout();
	void ComputeSquareTileLayout();
	void CreateTiles();

	LegoU32 GetWidth() const { return m_width; }
	LegoU32 GetHeight() const { return m_height; }
	LegoU32 GetStateFlags() const { return m_stateFlags; }
	LegoU32 GetTileColumnCount() const { return m_tileColumnCount; }
	LegoU32 GetTileRowCount() const { return m_tileRowCount; }
	LegoS32 GetTileWidth(LegoU32 p_column) const { return m_tileWidths[p_column]; }
	LegoS32 GetTileHeight(LegoU32 p_row) const { return m_tileHeights[p_row]; }

	// SYNTHETIC: GOLDP 0x1001f240
	// GolTiledTexture::`scalar deleting destructor'

public:
	LegoS32* m_tileWidths;          // 0x04
	LegoS32* m_tileHeights;         // 0x08
	GolSurfaceFormat m_format;      // 0x0c
	GolD3DRenderDevice* m_renderer; // 0x24
	union {
		ColorRGBA m_colorKey;     // 0x28
		LegoU32 m_colorKeyPacked; // 0x28
	};
	LegoU32 m_tileColumnCount;        // 0x2c
	LegoU32 m_tileRowCount;           // 0x30
	LegoU32 m_width;                  // 0x34
	LegoU32 m_height;                 // 0x38
	LegoU32 m_stateFlags;             // 0x3c
	LegoU16 m_flags;                  // 0x40
	FourBytes m_name[2];              // 0x42
	FourBytes m_tintColor;            // 0x4a
	undefined m_unk0x4e[0x50 - 0x4e]; // 0x4e
};

#endif // GOLTILEDTEXTURE_H
