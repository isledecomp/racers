#ifndef NULLSTREAMINGSOUNDINSTANCE_H
#define NULLSTREAMINGSOUNDINSTANCE_H

#include "audio/spatialsoundinstance.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

class SoundGroup;

// VTABLE: LEGORACERS 0x004afce4
// SIZE 0x44
class NullStreamingSoundInstance : public SpatialSoundInstance, public GolListLink {
public:
	NullStreamingSoundInstance();
	~NullStreamingSoundInstance() override; // vtable+0x00
	void Play(LegoBool32 p_loop) override;  // vtable+0x04
	void Stop() override;                   // vtable+0x08

	// FUNCTION: LEGORACERS 0x0044e7e0 FOLDED
	LegoBool32 IsPlaying() override { return FALSE; } // vtable+0x0c

	DirectSoundGroup* GetSoundGroup() override;     // vtable+0x10
	void SetPriority(undefined4 p_arg) override;    // vtable+0x14
	void UpdateSpatial(SoundNode* p_node) override; // vtable+0x18

	void SetSoundGroup(SoundGroup* p_soundGroup) { m_soundGroup = p_soundGroup; }

	// SYNTHETIC: LEGORACERS 0x0041c1b0
	// NullStreamingSoundInstance::`scalar deleting destructor'

private:
	SoundGroup* m_soundGroup; // 0x40
};

#endif // NULLSTREAMINGSOUNDINSTANCE_H
