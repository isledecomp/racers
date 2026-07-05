#ifndef HAZARDACTIONBASE_H
#define HAZARDACTIONBASE_H

#include "golboundingvolume.h"
#include "race/powerups/powerupaction.h"

// VTABLE: LEGORACERS 0x004b1630
// SIZE 0x2c
class HazardActionBase : public PowerupAction {
public:
	// Shared lifecycle terminal state (each action defines its full state set)
	enum {
		c_stateDone = 6,
	};

	HazardActionBase();

	// SYNTHETIC: LEGORACERS 0x00451960 FOLDED
	// WeaponActionBase::~WeaponActionBase

	// SYNTHETIC: LEGORACERS 0x00456300 FOLDED
	// HazardActionBase::`scalar deleting destructor'

	void OnEvent(LegoEventQueue::CallbackData* p_param) override; // vtable+0x00
	void Update(LegoU32) override = 0;                            // vtable+0x08
	void Draw(GolD3DRenderDevice*) override = 0;                  // vtable+0x0c
	void AdvanceState() override = 0;                             // vtable+0x14
	LegoS32 GetBrickColor() override;                             // vtable+0x18
	virtual void OnHitRacer(Racer* p_racer) = 0;                  // vtable+0x20

protected:
	void ComputeDropPosition(Racer* p_racer, GolVec3* p_position, GolBoundingVolume::HitTriangle* p_record);

	RaceState* m_raceState;                  // 0x018
	LegoEventQueue::Event* m_collisionEvent; // 0x01c
	TriggerWorld* m_collisionWorld;          // 0x020
	undefined4 m_unk0x024;                   // 0x024
	Racer* m_ownerRacer;                     // 0x028
};

#endif // HAZARDACTIONBASE_H
