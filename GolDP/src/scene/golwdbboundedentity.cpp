#include "scene/golwdbboundedentity.h"

// FUNCTION: GOLDP 0x1001b740
GolWdbBoundedEntity::GolWdbBoundedEntity()
{
	m_unk0x58 = 0;
	m_unk0x60 = 0;
}

// FUNCTION: GOLDP 0x1001b760
void GolWdbBoundedEntity::FUN_1001b760(GolBvbBoundingVolume* p_arg)
{
	m_unk0x58 = p_arg;
}
