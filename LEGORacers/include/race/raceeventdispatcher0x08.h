#ifndef RACEEVENTDISPATCHER0X08_H
#define RACEEVENTDISPATCHER0X08_H

#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "golworldentity.h"
#include "material/materialtable0x0c.h"
#include "race/racesessionfield0x27d4.h"
#include "race/racestate.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolCamera;
class GolD3DRenderDevice;
class GolFileParser;
class GolAnimatedEntity;
class GolBillboard;
class GolExport;
class GolModelEntity;
class GolNameTable;
class GolWorldDatabase;
struct CutsceneParticleRef;
class CutsceneAnimation;
class MabMaterialAnimationItem0x8;
class MabMaterialAnimationItem0x18;
class RaceEventTable0x90;
class RaceSession;
class RaceSessionField0x32b4;
class SpatialSoundInstance;

// SIZE 0x08
class RaceEventDispatcher0x08 {
public:
	class Context;

	// VTABLE: LEGORACERS 0x004b40c4
	// SIZE 0x10
	class Item : public LegoEventQueue::Callback {
	public:
		Item();
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual void VTable0x04(void*) = 0;                             // vtable+0x04
		virtual void VTable0x08(void*) = 0;                             // vtable+0x08
		virtual ~Item();                                                // vtable+0x0c
		virtual void VTable0x10(Context*, GolFileParser*) = 0;          // vtable+0x10
		virtual void VTable0x14(undefined4);                            // vtable+0x14
		virtual void VTable0x18(GolCamera*, RaceState::Racer*);         // vtable+0x18
		virtual void VTable0x1c(GolD3DRenderDevice*);                   // vtable+0x1c
		virtual LegoBool32 VTable0x20();                                // vtable+0x20
		virtual void VTable0x24();                                      // vtable+0x24
		virtual void VTable0x28(LegoS32, void*);                        // vtable+0x28
		virtual void VTable0x2c(LegoS32, void*);                        // vtable+0x2c

		LegoS32 Reset();
		void FUN_0048a470(void* p_unk0x04);
		void FUN_0048a490(void* p_unk0x04);

		// SYNTHETIC: LEGORACERS 0x0048a420
		// RaceEventDispatcher0x08::Item::`scalar deleting destructor'

	protected:
		friend class RaceEventDispatcher0x08;

		RaceEventTable0x90* m_unk0x04; // 0x04
		LegoS32 m_unk0x08;             // 0x08
		LegoS32 m_unk0x0c;             // 0x0c
	};

	// VTABLE: LEGORACERS 0x004b4194
	// SIZE 0x18
	class ItemI : public Item {
	public:
		ItemI();
		~ItemI() override;
		void VTable0x04(void* p_racer) override;                      // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                    // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser*) override; // vtable+0x10
		void VTable0x14(undefined4 p_unk0x04) override;               // vtable+0x14
		LegoBool32 VTable0x20() override;                             // vtable+0x20

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048aea0
		// RaceEventDispatcher0x08::ItemI::`scalar deleting destructor'

	private:
		enum {
			c_racerFlags0xd04Bit4 = 1 << 4,
		};

		RaceState::Racer::Field0x008* m_unk0x10; // 0x10
		LegoU32 m_unk0x14;                       // 0x14
	};

	// VTABLE: LEGORACERS 0x004b41c4
	// SIZE 0x20
	class Item6 : public Item {
	public:
		Item6();
		~Item6() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048b0a0
		// RaceEventDispatcher0x08::Item6::`scalar deleting destructor'

	private:
		GolModelEntity* m_unk0x10; // 0x10
		LegoFloat m_unk0x14;       // 0x14
		LegoFloat m_unk0x18;       // 0x18
		LegoFloat m_unk0x1c;       // 0x1c
	};

	// VTABLE: LEGORACERS 0x004b423c
	// SIZE 0x18
	class Item0x3f : public Item {
	public:
		Item0x3f();
		~Item0x3f() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_unk0x04) override;                        // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048b310
		// RaceEventDispatcher0x08::Item0x3f::`scalar deleting destructor'

	private:
		enum {
			c_randomTableMask = 0x3ff,
			c_positionCount = 3,
		};

		RaceState::Racer::Field0x008* m_unk0x10; // 0x10
		LegoU32 m_unk0x14;                       // 0x14
	};

	// VTABLE: LEGORACERS 0x004b4274
	// SIZE 0x58
	class Item0x40 : public Item {
	public:
		Item0x40();
		~Item0x40() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		void ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048b4d0
		// RaceEventDispatcher0x08::Item0x40::`scalar deleting destructor'

	private:
		enum {
			c_actionCooldownMs = 0x206c,
		};

		GolVec3 m_unk0x10;                       // 0x10
		GolVec3 m_unk0x1c;                       // 0x1c
		GolVec3 m_unk0x28;                       // 0x28
		RaceState::Racer::Field0x008* m_unk0x34; // 0x34
		GolAnimatedEntity* m_unk0x38;            // 0x38
		LegoFloat m_unk0x3c;                     // 0x3c
		LegoFloat m_unk0x40;                     // 0x40
		LegoFloat m_unk0x44;                     // 0x44
		LegoU32 m_unk0x48;                       // 0x48
		LegoU32 m_unk0x4c;                       // 0x4c
		LegoU32 m_unk0x50;                       // 0x50
		LegoU32 m_unk0x54;                       // 0x54
	};

	// VTABLE: LEGORACERS 0x004b42b8
	// SIZE 0x20
	class Item0x28 : public Item {
	public:
		Item0x28();
		~Item0x28() override;
		void VTable0x04(void*) override;                              // vtable+0x04
		void VTable0x08(void*) override;                              // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser*) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;             // vtable+0x14
		void VTable0x24() override;                                   // vtable+0x24

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048b8b0
		// RaceEventDispatcher0x08::Item0x28::`scalar deleting destructor'

	private:
		enum {
			c_field0x18FlagBit16 = 1 << 16,
			c_field0x18FlagBit17 = 1 << 17,
		};

		// SIZE 0x0c
		class Field0x18 {
		public:
			undefined4 m_unk0x00; // 0x00
			undefined4 m_unk0x04; // 0x04
			LegoU32 m_flags0x08;  // 0x08
		};

		GolAnimatedEntity* m_unk0x10; // 0x10
		CutsceneAnimation* m_unk0x14; // 0x14
		Field0x18* m_unk0x18;         // 0x18
		LegoU32 m_unk0x1c;            // 0x1c
	};

	// VTABLE: LEGORACERS 0x004b433c
	// SIZE 0x24
	class Item0x29 : public Item {
	public:
		Item0x29();
		~Item0x29() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14
		void VTable0x24() override;                                            // vtable+0x24

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048c050
		// RaceEventDispatcher0x08::Item0x29::`scalar deleting destructor'

	private:
		enum {
			c_field0x20FlagBit16 = 1 << 16,
			c_field0x20FlagBit17 = 1 << 17,
			c_modelDistanceCount = 3,
		};

		// SIZE 0x0c
		class Field0x20 {
		public:
			undefined4 m_unk0x00; // 0x00
			undefined4 m_unk0x04; // 0x04
			LegoU32 m_flags0x08;  // 0x08
		};

		CutsceneAnimation* m_unk0x10;            // 0x10
		GolWorldDatabase* m_unk0x14;             // 0x14
		MabMaterialAnimationItem0x18* m_unk0x18; // 0x18
		GolAnimatedEntity* m_unk0x1c;            // 0x1c
		Field0x20* m_unk0x20;                    // 0x20
	};

	// VTABLE: LEGORACERS 0x004b4434
	// SIZE 0x18
	class Item0x2a : public Item {
	public:
		Item0x2a();
		~Item0x2a() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048d010
		// RaceEventDispatcher0x08::Item0x2a::`scalar deleting destructor'

	private:
		GolAnimatedEntity* m_unk0x10; // 0x10
		LegoU32 m_unk0x14;            // 0x14
	};

	// VTABLE: LEGORACERS 0x004b43dc
	// SIZE 0x220
	class Item0x2b : public Item {
	public:
		Item0x2b();
		~Item0x2b() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;        // vtable+0x00
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14
		void VTable0x1c(GolD3DRenderDevice* p_renderer) override;              // vtable+0x1c

		// SYNTHETIC: LEGORACERS 0x0048c8c0
		// RaceEventDispatcher0x08::Item0x2b::`scalar deleting destructor'

	private:
		undefined m_unk0x10[0x220 - 0x10]; // 0x10
	};

	// VTABLE: LEGORACERS 0x004b44e0
	// SIZE 0x5c
	class Item0x2c : public Item {
	public:
		Item0x2c();
		~Item0x2c() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;        // vtable+0x00
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		LegoS32 ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048d850
		// RaceEventDispatcher0x08::Item0x2c::`scalar deleting destructor'

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
		RaceState::Racer::Field0x004* m_unk0x4c; // 0x4c
		LegoU32 m_unk0x50;                       // 0x50
		LegoU32 m_unk0x54;                       // 0x54
		LegoU32 m_unk0x58;                       // 0x58
	};

	// VTABLE: LEGORACERS 0x004b447c
	// SIZE 0x3c
	class Item0x2d : public Item {
	public:
		Item0x2d();
		~Item0x2d() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14
		void VTable0x28(LegoS32 p_unk0x04, void* p_unk0x08) override;          // vtable+0x28

		LegoS32 ClearFields();
		LegoS32 Reset();
		void FUN_0048d730();

		// SYNTHETIC: LEGORACERS 0x0048d290
		// RaceEventDispatcher0x08::Item0x2d::`scalar deleting destructor'

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
	class Item0x2e : public Item {
	public:
		Item0x2e();
		~Item0x2e() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;        // vtable+0x00
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		LegoS32 ClearFields();
		LegoS32 Reset();
		void FUN_0048e5a0();
		void FUN_0048e600();

		// SYNTHETIC: LEGORACERS 0x0048e300
		// RaceEventDispatcher0x08::Item0x2e::`scalar deleting destructor'

	private:
		enum {
			c_field0x48FlagBit16 = 1 << 16,
			c_field0x48FlagBit17 = 1 << 17,
			c_field0x0e0Flags0xd04Bit0 = 1 << 0,
			c_modelDistanceCount = 3,
			c_eventId = 0x23,
		};

		// SIZE 0x0c
		class Field0x48 {
		public:
			undefined4 m_unk0x00; // 0x00
			undefined4 m_unk0x04; // 0x04
			LegoU32 m_flags0x08;  // 0x08
		};

		GolWorldEntity m_unk0x10;         // 0x10
		LegoEventQueue* m_unk0x38;        // 0x38
		LegoEventQueue::Event* m_unk0x3c; // 0x3c
		GolModelEntity* m_unk0x40;        // 0x40
		GolModelEntity* m_unk0x44;        // 0x44
		Field0x48* m_unk0x48;             // 0x48
		LegoFloat m_unk0x4c[3];           // 0x4c
		LegoU32 m_unk0x58;                // 0x58
	};

	// VTABLE: LEGORACERS 0x004b4624
	// SIZE 0x20
	class Item0x2f : public Item {
	public:
		Item0x2f();
		~Item0x2f() override;
		void VTable0x04(void* p_unk0x04) override;                                   // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                                   // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override;       // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                            // vtable+0x14
		void VTable0x18(GolCamera* p_unk0x04, RaceState::Racer* p_unk0x08) override; // vtable+0x18
		void VTable0x24() override;                                                  // vtable+0x24

		LegoS32 ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048e9d0
		// RaceEventDispatcher0x08::Item0x2f::`scalar deleting destructor'

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
	class Item0x30 : public Item {
	public:
		Item0x30();
		~Item0x30() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048e6a0
		// RaceEventDispatcher0x08::Item0x30::`scalar deleting destructor'

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
	class Item0x32 : public Item {
	public:
		Item0x32();
		~Item0x32() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;              // vtable+0x00
		void VTable0x04(void* p_unk0x04) override;                                   // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                                   // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override;       // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                            // vtable+0x14
		void VTable0x18(GolCamera* p_unk0x04, RaceState::Racer* p_unk0x08) override; // vtable+0x18
		void VTable0x1c(GolD3DRenderDevice* p_renderer) override;                    // vtable+0x1c

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048fec0
		// RaceEventDispatcher0x08::Item0x32::`scalar deleting destructor'

	private:
		enum {
			c_flags0x178Bit0 = 1 << 0,
			c_flags0x178Bit1 = 1 << 1,
			c_soundId = 0xbbb,
			c_eventId0x14 = 0x14,
			c_eventId0x15 = 0x15,
		};

		GolWorldEntity m_unk0x10;                                     // 0x10
		GolAnimatedEntity* m_unk0x38;                                 // 0x38
		LegoEventQueue::Event* m_unk0x3c;                             // 0x3c
		LegoEventQueue* m_unk0x40;                                    // 0x40
		RaceSessionField0x27d4::Item::Field0x004 m_unk0x44;           // 0x44
		MaterialTable0x0c m_unk0x160;                                 // 0x160
		RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x16c; // 0x16c
		union {
			RaceResourceManager::Resource* m_unk0x170; // 0x170
			SpatialSoundInstance* m_sound0x170;        // 0x170
		};
		RaceState::Racer::Field0x004* m_unk0x174; // 0x174
		LegoU8 m_unk0x178;                        // 0x178
		undefined m_unk0x179[0x17c - 0x179];      // 0x179
	};

	// VTABLE: LEGORACERS 0x004b46c8
	// SIZE 0x124
	class Item0x33 : public Item {
	public:
		Item0x33();
		~Item0x33() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14
		void VTable0x1c(GolD3DRenderDevice* p_renderer) override;              // vtable+0x1c
		void VTable0x28(LegoS32 p_unk0x04, void* p_unk0x08) override;          // vtable+0x28

		void ClearFields();
		void Reset();

		// SYNTHETIC: LEGORACERS 0x0048f740
		// RaceEventDispatcher0x08::Item0x33::`scalar deleting destructor'

	protected:
		GolWorldEntity m_unk0x10;           // 0x10
		undefined m_unk0x38[0xe0 - 0x38];   // 0x38
		GolVec3 m_unk0xe0;                  // 0xe0
		GolVec3 m_unk0xec;                  // 0xec
		GolVec3 m_unk0xf8;                  // 0xf8
		LegoFloat m_unk0x104;               // 0x104
		LegoS32 m_unk0x108;                 // 0x108
		RaceSessionField0x32b4* m_unk0x10c; // 0x10c
		void* m_unk0x110;                   // 0x110
		GolBillboard* m_unk0x114;           // 0x114
		GolExport* m_unk0x118;              // 0x118
		void* m_unk0x11c;                   // 0x11c
		void* m_unk0x120;                   // 0x120
	};

	// VTABLE: LEGORACERS 0x004b4654
	// SIZE 0x30
	class Item0x34 : public Item {
	public:
		Item0x34();
		~Item0x34() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14
		void VTable0x1c(GolD3DRenderDevice* p_renderer) override;              // vtable+0x1c
		void VTable0x24() override;                                            // vtable+0x24

		void ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048ed60
		// RaceEventDispatcher0x08::Item0x34::`scalar deleting destructor'

	private:
		enum {
			c_entityCount = 4,
			c_modelDistanceCount = 3,
			c_field0x20FlagBit16 = 1 << 16,
			c_field0x20FlagBit17 = 1 << 17,
		};

		// SIZE 0x0c
		class Field0x20 {
		public:
			undefined4 m_unk0x00; // 0x00
			undefined4 m_unk0x04; // 0x04
			LegoU32 m_flags0x08;  // 0x08
		};

		GolAnimatedEntity* m_unk0x10[c_entityCount]; // 0x10
		Field0x20* m_unk0x20;                        // 0x20
		GolVec3 m_unk0x24;                           // 0x24
	};

	// VTABLE: LEGORACERS 0x004b4684
	// SIZE 0x140
	class Item0x3d : public Item0x33 {
	public:
		Item0x3d();
		~Item0x3d() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		void Reset();

		// SYNTHETIC: LEGORACERS 0x0048f240
		// RaceEventDispatcher0x08::Item0x3d::`scalar deleting destructor'

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
	class Item0x3e : public Item {
	public:
		Item0x3e();
		~Item0x3e() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		// SYNTHETIC: LEGORACERS 0x0048bb80
		// RaceEventDispatcher0x08::Item0x3e::`scalar deleting destructor'

	private:
		undefined m_unk0x10[0x204 - 0x10]; // 0x10
	};

	// VTABLE: LEGORACERS 0x004b4370
	// SIZE 0x44
	class Item0x43 : public Item {
	public:
		Item0x43();
		~Item0x43() override;
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048c490
		// RaceEventDispatcher0x08::Item0x43::`scalar deleting destructor'

	private:
		void ClearFields();

		enum {
			c_randomTableMask = 0x3ff,
		};

		GolName m_unk0x10;                       // 0x10
		GolVec3 m_unk0x18;                       // 0x18
		GolVec3 m_unk0x24;                       // 0x24
		LegoFloat m_unk0x30;                     // 0x30
		RaceState::Racer::Field0x008* m_unk0x34; // 0x34
		GolAnimatedEntity* m_unk0x38;            // 0x38
		LegoU32 m_unk0x3c;                       // 0x3c
		LegoU32 m_unk0x40;                       // 0x40
	};

	// VTABLE: LEGORACERS 0x004b4518
	// SIZE 0x60
	class Item0x48 : public Item {
	public:
		Item0x48();
		~Item0x48() override;
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override;        // vtable+0x00
		void VTable0x04(void* p_unk0x04) override;                             // vtable+0x04
		void VTable0x08(void* p_unk0x04) override;                             // vtable+0x08
		void VTable0x10(Context* p_context, GolFileParser* p_parser) override; // vtable+0x10
		void VTable0x14(undefined4 p_elapsedMs) override;                      // vtable+0x14

		LegoS32 ClearFields();
		LegoS32 Reset();

		// SYNTHETIC: LEGORACERS 0x0048dd80
		// RaceEventDispatcher0x08::Item0x48::`scalar deleting destructor'

	private:
		enum {
			c_racerFlags0xd04Bit0 = 1 << 0,
			c_racerFlags0xd04Bit29 = 0x20000000,
			c_racerFlags0xaa8Bit18 = 0x00040000,
			c_stateOne = 1,
			c_stateTwo = 2,
			c_timerMs = 1000,
			c_restoreTimerMs = 500,
		};

		void FUN_0048e1c0(GolVec3* p_position);
		void FUN_0048e230();

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
		class Field0x5c {
		public:
			virtual void VTable0x00() = 0;      // vtable+0x00
			virtual void VTable0x04(void*) = 0; // vtable+0x04
		};

		RaceEventTable0x90* GetUnk0x0c() const { return m_unk0x0c; }
		LegoEventQueue* GetUnk0x00() const { return m_unk0x00; }
		RaceState::Racer::Field0x004* GetUnk0x08() const { return m_unk0x08; }
		GolWorldDatabase* GetUnk0x10() const { return m_unk0x10; }
		GolWorldDatabase* GetUnk0x14() const { return m_unk0x14; }
		CutsceneAnimation* GetUnk0x1c() const { return m_unk0x1c; }
		RaceSessionField0x27d4::Item::Field0x004::Params* GetUnk0x20() const { return m_unk0x20; }
		GolExport* GetUnk0x24() const { return m_unk0x24; }
		GolD3DRenderDevice* GetUnk0x28() const { return m_unk0x28; }
		GolNameTable* GetUnk0x2c() const { return m_unk0x2c; }
		RaceSessionField0x32b4* GetUnk0x34() const { return m_unk0x34; }
		RaceState::Racer::Field0x008* GetUnk0x38() const { return m_unk0x38; }
		void* GetUnk0x38Raw() const { return m_unk0x38; }
		void* GetUnk0x3c() const { return m_unk0x3c; }
		LegoU32 GetUnk0x40() const { return m_unk0x40; }
		Field0x5c* GetUnk0x5c() const { return m_unk0x5c; }

	private:
		friend class RaceEventDispatcher0x08;

		LegoEventQueue* m_unk0x00;                                   // 0x00
		undefined m_unk0x04[0x08 - 0x04];                            // 0x04
		RaceState::Racer::Field0x004* m_unk0x08;                     // 0x08
		RaceEventTable0x90* m_unk0x0c;                               // 0x0c
		GolWorldDatabase* m_unk0x10;                                 // 0x10
		GolWorldDatabase* m_unk0x14;                                 // 0x14
		undefined m_unk0x18[0x1c - 0x18];                            // 0x18
		CutsceneAnimation* m_unk0x1c;                                // 0x1c
		RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x20; // 0x20
		GolExport* m_unk0x24;                                        // 0x24
		GolD3DRenderDevice* m_unk0x28;                               // 0x28
		GolNameTable* m_unk0x2c;                                     // 0x2c
		RaceState* m_unk0x30;                                        // 0x30
		RaceSessionField0x32b4* m_unk0x34;                           // 0x34
		RaceState::Racer::Field0x008* m_unk0x38;                     // 0x38
		void* m_unk0x3c;                                             // 0x3c
		LegoU32 m_unk0x40;                                           // 0x40
		undefined m_unk0x44[0x5c - 0x44];                            // 0x44
		Field0x5c* m_unk0x5c;                                        // 0x5c
	};

	RaceEventDispatcher0x08();
	~RaceEventDispatcher0x08();

	void FUN_0048aad0(LegoS32 p_unk0x04, void* p_unk0x08);
	void FUN_0048ab20(LegoS32 p_unk0x04, void* p_unk0x08);
	void FUN_0048ab70(LegoS32 p_unk0x04);
	void FUN_0048abb0(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_unk0x0c);
	void FUN_0048ac30(LegoS32 p_unk0x04, void* p_context);
	void FUN_0048aca0(LegoS32 p_unk0x04, void* p_context);
	void FUN_0048ad10(LegoS32 p_unk0x04, LegoS32 p_unk0x08, void* p_context);
	void FUN_0048add0(undefined4 p_unk0x04);
	void FUN_0048ae00(GolCamera* p_unk0x04, RaceState::Racer* p_unk0x08);
	void FUN_0048ae30(GolD3DRenderDevice* p_renderer);
	void FUN_0048ae60();

private:
	friend class RaceSession;

	void Destroy();
	void FUN_0048a4d0(void* p_unk0x04, const LegoChar* p_name, LegoBool32 p_binary);

	LegoU32 m_count;  // 0x00
	Item** m_entries; // 0x04
};

#endif
