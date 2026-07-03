#ifndef COLLIDERRECORD_H
#define COLLIDERRECORD_H

#include "golmath.h"
#include "types.h"

class GolCollidableEntity;

// Named collision-flag record looked up in the collider name table
// ("pilcol", "sphinx", "mmrocc"); bits 16/17 gate collidability.
// SIZE 0x0c
class ColliderRecord {
public:
	enum {
		c_flagBit16 = 1 << 16,
		c_flagBit17 = 1 << 17,
	};

	undefined4 m_unk0x00; // 0x00
	undefined4 m_unk0x04; // 0x04
	LegoU32 m_flags;      // 0x08
};
#endif // COLLIDERRECORD_H
