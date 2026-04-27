#ifndef NULLMUSICINSTANCE_H
#define NULLMUSICINSTANCE_H

#include "audio/musicinstance.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

class MusicGroup;

// VTABLE: LEGORACERS 0x004afca4
// SIZE 0x10
class NullMusicInstance : public MusicInstance {
public:
	NullMusicInstance();
	~NullMusicInstance() override;               // vtable+0x00
	LegoBool32 Play(LegoBool32 p_loop) override; // vtable+0x04
	void Stop() override;                        // vtable+0x08
	void Pause() override;                       // vtable+0x0c
	void Resume() override;                      // vtable+0x10
	LegoBool32 IsPlaying() override;             // vtable+0x14
	void SetVolume(LegoFloat p_volume) override; // vtable+0x18
	void VTable0x1c(undefined4 p_arg) override;  // vtable+0x1c
	void VTable0x20(undefined4 p_arg) override;  // vtable+0x20

	void SetMusicGroup(MusicGroup* p_musicGroup) { m_musicGroup = p_musicGroup; }

	// SYNTHETIC: LEGORACERS 0x0041bfc0
	// NullMusicInstance::`scalar deleting destructor'

private:
	MusicGroup* m_musicGroup; // 0x0c
};

#endif // NULLMUSICINSTANCE_H
