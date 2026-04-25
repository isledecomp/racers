#ifndef SOUNDINSTANCEBASE0X38_H
#define SOUNDINSTANCEBASE0X38_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004afad0
// SIZE 0x38
class SoundInstanceBase0x38 {
public:
	SoundInstanceBase0x38();
	virtual ~SoundInstanceBase0x38();    // vtable+0x00
	virtual void VTable0x04(undefined4); // vtable+0x04
	virtual void VTable0x08();           // vtable+0x08
	virtual undefined4 VTable0x0c();     // vtable+0x0c
	virtual undefined4 VTable0x10();     // vtable+0x10
	virtual void VTable0x14(undefined4); // vtable+0x14
	virtual void VTable0x18(undefined4); // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x00417c50
	// SoundInstanceBase0x38::`scalar deleting destructor'

private:
	LegoFloat m_unk0x04; // 0x04
	LegoFloat m_unk0x08; // 0x08
	LegoFloat m_unk0x0c; // 0x0c
	LegoFloat m_unk0x10; // 0x10
	LegoFloat m_unk0x14; // 0x14
	LegoFloat m_unk0x18; // 0x18
	LegoFloat m_unk0x1c; // 0x1c
	LegoFloat m_unk0x20; // 0x20
	LegoFloat m_unk0x24; // 0x24
	LegoFloat m_unk0x28; // 0x28
	LegoFloat m_unk0x2c; // 0x2c
	LegoFloat m_unk0x30; // 0x30
	LegoFloat m_unk0x34; // 0x34
};

#endif // SOUNDINSTANCEBASE0X38_H
