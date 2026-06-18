#include "golboundedentity.h"

#include "golboundingvolume.h"

// FUNCTION: GOLDP 0x1001b740
GolBoundedEntity::GolBoundedEntity()
{
	m_unk0x58 = 0;
	m_unk0x60 = 0;
}

// FUNCTION: GOLDP 0x1001b760
void GolBoundedEntity::FUN_1001b760(GolBoundingVolume* p_arg)
{
	m_unk0x58 = p_arg;
}

// FUNCTION: LEGORACERS 0x00403f80
void GolBoundedEntity::FUN_00403f80()
{
	m_unk0x58->FUN_004045e0();
	FUN_00411040();
}
