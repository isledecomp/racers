#ifndef GOLDEPTHBUFFER_H
#define GOLDEPTHBUFFER_H

#include "compat.h"
#include "decomp.h"
#include "surface/moltenquillphantom0x34.h"

#include <ddraw.h>

class GolDrawDPState;

// VTABLE: GOLDP 0x10056964
// SIZE 0x38
class GolDepthBuffer : public MoltenQuillPhantom0x34 {
public:
	GolDepthBuffer();
	~GolDepthBuffer() override; // vtable+0x00

	void Release();

	// SYNTHETIC: GOLDP 0x100182d0
	// GolDepthBuffer::`scalar deleting destructor'

	LegoS32 Create(GolDrawDPState* p_arg1, SlatePeak0x58* p_surface);

	friend class SlatePeak0x58;

protected:
	LPDIRECTDRAWSURFACE4 m_surface;
};

#endif // GOLDEPTHBUFFER_H
