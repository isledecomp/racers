#ifndef RACERPHYSICS_H
#define RACERPHYSICS_H

#include "race/racer/racercarbody.h"

class RacerSoundSource;

// Racer-facing physics: dispatches between the free rigid-body car
// simulation and recorded-route playback (AI/ghost cars), and applies
// the per-racer stat scales.
// VTABLE: LEGORACERS 0x004b04e4
// SIZE 0x888
class RacerPhysics : public RacerCarBody {
public:
	// Route-playback motion offsets relative to the path sample.
	// SIZE 0x10
	class RouteMotion {
	public:
		LegoFloat m_sink;         // 0x00
		LegoFloat m_jumpHeight;   // 0x04
		LegoFloat m_sideOffset;   // 0x08
		LegoFloat m_jumpVelocity; // 0x0c
	};

	RacerPhysics();

	void Update(LegoS32 p_elapsedMs) override; // vtable+0x04
	LegoU32 OnCollisionRecord(                                        // vtable+0x0c
		GolVec3* p_point,
		RaceEventRecord* p_record,
		GolBoundedEntity* p_world,
		GolBoundingVolume::HitTriangle* p_context
	) override;
	void UpdateWheelSurfaces() override;                                                // vtable+0x10
	void SetThrust(LegoFloat p_thrust) override;                                        // vtable+0x14
	void SetMaxSpeed(LegoFloat p_maxSpeed) override;                                    // vtable+0x18
	void ApplyImpulse(GolVec3* p_impulse, GolVec3* p_point) override;                   // vtable+0x1c
	void ApplyDirectionalImpulse(GolVec3* p_direction, LegoFloat p_magnitude) override; // vtable+0x20
	void StartSpin(LegoFloat p_turns, LegoFloat p_rate,
				   LegoFloat p_alignFraction) override;  // vtable+0x24
	void EndSpin() override;                             // vtable+0x2c
	void StartSliding() override;                        // vtable+0x30
	void StopSliding() override;                         // vtable+0x34
	void StartSpinOut() override;                        // vtable+0x38
	void EndSpinOut() override;                          // vtable+0x3c
	void StartExternalForce0(GolVec3* p_force) override; // vtable+0x40
	void EndExternalForce0() override;                   // vtable+0x44
	void StartExternalForce1(GolVec3* p_force) override; // vtable+0x48
	void EndExternalForce1() override;                   // vtable+0x4c
	virtual ~RacerPhysics();                             // vtable+0x50

	// SYNTHETIC: LEGORACERS 0x00429090
	// RacerPhysics::`scalar deleting destructor'

	void Reset();
	void Initialize(
		Racer* p_racer,
		RaceEventTable* p_eventTable,
		void* p_surfaceTable,
		GolAnimatedEntity* p_carEntity,
		GolBoundedEntity* p_trackWorld,
		GolBoundedEntity* p_triggerWorld,
		RacerSoundSource* p_soundSource,
		LegoFloat p_mass,
		LegoFloat p_sizeX,
		LegoFloat p_sizeY,
		LegoFloat p_sizeZ
	);
	void Destroy();
	void StartBoost();
	void EndBoost();
	void StartCurseSlow();
	void EndCurseSlow();
	void MoveBy(GolVec3* p_delta);
	void EndRoutePush();
	void StartRoutePush(GolVec3* p_force);
	void StartRouteGhost();
	void EndRouteGhost();
	void ApplyPitchImpulse(LegoFloat p_rate, LegoU32 p_durationMs);
	void UpdateRouteMotion(LegoU32 p_elapsedMs);
	void UpdateRouteSlideBank();
	void SaveRouteState();
	void UpdateRouteRotation(LegoU32 p_elapsedMs);
	void ApplyRoutePosition();
	void AttachRoute(RaceRouteRecord* p_record);
	void AttachRouteAtLoop(RaceRouteRecord* p_record);
	LegoBool32 IsMoving();
	void NotifySurfaceEnter(WheelProbe* p_probe, RaceEventRecord::Target* p_target);
	void NotifySurfaceLeave(WheelProbe* p_probe, RaceEventRecord::Target* p_target);
	void ApplyWheelSurface(WheelProbe* p_probe, RaceEventRecord::Target* p_target);
	void ResetWheelSurface(WheelProbe* p_probe);
	void SetHandlingStat(LegoS32 p_stat);
	void SetAccelerationStat(LegoS32 p_stat);
	void SetTopSpeedStat(LegoS32 p_stat);
	LegoFloat GetMinTurnRadius();
	LegoBool32 CanPowerslide();
	LegoBool32 CanSteer(LegoFloat p_turnRadius);
	SpatialSoundInstance* PlaySurfaceSound(LegoS32 p_soundId);
	void StopSurfaceSound();
	void ResetRouteMotion();
	LegoFloat ComputeMinTurnRadius();
	void SetTurnRadius(LegoFloat p_turnRadius);
	LegoFloat GetAverageLateralGrip();
	undefined4 StartPowerslide(undefined4 p_factorBits);
	undefined4 EndPowerslide();

	RouteCursorInstance m_routeCursor;      // 0x74c
	RouteMotion m_routeMotion;              // 0x7c4
	LegoFloat m_routeSpinRate;              // 0x7d4
	LegoFloat m_routeSpinAngle;             // 0x7d8
	LegoFloat m_routeTiltRate;              // 0x7dc
	LegoFloat m_routeTiltAngle;             // 0x7e0
	LegoFloat m_routeTiltHeight;            // 0x7e4
	LegoFloat m_routeBaseSpeed;             // 0x7e8
	LegoFloat m_routeTargetSpeed;           // 0x7ec
	RouteCursorInstance m_savedRouteCursor; // 0x7f0
	RouteMotion m_savedRouteMotion;         // 0x868
	LegoFloat m_savedRouteSpinRate;         // 0x878
	LegoFloat m_savedRouteSpinAngle;        // 0x87c
	undefined m_unk0x880[0x888 - 0x880];    // 0x880
};

#endif // RACERPHYSICS_H
