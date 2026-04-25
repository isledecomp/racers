#ifndef NULLSOUNDMANAGER_H
#define NULLSOUNDMANAGER_H

#include "audio/crimsonray0x20.h"
#include "audio/emberdust0x28.h"
#include "audio/soundmanager.h"
#include "audio/soundnode.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004afc6c
// SIZE 0x30
class NullSoundManager : public SoundManager {
public:
	NullSoundManager();
	~NullSoundManager() override;              // vtable+0x00
	LegoBool32 Initialize(LegoS32) override;   // vtable+0x04
	void Shutdown() override;                  // vtable+0x08
	void Pause() override;                     // vtable+0x0c
	void Resume() override;                    // vtable+0x10
	CrimsonRay0x20* VTable0x14() override;     // vtable+0x14
	void VTable0x18(CrimsonRay0x20*) override; // vtable+0x18
	EmberDust0x28* VTable0x1c() override;      // vtable+0x1c
	void VTable0x20(EmberDust0x28*) override;  // vtable+0x20
	SoundNode* VTable0x24() override;          // vtable+0x24
	void VTable0x28(SoundNode*) override;      // vtable+0x28
	void VTable0x34(undefined4) override;      // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x0041bce0
	// NullSoundManager::`scalar deleting destructor'

private:
	GolList<CrimsonRay0x20> m_unk0x18; // 0x18
	GolList<EmberDust0x28> m_unk0x24;  // 0x24
};

#endif // NULLSOUNDMANAGER_H
