#ifndef POWERUPPROJECTILE_H
#define POWERUPPROJECTILE_H

#include "decomp.h"
#include "golmath.h"
#include "race/racestate.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolWorldEntity;
class TriggerWorld;

// VTABLE: LEGORACERS 0x004b0778
// SIZE 0xa8
class PowerupProjectile : public LegoEventQueue::Callback {
public:
	enum {
		c_stateIdle = 0,
		c_stateFlying = 1,
		c_stateHitRacer = 2,
		c_stateHitWorld = 3,
		c_stateExpired = 4,
	};

	// SIZE 0x28
	class Params {
	public:
		GolWorldEntity* m_worldEntity;  // 0x00
		TriggerWorld* m_collisionWorld; // 0x04
		LegoFloat m_gravity;            // 0x08
		LegoEventQueue* m_eventQueue;   // 0x0c
		GolVec3 m_targetOffset;         // 0x10
		LegoFloat m_speed;              // 0x1c
		LegoU32 m_lifetimeMs;           // 0x20
		LegoFloat m_launchHeight;       // 0x24
	};

	PowerupProjectile();
	~PowerupProjectile();
	void OnEvent(LegoEventQueue::CallbackData* p_data) override;          // vtable+0x00
	virtual void LaunchAtPosition(Params* p_params, GolVec3* p_position); // vtable+0x04
	virtual void LaunchAtPoint(                                      // vtable+0x08
		Params* p_params,
		Racer* p_racer,
		GolVec3* p_targetPosition,
		GolVec3* p_targetVelocity,
		LegoBool32 p_fromRacerPosition
	);
	virtual void LaunchAtRacer(                                            // vtable+0x0c
		Params* p_params,
		Racer* p_racer,
		Racer* p_targetRacer,
		LegoBool32 p_fromRacerPosition,
		LegoBool32 p_predictiveLead
	);
	virtual PowerupProjectile* Destroy(undefined4 p_flags); // vtable+0x10
	virtual void Deactivate();                              // vtable+0x14
	virtual LegoS32 Update(LegoU32 p_elapsedMs);            // vtable+0x18
	virtual void GetVelocity(GolVec3* p_velocity);          // vtable+0x1c

	void Reset();
	void CancelCollisionEvent();
	void Initialize(Params* p_params);
	void Deflect(Racer* p_racer);
	void ComputeTrajectory(LegoFloat p_durationSeconds);
	void RegisterCollisionEvent(LegoEventQueue* p_eventQueue);
	LegoU32 GetState() const { return m_state; }
	GolWorldEntity* GetWorldEntity() { return m_worldEntity; }
	const GolVec3& GetTargetPosition() const { return m_targetPosition; }
	const GolVec3& GetHitPosition() const { return m_hitPosition; }
	const GolVec3& GetHitNormal() const { return m_hitNormal; }
	Racer* GetHitRacer() const { return m_hitRacer; }

protected:
	undefined4 m_state;                      // 0x004
	GolWorldEntity* m_worldEntity;           // 0x008
	TriggerWorld* m_collisionWorld;          // 0x00c
	GolVec3 m_startPosition;                 // 0x010
	GolVec3 m_targetPosition;                // 0x01c
	GolVec3 m_hitPosition;                   // 0x028
	LegoFloat m_velocityX;                   // 0x034
	LegoFloat m_velocityY;                   // 0x038
	LegoFloat m_velocityZ;                   // 0x03c
	LegoFloat m_gravity;                     // 0x040
	LegoEventQueue::Event* m_collisionEvent; // 0x044
	LegoFloat m_launchHeight;                // 0x048
	LegoFloat m_speed;                       // 0x04c
	LegoS32 m_ageMs;                         // 0x050
	LegoU32 m_flightTimeMs;                  // 0x054
	LegoU32 m_lifetimeMs;                    // 0x058
	GolVec3 m_hitNormal;                     // 0x05c
	undefined m_unk0x068[0x09c - 0x068];     // 0x068
	Racer* m_ownerRacer;                     // 0x09c
	Racer* m_targetRacer;                    // 0x0a0
	Racer* m_hitRacer;                       // 0x0a4
};

#endif // POWERUPPROJECTILE_H
