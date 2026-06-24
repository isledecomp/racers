#ifndef GOLTEXTURELIST_H
#define GOLTEXTURELIST_H

#include "golhashtable.h"
#include "golnametable.h"
#include "golsurfaceformat.h"
#include "goltxtparser.h"

class GolD3DRenderDevice;
class GoldDune0x38;
class PurpleDune0x7c;
class RaceState;

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
class GolTextureList : public GolNameTable {
public:
	// .tdb binary block tags (cf. data/liblr1/LibLR1/TDB.cs).
	enum TdbBlockType {
		c_tdbTextures = 0x27,
		c_tdbProperty28 = 0x28,
		c_tdbBmpTga = 0x2a,
		c_tdbColor2c = 0x2c,
		c_tdbProperty2d = 0x2d,
	};

	// VTABLE: GOLDP 0x100575d8
	// SIZE 0x1fc
	class TdbTxtParser : public GolTxtParser {
		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolTextureList::TdbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolTextureList::TdbTxtParser::~TdbTxtParser
	};

	GolTextureList();
	~GolTextureList() override; // vtable+0x00
	void Clear() override;      // vtable+0x08

	virtual void VTable0x0c();        // vtable+0x0c
	virtual void VTable0x10();        // vtable+0x10
	virtual void AllocateItems() = 0; // vtable+0x14
	virtual void VTable0x18(
		LegoU32 p_index,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) = 0;                                                                       // vtable+0x18
	virtual void VTable0x1c(GolD3DRenderDevice* p_renderer, LegoU32 p_capacity); // vtable+0x1c
	virtual void VTable0x20(
		GolD3DRenderDevice* p_renderer,
		MagentaRibbonSource0x4* p_source,
		LegoU32 p_capacity
	); // vtable+0x20
	virtual void VTable0x24(
		GolD3DRenderDevice* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                    // vtable+0x24
	virtual PurpleDune0x7c* GetItem(LegoU32 p_index) = 0; // vtable+0x28

	// SYNTHETIC: GOLDP 0x1002b500
	// GolTextureList::`scalar deleting destructor'

	GolTextureList* GetNext() const { return m_next; }
	void SetNext(GolTextureList* p_next) { m_next = p_next; }
	LegoU32 GetItemCount() const { return m_numItems; }

protected:
	friend class RaceState;

	void LoadTextures();

	GolD3DRenderDevice* m_renderer;    // 0x0c
	GolTextureList* m_next;            // 0x10
	MagentaRibbonSource0x4* m_unk0x14; // 0x14
	GolHashTable::Entry* m_unk0x18;    // 0x18
	LegoU32 m_numItems;                // 0x1c
};

#endif // GOLTEXTURELIST_H
