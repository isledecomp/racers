#ifndef CMBMODELPARTDATA0X28_H
#define CMBMODELPARTDATA0X28_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

class GolFileParser;

// SIZE 0x28
class CmbModelPartData0x28 {
public:
	CmbModelPartData0x28();
	void FUN_10018670(GolFileParser& p_parser);

private:
	LegoFloat m_unk0x00; // 0x00
	GolVec3 m_unk0x04;   // 0x04
	GolVec4 m_unk0x10;   // 0x10
	LegoU32 m_unk0x20;   // 0x20
	LegoU16 m_unk0x24;   // 0x24
	LegoU16 m_unk0x26;   // 0x26
};

#endif // CMBMODELPARTDATA0X28_H
