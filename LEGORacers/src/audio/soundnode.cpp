#include "audio/soundnode.h"

DECOMP_SIZE_ASSERT(SoundVector, 0x0c)
DECOMP_SIZE_ASSERT(SoundNode, 0x50)

// GLOBAL: LEGORACERS 0x004af58c
LegoFloat g_unk0x4af58c = 0.5f;

// GLOBAL: LEGORACERS 0x004afa38
LegoFloat g_unk0x4afa38 = 343.0f;

// FUNCTION: LEGORACERS 0x004179a0
SoundNode::SoundNode()
{
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_volume = 1.0f;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_frequencyScale = 1.0f;
	m_orientation.m_x = 0.0f;
	m_orientation.m_y = 1.0f;
	m_orientation.m_z = 0.0f;
	m_soundSpeed = g_unk0x4afa38;

	LegoFloat scaledDistance = g_unk0x4afa38;
	m_maxVelocity = scaledDistance * g_unk0x4af58c;
	m_unk0x44 = 1;
}
