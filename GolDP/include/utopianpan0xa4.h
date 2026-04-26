#ifndef GOLDP_UTOPIANPAN_H
#define GOLDP_UTOPIANPAN_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;

// This type is needed because
// - instances of this type have component access like `char[4]`, but copy like an `int`,
// - instances of this type are not aligned to 4 bytes.
struct FourBytes {
	LegoChar m_bytes[4];
};

class UtopianPan0xa4 {
public:
	enum Flags {
		c_flagBit2 = 0x0004,
		c_flagBit3 = 0x0008,
		c_flagBit4 = 0x0010,
		c_flagBit5 = 0x0020,
		c_flagBit6 = 0x0040,
		c_flagBit7 = 0x0080,
		c_flagBit11 = 0x0800,
		c_allFlags = 0xffff,
		c_flagsWithoutBit3 = c_allFlags & ~c_flagBit3,
		c_flagsWithoutBit4 = c_allFlags & ~c_flagBit4
	};

	enum StateFlags {
		c_stateFlagBit0 = 0x01
	};

	// VTable not yet identified. There may be additional functions.
	virtual void VTable0x00() = 0;
	virtual void VTable0x04() = 0;
	virtual void VTable0x08() = 0;
	virtual void VTable0x0c() = 0;
	virtual void VTable0x10() = 0;

	undefined2 m_unk0x04;             // 0x04
	undefined4 m_unk0x08;             // 0x08
	undefined m_unk0x0c[0x24 - 0x0c]; // 0x0c
	BronzeFalcon0xc8770* m_renderer;  // 0x24
	FourBytes m_unk0x28;              // 0x28
	undefined m_unk0x2c[0x3c - 0x2c]; // 0x2c
	LegoU8 m_unk0x3c;                 // 0x3c
	undefined m_unk0x3d[0x40 - 0x3d]; // 0x3d
	LegoU16 m_flags;                  // 0x40
	FourBytes m_name[2];              // 0x42
	FourBytes m_unk0x4a;              // 0x4a
	undefined m_unk0x4e[0xa4 - 0x4e]; // 0x46
};

#endif // GOLDP_UTOPIANPAN_H
