#ifndef DIRECTSOUNDGROUP_H
#define DIRECTSOUNDGROUP_H

#include "audio/soundgroup.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

class SoundManager;
class SoundInstance;
class StreamingSoundInstance;

// VTABLE: LEGORACERS 0x004afc08
// SIZE 0x34
class DirectSoundGroup : public SoundGroup {
public:
	DirectSoundGroup();
	~DirectSoundGroup();
	void Load(const LegoChar* p_name) override;                                               // vtable+0x00
	void Unload() override;                                                                   // vtable+0x04
	virtual LegoBool32 IsLoaded();                                                            // vtable+0x08
	virtual undefined4 VTable0x0c();                                                          // vtable+0x0c
	virtual void VTable0x10(undefined4, LegoFloat, LegoFloat, LegoFloat, LegoS32, LegoFloat); // vtable+0x10
	virtual void VTable0x14(LegoFloat);                                                       // vtable+0x14
	virtual SoundInstance* CreateSoundInstance(undefined4);                                   // vtable+0x18
	virtual void DestroySoundInstance(SoundInstance*);                                        // vtable+0x1c
	virtual StreamingSoundInstance* CreateStreamingSoundInstance(undefined4);                 // vtable+0x20
	virtual void DestroyStreamingSoundInstance(StreamingSoundInstance*);                      // vtable+0x24
	virtual SoundManager* GetSoundManager();                                                  // vtable+0x28

private:
	undefined4 m_unk0x10;                                      // 0x10
	undefined4 m_unk0x14;                                      // 0x14
	undefined4 m_unk0x18;                                      // 0x18
	GolList<SoundInstance> m_soundInstances;                   // 0x1c
	GolList<StreamingSoundInstance> m_streamingSoundInstances; // 0x28
};

#endif // DIRECTSOUNDGROUP_H
