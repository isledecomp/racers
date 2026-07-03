#ifndef GOLTEXTUREPALETTE_H
#define GOLTEXTUREPALETTE_H

#include "compat.h"
#include "device/golpalettebase.h"
#include "goltexture.h"

// VTABLE: GOLDP 0x10057554
// VTABLE: LEGORACERS 0x004af878
// SIZE 0x0c
class GolTexturePalette : public GolPaletteBase {
public:
	GolTexturePalette();
	void GetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count) override; // vtable+0x00
	void CopyEntriesFrom(GolPaletteBase* p_source) override;                          // vtable+0x04
	void SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count) override; // vtable+0x08
	void GetEntry(ColorRGBA* p_entry, LegoU32 p_index) override;                      // vtable+0x0c
	LegoS32 FindEntry(const ColorRGBA& p_entry) override;                             // vtable+0x10
	LegoU32 GetFirstEntry() override;                                                 // vtable+0x14
	LegoU32 GetEntryCount() override;                                                 // vtable+0x18
	LegoU32 GetPaletteSize() override;                                                // vtable+0x1c
	virtual ~GolTexturePalette();                                                     // vtable+0x20

	void Initialize(const GolSurfaceFormat& p_textureFormat);
	void Shutdown();

	ColorRGBA* GetEntries() const { return m_entries; }
	bool HasEntries() const { return m_entries != NULL; }

	// SYNTHETIC: GOLDP 0x1002a0b0
	// SYNTHETIC: LEGORACERS 0x00413400
	// GolTexturePalette::`scalar deleting destructor'

protected:
	ColorRGBA* m_entries; // 0x4
	LegoU32 m_size;       // 0x8
};

#endif // GOLTEXTUREPALETTE_H
