#ifndef MUSICINSTANCE_H
#define MUSICINSTANCE_H

#include "decomp.h"
#include "gollist.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004afa40
// SIZE 0x0c
class MusicInstance : public GolListLink {
public:
	MusicInstance() {}

	virtual ~MusicInstance();                // vtable+0x00
	virtual LegoBool32 Play(LegoBool32) = 0; // vtable+0x04
	virtual void Stop() = 0;                 // vtable+0x08
	virtual void Pause() = 0;                // vtable+0x0c
	virtual void Resume() = 0;               // vtable+0x10
	virtual LegoBool32 IsPlaying() = 0;      // vtable+0x14
	virtual void SetVolume(LegoFloat) = 0;   // vtable+0x18
	virtual void VTable0x1c(undefined4) = 0; // vtable+0x1c
	virtual void VTable0x20(undefined4) = 0; // vtable+0x20

	// SYNTHETIC: LEGORACERS 0x00417a10
	// MusicInstance::`scalar deleting destructor'
};

#endif // MUSICINSTANCE_H
