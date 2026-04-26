#ifndef STACKOFLEGOU16_H
#define STACKOFLEGOU16_H

#include "decomp.h"
#include "types.h"

// SIZE 0x0c
class StackOfLegoU16 {
public:
	StackOfLegoU16();
	~StackOfLegoU16();

	LegoS32 Reset();
	LegoBool32 Allocate(LegoS32 p_capacity);
	LegoBool32 Clear();
	LegoBool32 Push(LegoU16 p_value);
	LegoU16 Pop();
	LegoU16 Peek();
	LegoS32 GetSize() { return m_size; }

private:
	LegoU16* m_buffer;  // 0x00
	LegoS32 m_capacity; // 0x04
	LegoS32 m_size;     // 0x08
};

#endif // STACKOFLEGOU16_H
