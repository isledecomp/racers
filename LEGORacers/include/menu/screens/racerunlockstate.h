#ifndef RACERUNLOCKSTATE_H
#define RACERUNLOCKSTATE_H

#include "compat.h"
#include "decomp.h"
#include "save/savegame.h"
#include "types.h"

class SaveSystem;

// SIZE 0x28
class RacerUnlockState {
public:
	RacerUnlockState();

	void FUN_00442e60(SaveSystem* p_saveSystem);
	void Reset();
	void FUN_00442e70();
	LegoU32 FUN_00442e80(LegoU32 p_mask) const;
	SaveRecordList::Record* FUN_00442ef0(LegoU32 p_mask);
	SaveRecordList::Record* FUN_00442fe0();
	SaveRecordList::Record* FUN_00443050();
	SaveRecordList::Record* FUN_004430b0();
	SaveRecordList::Record* FUN_004430e0(SaveRecordList::Record* p_record);
	undefined4 GetUnk0x24() const { return m_unk0x24; }

private:
	SaveSystem* m_unk0x00;        // 0x00
	SaveRecordList* m_unk0x04[5]; // 0x04
	LegoU32 m_unk0x18;            // 0x18
	LegoU32 m_unk0x1c;            // 0x1c
	LegoU32 m_unk0x20;            // 0x20
	undefined4 m_unk0x24;         // 0x24
};

#endif // RACERUNLOCKSTATE_H
