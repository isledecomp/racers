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
	virtual LegoBool32 Play(LegoBool32 p_loop);        // vtable+0x00
	virtual void Stop();                               // vtable+0x04
	virtual LegoBool32 IsPlaying();                    // vtable+0x08
	virtual void SetVolume(LegoFloat p_volume);        // vtable+0x0c
	virtual void SetPan(LegoFloat p_pan);              // vtable+0x10
	virtual void SetFrequencyScale(LegoFloat p_scale); // vtable+0x14
	virtual void SetPriority(LegoS32 p_priority);      // vtable+0x18
	virtual FrostPetal0x34* GetOwner();                // vtable+0x1c
	virtual ~SoundInstance();                          // vtable+0x20

	// SYNTHETIC: LEGORACERS 0x0041b4d0
	// SoundInstance::`scalar deleting destructor'

	void SetOwner(FrostPetal0x34* p_owner) { m_owner = p_owner; }
	void SetSoundBuffer(SoundBuffer* p_soundBuffer) { m_soundBuffer = p_soundBuffer; }
	FrostPetal0x34* GetOwnerDirect() { return m_owner; }

private:
	FrostPetal0x34* m_owner;    // 0x0c
	SoundBuffer* m_soundBuffer; // 0x10
};

#endif // SOUNDINSTANCE_H
