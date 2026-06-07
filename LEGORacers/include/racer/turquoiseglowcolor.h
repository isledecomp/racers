#ifndef TURQUOISEGLOWCOLOR_H
#define TURQUOISEGLOWCOLOR_H

#include "types.h"

// SIZE 0x05
struct TurquoiseGlowColor {
	union {
		struct {
			LegoU8 m_unk0x00; // 0x00
			LegoU8 m_unk0x01; // 0x01
			LegoU8 m_unk0x02; // 0x02
			LegoU8 m_unk0x03; // 0x03
			LegoU8 m_unk0x04; // 0x04
		};
		LegoU8 m_components[5]; // 0x00
	};
};

#endif // TURQUOISEGLOWCOLOR_H
