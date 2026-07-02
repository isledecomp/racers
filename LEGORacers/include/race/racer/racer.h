#ifndef RACER_H
#define RACER_H

#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "race/raceactionsource.h"
#include "race/raceeventrecord.h"
#include "race/racer/carvisuals.h"
#include "race/racer/drivecontroller.h"
#include "race/racer/racerphysics.h"
#include "util/legoeventqueue.h"

class GolFileParser;
class RaceCameraController;
class RaceForceFeedback;
class RaceHud;
class RacePowerupManager;
class DroppableBrick;
class RacerContext;
class RacerSoundSource;
class SpatialSoundInstance;
class TimeRaceManager;

// VTABLE: LEGORACERS 0x004b09b0
// SIZE 0xe34
class Racer : public LegoEventQueue::Callback {
public:
	Racer();
	void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
	virtual ~Racer();                                               // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x0043b420
	// Racer::`vector deleting destructor'

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
		void* m_surfaceTable;             // 0x64
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

	// SIZE 0x0c
	class StandingsDeltaEntry {
	public:
		Racer* m_racer;    // 0x00
		LegoS32 m_delta;   // 0x04
		LegoU32 m_isValid; // 0x08
	};

	// SIZE 0x30
	class SpatialSoundResource : public RaceResourceManager::Resource {
	public:
		undefined m_unk0x004[0x018 - 0x004]; // 0x004
		GolVec3 m_position;                  // 0x018
		GolVec3 m_velocity;                  // 0x024
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
	friend class RacerPhysics;

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

	RacerSoundSource* m_soundSource;      // 0x004
	RacePowerupManager* m_powerupManager; // 0x008
	RaceState* m_raceState;               // 0x00c
	CheckpointGraph* m_checkpointGraph;   // 0x010
	RaceForceFeedback* m_forceFeedback;   // 0x014
	CarVisuals m_visuals;                 // 0x018
	RacerPhysics m_physics;               // 0x3e8
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

#endif // RACER_H
