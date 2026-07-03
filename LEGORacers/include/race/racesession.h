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
		c_keyboardKey0x10 = 0x10000010,
		c_keyboardKey0x1d = 0x1000001d,
		c_keyboardKey0x2a = 0x1000002a,
		c_keyboardKey0x01 = 0x10000001,
		c_keyboardKey0xb7 = 0x100000b7,
		c_keyboardKey0xc5 = 0x100000c5,
		c_keySourceAbortMask = 0x30000000,
		c_maxScreenshotIndex = 9999,
		c_contextFlag0x20Bit8 = 1 << 8,
		c_racerFlags0xd04Bit4 = 1 << 4,
		c_racerFlags0xd04Bit23 = 0x00800000,
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
		c_rabToken0x27 = GolFileParser::e_unknown0x27,
		c_rabToken0x28 = GolFileParser::e_unknown0x28,
		c_rabToken0x29 = GolFileParser::e_unknown0x29,
		c_rabToken0x2b = GolFileParser::e_unknown0x2b,
		c_rabToken0x2c = GolFileParser::e_unknown0x2c,
		c_rabToken0x2d = GolFileParser::e_unknown0x2d,
		c_rabToken0x2e = GolFileParser::e_unknown0x2e,
		c_rabToken0x2f = GolFileParser::e_unknown0x2f,
		c_rabToken0x30 = GolFileParser::e_unknown0x30,
		c_rabToken0x31 = GolFileParser::e_unknown0x31,
		c_rabToken0x32 = GolFileParser::e_unknown0x32,
		c_rabToken0x33 = GolFileParser::e_unknown0x33,
		c_rabToken0x34 = GolFileParser::e_unknown0x34,
		c_rabToken0x35 = GolFileParser::e_unknown0x35,
		c_rabToken0x37 = GolFileParser::e_unknown0x37,
		c_rabToken0x38 = GolFileParser::e_unknown0x38,
		c_rabToken0x39 = GolFileParser::e_unknown0x39,
		c_rabToken0x3a = GolFileParser::e_unknown0x3a,
		c_rabToken0x3b = GolFileParser::e_unknown0x3b,
		c_rabToken0x3c = GolFileParser::e_unknown0x3c,
		c_rabToken0x3d = GolFileParser::e_unknown0x3d,
		c_rabToken0x3f = GolFileParser::e_unknown0x3f,
		c_rabToken0x40 = GolFileParser::e_unknown0x40,
		c_rabToken0x41 = GolFileParser::e_unknown0x41,
		c_rabToken0x42 = GolFileParser::e_unknown0x42,
		c_rabToken0x43 = GolFileParser::e_unknown0x43,
		c_rabToken0x44 = GolFileParser::e_unknown0x44,
		c_rabToken0x45 = GolFileParser::e_unknown0x45,
		c_rabToken0x46 = GolFileParser::e_unknown0x46,
		c_rabToken0x48 = GolFileParser::e_unknown0x48,
		c_rabToken0x49 = GolFileParser::e_unknown0x49,
		c_rabToken0x4a = GolFileParser::e_unknown0x4a
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
	void DrawLoadProgress(LegoFloat p_unk0x04);
	void FlushOverlays();
	void BindSurfaceMaterials(LegoBool32 p_mirror);
	void BindCheckpointMaterials();
	void TakeScreenshot();
	void OpenPauseDialog();
	void ProcessPauseDialog();
	void RestartRace();

	LegoRacers::Context* m_context;                // 0x04
	Win32GolApp* m_golApp;                         // 0x08
	SoundManager* m_soundManager;                  // 0x0c
	GolExport* m_golExport;                        // 0x10
	GolD3DRenderDevice* m_renderer;                // 0x14
	CircuitStandings* m_standings;                 // 0x18
	LegoChar m_displayName;                        // 0x1c
	LegoChar m_unk0x1d[0x05c - 0x01d];             // 0x1d
	LegoChar m_trackModelName;                     // 0x5c
	LegoChar m_unk0x5d[0x069 - 0x05d];             // 0x5d
	LegoChar m_worldName;                          // 0x69
	LegoChar m_unk0x6a[0x076 - 0x06a];             // 0x6a
	LegoChar m_sharedModelName;                    // 0x76
	LegoChar m_unk0x77[0x083 - 0x077];             // 0x77
	LegoChar m_effectsModelName;                   // 0x83
	LegoChar m_unk0x84[0x090 - 0x084];             // 0x84
	LegoChar m_materialAnimationModelName;         // 0x90
	LegoChar m_unk0x91[0x09d - 0x091];             // 0x91
	LegoChar m_triggerModelName;                   // 0x9d
	LegoChar m_unk0x9e[0x0aa - 0x09e];             // 0x9e
	LegoChar m_collisionWorldName;                 // 0xaa
	LegoChar m_unk0xab[0x0b7 - 0x0ab];             // 0xab
	LegoChar m_triggerWorldName;                   // 0xb7
	LegoChar m_unk0xb8[0x0c4 - 0x0b8];             // 0xb8
	LegoChar m_powerupFileName;                    // 0xc4
	LegoChar m_unk0xc5[0x0d1 - 0x0c5];             // 0xc5
	LegoChar m_powerupDatabaseName;                // 0xd1
	LegoChar m_unk0xd2[0x0de - 0x0d2];             // 0xd2
	LegoChar m_turboDatabaseName;                  // 0xde
	LegoChar m_unk0xdf[0x0eb - 0x0df];             // 0xdf
	LegoChar m_unk0xeb;                            // 0xeb
	LegoChar m_unk0xec[0x0f8 - 0x0ec];             // 0xec
	LegoChar m_racerTriggerFileName;               // 0xf8
	LegoChar m_unk0xf9[0x105 - 0x0f9];             // 0xf9
	LegoChar m_eventFileName;                      // 0x105
	LegoChar m_unk0x106[0x112 - 0x106];            // 0x106
	LegoChar m_triggerFileName;                    // 0x112
	LegoChar m_unk0x113[0x11f - 0x113];            // 0x113
	LegoChar m_timerFileName;                      // 0x11f
	LegoChar m_unk0x120[0x12c - 0x120];            // 0x120
	LegoChar m_particleAnimationName;              // 0x12c
	LegoChar m_unk0x12d[0x139 - 0x12d];            // 0x12d
	LegoChar m_sharedParticleAnimationName;        // 0x139
	LegoChar m_unk0x13a[0x146 - 0x13a];            // 0x13a
	LegoChar m_soundFileName;                      // 0x146
	LegoChar m_unk0x147[0x153 - 0x147];            // 0x147
	LegoChar m_voiceFileName;                      // 0x153
	LegoChar m_unk0x154[0x160 - 0x154];            // 0x154
	LegoChar m_soundBankName;                      // 0x160
	LegoChar m_unk0x161[0x16d - 0x161];            // 0x161
	LegoChar m_musicFileName;                      // 0x16d
	LegoChar m_unk0x16e[0x17a - 0x16e];            // 0x16e
	LegoChar m_fontFileName;                       // 0x17a
	LegoChar m_unk0x17b[0x187 - 0x17b];            // 0x17b
	LegoChar m_imageFileName;                      // 0x187
	LegoChar m_unk0x188[0x194 - 0x188];            // 0x188
	LegoChar m_startPositionsFileName;             // 0x194
	LegoChar m_unk0x195[0x1a1 - 0x195];            // 0x195
	LegoChar m_skyName;                            // 0x1a1
	LegoChar m_unk0x1a2[0x1ae - 0x1a2];            // 0x1a2
	LegoChar m_surfaceFileName;                    // 0x1ae
	LegoChar m_unk0x1af[0x1bb - 0x1af];            // 0x1af
	LegoChar m_hazardFileName;                     // 0x1bb
	LegoChar m_unk0x1bc[0x1c8 - 0x1bc];            // 0x1bc
	LegoChar m_checkpointFileName;                 // 0x1c8
	LegoChar m_unk0x1c9[0x1d5 - 0x1c9];            // 0x1c9
	LegoChar m_extraTriggerWorldName;              // 0x1d5
	LegoChar m_unk0x1d6[0x1e2 - 0x1d6];            // 0x1d6
	LegoChar m_targetFileName;                     // 0x1e2
	LegoChar m_unk0x1e3[0x1ef - 0x1e3];            // 0x1e3
	LegoChar m_cameraName;                         // 0x1ef
	LegoChar m_unk0x1f0[0x1f8 - 0x1f0];            // 0x1f0
	GolVec3 m_cameraStartPosition;                 // 0x1f8
	GolVec3 m_cameraStartDirection;                // 0x204
	GolVec3 m_cameraStartUp;                       // 0x210
	InputManager* m_inputManager;                  // 0x21c
	InputEventQueue m_inputEvents;                 // 0x220
	RaceInputRouter m_inputRouter;                 // 0x23c
	PlayerControls m_playerControls[2];            // 0x258
	RaceForceFeedback m_forceFeedback[2];          // 0x340
	GolWorldDatabase* m_trackDatabase;             // 0x390
	GolCollidableEntity* m_trackCollidable;        // 0x394
	GolWorldDatabase* m_sharedDatabase;            // 0x398
	GolWorldDatabase* m_effectsDatabase;           // 0x39c
	GolWorldDatabase* m_triggerDatabase;           // 0x3a0
	GolWorldDatabase* m_materialAnimationDatabase; // 0x3a4
	GolWorldDatabase* m_unk0x3a8;                  // 0x3a8
	GolCameraBase* m_trackCamera;                  // 0x3ac
	GolBoundedEntity* m_collisionWorld;            // 0x3b0
	GolBoundedEntity* m_triggerWorldEntity;        // 0x3b4
	GolBoundedEntity* m_extraTriggerWorldEntity;   // 0x3b8
	RaceState m_raceState;                         // 0x3bc
	RacePowerupManager m_powerupManager;           // 0x6dc
	RacerTriggerList m_racerTriggers;              // 0x2080
	RaceEventTable m_eventTable;                   // 0x2098
	TriggerList m_triggers;                        // 0x2128
	RaceTimerList m_timers;                        // 0x213c
	HazardManager m_hazardManager;                 // 0x2148
	CutsceneAnimation m_particleAnimation;         // 0x2150
	CutsceneAnimation m_sharedParticleAnimation;   // 0x248c
	RaceTrailManager m_trailManager;               // 0x27c8
	RaceDecalManager m_decalManager;               // 0x27d4
	SurfaceTable m_surfaceTable;                   // 0x27e0
	CheckpointGraph m_checkpointGraph;             // 0x27f4
	MenuAnimationList m_animationList;             // 0x27fc
	TgbTargetPointList m_targetPoints;             // 0x2804
	LoadingScreen m_loadingScreen;                 // 0x280c
	RaceHud m_huds[2];                             // 0x283c
	LegoFloat m_mapMinX;                           // 0x2abc
	LegoFloat m_mapMaxX;                           // 0x2ac0
	LegoFloat m_mapMaxY;                           // 0x2ac4
	LegoFloat m_mapMinY;                           // 0x2ac8
	GolCamera* m_cameras[2];                       // 0x2acc
	RaceCameraController m_cameraControllers[2];   // 0x2ad4
	GolFontTable* m_fontTable;                     // 0x2d74
	GolFontBase* m_hudFont;                        // 0x2d78
	GolFontBase* m_loadingFont;                    // 0x2d7c
	GolString m_hudScratchString;                  // 0x2d80
	undefined2 m_hudScratchBuffer[0x100];          // 0x2d8c
	GolImageDefinitionList* m_hudImages;           // 0x2f8c
	RaceSkyState m_skyState;                       // 0x2f90
	RaceDialog m_dialog;                           // 0x3058
	undefined4 m_pauseState;                       // 0x30c0
	RaceReset m_raceReset;                         // 0x30c4
	GolStringTable m_stringTable;                  // 0x30f0
	RaceRouteRecord m_routeRecords[6];             // 0x3104
	TriggerWorld m_triggerWorld;                   // 0x32b4
	RacerCollisionWorlds m_racerCollisionWorlds;   // 0x32c4
	RaceSoundSource m_soundSource;                 // 0x3300
	MusicGroup* m_musicGroup;                      // 0x3314
	SoundNode* m_listenerNodes[2];                 // 0x3318
	MusicInstance* m_music;                        // 0x3320
	LegoFloat m_musicVolume;                       // 0x3324
	undefined4 m_state;                            // 0x3328
	LegoU32 m_elapsedMs;                           // 0x332c
	undefined4 m_finishedCount;                    // 0x3330
	undefined4 m_running;                          // 0x3334
	LegoBool m_abortKeyMask;                       // 0x3338
	undefined m_unk0x3339[0x333c - 0x3339];        // 0x3339
	LegoU32 m_frameCount;                          // 0x333c
	LegoU32 m_totalRunMs;                          // 0x3340
	LegoFloat m_fps;                               // 0x3344
	undefined m_lapCount;                          // 0x3348
	undefined m_unk0x3349[0x334c - 0x3349];        // 0x3349
	undefined4 m_demoTextMs;                       // 0x334c
	undefined4 m_demoMode;                         // 0x3350
	undefined4 m_splitScreen;                      // 0x3354
	undefined4 m_unk0x3358;                        // 0x3358
	undefined4 m_returnToGarage;                   // 0x335c
	undefined4 m_pendingAction;                    // 0x3360
	TimeRaceManager* m_timeRaceManager;            // 0x3364
};

#endif // RACESESSION_H
