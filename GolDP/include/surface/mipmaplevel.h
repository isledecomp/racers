#ifndef MIPMAPLEVEL_H
#define MIPMAPLEVEL_H

#include "decomp.h"
#include "types.h"

// SIZE 0x18
struct MipmapLevel {
	enum {
		c_sizeGeneric = 0,
		c_size8 = 3,
		c_size16 = 4,
		c_size32 = 5,
		c_size64 = 6,
		c_size128 = 7,
		c_size256 = 8
	};

	LegoU8* m_pixels;       // 0x00
	LegoU32 m_pitch;        // 0x04
	LegoU32 m_width;        // 0x08
	LegoU32 m_height;       // 0x0c
	LegoU8 m_bitsPerPixel;  // 0x10
	LegoU8 m_unk0x11;       // 0x11
	LegoU8 m_bytesPerPixel; // 0x12
	LegoS8 m_sizeLog2;      // 0x13
	LegoU16* m_paletteData; // 0x14
};

#endif // MIPMAPLEVEL_H
