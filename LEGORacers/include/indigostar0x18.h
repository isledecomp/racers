#ifndef INDIGOSTAR0X18_H
#define INDIGOSTAR0X18_H

#include "decomp.h"
#include "types.h"

class CrimsonRay0x20;
class EmberDust0x28;
struct SilverNode0x50;

// VTABLE: LEGORACERS 0x4afa64
// SIZE 0x18
class IndigoStar0x18 {
public:
	IndigoStar0x18();
	virtual ~IndigoStar0x18();                           // vtable+0x00
	virtual undefined4 VTable0x04(undefined4) = 0;       // vtable+0x04
	virtual void VTable0x08();                           // vtable+0x08
	virtual void VTable0x0c() = 0;                       // vtable+0x0c
	virtual void VTable0x10() = 0;                       // vtable+0x10
	virtual CrimsonRay0x20* VTable0x14() = 0;            // vtable+0x14
	virtual void VTable0x18(CrimsonRay0x20*) = 0;        // vtable+0x18
	virtual EmberDust0x28* VTable0x1c() = 0;             // vtable+0x1c
	virtual void VTable0x20(EmberDust0x28*) = 0;         // vtable+0x20
	virtual SilverNode0x50* VTable0x24() = 0;            // vtable+0x24
	virtual void VTable0x28(SilverNode0x50*) = 0;        // vtable+0x28
	virtual SilverNode0x50* VTable0x2c(SilverNode0x50*); // vtable+0x2c
	virtual SilverNode0x50* VTable0x30(SilverNode0x50*); // vtable+0x30
	virtual void VTable0x34(undefined4) = 0;             // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x417a60
	// IndigoStar0x18::`scalar deleting destructor'

	SilverNode0x50* FUN_00417ab0(SilverNode0x50* p_node);
	SilverNode0x50* FUN_00417ae0(SilverNode0x50* p_node);

protected:
	undefined4 m_unk0x04;      // 0x04
	SilverNode0x50* m_unk0x08; // 0x08
	SilverNode0x50* m_unk0x0c; // 0x0c
	LegoFloat m_unk0x10;       // 0x10
	LegoFloat m_unk0x14;       // 0x14
};

#endif // INDIGOSTAR0X18_H
