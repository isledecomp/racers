#ifndef HAZARDACTIONBASE_H
#define HAZARDACTIONBASE_H

#include "race/powerups/powerupactionbase.h"

// SIZE 0x2c
class HazardActionBase : public PowerupActionBase {
public:
	enum {
		c_racerFlags0xd04Bit0 = 1 << 0,
	};

	HazardActionBase();

	// SYNTHETIC: LEGORACERS 0x00451960
	// HazardActionBase::~HazardActionBase

	// SYNTHETIC: LEGORACERS 0x00456300
	// HazardActionBase::`scalar deleting destructor'

	void OnEvent(LegoEventQueue::CallbackData* p_param) override; // vtable+0x00
	void AdvanceState() override;                                 // vtable+0x14
	LegoS32 GetBrickColor() override;                             // vtable+0x18
	virtual void OnHitRacer(Racer* p_racer);                      // vtable+0x20

protected:
	void ComputeDropPosition(Racer* p_racer, GolVec3* p_position, GolBoundingVolume::HitTriangle* p_record);

	RaceState* m_raceState;                  // 0x018
	LegoEventQueue::Event* m_collisionEvent; // 0x01c
	TriggerWorld* m_collisionWorld;          // 0x020
	undefined4 m_unk0x024;                   // 0x024
	Racer* m_ownerRacer;                     // 0x028
};

#endif // HAZARDACTIONBASE_H
