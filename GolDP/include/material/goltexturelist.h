#ifndef GOLTEXTURELIST_H
#define GOLTEXTURELIST_H

#include "golhashtable.h"
#include "golnametable.h"
#include "golsurfaceformat.h"
#include "goltxtparser.h"

class GolD3DRenderDevice;
class GolTexture;
class GolD3DTexture;

// SIZE 0x2c
struct GolTextureSourceItem {
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
class GolTextureSource {
public:
	virtual void GetTextureDefinition(LegoU32 p_index, GolTextureSourceItem* p_item) = 0;      // vtable+0x00
	virtual void OnTextureLoaded(LegoU32 p_index, LegoU32 p_flags, GolTexture* p_texture) = 0; // vtable+0x04
};

// VTABLE: GOLDP 0x100575ac
// SIZE 0x20
class GolTextureList : public GolNameTable {
public:
	// VTABLE: GOLDP 0x100575d8
	// SIZE 0x1fc
	class TdbTxtParser : public GolTxtParser {
	public:
		// .tdb tokens with proven payloads; flag-only keywords stay generic
		enum {
			e_texture = 0x27,
			e_flipVertically = 0x28,
			e_mipmaps = 0x29,
			e_bmp = 0x2a,
			e_tga = 0x2b,
			e_colorKey = 0x2c,
			e_unknown0x2d = 0x2d,
			e_unknown0x2e = 0x2e,
		};

		// SYNTHETIC: GOLDP 0x10030050 FOLDED
		// GolTextureList::TdbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: GOLDP 0x1001b000 FOLDED
		// GolTextureList::TdbTxtParser::~TdbTxtParser
	};

	GolTextureList();
	~GolTextureList() override; // vtable+0x00
	void Clear() override;      // vtable+0x08

	virtual void ReleaseTextures();   // vtable+0x0c
	virtual void RestoreTextures();   // vtable+0x10
	virtual void AllocateItems() = 0; // vtable+0x14
	virtual void AllocateTexture(
		LegoU32 p_index,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) = 0;                                                                       // vtable+0x18
	virtual void Initialize(GolD3DRenderDevice* p_renderer, LegoU32 p_capacity); // vtable+0x1c
	virtual void InitializeFromSource(
		GolD3DRenderDevice* p_renderer,
		GolTextureSource* p_source,
		LegoU32 p_capacity
	); // vtable+0x20
	virtual void Load(GolD3DRenderDevice* p_renderer, const LegoChar* p_fileName,
					  LegoBool32 p_binary);              // vtable+0x24
	virtual GolD3DTexture* GetItem(LegoU32 p_index) = 0; // vtable+0x28

	// SYNTHETIC: GOLDP 0x1002b500
	// GolTextureList::`scalar deleting destructor'

	GolTextureList* GetNext() const { return m_next; }
	void SetNext(GolTextureList* p_next) { m_next = p_next; }
	LegoU32 GetItemCount() const { return m_itemCount; }

	void LoadTextures();

protected:
	GolD3DRenderDevice* m_renderer;        // 0x0c
	GolTextureList* m_next;                // 0x10
	GolTextureSource* m_textureSource;     // 0x14
	GolHashTable::Entry* m_nameTableEntry; // 0x18
	LegoU32 m_itemCount;                   // 0x1c
};

#endif // GOLTEXTURELIST_H
