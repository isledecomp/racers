#ifndef RACEEVENTTABLE_H
#define RACEEVENTTABLE_H

#include "decomp.h"
#include "golmath.h"
#include "goltxtparser.h"
#include "race/hazardmanager.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racesky.h"
#include "race/racestate.h"
#include "types.h"

class GolFileParser;
class GolWorldDatabase;
class MabMaterialAnimation0x14;
class MabMaterialAnimationItem0x18;
class MaterialTable0x0c;
class CutsceneAnimation;
struct CutsceneParticleRef;
class RaceSession;
class TriggerWorld;

// Track event table (.evb): per-event resources (sounds, animations,
// particles, sky/color/model changes, physics forces, lap zones) fanned
// out by event id from surface records, hazards, and race logic.
// SIZE 0x90
class RaceEventTable {
public:
	LegoU32 StartEventsAt(undefined4 p_eventId, GolVec3* p_position);
	void EndEventsAt(undefined4 p_eventId, GolVec3* p_position);
	void FireEventsAt(undefined4 p_startId, undefined4 p_endId, GolVec3* p_position);
	void StartEventsForRacer(undefined4 p_eventId, RaceState::Racer* p_racer);
	void EndEventsForRacer(undefined4 p_eventId, RaceState::Racer* p_racer);
	void FireEventsForRacer(undefined4 p_startId, undefined4 p_endId, RaceState::Racer* p_racer);
	void ForceEvents(undefined4 p_eventId);

public:
	// VTABLE: LEGORACERS 0x004b1b4c
	// SIZE 0x1fc
	class EvbTxtParser : public GolTxtParser {
		// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
		// RaceEventTable::EvbTxtParser::`scalar deleting destructor'

		// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
		// RaceEventTable::EvbTxtParser::~EvbTxtParser
	};

	// SIZE 0x34
	struct Params {
		GolWorldDatabase* m_trackDatabase;                   // 0x00
		GolWorldDatabase* m_sharedDatabase;                  // 0x04
		GolWorldDatabase* m_unk0x08;                         // 0x08
		GolWorldDatabase* m_unk0x0c;                         // 0x0c
		RaceState::Racer::SoundSource* m_soundSource;        // 0x10
		HazardManager* m_hazardManager;                      // 0x14
		CutsceneAnimation* m_particleAnimation;              // 0x18
		CutsceneAnimation* m_sharedParticleAnimation;        // 0x1c
		RaceSkyState* m_skyState;                            // 0x20
		RacePowerupManager::TargetPointList* m_targetPoints; // 0x24
		const LegoChar* m_name;                              // 0x28
		LegoBool32 m_binary;                                 // 0x2c
		LegoBool32 m_mirror;                                 // 0x30
	};

	// VTABLE: LEGORACERS 0x004b1b28
	// SIZE 0x20
	class Resource {
	public:
		enum {
			c_state0x18One = 1,
			c_state0x18Three = 3,
			c_state0x18Four = 4,
			c_state0x18Five = 5,
			c_flags0x1cBit1 = 1 << 1,
			c_flags0x1cBit2 = 1 << 2,
			c_flags0x1cBit3 = 1 << 3,
			c_flags0x1cBit5 = 1 << 5
		};

		Resource();
		virtual void OnStartForRacer(RaceState::Racer* p_racer); // vtable+0x00
		virtual void OnStartAt(GolVec3* p_position);             // vtable+0x04
		virtual void OnEndForRacer(RaceState::Racer* p_racer);   // vtable+0x08
		virtual void OnEnd();                                    // vtable+0x0c
		virtual ~Resource();                                     // vtable+0x10
		virtual void Update(LegoU32 p_elapsedMs);                // vtable+0x14

		void ForceEventStart(RaceState::Racer* p_racer);
		void ForceEventEnd(RaceState::Racer* p_racer);
		void Reset();
		void NotifyStateChange(LegoU32 p_unk0x04, LegoU32 p_unk0x08);
		void OnEventStart(GolVec3* p_position);
		void OnEventEnd(GolVec3* p_position);
		void SetState0x18(LegoU32 p_state) { m_state0x18 = p_state; }

		// SYNTHETIC: LEGORACERS 0x0045ed70
		// RaceEventTable::Resource::`scalar deleting destructor'

	public:
		RaceEventTable* m_eventTable;     // 0x04
		LegoS32 m_stateEventIds[3];       // 0x08
		undefined4 m_eventId;             // 0x14
		LegoU32 m_state0x18;              // 0x18
		LegoU8 m_flags0x1c;               // 0x1c
		undefined m_unk0x1d[0x20 - 0x1d]; // 0x1d
	};

	// VTABLE: LEGORACERS 0x004b1ca4
	// SIZE 0x24
	class LapZoneResource : public Resource {
	public:
		// SIZE 0x18
		struct InitParams {
			undefined4 m_unk0x00;         // 0x00
			LegoS32 m_stateEventIds[3];   // 0x04
			RaceEventTable* m_eventTable; // 0x10
			undefined4 m_unk0x14;         // 0x14
		};

		LapZoneResource();
		~LapZoneResource() override;
		void OnStartForRacer(RaceState::Racer* p_racer) override;
		void OnEndForRacer(RaceState::Racer* p_racer) override;

		void Initialize(InitParams* p_params);
		void Destroy();

		// SYNTHETIC: LEGORACERS 0x00461b40
		// RaceEventTable::LapZoneResource::`vector deleting destructor'

	private:
		undefined4 m_zone; // 0x20
	};

	// VTABLE: LEGORACERS 0x004b1ad4
	// SIZE 0x2c
	class LookTargetResource : public Resource {
	public:
		// SIZE 0x20
		struct InitParams {
			undefined4 m_unk0x00;         // 0x00
			LegoS32 m_stateEventIds[3];   // 0x04
			RaceEventTable* m_eventTable; // 0x10
			GolVec3 m_unk0x14;            // 0x14
		};

		LookTargetResource();
		~LookTargetResource() override;
		void OnStartForRacer(RaceState::Racer* p_racer) override;
		void OnEndForRacer(RaceState::Racer* p_racer) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void FUN_004513d0(undefined4 p_unk0x04);
		void Initialize(InitParams* p_params);
		void Destroy();

		// SYNTHETIC: LEGORACERS 0x00461610
		// RaceEventTable::LookTargetResource::`vector deleting destructor'

	private:
		GolVec3 m_lookPosition; // 0x20
	};

	// VTABLE: LEGORACERS 0x004b1af0
	// SIZE 0x30
	class TimerResource : public Resource {
	public:
		// SIZE 0x20
		struct InitParams {
			undefined4 m_unk0x00;         // 0x00
			LegoS32 m_stateEventIds[3];   // 0x04
			RaceEventTable* m_eventTable; // 0x10
			LegoS32 m_unk0x14;            // 0x14
			LegoU32 m_unk0x18;            // 0x18
			LegoBool32 m_unk0x1c;         // 0x1c
		};

		TimerResource();
		~TimerResource() override;
		void OnStartAt(GolVec3* p_unk0x04) override;
		void OnEnd() override;
		void Update(LegoU32 p_elapsedMs) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void FUN_004513d0(undefined4 p_unk0x04);
		void ClearFields();
		void Initialize(InitParams* p_params);
		void Destroy();

		// SYNTHETIC: LEGORACERS 0x00460cb0
		// RaceEventTable::TimerResource::`vector deleting destructor'

	public:
		LegoS32 m_holdEventId;            // 0x20
		LegoU32 m_durationMs;             // 0x24
		LegoU32 m_remainingMs;            // 0x28
		LegoU8 m_flags0x2c;               // 0x2c
		undefined m_unk0x2d[0x30 - 0x2d]; // 0x2d
	};

	// VTABLE: LEGORACERS 0x004b1be4
	// SIZE 0x34
	class MaterialAnimationResource : public Resource {
	public:
		// SIZE 0x38
		struct InitParams {
			undefined4 m_unk0x00;                // 0x00
			LegoS32 m_stateEventIds[3];          // 0x04
			RaceEventTable* m_eventTable;        // 0x10
			MabMaterialAnimation0x14* m_unk0x14; // 0x14
			MaterialTable0x0c* m_unk0x18;        // 0x18
			LegoU16 m_unk0x1c;                   // 0x1c
			undefined m_unk0x1e[0x20 - 0x1e];    // 0x1e
			LegoU32 m_unk0x20;                   // 0x20
			LegoU32 m_unk0x24;                   // 0x24
			LegoBool32 m_unk0x28;                // 0x28
			LegoBool32 m_unk0x2c;                // 0x2c
			LegoBool32 m_unk0x30;                // 0x30
			LegoBool32 m_unk0x34;                // 0x34
		};

		MaterialAnimationResource();
		~MaterialAnimationResource() override;
		void OnStartAt(GolVec3* p_unk0x04) override;
		void OnEnd() override;
		void Update(LegoU32 p_elapsedMs) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void FUN_00463120(InitParams* p_params);
		void FUN_004631e0();

		// SYNTHETIC: LEGORACERS 0x0045fe50
		// RaceEventTable::MaterialAnimationResource::`vector deleting destructor'

	private:
		enum {
			c_flags0x1cBit0 = 1 << 0
		};

		MabMaterialAnimation0x14* m_unk0x20;     // 0x20
		MabMaterialAnimationItem0x18* m_unk0x24; // 0x24
		MabMaterialAnimationItem0x18* m_unk0x28; // 0x28
		MaterialTable0x0c* m_unk0x2c;            // 0x2c
		LegoU16 m_unk0x30;                       // 0x30
		undefined m_unk0x32[0x34 - 0x32];        // 0x32
	};

	// VTABLE: LEGORACERS 0x004b1c00
	// SIZE 0x34
	class PartAnimationResource : public Resource {
	public:
		// SIZE 0x3c
		struct InitParams {
			undefined4 m_unk0x00;         // 0x00
			LegoS32 m_stateEventIds[3];   // 0x04
			RaceEventTable* m_eventTable; // 0x10
			GolAnimatedEntity* m_unk0x14; // 0x14
			LegoS32 m_unk0x18;            // 0x18
			LegoS32 m_unk0x1c;            // 0x1c
			LegoS32 m_unk0x20;            // 0x20
			LegoS32 m_unk0x24;            // 0x24
			LegoBool32 m_unk0x28;         // 0x28
			LegoBool32 m_unk0x2c;         // 0x2c
			LegoBool32 m_unk0x30;         // 0x30
			LegoBool32 m_unk0x34;         // 0x34
			LegoBool32 m_unk0x38;         // 0x38
		};

		PartAnimationResource();
		~PartAnimationResource() override;
		void OnStartAt(GolVec3* p_unk0x04) override;
		void OnEnd() override;
		void Update(LegoU32 p_elapsedMs) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void FUN_00463330(InitParams* p_params);
		void FUN_004633e0();

		// SYNTHETIC: LEGORACERS 0x0045f9d0
		// RaceEventTable::PartAnimationResource::`vector deleting destructor'

	private:
		enum {
			c_flags0x1cBit0 = 1 << 0,
			c_flags0x1cBit4 = 1 << 4,
			c_entityFlag0x200000 = 1 << 21,
			c_entityFlags0x4e0000 = 0x4e0000,
			c_entityFlags0x0e0000 = 0x0e0000,
			c_entityFlags0x120000 = 0x120000
		};

		GolAnimatedEntity* m_unk0x20; // 0x20
		LegoS32 m_unk0x24;            // 0x24
		LegoS32 m_unk0x28;            // 0x28
		LegoS32 m_unk0x2c;            // 0x2c
		LegoS32 m_unk0x30;            // 0x30
	};

	// VTABLE: LEGORACERS 0x004b1c20
	// SIZE 0x34
	class ModelDistanceResource : public Resource {
	public:
		// SIZE 0x24
		struct InitParams {
			undefined4 m_unk0x00;         // 0x00
			LegoS32 m_stateEventIds[3];   // 0x04
			RaceEventTable* m_eventTable; // 0x10
			GolModelEntity* m_unk0x14;    // 0x14
			LegoBool32 m_unk0x18;         // 0x18
			LegoBool32 m_unk0x1c;         // 0x1c
			LegoBool32 m_unk0x20;         // 0x20
		};

		ModelDistanceResource();
		~ModelDistanceResource() override;
		void OnStartAt(GolVec3*) override;
		void OnEnd() override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void FUN_004636e0();
		void FUN_00463700(InitParams* p_params);
		void FUN_004637a0();

		// SYNTHETIC: LEGORACERS 0x004613d0
		// RaceEventTable::ModelDistanceResource::`vector deleting destructor'

	private:
		GolModelEntity* m_unk0x20;     // 0x20
		LegoFloat m_modelDistances[3]; // 0x24
		LegoBool32 m_unk0x30;          // 0x30
	};

	// VTABLE: LEGORACERS 0x004b1c3c
	// SIZE 0x2c
	class NodeTransformResource : public Resource {
	public:
		// SIZE 0x24
		struct InitParams {
			undefined4 m_unk0x00;         // 0x00
			LegoS32 m_stateEventIds[3];   // 0x04
			RaceEventTable* m_eventTable; // 0x10
			GolBoundedEntity* m_unk0x14;  // 0x14
			GolModelEntity* m_unk0x18;    // 0x18
			LegoU32 m_unk0x1c;            // 0x1c
			LegoBool32 m_unk0x20;         // 0x20
		};

		NodeTransformResource();
		~NodeTransformResource() override;
		void OnStartAt(GolVec3*) override;
		void OnEnd() override;
		void Update(LegoU32 p_elapsedMs) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void FUN_004638f0();
		void FUN_00463900(InitParams* p_params);
		void FUN_00463970();

		// SYNTHETIC: LEGORACERS 0x00461010
		// RaceEventTable::NodeTransformResource::`vector deleting destructor'

	private:
		GolBoundedEntity* m_unk0x20; // 0x20
		GolModelEntity* m_unk0x24;   // 0x24
		LegoU32 m_unk0x28;           // 0x28
	};

	// VTABLE: LEGORACERS 0x004b1aac
	// SIZE 0x34
	class SkyStateResource : public Resource {
	public:
		// SIZE 0x2c
		struct InitParams {
			undefined4 m_unk0x00;             // 0x00
			LegoS32 m_stateEventIds[3];       // 0x04
			RaceEventTable* m_eventTable;     // 0x10
			RaceSkyState* m_unk0x14;          // 0x14
			GolName m_unk0x18;                // 0x18
			LegoU32 m_unk0x20;                // 0x20
			LegoBool32 m_unk0x24;             // 0x24
			LegoU8 m_flags0x28;               // 0x28
			undefined m_unk0x29[0x2c - 0x29]; // 0x29
		};

		SkyStateResource();
		~SkyStateResource() override;
		void OnStartAt(GolVec3* p_unk0x04) override;
		void OnEnd() override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void ClearFields();
		void Initialize(InitParams* p_params);
		void Destroy();

		// SYNTHETIC: LEGORACERS 0x004606c0
		// RaceEventTable::SkyStateResource::`vector deleting destructor'

	private:
		enum {
			c_flags0x30Bit0 = 1 << 0,
			c_flags0x30Bit1 = 1 << 1,
			c_flags0x30Bit2 = 1 << 2,
			c_flags0x30Bit3 = 1 << 3
		};

		RaceSkyState* m_skyState; // 0x20
		GolName m_unk0x24;        // 0x24
		LegoU32 m_unk0x2c;        // 0x2c
		LegoU8 m_flags0x30;       // 0x30
		undefined m_unk0x31[0x34 - 0x31];
	};

	// VTABLE: LEGORACERS 0x004b1bc8
	// SIZE 0x38
	class ExternalForceResource : public Resource {
	public:
		// SIZE 0x30
		struct InitParams {
			undefined4 m_unk0x00;         // 0x00
			LegoS32 m_stateEventIds[3];   // 0x04
			RaceEventTable* m_eventTable; // 0x10
			GolVec3 m_unk0x14;            // 0x14
			LegoU32 m_unk0x20;            // 0x20
			LegoS32 m_unk0x24;            // 0x24
			LegoBool32 m_unk0x28;         // 0x28
			LegoBool32 m_unk0x2c;         // 0x2c
		};

		ExternalForceResource();
		~ExternalForceResource() override;
		void OnStartForRacer(RaceState::Racer* p_racer) override;
		void OnEndForRacer(RaceState::Racer* p_racer) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void ClearFields();
		void Initialize(InitParams* p_params);
		void Destroy();

		// SYNTHETIC: LEGORACERS 0x00461930
		// RaceEventTable::ExternalForceResource::`vector deleting destructor'

	public:
		enum {
			c_flags0x34Bit0 = 1 << 0
		};

		GolVec3 m_force;                  // 0x20
		LegoU32 m_channel;                // 0x2c
		LegoS32 m_armEventId;             // 0x30
		LegoU8 m_flags0x34;               // 0x34
		undefined m_unk0x35[0x38 - 0x35]; // 0x35
	};

	// VTABLE: LEGORACERS 0x004b1de0
	// SIZE 0x48
	class ColorTransformResource : public Resource {
	public:
		// SIZE 0x3c
		struct InitParams {
			undefined4 m_unk0x00;         // 0x00
			LegoS32 m_stateEventIds[3];   // 0x04
			RaceEventTable* m_eventTable; // 0x10
			LegoU32 m_flags0x14;          // 0x14
			ColorTransform0x20 m_unk0x18; // 0x18
			GolWorldEntity* m_unk0x38;    // 0x38
		};

		ColorTransformResource();
		~ColorTransformResource() override;
		void OnStartForRacer(RaceState::Racer* p_racer) override;
		void OnEndForRacer(RaceState::Racer* p_racer) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void FUN_00465560();
		void FUN_00465570(InitParams* p_params);
		void FUN_004655e0();

		// SYNTHETIC: LEGORACERS 0x00460a70
		// RaceEventTable::ColorTransformResource::`vector deleting destructor'

	private:
		enum {
			c_flags0x20Bit1 = 1 << 1,
		};

		LegoU32 m_flags0x20;                 // 0x20
		ColorTransform0x20 m_colorTransform; // 0x24
		GolWorldEntity* m_unk0x44;           // 0x44
	};

	// VTABLE: LEGORACERS 0x004b1c84
	// SIZE 0x5c
	class SoundResource : public Resource {
	public:
		enum {
			c_flags0x1cBit0 = 1 << 0,
			c_flags0x1cBit3 = 1 << 3,
			c_randomTableMask = 0x3ff,
			c_randomDelayBaseMs = 500,
			c_randomDelayRangeMs = 1000,
			c_probabilityMax = 0xff
		};

		// SIZE 0x4c
		struct InitParams {
			undefined4 m_unk0x00;                     // 0x00
			undefined4 m_unk0x04;                     // 0x04
			RaceState::Racer::SoundSource* m_unk0x08; // 0x08
			GolVec3 m_unk0x0c;                        // 0x0c
			LegoU32 m_unk0x18;                        // 0x18
			LegoU32 m_unk0x1c;                        // 0x1c
			LegoFloat m_unk0x20;                      // 0x20
			LegoFloat m_unk0x24;                      // 0x24
			LegoFloat m_unk0x28;                      // 0x28
			LegoFloat m_unk0x2c;                      // 0x2c
			LegoFloat m_unk0x30;                      // 0x30
			LegoBool32 m_unk0x34;                     // 0x34
			LegoBool32 m_unk0x38;                     // 0x38
			LegoBool32 m_unk0x3c;                     // 0x3c
			LegoBool32 m_unk0x40;                     // 0x40
			GolModelEntity* m_unk0x44;                // 0x44
			LegoU32 m_unk0x48;                        // 0x48
		};

		SoundResource();
		~SoundResource() override;
		void OnStartAt(GolVec3* p_unk0x04) override;
		void OnEnd() override;
		void Update(LegoU32 p_elapsedMs) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void Initialize(InitParams* p_params);
		void Destroy();
		void StopSound();

		// SYNTHETIC: LEGORACERS 0x0045f600
		// RaceEventTable::SoundResource::`vector deleting destructor'

	private:
		union {
			SpatialSoundInstance* m_sound;            // 0x20
			RaceResourceManager::Resource* m_res0x20; // 0x20
		};
		RaceState::Racer::SoundSource* m_soundSource; // 0x24
		GolModelEntity* m_unk0x28;                    // 0x28
		LegoU32 m_unk0x2c;                            // 0x2c
		SoundVector m_position;                       // 0x30
		LegoU32 m_soundId;                            // 0x3c
		LegoU32 m_unk0x40;                            // 0x40
		LegoFloat m_volume;                           // 0x44
		LegoFloat m_frequencyScale;                   // 0x48
		LegoFloat m_minDistance;                      // 0x4c
		LegoFloat m_maxDistance;                      // 0x50
		LegoU8 m_probability;                         // 0x54
		undefined m_unk0x55[0x58 - 0x55];             // 0x55
		LegoU32 m_unk0x58;                            // 0x58
	};

	// VTABLE: LEGORACERS 0x004b1b0c
	// SIZE 0x64
	class ParticleResource : public Resource {
	public:
		// SIZE 0x5c
		struct InitParams {
			undefined4 m_unk0x00;                   // 0x00
			LegoS32 m_stateEventIds[3];             // 0x04
			RaceEventTable* m_eventTable;           // 0x10
			CutsceneAnimation* m_unk0x14;           // 0x14
			CutsceneAnimation* m_particleAnimation; // 0x18
			GolModelEntity* m_unk0x1c;              // 0x1c
			LegoU32 m_unk0x20;                      // 0x20
			GolName m_unk0x24;                      // 0x24
			GolVec3 m_unk0x2c;                      // 0x2c
			GolVec3 m_unk0x38;                      // 0x38
			GolVec3 m_unk0x44;                      // 0x44
			undefined4 m_unk0x50;                   // 0x50
			undefined4 m_unk0x54;                   // 0x54
			undefined4 m_unk0x58;                   // 0x58
		};

		ParticleResource();
		~ParticleResource() override;
		void OnStartAt(GolVec3* p_unk0x04) override;
		void OnEnd() override;
		void Update(LegoU32 p_elapsedMs) override;
		virtual LegoU32 GetKind(); // vtable+0x18

		void FUN_004513d0(undefined4 p_unk0x04);
		void ClearFields();
		void Initialize(InitParams* p_params);
		void Destroy();

		// SYNTHETIC: LEGORACERS 0x004602c0
		// RaceEventTable::ParticleResource::`vector deleting destructor'

	private:
		CutsceneAnimation* m_particleAnimation;       // 0x20
		CutsceneAnimation* m_sharedParticleAnimation; // 0x24
		GolName m_particleName;                       // 0x28
		CutsceneParticleRef* m_particle;              // 0x30
		GolModelEntity* m_trackedEntity;              // 0x34
		LegoU32 m_nodeIndex;                          // 0x38
		GolVec3 m_unk0x3c;                            // 0x3c
		GolVec3 m_unk0x48;                            // 0x48
		GolVec3 m_unk0x54;                            // 0x54
		LegoU32 m_partAnimations;                     // 0x60
	};

	// SIZE 0x08
	struct EventLink {
		LegoS32 m_eventId;       // 0x00
		LegoS32 m_forcedEventId; // 0x04
	};

	RaceEventTable();
	~RaceEventTable();
	RaceEventTable* GetEventTable() { return this; }
	void Update(LegoU32 p_elapsedMs);
	void ForceAllEvents();
	void EndAllForRacer(RaceState::Racer* p_racer);

private:
	friend class RaceSession;

	void Destroy();
	void Load(Params* p_params);
	void ParseSounds(GolFileParser* p_parser, LegoBool32 p_mirror);
	void ParsePartAnimations(GolFileParser* p_parser);
	void ParseMaterialAnimations(GolFileParser* p_parser);
	void ParseParticles(GolFileParser* p_parser, LegoBool32 p_mirror);
	void ParseEventLinks(GolFileParser* p_parser);
	void ParseSkyStates(GolFileParser* p_parser);
	void ParseColorTransforms(GolFileParser* p_parser);
	void ParseTimers(GolFileParser* p_parser);
	void ParseNodeTransforms(GolFileParser* p_parser);
	void ParseModelDistances(GolFileParser* p_parser);
	void ParseLookTargets(GolFileParser* p_parser, LegoBool32 p_mirror);
	void ParseExternalForces(GolFileParser* p_parser, LegoBool32 p_mirror);
	void ParseLapZones(GolFileParser* p_parser);

	GolWorldDatabase* m_trackDatabase;                   // 0x00
	GolWorldDatabase* m_sharedDatabase;                  // 0x04
	GolWorldDatabase* m_unk0x08;                         // 0x08
	GolWorldDatabase* m_unk0x0c;                         // 0x0c
	RaceState::Racer::SoundSource* m_soundSource;        // 0x10
	HazardManager* m_hazardManager;                      // 0x14
	CutsceneAnimation* m_particleAnimation;              // 0x18
	CutsceneAnimation* m_sharedParticleAnimation;        // 0x1c
	RaceSkyState* m_skyState;                            // 0x20
	RacePowerupManager::TargetPointList* m_targetPoints; // 0x24
	LegoU32 m_soundCount;                                // 0x28
	LegoU32 m_partAnimationCount;                        // 0x2c
	LegoU32 m_materialAnimationCount;                    // 0x30
	LegoU32 m_particleCount;                             // 0x34
	LegoU32 m_eventLinkCount;                            // 0x38
	LegoU32 m_skyStateCount;                             // 0x3c
	LegoU32 m_timerCount;                                // 0x40
	LegoU32 m_colorTransformCount;                       // 0x44
	LegoU32 m_lapZoneCount;                              // 0x48
	LegoU32 m_nodeTransformCount;                        // 0x4c
	LegoU32 m_modelDistanceCount;                        // 0x50
	LegoU32 m_lookTargetCount;                           // 0x54
	LegoU32 m_externalForceCount;                        // 0x58
	SoundResource* m_sounds;                             // 0x5c
	PartAnimationResource* m_partAnimations;             // 0x60
	MaterialAnimationResource* m_materialAnimations;     // 0x64
	ParticleResource* m_particles;                       // 0x68
	EventLink* m_eventLinks;                             // 0x6c
	SkyStateResource* m_skyStates;                       // 0x70
	TimerResource* m_timers;                             // 0x74
	NodeTransformResource* m_nodeTransforms;             // 0x78
	ColorTransformResource* m_colorTransforms;           // 0x7c
	LapZoneResource* m_lapZones;                         // 0x80
	ModelDistanceResource* m_modelDistances;             // 0x84
	LookTargetResource* m_lookTargets;                   // 0x88
	ExternalForceResource* m_externalForces;             // 0x8c
};

#endif // RACEEVENTTABLE_H
