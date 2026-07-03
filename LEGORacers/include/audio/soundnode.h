#ifndef SOUNDNODE_H
#define SOUNDNODE_H

#include "audio/soundvector.h"
#include "decomp.h"
#include "golmath.h"
#include "types.h"

// SIZE 0x50
struct SoundNode {
	SoundNode();

	SoundVector m_position;           // 0x00
	SoundVector m_velocity;           // 0x0c
	SoundVector m_right;              // 0x18
	SoundVector m_forward;            // 0x24
	SoundVector m_orientation;        // 0x30
	LegoFloat m_soundSpeed;           // 0x3c
	LegoFloat m_maxVelocity;          // 0x40
	undefined4 m_unk0x44;             // 0x44
	SoundNode* m_nextSoundNode;       // 0x48
	SoundNode* m_nextActiveSoundNode; // 0x4c
};

#endif // SOUNDNODE_H
