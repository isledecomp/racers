#ifndef OBSCUREVANTAGE0X58_H
#define OBSCUREVANTAGE0X58_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b29b4
// SIZE 0x58
class ObscureVantage0x58 {
public:
	ObscureVantage0x58();
	virtual void VTable0x00();                                         // vtable+0x00
	virtual ~ObscureVantage0x58();                                     // vtable+0x04
	virtual void VTable0x08();                                         // vtable+0x08
	virtual void VTable0x0c(undefined4);                               // vtable+0x0c
	virtual void VTable0x10(undefined4);                               // vtable+0x10
	virtual void VTable0x14(undefined4);                               // vtable+0x14
	virtual void VTable0x18(undefined4);                               // vtable+0x18
	virtual undefined4 VTable0x1c(undefined4, undefined4);             // vtable+0x1c
	virtual undefined4 VTable0x20(undefined4, undefined4, undefined4); // vtable+0x20
	virtual undefined4 VTable0x24(undefined4, undefined4, undefined4); // vtable+0x24
	virtual undefined4 VTable0x28(undefined4, undefined4, undefined4); // vtable+0x28
	virtual undefined4 VTable0x2c(undefined4, undefined4, undefined4); // vtable+0x2c
	virtual undefined4 VTable0x30(undefined4, undefined4, undefined4); // vtable+0x30
	virtual undefined4 VTable0x34(undefined4, undefined4, undefined4); // vtable+0x34
	virtual undefined4 VTable0x38(undefined4, undefined4);             // vtable+0x38
	virtual undefined4 VTable0x3c(undefined4);                         // vtable+0x3c

	// SYNTHETIC: LEGORACERS 0x004729d0
	// ObscureVantage0x58::`scalar deleting destructor'

protected:
	// SIZE 0x10
	class Struct0x34 {
	public:
		undefined4 m_unk0x00; // 0x00
		undefined4 m_unk0x04; // 0x04
		undefined4 m_unk0x08; // 0x08
		undefined4 m_unk0x0c; // 0x0c
	};

	undefined4 m_unk0x04; // 0x04
	undefined4 m_unk0x08; // 0x08
	undefined4 m_unk0x0c; // 0x0c
	undefined4 m_unk0x10; // 0x10
	undefined4 m_unk0x14; // 0x14
	undefined4 m_unk0x18; // 0x18
	undefined m_unk0x1c;  // 0x1c
	undefined4 m_unk0x20; // 0x20
	undefined4 m_unk0x24; // 0x24
	undefined4 m_unk0x28; // 0x28
	undefined4 m_unk0x2c; // 0x2c
	undefined2 m_unk0x30; // 0x30
	Struct0x34 m_unk0x34; // 0x34
	LegoFloat m_unk0x44;  // 0x44
	LegoFloat m_unk0x48;  // 0x48
	undefined4 m_unk0x4c; // 0x4c
	undefined4 m_unk0x50; // 0x50
	undefined m_unk0x54;  // 0x54
};

#endif // OBSCUREVANTAGE0X58_H
