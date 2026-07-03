#ifndef WDBLIGHT_H
#define WDBLIGHT_H

#include "golmath.h"
#include "surface/color.h"
#include "types.h"

// SIZE 0x10
struct WdbLight {
	ColorRGBA m_color;   // 0x00
	GolVec3 m_direction; // 0x04
};

#endif // WDBLIGHT_H
