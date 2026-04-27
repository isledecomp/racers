#ifndef NULLSOUNDINSTANCE_H
#define NULLSOUNDINSTANCE_H

#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

class SoundGroup;

// VTABLE: LEGORACERS 0x004afd30
// SIZE 0x10
class NullSoundInstance : public GolListLink {
public:
	NullSoundInstance();
	virtual void Play(LegoBool32 p_loop);              // vtable+0x00
	virtual void Stop();                               // vtable+0x04
	virtual LegoBool32 IsPlaying();                    // vtable+0x08
	virtual void SetVolume(LegoFloat p_volume);        // vtable+0x0c
	virtual void SetPan(LegoFloat p_pan);              // vtable+0x10
	virtual void SetFrequencyScale(LegoFloat p_scale); // vtable+0x14
	virtual void SetPriority(LegoS32 p_priority);      // vtable+0x18
	virtual SoundGroup* GetSoundGroup();               // vtable+0x1c
	virtual ~NullSoundInstance();                      // vtable+0x20

	void SetSoundGroup(SoundGroup* p_soundGroup) { m_soundGroup = p_soundGroup; }

	// SYNTHETIC: LEGORACERS 0x0041c3f0
	// NullSoundInstance::`scalar deleting destructor'

private:
	SoundGroup* m_soundGroup; // 0x0c
};

#endif // NULLSOUNDINSTANCE_H
