#ifndef STATICNULLSOUNDINSTANCE_H
#define STATICNULLSOUNDINSTANCE_H

#include "decomp.h"
#include "types.h"

#include <stddef.h>

class DirectSoundGroup;

// VTABLE: LEGORACERS 0x004b0be4
// SIZE 0x8
class StaticNullSoundInstance {
public:
	virtual void Play(LegoBool32 p_loop); // vtable+0x00
	virtual void Stop();                  // vtable+0x04

	// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
	virtual LegoBool32 IsPlaying() { return FALSE; } // vtable+0x08

	virtual void SetVolume(LegoFloat p_volume);        // vtable+0x0c
	virtual void SetPan(LegoFloat p_pan);              // vtable+0x10
	virtual void SetFrequencyScale(LegoFloat p_scale); // vtable+0x14
	virtual void SetPriority(LegoS32 p_priority);      // vtable+0x18

	// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
	virtual DirectSoundGroup* GetSoundGroup() { return NULL; } // vtable+0x1c

private:
	undefined4 m_unk0x04; // 0x04
};

#endif // STATICNULLSOUNDINSTANCE_H
