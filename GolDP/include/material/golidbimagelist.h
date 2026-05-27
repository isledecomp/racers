#ifndef GOLIDBIMAGELIST_H
#define GOLIDBIMAGELIST_H

#include "golhashtable.h"
#include "golnametable.h"
#include "image/utopianpan0xa4.h"
#include "scene/golwdbbillboard.h"

class GolD3DRenderDevice;

// VTABLE: GOLDP 0x10056f28
class GolIdbImageList : public GolNameTable {
public:
	GolIdbImageList();
	~GolIdbImageList() override;

	void Clear() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10022fc0
	// GolIdbImageList::`scalar deleting destructor'

	virtual void AllocateItems() = 0; // vtable+0x0c
	virtual void VTable0x10();        // vtable+0x10
	virtual void VTable0x14();        // vtable+0x14
	virtual void LoadImageDefinitions(
		GolD3DRenderDevice* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                                                                           // vtable+0x18
	virtual void VTable0x1c(GolD3DRenderDevice* p_renderer, LegoU32 p_numItems); // vtable+0x1c
	virtual UtopianPan0xa4* GetItem(undefined4 p_index) = 0;                     // vtable+0x20

	GolIdbImageList* GetNext() const { return m_next; }
	void SetNext(GolIdbImageList* p_next) { m_next = p_next; }

protected:
	GolD3DRenderDevice* m_renderer;          // 0x0c
	GolIdbImageList* m_next;                 // 0x10
	LegoU32 m_numItems;                      // 0x14
	GolHashTable::Entry* m_currentHashEntry; // 0x18
};

#endif // GOLIDBIMAGELIST_H
