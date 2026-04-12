#ifndef CORALBEAM0X30_H
#define CORALBEAM0X30_H

#include "compat.h"
#include "decomp.h"
#include "mossglow0x30.h"

// VTABLE: LEGORACERS 0x4b1250
// SIZE 0x30
class CoralBeam0x30 : public MossGlow0x30 {
public:
	CoralBeam0x30();
	~CoralBeam0x30();

	void VTable0x00() override; // vtable+0x00
	void VTable0x04() override; // vtable+0x04
	void VTable0x08() override; // vtable+0x08
	void VTable0x0c() override; // vtable+0x0c
	void VTable0x10() override; // vtable+0x10
	void VTable0x14() override; // vtable+0x14

	void FUN_0044cc90();
};

#endif // CORALBEAM0X30_H
