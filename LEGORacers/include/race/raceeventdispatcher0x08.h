#ifndef RACEEVENTDISPATCHER0X08_H
#define RACEEVENTDISPATCHER0X08_H

#include "decomp.h"
#include "golmath.h"
#include "race/racestate.h"
#include "types.h"

class GolCamera;
class GolD3DRenderDevice;
class GolFileParser;
class GolAnimatedEntity;
class GolModelEntity;
class GolNameTable;
class GolWorldDatabase;
class RaceEventTable0x90;
class RaceSession;

// SIZE 0x08
class RaceEventDispatcher0x08 {
public:
	class Context;

	// VTABLE: LEGORACERS 0x004b40c4
	// SIZE 0x10
	class Item {
	public:
		Item();
		virtual void VTable0x00(undefined4);                    // vtable+0x00
		virtual void VTable0x04(void*) = 0;                     // vtable+0x04
		virtual void VTable0x08(void*) = 0;                     // vtable+0x08
		virtual ~Item();                                        // vtable+0x0c
		virtual void VTable0x10(Context*, GolFileParser*) = 0;  // vtable+0x10
		virtual void VTable0x14(undefined4);                    // vtable+0x14
		virtual void VTable0x18(GolCamera*, RaceState::Racer*); // vtable+0x18
		virtual void VTable0x1c(GolD3DRenderDevice*);           // vtable+0x1c
		virtual LegoBool32 VTable0x20();                        // vtable+0x20
		virtual void VTable0x24();                              // vtable+0x24
		virtual void VTable0x28(LegoS32, void*);                // vtable+0x28
		virtual void VTable0x2c(LegoS32, void*);                // vtable+0x2c

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
		undefined4 m_unk0x14;         // 0x14
		Field0x18* m_unk0x18;         // 0x18
		LegoU32 m_unk0x1c;            // 0x1c
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
		GolWorldDatabase* GetUnk0x10() const { return m_unk0x10; }
		GolWorldDatabase* GetUnk0x14() const { return m_unk0x14; }
		undefined4 GetUnk0x1c() const { return m_unk0x1c; }
		GolNameTable* GetUnk0x2c() const { return m_unk0x2c; }
		RaceState::Racer::Field0x008* GetUnk0x38() const { return m_unk0x38; }
		LegoU32 GetUnk0x40() const { return m_unk0x40; }
		Field0x5c* GetUnk0x5c() const { return m_unk0x5c; }

	private:
		friend class RaceEventDispatcher0x08;

		undefined m_unk0x00[0x0c];               // 0x00
		RaceEventTable0x90* m_unk0x0c;           // 0x0c
		GolWorldDatabase* m_unk0x10;             // 0x10
		GolWorldDatabase* m_unk0x14;             // 0x14
		undefined m_unk0x18[0x1c - 0x18];        // 0x18
		undefined4 m_unk0x1c;                    // 0x1c
		undefined m_unk0x20[0x2c - 0x20];        // 0x20
		GolNameTable* m_unk0x2c;                 // 0x2c
		undefined m_unk0x30[0x38 - 0x30];        // 0x30
		RaceState::Racer::Field0x008* m_unk0x38; // 0x38
		undefined4 m_unk0x3c;                    // 0x3c
		LegoU32 m_unk0x40;                       // 0x40
		undefined m_unk0x44[0x5c - 0x44];        // 0x44
		Field0x5c* m_unk0x5c;                    // 0x5c
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
