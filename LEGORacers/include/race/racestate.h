#ifndef RACESTATE_H
#define RACESTATE_H

#include "app/legoracers.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golboundedentity.h"
#include "golboundingvolume.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golorientedentity.h"
#include "golstring.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "golworldentitygroup0x38.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "material/materialtable0x0c.h"
#include "race/data/championdefinitionlist.h"
#include "race/raceactionsource0x24.h"
#include "race/raceeventrecord.h"
#include "race/raceresourcemanager.h"
#include "race/racesessionfield0x27d4.h"
#include "race/racesessionfield0x27f4.h"
#include "race/racesessionfield0x32b4.h"
#include "racer/chassismodeltable.h"
#include "racer/drivercosmetictable.h"
#include "scene/golbillboard.h"
#include "types.h"
#include "util/legoeventqueue.h"

class GolCamera;
class GolD3DRenderDevice;
class GolExport;
class GolFileParser;
class GolMaterialLibrary;
class GolRenderDevice;
class GolTextureList;
class GolWorldDatabase;
class GolBoundedEntity;
class GolCollidableEntity;
class GolAnimatedEntity;
class MabMaterialAnimationItem0x8;
class DuskwindBananaRelic0x24;
class CutsceneAnimation;
class CobaltTrail0x140;
class RaceCameraController;
class RaceEventTable0x90;
class RaceSessionField0x32b4;
class RaceForceFeedback;
class RacePowerupManager;
class RaceRouteRecord;
class TimeRaceManager;
class SoundGroup;
class SoundManager;
class SpatialSoundInstance;
struct CutsceneParticleRef;
struct SoundVector;

// SIZE 0x320
class RaceState {
	class Field0x3b190Params0x08;

public:
	// VTABLE: LEGORACERS 0x004b0a2c
	// SIZE 0x1fc
	class SpbTxtParser : public GolTxtParser {};

	// VTABLE: LEGORACERS 0x004b09b0
	// SIZE 0xe34
	class Racer : public LegoEventQueue::Callback {
	public:
		Racer();
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual ~Racer();                                               // vtable+0x04

		// SYNTHETIC: LEGORACERS 0x0043b420
		// RaceState::Racer::`vector deleting destructor'

		class Field0x00c;
		class Field0x3e8;

		// Known fields currently reach through 0x2f.
		// SIZE 0x30
		class Field0x371c0 {
		public:
			undefined m_unk0x000[0x00c - 0x000]; // 0x000
			GolBoundedEntity* m_unk0x00c;        // 0x00c
			GolBoundedEntity* m_unk0x010;        // 0x010
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
			void* m_unk0x060;                    // 0x060
			void* m_unk0x064;                    // 0x064
			GolBoundedEntity* m_unk0x068;        // 0x068
			undefined m_unk0x06c[0x084 - 0x06c]; // 0x06c
			LegoU8 m_unk0x084;                   // 0x084
			LegoU8 m_unk0x085;                   // 0x085
			LegoU8 m_unk0x086;                   // 0x086
		};

		// SIZE 0x88
		class Field0x36df0Params {
		public:
			union {
				Field0x371c0Vehicle m_vehicle; // 0x00
				struct {
					LegoChar m_displayName[0x18];     // 0x00
					undefined2* m_stringChars;        // 0x18
					undefined m_unk0x1c[0x6c - 0x1c]; // 0x1c
					LegoU8 m_unk0x6c[6];              // 0x6c
					LegoU8 m_unk0x72;                 // 0x72
					undefined m_unk0x73[0x74 - 0x73]; // 0x73
					LegoU32 m_unk0x74;                // 0x74
					LegoFloat m_unk0x78;              // 0x78
					LegoU32 m_unk0x7c;                // 0x7c
					LegoU32 m_unk0x80;                // 0x80
					undefined m_unk0x84[0x88 - 0x84]; // 0x84
				};
			};
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

		protected:
			SoundGroup* m_groups[4]; // 0x04
		};

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
					void FUN_004a5e10(GolFileParser* p_parser, LegoBool32 p_mirror);

					LegoS16 m_positionX;          // 0x00
					LegoS16 m_positionY;          // 0x02
					LegoS8 m_positionZ;           // 0x04
					LegoS8 m_rotationX;           // 0x05
					LegoS8 m_rotationY;           // 0x06
					LegoS8 m_rotationZ;           // 0x07
					LegoS8 m_rotationW;           // 0x08
					LegoS8 m_unk0x09;             // 0x09
					LegoS8 m_unk0x0a;             // 0x0a
					LegoU8 m_packedTypeAndLength; // 0x0b
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
		};

		// SIZE 0x3d0
		class Field0x018 {
		public:
			// SIZE 0x68
			class InitParams {
			public:
				GolModelEntity* m_unk0x00;    // 0x00
				GolAnimatedEntity* m_unk0x04; // 0x04
				GolAnimatedEntity* m_unk0x08; // 0x08
				GolAnimatedEntity* m_unk0x0c; // 0x0c
				GolVec3 m_unk0x10;            // 0x10
				Racer* m_racer;               // 0x1c
				LegoFloat m_unk0x20;          // 0x20
				LegoFloat m_unk0x24;          // 0x24
				LegoFloat m_unk0x28;          // 0x28
				LegoFloat m_unk0x2c;          // 0x2c
				GolName m_materialName;       // 0x30
				GolVec3 m_unk0x38[4];         // 0x38
			};

			// SIZE 0x6c4
			class Field0x1dc {
			public:
				// SIZE 0x70
				class Field0x1a4 {
				public:
					enum {
						c_flags0x03cBit0 = 1 << 0,
					};

					GolVec3 m_unk0x000;                  // 0x00
					undefined m_unk0x00c[0x03c - 0x00c]; // 0x0c
					LegoU32 m_flags0x03c;                // 0x3c
					undefined m_unk0x040[0x70 - 0x040];  // 0x40
				};

				enum {
					c_flags0x6c0Bit1 = 1 << 1,
				};

				undefined m_unk0x000[0x008 - 0x000]; // 0x000
				GolVec3 m_unk0x008;                  // 0x008
				undefined m_unk0x014[0x1a4 - 0x014]; // 0x014
				Field0x1a4 m_unk0x1a4[4];            // 0x1a4
				undefined m_unk0x364[0x5f8 - 0x364]; // 0x364
				GolVec3 m_unk0x5f8;                  // 0x5f8
				LegoFloat m_unk0x604;                // 0x604
				undefined m_unk0x608[0x618 - 0x608]; // 0x608
				LegoFloat m_unk0x618;                // 0x618
				undefined m_unk0x61c[0x6c0 - 0x61c]; // 0x61c
				LegoU32 m_flags0x6c0;                // 0x6c0
			};

			enum {
				c_flags0x000Bit1 = 1 << 1,
				c_flags0x000Bit2 = 1 << 2,
				c_flags0x000Bit3 = 1 << 3,
				c_flags0x000Bit4 = 1 << 4,
				c_flags0x000Bit8 = 1 << 8,
				c_flags0x000Bit9 = 1 << 9,
				c_flags0x000Bit10 = 1 << 10,
				c_flags0x000Bit11 = 1 << 11,
				c_flags0x000Bit12 = 1 << 12,
				c_alphaOverrideFlag = 1,
				c_fadeAlphaMax = 0xbf,
				c_racerFlags0xd04Bit3 = 1 << 3,
				c_racerFlags0xd04Bit4 = 1 << 4,
				c_racerFlags0xd04Bit6 = 1 << 6,
				c_racerFlags0xd04Bit11 = 1 << 11,
				c_randomTableMask = 0x3ff,
				c_animationPart0 = 0,
				c_animationPart1 = 1,
				c_animationPart2 = 2,
				c_animationPart3 = 3,
				c_animationPart4 = 4,
				c_animationPart5 = 5,
				c_animationPart6 = 6,
				c_animationPart7 = 7,
				c_animationPart8 = 8,
				c_animationPart9 = 9,
				c_animationPart10 = 10,
				c_animationPart11 = 11,
				c_animationPart12 = 12,
				c_animationPart13 = 13,
				c_animationPart14 = 14,
				c_animationPart15 = 15,
				c_animationPart16 = 16,
				c_animationPart17 = 17,
				c_animationTransitionMs = 300,
				c_avoidanceCooldownBaseMs = 5000,
				c_avoidanceCooldownRangeMs = 1000,
				c_flags0x384Bit0 = 1 << 0,
				c_flags0x384Bit1 = 1 << 1,
				c_slotFlagsBit0 = 1 << 0,
				c_slotFlagsBit1 = 1 << 1,
				c_slotFlagsBit2 = 1 << 2,
				c_slotFlagsWithoutBit0 = 0xfe,
			};

			Field0x018();
			void Reset();
			void FUN_0043d7a0(InitParams* p_params, Field0x3b190Params0x08* p_context);
			void FUN_0043d990(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
			void FUN_0043d9f0();
			void FUN_0043da10();
			void FUN_0043da30();
			void Destroy();
			void FUN_0043db60();
			void FUN_0043dbb0();
			void FUN_0043dc00();
			void FUN_0043dcd0();
			void FUN_0043dd50(LegoU32 p_unk0x04, const LegoChar* p_unk0x08);
			void FUN_0043de90(LegoU32 p_unk0x04);
			void FUN_0043def0();
			void FUN_0043df90();
			void FUN_0043e070(LegoU32 p_elapsedMs);
			void FUN_0043e620();
			void FUN_0043e740(LegoS32 p_elapsedMs);
			void FUN_0043ec10(LegoU32 p_elapsedMs);
			void FUN_0043f1e0(LegoU32 p_elapsedMs);
			void FUN_0043f530(LegoU32 p_elapsedMs);
			void FUN_0043fa50(GolCamera* p_camera);
			void FUN_0043fbc0(GolD3DRenderDevice* p_renderer);
			void FUN_0043fc20(GolD3DRenderDevice* p_renderer);
			void FUN_0043fd30();
			void FUN_0043fd70();
			void FUN_0043fd90();
			void FUN_0043fdb0();
			LegoBool32 FUN_0043fdc0(const GolVec3* p_start, const GolVec3* p_end, GolVec3* p_hit);
			void FUN_0043ff20(GolD3DRenderDevice* p_renderer);
			void FUN_00440030();
			void FUN_004400a0(ColorTransform0x20* p_unk0x04);
			void FUN_004400e0();
			void FUN_00440100(ColorTransform0x20* p_unk0x04, undefined4 p_unk0x08);
			void FUN_00440130();
			void FUN_00440160(LegoFloat p_unk0x04);
			void FUN_004401a0();
			void FUN_004401b0();
			void FUN_004401e0();
			~Field0x018();

			GolAnimatedEntity* GetUnk0x044() const { return m_unk0x044; }
			void SetFlags0x384(LegoU32 p_flags) { m_unk0x384 |= p_flags; }

			LegoU32 m_unk0x000;                                  // 0x000
			GolWorldEntityGroup0x38 m_unk0x004;                  // 0x004
			GolModelEntity* m_unk0x03c;                          // 0x03c
			GolAnimatedEntity* m_unk0x040;                       // 0x040
			GolAnimatedEntity* m_unk0x044;                       // 0x044
			GolAnimatedEntity* m_unk0x048;                       // 0x048
			GolVec3 m_unk0x04c;                                  // 0x04c
			GolVec3 m_unk0x058;                                  // 0x058
			GolCollidableEntity* m_unk0x064;                     // 0x064
			LegoFloat m_unk0x068[3];                             // 0x068
			GolName m_unk0x074;                                  // 0x074
			RaceSessionField0x27d4::Item::Field0x004 m_unk0x07c; // 0x07c
			LegoFloat m_unk0x198;                                // 0x198
			LegoFloat m_unk0x19c;                                // 0x19c
			LegoFloat m_unk0x1a0;                                // 0x1a0
			LegoFloat m_unk0x1a4;                                // 0x1a4
			GolVec3 m_unk0x1a8[4];                               // 0x1a8
			Racer* m_racer;                                      // 0x1d8
			union {
				Field0x1dc* m_unk0x1dc;        // 0x1dc
				Field0x3e8* m_racerField0x3e8; // 0x1dc
			};
			RaceSessionField0x27d4* m_unk0x1e0;          // 0x1e0
			RaceSessionField0x27d4::Item* m_unk0x1e4[4]; // 0x1e4
			LegoU8 m_unk0x1f4[4];                        // 0x1f4
			LegoU32 m_unk0x1f8[4];                       // 0x1f8
			undefined4 m_unk0x208[4];                    // 0x208
			GolBillboard::Field0x2c m_unk0x218;          // 0x218
			GolBillboard::Field0x2c m_unk0x224;          // 0x224
			CutsceneParticleRef* m_unk0x230[4];          // 0x230
			GolName m_unk0x240[4];                       // 0x240
			LegoU32 m_unk0x260[4];                       // 0x260
			CutsceneParticleRef* m_unk0x270;             // 0x270
			CutsceneParticleRef* m_unk0x274;             // 0x274
			CutsceneParticleRef* m_unk0x278;             // 0x278
			CutsceneAnimation* m_unk0x27c;               // 0x27c
			CutsceneAnimation* m_unk0x280;               // 0x280
			GolAnimatedEntity m_unk0x284;                // 0x284
			LegoU32 m_unk0x378;                          // 0x378
			LegoU32 m_unk0x37c;                          // 0x37c
			Racer* m_unk0x380;                           // 0x380
			LegoU32 m_unk0x384;                          // 0x384
			LegoU32 m_unk0x388;                          // 0x388
			LegoFloat m_unk0x38c;                        // 0x38c
			undefined4 m_unk0x390;                       // 0x390
			undefined4 m_unk0x394;                       // 0x394
			LegoFloat m_unk0x398;                        // 0x398
			LegoFloat m_unk0x39c;                        // 0x39c
			ColorTransform0x20 m_unk0x3a0;               // 0x3a0
			LegoU32 m_unk0x3c0;                          // 0x3c0
			LegoU32 m_unk0x3c4;                          // 0x3c4
			undefined4 m_unk0x3c8;                       // 0x3c8
			LegoU32 m_unk0x3cc;                          // 0x3cc
		};

		// VTABLE: LEGORACERS 0x004b0b78
		// SIZE 0xd0
		class Field0x3e8Base0xd0 {
		public:
			Field0x3e8Base0xd0();
			virtual void VTable0x00() = 0;                // vtable+0x00
			virtual void VTable0x04(LegoS32 p_elapsedMs); // vtable+0x04
			virtual GolOrientedEntity* VTable0x08();      // vtable+0x08

			void FUN_00440970();
			void FUN_004409f0(GolOrientedEntity* p_unk0x04, LegoFloat p_unk0x08);
			void FUN_00440a50();
			void FUN_00440a60();
			void FUN_00440a80();

			GolOrientedEntity* m_unk0x004; // 0x004
			GolVec3 m_unk0x008;            // 0x008
			GolVec3 m_unk0x014;            // 0x014
			GolVec3 m_unk0x020;            // 0x020
			GolMatrix3 m_unk0x02c;         // 0x02c
			GolMatrix3 m_unk0x050;         // 0x050
			GolMatrix3 m_unk0x074;         // 0x074
			GolVec3 m_unk0x098;            // 0x098
			GolVec3 m_unk0x0a4;            // 0x0a4
			GolVec3 m_unk0x0b0;            // 0x0b0
			GolVec3 m_unk0x0bc;            // 0x0bc
			LegoFloat m_unk0x0c8;          // 0x0c8
			LegoFloat m_unk0x0cc;          // 0x0cc
		};

		// VTABLE: LEGORACERS 0x004b0b84
		// SIZE 0xe4
		class Field0x3e8Base0xe4 : public Field0x3e8Base0xd0 {
		public:
			Field0x3e8Base0xe4();
			void VTable0x00() override; // vtable+0x00
			void FUN_00441210(
				GolOrientedEntity* p_unk0x04,
				LegoFloat p_unk0x08,
				LegoFloat p_unk0x0c,
				LegoFloat p_unk0x10,
				LegoFloat p_unk0x14
			);

			LegoFloat m_unk0x0d0; // 0x0d0
			LegoFloat m_unk0x0d4; // 0x0d4
			LegoFloat m_unk0x0d8; // 0x0d8
			LegoFloat m_unk0x0dc; // 0x0dc
			Racer* m_racer;       // 0x0e0
		};

		// VTABLE: LEGORACERS 0x004b0d8c
		// SIZE 0x74c
		class Field0x3e8Base0x74c : public Field0x3e8Base0xe4 {
		public:
			Field0x3e8Base0x74c();

			// SIZE 0x78
			class Field0x74c {
			public:
				void FUN_004a5220(Field0x00c::Entry* p_unk0x04);
				void FUN_004a5200(Field0x00c::Entry* p_unk0x04);
				void FUN_004a5320(LegoFloat p_unk0x04);
				void FUN_004a5750(GolVec3* p_unk0x04);
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

			// SIZE 0x78
			class Field0x74cInstance : public Field0x74c {
			public:
				Field0x74cInstance();
				~Field0x74cInstance();
			};

			class CollisionCacheRecord;

			class Field0x198 {
			public:
				enum {
					c_flags0x048Active = 1 << 0,
					c_flags0x048Hit = 1 << 1,
				};

				GolVec3 m_unk0x000;               // 0x00
				GolVec3 m_unk0x00c;               // 0x0c
				GolVec3 m_unk0x018;               // 0x18
				GolVec3 m_unk0x024;               // 0x24
				GolVec3 m_unk0x030;               // 0x30
				RaceEventRecord* m_unk0x03c;      // 0x3c
				RaceEventRecord* m_unk0x040;      // 0x40
				CollisionCacheRecord* m_unk0x044; // 0x44
				LegoU32 m_flags0x048;             // 0x48
				LegoFloat m_unk0x04c;             // 0x4c
				LegoFloat m_unk0x050;             // 0x50
				LegoFloat m_unk0x054;             // 0x54
				LegoFloat m_unk0x058;             // 0x58
				LegoFloat m_unk0x05c;             // 0x5c
				LegoFloat m_unk0x060;             // 0x60
				GolVec3 m_unk0x064;               // 0x64
			};

			// SIZE 0x3c
			class CollisionCacheRecord {
			public:
				GolBoundingVolume::Field0x0c m_unk0x000; // 0x00
				LegoU32 m_unk0x034;                      // 0x34
				RaceEventRecord* m_unk0x038;             // 0x38
			};

			// SIZE 0x70
			class SnapshotEntry {
			public:
				GolVec3 m_unk0x000;                  // 0x00
				undefined m_unk0x00c[0x030 - 0x00c]; // 0x0c
				RaceEventRecord* m_unk0x030;         // 0x30
				undefined m_unk0x034[0x03c - 0x034]; // 0x34
				LegoU32 m_flags0x03c;                // 0x3c
				undefined4 m_unk0x040;               // 0x40
				LegoFloat m_unk0x044;                // 0x44
				LegoFloat m_unk0x048;                // 0x48
				LegoFloat m_unk0x04c;                // 0x4c
				LegoFloat m_unk0x050;                // 0x50
				LegoFloat m_unk0x054;                // 0x54
				GolVec3 m_unk0x058;                  // 0x58
				undefined m_unk0x064[0x070 - 0x064]; // 0x64
			};

			// SIZE 0x1ec
			class SnapshotEntryBlock {
			public:
				SnapshotEntry* GetEntries() { return m_entries; }
				GolBoundingVolume::Field0x0c* GetEventContext() { return &m_eventContext; }

				union {
					struct {
						SnapshotEntry m_entries[4];          // 0x000
						undefined m_unk0x1c0[0x1ec - 0x1c0]; // 0x1c0
					};
					struct {
						undefined m_unk0x000[0x1b4 - 0x000];         // 0x000
						GolBoundingVolume::Field0x0c m_eventContext; // 0x1b4
						undefined m_unk0x1e8[0x1ec - 0x1e8];         // 0x1e8
					};
				};
			};

			// SIZE 0xf4
			class Snapshot {
			public:
				GolVec3 m_unk0x000[4];               // 0x00
				GolVec3 m_unk0x030;                  // 0x30
				undefined m_unk0x03c[0x040 - 0x03c]; // 0x3c
				GolVec3 m_unk0x040[4];               // 0x40
				GolVec3 m_unk0x070[4];               // 0x70
				GolVec3 m_unk0x0a0;                  // 0xa0
				LegoFloat m_unk0x0ac;                // 0xac
				LegoFloat m_unk0x0b0;                // 0xb0
				undefined m_unk0x0b4[0x0c4 - 0x0b4]; // 0xb4
				GolMatrix3 m_unk0x0c4;               // 0xc4
				GolVec3 m_unk0x0e8;                  // 0xe8
			};

			void VTable0x04(LegoS32 p_elapsedMs) override; // vtable+0x04
			GolOrientedEntity* VTable0x08() override;      // vtable+0x08
			virtual LegoU32 VTable0x0c(                                       // vtable+0x0c
				GolVec3* p_unk0x04,
				RaceEventRecord* p_unk0x08,
				GolBoundedEntity* p_unk0x0c,
				GolBoundingVolume::Field0x0c* p_unk0x10
			) = 0;
			virtual void VTable0x10() = 0;                                    // vtable+0x10
			virtual void VTable0x14(LegoFloat p_unk0x04);                     // vtable+0x14
			virtual void VTable0x18(LegoFloat p_unk0x04);                     // vtable+0x18
			virtual void VTable0x1c(GolVec3* p_unk0x04, GolVec3* p_unk0x08);  // vtable+0x1c
			virtual void VTable0x20(GolVec3* p_unk0x04, LegoFloat p_unk0x08); // vtable+0x20
			virtual void VTable0x24(LegoFloat p_unk0x04, LegoFloat p_unk0x08,
									LegoFloat p_unk0x0c); // vtable+0x24
			virtual void VTable0x28();                    // vtable+0x28
			virtual void VTable0x2c();                    // vtable+0x2c
			virtual void VTable0x30();                    // vtable+0x30
			virtual void VTable0x34();                    // vtable+0x34
			virtual void VTable0x38();                    // vtable+0x38
			virtual void VTable0x3c();                    // vtable+0x3c
			virtual void VTable0x40(GolVec3* p_unk0x04);  // vtable+0x40
			virtual void VTable0x44();                    // vtable+0x44
			virtual void VTable0x48(GolVec3* p_unk0x04);  // vtable+0x48
			virtual void VTable0x4c();                    // vtable+0x4c

			void FUN_00429210(
				Racer* p_racer,
				RaceEventTable0x90* p_unk0x08,
				undefined4 p_unk0x0c,
				GolAnimatedEntity* p_unk0x10,
				GolBoundedEntity* p_unk0x14,
				GolBoundedEntity* p_unk0x18,
				Field0x004* p_unk0x1c,
				LegoFloat p_unk0x20,
				LegoFloat p_unk0x24,
				LegoFloat p_unk0x28,
				LegoFloat p_unk0x2c
			);
			void FUN_004292e0();
			void FUN_00429330();
			void FUN_00429380();
			void FUN_004293c0();
			void FUN_004293f0(LegoU32 p_elapsedMs);
			void FUN_00429680(GolVec3* p_unk0x04);
			void Destroy();
			void Reset();
			void FUN_00429a90();
			void FUN_00429af0();
			void FUN_0042a670(Field0x00c::Entry* p_unk0x04);
			void FUN_0042aa30(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08);
			void FUN_0042aa70(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08);
			void FUN_0042aad0(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08);
			void FUN_0042acb0(Field0x198* p_unk0x04);
			void FUN_0042ad70(LegoS32 p_unk0x04);
			void FUN_0042ada0(LegoS32 p_unk0x04);
			void FUN_0042add0(LegoS32 p_unk0x04);
			SpatialSoundInstance* FUN_0042af90(LegoS32 p_unk0x04);
			void FUN_0042b060();
			void FUN_00429940();
			void FUN_00429990(GolVec3* p_unk0x04);
			void FUN_00440b10(GolVec3* p_unk0x04);
			void FUN_00440b50(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
			void FUN_00440cb0(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
			void FUN_00440bd0(GolVec3* p_unk0x04);
			void FUN_00440da0(GolVec3* p_unk0x04);
			void FUN_00441190(GolVec3* p_unk0x04);
			void FUN_00444b40();
			void FUN_00444d90(
				GolAnimatedEntity* p_unk0x04,
				GolBoundedEntity* p_unk0x08,
				GolBoundedEntity* p_unk0x0c,
				Field0x004* p_unk0x10,
				LegoFloat p_unk0x14,
				LegoFloat p_unk0x18,
				LegoFloat p_unk0x1c,
				LegoFloat p_unk0x20
			);
			void FUN_00444e90();
			void FUN_00445bb0(LegoFloat p_unk0x04, LegoU32 p_unk0x08);
			void FUN_00445c30(LegoFloat p_unk0x04, LegoU32 p_unk0x08);
			void FUN_00446e60(GolVec3* p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c);
			void FUN_00446ea0(LegoU32 p_unk0x04, GolVec3* p_unk0x08);
			void FUN_00446fa0();
			void FUN_004480c0(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
			void FUN_00448110(GolVec3* p_unk0x04, LegoFloat p_unk0x08);
			void FUN_004482e0();
			void FUN_00448370(LegoFloat p_unk0x04);
			void FUN_00448390(LegoFloat p_unk0x04);
			void FUN_004483b0();
			void FUN_00448160(LegoFloat p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c);
			void FUN_00448430(Field0x198* p_unk0x04);
			void FUN_00448660();
			void FUN_00448730();
			void FUN_00448760(GolVec3* p_unk0x04);
			void FUN_004487a0();
			void FUN_004487b0(GolVec3* p_unk0x04);
			void FUN_004487f0();
			void FUN_00448800();
			void FUN_00448820();
			LegoU32 FUN_004488e0(GolBoundedEntity* p_unk0x04);
			void FUN_00448930(GolBoundedEntity* p_unk0x04);
			LegoFloat FUN_00448990();
			LegoFloat FUN_004489c0();
			void FUN_00448a50();
			CollisionCacheRecord* FUN_00448a70(GolBoundingVolume::Field0x0c* p_unk0x04, RaceEventRecord* p_unk0x08);
			LegoBool32 FUN_00448ae0(Field0x198* p_unk0x04);
			static LegoBool32 FUN_00448b80(Field0x198* p_unk0x04, CollisionCacheRecord* p_unk0x08);
			void FUN_00448c70();
			void FUN_00448d90(GolBoundedEntity* p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c);
			void FUN_004490b0(GolVec3* p_unk0x04);
			void FUN_00429cf0(LegoFloat p_unk0x04, LegoU32 p_unk0x08);
			void FUN_00429d40(LegoU32 p_elapsedMs);
			void FUN_0042a100();
			void FUN_0042a220();
			void FUN_0042a290(LegoU32 p_elapsedMs);
			void FUN_0042a570();
			void FUN_0042a730(Field0x00c::Entry* p_unk0x04);
			LegoBool32 FUN_0042a7f0();
			LegoFloat FUN_0042ae10();
			LegoBool32 FUN_0042ae20();
			LegoBool32 FUN_0042aea0(LegoFloat p_unk0x04);
			void FUN_0042b0c0();
			void FUN_004452b0(LegoS32 p_elapsedMs);
			void FUN_00445500();
			void FUN_00445d10();
			void FUN_00445dc0(LegoU32 p_elapsedMs);
			LegoFloat FUN_00445cb0();
			void FUN_004464a0(LegoS32 p_elapsedMs);
			void FUN_004465c0(LegoU32 p_elapsedMs);
			void FUN_00446fd0(LegoU32 p_elapsedMs);
			void FUN_00446ef0(LegoFloat p_unk0x04);
			void FUN_00447230(LegoS32 p_elapsedMs, GolVec3* p_unk0x08);
			void FUN_00447330();
			void FUN_004474c0();
			void FUN_00447690();
			void FUN_00447880();
			LegoU32 FUN_004478b0(LegoU32 p_elapsedMs, LegoBool32 p_unk0x08);
			void FUN_00447cf0();
			void FUN_00447f30(LegoFloat p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c);
			void FUN_00448070();
			void FUN_00448840();
			LegoFloat FUN_004489f0();
			undefined4 FUN_00449070(undefined4 p_unk0x04);
			undefined4 FUN_00449090();

			enum {
				c_unk0x140Count = 5,
				c_collisionCacheRecordCount = 8,
				c_flags0x6c0Bit0 = 1 << 0,
				c_flags0x6c0Bit1 = 1 << 1,
				c_flags0x6c0Bit2 = 1 << 2,
				c_flags0x6c0Bit3 = 1 << 3,
				c_flags0x6c0Bit5 = 1 << 5,
				c_flags0x6c0Bit6 = 1 << 6,
				c_flags0x6c0Bit7 = 1 << 7,
				c_flags0x6c0Bit8 = 1 << 8,
				c_flags0x6c0Bit9 = 1 << 9,
				c_flags0x6c0Bit10 = 1 << 10,
				c_flags0x6c0Bit11 = 1 << 11,
				c_flags0x6c0Bit12 = 1 << 12,
				c_flags0x6c0Bit16 = 1 << 16,
				c_flags0x6c0Bit17 = 1 << 17,
				c_flags0x6c0Bit18 = 1 << 18,
				c_flags0x6c0Bit19 = 1 << 19,
				c_flags0x6c0Bit20 = 1 << 20,
			};

			GolOrientedEntity m_unk0x0e4;                                 // 0x0e4
			GolOrientedEntity* m_unk0x13c;                                // 0x13c
			GolBoundedEntity* m_unk0x140[c_unk0x140Count];                // 0x140
			LegoU32 m_unk0x154;                                           // 0x154
			Field0x004* m_unk0x158;                                       // 0x158
			LegoFloat m_unk0x15c;                                         // 0x15c
			LegoFloat m_unk0x160;                                         // 0x160
			LegoFloat m_unk0x164;                                         // 0x164
			GolVec3 m_unk0x168;                                           // 0x168
			GolVec3 m_unk0x174;                                           // 0x174
			GolVec3 m_unk0x180;                                           // 0x180
			LegoFloat m_unk0x18c;                                         // 0x18c
			LegoFloat m_unk0x190;                                         // 0x190
			LegoFloat m_unk0x194;                                         // 0x194
			Field0x198 m_unk0x198[4];                                     // 0x198
			GolVec3 m_unk0x358;                                           // 0x358
			LegoFloat m_unk0x364;                                         // 0x364
			LegoFloat m_unk0x368;                                         // 0x368
			LegoU32 m_unk0x36c;                                           // 0x36c
			GolVec3 m_unk0x370[4];                                        // 0x370
			GolVec3 m_unk0x3a0[4];                                        // 0x3a0
			undefined4 m_unk0x3d0[4];                                     // 0x3d0
			GolVec3 m_unk0x3e0;                                           // 0x3e0
			LegoU32 m_unk0x3ec;                                           // 0x3ec
			LegoU32 m_unk0x3f0;                                           // 0x3f0
			CollisionCacheRecord m_unk0x3f4[c_collisionCacheRecordCount]; // 0x3f4
			LegoU32 m_unk0x5d4;                                           // 0x5d4
			LegoU32 m_unk0x5d8;                                           // 0x5d8
			LegoU32 m_unk0x5dc;                                           // 0x5dc
			LegoU32 m_unk0x5e0;                                           // 0x5e0
			LegoU32 m_unk0x5e4;                                           // 0x5e4
			LegoU32 m_unk0x5e8;                                           // 0x5e8
			LegoFloat m_unk0x5ec;                                         // 0x5ec
			undefined4 m_unk0x5f0;                                        // 0x5f0
			LegoFloat m_unk0x5f4;                                         // 0x5f4
			GolVec3 m_unk0x5f8;                                           // 0x5f8
			LegoFloat m_unk0x604;                                         // 0x604
			LegoFloat m_unk0x608;                                         // 0x608
			GolVec3 m_unk0x60c;                                           // 0x60c
			LegoFloat m_unk0x618;                                         // 0x618
			GolVec3 m_unk0x61c;                                           // 0x61c
			LegoFloat m_unk0x628;                                         // 0x628
			undefined4 m_unk0x62c;                                        // 0x62c
			GolVec3 m_unk0x630;                                           // 0x630
			GolVec3 m_unk0x63c;                                           // 0x63c
			LegoFloat m_unk0x648;                                         // 0x648
			LegoFloat m_unk0x64c;                                         // 0x64c
			LegoFloat m_unk0x650;                                         // 0x650
			LegoFloat m_unk0x654;                                         // 0x654
			LegoFloat m_unk0x658;                                         // 0x658
			LegoFloat m_unk0x65c;                                         // 0x65c
			LegoFloat m_unk0x660;                                         // 0x660
			GolVec3 m_unk0x664;                                           // 0x664
			GolVec3 m_unk0x670;                                           // 0x670
			LegoFloat m_unk0x67c;                                         // 0x67c
			LegoFloat m_unk0x680;                                         // 0x680
			GolVec3 m_unk0x684;                                           // 0x684
			GolVec3 m_unk0x690;                                           // 0x690
			GolMatrix3 m_unk0x69c;                                        // 0x69c
			LegoU32 m_flags0x6c0;                                         // 0x6c0
			LegoFloat m_unk0x6c4;                                         // 0x6c4
			LegoFloat m_unk0x6c8;                                         // 0x6c8
			LegoFloat m_unk0x6cc;                                         // 0x6cc
			LegoFloat m_unk0x6d0;                                         // 0x6d0
			LegoFloat m_unk0x6d4;                                         // 0x6d4
			union {
				LegoU32 m_unk0x6d8;     // 0x6d8
				LegoFloat m_float0x6d8; // 0x6d8
			};
			LegoU32 m_unk0x6dc; // 0x6dc
			LegoU32 m_unk0x6e0; // 0x6e0
			union {
				RaceResourceManager::Resource* m_unk0x6e4; // 0x6e4
				SpatialSoundInstance* m_sound6e4;          // 0x6e4
			};
			union {
				RaceResourceManager::Resource* m_unk0x6e8; // 0x6e8
				SpatialSoundInstance* m_sound6e8;          // 0x6e8
			};
			LegoU32 m_unk0x6ec;             // 0x6ec
			Racer* m_unk0x6f0;              // 0x6f0
			RaceEventTable0x90* m_unk0x6f4; // 0x6f4
			undefined4 m_unk0x6f8;          // 0x6f8
			GolBoundedEntity* m_unk0x6fc;   // 0x6fc
			GolVec3 m_unk0x700;             // 0x700
			GolQuat m_unk0x70c;             // 0x70c
			LegoS32 m_unk0x71c;             // 0x71c
			LegoS32 m_unk0x720;             // 0x720
			LegoS32 m_unk0x724;             // 0x724
			LegoFloat m_unk0x728;           // 0x728
			LegoFloat m_unk0x72c;           // 0x72c
			LegoFloat m_unk0x730;           // 0x730
			LegoFloat m_unk0x734;           // 0x734
			undefined4 m_unk0x738;          // 0x738
			LegoS32 m_unk0x73c;             // 0x73c
			union {
				SpatialSoundInstance* m_unk0x740;               // 0x740
				RaceResourceManager::Resource* m_soundResource; // 0x740
			};
			LegoU32 m_unk0x744; // 0x744
			LegoU32 m_unk0x748; // 0x748
		};

		// VTABLE: LEGORACERS 0x004b04e4
		// SIZE 0x888
		class Field0x3e8 : public Field0x3e8Base0x74c {
		public:
			Field0x3e8();

			void VTable0x04(LegoS32 p_elapsedMs) override; // vtable+0x04
			LegoU32 VTable0x0c(                                               // vtable+0x0c
				GolVec3* p_unk0x04,
				RaceEventRecord* p_unk0x08,
				GolBoundedEntity* p_unk0x0c,
				GolBoundingVolume::Field0x0c* p_unk0x10
			) override;
			void VTable0x10() override;                                        // vtable+0x10
			void VTable0x14(LegoFloat p_unk0x04) override;                     // vtable+0x14
			void VTable0x18(LegoFloat p_unk0x04) override;                     // vtable+0x18
			void VTable0x1c(GolVec3* p_unk0x04, GolVec3* p_unk0x08) override;  // vtable+0x1c
			void VTable0x20(GolVec3* p_unk0x04, LegoFloat p_unk0x08) override; // vtable+0x20
			void VTable0x24(LegoFloat p_unk0x04, LegoFloat p_unk0x08,
							LegoFloat p_unk0x0c) override; // vtable+0x24
			void VTable0x2c() override;                    // vtable+0x2c
			void VTable0x30() override;                    // vtable+0x30
			void VTable0x34() override;                    // vtable+0x34
			void VTable0x38() override;                    // vtable+0x38
			void VTable0x3c() override;                    // vtable+0x3c
			void VTable0x40(GolVec3* p_unk0x04) override;  // vtable+0x40
			void VTable0x44() override;                    // vtable+0x44
			void VTable0x48(GolVec3* p_unk0x04) override;  // vtable+0x48
			void VTable0x4c() override;                    // vtable+0x4c
			virtual ~Field0x3e8();                         // vtable+0x50

			// SYNTHETIC: LEGORACERS 0x00429090
			// RaceState::Racer::Field0x3e8::`scalar deleting destructor'

			void Reset();
			void FUN_00429210(
				Racer* p_racer,
				RaceEventTable0x90* p_unk0x08,
				undefined4 p_unk0x0c,
				GolAnimatedEntity* p_unk0x10,
				GolBoundedEntity* p_unk0x14,
				GolBoundedEntity* p_unk0x18,
				Field0x004* p_unk0x1c,
				LegoFloat p_unk0x20,
				LegoFloat p_unk0x24,
				LegoFloat p_unk0x28,
				LegoFloat p_unk0x2c
			);
			void Destroy();
			void FUN_004292e0();
			void FUN_00429330();
			void FUN_00429380();
			void FUN_004293c0();
			void FUN_00429680(GolVec3* p_unk0x04);
			void FUN_00429940();
			void FUN_00429990(GolVec3* p_unk0x04);
			void FUN_00429a90();
			void FUN_00429af0();
			void FUN_00429cf0(LegoFloat p_unk0x04, LegoU32 p_unk0x08);
			void FUN_00429d40(LegoU32 p_elapsedMs);
			void FUN_0042a100();
			void FUN_0042a220();
			void FUN_0042a290(LegoU32 p_elapsedMs);
			void FUN_0042a570();
			void FUN_0042a670(Field0x00c::Entry* p_unk0x04);
			void FUN_0042a730(Field0x00c::Entry* p_entry);
			LegoBool32 FUN_0042a7f0();
			void FUN_0042aa30(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08);
			void FUN_0042aa70(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08);
			void FUN_0042aad0(Field0x198* p_unk0x04, RaceEventRecord::Target* p_unk0x08);
			void FUN_0042acb0(Field0x198* p_unk0x04);
			void FUN_0042ad70(LegoS32 p_unk0x04);
			void FUN_0042ada0(LegoS32 p_unk0x04);
			void FUN_0042add0(LegoS32 p_unk0x04);
			LegoFloat FUN_0042ae10();
			LegoBool32 FUN_0042ae20();
			LegoBool32 FUN_0042aea0(LegoFloat p_unk0x04);
			SpatialSoundInstance* FUN_0042af90(LegoS32 p_unk0x04);
			void FUN_0042b060();
			void FUN_0042b0c0();
			LegoFloat FUN_00445cb0();
			void FUN_00446ef0(LegoFloat p_unk0x04);
			LegoFloat FUN_004489f0();
			undefined4 FUN_00449070(undefined4 p_unk0x04);
			undefined4 FUN_00449090();

			Field0x74cInstance m_unk0x74c;       // 0x74c
			GolQuat m_unk0x7c4;                  // 0x7c4
			LegoFloat m_unk0x7d4;                // 0x7d4
			LegoFloat m_unk0x7d8;                // 0x7d8
			LegoFloat m_unk0x7dc;                // 0x7dc
			LegoFloat m_unk0x7e0;                // 0x7e0
			LegoFloat m_unk0x7e4;                // 0x7e4
			LegoFloat m_unk0x7e8;                // 0x7e8
			LegoFloat m_unk0x7ec;                // 0x7ec
			Field0x74cInstance m_unk0x7f0;       // 0x7f0
			GolQuat m_unk0x868;                  // 0x868
			LegoFloat m_unk0x878;                // 0x878
			LegoFloat m_unk0x87c;                // 0x87c
			undefined m_unk0x880[0x888 - 0x880]; // 0x880
		};

		class Field0xd5c;

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

			void FUN_0041fbd0(Field0x3e8* p_unk0x04);
			void FUN_0041fc00(LegoU32 p_elapsedMs);
			void FUN_0041fd60(LegoU32 p_elapsedMs);
			void FUN_0041fdb0(LegoU32 p_elapsedMs);
			void FUN_0041fe60(LegoFloat p_unk0x04);
			void FUN_0041fee0();
			void FUN_00420130(LegoFloat p_unk0x04);
			void FUN_004201e0();
			void FUN_00420260(LegoBool32 p_unk0x04);
			undefined4 FUN_004202c0();
			GolQuat* FUN_004202f0(Field0x00c::Entry* p_unk0x04);
			void FUN_00420380();
			void FUN_004203b0(LegoU32 p_elapsedMs);
			Field0xc70();
			void Destroy();
			void Reset();
			~Field0xc70();

			Field0x3e8* m_unk0x000;                     // 0x00
			Field0x00c::Entry* m_unk0x004;              // 0x04
			LegoFloat m_unk0x008;                       // 0x08
			LegoFloat m_unk0x00c;                       // 0x0c
			LegoFloat m_unk0x010;                       // 0x10
			LegoU32 m_unk0x014;                         // 0x14
			LegoFloat m_unk0x018;                       // 0x18
			LegoFloat m_unk0x01c;                       // 0x1c
			LegoU32 m_unk0x020;                         // 0x20
			LegoS32 m_unk0x024;                         // 0x24
			LegoU32 m_unk0x028;                         // 0x28
			LegoU32 m_unk0x02c;                         // 0x2c
			LegoU32 m_unk0x030;                         // 0x30
			GolVec3 m_unk0x034;                         // 0x34
			GolQuat m_unk0x040;                         // 0x40
			Field0x3e8::Field0x74cInstance* m_unk0x050; // 0x50
		};

		enum {
			c_flags0xd04Bit21 = 0x00200000,
		};

		void FUN_00439100();
		LegoU32 FUN_00439210(LegoU32 p_unk0x04);
		LegoU32 GetUnk0xccc() const { return m_unk0xccc; }
		LegoU32 GetUnk0xd04() const { return m_unk0xd04; }
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
		void FUN_00439570();
		void FUN_004395a0();
		void FUN_004395d0();
		void FUN_00439660();
		void FUN_004396c0(LegoU32 p_unk0x04);
		void FUN_00439730();
		void FUN_00439790();
		void FUN_004397a0();
		void FUN_004397b0();
		void FUN_004397c0(LegoBool32 p_unk0x04);
		void FUN_00439240(LegoBool32 p_unk0x04);
		Field0xd5c* FUN_00439490();
		LegoFloat FUN_0043a0a0();
		void FUN_0043a0c0();
		void FUN_0043a0e0();
		void FUN_0043a130();
		void FUN_0043a1a0();
		void FUN_0043a210(LegoU32 p_unk0x04);
		void FUN_0043a270();
		void FUN_0043a300(LegoU32 p_unk0x04, LegoBool32 p_unk0x08);
		void FUN_0043a360();
		void FUN_0043a390();
		void FUN_00437540(RaceCameraController* p_controller, LegoBool32 p_unk0x08);
		LegoU32 FUN_00439770(LegoU32 p_unk0x04);
		void FUN_00439870();
		void FUN_00439900(GolAnimatedEntity* p_unk0x04, LegoU32 p_durationMs);
		void FUN_00439b00();
		void FUN_00439b70();
		LegoU32 FUN_00439ba0();
		void FUN_00439c40();
		void FUN_00439c70(Field0x00c::StandingsDeltaEntry* p_entries);
		void FUN_00439e60(GolVec3* p_unk0x04);
		void FUN_00439e90();
		void FUN_0043a3e0();
		void FUN_0043a3f0();
		void FUN_0043a400();

	private:
		friend class RaceState;
		friend class Field0x3e8;

		void Destroy();
		void Reset();
		void FUN_00436df0(
			Field0x3b190Params0x08* p_context,
			Field0x018::InitParams* p_params,
			Field0x36df0Params* p_unk0x0c,
			RaceState* p_raceState,
			LegoU32 p_racerIndex
		);

		enum {
			c_flags0xd04Bit0 = 1 << 0,
			c_flags0xd04Bit1 = 1 << 1,
			c_flags0xd04Bit3 = 1 << 3,
			c_flags0xd04Bit4 = 1 << 4,
			c_flags0xd04Bit6 = 1 << 6,
			c_flags0xd04Bit7 = 1 << 7,
			c_flags0xd04Bit8 = 1 << 8,
			c_flags0xd04Bit10 = 1 << 10,
			c_flags0xd04Bit11 = 1 << 11,
			c_flags0xd04Bit12 = 1 << 12,
			c_flags0xd04Bit13 = 1 << 13,
			c_flags0xd04Bit14 = 1 << 14,
			c_flags0xd04Bit15 = 1 << 15,
			c_flags0xd04Bit16 = 1 << 16,
			c_flags0xd04Bit17 = 1 << 17,
			c_flags0xd04Bit19 = 0x00080000,
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

		void FUN_00438e60(GolVec3* p_unk0x04);
		void FUN_00438f20();
		void FUN_00439c90();
		void FUN_00439cf0(LegoU32 p_elapsedMs);
		void FUN_00439ea0(LegoU32 p_elapsedMs);
		void FUN_00439fc0(RaceSessionField0x27f4::Entry* p_unk0x04, GolBoundingVolume::Field0x0c* p_unk0x08);

	public:
		LegoBool32 FUN_00439420(Field0xd5c* p_unk0x04);

		union {
			Field0x004* m_unk0x004;                    // 0x004
			RaceResourceManager* m_resourceManager004; // 0x004
		};
		RacePowerupManager* m_unk0x008; // 0x008
		union {
			RaceState* m_unk0x00c;     // 0x00c
			RaceState* m_raceState00c; // 0x00c
		};
		RaceSessionField0x27f4* m_unk0x010;        // 0x010
		RaceForceFeedback* m_unk0x014;             // 0x014
		Field0x018 m_unk0x018;                     // 0x018
		Field0x3e8 m_unk0x3e8;                     // 0x3e8
		Field0xc70 m_unk0xc70;                     // 0xc70
		RaceSessionField0x27f4::Entry* m_unk0xcc4; // 0xcc4
		undefined4 m_unk0xcc8;                     // 0xcc8
		LegoU32 m_unk0xccc;                        // 0xccc
		LegoU32 m_unk0xcd0;                        // 0xcd0
		LegoU32 m_unk0xcd4;                        // 0xcd4
		LegoU32 m_unk0xcd8;                        // 0xcd8
		LegoU32 m_unk0xcdc;                        // 0xcdc
		LegoU8 m_unk0xce0;                         // 0xce0
		undefined m_unk0xce1[0xce4 - 0xce1];       // 0xce1
		LegoU32 m_lapsCompleted;                   // 0xce4
		LegoU32 m_unk0xce8;                        // 0xce8
		LegoU32 m_lapTimes[0x18 / 4];              // 0xcec
		LegoU32 m_unk0xd04;                        // 0xd04
		LegoU32 m_unk0xd08;                        // 0xd08
		LegoU32 m_unk0xd0c;                        // 0xd0c
		LegoU32 m_unk0xd10;                        // 0xd10
		LegoU32 m_unk0xd14;                        // 0xd14
		LegoS32 m_unk0xd18;                        // 0xd18
		LegoU8 m_unk0xd1c;                         // 0xd1c
		LegoU8 m_unk0xd1d;                         // 0xd1d
		LegoU8 m_unk0xd1e;                         // 0xd1e
		LegoU8 m_unk0xd1f;                         // 0xd1f
		LegoU8 m_unk0xd20;                         // 0xd20
		LegoU8 m_unk0xd21;                         // 0xd21
		LegoU8 m_unk0xd22;                         // 0xd22
		LegoU8 m_unk0xd23;                         // 0xd23
		LegoU32 m_unk0xd24;                        // 0xd24
		LegoFloat m_unk0xd28;                      // 0xd28
		LegoFloat m_unk0xd2c;                      // 0xd2c
		LegoFloat m_unk0xd30;                      // 0xd30
		undefined4 m_unk0xd34;                     // 0xd34
		undefined4 m_unk0xd38;                     // 0xd38
		undefined4 m_unk0xd3c;                     // 0xd3c
		LegoU32 m_unk0xd40;                        // 0xd40
		LegoU32 m_unk0xd44;                        // 0xd44
		undefined4 m_unk0xd48;                     // 0xd48
		undefined4 m_unk0xd4c;                     // 0xd4c
		LegoU32 m_unk0xd50;                        // 0xd50
		LegoFloat m_unk0xd54;                      // 0xd54
		LegoU32 m_unk0xd58;                        // 0xd58
		Field0xd5c* m_unk0xd5c[3];                 // 0xd5c
		LegoU32 m_unk0xd68;                        // 0xd68
		LegoU32 m_unk0xd6c;                        // 0xd6c
		undefined4 m_unk0xd70;                     // 0xd70
		undefined4 m_unk0xd74;                     // 0xd74
		LegoU32 m_unk0xd78;                        // 0xd78
		undefined4 m_unk0xd7c;                     // 0xd7c
		LegoU32 m_unk0xd80;                        // 0xd80
		LegoU32 m_unk0xd84;                        // 0xd84
		LegoU32 m_unk0xd88;                        // 0xd88
		union {
			Field0xd8c* m_unk0xd8c;                  // 0xd8c
			SpatialSoundInstance* m_soundD8c;        // 0xd8c
			RaceResourceManager::Resource* m_resD8c; // 0xd8c
		};
		union {
			Field0xd8c* m_unk0xd90;                  // 0xd90
			SpatialSoundInstance* m_soundD90;        // 0xd90
			RaceResourceManager::Resource* m_resD90; // 0xd90
		};
		union {
			Field0xd8c* m_unk0xd94;                  // 0xd94
			SpatialSoundInstance* m_soundD94;        // 0xd94
			RaceResourceManager::Resource* m_resD94; // 0xd94
		};
		union {
			Field0xd8c* m_unk0xd98;                  // 0xd98
			SpatialSoundInstance* m_soundD98;        // 0xd98
			RaceResourceManager::Resource* m_resD98; // 0xd98
		};
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
		union {
			Field0xd8c* m_unk0xdac;                  // 0xdac
			SpatialSoundInstance* m_soundDac;        // 0xdac
			RaceResourceManager::Resource* m_resDac; // 0xdac
		};
		undefined4 m_unk0xdb0;               // 0xdb0
		RaceCameraController* m_unk0xdb4;    // 0xdb4
		LegoU32 m_unk0xdb8;                  // 0xdb8
		LegoU16 m_unk0xdbc;                  // 0xdbc
		undefined m_unk0xdbe[0xdec - 0xdbe]; // 0xdbe
		GolString m_displayName;             // 0xdec
		GolVec3 m_unk0xdf8;                  // 0xdf8
		LegoU32 m_unk0xe04;                  // 0xe04
		RaceActionSource0x24 m_unk0xe08;     // 0xe08
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

		void FUN_0043d200();
		void FUN_0043d270();
		void FUN_0043d3f0();

		LegoEventQueue::Event* m_unk0x048; // 0x048
		RaceState* m_unk0x04c;             // 0x04c
		Racer* m_racers;                   // 0x050
		LegoU32 m_racerCount;              // 0x054
		union {
			undefined4 m_unk0x058;                // 0x058
			RaceSessionField0x27f4* m_field0x010; // 0x058
		};
		union {
			RaceResourceManager* m_unk0x05c;  // 0x05c
			Racer::Field0x004* m_soundSource; // 0x05c
		};
		RacePowerupManager* m_unk0x060;       // 0x060
		LegoEventQueue::Event* m_unk0x064[6]; // 0x064
		union {
			RaceResourceManager::Resource* m_unk0x07c; // 0x07c
			SpatialSoundInstance* m_sound;             // 0x07c
		};
		union {
			GolExport* m_unk0x080[3]; // 0x080
			Racer* m_racer080;        // 0x080
			struct {
				undefined4* m_unk0x0800;            // 0x080
				GolExport* m_golExport;             // 0x084
				TimeRaceManager* m_timeRaceManager; // 0x088
			};
		};
		GolModelEntity* m_unk0x08c[2];    // 0x08c
		GolAnimatedEntity* m_unk0x094[2]; // 0x094
		LegoU32 m_unk0x09c;               // 0x09c
		RaceRouteRecord* m_routeRecords;  // 0x0a0
		GolVec3 m_unk0x0a4[6];            // 0x0a4
		GolVec3 m_unk0x0ec[6];            // 0x0ec
		GolVec3 m_unk0x134[6];            // 0x134
		LegoU32 m_unk0x17c[6];            // 0x17c
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
		void FUN_0043a450(Racer* p_racers, LegoU32 p_racerCount);
		LegoU32 FUN_0043a480(LegoU32 p_elapsedMs);

		Racer* m_racers;                  // 0x00
		LegoU32 m_racerCount;             // 0x04
		LegoU32 m_updateDelayMs;          // 0x08
		LegoFloat m_unk0x0c;              // 0x0c
		GolTextureList* m_unk0x10;        // 0x10
		GolMaterialLibrary* m_unk0x14;    // 0x14
		LegoU8 m_lapCount;                // 0x18
		undefined m_unk0x19[0x1c - 0x19]; // 0x19
	};

	RaceState();
	~RaceState();
	void FUN_0043d120();
	void RecordBestTimes(LegoRacers::Context* p_context);
	Field0x0f0* GetUnk0x0f0() { return &m_unk0x0f0; }
	LegoEventQueue* GetEventQueue() { return &m_unk0x0f0; }
	Racer* GetRacers() { return m_unk0x0f0.m_racers; }
	Racer* GetRacer(LegoU32 p_index) { return &m_unk0x0f0.m_racers[p_index]; }
	LegoU32 GetRacerCount() const { return m_unk0x0f0.m_racerCount; }
	Racer* GetCurrentRacer() { return m_unk0x0f0.m_racer080; }
	GolMaterialLibrary* GetMaterialLibrary() const { return m_unk0x284.m_unk0x14; }
	Racer* GetUnk0x318() { return m_unk0x318[0]; }
	Racer::Field0x00c::Entry* FUN_0043d070(Racer* p_racer);
	Racer* FUN_0043c6e0(
		GolVec3* p_unk0x04,
		GolVec3* p_unk0x08,
		LegoFloat p_unk0x0c,
		LegoFloat p_unk0x10,
		LegoFloat p_unk0x14
	);
	Racer* FUN_0043c7f0(
		Racer* p_racer,
		GolVec3* p_unk0x08,
		GolVec3* p_unk0x0c,
		LegoFloat p_unk0x10,
		LegoFloat p_unk0x14,
		LegoFloat p_unk0x18
	);
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
	Racer* FUN_0043cbb0(GolVec3* p_unk0x04, LegoFloat p_unk0x08, LegoFloat p_unk0x0c);
	LegoU32 FUN_0043cda0(Racer* p_racer);
	void FUN_0043cf30(Racer* p_racer, Racer::Field0x00c::StandingsDeltaEntry* p_entries);
	const GolVec3& GetUnk0x0a4(LegoU32 p_index) const { return m_unk0x0f0.m_unk0x0a4[p_index]; }
	const GolVec3& GetUnk0x0ec(LegoU32 p_index) const { return m_unk0x0f0.m_unk0x0ec[p_index]; }
	const GolVec3& GetUnk0x134(LegoU32 p_index) const { return m_unk0x0f0.m_unk0x134[p_index]; }
	LegoU32 GetUnk0x17c(LegoU32 p_index) const { return m_unk0x0f0.m_unk0x17c[p_index]; }
	Racer::Field0x3e8::Field0x74cInstance* GetUnk0x2a0() { return &m_unk0x2a0; }

private:
	friend class RaceSession;

	enum {
		c_invalidTime = 0xffffffff,
		c_racerFlags0xd04Bit10 = 1 << 10,
		c_racerFlags0xd04Bit12 = 1 << 12,
		c_racerProgressEntryCount = 6,
	};

	static RacerProgressEntry g_racerProgressEntries[c_racerProgressEntryCount];

	// SIZE 0x44
	class Field0x3b190Params0x04 {
	public:
		LegoU32 m_racerCount;                               // 0x00
		LegoRacers::Context::PlayerSetupSlot* m_unk0x04[6]; // 0x04
		RaceRouteRecord* m_routeRecords;                    // 0x1c
		Racer::Field0x00c::Entry* m_unk0x20[6];             // 0x20
		TimeRaceManager* m_timeRaceManager;                 // 0x38
		undefined4 m_unk0x3c;                               // 0x3c
		LegoU8 m_lapCount;                                  // 0x40
		undefined m_unk0x41[0x44 - 0x41];                   // 0x41
	};

	// SIZE 0x40
	class Field0x3b190Params0x08 {
	public:
		union {
			Racer::Field0x371c0 m_field0x371c0; // 0x00
			struct {
				GolD3DRenderDevice* m_renderer;            // 0x00
				GolExport* m_golExport;                    // 0x04
				GolCollidableEntity* m_unk0x08;            // 0x08
				GolBoundedEntity* m_unk0x0c;               // 0x0c
				GolBoundedEntity* m_unk0x10;               // 0x10
				RaceResourceManager* m_resourceMgr;        // 0x14
				RacePowerupManager* m_unk0x18;             // 0x18
				CutsceneAnimation* m_unk0x1c;              // 0x1c
				CutsceneAnimation* m_unk0x20;              // 0x20
				RaceSessionField0x27d4* m_unk0x24;         // 0x24
				void* m_unk0x28;                           // 0x28
				void* m_unk0x2c;                           // 0x2c
				LegoBool32 m_unk0x30;                      // 0x30
				Racer::Field0x00c::Entry* m_unk0x34;       // 0x34
				RaceSessionField0x27f4* m_racerField0x010; // 0x38
				LegoU32 m_flags0x3c;                       // 0x3c
			};
		};
	};

	void FUN_0043b190(Field0x3b190Params0x04* p_unk0x04, Field0x3b190Params0x08* p_unk0x08, LegoBool32 p_binary);
	void FUN_0043b480(
		LegoRacers::Context::PlayerSetupSlot* p_unk0x04,
		Field0x3b190Params0x08* p_unk0x08,
		LegoU32 p_unk0x0c,
		undefined4 p_unk0x10
	);
	void FUN_0043bc10(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
	void FUN_0043be60(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
	void FUN_0043bff0(GolD3DRenderDevice* p_renderer);
	void FUN_0043c030(LegoU32 p_elapsedMs);
	void FUN_0043c1b0();
	void FUN_0043c6a0(GolCamera* p_camera);
	void FUN_0043ccb0();
	void FUN_0043cd30(GolRenderDevice* p_renderer, Racer* p_racer);
	void SetUnk0x080(Racer* p_racer) { m_unk0x0f0.m_racer080 = p_racer; }
	void SetUnk0x284Unk0x0c(LegoFloat p_unk0x0c) { m_unk0x284.m_unk0x0c = p_unk0x0c; }
	void Reset();
	void Destroy();

	DriverCosmeticTable m_unk0x000;                   // 0x000
	ChampionDefinitionList m_unk0x080;                // 0x080
	ChassisModelTable m_unk0x0b4;                     // 0x0b4
	Field0x0f0 m_unk0x0f0;                            // 0x0f0
	Field0x284 m_unk0x284;                            // 0x284
	Racer::Field0x3e8::Field0x74cInstance m_unk0x2a0; // 0x2a0
	Racer* m_unk0x318[2];                             // 0x318
};

#endif // RACESTATE_H
