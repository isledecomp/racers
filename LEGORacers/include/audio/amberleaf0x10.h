#ifndef AMBERLEAF0X10_H
#define AMBERLEAF0X10_H

#include "compat.h"
#include "decomp.h"
#include "jadestorm0x0c.h"

class CrimsonRay0x20;

// VTABLE: LEGORACERS 0x004afca4
// SIZE 0x10
class AmberLeaf0x10 : public JadeStorm0x0c {
public:
	AmberLeaf0x10();
	~AmberLeaf0x10() override;                  // vtable+0x00
	undefined4 VTable0x04(undefined4) override; // vtable+0x04
	void VTable0x08() override;                 // vtable+0x08
	void VTable0x0c() override;                 // vtable+0x0c

	void SetUnk0x0c(CrimsonRay0x20* p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

	// SYNTHETIC: LEGORACERS 0x0041bfc0
	// AmberLeaf0x10::`scalar deleting destructor'

private:
	CrimsonRay0x20* m_unk0x0c; // 0x0c
};

#endif // AMBERLEAF0X10_H
