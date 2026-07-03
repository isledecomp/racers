#ifndef HOMINGPROJECTILE_H
#define HOMINGPROJECTILE_H

#include "race/powerups/powerupprojectile.h"

class Racer;

// VTABLE: LEGORACERS 0x004b0248
// SIZE 0xf8
class HomingProjectile : public PowerupProjectile {
public:
	HomingProjectile();
	PowerupProjectile* Destroy(undefined4 p_flags) override;
	LegoS32 Update(LegoU32 p_elapsedMs) override;
	void GetVelocity(GolVec3* p_velocity) override;
	void Destruct();
	void UpdateTargeting(
		LegoU32 p_elapsedMs,
		RaceState* p_raceState,
		LegoFloat p_minDistanceSquared,
		LegoFloat p_maxDistanceSquared,
		LegoFloat p_coneCosine
	);
	void StartHoming();
	void ApplySpiral(LegoFloat p_elapsedSeconds, GolVec3* p_direction, GolVec3* p_position);

protected:
	friend class HomingMissileAction;

	enum {
		c_invalidTargetMask = Racer::c_flagShielded | Racer::c_flagGhost,
		c_targetRefreshMs = 1000,
	};

	GolVec3 m_position;                  // 0x0a8
	LegoFloat m_spiralAmplitude;         // 0x0b4
	LegoFloat m_maxSpiralAmplitude;      // 0x0b8
	LegoFloat m_spiralAngle;             // 0x0bc
	LegoFloat m_spiralRate;              // 0x0c0
	GolVec3 m_velocity;                  // 0x0c4
	GolVec3 m_direction;                 // 0x0d0
	GolVec3 m_waypointPosition;          // 0x0dc
	LegoU32 m_hasWaypoint;               // 0x0e8
	CheckpointGraph::Entry* m_pathEntry; // 0x0ec
	LegoU32 m_retargetTimerMs;           // 0x0f0
	undefined4 m_unk0x0f4;               // 0x0f4
};

#endif // HOMINGPROJECTILE_H
