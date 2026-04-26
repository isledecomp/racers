#ifndef GOLDP_PEARLDEW0X0C_H
#define GOLDP_PEARLDEW0X0C_H

#include "decomp.h"
#include "types.h"

#include <ddraw.h>

// VTABLE: GOLDP 0x10056520
// SIZE 0x0c
class PearlDew0x0c {
public:
	PearlDew0x0c();
	~PearlDew0x0c();

	void Release();
	void Set332PaletteEntries();

	virtual void GetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count); // vtable+0x00
	virtual void CopyEntriesFrom(PearlDew0x0c* p_source);                               // vtable+0x04
	virtual void SetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count); // vtable+0x08
	virtual void GetEntry(PALETTEENTRY* p_entry, LegoU32 p_index);                      // vtable+0x0c
	virtual LegoS32 FindEntry(PALETTEENTRY* p_entry);                                   // vtable+0x10
	virtual LegoU32 GetFirstEntry();                                                    // vtable+0x14
	virtual LegoU32 GetEntryCount();                                                    // vtable+0x18
	virtual LegoU32 GetPaletteSize();                                                   // vtable+0x1c

	LPDIRECTDRAWPALETTE GetPalette() const { return m_palette; }

private:
	LPDIRECTDRAWPALETTE m_palette; // 0x04
	LegoU16 m_firstEntry;          // 0x08
	LegoU16 m_entryCount;          // 0x0a
};

#endif // GOLDP_PEARLDEW0X0C_H
