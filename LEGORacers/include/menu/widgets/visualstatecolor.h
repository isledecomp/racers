#ifndef VISUALSTATECOLOR_H
#define VISUALSTATECOLOR_H

#include "decomp.h"
#include "surface/color.h"
#include "types.h"

#pragma pack(push, 1)

// SIZE 0x04
class VisualStateColor {
public:
	union {
		LegoU32 m_packed;  // 0x00
		LegoS8 m_bytes[4]; // 0x00
		ColorRGBA m_color; // 0x00
	};
};

#pragma pack(pop)

#endif // VISUALSTATECOLOR_H
