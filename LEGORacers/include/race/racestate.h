#ifndef RACESTATE_H
#define RACESTATE_H

#include "app/legoracers.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golboundedentity.h"
#include "golboundingvolume.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golorientedentity.h"
#include "golstring.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "golworldentitygroup0x38.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "material/materialtable0x0c.h"
#include "race/checkpointgraph.h"
#include "race/data/championdefinitionlist.h"
#include "race/raceactionsource.h"
#include "race/racedecalmanager.h"
#include "race/raceeventrecord.h"
#include "race/raceresourcemanager.h"
#include "race/triggerworld.h"
#include "racer/chassismodeltable.h"
#include "racer/drivercosmetictable.h"
#include "scene/golbillboard.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolCamera;
class GolD3DRenderDevice;
class GolExport;
class GolFileParser;
class GolMaterialLibrary;
class GolRenderDevice;
class GolTextureList;
class GolWorldDatabase;
class GolBoundedEntity;
class GolCollidableEntity;
class GolAnimatedEntity;
class MabMaterialAnimationItem0x8;
class DuskwindBananaRelic0x24;
class CutsceneAnimation;
class RaceHud;
class RaceCameraController;
class RaceEventTable;
class TriggerWorld;
class RaceForceFeedback;
class RacePowerupManager;
class RaceRouteRecord;
class TimeRaceManager;
class SoundGroup;
class SoundManager;
class SpatialSoundInstance;
struct CutsceneParticleRef;
struct SoundVector;

// SIZE 0x320
class RaceState {
	class RacerContext;

public:
	// VTABLE: LEGORACERS 0x004b0a2c
	// SIZE 0x1fc
	class SpbTxtParser : public GolTxtParser {
	public:
		// .spb token meanings
		enum {
			e_startPosition = 0x27,
			e_position = 0x28,
			e_orientation = 0x29,
		};
	};

	// VTABLE: LEGORACERS 0x004b09b0
	// SIZE 0xe34
	class Racer : public LegoEventQueue::Callback {
	public:
		Racer();
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual ~Racer();                                               // vtable+0x04

		// SYNTHETIC: LEGORACERS 0x0043b420
		// RaceState::Racer::`vector deleting destructor'

		class Physics;

		// Combined racer setup record: driver identity/stats plus the vehicle
		// physics description consumed by InitializePhysics.
		// SIZE 0x88
		class SetupParams {
		public:
			LegoChar m_displayName[0x18];     // 0x00
			undefined2* m_displayNameWide;    // 0x18
			undefined m_unk0x1c[0x28 - 0x1c]; // 0x1c
			GolVec3 m_anchorWheelPosition;    // 0x28
			undefined m_unk0x34[0x38 - 0x34]; // 0x34
			LegoFloat m_rearWheelY0;          // 0x38
			undefined m_unk0x3c[0x40 - 0x3c]; // 0x3c
			LegoFloat m_rearWheelX;           // 0x40
			LegoFloat m_rearWheelY1;          // 0x44
			undefined m_unk0x48[0x4c - 0x48]; // 0x48
			GolVec3 m_centerOfMass;           // 0x4c
			LegoFloat m_mass;                 // 0x58
			LegoFloat m_weight;               // 0x5c
			RaceEventTable* m_eventTable;     // 0x60
			void* m_unk0x64;                  // 0x64
			GolBoundedEntity* m_trackWorld;   // 0x68
			LegoU8 m_driverStats[6];          // 0x6c
			LegoU8 m_lapCount;                // 0x72
			undefined m_unk0x73[0x74 - 0x73]; // 0x73
			LegoU32 m_voiceBank;              // 0x74
			LegoFloat m_enginePitchScale;     // 0x78
			LegoU32 m_aiChargeColor;          // 0x7c
			LegoU32 m_aiChargeTarget;         // 0x80
			LegoU8 m_handlingStat;            // 0x84
			LegoU8 m_accelerationStat;        // 0x85
			LegoU8 m_topSpeedStat;            // 0x86
			undefined m_unk0x87[0x88 - 0x87]; // 0x87
		};

		// SIZE 0x14
		class SoundSource : public RaceResourceManager {
		public:
			void PlaySoundById(LegoU32 p_soundId);
			void PlaySpatialSoundById(
				LegoU32 p_soundId,
				SoundVector* p_position,
				LegoFloat p_minDistance,
				LegoFloat p_maxDistance,
				LegoFloat p_volume,
				LegoFloat p_frequencyScale
			);
			SpatialSoundInstance* AcquireSoundById(LegoU32 p_soundId);

		private:
			LegoU32 ResolveSoundId(LegoU32 p_unk0x04, SoundGroup** p_soundGroup);

		protected:
			SoundGroup* m_groups[4]; // 0x04
		};

		// SIZE 0x0c
		class StandingsDeltaEntry {
		public:
			Racer* m_racer;    // 0x00
			LegoS32 m_delta;   // 0x04
			LegoU32 m_isValid; // 0x08
		};

		// SIZE 0x3d0
		class CarVisuals {
		public:
			// SIZE 0x68
			class InitParams {
			public:
				GolModelEntity* m_bodyModel;         // 0x00
				GolAnimatedEntity* m_secondaryModel; // 0x04
				GolAnimatedEntity* m_carEntity;      // 0x08
				GolAnimatedEntity* m_driverEntity;   // 0x0c
				GolVec3 m_driverMountOffset;         // 0x10
				Racer* m_racer;                      // 0x1c
				LegoFloat m_shadowWidth;             // 0x20
				LegoFloat m_shadowLength;            // 0x24
				LegoFloat m_frontSkidWidth;          // 0x28
				LegoFloat m_rearSkidWidth;           // 0x2c
				GolName m_materialName;              // 0x30
				GolVec3 m_wheelOffsets[4];           // 0x38
			};

			enum {
				c_flagVisible = 1 << 1,
				c_flagShadowEnabled = 1 << 2,
				c_flagSkidding = 1 << 3,
				c_flagShadowVisible = 1 << 4,
				c_flagSliding = 1 << 8,
				c_flagAirborne = 1 << 9,
				c_flagVisible0 = 1 << 10,
				c_flagVisible1 = 1 << 11,
				c_flagVisible2 = 1 << 12,
				c_alphaOverrideFlag = 1,
				c_fadeAlphaMax = 0xbf,
				c_randomTableMask = 0x3ff,
				c_animationPart0 = 0,
				c_animationPart1 = 1,
				c_animationPart2 = 2,
				c_animationPart3 = 3,
				c_animationPart4 = 4,
				c_animationPart5 = 5,
				c_animationPart6 = 6,
				c_animationPart7 = 7,
				c_animationPart8 = 8,
				c_animationPart9 = 9,
				c_animationPart10 = 10,
				c_animationPart11 = 11,
				c_animationPart12 = 12,
				c_animationPart13 = 13,
				c_animationPart14 = 14,
				c_animationPart15 = 15,
				c_animationPart16 = 16,
				c_animationPart17 = 17,
				c_animationTransitionMs = 300,
				c_avoidanceCooldownBaseMs = 5000,
				c_avoidanceCooldownRangeMs = 1000,
				c_flags0x384Bit0 = 1 << 0,
				c_flags0x384Bit1 = 1 << 1,
				c_wheelSkidActive = 1 << 0,
				c_wheelSkidGrounded = 1 << 1,
				c_wheelSkidFading = 1 << 2,
				c_wheelSkidAllButActive = 0xfe,
			};

			CarVisuals();
			void Reset();
			void Initialize(InitParams* p_params, RacerContext* p_context);
			void InitializeVisuals(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
			void RefreshCarMaterial();
			void UseTurboSkidMaterial();
			void UseNormalSkidMaterial();
			void Destroy();
			void ShowModels();
			void HideModels();
			void StartSkidEffects();
			void StopSkidEffects();
			void SetWheelParticle(LegoU32 p_unk0x04, const LegoChar* p_unk0x08);
			void ClearWheelParticle(LegoU32 p_unk0x04);
			void StartDust();
			void StartCarSmoke();
			void Update(LegoU32 p_elapsedMs);
			void SnapVisuals();
			void UpdateBodyLean(LegoS32 p_elapsedMs);
			void UpdateDriver(LegoU32 p_elapsedMs);
			void UpdateSkidMarks(LegoU32 p_elapsedMs);
			void UpdateCurseEntity(LegoU32 p_elapsedMs);
			void UpdateShadow(GolCamera* p_camera);
			void Draw(GolD3DRenderDevice* p_renderer);
			void DrawTransparent(GolD3DRenderDevice* p_renderer);
			void StartTurboEffects();
			void StopTurboEffects();
			void StartSlideSkid();
			void StopSlideSkid();
			LegoBool32 IntersectSegment(const GolVec3* p_start, const GolVec3* p_end, GolVec3* p_hit);
			void RenderImpostor(GolD3DRenderDevice* p_renderer);
			void RebuildEntityGroup();
			void SetColorTransform(ColorTransform0x20* p_unk0x04);
			void ClearColorTransform();
			void FlashColor(ColorTransform0x20* p_unk0x04, undefined4 p_unk0x08);
			void EndFlash();
			void SetScale(LegoFloat p_unk0x04);
			void ResetDriverAnimation();
			void PlayForwardAnimation();
			void PlayReverseAnimation();
			~CarVisuals();

			GolAnimatedEntity* GetCarEntity() const { return m_carEntity; }
			void SetReactionFlags(LegoU32 p_flags) { m_reactionFlags |= p_flags; }

			LegoU32 m_flags;                               // 0x000
			GolWorldEntityGroup0x38 m_entityGroup;         // 0x004
			GolModelEntity* m_bodyModelEntity;             // 0x03c
			GolAnimatedEntity* m_secondaryEntity;          // 0x040
			GolAnimatedEntity* m_carEntity;                // 0x044
			GolAnimatedEntity* m_driverEntity;             // 0x048
			GolVec3 m_driverMountOffset;                   // 0x04c
			GolVec3 m_shadowDirection;                     // 0x058
			GolCollidableEntity* m_trackCollidable;        // 0x064
			LegoFloat m_modelDistances[3];                 // 0x068
			GolName m_shadowTextureName;                   // 0x074
			RaceDecalManager::Trail::Decal m_shadowDecal;  // 0x07c
			LegoFloat m_shadowWidth;                       // 0x198
			LegoFloat m_shadowLength;                      // 0x19c
			LegoFloat m_frontSkidWidth;                    // 0x1a0
			LegoFloat m_rearSkidWidth;                     // 0x1a4
			GolVec3 m_wheelOffsets[4];                     // 0x1a8
			Racer* m_racer;                                // 0x1d8
			Physics* m_racerPhysics;                       // 0x1dc
			RaceDecalManager* m_skidMarkManager;           // 0x1e0
			RaceDecalManager::Trail* m_skidMarks[4];       // 0x1e4
			LegoU8 m_wheelSkidFlags[4];                    // 0x1f4
			LegoU32 m_wheelAirTimers[4];                   // 0x1f8
			undefined4 m_skidFadeTimers[4];                // 0x208
			GolBillboard::Field0x2c m_shadowMaterialTable; // 0x218
			GolBillboard::Field0x2c m_skidMaterialTable;   // 0x224
			CutsceneParticleRef* m_wheelParticles[4];      // 0x230
			GolName m_wheelParticleNames[4];               // 0x240
			LegoU32 m_wheelParticleFromRace[4];            // 0x260
			CutsceneParticleRef* m_dustParticle;           // 0x270
			CutsceneParticleRef* m_tireSmokeParticle;      // 0x274
			CutsceneParticleRef* m_carSmokeParticle;       // 0x278
			CutsceneAnimation* m_particleAnimation;        // 0x27c
			CutsceneAnimation* m_sharedParticleAnimation;  // 0x280
			GolAnimatedEntity m_curseEntity;               // 0x284
			LegoU32 m_cursePhaseMs;                        // 0x378
			LegoU32 m_curseBlendMs;                        // 0x37c
			Racer* m_nearbyRacer;                          // 0x380
			LegoU32 m_reactionFlags;                       // 0x384
			LegoU32 m_lookCooldownMs;                      // 0x388
			LegoFloat m_lastSpeed;                         // 0x38c
			undefined4 m_unk0x390;                         // 0x390
			undefined4 m_unk0x394;                         // 0x394
			LegoFloat m_pitchLean;                         // 0x398
			LegoFloat m_rollLean;                          // 0x39c
			ColorTransform0x20 m_baseColorTransform;       // 0x3a0
			LegoU32 m_hasColorTransform;                   // 0x3c0
			LegoU32 m_isFlashing;                          // 0x3c4
			undefined4 m_flashTimerMs;                     // 0x3c8
			LegoU32 m_lastGroundedWheelCount;              // 0x3cc
		};

		// Rigid-body integrator core: force/torque accumulators, inertia
		// tensors, and the per-step position/orientation integration.
		// VTABLE: LEGORACERS 0x004b0b78
		// SIZE 0xd0
		class RigidBody {
		public:
			RigidBody();
			virtual void ComputeInertiaTensor() = 0;  // vtable+0x00
			virtual void Update(LegoS32 p_elapsedMs); // vtable+0x04
			virtual GolOrientedEntity* GetEntity();   // vtable+0x08

			void Reset();
			void Initialize(GolOrientedEntity* p_body, LegoFloat p_mass);
			void Destroy();
			void UpdateWorldInverseInertia();
			void UpdateAngularVelocity();

			GolOrientedEntity* m_body;         // 0x004
			GolVec3 m_velocity;                // 0x008
			GolVec3 m_centerOfMassLocal;       // 0x014
			GolVec3 m_centerOfMassWorld;       // 0x020
			GolMatrix3 m_inertiaTensor;        // 0x02c
			GolMatrix3 m_inverseInertiaTensor; // 0x050
			GolMatrix3 m_worldInverseInertia;  // 0x074
			GolVec3 m_angularVelocity;         // 0x098
			GolVec3 m_angularMomentum;         // 0x0a4
			GolVec3 m_force;                   // 0x0b0
			GolVec3 m_torque;                  // 0x0bc
			LegoFloat m_mass;                  // 0x0c8
			LegoFloat m_inverseMass;           // 0x0cc
		};

		// Box-shaped rigid body: inertia tensor from box dimensions.
		// VTABLE: LEGORACERS 0x004b0b84
		// SIZE 0xe4
		class BoxBody : public RigidBody {
		public:
			BoxBody();
			void ComputeInertiaTensor() override; // vtable+0x00
			void Initialize(
				GolOrientedEntity* p_body,
				LegoFloat p_mass,
				LegoFloat p_sizeX,
				LegoFloat p_sizeY,
				LegoFloat p_sizeZ
			);

			LegoFloat m_sizeX;          // 0x0d0
			LegoFloat m_sizeY;          // 0x0d4
			LegoFloat m_sizeZ;          // 0x0d8
			LegoFloat m_speedRampScale; // 0x0dc
			Racer* m_racer;             // 0x0e0
		};

		// Car dynamics on top of the box body: wheel ground probes, surface
		// effects, steering/thrust forces, wall collision resolution, and the
		// spin/slide/spin-out state machine.
		// VTABLE: LEGORACERS 0x004b0d8c
		// SIZE 0x74c
		class CarBody : public BoxBody {
		public:
			CarBody();

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
				GolBoundingVolume::Field0x0c m_plane; // 0x00
				LegoU32 m_age;                        // 0x34
				RaceEventRecord* m_record;            // 0x38
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
				GolBoundingVolume::Field0x0c* GetEventContext() { return &m_eventContext; }

				union {
					struct {
						SavedWheelState m_entries[4];        // 0x000
						undefined m_unk0x1c0[0x1ec - 0x1c0]; // 0x1c0
					};
					struct {
						undefined m_unk0x000[0x1b4 - 0x000];         // 0x000
						GolBoundingVolume::Field0x0c m_eventContext; // 0x1b4
						undefined m_unk0x1e8[0x1ec - 0x1e8];         // 0x1e8
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
				GolBoundingVolume::Field0x0c* p_context
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
				SoundSource* p_soundSource,
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
			CollisionCacheRecord* CachePlane(GolBoundingVolume::Field0x0c* p_plane, RaceEventRecord* p_record);
			LegoBool32 TestCachedPlanes(WheelProbe* p_probe);
			static LegoBool32 TestCachedPlane(WheelProbe* p_probe, CollisionCacheRecord* p_record);
			void ComputeWheelPositions();
			void ComputeWheelRaysLocal(GolBoundedEntity* p_world, LegoFloat p_sweepHeight, LegoFloat p_sweepDistance);
			void MoveBy(GolVec3* p_delta);

			enum {
				c_collisionWorldCount = 5,
				c_collisionCacheRecordCount = 8,
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
			SoundSource* m_soundSource;                                     // 0x158
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
			LegoU32 m_airborneMs; // 0x6dc
			LegoU32 m_spinOutMs;  // 0x6e0
			union {
				RaceResourceManager::Resource* m_spinSoundResource; // 0x6e4
				SpatialSoundInstance* m_spinSound;                  // 0x6e4
			};
			union {
				RaceResourceManager::Resource* m_skidSoundResource; // 0x6e8
				SpatialSoundInstance* m_skidSound;                  // 0x6e8
			};
			LegoU32 m_soundsEnabled;               // 0x6ec
			Racer* m_ownerRacer;                   // 0x6f0
			RaceEventTable* m_eventTable;          // 0x6f4
			void* m_unk0x6f8;                      // 0x6f8
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
			undefined4 m_surfaceSoundMs;           // 0x738
			LegoS32 m_surfaceSoundId;              // 0x73c
			union {
				SpatialSoundInstance* m_surfaceSound;                  // 0x740
				RaceResourceManager::Resource* m_surfaceSoundResource; // 0x740
			};
			LegoU32 m_routeMode;   // 0x744
			LegoU32 m_routePaused; // 0x748
		};

		// Racer-facing physics: dispatches between the free rigid-body car
		// simulation and recorded-route playback (AI/ghost cars), and applies
		// the per-racer stat scales.
		// VTABLE: LEGORACERS 0x004b04e4
		// SIZE 0x888
		class Physics : public CarBody {
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

			Physics();

			void Update(LegoS32 p_elapsedMs) override; // vtable+0x04
			LegoU32 OnCollisionRecord(                                        // vtable+0x0c
				GolVec3* p_point,
				RaceEventRecord* p_record,
				GolBoundedEntity* p_world,
				GolBoundingVolume::Field0x0c* p_context
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
			virtual ~Physics();                                  // vtable+0x50

			// SYNTHETIC: LEGORACERS 0x00429090
			// RaceState::Racer::Physics::`scalar deleting destructor'

			void Reset();
			void Initialize(
				Racer* p_racer,
				RaceEventTable* p_eventTable,
				void* p_unk0x0c,
				GolAnimatedEntity* p_carEntity,
				GolBoundedEntity* p_trackWorld,
				GolBoundedEntity* p_triggerWorld,
				SoundSource* p_soundSource,
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

		class DroppableBrick;

		// SIZE 0x30
		class SpatialSoundResource : public RaceResourceManager::Resource {
		public:
			undefined m_unk0x004[0x018 - 0x004]; // 0x004
			GolVec3 m_position;                  // 0x018
			GolVec3 m_velocity;                  // 0x024
		};

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

			void Initialize(Physics* p_physics);
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

			Physics* m_physics;                            // 0x00
			RaceRouteRecord* m_returnRecord;               // 0x04
			LegoFloat m_previousTurnRadius;                // 0x08
			LegoFloat m_turnRadius;                        // 0x0c
			LegoFloat m_thrust;                            // 0x10
			LegoU32 m_flags;                               // 0x14
			LegoFloat m_curseSteerOffset;                  // 0x18
			LegoFloat m_curseThrottleOffset;               // 0x1c
			LegoU32 m_curseJitterMs;                       // 0x20
			LegoS32 m_returnPreviewMs;                     // 0x24
			LegoU32 m_stuckMs;                             // 0x28
			LegoU32 m_slideMs;                             // 0x2c
			LegoU32 m_slideLeft;                           // 0x30
			GolVec3 m_returnPosition;                      // 0x34
			GolQuat m_returnRotation;                      // 0x40
			Physics::RouteCursorInstance* m_previewCursor; // 0x50
		};

		enum {
			c_flagBit21 = 0x00200000,
		};
		enum {
			c_flags0xd04Bit21 = 0x00200000,
		};

		void AiUsePowerup();
		LegoU32 CollectColorBrick(LegoU32 p_brickColor);
		LegoU32 GetHeldPowerupColor() const { return m_heldPowerupColor; }
		LegoU32 GetFlags() const { return m_flags; }
		void OnRaceStart();
		void StartEngine();
		void InitializePhysics(RacerContext* p_context, SetupParams* p_params);
		void ResetRaceProgress();
		void UpdateCarAnimation(LegoU32 p_elapsedMs);
		void UpdateTimers(LegoU32 p_elapsedMs);
		void UpdateDriftLean();
		void UpdateSpatialSounds();
		void UpdateEngineSound(LegoU32 p_elapsedMs);
		void StopEngineSounds();
		LegoU32 ReturnAllWhiteBricks();
		void Halt();
		void Resume();
		void EnterGhostMode();
		void LeaveGhostMode();
		void StartTurbo(LegoU32 p_unk0x04);
		void ClearActiveAction();
		void EndShield();
		void StartSpinOut();
		void EndSpinOut();
		void StartDrift(LegoBool32 p_left);
		void PlayReaction(LegoBool32 p_unk0x04);
		DroppableBrick* DropWhiteBrick();
		LegoFloat GetRaceProgress();
		void CycleHudGadget();
		void SwitchToAiControl();
		void StartMagnetHold();
		void EndMagnetHold();
		void SetStandingsPosition(LegoU32 p_position);
		void AbsorbShieldHit();
		void SetCameraView(LegoU32 p_viewIndex, LegoBool32 p_flag);
		void ReapplyCameraView();
		void CycleCameraView();
		void InitializeSounds(RaceCameraController* p_cameraController, LegoBool32 p_controlMode);
		LegoU32 StartShield(LegoU32 p_unk0x04);
		void EndDrift();
		void AttachCurse(GolAnimatedEntity* p_unk0x04, LegoU32 p_durationMs);
		void RemoveCurse();
		void EnterOpenTrack();
		LegoU32 CrossFinishLine();
		void EnterPostLineZone();
		void ComputeStandingsDeltas(StandingsDeltaEntry* p_entries);
		void SetLookTarget(GolVec3* p_position);
		void ClearLookTarget();
		void InvalidateCamera();
		void StartLookBack();
		void EndLookBack();

	private:
		friend class RaceState;
		friend class Physics;

		void Destroy();
		void Reset();
		void Initialize(
			RacerContext* p_context,
			CarVisuals::InitParams* p_visualParams,
			SetupParams* p_params,
			RaceState* p_raceState,
			LegoU32 p_racerIndex
		);

	public:
		enum {
			c_flagShielded = 1 << 0,
			c_flagPreStart = 1 << 1,
			c_flagHalted = 1 << 3,
			c_flagGhost = 1 << 4,
			c_flagTurbo = 1 << 6,
			c_flagDrifting = 1 << 7,
			c_flagShoveActive = 1 << 8,
			c_flagEngineSounds = 1 << 10,
			c_flagCursed = 1 << 11,
			c_flagFinished = 1 << 12,
			c_flagFacingForwardPending = 1 << 13,
			c_flagFacingForward = 1 << 14,
			c_flagHasLookTarget = 1 << 15,
			c_flagLookTargetLeft = 1 << 16,
			c_flagLookTargetRight = 1 << 17,
			c_flagCrossedBackward = 0x00080000,
			c_flagMagnetHeld = 0x00100000,
			c_flagBit22 = 0x00400000,
			c_flagCheatRedOnly = 0x01000000,
			c_flagCheatMaxPowerups = 0x02000000,
			c_flagCheatNslwj = 0x04000000,
			c_flagCheatFlySkyHigh = 0x08000000,
			c_flagSpeedRamping = 0x10000000,
			c_flagBit29 = 0x20000000,
			c_randomTableMask = 0x3ff,
			c_volumeTableMask = 0x3ff,
			c_volumeTableBase = 0xffffff00,
			c_boostSoundElapsedThreshold = 50,
			c_feedbackVariantCount = 6,
			c_feedbackHighOffset = 6,
		};

	private:
		void ApplyShove(GolVec3* p_impulse);
		void AiConsiderPowerup();
		void PlayTaunt();
		void UpdateFacing(LegoU32 p_elapsedMs);
		void UpdateLookTarget(LegoU32 p_elapsedMs);
		void OnCheckpointCrossed(CheckpointGraph::Entry* p_entry, GolBoundingVolume::Field0x0c* p_record);

	public:
		LegoBool32 CollectWhiteBrick(DroppableBrick* p_brick);

		SoundSource* m_soundSource;           // 0x004
		RacePowerupManager* m_powerupManager; // 0x008
		RaceState* m_raceState;               // 0x00c
		CheckpointGraph* m_checkpointGraph;   // 0x010
		RaceForceFeedback* m_forceFeedback;   // 0x014
		CarVisuals m_visuals;                 // 0x018
		Physics m_physics;                    // 0x3e8
		DriveController m_driveController;    // 0xc70
		CheckpointGraph::Entry* m_checkpoint; // 0xcc4
		undefined4 m_checkpointForward;       // 0xcc8
		LegoU32 m_heldPowerupColor;           // 0xccc
		LegoU32 m_aiChargeColor;              // 0xcd0
		LegoU32 m_aiChargeTarget;             // 0xcd4
		LegoU32 m_aiPowerupCheckMs;           // 0xcd8
		LegoU32 m_aiPowerupCheckIntervalMs;   // 0xcdc
		LegoU8 m_lapCount;                    // 0xce0
		undefined m_unk0xce1[0xce4 - 0xce1];  // 0xce1
		LegoU32 m_lapsCompleted;              // 0xce4
		LegoU32 m_lapTransitionCount;         // 0xce8
		LegoU32 m_lapTimes[0x18 / 4];         // 0xcec
		LegoU32 m_flags;                      // 0xd04
		LegoU32 m_controlMode;                // 0xd08
		LegoU32 m_currentZone;                // 0xd0c
		LegoU32 m_previousZone;               // 0xd10
		LegoU32 m_zoneBeforePrevious;         // 0xd14
		LegoS32 m_checkpointCount;            // 0xd18
		LegoU8 m_aiRedUseChance;              // 0xd1c
		LegoU8 m_aiYellowUseChance;           // 0xd1d
		LegoU8 m_aiGreenUseChance;            // 0xd1e
		LegoU8 m_aiBlueUseChance;             // 0xd1f
		LegoU8 m_driverStat4;                 // 0xd20
		LegoU8 m_driverStat5;                 // 0xd21
		LegoU8 m_aiAggression;                // 0xd22
		LegoU8 m_tauntSoundId;                // 0xd23
		LegoU32 m_activeEngineSound;          // 0xd24
		LegoFloat m_engineIdleVolume;         // 0xd28
		LegoFloat m_engineDriveVolume;        // 0xd2c
		LegoFloat m_engineFastVolume;         // 0xd30
		undefined4 m_tauntCooldownMs;         // 0xd34
		undefined4 m_unk0xd38;                // 0xd38
		undefined4 m_unk0xd3c;                // 0xd3c
		LegoU32 m_voiceBank;                  // 0xd40
		LegoU32 m_reactionCooldownMs;         // 0xd44
		undefined4 m_speedRampTimerMs;        // 0xd48
		undefined4 m_scrapeSoundCooldownMs;   // 0xd4c
		LegoU32 m_airborneMs;                 // 0xd50
		LegoFloat m_enginePitchScale;         // 0xd54
		LegoU32 m_whiteBrickCount;            // 0xd58
		DroppableBrick* m_whiteBricks[3];     // 0xd5c
		LegoU32 m_turboLevel;                 // 0xd68
		LegoU32 m_shieldLevel;                // 0xd6c
		undefined4 m_shoveForceSlot;          // 0xd70
		undefined4 m_shieldHitCooldownMs;     // 0xd74
		LegoU32 m_facingForwardMs;            // 0xd78
		undefined4 m_curseTimerMs;            // 0xd7c
		LegoU32 m_curseTickMs;                // 0xd80
		LegoU32 m_timeBehindDisplayMs;        // 0xd84
		LegoU32 m_timeBehind;                 // 0xd88
		union {
			SpatialSoundResource* m_turboSoundL0;    // 0xd8c
			SpatialSoundInstance* m_soundD8c;        // 0xd8c
			RaceResourceManager::Resource* m_resD8c; // 0xd8c
		};
		union {
			SpatialSoundResource* m_turboSoundL1;    // 0xd90
			SpatialSoundInstance* m_soundD90;        // 0xd90
			RaceResourceManager::Resource* m_resD90; // 0xd90
		};
		union {
			SpatialSoundResource* m_turboSoundL2;    // 0xd94
			SpatialSoundInstance* m_soundD94;        // 0xd94
			RaceResourceManager::Resource* m_resD94; // 0xd94
		};
		union {
			SpatialSoundResource* m_ghostSound;      // 0xd98
			SpatialSoundInstance* m_soundD98;        // 0xd98
			RaceResourceManager::Resource* m_resD98; // 0xd98
		};
		union {
			SpatialSoundInstance* m_engineIdleSound;   // 0xd9c
			RaceResourceManager::Resource* m_soundD9c; // 0xd9c
		};
		union {
			SpatialSoundInstance* m_engineDriveSound;  // 0xda0
			RaceResourceManager::Resource* m_soundDa0; // 0xda0
		};
		union {
			SpatialSoundInstance* m_engineFastSound;   // 0xda4
			RaceResourceManager::Resource* m_soundDa4; // 0xda4
		};
		union {
			SpatialSoundInstance* m_brakeSound;                  // 0xda8
			RaceResourceManager::Resource* m_brakeSoundResource; // 0xda8
		};
		union {
			SpatialSoundResource* m_curseSound;      // 0xdac
			SpatialSoundInstance* m_soundDac;        // 0xdac
			RaceResourceManager::Resource* m_resDac; // 0xdac
		};
		undefined4 m_unk0xdb0;                    // 0xdb0
		RaceCameraController* m_cameraController; // 0xdb4
		LegoU32 m_cameraViewIndex;                // 0xdb8
		LegoU16 m_displayNameBuffer;              // 0xdbc
		undefined m_unk0xdbe[0xdec - 0xdbe];      // 0xdbe
		GolString m_displayName;                  // 0xdec
		GolVec3 m_lookTargetPosition;             // 0xdf8
		LegoU32 m_materialIndex;                  // 0xe04
		RaceActionSource m_actionSource;          // 0xe08
		RaceRouteRecord* m_routeRecord;           // 0xe2c
		RaceHud* m_hud;                           // 0xe30
	};

	// SIZE 0x0c
	class RacerProgressEntry {
	public:
		Racer* m_racer;               // 0x00
		LegoFloat m_tieBreakDistance; // 0x04
		LegoFloat m_progress;         // 0x08
	};

	// Race roster and event hub: the racer array plus the shared per-race
	// services wired through the event queue callback interface.
	// VTABLE: LEGORACERS 0x004b0aa8
	// SIZE 0x194
	class RaceRoster : public LegoEventQueue::Field0x30 {
	public:
		RaceRoster();
		LegoS32 VTable0x00(LegoEventQueue::Event* p_event) override;         // vtable+0x00
		void Destroy() override;                                             // vtable+0x0c
		void VTable0x10(LegoU32 p_elapsedMs) override;                       // vtable+0x10
		GolWorldEntity* VTable0x14(LegoEventQueue::Event* p_event) override; // vtable+0x14

	private:
		friend class RaceState;

		// SIZE 0x28
		class Field0x064 {
		public:
			undefined m_unk0x00[0x24 - 0x00]; // 0x00
			undefined4 m_unk0x24;             // 0x24
		};

		void PruneBodyEvents();
		void TestRacerCollisions();
		void SortBodyEvents();

		LegoEventQueue::Event* m_bodyEvents; // 0x048
		RaceState* m_raceState;              // 0x04c
		Racer* m_racers;                     // 0x050
		LegoU32 m_racerCount;                // 0x054
		union {
			undefined4 m_unk0x058;         // 0x058
			CheckpointGraph* m_field0x010; // 0x058
		};
		union {
			RaceResourceManager* m_unk0x05c;   // 0x05c
			Racer::SoundSource* m_soundSource; // 0x05c
		};
		RacePowerupManager* m_powerupManager; // 0x060
		LegoEventQueue::Event* m_unk0x064[6]; // 0x064
		union {
			RaceResourceManager::Resource* m_proximitySoundResource; // 0x07c
			SpatialSoundInstance* m_proximitySound;                  // 0x07c
		};
		union {
			GolExport* m_unk0x080[3]; // 0x080
			Racer* m_racer080;        // 0x080
			struct {
				undefined4* m_unk0x0800;            // 0x080
				GolExport* m_golExport;             // 0x084
				TimeRaceManager* m_timeRaceManager; // 0x088
			};
		};
		GolModelEntity* m_customCarModels[2];      // 0x08c
		GolAnimatedEntity* m_customCarEntities[2]; // 0x094
		LegoU32 m_customCarCount;                  // 0x09c
		RaceRouteRecord* m_routeRecords;           // 0x0a0
		GolVec3 m_startPositions[6];               // 0x0a4
		GolVec3 m_startDirections[6];              // 0x0ec
		GolVec3 m_startUps[6];                     // 0x134
		LegoU32 m_placementSlots[6];               // 0x17c
	};

	// SIZE 0x1c
	class RaceSetup {
	public:
		RaceSetup();
		~RaceSetup();

	private:
		friend class RaceState;

		enum {
			c_rubberBandFlags = Racer::c_flagMagnetHeld | Racer::c_flagBit29,
		};

		void Reset();
		void Destroy();
		void Initialize(Racer* p_racers, LegoU32 p_racerCount);
		LegoU32 Update(LegoU32 p_elapsedMs);

		Racer* m_racers;                       // 0x00
		LegoU32 m_racerCount;                  // 0x04
		LegoU32 m_updateDelayMs;               // 0x08
		LegoFloat m_rubberBandBoost;           // 0x0c
		GolTextureList* m_textureList;         // 0x10
		GolMaterialLibrary* m_materialLibrary; // 0x14
		LegoU8 m_lapCount;                     // 0x18
		undefined m_unk0x19[0x1c - 0x19];      // 0x19
	};

	RaceState();
	~RaceState();
	void StopProximitySound();
	void RecordBestTimes(LegoRacers::Context* p_context);
	RaceRoster* GetRoster() { return &m_roster; }
	LegoEventQueue* GetEventQueue() { return &m_roster; }
	Racer* GetRacers() { return m_roster.m_racers; }
	Racer* GetRacer(LegoU32 p_index) { return &m_roster.m_racers[p_index]; }
	LegoU32 GetRacerCount() const { return m_roster.m_racerCount; }
	Racer* GetCurrentRacer() { return m_roster.m_racer080; }
	GolMaterialLibrary* GetMaterialLibrary() const { return m_setup.m_materialLibrary; }
	Racer* GetPlayerRacer() { return m_playerRacers[0]; }
	RaceRouteRecord* FindNearestRouteRecord(Racer* p_racer);
	Racer* FindRacerInCone(
		GolVec3* p_position,
		GolVec3* p_direction,
		LegoFloat p_minDistanceSquared,
		LegoFloat p_maxDistanceSquared,
		LegoFloat p_coneCosine
	);
	Racer* FindNextRacerInCone(
		Racer* p_racer,
		GolVec3* p_position,
		GolVec3* p_direction,
		LegoFloat p_minDistanceSquared,
		LegoFloat p_maxDistanceSquared,
		LegoFloat p_coneCosine
	);
	Racer* FindFarthestRacerInCone(
		GolVec3* p_position,
		GolVec3* p_direction,
		LegoFloat p_minDistanceSquared,
		LegoFloat p_maxDistanceSquared,
		LegoFloat p_coneCosine
	);
	Racer* FindNearestRacerInCone(
		GolVec3* p_position,
		GolVec3* p_direction,
		LegoFloat p_minDistanceSquared,
		LegoFloat p_maxDistanceSquared,
		LegoFloat p_coneCosine
	);
	Racer* FindNearestRacerInRange(GolVec3* p_position, LegoFloat p_minDistanceSquared, LegoFloat p_maxDistanceSquared);
	LegoU32 GetTimeBehind(Racer* p_racer);
	void ComputeStandingsDeltas(Racer* p_racer, Racer::StandingsDeltaEntry* p_entries);
	const GolVec3& GetStartPosition(LegoU32 p_index) const { return m_roster.m_startPositions[p_index]; }
	const GolVec3& GetStartDirection(LegoU32 p_index) const { return m_roster.m_startDirections[p_index]; }
	const GolVec3& GetStartUp(LegoU32 p_index) const { return m_roster.m_startUps[p_index]; }
	LegoU32 GetPlacementSlot(LegoU32 p_index) const { return m_roster.m_placementSlots[p_index]; }
	Racer::Physics::RouteCursorInstance* GetSharedRouteCursor() { return &m_sharedRouteCursor; }

private:
	friend class RaceSession;

	enum {
		c_invalidTime = 0xffffffff,
		c_racerFlags0xd04Bit10 = 1 << 10,
		c_racerFlags0xd04Bit12 = 1 << 12,
		c_racerProgressEntryCount = 6,
	};

	static RacerProgressEntry g_racerProgressEntries[c_racerProgressEntryCount];

	// SIZE 0x44
	class CreateRacersParams {
	public:
		LegoU32 m_racerCount;                             // 0x00
		LegoRacers::Context::PlayerSetupSlot* m_slots[6]; // 0x04
		RaceRouteRecord* m_routeRecords;                  // 0x1c
		RaceRouteRecord* m_racerRoutes[6];                // 0x20
		TimeRaceManager* m_timeRaceManager;               // 0x38
		undefined4 m_splitScreen;                         // 0x3c
		LegoU8 m_lapCount;                                // 0x40
		undefined m_unk0x41[0x44 - 0x41];                 // 0x41
	};

	// SIZE 0x40
	class RacerContext {
	public:
		GolD3DRenderDevice* m_renderer;               // 0x00
		GolExport* m_golExport;                       // 0x04
		GolCollidableEntity* m_trackCollidable;       // 0x08
		GolBoundedEntity* m_trackWorld;               // 0x0c
		GolBoundedEntity* m_triggerWorld;             // 0x10
		Racer::SoundSource* m_soundSource;            // 0x14
		RacePowerupManager* m_powerupManager;         // 0x18
		CutsceneAnimation* m_particleAnimation;       // 0x1c
		CutsceneAnimation* m_sharedParticleAnimation; // 0x20
		RaceDecalManager* m_decalManager;             // 0x24
		RaceEventTable* m_eventTable;                 // 0x28
		void* m_surfaceTable;                         // 0x2c
		LegoBool32 m_shadowsEnabled;                  // 0x30
		RaceRouteRecord* m_routeRecord;               // 0x34
		CheckpointGraph* m_checkpointGraph;           // 0x38
		LegoU32 m_cheatFlags;                         // 0x3c
	};

	void CreateRacers(CreateRacersParams* p_params, RacerContext* p_context, LegoBool32 p_binary);
	void CreateRacer(
		LegoRacers::Context::PlayerSetupSlot* p_slot,
		RacerContext* p_context,
		LegoU32 p_racerIndex,
		undefined4 p_unk0x10
	);
	void LoadStartPositions(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
	void InitializeRacerVisuals(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
	void DrawRacersTransparent(GolD3DRenderDevice* p_renderer);
	void UpdateRacers(LegoU32 p_elapsedMs);
	void UpdateStandings();
	void UpdateShadows(GolCamera* p_camera);
	void StartRace();
	void DrawRacerEntities(GolRenderDevice* p_renderer, Racer* p_racer);
	void SetCurrentRacer(Racer* p_racer) { m_roster.m_racer080 = p_racer; }
	void SetRubberBandBoost(LegoFloat p_boost) { m_setup.m_rubberBandBoost = p_boost; }
	void Reset();
	void Destroy();

	DriverCosmeticTable m_driverTable;                       // 0x000
	ChampionDefinitionList m_championList;                   // 0x080
	ChassisModelTable m_chassisTable;                        // 0x0b4
	RaceRoster m_roster;                                     // 0x0f0
	RaceSetup m_setup;                                       // 0x284
	Racer::Physics::RouteCursorInstance m_sharedRouteCursor; // 0x2a0
	Racer* m_playerRacers[2];                                // 0x318
};

#endif // RACESTATE_H
