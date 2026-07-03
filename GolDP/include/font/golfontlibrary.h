#ifndef GOLFONTLIBRARY_H
#define GOLFONTLIBRARY_H

#include "golnametable.h"
#include "goltxtparser.h"
#include "image/goltiledtexture.h"
#include "surface/color.h"

class GolD3DRenderDevice;
class GolFileParser;
class GolFontBase;
class GolString;

// VTABLE: GOLDP 0x10056e08
// SIZE 0x28
class GolFontLibrary : public GolNameTable {
public:
	// VTABLE: GOLDP 0x10056e30
	// SIZE 0x1fc
	class FdbTxtParser : public GolTxtParser {
	public:
		// .fdb tokens; ids proven by the field or flag each one feeds
		enum {
			e_font = GolFileParser::e_unknown0x27,
			e_bmp = GolFileParser::e_unknown0x28,
			e_tga = GolFileParser::e_unknown0x29,
			e_colorKey = GolFileParser::e_unknown0x2a,
			e_characters = GolFileParser::e_unknown0x2b,
			e_charSpacing = GolFileParser::e_unknown0x2c,
			e_textColor = GolFileParser::e_unknown0x2d,
		};
	};

	// SIZE 0x0c
	struct FontParseStyle {
		union {
			ColorRGBA m_colorKey;     // 0x00
			LegoU32 m_colorKeyPacked; // 0x00
		};
		LegoU32 m_flags; // 0x04
		union {
			ColorRGBA m_textColor;     // 0x08
			LegoU32 m_textColorPacked; // 0x08
		};
	};

	GolFontLibrary();
	~GolFontLibrary() override; // vtable+0x00
	void Clear() override;      // vtable+0x08

	virtual void AllocateItems() = 0;                              // vtable+0x0c
	virtual void AllocateDefinitionBuffer(undefined4 p_index) = 0; // vtable+0x10
	virtual void ReleaseDefinitionBuffers() = 0;                   // vtable+0x14
	virtual void ReleaseFontSurfaces();                            // vtable+0x18
	virtual void RefreshFontSurfaces();                            // vtable+0x1c
	virtual void LoadFontDefinitions(
		GolD3DRenderDevice* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                 // vtable+0x20
	virtual GolFontBase* GetItem(LegoU32 p_index) = 0; // vtable+0x24

	// SYNTHETIC: GOLDP 0x1001d850
	// GolFontLibrary::`scalar deleting destructor'

	GolFontLibrary* GetNext() const { return m_next; }
	void SetNext(GolFontLibrary* p_next) { m_next = p_next; }

protected:
	void ReadFontCharList(GolFileParser* p_parser, undefined2* p_chars, LegoU16* p_count);

	GolD3DRenderDevice* m_renderer;   // 0x0c
	GolFontLibrary* m_next;           // 0x10
	LegoU32 m_itemCount;              // 0x14
	GolString* m_charStrings;         // 0x18
	undefined2** m_charCodes;         // 0x1c
	LegoU16* m_charCounts;            // 0x20
	undefined4 m_hashTableCheckpoint; // 0x24
};

#endif // GOLFONTLIBRARY_H
