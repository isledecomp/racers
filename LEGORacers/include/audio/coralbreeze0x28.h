#ifndef CORALBREEZE0X28_H
#define CORALBREEZE0X28_H

#include "decomp.h"
#include "gollist.h"
#include "types.h"

class SoundManager;
class SoundInstance;
class StreamingSoundInstance;

// SIZE 0x28
class CoralBreeze0x28 : public GolListLink {
public:
	CoralBreeze0x28() {}

	virtual undefined4 VTable0x00(undefined4) = 0; // vtable+0x00
	virtual undefined4 VTable0x04() = 0;           // vtable+0x04

	void SetUnk0x0c(SoundManager* p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

protected:
	SoundManager* m_unk0x0c;                   // 0x0c
	GolList<SoundInstance> m_unk0x10;          // 0x10
	GolList<StreamingSoundInstance> m_unk0x1c; // 0x1c
};

#endif // CORALBREEZE0X28_H
