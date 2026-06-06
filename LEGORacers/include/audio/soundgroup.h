#ifndef SOUNDGROUP_H
#define SOUNDGROUP_H

#include "decomp.h"
#include "gollist.h"
#include "types.h"

class SoundManager;
class SoundInstance;
class StreamingSoundInstance;
struct SoundVector;

// SIZE 0x10
class SoundGroup : public GolListLink {
public:
	SoundGroup() {}

	virtual void Load(const LegoChar* p_name) = 0; // vtable+0x00
	virtual void Unload() = 0;                     // vtable+0x04
	virtual LegoBool32 IsLoaded() = 0;             // vtable+0x08
	virtual LegoU32 GetSoundCount() = 0;           // vtable+0x0c
	virtual void PlaySpatialSound(
		LegoU32 p_index,
		SoundVector* p_position,
		LegoFloat p_minDistance,
		LegoFloat p_maxDistance,
		LegoFloat p_volume,
		LegoFloat p_frequencyScale
	) = 0;                                                                     // vtable+0x10
	virtual void PlaySoundByIndex(LegoU32 p_index) = 0;                        // vtable+0x14
	virtual SoundInstance* CreateSoundInstance(LegoU32 p_index) = 0;           // vtable+0x18
	virtual void DestroySoundInstance(SoundInstance* p_sound) = 0;             // vtable+0x1c
	virtual StreamingSoundInstance* CreateStreamingSoundInstance(LegoU32) = 0; // vtable+0x20
	virtual void DestroyStreamingSoundInstance(StreamingSoundInstance*) = 0;   // vtable+0x24
	virtual SoundManager* GetSoundManager() = 0;                               // vtable+0x28

	void SetSoundManager(SoundManager* p_soundManager) { m_soundManager = p_soundManager; }

protected:
	SoundManager* m_soundManager; // 0x0c
};

#endif // SOUNDGROUP_H
