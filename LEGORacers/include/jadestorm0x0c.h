#ifndef JADESTORM0X0C_H
#define JADESTORM0X0C_H

#include "decomp.h"
#include "gollist.h"

// VTABLE: LEGORACERS 0x004afa40
// SIZE 0x0c
class JadeStorm0x0c : public GolListLink {
public:
	JadeStorm0x0c() {}

	virtual ~JadeStorm0x0c();                      // vtable+0x00
	virtual undefined4 VTable0x04(undefined4) = 0; // vtable+0x04
	virtual void VTable0x08() = 0;                 // vtable+0x08
	virtual void VTable0x0c() = 0;                 // vtable+0x0c

	// SYNTHETIC: LEGORACERS 0x00417a10
	// JadeStorm0x0c::`scalar deleting destructor'
};

#endif // JADESTORM0X0C_H
