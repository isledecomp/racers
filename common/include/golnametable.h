#ifndef GOLNAMETABLE_H
#define GOLNAMETABLE_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

// SIZE 0x0c
// VTABLE: GOLDP 0x100572d8
// VTABLE: LEGORACERS 0x004af7c0
class GolNameTable {
public:
	// SIZE 0x0c
	struct Entry {
		LegoChar m_name[8]; // 0x00
		void* m_value;      // 0x08
	};

	GolNameTable();

	virtual ~GolNameTable();                   // vtable+0x00
	virtual void Allocate(LegoU32 p_capacity); // vtable+0x04
	virtual void Clear();                      // vtable+0x08

	void AddName(const LegoChar* p_name, void* p_value);
	void* GetName(const LegoChar* p_name) const;
	LegoChar* GetNameByValue(const void* p_value, LegoChar* p_buffer) const;

	// SYNTHETIC: GOLDP 0x100281e0
	// SYNTHETIC: LEGORACERS 0x004117d0
	// GolNameTable::`scalar deleting destructor'

protected:
	Entry* m_nameEntries; // 0x04
	LegoU32 m_capacity;   // 0x08
};

#endif // GOLNAMETABLE_H
