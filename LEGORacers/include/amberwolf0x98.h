#ifndef AMBERWOLF0X98_H
#define AMBERWOLF0X98_H

#include "compat.h"
#include "decomp.h"
#include "indigostar0x18.h"
#include "silvernode0x50.h"
#include "util/list.h"

#include <objbase.h>

// VTABLE: LEGORACERS 0x4afaf0
// SIZE 0x98
class AmberWolf0x98 : public IndigoStar0x18 {
public:
	AmberWolf0x98();
	~AmberWolf0x98() override;                  // vtable+0x00
	undefined4 VTable0x04(undefined4) override; // vtable+0x04
	void VTable0x08() override;                 // vtable+0x08
	void VTable0x0c() override;                 // vtable+0x0c
	void VTable0x10() override;                 // vtable+0x10
	CrimsonRay0x20* VTable0x14() override;      // vtable+0x14
	void VTable0x18(CrimsonRay0x20*) override;  // vtable+0x18
	EmberDust0x28* VTable0x1c() override;       // vtable+0x1c
	void VTable0x20(EmberDust0x28*) override;   // vtable+0x20
	SilverNode0x50* VTable0x24() override;      // vtable+0x24
	void VTable0x28(SilverNode0x50*) override;  // vtable+0x28
	void VTable0x34(undefined4) override;       // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x418680
	// AmberWolf0x98::`scalar deleting destructor'

private:
	undefined4 m_unk0x18;             // 0x18
	undefined4 m_unk0x1c;             // 0x1c
	undefined4 m_unk0x20;             // 0x20
	IUnknown* m_unk0x24;              // 0x24
	undefined4 m_unk0x28;             // 0x28
	undefined4 m_unk0x2c;             // 0x2c
	IUnknown* m_unk0x30;              // 0x30
	undefined m_unk0x34;              // 0x34
	undefined m_unk0x35;              // 0x35
	undefined m_unk0x36[0x38 - 0x36]; // 0x36
	undefined4 m_unk0x38;             // 0x38
	ListHead m_unk0x3c;               // 0x3c
	ListHead m_unk0x48;               // 0x48
	undefined4 m_unk0x54;             // 0x54
	undefined4 m_unk0x58;             // 0x58
	ListHead m_unk0x5c;               // 0x5c
	ListHead m_unk0x68;               // 0x68
	ListHead m_unk0x74;               // 0x74
	ListHead m_unk0x80;               // 0x80
	ListHead m_unk0x8c;               // 0x8c
};

#endif // AMBERWOLF0X98_H
