#include "audio/soundnode.h"

DECOMP_SIZE_ASSERT(SoundVector, 0x0c)
DECOMP_SIZE_ASSERT(SoundNode, 0x50)

// GLOBAL: LEGORACERS 0x004afa38
LegoFloat g_speedOfSound = 343.0f;

// FUNCTION: LEGORACERS 0x004179a0
SoundNode::SoundNode()
{
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_velocity.m_x = 0.0f;
	m_velocity.m_y = 0.0f;
	m_velocity.m_z = 0.0f;
	m_right.m_x = 1.0f;
	m_right.m_y = 0.0f;
	m_right.m_z = 0.0f;
	m_forward.m_x = 0.0f;
	m_forward.m_y = 0.0f;
	m_forward.m_z = 1.0f;
	m_orientation.m_x = 0.0f;
	m_orientation.m_y = 1.0f;
	m_orientation.m_z = 0.0f;
	m_soundSpeed = g_speedOfSound;
	m_maxVelocity = g_speedOfSound * 0.5f;
	m_unk0x44 = 1;
}
