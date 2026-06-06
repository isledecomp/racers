#ifndef RACERPICKMODELSTATE0X28_H
#define RACERPICKMODELSTATE0X28_H

#include "compat.h"
#include "decomp.h"
#include "save/peridottrace0x4e0.h"
#include "types.h"

class SaveSystem;

// SIZE 0x28
class RacerPickModelState0x28 {
public:
	RacerPickModelState0x28();

	void FUN_00442e60(SaveSystem* p_saveSystem);
	void Reset();
	LegoU32 FUN_00442e80(LegoU32 p_mask) const;
	PeridotTraceBase0x24::Record* FUN_00442ef0(LegoU32 p_mask);
	PeridotTraceBase0x24::Record* FUN_00442fe0();
	PeridotTraceBase0x24::Record* FUN_00443050();
	PeridotTraceBase0x24::Record* FUN_004430b0();
	undefined4 GetUnk0x24() const { return m_unk0x24; }

private:
	SaveSystem* m_unk0x00;              // 0x00
	PeridotTraceBase0x24* m_unk0x04[5]; // 0x04
	LegoU32 m_unk0x18;                  // 0x18
	LegoU32 m_unk0x1c;                  // 0x1c
	LegoU32 m_unk0x20;                  // 0x20
	undefined4 m_unk0x24;               // 0x24
};

#endif // RACERPICKMODELSTATE0X28_H
