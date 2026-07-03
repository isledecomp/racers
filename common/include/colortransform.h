#ifndef COLORTRANSFORM_H
#define COLORTRANSFORM_H

#include "types.h"

// SIZE 0x20
struct ColorTransform {
	LegoU32 m_redShift;  // 0x00
	LegoU32 m_grnShift;  // 0x04
	LegoU32 m_bluShift;  // 0x08
	LegoU32 m_alpShift;  // 0x0c
	LegoU32 m_redOffset; // 0x10
	LegoU32 m_grnOffset; // 0x14
	LegoU32 m_bluOffset; // 0x18
	LegoU32 m_alpOffset; // 0x1c
};

#endif // COLORTRANSFORM_H
