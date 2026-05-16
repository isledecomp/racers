#ifndef GOLBYTEORDER_H
#define GOLBYTEORDER_H

#include "types.h"

inline LegoU16 ReadLittleEndianU16(const LegoU8* p_source)
{
	return static_cast<LegoU16>(p_source[0] + (p_source[1] << 8));
}

inline LegoU32 ReadLittleEndianU32(const LegoU8* p_source)
{
	return (static_cast<LegoU32>(p_source[3]) << 24) + (static_cast<LegoU32>(p_source[2]) << 16) +
		   (static_cast<LegoU32>(p_source[1]) << 8) + p_source[0];
}

inline void WriteLittleEndianU32(LegoU8* p_dest, LegoU32 p_value)
{
	p_dest[0] = static_cast<LegoU8>(p_value);
	p_dest[1] = static_cast<LegoU8>(p_value >> 8);
	p_dest[2] = static_cast<LegoU8>(p_value >> 16);
	p_dest[3] = static_cast<LegoU8>(p_value >> 24);
}

#endif // GOLBYTEORDER_H
