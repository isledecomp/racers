#ifndef NULLSOUNDGROUP_H
#define NULLSOUNDGROUP_H

#include "audio/soundgroup.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"

class SoundInstance;
class SoundManager;
struct SoundNode;
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
	virtual LegoBool32 IsLoaded();              // vtable+0x08
	virtual LegoU32 GetSoundCount();            // vtable+0x0c
	virtual void PlaySpatialSound(
		LegoU32 p_index,
		SoundNode* p_node,
		LegoFloat p_minDistance,
		LegoFloat p_maxDistance,
		LegoFloat p_volume,
		LegoFloat p_frequencyScale
	);                                                                             // vtable+0x10
	virtual void PlaySoundByIndex(LegoU32 p_index);                                // vtable+0x14
	virtual SoundInstance* CreateSoundInstance(LegoU32 p_index);                   // vtable+0x18
	virtual void DestroySoundInstance(SoundInstance* p_sound);                     // vtable+0x1c
	virtual StreamingSoundInstance* CreateStreamingSoundInstance(LegoU32 p_index); // vtable+0x20
	virtual void DestroyStreamingSoundInstance(StreamingSoundInstance* p_sound);   // vtable+0x24
	virtual SoundManager* GetSoundManager();                                       // vtable+0x28

private:
	GolList<NullSoundInstance> m_soundInstances;                   // 0x10
	GolList<NullStreamingSoundInstance> m_streamingSoundInstances; // 0x1c
};

#endif // NULLSOUNDGROUP_H
