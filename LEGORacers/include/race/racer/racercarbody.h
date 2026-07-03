#ifndef RACERCARBODY_H
#define RACERCARBODY_H

#include "golboundedentity.h"
#include "golboundingvolume.h"
#include "golname.h"
#include "golstring.h"
#include "golworldentity.h"
#include "race/checkpointgraph.h"
#include "race/racer/racerboxbody.h"
#include "race/raceresourcemanager.h"
#include "util/legoeventqueue.h"

class GolCollidableEntity;
class GolWorldDatabase;
class RaceEventTable;
class RaceRouteRecord;
class RacerPhysics;
class RacerSoundSource;
class SpatialSoundInstance;

// Car dynamics on top of the box body: wheel ground probes, surface
// effects, steering/thrust forces, wall collision resolution, and the
// spin/slide/spin-out state machine.
// VTABLE: LEGORACERS 0x004b0d8c
// SIZE 0x74c
class RacerCarBody : public RacerBoxBody {
public:
	RacerCarBody();

	// SIZE 0x78
	class RouteCursor {
	public:
		void AttachAtLoop(RaceRouteRecord* p_record);
		void Attach(RaceRouteRecord* p_record);
		void Advance(LegoFloat p_elapsedMs);
		void SeekByDelta(GolVec3* p_delta);
		void Destroy();
		void Reset();

		GolVec3 m_position;         // 0x00
		GolQuat m_rotation;         // 0x0c
		LegoU32 m_pointType;        // 0x1c
		LegoFloat m_widthLeft;      // 0x20
		LegoFloat m_widthRight;     // 0x24
		RaceRouteRecord* m_record;  // 0x28
		LegoFloat m_playbackSpeed;  // 0x2c
		LegoFloat m_currentTime;    // 0x30
		LegoS32 m_startIndex;       // 0x34
		LegoS32 m_endIndex;         // 0x38
		GolVec3 m_startPosition;    // 0x3c
		GolVec3 m_endPosition;      // 0x48
		GolQuat m_startRotation;    // 0x54
		GolQuat m_endRotation;      // 0x64
		LegoS32 m_segmentStartTime; // 0x74
	};

	// SIZE 0x78
	class RouteCursorInstance : public RouteCursor {
	public:
		RouteCursorInstance();
		~RouteCursorInstance();
	};

	class CollisionCacheRecord;

	// Per-wheel ground probe: contact ray, hit surface record, and the
	// surface-driven handling parameters applied while on it.
	class WheelProbe {
	public:
		enum {
			c_flagContact = 1 << 0,
			c_flagHit = 1 << 1,
		};

		GolVec3 m_contactForce;               // 0x00
		GolVec3 m_wheelPosition;              // 0x0c
		GolVec3 m_rayStart;                   // 0x18
		GolVec3 m_rayEnd;                     // 0x24
		GolVec3 m_hitPoint;                   // 0x30
		RaceEventRecord* m_hitRecord;         // 0x3c
		RaceEventRecord* m_previousHitRecord; // 0x40
		CollisionCacheRecord* m_cachedPlane;  // 0x44
		LegoU32 m_flags;                      // 0x48
		LegoFloat m_hitDistanceSquared;       // 0x4c
		LegoFloat m_rollingResistance;        // 0x50
		LegoFloat m_supportThreshold;         // 0x54
		LegoFloat m_friction;                 // 0x58
		LegoFloat m_lateralGrip;              // 0x5c
		LegoFloat m_unk0x060;                 // 0x60
		GolVec3 m_surfaceForce;               // 0x64
	};

	// SIZE 0x3c
	class CollisionCacheRecord {
	public:
		GolBoundingVolume::HitTriangle m_plane; // 0x00
		LegoU32 m_age;                          // 0x34
		RaceEventRecord* m_record;              // 0x38
	};

	// SIZE 0x70
	class SavedWheelState {
	public:
		GolVec3 m_wheelPosition;             // 0x00
		undefined m_unk0x00c[0x030 - 0x00c]; // 0x0c
		RaceEventRecord* m_hitRecord;        // 0x30
		undefined m_unk0x034[0x03c - 0x034]; // 0x34
		LegoU32 m_flags;                     // 0x3c
		undefined4 m_unk0x040;               // 0x40
		LegoFloat m_rollingResistance;       // 0x44
		LegoFloat m_supportThreshold;        // 0x48
		LegoFloat m_friction;                // 0x4c
		LegoFloat m_lateralGrip;             // 0x50
		LegoFloat m_unk0x054;                // 0x54
		GolVec3 m_surfaceForce;              // 0x58
		undefined m_unk0x064[0x070 - 0x064]; // 0x64
	};

	// SIZE 0x1ec
	class SavedWheelStateBlock {
	public:
		SavedWheelState* GetEntries() { return m_entries; }
		GolBoundingVolume::HitTriangle* GetEventContext() { return &m_eventContext; }

		union {
			SavedWheelState m_entries[4]; // 0x000
			struct {
				undefined m_unk0x000[0x1b4 - 0x000];           // 0x000
				GolBoundingVolume::HitTriangle m_eventContext; // 0x1b4
				undefined m_unk0x1e8[0x1ec - 0x1e8];           // 0x1e8
			};
		};
	};

	// SIZE 0xf4
	class SavedState {
	public:
		GolVec3 m_bodyPointsWorld[4];     // 0x00
		GolVec3 m_facingDirection;        // 0x30
		undefined4 m_unk0x03c;            // 0x3c
		GolVec3 m_rayEndsLocal[4];        // 0x40
		GolVec3 m_rayStartsLocal[4];      // 0x70
		GolVec3 m_angularMomentum;        // 0xa0
		LegoFloat m_slideLift;            // 0xac
		LegoFloat m_slideBankAngle;       // 0xb0
		undefined4 m_unk0x0b4;            // 0xb4
		GolVec3 m_contactForce;           // 0xb8
		GolMatrix3 m_worldInverseInertia; // 0xc4
		GolVec3 m_angularVelocity;        // 0xe8
	};

	void Update(LegoS32 p_elapsedMs) override; // vtable+0x04
	GolOrientedEntity* GetEntity() override;   // vtable+0x08
	virtual LegoU32 OnCollisionRecord(                                // vtable+0x0c
		GolVec3* p_point,
		RaceEventRecord* p_record,
		GolBoundedEntity* p_world,
		GolBoundingVolume::HitTriangle* p_context
	) = 0;
	virtual void UpdateWheelSurfaces() = 0;                                            // vtable+0x10
	virtual void SetThrust(LegoFloat p_thrust);                                        // vtable+0x14
	virtual void SetMaxSpeed(LegoFloat p_maxSpeed);                                    // vtable+0x18
	virtual void ApplyImpulse(GolVec3* p_impulse, GolVec3* p_point);                   // vtable+0x1c
	virtual void ApplyDirectionalImpulse(GolVec3* p_direction, LegoFloat p_magnitude); // vtable+0x20
	virtual void StartSpin(LegoFloat p_turns, LegoFloat p_rate,
						   LegoFloat p_alignFraction);  // vtable+0x24
	virtual void FinishSpin();                          // vtable+0x28
	virtual void EndSpin();                             // vtable+0x2c
	virtual void StartSliding();                        // vtable+0x30
	virtual void StopSliding();                         // vtable+0x34
	virtual void StartSpinOut();                        // vtable+0x38
	virtual void EndSpinOut();                          // vtable+0x3c
	virtual void StartExternalForce0(GolVec3* p_force); // vtable+0x40
	virtual void EndExternalForce0();                   // vtable+0x44
	virtual void StartExternalForce1(GolVec3* p_force); // vtable+0x48
	virtual void EndExternalForce1();                   // vtable+0x4c

	void Reset();
	void Initialize(
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
	void AddForce(GolVec3* p_force);
	void AddForceAtPoint(GolVec3* p_force, GolVec3* p_point);
	void AddAngularImpulse(GolVec3* p_impulse);
	void CancelAngularMomentum(GolVec3* p_direction, GolVec3* p_point);
	void CancelAngularMomentumAlong(GolVec3* p_axis);
	void SetCenterOfMass(GolVec3* p_centerOfMass);
	void UpdateVisualBank(LegoS32 p_elapsedMs);
	void AccumulateForces();
	void ApplyPitchImpulse(LegoFloat p_rate, LegoU32 p_durationMs);
	void ApplyYawImpulse(LegoFloat p_rate, LegoU32 p_durationMs);
	void LimitUprightTilt();
	void UpdateWheelContacts(LegoS32 p_elapsedMs);
	void UpdateSlideBank(LegoS32 p_elapsedMs);
	void UpdateSlideContacts(LegoU32 p_elapsedMs);
	void SetWheelGeometry(GolVec3* p_anchorWheel, LegoFloat p_trackWidth, LegoFloat p_wheelbase);
	void SetBodyPoint(LegoU32 p_index, GolVec3* p_point);
	void SnapFacingDirection();
	void UpdateFacingDirection(LegoU32 p_elapsedMs);
	void RotateFacingToward(LegoS32 p_elapsedMs, GolVec3* p_target);
	void UpdateVelocityStats();
	void SaveState();
	void RestoreState();
	void ClearWallContacts();
	LegoU32 ResolveWallCollisions(LegoU32 p_elapsedMs, LegoBool32 p_queryTrack);
	void ApplyWallResponse();
	void StartSteering(LegoFloat p_gain, LegoFloat p_slipRatio, LegoFloat p_maxAngle);
	void StopSteering();
	void UpdateDragCoefficient();
	void SnapToContacts(WheelProbe* p_probe);
	void ComputeSlideBankTarget();
	LegoU32 AddCollisionWorld(GolBoundedEntity* p_world);
	void RemoveCollisionWorld(GolBoundedEntity* p_world);
	LegoFloat GetAverageSupportThreshold();
	LegoFloat GetAverageFriction();
	void AgePlaneCache();
	CollisionCacheRecord* CachePlane(GolBoundingVolume::HitTriangle* p_plane, RaceEventRecord* p_record);
	LegoBool32 TestCachedPlanes(WheelProbe* p_probe);
	static LegoBool32 TestCachedPlane(WheelProbe* p_probe, CollisionCacheRecord* p_record);
	void ComputeWheelPositions();
	void ComputeWheelRaysLocal(GolBoundedEntity* p_world, LegoFloat p_sweepHeight, LegoFloat p_sweepDistance);
	void MoveBy(GolVec3* p_delta);

	enum {
		c_collisionWorldCount = 5,
		c_collisionCacheRecordCount = 8,
		c_soundSkid = 0x3a,
		c_soundSpin = 0x3c,
	};

	enum {
		c_flagSteering = 1 << 0,
		c_flagSpinning = 1 << 1,
		c_flagSpinFresh = 1 << 2,
		c_flagSliding = 1 << 3,
		c_flagExternalForce0 = 1 << 5,
		c_flagExternalForce1 = 1 << 6,
		c_flagSpinOut = 1 << 7,
		c_flagAtRest = 1 << 8,
		c_flagBit9 = 1 << 9,
		c_flagPowerslide = 1 << 10,
		c_flagYawImpulse = 1 << 11,
		c_flagNoTrackCollision = 1 << 12,
		c_flagBoost = 1 << 16,
		c_flagRouteGhost = 1 << 17,
		c_flagRoutePushed = 1 << 18,
		c_flagCurseSlow = 1 << 19,
		c_flagIgnoreSurfaces = 1 << 20,
	};

	GolOrientedEntity m_physicsEntity;                              // 0x0e4
	GolOrientedEntity* m_carEntity;                                 // 0x13c
	GolBoundedEntity* m_collisionWorlds[c_collisionWorldCount];     // 0x140
	LegoU32 m_collisionWorldCount;                                  // 0x154
	RacerSoundSource* m_soundSource;                                // 0x158
	LegoFloat m_massScale;                                          // 0x15c
	LegoFloat m_gravity;                                            // 0x160
	LegoFloat m_gravityForce;                                       // 0x164
	GolVec3 m_facingDirection;                                      // 0x168
	GolVec3 m_supportNormal;                                        // 0x174
	GolVec3 m_supportForce;                                         // 0x180
	LegoFloat m_contactOffsetX;                                     // 0x18c
	LegoFloat m_contactOffsetY;                                     // 0x190
	LegoFloat m_rideHeight;                                         // 0x194
	WheelProbe m_wheelProbes[4];                                    // 0x198
	GolVec3 m_anchorWheelOffset;                                    // 0x358
	LegoFloat m_trackWidth;                                         // 0x364
	LegoFloat m_wheelbase;                                          // 0x368
	LegoU32 m_contactCount;                                         // 0x36c
	GolVec3 m_bodyPointsLocal[4];                                   // 0x370
	GolVec3 m_bodyPointsWorld[4];                                   // 0x3a0
	undefined4 m_bodyPointHit[4];                                   // 0x3d0
	GolVec3 m_wallNormal;                                           // 0x3e0
	LegoU32 m_wallContact;                                          // 0x3ec
	LegoU32 m_stepRemainderMs;                                      // 0x3f0
	CollisionCacheRecord m_planeCache[c_collisionCacheRecordCount]; // 0x3f4
	LegoU32 m_planeCacheCount;                                      // 0x5d4
	LegoU32 m_rollImpulseMs;                                        // 0x5d8
	LegoU32 m_pitchImpulseMs;                                       // 0x5dc
	LegoU32 m_yawImpulseMs;                                         // 0x5e0
	LegoU32 m_spinStopAtMs;                                         // 0x5e4
	LegoU32 m_spinPeriodMs;                                         // 0x5e8
	LegoFloat m_dragCoefficient;                                    // 0x5ec
	undefined4 m_unk0x5f0;                                          // 0x5f0
	LegoFloat m_gripScale;                                          // 0x5f4
	GolVec3 m_velocityDirection;                                    // 0x5f8
	LegoFloat m_speed;                                              // 0x604
	LegoFloat m_maxSpeed;                                           // 0x608
	GolVec3 m_forwardVelocity;                                      // 0x60c
	LegoFloat m_forwardSpeed;                                       // 0x618
	GolVec3 m_lateralVelocity;                                      // 0x61c
	LegoFloat m_thrust;                                             // 0x628
	undefined4 m_unk0x62c;                                          // 0x62c
	GolVec3 m_externalForce0;                                       // 0x630
	GolVec3 m_externalForce1;                                       // 0x63c
	LegoFloat m_centripetalForce;                                   // 0x648
	LegoFloat m_turnRadius;                                         // 0x64c
	LegoFloat m_yawRate;                                            // 0x650
	LegoFloat m_unk0x654;                                           // 0x654
	LegoFloat m_slideLift;                                          // 0x658
	LegoFloat m_slideLiftTarget;                                    // 0x65c
	LegoFloat m_slideLiftRate;                                      // 0x660
	GolVec3 m_frontAxleMid;                                         // 0x664
	GolVec3 m_rearAxleMid;                                          // 0x670
	LegoFloat m_slideBankTarget;                                    // 0x67c
	LegoFloat m_slideBankAngle;                                     // 0x680
	GolVec3 m_savedVelocity;                                        // 0x684
	GolVec3 m_savedPosition;                                        // 0x690
	GolMatrix3 m_savedOrientation;                                  // 0x69c
	LegoU32 m_flags;                                                // 0x6c0
	LegoFloat m_steeringGain;                                       // 0x6c4
	LegoFloat m_steeringAlignmentMin;                               // 0x6c8
	LegoFloat m_facingLagMax;                                       // 0x6cc
	LegoFloat m_slipRatio;                                          // 0x6d0
	LegoFloat m_visualBankAngle;                                    // 0x6d4
	union {
		LegoU32 m_powerslideFactorBits; // 0x6d8
		LegoFloat m_powerslideFactor;   // 0x6d8
	};
	LegoU32 m_airborneMs;                  // 0x6dc
	LegoU32 m_spinOutMs;                   // 0x6e0
	SpatialSoundInstance* m_spinSound;     // 0x6e4
	SpatialSoundInstance* m_skidSound;     // 0x6e8
	LegoU32 m_soundsEnabled;               // 0x6ec
	Racer* m_ownerRacer;                   // 0x6f0
	RaceEventTable* m_eventTable;          // 0x6f4
	void* m_surfaceTable;                  // 0x6f8
	GolBoundedEntity* m_triggerCollidable; // 0x6fc
	GolVec3 m_resetPosition;               // 0x700
	GolQuat m_resetRotation;               // 0x70c
	LegoS32 m_handlingStat;                // 0x71c
	LegoS32 m_accelerationStat;            // 0x720
	LegoS32 m_topSpeedStat;                // 0x724
	LegoFloat m_handlingScale;             // 0x728
	LegoFloat m_accelerationScale;         // 0x72c
	LegoFloat m_topSpeedScale;             // 0x730
	LegoFloat m_maxSpeedSetting;           // 0x734
	LegoU32 m_surfaceSoundMs;              // 0x738
	LegoS32 m_surfaceSoundId;              // 0x73c
	SpatialSoundInstance* m_surfaceSound;  // 0x740
	LegoU32 m_routeMode;                   // 0x744
	LegoU32 m_routePaused;                 // 0x748
};

#endif // RACERCARBODY_H
