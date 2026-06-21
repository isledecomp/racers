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
	class Field0x27c8;
	class Field0x2098;
	class Field0x2f90;
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

		LegoS32 FUN_00427960();

		DirectInputDevice* m_unk0x04;        // 0x04
		Field0x258::Field0x04* m_unk0x08[2]; // 0x08
		LegoU32 m_unk0x10;                   // 0x10
		InputDevice::Callback* m_unk0x14;    // 0x14
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
			// SIZE 0x1c
			class Params {
			public:
				LegoU32 m_unk0x00;   // 0x00
				LegoU32 m_unk0x04;   // 0x04
				LegoU32 m_unk0x08;   // 0x08
				LegoU32 m_unk0x0c;   // 0x0c
				LegoU32 m_unk0x10;   // 0x10
				LegoFloat m_unk0x14; // 0x14
				LegoFloat m_unk0x18; // 0x18
			};

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
				c_flags0x09cBit2 = 1 << 2,
				c_flags0x09cBit3 = 1 << 3,
				c_flags0x09cBit4 = 1 << 4,
				c_flags0x09cBit5 = 1 << 5,
			};

			Item();
			~Item();
			virtual Item* VTable0x00(undefined4 p_flags); // vtable+0x00

			void FUN_00492a50(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
			void FUN_00492a90(GolD3DRenderDevice* p_renderer, DuskwindBananaRelic0x24* p_material);
			void FUN_00492ab0(const ColorRGBA* p_color);
			void FUN_00492ae0(Params* p_params);
			void FUN_00492bd0();
			void FUN_00492be0(LegoU32 p_elapsedMs);
			void FUN_00492c30(LegoU32 p_elapsedMs);
			void FUN_00492ee0(
				LegoU32 p_elapsedMs,
				GolVec3* p_positions,
				LegoFloat p_unk0x0c,
				LegoFloat p_unk0x10,
				LegoFloat p_unk0x14
			);
			void FUN_00492f10(LegoU32 p_elapsedMs, GolVec3* p_positions);
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
			LegoU32 m_unk0x0c0;                  // 0x0c0
			LegoFloat m_unk0x0c4;                // 0x0c4
			LegoFloat m_unk0x0c8;                // 0x0c8
			LegoFloat m_unk0x0cc;                // 0x0cc
			LegoFloat m_unk0x0d0;                // 0x0d0
			LegoFloat m_unk0x0d4;                // 0x0d4
			ColorRGBA m_unk0x0d8;                // 0x0d8
			Field0x0dc m_unk0x0dc[6];            // 0x0dc
		};

		LegoU32 FUN_00493a60(GolD3DRenderDevice* p_renderer);
		LegoU32 FUN_00493aa0(GolD3DRenderDevice* p_renderer);
		Item* FUN_004939b0(Item::Params* p_params);
		void FUN_00493a10(Item* p_item);
		LegoU32 FUN_00493a20(LegoU32 p_elapsedMs);
		void FUN_00493850(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, LegoU32 p_count);

	private:
		Item* m_items;   // 0x04
		LegoU32 m_count; // 0x08
	};

	// SIZE 0x19a4
	class Field0x6dc {
	public:
		class Field0x0 : public GolExport {
		public:
			GolBillboard* CreateBillboard() { return static_cast<GolBillboard*>(VTable0x30()); }
		};

		typedef RaceResourceManager Field0x3c;

		// VTABLE: LEGORACERS 0x004b1884
		// SIZE 0x1fc
		class PwbTxtParser : public GolTxtParser {};

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
			LegoEventQueue* GetEventQueue() { return &m_eventQueue; }
			GolMaterialLibrary* GetUnk0x298() const { return m_unk0x298; }
			RaceState::Racer* GetUnk0x140() const { return m_unk0x140; }
			RaceState::Racer* GetRacer(LegoU32 p_index) const { return &m_unk0x140[p_index]; }
			RaceState::Racer* GetRacerByOffset(LegoS32 p_offset) const
			{
				return (RaceState::Racer*) ((LegoU8*) m_unk0x140 + p_offset);
			}

		private:
			undefined m_unk0x000[0x0f0 - 0x000]; // 0x000
			LegoEventQueue m_eventQueue;         // 0x0f0
			undefined m_unk0x118[0x140 - 0x118]; // 0x118
			RaceState::Racer* m_unk0x140;        // 0x140
			undefined m_unk0x144[0x170 - 0x144]; // 0x144
			Field0x170* m_unk0x170;              // 0x170
			undefined m_unk0x174[0x298 - 0x174]; // 0x174
			GolMaterialLibrary* m_unk0x298;      // 0x298
		};

		typedef Field0x0 Field0x64;

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

		// VTABLE: LEGORACERS 0x004b47a8
		// SIZE 0x98
		class Field0x98 : public GolModelEntity {
		public:
			Field0x98();
			~Field0x98();
			Field0x98* FUN_00494c20(undefined4 p_flags);
			void VTable0x1c(GolRenderDevice& p_renderer) override; // vtable+0x1c
			void FUN_00494c50(
				GolModelBase* p_model,
				GolSceneNode* p_sceneNode,
				undefined4 p_unk0x0c,
				LegoFloat p_modelDistance
			);
			void VTable0x54() override;
			GolSceneNode* VTable0x58(undefined4) override; // vtable+0x58

		private:
			GolSceneNode* m_unk0x90; // 0x90
			undefined4 m_unk0x94;    // 0x94
		};

		// SIZE 0x170
		class Field0x170 {
		public:
			enum {
				c_flags0x140Bit0 = 1 << 0,
				c_flags0x140Bit1 = 1 << 1,
				c_flags0x140Bit2 = 1 << 2,
				c_group0x20000000 = 0x20000000,
				c_group0x80000000 = 0x80000000,
				c_group0xa0000000 = 0xa0000000,
				c_group0xc0000000 = 0xc0000000
			};

			// SIZE 0x74
			struct SetupParams {
				Field0x0* m_unk0x00;                 // 0x00
				GolRenderDevice* m_renderer;         // 0x04
				DuskwindBananaRelic0x24* m_material; // 0x08
				LegoU32 m_unk0x0c;                   // 0x0c
				LegoU32 m_unk0x10;                   // 0x10
				LegoU32 m_unk0x14;                   // 0x14
				GolVec3 m_unk0x18[3];                // 0x18
				undefined4 m_unk0x3c[6];             // 0x3c
				LegoFloat m_unk0x54[5];              // 0x54
				LegoU32 m_unk0x68;                   // 0x68
				LegoFloat m_modelDistance;           // 0x6c
				undefined4 m_unk0x70;                // 0x70
			};

			Field0x170();
			~Field0x170();
			void Reset();
			void FUN_00493c90(const SetupParams* p_params);
			void FUN_00493e60();
			void FUN_00493ea0(const GolVec3* p_position, const GolVec3* p_direction);
			void FUN_00494030(const GolVec3* p_position);
			void FUN_00494140(const GolVec3* p_position);
			void FUN_00494230();
			void FUN_00494290(
				const GolVec3* p_position,
				const ColorRGBA* p_color,
				LegoU32 p_textureColumn,
				LegoU32 p_offsetIndex
			);
			void FUN_00494480();
			void FUN_004944e0();
			void FUN_004946b0();
			void FUN_00494820(const ColorRGBA* p_unk0x04, const ColorRGBA* p_unk0x08, const ColorRGBA* p_unk0x0c);
			void FUN_00494850(GolD3DRenderDevice* p_renderer);
			void FUN_00494870(const GolVec3* p_position, LegoFloat p_amount);
			void FUN_00494ad0(
				const GolVec3* p_fromPosition,
				const GolVec3* p_toPosition,
				const ColorRGBA* p_fromColor,
				const ColorRGBA* p_toColor,
				ColorRGBA* p_colorResult,
				GolVec3* p_positionResult,
				LegoFloat p_amount
			);
			void FUN_00494be0(const GolVec3* p_offsets);

		private:
			GolExport* m_unk0x000;                      // 0x000
			GolModelBase* m_unk0x004;                   // 0x004
			GdbVertexArray0xc* m_unk0x008;              // 0x008
			GdbModelIndexArray0xc::Indices* m_unk0x00c; // 0x00c
			GolSceneNode* m_unk0x010;                   // 0x010
			DuskwindBananaRelic0x24* m_unk0x014;        // 0x014
			Field0x98 m_unk0x018;                       // 0x018
			LegoS32 m_unk0x0b0;                         // 0x0b0
			LegoS32 m_unk0x0b4;                         // 0x0b4
			LegoS32 m_unk0x0b8;                         // 0x0b8
			LegoU32 m_unk0x0bc;                         // 0x0bc
			LegoU32 m_unk0x0c0;                         // 0x0c0
			LegoU32 m_unk0x0c4;                         // 0x0c4
			LegoU32 m_unk0x0c8;                         // 0x0c8
			LegoU32 m_unk0x0cc;                         // 0x0cc
			LegoU32 m_unk0x0d0;                         // 0x0d0
			LegoU32 m_unk0x0d4;                         // 0x0d4
			LegoFloat m_unk0x0d8;                       // 0x0d8
			LegoU32 m_unk0x0dc;                         // 0x0dc
			LegoU32 m_unk0x0e0;                         // 0x0e0
			LegoU32 m_unk0x0e4;                         // 0x0e4
			LegoU32 m_unk0x0e8;                         // 0x0e8
			GolVec3 m_unk0x0ec[5];                      // 0x0ec
			LegoFloat m_unk0x128[5];                    // 0x128
			LegoU32 m_unk0x13c;                         // 0x13c
			LegoU32 m_unk0x140;                         // 0x140
			const GolVec3* m_unk0x144;                  // 0x144
			GolVec3 m_unk0x148;                         // 0x148
			GolVec3 m_unk0x154;                         // 0x154
			ColorRGBA m_unk0x160;                       // 0x160
			ColorRGBA m_unk0x164;                       // 0x164
			ColorRGBA m_unk0x168;                       // 0x168
			undefined4 m_unk0x16c;                      // 0x16c
		};

		// VTABLE: LEGORACERS 0x004b0778
		// SIZE 0xa8
		class Field0xa8 : public LegoEventQueue::Callback {
		public:
			// SIZE 0x28
			class Params {
			public:
				GolWorldEntity* m_unk0x00;         // 0x00
				RaceSessionField0x32b4* m_unk0x04; // 0x04
				LegoFloat m_unk0x08;               // 0x08
				LegoEventQueue* m_unk0x0c;         // 0x0c
				GolVec3 m_unk0x10;                 // 0x10
				LegoFloat m_unk0x1c;               // 0x1c
				LegoU32 m_unk0x20;                 // 0x20
				LegoFloat m_unk0x24;               // 0x24
			};

			Field0xa8();
			~Field0xa8();
			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			virtual void VTable0x04(Params* p_params, GolVec3* p_unk0x08);  // vtable+0x04
			virtual void VTable0x08(                                                      // vtable+0x08
				Params* p_params,
				RaceState::Racer* p_racer,
				GolVec3* p_unk0x0c,
				GolVec3* p_unk0x10,
				LegoBool32 p_unk0x14
			);
			virtual void VTable0x0c(                                                            // vtable+0x0c
				Params* p_params,
				RaceState::Racer* p_racer,
				RaceState::Racer* p_targetRacer,
				LegoBool32 p_unk0x10,
				LegoBool32 p_unk0x14
			);
			virtual Field0xa8* VTable0x10(undefined4);       // vtable+0x10
			virtual void VTable0x14();                       // vtable+0x14
			virtual LegoS32 VTable0x18(LegoU32 p_elapsedMs); // vtable+0x18
			virtual void VTable0x1c(GolVec3*);               // vtable+0x1c

			void Reset();
			void FUN_004316d0();
			void FUN_00430d40(Params* p_params);
			void FUN_00431310(RaceState::Racer* p_racer);
			void FUN_00431450(LegoFloat p_durationSeconds);
			void FUN_004314d0(LegoEventQueue* p_eventQueue);
			LegoU32 GetUnk0x004() const { return m_unk0x004; }
			GolWorldEntity* GetUnk0x008() { return m_unk0x008; }
			const GolVec3& GetUnk0x028() const { return m_unk0x028; }
			const GolVec3& GetUnk0x05c() const { return m_unk0x05c; }
			RaceState::Racer* GetUnk0x0a4() const { return m_unk0x0a4; }

		protected:
			undefined4 m_unk0x004;               // 0x004
			GolWorldEntity* m_unk0x008;          // 0x008
			RaceSessionField0x32b4* m_unk0x00c;  // 0x00c
			GolVec3 m_unk0x010;                  // 0x010
			GolVec3 m_unk0x01c;                  // 0x01c
			GolVec3 m_unk0x028;                  // 0x028
			LegoFloat m_unk0x034;                // 0x034
			LegoFloat m_unk0x038;                // 0x038
			LegoFloat m_unk0x03c;                // 0x03c
			LegoFloat m_unk0x040;                // 0x040
			LegoEventQueue::Event* m_unk0x044;   // 0x044
			LegoFloat m_unk0x048;                // 0x048
			LegoFloat m_unk0x04c;                // 0x04c
			LegoS32 m_unk0x050;                  // 0x050
			undefined4 m_unk0x054;               // 0x054
			LegoU32 m_unk0x058;                  // 0x058
			GolVec3 m_unk0x05c;                  // 0x05c
			undefined m_unk0x068[0x09c - 0x068]; // 0x068
			RaceState::Racer* m_unk0x09c;        // 0x09c
			RaceState::Racer* m_unk0x0a0;        // 0x0a0
			RaceState::Racer* m_unk0x0a4;        // 0x0a4
		};

		class Field0x18ac;

		// VTABLE: LEGORACERS 0x004b0248
		// SIZE 0xf8
		class Field0xf8 : public Field0xa8 {
		public:
			Field0xf8();
			Field0xa8* VTable0x10(undefined4 p_flags) override;
			LegoS32 VTable0x18(LegoU32 p_elapsedMs) override;
			void VTable0x1c(GolVec3* p_unk0x04) override;
			void FUN_00423630();
			void FUN_00423640(
				LegoU32 p_elapsedMs,
				RaceState::Racer::Field0x00c* p_unk0x08,
				LegoFloat p_unk0x0c,
				LegoFloat p_unk0x10,
				LegoFloat p_unk0x14
			);
			void FUN_00423980();
			void FUN_00423ed0(LegoFloat p_elapsedSeconds, GolVec3* p_unk0x08, GolVec3* p_unk0x0c);

		protected:
			friend class Field0x18ac;

			enum {
				c_racerFlags0xd04InvalidTargetMask = 0x11,
				c_racerFlags0xaa8Bit7 = 1 << 7,
				c_targetRefreshMs = 1000,
			};

			GolVec3 m_unk0x0a8;                       // 0x0a8
			LegoFloat m_unk0x0b4;                     // 0x0b4
			LegoFloat m_unk0x0b8;                     // 0x0b8
			LegoFloat m_unk0x0bc;                     // 0x0bc
			LegoFloat m_unk0x0c0;                     // 0x0c0
			GolVec3 m_unk0x0c4;                       // 0x0c4
			GolVec3 m_unk0x0d0;                       // 0x0d0
			GolVec3 m_unk0x0dc;                       // 0x0dc
			LegoU32 m_unk0x0e8;                       // 0x0e8
			RaceState::Racer::Field0xcc4* m_unk0x0ec; // 0x0ec
			LegoU32 m_unk0x0f0;                       // 0x0f0
			undefined4 m_unk0x0f4;                    // 0x0f4
		};

		// VTABLE: LEGORACERS 0x004b0ca8
		// SIZE 0x238
		class Field0x238 : public Field0xa8 {
		public:
			// SIZE 0x20
			struct SetupParams {
				Field0x0* m_unk0x00;                 // 0x00
				LegoFloat m_unk0x04;                 // 0x04
				LegoFloat m_unk0x08;                 // 0x08
				LegoFloat m_unk0x0c;                 // 0x0c
				ColorRGBA m_unk0x10;                 // 0x10
				ColorRGBA m_unk0x14;                 // 0x14
				ColorRGBA m_unk0x18;                 // 0x18
				DuskwindBananaRelic0x24* m_material; // 0x1c
			};

			Field0x238();
			~Field0x238();
			Field0xa8* VTable0x10(undefined4) override;
			void VTable0x14() override;
			LegoS32 VTable0x18(LegoU32 p_elapsedMs) override;
			virtual void VTable0x20(const SetupParams* p_params);    // vtable+0x20
			virtual void VTable0x24(GolD3DRenderDevice* p_renderer); // vtable+0x24

			void FUN_00444ac0(GolVec3* p_unk0x04);

		private:
			enum {
				c_flags0x234Bit0 = 1 << 0,
				c_flags0x234Bit1 = 1 << 1,
			};

			void FUN_00444540(const GolVec3* p_position, LegoU32 p_elapsedMs, LegoFloat p_amount);
			LegoS32 FUN_00444690(LegoU32 p_elapsedMs);
			LegoS32 FUN_00444820(LegoU32 p_elapsedMs);

			Field0x170 m_unk0x0a8; // 0x0a8
			LegoFloat m_unk0x218;  // 0x218
			LegoFloat m_unk0x21c;  // 0x21c
			LegoFloat m_unk0x220;  // 0x220
			LegoFloat m_unk0x224;  // 0x224
			GolVec3 m_unk0x228;    // 0x228
			LegoU32 m_unk0x234;    // 0x234
		};

		// SIZE 0x18
		class Field0x1880 : public LegoEventQueue::Callback {
		public:
			typedef LegoEventQueue::CallbackData VTable0x00Param;

			void VTable0x00(VTable0x00Param* p_param) override = 0; // vtable+0x00
			virtual Field0x1880* VTable0x04(undefined4) = 0;        // vtable+0x04
			virtual void VTable0x08(LegoU32) = 0;                   // vtable+0x08
			virtual void VTable0x0c(GolD3DRenderDevice*) = 0;       // vtable+0x0c
			virtual void VTable0x10(GolD3DRenderDevice*) = 0;       // vtable+0x10
			virtual void VTable0x14() = 0;                          // vtable+0x14
			virtual LegoS32 VTable0x18() = 0;                       // vtable+0x18
			virtual void VTable0x1c() = 0;                          // vtable+0x1c

			Field0x1880* GetNext() { return m_next; }
			LegoS32 GetUnk0x04() const { return m_unk0x004; }
			LegoU32 GetState() const { return m_state; }
			void SetUnk0x04(LegoS32 p_unk0x04) { m_unk0x004 = p_unk0x04; }
			void SetUnk0x010(RaceState::Racer::Field0x004* p_unk0x010) { m_unk0x010 = p_unk0x010; }
			void SetNext(Field0x1880* p_next) { m_next = p_next; }

		protected:
			LegoS32 m_unk0x004;                       // 0x004
			LegoU32 m_unk0x008;                       // 0x008
			Field0x1880* m_next;                      // 0x00c
			RaceState::Racer::Field0x004* m_unk0x010; // 0x010
			LegoU32 m_state;                          // 0x014
		};

		// VTABLE: LEGORACERS 0x004b132c
		// SIZE 0x18
		class ResourceBase : public Field0x1880 {
		public:
			ResourceBase();
			~ResourceBase();
			void VTable0x00(VTable0x00Param* p_param) override;   // vtable+0x00
			Field0x1880* VTable0x04(undefined4 p_flags) override; // vtable+0x04
			void VTable0x08(LegoU32) override;                    // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice*) override;        // vtable+0x0c
			void VTable0x10(GolD3DRenderDevice*) override;        // vtable+0x10
			void VTable0x14() override = 0;                       // vtable+0x14
			LegoS32 VTable0x18() override = 0;                    // vtable+0x18
			void VTable0x1c() override;                           // vtable+0x1c
		};

		// SIZE 0x2c
		class ResourceBase0x2c : public ResourceBase {
		public:
			enum {
				c_racerFlags0xd04Bit0 = 1 << 0,
			};

			ResourceBase0x2c();

			// SYNTHETIC: LEGORACERS 0x00451960
			// RaceSession::Field0x6dc::ResourceBase0x2c::~ResourceBase0x2c

			// SYNTHETIC: LEGORACERS 0x00456300
			// RaceSession::Field0x6dc::ResourceBase0x2c::`scalar deleting destructor'

			void VTable0x00(VTable0x00Param* p_param) override; // vtable+0x00
			void VTable0x14() override;                         // vtable+0x14
			LegoS32 VTable0x18() override;                      // vtable+0x18
			virtual void VTable0x20(RaceState::Racer* p_racer); // vtable+0x20

		protected:
			void FUN_00456360(
				RaceState::Racer* p_racer,
				GolVec3* p_position,
				RaceSessionField0x32b4::Field0x0c* p_record
			);

			Field0x074* m_unk0x018;             // 0x018
			LegoEventQueue::Event* m_unk0x01c;  // 0x01c
			RaceSessionField0x32b4* m_unk0x020; // 0x020
			undefined4 m_unk0x024;              // 0x024
			RaceState::Racer* m_unk0x028;       // 0x028
		};

		// SIZE 0x30
		class ResourceBase0x30 : public ResourceBase {
		public:
			ResourceBase0x30();
			void VTable0x14() override;                         // vtable+0x14
			LegoS32 VTable0x18() override;                      // vtable+0x18
			virtual void VTable0x20(RaceState::Racer* p_racer); // vtable+0x20
			virtual void VTable0x24(GolVec3* p_unk0x04);        // vtable+0x24
			virtual void VTable0x28(GolVec3* p_unk0x04);        // vtable+0x28

		protected:
			Field0xa8* m_unk0x018; // 0x018
			union {
				Field0x64** m_unk0x01c;   // 0x01c
				Field0x6dc* m_owner0x01c; // 0x01c
			};
			RaceSessionField0x32b4* m_unk0x020; // 0x020
			RaceState::Racer* m_unk0x024;       // 0x024
			RaceState::Racer* m_unk0x028;       // 0x028
			GolVec3* m_unk0x02c;                // 0x02c
		};

		// VTABLE: LEGORACERS 0x004b14b0
		// SIZE 0x54
		class Field0x68 : public LegoEventQueue::Callback {
		public:
			typedef GolWorldEntity Field0x08;

			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			virtual void VTable0x04(RaceState::Racer* p_racer) = 0;         // vtable+0x04
			virtual ~Field0x68();                                           // vtable+0x08
			virtual void VTable0x0c();                                      // vtable+0x0c
			virtual void VTable0x10(GolD3DRenderDevice* p_renderer);        // vtable+0x10
			virtual void VTable0x14(GolD3DRenderDevice* p_renderer);        // vtable+0x14

			// SYNTHETIC: LEGORACERS 0x00453940
			// RaceSession::Field0x6dc::Field0x68::`scalar deleting destructor'

			Field0x68();
			void FUN_004539b0(
				Field0x6dc* p_owner,
				RaceState::Racer::Field0x004* p_soundResource,
				GolVec3* p_position,
				GolModelEntity* p_model0,
				GolModelEntity* p_model1
			);
			void FUN_00453a10();
			LegoS32 FUN_00453970();

			void SetFlags0x50Bit0() { m_flags0x50 |= c_flags0x50Bit0; }
			void ClearFlags0x50Bit0() { m_flags0x50 &= ~c_flags0x50Bit0; }
			void ClearUnk0x24() { m_unk0x08.ClearVelocityX(); }
			Field0x08* GetUnk0x08() { return &m_unk0x08; }

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
				c_racerFlags0xd04Bit4 = 1 << 4,
			};

			void FUN_00453a20(LegoU32 p_elapsedMs);
			void FUN_00453ad0(LegoBool32 p_unk0x04);

			Field0x6dc* m_unk0x04;                   // 0x04
			Field0x08 m_unk0x08;                     // 0x08
			LegoFloat m_unk0x30;                     // 0x30
			GolModelEntity* m_unk0x34;               // 0x34
			GolModelEntity* m_unk0x38;               // 0x38
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
			Field0x68Field0x028();
			~Field0x68Field0x028() override;
			void VTable0x04(RaceState::Racer* p_racer) override;
			void VTable0x0c() override;
			void VTable0x10(GolD3DRenderDevice* p_renderer) override;
			void VTable0x14(GolD3DRenderDevice* p_renderer) override;

			// SYNTHETIC: LEGORACERS 0x00458e20
			// RaceSession::Field0x6dc::Field0x68Field0x028::`vector deleting destructor'

			void FUN_004576c0(LegoU32 p_unk0x04);
			void FUN_00457700();
			void FUN_00457710(LegoU32 p_elapsedMs);
			void FUN_004578e0(DuskwindBananaRelic0x24* p_unk0x04, DuskwindBananaRelic0x24* p_unk0x08);
			void SetUnk0x48(LegoU32 p_unk0x48) { m_unk0x48 = p_unk0x48; }

		private:
			DuskwindBananaRelic0x24* m_unk0x54; // 0x54
			DuskwindBananaRelic0x24* m_unk0x58; // 0x58
			LegoU32 m_unk0x5c;                  // 0x5c
			LegoU32 m_unk0x60;                  // 0x60
			LegoU32 m_unk0x64;                  // 0x64
		};

		class Field0x68Field0x02c;

		// VTABLE: LEGORACERS 0x004b15fc
		// SIZE 0x84
		class Field0x1890 : public ResourceBase0x2c {
		public:
			enum {
				c_timer0x03e8 = 0x03e8,
				c_timer0x0fa0 = 0x0fa0,
				c_timer0x4e20 = 0x4e20,
				c_sound0x21 = 0x21,
				c_sound0x22 = 0x22,
				c_sound0x23 = 0x23,
				c_sound0x4a = 0x4a,
				c_flags0x80Bit0 = 1 << 0,
				c_flags0x80Bit1 = 1 << 1,
				c_racerFlags0xd04Bit3 = 1 << 3,
				c_racerField0xc70Flags0x014Bit0 = 1 << 0,
			};

			Field0x1890();
			~Field0x1890();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x10(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
			void VTable0x14() override;                               // vtable+0x14
			void VTable0x1c() override;                               // vtable+0x1c
			void VTable0x20(RaceState::Racer* p_racer) override;      // vtable+0x20

			void FUN_00455810(
				Field0x6dc* p_unk0x04,
				Field0x074* p_unk0x08,
				RaceSessionField0x32b4* p_unk0x0c,
				undefined4 p_unk0x10,
				Field0x0* p_unk0x14,
				GolD3DRenderDevice* p_unk0x18,
				undefined4 p_unk0x1c
			);
			void FUN_004557c0();
			void FUN_004557e0();
			void FUN_004560b0();

		private:
			GolVec3 m_unk0x2c;            // 0x2c
			Field0x6dc* m_unk0x38;        // 0x38
			GolAnimatedEntity* m_unk0x3c; // 0x3c
			GolAnimatedEntity* m_unk0x40; // 0x40
			GolAnimatedEntity* m_unk0x44; // 0x44
			GolWorldEntity m_unk0x48;     // 0x48
			union {
				SpatialSoundInstance* m_unk0x70;                  // 0x70
				RaceResourceManager::Resource* m_soundResource70; // 0x70
			};
			undefined m_unk0x74[0x78 - 0x74]; // 0x74
			RaceState::Racer* m_unk0x78;      // 0x78
			RaceState::Racer* m_unk0x7c;      // 0x7c
			LegoU8 m_flags0x80;               // 0x80
			undefined m_unk0x81[0x84 - 0x81]; // 0x81
		};

		// VTABLE: LEGORACERS 0x004b16e0
		// SIZE 0x190
		class Field0x1894 : public ResourceBase0x2c {
		public:
			enum {
				c_state0x02 = 2,
				c_state0x03 = 3,
				c_state0x05 = 5,
				c_state0x06 = 6,
				c_racerFlags0xd04Bit3 = 1 << 3,
				c_racerField0x018Flags0x384Bit1 = 1 << 1,
				c_timer0x2710 = 0x2710,
				c_sound0x2e = 0x2e,
				c_sound0x2f = 0x2f,
				c_sound0x30 = 0x30,
			};

			Field0x1894();
			~Field0x1894();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x14() override;                               // vtable+0x14
			void VTable0x1c() override;                               // vtable+0x1c
			void VTable0x20(RaceState::Racer* p_racer) override;      // vtable+0x20
			void FUN_004571b0(
				Field0x6dc* p_unk0x04,
				Field0x074* p_unk0x08,
				RaceSessionField0x27d4::Item::Field0x004::Params* p_unk0x0c,
				RaceSessionField0x32b4* p_unk0x10,
				CutsceneAnimation* p_unk0x14,
				GolRenderDevice* p_renderer,
				Field0x0* p_export
			);
			void FUN_00457170();

		private:
			Field0x6dc* m_unk0x02c;    // 0x02c
			GolWorldEntity m_unk0x030; // 0x030
			union {
				SpatialSoundInstance* m_unk0x058;          // 0x058
				RaceResourceManager::Resource* m_sound058; // 0x058
			};
			CutsceneAnimation* m_unk0x05c;                                // 0x05c
			CutsceneParticleRef* m_unk0x060;                              // 0x060
			MarblePath0x114 m_unk0x064;                                   // 0x064
			undefined m_unk0x178[0x180 - 0x178];                          // 0x178
			GolBillboard::Field0x2c m_unk0x180;                           // 0x180
			RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x18c; // 0x18c
		};

		// VTABLE: LEGORACERS 0x004b1448
		// SIZE 0x17c
		class Field0x1898 : public ResourceBase0x2c {
		public:
			enum {
				c_state0x02 = 2,
				c_state0x03 = 3,
				c_state0x04 = 4,
				c_state0x05 = 5,
				c_state0x06 = 6,
				c_timer0x01f4 = 0x01f4,
				c_timer0x1388 = 0x1388,
				c_sound0x05 = 0x05,
				c_sound0x11 = 0x11,
			};

			Field0x1898();
			~Field0x1898();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x14() override;                               // vtable+0x14
			void VTable0x1c() override;                               // vtable+0x1c
			void FUN_00452ee0(
				Field0x074* p_unk0x04,
				RaceSessionField0x32b4* p_unk0x08,
				Field0x6dc* p_unk0x0c,
				undefined4 p_unk0x10,
				GolModelEntity* p_model
			);
			void FUN_00452eb0();

		private:
			GolModelEntity m_unk0x02c; // 0x02c
			Field0xa8 m_unk0x0bc;      // 0x0bc
			Field0x6dc* m_unk0x164;    // 0x164
			union {
				undefined4 m_unk0x168;                  // 0x168
				CutsceneAnimation* m_cutsceneAnimation; // 0x168
			};
			CutsceneParticleRef* m_unk0x16c; // 0x16c
			union {
				SpatialSoundInstance* m_unk0x170;                  // 0x170
				RaceResourceManager::Resource* m_soundResource170; // 0x170
			};
			RaceState::Racer* m_unk0x174; // 0x174
			LegoFloat m_unk0x178;         // 0x178
		};

		// VTABLE: LEGORACERS 0x004b13fc
		// SIZE 0x68
		class Field0x189c : public ResourceBase0x2c {
		public:
			enum {
				c_state0x02 = 2,
				c_state0x03 = 3,
				c_state0x04 = 4,
				c_state0x05 = 5,
				c_state0x06 = 6,
				c_timer0x03e8 = 0x03e8,
				c_timer0x2710 = 0x2710,
				c_timer0x3a98 = 0x3a98,
				c_sound0x09 = 0x09,
				c_racerFlags0xd04Bit11 = 1 << 11,
			};

			Field0x189c();
			~Field0x189c();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x10(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
			void VTable0x14() override;                               // vtable+0x14
			void VTable0x1c() override;                               // vtable+0x1c
			void VTable0x20(RaceState::Racer* p_racer) override;      // vtable+0x20
			void FUN_00452530(Field0x074* p_unk0x04, RaceSessionField0x32b4* p_unk0x08, Field0x6dc* p_unk0x0c);
			void FUN_004524f0();
			void FUN_00452510();

		private:
			Field0x6dc* m_unk0x2c;        // 0x2c
			GolAnimatedEntity* m_unk0x30; // 0x30
			GolAnimatedEntity* m_unk0x34; // 0x34
			GolAnimatedEntity* m_unk0x38; // 0x38
			GolWorldEntity m_unk0x3c;     // 0x3c
			union {
				SpatialSoundInstance* m_unk0x64;                  // 0x64
				RaceResourceManager::Resource* m_soundResource64; // 0x64
			};
		};

		// VTABLE: LEGORACERS 0x004b13b8
		// SIZE 0xe8
		class Field0x18a0 : public ResourceBase0x30 {
		public:
			enum {
				c_racerFlags0xd04Bit0 = 1 << 0,
				c_racerField0x018Flags0x384Bit1 = 1 << 1,
			};

			Field0x18a0();
			~Field0x18a0();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x14() override;                               // vtable+0x14
			void VTable0x1c() override;                               // vtable+0x1c
			void VTable0x20(RaceState::Racer* p_racer) override;      // vtable+0x20
			void FUN_004519d0(Field0x64** p_unk0x04, RaceSessionField0x32b4* p_unk0x08);
			void FUN_00451a10();

		private:
			// SIZE 0x24
			class Field0x0e0 {
			public:
				undefined m_unk0x000[0x008 - 0x000]; // 0x000
				GolVec3 m_unk0x008;                  // 0x008
				GolVec3 m_unk0x014;                  // 0x014
				LegoU32 m_unk0x020;                  // 0x020
			};

			Field0xa8 m_unk0x030;            // 0x030
			GolBillboard* m_unk0x0d8;        // 0x0d8
			CutsceneParticleRef* m_unk0x0dc; // 0x0dc
			Field0x0e0* m_unk0x0e0;          // 0x0e0
			union {
				CutsceneParticleRef* m_unk0x0e4;     // 0x0e4
				Field0x27c8::Item* m_trailItem0x0e4; // 0x0e4
			};
		};

		// VTABLE: LEGORACERS 0x004b1518
		// SIZE 0x290
		class Field0x18a4 : public ResourceBase0x30 {
		public:
			enum {
				c_racerFlags0xd04Bit0 = 1 << 0,
			};

			Field0x18a4();
			~Field0x18a4();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x14() override;                               // vtable+0x14
			void VTable0x1c() override;                               // vtable+0x1c
			void VTable0x20(RaceState::Racer* p_racer) override;      // vtable+0x20
			void FUN_00453cd0(Field0x6dc* p_unk0x04, RaceSessionField0x32b4* p_unk0x08, undefined4 p_unk0x0c);
			void FUN_00453d90();
			void FUN_00454690(SoundVector* p_position);

		private:
			Field0x238 m_unk0x030;                   // 0x030
			GolWorldEntity* m_unk0x268;              // 0x268
			CutsceneParticleRef* m_unk0x26c;         // 0x26c
			GolBillboard* m_unk0x270;                // 0x270
			MabMaterialAnimationItem0x18 m_unk0x274; // 0x274
			undefined4 m_unk0x28c;                   // 0x28c
		};

		// VTABLE: LEGORACERS 0x004b15a8
		// SIZE 0x24c
		class Field0x18a8 : public ResourceBase0x30 {
		public:
			enum {
				c_state0x02 = 2,
				c_state0x03 = 3,
				c_state0x04 = 4,
				c_state0x06 = 6,
				c_racerFlags0xd04Bit0 = 1 << 0,
				c_racerFlags0xaa8Bit7 = 1 << 7,
				c_timer0x0032 = 0x0032,
				c_timer0x01f4 = 0x01f4,
				c_timer0x03e8 = 0x03e8,
				c_timer0x1b58 = 0x1b58,
				c_sound0x42 = 0x42,
			};

			Field0x18a8();
			~Field0x18a8();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x10(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
			void VTable0x14() override;                               // vtable+0x14
			void VTable0x1c() override;                               // vtable+0x1c
			void VTable0x20(RaceState::Racer* p_racer) override;      // vtable+0x20
			void VTable0x24(GolVec3* p_unk0x04) override;             // vtable+0x24
			void VTable0x28(GolVec3* p_unk0x04) override;             // vtable+0x28

			void FUN_004548f0(Field0x0* p_export, Field0x6dc* p_unk0x08);
			void FUN_00454a70();
			void FUN_00454ab0();
			void FUN_00454b20();
			void FUN_00454b90();
			void FUN_00454bb0();
			void FUN_00454e50(LegoU32 p_elapsedMs);
			void FUN_00455100();
			void FUN_00455350();
			void FUN_00455660();

		private:
			Field0x170 m_unk0x030;    // 0x030
			GolVec3 m_unk0x1a0[4];    // 0x1a0
			LegoFloat m_unk0x1d0[20]; // 0x1d0
			LegoU32 m_unk0x220;       // 0x220
			LegoU32 m_unk0x224;       // 0x224
			undefined4 m_unk0x228;    // 0x228
			LegoU32 m_unk0x22c;       // 0x22c
			LegoFloat m_unk0x230;     // 0x230
			undefined4 m_unk0x234;    // 0x234
			union {
				SpatialSoundInstance* m_unk0x238;          // 0x238
				Field0x3c::Resource* m_soundResource0x238; // 0x238
			};
			SoundNode* m_unk0x23c;           // 0x23c
			LegoU32 m_unk0x240;              // 0x240
			CutsceneParticleRef* m_unk0x244; // 0x244
			GolBillboard* m_unk0x248;        // 0x248
		};

		// VTABLE: LEGORACERS 0x004b1690
		// SIZE 0x224
		class Field0x18ac : public ResourceBase0x30 {
		public:
			enum {
				c_state0x02 = 2,
				c_state0x03 = 3,
				c_state0x04 = 4,
				c_state0x06 = 6,
				c_racerFlags0xd04Bit0 = 1 << 0,
				c_racerField0x018Flags0x384Bit1 = 1 << 1,
				c_transformNodeIndex1 = 1,
				c_timer0x157c = 0x157c,
				c_sound0x32 = 0x32,
			};

			Field0x18ac();
			~Field0x18ac();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x14() override;                               // vtable+0x14
			void VTable0x1c() override;                               // vtable+0x1c
			void VTable0x20(RaceState::Racer* p_racer) override;      // vtable+0x20
			void FUN_00456510(Field0x64** p_unk0x04, RaceSessionField0x32b4* p_unk0x08);
			void FUN_00456540();
			void FUN_00456680();

		private:
			Field0xf8 m_unk0x030;          // 0x030
			GolAnimatedEntity m_unk0x128;  // 0x128
			Field0x27c8::Item* m_unk0x21c; // 0x21c
			LegoU32 m_unk0x220;            // 0x220
		};

		// VTABLE: LEGORACERS 0x004b1938
		// SIZE 0x2c
		class Field0x18b0 : public ResourceBase {
		public:
			// SIZE 0x0c
			class Field0x18 {
			public:
				undefined4 m_unk0x00;        // 0x00
				undefined4 m_unk0x04;        // 0x04
				RaceState::Racer* m_unk0x08; // 0x08
			};

			Field0x18b0();
			~Field0x18b0();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x10(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
			void VTable0x14() override;                               // vtable+0x14
			LegoS32 VTable0x18() override;                            // vtable+0x18
			void VTable0x1c() override;                               // vtable+0x1c
			RaceState::Racer* FUN_0045bc40();
			void FUN_0045bcd0(Field0x6dc* p_unk0x04);
			void FUN_0045bd10();

		private:
			union {
				Field0x18* m_unk0x18;            // 0x18
				GolAnimatedEntity* m_entity0x18; // 0x18
			};
			GolAnimatedEntity* m_unk0x1c; // 0x1c
			RaceState::Racer* m_unk0x20;  // 0x20
			Field0x6dc* m_unk0x24;        // 0x24
			union {
				SpatialSoundInstance* m_unk0x28;          // 0x28
				Field0x3c::Resource* m_soundResource0x28; // 0x28
			};
		};

		// VTABLE: LEGORACERS 0x004b1a30
		// SIZE 0x34
		class Field0x18b4 : public ResourceBase {
		public:
			enum {
				c_state0x01 = 1,
				c_state0x02 = 2,
				c_state0x03 = 3,
				c_state0x04 = 4,
				c_state0x06 = 6,
				c_duration0x007d = 0x007d,
				c_duration0x00fa = 0x00fa,
				c_timer0x0032 = 0x0032,
				c_timer0x0320 = 0x0320,
				c_timer0x03e8 = 0x03e8,
				c_timer0x05dc = 0x05dc,
				c_timer0x1194 = 0x1194,
				c_timer0x1388 = 0x1388,
				c_sound0x24 = 0x24,
				c_sound0x28 = 0x28,
				c_sound0x41 = 0x41,
				c_sound0x4b = 0x4b,
				c_ownerFlags0x058Bit1 = 1 << 1,
				c_racerFlags0xd04Bit3 = 1 << 3,
			};

			Field0x18b4();
			~Field0x18b4();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x10(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
			void VTable0x14() override;                               // vtable+0x14
			LegoS32 VTable0x18() override;                            // vtable+0x18
			void VTable0x1c() override;                               // vtable+0x1c
			void FUN_0045c880(Field0x6dc* p_unk0x04, CutsceneAnimation* p_unk0x08);
			void FUN_0045c8b0();
			void FUN_0045c8d0();
			void FUN_0045cd70();
			void FUN_0045cf90();

		private:
			friend class Field0x6dc;

			RaceState::Racer* m_unk0x018;   // 0x18
			Field0x6dc* m_unk0x1c;          // 0x1c
			GolAnimatedEntity* m_unk0x20;   // 0x20
			GolAnimatedEntity* m_unk0x24;   // 0x24
			GolAnimatedEntity* m_unk0x28;   // 0x28
			CutsceneAnimation* m_unk0x2c;   // 0x2c
			CutsceneParticleRef* m_unk0x30; // 0x30
		};

		// VTABLE: LEGORACERS 0x004b1a88
		// SIZE 0xe4
		class Field0x18b8 : public ResourceBase {
		public:
			// SIZE 0x08
			struct SetupParams {
				Field0x6dc* m_unk0x00; // 0x00
				LegoFloat m_unk0x04;   // 0x04
			};

			Field0x18b8();
			~Field0x18b8();
			Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
			void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
			void VTable0x10(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
			void VTable0x14() override;                               // vtable+0x14
			LegoS32 VTable0x18() override;                            // vtable+0x18
			void VTable0x1c() override;                               // vtable+0x1c
			void FUN_0045d4b0();
			void FUN_0045d510(const SetupParams* p_params);
			void FUN_0045d540();
			void FUN_0045e080(GolWorldEntity* p_entity);

		private:
			friend class Field0x6dc;

			enum {
				c_stateInitialized = 1,
				c_stateStarting = 2,
				c_stateActive = 3,
				c_stateDone = 6,
				c_menuAnimationDurationMs = 200,
				c_menuAnimationColorBlue = 100,
				c_transitionDurationMs = 1500,
				c_soundStart = 0x27,
				c_soundFinish = 0x29,
				c_soundSpatial = 0x41,
			};

			GolModelEntity m_unk0x018;    // 0x018
			RaceState::Racer* m_unk0x0a8; // 0x0a8
			Field0x6dc* m_unk0x0ac;       // 0x0ac
			LegoFloat m_unk0x0b0;         // 0x0b0
			GolVec3 m_unk0x0b4;           // 0x0b4
			GolVec3 m_unk0x0c0;           // 0x0c0
			GolVec3 m_unk0x0cc;           // 0x0cc
			LegoBool32 m_unk0x0d8;        // 0x0d8
			LegoBool32 m_unk0x0dc;        // 0x0dc
			LegoBool32 m_unk0x0e0;        // 0x0e0
		};

		// SIZE 0x270
		class Field0x270 : public LegoEventQueue::Callback {
		public:
			typedef GolModelEntity Field0x34;

			// SIZE 0x48
			struct Params {
				Field0x64* m_unk0x00;                                        // 0x00
				RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x04; // 0x04
				GolModelEntity* m_unk0x08;                                   // 0x08
				DuskwindBananaRelic0x24* m_unk0x0c;                          // 0x0c
				DuskwindBananaRelic0x24* m_unk0x10;                          // 0x10
				DuskwindBananaRelic0x24* m_unk0x14;                          // 0x14
				LegoEventQueue* m_unk0x18;                                   // 0x18
				Field0x6dc* m_unk0x1c;                                       // 0x1c
				MabMaterialAnimationItem0x18* m_unk0x20;                     // 0x20
				LegoU32 m_unk0x24;                                           // 0x24
				CutsceneAnimation* m_unk0x28;                                // 0x28
				LegoU32 m_unk0x2c;                                           // 0x2c
				LegoU32 m_unk0x30;                                           // 0x30
				LegoFloat m_unk0x34;                                         // 0x34
				LegoFloat m_unk0x38;                                         // 0x38
				LegoFloat m_unk0x3c;                                         // 0x3c
				LegoFloat m_unk0x40;                                         // 0x40
				LegoU32 m_unk0x44;                                           // 0x44
			};

			void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
			virtual void VTable0x04(undefined4);                            // vtable+0x04

			Field0x270();
			~Field0x270();
			Field0x270* GetNext() { return m_next; }
			LegoS32 GetUnk0x04() const { return m_unk0x04; }
			LegoU32 GetUnk0x238() const { return m_unk0x238; }
			void SetNext(Field0x270* p_next) { m_next = p_next; }
			void FUN_00421250(const Params* p_params);
			void FUN_004214b0();
			void FUN_00421520(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer);
			void FUN_004217b0();
			void FUN_004217d0(LegoU32 p_elapsedMs);
			void FUN_00421850(LegoU32 p_elapsedMs);
			void FUN_00421ae0(GolD3DRenderDevice* p_renderer);
			void FUN_004513d0(GolD3DRenderDevice* p_renderer);

		private:
			enum {
				c_racerFlags0xd04Bit0 = 1 << 0,
			};

			LegoS32 m_unk0x04;                                            // 0x004
			GolWorldEntity m_unk0x008;                                    // 0x008
			Field0x64* m_unk0x030;                                        // 0x030
			Field0x34 m_unk0x034;                                         // 0x034
			GolBillboard* m_unk0x0c4;                                     // 0x0c4
			MabMaterialAnimationItem0x18 m_unk0x0c8;                      // 0x0c8
			LegoU32 m_unk0x0e0;                                           // 0x0e0
			RaceSessionField0x27d4::Item::Field0x004 m_unk0x0e4;          // 0x0e4
			RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x200; // 0x200
			MaterialTable0x0c m_unk0x204;                                 // 0x204
			DuskwindBananaRelic0x24* m_unk0x210;                          // 0x210
			DuskwindBananaRelic0x24* m_unk0x214;                          // 0x214
			LegoEventQueue* m_unk0x218;                                   // 0x218
			RaceState::Racer* m_unk0x21c;                                 // 0x21c
			LegoEventQueue::Event* m_unk0x220;                            // 0x220
			Field0x6dc* m_unk0x224;                                       // 0x224
			CutsceneAnimation* m_unk0x228;                                // 0x228
			LegoU32 m_unk0x22c;                                           // 0x22c
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
				void FUN_00451480(GolD3DRenderDevice* p_renderer);
				void FUN_004514b0(
					GolAnimatedEntity* p_sourceEntity,
					GolAnimatedEntity* p_entity,
					const GolVec3* p_position,
					const GolVec3* p_direction,
					LegoU32 p_partIndex,
					void* p_billboardPosition
				);
				GolAnimatedEntity* GetUnk0x0c() { return m_unk0x0c; }
				LegoS32 GetUnk0x10() const { return m_unk0x10; }

			private:
				friend class Field0x18bc;

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
			friend class Field0x6dc;

			void FUN_00451750(Field0x6dc* p_unk0x04, GolD3DRenderDevice* p_renderer);
			void FUN_004517c0(const GolVec3* p_position, const GolVec3* p_direction, RaceState::Racer* p_racer);

			Entry m_entries[5];              // 0x00
			GolAnimatedEntity* m_unk0x64[4]; // 0x64
			Field0x6dc* m_unk0x74;           // 0x74
			undefined4 m_unk0x78;            // 0x78
			undefined4 m_unk0x7c;            // 0x7c
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
		void FUN_0045b470(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer);
		void FUN_0045b4d0(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer);
		void FUN_0045b4f0(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer);
		void FUN_0045b550(const GolVec3* p_unk0x04, const GolVec3* p_position, RaceState::Racer* p_racer);
		void FUN_0045b740(RaceState::Racer* p_racer);
		void FUN_0045b900();
		LegoBool32 FUN_0045b9a0(RaceState::Racer* p_racer);
		void FUN_0045bb30();
		undefined4 GetUnk0x19a0() const { return m_unk0x19a0; }
		GolBillboard::Field0x2c* GetBillboardMaterialTable() { return &m_unk0x008; }
		MabMaterialAnimationItem0x8* GetMaterialAnimationItems() const { return m_unk0x014.GetUnk0x04(); }
		LegoU32 GetMaterialAnimationItemCount() const { return m_unk0x014.GetUnk0x08(); }

	private:
		// SIZE 0x3c
		struct Params {
			Field0x0* m_unk0x00;                                         // 0x00
			GolD3DRenderDevice* m_renderer;                              // 0x04
			Field0x074* m_unk0x08;                                       // 0x08
			RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x0c; // 0x0c
			undefined4 m_unk0x10;                                        // 0x10
			RaceSessionField0x32b4* m_unk0x14;                           // 0x14
			RaceState::Racer::Field0x004* m_unk0x18;                     // 0x18
			undefined4 m_unk0x1c;                                        // 0x1c
			Field0x27c8* m_unk0x20;                                      // 0x20
			undefined4 m_unk0x24;                                        // 0x24
			MenuAnimationList* m_unk0x28;                                // 0x28
			GolWorldDatabase* m_unk0x2c;                                 // 0x2c
			undefined4 m_unk0x30;                                        // 0x30
			LegoFloat m_unk0x34;                                         // 0x34
			undefined4 m_unk0x38;                                        // 0x38
		};

		friend class RaceSession;
		friend class Field0x1890;
		friend class Field0x189c;
		friend class Field0x18a0;
		friend class Field0x18a4;
		friend class Field0x18a8;
		friend class Field0x18ac;
		friend class Field0x18b0;
		friend class Field0x18b4;
		friend class Field0x18b8;
		friend class Field0x18bc;
		friend class Field0x68Field0x028;
		friend class RaceState::Racer::Field0xd5c;

		void FUN_00457c20(const Params* p_params);
		void FUN_00457c90(const LegoChar* p_unk0x04, const LegoChar* p_unk0x08, LegoBool32 p_binary);
		void FUN_00457cf0(LegoBool32 p_unk0x04);
		void FUN_00457d30(LegoBool32 p_unk0x04);
		void FUN_00458810(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
		void FUN_00458a80(GolFileParser* p_parser, LegoBool32 p_mirror);
		void FUN_00458e80(GolFileParser* p_parser, LegoBool32 p_mirror);
		void FUN_00458940();
		void FUN_004590f0();
		void FUN_004164c0();
		void FUN_00459b80();
		void FUN_00457a90();
		void FUN_00459e20();
		void FUN_0045a3f0(LegoU32 p_elapsedMs);
		void FUN_0045a340();
		void FUN_0045b690(RaceState::Racer* p_racer);
		void FUN_0045b7a0(Field0x1958Resource* p_resource, LegoU32 p_unk0x08, LegoS32 p_unk0x0c);
		void FUN_0045b950();
		GolAnimatedEntity* FUN_0045b9e0();
		LegoU32 FUN_0045ba40(GolAnimatedEntity* p_entity);
		DuskwindBananaRelic0x24* FUN_0045ba90(LegoU32* p_unk0x04);
		DuskwindBananaRelic0x24* FUN_0045bae0(LegoU32* p_unk0x04);
		static Field0x270* __stdcall FUN_0045b3a0(Field0x270** p_head);

		enum {
			c_unk0x1978Slot1A = 0,
			c_unk0x1978Slot1B = 1,
			c_unk0x1978Slot4A = 2,
			c_unk0x1978Slot4B = 3,
			c_unk0x1978Slot2A = 4,
			c_unk0x1978Slot2B = 5,
			c_unk0x1978Slot3A = 6,
			c_unk0x1978Slot3B = 7,
			c_unk0x1978MaterialPBrickP = 0,
			c_unk0x1978MaterialPTrailP = 1,
			c_unk0x1978MaterialPBrickM = 2,
			c_unk0x1978MaterialPTrailM = 3,
			c_unk0x1978MaterialPBrickS = 4,
			c_unk0x1978MaterialPTrailS = 5,
			c_unk0x1978MaterialPBrickT = 6,
			c_unk0x1978MaterialPTrailT = 7,
			c_unk0x1978SlotCount = 8,
			c_randomTableMask = 0x3ff,
			c_randomOffsetRange = 100,
			c_randomBurstMax = 3,
		};

		Field0x0* m_unk0x000;                     // 0x000
		GolD3DRenderDevice* m_renderer;           // 0x004
		GolBillboard::Field0x2c m_unk0x008;       // 0x008
		MabMaterialAnimation0x14 m_unk0x014;      // 0x014
		Field0x68Field0x028* m_unk0x028;          // 0x028
		Field0x68Field0x02c* m_unk0x02c;          // 0x02c
		LegoEventQueue::Event** m_unk0x030;       // 0x030
		LegoU32 m_unk0x034;                       // 0x034
		LegoU32 m_unk0x038;                       // 0x038
		RaceState::Racer::Field0x004* m_unk0x03c; // 0x03c
		union {
			undefined4 m_unk0x040;                       // 0x040
			CutsceneAnimation* m_cutsceneAnimation0x040; // 0x040
		};
		Field0x27c8* m_unk0x044;                                      // 0x044
		undefined4 m_unk0x048;                                        // 0x048
		MenuAnimationList* m_unk0x04c;                                // 0x04c
		undefined4 m_unk0x050;                                        // 0x050
		LegoFloat m_unk0x054;                                         // 0x054
		undefined4 m_unk0x058;                                        // 0x058
		GolWorldDatabase* m_unk0x05c;                                 // 0x05c
		GolWorldDatabase* m_unk0x060;                                 // 0x060
		GolWorldDatabase* m_unk0x064;                                 // 0x064
		RaceSessionField0x32b4* m_unk0x068;                           // 0x068
		RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x06c; // 0x06c
		undefined4 m_unk0x070;                                        // 0x070
		union {
			Field0x074* m_unk0x074;                          // 0x074
			RaceState::Racer::Field0x00c* m_racerField0x00c; // 0x074
		};
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
		union {
			Field0x1958Resource* m_unk0x1958;      // 0x1958
			SpatialSoundInstance* m_sound0x1958;   // 0x1958
			Field0x3c::Resource* m_resource0x1958; // 0x1958
		};
		union {
			Field0x1958Resource* m_unk0x195c;      // 0x195c
			SpatialSoundInstance* m_sound0x195c;   // 0x195c
			Field0x3c::Resource* m_resource0x195c; // 0x195c
		};
		union {
			Field0x1958Resource* m_unk0x1960;      // 0x1960
			SpatialSoundInstance* m_sound0x1960;   // 0x1960
			Field0x3c::Resource* m_resource0x1960; // 0x1960
		};
		union {
			Field0x1958Resource* m_unk0x1964;      // 0x1964
			SpatialSoundInstance* m_sound0x1964;   // 0x1964
			Field0x3c::Resource* m_resource0x1964; // 0x1964
		};
		GolAnimatedEntity* m_unk0x1968;          // 0x1968
		GolAnimatedEntity* m_unk0x196c;          // 0x196c
		GolAnimatedEntity* m_unk0x1970;          // 0x1970
		GolAnimatedEntity* m_unk0x1974;          // 0x1974
		DuskwindBananaRelic0x24* m_unk0x1978[8]; // 0x1978
		undefined4 m_unk0x1998;                  // 0x1998
		LegoFloat m_unk0x199c;                   // 0x199c
		undefined4 m_unk0x19a0;                  // 0x19a0
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
			typedef Field0x2128::Entry BaseEntry;

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

			LegoU32 m_unk0x3c;                 // 0x3c
			LegoU32 m_unk0x40;                 // 0x40
			Field0x6dc::Field0x074* m_unk0x44; // 0x44
			Field0x6dc* m_unk0x48;             // 0x48
			Field0x32c4* m_unk0x4c;            // 0x4c
			LegoU32 m_unk0x50;                 // 0x50
			LegoU32 m_unk0x54;                 // 0x54
		};

		// SIZE 0x3c
		class EntryParams : public Field0x2128::EntryParams {
		public:
			Field0x6dc::Field0x074* m_unk0x1c; // 0x1c
			Field0x6dc* m_unk0x20;             // 0x20
			Field0x32c4* m_unk0x24;            // 0x24
			LegoU32 m_unk0x28;                 // 0x28
			LegoBool32 m_unk0x2c;              // 0x2c
			LegoBool32 m_unk0x30;              // 0x30
			LegoBool32 m_unk0x34;              // 0x34
			LegoU32 m_unk0x38;                 // 0x38
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
			Field0x6dc::Field0x074* p_field0x074,
			RaceEventTable0x90* p_eventTable,
			Field0x6dc* p_field0x6dc,
			RaceSessionField0x32b4::Field0x000* p_field0x32b4Field0x000,
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
			undefined4 m_unk0x14;                    // 0x14
			CutsceneAnimation* m_unk0x18;            // 0x18
			CutsceneAnimation* m_unk0x1c;            // 0x1c
			Field0x2f90* m_unk0x20;                  // 0x20
			undefined4 m_unk0x24;                    // 0x24
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
				undefined4 m_eventIds[3];         // 0x04
				RaceEventTable0x90* m_eventTable; // 0x10
				undefined4 m_unk0x14;             // 0x14
			};

			Resource0x24();
			~Resource0x24() override;
			void VTable0x00(RaceState::Racer* p_racer) override;
			void VTable0x08(RaceState::Racer* p_racer) override;

			undefined4* FUN_00464610(InitParams* p_params);
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
				undefined4 m_eventIds[3];         // 0x04
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
				undefined4 m_eventIds[3];         // 0x04
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
				undefined4 m_eventIds[3];            // 0x04
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
				undefined4 m_eventIds[3];         // 0x04
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
				undefined4 m_eventIds[3];         // 0x04
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
				undefined4 m_eventIds[3];         // 0x04
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
				undefined4 m_eventIds[3];         // 0x04
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
				undefined4 m_eventIds[3];         // 0x04
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
				undefined4 m_eventIds[3];         // 0x04
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
				undefined4 m_eventIds[3];         // 0x04
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

		GolWorldDatabase* m_unk0x00;             // 0x00
		GolWorldDatabase* m_unk0x04;             // 0x04
		GolWorldDatabase* m_unk0x08;             // 0x08
		GolWorldDatabase* m_unk0x0c;             // 0x0c
		RaceState::Racer::Field0x004* m_unk0x10; // 0x10
		undefined4 m_unk0x14;                    // 0x14
		CutsceneAnimation* m_unk0x18;            // 0x18
		CutsceneAnimation* m_unk0x1c;            // 0x1c
		Field0x2f90* m_unk0x20;                  // 0x20
		undefined4 m_unk0x24;                    // 0x24
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

	typedef RaceEventDispatcher0x08 Field0x2148;

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

	typedef RaceCameraController Field0x2ad4;

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
	class Field0x27f4 {
	public:
		// VTABLE: LEGORACERS 0x004afef4
		// SIZE 0x1fc
		class CpbTxtParser : public GolTxtParser {};

		// SIZE 0x24
		class Entry {
		public:
			// SIZE 0x04
			union Field0x20 {
				LegoU32 m_all;     // 0x00
				LegoU8 m_items[4]; // 0x00
			};

			Entry();
			~Entry();

		private:
			friend class Field0x27f4;

			void Reset();
			void FUN_0041e630();
			void FUN_0041e640(GolFileParser* p_parser, LegoBool32 p_mirror);

			GolVec3 m_unk0x00;   // 0x00
			LegoFloat m_unk0x0c; // 0x0c
			GolVec3 m_unk0x10;   // 0x10
			LegoFloat m_unk0x1c; // 0x1c
			Field0x20 m_unk0x20; // 0x20
		};

		Field0x27f4();
		~Field0x27f4();

	private:
		friend class RaceSession;

		void Reset();
		void FUN_0041e770(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
		Entry* FUN_0041e940(LegoU32 p_unk0x04);
		void FUN_0041e950();
		LegoU32 FUN_0041ea60();
		LegoU32 FUN_0041ea90(LegoU32 p_unk0x04, LegoU32* p_unk0x08);

		Entry* m_entries; // 0x00
		LegoU32 m_count;  // 0x04
	};

	// SIZE 0x08
	class Field0x2804 {
	public:
		// VTABLE: LEGORACERS 0x004b1958
		// SIZE 0x1fc
		class TgbTxtParser : public GolTxtParser {};

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
		void FUN_0045c3d0(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);

		Entry* m_entries; // 0x00
		LegoU32 m_count;  // 0x04
	};

	// SIZE 0x48
	class Field0x3104 {
	public:
		// VTABLE: LEGORACERS 0x004b4b50
		// SIZE 0x1fc
		class RrbTxtParser : public GolTxtParser {};

		Field0x3104();
		~Field0x3104();
		void FUN_004a50a0();

	private:
		friend class RaceSession;

		void FUN_004a4e30(const LegoChar* p_fileName, LegoBool32 p_binary, LegoBool32 p_mirror);
		void FUN_004a50c0();
		void FUN_004a5100(GolFileParser* p_parser, LegoBool32 p_mirror);

		undefined4 m_unk0x00;                                      // 0x00
		RaceState::Racer::Field0x00c::Entry::PathPoint* m_unk0x04; // 0x04
		LegoFloat m_unk0x08;                                       // 0x08
		LegoFloat m_unk0x0c;                                       // 0x0c
		LegoFloat m_unk0x10;                                       // 0x10
		LegoFloat m_unk0x14;                                       // 0x14
		LegoFloat m_unk0x18;                                       // 0x18
		LegoFloat m_unk0x1c;                                       // 0x1c
		LegoFloat m_unk0x20;                                       // 0x20
		LegoFloat m_unk0x24;                                       // 0x24
		LegoFloat m_unk0x28;                                       // 0x28
		LegoFloat m_unk0x2c;                                       // 0x2c
		LegoFloat m_unk0x30;                                       // 0x30
		LegoFloat m_unk0x34;                                       // 0x34
		LegoFloat m_unk0x38;                                       // 0x38
		LegoFloat m_unk0x3c;                                       // 0x3c
		undefined4 m_unk0x40;                                      // 0x40
		undefined4 m_unk0x44;                                      // 0x44
	};

	// SIZE 0x2c
	class Field0x30c4 {
	public:
		// SIZE 0x2c
		class Params {
		public:
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
			// SIZE 0x68
			struct Field0x000 {
				undefined m_unk0x000[0x064 - 0x000]; // 0x000
				LegoU32 m_unk0x064;                  // 0x064
			};

			union {
				undefined m_unk0x000[0x0a8 - 0x000]; // 0x000
				Field0x000 m_field0x000;             // 0x000
			};
			RaceSessionField0x32b4::Field0x000::Field0x0a8* m_unk0x0a8; // 0x0a8
		};

		Field0x32c4();
		virtual ~Field0x32c4(); // vtable+0x00
		void FUN_0045e470(LegoU32 p_elapsedMs);
		void FUN_0045e520(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
		LegoU32 FUN_0045e5b0();

		// SYNTHETIC: LEGORACERS 0x0045e380
		// RaceSession::Field0x32c4::`scalar deleting destructor'

	private:
		friend class RaceSession;

		void FUN_0045e3f0(Field0x1c* p_unk0x04, RaceState* p_raceState);
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

// SIZE 0x68
class RaceState::Racer::Field0xd5c : public RaceSession::Field0x6dc::Field0x68 {
public:
	LegoU8 FUN_00453790(GolVec3 p_unk0x04);
	void FUN_004537f0();
	LegoS32 FUN_00453840(GolVec3* p_unk0x04);

protected:
	GolVec3 m_unk0x54;                // 0x54
	LegoU32 m_unk0x60;                // 0x60
	LegoU8 m_flags0x64;               // 0x64
	undefined m_unk0x65[0x68 - 0x65]; // 0x65
};

// SIZE 0x68
class RaceSession::Field0x6dc::Field0x68Field0x02c : public RaceState::Racer::Field0xd5c {
public:
	Field0x68Field0x02c();
	~Field0x68Field0x02c() override;
	void VTable0x04(RaceState::Racer* p_racer) override;
	void VTable0x0c() override;

	// SYNTHETIC: LEGORACERS 0x00459090
	// RaceSession::Field0x6dc::Field0x68Field0x02c::`vector deleting destructor'

	void FUN_00453610();
	void FUN_00453620();
	void FUN_00453690(LegoU32 p_elapsedMs);
};

#endif // RACESESSION_H
