#ifndef GOLDP_GOLFONTTABLE_H
#define GOLDP_GOLFONTTABLE_H

#include "cinderbasin0x28.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolFont0xa0;

// VTABLE: GOLDP 0x100562b4
// SIZE 0x2c
class GolFontTable : public CinderBasin0x28 {
public:
	GolFontTable();
	~GolFontTable() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10003fd0
	// GolFontTable::`scalar deleting destructor'

	void VTable0x0c() override;                   // vtable+0x0c
	void VTable0x10(undefined4 p_index) override; // vtable+0x10
	void VTable0x14() override;                   // vtable+0x14
	void VTable0x18() override;                   // vtable+0x18
	void VTable0x1c() override;                   // vtable+0x1c
	void* VTable0x24(LegoU32 p_index) override;   // vtable+0x24

	void LoadFontDefinitions(BronzeFalcon0xc8770* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
	{
		VTable0x20(p_renderer, p_fileName, p_binary);
	}

	GolFont0xa0* GetFont(LegoU32 p_index) { return static_cast<GolFont0xa0*>(VTable0x24(p_index)); }

private:
	GolFont0xa0* m_fonts; // 0x28
};

#endif // GOLDP_GOLFONTTABLE_H
