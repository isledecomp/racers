#ifndef RACEFORCEFEEDBACK_H
#define RACEFORCEFEEDBACK_H

#include "decomp.h"
#include "types.h"

#include <dinput.h>

class DirectInputDevice;

// SIZE 0x28
class RaceForceFeedback {
public:
	RaceForceFeedback();
	~RaceForceFeedback();

	void FUN_00421e00(DirectInputDevice* p_device);
	void FUN_00422100();
	void FUN_00422130();
	void FUN_00422150();
	void FUN_00422170();
	void FUN_004221a0();

private:
	void FUN_00421de0();
	void FUN_00421e30(LegoU32 p_elapsedMs, LegoFloat p_unk0x08);
	void FUN_00421ef0();
	LegoS32 FUN_00421f40();
	LegoS32 FUN_00421f80(LegoFloat p_unk0x04);
	void FUN_004221d0();
	undefined4 FUN_004222b0(LegoFloat p_unk0x04);

	DirectInputDevice* m_device;  // 0x00
	LegoU32 m_unk0x04;            // 0x04
	LegoU32 m_unk0x08;            // 0x08
	LegoS32 m_unk0x0c;            // 0x0c
	LegoU32 m_unk0x10;            // 0x10
	LegoFloat m_unk0x14;          // 0x14
	LegoU32 m_unk0x18;            // 0x18
	LegoU32 m_unk0x1c;            // 0x1c
	LegoU32 m_unk0x20;            // 0x20
	LPDIRECTINPUTEFFECT m_effect; // 0x24

	friend class RaceSession;
};

#endif // RACEFORCEFEEDBACK_H
