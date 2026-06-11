#ifndef TURQUOISEGLOWCOLOR_H
#define TURQUOISEGLOWCOLOR_H

#include "types.h"

// SIZE 0x05
struct TurquoiseGlowColor {
	union {
		struct {
			LegoU8 m_hatIndex;        // 0x00
			LegoU8 m_faceIndex;       // 0x01
			LegoU8 m_torsoIndex;      // 0x02
			LegoU8 m_legIndex;        // 0x03
			LegoU8 m_expressionIndex; // 0x04
		};
		LegoU8 m_components[5]; // 0x00
	};
};

#endif // TURQUOISEGLOWCOLOR_H
