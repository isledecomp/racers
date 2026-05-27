#include "render/golrenderdevice.h"

DECOMP_SIZE_ASSERT(GolRenderDevice::Light, 0x10)

// FUNCTION: GOLDP 0x1001ced0
// FUNCTION: LEGORACERS 0x00408460
GolRenderDevice::Light::Light()
{
	m_direction.m_z = -1.0f;
	m_direction.m_x = 0.0f;
	m_direction.m_y = 0.0f;
}

// FUNCTION: GOLDP 0x1001cef0
// FUNCTION: LEGORACERS 0x00408480
void GolRenderDevice::Light::SetDirection(const GolVec3& p_direction)
{
	GolMath::NormalizeVector3(p_direction, &m_direction);
}
