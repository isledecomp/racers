#ifndef DROPPABLEBRICK_H
#define DROPPABLEBRICK_H

#include "race/powerups/pickupbrick.h"

class RacePowerupManager;
class Racer;

// SIZE 0x68
class DroppableBrick : public PickupBrick {
public:
	LegoU8 DropAt(GolVec3 p_position);
	void ReturnHome();
	LegoS32 SnapToGround(GolVec3* p_position);

protected:
	GolVec3 m_homePosition;           // 0x54
	LegoU32 m_droppedTimeMs;          // 0x60
	LegoU8 m_flags;                   // 0x64
	undefined m_unk0x65[0x68 - 0x65]; // 0x65
};
#endif // DROPPABLEBRICK_H
