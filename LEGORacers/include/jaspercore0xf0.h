#ifndef JASPERCORE0XF0_H
#define JASPERCORE0XF0_H

#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x4b0f00
// SIZE 0xf0
class JasperCore0xf0 {
public:
	JasperCore0xf0();
	virtual void VTable0x00();     // vtable+0x00
	virtual ~JasperCore0xf0();     // vtable+0x04
	virtual void VTable0x08() = 0; // vtable+0x08
	virtual void VTable0x0c() = 0; // vtable+0x0c
	virtual void VTable0x10() = 0; // vtable+0x10
	virtual void VTable0x14() = 0; // vtable+0x14
	virtual void VTable0x18();     // vtable+0x18
	virtual void VTable0x1c();     // vtable+0x1c
	virtual void VTable0x20();     // vtable+0x20
	virtual void VTable0x24();     // vtable+0x24

	// SYNTHETIC: LEGORACERS 0x44bf40
	// JasperCore0xf0::`scalar deleting destructor'

protected:
	undefined m_unk0x04[0xf0 - 0x04]; // 0x04
};

#endif // JASPERCORE0XF0_H
