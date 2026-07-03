#ifndef RACEEVENTTABLE_H
#define RACEEVENTTABLE_H

#include "decomp.h"
#include "golmath.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;
class GolWorldDatabase;
class MabMaterialAnimation;
class MabMaterialTrack;
struct MaterialTable;
class CutsceneAnimation;
struct CutsceneParticleRef;
class RaceSession;
class HazardManager;
class Racer;
class RaceSkyState;
class RacerSoundSource;
class TargetPointList;
class RaceEventResource;
class LapZoneResource;
class LookTargetResource;
class TimerResource;
class MaterialAnimationResource;
class PartAnimationResource;
class ModelDistanceResource;
class NodeTransformResource;
class SkyStateResource;
class ExternalForceResource;
class ColorTransformResource;
class SoundResource;
class ParticleResource;
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
	void StartEventsForRacer(undefined4 p_eventId, Racer* p_racer);
	void EndEventsForRacer(undefined4 p_eventId, Racer* p_racer);
	void FireEventsForRacer(undefined4 p_startId, undefined4 p_endId, Racer* p_racer);
	void ForceEvents(undefined4 p_eventId);

public:
	// VTABLE: LEGORACERS 0x004b1b4c
	// SIZE 0x1fc
	class EvbTxtParser : public GolTxtParser {
	public:
		// .evb token meanings (section + record level; field tokens are
		// section-scoped and live in each resource class)
		enum {
			e_event = 0x27,
			e_materialAnimation = 0x38,
			e_position = 0x3b,
			e_particle = 0x3d,
			e_direction = 0x3e,
			e_duration = 0x44,
			e_partAnimations = 0x28,
			e_materialAnimations = 0x29,
			e_sounds = 0x2a,
			e_entityName = 0x33,
			e_looping = 0x2d,
			e_active = 0x34,
			e_idle = 0x35,
			e_start = 0x36,
			e_end = 0x37,
			e_eventLinks = 0x39,
			e_noEnd = 0x3a,
			e_triggerOnEnd = 0x3c,
			e_particles = 0x3d,
			e_atEventPosition = 0x3f,
			e_sharedDatabase = 0x41,
			e_skyStates = 0x42,
			e_timers = 0x4b,
			e_colorTransforms = 0x4d,
			e_lapZones = 0x51,
			e_nodeTransforms = 0x52,
			e_modelDistances = 0x53,
			e_node = 0x54,
			e_lookTargets = 0x55,
			e_externalForces = 0x59,
		};
	};

	// SIZE 0x34
	struct Params {
		GolWorldDatabase* m_trackDatabase;             // 0x00
		GolWorldDatabase* m_sharedDatabase;            // 0x04
		GolWorldDatabase* m_triggerDatabase;           // 0x08
		GolWorldDatabase* m_materialAnimationDatabase; // 0x0c
		RacerSoundSource* m_soundSource;               // 0x10
		HazardManager* m_hazardManager;                // 0x14
		CutsceneAnimation* m_particleAnimation;        // 0x18
		CutsceneAnimation* m_sharedParticleAnimation;  // 0x1c
		RaceSkyState* m_skyState;                      // 0x20
		TargetPointList* m_targetPoints;               // 0x24
		const LegoChar* m_name;                        // 0x28
		LegoBool32 m_binary;                           // 0x2c
		LegoBool32 m_mirror;                           // 0x30
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
	void EndAllForRacer(Racer* p_racer);

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

	GolWorldDatabase* m_trackDatabase;               // 0x00
	GolWorldDatabase* m_sharedDatabase;              // 0x04
	GolWorldDatabase* m_triggerDatabase;             // 0x08
	GolWorldDatabase* m_materialAnimationDatabase;   // 0x0c
	RacerSoundSource* m_soundSource;                 // 0x10
	HazardManager* m_hazardManager;                  // 0x14
	CutsceneAnimation* m_particleAnimation;          // 0x18
	CutsceneAnimation* m_sharedParticleAnimation;    // 0x1c
	RaceSkyState* m_skyState;                        // 0x20
	TargetPointList* m_targetPoints;                 // 0x24
	LegoU32 m_soundCount;                            // 0x28
	LegoU32 m_partAnimationCount;                    // 0x2c
	LegoU32 m_materialAnimationCount;                // 0x30
	LegoU32 m_particleCount;                         // 0x34
	LegoU32 m_eventLinkCount;                        // 0x38
	LegoU32 m_skyStateCount;                         // 0x3c
	LegoU32 m_timerCount;                            // 0x40
	LegoU32 m_colorTransformCount;                   // 0x44
	LegoU32 m_lapZoneCount;                          // 0x48
	LegoU32 m_nodeTransformCount;                    // 0x4c
	LegoU32 m_modelDistanceCount;                    // 0x50
	LegoU32 m_lookTargetCount;                       // 0x54
	LegoU32 m_externalForceCount;                    // 0x58
	SoundResource* m_sounds;                         // 0x5c
	PartAnimationResource* m_partAnimations;         // 0x60
	MaterialAnimationResource* m_materialAnimations; // 0x64
	ParticleResource* m_particles;                   // 0x68
	EventLink* m_eventLinks;                         // 0x6c
	SkyStateResource* m_skyStates;                   // 0x70
	TimerResource* m_timers;                         // 0x74
	NodeTransformResource* m_nodeTransforms;         // 0x78
	ColorTransformResource* m_colorTransforms;       // 0x7c
	LapZoneResource* m_lapZones;                     // 0x80
	ModelDistanceResource* m_modelDistances;         // 0x84
	LookTargetResource* m_lookTargets;               // 0x88
	ExternalForceResource* m_externalForces;         // 0x8c
};

#endif // RACEEVENTTABLE_H
