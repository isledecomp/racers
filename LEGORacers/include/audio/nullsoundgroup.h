#ifndef NULLSOUNDGROUP_H
#define NULLSOUNDGROUP_H

#include "audio/soundgroup.h"
#include "compat.h"
#include "decomp.h"

class SoundInstance;
class StreamingSoundInstance;

// VTABLE: LEGORACERS 0x004afd04
// SIZE 0x28
class NullSoundGroup : public SoundGroup {
public:
	NullSoundGroup();
	~NullSoundGroup();
	void Load(const LegoChar* p_name) override; // vtable+0x00
	void Unload() override;                     // vtable+0x04

private:
	GolList<SoundInstance> m_soundInstances;                   // 0x10
	GolList<StreamingSoundInstance> m_streamingSoundInstances; // 0x1c
};

#endif // NULLSOUNDGROUP_H
