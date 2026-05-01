#ifndef DEPTHBUFFER0X38_H
#define DEPTHBUFFER0X38_H

#include "compat.h"
#include "decomp.h"
#include "moltenquillphantom0x34.h"

#include <ddraw.h>

class GolDrawDPState;

// VTABLE: GOLDP 0x10056964
// SIZE 0x38
class DepthBuffer0x38 : public MoltenQuillPhantom0x34 {
public:
	DepthBuffer0x38();
	~DepthBuffer0x38() override; // vtable+0x00

	void Release();

	// SYNTHETIC: GOLDP 0x100182d0
	// DepthBuffer0x38::`scalar deleting destructor'

	LegoS32 Create(GolDrawDPState* p_arg1, SlatePeak0x58* p_surface);

	friend class SlatePeak0x58;

protected:
	LPDIRECTDRAWSURFACE4 m_surface;
};

#endif // DEPTHBUFFER0X38_H
