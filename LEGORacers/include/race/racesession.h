#ifndef RACESESSION_H
#define RACESESSION_H

#include "app/golappeventhandler.h"
#include "app/legoracers.h"
#include "audio/soundnode.h"
#include "compat.h"
#include "core/gol.h"
#include "decomp.h"
#include "gdbmodelindexarray.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golnametable.h"
#include "golstring.h"
#include "golstringtable.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "input/inputeventqueue.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/checkpointgraph.h"
#include "race/hazardmanager.h"
#include "race/inputeventsink.h"
#include "race/loadingscreen.h"
#include "race/playercontrols.h"
#include "race/powerups/powerupprojectile.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racecameracontroller.h"
#include "race/racedecalmanager.h"
#include "race/racedialog.h"
#include "race/raceeventtable.h"
#include "race/raceforcefeedback.h"
#include "race/racehud.h"
#include "race/raceinputrouter.h"
#include "race/racer/racerouterecord.h"
#include "race/racer/racersoundsource.h"
#include "race/racercollisionworlds.h"
#include "race/racereset.h"
#include "race/raceresourcemanager.h"
#include "race/racertriggerlist.h"
#include "race/racesky.h"
#include "race/racesoundsource.h"
#include "race/racestate.h"
#include "race/racetimerlist.h"
#include "race/racetrailmanager.h"
#include "race/surfacetable.h"
#include "race/tgbtargetpointlist.h"
#include "race/triggerlist.h"
#include "race/triggerworld.h"
#include "scene/golbillboard.h"
#include "surface/color.h"
#include "types.h"
#include "util/decalgeometry.h"
#include "util/legoeventqueue.h"

class GolD3DRenderDevice;
class GolRenderDevice;
class CircuitStandings;
class TimeRaceManager;
class GolExport;
class GolCamera;
class GolCameraBase;
class GolFontBase;
class GolFontTable;
class GolFileParser;
class GolNameTable;
class GolWorldDatabase;
class GolWorldEntity;
class GolModelBase;
class GolSceneNode;
class GolBoundedEntity;
class GolCollidableEntity;
class GdbVertexArray;
class GolImageDefinitionList;
class GolImage;
class GolMaterial;
class MusicGroup;
class MusicInstance;
class SoundGroup;
class SoundManager;
class SpatialSoundInstance;
struct SoundNode;
class Win32GolApp;
class InputManager;
class DirectInputDevice;

// VTABLE: LEGORACERS 0x004b07f4
// SIZE 0x3368
class RaceSession : public GolAppEventHandler {
public:
	// VTABLE: LEGORACERS 0x004b0844
	// SIZE 0x1fc
	class RabTxtParser : public GolTxtParser {};

	RaceSession();
	void OnCloseRequested() override; // vtable+0x00
	void Initialize(
		LegoRacers::Context* p_context,
		const LegoChar* p_raceName,
		undefined4 p_mirror,
		TimeRaceManager* p_timeRaceManager
	);
	void Shutdown();
	void Run();
	virtual void Update();                     // vtable+0x30
	virtual void ClearViewport();              // vtable+0x34
	virtual void DrawScene(Racer*);            // vtable+0x38
	virtual void DrawTransparent();            // vtable+0x3c
	virtual void DrawHuds();                   // vtable+0x40
	virtual void OnKeyDown(LegoU32 p_keyCode); // vtable+0x44
	virtual void OnKeyUp(LegoU32 p_keyCode);   // vtable+0x48
	virtual ~RaceSession();                    // vtable+0x4c
	void SetStandings(CircuitStandings* p_standings) { m_standings = p_standings; }

	// SYNTHETIC: LEGORACERS 0x00431960
	// RaceSession::`scalar deleting destructor'

private:
	enum {
		c_keyQ = 0x10000010,
		c_keyLeftControl = 0x1000001d,
		c_keyLeftShift = 0x1000002a,
		c_keyEscape = 0x10000001,
		c_keyPrintScreen = 0x100000b7,
		c_keyPause = 0x100000c5,
		c_keySourceAbortMask = 0x30000000,
		c_maxScreenshotIndex = 9999,
		c_cheatFastForward = 1 << 8,
		c_updateStepMs = 40,
		c_overlayStringId = 0x2e,
		c_overlayDrawDelayMs = 250,
		c_overlayBottomPadding = 5,
		c_demoTextCycleMs = 1000,
		c_abortKeyQ = 1 << 0,
		c_abortKeyControl = 1 << 1,
		c_abortKeyShift = 1 << 2
	};

public:
	// SIZE 0x90

private:
	enum RabParserToken {
		e_world = GolFileParser::e_unknown0x27,
		e_cameraDirection = GolFileParser::e_unknown0x28,
		e_cameraPosition = GolFileParser::e_unknown0x29,
		e_collision = GolFileParser::e_unknown0x2b,
		e_events = GolFileParser::e_unknown0x2c,
		e_fonts = GolFileParser::e_unknown0x2d,
		e_trackModel = GolFileParser::e_unknown0x2e,
		e_images = GolFileParser::e_unknown0x2f,
		e_music = GolFileParser::e_unknown0x30,
		e_unused0x31 = GolFileParser::e_unknown0x31,
		e_unused0x32 = GolFileParser::e_unknown0x32,
		e_powerups = GolFileParser::e_unknown0x33,
		e_unusedFile = GolFileParser::e_unknown0x34,
		e_race = GolFileParser::e_unknown0x35,
		e_triggers = GolFileParser::e_unknown0x37,
		e_timers = GolFileParser::e_unknown0x38,
		e_racerTriggers = GolFileParser::e_unknown0x39,
		e_particleAnimations = GolFileParser::e_unknown0x3a,
		e_sharedModel = GolFileParser::e_unknown0x3b,
		e_sounds = GolFileParser::e_unknown0x3c,
		e_voices = GolFileParser::e_unknown0x3d,
		e_soundBank = GolFileParser::e_unknown0x3f,
		e_effectsModel = GolFileParser::e_unknown0x40,
		e_startPositions = GolFileParser::e_unknown0x41,
		e_sky = GolFileParser::e_unknown0x42,
		e_surfaces = GolFileParser::e_unknown0x43,
		e_hazards = GolFileParser::e_unknown0x44,
		e_materialAnimationModel = GolFileParser::e_unknown0x45,
		e_mapBounds = GolFileParser::e_unknown0x46,
		e_checkpoints = GolFileParser::e_unknown0x48,
		e_camera = GolFileParser::e_unknown0x49,
		e_targets = GolFileParser::e_unknown0x4a
	};

	void Reset();
	void AttachContext(LegoRacers::Context* p_context);
	void DetachContext();
	void InitializeSound();
	LegoU32 GetPlayerVoiceName(LegoU32 p_index, LegoChar* p_buffer);
	void DestroySound();
	void LoadStringsAndFonts();
	void DestroyStringsAndFonts();
	void LoadHudImages();
	void DestroyHudImages();
	void LoadDatabases(LegoBool32 p_mirror);
	void DestroyDatabases();
	void LoadRouteRecords(LegoBool32 p_mirror);
	void DestroyRouteRecords();
	void LoadRaceContent(LegoBool32 p_mirror);
	void DestroyRaceContent();
	void CreateCameras();
	void DestroyCameras();
	void StartIntroCamera();
	void InitializeInput();
	void DestroyInput();
	void PlayIntroMusic();
	void UpdateIntroState();
	void UpdateCountdownState();
	void UpdateRacingState();
	void UpdateFinishedState();
	void UpdateResultsState();
	void UpdateHuds();
	void Draw();
	void DrawRacerViewportForState1(Racer* p_racer);
	void DrawRacerViewportForState2(Racer* p_racer);
	void DrawRacerViewportForState3(Racer* p_racer);
	void DrawRacerViewportForState4(Racer* p_racer);
	void DrawRacerViewportForState5(Racer* p_racer);
	void DrawOverlaysForState1();
	void DrawOverlaysForState2();
	void DrawOverlaysForState3();
	void DrawOverlaysForState4();
	void DrawOverlaysForState5();
	void DrawPauseDialog();
	void DrawDemoText();
	void DrawLoadProgress(LegoFloat p_progress);
	void FlushOverlays();
	void BindSurfaceMaterials(LegoBool32 p_mirror);
	void BindCheckpointMaterials();
	void TakeScreenshot();
	void OpenPauseDialog();
	void ProcessPauseDialog();
	void RestartRace();

	LegoRacers::Context* m_context;                        // 0x04
	Win32GolApp* m_golApp;                                 // 0x08
	SoundManager* m_soundManager;                          // 0x0c
	GolExport* m_golExport;                                // 0x10
	GolD3DRenderDevice* m_renderer;                        // 0x14
	CircuitStandings* m_standings;                         // 0x18
	LegoChar m_displayName[0x05c - 0x1c];                  // 0x1c
	LegoChar m_trackModelName[0x069 - 0x5c];               // 0x5c
	LegoChar m_worldName[0x076 - 0x69];                    // 0x69
	LegoChar m_sharedModelName[0x083 - 0x76];              // 0x76
	LegoChar m_effectsModelName[0x090 - 0x83];             // 0x83
	LegoChar m_materialAnimationModelName[0x09d - 0x90];   // 0x90
	LegoChar m_triggerModelName[0x0aa - 0x9d];             // 0x9d
	LegoChar m_collisionWorldName[0x0b7 - 0xaa];           // 0xaa
	LegoChar m_triggerWorldName[0x0c4 - 0xb7];             // 0xb7
	LegoChar m_powerupFileName[0x0d1 - 0xc4];              // 0xc4
	LegoChar m_powerupDatabaseName[0x0de - 0xd1];          // 0xd1
	LegoChar m_turboDatabaseName[0x0eb - 0xde];            // 0xde
	LegoChar m_unusedFileName[0x0f8 - 0xeb];               // 0xeb
	LegoChar m_racerTriggerFileName[0x105 - 0xf8];         // 0xf8
	LegoChar m_eventFileName[0x112 - 0x105];               // 0x105
	LegoChar m_triggerFileName[0x11f - 0x112];             // 0x112
	LegoChar m_timerFileName[0x12c - 0x11f];               // 0x11f
	LegoChar m_particleAnimationName[0x139 - 0x12c];       // 0x12c
	LegoChar m_sharedParticleAnimationName[0x146 - 0x139]; // 0x139
	LegoChar m_soundFileName[0x153 - 0x146];               // 0x146
	LegoChar m_voiceFileName[0x160 - 0x153];               // 0x153
	LegoChar m_soundBankName[0x16d - 0x160];               // 0x160
	LegoChar m_musicFileName[0x17a - 0x16d];               // 0x16d
	LegoChar m_fontFileName[0x187 - 0x17a];                // 0x17a
	LegoChar m_imageFileName[0x194 - 0x187];               // 0x187
	LegoChar m_startPositionsFileName[0x1a1 - 0x194];      // 0x194
	LegoChar m_skyName[0x1ae - 0x1a1];                     // 0x1a1
	LegoChar m_surfaceFileName[0x1bb - 0x1ae];             // 0x1ae
	LegoChar m_hazardFileName[0x1c8 - 0x1bb];              // 0x1bb
	LegoChar m_checkpointFileName[0x1d5 - 0x1c8];          // 0x1c8
	LegoChar m_extraTriggerWorldName[0x1e2 - 0x1d5];       // 0x1d5
	LegoChar m_targetFileName[0x1ef - 0x1e2];              // 0x1e2
	LegoChar m_cameraName[0x1f8 - 0x1ef];                  // 0x1ef
	GolVec3 m_cameraStartPosition;                         // 0x1f8
	GolVec3 m_cameraStartDirection;                        // 0x204
	GolVec3 m_cameraStartUp;                               // 0x210
	InputManager* m_inputManager;                          // 0x21c
	InputEventQueue m_inputEvents;                         // 0x220
	RaceInputRouter m_inputRouter;                         // 0x23c
	PlayerControls m_playerControls[2];                    // 0x258
	RaceForceFeedback m_forceFeedback[2];                  // 0x340
	GolWorldDatabase* m_trackDatabase;                     // 0x390
	GolCollidableEntity* m_trackCollidable;                // 0x394
	GolWorldDatabase* m_sharedDatabase;                    // 0x398
	GolWorldDatabase* m_effectsDatabase;                   // 0x39c
	GolWorldDatabase* m_triggerDatabase;                   // 0x3a0
	GolWorldDatabase* m_materialAnimationDatabase;         // 0x3a4
	GolWorldDatabase* m_powerupTrackDatabase;              // 0x3a8
	GolCameraBase* m_trackCamera;                          // 0x3ac
	GolBoundedEntity* m_collisionWorld;                    // 0x3b0
	GolBoundedEntity* m_triggerWorldEntity;                // 0x3b4
	GolBoundedEntity* m_extraTriggerWorldEntity;           // 0x3b8
	RaceState m_raceState;                                 // 0x3bc
	RacePowerupManager m_powerupManager;                   // 0x6dc
	RacerTriggerList m_racerTriggers;                      // 0x2080
	RaceEventTable m_eventTable;                           // 0x2098
	TriggerList m_triggers;                                // 0x2128
	RaceTimerList m_timers;                                // 0x213c
	HazardManager m_hazardManager;                         // 0x2148
	CutsceneAnimation m_particleAnimation;                 // 0x2150
	CutsceneAnimation m_sharedParticleAnimation;           // 0x248c
	RaceTrailManager m_trailManager;                       // 0x27c8
	RaceDecalManager m_decalManager;                       // 0x27d4
	SurfaceTable m_surfaceTable;                           // 0x27e0
	CheckpointGraph m_checkpointGraph;                     // 0x27f4
	MenuAnimationList m_animationList;                     // 0x27fc
	TgbTargetPointList m_targetPoints;                     // 0x2804
	LoadingScreen m_loadingScreen;                         // 0x280c
	RaceHud m_huds[2];                                     // 0x283c
	LegoFloat m_mapMinX;                                   // 0x2abc
	LegoFloat m_mapMaxX;                                   // 0x2ac0
	LegoFloat m_mapMaxY;                                   // 0x2ac4
	LegoFloat m_mapMinY;                                   // 0x2ac8
	GolCamera* m_cameras[2];                               // 0x2acc
	RaceCameraController m_cameraControllers[2];           // 0x2ad4
	GolFontTable* m_fontTable;                             // 0x2d74
	GolFontBase* m_hudFont;                                // 0x2d78
	GolFontBase* m_loadingFont;                            // 0x2d7c
	GolString m_hudScratchString;                          // 0x2d80
	undefined2 m_hudScratchBuffer[0x100];                  // 0x2d8c
	GolImageDefinitionList* m_hudImages;                   // 0x2f8c
	RaceSkyState m_skyState;                               // 0x2f90
	RaceDialog m_dialog;                                   // 0x3058
	undefined4 m_pauseState;                               // 0x30c0
	RaceReset m_raceReset;                                 // 0x30c4
	GolStringTable m_stringTable;                          // 0x30f0
	RaceRouteRecord m_routeRecords[6];                     // 0x3104
	TriggerWorld m_triggerWorld;                           // 0x32b4
	RacerCollisionWorlds m_racerCollisionWorlds;           // 0x32c4
	RaceSoundSource m_soundSource;                         // 0x3300
	MusicGroup* m_musicGroup;                              // 0x3314
	SoundNode* m_listenerNodes[2];                         // 0x3318
	MusicInstance* m_music;                                // 0x3320
	LegoFloat m_musicVolume;                               // 0x3324
	undefined4 m_state;                                    // 0x3328
	LegoU32 m_elapsedMs;                                   // 0x332c
	LegoU32 m_finishedCount;                               // 0x3330
	LegoBool32 m_running;                                  // 0x3334
	LegoBool m_abortKeyMask;                               // 0x3338
	undefined m_unk0x3339[0x333c - 0x3339];                // 0x3339
	LegoU32 m_frameCount;                                  // 0x333c
	LegoU32 m_totalRunMs;                                  // 0x3340
	LegoFloat m_fps;                                       // 0x3344
	undefined m_lapCount;                                  // 0x3348
	undefined m_unk0x3349[0x334c - 0x3349];                // 0x3349
	LegoU32 m_demoTextMs;                                  // 0x334c
	LegoU32 m_demoMode;                                    // 0x3350
	undefined4 m_splitScreen;                              // 0x3354
	LegoU32 m_clearMode;                                   // 0x3358
	undefined4 m_returnToGarage;                           // 0x335c
	undefined4 m_pendingAction;                            // 0x3360
	TimeRaceManager* m_timeRaceManager;                    // 0x3364
};

#endif // RACESESSION_H
