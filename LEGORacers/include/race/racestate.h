#ifndef RACESTATE_H
#define RACESTATE_H

#include "app/legoracers.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golorientedentity.h"
#include "golstring.h"
#include "golworldentity.h"
#include "golworldentitygroup0x38.h"
#include "mabmaterialanimationitem0x18.h"
#include "material/materialtable0x0c.h"
#include "race/data/championdefinitionlist.h"
#include "race/raceresourcemanager.h"
#include "race/racesessionfield0x27d4.h"
#include "racer/chassismodeltable.h"
#include "racer/drivercosmetictable.h"
#include "scene/golbillboard.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolCamera;
class GolD3DRenderDevice;
class GolRenderDevice;
class GolWorldDatabase;
class GolAnimatedEntity;
class MabMaterialAnimationItem0x8;
class DuskwindBananaRelic0x24;
class CutsceneAnimation;
class CobaltTrail0x140;
class RaceCameraController;
class RaceEventTable0x90;
class RaceSessionField0x32b4;
class SoundGroup;
class SoundManager;
class SpatialSoundInstance;
struct CutsceneParticleRef;
struct SoundVector;

// SIZE 0x320
class RaceState {
public:
	// VTABLE: LEGORACERS 0x004b09b0
	// SIZE 0xe34
	class Racer {
	public:
		virtual void VTable0x00(undefined4* p_unk0x04); // vtable+0x00
		virtual void VTable0x04(undefined4 p_flags);    // vtable+0x04

		class Field0x00c;

		// Known fields currently reach through 0x2f.
		// SIZE 0x30
		class Field0x371c0 {
		public:
			undefined m_unk0x000[0x00c - 0x000]; // 0x000
			LegoS32 m_unk0x00c;                  // 0x00c
			undefined4 m_unk0x010;               // 0x010
			undefined m_unk0x014[0x028 - 0x014]; // 0x014
			RaceEventTable0x90* m_unk0x028;      // 0x028
			undefined4 m_unk0x02c;               // 0x02c
		};

		// Known fields currently reach through 0x86.
		// SIZE 0x88
		class Field0x371c0Vehicle {
		public:
			undefined m_unk0x000[0x028 - 0x000]; // 0x000
			GolVec3 m_unk0x028;                  // 0x028
			undefined m_unk0x034[0x038 - 0x034]; // 0x034
			LegoFloat m_unk0x038;                // 0x038
			undefined m_unk0x03c[0x040 - 0x03c]; // 0x03c
			LegoFloat m_unk0x040;                // 0x040
			LegoFloat m_unk0x044;                // 0x044
			undefined m_unk0x048[0x04c - 0x048]; // 0x048
			GolVec3 m_unk0x04c;                  // 0x04c
			LegoFloat m_unk0x058;                // 0x058
			LegoFloat m_unk0x05c;                // 0x05c
			undefined m_unk0x060[0x084 - 0x060]; // 0x060
			LegoU8 m_unk0x084;                   // 0x084
			LegoU8 m_unk0x085;                   // 0x085
			LegoU8 m_unk0x086;                   // 0x086
		};

		// SIZE 0x14
		class Field0x004 : public RaceResourceManager {
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

			SoundGroup* m_groups[4]; // 0x04
		};

		// SIZE 0x199c
		class Field0x008 {
		public:
			void FUN_0045a950(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045a9b0(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045b030(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045b1e0(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 GetUnk0x187c() const { return m_unk0x187c; }

			class Field0x050 {
			public:
				// SIZE 0x14
				class Entry {
				public:
					enum {
						c_flags0x10Bit1 = 1 << 1,
					};

					GolVec3 m_unk0x00;                // 0x00
					undefined4 m_unk0x0c;             // 0x0c
					LegoU8 m_flags0x10;               // 0x10
					undefined m_unk0x11[0x14 - 0x11]; // 0x11
				};

				Entry* FUN_0045c6a0(
					GolVec3* p_unk0x04,
					GolVec3* p_unk0x08,
					LegoFloat p_unk0x0c,
					LegoFloat p_unk0x10,
					LegoFloat p_unk0x14
				);

				Entry* m_entries; // 0x00
				LegoS32 m_count;  // 0x04
			};

			// SIZE 0x1c
			class ActionTarget {
			public:
				GolVec3 m_unk0x00; // 0x00
				GolVec3 m_unk0x0c; // 0x0c
				union {
					const LegoChar* m_materialName; // 0x18
					GolVec3* m_positionSource;      // 0x18
				};
			};

			// SIZE 0x14
			class ActionSetup {
			public:
				Racer* m_racer;               // 0x00
				Racer* m_unk0x04;             // 0x04
				Field0x050::Entry* m_unk0x08; // 0x08
				ActionTarget* m_unk0x0c;      // 0x0c
				LegoU32 m_unk0x10;            // 0x10
			};

			// SIZE 0x18
			class ActionBase {
			public:
				virtual void VTable0x00() = 0;    // vtable+0x00
				virtual void VTable0x04() = 0;    // vtable+0x04
				virtual void VTable0x08() = 0;    // vtable+0x08
				virtual void VTable0x0c() = 0;    // vtable+0x0c
				virtual void VTable0x10() = 0;    // vtable+0x10
				virtual void VTable0x14() = 0;    // vtable+0x14
				virtual LegoU32 VTable0x18() = 0; // vtable+0x18
				virtual void VTable0x1c() = 0;    // vtable+0x1c

				LegoS32 m_unk0x004;     // 0x04
				LegoU32 m_unk0x008;     // 0x08
				ActionBase* m_next;     // 0x0c
				Field0x004* m_unk0x010; // 0x10
				LegoU32 m_unk0x014;     // 0x14
			};

			// SIZE 0x2c
			class Action : public ActionBase {
			public:
				void FUN_0045bd30(
					Racer* p_racer,
					LegoU32 p_unk0x08,
					GolAnimatedEntity* p_unk0x0c,
					GolAnimatedEntity* p_unk0x10
				);
				void FUN_0045c8f0(Racer* p_racer, LegoU32 p_unk0x08);

				GolAnimatedEntity* m_unk0x018;    // 0x18
				GolAnimatedEntity* m_unk0x01c;    // 0x1c
				Racer* m_unk0x020;                // 0x20
				Field0x008* m_unk0x024;           // 0x24
				SpatialSoundInstance* m_unk0x028; // 0x28
			};

			// SIZE 0x84
			class MagnetAction : public ActionBase {
			public:
				void FUN_00455830(
					Racer* p_racer,
					GolAnimatedEntity* p_unk0x08,
					GolAnimatedEntity* p_unk0x0c,
					GolAnimatedEntity* p_unk0x10
				);

				undefined4* m_unk0x018;                    // 0x018
				undefined4* m_unk0x01c;                    // 0x01c
				undefined4 m_unk0x020;                     // 0x020
				undefined m_unk0x024[0x028 - 0x024];       // 0x024
				Racer* m_racer;                            // 0x028
				undefined4 m_unk0x02c;                     // 0x02c
				undefined4 m_unk0x030;                     // 0x030
				undefined4 m_unk0x034;                     // 0x034
				Field0x008* m_owner;                       // 0x038
				GolAnimatedEntity* m_unk0x03c;             // 0x03c
				GolAnimatedEntity* m_unk0x040;             // 0x040
				GolAnimatedEntity* m_unk0x044;             // 0x044
				undefined m_unk0x048[0x070 - 0x048];       // 0x048
				RaceResourceManager::Resource* m_unk0x070; // 0x070
				undefined m_unk0x074[0x078 - 0x074];       // 0x074
				Racer* m_unk0x078;                         // 0x078
				undefined4 m_unk0x07c;                     // 0x07c
				LegoU8 m_unk0x080;                         // 0x080
				undefined m_unk0x081[0x084 - 0x081];       // 0x081
			};

			// SIZE 0x224
			class MissileAction : public ActionBase {
			public:
				void FUN_00456560(
					GolAnimatedEntity* p_unk0x04,
					GolAnimatedEntity* p_unk0x08,
					Racer* p_racer,
					LegoU32 p_unk0x10
				);

				undefined4* m_unk0x018;              // 0x018
				Field0x008* m_owner;                 // 0x01c
				undefined4 m_unk0x020;               // 0x020
				Racer* m_racer;                      // 0x024
				undefined4 m_unk0x028;               // 0x028
				undefined m_unk0x02c[0x124 - 0x02c]; // 0x02c
				GolAnimatedEntity* m_unk0x124;       // 0x124
				GolAnimatedEntity m_unk0x128;        // 0x128
				undefined4 m_unk0x21c;               // 0x21c
				LegoU32 m_unk0x220;                  // 0x220
			};

			// SIZE 0x17c
			class BarrelAction : public ActionBase {
			public:
				LegoU32 FUN_00452f60(Racer* p_racer, Racer* p_unk0x08);

				undefined m_unk0x018[0x028 - 0x018]; // 0x18
				Racer* m_racer;                      // 0x28
				undefined m_unk0x02c[0x174 - 0x02c]; // 0x2c
				Racer* m_unk0x174;                   // 0x174
				undefined4 m_unk0x178;               // 0x178
			};

			// SIZE 0xe8
			class CannonAction : public ActionBase {
			public:
				class Field0xd8 {
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
					virtual LegoU32 VTable0x4c(
						DuskwindBananaRelic0x24* p_material,
						LegoFloat p_unk0x08,
						LegoFloat p_unk0x0c,
						LegoFloat p_unk0x10
					) = 0; // vtable+0x4c
				};

				LegoU32 FUN_00451a50(ActionSetup* p_unk0x04);

				undefined4* m_unk0x018;              // 0x18
				Field0x008* m_owner;                 // 0x1c
				undefined4 m_unk0x020;               // 0x20
				Racer* m_racer;                      // 0x24
				Racer* m_unk0x028;                   // 0x28
				Field0x050::Entry* m_unk0x02c;       // 0x2c
				undefined m_unk0x030[0x0d8 - 0x030]; // 0x30
				Field0xd8* m_unk0x0d8;               // 0xd8
				CutsceneParticleRef* m_unk0x0dc;     // 0xdc
				const LegoChar* m_materialName;      // 0xe0
				undefined4* m_unk0x0e4;              // 0xe4
			};

			// SIZE 0x290
			class TetherAction : public ActionBase {
			public:
				LegoU32 FUN_00453de0(
					GolModelEntity* p_unk0x04,
					Racer* p_racer,
					Racer* p_unk0x0c,
					Field0x050::Entry* p_unk0x10,
					MabMaterialAnimationItem0x18* p_unk0x14,
					LegoU32 p_unk0x18
				);

				undefined4* m_unk0x018;                  // 0x018
				Field0x008* m_owner;                     // 0x01c
				undefined4 m_unk0x020;                   // 0x020
				Racer* m_racer;                          // 0x024
				Racer* m_unk0x028;                       // 0x028
				Field0x050::Entry* m_unk0x02c;           // 0x02c
				undefined m_unk0x030[0x268 - 0x030];     // 0x030
				GolModelEntity* m_unk0x268;              // 0x268
				CutsceneParticleRef* m_unk0x26c;         // 0x26c
				GolBillboard* m_unk0x270;                // 0x270
				MabMaterialAnimationItem0x18 m_unk0x274; // 0x274
				LegoU32 m_unk0x28c;                      // 0x28c
			};

			// SIZE 0x24c
			class LightningAction : public ActionBase {
			public:
				void FUN_00454cb0(Racer* p_racer, ActionTarget* p_unk0x08);

				undefined4* m_unk0x018;                    // 0x018
				Field0x008* m_owner;                       // 0x01c
				undefined4 m_unk0x020;                     // 0x020
				Racer* m_racer;                            // 0x024
				undefined4 m_unk0x028;                     // 0x028
				undefined m_unk0x02c[0x22c - 0x02c];       // 0x02c
				undefined4 m_unk0x22c;                     // 0x22c
				undefined m_unk0x230[0x234 - 0x230];       // 0x230
				undefined4 m_unk0x234;                     // 0x234
				RaceResourceManager::Resource* m_unk0x238; // 0x238
				GolVec3* m_positionSource;                 // 0x23c
				undefined4 m_unk0x240;                     // 0x240
				CutsceneParticleRef* m_unk0x244;           // 0x244
				GolBillboard* m_unk0x248;                  // 0x248
			};

			// SIZE 0x190
			class Field0x1894Action : public ActionBase {
			public:
				void FUN_00457230(Racer* p_racer);

				undefined m_unk0x018[0x028 - 0x018]; // 0x018
				Racer* m_racer;                      // 0x028
				undefined m_unk0x02c[0x190 - 0x02c]; // 0x02c
			};

			// SIZE 0x2c
			class EffectActionBase : public ActionBase {
			public:
				Racer* m_unk0x018;        // 0x18
				undefined4* m_unk0x01c;   // 0x1c
				ActionTarget* m_unk0x020; // 0x20
				undefined4 m_unk0x024;    // 0x24
				Racer* m_racer;           // 0x28
			};

			// SIZE 0x68
			class CurseAction : public EffectActionBase {
			public:
				void FUN_00452550(
					Racer* p_racer,
					GolAnimatedEntity* p_unk0x08,
					GolAnimatedEntity* p_unk0x0c,
					GolAnimatedEntity* p_unk0x10,
					ActionTarget* p_unk0x14
				);

				Field0x008* m_owner;              // 0x2c
				GolAnimatedEntity* m_unk0x030;    // 0x30
				GolAnimatedEntity* m_unk0x034;    // 0x34
				GolAnimatedEntity* m_unk0x038;    // 0x38
				GolWorldEntity m_unk0x03c;        // 0x3c
				SpatialSoundInstance* m_unk0x064; // 0x64
			};

			// SIZE 0x34
			class TurboAction : public ActionBase {
			public:
				void FUN_0045c8f0(Racer* p_racer, LegoU32 p_unk0x08);

				Racer* m_racer;                  // 0x18
				Field0x008* m_owner;             // 0x1c
				GolAnimatedEntity* m_unk0x020;   // 0x20
				GolAnimatedEntity* m_unk0x024;   // 0x24
				GolAnimatedEntity* m_unk0x028;   // 0x28
				undefined4* m_unk0x02c;          // 0x2c
				CutsceneParticleRef* m_unk0x030; // 0x30
			};

			// SIZE 0xe4
			class WarpAction : public ActionBase {
			public:
				LegoU32 FUN_0045d560(Racer* p_racer, GolModelEntity* p_unk0x08, ActionTarget* p_unk0x0c);

				GolModelEntity m_unk0x018; // 0x18
				Racer* m_racer;            // 0xa8
				Field0x008* m_owner;       // 0xac
				LegoFloat m_unk0x0b0;      // 0xb0
				GolVec3 m_unk0x0b4;        // 0xb4
				GolVec3 m_unk0x0c0;        // 0xc0
				GolVec3 m_unk0x0cc;        // 0xcc
				LegoU32 m_unk0x0d8;        // 0xd8
				LegoU32 m_unk0x0dc;        // 0xdc
				LegoU32 m_unk0x0e0;        // 0xe0
			};

		private:
			friend class ActionBase;
			friend class Action;
			friend class MagnetAction;
			friend class MissileAction;
			friend class BarrelAction;
			friend class CannonAction;
			friend class TetherAction;
			friend class LightningAction;
			friend class Field0x1894Action;
			friend class EffectActionBase;
			friend class CurseAction;
			friend class TurboAction;
			friend class WarpAction;

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
			void FUN_0045ac80(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045ace0(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045ad30(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045adf0(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045aeb0(Racer* p_racer, LegoU32 p_unk0x08);
			void FUN_0045af80(Racer* p_racer, LegoU32 p_unk0x08);
			LegoU32 FUN_0045b260(Racer* p_racer, LegoU32 p_unk0x08);
			ActionBase* FUN_0045b2e0(
				LegoU32 p_unk0x04,
				LegoU32 p_unk0x08,
				LegoS32 p_unk0x0c,
				LegoS32 p_unk0x10,
				LegoS32 p_unk0x14
			);
			void FUN_0045b640(Racer* p_racer);
			void FUN_0045b690(Racer* p_racer);
			void FUN_0045b6f0(Racer* p_racer);
			GolAnimatedEntity* FUN_0045b9e0();

			undefined4 m_unk0x000;                    // 0x000
			GolRenderDevice* m_renderDevice;          // 0x004
			GolBillboard::Field0x2c m_unk0x008;       // 0x008
			undefined m_unk0x014[0x018 - 0x014];      // 0x014
			MabMaterialAnimationItem0x8* m_unk0x018;  // 0x018
			LegoU32 m_unk0x01c;                       // 0x01c
			MabMaterialAnimationItem0x18* m_unk0x020; // 0x020
			undefined m_unk0x024[0x050 - 0x024];      // 0x024
			Field0x050* m_unk0x050;                   // 0x050
			undefined m_unk0x054[0x05c - 0x054];      // 0x054
			GolWorldDatabase* m_unk0x05c;             // 0x05c
			undefined m_unk0x060[0x074 - 0x060];      // 0x060
			Field0x00c* m_unk0x074;                   // 0x074
			MagnetAction* m_unk0x078;                 // 0x078
			Field0x1894Action* m_unk0x07c;            // 0x07c
			BarrelAction* m_unk0x080;                 // 0x080
			CurseAction* m_unk0x084;                  // 0x084
			CannonAction* m_unk0x088;                 // 0x088
			TetherAction* m_unk0x08c;                 // 0x08c
			LightningAction* m_unk0x090;              // 0x090
			MissileAction* m_unk0x094;                // 0x094
			Action* m_unk0x098;                       // 0x098
			TurboAction* m_unk0x09c;                  // 0x09c
			WarpAction* m_unk0x0a0;                   // 0x0a0
			GolAnimatedEntity m_unk0x0a4[25];         // 0x0a4
			LegoU32 m_unk0x1878;                      // 0x1878
			LegoU32 m_unk0x187c;                      // 0x187c
			ActionBase* m_unk0x1880;                  // 0x1880
			LegoU8 m_unk0x1884;                       // 0x1884
			undefined m_unk0x1885[0x188c - 0x1885];   // 0x1885
			LegoU8 m_unk0x188c;                       // 0x188c
			LegoU8 m_unk0x188d;                       // 0x188d
			LegoU8 m_unk0x188e;                       // 0x188e
			undefined m_unk0x188f;                    // 0x188f
			MagnetAction* m_unk0x1890;                // 0x1890
			Field0x1894Action* m_unk0x1894;           // 0x1894
			BarrelAction* m_unk0x1898;                // 0x1898
			CurseAction* m_unk0x189c;                 // 0x189c
			CannonAction* m_unk0x18a0;                // 0x18a0
			TetherAction* m_unk0x18a4;                // 0x18a4
			LightningAction* m_unk0x18a8;             // 0x18a8
			MissileAction* m_unk0x18ac;               // 0x18ac
			Action* m_unk0x18b0;                      // 0x18b0
			TurboAction* m_unk0x18b4;                 // 0x18b4
			WarpAction* m_unk0x18b8;                  // 0x18b8
			undefined m_unk0x18bc[0x1998 - 0x18bc];   // 0x18bc
			ActionTarget* m_unk0x1998;                // 0x1998
		};

		// SIZE 0x2a0
		class Field0x00c {
		public:
			// SIZE 0x0c
			class StandingsDeltaEntry {
			public:
				Racer* m_racer;    // 0x00
				LegoS32 m_delta;   // 0x04
				LegoU32 m_isValid; // 0x08
			};

			// SIZE 0x48
			class Entry {
			public:
				// SIZE 0x0c
				class PathPoint {
				public:
					LegoU32 GetType() const;
					LegoU32 GetLength() const;
					GolVec3* GetPosition(GolVec3* p_position) const;
					GolQuat* GetRotation(GolQuat* p_rotation) const;
					LegoFloat GetUnk0x09() const;
					LegoFloat GetUnk0x0a() const;

					LegoS16 m_unk0x00; // 0x00
					LegoS16 m_unk0x02; // 0x02
					LegoS8 m_unk0x04;  // 0x04
					LegoS8 m_unk0x05;  // 0x05
					LegoS8 m_unk0x06;  // 0x06
					LegoS8 m_unk0x07;  // 0x07
					LegoS8 m_unk0x08;  // 0x08
					LegoS8 m_unk0x09;  // 0x09
					LegoS8 m_unk0x0a;  // 0x0a
					LegoU8 m_unk0x0b;  // 0x0b
				};

				LegoS32 m_unk0x000;    // 0x00
				PathPoint* m_unk0x004; // 0x04
				GolVec3 m_unk0x008;    // 0x08
				GolQuat m_unk0x014;    // 0x14
				GolVec3 m_unk0x024;    // 0x24
				GolQuat m_unk0x030;    // 0x30
				LegoS32 m_unk0x040;    // 0x40
				LegoS32 m_unk0x044;    // 0x44
			};

			Entry* FUN_0043d070(Racer* p_racer);
			Racer* FUN_0043c910(
				GolVec3* p_unk0x04,
				GolVec3* p_unk0x08,
				LegoFloat p_unk0x0c,
				LegoFloat p_unk0x10,
				LegoFloat p_unk0x14
			);
			Racer* FUN_0043ca60(
				GolVec3* p_unk0x04,
				GolVec3* p_unk0x08,
				LegoFloat p_unk0x0c,
				LegoFloat p_unk0x10,
				LegoFloat p_unk0x14
			);
			StandingsDeltaEntry* FUN_0043cf30(Racer* p_racer, StandingsDeltaEntry* p_entries);
			Racer* GetRacers() { return m_racers; }
			LegoU32 GetRacerCount() const { return m_racerCount; }

		private:
			undefined m_unk0x000[0x140 - 0x000]; // 0x000
			Racer* m_racers;                     // 0x140
			LegoU32 m_racerCount;                // 0x144
			undefined m_unk0x148[0x190 - 0x148]; // 0x148
			Entry* m_entries;                    // 0x190
			undefined m_unk0x194[0x29c - 0x194]; // 0x194
			LegoU8 m_lapCount;                   // 0x29c
		};

		// SIZE 0x3d0
		class Field0x018 {
		public:
			// SIZE 0x6c4
			class Field0x1dc {
			public:
				// SIZE 0x70
				class Field0x1a4 {
				public:
					GolVec3 m_unk0x000;                 // 0x00
					undefined m_unk0x00c[0x70 - 0x00c]; // 0x0c
				};

				enum {
					c_flags0x6c0Bit1 = 1 << 1,
				};

				undefined m_unk0x000[0x1a4 - 0x000]; // 0x000
				Field0x1a4 m_unk0x1a4[4];            // 0x1a4
				undefined m_unk0x364[0x6c0 - 0x364]; // 0x364
				LegoU32 m_flags0x6c0;                // 0x6c0
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
				c_racerFlags0xd04Bit3 = 1 << 3,
				c_racerFlags0xd04Bit11 = 1 << 11,
				c_slotFlagsBit1 = 1 << 1,
				c_slotFlagsBit2 = 1 << 2,
			};

			void Reset();
			void FUN_0043d9f0();
			void FUN_0043da10();
			void FUN_0043da30();
			void Destroy();
			void FUN_0043db60();
			void FUN_0043dc00();
			void FUN_0043dcd0();
			void FUN_0043dd50(LegoU32 p_unk0x04, const LegoChar* p_unk0x08);
			void FUN_0043de90(LegoU32 p_unk0x04);
			void FUN_0043def0();
			void FUN_0043df90();
			void FUN_0043e070(LegoU32 p_elapsedMs);
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
			void FUN_004401b0();
			void FUN_004401e0();

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
			undefined m_unk0x1a0[0x1a8 - 0x1a0];                          // 0x1a0
			GolVec3 m_unk0x1a8[4];                                        // 0x1a8
			Racer* m_racer;                                               // 0x1d8
			Field0x1dc* m_unk0x1dc;                                       // 0x1dc
			RaceSessionField0x27d4* m_unk0x1e0;                           // 0x1e0
			RaceSessionField0x27d4::Item* m_unk0x1e4[4];                  // 0x1e4
			LegoU8 m_unk0x1f4[4];                                         // 0x1f4
			undefined4 m_unk0x1f8[4];                                     // 0x1f8
			undefined4 m_unk0x208[4];                                     // 0x208
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
			GolModelEntity m_unk0x284;                                    // 0x284
			undefined m_unk0x314[0x378 - 0x314];                          // 0x314
			undefined4 m_unk0x378;                                        // 0x378
			undefined4 m_unk0x37c;                                        // 0x37c
			undefined4 m_unk0x380;                                        // 0x380
			undefined4 m_unk0x384;                                        // 0x384
			undefined4 m_unk0x388;                                        // 0x388
			undefined4 m_unk0x38c;                                        // 0x38c
			undefined4 m_unk0x390;                                        // 0x390
			undefined4 m_unk0x394;                                        // 0x394
			undefined4 m_unk0x398;                                        // 0x398
			LegoFloat m_unk0x39c;                                         // 0x39c
			ColorTransform0x20 m_unk0x3a0;                                // 0x3a0
			LegoU32 m_unk0x3c0;                                           // 0x3c0
			LegoU32 m_unk0x3c4;                                           // 0x3c4
			undefined4 m_unk0x3c8;                                        // 0x3c8
			undefined4 m_unk0x3cc;                                        // 0x3cc
		};

		// SIZE 0x888
		class Field0x3e8 {
		public:
			// SIZE 0x4c
			class Field0x13c {
			public:
				virtual void VTable0x00() = 0;                                       // vtable+0x00
				virtual void VTable0x04(GolVec3* p_unk0x04) = 0;                     // vtable+0x04
				virtual void VTable0x08(GolVec3* p_unk0x04) = 0;                     // vtable+0x08
				virtual void VTable0x0c() = 0;                                       // vtable+0x0c
				virtual void VTable0x10() = 0;                                       // vtable+0x10
				virtual void VTable0x14() = 0;                                       // vtable+0x14
				virtual void VTable0x18() = 0;                                       // vtable+0x18
				virtual void VTable0x1c() = 0;                                       // vtable+0x1c
				virtual void VTable0x20() = 0;                                       // vtable+0x20
				virtual void VTable0x24() = 0;                                       // vtable+0x24
				virtual void VTable0x28() = 0;                                       // vtable+0x28
				virtual void VTable0x2c(GolVec3* p_unk0x04, GolVec3* p_unk0x08) = 0; // vtable+0x2c

				void CopyOrientationTo(GolMatrix3* p_orientation) const
				{
					p_orientation->m_m[0][0] = m_unk0x28.m_m[0][0];
					p_orientation->m_m[0][1] = m_unk0x28.m_m[0][1];
					p_orientation->m_m[0][2] = m_unk0x28.m_m[0][2];
					p_orientation->m_m[1][0] = m_unk0x28.m_m[1][0];
					p_orientation->m_m[1][1] = m_unk0x28.m_m[1][1];
					p_orientation->m_m[1][2] = m_unk0x28.m_m[1][2];
					p_orientation->m_m[2][0] = m_unk0x28.m_m[2][0];
					p_orientation->m_m[2][1] = m_unk0x28.m_m[2][1];
					p_orientation->m_m[2][2] = m_unk0x28.m_m[2][2];
				}

			private:
				friend class Racer;
				friend class Field0x3e8;

				undefined m_unk0x004[0x28 - 0x004]; // 0x004
				GolMatrix3 m_unk0x28;               // 0x28
			};

			// SIZE 0x78
			class Field0x74c {
			public:
				void FUN_004a5200(Field0x00c::Entry* p_unk0x04);
				void Destroy();
				void Reset();

				GolVec3 m_unk0x00;            // 0x00
				GolQuat m_unk0x0c;            // 0x0c
				LegoU32 m_unk0x1c;            // 0x1c
				LegoFloat m_unk0x20;          // 0x20
				LegoFloat m_unk0x24;          // 0x24
				Field0x00c::Entry* m_unk0x28; // 0x28
				LegoFloat m_unk0x2c;          // 0x2c
				LegoFloat m_unk0x30;          // 0x30
				LegoS32 m_unk0x34;            // 0x34
				LegoS32 m_unk0x38;            // 0x38
				GolVec3 m_unk0x3c;            // 0x3c
				GolVec3 m_unk0x48;            // 0x48
				GolQuat m_unk0x54;            // 0x54
				GolQuat m_unk0x64;            // 0x64
				LegoS32 m_unk0x74;            // 0x74
			};

			// SIZE 0x70
			class Field0x198 {
			public:
				undefined m_unk0x000[0x00c - 0x000]; // 0x00
				GolVec3 m_unk0x00c;                  // 0x0c
				undefined m_unk0x018[0x070 - 0x018]; // 0x18
			};

			virtual void VTable0x00();                    // vtable+0x00
			virtual void VTable0x04(LegoU32 p_elapsedMs); // vtable+0x04
			virtual void VTable0x08();                    // vtable+0x08
			virtual void VTable0x0c();                    // vtable+0x0c
			virtual void VTable0x10();                    // vtable+0x10
			virtual void VTable0x14();                    // vtable+0x14
			virtual void VTable0x18(LegoFloat p_unk0x04); // vtable+0x18
			virtual void VTable0x1c();                    // vtable+0x1c
			virtual void VTable0x20();                    // vtable+0x20
			virtual void VTable0x24();                    // vtable+0x24
			virtual void VTable0x28();                    // vtable+0x28
			virtual void VTable0x2c();                    // vtable+0x2c
			virtual void VTable0x30();                    // vtable+0x30
			virtual void VTable0x34();                    // vtable+0x34
			virtual void VTable0x38();                    // vtable+0x38
			virtual void VTable0x3c();                    // vtable+0x3c

			void FUN_00429210(
				Racer* p_racer,
				RaceEventTable0x90* p_unk0x08,
				undefined4 p_unk0x0c,
				GolAnimatedEntity* p_unk0x10,
				LegoS32 p_unk0x14,
				undefined4 p_unk0x18,
				Field0x004* p_unk0x1c,
				LegoFloat p_unk0x20,
				LegoFloat p_unk0x24,
				LegoFloat p_unk0x28,
				LegoFloat p_unk0x2c
			);
			void FUN_00429330();
			void FUN_004293c0();
			void Destroy();
			void Reset();
			void FUN_00429af0();
			void FUN_0042a670(Field0x00c::Entry* p_unk0x04);
			void FUN_0042ad70(LegoS32 p_unk0x04);
			void FUN_0042ada0(LegoS32 p_unk0x04);
			void FUN_0042add0(LegoS32 p_unk0x04);
			void FUN_0042b060();
			void FUN_00440970();
			void FUN_004409f0(GolOrientedEntity* p_unk0x04, LegoFloat p_unk0x08);
			void FUN_00440a50();
			void FUN_00440a60();
			void FUN_00441190(GolVec3* p_unk0x04);
			void FUN_00441210(
				GolOrientedEntity* p_unk0x04,
				LegoFloat p_unk0x08,
				LegoFloat p_unk0x0c,
				LegoFloat p_unk0x10,
				LegoFloat p_unk0x14
			);
			void FUN_00444b40();
			void FUN_00444d90(
				GolAnimatedEntity* p_unk0x04,
				LegoS32 p_unk0x08,
				undefined4 p_unk0x0c,
				Field0x004* p_unk0x10,
				LegoFloat p_unk0x14,
				LegoFloat p_unk0x18,
				LegoFloat p_unk0x1c,
				LegoFloat p_unk0x20
			);
			void FUN_00444e90();
			void FUN_00446e60(GolVec3* p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c);
			void FUN_00446ea0(LegoU32 p_unk0x04, GolVec3* p_unk0x08);
			void FUN_00448930(LegoS32 p_unk0x04);
			void FUN_00448c70();

			enum {
				c_unk0x140Count = 5,
				c_flags0x6c0Bit1 = 1 << 1,
				c_flags0x6c0Bit3 = 1 << 3,
				c_flags0x6c0Bit16 = 1 << 16,
				c_flags0x6c0Bit17 = 1 << 17,
				c_flags0x6c0Bit18 = 1 << 18,
				c_flags0x6c0Bit19 = 1 << 19,
				c_flags0x6c0Bit20 = 1 << 20,
			};

			GolOrientedEntity* m_unk0x004;             // 0x004
			GolVec3 m_unk0x008;                        // 0x008
			GolVec3 m_unk0x014;                        // 0x014
			GolVec3 m_unk0x020;                        // 0x020
			undefined m_unk0x02c[0x050 - 0x02c];       // 0x02c
			GolMatrix3 m_unk0x050;                     // 0x050
			GolMatrix3 m_unk0x074;                     // 0x074
			undefined4 m_unk0x098[12];                 // 0x098
			LegoFloat m_unk0x0c8;                      // 0x0c8
			LegoFloat m_unk0x0cc;                      // 0x0cc
			LegoFloat m_unk0x0d0;                      // 0x0d0
			LegoFloat m_unk0x0d4;                      // 0x0d4
			LegoFloat m_unk0x0d8;                      // 0x0d8
			LegoFloat m_unk0x0dc;                      // 0x0dc
			Racer* m_racer;                            // 0x0e0
			GolOrientedEntity m_unk0x0e4;              // 0x0e4
			GolOrientedEntity* m_unk0x13c;             // 0x13c
			LegoS32 m_unk0x140[c_unk0x140Count];       // 0x140
			LegoU32 m_unk0x154;                        // 0x154
			Field0x004* m_unk0x158;                    // 0x158
			LegoFloat m_unk0x15c;                      // 0x15c
			LegoFloat m_unk0x160;                      // 0x160
			undefined4 m_unk0x164;                     // 0x164
			GolVec3 m_unk0x168;                        // 0x168
			undefined4 m_unk0x174;                     // 0x174
			undefined4 m_unk0x178;                     // 0x178
			undefined4 m_unk0x17c;                     // 0x17c
			undefined4 m_unk0x180;                     // 0x180
			undefined4 m_unk0x184;                     // 0x184
			undefined4 m_unk0x188;                     // 0x188
			undefined4 m_unk0x18c;                     // 0x18c
			undefined4 m_unk0x190;                     // 0x190
			LegoFloat m_unk0x194;                      // 0x194
			Field0x198 m_unk0x198[4];                  // 0x198
			GolVec3 m_unk0x358;                        // 0x358
			LegoFloat m_unk0x364;                      // 0x364
			LegoFloat m_unk0x368;                      // 0x368
			undefined4 m_unk0x36c;                     // 0x36c
			GolVec3 m_unk0x370[4];                     // 0x370
			GolVec3 m_unk0x3a0[4];                     // 0x3a0
			undefined4 m_unk0x3d0[4];                  // 0x3d0
			undefined m_unk0x3e0[0x3ec - 0x3e0];       // 0x3e0
			undefined4 m_unk0x3ec;                     // 0x3ec
			undefined4 m_unk0x3f0;                     // 0x3f0
			undefined4 m_unk0x3f4[0x78];               // 0x3f4
			undefined4 m_unk0x5d4;                     // 0x5d4
			undefined4 m_unk0x5d8;                     // 0x5d8
			undefined4 m_unk0x5dc;                     // 0x5dc
			undefined4 m_unk0x5e0;                     // 0x5e0
			undefined4 m_unk0x5e4;                     // 0x5e4
			undefined4 m_unk0x5e8;                     // 0x5e8
			undefined m_unk0x5ec[0x5f0 - 0x5ec];       // 0x5ec
			undefined4 m_unk0x5f0;                     // 0x5f0
			LegoFloat m_unk0x5f4;                      // 0x5f4
			LegoFloat m_unk0x5f8;                      // 0x5f8
			undefined4 m_unk0x5fc;                     // 0x5fc
			undefined4 m_unk0x600;                     // 0x600
			LegoFloat m_unk0x604;                      // 0x604
			undefined m_unk0x608[0x60c - 0x608];       // 0x608
			undefined4 m_unk0x60c;                     // 0x60c
			undefined4 m_unk0x610;                     // 0x610
			undefined4 m_unk0x614;                     // 0x614
			LegoFloat m_unk0x618;                      // 0x618
			undefined m_unk0x61c[0x628 - 0x61c];       // 0x61c
			LegoFloat m_unk0x628;                      // 0x628
			undefined4 m_unk0x62c;                     // 0x62c
			undefined4 m_unk0x630;                     // 0x630
			undefined4 m_unk0x634;                     // 0x634
			undefined4 m_unk0x638;                     // 0x638
			undefined4 m_unk0x63c;                     // 0x63c
			undefined4 m_unk0x640;                     // 0x640
			undefined4 m_unk0x644;                     // 0x644
			undefined4 m_unk0x648;                     // 0x648
			LegoFloat m_unk0x64c;                      // 0x64c
			undefined4 m_unk0x650;                     // 0x650
			LegoFloat m_unk0x654;                      // 0x654
			undefined4 m_unk0x658;                     // 0x658
			LegoFloat m_unk0x65c;                      // 0x65c
			LegoFloat m_unk0x660;                      // 0x660
			undefined m_unk0x664[0x67c - 0x664];       // 0x664
			LegoU32 m_unk0x67c;                        // 0x67c
			undefined4 m_unk0x680;                     // 0x680
			undefined m_unk0x684[0x690 - 0x684];       // 0x684
			undefined4 m_unk0x690;                     // 0x690
			undefined4 m_unk0x694;                     // 0x694
			undefined4 m_unk0x698;                     // 0x698
			undefined m_unk0x69c[0x6c0 - 0x69c];       // 0x69c
			LegoU32 m_flags0x6c0;                      // 0x6c0
			LegoFloat m_unk0x6c4;                      // 0x6c4
			LegoFloat m_unk0x6c8;                      // 0x6c8
			LegoFloat m_unk0x6cc;                      // 0x6cc
			undefined4 m_unk0x6d0;                     // 0x6d0
			undefined4 m_unk0x6d4;                     // 0x6d4
			LegoU32 m_unk0x6d8;                        // 0x6d8
			undefined4 m_unk0x6dc;                     // 0x6dc
			undefined4 m_unk0x6e0;                     // 0x6e0
			RaceResourceManager::Resource* m_unk0x6e4; // 0x6e4
			RaceResourceManager::Resource* m_unk0x6e8; // 0x6e8
			LegoU32 m_unk0x6ec;                        // 0x6ec
			Racer* m_unk0x6f0;                         // 0x6f0
			RaceEventTable0x90* m_unk0x6f4;            // 0x6f4
			undefined4 m_unk0x6f8;                     // 0x6f8
			undefined4 m_unk0x6fc;                     // 0x6fc
			GolVec3 m_unk0x700;                        // 0x700
			GolQuat m_unk0x70c;                        // 0x70c
			LegoS32 m_unk0x71c;                        // 0x71c
			LegoS32 m_unk0x720;                        // 0x720
			LegoS32 m_unk0x724;                        // 0x724
			LegoFloat m_unk0x728;                      // 0x728
			LegoFloat m_unk0x72c;                      // 0x72c
			LegoFloat m_unk0x730;                      // 0x730
			LegoFloat m_unk0x734;                      // 0x734
			undefined4 m_unk0x738;                     // 0x738
			LegoS32 m_unk0x73c;                        // 0x73c
			union {
				SpatialSoundInstance* m_unk0x740;               // 0x740
				RaceResourceManager::Resource* m_soundResource; // 0x740
			};
			LegoU32 m_unk0x744;                  // 0x744
			LegoU32 m_unk0x748;                  // 0x748
			Field0x74c m_unk0x74c;               // 0x74c
			GolQuat m_unk0x7c4;                  // 0x7c4
			undefined4 m_unk0x7d4;               // 0x7d4
			undefined4 m_unk0x7d8;               // 0x7d8
			undefined4 m_unk0x7dc;               // 0x7dc
			undefined4 m_unk0x7e0;               // 0x7e0
			undefined4 m_unk0x7e4;               // 0x7e4
			LegoFloat m_unk0x7e8;                // 0x7e8
			LegoFloat m_unk0x7ec;                // 0x7ec
			Field0x74c m_unk0x7f0;               // 0x7f0
			undefined m_unk0x868[0x888 - 0x868]; // 0x868
		};

		// SIZE 0x68
		class Field0xd5c {
		public:
			// SIZE 0x6c
			class Field0x04 {
			public:
				undefined m_unk0x00[0x68 - 0x00];  // 0x00
				RaceSessionField0x32b4* m_unk0x68; // 0x68
			};

			// SIZE 0x04
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
			undefined m_unk0x00[0x04 - 0x00]; // 0x00
			Field0x04* m_unk0x04;             // 0x04
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

		typedef RaceEventTable0x90 Field0xadc;

		// SIZE 0x30
		class Field0xd8c : public RaceResourceManager::Resource {
		public:
			undefined m_unk0x004[0x018 - 0x004]; // 0x004
			GolVec3 m_unk0x018;                  // 0x018
			GolVec3 m_unk0x024;                  // 0x024
		};

		// SIZE 0x54
		class Field0xc70 {
		public:
			enum {
				c_flags0x014Bit0 = 1 << 0,
				c_flags0x014Bit1 = 1 << 1,
				c_flags0x014Bit2 = 1 << 2,
				c_flags0x014Bit3 = 1 << 3,
				c_flags0x014Bit4 = 1 << 4,
				c_flags0x014Bit5 = 1 << 5,
				c_flags0x014Bit6 = 1 << 6,
				c_flags0x014Bit7 = 1 << 7,
				c_flags0x014Bit8 = 1 << 8,
			};

			// SIZE 0x78
			class Field0x050 {
			public:
				Field0x050();
				~Field0x050();
				void FUN_004a5220(Field0x00c::Entry* p_unk0x04);
				void FUN_004a5320(LegoFloat p_unk0x04);
				void FUN_004a5750(GolVec3* p_unk0x04);

				GolVec3 m_unk0x00;            // 0x00
				GolQuat m_unk0x0c;            // 0x0c
				LegoU32 m_unk0x1c;            // 0x1c
				LegoFloat m_unk0x20;          // 0x20
				LegoFloat m_unk0x24;          // 0x24
				Field0x00c::Entry* m_unk0x28; // 0x28
				LegoFloat m_unk0x2c;          // 0x2c
				LegoFloat m_unk0x30;          // 0x30
				LegoS32 m_unk0x34;            // 0x34
				LegoS32 m_unk0x38;            // 0x38
				GolVec3 m_unk0x3c;            // 0x3c
				GolVec3 m_unk0x48;            // 0x48
				GolQuat m_unk0x54;            // 0x54
				GolQuat m_unk0x64;            // 0x64
				LegoS32 m_unk0x74;            // 0x74

			private:
				void Reset();
				void Destroy();
			};

			// SIZE 0x868
			class Field0x000 {
			public:
				// SIZE 0x4c
				class Field0x13c {
				public:
					virtual void VTable0x00() = 0;                                       // vtable+0x00
					virtual void VTable0x04(GolVec3* p_unk0x04) = 0;                     // vtable+0x04
					virtual void VTable0x08(GolVec3* p_unk0x04) = 0;                     // vtable+0x08
					virtual void VTable0x0c() = 0;                                       // vtable+0x0c
					virtual void VTable0x10() = 0;                                       // vtable+0x10
					virtual void VTable0x14() = 0;                                       // vtable+0x14
					virtual void VTable0x18() = 0;                                       // vtable+0x18
					virtual void VTable0x1c() = 0;                                       // vtable+0x1c
					virtual void VTable0x20() = 0;                                       // vtable+0x20
					virtual void VTable0x24() = 0;                                       // vtable+0x24
					virtual void VTable0x28() = 0;                                       // vtable+0x28
					virtual void VTable0x2c(GolVec3* p_unk0x04, GolVec3* p_unk0x08) = 0; // vtable+0x2c

				private:
					friend class Field0x000;
					friend class Field0xc70;

					undefined m_unk0x004[0x28 - 0x004]; // 0x004
					GolMatrix3 m_unk0x28;               // 0x28
				};

				// SIZE 0x70
				class Field0x198 {
				public:
					enum {
						c_flags0x48Bit0 = 1 << 0,
					};

					undefined m_unk0x00[0x48];        // 0x00
					LegoU8 m_flags0x48;               // 0x48
					undefined m_unk0x49[0x5c - 0x49]; // 0x49
					LegoFloat m_unk0x5c;              // 0x5c
					undefined m_unk0x60[0x70 - 0x60]; // 0x60
				};

				virtual void VTable0x00() = 0;                    // vtable+0x00
				virtual void VTable0x04() = 0;                    // vtable+0x04
				virtual void VTable0x08() = 0;                    // vtable+0x08
				virtual void VTable0x0c() = 0;                    // vtable+0x0c
				virtual void VTable0x10() = 0;                    // vtable+0x10
				virtual void VTable0x14(LegoFloat p_unk0x04) = 0; // vtable+0x14

				void FUN_0042a730(Field0x00c::Entry* p_unk0x04);
				LegoFloat FUN_0042ae10();
				LegoBool32 FUN_0042ae20();
				LegoBool32 FUN_0042aea0(LegoFloat p_unk0x04);
				SpatialSoundInstance* FUN_0042af90(LegoU32 p_unk0x04);
				void FUN_0042b060();
				void FUN_0042b0c0();
				LegoFloat FUN_00445cb0();
				void FUN_00446ef0(LegoFloat p_unk0x04);
				void FUN_00447f30(LegoFloat p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c);
				void FUN_00448070();
				undefined4 FUN_00449070(undefined4 p_unk0x04);
				undefined4 FUN_00449090();

			private:
				friend class Field0xc70;

				enum {
					c_flags0x6c0Bit0 = 1 << 0,
					c_flags0x6c0Bit1 = 1 << 1,
					c_flags0x6c0Bit3 = 1 << 3,
					c_flags0x6c0Bit9 = 1 << 9,
					c_flags0x6c0Bit10 = 1 << 10,
				};

				LegoFloat FUN_004489f0();

				undefined m_unk0x004[0x008 - 0x004]; // 0x004
				GolVec3 m_unk0x008;                  // 0x008
				GolVec3 m_unk0x014;                  // 0x014
				GolVec3 m_unk0x020;                  // 0x020
				undefined m_unk0x02c[0x0c8 - 0x02c]; // 0x02c
				LegoFloat m_unk0x0c8;                // 0x0c8
				undefined m_unk0x0cc[0x10c - 0x0cc]; // 0x0cc
				GolVec3 m_unk0x10c;                  // 0x10c
				undefined m_unk0x118[0x13c - 0x118]; // 0x118
				Field0x13c* m_unk0x13c;              // 0x13c
				undefined m_unk0x140[0x158 - 0x140]; // 0x140
				Field0x004* m_unk0x158;              // 0x158
				LegoFloat m_unk0x15c;                // 0x15c
				LegoFloat m_unk0x160;                // 0x160
				undefined m_unk0x164[0x168 - 0x164]; // 0x164
				GolVec3 m_unk0x168;                  // 0x168
				undefined m_unk0x174[0x198 - 0x174]; // 0x174
				Field0x198 m_unk0x198[4];            // 0x198
				undefined m_unk0x358[0x36c - 0x358]; // 0x358
				LegoU32 m_unk0x36c;                  // 0x36c
				GolVec3 m_unk0x370[4];               // 0x370
				GolVec3 m_unk0x3a0[4];               // 0x3a0
				undefined m_unk0x3d0[0x3ec - 0x3d0]; // 0x3d0
				LegoU32 m_unk0x3ec;                  // 0x3ec
				undefined m_unk0x3f0[0x5f4 - 0x3f0]; // 0x3f0
				LegoFloat m_unk0x5f4;                // 0x5f4
				GolVec3 m_unk0x5f8;                  // 0x5f8
				LegoFloat m_unk0x604;                // 0x604
				undefined m_unk0x608[0x618 - 0x608]; // 0x608
				LegoFloat m_unk0x618;                // 0x618
				undefined m_unk0x61c[0x64c - 0x61c]; // 0x61c
				LegoFloat m_unk0x64c;                // 0x64c
				undefined m_unk0x650[0x6c0 - 0x650]; // 0x650
				LegoU32 m_flags0x6c0;                // 0x6c0
				LegoFloat m_unk0x6c4;                // 0x6c4
				LegoFloat m_unk0x6c8;                // 0x6c8
				LegoFloat m_unk0x6cc;                // 0x6cc
				LegoFloat m_unk0x6d0;                // 0x6d0
				undefined4 m_unk0x6d4;               // 0x6d4
				LegoU32 m_unk0x6d8;                  // 0x6d8
				undefined m_unk0x6dc[0x6e8 - 0x6dc]; // 0x6dc
				union {
					SpatialSoundInstance* m_unk0x6e8;          // 0x6e8
					RaceResourceManager::Resource* m_resource; // 0x6e8
				};
				LegoU32 m_unk0x6ec;                  // 0x6ec
				undefined m_unk0x6f0[0x738 - 0x6f0]; // 0x6f0
				LegoU32 m_unk0x738;                  // 0x738
				LegoU32 m_unk0x73c;                  // 0x73c
				union {
					SpatialSoundInstance* m_unk0x740;               // 0x740
					RaceResourceManager::Resource* m_soundResource; // 0x740
				};
				LegoU32 m_unk0x744;                  // 0x744
				undefined m_unk0x748[0x74c - 0x748]; // 0x748
				Field0x050 m_unk0x74c;               // 0x74c
				GolQuat m_unk0x7c4;                  // 0x7c4
				undefined m_unk0x7d4[0x7e8 - 0x7d4]; // 0x7d4
				LegoFloat m_unk0x7e8;                // 0x7e8
				LegoFloat m_unk0x7ec;                // 0x7ec
				Field0x050 m_unk0x7f0;               // 0x7f0
			};

			void FUN_0041fbd0(Field0x3e8* p_unk0x04);
			void FUN_0041fc00(LegoU32 p_elapsedMs);
			void FUN_0041fd60(LegoU32 p_elapsedMs);
			void FUN_0041fdb0(LegoU32 p_elapsedMs);
			void FUN_0041fee0();
			void FUN_00420130(LegoFloat p_unk0x04);
			void FUN_004201e0();
			undefined4 FUN_00420260(LegoBool32 p_unk0x04);
			undefined4 FUN_004202c0();
			GolQuat* FUN_004202f0(Field0x00c::Entry* p_unk0x04);
			void FUN_00420380();
			void FUN_004203b0(LegoU32 p_elapsedMs);
			void Destroy();
			void Reset();

			union {
				Field0x000* m_unk0x000;   // 0x00
				Field0x3e8* m_field0x000; // 0x00
			};
			Field0x00c::Entry* m_unk0x004; // 0x04
			LegoFloat m_unk0x008;          // 0x08
			LegoFloat m_unk0x00c;          // 0x0c
			LegoFloat m_unk0x010;          // 0x10
			LegoU32 m_unk0x014;            // 0x14
			LegoFloat m_unk0x018;          // 0x18
			LegoFloat m_unk0x01c;          // 0x1c
			LegoU32 m_unk0x020;            // 0x20
			LegoS32 m_unk0x024;            // 0x24
			LegoU32 m_unk0x028;            // 0x28
			LegoU32 m_unk0x02c;            // 0x2c
			LegoU32 m_unk0x030;            // 0x30
			GolVec3 m_unk0x034;            // 0x34
			GolQuat m_unk0x040;            // 0x40
			Field0x050* m_unk0x050;        // 0x50
		};

		enum {
			c_flags0xd04Bit21 = 0x00200000,
		};

		void FUN_00439100();
		LegoU32 FUN_00439210(LegoU32 p_unk0x04);
		void FUN_00439340();
		void FUN_004393d0();
		void FUN_004371c0(Field0x371c0* p_unk0x04, Field0x371c0Vehicle* p_unk0x08);
		void FUN_004374c0();
		void FUN_00437740(LegoU32 p_elapsedMs);
		void FUN_004377f0(LegoU32 p_elapsedMs);
		void FUN_00437b50();
		void FUN_00437be0();
		void FUN_00437d40(LegoU32 p_elapsedMs);
		void FUN_00438500();
		LegoU32 FUN_00439520();
		void FUN_004395a0();
		void FUN_00439660();
		void FUN_00439730();
		void FUN_00439790();
		void FUN_004397b0();
		void FUN_004397c0(LegoBool32 p_unk0x04);
		LegoFloat FUN_0043a0a0();
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
		Field0x00c::StandingsDeltaEntry* FUN_00439c70(Field0x00c::StandingsDeltaEntry* p_entries);
		void FUN_0043a3e0();
		void FUN_0043a3f0();
		void FUN_0043a400();

	private:
		friend class RaceState;
		friend class Field0x008::ActionBase;
		friend class Field0x008::Action;
		friend class Field0x008::EffectActionBase;
		friend class Field0x008::CurseAction;
		friend class Field0x008::TurboAction;
		friend class Field0x008::WarpAction;

		void Destroy();
		void Reset();

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
			c_flags0xd04Bit13 = 1 << 13,
			c_flags0xd04Bit14 = 1 << 14,
			c_flags0xd04Bit15 = 1 << 15,
			c_flags0xd04Bit16 = 1 << 16,
			c_flags0xd04Bit17 = 1 << 17,
			c_flags0xd04Bit20 = 0x00100000,
			c_flags0xd04Bit22 = 0x00400000,
			c_flags0xd04Bit24 = 0x01000000,
			c_flags0xd04Bit25 = 0x02000000,
			c_flags0xd04Bit26 = 0x04000000,
			c_flags0xd04Bit27 = 0x08000000,
			c_flags0xd04Bit28 = 0x10000000,
			c_flags0xd04Bit29 = 0x20000000,
			c_flags0xaa8Bit1 = 1 << 1,
			c_flags0xaa8Bit3 = 1 << 3,
			c_flags0xaa8Bit7 = 1 << 7,
			c_flags0xaa8Bit12 = 1 << 12,
			c_flags0xaa8Bit18 = 0x00040000,
			c_randomTableMask = 0x3ff,
			c_volumeTableMask = 0x3ff,
			c_volumeTableBase = 0xffffff00,
			c_boostSoundElapsedThreshold = 50,
			c_feedbackVariantCount = 6,
			c_feedbackHighOffset = 6,
		};

		void FUN_00439240(LegoBool32 p_unk0x04);
		LegoBool32 FUN_00439420(Field0xd5c* p_unk0x04);
		Field0xd5c* FUN_00439490();
		void FUN_00438f20();
		void FUN_00439c90();
		void FUN_00439cf0(LegoU32 p_elapsedMs);
		void FUN_00439ea0(LegoU32 p_elapsedMs);

	public:
		class Field0xcc4;

		// SIZE 0x04
		class Field0x010 {
		public:
			Field0xcc4* FUN_0041e940(LegoU32 p_unk0x04);

		private:
			Field0xcc4* m_entries; // 0x00
		};

		// SIZE 0x28
		class Field0x014 {
		public:
			void FUN_00422100();

		private:
			undefined4* m_unk0x00; // 0x00
			LegoU32 m_unk0x04;     // 0x04
			LegoU32 m_unk0x08;     // 0x08
			LegoS32 m_unk0x0c;     // 0x0c
			LegoU32 m_unk0x10;     // 0x10
			LegoFloat m_unk0x14;   // 0x14
			LegoU32 m_unk0x18;     // 0x18
			LegoU32 m_unk0x1c;     // 0x1c
			LegoU32 m_unk0x20;     // 0x20
			undefined4* m_unk0x24; // 0x24
		};

		// SIZE 0x24
		class Field0xcc4 {
		public:
			GolVec3 m_unk0x00;                // 0x00
			LegoFloat m_unk0x0c;              // 0x0c
			undefined m_unk0x10[0x1c - 0x10]; // 0x10
			LegoFloat m_unk0x1c;              // 0x1c
			LegoU8 m_unk0x20[4];              // 0x20
		};

		union {
			Field0x004* m_unk0x004;                    // 0x004
			RaceResourceManager* m_resourceManager004; // 0x004
		};
		Field0x008* m_unk0x008;              // 0x008
		Field0x00c* m_unk0x00c;              // 0x00c
		Field0x010* m_unk0x010;              // 0x010
		Field0x014* m_unk0x014;              // 0x014
		Field0x018 m_unk0x018;               // 0x018
		Field0x3e8 m_unk0x3e8;               // 0x3e8
		Field0xc70 m_unk0xc70;               // 0xc70
		Field0xcc4* m_unk0xcc4;              // 0xcc4
		undefined4 m_unk0xcc8;               // 0xcc8
		LegoU32 m_unk0xccc;                  // 0xccc
		LegoU32 m_unk0xcd0;                  // 0xcd0
		LegoU32 m_unk0xcd4;                  // 0xcd4
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
		LegoS32 m_unk0xd18;                  // 0xd18
		LegoU8 m_unk0xd1c;                   // 0xd1c
		LegoU8 m_unk0xd1d;                   // 0xd1d
		LegoU8 m_unk0xd1e;                   // 0xd1e
		LegoU8 m_unk0xd1f;                   // 0xd1f
		LegoU8 m_unk0xd20;                   // 0xd20
		LegoU8 m_unk0xd21;                   // 0xd21
		LegoU8 m_unk0xd22;                   // 0xd22
		LegoU8 m_unk0xd23;                   // 0xd23
		LegoU32 m_unk0xd24;                  // 0xd24
		LegoFloat m_unk0xd28;                // 0xd28
		LegoFloat m_unk0xd2c;                // 0xd2c
		LegoFloat m_unk0xd30;                // 0xd30
		undefined4 m_unk0xd34;               // 0xd34
		undefined4 m_unk0xd38;               // 0xd38
		undefined4 m_unk0xd3c;               // 0xd3c
		LegoU32 m_unk0xd40;                  // 0xd40
		LegoU32 m_unk0xd44;                  // 0xd44
		undefined4 m_unk0xd48;               // 0xd48
		undefined4 m_unk0xd4c;               // 0xd4c
		LegoU32 m_unk0xd50;                  // 0xd50
		LegoFloat m_unk0xd54;                // 0xd54
		LegoU32 m_unk0xd58;                  // 0xd58
		Field0xd5c* m_unk0xd5c[3];           // 0xd5c
		LegoU32 m_unk0xd68;                  // 0xd68
		LegoU32 m_unk0xd6c;                  // 0xd6c
		undefined4 m_unk0xd70;               // 0xd70
		undefined4 m_unk0xd74;               // 0xd74
		LegoU32 m_unk0xd78;                  // 0xd78
		undefined4 m_unk0xd7c;               // 0xd7c
		undefined m_unk0xd80[0xd84 - 0xd80]; // 0xd80
		LegoU32 m_unk0xd84;                  // 0xd84
		LegoU32 m_unk0xd88;                  // 0xd88
		Field0xd8c* m_unk0xd8c;              // 0xd8c
		Field0xd8c* m_unk0xd90;              // 0xd90
		Field0xd8c* m_unk0xd94;              // 0xd94
		Field0xd8c* m_unk0xd98;              // 0xd98
		union {
			SpatialSoundInstance* m_unk0xd9c;          // 0xd9c
			RaceResourceManager::Resource* m_soundD9c; // 0xd9c
		};
		union {
			SpatialSoundInstance* m_unk0xda0;          // 0xda0
			RaceResourceManager::Resource* m_soundDa0; // 0xda0
		};
		union {
			SpatialSoundInstance* m_unk0xda4;          // 0xda4
			RaceResourceManager::Resource* m_soundDa4; // 0xda4
		};
		union {
			SpatialSoundInstance* m_unk0xda8;          // 0xda8
			RaceResourceManager::Resource* m_soundDa8; // 0xda8
		};
		Field0xd8c* m_unk0xdac;              // 0xdac
		undefined4 m_unk0xdb0;               // 0xdb0
		RaceCameraController* m_unk0xdb4;    // 0xdb4
		LegoU32 m_unk0xdb8;                  // 0xdb8
		LegoU16 m_unk0xdbc;                  // 0xdbc
		undefined m_unk0xdbe[0xdec - 0xdbe]; // 0xdbe
		GolString m_displayName;             // 0xdec
		GolVec3 m_unk0xdf8;                  // 0xdf8
		LegoU32 m_unk0xe04;                  // 0xe04
		GolVec3 m_unk0xe08;                  // 0xe08
		GolVec3 m_unk0xe14;                  // 0xe14
		GolVec3 m_unk0xe20;                  // 0xe20
		Field0x00c::Entry* m_unk0xe2c;       // 0xe2c
		CobaltTrail0x140* m_unk0xe30;        // 0xe30
	};

	// SIZE 0x0c
	class RacerProgressEntry {
	public:
		Racer* m_racer;      // 0x00
		LegoFloat m_unk0x04; // 0x04
		LegoFloat m_unk0x08; // 0x08
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

		// SIZE 0x28
		class Field0x064 {
		public:
			undefined m_unk0x00[0x24 - 0x00]; // 0x00
			undefined4 m_unk0x24;             // 0x24
		};

		class Field0x080 {
		public:
			virtual void VTable0x00() = 0;                      // vtable+0x00
			virtual void VTable0x04() = 0;                      // vtable+0x04
			virtual void VTable0x08() = 0;                      // vtable+0x08
			virtual void VTable0x0c() = 0;                      // vtable+0x0c
			virtual void VTable0x10() = 0;                      // vtable+0x10
			virtual void VTable0x14() = 0;                      // vtable+0x14
			virtual void VTable0x18() = 0;                      // vtable+0x18
			virtual void VTable0x1c() = 0;                      // vtable+0x1c
			virtual void VTable0x20() = 0;                      // vtable+0x20
			virtual void VTable0x24() = 0;                      // vtable+0x24
			virtual void VTable0x28() = 0;                      // vtable+0x28
			virtual void VTable0x2c() = 0;                      // vtable+0x2c
			virtual void VTable0x30() = 0;                      // vtable+0x30
			virtual void VTable0x34() = 0;                      // vtable+0x34
			virtual void VTable0x38() = 0;                      // vtable+0x38
			virtual void VTable0x3c() = 0;                      // vtable+0x3c
			virtual void VTable0x40(undefined4* p_unk0x04) = 0; // vtable+0x40
			virtual void VTable0x44(undefined4* p_unk0x04) = 0; // vtable+0x44
		};

		void FUN_0043d200();
		void FUN_0043d270();
		void FUN_0043d3f0();

		LegoEventQueue::Event* m_unk0x048; // 0x048
		LegoEventQueue::Event* m_unk0x04c; // 0x04c
		Racer* m_racers;                   // 0x050
		LegoU32 m_racerCount;              // 0x054
		union {
			undefined4 m_unk0x058;           // 0x058
			Racer::Field0x010* m_field0x010; // 0x058
		};
		union {
			RaceResourceManager* m_unk0x05c;  // 0x05c
			Racer::Field0x004* m_soundSource; // 0x05c
		};
		undefined4 m_unk0x060;     // 0x060
		Field0x064* m_unk0x064[6]; // 0x064
		union {
			RaceResourceManager::Resource* m_unk0x07c; // 0x07c
			SpatialSoundInstance* m_sound;             // 0x07c
		};
		union {
			Field0x080* m_unk0x080[3]; // 0x080
			Racer* m_racer080;         // 0x080
		};
		undefined* m_unk0x08c[2]; // 0x08c
		undefined* m_unk0x094[2]; // 0x094
		undefined4 m_unk0x09c;    // 0x09c
		undefined4 m_unk0x0a0;    // 0x0a0
		GolVec3 m_unk0x0a4[6];    // 0x0a4
		GolVec3 m_unk0x0ec[6];    // 0x0ec
		GolVec3 m_unk0x134[6];    // 0x134
		LegoU32 m_unk0x17c[6];    // 0x17c
	};

	// SIZE 0x1c
	class Field0x284 {
	public:
		Field0x284();
		~Field0x284();

	private:
		friend class RaceState;

		enum {
			c_racerFlags0xd04RubberBandMask = 0x20100000,
			c_racerFlags0xaa8Bit18 = 0x00040000,
		};

		void Reset();
		void Destroy();
		LegoU32 FUN_0043a480(LegoU32 p_elapsedMs);

		Racer* m_racers;                  // 0x00
		LegoU32 m_racerCount;             // 0x04
		LegoU32 m_updateDelayMs;          // 0x08
		LegoFloat m_unk0x0c;              // 0x0c
		undefined4* m_unk0x10;            // 0x10
		undefined4* m_unk0x14;            // 0x14
		LegoU8 m_lapCount;                // 0x18
		undefined m_unk0x19[0x1c - 0x19]; // 0x19
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
		c_racerProgressEntryCount = 6,
	};

	static RacerProgressEntry g_racerProgressEntries[c_racerProgressEntryCount];

	void FUN_0043bff0(GolD3DRenderDevice* p_renderer);
	void FUN_0043c030(LegoU32 p_elapsedMs);
	void FUN_0043c1b0();
	void FUN_0043c6a0(GolCamera* p_camera);
	void FUN_0043ccb0();
	void FUN_0043cd30(GolRenderDevice* p_renderer, Racer* p_racer);
	void Reset();
	void Destroy();

	DriverCosmeticTable m_unk0x000;           // 0x000
	ChampionDefinitionList m_unk0x080;        // 0x080
	ChassisModelTable m_unk0x0b4;             // 0x0b4
	Field0x0f0 m_unk0x0f0;                    // 0x0f0
	Field0x284 m_unk0x284;                    // 0x284
	Racer::Field0xc70::Field0x050 m_unk0x2a0; // 0x2a0
	Racer* m_unk0x318[2];                     // 0x318
};

#endif // RACESTATE_H
