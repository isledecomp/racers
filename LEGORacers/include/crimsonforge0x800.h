#ifndef CRIMSONFORGE0X800_H
#define CRIMSONFORGE0X800_H

#include "decomp.h"
#include "golfile.h"
#include "golfilesource.h"
#include "tealpulse0x24.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af9a8
// SIZE 0x800
class CrimsonForge0x800 {
public:
	CrimsonForge0x800();
	virtual void VTable0x00() = 0;                                 // vtable+0x00
	virtual ~CrimsonForge0x800();                                  // vtable+0x04
	virtual void VTable0x08();                                     // vtable+0x08
	virtual void VTable0x0c(const LegoChar*, const LegoChar*) = 0; // vtable+0x0c
	virtual void VTable0x10() = 0;                                 // vtable+0x10
	virtual void VTable0x14() = 0;                                 // vtable+0x14
	virtual void VTable0x18() = 0;                                 // vtable+0x18
	virtual void VTable0x1c() = 0;                                 // vtable+0x1c
	virtual void VTable0x20() = 0;                                 // vtable+0x20
	virtual void VTable0x24() = 0;                                 // vtable+0x24
	virtual void VTable0x28();                                     // vtable+0x28
	virtual void VTable0x2c() = 0;                                 // vtable+0x2c
	virtual void VTable0x30() = 0;                                 // vtable+0x30
	virtual void VTable0x34() = 0;                                 // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x004163b0
	// CrimsonForge0x800::`scalar deleting destructor'

	LegoU8 GetUnk0x04() { return m_unk0x04; }
	TealPulse0x24& GetUnk0x7dc() { return m_unk0x7dc; }

	void FUN_004162c0();

protected:
	LegoU8 m_unk0x04;                    // 0x04
	undefined m_unk0x05[0x08 - 0x05];    // 0x05
	GolFile m_unk0x08[20];               // 0x08
	GolFileSource m_unk0x3c8[20];        // 0x3c8
	undefined m_unk0x7d8[0x7dc - 0x7d8]; // 0x7d8
	TealPulse0x24 m_unk0x7dc;            // 0x7dc
};

#endif // CRIMSONFORGE0X800_H
