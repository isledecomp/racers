#ifndef GOLDP_PEARLDEW0X0C_H
#define GOLDP_PEARLDEW0X0C_H

#include "compat.h"
#include "decomp.h"
#include "ipalette0x4.h"
#include "types.h"

#include <ddraw.h>

// VTABLE: GOLDP 0x10056520
// SIZE 0x0c
class PearlDew0x0c : public IPalette0x4 {
public:
	enum {
		c_errorBufferSize = 128,
		c_colorChannelMax = 0xff,
		c_paletteEntryFlagsAll = 0xff,
		c_systemPaletteEntries = 2,
		c_paletteEntries2Bit = 4,
		c_paletteEntries4Bit = 0x10,
		c_paletteEntries8Bit = 0x100,
		c_paletteEntries8BitUsable = c_paletteEntries8Bit - c_systemPaletteEntries,
		c_332RedLevels = 8,
		c_332GreenLevels = 8,
		c_332BlueLevels = 4,
		c_332GreenStride = c_332BlueLevels * sizeof(ColorRGBA),
		c_332RedStride = c_332GreenLevels * c_332GreenStride
	};

	PearlDew0x0c();
	~PearlDew0x0c();

	void Release();
	void Set332PaletteEntries();

	void GetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count) override; // vtable+0x00
	void CopyEntriesFrom(IPalette0x4* p_source) override;                             // vtable+0x04
	void SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count) override; // vtable+0x08
	void GetEntry(ColorRGBA* p_entry, LegoU32 p_index) override;                      // vtable+0x0c
	LegoS32 FindEntry(const ColorRGBA& p_entry) override;                             // vtable+0x10
	LegoU32 GetFirstEntry() override;                                                 // vtable+0x14
	LegoU32 GetEntryCount() override;                                                 // vtable+0x18
	LegoU32 GetPaletteSize() override;                                                // vtable+0x1c

	LPDIRECTDRAWPALETTE GetPalette() const { return m_palette; }

private:
	LPDIRECTDRAWPALETTE m_palette; // 0x04
	LegoU16 m_firstEntry;          // 0x08
	LegoU16 m_entryCount;          // 0x0a
};

#endif // GOLDP_PEARLDEW0X0C_H
