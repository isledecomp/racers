#ifndef GOLDP_AWAKEKITE0x20_H
#define GOLDP_AWAKEKITE0x20_H

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
	void VTable0x10() override;                     // vtable+0x10
	void VTable0x14() override;                     // vtable+0x14
	GolImage* GetItem(undefined4 p_index) override; // vtable+0x20

private:
	GolImage* m_items; // 0x1c
};

#endif // GOLDP_AWAKEKITE0x20_H
