#ifndef ACTIONSETUP_H
#define ACTIONSETUP_H

#include "golmath.h"
#include "race/powerups/actiontarget.h"
#include "race/targetpointlist.h"
#include "types.h"

class Racer;

// SIZE 0x14
class ActionSetup {
public:
	Racer* m_racer;                        // 0x00
	Racer* m_targetRacer;                  // 0x04
	TargetPointList::Entry* m_targetPoint; // 0x08
	ActionTarget* m_aimTarget;             // 0x0c
	LegoU32 m_initialTimerMs;              // 0x10
};

#endif // ACTIONSETUP_H
