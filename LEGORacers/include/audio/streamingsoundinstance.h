#ifndef STREAMINGSOUNDINSTANCE_H
#define STREAMINGSOUNDINSTANCE_H

#include "audio/soundinstancebase0x38.h"
#include "compat.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

class FrostPetal0x34;
class SoundBuffer;

// VTABLE: LEGORACERS 0x004afbe4
// SIZE 0x48
class StreamingSoundInstance : public SoundInstanceBase0x38, public GolListLink {
public:
	StreamingSoundInstance();
	~StreamingSoundInstance() override;   // vtable+0x00
	void VTable0x04(undefined4) override; // vtable+0x04
	void VTable0x08() override;           // vtable+0x08
	undefined4 VTable0x0c() override;     // vtable+0x0c
	undefined4 VTable0x10() override;     // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14
	void VTable0x18(undefined4) override; // vtable+0x18

	// SYNTHETIC: LEGORACERS 0x0041ace0
	// StreamingSoundInstance::`scalar deleting destructor'

	void SetOwner(FrostPetal0x34* p_owner) { m_owner = p_owner; }
	void SetSoundBuffer(SoundBuffer* p_soundBuffer) { m_soundBuffer = p_soundBuffer; }
	FrostPetal0x34* GetOwner() { return m_owner; }

private:
	FrostPetal0x34* m_owner;    // 0x40
	SoundBuffer* m_soundBuffer; // 0x44
};

#endif // STREAMINGSOUNDINSTANCE_H
