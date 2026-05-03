#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "decomp.h"
#include "types.h"

class MusicGroup;
class SoundGroup;
struct SoundNode;

// VTABLE: LEGORACERS 0x004afa64
// SIZE 0x18
class SoundManager {
public:
	SoundManager();
	virtual ~SoundManager();                              // vtable+0x00
	virtual LegoBool32 Initialize(LegoS32) = 0;           // vtable+0x04
	virtual void Shutdown();                              // vtable+0x08
	virtual void Pause() = 0;                             // vtable+0x0c
	virtual void Resume() = 0;                            // vtable+0x10
	virtual MusicGroup* CreateMusicGroup() = 0;           // vtable+0x14
	virtual void DestroyMusicGroup(MusicGroup*) = 0;      // vtable+0x18
	virtual SoundGroup* CreateSoundGroup() = 0;           // vtable+0x1c
	virtual void DestroySoundGroup(SoundGroup*) = 0;      // vtable+0x20
	virtual SoundNode* CreateSoundNode() = 0;             // vtable+0x24
	virtual void DestroySoundNode(SoundNode*) = 0;        // vtable+0x28
	virtual SoundNode* AddActiveSoundNode(SoundNode*);    // vtable+0x2c
	virtual SoundNode* RemoveActiveSoundNode(SoundNode*); // vtable+0x30
	virtual void Update(undefined4) = 0;                  // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x00417a60
	// SoundManager::`scalar deleting destructor'

	SoundNode* AddNode(SoundNode* p_node);
	SoundNode* RemoveNode(SoundNode* p_node);
	LegoFloat GetVolumeScale() { return m_volumeScale; }
	LegoFloat GetMusicVolumeScale() { return m_musicVolumeScale; }
	void SetVolumeScale(LegoFloat p_volumeScale) { m_volumeScale = p_volumeScale; }
	void SetMusicVolumeScale(LegoFloat p_musicVolumeScale) { m_musicVolumeScale = p_musicVolumeScale; }
	void SetUnk0x04Flag0x04() { m_unk0x04 |= c_flagBit2; }
	void ClearUnk0x04Flag0x04() { m_unk0x04 &= ~c_flagBit2; }

protected:
	enum {
		c_flagBit2 = 1 << 2,
	};

	undefined4 m_unk0x04;          // 0x04
	SoundNode* m_soundNodes;       // 0x08
	SoundNode* m_activeSoundNodes; // 0x0c
	LegoFloat m_volumeScale;       // 0x10
	LegoFloat m_musicVolumeScale;  // 0x14
};

#endif // SOUNDMANAGER_H
