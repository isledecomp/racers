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

	void AllocateItems() override;                // vtable+0x0c
	void VTable0x10(undefined4 p_index) override; // vtable+0x10
	void ReleaseDefinitionBuffers() override;     // vtable+0x14
	void ReleaseFontSurfaces() override;          // vtable+0x18
	void RefreshFontSurfaces() override;          // vtable+0x1c
	void* GetItem(LegoU32 p_index) override;      // vtable+0x24

	void LoadFontDefinitions(BronzeFalcon0xc8770* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
	{
		VTable0x20(p_renderer, p_fileName, p_binary);
	}

private:
	GolFont0xa0* m_fonts; // 0x28
};

#endif // GOLDP_GOLFONTTABLE_H
