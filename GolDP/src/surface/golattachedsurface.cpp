#include "surface/golattachedsurface.h"

#include "decomp.h"

#include <stddef.h>

DECOMP_SIZE_ASSERT(GolAttachedSurface, 0x34)

// FUNCTION: GOLDP 0x1002f360
GolAttachedSurface::GolAttachedSurface()
{
	m_attachedSurface = NULL;
}
