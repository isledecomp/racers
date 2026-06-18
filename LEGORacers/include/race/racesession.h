#ifndef RACESESSION_H
#define RACESESSION_H

#include "app/golappeventhandler.h"
#include "app/legoracers.h"
#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golnametable.h"
#include "golstring.h"
#include "golstringtable.h"
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
#include "race/raceresourcemanager.h"
#include "race/racesessionfield0x27d4.h"
#include "race/racesessionfield0x32b4.h"
#include "race/racestate.h"
#include "race/slatebridge0x68.h"
#include "scene/golbillboard.h"
#include "surface/color.h"
#include "types.h"
#include "util/legoeventqueue.h"
#include "util/marblepath0x114.h"

class GolD3DRenderDevice;
class CircuitStandings;
class TimeRaceManager;
class GolExport;
class GolCamera;
class GolFontBase;
class GolFontTable;
class GolNameTable;
class GolWorldDatabase;
class GolWorldEntity;
class GolModelBase;
class GolSceneNode;
class AwakeKite0x20;
class UtopianPan0xa4;
class MusicGroup;
class MusicInstance;
class SoundGroup;
class SoundManager;
struct SoundNode;
class Win32GolApp;

// VTABLE: LEGORACERS 0x004b07f4
// SIZE 0x3368
class RaceSession : public GolAppEventHandler {
public:
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
	class InputDispatchSource;
	class Field0x258;
	class Field0x23c;
	class Field0x3ac;
	class Field0x32c4;

	// SIZE 0x04
	class InputEventSink {
	public:
		virtual LegoS32 VTable0x00(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time) = 0;
		virtual LegoS32 VTable0x04(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time) = 0;
		virtual LegoS32 VTable0x08(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time);
	};

	// SIZE 0x9c
	class InputDispatchSource {
	public:
		virtual void VTable0x00() = 0;                        // vtable+0x00
		virtual void VTable0x04() = 0;                        // vtable+0x04
		virtual void VTable0x08() = 0;                        // vtable+0x08
		virtual void VTable0x0c() = 0;                        // vtable+0x0c
		virtual void VTable0x10() = 0;                        // vtable+0x10
		virtual void VTable0x14() = 0;                        // vtable+0x14
		virtual LegoS32 VTable0x18() = 0;                     // vtable+0x18
		virtual void VTable0x1c() = 0;                        // vtable+0x1c
		virtual void VTable0x20() = 0;                        // vtable+0x20
		virtual void VTable0x24() = 0;                        // vtable+0x24
		virtual void VTable0x28() = 0;                        // vtable+0x28
		virtual void VTable0x2c() = 0;                        // vtable+0x2c
		virtual LegoFloat VTable0x30(undefined4 p_input) = 0; // vtable+0x30
		virtual void VTable0x34() = 0;                        // vtable+0x34
		virtual void VTable0x38() = 0;                        // vtable+0x38
		virtual void VTable0x3c() = 0;                        // vtable+0x3c
		virtual void VTable0x40() = 0;                        // vtable+0x40
		virtual void VTable0x44() = 0;                        // vtable+0x44
		virtual void VTable0x48() = 0;                        // vtable+0x48
		virtual void VTable0x4c() = 0;                        // vtable+0x4c
		virtual void VTable0x50() = 0;                        // vtable+0x50
		virtual void VTable0x54() = 0;                        // vtable+0x54

		undefined m_unk0x04[0x98 - 0x04]; // 0x04
		InputEventSink* m_unk0x98;        // 0x98
	};

	// SIZE 0x30
	class Field0x3ac {
	public:
		undefined m_unk0x00[0x28 - 0x00]; // 0x00
		GolAnimatedEntity* m_unk0x28;     // 0x28
		LegoU32 m_unk0x2c;                // 0x2c
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
			LegoS32 VTable0x00(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time) override;
			LegoS32 VTable0x04(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time) override;
			virtual ~Field0x04();

			// SYNTHETIC: LEGORACERS 0x00430870
			// RaceSession::Field0x258::Field0x04::`scalar deleting destructor'

			void FUN_00430c20();

		private:
			friend class RaceSession;
			friend class Field0x258;
			friend class Field0x23c;

			void FUN_004308a0();
			void FUN_00430980();
			undefined4 FUN_00430910(InputDispatchSource** p_source, LegoU32 p_index);

			Field0x258* m_unk0x004;                            // 0x004
			undefined4 m_unk0x008[c_inputSlotCount];           // 0x008
			InputDispatchSource* m_unk0x02c[c_inputSlotCount]; // 0x02c
			InputEventSink* m_unk0x050;                        // 0x050
			LegoBool32 m_unk0x054;                             // 0x054
			LegoU32 m_unk0x058;                                // 0x058
			LegoU32 m_unk0x05c;                                // 0x05c
			LegoU32 m_unk0x060;                                // 0x060
			LegoU32 m_unk0x064;                                // 0x064
			LegoFloat m_unk0x068;                              // 0x068
			LegoBool32 m_unk0x06c;                             // 0x06c
		};

		Field0x258();
		~Field0x258();

	private:
		friend class RaceSession;
		friend class Field0x04;

		void FUN_004300a0();
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

		RaceState::Racer* m_unk0x000; // 0x000
		Field0x04 m_unk0x004;         // 0x004
	};

	// SIZE 0x28
	class Field0x340 {
	public:
		class Field0x00 {
		public:
			virtual void VTable0x00() = 0; // vtable+0x00
			virtual void VTable0x04() = 0; // vtable+0x04
			virtual void VTable0x08() = 0; // vtable+0x08
			virtual void VTable0x0c() = 0; // vtable+0x0c
			virtual void VTable0x10() = 0; // vtable+0x10
			virtual void VTable0x14() = 0; // vtable+0x14
			virtual void VTable0x18() = 0; // vtable+0x18
			virtual void VTable0x1c() = 0; // vtable+0x1c
			virtual void VTable0x20() = 0; // vtable+0x20
			virtual void VTable0x24() = 0; // vtable+0x24
			virtual void VTable0x28() = 0; // vtable+0x28
			virtual void VTable0x2c() = 0; // vtable+0x2c
			virtual void VTable0x30() = 0; // vtable+0x30
			virtual void VTable0x34() = 0; // vtable+0x34
			virtual void VTable0x38() = 0; // vtable+0x38
			virtual void VTable0x3c() = 0; // vtable+0x3c
			virtual void VTable0x40() = 0; // vtable+0x40
			virtual void VTable0x44() = 0; // vtable+0x44
			virtual void VTable0x48() = 0; // vtable+0x48
			virtual void VTable0x4c() = 0; // vtable+0x4c
			virtual void VTable0x50() = 0; // vtable+0x50
			virtual void VTable0x54() = 0; // vtable+0x54
			virtual void VTable0x58() = 0; // vtable+0x58
			virtual void VTable0x5c() = 0; // vtable+0x5c
			virtual void VTable0x60() = 0; // vtable+0x60
		};

		class Field0x24 {
		public:
			virtual void __stdcall VTable0x00() = 0; // vtable+0x00
			virtual void __stdcall VTable0x04() = 0; // vtable+0x04
			virtual void __stdcall VTable0x08() = 0; // vtable+0x08
			virtual void __stdcall VTable0x0c() = 0; // vtable+0x0c
			virtual void __stdcall VTable0x10() = 0; // vtable+0x10
			virtual void __stdcall VTable0x14() = 0; // vtable+0x14
			virtual undefined4 __stdcall VTable0x18(undefined4* p_unk0x04,
													undefined4 p_unk0x08) = 0; // vtable+0x18
			virtual void __stdcall VTable0x1c(undefined4, undefined4) = 0;     // vtable+0x1c
			virtual void __stdcall VTable0x20() = 0;                           // vtable+0x20
		};

		Field0x340();
		~Field0x340();
		void FUN_00422130();
		void FUN_00422150();
		void FUN_00422170();
		void FUN_004221a0();

	private:
		friend class RaceSession;

		void FUN_00421de0();
		void FUN_00421e30(LegoU32 p_elapsedMs, LegoFloat p_unk0x08);
		void FUN_00421ef0();
		LegoS32 FUN_00421f40();
		LegoS32 FUN_00421f80(LegoFloat p_unk0x04);
		undefined4 FUN_004222b0(LegoFloat p_unk0x04);

		Field0x00* m_unk0x00; // 0x00
		LegoU32 m_unk0x04;    // 0x04
		LegoU32 m_unk0x08;    // 0x08
		LegoS32 m_unk0x0c;    // 0x0c
		LegoU32 m_unk0x10;    // 0x10
		LegoFloat m_unk0x14;  // 0x14
		LegoU32 m_unk0x18;    // 0x18
		LegoU32 m_unk0x1c;    // 0x1c
		LegoU32 m_unk0x20;    // 0x20
		Field0x24* m_unk0x24; // 0x24
	};

	// SIZE 0x1c
	// VTABLE: LEGORACERS 0x004b0300
	class Field0x23c : public InputEventSink {
	public:
		Field0x23c();
		LegoS32 VTable0x00(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time) override;
		LegoS32 VTable0x04(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time) override;
		virtual ~Field0x23c();

		// SYNTHETIC: LEGORACERS 0x00427930
		// RaceSession::Field0x23c::`scalar deleting destructor'

		void FUN_00427980(InputDispatchSource* p_source, InputEventSink* p_fallback);
		void FUN_004279a0(Field0x258::Field0x04* p_sink);
		void FUN_004279c0();
		void FUN_004279f0();
		void FUN_00427b40();

	private:
		friend class RaceSession;

		LegoS32 FUN_00427960();

		InputDispatchSource* m_unk0x04;      // 0x04
		Field0x258::Field0x04* m_unk0x08[2]; // 0x08
		LegoU32 m_unk0x10;                   // 0x10
		InputEventSink* m_unk0x14;           // 0x14
		undefined4 m_unk0x18;                // 0x18
	};

	// SIZE 0x14
	class Field0x3300 {
	public:
		Field0x3300();
		~Field0x3300();
		void FUN_00443a80();
		void FUN_00443ac0(SoundManager* p_soundManager);
		void FUN_00443b00(const LegoChar* p_name);
		void FUN_00443b10(const LegoChar* p_name1, const LegoChar* p_name2);
		void FUN_00443b40(const LegoChar* p_name);

	private:
		SoundManager* m_soundManager; // 0x00
		SoundGroup* m_groups[4];      // 0x04
	};

	// SIZE 0xa4
	class Field0x21c {
	public:
		undefined m_unk0x000[0x0a0 - 0x000]; // 0x000
		InputDispatchSource* m_unk0x0a0;     // 0x0a0
	};

	// SIZE 0x19a4
	class Field0x6dc {
	public:
		class Field0x0 {
		public:
			virtual void VTable0x00() = 0;           // vtable+0x00
			virtual void VTable0x04() = 0;           // vtable+0x04
			virtual void VTable0x08() = 0;           // vtable+0x08
			virtual void VTable0x0c() = 0;           // vtable+0x0c
			virtual void VTable0x10() = 0;           // vtable+0x10
			virtual void VTable0x14() = 0;           // vtable+0x14
			virtual void VTable0x18() = 0;           // vtable+0x18
			virtual void VTable0x1c() = 0;           // vtable+0x1c
			virtual void VTable0x20() = 0;           // vtable+0x20
			virtual void VTable0x24() = 0;           // vtable+0x24
			virtual void VTable0x28() = 0;           // vtable+0x28
			virtual void VTable0x2c() = 0;           // vtable+0x2c
			virtual void VTable0x30() = 0;           // vtable+0x30
			virtual void VTable0x34() = 0;           // vtable+0x34
			virtual void VTable0x38() = 0;           // vtable+0x38
			virtual void VTable0x3c(undefined4) = 0; // vtable+0x3c
		};

		typedef RaceResourceManager Field0x3c;

		// SIZE 0x174
		class Field0x074 {
		public:
			// SIZE 0x60
			class Field0x170 {
			public:
				GolWorldEntity* GetUnk0x5c() { return m_unk0x05c; }

			private:
				undefined m_unk0x000[0x05c - 0x000]; // 0x000
				GolWorldEntity* m_unk0x05c;          // 0x05c
			};

			Field0x170* GetUnk0x170() { return m_unk0x170; }

		private:
			undefined m_unk0x000[0x170 - 0x000]; // 0x000
			Field0x170* m_unk0x170;              // 0x170
		};

		class Field0x64 {
		public:
			virtual void VTable0x00() = 0;              // vtable+0x00
			virtual void VTable0x04() = 0;              // vtable+0x04
			virtual void VTable0x08() = 0;              // vtable+0x08
			virtual void VTable0x0c() = 0;              // vtable+0x0c
			virtual void VTable0x10() = 0;              // vtable+0x10
			virtual void VTable0x14() = 0;              // vtable+0x14
			virtual void VTable0x18() = 0;              // vtable+0x18
			virtual void VTable0x1c() = 0;              // vtable+0x1c
			virtual void VTable0x20() = 0;              // vtable+0x20
			virtual void VTable0x24() = 0;              // vtable+0x24
			virtual void VTable0x28() = 0;              // vtable+0x28
			virtual void VTable0x2c() = 0;              // vtable+0x2c
			virtual void VTable0x30() = 0;              // vtable+0x30
			virtual void VTable0x34() = 0;              // vtable+0x34
			virtual void VTable0x38() = 0;              // vtable+0x38
			virtual void VTable0x3c() = 0;              // vtable+0x3c
			virtual void VTable0x40() = 0;              // vtable+0x40
			virtual void VTable0x44() = 0;              // vtable+0x44
			virtual void VTable0x48() = 0;              // vtable+0x48
			virtual void VTable0x4c() = 0;              // vtable+0x4c
			virtual void VTable0x50() = 0;              // vtable+0x50
			virtual void VTable0x54() = 0;              // vtable+0x54
			virtual void VTable0x58() = 0;              // vtable+0x58
			virtual void VTable0x5c() = 0;              // vtable+0x5c
			virtual void VTable0x60() = 0;              // vtable+0x60
			virtual void VTable0x64(GolBillboard*) = 0; // vtable+0x64
		};

		// SIZE 0x04
		class Field0x54 {
		public:
			virtual void VTable0x00(); // vtable+0x00
			virtual void VTable0x04(); // vtable+0x04
			virtual void VTable0x08(); // vtable+0x08
			virtual void VTable0x0c(); // vtable+0x0c
			virtual void VTable0x10(); // vtable+0x10
			virtual void VTable0x14(); // vtable+0x14
			virtual void VTable0x18(); // vtable+0x18
			virtual void VTable0x1c(); // vtable+0x1c
			virtual void VTable0x20(); // vtable+0x20
			virtual void VTable0x24(); // vtable+0x24
			virtual void VTable0x28(); // vtable+0x28
			virtual void VTable0x2c(); // vtable+0x2c
			virtual void VTable0x30(); // vtable+0x30
			virtual void VTable0x34(); // vtable+0x34
			virtual void VTable0x38(); // vtable+0x38
			virtual void VTable0x3c(); // vtable+0x3c
			virtual void VTable0x40(); // vtable+0x40
			virtual void VTable0x44(); // vtable+0x44
			virtual void VTable0x48(); // vtable+0x48
			virtual void VTable0x4c(); // vtable+0x4c
			virtual void VTable0x50(); // vtable+0x50
			virtual void VTable0x54(); // vtable+0x54
		};

		// SIZE 0x170
		class Field0x170 {
		public:
			void Reset();
			void FUN_00493e60();

		private:
			GolExport* m_unk0x000;               // 0x000
			GolModelBase* m_unk0x004;            // 0x004
			undefined4 m_unk0x008;               // 0x008
			undefined4 m_unk0x00c;               // 0x00c
			GolSceneNode* m_unk0x010;            // 0x010
			undefined4 m_unk0x014;               // 0x014
			Field0x54 m_unk0x018;                // 0x018
			undefined m_unk0x01c[0x0b0 - 0x01c]; // 0x01c
			undefined4 m_unk0x0b0;               // 0x0b0
			undefined4 m_unk0x0b4;               // 0x0b4
			undefined4 m_unk0x0b8;               // 0x0b8
			undefined4 m_unk0x0bc;               // 0x0bc
			undefined4 m_unk0x0c0;               // 0x0c0
			undefined4 m_unk0x0c4;               // 0x0c4
			undefined4 m_unk0x0c8;               // 0x0c8
			undefined4 m_unk0x0cc;               // 0x0cc
			undefined4 m_unk0x0d0;               // 0x0d0
			undefined4 m_unk0x0d4;               // 0x0d4
			undefined m_unk0x0d8[0x0dc - 0x0d8]; // 0x0d8
			undefined4 m_unk0x0dc;               // 0x0dc
			undefined4 m_unk0x0e0;               // 0x0e0
			undefined4 m_unk0x0e4;               // 0x0e4
			undefined4 m_unk0x0e8;               // 0x0e8
			undefined4 m_unk0x0ec[15];           // 0x0ec
			undefined4 m_unk0x128[5];            // 0x128
			undefined4 m_unk0x13c;               // 0x13c
			undefined4 m_unk0x140;               // 0x140
			undefined4 m_unk0x144;               // 0x144
			undefined4 m_unk0x148;               // 0x148
			undefined4 m_unk0x14c;               // 0x14c
			undefined4 m_unk0x150;               // 0x150
			undefined m_unk0x154[0x160 - 0x154]; // 0x154
			LegoU8 m_unk0x160;                   // 0x160
			LegoU8 m_unk0x161;                   // 0x161
			LegoU8 m_unk0x162;                   // 0x162
			LegoU8 m_unk0x163;                   // 0x163
			LegoU8 m_unk0x164;                   // 0x164
			LegoU8 m_unk0x165;                   // 0x165
			LegoU8 m_unk0x166;                   // 0x166
			LegoU8 m_unk0x167;                   // 0x167
			LegoU8 m_unk0x168;                   // 0x168
			LegoU8 m_unk0x169;                   // 0x169
			LegoU8 m_unk0x16a;                   // 0x16a
			LegoU8 m_unk0x16b;                   // 0x16b
			undefined4 m_unk0x16c;               // 0x16c
		};

		class ResourceBase {
		public:
			virtual void VTable0x00() = 0;           // vtable+0x00
			virtual void VTable0x04(undefined4) = 0; // vtable+0x04
			virtual void VTable0x08() = 0;           // vtable+0x08
			virtual void VTable0x0c() = 0;           // vtable+0x0c
			virtual void VTable0x10() = 0;           // vtable+0x10
			virtual void VTable0x14() = 0;           // vtable+0x14
			virtual void VTable0x18() = 0;           // vtable+0x18
			virtual void VTable0x1c() = 0;           // vtable+0x1c
		};

		class Field0x1880;

		// SIZE 0x54
		class Field0x68 {
		public:
			// SIZE 0x04
			class Field0x08 {
			public:
				virtual void VTable0x00();                      // vtable+0x00
				virtual void VTable0x04(GolVec3* p_position);   // vtable+0x04
				virtual LegoU8 VTable0x08(GolVec3* p_position); // vtable+0x08
			};

			virtual void VTable0x00() = 0;                    // vtable+0x00
			virtual void VTable0x04() = 0;                    // vtable+0x04
			virtual void VTable0x08(undefined4) = 0;          // vtable+0x08
			virtual void VTable0x0c() = 0;                    // vtable+0x0c
			virtual void VTable0x10(GolD3DRenderDevice*) = 0; // vtable+0x10
			virtual void VTable0x14(GolD3DRenderDevice*) = 0; // vtable+0x14

			void ClearUnk0x24() { m_unk0x24 = NULL; }
			void SetFlags0x50Bit0() { m_flags0x50 |= c_flags0x50Bit0; }

		protected:
			enum {
				c_stateIdle = 0,
				c_stateWait = 1,
				c_stateActive = 2,
				c_stateTransition = 3,
				c_stateInactive = 4,

				c_flags0x50Bit0 = 1 << 0,
				c_flags0x50Bit1 = 1 << 1,
				c_flags0x50Bit2 = 1 << 2,
				c_flags0x64Bit0 = 1 << 0,
				c_flags0x64Bit1 = 1 << 1,
			};

			void FUN_00453a20(LegoU32 p_elapsedMs);
			void FUN_00453ad0(LegoBool32 p_unk0x04);

			Field0x6dc* m_unk0x04;                   // 0x04
			Field0x08 m_unk0x08;                     // 0x08
			undefined m_unk0x0c[0x24 - 0x0c];        // 0x0c
			Field0x6dc* m_unk0x24;                   // 0x24
			undefined m_unk0x28[0x30 - 0x28];        // 0x28
			LegoFloat m_unk0x30;                     // 0x30
			undefined4 m_unk0x34;                    // 0x34
			undefined4 m_unk0x38;                    // 0x38
			LegoU32 m_unk0x3c;                       // 0x3c
			LegoU32 m_unk0x40;                       // 0x40
			RaceState::Racer::Field0x004* m_unk0x44; // 0x44
			LegoU32 m_unk0x48;                       // 0x48
			LegoU32 m_unk0x4c;                       // 0x4c
			LegoU8 m_flags0x50;                      // 0x50
			undefined m_unk0x51[0x54 - 0x51];        // 0x51
		};

		// SIZE 0x68
		class Field0x68Field0x028 : public Field0x68 {
		public:
			void FUN_00457710(LegoU32 p_elapsedMs);

		private:
			Field0x1880* m_unk0x54; // 0x54
			Field0x1880* m_unk0x58; // 0x58
			LegoU32 m_unk0x5c;      // 0x5c
			LegoU32 m_unk0x60;      // 0x60
			LegoU32 m_unk0x64;      // 0x64
		};

		// SIZE 0x68
		class Field0x68Field0x02c : public Field0x68 {
		public:
			void FUN_00453690(LegoU32 p_elapsedMs);

		private:
			void FUN_004537f0();

			GolVec3 m_unk0x54;                // 0x54
			LegoU32 m_unk0x60;                // 0x60
			LegoU8 m_flags0x64;               // 0x64
			undefined m_unk0x65[0x68 - 0x65]; // 0x65
		};

		// SIZE 0x84
		class Field0x1890 : public ResourceBase {
		public:
			void FUN_004557c0();
			void FUN_004557e0();

		private:
			undefined m_unk0x04[0x2c - 0x04]; // 0x04
			undefined4 m_unk0x2c;             // 0x2c
			undefined4 m_unk0x30;             // 0x30
			undefined4 m_unk0x34;             // 0x34
			undefined4 m_unk0x38;             // 0x38
			undefined4 m_unk0x3c;             // 0x3c
			undefined4 m_unk0x40;             // 0x40
			undefined4 m_unk0x44;             // 0x44
			undefined m_unk0x48[0x70 - 0x48]; // 0x48
			undefined4 m_unk0x70;             // 0x70
			undefined m_unk0x74[0x78 - 0x74]; // 0x74
			undefined4 m_unk0x78;             // 0x78
			undefined4 m_unk0x7c;             // 0x7c
			undefined m_unk0x80;              // 0x80
			undefined m_unk0x81[0x84 - 0x81]; // 0x81
		};

		// SIZE 0x190
		class Field0x1894 : public ResourceBase {
		public:
			void FUN_00457170();

		private:
			undefined m_unk0x004[0x02c - 0x004]; // 0x004
			undefined4 m_unk0x02c;               // 0x02c
			undefined m_unk0x030[0x058 - 0x030]; // 0x030
			undefined4 m_unk0x058;               // 0x058
			undefined4 m_unk0x05c;               // 0x05c
			undefined4 m_unk0x060;               // 0x060
			MarblePath0x114 m_unk0x064;          // 0x064
			undefined m_unk0x178[0x180 - 0x178]; // 0x178
			GolBillboard::Field0x2c m_unk0x180;  // 0x180
			undefined4 m_unk0x18c;               // 0x18c
		};

		// SIZE 0x17c
		class Field0x1898 : public ResourceBase {
		public:
			void FUN_00452eb0();

		private:
			undefined m_unk0x004[0x02c - 0x004]; // 0x004
			Field0x54 m_unk0x02c;                // 0x02c
			undefined m_unk0x030[0x164 - 0x030]; // 0x030
			undefined4 m_unk0x164;               // 0x164
			undefined4 m_unk0x168;               // 0x168
			undefined4 m_unk0x16c;               // 0x16c
			undefined4 m_unk0x170;               // 0x170
			undefined m_unk0x174[0x17c - 0x174]; // 0x174
		};

		// SIZE 0x68
		class Field0x189c : public ResourceBase {
		public:
			void FUN_004524f0();
			void FUN_00452510();

		private:
			undefined m_unk0x04[0x18 - 0x04]; // 0x04
			undefined4 m_unk0x18;             // 0x18
			undefined m_unk0x1c[0x20 - 0x1c]; // 0x1c
			undefined4 m_unk0x20;             // 0x20
			undefined m_unk0x24[0x2c - 0x24]; // 0x24
			undefined4 m_unk0x2c;             // 0x2c
			undefined4 m_unk0x30;             // 0x30
			undefined4 m_unk0x34;             // 0x34
			undefined4 m_unk0x38;             // 0x38
			undefined m_unk0x3c[0x64 - 0x3c]; // 0x3c
			undefined4 m_unk0x64;             // 0x64
		};

		// SIZE 0xe8
		class Field0x18a0 : public ResourceBase {
		public:
			void FUN_00451a10();

		private:
			undefined4 m_unk0x04;             // 0x04
			undefined m_unk0x08[0x1c - 0x08]; // 0x08
			Field0x64** m_unk0x1c;            // 0x1c
			undefined m_unk0x20[0xd8 - 0x20]; // 0x20
			GolBillboard* m_unk0xd8;          // 0xd8
			undefined m_unk0xdc[0xe8 - 0xdc]; // 0xdc
		};

		// SIZE 0x290
		class Field0x18a4 : public ResourceBase {
		public:
			void FUN_00453d90();

		private:
			undefined4 m_unk0x004;               // 0x004
			undefined m_unk0x008[0x01c - 0x008]; // 0x008
			Field0x64** m_unk0x01c;              // 0x01c
			undefined m_unk0x020[0x030 - 0x020]; // 0x020
			Field0x54 m_unk0x030;                // 0x030
			undefined m_unk0x034[0x270 - 0x034]; // 0x034
			GolBillboard* m_unk0x270;            // 0x270
			undefined m_unk0x274[0x290 - 0x274]; // 0x274
		};

		// SIZE 0x24c
		class Field0x18a8 : public ResourceBase {
		public:
			void FUN_00454ab0();

		private:
			undefined4 m_unk0x004;               // 0x004
			undefined m_unk0x008[0x010 - 0x008]; // 0x008
			Field0x3c* m_unk0x010;               // 0x010
			undefined m_unk0x014[0x01c - 0x014]; // 0x014
			Field0x64** m_unk0x01c;              // 0x01c
			undefined m_unk0x020[0x030 - 0x020]; // 0x020
			Field0x170 m_unk0x030;               // 0x030
			undefined m_unk0x1a0[0x238 - 0x1a0]; // 0x1a0
			Field0x3c::Resource* m_unk0x238;     // 0x238
			undefined4 m_unk0x23c;               // 0x23c
			undefined m_unk0x240[0x244 - 0x240]; // 0x240
			undefined4 m_unk0x244;               // 0x244
			GolBillboard* m_unk0x248;            // 0x248
		};

		// SIZE 0x224
		class Field0x18ac : public ResourceBase {
		public:
			void FUN_00456540();

		private:
			undefined4 m_unk0x004;               // 0x004
			undefined m_unk0x008[0x21c - 0x008]; // 0x008
			undefined4 m_unk0x21c;               // 0x21c
			undefined m_unk0x220[0x224 - 0x220]; // 0x220
		};

		// SIZE 0x2c
		class Field0x18b0 : public ResourceBase {
		public:
			void FUN_0045bd10();

		private:
			undefined4 m_unk0x04;             // 0x04
			undefined m_unk0x08[0x2c - 0x08]; // 0x08
		};

		// SIZE 0x34
		class Field0x18b4 : public ResourceBase {
		public:
			void FUN_0045c8b0();
			void FUN_0045c8d0();

		private:
			undefined4 m_unk0x04;             // 0x04
			undefined m_unk0x08[0x18 - 0x08]; // 0x08
			undefined4 m_unk0x18;             // 0x18
			undefined4 m_unk0x1c;             // 0x1c
			undefined4 m_unk0x20;             // 0x20
			undefined4 m_unk0x24;             // 0x24
			undefined4 m_unk0x28;             // 0x28
			undefined4 m_unk0x2c;             // 0x2c
			undefined4 m_unk0x30;             // 0x30
		};

		// SIZE 0xe4
		class Field0x18b8 : public ResourceBase {
		public:
			void FUN_0045d4b0();
			void FUN_0045d540();

		private:
			friend class Field0x6dc;

			LegoS32 m_unk0x004;                  // 0x004
			LegoU32 m_unk0x008;                  // 0x008
			undefined m_unk0x00c[0x0a8 - 0x00c]; // 0x00c
			RaceState::Racer* m_unk0x0a8;        // 0x0a8
			undefined4 m_unk0x0ac;               // 0x0ac
			undefined4 m_unk0x0b0;               // 0x0b0
			undefined4 m_unk0x0b4;               // 0x0b4
			undefined4 m_unk0x0b8;               // 0x0b8
			undefined4 m_unk0x0bc;               // 0x0bc
			undefined4 m_unk0x0c0;               // 0x0c0
			undefined4 m_unk0x0c4;               // 0x0c4
			undefined4 m_unk0x0c8;               // 0x0c8
			undefined4 m_unk0x0cc;               // 0x0cc
			undefined4 m_unk0x0d0;               // 0x0d0
			undefined4 m_unk0x0d4;               // 0x0d4
			undefined4 m_unk0x0d8;               // 0x0d8
			undefined4 m_unk0x0dc;               // 0x0dc
			undefined4 m_unk0x0e0;               // 0x0e0
		};

		// SIZE 0x18
		class Field0x1880 {
		public:
			virtual void VTable0x00() = 0;                    // vtable+0x00
			virtual void VTable0x04() = 0;                    // vtable+0x04
			virtual void VTable0x08(LegoU32) = 0;             // vtable+0x08
			virtual void VTable0x0c(GolD3DRenderDevice*) = 0; // vtable+0x0c
			virtual void VTable0x10(GolD3DRenderDevice*) = 0; // vtable+0x10
			virtual void VTable0x14() = 0;                    // vtable+0x14
			virtual LegoS32 VTable0x18() = 0;                 // vtable+0x18
			virtual void VTable0x1c() = 0;                    // vtable+0x1c
			virtual void VTable0x20() = 0;                    // vtable+0x20
			virtual void VTable0x24(GolVec3* p_unk0x04) = 0;  // vtable+0x24
			virtual void VTable0x28(GolVec3* p_unk0x04) = 0;  // vtable+0x28

			Field0x1880* GetNext() { return m_next; }
			LegoS32 GetUnk0x04() const { return m_unk0x04; }
			LegoU32 GetState() const { return m_state; }
			void SetUnk0x04(LegoS32 p_unk0x04) { m_unk0x04 = p_unk0x04; }
			void SetNext(Field0x1880* p_next) { m_next = p_next; }

		private:
			LegoS32 m_unk0x04;    // 0x04
			undefined4 m_unk0x08; // 0x08
			Field0x1880* m_next;  // 0x0c
			undefined4 m_unk0x10; // 0x10
			LegoU32 m_state;      // 0x14
		};

		// SIZE 0x270
		class Field0x270 {
		public:
			// SIZE 0x5c
			class Field0x34 {
			public:
				virtual void VTable0x00();                    // vtable+0x00
				virtual void VTable0x04();                    // vtable+0x04
				virtual void VTable0x08();                    // vtable+0x08
				virtual void VTable0x0c();                    // vtable+0x0c
				virtual void VTable0x10();                    // vtable+0x10
				virtual void VTable0x14();                    // vtable+0x14
				virtual void VTable0x18();                    // vtable+0x18
				virtual void VTable0x1c(GolD3DRenderDevice*); // vtable+0x1c
				virtual void VTable0x20();                    // vtable+0x20
				virtual void VTable0x24();                    // vtable+0x24
				virtual void VTable0x28();                    // vtable+0x28
				virtual void VTable0x2c();                    // vtable+0x2c
				virtual void VTable0x30();                    // vtable+0x30
				virtual void VTable0x34();                    // vtable+0x34
				virtual void VTable0x38();                    // vtable+0x38
				virtual void VTable0x3c();                    // vtable+0x3c
				virtual void VTable0x40();                    // vtable+0x40
				virtual void VTable0x44();                    // vtable+0x44
				virtual void VTable0x48();                    // vtable+0x48
				virtual void VTable0x4c();                    // vtable+0x4c
				virtual void VTable0x50();                    // vtable+0x50
				virtual void VTable0x54();                    // vtable+0x54

				void SetUnk0x10(LegoFloat p_unk0x10) { m_unk0x10 = p_unk0x10; }
				void SetUnk0x58(LegoFloat p_unk0x58) { m_unk0x58 = p_unk0x58; }

			private:
				undefined m_unk0x04[0x10 - 0x04]; // 0x04
				LegoFloat m_unk0x10;              // 0x10
				undefined m_unk0x14[0x58 - 0x14]; // 0x14
				LegoFloat m_unk0x58;              // 0x58
			};

			// SIZE 0x20
			class Field0x224 {
			public:
				MabMaterialAnimationItem0x8* GetUnk0x18() const { return m_unk0x18; }
				LegoU32 GetUnk0x1c() const { return m_unk0x1c; }

			private:
				undefined m_unk0x00[0x18 - 0x00];       // 0x00
				MabMaterialAnimationItem0x8* m_unk0x18; // 0x18
				LegoU32 m_unk0x1c;                      // 0x1c
			};

			virtual void VTable0x00() = 0;           // vtable+0x00
			virtual void VTable0x04(undefined4) = 0; // vtable+0x04

			Field0x270* GetNext() { return m_next; }
			LegoS32 GetUnk0x04() const { return m_unk0x04; }
			void SetNext(Field0x270* p_next) { m_next = p_next; }
			void FUN_004214b0();
			void FUN_004217b0();
			void FUN_004217d0(LegoU32 p_elapsedMs);
			void FUN_00421850(LegoU32 p_elapsedMs);
			void FUN_00421ae0(GolD3DRenderDevice* p_renderer);
			void FUN_004513d0(GolD3DRenderDevice* p_renderer);

		private:
			enum {
				c_flag0x090Bit0 = 1 << 0,
			};

			LegoS32 m_unk0x04;                                            // 0x004
			GolWorldEntity m_unk0x008;                                    // 0x008
			Field0x64* m_unk0x030;                                        // 0x030
			Field0x34 m_unk0x034;                                         // 0x034
			LegoU32 m_flags0x090;                                         // 0x090
			undefined m_unk0x094[0x0c4 - 0x094];                          // 0x094
			GolBillboard* m_unk0x0c4;                                     // 0x0c4
			MabMaterialAnimationItem0x18 m_unk0x0c8;                      // 0x0c8
			LegoU32 m_unk0x0e0;                                           // 0x0e0
			RaceSessionField0x27d4::Item::Field0x004 m_unk0x0e4;          // 0x0e4
			RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x200; // 0x200
			MaterialTable0x0c m_unk0x204;                                 // 0x204
			undefined m_unk0x210[0x214 - 0x210];                          // 0x210
			void* m_unk0x214;                                             // 0x214
			undefined m_unk0x218[0x220 - 0x218];                          // 0x218
			Field0x68* m_unk0x220;                                        // 0x220
			Field0x224* m_unk0x224;                                       // 0x224
			undefined m_unk0x228[0x230 - 0x228];                          // 0x228
			LegoU32 m_unk0x230;                                           // 0x230
			LegoU32 m_unk0x234;                                           // 0x234
			LegoU32 m_unk0x238;                                           // 0x238
			LegoFloat m_unk0x23c;                                         // 0x23c
			LegoFloat m_unk0x240;                                         // 0x240
			LegoFloat m_unk0x244;                                         // 0x244
			LegoFloat m_unk0x248;                                         // 0x248
			LegoFloat m_unk0x24c;                                         // 0x24c
			LegoFloat m_unk0x250;                                         // 0x250
			LegoFloat m_unk0x254;                                         // 0x254
			LegoFloat m_unk0x258;                                         // 0x258
			LegoFloat m_unk0x25c;                                         // 0x25c
			LegoFloat m_unk0x260;                                         // 0x260
			LegoFloat m_unk0x264;                                         // 0x264
			LegoS32 m_unk0x268;                                           // 0x268
			Field0x270* m_next;                                           // 0x26c
		};

		// SIZE 0x80
		class Field0x18bc {
		public:
			// SIZE 0x14
			class Entry {
			public:
				Entry();
				~Entry();
				void Reset();
				void FUN_004515d0(LegoU32 p_elapsedMs);
				void FUN_00451610(GolD3DRenderDevice* p_renderer);
				void FUN_00451630();
				GolAnimatedEntity* GetUnk0x0c() { return m_unk0x0c; }
				LegoS32 GetUnk0x10() const { return m_unk0x10; }

			private:
				GolBillboard::Field0x2c m_unk0x00; // 0x00
				GolAnimatedEntity* m_unk0x0c;      // 0x0c
				LegoS32 m_unk0x10;                 // 0x10
			};

			Field0x18bc();
			~Field0x18bc();
			LegoS32 FUN_00451700();
			LegoS32 Reset();
			void FUN_00451860(LegoU32 p_elapsedMs);
			void FUN_004518a0(GolD3DRenderDevice* p_renderer);
			void FUN_004518d0();

		private:
			Entry m_entries[5];    // 0x00
			undefined4 m_unk0x64;  // 0x64
			undefined4 m_unk0x68;  // 0x68
			undefined4 m_unk0x6c;  // 0x6c
			undefined4 m_unk0x70;  // 0x70
			Field0x6dc* m_unk0x74; // 0x74
			undefined4 m_unk0x78;  // 0x78
			undefined4 m_unk0x7c;  // 0x7c
		};

		class Field0x1968 {
		public:
			virtual void VTable0x00() = 0;        // vtable+0x00
			virtual void VTable0x04() = 0;        // vtable+0x04
			virtual void VTable0x08() = 0;        // vtable+0x08
			virtual void VTable0x0c() = 0;        // vtable+0x0c
			virtual void VTable0x10(LegoU32) = 0; // vtable+0x10
		};

		// SIZE 0x30
		class Field0x1958Resource : public Field0x3c::Resource {
		public:
			void SetUnk0x18(const GolVec3& p_unk0x18) { m_unk0x18 = p_unk0x18; }
			void SetUnk0x24(const GolVec3& p_unk0x24) { m_unk0x24 = p_unk0x24; }

		private:
			friend class Field0x6dc;

			undefined m_unk0x04[0x18 - 0x04]; // 0x04
			GolVec3 m_unk0x18;                // 0x18
			GolVec3 m_unk0x24;                // 0x24
		};

		Field0x6dc();
		~Field0x6dc();
		void FUN_0045a490(LegoU32 p_elapsedMs);
		void FUN_0045a7b0(LegoBool32 p_unk0x04);
		void FUN_0045a8a0();
		void FUN_0045b740(RaceState::Racer* p_racer);
		void FUN_0045b900();
		void FUN_0045bb30();
		undefined4 GetUnk0x19a0() const { return m_unk0x19a0; }

	private:
		friend class RaceSession;
		friend class Field0x18bc;
		friend class Field0x68Field0x028;

		void FUN_00457a90();
		void FUN_00459e20();
		void FUN_0045a3f0(LegoU32 p_elapsedMs);
		void FUN_0045b7a0(Field0x1958Resource* p_resource, LegoU32 p_unk0x08, LegoS32 p_unk0x0c);
		LegoU32 FUN_0045ba40(GolAnimatedEntity* p_entity);
		Field0x1880* FUN_0045ba90(LegoU32* p_unk0x04);
		Field0x1880* FUN_0045bae0(LegoU32* p_unk0x04);

		enum {
			c_unk0x1978Slot1A = 0,
			c_unk0x1978Slot1B = 1,
			c_unk0x1978Slot4A = 2,
			c_unk0x1978Slot4B = 3,
			c_unk0x1978Slot2A = 4,
			c_unk0x1978Slot2B = 5,
			c_unk0x1978Slot3A = 6,
			c_unk0x1978Slot3B = 7,
			c_unk0x1978SlotCount = 8,
		};

		Field0x0* m_unk0x000;                   // 0x000
		GolD3DRenderDevice* m_renderer;         // 0x004
		GolBillboard::Field0x2c m_unk0x008;     // 0x008
		MabMaterialAnimation0x14 m_unk0x014;    // 0x014
		Field0x68Field0x028* m_unk0x028;        // 0x028
		Field0x68Field0x02c* m_unk0x02c;        // 0x02c
		Field0x68** m_unk0x030;                 // 0x030
		LegoU32 m_unk0x034;                     // 0x034
		LegoU32 m_unk0x038;                     // 0x038
		Field0x3c* m_unk0x03c;                  // 0x03c
		undefined4 m_unk0x040;                  // 0x040
		undefined m_unk0x044[0x048 - 0x044];    // 0x044
		undefined4 m_unk0x048;                  // 0x048
		undefined4 m_unk0x04c;                  // 0x04c
		undefined4 m_unk0x050;                  // 0x050
		undefined4 m_unk0x054;                  // 0x054
		undefined m_unk0x058[0x05c - 0x058];    // 0x058
		undefined4 m_unk0x05c;                  // 0x05c
		GolWorldDatabase* m_unk0x060;           // 0x060
		undefined4 m_unk0x064;                  // 0x064
		undefined4 m_unk0x068;                  // 0x068
		undefined4 m_unk0x06c;                  // 0x06c
		undefined4 m_unk0x070;                  // 0x070
		Field0x074* m_unk0x074;                 // 0x074
		Field0x1880* m_unk0x078;                // 0x078
		Field0x1880* m_unk0x07c;                // 0x07c
		Field0x1880* m_unk0x080;                // 0x080
		Field0x1880* m_unk0x084;                // 0x084
		Field0x1880* m_unk0x088;                // 0x088
		Field0x1880* m_unk0x08c;                // 0x08c
		Field0x1880* m_unk0x090;                // 0x090
		Field0x1880* m_unk0x094;                // 0x094
		Field0x1880* m_unk0x098;                // 0x098
		Field0x1880* m_unk0x09c;                // 0x09c
		Field0x1880* m_unk0x0a0;                // 0x0a0
		GolAnimatedEntity m_unk0x0a4[25];       // 0x0a4
		LegoU32 m_unk0x1878;                    // 0x1878
		LegoU32 m_unk0x187c;                    // 0x187c
		Field0x1880* m_unk0x1880;               // 0x1880
		LegoU8 m_unk0x1884[11];                 // 0x1884
		undefined m_unk0x188f;                  // 0x188f
		Field0x1890* m_unk0x1890;               // 0x1890
		Field0x1894* m_unk0x1894;               // 0x1894
		Field0x1898* m_unk0x1898;               // 0x1898
		Field0x189c* m_unk0x189c;               // 0x189c
		Field0x18a0* m_unk0x18a0;               // 0x18a0
		Field0x18a4* m_unk0x18a4;               // 0x18a4
		Field0x18a8* m_unk0x18a8;               // 0x18a8
		Field0x18ac* m_unk0x18ac;               // 0x18ac
		Field0x18b0* m_unk0x18b0;               // 0x18b0
		Field0x18b4* m_unk0x18b4;               // 0x18b4
		Field0x18b8* m_unk0x18b8;               // 0x18b8
		Field0x18bc m_unk0x18bc;                // 0x18bc
		Field0x270* m_unk0x193c;                // 0x193c
		Field0x270* m_unk0x1940;                // 0x1940
		Field0x270* m_unk0x1944;                // 0x1944
		Field0x270* m_unk0x1948;                // 0x1948
		LegoU8 m_unk0x194c;                     // 0x194c
		LegoU8 m_unk0x194d;                     // 0x194d
		undefined m_unk0x194e[0x1950 - 0x194e]; // 0x194e
		Field0x270* m_unk0x1950;                // 0x1950
		Field0x270* m_unk0x1954;                // 0x1954
		Field0x1958Resource* m_unk0x1958;       // 0x1958
		Field0x1958Resource* m_unk0x195c;       // 0x195c
		Field0x1958Resource* m_unk0x1960;       // 0x1960
		Field0x1958Resource* m_unk0x1964;       // 0x1964
		Field0x1968* m_unk0x1968;               // 0x1968
		Field0x1968* m_unk0x196c;               // 0x196c
		Field0x1968* m_unk0x1970;               // 0x1970
		Field0x1968* m_unk0x1974;               // 0x1974
		Field0x1880* m_unk0x1978[8];            // 0x1978
		undefined4 m_unk0x1998;                 // 0x1998
		LegoFloat m_unk0x199c;                  // 0x199c
		undefined4 m_unk0x19a0;                 // 0x19a0
	};

	// VTABLE: LEGORACERS 0x004b1d54
	// SIZE 0x14
	class Field0x2128 {
	public:
		// SIZE 0x3c
		class Entry {
		public:
			virtual void VTable0x00() = 0;           // vtable+0x00
			virtual void VTable0x04(undefined4) = 0; // vtable+0x04
			virtual void VTable0x08() = 0;           // vtable+0x08
			virtual void VTable0x0c(undefined4) = 0; // vtable+0x0c
			virtual void VTable0x10() = 0;           // vtable+0x10

		private:
			undefined m_unk0x04[0x3c - 0x04]; // 0x04
		};

		Field0x2128();
		virtual ~Field0x2128();                 // vtable+0x00
		virtual void Destroy();                 // vtable+0x04
		virtual LegoU32 VTable0x08(undefined4); // vtable+0x08
		virtual LegoU32 VTable0x0c();           // vtable+0x0c

		// SYNTHETIC: LEGORACERS 0x00464fc0
		// RaceSession::Field0x2128::`scalar deleting destructor'

	protected:
		undefined4 m_unk0x04; // 0x04
		undefined4 m_unk0x08; // 0x08
		LegoU32 m_count;      // 0x0c
		Entry* m_entries;     // 0x10
	};

	// VTABLE: LEGORACERS 0x004b1c74
	// SIZE 0x18
	class Field0x2080 : public Field0x2128 {
	public:
		// SIZE 0x58
		class Entry {
		public:
			virtual void VTable0x00() = 0;           // vtable+0x00
			virtual void VTable0x04(undefined4) = 0; // vtable+0x04
			virtual void VTable0x08() = 0;           // vtable+0x08
			virtual void VTable0x0c(undefined4) = 0; // vtable+0x0c
			virtual void VTable0x10() = 0;           // vtable+0x10

		private:
			undefined m_unk0x04[0x58 - 0x04]; // 0x04
		};

		Field0x2080();
		~Field0x2080() override;                 // vtable+0x00
		void Destroy() override;                 // vtable+0x04
		LegoU32 VTable0x08(undefined4) override; // vtable+0x08
		LegoU32 VTable0x0c() override;           // vtable+0x0c

		// SYNTHETIC: LEGORACERS 0x00463d50
		// RaceSession::Field0x2080::`scalar deleting destructor'

	private:
		Entry* m_unk0x14; // 0x14
	};

	// SIZE 0x90
	class Field0x2098 {
	public:
		// SIZE 0x20
		class Resource {
		public:
			enum {
				c_state0x18One = 1,
				c_state0x18Four = 4,
				c_state0x18Five = 5,
				c_flags0x1cBit1 = 1 << 1,
				c_flags0x1cBit2 = 1 << 2
			};

			virtual void VTable0x00(RaceState::Racer*) = 0; // vtable+0x00
			virtual void VTable0x04(undefined4) = 0;        // vtable+0x04
			virtual void VTable0x08(RaceState::Racer*) = 0; // vtable+0x08
			virtual void VTable0x0c() = 0;                  // vtable+0x0c
			virtual void VTable0x10(undefined4) = 0;        // vtable+0x10
			virtual void VTable0x14(LegoU32) = 0;           // vtable+0x14

			void FUN_0045eee0(RaceState::Racer* p_racer);
			void SetState0x18(LegoU32 p_state) { m_state0x18 = p_state; }

		private:
			undefined4 m_unk0x04;             // 0x04
			undefined4 m_unk0x08;             // 0x08
			undefined4 m_unk0x0c;             // 0x0c
			undefined4 m_unk0x10;             // 0x10
			undefined4 m_unk0x14;             // 0x14
			LegoU32 m_state0x18;              // 0x18
			LegoU8 m_flags0x1c;               // 0x1c
			undefined m_unk0x1d[0x20 - 0x1d]; // 0x1d
		};

		// SIZE 0x24
		class Resource0x24 : public Resource {
		private:
			undefined m_unk0x20[0x24 - 0x20]; // 0x20
		};

		// SIZE 0x2c
		class Resource0x2c : public Resource {
		private:
			undefined m_unk0x20[0x2c - 0x20]; // 0x20
		};

		// SIZE 0x30
		class Resource0x30 : public Resource {
		private:
			undefined m_unk0x20[0x30 - 0x20]; // 0x20
		};

		// SIZE 0x34
		class Resource0x34 : public Resource {
		private:
			undefined m_unk0x20[0x34 - 0x20]; // 0x20
		};

		// SIZE 0x38
		class Resource0x38 : public Resource {
		private:
			undefined m_unk0x20[0x38 - 0x20]; // 0x20
		};

		// SIZE 0x48
		class Resource0x48 : public Resource {
		private:
			undefined m_unk0x20[0x48 - 0x20]; // 0x20
		};

		// SIZE 0x5c
		class Resource0x5c : public Resource {
		private:
			undefined m_unk0x20[0x5c - 0x20]; // 0x20
		};

		// SIZE 0x64
		class Resource0x64 : public Resource {
		private:
			undefined m_unk0x20[0x64 - 0x20]; // 0x20
		};

		Field0x2098();
		~Field0x2098();
		void FUN_00461cc0(LegoU32 p_elapsedMs);
		void FUN_00462c60();
		void FUN_00462da0(RaceState::Racer* p_racer);

	private:
		friend class RaceSession;

		void Destroy();

		undefined4 m_unk0x00;             // 0x00
		undefined4 m_unk0x04;             // 0x04
		undefined4 m_unk0x08;             // 0x08
		undefined4 m_unk0x0c;             // 0x0c
		undefined4 m_unk0x10;             // 0x10
		undefined4 m_unk0x14;             // 0x14
		undefined m_unk0x18[0x20 - 0x18]; // 0x18
		undefined4 m_unk0x20;             // 0x20
		undefined4 m_unk0x24;             // 0x24
		LegoU32 m_unk0x28;                // 0x28
		LegoU32 m_unk0x2c;                // 0x2c
		LegoU32 m_unk0x30;                // 0x30
		LegoU32 m_unk0x34;                // 0x34
		LegoU32 m_unk0x38;                // 0x38
		LegoU32 m_unk0x3c;                // 0x3c
		LegoU32 m_unk0x40;                // 0x40
		LegoU32 m_unk0x44;                // 0x44
		LegoU32 m_unk0x48;                // 0x48
		LegoU32 m_unk0x4c;                // 0x4c
		LegoU32 m_unk0x50;                // 0x50
		LegoU32 m_unk0x54;                // 0x54
		LegoU32 m_unk0x58;                // 0x58
		Resource0x5c* m_unk0x5c;          // 0x5c
		Resource0x34* m_unk0x60;          // 0x60
		Resource0x34* m_unk0x64;          // 0x64
		Resource0x64* m_unk0x68;          // 0x68
		undefined* m_unk0x6c;             // 0x6c
		Resource0x34* m_unk0x70;          // 0x70
		Resource0x30* m_unk0x74;          // 0x74
		Resource0x2c* m_unk0x78;          // 0x78
		Resource0x48* m_unk0x7c;          // 0x7c
		Resource0x24* m_unk0x80;          // 0x80
		Resource0x34* m_unk0x84;          // 0x84
		Resource0x2c* m_unk0x88;          // 0x88
		Resource0x38* m_unk0x8c;          // 0x8c
	};

	// SIZE 0x0c
	class Field0x213c {
	public:
		// SIZE 0x24
		class Resource : public LegoEventQueue::Callback {
		public:
			void VTable0x00(LegoEventQueue::CallbackData* p_data) override = 0; // vtable+0x00
			virtual void VTable0x04(undefined4) = 0;                            // vtable+0x04

			void FUN_00464830(LegoU32 p_elapsedMs);
			LegoEventQueue::Event* FUN_00464a40(LegoU32 p_unk0x04);

		private:
			enum {
				c_flags0x1cBit1 = 1 << 1,
				c_randomTableMask = 0x3ff,
			};

			LegoEventQueue::Event* m_unk0x04; // 0x04
			undefined4 m_unk0x08;             // 0x08
			LegoEventQueue* m_unk0x0c;        // 0x0c
			LegoU32 m_unk0x10;                // 0x10
			LegoU32 m_unk0x14;                // 0x14
			LegoU32 m_unk0x18;                // 0x18
			LegoU32 m_unk0x1c;                // 0x1c
			undefined4 m_unk0x20;             // 0x20
		};

		Field0x213c();
		~Field0x213c();
		LegoU32 FUN_00464dd0(LegoU32 p_elapsedMs);

	private:
		friend class RaceSession;

		void Destroy();

		undefined4 m_unk0x00; // 0x00
		undefined4 m_unk0x04; // 0x04
		Resource* m_unk0x08;  // 0x08
	};

	typedef RaceEventDispatcher0x08 Field0x2148;

	// VTABLE: LEGORACERS 0x004b47a0
	// SIZE 0x0c
	class Field0x27c8 {
	public:
		Field0x27c8();
		virtual ~Field0x27c8(); // vtable+0x00

		// SYNTHETIC: LEGORACERS 0x004937d0
		// RaceSession::Field0x27c8::`scalar deleting destructor'

		void Destroy();

		// VTABLE: LEGORACERS 0x004b4794
		// SIZE 0x2a4
		class Item {
		public:
			// SIZE 0x4c
			class Field0x0dc {
			public:
				LegoU32 m_unk0x00;    // 0x00
				GolVec3 m_unk0x04[5]; // 0x04
				GolVec3 m_unk0x40;    // 0x40
			};

			enum {
				c_flags0x09cBit0 = 1 << 0,
				c_flags0x09cBit1 = 1 << 1,
				c_flags0x09cBit3 = 1 << 3,
				c_flags0x09cBit4 = 1 << 4,
				c_flags0x09cBit5 = 1 << 5,
			};

			Item();
			~Item();
			virtual Item* VTable0x00(undefined4 p_flags); // vtable+0x00

			void FUN_00492be0(LegoU32 p_elapsedMs);
			void FUN_00492c30(LegoU32 p_elapsedMs);
			void FUN_004931a0();
			void FUN_004513d0(GolD3DRenderDevice* p_renderer);
			void Destroy();
			void FUN_00493790(GolD3DRenderDevice* p_renderer);
			LegoU8 GetFlags0x09c() const { return m_flags0x09c; }
			LegoBool32 IsActive() const { return m_flags0x09c & c_flags0x09cBit0; }

		private:
			friend class Field0x27c8;

			void Reset();

			GolExport* m_unk0x004;               // 0x004
			GolModelBase* m_unk0x008;            // 0x008
			GolModelEntity m_unk0x00c;           // 0x00c
			LegoU8 m_flags0x09c;                 // 0x09c
			undefined m_unk0x09d[0x0a0 - 0x09d]; // 0x09d
			LegoU32 m_unk0x0a0;                  // 0x0a0
			LegoU32 m_unk0x0a4;                  // 0x0a4
			LegoU32 m_unk0x0a8;                  // 0x0a8
			LegoU32 m_unk0x0ac;                  // 0x0ac
			LegoU32 m_unk0x0b0;                  // 0x0b0
			LegoU32 m_unk0x0b4;                  // 0x0b4
			LegoU32 m_unk0x0b8;                  // 0x0b8
			LegoU32 m_unk0x0bc;                  // 0x0bc
			LegoU32 m_unk0x0c0[4];               // 0x0c0
			LegoFloat m_unk0x0d0;                // 0x0d0
			LegoFloat m_unk0x0d4;                // 0x0d4
			ColorRGBA m_unk0x0d8;                // 0x0d8
			Field0x0dc m_unk0x0dc[6];            // 0x0dc
		};

		LegoU32 FUN_00493a60(GolD3DRenderDevice* p_renderer);
		LegoU32 FUN_00493aa0(GolD3DRenderDevice* p_renderer);
		LegoU32 FUN_00493a20(LegoU32 p_elapsedMs);

	private:
		Item* m_items;   // 0x04
		LegoU32 m_count; // 0x08
	};

	// SIZE 0x14
	// VTABLE: LEGORACERS 0x004b0c04
	class Field0x27e0 : public GolNameTable {
	public:
		Field0x27e0();
		~Field0x27e0() override;
		void Clear() override;

		// SYNTHETIC: LEGORACERS 0x00443fc0
		// RaceSession::Field0x27e0::`scalar deleting destructor'

	private:
		undefined4 m_unk0x0c; // 0x0c
		undefined* m_unk0x10; // 0x10
	};

	// SIZE 0x30
	class Field0x280c {
	public:
		Field0x280c();
		~Field0x280c();
		void FUN_0042f430();
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

	typedef RaceCameraController Field0x2ad4;

	// SIZE 0xc8
	// VTABLE: LEGORACERS 0x004afd58
	class Field0x2f90 : public GolNameTable {
	public:
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

		Field0x2f90();
		~Field0x2f90() override;
		void Clear() override;
		void FUN_0041ccb0(LegoU32 p_elapsedMs);
		void FUN_0041d040(GolVec3* p_position);
		void FUN_0041d0f0(GolD3DRenderDevice* p_renderer);

		// SYNTHETIC: LEGORACERS 0x0041c490
		// RaceSession::Field0x2f90::`scalar deleting destructor'

	private:
		enum {
			c_flag0xc4Bit0 = 1 << 0,
			c_flag0xc4Bit1 = 1 << 1,
		};

		void Reset();
		void FUN_0041ce60(Entry* p_entry, ColorRGBA* p_unk0x08, ColorRGBA* p_unk0x0c, ColorRGBA* p_unk0x10);
		void FUN_0041cf20(const ColorRGBA* p_from, const ColorRGBA* p_to, ColorRGBA* p_result, LegoFloat p_amount);
		void FUN_0041cfc0(const ColorRGBA* p_unk0x04, const ColorRGBA* p_unk0x08, const ColorRGBA* p_unk0x0c);

		GolModelEntity m_unk0x0c;    // 0x0c
		GolWorldDatabase* m_unk0x9c; // 0x9c
		GolModelBase* m_unk0xa0;     // 0xa0
		GolExport* m_unk0xa4;        // 0xa4
		Entry* m_entries;            // 0xa8
		LegoFloat m_unk0xac;         // 0xac
		LegoU32 m_count;             // 0xb0
		LegoU32 m_unk0xb4;           // 0xb4
		LegoU32 m_unk0xb8;           // 0xb8
		LegoU32 m_unk0xbc;           // 0xbc
		LegoU32 m_unk0xc0;           // 0xc0
		LegoU8 m_unk0xc4;            // 0xc4
		undefined m_unk0xc5[3];      // 0xc5
	};

	// SIZE 0x08
	class Field0x27f4 {
	public:
		// SIZE 0x24
		class Entry {
		public:
			Entry();
			~Entry();

		private:
			void Reset();
			void FUN_0041e630();

			undefined4 m_unk0x00; // 0x00
			undefined4 m_unk0x04; // 0x04
			undefined4 m_unk0x08; // 0x08
			undefined4 m_unk0x0c; // 0x0c
			undefined4 m_unk0x10; // 0x10
			undefined4 m_unk0x14; // 0x14
			undefined4 m_unk0x18; // 0x18
			LegoFloat m_unk0x1c;  // 0x1c
			undefined4 m_unk0x20; // 0x20
		};

		Field0x27f4();
		~Field0x27f4();

	private:
		friend class RaceSession;

		void Reset();

		Entry* m_entries; // 0x00
		LegoU32 m_count;  // 0x04
	};

	// SIZE 0x08
	class Field0x2804 {
	public:
		// SIZE 0x14
		class Entry {
		public:
			Entry();
			~Entry();
			void FUN_0045c380(GolVec3* p_unk0x04, LegoS32 p_unk0x08);

		private:
			GolVec3 m_unk0x00;                // 0x00
			LegoS32 m_unk0x0c;                // 0x0c
			LegoU8 m_flags0x10;               // 0x10
			undefined m_unk0x11[0x14 - 0x11]; // 0x11
		};

		Field0x2804();
		~Field0x2804();

	private:
		friend class RaceSession;

		void Reset();

		Entry* m_entries; // 0x00
		LegoU32 m_count;  // 0x04
	};

	// SIZE 0x48
	class Field0x3104 {
	public:
		Field0x3104();
		~Field0x3104();
		void FUN_004a50a0();

	private:
		friend class RaceSession;

		void FUN_004a50c0();

		undefined4 m_unk0x00; // 0x00
		undefined* m_unk0x04; // 0x04
		undefined4 m_unk0x08; // 0x08
		undefined4 m_unk0x0c; // 0x0c
		undefined4 m_unk0x10; // 0x10
		undefined4 m_unk0x14; // 0x14
		undefined4 m_unk0x18; // 0x18
		undefined4 m_unk0x1c; // 0x1c
		LegoFloat m_unk0x20;  // 0x20
		undefined4 m_unk0x24; // 0x24
		undefined4 m_unk0x28; // 0x28
		undefined4 m_unk0x2c; // 0x2c
		undefined4 m_unk0x30; // 0x30
		undefined4 m_unk0x34; // 0x34
		undefined4 m_unk0x38; // 0x38
		LegoFloat m_unk0x3c;  // 0x3c
		undefined4 m_unk0x40; // 0x40
		undefined4 m_unk0x44; // 0x44
	};

	// SIZE 0x2c
	class Field0x30c4 {
	public:
		Field0x30c4();
		~Field0x30c4();

	private:
		friend class RaceSession;

		void Reset();
		void FUN_0043a690(const Field0x30c4* p_source);
		void FUN_0043a6e0();
		void FUN_0043a780();

		LegoRacers::Context* m_context;     // 0x00
		RaceState* m_raceState;             // 0x04
		Field0x6dc* m_unk0x08;              // 0x08
		Field0x2148* m_unk0x0c;             // 0x0c
		CutsceneAnimation* m_unk0x10;       // 0x10
		CutsceneAnimation* m_unk0x14;       // 0x14
		TimeRaceManager* m_timeRaceManager; // 0x18
		Field0x2080* m_unk0x1c;             // 0x1c
		Field0x2128* m_unk0x20;             // 0x20
		Field0x32c4* m_unk0x24;             // 0x24
		Field0x2098* m_unk0x28;             // 0x28
	};

	// SIZE 0x10
	typedef RaceSessionField0x32b4 Field0x32b4;

	// VTABLE: LEGORACERS 0x004b1acc
	// SIZE 0x3c
	class Field0x32c4 {
	public:
		// SIZE 0xac
		class Field0x1c {
		public:
			undefined m_unk0x000[0x0a8 - 0x000]; // 0x000
			LegoS32 m_unk0x0a8;                  // 0x0a8
		};

		Field0x32c4();
		virtual ~Field0x32c4(); // vtable+0x00
		void FUN_0045e470(LegoU32 p_elapsedMs);
		LegoU32 FUN_0045e5b0();

		// SYNTHETIC: LEGORACERS 0x0045e380
		// RaceSession::Field0x32c4::`scalar deleting destructor'

	private:
		friend class RaceSession;

		void Destroy();

		enum {
			c_racerCount = 6,
			c_maxElapsedChunk = 0xff,
			c_unk0x0a8Stride = 100,
		};

		RaceState::Racer* m_unk0x04[c_racerCount]; // 0x04
		Field0x1c* m_unk0x1c;                      // 0x1c
		LegoU8* m_unk0x20[c_racerCount];           // 0x20
		LegoU32 m_unk0x38;                         // 0x38
	};

private:
	void FUN_00431bd0();
	void FUN_004328d0();
	void FUN_004328f0();
	LegoU32 FUN_00432a50(LegoU32 p_index, LegoChar* p_buffer);
	void FUN_00432b30();
	void FUN_00432bc0();
	void FUN_00432d70();
	void FUN_00432dc0();
	void FUN_00432df0();
	void FUN_004330e0();
	void FUN_00433460();
	void FUN_00434000();
	void FUN_00434170();
	void FUN_00434300();
	void FUN_00434340();
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
	undefined m_unk0x1c;                    // 0x1c
	undefined m_unk0x1d[0x05c - 0x01d];     // 0x1d
	undefined m_unk0x5c;                    // 0x5c
	undefined m_unk0x5d[0x069 - 0x05d];     // 0x5d
	undefined m_unk0x69;                    // 0x69
	undefined m_unk0x6a[0x076 - 0x06a];     // 0x6a
	undefined m_unk0x76;                    // 0x76
	undefined m_unk0x77[0x083 - 0x077];     // 0x77
	undefined m_unk0x83;                    // 0x83
	undefined m_unk0x84[0x090 - 0x084];     // 0x84
	undefined m_unk0x90;                    // 0x90
	undefined m_unk0x91[0x09d - 0x091];     // 0x91
	undefined m_unk0x9d;                    // 0x9d
	undefined m_unk0x9e[0x0aa - 0x09e];     // 0x9e
	undefined m_unk0xaa;                    // 0xaa
	undefined m_unk0xab[0x0b7 - 0x0ab];     // 0xab
	undefined m_unk0xb7;                    // 0xb7
	undefined m_unk0xb8[0x0c4 - 0x0b8];     // 0xb8
	undefined m_unk0xc4;                    // 0xc4
	undefined m_unk0xc5[0x0d1 - 0x0c5];     // 0xc5
	undefined m_unk0xd1;                    // 0xd1
	undefined m_unk0xd2[0x0de - 0x0d2];     // 0xd2
	undefined m_unk0xde;                    // 0xde
	undefined m_unk0xdf[0x0eb - 0x0df];     // 0xdf
	undefined m_unk0xeb;                    // 0xeb
	undefined m_unk0xec[0x0f8 - 0x0ec];     // 0xec
	undefined m_unk0xf8;                    // 0xf8
	undefined m_unk0xf9[0x105 - 0x0f9];     // 0xf9
	undefined m_unk0x105;                   // 0x105
	undefined m_unk0x106[0x112 - 0x106];    // 0x106
	undefined m_unk0x112;                   // 0x112
	undefined m_unk0x113[0x11f - 0x113];    // 0x113
	undefined m_unk0x11f;                   // 0x11f
	undefined m_unk0x120[0x12c - 0x120];    // 0x120
	undefined m_unk0x12c;                   // 0x12c
	undefined m_unk0x12d[0x146 - 0x12d];    // 0x12d
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
	Field0x21c* m_unk0x21c;                 // 0x21c
	InputEventQueue m_inputEvents;          // 0x220
	Field0x23c m_unk0x23c;                  // 0x23c
	Field0x258 m_unk0x258[2];               // 0x258
	Field0x340 m_unk0x340[2];               // 0x340
	GolWorldDatabase* m_unk0x390;           // 0x390
	undefined4 m_unk0x394;                  // 0x394
	GolWorldDatabase* m_unk0x398;           // 0x398
	GolWorldDatabase* m_unk0x39c;           // 0x39c
	GolWorldDatabase* m_unk0x3a0;           // 0x3a0
	GolWorldDatabase* m_unk0x3a4;           // 0x3a4
	GolWorldDatabase* m_unk0x3a8;           // 0x3a8
	Field0x3ac* m_unk0x3ac;                 // 0x3ac
	undefined4 m_unk0x3b0;                  // 0x3b0
	undefined4 m_unk0x3b4;                  // 0x3b4
	undefined4 m_unk0x3b8;                  // 0x3b8
	RaceState m_raceState;                  // 0x3bc
	Field0x6dc m_unk0x6dc;                  // 0x6dc
	Field0x2080 m_unk0x2080;                // 0x2080
	Field0x2098 m_unk0x2098;                // 0x2098
	Field0x2128 m_unk0x2128;                // 0x2128
	Field0x213c m_unk0x213c;                // 0x213c
	Field0x2148 m_unk0x2148;                // 0x2148
	CutsceneAnimation m_unk0x2150;          // 0x2150
	CutsceneAnimation m_unk0x248c;          // 0x248c
	Field0x27c8 m_unk0x27c8;                // 0x27c8
	RaceSessionField0x27d4 m_unk0x27d4;     // 0x27d4
	Field0x27e0 m_unk0x27e0;                // 0x27e0
	Field0x27f4 m_unk0x27f4;                // 0x27f4
	MenuAnimationList m_unk0x27fc;          // 0x27fc
	Field0x2804 m_unk0x2804;                // 0x2804
	Field0x280c m_unk0x280c;                // 0x280c
	CobaltTrail0x140 m_unk0x283c[2];        // 0x283c
	LegoFloat m_unk0x2abc;                  // 0x2abc
	LegoFloat m_unk0x2ac0;                  // 0x2ac0
	LegoFloat m_unk0x2ac4;                  // 0x2ac4
	LegoFloat m_unk0x2ac8;                  // 0x2ac8
	GolCamera* m_unk0x2acc[2];              // 0x2acc
	Field0x2ad4 m_unk0x2ad4[2];             // 0x2ad4
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
	Field0x3104 m_unk0x3104[6];             // 0x3104
	Field0x32b4 m_unk0x32b4;                // 0x32b4
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
