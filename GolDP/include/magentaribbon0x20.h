#ifndef MAGENTARIBBON0X20_H
#define MAGENTARIBBON0X20_H

#include "golhashtable.h"
#include "golnametable.h"
#include "golsurfaceformat.h"
#include "goltxtparser.h"

class BronzeFalcon0xc8770;
class GoldDune0x38;

// SIZE 0x1fc
// VTABLE: GOLDP 0x100575d8
class TdbTxtParser : public GolTxtParser {
	// SYNTHETIC: GOLDP 0x10030050 FOLDED
	// TdbTxtParser::`scalar deleting destructor'

	// SYNTHETIC: GOLDP 0x1001b000 FOLDED
	// TdbTxtParser::~TdbTxtParser
};

// SIZE 0x2c
struct MagentaRibbonSourceItem0x2c {
	LegoU32 m_width;                  // 0x00
	LegoU32 m_height;                 // 0x04
	GolSurfaceFormat m_textureFormat; // 0x08
	LegoU16 m_mipmapCount;            // 0x20
	undefined2 m_unk0x22;             // 0x22
	LegoU16 m_flags;                  // 0x24
	ColorRGBA m_colorKey;             // 0x26
};

// Runtime texture source used by VTable0x20 when textures are supplied by code
// instead of parsed from a .tdb definition file.
// SIZE 0x04
class MagentaRibbonSource0x4 {
public:
	virtual void VTable0x00(LegoU32 p_index, MagentaRibbonSourceItem0x2c* p_item) = 0;      // vtable+0x00
	virtual void VTable0x04(LegoU32 p_index, LegoU32 p_flags, GoldDune0x38* p_texture) = 0; // vtable+0x04
};

// VTABLE: GOLDP 0x100575ac
// SIZE 0x20
class MagentaRibbon0x20 : public GolNameTable {
public:
	MagentaRibbon0x20();
	~MagentaRibbon0x20() override; // vtable+0x00
	void Clear() override;         // vtable+0x08

	virtual void VTable0x0c();        // vtable+0x0c
	virtual void VTable0x10();        // vtable+0x10
	virtual void AllocateItems() = 0; // vtable+0x14
	virtual void VTable0x18(
		LegoU32 p_index,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) = 0;                                                                        // vtable+0x18
	virtual void VTable0x1c(BronzeFalcon0xc8770* p_renderer, LegoU32 p_capacity); // vtable+0x1c
	virtual void VTable0x20(
		BronzeFalcon0xc8770* p_renderer,
		MagentaRibbonSource0x4* p_source,
		LegoU32 p_capacity
	); // vtable+0x20
	virtual void VTable0x24(
		BronzeFalcon0xc8770* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                  // vtable+0x24
	virtual GoldDune0x38* GetItem(LegoU32 p_index) = 0; // vtable+0x28

	// SYNTHETIC: GOLDP 0x1002b500
	// MagentaRibbon0x20::`scalar deleting destructor'

	MagentaRibbon0x20* GetNext() const { return m_next; }
	void SetNext(MagentaRibbon0x20* p_next) { m_next = p_next; }
	LegoU32 GetItemCount() const { return m_numItems; }

protected:
	void LoadTextures();

	BronzeFalcon0xc8770* m_renderer;   // 0x0c
	MagentaRibbon0x20* m_next;         // 0x10
	MagentaRibbonSource0x4* m_unk0x14; // 0x14
	GolHashTable::Entry* m_unk0x18;    // 0x18
	LegoU32 m_numItems;                // 0x1c
};

#endif // MAGENTARIBBON0X20_H
