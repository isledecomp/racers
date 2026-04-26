#ifndef MUSICINSTANCEBASE_H
#define MUSICINSTANCEBASE_H

#include "decomp.h"
#include "gollist.h"

// VTABLE: LEGORACERS 0x004afa40
// SIZE 0x0c
class MusicInstanceBase : public GolListLink {
public:
	MusicInstanceBase() {}

	virtual ~MusicInstanceBase();                  // vtable+0x00
	virtual undefined4 VTable0x04(undefined4) = 0; // vtable+0x04
	virtual void Stop() = 0;                       // vtable+0x08
	virtual void VTable0x0c() = 0;                 // vtable+0x0c

	// SYNTHETIC: LEGORACERS 0x00417a10
	// MusicInstanceBase::`scalar deleting destructor'
};

#endif // MUSICINSTANCEBASE_H
