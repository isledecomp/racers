#ifndef COBALTMIST0X30_H
#define COBALTMIST0X30_H

#include "compat.h"
#include "crimsonray0x20.h"
#include "decomp.h"
#include "emberdust0x28.h"
#include "indigostar0x18.h"
#include "types.h"
#include "util/list.h"

// VTABLE: LEGORACERS 0x4afc6c
// SIZE 0x30
class CobaltMist0x30 : public IndigoStar0x18 {
public:
	~CobaltMist0x30() override;                 // vtable+0x00
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

	// SYNTHETIC: LEGORACERS 0x41bce0
	// CobaltMist0x30::`scalar deleting destructor'

private:
	ListHead m_unk0x18; // 0x18
	ListHead m_unk0x24; // 0x24
};

#endif // COBALTMIST0X30_H
