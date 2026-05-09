#ifndef COLOR_H
#define COLOR_H

#include "types.h"

#define ARGBU32(A, R, G, B) ((((A) & 0xff) << 24) | (((R) & 0xff) << 16) | (((G) & 0xff) << 8) | (((B) & 0xff) << 0))

// SIZE: 0x4
struct ColorRGBA {
	LegoU8 m_red; // 0x00
	LegoU8 m_grn; // 0x01
	LegoU8 m_blu; // 0x02
	LegoU8 m_alp; // 0x03
};

// SIZE: 0x3
struct ColorBGR {
	LegoU8 m_blu; // 0x00
	LegoU8 m_grn; // 0x01
	LegoU8 m_red; // 0x02
};

// SIZE: 0xc
struct FColorRGB {
	LegoFloat m_red; // 0x00
	LegoFloat m_grn; // 0x04
	LegoFloat m_blu; // 0x08
};
#endif // COLOR_H
