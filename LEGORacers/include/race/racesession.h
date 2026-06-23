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
#include "race/cobalttrail0x140.h"
#include "race/racecameracontroller.h"
#include "race/raceeventdispatcher0x08.h"
#include "race/raceeventtable0x90.h"
#include "race/raceforcefeedback.h"
#include "race/racepowerupmanager.h"
#include "race/raceresourcemanager.h"
#include "race/racerouterecord.h"
#include "race/racesessionfield0x27d4.h"
#include "race/racesessionfield0x27f4.h"
#include "race/racesessionfield0x32b4.h"
#include "race/racesessionfield0x6dcfield0xa8.h"
#include "race/racestate.h"
#include "race/racetrailmanager.h"
#include "race/slatebridge0x68.h"
#include "scene/golbillboard.h"
#include "surface/color.h"
#include "types.h"
#include "util/legoeventqueue.h"
#include "util/marblepath0x114.h"

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
	void VTable0x00() override; // vtable+0x00
	LegoS32 Initialize(
		LegoRacers::Context* p_context,
		const LegoChar* p_raceName,
		undefined4 p_mirror,
		TimeRaceManager* p_timeRaceManager
	);
	void Shutdown();
	void Run();
	virtual void VTable0x30();                  // vtable+0x30
	virtual void VTable0x34();                  // vtable+0x34
	virtual void VTable0x38(RaceState::Racer*); // vtable+0x38
	virtual void VTable0x3c();                  // vtable+0x3c
	virtual void VTable0x40();                  // vtable+0x40
	virtual void VTable0x44(LegoU32 p_keyCode); // vtable+0x44
	virtual void VTable0x48(LegoU32 p_keyCode); // vtable+0x48
	virtual ~RaceSession();                     // vtable+0x4c
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
		c_unk0x334cResetMs = 1000,
		c_unk0x3338Bit0 = 1 << 0,
		c_unk0x3338Bit1 = 1 << 1,
		c_unk0x3338Bit2 = 1 << 2
	};

public:
	class Field0x258;
	class Field0x23c;
	class Field0x2098;
	class Field0x2f90;
	class Field0x2804;
	class Field0x32c4;

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
	class Field0x258 {
	public:
		enum {
			c_inputSlotCount = 9,
			c_inputFlagSteerPositive = 1 << 0,
			c_inputFlagSteerNegative = 1 << 1,
			c_inputFlagThrottle = 1 << 2,
			c_inputFlagBrake = 1 << 3,
			c_inputFlagDrift = 1 << 7,
			c_inputFlagSteerMask = c_inputFlagSteerPositive | c_inputFlagSteerNegative,
			c_stateFlagBit0 = 1 << 0,
			c_stateFlagBit1 = 1 << 1,
			c_stateFlagThrottle = 1 << 3,
			c_stateControlMask = c_stateFlagBit0 | c_stateFlagBit1,
			c_racerFlags0xd04Bit7 = 1 << 7,
		};

		// SIZE 0x70
		// VTABLE: LEGORACERS 0x004b075c
		class Field0x04 : public InputEventSink {
		public:
			Field0x04();
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
			virtual ~Field0x04();

			// SYNTHETIC: LEGORACERS 0x00430870
			// RaceSession::Field0x258::Field0x04::`scalar deleting destructor'

			void FUN_00430c20();

		private:
			friend class RaceSession;
			friend class Field0x258;
			friend class Field0x23c;

			void FUN_004308a0();
			Field0x258* FUN_004308d0(Field0x258* p_parent, InputDevice::Callback* p_fallback);
			LegoU32 FUN_004308f0(DirectInputDevice* p_source, undefined4 p_input, LegoU32 p_index);
			undefined4 FUN_00430910(DirectInputDevice** p_source, LegoU32 p_index);
			void FUN_00430930();
			void FUN_00430980();

			Field0x258* m_unk0x004;                          // 0x004
			undefined4 m_unk0x008[c_inputSlotCount];         // 0x008
			DirectInputDevice* m_unk0x02c[c_inputSlotCount]; // 0x02c
			InputDevice::Callback* m_unk0x050;               // 0x050
			LegoBool32 m_unk0x054;                           // 0x054
			LegoU32 m_unk0x058;                              // 0x058
			LegoU32 m_unk0x05c;                              // 0x05c
			LegoU32 m_unk0x060;                              // 0x060
			LegoU32 m_unk0x064;                              // 0x064
			LegoFloat m_unk0x068;                            // 0x068
			LegoBool32 m_unk0x06c;                           // 0x06c
		};

		Field0x258();
		~Field0x258();

	private:
		friend class RaceSession;
		friend class Field0x04;

		void FUN_004300a0();
		void FUN_004300d0(RaceState::Racer* p_racer, InputDevice::Callback* p_fallback);
		void FUN_00430100();
		void FUN_00430120(LegoU32 p_elapsedMs);
		void FUN_00430390();
		void FUN_00430530(LegoU32 p_elapsedMs);
		void FUN_00430570(LegoBool32 p_enabled);
		void FUN_00430590(LegoBool32 p_enabled);
		void FUN_004305b0(LegoBool32 p_enabled);
		void FUN_004305e0(LegoBool32 p_enabled);
		void FUN_00430620(LegoBool32 p_enabled);
		void FUN_00430650(LegoBool32 p_enabled);
		void FUN_00430680(LegoBool32 p_enabled);
		void FUN_004306b0(LegoBool32 p_enabled);
		void FUN_004306d0(LegoBool32 p_enabled);
		void FUN_00430710();
		void FUN_00430760();
		void FUN_00430790();
		LegoS32 FUN_004307f0();

		RaceState::Racer* m_unk0x000; // 0x000
		Field0x04 m_unk0x004;         // 0x004
	};

	// SIZE 0x1c
	// VTABLE: LEGORACERS 0x004b0300
	class Field0x23c : public InputEventSink {
	public:
		Field0x23c();
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
		virtual ~Field0x23c();

		// SYNTHETIC: LEGORACERS 0x00427930
		// RaceSession::Field0x23c::`scalar deleting destructor'

		void FUN_00427980(DirectInputDevice* p_source, InputDevice::Callback* p_fallback);
		void FUN_004279a0(Field0x258::Field0x04* p_sink);
		void FUN_004279c0();
		void FUN_004279f0();
		void FUN_00427b40();

	private:
		friend class RaceSession;

		void FUN_00427960();

		DirectInputDevice* m_unk0x04;        // 0x04
		Field0x258::Field0x04* m_unk0x08[2]; // 0x08
		LegoU32 m_unk0x10;                   // 0x10
		InputDevice::Callback* m_unk0x14;    // 0x14
		LegoBool32 m_unk0x18;                // 0x18
	};

	// SIZE 0x14
	class Field0x3300 : public RaceState::Racer::Field0x004 {
	public:
		Field0x3300();
		~Field0x3300();
		void FUN_00443a80();
		void FUN_00443ac0(SoundManager* p_soundManager);
		void FUN_00443b00(const LegoChar* p_name);
		void FUN_00443b10(const LegoChar* p_name1, const LegoChar* p_name2);
		void FUN_00443b40(const LegoChar* p_name);
	};

	// VTABLE: LEGORACERS 0x004b1d54
	// SIZE 0x14
	class Field0x2128 {
	public:
		// VTABLE: LEGORACERS 0x004b1d64
		// SIZE 0x1fc
		class TrbTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::Field0x2128::TrbTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::Field0x2128::TrbTxtParser::~TrbTxtParser
		};

		class EntryParams;

		// VTABLE: LEGORACERS 0x004b1d40
		// SIZE 0x3c
		class Entry : public LegoEventQueue::Callback {
		public:
			Entry();
			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			virtual ~Entry();                                               // vtable+0x04
			virtual void VTable0x08();                                      // vtable+0x08
			virtual void VTable0x0c(LegoU32 p_elapsedMs);                   // vtable+0x0c
			virtual void VTable0x10();                                      // vtable+0x10

		protected:
			friend class Field0x2128;
			friend class Field0x2080;

			enum {
				c_flags0x38Bit0 = 1 << 0,
				c_flags0x38Bit1 = 1 << 1,
				c_flags0x38Bit2 = 1 << 2,
			};

			void FUN_00464e80(const EntryParams* p_params);
			void CallBaseVTable0x00(LegoEventQueue::CallbackData* p_data) { Entry::VTable0x00(p_data); }
			void CallBaseVTable0x08() { Entry::VTable0x08(); }
			void CallBaseVTable0x0c(LegoU32 p_elapsedMs) { Entry::VTable0x0c(p_elapsedMs); }
			void CallBaseVTable0x10() { Entry::VTable0x10(); }

			GolWorldEntity m_unk0x04;         // 0x04
			LegoEventQueue::Event* m_unk0x2c; // 0x2c
			RaceEventTable0x90* m_unk0x30;    // 0x30
			LegoS32 m_unk0x34;                // 0x34
			LegoU32 m_flags0x38;              // 0x38
		};

		// SIZE 0x1c
		class EntryParams {
		public:
			RaceEventTable0x90* m_unk0x00; // 0x00
			LegoS32 m_unk0x04;             // 0x04
			GolVec3 m_unk0x08;             // 0x08
			LegoFloat m_unk0x14;           // 0x14
			LegoBool32 m_unk0x18;          // 0x18
		};

		Field0x2128();
		virtual ~Field0x2128();                 // vtable+0x00
		virtual void Destroy();                 // vtable+0x04
		virtual LegoU32 VTable0x08(undefined4); // vtable+0x08
		virtual LegoU32 VTable0x0c();           // vtable+0x0c

		// SYNTHETIC: LEGORACERS 0x00464fc0
		// RaceSession::Field0x2128::`scalar deleting destructor'

		// SYNTHETIC: LEGORACERS 0x00465180
		// RaceSession::Field0x2128::Entry::`vector deleting destructor'

	protected:
		friend class RaceSession;

		void FUN_00464ff0(
			LegoEventQueue* p_eventQueue,
			RaceEventTable0x90* p_unk0x08,
			const LegoChar* p_name,
			LegoBool32 p_binary,
			LegoBool32 p_mirror
		);

		GolFileParser* FUN_00465210(const LegoChar* p_name, LegoBool32 p_binary);
		void FUN_00465330(GolFileParser* p_parser);
		void FUN_00465350(GolFileParser* p_parser, EntryParams* p_params);
		LegoEventQueue::Event* FUN_004653f0(Entry* p_entry, LegoBool32 p_unk0x0c);

		LegoEventQueue* m_eventQueue;  // 0x04
		RaceEventTable0x90* m_unk0x08; // 0x08
		LegoU32 m_count;               // 0x0c
		Entry* m_entries;              // 0x10
	};

	// VTABLE: LEGORACERS 0x004b1c74
	// SIZE 0x18
	class Field0x2080 : public Field0x2128 {
	public:
		class EntryParams;

		// VTABLE: LEGORACERS 0x004b1c5c
		// SIZE 0x58
		class Entry : public Field0x2128::Entry {
		public:
			Entry();
			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			~Entry() override;                                              // vtable+0x04
			void VTable0x08() override;                                     // vtable+0x08
			void VTable0x0c(LegoU32 p_elapsedMs) override;                  // vtable+0x0c
			void VTable0x10() override;                                     // vtable+0x10

			void FUN_00463b60(const EntryParams* p_params);

			// SYNTHETIC: LEGORACERS 0x00464040
			// RaceSession::Field0x2080::Entry::`vector deleting destructor'

		private:
			enum {
				c_flags0x38Bit0x1000 = 1 << 12,
				c_flags0x38Bit0x2000 = 1 << 13,
				c_flags0x38Bit0x4000 = 1 << 14
			};

			LegoU32 m_unk0x3c;             // 0x3c
			LegoU32 m_unk0x40;             // 0x40
			RaceState* m_raceState;        // 0x44
			RacePowerupManager* m_unk0x48; // 0x48
			Field0x32c4* m_unk0x4c;        // 0x4c
			LegoU32 m_unk0x50;             // 0x50
			LegoU32 m_unk0x54;             // 0x54
		};

		// SIZE 0x3c
		class EntryParams : public Field0x2128::EntryParams {
		public:
			RaceState* m_raceState;        // 0x1c
			RacePowerupManager* m_unk0x20; // 0x20
			Field0x32c4* m_unk0x24;        // 0x24
			LegoU32 m_unk0x28;             // 0x28
			LegoBool32 m_unk0x2c;          // 0x2c
			LegoBool32 m_unk0x30;          // 0x30
			LegoBool32 m_unk0x34;          // 0x34
			LegoU32 m_unk0x38;             // 0x38
		};

		Field0x2080();
		~Field0x2080() override;                 // vtable+0x00
		void Destroy() override;                 // vtable+0x04
		LegoU32 VTable0x08(undefined4) override; // vtable+0x08
		LegoU32 VTable0x0c() override;           // vtable+0x0c

		// SYNTHETIC: LEGORACERS 0x00463d50
		// RaceSession::Field0x2080::`scalar deleting destructor'

	private:
		friend class RaceSession;

		void FUN_00463dc0(
			RaceState* p_raceState,
			RaceEventTable0x90* p_eventTable,
			RacePowerupManager* p_field0x6dc,
			GolWorldDatabase* p_worldDatabase,
			Field0x32c4* p_field0x32c4,
			const LegoChar* p_name,
			LegoBool32 p_binary,
			LegoBool32 p_mirror
		);

		Entry* m_unk0x14; // 0x14
	};

	// SIZE 0x90
	class Field0x2098 {
	public:
		// VTABLE: LEGORACERS 0x004b1b4c
		// SIZE 0x1fc
		class EvbTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::Field0x2098::EvbTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::Field0x2098::EvbTxtParser::~EvbTxtParser
		};

		// SIZE 0x34
		struct Params {
			GolWorldDatabase* m_unk0x00;             // 0x00
			GolWorldDatabase* m_unk0x04;             // 0x04
			GolWorldDatabase* m_unk0x08;             // 0x08
			GolWorldDatabase* m_unk0x0c;             // 0x0c
			RaceState::Racer::Field0x004* m_unk0x10; // 0x10
			RaceEventDispatcher0x08* m_unk0x14;      // 0x14
			CutsceneAnimation* m_unk0x18;            // 0x18
			CutsceneAnimation* m_unk0x1c;            // 0x1c
			Field0x2f90* m_unk0x20;                  // 0x20
			Field0x2804* m_unk0x24;                  // 0x24
			const LegoChar* m_name;                  // 0x28
			LegoBool32 m_binary;                     // 0x2c
			LegoBool32 m_mirror;                     // 0x30
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
			virtual void VTable0x00(RaceState::Racer* p_racer); // vtable+0x00
			virtual void VTable0x04(GolVec3* p_unk0x04);        // vtable+0x04
			virtual void VTable0x08(RaceState::Racer* p_racer); // vtable+0x08
			virtual void VTable0x0c();                          // vtable+0x0c
			virtual ~Resource();                                // vtable+0x10
			virtual void VTable0x14(LegoU32 p_elapsedMs);       // vtable+0x14

			void FUN_0045eee0(RaceState::Racer* p_racer);
			void Reset();
			void FUN_0045edd0(LegoU32 p_unk0x04, LegoU32 p_unk0x08);
			void SetState0x18(LegoU32 p_state) { m_state0x18 = p_state; }

			// SYNTHETIC: LEGORACERS 0x0045ed70
			// RaceSession::Field0x2098::Resource::`scalar deleting destructor'

		protected:
			RaceEventTable0x90* m_unk0x04;    // 0x04
			LegoS32 m_eventIds[3];            // 0x08
			undefined4 m_unk0x14;             // 0x14
			LegoU32 m_state0x18;              // 0x18
			LegoU8 m_flags0x1c;               // 0x1c
			undefined m_unk0x1d[0x20 - 0x1d]; // 0x1d
		};

		// VTABLE: LEGORACERS 0x004b1ca4
		// SIZE 0x24
		class Resource0x24 : public Resource {
		public:
			// SIZE 0x18
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				undefined4 m_unk0x14;             // 0x14
			};

			Resource0x24();
			~Resource0x24() override;
			void VTable0x00(RaceState::Racer* p_racer) override;
			void VTable0x08(RaceState::Racer* p_racer) override;

			void FUN_00464610(InitParams* p_params);
			void FUN_00464660();

			// SYNTHETIC: LEGORACERS 0x00461b40
			// RaceSession::Field0x2098::Resource0x24::`vector deleting destructor'

		private:
			undefined4 m_unk0x20; // 0x20
		};

		// VTABLE: LEGORACERS 0x004b1ad4
		// SIZE 0x2c
		class Resource0x2c : public Resource {
		public:
			// SIZE 0x20
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				GolVec3 m_unk0x14;                // 0x14
			};

			Resource0x2c();
			~Resource0x2c() override;
			void VTable0x00(RaceState::Racer* p_racer) override;
			void VTable0x08(RaceState::Racer* p_racer) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_004513d0(undefined4 p_unk0x04);
			void FUN_0045e650(InitParams* p_params);
			void FUN_0045e6b0();

			// SYNTHETIC: LEGORACERS 0x00461610
			// RaceSession::Field0x2098::Resource0x2c::`vector deleting destructor'

		private:
			GolVec3 m_unk0x20; // 0x20
		};

		// VTABLE: LEGORACERS 0x004b1af0
		// SIZE 0x30
		class Resource0x30 : public Resource {
		public:
			// SIZE 0x20
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				LegoS32 m_unk0x14;                // 0x14
				LegoU32 m_unk0x18;                // 0x18
				LegoBool32 m_unk0x1c;             // 0x1c
			};

			Resource0x30();
			~Resource0x30() override;
			void VTable0x04(GolVec3* p_unk0x04) override;
			void VTable0x0c() override;
			void VTable0x14(LegoU32 p_elapsedMs) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_004513d0(undefined4 p_unk0x04);
			void FUN_0045e7d0();
			void FUN_0045e7f0(InitParams* p_params);
			void FUN_0045e860();

			// SYNTHETIC: LEGORACERS 0x00460cb0
			// RaceSession::Field0x2098::Resource0x30::`vector deleting destructor'

		private:
			LegoS32 m_unk0x20;                // 0x20
			LegoU32 m_unk0x24;                // 0x24
			LegoU32 m_unk0x28;                // 0x28
			LegoU8 m_flags0x2c;               // 0x2c
			undefined m_unk0x2d[0x30 - 0x2d]; // 0x2d
		};

		// VTABLE: LEGORACERS 0x004b1be4
		// SIZE 0x34
		class Resource0x34 : public Resource {
		public:
			// SIZE 0x38
			struct InitParams {
				undefined4 m_unk0x00;                // 0x00
				LegoS32 m_eventIds[3];               // 0x04
				RaceEventTable0x90* m_eventTable;    // 0x10
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

			Resource0x34();
			~Resource0x34() override;
			void VTable0x04(GolVec3* p_unk0x04) override;
			void VTable0x0c() override;
			void VTable0x14(LegoU32 p_elapsedMs) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_00463120(InitParams* p_params);
			void FUN_004631e0();

			// SYNTHETIC: LEGORACERS 0x0045fe50
			// RaceSession::Field0x2098::Resource0x34::`vector deleting destructor'

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
		class AnimatedPartResource0x34 : public Resource {
		public:
			// SIZE 0x3c
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				GolAnimatedEntity* m_unk0x14;     // 0x14
				LegoS32 m_unk0x18;                // 0x18
				LegoS32 m_unk0x1c;                // 0x1c
				LegoS32 m_unk0x20;                // 0x20
				LegoS32 m_unk0x24;                // 0x24
				LegoBool32 m_unk0x28;             // 0x28
				LegoBool32 m_unk0x2c;             // 0x2c
				LegoBool32 m_unk0x30;             // 0x30
				LegoBool32 m_unk0x34;             // 0x34
				LegoBool32 m_unk0x38;             // 0x38
			};

			AnimatedPartResource0x34();
			~AnimatedPartResource0x34() override;
			void VTable0x04(GolVec3* p_unk0x04) override;
			void VTable0x0c() override;
			void VTable0x14(LegoU32 p_elapsedMs) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_00463330(InitParams* p_params);
			void FUN_004633e0();

			// SYNTHETIC: LEGORACERS 0x0045f9d0
			// RaceSession::Field0x2098::AnimatedPartResource0x34::`vector deleting destructor'

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
		class ModelDistanceResource0x34 : public Resource {
		public:
			// SIZE 0x24
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				GolModelEntity* m_unk0x14;        // 0x14
				LegoBool32 m_unk0x18;             // 0x18
				LegoBool32 m_unk0x1c;             // 0x1c
				LegoBool32 m_unk0x20;             // 0x20
			};

			ModelDistanceResource0x34();
			~ModelDistanceResource0x34() override;
			void VTable0x04(GolVec3*) override;
			void VTable0x0c() override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_004636e0();
			void FUN_00463700(InitParams* p_params);
			void FUN_004637a0();

			// SYNTHETIC: LEGORACERS 0x004613d0
			// RaceSession::Field0x2098::ModelDistanceResource0x34::`vector deleting destructor'

		private:
			GolModelEntity* m_unk0x20;     // 0x20
			LegoFloat m_modelDistances[3]; // 0x24
			LegoBool32 m_unk0x30;          // 0x30
		};

		// VTABLE: LEGORACERS 0x004b1c3c
		// SIZE 0x2c
		class NodeTransformResource0x2c : public Resource {
		public:
			// SIZE 0x24
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				GolBoundedEntity* m_unk0x14;      // 0x14
				GolModelEntity* m_unk0x18;        // 0x18
				LegoU32 m_unk0x1c;                // 0x1c
				LegoBool32 m_unk0x20;             // 0x20
			};

			NodeTransformResource0x2c();
			~NodeTransformResource0x2c() override;
			void VTable0x04(GolVec3*) override;
			void VTable0x0c() override;
			void VTable0x14(LegoU32 p_elapsedMs) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_004638f0();
			void FUN_00463900(InitParams* p_params);
			void FUN_00463970();

			// SYNTHETIC: LEGORACERS 0x00461010
			// RaceSession::Field0x2098::NodeTransformResource0x2c::`vector deleting destructor'

		private:
			GolBoundedEntity* m_unk0x20; // 0x20
			GolModelEntity* m_unk0x24;   // 0x24
			LegoU32 m_unk0x28;           // 0x28
		};

		// VTABLE: LEGORACERS 0x004b1aac
		// SIZE 0x34
		class SkyStateResource0x34 : public Resource {
		public:
			// SIZE 0x2c
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				Field0x2f90* m_unk0x14;           // 0x14
				GolName m_unk0x18;                // 0x18
				LegoU32 m_unk0x20;                // 0x20
				LegoBool32 m_unk0x24;             // 0x24
				LegoU8 m_flags0x28;               // 0x28
				undefined m_unk0x29[0x2c - 0x29]; // 0x29
			};

			SkyStateResource0x34();
			~SkyStateResource0x34() override;
			void VTable0x04(GolVec3* p_unk0x04) override;
			void VTable0x0c() override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_0045e1f0();
			void FUN_0045e200(InitParams* p_params);
			void FUN_0045e280();

			// SYNTHETIC: LEGORACERS 0x004606c0
			// RaceSession::Field0x2098::SkyStateResource0x34::`vector deleting destructor'

		private:
			enum {
				c_flags0x30Bit0 = 1 << 0,
				c_flags0x30Bit1 = 1 << 1,
				c_flags0x30Bit2 = 1 << 2,
				c_flags0x30Bit3 = 1 << 3
			};

			Field0x2f90* m_unk0x20; // 0x20
			GolName m_unk0x24;      // 0x24
			LegoU32 m_unk0x2c;      // 0x2c
			LegoU8 m_flags0x30;     // 0x30
			undefined m_unk0x31[0x34 - 0x31];
		};

		// VTABLE: LEGORACERS 0x004b1bc8
		// SIZE 0x38
		class Resource0x38 : public Resource {
		public:
			// SIZE 0x30
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				GolVec3 m_unk0x14;                // 0x14
				LegoU32 m_unk0x20;                // 0x20
				LegoS32 m_unk0x24;                // 0x24
				LegoBool32 m_unk0x28;             // 0x28
				LegoBool32 m_unk0x2c;             // 0x2c
			};

			Resource0x38();
			~Resource0x38() override;
			void VTable0x00(RaceState::Racer* p_racer) override;
			void VTable0x08(RaceState::Racer* p_racer) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_00462f10();
			void FUN_00462f40(InitParams* p_params);
			void FUN_00462fc0();

			// SYNTHETIC: LEGORACERS 0x00461930
			// RaceSession::Field0x2098::Resource0x38::`vector deleting destructor'

		private:
			enum {
				c_flags0x34Bit0 = 1 << 0
			};

			GolVec3 m_unk0x20;                // 0x20
			LegoU32 m_unk0x2c;                // 0x2c
			LegoS32 m_unk0x30;                // 0x30
			LegoU8 m_flags0x34;               // 0x34
			undefined m_unk0x35[0x38 - 0x35]; // 0x35
		};

		// VTABLE: LEGORACERS 0x004b1de0
		// SIZE 0x48
		class Resource0x48 : public Resource {
		public:
			// SIZE 0x3c
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				LegoU32 m_flags0x14;              // 0x14
				ColorTransform0x20 m_unk0x18;     // 0x18
				GolWorldEntity* m_unk0x38;        // 0x38
			};

			Resource0x48();
			~Resource0x48() override;
			void VTable0x00(RaceState::Racer* p_racer) override;
			void VTable0x08(RaceState::Racer* p_racer) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_00465560();
			void FUN_00465570(InitParams* p_params);
			void FUN_004655e0();

			// SYNTHETIC: LEGORACERS 0x00460a70
			// RaceSession::Field0x2098::Resource0x48::`vector deleting destructor'

		private:
			enum {
				c_flags0x20Bit1 = 1 << 1,
			};

			LegoU32 m_flags0x20;          // 0x20
			ColorTransform0x20 m_unk0x24; // 0x24
			GolWorldEntity* m_unk0x44;    // 0x44
		};

		// VTABLE: LEGORACERS 0x004b1c84
		// SIZE 0x5c
		class Resource0x5c : public Resource {
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
				undefined4 m_unk0x00;                    // 0x00
				undefined4 m_unk0x04;                    // 0x04
				RaceState::Racer::Field0x004* m_unk0x08; // 0x08
				GolVec3 m_unk0x0c;                       // 0x0c
				LegoU32 m_unk0x18;                       // 0x18
				LegoU32 m_unk0x1c;                       // 0x1c
				LegoFloat m_unk0x20;                     // 0x20
				LegoFloat m_unk0x24;                     // 0x24
				LegoFloat m_unk0x28;                     // 0x28
				LegoFloat m_unk0x2c;                     // 0x2c
				LegoFloat m_unk0x30;                     // 0x30
				LegoBool32 m_unk0x34;                    // 0x34
				LegoBool32 m_unk0x38;                    // 0x38
				LegoBool32 m_unk0x3c;                    // 0x3c
				LegoBool32 m_unk0x40;                    // 0x40
				GolModelEntity* m_unk0x44;               // 0x44
				LegoU32 m_unk0x48;                       // 0x48
			};

			Resource0x5c();
			~Resource0x5c() override;
			void VTable0x04(GolVec3* p_unk0x04) override;
			void VTable0x0c() override;
			void VTable0x14(LegoU32 p_elapsedMs) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_004641b0(InitParams* p_params);
			void FUN_00464290();
			void FUN_004644b0();

			// SYNTHETIC: LEGORACERS 0x0045f600
			// RaceSession::Field0x2098::Resource0x5c::`vector deleting destructor'

		private:
			union {
				SpatialSoundInstance* m_unk0x20;          // 0x20
				RaceResourceManager::Resource* m_res0x20; // 0x20
			};
			RaceState::Racer::Field0x004* m_unk0x24; // 0x24
			GolModelEntity* m_unk0x28;               // 0x28
			LegoU32 m_unk0x2c;                       // 0x2c
			SoundVector m_unk0x30;                   // 0x30
			LegoU32 m_unk0x3c;                       // 0x3c
			LegoU32 m_unk0x40;                       // 0x40
			LegoFloat m_unk0x44;                     // 0x44
			LegoFloat m_unk0x48;                     // 0x48
			LegoFloat m_unk0x4c;                     // 0x4c
			LegoFloat m_unk0x50;                     // 0x50
			LegoU8 m_unk0x54;                        // 0x54
			undefined m_unk0x55[0x58 - 0x55];        // 0x55
			LegoU32 m_unk0x58;                       // 0x58
		};

		// VTABLE: LEGORACERS 0x004b1b0c
		// SIZE 0x64
		class Resource0x64 : public Resource {
		public:
			// SIZE 0x5c
			struct InitParams {
				undefined4 m_unk0x00;             // 0x00
				LegoS32 m_eventIds[3];            // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				CutsceneAnimation* m_unk0x14;     // 0x14
				CutsceneAnimation* m_unk0x18;     // 0x18
				GolModelEntity* m_unk0x1c;        // 0x1c
				LegoU32 m_unk0x20;                // 0x20
				GolName m_unk0x24;                // 0x24
				GolVec3 m_unk0x2c;                // 0x2c
				GolVec3 m_unk0x38;                // 0x38
				GolVec3 m_unk0x44;                // 0x44
				undefined4 m_unk0x50;             // 0x50
				undefined4 m_unk0x54;             // 0x54
				undefined4 m_unk0x58;             // 0x58
			};

			Resource0x64();
			~Resource0x64() override;
			void VTable0x04(GolVec3* p_unk0x04) override;
			void VTable0x0c() override;
			void VTable0x14(LegoU32 p_elapsedMs) override;
			virtual LegoU32 VTable0x18(); // vtable+0x18

			void FUN_004513d0(undefined4 p_unk0x04);
			void FUN_0045e9c0();
			void FUN_0045ea00(InitParams* p_params);
			void FUN_0045ead0();

			// SYNTHETIC: LEGORACERS 0x004602c0
			// RaceSession::Field0x2098::Resource0x64::`vector deleting destructor'

		private:
			CutsceneAnimation* m_unk0x20;   // 0x20
			CutsceneAnimation* m_unk0x24;   // 0x24
			GolName m_unk0x28;              // 0x28
			CutsceneParticleRef* m_unk0x30; // 0x30
			GolModelEntity* m_unk0x34;      // 0x34
			LegoU32 m_unk0x38;              // 0x38
			GolVec3 m_unk0x3c;              // 0x3c
			GolVec3 m_unk0x48;              // 0x48
			GolVec3 m_unk0x54;              // 0x54
			LegoU32 m_unk0x60;              // 0x60
		};

		// SIZE 0x08
		struct Field0x6c {
			LegoS32 m_unk0x00; // 0x00
			LegoS32 m_unk0x04; // 0x04
		};

		Field0x2098();
		~Field0x2098();
		RaceEventTable0x90* GetEventTable() { return &m_eventTable; }
		void FUN_00461cc0(LegoU32 p_elapsedMs);
		void FUN_00462c60();
		void FUN_00462da0(RaceState::Racer* p_racer);

	private:
		friend class RaceSession;

		void Destroy();
		void FUN_0045efa0(Params* p_params);
		void FUN_0045f220(GolFileParser* p_parser, LegoBool32 p_mirror);
		void FUN_0045f660(GolFileParser* p_parser);
		void FUN_0045fa30(GolFileParser* p_parser);
		void FUN_0045feb0(GolFileParser* p_parser, LegoBool32 p_mirror);
		void FUN_00460320(GolFileParser* p_parser);
		void FUN_00460430(GolFileParser* p_parser);
		void FUN_00460720(GolFileParser* p_parser);
		void FUN_00460ad0(GolFileParser* p_parser);
		void FUN_00460d10(GolFileParser* p_parser);
		void FUN_00461070(GolFileParser* p_parser);
		void FUN_00461430(GolFileParser* p_parser, LegoBool32 p_mirror);
		void FUN_00461670(GolFileParser* p_parser, LegoBool32 p_mirror);
		void FUN_00461990(GolFileParser* p_parser);

		union {
			RaceEventTable0x90 m_eventTable; // 0x00
			struct {
				GolWorldDatabase* m_unk0x00;             // 0x00
				GolWorldDatabase* m_unk0x04;             // 0x04
				GolWorldDatabase* m_unk0x08;             // 0x08
				GolWorldDatabase* m_unk0x0c;             // 0x0c
				RaceState::Racer::Field0x004* m_unk0x10; // 0x10
				RaceEventDispatcher0x08* m_unk0x14;      // 0x14
				CutsceneAnimation* m_unk0x18;            // 0x18
				CutsceneAnimation* m_unk0x1c;            // 0x1c
				Field0x2f90* m_unk0x20;                  // 0x20
				Field0x2804* m_unk0x24;                  // 0x24
				LegoU32 m_unk0x28;                       // 0x28
				LegoU32 m_unk0x2c;                       // 0x2c
				LegoU32 m_unk0x30;                       // 0x30
				LegoU32 m_unk0x34;                       // 0x34
				LegoU32 m_unk0x38;                       // 0x38
				LegoU32 m_unk0x3c;                       // 0x3c
				LegoU32 m_unk0x40;                       // 0x40
				LegoU32 m_unk0x44;                       // 0x44
				LegoU32 m_unk0x48;                       // 0x48
				LegoU32 m_unk0x4c;                       // 0x4c
				LegoU32 m_unk0x50;                       // 0x50
				LegoU32 m_unk0x54;                       // 0x54
				LegoU32 m_unk0x58;                       // 0x58
				Resource0x5c* m_unk0x5c;                 // 0x5c
				AnimatedPartResource0x34* m_unk0x60;     // 0x60
				Resource0x34* m_unk0x64;                 // 0x64
				Resource0x64* m_unk0x68;                 // 0x68
				Field0x6c* m_unk0x6c;                    // 0x6c
				SkyStateResource0x34* m_unk0x70;         // 0x70
				Resource0x30* m_unk0x74;                 // 0x74
				NodeTransformResource0x2c* m_unk0x78;    // 0x78
				Resource0x48* m_unk0x7c;                 // 0x7c
				Resource0x24* m_unk0x80;                 // 0x80
				ModelDistanceResource0x34* m_unk0x84;    // 0x84
				Resource0x2c* m_unk0x88;                 // 0x88
				Resource0x38* m_unk0x8c;                 // 0x8c
			};
		};
	};

	// SIZE 0x0c
	class Field0x213c {
	public:
		// VTABLE: LEGORACERS 0x004b1cc8
		// SIZE 0x1fc
		class TibTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::Field0x213c::TibTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::Field0x213c::TibTxtParser::~TibTxtParser
		};

		static LegoU32 FUN_00464700();

		// VTABLE: LEGORACERS 0x004b1cc0
		// SIZE 0x24
		class Resource : public LegoEventQueue::Callback {
		public:
			enum {
				c_flags0x1cBit0 = 1 << 0,
				c_flags0x1cBit1 = 1 << 1,
				c_flags0x1cBit2 = 1 << 2,
				c_randomTableMask = 0x3ff,
			};

			Resource();
			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			virtual ~Resource();                                            // vtable+0x04

			void FUN_00464750(
				LegoEventQueue* p_eventQueue,
				RaceEventTable0x90* p_eventTable,
				LegoU32 p_unk0x0c,
				LegoU32 p_unk0x10,
				LegoU32 p_unk0x14,
				LegoS32 p_unk0x18,
				LegoU32 p_flags
			);
			void Reset();
			void FUN_00464830(LegoU32 p_elapsedMs);
			LegoEventQueue::Event* FUN_00464a40(LegoU32 p_unk0x04);

			// SYNTHETIC: LEGORACERS 0x00464d70
			// RaceSession::Field0x213c::Resource::`vector deleting destructor'

		private:
			LegoEventQueue::Event* m_unk0x04; // 0x04
			RaceEventTable0x90* m_unk0x08;    // 0x08
			LegoEventQueue* m_unk0x0c;        // 0x0c
			LegoU32 m_unk0x10;                // 0x10
			LegoU32 m_unk0x14;                // 0x14
			LegoU32 m_unk0x18;                // 0x18
			LegoU32 m_unk0x1c;                // 0x1c
			LegoS32 m_unk0x20;                // 0x20
		};

		Field0x213c();
		~Field0x213c();
		LegoU32 FUN_00464dd0(LegoU32 p_elapsedMs);

	private:
		friend class RaceSession;

		void Destroy();
		void FUN_00464aa0(
			LegoEventQueue* p_eventQueue,
			RaceEventTable0x90* p_eventTable,
			const LegoChar* p_name,
			LegoBool32 p_binary
		);

		RaceEventTable0x90* m_unk0x00; // 0x00
		LegoU32 m_unk0x04;             // 0x04
		Resource* m_unk0x08;           // 0x08
	};

	// SIZE 0x14
	// VTABLE: LEGORACERS 0x004b0c04
	class Field0x27e0 : public GolNameTable {
	public:
		// SIZE 0x5c
		class Entry {
		public:
			Entry();
			void Reset();
			void FUN_00443cf0(GolFileParser* p_parser, LegoBool32 p_mirror);
			void FUN_00443f90();

			const LegoChar* GetName() const { return m_name; }

		private:
			friend class Field0x27e0;

			enum {
				c_flagLoaded = 1 << 0,
				c_flagUnk0x0c = 1 << 1,
				c_flagUnk0x10 = 1 << 2,
				c_flagUnk0x14 = 1 << 3,
				c_flagUnk0x18 = 1 << 4,
				c_flagUnk0x1c = 1 << 5,
				c_flagUnk0x28 = 1 << 6,
				c_flagUnk0x34 = 1 << 7,
				c_flagUnk0x38 = 1 << 8,
				c_flagUnk0x3c = 1 << 9,
				c_flagUnk0x40 = 1 << 10,
				c_flagUnk0x48 = 1 << 11,
				c_flagUnk0x4c = 1 << 12,
				c_flagUnk0x50 = 1 << 13,
				c_flagUnk0x54 = 1 << 14,
				c_flagUnk0x58 = 1 << 15,
				c_flagBit16 = 1 << 16,
				c_flagBit17 = 1 << 17,
				c_flagBit18 = 1 << 18
			};

			GolName m_name;      // 0x00
			LegoU32 m_flags;     // 0x08
			LegoS32 m_unk0x0c;   // 0x0c
			LegoS32 m_unk0x10;   // 0x10
			LegoS32 m_unk0x14;   // 0x14
			LegoS32 m_unk0x18;   // 0x18
			GolVec3 m_unk0x1c;   // 0x1c
			GolVec3 m_unk0x28;   // 0x28
			LegoS32 m_unk0x34;   // 0x34
			LegoS32 m_unk0x38;   // 0x38
			LegoS32 m_unk0x3c;   // 0x3c
			GolName m_unk0x40;   // 0x40
			LegoFloat m_unk0x48; // 0x48
			LegoFloat m_unk0x4c; // 0x4c
			LegoFloat m_unk0x50; // 0x50
			LegoFloat m_unk0x54; // 0x54
			LegoFloat m_unk0x58; // 0x58
		};

		// VTABLE: LEGORACERS 0x004b0c10
		// SIZE 0x1fc
		class TmbTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::Field0x27e0::TmbTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::Field0x27e0::TmbTxtParser::~TmbTxtParser
		};

		Field0x27e0();
		~Field0x27e0() override;
		void Clear() override;
		void FUN_00444030(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);

		// SYNTHETIC: LEGORACERS 0x00443fc0
		// RaceSession::Field0x27e0::`scalar deleting destructor'

	private:
		LegoU32 m_count;  // 0x0c
		Entry* m_entries; // 0x10
	};

	// SIZE 0x30
	class Field0x280c {
	public:
		// VTABLE: LEGORACERS 0x004b0698
		// SIZE 0x1fc
		class LsbTxtParser : public GolTxtParser {
			// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
			// RaceSession::Field0x280c::LsbTxtParser::`scalar deleting destructor'

			// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
			// RaceSession::Field0x280c::LsbTxtParser::~LsbTxtParser
		};

		Field0x280c();
		~Field0x280c();
		void FUN_0042f430();
		void FUN_0042f480(
			GolExport* p_golExport,
			GolD3DRenderDevice* p_renderer,
			GolStringTable* p_stringTable,
			GolFontBase* p_font,
			LegoBool32 p_binary
		);
		void FUN_0042f790(LegoFloat p_unk0x04);
		void FUN_0042f7a0();

	private:
		GolD3DRenderDevice* m_renderer; // 0x00
		GolExport* m_unk0x04;           // 0x04
		AwakeKite0x20* m_unk0x08;       // 0x08
		UtopianPan0xa4* m_unk0x0c;      // 0x0c
		LegoFloat m_unk0x10;            // 0x10
		LegoS32 m_unk0x14;              // 0x14
		LegoS32* m_unk0x18;             // 0x18
		GolString m_unk0x1c;            // 0x1c
		GolFontBase* m_unk0x28;         // 0x28
		LegoS32 m_unk0x2c;              // 0x2c
	};

	// SIZE 0xc8
	// VTABLE: LEGORACERS 0x004afd58
	class Field0x2f90 : public GolNameTable {
	public:
		// VTABLE: LEGORACERS 0x004afd64
		// SIZE 0x1fc
		class SkbTxtParser : public GolTxtParser {};

		// SIZE 0x10
		struct Entry {
			// SIZE 0x10
			struct Keyframe {
				LegoU32 m_unk0x00;   // 0x00
				ColorRGBA m_unk0x04; // 0x04
				ColorRGBA m_unk0x08; // 0x08
				ColorRGBA m_unk0x0c; // 0x0c
			};

			LegoU32 m_unk0x00;   // 0x00
			LegoU32 m_unk0x04;   // 0x04
			Keyframe* m_unk0x08; // 0x08
			LegoU32 m_unk0x0c;   // 0x0c
		};

		// SIZE 0x01
		class ModelBuilder {
		public:
			// SIZE 0x38
			struct Params {
				GolD3DRenderDevice* m_renderer;   // 0x00
				GolModelBase* m_model;            // 0x04
				GolVec3 m_origin;                 // 0x08
				LegoFloat m_radius;               // 0x14
				LegoU32 m_segmentCount;           // 0x18
				LegoU32 m_unk0x1c;                // 0x1c
				LegoU32 m_unk0x20;                // 0x20
				LegoU32 m_unk0x24;                // 0x24
				LegoU32 m_unk0x28;                // 0x28
				LegoU32 m_unk0x2c;                // 0x2c
				LegoU16 m_vertexType;             // 0x30
				undefined2 m_unk0x32;             // 0x32
				GdbModelIndexArray0xc* m_unk0x34; // 0x34
			};

			void FUN_004907d0(Params* p_params);
			void FUN_004907f0(Params* p_params);
			void FUN_004910e0(Params* p_params);
		};

		Field0x2f90();
		~Field0x2f90() override;
		void Clear() override;
		void FUN_0041c550(
			GolD3DRenderDevice* p_renderer,
			GolExport* p_golExport,
			const LegoChar* p_unk0x0c,
			const LegoChar* p_unk0x10,
			LegoBool32 p_binary
		);
		void FUN_0041ccb0(LegoU32 p_elapsedMs);
		void FUN_0041d040(GolVec3* p_position);
		void FUN_0041d0f0(GolD3DRenderDevice* p_renderer);
		void FUN_0041d150(const LegoChar* p_name, LegoU32 p_durationMs);

		// SYNTHETIC: LEGORACERS 0x0041c490
		// RaceSession::Field0x2f90::`scalar deleting destructor'

	private:
		friend class Field0x2098::SkyStateResource0x34;

		enum {
			c_flag0xc4Bit0 = 1 << 0,
			c_flag0xc4Bit1 = 1 << 1,
		};

		void Reset();
		void FUN_0041ce60(Entry* p_entry, ColorRGBA* p_unk0x08, ColorRGBA* p_unk0x0c, ColorRGBA* p_unk0x10);
		void FUN_0041cf20(const ColorRGBA* p_from, const ColorRGBA* p_to, ColorRGBA* p_result, LegoFloat p_amount);
		void FUN_0041cfc0(const ColorRGBA* p_unk0x04, const ColorRGBA* p_unk0x08, const ColorRGBA* p_unk0x0c);

		GolModelEntity m_unk0x0c;         // 0x0c
		GolWorldDatabase* m_unk0x9c;      // 0x9c
		GolModelBase* m_unk0xa0;          // 0xa0
		GolExport* m_unk0xa4;             // 0xa4
		Entry* m_entries;                 // 0xa8
		LegoFloat m_unk0xac;              // 0xac
		LegoU32 m_count;                  // 0xb0
		LegoU32 m_unk0xb4;                // 0xb4
		LegoU32 m_unk0xb8;                // 0xb8
		LegoU32 m_unk0xbc;                // 0xbc
		LegoU32 m_unk0xc0;                // 0xc0
		LegoU8 m_unk0xc4;                 // 0xc4
		ModelBuilder m_unk0xc5;           // 0xc5
		undefined m_unk0xc6[0xc8 - 0xc6]; // 0xc6
	};

	// SIZE 0x08
	class Field0x2804 : public RacePowerupManager::Field0x050 {
	public:
		// VTABLE: LEGORACERS 0x004b1958
		// SIZE 0x1fc
		class TgbTxtParser : public GolTxtParser {};

		Field0x2804();
		~Field0x2804();

	private:
		friend class RaceSession;

		void Reset();
		void FUN_0045c3d0(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
	};

	// SIZE 0x2c
	class Field0x30c4 {
	public:
		// SIZE 0x2c
		class Params {
		public:
			LegoRacers::Context* m_context;     // 0x00
			RaceState* m_raceState;             // 0x04
			RacePowerupManager* m_unk0x08;      // 0x08
			RaceEventDispatcher0x08* m_unk0x0c; // 0x0c
			CutsceneAnimation* m_unk0x10;       // 0x10
			CutsceneAnimation* m_unk0x14;       // 0x14
			TimeRaceManager* m_timeRaceManager; // 0x18
			Field0x2080* m_unk0x1c;             // 0x1c
			Field0x2128* m_unk0x20;             // 0x20
			Field0x32c4* m_unk0x24;             // 0x24
			Field0x2098* m_unk0x28;             // 0x28
		};

		Field0x30c4();
		~Field0x30c4();

	private:
		friend class RaceSession;

		void Reset();
		void FUN_0043a690(const Params* p_source);
		void FUN_0043a6e0();
		void FUN_0043a780();

		LegoRacers::Context* m_context;     // 0x00
		RaceState* m_raceState;             // 0x04
		RacePowerupManager* m_unk0x08;      // 0x08
		RaceEventDispatcher0x08* m_unk0x0c; // 0x0c
		CutsceneAnimation* m_unk0x10;       // 0x10
		CutsceneAnimation* m_unk0x14;       // 0x14
		TimeRaceManager* m_timeRaceManager; // 0x18
		Field0x2080* m_unk0x1c;             // 0x1c
		Field0x2128* m_unk0x20;             // 0x20
		Field0x32c4* m_unk0x24;             // 0x24
		Field0x2098* m_unk0x28;             // 0x28
	};

	// VTABLE: LEGORACERS 0x004b1acc
	// SIZE 0x3c
	class Field0x32c4 {
	public:
		Field0x32c4();
		virtual ~Field0x32c4(); // vtable+0x00
		void FUN_0045e470(LegoU32 p_elapsedMs);
		void FUN_0045e520(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
		LegoU32 FUN_0045e5b0();

		// SYNTHETIC: LEGORACERS 0x0045e380
		// RaceSession::Field0x32c4::`scalar deleting destructor'

	private:
		friend class RaceSession;

		void FUN_0045e3f0(GolWorldDatabase* p_unk0x04, RaceState* p_raceState);
		void Destroy();

		enum {
			c_racerCount = 6,
			c_maxElapsedChunk = 0xff,
			c_unk0x0a8Stride = 100,
		};

		RaceState::Racer* m_unk0x04[c_racerCount]; // 0x04
		GolWorldDatabase* m_unk0x1c;               // 0x1c
		LegoU8* m_unk0x20[c_racerCount];           // 0x20
		LegoU32 m_unk0x38;                         // 0x38
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

	void FUN_00431bd0();
	void FUN_004327f0(LegoRacers::Context* p_context);
	void FUN_004328d0();
	void FUN_004328f0();
	LegoU32 FUN_00432a50(LegoU32 p_index, LegoChar* p_buffer);
	void FUN_00432b30();
	void FUN_00432bc0();
	void FUN_00432d70();
	void FUN_00432dc0();
	void FUN_00432df0();
	void FUN_00432e20(LegoBool32 p_mirror);
	void FUN_004330e0();
	void FUN_00433190(LegoBool32 p_mirror);
	void FUN_00433460();
	void FUN_00433480(LegoBool32 p_mirror);
	void FUN_00434000();
	void FUN_00434170();
	void FUN_00434300();
	void FUN_00434340();
	void FUN_004343e0();
	void FUN_004348a0();
	void FUN_00434930();
	void FUN_004349a0();
	void FUN_00434b00();
	void FUN_00434c80();
	void FUN_00434eb0();
	void FUN_00435180();
	void FUN_004351f0();
	void FUN_004354d0();
	void FUN_004357b0(RaceState::Racer* p_racer);
	void FUN_004357e0();
	void FUN_00435800();
	void FUN_00435830();
	void FUN_00435860();
	void FUN_004358e0();
	void FUN_00435920();
	void FUN_00435ab0();
	void FUN_00435ba0(LegoFloat p_unk0x04);
	void FUN_00435bf0();
	void FUN_00435d20(LegoBool32 p_mirror);
	void FUN_00435e70();
	void FUN_00435f20();
	void FUN_00436010();
	void FUN_00436160();
	void FUN_004362e0();

	LegoRacers::Context* m_context;         // 0x04
	Win32GolApp* m_golApp;                  // 0x08
	SoundManager* m_soundManager;           // 0x0c
	GolExport* m_golExport;                 // 0x10
	GolD3DRenderDevice* m_renderer;         // 0x14
	CircuitStandings* m_standings;          // 0x18
	LegoChar m_unk0x1c;                     // 0x1c
	LegoChar m_unk0x1d[0x05c - 0x01d];      // 0x1d
	LegoChar m_unk0x5c;                     // 0x5c
	LegoChar m_unk0x5d[0x069 - 0x05d];      // 0x5d
	LegoChar m_unk0x69;                     // 0x69
	LegoChar m_unk0x6a[0x076 - 0x06a];      // 0x6a
	LegoChar m_unk0x76;                     // 0x76
	LegoChar m_unk0x77[0x083 - 0x077];      // 0x77
	LegoChar m_unk0x83;                     // 0x83
	LegoChar m_unk0x84[0x090 - 0x084];      // 0x84
	LegoChar m_unk0x90;                     // 0x90
	LegoChar m_unk0x91[0x09d - 0x091];      // 0x91
	LegoChar m_unk0x9d;                     // 0x9d
	LegoChar m_unk0x9e[0x0aa - 0x09e];      // 0x9e
	LegoChar m_unk0xaa;                     // 0xaa
	LegoChar m_unk0xab[0x0b7 - 0x0ab];      // 0xab
	LegoChar m_unk0xb7;                     // 0xb7
	LegoChar m_unk0xb8[0x0c4 - 0x0b8];      // 0xb8
	LegoChar m_unk0xc4;                     // 0xc4
	LegoChar m_unk0xc5[0x0d1 - 0x0c5];      // 0xc5
	LegoChar m_unk0xd1;                     // 0xd1
	LegoChar m_unk0xd2[0x0de - 0x0d2];      // 0xd2
	LegoChar m_unk0xde;                     // 0xde
	LegoChar m_unk0xdf[0x0eb - 0x0df];      // 0xdf
	LegoChar m_unk0xeb;                     // 0xeb
	LegoChar m_unk0xec[0x0f8 - 0x0ec];      // 0xec
	LegoChar m_unk0xf8;                     // 0xf8
	LegoChar m_unk0xf9[0x105 - 0x0f9];      // 0xf9
	LegoChar m_unk0x105;                    // 0x105
	LegoChar m_unk0x106[0x112 - 0x106];     // 0x106
	LegoChar m_unk0x112;                    // 0x112
	LegoChar m_unk0x113[0x11f - 0x113];     // 0x113
	LegoChar m_unk0x11f;                    // 0x11f
	LegoChar m_unk0x120[0x12c - 0x120];     // 0x120
	LegoChar m_unk0x12c;                    // 0x12c
	LegoChar m_unk0x12d[0x139 - 0x12d];     // 0x12d
	LegoChar m_unk0x139;                    // 0x139
	LegoChar m_unk0x13a[0x146 - 0x13a];     // 0x13a
	LegoChar m_unk0x146;                    // 0x146
	LegoChar m_unk0x147[0x153 - 0x147];     // 0x147
	LegoChar m_unk0x153;                    // 0x153
	LegoChar m_unk0x154[0x160 - 0x154];     // 0x154
	LegoChar m_unk0x160;                    // 0x160
	LegoChar m_unk0x161[0x16d - 0x161];     // 0x161
	LegoChar m_unk0x16d;                    // 0x16d
	LegoChar m_unk0x16e[0x17a - 0x16e];     // 0x16e
	LegoChar m_unk0x17a;                    // 0x17a
	LegoChar m_unk0x17b[0x187 - 0x17b];     // 0x17b
	LegoChar m_unk0x187;                    // 0x187
	LegoChar m_unk0x188[0x194 - 0x188];     // 0x188
	LegoChar m_unk0x194;                    // 0x194
	LegoChar m_unk0x195[0x1a1 - 0x195];     // 0x195
	LegoChar m_unk0x1a1;                    // 0x1a1
	LegoChar m_unk0x1a2[0x1ae - 0x1a2];     // 0x1a2
	LegoChar m_unk0x1ae;                    // 0x1ae
	LegoChar m_unk0x1af[0x1bb - 0x1af];     // 0x1af
	LegoChar m_unk0x1bb;                    // 0x1bb
	LegoChar m_unk0x1bc[0x1c8 - 0x1bc];     // 0x1bc
	LegoChar m_unk0x1c8;                    // 0x1c8
	LegoChar m_unk0x1c9[0x1d5 - 0x1c9];     // 0x1c9
	LegoChar m_unk0x1d5;                    // 0x1d5
	LegoChar m_unk0x1d6[0x1e2 - 0x1d6];     // 0x1d6
	LegoChar m_unk0x1e2;                    // 0x1e2
	LegoChar m_unk0x1e3[0x1ef - 0x1e3];     // 0x1e3
	LegoChar m_unk0x1ef;                    // 0x1ef
	LegoChar m_unk0x1f0[0x1f8 - 0x1f0];     // 0x1f0
	GolVec3 m_unk0x1f8;                     // 0x1f8
	GolVec3 m_unk0x204;                     // 0x204
	GolVec3 m_unk0x210;                     // 0x210
	InputManager* m_unk0x21c;               // 0x21c
	InputEventQueue m_inputEvents;          // 0x220
	Field0x23c m_unk0x23c;                  // 0x23c
	Field0x258 m_unk0x258[2];               // 0x258
	RaceForceFeedback m_unk0x340[2];        // 0x340
	GolWorldDatabase* m_unk0x390;           // 0x390
	GolCollidableEntity* m_unk0x394;        // 0x394
	GolWorldDatabase* m_unk0x398;           // 0x398
	GolWorldDatabase* m_unk0x39c;           // 0x39c
	GolWorldDatabase* m_unk0x3a0;           // 0x3a0
	GolWorldDatabase* m_unk0x3a4;           // 0x3a4
	GolWorldDatabase* m_unk0x3a8;           // 0x3a8
	GolCameraBase* m_unk0x3ac;              // 0x3ac
	GolBoundedEntity* m_unk0x3b0;           // 0x3b0
	GolBoundedEntity* m_unk0x3b4;           // 0x3b4
	GolBoundedEntity* m_unk0x3b8;           // 0x3b8
	RaceState m_raceState;                  // 0x3bc
	RacePowerupManager m_unk0x6dc;          // 0x6dc
	Field0x2080 m_unk0x2080;                // 0x2080
	Field0x2098 m_unk0x2098;                // 0x2098
	Field0x2128 m_unk0x2128;                // 0x2128
	Field0x213c m_unk0x213c;                // 0x213c
	RaceEventDispatcher0x08 m_unk0x2148;    // 0x2148
	CutsceneAnimation m_unk0x2150;          // 0x2150
	CutsceneAnimation m_unk0x248c;          // 0x248c
	RaceTrailManager m_trailManager;        // 0x27c8
	RaceSessionField0x27d4 m_unk0x27d4;     // 0x27d4
	Field0x27e0 m_unk0x27e0;                // 0x27e0
	RaceSessionField0x27f4 m_unk0x27f4;     // 0x27f4
	MenuAnimationList m_unk0x27fc;          // 0x27fc
	Field0x2804 m_unk0x2804;                // 0x2804
	Field0x280c m_unk0x280c;                // 0x280c
	CobaltTrail0x140 m_unk0x283c[2];        // 0x283c
	LegoFloat m_unk0x2abc;                  // 0x2abc
	LegoFloat m_unk0x2ac0;                  // 0x2ac0
	LegoFloat m_unk0x2ac4;                  // 0x2ac4
	LegoFloat m_unk0x2ac8;                  // 0x2ac8
	GolCamera* m_unk0x2acc[2];              // 0x2acc
	RaceCameraController m_unk0x2ad4[2];    // 0x2ad4
	GolFontTable* m_unk0x2d74;              // 0x2d74
	GolFontBase* m_unk0x2d78;               // 0x2d78
	GolFontBase* m_unk0x2d7c;               // 0x2d7c
	GolString m_unk0x2d80;                  // 0x2d80
	undefined2 m_unk0x2d8c[0x100];          // 0x2d8c
	AwakeKite0x20* m_unk0x2f8c;             // 0x2f8c
	Field0x2f90 m_unk0x2f90;                // 0x2f90
	SlateBridge0x68 m_unk0x3058;            // 0x3058
	undefined4 m_unk0x30c0;                 // 0x30c0
	Field0x30c4 m_unk0x30c4;                // 0x30c4
	GolStringTable m_unk0x30f0;             // 0x30f0
	RaceRouteRecord m_routeRecords[6];      // 0x3104
	RaceSessionField0x32b4 m_unk0x32b4;     // 0x32b4
	Field0x32c4 m_unk0x32c4;                // 0x32c4
	Field0x3300 m_unk0x3300;                // 0x3300
	MusicGroup* m_unk0x3314;                // 0x3314
	SoundNode* m_unk0x3318[2];              // 0x3318
	MusicInstance* m_unk0x3320;             // 0x3320
	LegoFloat m_unk0x3324;                  // 0x3324
	undefined4 m_state;                     // 0x3328
	LegoU32 m_elapsedMs;                    // 0x332c
	undefined4 m_unk0x3330;                 // 0x3330
	undefined4 m_running;                   // 0x3334
	LegoBool m_unk0x3338;                   // 0x3338
	undefined m_unk0x3339[0x333c - 0x3339]; // 0x3339
	LegoU32 m_frameCount;                   // 0x333c
	LegoU32 m_unk0x3340;                    // 0x3340
	LegoFloat m_fps;                        // 0x3344
	undefined m_unk0x3348;                  // 0x3348
	undefined m_unk0x3349[0x334c - 0x3349]; // 0x3349
	undefined4 m_unk0x334c;                 // 0x334c
	undefined4 m_unk0x3350;                 // 0x3350
	undefined4 m_unk0x3354;                 // 0x3354
	undefined4 m_unk0x3358;                 // 0x3358
	undefined4 m_unk0x335c;                 // 0x335c
	undefined4 m_unk0x3360;                 // 0x3360
	TimeRaceManager* m_timeRaceManager;     // 0x3364
};

#endif // RACESESSION_H
