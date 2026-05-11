#ifndef AMBERHAZE0X20_H
#define AMBERHAZE0X20_H

#include "amberhaze0x1c.h"

class DuskwindBananaRelic0x30;

// VTABLE: GOLDP 0x100563d0
// SIZE 0x20
class AmberHaze0x20 : public AmberHaze0x1c {
public:
	AmberHaze0x20();
	~AmberHaze0x20() override; // vtable+0x00

	void Clear() override;                                            // vtable+0x08
	void VTable0x0c() override;                                       // vtable+0x0c
	void VTable0x10() override;                                       // vtable+0x10
	void AllocateItems() override;                                    // vtable+0x14
	void VTable0x18(LegoU32 p_index) override;                        // vtable+0x18
	DuskwindBananaRelic0x24* GetItem(LegoU32 p_index) const override; // vtable+0x28

	// SYNTHETIC: GOLDP 0x10017820
	// AmberHaze0x20::`vector deleting destructor'

private:
	DuskwindBananaRelic0x30* m_items; // 0x1c
};

#endif // AMBERHAZE0X20_H
