#ifndef SOUNDNODE_H
#define SOUNDNODE_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

// SIZE 0x0c
struct SoundVector : public GolVec3 {};

// SIZE 0x50
struct SoundNode {
	SoundNode();

	SoundVector m_position;           // 0x00
	SoundVector m_velocity;           // 0x0c
	LegoFloat m_volume;               // 0x18
	LegoFloat m_unk0x1c;              // 0x1c
	LegoFloat m_unk0x20;              // 0x20
	LegoFloat m_unk0x24;              // 0x24
	LegoFloat m_unk0x28;              // 0x28
	LegoFloat m_frequencyScale;       // 0x2c
	SoundVector m_orientation;        // 0x30
	LegoFloat m_soundSpeed;           // 0x3c
	LegoFloat m_maxVelocity;          // 0x40
	undefined4 m_unk0x44;             // 0x44
	SoundNode* m_nextSoundNode;       // 0x48
	SoundNode* m_nextActiveSoundNode; // 0x4c
};

#endif // SOUNDNODE_H
