#ifndef NULLSTREAMINGSOUNDINSTANCE_H
#define NULLSTREAMINGSOUNDINSTANCE_H

#include "audio/spatialsoundinstance.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

class SoundGroup;
struct SoundNode;

// VTABLE: LEGORACERS 0x004afce4
// SIZE 0x44
class NullStreamingSoundInstance : public SpatialSoundInstance, public GolListLink {
public:
	NullStreamingSoundInstance();
	~NullStreamingSoundInstance() override;         // vtable+0x00
	void Play(LegoBool32 p_loop) override;          // vtable+0x04
	void Stop() override;                           // vtable+0x08
	LegoBool32 IsPlaying() override;                // vtable+0x0c
	DirectSoundGroup* GetSoundGroup() override;     // vtable+0x10
	void VTable0x14(undefined4 p_arg) override;     // vtable+0x14
	void UpdateSpatial(SoundNode* p_node) override; // vtable+0x18

	void SetSoundGroup(SoundGroup* p_soundGroup) { m_soundGroup = p_soundGroup; }

	// SYNTHETIC: LEGORACERS 0x0041c1b0
	// NullStreamingSoundInstance::`scalar deleting destructor'

private:
	SoundGroup* m_soundGroup; // 0x40
};

#endif // NULLSTREAMINGSOUNDINSTANCE_H
