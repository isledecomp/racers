#ifndef MUSICINSTANCESTATE_H
#define MUSICINSTANCESTATE_H

#include "audio/musicinstance.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

class MusicGroup;

// VTABLE: LEGORACERS 0x004afba4
// SIZE 0x18
class MusicInstanceState : public MusicInstance {
public:
	MusicInstanceState();
	~MusicInstanceState() override;              // vtable+0x00
	void SetVolume(LegoFloat p_volume) override; // vtable+0x18

	void SetMusicGroup(MusicGroup* p_musicGroup) { m_musicGroup = p_musicGroup; }
	MusicGroup* GetMusicGroup() { return m_musicGroup; }

	// SYNTHETIC: LEGORACERS 0x0041a5a0
	// MusicInstanceState::`scalar deleting destructor'

protected:
	MusicGroup* m_musicGroup; // 0x0c
	LegoFloat m_volume;       // 0x10
	LegoBool m_playing;       // 0x14
	LegoBool m_paused;        // 0x15
	LegoBool m_wasPaused;     // 0x16
	LegoBool m_playFlag;      // 0x17
};

#endif // MUSICINSTANCESTATE_H
