#include "whitefalcon0x140.h"

DECOMP_SIZE_ASSERT(WhiteFalcon0x140::Light, 0x10)

// FUNCTION: LEGORACERS 0x00408460
WhiteFalcon0x140::Light::Light()
{
	m_direction.m_z = -1.0f;
	m_direction.m_x = 0.0f;
	m_direction.m_y = 0.0f;
}

// FUNCTION: LEGORACERS 0x00408480
void WhiteFalcon0x140::Light::SetDirection(const GolVec3& p_direction)
{
	GolMath::NormalizeVector3(p_direction, &m_direction);
}
