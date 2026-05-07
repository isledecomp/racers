#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "types.h"

// SIZE 0x10
struct Rect {
	LegoS32 m_left;   // 0x00
	LegoS32 m_top;    // 0x04
	LegoS32 m_right;  // 0x08
	LegoS32 m_bottom; // 0x0c
};

#endif // RECTANGLE_H
