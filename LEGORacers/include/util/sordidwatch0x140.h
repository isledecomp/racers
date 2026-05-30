#ifndef SORDIDWATCH0x140_H
#define SORDIDWATCH0x140_H

#include "decomp.h"
#include "types.h"
#include "util/silverhollow0xb8.h"

class SordidWatch0x140 {
public:
	SordidWatch0x140();

	undefined4 GetFlags() const { return m_unk0x010.GetFlags0xb4(); }

	void Reset();
	undefined4 FUN_00412760(undefined4* p_param1, LegoFloat p_param2);
	void FUN_00412840();
	void FUN_00412970();
	undefined4 FUN_00412a00();

private:
	undefined4 m_unk0x000;             // 0x000
	undefined4 m_unk0x004;             // 0x000
	undefined4 m_unk0x008;             // 0x000
	undefined4 m_unk0x00c;             // 0x000
	SilverHollow0xb8 m_unk0x010;       // 0x004
	undefined4 m_unk0xc8;              // 0x0c8
	undefined4 m_unk0xcc;              // 0x0cc
	undefined4 m_unk0xd0;              // 0x0d0
	undefined4 m_unk0xd4;              // 0x0d4
	undefined4 m_unk0xd8;              // 0x0d8
	undefined4 m_unk0xdc;              // 0x0dc
	undefined4 m_unk0xe0;              // 0x0e0
	undefined4 m_unk0xe4;              // 0x0e4
	undefined m_unk0xe8[0x120 - 0xe8]; // 0x0e8
	undefined4 m_unk0x120;             // 0x120
	undefined4 m_unk0x134;             // 0x134
	undefined4 m_unk0x12c;             // 0x12c
	undefined4 m_unk0x130;             // 0x130
	undefined4 m_unk0x124;             // 0x124
	undefined4 m_unk0x128;             // 0x128
	undefined4 m_unk0x138;             // 0x138
	undefined4 m_unk0x13c;             // 0x13c
};

#endif // SORDIDWATCH0x140_H
