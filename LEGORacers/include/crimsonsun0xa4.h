#ifndef CRIMSONSUN0XA4_H
#define CRIMSONSUN0XA4_H

#include "decomp.h"
#include "types.h"

// SIZE 0xa4
class CrimsonSun0xa4 {
public:
	CrimsonSun0xa4();
	~CrimsonSun0xa4();

	LegoS32 Reset();
	LegoS32 FUN_00468ab0();
	void FUN_00468da0(LegoU32 p_unk0x04);
	void FUN_00468e20();
	LegoBool FUN_00468af0(void* p_unk0x04, LegoS32 p_unk0x08, void* p_unk0x0c);
	undefined4 GetUnk0x9c() { return m_unk0x9c; }

private:
	undefined m_unk0x00[0x9c - 0x00]; // 0x00
	undefined4 m_unk0x9c;             // 0x9c
	undefined m_unk0xa0[0xa4 - 0xa0]; // 0xa0
};

#endif // CRIMSONSUN0XA4_H
