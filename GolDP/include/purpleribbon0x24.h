#ifndef PURPLERIBBON0x25_H
#define PURPLERIBBON0x25_H

#include "decomp.h"
#include "magentaribbon0x20.h"

class PurpleDune0x7c;

// VTABLE: GOLDP 0x100567f0
// SIZE 0x24
class PurpleRibbon0x24 : public MagentaRibbon0x20 {
public:
	PurpleRibbon0x24();
	~PurpleRibbon0x24() override;  // vtable+0x00
	void Clear() override;         // vtable+0x08
	void VTable0x0c() override;    // vtable+0x0c
	void VTable0x10() override;    // vtable+0x10
	void AllocateItems() override; // vtable+0x14
	void VTable0x18(
		LegoU32 p_index,
		const GolSurfaceFormat& p_textureFormat,
		LegoU32 p_width,
		LegoU32 p_height
	) override;
	GoldDune0x38* GetItem(LegoU32 p_index) override; // vtable+0x28

	// SYNTHETIC: GOLDP 0x100177c0
	// PurpleRibbon0x24::`vector deleting destructor'

private:
	PurpleDune0x7c* m_items; // 0x20
};

#endif // PURPLERIBBON0x25_H
