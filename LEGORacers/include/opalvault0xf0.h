#ifndef OPALVAULT0XF0_H
#define OPALVAULT0XF0_H

#include "compat.h"
#include "decomp.h"
#include "jaspercore0xf0.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b1224
// SIZE 0xf0
class OpalVault0xf0 : public JasperCore0xf0 {
public:
	OpalVault0xf0();
	LegoS32 VTable0x00() override; // vtable+0x00
	~OpalVault0xf0() override;     // vtable+0x04
	LegoS32 VTable0x08() override; // vtable+0x08
	LegoS32 VTable0x0c() override; // vtable+0x0c
	LegoS32 VTable0x10() override; // vtable+0x10
	LegoS32 VTable0x14() override; // vtable+0x14
	LegoS32 VTable0x18() override; // vtable+0x18
	LegoS32 VTable0x1c() override; // vtable+0x1c
	LegoS32 VTable0x20() override; // vtable+0x20
	void VTable0x24() override;    // vtable+0x24
	virtual void VTable0x28();     // vtable+0x28

	// SYNTHETIC: LEGORACERS 0x00450350
	// OpalVault0xf0::`scalar deleting destructor'
};

#endif // OPALVAULT0XF0_H
