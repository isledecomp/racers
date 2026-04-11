#ifndef CRIMSONRAY0X20_H
#define CRIMSONRAY0X20_H

#include "amberleaf0x10.h"
#include "compat.h"
#include "decomp.h"
#include "opalstar0x20.h"

// VTABLE: LEGORACERS 0x4afcc8
// SIZE 0x20
class CrimsonRay0x20 : public OpalStar0x20 {
public:
	CrimsonRay0x20();
	~CrimsonRay0x20() override;                // vtable+0x00
	ListLink* VTable0x04(undefined4) override; // vtable+0x04
	ListLink* VTable0x08() override;           // vtable+0x08
	void VTable0x0c() override;                // vtable+0x0c
	void VTable0x10() override;                // vtable+0x10
	void VTable0x14(AmberLeaf0x10*) override;  // vtable+0x14
	undefined4 VTable0x18() override;          // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x41c050
	// CrimsonRay0x20::`scalar deleting destructor'
};

#endif // CRIMSONRAY0X20_H
