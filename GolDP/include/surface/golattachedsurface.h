#ifndef GOLATTACHEDSURFACE_H
#define GOLATTACHEDSURFACE_H

#include "golsurface.h"

class GolRenderTarget;

// VTABLE: GOLDP 0x100577bc
// SIZE 0x34
class GolAttachedSurface : public GolSurface {
public:
	GolAttachedSurface();

protected:
	GolRenderTarget* m_attachedSurface; // 0x30
};

#endif // GOLATTACHEDSURFACE_H
