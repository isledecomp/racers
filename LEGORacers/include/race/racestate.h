#ifndef RACESTATE_H
#define RACESTATE_H

#include "app/legoracers.h"
#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golworldentitygroup0x38.h"
#include "material/materialtable0x0c.h"
#include "race/data/championdefinitionlist.h"
#include "race/racesessionfield0x27d4.h"
#include "racer/chassismodeltable.h"
#include "racer/drivercosmetictable.h"
#include "types.h"

class GolD3DRenderDevice;
class GolCamera;
class CutsceneAnimation;
class CobaltTrail0x140;
class RaceCameraController;
struct CutsceneParticleRef;

// SIZE 0x320
class RaceState {
public:
	// SIZE 0xe34
	class Racer {
	public:
		class Field0x004 {
		public:
			void FUN_00443b50(LegoU32 p_unk0x04);
			void FUN_00443b80(
				LegoU32 p_unk0x04,
				GolVec3* p_unk0x08,
				LegoFloat p_unk0x0c,
				LegoFloat p_unk0x10,
				LegoFloat p_unk0x14,
				LegoFloat p_unk0x18
			);
		};

		class Field0x008 {
		public:
			void FUN_0045a950(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045a9b0(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045b030(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045b1e0(Racer* p_racer, LegoU32 p_unk0x08);
		};

		class Field0x00c {
		public:
			undefined4 FUN_0043d070(Racer* p_racer);
		};

		// SIZE 0x3d0
		class Field0x018 {
		public:
			class Field0x1dc {
			public:
				// SIZE 0x70
				class Field0x1a4 {
				public:
					GolVec3 m_unk0x000;                 // 0x00
					undefined m_unk0x00c[0x70 - 0x00c]; // 0x0c
				};

				undefined m_unk0x000[0x1a4 - 0x000]; // 0x000
				Field0x1a4 m_unk0x1a4[4];            // 0x1a4
			};

			enum {
				c_flags0x000Bit2 = 1 << 2,
				c_flags0x000Bit3 = 1 << 3,
				c_flags0x000Bit4 = 1 << 4,
				c_flags0x000Bit10 = 1 << 10,
				c_flags0x000Bit11 = 1 << 11,
				c_flags0x000Bit12 = 1 << 12,
				c_slotFlagsBit1 = 1 << 1,
				c_slotFlagsBit2 = 1 << 2,
			};

			void FUN_0043dcd0();
			void FUN_0043dd50(LegoU32 p_unk0x04, const LegoChar* p_unk0x08);
			void FUN_0043def0();
			void FUN_0043df90();
			void FUN_0043fa50(GolCamera* p_camera);
			void FUN_00440030();
			void FUN_004400a0(ColorTransform0x20* p_unk0x04);
			void FUN_004400e0();
			void FUN_00440100(ColorTransform0x20* p_unk0x04, undefined4 p_unk0x08);
			void FUN_00440130();

			LegoU32 m_unk0x000;                                           // 0x000
			GolWorldEntityGroup0x38 m_unk0x004;                           // 0x004
			GolWorldEntity* m_unk0x03c;                                   // 0x03c
			GolWorldEntity* m_unk0x040;                                   // 0x040
			GolModelEntity* m_unk0x044;                                   // 0x044
			GolWorldEntity* m_unk0x048;                                   // 0x048
			undefined m_unk0x04c[0x058 - 0x04c];                          // 0x04c
			GolVec3 m_unk0x058;                                           // 0x058
			RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x064; // 0x064
			undefined m_unk0x068[0x07c - 0x068];                          // 0x068
			RaceSessionField0x27d4::Item::Field0x004 m_unk0x07c;          // 0x07c
			LegoFloat m_unk0x198;                                         // 0x198
			LegoFloat m_unk0x19c;                                         // 0x19c
			undefined m_unk0x1a0[0x1dc - 0x1a0];                          // 0x1a0
			Field0x1dc* m_unk0x1dc;                                       // 0x1dc
			RaceSessionField0x27d4* m_unk0x1e0;                           // 0x1e0
			RaceSessionField0x27d4::Item* m_unk0x1e4[4];                  // 0x1e4
			LegoU8 m_unk0x1f4[4];                                         // 0x1f4
			undefined m_unk0x1f8[0x218 - 0x1f8];                          // 0x1f8
			MaterialTable0x0c m_unk0x218;                                 // 0x218
			undefined m_unk0x224[0x230 - 0x224];                          // 0x224
			CutsceneParticleRef* m_unk0x230[4];                           // 0x230
			GolName m_unk0x240[4];                                        // 0x240
			LegoU32 m_unk0x260[4];                                        // 0x260
			CutsceneParticleRef* m_unk0x270;                              // 0x270
			CutsceneParticleRef* m_unk0x274;                              // 0x274
			CutsceneParticleRef* m_unk0x278;                              // 0x278
			CutsceneAnimation* m_unk0x27c;                                // 0x27c
			CutsceneAnimation* m_unk0x280;                                // 0x280
			undefined m_unk0x284[0x3a0 - 0x284];                          // 0x284
			ColorTransform0x20 m_unk0x3a0;                                // 0x3a0
			LegoU32 m_unk0x3c0;                                           // 0x3c0
			LegoU32 m_unk0x3c4;                                           // 0x3c4
			undefined4 m_unk0x3c8;                                        // 0x3c8
			undefined m_unk0x3cc[0x3d0 - 0x3cc];                          // 0x3cc
		};

		class Field0x3e8 {
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
		};

		class Field0xd5c {
		public:
			class Field0x08 {
			public:
				virtual void VTable0x00();                     // vtable+0x00
				virtual void VTable0x04();                     // vtable+0x04
				virtual LegoU8 VTable0x08(GolVec3* p_unk0x04); // vtable+0x08
			};

			LegoU8 FUN_00453790(GolVec3 p_unk0x04);
			LegoU8 FUN_004537f0();
			LegoS32 FUN_00453840(GolVec3* p_unk0x04);

		private:
			undefined m_unk0x00[0x08 - 0x00]; // 0x00
			Field0x08 m_unk0x08;              // 0x08
			undefined m_unk0x0c[0x3c - 0x0c]; // 0x0c
			LegoU32 m_unk0x3c;                // 0x3c
			undefined m_unk0x40[0x4c - 0x40]; // 0x40
			LegoU32 m_unk0x4c;                // 0x4c
			undefined m_unk0x50[0x54 - 0x50]; // 0x50
			GolVec3 m_unk0x54;                // 0x54
			LegoU32 m_unk0x60;                // 0x60
			LegoU8 m_unk0x64;                 // 0x64
			undefined m_unk0x65[0x68 - 0x65]; // 0x65
		};

		// SIZE 0x54
		class Field0xc70 {
		public:
			enum {
				c_flags0x014Bit0 = 1 << 0,
				c_flags0x014Bit2 = 1 << 2,
				c_flags0x014Bit3 = 1 << 3,
				c_flags0x014Bit6 = 1 << 6,
				c_flags0x014Bit7 = 1 << 7,
			};

			class Field0x000 {
			public:
				void FUN_00448070();
				undefined4 FUN_00449090();
			};

			// SIZE 0x30
			class Field0x050 {
			public:
				void FUN_004a5220(undefined4 p_unk0x04);
				void FUN_004a5320(LegoFloat p_unk0x04);

				GolVec3 m_unk0x00;                // 0x00
				GolVec4 m_unk0x0c;                // 0x0c
				undefined m_unk0x1c[0x2c - 0x1c]; // 0x1c
				LegoFloat m_unk0x2c;              // 0x2c
			};

			undefined4 FUN_004202c0();
			GolVec4* FUN_004202f0(undefined4 p_unk0x04);

			Field0x000* m_unk0x000;              // 0x00
			undefined4 m_unk0x004;               // 0x04
			undefined4 m_unk0x008;               // 0x08
			undefined4 m_unk0x00c;               // 0x0c
			undefined4 m_unk0x010;               // 0x10
			LegoU32 m_unk0x014;                  // 0x14
			undefined m_unk0x018[0x024 - 0x018]; // 0x18
			LegoS32 m_unk0x024;                  // 0x24
			undefined m_unk0x028[0x02c - 0x028]; // 0x28
			undefined4 m_unk0x02c;               // 0x2c
			undefined m_unk0x030[0x034 - 0x030]; // 0x30
			GolVec3 m_unk0x034;                  // 0x34
			GolVec4 m_unk0x040;                  // 0x40
			Field0x050* m_unk0x050;              // 0x50
		};

		void FUN_00439100();
		LegoU32 FUN_00439210(LegoU32 p_unk0x04);
		void FUN_00439340();
		void FUN_004393d0();
		void FUN_0043a0c0();
		void FUN_0043a0e0();
		void FUN_0043a210(LegoU32 p_unk0x04);
		void FUN_0043a300(LegoU32 p_unk0x04, LegoBool32 p_unk0x08);
		void FUN_0043a360();
		void FUN_0043a390();
		void FUN_00439870();
		void FUN_0043a3e0();
		void FUN_0043a3f0();
		void FUN_0043a400();

	private:
		enum {
			c_flags0xd04Bit1 = 1 << 1,
			c_flags0xd04Bit7 = 1 << 7,
			c_flags0xd04Bit10 = 1 << 10,
			c_flags0xd04Bit12 = 1 << 12,
			c_flags0xd04Bit22 = 0x00400000,
			c_flags0xd04Bit24 = 0x01000000,
			c_flags0xd04Bit25 = 0x02000000,
			c_flags0xd04Bit27 = 0x08000000,
			c_flags0xaa8Bit3 = 1 << 3,
			c_randomTableMask = 0x3ff,
			c_feedbackVariantCount = 6,
			c_feedbackHighOffset = 6,
		};

		void FUN_00439240(LegoBool32 p_unk0x04);
		LegoBool32 FUN_00439420(Field0xd5c* p_unk0x04);
		Field0xd5c* FUN_00439490();
		LegoU32 FUN_00439520();
		void FUN_00439c90();

	public:
		undefined m_unk0x000[0x004 - 0x000]; // 0x000
		Field0x004* m_unk0x004;              // 0x004
		Field0x008* m_unk0x008;              // 0x008
		Field0x00c* m_unk0x00c;              // 0x00c
		undefined m_unk0x010[0x018 - 0x010]; // 0x010
		Field0x018 m_unk0x018;               // 0x018
		Field0x3e8 m_unk0x3e8;               // 0x3e8
		undefined m_unk0x3ec[0xa00 - 0x3ec]; // 0x3ec
		LegoFloat m_unk0xa00;                // 0xa00
		undefined m_unk0xa04[0xaa8 - 0xa04]; // 0xa04
		LegoU32 m_unk0xaa8;                  // 0xaa8
		undefined m_unk0xaac[0xad4 - 0xaac]; // 0xaac
		LegoU32 m_unk0xad4;                  // 0xad4
		undefined m_unk0xad8[0xb30 - 0xad8]; // 0xad8
		LegoU32 m_unk0xb30;                  // 0xb30
		undefined m_unk0xb34[0xc70 - 0xb34]; // 0xb34
		Field0xc70 m_unk0xc70;               // 0xc70
		undefined m_unk0xcc4[0xccc - 0xcc4]; // 0xcc4
		LegoU32 m_unk0xccc;                  // 0xccc
		undefined m_unk0xcd0[0xcd8 - 0xcd0]; // 0xcd0
		LegoU32 m_unk0xcd8;                  // 0xcd8
		LegoU32 m_unk0xcdc;                  // 0xcdc
		LegoU8 m_unk0xce0;                   // 0xce0
		undefined m_unk0xce1[0xce4 - 0xce1]; // 0xce1
		LegoU32 m_lapsCompleted;             // 0xce4
		LegoU32 m_unk0xce8;                  // 0xce8
		LegoU32 m_lapTimes[0x18 / 4];        // 0xcec
		LegoU32 m_unk0xd04;                  // 0xd04
		LegoU32 m_unk0xd08;                  // 0xd08
		LegoU32 m_unk0xd0c;                  // 0xd0c
		LegoU32 m_unk0xd10;                  // 0xd10
		LegoU32 m_unk0xd14;                  // 0xd14
		undefined m_unk0xd18[0xd1e - 0xd18]; // 0xd18
		LegoU8 m_unk0xd1e;                   // 0xd1e
		undefined m_unk0xd1f[0xd40 - 0xd1f]; // 0xd1f
		LegoU32 m_unk0xd40;                  // 0xd40
		LegoU32 m_unk0xd44;                  // 0xd44
		undefined m_unk0xd48[0xd58 - 0xd48]; // 0xd48
		LegoU32 m_unk0xd58;                  // 0xd58
		Field0xd5c* m_unk0xd5c[3];           // 0xd5c
		undefined m_unk0xd68[0xd84 - 0xd68]; // 0xd68
		LegoU32 m_unk0xd84;                  // 0xd84
		LegoU32 m_unk0xd88;                  // 0xd88
		undefined m_unk0xd8c[0xdb4 - 0xd8c]; // 0xd8c
		RaceCameraController* m_unk0xdb4;    // 0xdb4
		LegoU32 m_unk0xdb8;                  // 0xdb8
		undefined m_unk0xdbc[0xe04 - 0xdbc]; // 0xdbc
		LegoU32 m_unk0xe04;                  // 0xe04
		undefined m_unk0xe08[0xe2c - 0xe08]; // 0xe08
		undefined4 m_unk0xe2c;               // 0xe2c
		CobaltTrail0x140* m_unk0xe30;        // 0xe30
	};

	// SIZE 0x194
	class Field0x0f0 {
	public:
		Field0x0f0();
		~Field0x0f0();

	private:
		friend class RaceState;

		undefined m_unk0x000[0x050 - 0x000]; // 0x000
		Racer* m_racers;                     // 0x050
		LegoU32 m_racerCount;                // 0x054
		undefined m_unk0x058[0x194 - 0x058]; // 0x058
	};

	// SIZE 0x1c
	class Field0x284 {
	public:
		Field0x284();
		~Field0x284();

	private:
		friend class RaceState;

		void Reset();
		void Destroy();

		undefined4 m_unk0x00[4];          // 0x00
		undefined m_unk0x10[0x18 - 0x10]; // 0x10
		LegoU8 m_lapCount;                // 0x18
		undefined m_unk0x19[0x1c - 0x19]; // 0x19
	};

	// SIZE 0x78
	class Field0x2a0 {
	public:
		Field0x2a0();
		~Field0x2a0();

	private:
		void Reset();
		void Destroy();

		undefined4 m_unk0x00; // 0x00
		undefined4 m_unk0x04; // 0x04
		undefined4 m_unk0x08; // 0x08
		undefined4 m_unk0x0c; // 0x0c
		undefined4 m_unk0x10; // 0x10
		undefined4 m_unk0x14; // 0x14
		LegoFloat m_unk0x18;  // 0x18
		undefined4 m_unk0x1c; // 0x1c
		undefined m_unk0x20[0x28 - 0x20];
		undefined4 m_unk0x28; // 0x28
		LegoFloat m_unk0x2c;  // 0x2c
		undefined4 m_unk0x30; // 0x30
		undefined4 m_unk0x34; // 0x34
		undefined4 m_unk0x38; // 0x38
		undefined4 m_unk0x3c; // 0x3c
		undefined4 m_unk0x40; // 0x40
		undefined4 m_unk0x44; // 0x44
		undefined4 m_unk0x48; // 0x48
		undefined4 m_unk0x4c; // 0x4c
		undefined4 m_unk0x50; // 0x50
		undefined4 m_unk0x54; // 0x54
		undefined4 m_unk0x58; // 0x58
		undefined4 m_unk0x5c; // 0x5c
		LegoFloat m_unk0x60;  // 0x60
		undefined4 m_unk0x64; // 0x64
		undefined4 m_unk0x68; // 0x68
		undefined4 m_unk0x6c; // 0x6c
		LegoFloat m_unk0x70;  // 0x70
		undefined4 m_unk0x74; // 0x74
	};

	RaceState();
	~RaceState();
	void RecordBestTimes(LegoRacers::Context* p_context);
	Racer* GetRacers() { return m_unk0x0f0.m_racers; }
	Racer* GetUnk0x318() { return m_unk0x318[0]; }

private:
	friend class RaceSession;

	enum {
		c_invalidTime = 0xffffffff,
	};

	void FUN_0043bff0(GolD3DRenderDevice* p_renderer);
	void FUN_0043c030(LegoU32 p_elapsedMs);
	void FUN_0043c6a0(GolCamera* p_camera);
	void FUN_0043ccb0();
	void FUN_0043cd30(GolD3DRenderDevice* p_renderer, Racer* p_racer);
	void Reset();
	void Destroy();

	DriverCosmeticTable m_unk0x000;    // 0x000
	ChampionDefinitionList m_unk0x080; // 0x080
	ChassisModelTable m_unk0x0b4;      // 0x0b4
	Field0x0f0 m_unk0x0f0;             // 0x0f0
	Field0x284 m_unk0x284;             // 0x284
	Field0x2a0 m_unk0x2a0;             // 0x2a0
	Racer* m_unk0x318[2];              // 0x318
};

#endif // RACESTATE_H
