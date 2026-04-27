#ifndef DIRECTSOUNDGROUP_H
#define DIRECTSOUNDGROUP_H

#include "audio/soundgroup.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

class SoundManager;
class SoundInstance;
class SoundData;
struct SoundNode;
class StreamingSoundInstance;

// VTABLE: LEGORACERS 0x004afc08
// SIZE 0x34
class DirectSoundGroup : public SoundGroup {
public:
	enum {
		c_audioPathLength = 260,
		c_soundBankExtensionLength = 4,
		c_soundCountLength = 4,
		c_fileBufferSize = 0x1000
	};

	DirectSoundGroup();
	~DirectSoundGroup();
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
	undefined4 m_unk0x10;                                      // 0x10
	LegoU32 m_soundCount;                                      // 0x14
	SoundData* m_soundData;                                    // 0x18
	GolList<SoundInstance> m_soundInstances;                   // 0x1c
	GolList<StreamingSoundInstance> m_streamingSoundInstances; // 0x28
};

#endif // DIRECTSOUNDGROUP_H
