#ifndef RACEEVENTDISPATCHER0X08_H
#define RACEEVENTDISPATCHER0X08_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golworldentity.h"
#include "material/materialtable0x0c.h"
#include "race/powerups/powerupprojectile.h"
#include "race/raceactionsource.h"
#include "race/racesessionfield0x27d4.h"
#include "race/racestate.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolCamera;
class GolD3DRenderDevice;
class GolFileParser;
class GolAnimatedEntity;
class GolBillboard;
class GolCollidableEntity;
class GolExport;
class GolModelEntity;
class GolNameTable;
class GolWorldDatabase;
struct CutsceneParticleRef;
class CutsceneAnimation;
class MabMaterialAnimationItem0x8;
class MabMaterialAnimationItem0x18;
class RaceEventTable;
class RacePowerupManager;
class RaceSession;
class TriggerWorld;
class SpatialSoundInstance;

// SIZE 0x08
class HazardManager {
public:
	class Context;

	// VTABLE: LEGORACERS 0x004b40f8
	// SIZE 0x1fc
	class HzbTxtParser : public GolTxtParser {};

	// Named collision-flag record looked up in the collider name table
	// ("pilcol", "sphinx", "mmrocc"); bits 16/17 gate collidability.
	// SIZE 0x0c
	class ColliderRecord {
	public:
		enum {
			c_flagBit16 = 1 << 16,
			c_flagBit17 = 1 << 17,
		};

		undefined4 m_unk0x00; // 0x00
		undefined4 m_unk0x04; // 0x04
		LegoU32 m_flags;      // 0x08
	};

	// VTABLE: LEGORACERS 0x004b40c4
	// SIZE 0x10
	class Hazard : public LegoEventQueue::Callback {
	public:
		Hazard();
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual void OnActivate(void*) = 0;                             // vtable+0x04
		virtual void OnDeactivate(void*) = 0;                           // vtable+0x08
		virtual ~Hazard();                                              // vtable+0x0c
		virtual void Load(Context*, GolFileParser*) = 0;                // vtable+0x10
		virtual void Update(undefined4 p_elapsedMs);                    // vtable+0x14
		virtual void UpdatePerRacer(GolCamera*, RaceState::Racer*);     // vtable+0x18
		virtual void Draw(GolD3DRenderDevice*);                         // vtable+0x1c
		virtual LegoBool32 CanRetrigger();                              // vtable+0x20
		virtual void ResetState();                                      // vtable+0x24
		virtual void OnEventStart(LegoS32, void*);                      // vtable+0x28
		virtual void OnEventEnd(LegoS32, void*);                        // vtable+0x2c

		LegoS32 Reset();
		void Activate(void* p_unk0x04);
		void Deactivate(void* p_unk0x04);

		// SYNTHETIC: LEGORACERS 0x0048a420
		// HazardManager::Hazard::`scalar deleting destructor'

	protected:
		friend class HazardManager;

		RaceEventTable* m_eventTable; // 0x04
		LegoS32 m_triggerId;          // 0x08
		LegoS32 m_state;              // 0x0c
	};

	// VTABLE: LEGORACERS 0x004b4194
	// SIZE 0x18
	class WarpPadHazard : public Hazard {
	public:
		WarpPadHazard();
		~WarpPadHazard() override;
		void OnActivate(void* p_racer) override;                // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;            // vtable+0x08
		void Load(Context* p_context, GolFileParser*) override; // vtable+0x10
		void Update(undefined4 p_unk0x04) override;             // vtable+0x14
		LegoBool32 CanRetrigger() override;                     // vtable+0x20

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048aea0
		// HazardManager::WarpPadHazard::`scalar deleting destructor'

	private:
		enum {
			c_flagGhost = 1 << 4,
		};

		RacePowerupManager* m_unk0x10; // 0x10
		LegoU32 m_unk0x14;             // 0x14
	};

	// VTABLE: LEGORACERS 0x004b41c4
	// SIZE 0x20
	class OscillatorHazard : public Hazard {
	public:
		OscillatorHazard();
		~OscillatorHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048b0a0
		// HazardManager::OscillatorHazard::`scalar deleting destructor'

	private:
		GolModelEntity* m_unk0x10; // 0x10
		LegoFloat m_unk0x14;       // 0x14
		LegoFloat m_unk0x18;       // 0x18
		LegoFloat m_unk0x1c;       // 0x1c
	};

	// VTABLE: LEGORACERS 0x004b423c
	// SIZE 0x18
	class CurseDropHazard : public Hazard {
	public:
		CurseDropHazard();
		~CurseDropHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_unk0x04) override;                      // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048b310
		// HazardManager::CurseDropHazard::`scalar deleting destructor'

	private:
		enum {
			c_randomTableMask = 0x3ff,
			c_positionCount = 3,
		};

		RacePowerupManager* m_unk0x10; // 0x10
		LegoU32 m_unk0x14;             // 0x14
	};

	// VTABLE: LEGORACERS 0x004b4274
	// SIZE 0x58
	class SweepCannonHazard : public Hazard {
	public:
		SweepCannonHazard();
		~SweepCannonHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		void ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048b4d0
		// HazardManager::SweepCannonHazard::`scalar deleting destructor'

	private:
		enum {
			c_actionCooldownMs = 0x206c,
		};

		RaceActionSource m_unk0x10;    // 0x10
		RacePowerupManager* m_unk0x34; // 0x34
		GolAnimatedEntity* m_unk0x38;  // 0x38
		LegoFloat m_unk0x3c;           // 0x3c
		LegoFloat m_unk0x40;           // 0x40
		LegoFloat m_unk0x44;           // 0x44
		LegoU32 m_unk0x48;             // 0x48
		LegoU32 m_unk0x4c;             // 0x4c
		LegoU32 m_unk0x50;             // 0x50
		LegoU32 m_unk0x54;             // 0x54
	};

	// VTABLE: LEGORACERS 0x004b42b8
	// SIZE 0x20
	class FallingPillarHazard : public Hazard {
	public:
		FallingPillarHazard();
		~FallingPillarHazard() override;
		void OnActivate(void*) override;                        // vtable+0x04
		void OnDeactivate(void*) override;                      // vtable+0x08
		void Load(Context* p_context, GolFileParser*) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;           // vtable+0x14
		void ResetState() override;                             // vtable+0x24

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048b8b0
		// HazardManager::FallingPillarHazard::`scalar deleting destructor'

	private:
		enum {
		};

		GolAnimatedEntity* m_unk0x10; // 0x10
		CutsceneAnimation* m_unk0x14; // 0x14
		ColliderRecord* m_unk0x18;    // 0x18
		LegoU32 m_unk0x1c;            // 0x1c
	};

	// VTABLE: LEGORACERS 0x004b433c
	// SIZE 0x24
	class SphinxHazard : public Hazard {
	public:
		SphinxHazard();
		~SphinxHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14
		void ResetState() override;                                      // vtable+0x24

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048c050
		// HazardManager::SphinxHazard::`scalar deleting destructor'

	private:
		enum {
			c_modelDistanceCount = 3,
		};

		CutsceneAnimation* m_unk0x10;            // 0x10
		GolWorldDatabase* m_unk0x14;             // 0x14
		MabMaterialAnimationItem0x18* m_unk0x18; // 0x18
		GolAnimatedEntity* m_unk0x1c;            // 0x1c
		ColliderRecord* m_unk0x20;               // 0x20
	};

	// VTABLE: LEGORACERS 0x004b4434
	// SIZE 0x18
	class HammerHazard : public Hazard {
	public:
		HammerHazard();
		~HammerHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048d010
		// HazardManager::HammerHazard::`scalar deleting destructor'

	private:
		GolAnimatedEntity* m_unk0x10; // 0x10
		LegoU32 m_unk0x14;            // 0x14
	};

	// VTABLE: LEGORACERS 0x004b43dc
	// SIZE 0x220
	class GhostHazard : public Hazard {
	public:
		GhostHazard();
		~GhostHazard() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;  // vtable+0x00
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14
		void Draw(GolD3DRenderDevice* p_renderer) override;              // vtable+0x1c

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048c8c0
		// HazardManager::GhostHazard::`scalar deleting destructor'

	private:
		enum {
			c_randomTableMask = 0x3ff,
			c_soundId0xbc5 = 0xbc5,
			c_soundId0xbc7 = 0xbc7,
			c_racerFlags0xd04Bit0 = 1 << 0,
			c_racerSearchIntervalMs = 4000,
			c_soundFrequencyUpdateMs = 500,
			c_randomFrequencyVariantCount = 100,
			c_trailFrameOffsetStep = 100,
			c_trailFrameOffsetEnd = 400,
		};

		void ClearFields();

		GolWorldEntity m_unk0x10;         // 0x10
		GolAnimatedEntity* m_unk0x38;     // 0x38
		GolModelEntity* m_unk0x3c;        // 0x3c
		LegoEventQueue* m_unk0x40;        // 0x40
		LegoEventQueue::Event* m_unk0x44; // 0x44
		CutsceneAnimation* m_unk0x48;     // 0x48
		CutsceneParticleRef* m_unk0x4c;   // 0x4c
		union {
			SpatialSoundInstance* m_unk0x50;               // 0x50
			RaceResourceManager::Resource* m_resource0x50; // 0x50
		};
		RaceState::Racer::SoundSource* m_unk0x54; // 0x54
		RaceState* m_unk0x58;                     // 0x58
		undefined4 m_unk0x5c;                     // 0x5c
		LegoS32 m_unk0x60;                        // 0x60
		LegoU32 m_unk0x64;                        // 0x64
		LegoFloat m_unk0x68;                      // 0x68
		LegoU32 m_unk0x6c;                        // 0x6c
		GolModelEntity m_unk0x70[3];              // 0x70
	};

	// VTABLE: LEGORACERS 0x004b44e0
	// SIZE 0x5c
	class LavaGeyserHazard : public Hazard {
	public:
		LavaGeyserHazard();
		~LavaGeyserHazard() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;  // vtable+0x00
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		LegoS32 ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048d850
		// HazardManager::LavaGeyserHazard::`scalar deleting destructor'

	private:
		enum {
			c_lavaPositionCount = 3,
			c_smokeCooldownMs = 800,
			c_eventCooldownMs = 400,
			c_eventId = 0x2b,
			c_soundId = 0xbba,
		};

		GolWorldEntity m_unk0x10;         // 0x10
		GolAnimatedEntity* m_unk0x38;     // 0x38
		LegoEventQueue* m_unk0x3c;        // 0x3c
		LegoEventQueue::Event* m_unk0x40; // 0x40
		CutsceneAnimation* m_unk0x44;     // 0x44
		union {
			SpatialSoundInstance* m_unk0x48;                // 0x48
			RaceResourceManager::Resource* m_soundResource; // 0x48
		};
		RaceState::Racer::SoundSource* m_unk0x4c; // 0x4c
		LegoU32 m_unk0x50;                        // 0x50
		LegoU32 m_unk0x54;                        // 0x54
		LegoU32 m_unk0x58;                        // 0x58
	};

	// VTABLE: LEGORACERS 0x004b447c
	// SIZE 0x3c
	class CodePuzzleHazard : public Hazard {
	public:
		CodePuzzleHazard();
		~CodePuzzleHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14
		void OnEventStart(LegoS32 p_unk0x04, void* p_unk0x08) override;  // vtable+0x28

		LegoS32 ClearFields();
		LegoS32 Reset();
		void ResetCodeModels();

		// SYNTHETIC: LEGORACERS 0x0048d290
		// HazardManager::CodePuzzleHazard::`scalar deleting destructor'

	private:
		enum {
			c_randomTableMask = 0x3ff,
			c_successFirstEvent = 0x12,
			c_successSecondEvent = 0x1c,
			c_goodInputEvent = 0x15,
			c_badInputEvent = 0x1e,
			c_correctCodeEvent = 0x1d,
			c_wrongCodeEvent = 0x14,
			c_firstCodeEvent = 0xc8,
			c_secondCodeEvent = 0xca,
			c_thirdCodeEvent = 0xcc,
			c_delayMs = 2500,
		};

		GolModelEntity* m_unk0x10;               // 0x10
		GolModelEntity* m_unk0x14;               // 0x14
		GolModelEntity* m_unk0x18;               // 0x18
		MabMaterialAnimationItem0x18* m_unk0x1c; // 0x1c
		MabMaterialAnimationItem0x18* m_unk0x20; // 0x20
		MabMaterialAnimationItem0x18* m_unk0x24; // 0x24
		MabMaterialAnimationItem0x8* m_unk0x28;  // 0x28
		LegoU32 m_unk0x2c;                       // 0x2c
		LegoU8 m_unk0x30;                        // 0x30
		LegoU8 m_unk0x31;                        // 0x31
		LegoU8 m_unk0x32;                        // 0x32
		LegoU8 m_unk0x33;                        // 0x33
		LegoU8 m_unk0x34;                        // 0x34
		LegoU8 m_unk0x35;                        // 0x35
		LegoU8 m_unk0x36;                        // 0x36
		undefined m_unk0x37;                     // 0x37
		LegoU32 m_unk0x38;                       // 0x38
	};

	// VTABLE: LEGORACERS 0x004b456c
	// SIZE 0x5c
	class RocketHazard : public Hazard {
	public:
		RocketHazard();
		~RocketHazard() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;  // vtable+0x00
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		LegoS32 ClearFields();
		LegoS32 Reset();
		void ShowOnModel();
		void ShowOffModel();

		// SYNTHETIC: LEGORACERS 0x0048e300
		// HazardManager::RocketHazard::`scalar deleting destructor'

	private:
		enum {
			c_field0x0e0Flags0xd04Bit0 = 1 << 0,
			c_modelDistanceCount = 3,
			c_eventId = 0x23,
		};

		GolWorldEntity m_unk0x10;         // 0x10
		LegoEventQueue* m_unk0x38;        // 0x38
		LegoEventQueue::Event* m_unk0x3c; // 0x3c
		GolModelEntity* m_unk0x40;        // 0x40
		GolModelEntity* m_unk0x44;        // 0x44
		ColliderRecord* m_unk0x48;        // 0x48
		LegoFloat m_unk0x4c[3];           // 0x4c
		LegoU32 m_unk0x58;                // 0x58
	};

	// VTABLE: LEGORACERS 0x004b4624
	// SIZE 0x20
	class SnowfallHazard : public Hazard {
	public:
		SnowfallHazard();
		~SnowfallHazard() override;
		void OnActivate(void* p_unk0x04) override;                                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override;                 // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                                    // vtable+0x14
		void UpdatePerRacer(GolCamera* p_unk0x04, RaceState::Racer* p_unk0x08) override; // vtable+0x18
		void ResetState() override;                                                      // vtable+0x24

		LegoS32 ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048e9d0
		// HazardManager::SnowfallHazard::`scalar deleting destructor'

	private:
		enum {
			c_snowResetMs = 1000,
			c_randomTableMask = 0x3ff,
		};

		CutsceneAnimation* m_unk0x10;   // 0x10
		CutsceneParticleRef* m_unk0x14; // 0x14
		LegoU32 m_unk0x18;              // 0x18
		LegoU32 m_unk0x1c;              // 0x1c
	};

	// VTABLE: LEGORACERS 0x004b45e0
	// SIZE 0x20
	class SmokeVentHazard : public Hazard {
	public:
		SmokeVentHazard();
		~SmokeVentHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048e6a0
		// HazardManager::SmokeVentHazard::`scalar deleting destructor'

	private:
		enum {
			c_randomTableMask = 0x3ff,
		};

		GolAnimatedEntity* m_unk0x10;   // 0x10
		CutsceneAnimation* m_unk0x14;   // 0x14
		CutsceneParticleRef* m_unk0x18; // 0x18
		LegoU32 m_unk0x1c;              // 0x1c
	};

	// VTABLE: LEGORACERS 0x004b4734
	// SIZE 0x17c
	class MovingObstacleHazard : public Hazard {
	public:
		MovingObstacleHazard();
		~MovingObstacleHazard() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;                  // vtable+0x00
		void OnActivate(void* p_unk0x04) override;                                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override;                 // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                                    // vtable+0x14
		void UpdatePerRacer(GolCamera* p_unk0x04, RaceState::Racer* p_unk0x08) override; // vtable+0x18
		void Draw(GolD3DRenderDevice* p_renderer) override;                              // vtable+0x1c

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048fec0
		// HazardManager::MovingObstacleHazard::`scalar deleting destructor'

	private:
		enum {
			c_flags0x178Bit0 = 1 << 0,
			c_flags0x178Bit1 = 1 << 1,
			c_soundId = 0xbbb,
			c_eventId0x14 = 0x14,
			c_eventId0x15 = 0x15,
		};

		GolWorldEntity m_unk0x10;                      // 0x10
		GolAnimatedEntity* m_unk0x38;                  // 0x38
		LegoEventQueue::Event* m_unk0x3c;              // 0x3c
		LegoEventQueue* m_unk0x40;                     // 0x40
		RaceSessionField0x27d4::Item::Decal m_unk0x44; // 0x44
		MaterialTable0x0c m_unk0x160;                  // 0x160
		GolCollidableEntity* m_unk0x16c;               // 0x16c
		union {
			RaceResourceManager::Resource* m_unk0x170; // 0x170
			SpatialSoundInstance* m_sound0x170;        // 0x170
		};
		RaceState::Racer::SoundSource* m_unk0x174; // 0x174
		LegoU8 m_unk0x178;                         // 0x178
		undefined m_unk0x179[0x17c - 0x179];       // 0x179
	};

	// VTABLE: LEGORACERS 0x004b46c8
	// SIZE 0x124
	class LauncherHazard : public Hazard {
	public:
		LauncherHazard();
		~LauncherHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14
		void Draw(GolD3DRenderDevice* p_renderer) override;              // vtable+0x1c
		void OnEventStart(LegoS32 p_unk0x04, void* p_unk0x08) override;  // vtable+0x28

		void ClearFields();
		void Reset();

		// SYNTHETIC: LEGORACERS 0x0048f740
		// HazardManager::LauncherHazard::`scalar deleting destructor'

	protected:
		GolWorldEntity m_unk0x10;       // 0x10
		PowerupProjectile m_unk0x38;    // 0x38
		GolVec3 m_unk0xe0;              // 0xe0
		GolVec3 m_unk0xec;              // 0xec
		GolVec3 m_unk0xf8;              // 0xf8
		LegoFloat m_unk0x104;           // 0x104
		LegoS32 m_unk0x108;             // 0x108
		TriggerWorld* m_unk0x10c;       // 0x10c
		RacePowerupManager* m_unk0x110; // 0x110
		GolBillboard* m_unk0x114;       // 0x114
		GolExport* m_unk0x118;          // 0x118
		void* m_unk0x11c;               // 0x11c
		void* m_unk0x120;               // 0x120
	};

	// VTABLE: LEGORACERS 0x004b4654
	// SIZE 0x30
	class TriggeredAnimationHazard : public Hazard {
	public:
		TriggeredAnimationHazard();
		~TriggeredAnimationHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14
		void Draw(GolD3DRenderDevice* p_renderer) override;              // vtable+0x1c
		void ResetState() override;                                      // vtable+0x24

		void ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048ed60
		// HazardManager::TriggeredAnimationHazard::`scalar deleting destructor'

	private:
		enum {
			c_entityCount = 4,
			c_modelDistanceCount = 3,
		};

		GolAnimatedEntity* m_unk0x10[c_entityCount]; // 0x10
		ColliderRecord* m_unk0x20;                   // 0x20
		GolVec3 m_unk0x24;                           // 0x24
	};

	// VTABLE: LEGORACERS 0x004b4684
	// SIZE 0x140
	class MultiLauncherHazard : public LauncherHazard {
	public:
		MultiLauncherHazard();
		~MultiLauncherHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		void Reset();

		// SYNTHETIC: LEGORACERS 0x0048f240
		// HazardManager::MultiLauncherHazard::`scalar deleting destructor'

	private:
		enum {
			c_randomTableMask = 0x3ff,
		};

		GolVec3* m_unk0x124; // 0x124
		LegoS32* m_unk0x128; // 0x128
		GolVec3* m_unk0x12c; // 0x12c
		LegoS32* m_unk0x130; // 0x130
		LegoU32 m_unk0x134;  // 0x134
		LegoU32 m_unk0x138;  // 0x138
		LegoU32 m_unk0x13c;  // 0x13c
	};

	// VTABLE: LEGORACERS 0x004b42f0
	// SIZE 0x204
	class RollingRockHazard : public Hazard {
	public:
		RollingRockHazard();
		~RollingRockHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		// SYNTHETIC: LEGORACERS 0x0048bb80
		// HazardManager::RollingRockHazard::`scalar deleting destructor'

	private:
		void Reset();

		RaceState::Racer::BoxBody m_unk0x10; // 0x10
		GolAnimatedEntity m_unk0x0f4;        // 0x0f4
		GolAnimatedEntity* m_unk0x1e8;       // 0x1e8
		LegoEventQueue* m_unk0x1ec;          // 0x1ec
		LegoEventQueue::Event* m_unk0x1f0;   // 0x1f0
		LegoFloat m_unk0x1f4;                // 0x1f4
		LegoFloat m_unk0x1f8;                // 0x1f8
		LegoFloat m_unk0x1fc;                // 0x1fc
		LegoU32 m_unk0x200;                  // 0x200
	};

	// VTABLE: LEGORACERS 0x004b4370
	// SIZE 0x44
	class CannonballRainHazard : public Hazard {
	public:
		CannonballRainHazard();
		~CannonballRainHazard() override;
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048c490
		// HazardManager::CannonballRainHazard::`scalar deleting destructor'

	private:
		void ClearFields();

		enum {
			c_randomTableMask = 0x3ff,
		};

		GolName m_unk0x10;             // 0x10
		GolVec3 m_unk0x18;             // 0x18
		GolVec3 m_unk0x24;             // 0x24
		LegoFloat m_unk0x30;           // 0x30
		RacePowerupManager* m_unk0x34; // 0x34
		GolAnimatedEntity* m_unk0x38;  // 0x38
		LegoU32 m_unk0x3c;             // 0x3c
		LegoU32 m_unk0x40;             // 0x40
	};

	// VTABLE: LEGORACERS 0x004b4518
	// SIZE 0x60
	class GrabberHazard : public Hazard {
	public:
		GrabberHazard();
		~GrabberHazard() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;  // vtable+0x00
		void OnActivate(void* p_unk0x04) override;                       // vtable+0x04
		void OnDeactivate(void* p_unk0x04) override;                     // vtable+0x08
		void Load(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void Update(undefined4 p_elapsedMs) override;                    // vtable+0x14

		LegoS32 ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048dd80
		// HazardManager::GrabberHazard::`scalar deleting destructor'

	private:
		enum {
			c_racerFlags0xd04Bit0 = 1 << 0,
			c_racerFlags0xd04Bit29 = 0x20000000,
			c_stateOne = 1,
			c_stateTwo = 2,
			c_timerMs = 1000,
			c_restoreTimerMs = 500,
		};

		void GetGrabPosition(GolVec3* p_position);
		void ReleaseRacer();

		GolWorldEntity m_unk0x10;         // 0x10
		GolAnimatedEntity* m_unk0x38;     // 0x38
		LegoEventQueue* m_unk0x3c;        // 0x3c
		LegoEventQueue::Event* m_unk0x40; // 0x40
		RaceState::Racer* m_unk0x44;      // 0x44
		LegoFloat m_unk0x48;              // 0x48
		LegoFloat m_unk0x4c;              // 0x4c
		LegoFloat m_unk0x50;              // 0x50
		LegoU32 m_unk0x54;                // 0x54
		LegoU32 m_unk0x58;                // 0x58
		LegoU32 m_unk0x5c;                // 0x5c
	};

	// SIZE 0x60
	class Context {
	public:
		class PositionProvider {
		public:
			virtual void VTable0x00() = 0;       // vtable+0x00
			virtual void GetPosition(void*) = 0; // vtable+0x04
		};

		RaceEventTable* GetEventTable() const { return m_eventTable; }
		LegoEventQueue* GetEventQueue() const { return m_eventQueue; }
		RaceState::Racer::SoundSource* GetSoundSource() const { return m_soundSource; }
		GolWorldDatabase* GetTrackDatabase() const { return m_trackDatabase; }
		GolWorldDatabase* GetSharedDatabase() const { return m_sharedDatabase; }
		CutsceneAnimation* GetParticleAnimation() const { return m_particleAnimation; }
		GolCollidableEntity* GetTrackCollidable() const { return m_trackCollidable; }
		GolExport* GetGolExport() const { return m_golExport; }
		GolD3DRenderDevice* GetRenderer() const { return m_renderer; }
		GolNameTable* GetColliderTable() const { return m_colliderTable; }
		RaceState* GetRaceState() const { return m_raceState; }
		TriggerWorld* GetSkyState() const { return m_skyState; }
		RacePowerupManager* GetPowerupManager() const { return m_powerupManager; }
		void* GetUnk0x3c() const { return m_unk0x3c; }
		LegoU32 GetMirror() const { return m_mirror; }
		PositionProvider* GetPositionProvider() const { return m_positionProvider; }

	private:
		friend class HazardManager;
		friend class RaceSession;

		LegoEventQueue* m_eventQueue;                 // 0x00
		void* m_unk0x04;                              // 0x04
		RaceState::Racer::SoundSource* m_soundSource; // 0x08
		RaceEventTable* m_eventTable;                 // 0x0c
		GolWorldDatabase* m_trackDatabase;            // 0x10
		GolWorldDatabase* m_sharedDatabase;           // 0x14
		GolWorldDatabase* m_unk0x18;                  // 0x18
		CutsceneAnimation* m_particleAnimation;       // 0x1c
		GolCollidableEntity* m_trackCollidable;       // 0x20
		GolExport* m_golExport;                       // 0x24
		GolD3DRenderDevice* m_renderer;               // 0x28
		GolNameTable* m_colliderTable;                // 0x2c
		RaceState* m_raceState;                       // 0x30
		TriggerWorld* m_skyState;                     // 0x34
		RacePowerupManager* m_powerupManager;         // 0x38
		void* m_unk0x3c;                              // 0x3c
		LegoU32 m_mirror;                             // 0x40
		undefined m_unk0x44[0x5c - 0x44];             // 0x44
		PositionProvider* m_positionProvider;         // 0x5c
	};

	HazardManager();
	~HazardManager();

	void NotifyEventStart(LegoS32 p_unk0x04, void* p_unk0x08);
	void NotifyEventEnd(LegoS32 p_unk0x04, void* p_unk0x08);
	void ForceActivate(LegoS32 p_unk0x04);
	void NotifyEventPair(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_unk0x0c);
	void DispatchEventStart(LegoS32 p_unk0x04, void* p_context);
	void DispatchEventEnd(LegoS32 p_unk0x04, void* p_context);
	void DispatchEventPair(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_context);
	void Update(undefined4 p_unk0x04);
	void UpdatePerRacer(GolCamera* p_unk0x04, RaceState::Racer* p_unk0x08);
	void Draw(GolD3DRenderDevice* p_renderer);
	void ResetAll();

private:
	friend class RaceSession;

	void Destroy();
	void LoadHazards(void* p_unk0x04, const LegoChar* p_name, LegoBool32 p_binary);

	LegoU32 m_count;    // 0x00
	Hazard** m_entries; // 0x04
};

#endif
