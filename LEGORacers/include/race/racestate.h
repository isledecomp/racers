#ifndef RACESTATE_H
#define RACESTATE_H

#include "app/legoracers.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golworldentitygroup0x38.h"
#include "material/materialtable0x0c.h"
#include "race/data/championdefinitionlist.h"
#include "race/raceresourcemanager.h"
#include "race/racesessionfield0x27d4.h"
#include "racer/chassismodeltable.h"
#include "racer/drivercosmetictable.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolCamera;
class GolD3DRenderDevice;
class GolRenderDevice;
class GolWorldDatabase;
class GolAnimatedEntity;
class CutsceneAnimation;
class CobaltTrail0x140;
class RaceCameraController;
class SoundGroup;
class SoundManager;
class SpatialSoundInstance;
struct CutsceneParticleRef;
struct SoundVector;

// SIZE 0x320
class RaceState {
public:
	class Field0x2a0;

	// SIZE 0xe34
	class Racer {
	public:
		class Field0x004 {
		public:
			void FUN_00443b50(LegoU32 p_unk0x04);
			void FUN_00443b80(
				LegoU32 p_unk0x04,
				SoundVector* p_unk0x08,
				LegoFloat p_unk0x0c,
				LegoFloat p_unk0x10,
				LegoFloat p_unk0x14,
				LegoFloat p_unk0x18
			);
			SpatialSoundInstance* FUN_00443bd0(LegoU32 p_unk0x04);

		private:
			LegoU32 FUN_00443c30(LegoU32 p_unk0x04, SoundGroup** p_soundGroup);

			SoundManager* m_soundManager; // 0x00
			SoundGroup* m_groups[4];      // 0x04
		};

		class Field0x008 {
		public:
			LegoU32 FUN_0045a950(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045a9b0(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045b030(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045b1e0(Racer* p_racer, LegoU32 p_unk0x08);

			class Action {
			public:
				virtual void VTable0x00() = 0;    // vtable+0x00
				virtual void VTable0x04() = 0;    // vtable+0x04
				virtual void VTable0x08() = 0;    // vtable+0x08
				virtual void VTable0x0c() = 0;    // vtable+0x0c
				virtual void VTable0x10() = 0;    // vtable+0x10
				virtual void VTable0x14() = 0;    // vtable+0x14
				virtual LegoU32 VTable0x18() = 0; // vtable+0x18
				virtual void VTable0x1c() = 0;    // vtable+0x1c

				void FUN_0045bd30(
					Racer* p_racer,
					LegoU32 p_unk0x08,
					GolAnimatedEntity* p_unk0x0c,
					GolAnimatedEntity* p_unk0x10
				);
				void FUN_0045c8f0(Racer* p_racer, LegoU32 p_unk0x08);
				LegoU32 FUN_0045d560(Racer* p_racer, GolModelEntity* p_unk0x08, LegoU32 p_unk0x0c);

				LegoS32 m_unk0x004;               // 0x04
				LegoU32 m_unk0x008;               // 0x08
				Action* m_next;                   // 0x0c
				Field0x004* m_unk0x010;           // 0x10
				LegoU32 m_unk0x014;               // 0x14
				GolAnimatedEntity* m_unk0x018;    // 0x18
				GolAnimatedEntity* m_unk0x01c;    // 0x1c
				Racer* m_unk0x020;                // 0x20
				Field0x008* m_unk0x024;           // 0x24
				SpatialSoundInstance* m_unk0x028; // 0x28
			};

		private:
			friend class Action;

			// SIZE 0x2c
			class Field0x18b0 {
			public:
				undefined4 m_unk0x000;              // 0x00
				LegoS32 m_unk0x004;                 // 0x04
				undefined m_unk0x008[0x020 - 0x08]; // 0x08
				Racer* m_unk0x020;                  // 0x20
				undefined m_unk0x024[0x02c - 0x24]; // 0x24
			};

			LegoU32 FUN_0045aa30(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045ab50(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045ac80(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045ace0(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045ad30(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045adf0(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045aeb0(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045af80(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045b260(Racer* p_racer, LegoU32 p_unk0x08);
			Action* FUN_0045b2e0(
				LegoU32 p_unk0x04,
				LegoU32 p_unk0x08,
				LegoS32 p_unk0x0c,
				LegoS32 p_unk0x10,
				LegoS32 p_unk0x14
			);
			void FUN_0045b640(Racer* p_racer);
			GolAnimatedEntity* FUN_0045b9e0();

			undefined m_unk0x000[0x05c - 0x000];    // 0x000
			GolWorldDatabase* m_unk0x05c;           // 0x05c
			undefined m_unk0x060[0x098 - 0x060];    // 0x060
			Action* m_unk0x098;                     // 0x098
			Action* m_unk0x09c;                     // 0x09c
			Action* m_unk0x0a0;                     // 0x0a0
			GolAnimatedEntity m_unk0x0a4[25];       // 0x0a4
			LegoU32 m_unk0x1878;                    // 0x1878
			LegoU32 m_unk0x187c;                    // 0x187c
			Action* m_unk0x1880;                    // 0x1880
			undefined m_unk0x1884[0x188c - 0x1884]; // 0x1884
			LegoU8 m_unk0x188c;                     // 0x188c
			undefined m_unk0x188d[0x18b0 - 0x188d]; // 0x188d
			Field0x18b0* m_unk0x18b0;               // 0x18b0
			undefined m_unk0x18b4[0x1998 - 0x18b4]; // 0x18b4
			LegoU32 m_unk0x1998;                    // 0x1998
		};

		class Field0x00c {
		public:
			// SIZE 0x48
			class Entry {
			public:
				undefined4 m_unk0x000;              // 0x00
				undefined4 m_unk0x004;              // 0x04
				undefined m_unk0x008[0x024 - 0x08]; // 0x08
				GolVec3 m_unk0x024;                 // 0x24
				undefined m_unk0x030[0x048 - 0x30]; // 0x30
			};

			Entry* FUN_0043d070(Racer* p_racer);

		private:
			undefined m_unk0x000[0x190 - 0x000]; // 0x000
			Entry* m_entries;                    // 0x190
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
				c_flags0x000Bit1 = 1 << 1,
				c_flags0x000Bit2 = 1 << 2,
				c_flags0x000Bit3 = 1 << 3,
				c_flags0x000Bit4 = 1 << 4,
				c_flags0x000Bit8 = 1 << 8,
				c_flags0x000Bit10 = 1 << 10,
				c_flags0x000Bit11 = 1 << 11,
				c_flags0x000Bit12 = 1 << 12,
				c_alphaOverrideFlag = 1,
				c_fadeAlphaMax = 0xbf,
				c_racerFlags0xd04Bit11 = 1 << 11,
				c_slotFlagsBit1 = 1 << 1,
				c_slotFlagsBit2 = 1 << 2,
			};

			void FUN_0043d9f0();
			void FUN_0043da10();
			void FUN_0043da30();
			void FUN_0043db60();
			void FUN_0043dcd0();
			void FUN_0043dd50(LegoU32 p_unk0x04, const LegoChar* p_unk0x08);
			void FUN_0043de90(LegoU32 p_unk0x04);
			void FUN_0043def0();
			void FUN_0043df90();
			void FUN_0043e620();
			void FUN_0043fa50(GolCamera* p_camera);
			void FUN_0043fc20(GolD3DRenderDevice* p_renderer);
			void FUN_0043fd70();
			void FUN_0043fdb0();
			void FUN_00440030();
			void FUN_004400a0(ColorTransform0x20* p_unk0x04);
			void FUN_004400e0();
			void FUN_00440100(ColorTransform0x20* p_unk0x04, undefined4 p_unk0x08);
			void FUN_00440130();
			void FUN_00440160(LegoFloat p_unk0x04);
			void FUN_004401a0();

			LegoU32 m_unk0x000;                                           // 0x000
			GolWorldEntityGroup0x38 m_unk0x004;                           // 0x004
			GolModelEntity* m_unk0x03c;                                   // 0x03c
			GolAnimatedEntity* m_unk0x040;                                // 0x040
			GolAnimatedEntity* m_unk0x044;                                // 0x044
			GolAnimatedEntity* m_unk0x048;                                // 0x048
			GolVec3 m_unk0x04c;                                           // 0x04c
			GolVec3 m_unk0x058;                                           // 0x058
			RaceSessionField0x27d4::Item::Field0x004::Params* m_unk0x064; // 0x064
			LegoFloat m_unk0x068[3];                                      // 0x068
			GolName m_unk0x074;                                           // 0x074
			RaceSessionField0x27d4::Item::Field0x004 m_unk0x07c;          // 0x07c
			LegoFloat m_unk0x198;                                         // 0x198
			LegoFloat m_unk0x19c;                                         // 0x19c
			undefined m_unk0x1a0[0x1d8 - 0x1a0];                          // 0x1a0
			Racer* m_racer;                                               // 0x1d8
			Field0x1dc* m_unk0x1dc;                                       // 0x1dc
			RaceSessionField0x27d4* m_unk0x1e0;                           // 0x1e0
			RaceSessionField0x27d4::Item* m_unk0x1e4[4];                  // 0x1e4
			LegoU8 m_unk0x1f4[4];                                         // 0x1f4
			undefined m_unk0x1f8[0x218 - 0x1f8];                          // 0x1f8
			MaterialTable0x0c m_unk0x218;                                 // 0x218
			MaterialTable0x0c m_unk0x224;                                 // 0x224
			CutsceneParticleRef* m_unk0x230[4];                           // 0x230
			GolName m_unk0x240[4];                                        // 0x240
			LegoU32 m_unk0x260[4];                                        // 0x260
			CutsceneParticleRef* m_unk0x270;                              // 0x270
			CutsceneParticleRef* m_unk0x274;                              // 0x274
			CutsceneParticleRef* m_unk0x278;                              // 0x278
			CutsceneAnimation* m_unk0x27c;                                // 0x27c
			CutsceneAnimation* m_unk0x280;                                // 0x280
			GolWorldEntity m_unk0x284;                                    // 0x284
			undefined m_unk0x2ac[0x3a0 - 0x2ac];                          // 0x2ac
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
			virtual void VTable0x2c(); // vtable+0x2c
			virtual void VTable0x30(); // vtable+0x30
			virtual void VTable0x34(); // vtable+0x34
			virtual void VTable0x38(); // vtable+0x38
			virtual void VTable0x3c(); // vtable+0x3c

			void FUN_00429330();
			void FUN_00429af0();
			void FUN_00448930(LegoS32 p_unk0x04);

		private:
			enum {
				c_unk0x140Count = 5,
			};

			undefined m_unk0x004[0x140 - 0x004]; // 0x004
			LegoS32 m_unk0x140[c_unk0x140Count]; // 0x140
			LegoU32 m_unk0x154;                  // 0x154
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

		class Field0xadc {
		public:
			void FUN_00462580(LegoS32 p_unk0x04, LegoS32 p_unk0x08, GolVec3* p_unk0x0c);
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
				c_flags0x014Bit8 = 1 << 8,
			};

			class Field0x000 {
			public:
				void FUN_00448070();
				undefined4 FUN_00449090();
			};

			// SIZE 0x30
			class Field0x050 {
			public:
				void FUN_004a5220(Field0x00c::Entry* p_unk0x04);
				void FUN_004a5320(LegoFloat p_unk0x04);

				GolVec3 m_unk0x00;                // 0x00
				GolVec4 m_unk0x0c;                // 0x0c
				LegoFloat m_unk0x1c;              // 0x1c
				undefined m_unk0x20[0x28 - 0x20]; // 0x20
				Field0x00c::Entry* m_unk0x28;     // 0x28
				LegoFloat m_unk0x2c;              // 0x2c
			};

			undefined4 FUN_004202c0();
			GolVec4* FUN_004202f0(Field0x00c::Entry* p_unk0x04);

			Field0x000* m_unk0x000;              // 0x00
			Field0x00c::Entry* m_unk0x004;       // 0x04
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

		enum {
			c_flags0xd04Bit21 = 0x00200000,
		};

		void FUN_00439100();
		LegoU32 FUN_00439210(LegoU32 p_unk0x04);
		void FUN_00439340();
		void FUN_004393d0();
		void FUN_004371c0(undefined4* p_unk0x04, LegoFloat p_unk0x08);
		void FUN_004374c0();
		void FUN_00438500();
		LegoU32 FUN_00439520();
		void FUN_004395a0();
		void FUN_00439660();
		void FUN_00439730();
		void FUN_00439790();
		void FUN_004397b0();
		void FUN_0043a0c0();
		void FUN_0043a0e0();
		void FUN_0043a1a0();
		void FUN_0043a210(LegoU32 p_unk0x04);
		void FUN_0043a300(LegoU32 p_unk0x04, LegoBool32 p_unk0x08);
		void FUN_0043a360();
		void FUN_0043a390();
		LegoU32 FUN_00439770(LegoU32 p_unk0x04);
		void FUN_00439870();
		void FUN_00439b00();
		void FUN_0043a3e0();
		void FUN_0043a3f0();
		void FUN_0043a400();

	private:
		friend class Field0x008::Action;

		enum {
			c_flags0xd04Bit0 = 1 << 0,
			c_flags0xd04Bit1 = 1 << 1,
			c_flags0xd04Bit3 = 1 << 3,
			c_flags0xd04Bit4 = 1 << 4,
			c_flags0xd04Bit6 = 1 << 6,
			c_flags0xd04Bit7 = 1 << 7,
			c_flags0xd04Bit10 = 1 << 10,
			c_flags0xd04Bit11 = 1 << 11,
			c_flags0xd04Bit12 = 1 << 12,
			c_flags0xd04Bit22 = 0x00400000,
			c_flags0xd04Bit24 = 0x01000000,
			c_flags0xd04Bit25 = 0x02000000,
			c_flags0xd04Bit27 = 0x08000000,
			c_flags0xaa8Bit3 = 1 << 3,
			c_flags0xaa8Bit12 = 1 << 12,
			c_randomTableMask = 0x3ff,
			c_feedbackVariantCount = 6,
			c_feedbackHighOffset = 6,
		};

		void FUN_00439240(LegoBool32 p_unk0x04);
		LegoBool32 FUN_00439420(Field0xd5c* p_unk0x04);
		Field0xd5c* FUN_00439490();
		void FUN_00439c90();

	public:
		undefined m_unk0x000[0x004 - 0x000]; // 0x000
		Field0x004* m_unk0x004;              // 0x004
		Field0x008* m_unk0x008;              // 0x008
		Field0x00c* m_unk0x00c;              // 0x00c
		undefined m_unk0x010[0x018 - 0x010]; // 0x010
		Field0x018 m_unk0x018;               // 0x018
		Field0x3e8 m_unk0x3e8;               // 0x3e8
		undefined m_unk0x540[0xa00 - 0x540]; // 0x540
		LegoFloat m_unk0xa00;                // 0xa00
		undefined m_unk0xa04[0xaa8 - 0xa04]; // 0xa04
		LegoU32 m_unk0xaa8;                  // 0xaa8
		undefined m_unk0xaac[0xad4 - 0xaac]; // 0xaac
		LegoU32 m_unk0xad4;                  // 0xad4
		undefined m_unk0xad8[0xadc - 0xad8]; // 0xad8
		Field0xadc* m_unk0xadc;              // 0xadc
		undefined m_unk0xae0[0xb2c - 0xae0]; // 0xae0
		undefined4 m_unk0xb2c;               // 0xb2c
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
		undefined m_unk0xd1f[0xd23 - 0xd1f]; // 0xd1f
		LegoU8 m_unk0xd23;                   // 0xd23
		undefined m_unk0xd24[0xd40 - 0xd24]; // 0xd24
		LegoU32 m_unk0xd40;                  // 0xd40
		LegoU32 m_unk0xd44;                  // 0xd44
		undefined m_unk0xd48[0xd58 - 0xd48]; // 0xd48
		LegoU32 m_unk0xd58;                  // 0xd58
		Field0xd5c* m_unk0xd5c[3];           // 0xd5c
		undefined m_unk0xd68[0xd6c - 0xd68]; // 0xd68
		LegoU32 m_unk0xd6c;                  // 0xd6c
		undefined m_unk0xd70[0xd84 - 0xd70]; // 0xd70
		LegoU32 m_unk0xd84;                  // 0xd84
		LegoU32 m_unk0xd88;                  // 0xd88
		undefined m_unk0xd8c[0xdb4 - 0xd8c]; // 0xd8c
		RaceCameraController* m_unk0xdb4;    // 0xdb4
		LegoU32 m_unk0xdb8;                  // 0xdb8
		undefined m_unk0xdbc[0xe04 - 0xdbc]; // 0xdbc
		LegoU32 m_unk0xe04;                  // 0xe04
		undefined m_unk0xe08[0xe2c - 0xe08]; // 0xe08
		Field0x00c::Entry* m_unk0xe2c;       // 0xe2c
		CobaltTrail0x140* m_unk0xe30;        // 0xe30
	};

	// VTABLE: LEGORACERS 0x004b0aa8
	// SIZE 0x194
	class Field0x0f0 : public LegoEventQueue::Field0x30 {
	public:
		Field0x0f0();
		LegoS32 VTable0x00(LegoEventQueue::Event* p_event) override;         // vtable+0x00
		void Destroy() override;                                             // vtable+0x0c
		void VTable0x10(LegoU32 p_elapsedMs) override;                       // vtable+0x10
		GolWorldEntity* VTable0x14(LegoEventQueue::Event* p_event) override; // vtable+0x14

	private:
		friend class RaceState;

		void FUN_0043d200();
		void FUN_0043d270();
		void FUN_0043d3f0();

		LegoEventQueue::Event* m_unk0x048;         // 0x048
		LegoEventQueue::Event* m_unk0x04c;         // 0x04c
		Racer* m_racers;                           // 0x050
		LegoU32 m_racerCount;                      // 0x054
		undefined4 m_unk0x058;                     // 0x058
		RaceResourceManager* m_unk0x05c;           // 0x05c
		undefined4 m_unk0x060;                     // 0x060
		undefined4 m_unk0x064[6];                  // 0x064
		RaceResourceManager::Resource* m_unk0x07c; // 0x07c
		undefined4 m_unk0x080[3];                  // 0x080
		undefined4 m_unk0x08c[2];                  // 0x08c
		undefined4 m_unk0x094[2];                  // 0x094
		undefined4 m_unk0x09c;                     // 0x09c
		undefined4 m_unk0x0a0;                     // 0x0a0
		GolVec3 m_unk0x0a4[6];                     // 0x0a4
		GolVec3 m_unk0x0ec[6];                     // 0x0ec
		GolVec3 m_unk0x134[6];                     // 0x134
		LegoU32 m_unk0x17c[6];                     // 0x17c
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
		undefined4 m_unk0x10;             // 0x10
		undefined4 m_unk0x14;             // 0x14
		LegoU8 m_lapCount;                // 0x18
		undefined m_unk0x19[0x1c - 0x19]; // 0x19
	};

	// SIZE 0x78
	class Field0x2a0 : public Racer::Field0xc70::Field0x050 {
	public:
		Field0x2a0();
		~Field0x2a0();
		LegoFloat m_unk0x30;  // 0x30
		LegoS32 m_unk0x34;    // 0x34
		LegoS32 m_unk0x38;    // 0x38
		GolVec3 m_unk0x3c;    // 0x3c
		GolVec3 m_unk0x48;    // 0x48
		GolVec4 m_unk0x54;    // 0x54
		LegoFloat m_unk0x64;  // 0x64
		undefined4 m_unk0x68; // 0x68
		undefined4 m_unk0x6c; // 0x6c
		LegoFloat m_unk0x70;  // 0x70
		LegoS32 m_unk0x74;    // 0x74

	private:
		void Reset();
		void Destroy();
	};

	RaceState();
	~RaceState();
	void FUN_0043d120();
	void RecordBestTimes(LegoRacers::Context* p_context);
	Racer* GetRacers() { return m_unk0x0f0.m_racers; }
	LegoU32 GetRacerCount() const { return m_unk0x0f0.m_racerCount; }
	Racer* GetUnk0x318() { return m_unk0x318[0]; }
	const GolVec3& GetUnk0x0a4(LegoU32 p_index) const { return m_unk0x0f0.m_unk0x0a4[p_index]; }
	const GolVec3& GetUnk0x0ec(LegoU32 p_index) const { return m_unk0x0f0.m_unk0x0ec[p_index]; }
	const GolVec3& GetUnk0x134(LegoU32 p_index) const { return m_unk0x0f0.m_unk0x134[p_index]; }
	LegoU32 GetUnk0x17c(LegoU32 p_index) const { return m_unk0x0f0.m_unk0x17c[p_index]; }
	Racer::Field0xc70::Field0x050* GetUnk0x2a0() { return &m_unk0x2a0; }

private:
	friend class RaceSession;

	enum {
		c_invalidTime = 0xffffffff,
		c_racerFlags0xd04Bit10 = 1 << 10,
		c_racerFlags0xd04Bit12 = 1 << 12,
	};

	void FUN_0043bff0(GolD3DRenderDevice* p_renderer);
	void FUN_0043c030(LegoU32 p_elapsedMs);
	void FUN_0043c6a0(GolCamera* p_camera);
	void FUN_0043ccb0();
	void FUN_0043cd30(GolRenderDevice* p_renderer, Racer* p_racer);
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
