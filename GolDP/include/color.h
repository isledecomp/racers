#ifndef COLOR_H
#define COLOR_H

#include "types.h"

struct ColorRGBA {
	LegoU8 m_red; // 0x00
	LegoU8 m_grn; // 0x01
	LegoU8 m_blu; // 0x02
	LegoU8 m_alp; // 0x03
};

#endif // COLOR_H
