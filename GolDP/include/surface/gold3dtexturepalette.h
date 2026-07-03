#ifndef GOLD3DTEXTUREPALETTE_H
#define GOLD3DTEXTUREPALETTE_H

#include "decomp.h"
#include "golsurfaceformat.h"
#include "goltexturepalette.h"

#include <windows.h>

// VTABLE: GOLDP 0x10056708
// SIZE 0x10
class GolD3DTexturePalette : public GolTexturePalette {
public:
	GolD3DTexturePalette();
	~GolD3DTexturePalette() override; // vtable+0x20

	void CopyEntriesFrom(GolPaletteBase* p_source) override;                          // vtable+0x04
	void SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count) override; // vtable+0x08

	void Initialize(const GolSurfaceFormat& p_textureFormat);
	void Destroy();

	LegoU16* GetMappedEntries() const { return m_mappedEntries; }

	static void SetTextureFormat(const GolSurfaceFormat& p_format);
	// SYNTHETIC: GOLDP 0x100146e0
	// GolD3DTexturePalette::`scalar deleting destructor'

private:
	LegoU16* m_mappedEntries; // 0x0c

	static GolSurfaceFormat g_textureFormat;

	friend class GolD3DTexture;
};

#endif // GOLD3DTEXTUREPALETTE_H
