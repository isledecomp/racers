#ifndef GOLDP_GOLFONTTABLE_H
#define GOLDP_GOLFONTTABLE_H

#include "golhashtable.h"
#include "golnametable.h"
#include "types.h"

class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x100562b4
// SIZE 0x2c
class GolFontTable : public GolNameTable {
public:
	GolFontTable();
	~GolFontTable() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10003fd0
	// GolFontTable::`scalar deleting destructor'

	virtual void VTable0x0c();                   // vtable+0x0c
	virtual void VTable0x10(undefined4 p_index); // vtable+0x10
	virtual void VTable0x14();                   // vtable+0x14
	virtual void VTable0x18();                   // vtable+0x18
	virtual void VTable0x1c();                   // vtable+0x1c
	virtual LegoBool32 LoadFontDefinitions(
		BronzeFalcon0xc8770* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                              // vtable+0x20
	virtual undefined* GetFont(undefined4 p_index); // vtable+0x24
	virtual void VTable0x28(undefined4 p_index);    // vtable+0x28
	virtual void VTable0x2c(undefined4 p_index);    // vtable+0x2c

protected:
	BronzeFalcon0xc8770* m_renderer;         // 0x0c
	undefined4 m_unk0x10;                    // 0x10
	LegoU32 m_numFonts;                      // 0x14
	undefined* m_unk0x18;                    // 0x18
	undefined** m_unk0x1c;                   // 0x1c
	LegoU16* m_unk0x20;                      // 0x20
	GolHashTable::Entry* m_currentHashEntry; // 0x24
	undefined* m_fonts;                      // 0x28
};

#endif // GOLDP_GOLFONTTABLE_H
