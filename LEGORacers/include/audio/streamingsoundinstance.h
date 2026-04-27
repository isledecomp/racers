#ifndef STREAMINGSOUNDINSTANCE_H
#define STREAMINGSOUNDINSTANCE_H

#include "audio/spatialsoundinstance.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

class DirectSoundGroup;
class SoundBuffer;
struct SoundNode;

// VTABLE: LEGORACERS 0x004afbe4
// SIZE 0x48
class StreamingSoundInstance : public SpatialSoundInstance, public GolListLink {
public:
	StreamingSoundInstance();
	~StreamingSoundInstance() override;             // vtable+0x00
	void Play(LegoBool32 p_loop) override;          // vtable+0x04
	void Stop() override;                           // vtable+0x08
	LegoBool32 IsPlaying() override;                // vtable+0x0c
	DirectSoundGroup* GetSoundGroup() override;     // vtable+0x10
	void VTable0x14(undefined4) override;           // vtable+0x14
	void UpdateSpatial(SoundNode* p_node) override; // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x0041ace0
	// StreamingSoundInstance::`scalar deleting destructor'

	void SetSoundGroup(DirectSoundGroup* p_soundGroup) { m_soundGroup = p_soundGroup; }
	void SetSoundBuffer(SoundBuffer* p_soundBuffer) { m_soundBuffer = p_soundBuffer; }
	DirectSoundGroup* GetSoundGroupDirect() { return m_soundGroup; }
	SoundBuffer* GetSoundBuffer() { return m_soundBuffer; }

private:
	DirectSoundGroup* m_soundGroup; // 0x40
	SoundBuffer* m_soundBuffer;     // 0x44
};

#endif // STREAMINGSOUNDINSTANCE_H
