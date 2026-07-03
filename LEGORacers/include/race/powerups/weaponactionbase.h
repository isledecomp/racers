#ifndef WEAPONACTIONBASE_H
#define WEAPONACTIONBASE_H

#include "race/powerups/powerupaction.h"

// SIZE 0x30
class WeaponActionBase : public PowerupAction {
public:
	WeaponActionBase();
	void AdvanceState() override;                            // vtable+0x14
	LegoS32 GetBrickColor() override;                        // vtable+0x18
	virtual void OnHitRacer(Racer* p_racer);                 // vtable+0x20
	virtual void GetProjectilePosition(GolVec3* p_position); // vtable+0x24
	virtual void GetProjectileVelocity(GolVec3* p_velocity); // vtable+0x28

	GolWorldEntity* GetProjectileWorldEntity();

protected:
	PowerupProjectile* m_activeProjectile; // 0x018
	RacePowerupManager* m_owner;           // 0x01c
	TriggerWorld* m_collisionWorld;        // 0x020
	Racer* m_ownerRacer;                   // 0x024
	Racer* m_targetRacer;                  // 0x028
	TargetPointList::Entry* m_targetPoint; // 0x02c
};

#endif // WEAPONACTIONBASE_H
