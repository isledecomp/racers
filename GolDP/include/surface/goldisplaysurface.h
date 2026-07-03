#ifndef GOLDP_GOLDISPLAYSURFACE_H
#define GOLDP_GOLDISPLAYSURFACE_H

#include "compat.h"
#include "golsurface.h"

class GolDrawState;

// VTABLE: GOLDP 0x10056dc4
// SIZE 0x38
class GolDisplaySurface : public GolSurface {
public:
	enum {
		c_surfaceFlagWindowed = 0x01,
		c_surfaceFlagFlip = 0x02
	};

	GolDisplaySurface();
	~GolDisplaySurface() override; // vtable+0x00

	virtual void VTable0x30(
		GolDrawState* p_drawState,
		undefined4 p_width,
		undefined4 p_height,
		undefined4 p_bpp
	);                         // vtable+0x30
	virtual void VTable0x34(); // vtable+0x34

	// SYNTHETIC: GOLDP 0x1001d750
	// GolDisplaySurface::`scalar deleting destructor'

protected:
	GolDrawState* m_unk0x30; // 0x30
	undefined4 m_unk0x34;    // 0x34
};

#endif // GOLDP_GOLDISPLAYSURFACE_H
