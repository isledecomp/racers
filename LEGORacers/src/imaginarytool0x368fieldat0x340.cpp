#include "imaginarytool0x368.h"

DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x340, 0x10)

// FUNCTION: LEGORACERS 0x00408460
ImaginaryTool0x368::FieldAt0x340::FieldAt0x340()
{
	m_direction.m_z = -1.0f;
	m_direction.m_x = 0.0f;
	m_direction.m_y = 0.0f;
}

// FUNCTION: LEGORACERS 0x00408480
void ImaginaryTool0x368::FieldAt0x340::SetDirection(const GolVec3& p_direction)
{
	GolMath::NormalizeVector3(p_direction, &m_direction);
}
