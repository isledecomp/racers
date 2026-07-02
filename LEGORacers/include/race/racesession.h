#ifndef RACESESSION_H
#define RACESESSION_H

#include "app/golappeventhandler.h"
#include "app/legoracers.h"
#include "audio/soundnode.h"
#include "compat.h"
#include "core/gol.h"
#include "decomp.h"
#include "gdbmodelindexarray0xc.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golnametable.h"
#include "golstring.h"
#include "golstringtable.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "input/inputeventqueue.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/checkpointgraph.h"
#include "race/hazardmanager.h"
#include "race/powerups/powerupprojectile.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racecameracontroller.h"
#include "race/racedecalmanager.h"
#include "race/racedialog.h"
#include "race/raceeventtable.h"
#include "race/raceforcefeedback.h"
#include "race/racehud.h"
#include "race/racer/racerouterecord.h"
#include "race/raceresourcemanager.h"
#include "race/racesky.h"
#include "race/racestate.h"
#include "race/racetrailmanager.h"
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
class GdbVertexArray0xc;
class AwakeKite0x20;
class UtopianPan0xa4;
class DuskwindBananaRelic0x24;
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
	class RabTxtParser : public GolTxtParser {
		// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
		// RaceSession::RabTxtParser::`scalar deleting destructor'

		// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
		// RaceSession::RabTxtParser::~RabTxtParser
	};

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
	virtual void DrawScene(RaceState::Racer*); // vtable+0x38
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
	class PlayerControls;
	class RaceInputRouter;
	class TargetPointList;
	class RacerCollisionWorlds;

	// SIZE 0x04
	class InputEventSink : public InputDevice::Callback {
	public:
		InputDevice::Callback::ResultValue OnKeyDown(
			InputDevice* p_source,
			undefined4 p_input,
			undefined4 p_time
		) override = 0;
		InputDevice::Callback::ResultValue OnKeyUp(
			InputDevice* p_source,
			undefined4 p_input,
			undefined4 p_time
		) override = 0;
		InputDevice::Callback::ResultValue OnKeyRepeat(
			InputDevice* p_source,
			undefined4 p_input,
			undefined4 p_time
		) override;
	};

	// SIZE 0x74
	class PlayerControls {
	public:
		enum {
			c_inputSlotCount = 9,
			c_inputFlagSteerPositive = 1 << 0,
			c_inputFlagSteerNegative = 1 << 1,
			c_inputFlagThrottle = 1 << 2,
			c_inputFlagBrake = 1 << 3,
			c_inputFlagDrift = 1 << 7,
			c_inputFlagSteerMask = c_inputFlagSteerPositive | c_inputFlagSteerNegative,
			c_statePreStart = 1 << 0,
			c_stateAiControl = 1 << 1,
			c_stateFlagThrottle = 1 << 3,
			c_stateControlMask = c_statePreStart | c_stateAiControl,
			c_racerFlags0xd04Bit7 = 1 << 7,
		};

		// SIZE 0x70
		// VTABLE: LEGORACERS 0x004b075c
		class InputState : public InputEventSink {
		public:
			InputState();
			InputDevice::Callback::ResultValue OnKeyDown(
				InputDevice* p_source,
				undefined4 p_input,
				undefined4 p_time
			) override;
			InputDevice::Callback::ResultValue OnKeyUp(
				InputDevice* p_source,
				undefined4 p_input,
				undefined4 p_time
			) override;
			virtual ~InputState();

			// SYNTHETIC: LEGORACERS 0x00430870
			// RaceSession::PlayerControls::InputState::`scalar deleting destructor'

			void ReleaseAllInputs();

		private:
			friend class RaceSession;
			friend class PlayerControls;
			friend class RaceInputRouter;

			void Destroy();
			PlayerControls* Initialize(PlayerControls* p_parent, InputDevice::Callback* p_fallback);
			LegoU32 SetBinding(DirectInputDevice* p_source, undefined4 p_input, LegoU32 p_index);
			undefined4 GetBinding(DirectInputDevice** p_source, LegoU32 p_index);
			void AcquireDevices();
			void UnacquireDevices();

			PlayerControls* m_controls;                     // 0x004
			undefined4 m_inputs[c_inputSlotCount];          // 0x008
			DirectInputDevice* m_devices[c_inputSlotCount]; // 0x02c
			InputDevice::Callback* m_fallback;              // 0x050
			LegoBool32 m_enabled;                           // 0x054
			LegoU32 m_inputFlags;                           // 0x058
			LegoU32 m_stateFlags;                           // 0x05c
			LegoU32 m_boostWindowMs;                        // 0x060
			LegoU32 m_throttleHoldMs;                       // 0x064
			LegoFloat m_steering;                           // 0x068
			LegoBool32 m_analogThrottle;                    // 0x06c
		};

		PlayerControls();
		~PlayerControls();

	private:
		friend class RaceSession;
		friend class InputState;

		void Destroy();
		void Initialize(RaceState::Racer* p_racer, InputDevice::Callback* p_fallback);
		void Reset();
		void UpdateSteering(LegoU32 p_elapsedMs);
		void UpdateThrottle();
		void Update(LegoU32 p_elapsedMs);
		void OnSteerLeft(LegoBool32 p_enabled);
		void OnSteerRight(LegoBool32 p_enabled);
		void OnThrottle(LegoBool32 p_enabled);
		void OnBrake(LegoBool32 p_enabled);
		void OnUsePowerup(LegoBool32 p_enabled);
		void OnCycleCamera(LegoBool32 p_enabled);
		void OnCycleHud(LegoBool32 p_enabled);
		void OnDrift(LegoBool32 p_enabled);
		void OnLookBack(LegoBool32 p_enabled);
		void TryStartBoost();
		void EnterAiControl();
		void TrackThrottleHold();
		LegoS32 DetectAnalogDevice();

		RaceState::Racer* m_racer; // 0x000
		InputState m_input;        // 0x004
	};

	// SIZE 0x1c
	// VTABLE: LEGORACERS 0x004b0300
	class RaceInputRouter : public InputEventSink {
	public:
		RaceInputRouter();
		InputDevice::Callback::ResultValue OnKeyDown(
			InputDevice* p_source,
			undefined4 p_input,
			undefined4 p_time
		) override;
		InputDevice::Callback::ResultValue OnKeyUp(
			InputDevice* p_source,
			undefined4 p_input,
			undefined4 p_time
		) override;
		virtual ~RaceInputRouter();

		// SYNTHETIC: LEGORACERS 0x00427930
		// RaceSession::RaceInputRouter::`scalar deleting destructor'

		void Initialize(DirectInputDevice* p_source, InputDevice::Callback* p_fallback);
		void AddSink(PlayerControls::InputState* p_sink);
		void AcquireDevice();
		void UnacquireDevice();
		void ReleaseAllInputs();

	private:
		friend class RaceSession;

		void Reset();

		DirectInputDevice* m_device;            // 0x04
		PlayerControls::InputState* m_sinks[2]; // 0x08
		LegoU32 m_sinkCount;                    // 0x10
		InputDevice::Callback* m_fallback;      // 0x14
		LegoBool32 m_enabled;                   // 0x18
	};

	// SIZE 0x14
	class RaceSoundSource : public RaceState::Racer::SoundSource {
	public:
		RaceSoundSource();
		~RaceSoundSource();
		void DestroyGroups();
		void Initialize(SoundManager* p_soundManager);
		void LoadSfxBank(const LegoChar* p_name);
		void LoadVoiceBanks(const LegoChar* p_name1, const LegoChar* p_name2);
		void LoadAmbientBank(const LegoChar* p_name);
	};

	// VTABLE: LEGORACERS 0x004b1d54
	// SIZE 0x14
	class TriggerList {
	public:
		// VTABLE: LEGORACERS 0x004b1d64
		// SIZE 0x1fc
		class TrbTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::TriggerList::TrbTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::TriggerList::TrbTxtParser::~TrbTxtParser
		};

		class EntryParams;

		// VTABLE: LEGORACERS 0x004b1d40
		// SIZE 0x3c
		class Entry : public LegoEventQueue::Callback {
		public:
			Entry();
			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			virtual ~Entry();                                               // vtable+0x04
			virtual void Destroy();                                         // vtable+0x08
			virtual void Update(LegoU32 p_elapsedMs);                       // vtable+0x0c
			virtual void Reset();                                           // vtable+0x10

		protected:
			friend class TriggerList;
			friend class RacerTriggerList;

			enum {
				c_touchedThisFrame = 1 << 0,
				c_eventsActive = 1 << 1,
				c_mirror = 1 << 2,
			};

			void Initialize(const EntryParams* p_params);
			void CallBaseInitialize(const EntryParams* p_params) { Entry::Initialize(p_params); }
			void CallBaseVTable0x00(LegoEventQueue::CallbackData* p_data) { Entry::VTable0x00(p_data); }
			void CallBaseDestroy() { Entry::Destroy(); }
			void CallBaseUpdate(LegoU32 p_elapsedMs) { Entry::Update(p_elapsedMs); }
			void CallBaseReset() { Entry::Reset(); }

			GolWorldEntity m_body;          // 0x04
			LegoEventQueue::Event* m_event; // 0x2c
			RaceEventTable* m_eventTable;   // 0x30
			LegoS32 m_eventId;              // 0x34
			LegoU32 m_flags0x38;            // 0x38
		};

		// SIZE 0x1c
		class EntryParams {
		public:
			RaceEventTable* m_eventTable; // 0x00
			LegoS32 m_eventId;            // 0x04
			GolVec3 m_position;           // 0x08
			LegoFloat m_radius;           // 0x14
			LegoBool32 m_mirror;          // 0x18
		};

		TriggerList();
		virtual ~TriggerList();                      // vtable+0x00
		virtual void Destroy();                      // vtable+0x04
		virtual LegoU32 Update(LegoU32 p_elapsedMs); // vtable+0x08
		virtual LegoU32 Reset();                     // vtable+0x0c

		// SYNTHETIC: LEGORACERS 0x00464fc0
		// RaceSession::TriggerList::`scalar deleting destructor'

		// SYNTHETIC: LEGORACERS 0x00465180
		// RaceSession::TriggerList::Entry::`vector deleting destructor'

	protected:
		friend class RaceSession;

		void Load(
			LegoEventQueue* p_eventQueue,
			RaceEventTable* p_eventTable,
			const LegoChar* p_name,
			LegoBool32 p_binary,
			LegoBool32 p_mirror
		);

		GolFileParser* CreateParser(const LegoChar* p_name, LegoBool32 p_binary);
		void DestroyParser(GolFileParser* p_parser);
		void ParseTrigger(GolFileParser* p_parser, EntryParams* p_params);
		LegoEventQueue::Event* RegisterTrigger(Entry* p_entry, LegoBool32 p_projectiles);

		LegoEventQueue* m_eventQueue; // 0x04
		RaceEventTable* m_eventTable; // 0x08
		LegoU32 m_count;              // 0x0c
		Entry* m_entries;             // 0x10
	};

	// VTABLE: LEGORACERS 0x004b1c74
	// SIZE 0x18
	class RacerTriggerList : public TriggerList {
	public:
		class EntryParams;

		// VTABLE: LEGORACERS 0x004b1c5c
		// SIZE 0x58
		class Entry : public TriggerList::Entry {
		public:
			Entry();
			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			~Entry() override;                                              // vtable+0x04
			void Destroy() override;                                        // vtable+0x08
			void Update(LegoU32 p_elapsedMs) override;                      // vtable+0x0c
			void Reset() override;                                          // vtable+0x10

			void Initialize(const EntryParams* p_params);

			// SYNTHETIC: LEGORACERS 0x00464040
			// RaceSession::RacerTriggerList::Entry::`vector deleting destructor'

		private:
			enum {
				c_triggerOnProjectiles = 1 << 12,
				c_activatesCollisionWorld = 1 << 13,
				c_lapGated = 1 << 14
			};

			LegoU32 m_insideMask;                    // 0x3c
			LegoU32 m_previousInsideMask;            // 0x40
			RaceState* m_raceState;                  // 0x44
			RacePowerupManager* m_powerupManager;    // 0x48
			RacerCollisionWorlds* m_collisionWorlds; // 0x4c
			LegoU32 m_collisionWorldIndex;           // 0x50
			LegoU32 m_lapNumber;                     // 0x54
		};

		// SIZE 0x3c
		class EntryParams : public TriggerList::EntryParams {
		public:
			RaceState* m_raceState;                  // 0x1c
			RacePowerupManager* m_powerupManager;    // 0x20
			RacerCollisionWorlds* m_collisionWorlds; // 0x24
			LegoU32 m_lapNumber;                     // 0x28
			LegoBool32 m_triggerOnProjectiles;       // 0x2c
			LegoBool32 m_hasCollisionWorld;          // 0x30
			LegoBool32 m_hasLapNumber;               // 0x34
			LegoU32 m_collisionWorldIndex;           // 0x38
		};

		RacerTriggerList();
		~RacerTriggerList() override;                 // vtable+0x00
		void Destroy() override;                      // vtable+0x04
		LegoU32 Update(LegoU32 p_elapsedMs) override; // vtable+0x08
		LegoU32 Reset() override;                     // vtable+0x0c

		// SYNTHETIC: LEGORACERS 0x00463d50
		// RaceSession::RacerTriggerList::`scalar deleting destructor'

	private:
		friend class RaceSession;

		void Load(
			RaceState* p_raceState,
			RaceEventTable* p_eventTable,
			RacePowerupManager* p_powerupManager,
			GolWorldDatabase* p_worldDatabase,
			RacerCollisionWorlds* p_collisionWorlds,
			const LegoChar* p_name,
			LegoBool32 p_binary,
			LegoBool32 p_mirror
		);

		Entry* m_racerEntries; // 0x14
	};

	// SIZE 0x90

	// SIZE 0x0c
	class RaceTimerList {
	public:
		// VTABLE: LEGORACERS 0x004b1cc8
		// SIZE 0x1fc
		class TibTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::RaceTimerList::TibTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::RaceTimerList::TibTxtParser::~TibTxtParser
		};

		static LegoU32 FUN_00464700();

		// VTABLE: LEGORACERS 0x004b1cc0
		// SIZE 0x24
		class Resource : public LegoEventQueue::Callback {
		public:
			enum {
				c_active = 1 << 0,
				c_randomizeOnDuration = 1 << 1,
				c_randomizeOffDuration = 1 << 2,
				c_randomTableMask = 0x3ff,
			};

			Resource();
			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			virtual ~Resource();                                            // vtable+0x04

			void Initialize(
				LegoEventQueue* p_eventQueue,
				RaceEventTable* p_eventTable,
				LegoU32 p_onDurationMs,
				LegoU32 p_offDurationMs,
				LegoU32 p_delayMs,
				LegoS32 p_eventId,
				LegoU32 p_flags
			);
			void Reset();
			void Update(LegoU32 p_elapsedMs);
			LegoEventQueue::Event* Schedule(LegoU32 p_delayMs);

			// SYNTHETIC: LEGORACERS 0x00464d70
			// RaceSession::RaceTimerList::Resource::`vector deleting destructor'

		private:
			LegoEventQueue::Event* m_event; // 0x04
			RaceEventTable* m_eventTable;   // 0x08
			LegoEventQueue* m_eventQueue;   // 0x0c
			LegoU32 m_onDurationMs;         // 0x10
			LegoU32 m_offDurationMs;        // 0x14
			LegoU32 m_delayMs;              // 0x18
			LegoU32 m_flags;                // 0x1c
			LegoS32 m_eventId;              // 0x20
		};

		RaceTimerList();
		~RaceTimerList();
		LegoU32 Update(LegoU32 p_elapsedMs);

	private:
		friend class RaceSession;

		void Destroy();
		void Load(
			LegoEventQueue* p_eventQueue,
			RaceEventTable* p_eventTable,
			const LegoChar* p_name,
			LegoBool32 p_binary
		);

		RaceEventTable* m_eventTable; // 0x00
		LegoU32 m_count;              // 0x04
		Resource* m_timers;           // 0x08
	};

	// SIZE 0x14
	// VTABLE: LEGORACERS 0x004b0c04
	class SurfaceTable : public GolNameTable {
	public:
		// SIZE 0x5c
		class Entry {
		public:
			Entry();
			void Unload();
			void Load(GolFileParser* p_parser, LegoBool32 p_mirror);
			void Reset();

			const LegoChar* GetName() const { return m_name; }

		private:
			friend class SurfaceTable;

			enum {
				c_flagLoaded = 1 << 0,
				c_flagEnterEventId = 1 << 1,
				c_flagLeaveEventId = 1 << 2,
				c_flagTouchEventId = 1 << 3,
				c_flagUnk0x18 = 1 << 4,
				c_flagUnk0x1c = 1 << 5,
				c_flagSurfaceForce = 1 << 6,
				c_flagSurfaceSoundId = 1 << 7,
				c_flagUnk0x38 = 1 << 8,
				c_flagUnk0x3c = 1 << 9,
				c_flagWheelParticleName = 1 << 10,
				c_flagSupportThreshold = 1 << 11,
				c_flagFriction = 1 << 12,
				c_flagLateralGrip = 1 << 13,
				c_flagUnk0x54 = 1 << 14,
				c_flagRollingResistance = 1 << 15,
				c_flagBit16 = 1 << 16,
				c_flagBit17 = 1 << 17,
				c_flagBit18 = 1 << 18
			};

			GolName m_name;                // 0x00
			LegoU32 m_flags;               // 0x08
			LegoS32 m_enterEventId;        // 0x0c
			LegoS32 m_leaveEventId;        // 0x10
			LegoS32 m_touchEventId;        // 0x14
			LegoS32 m_unk0x18;             // 0x18
			GolVec3 m_unk0x1c;             // 0x1c
			GolVec3 m_surfaceForce;        // 0x28
			LegoS32 m_surfaceSoundId;      // 0x34
			LegoS32 m_unk0x38;             // 0x38
			LegoS32 m_unk0x3c;             // 0x3c
			GolName m_wheelParticleName;   // 0x40
			LegoFloat m_supportThreshold;  // 0x48
			LegoFloat m_friction;          // 0x4c
			LegoFloat m_lateralGrip;       // 0x50
			LegoFloat m_unk0x54;           // 0x54
			LegoFloat m_rollingResistance; // 0x58
		};

		// VTABLE: LEGORACERS 0x004b0c10
		// SIZE 0x1fc
		class TmbTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::SurfaceTable::TmbTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::SurfaceTable::TmbTxtParser::~TmbTxtParser
		};

		SurfaceTable();
		~SurfaceTable() override;
		void Clear() override;
		void Load(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);

		// SYNTHETIC: LEGORACERS 0x00443fc0
		// RaceSession::SurfaceTable::`scalar deleting destructor'

	private:
		LegoU32 m_count;  // 0x0c
		Entry* m_entries; // 0x10
	};

	// SIZE 0x30
	class LoadingScreen {
	public:
		// VTABLE: LEGORACERS 0x004b0698
		// SIZE 0x1fc
		class LsbTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::LoadingScreen::LsbTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::LoadingScreen::LsbTxtParser::~LsbTxtParser
		};

		LoadingScreen();
		~LoadingScreen();
		void Destroy();
		void Initialize(
			GolExport* p_golExport,
			GolD3DRenderDevice* p_renderer,
			GolStringTable* p_stringTable,
			GolFontBase* p_font,
			LegoBool32 p_binary
		);
		void SetProgress(LegoFloat p_progress);
		void Draw();

	private:
		GolD3DRenderDevice* m_renderer; // 0x00
		GolExport* m_golExport;         // 0x04
		AwakeKite0x20* m_images;        // 0x08
		UtopianPan0xa4* m_tickImage;    // 0x0c
		LegoFloat m_progress;           // 0x10
		LegoS32 m_dotCount;             // 0x14
		LegoS32* m_dotPositions;        // 0x18
		GolString m_text;               // 0x1c
		GolFontBase* m_font;            // 0x28
		LegoS32 m_textX;                // 0x2c
	};

	// SIZE 0x08
	class TargetPointList : public RacePowerupManager::TargetPointList {
	public:
		// VTABLE: LEGORACERS 0x004b1958
		// SIZE 0x1fc
		class TgbTxtParser : public GolTxtParser {
		public:
			// .tgb token meanings
			enum {
				e_target = 0x27,
				e_position = 0x28,
				e_index = 0x29,
			};
		};

		TargetPointList();
		~TargetPointList();

	private:
		friend class RaceSession;

		void Reset();
		void Load(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
	};

	// SIZE 0x2c
	class RaceReset {
	public:
		// SIZE 0x2c
		class Params {
		public:
			LegoRacers::Context* m_context;               // 0x00
			RaceState* m_raceState;                       // 0x04
			RacePowerupManager* m_powerupManager;         // 0x08
			HazardManager* m_hazardManager;               // 0x0c
			CutsceneAnimation* m_particleAnimation;       // 0x10
			CutsceneAnimation* m_sharedParticleAnimation; // 0x14
			TimeRaceManager* m_timeRaceManager;           // 0x18
			RacerTriggerList* m_racerTriggers;            // 0x1c
			TriggerList* m_triggers;                      // 0x20
			RacerCollisionWorlds* m_collisionWorlds;      // 0x24
			RaceEventTable* m_eventTable;                 // 0x28
		};

		RaceReset();
		~RaceReset();

	private:
		friend class RaceSession;

		void Reset();
		void Initialize(const Params* p_source);
		void FinishRace();
		void ResetRacers();

		LegoRacers::Context* m_context;               // 0x00
		RaceState* m_raceState;                       // 0x04
		RacePowerupManager* m_powerupManager;         // 0x08
		HazardManager* m_hazardManager;               // 0x0c
		CutsceneAnimation* m_particleAnimation;       // 0x10
		CutsceneAnimation* m_sharedParticleAnimation; // 0x14
		TimeRaceManager* m_timeRaceManager;           // 0x18
		RacerTriggerList* m_racerTriggers;            // 0x1c
		TriggerList* m_triggers;                      // 0x20
		RacerCollisionWorlds* m_collisionWorlds;      // 0x24
		RaceEventTable* m_eventTable;                 // 0x28
	};

	// VTABLE: LEGORACERS 0x004b1acc
	// SIZE 0x3c
	class RacerCollisionWorlds {
	public:
		RacerCollisionWorlds();
		virtual ~RacerCollisionWorlds(); // vtable+0x00
		void Update(LegoU32 p_elapsedMs);
		void ActivateWorld(RaceState::Racer* p_racer, LegoU32 p_worldIndex);
		LegoU32 Reset();

		// SYNTHETIC: LEGORACERS 0x0045e380
		// RaceSession::RacerCollisionWorlds::`scalar deleting destructor'

	private:
		friend class RaceSession;

		void Initialize(GolWorldDatabase* p_worldDatabase, RaceState* p_raceState);
		void Destroy();

		enum {
			c_racerCount = 6,
			c_maxElapsedChunk = 0xff,
			c_unk0x0a8Stride = 100,
			c_activationTtl = 150,
		};

		RaceState::Racer* m_racers[c_racerCount]; // 0x04
		GolWorldDatabase* m_worldDatabase;        // 0x1c
		LegoU8* m_ttl[c_racerCount];              // 0x20
		LegoU32 m_worldCount;                     // 0x38
	};

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
	void DrawRacerViewportForState1(RaceState::Racer* p_racer);
	void DrawRacerViewportForState2(RaceState::Racer* p_racer);
	void DrawRacerViewportForState3(RaceState::Racer* p_racer);
	void DrawRacerViewportForState4(RaceState::Racer* p_racer);
	void DrawRacerViewportForState5(RaceState::Racer* p_racer);
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
	TargetPointList m_targetPoints;                // 0x2804
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
	AwakeKite0x20* m_hudImages;                    // 0x2f8c
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
