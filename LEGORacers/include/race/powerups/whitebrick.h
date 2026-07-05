#ifndef WHITEBRICK_H
#define WHITEBRICK_H

#include "race/powerups/droppablebrick.h"

class Racer;
class RacePowerupManager;

// VTABLE: LEGORACERS 0x004b148c
// SIZE 0x68
class WhiteBrick : public DroppableBrick {
public:
	WhiteBrick();
	~WhiteBrick() override;
	void OnTouched(Racer* p_racer) override;
	void Respawn() override;

	// SYNTHETIC: LEGORACERS 0x00459090
	// WhiteBrick::`vector deleting destructor'

	void Reset();
	void CaptureHomePosition();
	void Update(LegoU32 p_elapsedMs);
};

#endif // WHITEBRICK_H
