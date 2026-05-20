#ifndef CINDERBASIN0X28_H
#define CINDERBASIN0X28_H

#include "color.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "whitebaffoon0x50.h"

class BronzeFalcon0xc8770;
class GolFileParser;
class GolFontBase0x40;
class GolString;

// VTABLE: GOLDP 0x10056e30
// SIZE 0x1fc
class FdbTxtParser : public GolTxtParser {};

// VTABLE: GOLDP 0x10056e08
// SIZE 0x28
class CinderBasin0x28 : public GolNameTable {
public:
	// SIZE 0x0c
	struct FontParseStyle {
		union {
			ColorRGBA m_foregroundColor;     // 0x00
			LegoU32 m_foregroundColorPacked; // 0x00
		};
		LegoU32 m_flags; // 0x04
		union {
			ColorRGBA m_textColor;     // 0x08
			LegoU32 m_textColorPacked; // 0x08
		};
	};

	CinderBasin0x28();
	~CinderBasin0x28() override; // vtable+0x00
	void Clear() override;       // vtable+0x08

	virtual void AllocateItems() = 0;                // vtable+0x0c
	virtual void VTable0x10(undefined4 p_index) = 0; // vtable+0x10
	virtual void ReleaseDefinitionBuffers() = 0;     // vtable+0x14
	virtual void ReleaseFontSurfaces();              // vtable+0x18
	virtual void RefreshFontSurfaces();              // vtable+0x1c
	virtual void VTable0x20(
		BronzeFalcon0xc8770* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                     // vtable+0x20
	virtual GolFontBase0x40* GetItem(LegoU32 p_index) = 0; // vtable+0x24

	// SYNTHETIC: GOLDP 0x1001d850
	// CinderBasin0x28::`scalar deleting destructor'

	CinderBasin0x28* GetNext() const { return m_next; }
	void SetNext(CinderBasin0x28* p_next) { m_next = p_next; }

protected:
	static void __stdcall ReadFontCharList(GolFileParser* p_parser, undefined2* p_chars, LegoU16* p_count);

	BronzeFalcon0xc8770* m_renderer; // 0x0c
	CinderBasin0x28* m_next;         // 0x10
	LegoU32 m_numItems;              // 0x14
	GolString* m_unk0x18;            // 0x18
	undefined2** m_unk0x1c;          // 0x1c
	LegoU16* m_unk0x20;              // 0x20
	undefined4 m_unk0x24;            // 0x24
};

#endif // CINDERBASIN0X28_H
