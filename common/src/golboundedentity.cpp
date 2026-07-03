#include "golboundedentity.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GolBoundedEntity, 0x64)

#include "golboundingvolume.h"

// FUNCTION: GOLDP 0x1001b740
GolBoundedEntity::GolBoundedEntity()
{
	m_boundingVolume = 0;
	m_boundedFlags = 0;
}

// FUNCTION: GOLDP 0x1001b760
void GolBoundedEntity::SetBoundingVolume(GolBoundingVolume* p_boundingVolume)
{
	m_boundingVolume = p_boundingVolume;
}

// FUNCTION: LEGORACERS 0x00403f80
void GolBoundedEntity::MirrorY()
{
	m_boundingVolume->MirrorY();
	GolOrientedEntity::MirrorY();
}
