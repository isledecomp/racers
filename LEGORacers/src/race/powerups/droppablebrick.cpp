#include "race/racesession.h"

DECOMP_SIZE_ASSERT(DroppableBrick, 0x68)

// GLOBAL: LEGORACERS 0x004b1480
extern const LegoFloat g_brickGroundOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b1488
extern const LegoFloat g_brickProbeRange = 25.0f;

// FUNCTION: LEGORACERS 0x00453790
LegoU8 DroppableBrick::DropAt(GolVec3 p_position)
{
	GolVec3 position;

	position.m_x = p_position.m_x;
	position.m_y = p_position.m_y;
	position.m_z = p_position.m_z;

	SnapToGround(&position);
	m_worldEntity.SetPosition(position);

	LegoU8 flags = m_flags;
	m_state = c_stateActive;
	LegoU8 result = flags | 1;
	m_stateTimerMs = 0;
	m_flags = result;
	return result;
}

// FUNCTION: LEGORACERS 0x004537f0
void DroppableBrick::ReturnHome()
{
	LegoU32 state = m_state;
	LegoU8 flags = m_flags;
	flags &= 0xfe;
	m_droppedTimeMs = 0;
	m_flags = flags;

	if (!state) {
		flags |= 2;
		m_state = c_stateTransition;
		m_flags = flags;
		m_stateTimerMs = 0;
		return;
	}

	m_worldEntity.SetPosition(m_homePosition);
	m_state = c_stateActive;
	m_stateTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00453840
LegoS32 DroppableBrick::SnapToGround(GolVec3* p_position)
{
	GolVec3 start;
	GolVec3 end;
	GolBoundingVolume::HitTriangle record;

	start.m_x = p_position->m_x;
	start.m_y = p_position->m_y;
	start.m_z = p_position->m_z + g_brickProbeRange;

	end.m_x = p_position->m_x;
	end.m_y = p_position->m_y;
	end.m_z = p_position->m_z - g_brickProbeRange;

	LegoS32 result = m_manager->m_collisionWorld->IntersectSegment(&start, &end, &record, p_position, NULL);
	p_position->m_z = p_position->m_z + g_brickGroundOffset;
	return result;
}
