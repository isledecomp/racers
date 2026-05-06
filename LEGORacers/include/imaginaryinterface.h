#ifndef IMAGINARYINTERFACE_H
#define IMAGINARYINTERFACE_H

#include "decomp.h"
#include "onyxcircularbuffer0x1c.h"
#include "silverdune0x30.h"

class ObscureIcon0x1a8;

class ObscureVantage0x58;

// VTABLE: LEGORACERS 0x004b2388
class ImaginaryInterface {
public:
	virtual void VTable0x00(undefined4) = 0;                                             // vtable+0x00
	virtual void VTable0x04(ObscureVantage0x58*) = 0;                                    // vtable+0x04
	virtual void VTable0x08(ObscureVantage0x58*) = 0;                                    // vtable+0x08
	virtual void VTable0x0c(ObscureVantage0x58*) = 0;                                    // vtable+0x0c
	virtual void VTable0x10(undefined4) = 0;                                             // vtable+0x10
	virtual undefined4 VTable0x14(ObscureIcon0x1a8*, void*, undefined4, undefined4) = 0; // vtable+0x14
	virtual undefined4 VTable0x18(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) = 0; // vtable+0x18
	virtual undefined4 VTable0x1c(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) = 0;                                                                               // vtable+0x1c
	virtual void VTable0x20(undefined4) = 0;                                             // vtable+0x20
	virtual void VTable0x24(undefined4) = 0;                                             // vtable+0x24
	virtual undefined4 VTable0x28(ObscureIcon0x1a8*, void*, undefined4, undefined4) = 0; // vtable+0x28
	virtual void VTable0x2c(undefined4) = 0;                                             // vtable+0x2c
	virtual void VTable0x30(undefined4) = 0;                                             // vtable+0x30
	virtual void VTable0x34(undefined4) = 0;                                             // vtable+0x34
	virtual void VTable0x38(undefined4) = 0;                                             // vtable+0x38
	virtual void VTable0x3c(undefined4) = 0;                                             // vtable+0x3c
	virtual void VTable0x40(undefined4) = 0;                                             // vtable+0x40
	virtual void VTable0x44(undefined4) = 0;                                             // vtable+0x44
	virtual void VTable0x48(undefined4) = 0;                                             // vtable+0x48
};

#endif // IMAGINARYINTERFACE_H
