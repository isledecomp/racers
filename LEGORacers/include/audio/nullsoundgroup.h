#ifndef NULLSOUNDGROUP_H
#define NULLSOUNDGROUP_H

#include "audio/soundgroup.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"

class SoundInstance;
class SoundManager;
struct SoundVector;
class NullSoundInstance;
class NullStreamingSoundInstance;
class StreamingSoundInstance;

// VTABLE: LEGORACERS 0x004afd04
// SIZE 0x28
class NullSoundGroup : public SoundGroup {
public:
	NullSoundGroup();
	~NullSoundGroup();
	void Load(const LegoChar* p_name) override; // vtable+0x00
	void Unload() override;                     // vtable+0x04
	LegoBool32 IsLoaded() override;             // vtable+0x08
	LegoU32 GetSoundCount() override;           // vtable+0x0c
	void PlaySpatialSound(
		LegoU32 p_index,
		SoundVector* p_position,
		LegoFloat p_minDistance,
		LegoFloat p_maxDistance,
		LegoFloat p_volume,
		LegoFloat p_frequencyScale
	) override;                                                                     // vtable+0x10
	void PlaySoundByIndex(LegoU32 p_index) override;                                // vtable+0x14
	SoundInstance* CreateSoundInstance(LegoU32 p_index) override;                   // vtable+0x18
	void DestroySoundInstance(SoundInstance* p_sound) override;                     // vtable+0x1c
	StreamingSoundInstance* CreateStreamingSoundInstance(LegoU32 p_index) override; // vtable+0x20
	void DestroyStreamingSoundInstance(StreamingSoundInstance* p_sound) override;   // vtable+0x24
	SoundManager* GetSoundManager() override;                                       // vtable+0x28

private:
	GolList<NullSoundInstance> m_soundInstances;                   // 0x10
	GolList<NullStreamingSoundInstance> m_streamingSoundInstances; // 0x1c
};

#endif // NULLSOUNDGROUP_H
