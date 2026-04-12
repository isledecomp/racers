#ifndef OPALVAULT0XF0_H
#define OPALVAULT0XF0_H

#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x4b1224
// SIZE 0xf0
class OpalVault0xf0 {
public:
	OpalVault0xf0();
	virtual void VTable0x00(); // vtable+0x00
	virtual ~OpalVault0xf0();  // vtable+0x04
	virtual void VTable0x08(); // vtable+0x08
	virtual void VTable0x0c(); // vtable+0x0c
	virtual void VTable0x10(); // vtable+0x10
	virtual void VTable0x14(); // vtable+0x14
	virtual void VTable0x18(); // vtable+0x18
	virtual void VTable0x1c(); // vtable+0x1c

	// SYNTHETIC: LEGORACERS 0x450350
	// OpalVault0xf0::`scalar deleting destructor'

private:
	undefined m_unk0x04[0xf0 - 0x04]; // 0x04
};

#endif // OPALVAULT0XF0_H
