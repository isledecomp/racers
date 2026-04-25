#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "decomp.h"
#include "types.h"

class CrimsonRay0x20;
class EmberDust0x28;
struct SoundNode;

// VTABLE: LEGORACERS 0x004afa64
// SIZE 0x18
class SoundManager {
public:
	SoundManager();
	virtual ~SoundManager();                      // vtable+0x00
	virtual LegoBool32 Initialize(LegoS32) = 0;   // vtable+0x04
	virtual void Shutdown();                      // vtable+0x08
	virtual void Pause() = 0;                     // vtable+0x0c
	virtual void Resume() = 0;                    // vtable+0x10
	virtual CrimsonRay0x20* VTable0x14() = 0;     // vtable+0x14
	virtual void VTable0x18(CrimsonRay0x20*) = 0; // vtable+0x18
	virtual EmberDust0x28* VTable0x1c() = 0;      // vtable+0x1c
	virtual void VTable0x20(EmberDust0x28*) = 0;  // vtable+0x20
	virtual SoundNode* VTable0x24() = 0;          // vtable+0x24
	virtual void VTable0x28(SoundNode*) = 0;      // vtable+0x28
	virtual SoundNode* VTable0x2c(SoundNode*);    // vtable+0x2c
	virtual SoundNode* VTable0x30(SoundNode*);    // vtable+0x30
	virtual void VTable0x34(undefined4) = 0;      // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x00417a60
	// SoundManager::`scalar deleting destructor'

	SoundNode* AddNode(SoundNode* p_node);
	SoundNode* RemoveNode(SoundNode* p_node);

protected:
	undefined4 m_unk0x04; // 0x04
	SoundNode* m_unk0x08; // 0x08
	SoundNode* m_unk0x0c; // 0x0c
	LegoFloat m_unk0x10;  // 0x10
	LegoFloat m_unk0x14;  // 0x14
};

#endif // SOUNDMANAGER_H
