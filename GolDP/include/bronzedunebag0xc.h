#ifndef BRONZEDUNEBAG0XC_H
#define BRONZEDUNEBAG0XC_H

#include "compat.h"
#include "golddune0x38.h"
#include "ipalette0x4.h"

// VTABLE: GOLDP 0x10057554
class BronzeDuneBag0xc : public IPalette0x4 {
public:
	BronzeDuneBag0xc();
	void GetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count) override; // vtable+0x
	void CopyEntriesFrom(IPalette0x4* p_source) override;                             // vtable+0x
	void SetEntries(ColorRGBA* p_entries, LegoU32 p_start, LegoU32 p_count) override; // vtable+0x
	void GetEntry(ColorRGBA* p_entry, LegoU32 p_index) override;                      // vtable+0x
	LegoS32 FindEntry(const ColorRGBA& p_entry) override;                             // vtable+0x
	LegoU32 GetFirstEntry() override;                                                 // vtable+0x
	LegoU32 GetEntryCount() override;                                                 // vtable+0x
	LegoU32 GetPaletteSize() override;                                                // vtable+0x
	virtual ~BronzeDuneBag0xc();                                                      // vtable+0x00

	void FUN_1002a120(const GolSurfaceFormat& p_textureFormat);
	void FUN_1002a1b0();

	ColorRGBA* GetEntries() const { return m_entries; }
	bool HasEntries() const { return m_entries != NULL; }

	// SYNTHETIC: GOLDP 0x1002a0b0
	// BronzeDuneBag0xc::`scalar deleting destructor'

protected:
	ColorRGBA* m_entries; // 0x4
	LegoU32 m_size;       // 0x8
};

#endif // BRONZEDUNEBAG0XC_H
