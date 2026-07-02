#ifndef DRIVECONTROLLER_H
#define DRIVECONTROLLER_H

#include "golmath.h"
#include "race/racer/racerphysics.h"
#include "types.h"

class Racer;

// Steering/throttle layer between racer control input (or the AI
// return-to-path autopilot) and the physics turn radius/thrust.
// SIZE 0x54
class DriveController {
public:
	enum {
		c_flagTurbo = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagSliding = 1 << 2,
		c_flagSlideBoost = 1 << 3,
		c_flagCursed = 1 << 4,
		c_flagReversing = 1 << 5,
		c_flagReturnToPath = 1 << 6,
		c_flagBrakeToStop = 1 << 7,
		c_flagTurboWeakened = 1 << 8,
	};

	void Initialize(RacerPhysics* p_physics);
	void Update(LegoU32 p_elapsedMs);
	void UpdateBrakeToStop(LegoU32 p_elapsedMs);
	void UpdateStuckDetection(LegoU32 p_elapsedMs);
	void SetSteeringInput(LegoFloat p_input);
	void ApplySteering();
	void SetThrottleInput(LegoFloat p_input);
	void ApplyThrust();
	void EngageSlide(LegoBool32 p_left);
	undefined4 ReleaseSlide();
	GolQuat* StartReturnToPath(RaceRouteRecord* p_record);
	void EndReturnToPath();
	void UpdateReturnToPath(LegoU32 p_elapsedMs);
	DriveController();
	void Destroy();
	void Reset();
	~DriveController();

	RacerPhysics* m_physics;                            // 0x00
	RaceRouteRecord* m_returnRecord;                    // 0x04
	LegoFloat m_previousTurnRadius;                     // 0x08
	LegoFloat m_turnRadius;                             // 0x0c
	LegoFloat m_thrust;                                 // 0x10
	LegoU32 m_flags;                                    // 0x14
	LegoFloat m_curseSteerOffset;                       // 0x18
	LegoFloat m_curseThrottleOffset;                    // 0x1c
	LegoU32 m_curseJitterMs;                            // 0x20
	LegoS32 m_returnPreviewMs;                          // 0x24
	LegoU32 m_stuckMs;                                  // 0x28
	LegoU32 m_slideMs;                                  // 0x2c
	LegoU32 m_slideLeft;                                // 0x30
	GolVec3 m_returnPosition;                           // 0x34
	GolQuat m_returnRotation;                           // 0x40
	RacerPhysics::RouteCursorInstance* m_previewCursor; // 0x50
};

#endif // DRIVECONTROLLER_H
