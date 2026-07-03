#ifndef GOLDEPTHBUFFER_H
#define GOLDEPTHBUFFER_H

#include "compat.h"
#include "decomp.h"
#include "surface/golattachedsurface.h"

#include <ddraw.h>

class GolDrawDPState;

// VTABLE: GOLDP 0x10056964
// SIZE 0x38
class GolDepthBuffer : public GolAttachedSurface {
public:
	GolDepthBuffer();
	~GolDepthBuffer() override; // vtable+0x00

	void Release();

	// SYNTHETIC: GOLDP 0x100182d0
	// GolDepthBuffer::`scalar deleting destructor'

	LegoS32 Create(GolDrawDPState* p_arg1, GolRenderTarget* p_surface);

	friend class GolRenderTarget;

protected:
	LPDIRECTDRAWSURFACE4 m_surface; // 0x34
};

#endif // GOLDEPTHBUFFER_H
