#ifndef RACESTATE_H
#define RACESTATE_H

#include "app/legoracers.h"
#include "decomp.h"
#include "goltxtparser.h"
#include "race/data/championdefinitionlist.h"
#include "race/racer/racer.h"
#include "race/racercontext.h"
#include "race/raceroster.h"
#include "race/racesetup.h"
#include "racer/chassismodeltable.h"
#include "racer/drivercosmetictable.h"
#include "types.h"

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
class MabMaterialFrame;
class GolMaterial;
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

	// SIZE 0x0c
	class RacerProgressEntry {
	public:
		Racer* m_racer;               // 0x00
		LegoFloat m_tieBreakDistance; // 0x04
		LegoFloat m_progress;         // 0x08
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
	Racer* GetCurrentRacer() { return m_roster.m_currentRacer; }
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
	RacerPhysics::RouteCursorInstance* GetSharedRouteCursor() { return &m_sharedRouteCursor; }

private:
	friend class RaceSession;

	enum {
		c_invalidTime = 0xffffffff,
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

	void CreateRacers(CreateRacersParams* p_params, RacerContext* p_context, LegoBool32 p_binary);
	void CreateRacer(
		LegoRacers::Context::PlayerSetupSlot* p_slot,
		RacerContext* p_context,
		LegoU32 p_racerIndex,
		undefined4 p_splitScreen
	);
	void LoadStartPositions(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
	void InitializeRacerVisuals(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
	void DrawRacersTransparent(GolD3DRenderDevice* p_renderer);
	void UpdateRacers(LegoU32 p_elapsedMs);
	void UpdateStandings();
	void UpdateShadows(GolCamera* p_camera);
	void StartRace();
	void DrawRacerEntities(GolRenderDevice* p_renderer, Racer* p_racer);
	void SetCurrentRacer(Racer* p_racer) { m_roster.m_currentRacer = p_racer; }
	void SetRubberBandBoost(LegoFloat p_boost) { m_setup.m_rubberBandBoost = p_boost; }
	void Reset();
	void Destroy();

	DriverCosmeticTable m_driverTable;                     // 0x000
	ChampionDefinitionList m_championList;                 // 0x080
	ChassisModelTable m_chassisTable;                      // 0x0b4
	RaceRoster m_roster;                                   // 0x0f0
	RaceSetup m_setup;                                     // 0x284
	RacerPhysics::RouteCursorInstance m_sharedRouteCursor; // 0x2a0
	Racer* m_playerRacers[2];                              // 0x318
};

#endif // RACESTATE_H
