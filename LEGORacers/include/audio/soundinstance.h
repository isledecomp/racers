#ifndef SOUNDINSTANCE_H
#define SOUNDINSTANCE_H

#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

class FrostPetal0x34;
class SoundBuffer;

// VTABLE: LEGORACERS 0x004afc34
// SIZE 0x14
class SoundInstance : public GolListLink {
public:
	SoundInstance();
	virtual void VTable0x00(undefined4); // vtable+0x00
	virtual void VTable0x04();           // vtable+0x04
	virtual LegoBool32 VTable0x08();     // vtable+0x08
	virtual void VTable0x0c(LegoFloat);  // vtable+0x0c
	virtual void VTable0x10(LegoFloat);  // vtable+0x10
	virtual void VTable0x14(LegoFloat);  // vtable+0x14
	virtual void VTable0x18(LegoS32);    // vtable+0x18
	virtual undefined4 VTable0x1c();     // vtable+0x1c
	virtual ~SoundInstance();            // vtable+0x20

	// SYNTHETIC: LEGORACERS 0x0041b4d0
	// SoundInstance::`scalar deleting destructor'

	void SetOwner(FrostPetal0x34* p_owner) { m_owner = p_owner; }
	void SetSoundBuffer(SoundBuffer* p_soundBuffer) { m_soundBuffer = p_soundBuffer; }
	FrostPetal0x34* GetOwner() { return m_owner; }

private:
	FrostPetal0x34* m_owner;    // 0x0c
	SoundBuffer* m_soundBuffer; // 0x10
};

#endif // SOUNDINSTANCE_H
