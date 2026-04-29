#ifndef IPALETTE0x4_H
#define IPALETTE0x4_H

#include "types.h"

#include <windows.h>

class IPalette0x4 {
public:
	virtual void GetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count) = 0; // vtable+0x00
	virtual void CopyEntriesFrom(IPalette0x4* p_source) = 0;                                // vtable+0x04
	virtual void SetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count) = 0; // vtable+0x08
	virtual void GetEntry(PALETTEENTRY* p_entry, LegoU32 p_index) = 0;                      // vtable+0x0c
	virtual LegoS32 FindEntry(PALETTEENTRY* p_entry) = 0;                                   // vtable+0x10
	virtual LegoU32 GetFirstEntry() = 0;                                                    // vtable+0x14
	virtual LegoU32 GetEntryCount() = 0;                                                    // vtable+0x18
	virtual LegoU32 GetPaletteSize() = 0;                                                   // vtable+0x1c
};

#endif //  IPALETTE0x4_H
