#ifndef GOLDISPLAYSURFACE_H
#define GOLDISPLAYSURFACE_H

#include "compat.h"
#include "decomp.h"
#include "golsurface.h"
#include "types.h"

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

	virtual void Create(
		GolDrawState* p_drawState,
		undefined4 p_width,
		undefined4 p_height,
		undefined4 p_bpp
	);                      // vtable+0x30
	virtual void Destroy(); // vtable+0x34

	// SYNTHETIC: GOLDP 0x1001d750
	// GolDisplaySurface::`scalar deleting destructor'

protected:
	GolDrawState* m_displayDrawState; // 0x30
	LegoU32 m_surfaceFlags;           // 0x34
};

#endif // GOLDISPLAYSURFACE_H
