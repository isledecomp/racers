#ifndef RACEPOWERUPMANAGER_H
#define RACEPOWERUPMANAGER_H

#include "audio/soundnode.h"
#include "core/gol.h"
#include "decomp.h"
#include "gdbmodelindexarray0xc.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "material/materialtable0x0c.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/raceactionsource0x24.h"
#include "race/raceresourcemanager.h"
#include "race/racesessionfield0x27d4.h"
#include "race/racesessionfield0x27f4.h"
#include "race/racesessionfield0x32b4.h"
#include "race/racesessionfield0x6dcfield0xa8.h"
#include "race/racestate.h"
#include "race/racetrailmanager.h"
#include "scene/golbillboard.h"
#include "surface/color.h"
#include "types.h"
#include "util/legoeventqueue.h"

class CutsceneAnimation;
class DuskwindBananaRelic0x24;
class Field0x2804;
class GolCollidableEntity;
class GolD3DRenderDevice;
class GolExport;
class GolFileParser;
class GolMaterialLibrary;
class GolModelBase;
class GolRenderDevice;
class GolSceneNode;
class GolWorldDatabase;
class RaceSessionField0x32b4;
class SpatialSoundInstance;
struct CutsceneParticleRef;

// SIZE 0x19a4
class RacePowerupManager {
public:
	// VTABLE: LEGORACERS 0x004b1884
	// SIZE 0x1fc
	class PwbTxtParser : public GolTxtParser {};

	// SIZE 0x1c
	class ActionTarget {
	public:
		GolVec3 m_unk0x00; // 0x00
		GolVec3 m_unk0x0c; // 0x0c
		union {
			const LegoChar* m_materialName; // 0x18
			RaceActionSource0x24* m_source; // 0x18
		};
	};

	class Field0x050 {
	public:
		// SIZE 0x14
		class Entry {
		public:
			enum {
				c_flags0x10Bit1 = 1 << 1,
			};

			Entry();
			~Entry();
			void FUN_0045c380(GolVec3* p_unk0x04, LegoS32 p_unk0x08);

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

	// SIZE 0x14
	class ActionSetup {
	public:
		RaceState::Racer* m_racer;    // 0x00
		RaceState::Racer* m_unk0x04;  // 0x04
		Field0x050::Entry* m_unk0x08; // 0x08
		ActionTarget* m_unk0x0c;      // 0x0c
		LegoU32 m_unk0x10;            // 0x10
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
			GolExport* m_unk0x00;                // 0x00
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
			LegoFloat p_amount,
			GolVec3* p_positionResult,
			ColorRGBA* p_colorResult
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

	class Field0x18ac;

	// VTABLE: LEGORACERS 0x004b0248
	// SIZE 0xf8
	class Field0xf8 : public RaceSessionField0x6dcField0xa8 {
	public:
		Field0xf8();
		RaceSessionField0x6dcField0xa8* VTable0x10(undefined4 p_flags) override;
		LegoS32 VTable0x18(LegoU32 p_elapsedMs) override;
		void VTable0x1c(GolVec3* p_unk0x04) override;
		void FUN_00423630();
		void FUN_00423640(
			LegoU32 p_elapsedMs,
			RaceState* p_unk0x08,
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

		GolVec3 m_unk0x0a8;                        // 0x0a8
		LegoFloat m_unk0x0b4;                      // 0x0b4
		LegoFloat m_unk0x0b8;                      // 0x0b8
		LegoFloat m_unk0x0bc;                      // 0x0bc
		LegoFloat m_unk0x0c0;                      // 0x0c0
		GolVec3 m_unk0x0c4;                        // 0x0c4
		GolVec3 m_unk0x0d0;                        // 0x0d0
		GolVec3 m_unk0x0dc;                        // 0x0dc
		LegoU32 m_unk0x0e8;                        // 0x0e8
		RaceSessionField0x27f4::Entry* m_unk0x0ec; // 0x0ec
		LegoU32 m_unk0x0f0;                        // 0x0f0
		undefined4 m_unk0x0f4;                     // 0x0f4
	};

	// VTABLE: LEGORACERS 0x004b0ca8
	// SIZE 0x238
	class Field0x238 : public RaceSessionField0x6dcField0xa8 {
	public:
		// SIZE 0x20
		struct SetupParams {
			GolExport* m_unk0x00;                // 0x00
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
		RaceSessionField0x6dcField0xa8* VTable0x10(undefined4) override;
		void VTable0x14() override;
		LegoS32 VTable0x18(LegoU32 p_elapsedMs) override;
		virtual void VTable0x20(const SetupParams* p_params);    // vtable+0x20
		virtual void VTable0x24(GolD3DRenderDevice* p_renderer); // vtable+0x24

		void FUN_00444ac0(GolVec3* p_unk0x04);
		void ResetUnk0x224AndFlags0x234()
		{
			m_unk0x224 = 0.0f;
			m_unk0x234 = 0;
		}

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
		void VTable0x00(LegoEventQueue::CallbackData* p_param) override = 0; // vtable+0x00
		virtual Field0x1880* VTable0x04(undefined4) = 0;                     // vtable+0x04
		virtual void VTable0x08(LegoU32) = 0;                                // vtable+0x08
		virtual void VTable0x0c(GolD3DRenderDevice*) = 0;                    // vtable+0x0c
		virtual void VTable0x10(GolD3DRenderDevice*) = 0;                    // vtable+0x10
		virtual void VTable0x14() = 0;                                       // vtable+0x14
		virtual LegoS32 VTable0x18() = 0;                                    // vtable+0x18
		virtual void VTable0x1c() = 0;                                       // vtable+0x1c

		Field0x1880* GetNext() { return m_next; }
		LegoS32 GetUnk0x04() const { return m_unk0x004; }
		LegoU32 GetUnk0x008() const { return m_unk0x008; }
		LegoU32 GetState() const { return m_state; }
		void SetUnk0x04(LegoS32 p_unk0x04) { m_unk0x004 = p_unk0x04; }
		void SetUnk0x010(RaceState::Racer::Field0x004* p_unk0x010) { m_unk0x010 = p_unk0x010; }
		void SetNext(Field0x1880* p_next) { m_next = p_next; }
		void SetState(LegoU32 p_state) { m_state = p_state; }

	protected:
		friend class RacePowerupManager;

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
		void VTable0x00(LegoEventQueue::CallbackData* p_param) override; // vtable+0x00
		Field0x1880* VTable0x04(undefined4 p_flags) override;            // vtable+0x04
		void VTable0x08(LegoU32) override;                               // vtable+0x08
		void VTable0x0c(GolD3DRenderDevice*) override;                   // vtable+0x0c
		void VTable0x10(GolD3DRenderDevice*) override;                   // vtable+0x10
		void VTable0x14() override = 0;                                  // vtable+0x14
		LegoS32 VTable0x18() override = 0;                               // vtable+0x18
		void VTable0x1c() override;                                      // vtable+0x1c
	};

	// SIZE 0x2c
	class ResourceBase0x2c : public ResourceBase {
	public:
		enum {
			c_racerFlags0xd04Bit0 = 1 << 0,
		};

		ResourceBase0x2c();

		// SYNTHETIC: LEGORACERS 0x00451960
		// RacePowerupManager::ResourceBase0x2c::~ResourceBase0x2c

		// SYNTHETIC: LEGORACERS 0x00456300
		// RacePowerupManager::ResourceBase0x2c::`scalar deleting destructor'

		void VTable0x00(LegoEventQueue::CallbackData* p_param) override; // vtable+0x00
		void VTable0x14() override;                                      // vtable+0x14
		LegoS32 VTable0x18() override;                                   // vtable+0x18
		virtual void VTable0x20(RaceState::Racer* p_racer);              // vtable+0x20

	protected:
		void FUN_00456360(RaceState::Racer* p_racer, GolVec3* p_position, GolBoundingVolume::Field0x0c* p_record);

		RaceState* m_raceState0x018;        // 0x018
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
		RaceSessionField0x6dcField0xa8* m_unk0x018; // 0x018
		union {
			GolExport** m_unk0x01c;           // 0x01c
			RacePowerupManager* m_owner0x01c; // 0x01c
		};
		RaceSessionField0x32b4* m_unk0x020; // 0x020
		RaceState::Racer* m_unk0x024;       // 0x024
		RaceState::Racer* m_unk0x028;       // 0x028
		Field0x050::Entry* m_unk0x02c;      // 0x02c
	};

	// VTABLE: LEGORACERS 0x004b14b0
	// SIZE 0x54
	class Field0x68 : public LegoEventQueue::Callback {
	public:
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual void VTable0x04(RaceState::Racer* p_racer) = 0;         // vtable+0x04
		virtual ~Field0x68();                                           // vtable+0x08
		virtual void VTable0x0c();                                      // vtable+0x0c
		virtual void VTable0x10(GolD3DRenderDevice* p_renderer);        // vtable+0x10
		virtual void VTable0x14(GolD3DRenderDevice* p_renderer);        // vtable+0x14

		// SYNTHETIC: LEGORACERS 0x00453940
		// RacePowerupManager::Field0x68::`scalar deleting destructor'

		Field0x68();
		void FUN_004539b0(
			RacePowerupManager* p_owner,
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
		GolWorldEntity* GetUnk0x08() { return &m_unk0x08; }

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

		RacePowerupManager* m_unk0x04;           // 0x04
		GolWorldEntity m_unk0x08;                // 0x08
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
		// RacePowerupManager::Field0x68Field0x028::`vector deleting destructor'

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
			RacePowerupManager* p_unk0x04,
			RaceState* p_raceState,
			RaceSessionField0x32b4* p_unk0x0c,
			undefined4 p_unk0x10,
			GolExport* p_unk0x14,
			GolD3DRenderDevice* p_unk0x18,
			undefined4 p_unk0x1c
		);
		void FUN_004557c0();
		void FUN_004557e0();
		void FUN_00455830(
			RaceState::Racer* p_racer,
			GolAnimatedEntity* p_unk0x08,
			GolAnimatedEntity* p_unk0x0c,
			GolAnimatedEntity* p_unk0x10
		);
		void FUN_004560b0();

	private:
		friend class RacePowerupManager;

		GolVec3 m_unk0x2c;             // 0x2c
		RacePowerupManager* m_unk0x38; // 0x38
		GolAnimatedEntity* m_unk0x3c;  // 0x3c
		GolAnimatedEntity* m_unk0x40;  // 0x40
		GolAnimatedEntity* m_unk0x44;  // 0x44
		GolWorldEntity m_unk0x48;      // 0x48
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
			c_randomTableMask = 0x3ff,
			c_randomPhaseRange = 0x274,
			c_randomBubbleOffsetRange = 7,
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
			RacePowerupManager* p_unk0x04,
			RaceState* p_raceState,
			GolCollidableEntity* p_unk0x0c,
			RaceSessionField0x32b4* p_unk0x10,
			CutsceneAnimation* p_unk0x14,
			GolRenderDevice* p_renderer,
			GolExport* p_export
		);
		void FUN_00457170();
		void FUN_00457230(RaceState::Racer* p_racer);

	private:
		RacePowerupManager* m_unk0x02c; // 0x02c
		GolWorldEntity m_unk0x030;      // 0x030
		union {
			SpatialSoundInstance* m_unk0x058;          // 0x058
			RaceResourceManager::Resource* m_sound058; // 0x058
		};
		CutsceneAnimation* m_unk0x05c;                       // 0x05c
		CutsceneParticleRef* m_unk0x060;                     // 0x060
		RaceSessionField0x27d4::Item::Field0x004 m_unk0x064; // 0x064
		GolBillboard::Field0x2c m_unk0x180;                  // 0x180
		GolCollidableEntity* m_unk0x18c;                     // 0x18c
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
			c_timer0x0bb8 = 0x0bb8,
			c_timer0x1388 = 0x1388,
			c_sound0x05 = 0x05,
			c_sound0x11 = 0x11,
			c_randomTableMask = 0x3ff,
			c_randomOffsetRange = 13,
			c_randomOffsetCenter = 6,
		};

		Field0x1898();
		~Field0x1898();
		Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
		void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
		void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
		void VTable0x14() override;                               // vtable+0x14
		void VTable0x1c() override;                               // vtable+0x1c
		void FUN_00452ee0(
			RaceState* p_raceState,
			RaceSessionField0x32b4* p_unk0x08,
			RacePowerupManager* p_unk0x0c,
			undefined4 p_unk0x10,
			GolModelEntity* p_model
		);
		void FUN_00452eb0();
		LegoU32 FUN_00452f60(RaceState::Racer* p_racer, RaceState::Racer* p_unk0x08);

	private:
		GolModelEntity m_unk0x02c;                 // 0x02c
		RaceSessionField0x6dcField0xa8 m_unk0x0bc; // 0x0bc
		RacePowerupManager* m_unk0x164;            // 0x164
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
		void FUN_00452530(RaceState* p_raceState, RaceSessionField0x32b4* p_unk0x08, RacePowerupManager* p_unk0x0c);
		void FUN_004524f0();
		void FUN_00452510();
		void FUN_00452550(
			RaceState::Racer* p_racer,
			GolAnimatedEntity* p_unk0x08,
			GolAnimatedEntity* p_unk0x0c,
			GolAnimatedEntity* p_unk0x10,
			ActionTarget* p_unk0x14
		);

	private:
		RacePowerupManager* m_unk0x2c; // 0x2c
		GolAnimatedEntity* m_unk0x30;  // 0x30
		GolAnimatedEntity* m_unk0x34;  // 0x34
		GolAnimatedEntity* m_unk0x38;  // 0x38
		GolWorldEntity m_unk0x3c;      // 0x3c
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
		void FUN_004519d0(GolExport** p_unk0x04, RaceSessionField0x32b4* p_unk0x08);
		void FUN_00451a10();
		LegoU32 FUN_00451a50(ActionSetup* p_unk0x04);

	private:
		// SIZE 0x24
		class Field0x0e0 {
		public:
			undefined m_unk0x000[0x008 - 0x000]; // 0x000
			GolVec3 m_unk0x008;                  // 0x008
			GolVec3 m_unk0x014;                  // 0x014
			LegoU32 m_unk0x020;                  // 0x020
		};

		RaceSessionField0x6dcField0xa8 m_unk0x030; // 0x030
		GolBillboard* m_unk0x0d8;                  // 0x0d8
		CutsceneParticleRef* m_unk0x0dc;           // 0x0dc
		union {
			Field0x0e0* m_unk0x0e0;              // 0x0e0
			const LegoChar* m_materialName0x0e0; // 0x0e0
		};
		union {
			CutsceneParticleRef* m_unk0x0e4;           // 0x0e4
			RaceTrailManager::Trail* m_trailItem0x0e4; // 0x0e4
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
		void FUN_00453cd0(RacePowerupManager* p_unk0x04, RaceSessionField0x32b4* p_unk0x08, undefined4 p_unk0x0c);
		void FUN_00453d90();
		LegoU32 FUN_00453de0(
			GolModelEntity* p_unk0x04,
			RaceState::Racer* p_racer,
			RaceState::Racer* p_unk0x0c,
			Field0x050::Entry* p_unk0x10,
			MabMaterialAnimationItem0x18* p_unk0x14,
			LegoU32 p_unk0x18
		);
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
			c_racerField0x018Flags0x384Bit1 = 1 << 1,
			c_timer0x0032 = 0x0032,
			c_timer0x0064 = 0x0064,
			c_timer0x01f4 = 0x01f4,
			c_timer0x00c8 = 0x00c8,
			c_timer0x012c = 0x012c,
			c_timer0x03e8 = 0x03e8,
			c_timer0x1b58 = 0x1b58,
			c_sound0x42 = 0x42,
			c_sound0x43 = 0x43,
			c_sound0x45 = 0x45,
			c_colorOffset0xe1 = 0xe1,
			c_colorOffset0xff = 0xff,
			c_randomTableMask = 0x3ff,
			c_randomOffsetRange = 0x32,
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

		void FUN_004548f0(GolExport* p_export, RacePowerupManager* p_unk0x08);
		void FUN_00454a70();
		void FUN_00454ab0();
		void FUN_00454b20();
		void FUN_00454b90();
		void FUN_00454bb0();
		void FUN_00454cb0(RaceState::Racer* p_racer, ActionTarget* p_unk0x08);
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
			SpatialSoundInstance* m_unk0x238;                    // 0x238
			RaceResourceManager::Resource* m_soundResource0x238; // 0x238
		};
		RaceActionSource0x24* m_unk0x23c; // 0x23c
		LegoU32 m_unk0x240;               // 0x240
		CutsceneParticleRef* m_unk0x244;  // 0x244
		GolBillboard* m_unk0x248;         // 0x248
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
			c_sound0x33 = 0x33,
		};

		Field0x18ac();
		~Field0x18ac();
		Field0x1880* VTable0x04(undefined4 p_flags) override;     // vtable+0x04
		void VTable0x08(LegoU32 p_elapsedMs) override;            // vtable+0x08
		void VTable0x0c(GolD3DRenderDevice* p_renderer) override; // vtable+0x0c
		void VTable0x14() override;                               // vtable+0x14
		void VTable0x1c() override;                               // vtable+0x1c
		void VTable0x20(RaceState::Racer* p_racer) override;      // vtable+0x20
		void FUN_00456510(GolExport** p_unk0x04, RaceSessionField0x32b4* p_unk0x08);
		void FUN_00456540();
		void FUN_00456560(
			GolAnimatedEntity* p_unk0x04,
			GolAnimatedEntity* p_unk0x08,
			RaceState::Racer* p_racer,
			LegoU32 p_unk0x10
		);
		void FUN_00456680();

	private:
		Field0xf8 m_unk0x030;                // 0x030
		GolAnimatedEntity m_unk0x128;        // 0x128
		RaceTrailManager::Trail* m_unk0x21c; // 0x21c
		LegoU32 m_unk0x220;                  // 0x220
	};

	// VTABLE: LEGORACERS 0x004b1938
	// SIZE 0x2c
	class Field0x18b0 : public ResourceBase {
	public:
		enum {
			c_state0x03 = 3,
			c_state0x04 = 4,
			c_state0x06 = 6,
			c_duration0x03e8 = 0x03e8,
			c_duration0x0fa0 = 0x0fa0,
			c_duration0x1770 = 0x1770,
			c_duration0x1f40 = 0x1f40,
			c_duration0x2710 = 0x2710,
			c_sound0x35 = 0x35,
			c_sound0x3b = 0x3b,
			c_sound0x4c = 0x4c,
			c_sound0x4d = 0x4d,
			c_sound0x4e = 0x4e,
			c_racerFlags0xd04Bit0 = 1 << 0,
			c_racerFlags0xd04Bit11 = 1 << 11,
		};

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
		void FUN_0045bcd0(RacePowerupManager* p_unk0x04);
		void FUN_0045bd10();
		void FUN_0045bd30(
			RaceState::Racer* p_racer,
			LegoU32 p_unk0x08,
			GolAnimatedEntity* p_unk0x0c,
			GolAnimatedEntity* p_unk0x10
		);

	private:
		friend class RacePowerupManager;

		union {
			Field0x18* m_unk0x18;            // 0x18
			GolAnimatedEntity* m_entity0x18; // 0x18
		};
		GolAnimatedEntity* m_unk0x1c;  // 0x1c
		RaceState::Racer* m_unk0x20;   // 0x20
		RacePowerupManager* m_unk0x24; // 0x24
		union {
			SpatialSoundInstance* m_unk0x28;                    // 0x28
			RaceResourceManager::Resource* m_soundResource0x28; // 0x28
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
			c_timer0x015e = 0x015e,
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
		void FUN_0045c880(RacePowerupManager* p_unk0x04, CutsceneAnimation* p_unk0x08);
		void FUN_0045c8b0();
		void FUN_0045c8d0();
		void FUN_0045c8f0(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
		void FUN_0045cd70();
		void FUN_0045cf90();

	private:
		friend class RacePowerupManager;

		RaceState::Racer* m_unk0x018;   // 0x18
		RacePowerupManager* m_unk0x1c;  // 0x1c
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
			RacePowerupManager* m_unk0x00; // 0x00
			LegoFloat m_unk0x04;           // 0x04
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
		LegoU32 FUN_0045d560(RaceState::Racer* p_racer, GolModelEntity* p_unk0x08, ActionTarget* p_unk0x0c);
		void FUN_0045e080(GolWorldEntity* p_entity);

	private:
		friend class RacePowerupManager;

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
			c_racerFlags0xd04Bit4 = 1 << 4,
			c_racerFlags0xd04Bit21 = 0x00200000,
		};

		GolModelEntity m_unk0x018;      // 0x018
		RaceState::Racer* m_unk0x0a8;   // 0x0a8
		RacePowerupManager* m_unk0x0ac; // 0x0ac
		LegoFloat m_unk0x0b0;           // 0x0b0
		SoundVector m_unk0x0b4;         // 0x0b4
		GolVec3 m_unk0x0c0;             // 0x0c0
		GolVec3 m_unk0x0cc;             // 0x0cc
		LegoBool32 m_unk0x0d8;          // 0x0d8
		LegoBool32 m_unk0x0dc;          // 0x0dc
		LegoBool32 m_unk0x0e0;          // 0x0e0
	};

	// VTABLE: LEGORACERS 0x004b0164
	// SIZE 0x270
	class Field0x270 : public LegoEventQueue::Callback {
	public:
		// SIZE 0x48
		struct Params {
			GolExport* m_unk0x00;                    // 0x00
			GolCollidableEntity* m_unk0x04;          // 0x04
			GolModelEntity* m_unk0x08;               // 0x08
			DuskwindBananaRelic0x24* m_unk0x0c;      // 0x0c
			DuskwindBananaRelic0x24* m_unk0x10;      // 0x10
			DuskwindBananaRelic0x24* m_unk0x14;      // 0x14
			LegoEventQueue* m_unk0x18;               // 0x18
			RacePowerupManager* m_unk0x1c;           // 0x1c
			MabMaterialAnimationItem0x18* m_unk0x20; // 0x20
			LegoU32 m_unk0x24;                       // 0x24
			CutsceneAnimation* m_unk0x28;            // 0x28
			LegoU32 m_unk0x2c;                       // 0x2c
			LegoU32 m_unk0x30;                       // 0x30
			LegoFloat m_unk0x34;                     // 0x34
			LegoFloat m_unk0x38;                     // 0x38
			LegoFloat m_unk0x3c;                     // 0x3c
			LegoFloat m_unk0x40;                     // 0x40
			LegoU32 m_unk0x44;                       // 0x44
		};

		Field0x270();
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual Field0x270* VTable0x04(undefined4 p_flags);             // vtable+0x04

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

		LegoS32 m_unk0x04;                                   // 0x004
		GolWorldEntity m_unk0x008;                           // 0x008
		GolExport* m_unk0x030;                               // 0x030
		GolModelEntity m_unk0x034;                           // 0x034
		GolBillboard* m_unk0x0c4;                            // 0x0c4
		MabMaterialAnimationItem0x18 m_unk0x0c8;             // 0x0c8
		LegoU32 m_unk0x0e0;                                  // 0x0e0
		RaceSessionField0x27d4::Item::Field0x004 m_unk0x0e4; // 0x0e4
		GolCollidableEntity* m_unk0x200;                     // 0x200
		MaterialTable0x0c m_unk0x204;                        // 0x204
		DuskwindBananaRelic0x24* m_unk0x210;                 // 0x210
		DuskwindBananaRelic0x24* m_unk0x214;                 // 0x214
		LegoEventQueue* m_unk0x218;                          // 0x218
		RaceState::Racer* m_unk0x21c;                        // 0x21c
		LegoEventQueue::Event* m_unk0x220;                   // 0x220
		RacePowerupManager* m_unk0x224;                      // 0x224
		CutsceneAnimation* m_unk0x228;                       // 0x228
		LegoU32 m_unk0x22c;                                  // 0x22c
		LegoU32 m_unk0x230;                                  // 0x230
		LegoU32 m_unk0x234;                                  // 0x234
		LegoU32 m_unk0x238;                                  // 0x238
		LegoFloat m_unk0x23c;                                // 0x23c
		LegoFloat m_unk0x240;                                // 0x240
		LegoFloat m_unk0x244;                                // 0x244
		LegoFloat m_unk0x248;                                // 0x248
		LegoFloat m_unk0x24c;                                // 0x24c
		LegoFloat m_unk0x250;                                // 0x250
		LegoFloat m_unk0x254;                                // 0x254
		LegoFloat m_unk0x258;                                // 0x258
		LegoFloat m_unk0x25c;                                // 0x25c
		LegoFloat m_unk0x260;                                // 0x260
		LegoFloat m_unk0x264;                                // 0x264
		LegoS32 m_unk0x268;                                  // 0x268
		Field0x270* m_next;                                  // 0x26c
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
		friend class RacePowerupManager;

		void FUN_00451750(RacePowerupManager* p_unk0x04, GolD3DRenderDevice* p_renderer);
		void FUN_004517c0(const GolVec3* p_position, const GolVec3* p_direction, RaceState::Racer* p_racer);

		Entry m_entries[5];              // 0x00
		GolAnimatedEntity* m_unk0x64[4]; // 0x64
		RacePowerupManager* m_unk0x74;   // 0x74
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
	class Field0x1958Resource : public RaceResourceManager::Resource {
	public:
		void SetUnk0x18(const GolVec3& p_unk0x18) { m_unk0x18 = p_unk0x18; }
		void SetUnk0x24(const GolVec3& p_unk0x24) { m_unk0x24 = p_unk0x24; }

	private:
		friend class RacePowerupManager;

		undefined m_unk0x04[0x18 - 0x04]; // 0x04
		GolVec3 m_unk0x18;                // 0x18
		GolVec3 m_unk0x24;                // 0x24
	};

	RacePowerupManager();
	~RacePowerupManager();
	void FUN_0045a490(LegoU32 p_elapsedMs);
	void FUN_0045a7b0(LegoBool32 p_unk0x04);
	void FUN_0045a8a0();
	void FUN_0045a950(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045a9b0(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045b030(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045b1e0(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	LegoU32 FUN_0045b260(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045b470(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer);
	void FUN_0045b4d0(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer);
	void FUN_0045b4f0(const GolVec3* p_position, undefined4 p_unk0x08, RaceState::Racer* p_racer);
	void FUN_0045b550(const GolVec3* p_unk0x04, const GolVec3* p_position, RaceState::Racer* p_racer);
	void FUN_0045b740(RaceState::Racer* p_racer);
	void FUN_0045b900();
	LegoBool32 FUN_0045b9a0(RaceState::Racer* p_racer);
	void FUN_0045bb30();
	LegoU32 GetUnk0x187c() const { return m_unk0x187c; }
	undefined4 GetUnk0x19a0() const { return m_unk0x19a0; }
	GolBillboard::Field0x2c* GetBillboardMaterialTable() { return &m_unk0x008; }
	MabMaterialAnimationItem0x8* GetMaterialAnimationItems() const { return m_unk0x014.GetUnk0x04(); }
	LegoU32 GetMaterialAnimationItemCount() const { return m_unk0x014.GetUnk0x08(); }
	MabMaterialAnimationItem0x18* GetMaterialAnimationItems0x18() const { return m_unk0x014.GetUnk0x0c(); }
	RaceState* GetRaceState() { return m_raceState; }
	void SetUnk0x1998(ActionTarget* p_unk0x1998) { m_unk0x1998 = p_unk0x1998; }

private:
	// SIZE 0x3c
	struct Params {
		GolExport* m_unk0x00;                    // 0x00
		GolD3DRenderDevice* m_renderer;          // 0x04
		RaceState* m_raceState;                  // 0x08
		GolCollidableEntity* m_unk0x0c;          // 0x0c
		GolBoundedEntity* m_unk0x10;             // 0x10
		RaceSessionField0x32b4* m_unk0x14;       // 0x14
		RaceState::Racer::Field0x004* m_unk0x18; // 0x18
		CutsceneAnimation* m_unk0x1c;            // 0x1c
		RaceTrailManager* m_trailManager;        // 0x20
		void* m_unk0x24;                         // 0x24
		MenuAnimationList* m_unk0x28;            // 0x28
		GolWorldDatabase* m_unk0x2c;             // 0x2c
		Field0x050* m_unk0x30;                   // 0x30
		LegoFloat m_unk0x34;                     // 0x34
		undefined4 m_unk0x38;                    // 0x38
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
	LegoU32 FUN_0045aa30(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	LegoU32 FUN_0045ab50(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045ac80(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045ace0(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	LegoU32 FUN_0045ad30(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045adf0(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045aeb0(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	void FUN_0045af80(RaceState::Racer* p_racer, LegoU32 p_unk0x08);
	Field0x1880* FUN_0045b2e0(
		LegoU32 p_unk0x04,
		LegoU32 p_unk0x08,
		LegoS32 p_unk0x0c,
		LegoS32 p_unk0x10,
		LegoS32 p_unk0x14
	);
	void FUN_0045b640(RaceState::Racer* p_racer);
	void FUN_0045b690(RaceState::Racer* p_racer);
	void FUN_0045b6f0(RaceState::Racer* p_racer);
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

	GolExport* m_unk0x000;                    // 0x000
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
	RaceTrailManager* m_trailManager;       // 0x044
	void* m_unk0x048;                       // 0x048
	MenuAnimationList* m_unk0x04c;          // 0x04c
	Field0x050* m_unk0x050;                 // 0x050
	LegoFloat m_unk0x054;                   // 0x054
	undefined4 m_unk0x058;                  // 0x058
	GolWorldDatabase* m_unk0x05c;           // 0x05c
	GolWorldDatabase* m_unk0x060;           // 0x060
	GolWorldDatabase* m_unk0x064;           // 0x064
	RaceSessionField0x32b4* m_unk0x068;     // 0x068
	GolCollidableEntity* m_unk0x06c;        // 0x06c
	GolBoundedEntity* m_unk0x070;           // 0x070
	RaceState* m_raceState;                 // 0x074
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
		Field0x1958Resource* m_unk0x1958;                // 0x1958
		SpatialSoundInstance* m_sound0x1958;             // 0x1958
		RaceResourceManager::Resource* m_resource0x1958; // 0x1958
	};
	union {
		Field0x1958Resource* m_unk0x195c;                // 0x195c
		SpatialSoundInstance* m_sound0x195c;             // 0x195c
		RaceResourceManager::Resource* m_resource0x195c; // 0x195c
	};
	union {
		Field0x1958Resource* m_unk0x1960;                // 0x1960
		SpatialSoundInstance* m_sound0x1960;             // 0x1960
		RaceResourceManager::Resource* m_resource0x1960; // 0x1960
	};
	union {
		Field0x1958Resource* m_unk0x1964;                // 0x1964
		SpatialSoundInstance* m_sound0x1964;             // 0x1964
		RaceResourceManager::Resource* m_resource0x1964; // 0x1964
	};
	GolAnimatedEntity* m_unk0x1968;          // 0x1968
	GolAnimatedEntity* m_unk0x196c;          // 0x196c
	GolAnimatedEntity* m_unk0x1970;          // 0x1970
	GolAnimatedEntity* m_unk0x1974;          // 0x1974
	DuskwindBananaRelic0x24* m_unk0x1978[8]; // 0x1978
	ActionTarget* m_unk0x1998;               // 0x1998
	LegoFloat m_unk0x199c;                   // 0x199c
	undefined4 m_unk0x19a0;                  // 0x19a0
};

// SIZE 0x68
class RaceState::Racer::Field0xd5c : public RacePowerupManager::Field0x68 {
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
class RacePowerupManager::Field0x68Field0x02c : public RaceState::Racer::Field0xd5c {
public:
	Field0x68Field0x02c();
	~Field0x68Field0x02c() override;
	void VTable0x04(RaceState::Racer* p_racer) override;
	void VTable0x0c() override;

	// SYNTHETIC: LEGORACERS 0x00459090
	// RacePowerupManager::Field0x68Field0x02c::`vector deleting destructor'

	void FUN_00453610();
	void FUN_00453620();
	void FUN_00453690(LegoU32 p_elapsedMs);
};

#endif // RACEPOWERUPMANAGER_H
