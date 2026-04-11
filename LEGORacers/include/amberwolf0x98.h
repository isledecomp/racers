#ifndef AMBERWOLF0X98_H
#define AMBERWOLF0X98_H

#include "compat.h"
#include "decomp.h"
#include "indigostar0x18.h"

// VTABLE: LEGORACERS 0x4afaf0
// SIZE 0x98
class AmberWolf0x98 : public IndigoStar0x18 {
public:
	~AmberWolf0x98() override;                  // vtable+0x00
	undefined4 VTable0x04(undefined4) override; // vtable+0x04
	void VTable0x08() override;                 // vtable+0x08
	void VTable0x0c() override;                 // vtable+0x0c
	void VTable0x10() override;                 // vtable+0x10
	CrimsonRay0x20* VTable0x14() override;      // vtable+0x14
	void VTable0x18(CrimsonRay0x20*) override;  // vtable+0x18
	EmberDust0x28* VTable0x1c() override;       // vtable+0x1c
	void VTable0x20(EmberDust0x28*) override;   // vtable+0x20
	void VTable0x24() override;                 // vtable+0x24
	void VTable0x28(undefined4) override;       // vtable+0x28
	void VTable0x34(undefined4) override;       // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x418680
	// AmberWolf0x98::`scalar deleting destructor'

private:
	undefined m_unk0x18[0x80]; // 0x18
};

#endif // AMBERWOLF0X98_H
