#ifndef IRONFLAME0X944_H
#define IRONFLAME0X944_H

#include "decomp.h"
#include "tealpulse0x24.h"
#include "types.h"

// VTABLE: LEGORACERS 0x4af9f4
// SIZE 0x944
class IronFlame0x944 {
public:
	virtual void VTable0x00();                     // vtable+0x00
	virtual ~IronFlame0x944();                     // vtable+0x04
	virtual void VTable0x08();                     // vtable+0x08
	virtual void VTable0x0c(LegoChar*, LegoChar*); // vtable+0x0c
	virtual void VTable0x10();                     // vtable+0x10
	virtual void VTable0x14();                     // vtable+0x14
	virtual void VTable0x18();                     // vtable+0x18
	virtual void VTable0x1c();                     // vtable+0x1c
	virtual void VTable0x20();                     // vtable+0x20
	virtual void VTable0x24();                     // vtable+0x24
	virtual void VTable0x28();                     // vtable+0x28
	virtual void VTable0x2c();                     // vtable+0x2c

	// SYNTHETIC: LEGORACERS 0x416560
	// IronFlame0x944::`scalar deleting destructor'

	LegoU8 GetUnk0x04() { return m_unk0x04; }
	TealPulse0x24& GetUnk0x7dc() { return m_unk0x7dc; }
	undefined4 GetUnk0x928() { return m_unk0x928; }

	void SetUnk0x928(undefined4 p_unk0x928) { m_unk0x928 = p_unk0x928; }

private:
	LegoU8 m_unk0x04;                    // 0x04
	undefined m_unk0x05[0x7dc - 0x05];   // 0x05
	TealPulse0x24 m_unk0x7dc;            // 0x7dc
	undefined m_unk0x800[0x928 - 0x800]; // 0x800
	undefined4 m_unk0x928;               // 0x928
	undefined m_unk0x92c[0x944 - 0x92c]; // 0x92c
};

#endif // IRONFLAME0X944_H
