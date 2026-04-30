#ifndef CITRINEGROVE0X1F4C_H
#define CITRINEGROVE0X1F4C_H

#include "decomp.h"
#include "marigoldtrail0x108.h"
#include "peridottrace0x4e0.h"
#include "types.h"

// SIZE 0x1f4c
class CitrineGrove0x1f4c {
public:
	CitrineGrove0x1f4c();
	~CitrineGrove0x1f4c();

	PeridotTrace0x4e0* GetUnk0xa58() { return m_unk0xa58; }
	LegoU32 GetUnk0x18c0() const { return m_unk0x18c0; }
	PeridotTraceState0x438& GetUnk0x18c4() { return m_unk0x18c4; }
	LegoU8 GetUnk0x18e6() const { return m_unk0x18c4.GetUnk0x22(); }
	PeridotTraceBuffer0x250& GetUnk0x1cfc() { return m_unk0x1cfc; }

	void FUN_004432d0();
	void FUN_004432e0(undefined4* p_arg1, undefined4 p_arg2);
	undefined4 FUN_00443420(LegoU32 p_index, undefined4 p_arg2);
	undefined4 FUN_004434a0(undefined4);
	void FUN_00443520(undefined4);
	void FUN_004435c0();
	void FUN_00443620(const LegoChar*, PeridotTrace0x4a8*);
	void FUN_004436e0();
	void FUN_00450fc0(const LegoChar* p_path);

private:
	MarigoldTrail0x108 m_unk0x00;        // 0x00
	PeridotTrace0x4a8 m_unk0x108;        // 0x108
	PeridotTrace0x4a8 m_unk0x5b0;        // 0x5b0
	PeridotTrace0x4e0 m_unk0xa58[2];     // 0xa58
	PeridotTrace0x4a8 m_unk0x1418;       // 0x1418
	LegoU32 m_unk0x18c0;                 // 0x18c0
	PeridotTraceState0x438 m_unk0x18c4;  // 0x18c4
	PeridotTraceBuffer0x250 m_unk0x1cfc; // 0x1cfc
};

#endif // CITRINEGROVE0X1F4C_H
