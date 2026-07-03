#ifndef GOLIMAGEDEFINITIONLIST_H
#define GOLIMAGEDEFINITIONLIST_H

#include "golnametable.h"
#include "material/golimagelist.h"

class GolD3DRenderDevice;

// SIZE 0x20
// VTABLE: GOLDP 0x10056364
class GolImageDefinitionList : public GolImageList {
public:
	GolImageDefinitionList();
	~GolImageDefinitionList() override;

	void Clear() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10005d30
	// GolImageDefinitionList::`scalar deleting destructor'

	void AllocateItems() override;                  // vtable+0x0c
	void ReleaseImages() override;                  // vtable+0x10
	void RestoreImages() override;                  // vtable+0x14
	GolImage* GetItem(undefined4 p_index) override; // vtable+0x20

private:
	GolImage* m_items; // 0x1c
};

#endif // GOLIMAGEDEFINITIONLIST_H
