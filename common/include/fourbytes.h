#ifndef FOURBYTES_H
#define FOURBYTES_H

#include "types.h"

// This type is needed because
// - instances of this type have component access like `char[4]`, but copy like an `int`,
// - instances of this type are not aligned to 4 bytes.
#pragma pack(push, 1)
struct FourBytes {
	union {
		LegoChar m_bytes[4]; // 0x00
		LegoU8 m_uBytes[4];  // 0x00
		LegoU32 m_u32;       // 0x00
	};
};
#pragma pack(pop)

#endif // FOURBYTES_H
