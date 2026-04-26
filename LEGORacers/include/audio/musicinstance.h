#ifndef MUSICINSTANCE_H
#define MUSICINSTANCE_H

#include "audio/musicinstancebase.h"
#include "compat.h"
#include "decomp.h"

class MusicGroup;

// VTABLE: LEGORACERS 0x004afca4
// SIZE 0x10
class MusicInstance : public MusicInstanceBase {
public:
	MusicInstance();
	~MusicInstance() override;                  // vtable+0x00
	undefined4 VTable0x04(undefined4) override; // vtable+0x04
	void Stop() override;                       // vtable+0x08
	void VTable0x0c() override;                 // vtable+0x0c

	void SetMusicGroup(MusicGroup* p_musicGroup) { m_musicGroup = p_musicGroup; }

	// SYNTHETIC: LEGORACERS 0x0041bfc0
	// MusicInstance::`scalar deleting destructor'

private:
	MusicGroup* m_musicGroup; // 0x0c
};

#endif // MUSICINSTANCE_H
