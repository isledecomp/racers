#ifndef GOLATTACHEDSURFACE_H
#define GOLATTACHEDSURFACE_H

#include "decomp.h"
#include "golsurface.h"

class GolRenderTarget;

// VTABLE: GOLDP 0x100577bc
// SIZE 0x34
class GolAttachedSurface : public GolSurface {
public:
	GolAttachedSurface();

	// SYNTHETIC: GOLDP 0x1002f380 FOLDED
	// GolAttachedSurface::`scalar deleting destructor'

protected:
	GolRenderTarget* m_attachedSurface; // 0x30
};

#endif // GOLATTACHEDSURFACE_H
