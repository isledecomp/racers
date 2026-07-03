#ifndef GOLIMAGELIST_H
#define GOLIMAGELIST_H

#include "golhashtable.h"
#include "golnametable.h"
#include "image/golimage.h"
#include "scene/golbillboard.h"

class GolD3DRenderDevice;

// VTABLE: GOLDP 0x10056f28
class GolImageList : public GolNameTable {
public:
	// .idb tokens (parsed with the plain shared parser; ids proven by the
	// flag/field each one feeds)
	enum {
		e_image = 0x27,
		e_flipVertically = 0x28,
		e_bmp = 0x29,
		e_tga = 0x2a,
		e_colorKey = 0x2b,
		e_tint = 0x2c,
	};

	GolImageList();
	~GolImageList() override;

	void Clear() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10022fc0
	// GolImageList::`scalar deleting destructor'

	virtual void AllocateItems() = 0; // vtable+0x0c
	virtual void ReleaseImages();     // vtable+0x10
	virtual void RestoreImages();     // vtable+0x14
	virtual void LoadImageDefinitions(
		GolD3DRenderDevice* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                                           // vtable+0x18
	virtual void Initialize(GolD3DRenderDevice* p_renderer, LegoU32 p_numItems); // vtable+0x1c
	virtual GolImage* GetItem(undefined4 p_index) = 0;                           // vtable+0x20

	GolImageList* GetNext() const { return m_next; }
	void SetNext(GolImageList* p_next) { m_next = p_next; }

protected:
	GolD3DRenderDevice* m_renderer;          // 0x0c
	GolImageList* m_next;                    // 0x10
	LegoU32 m_itemCount;                     // 0x14
	GolHashTable::Entry* m_currentHashEntry; // 0x18
};

#endif // GOLIMAGELIST_H
