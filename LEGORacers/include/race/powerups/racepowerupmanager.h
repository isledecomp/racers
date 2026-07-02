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
#include "race/powerups/powerupprojectile.h"
#include "race/raceactionsource0x24.h"
#include "race/raceresourcemanager.h"
#include "race/racesessionfield0x27d4.h"
#include "race/racesessionfield0x27f4.h"
#include "race/racesessionfield0x32b4.h"
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
	class PwbTxtParser : public GolTxtParser {
	public:
		// .pwb token meanings
		enum {
			e_colorBricks = 0x27,
			e_position = 0x28,
			e_colorRed = 0x2a,
			e_colorYellow = 0x2b,
			e_colorBlue = 0x2c,
			e_colorGreen = 0x2d,
			e_respawnMs = 0x2e,
			e_whiteBricks = 0x2f,
		};
	};

	// Brick color codes (PWB color tokens map to these; GetBrickColor returns them)
	enum {
		c_brickColorRed = 1,
		c_brickColorBlue = 2,
		c_brickColorGreen = 3,
		c_brickColorYellow = 4,
	};

	// SIZE 0x1c
	class ActionTarget {
	public:
		GolVec3 m_position;  // 0x00
		GolVec3 m_direction; // 0x0c
		union {
			const LegoChar* m_materialName; // 0x18
			RaceActionSource0x24* m_source; // 0x18
		};
	};

	class TargetPointList {
	public:
		// SIZE 0x14
		class Entry {
		public:
			enum {
				c_flagEnabled = 1 << 1,
			};

			Entry();
			~Entry();
			void Set(GolVec3* p_position, LegoS32 p_index);

			GolVec3 m_position;               // 0x00
			LegoS32 m_index;                  // 0x0c
			LegoU8 m_flags0x10;               // 0x10
			undefined m_unk0x11[0x14 - 0x11]; // 0x11
		};

		Entry* FindTargetInCone(
			GolVec3* p_position,
			GolVec3* p_direction,
			LegoFloat p_minDistanceSquared,
			LegoFloat p_maxDistanceSquared,
			LegoFloat p_coneCosine
		);

		Entry* m_entries; // 0x00
		LegoS32 m_count;  // 0x04
	};

	// SIZE 0x14
	class ActionSetup {
	public:
		RaceState::Racer* m_racer;             // 0x00
		RaceState::Racer* m_targetRacer;       // 0x04
		TargetPointList::Entry* m_targetPoint; // 0x08
		ActionTarget* m_aimTarget;             // 0x0c
		LegoU32 m_initialTimerMs;              // 0x10
	};

	// VTABLE: LEGORACERS 0x004b47a8
	// SIZE 0x98
	class BeamEntity : public GolModelEntity {
	public:
		BeamEntity();
		~BeamEntity();
		BeamEntity* Destroy(undefined4 p_flags);
		void VTable0x1c(GolRenderDevice& p_renderer) override; // vtable+0x1c
		void Initialize(
			GolModelBase* p_model,
			GolSceneNode* p_sceneNode,
			undefined4 p_faceCamera,
			LegoFloat p_modelDistance
		);
		void VTable0x54() override;
		GolSceneNode* VTable0x58(undefined4) override; // vtable+0x58

	private:
		GolSceneNode* m_sceneNode; // 0x90
		undefined4 m_faceCamera;   // 0x94
	};

	// SIZE 0x170
	class BeamMesh {
	public:
		enum {
			c_flagVisible = 1 << 0,
			c_flagUseSegmentOffsets = 1 << 1,
			c_flagSectionAttached = 1 << 2,
			c_groupTriangleRun = 0x20000000,
			c_groupBegin = 0x80000000,
			c_groupAttachSection = 0xa0000000,
			c_groupClose = 0xc0000000
		};

		// SIZE 0x74
		struct SetupParams {
			GolExport* m_golExport;              // 0x00
			GolRenderDevice* m_renderer;         // 0x04
			DuskwindBananaRelic0x24* m_material; // 0x08
			LegoU32 m_sectionCount;              // 0x0c
			LegoU32 m_segmentCount;              // 0x10
			LegoU32 m_ringQuadCount;             // 0x14
			GolVec3 m_ringVertices[3];           // 0x18
			undefined4 m_unk0x3c[6];             // 0x3c
			LegoFloat m_ringTextureXs[5];        // 0x54
			LegoU32 m_textureColumnCount;        // 0x68
			LegoFloat m_modelDistance;           // 0x6c
			undefined4 m_faceCamera;             // 0x70
		};

		BeamMesh();
		~BeamMesh();
		void Reset();
		void Initialize(const SetupParams* p_params);
		void Destroy();
		void Begin(const GolVec3* p_position, const GolVec3* p_direction);
		void AdvanceSection(const GolVec3* p_position);
		void AppendPoint(const GolVec3* p_position);
		void Finish();
		void EmitRing(
			const GolVec3* p_position,
			const ColorRGBA* p_color,
			LegoU32 p_textureColumn,
			LegoU32 p_offsetIndex
		);
		void EmitQuads();
		void FlushWindow();
		void FlushRuns();
		void SetColors(
			const ColorRGBA* p_baseColor,
			const ColorRGBA* p_secondaryColor,
			const ColorRGBA* p_tertiaryColor
		);
		void Draw(GolD3DRenderDevice* p_renderer);
		void AppendSpan(const GolVec3* p_position, LegoFloat p_amount);
		void Interpolate(
			const GolVec3* p_fromPosition,
			const GolVec3* p_toPosition,
			const ColorRGBA* p_fromColor,
			const ColorRGBA* p_toColor,
			LegoFloat p_amount,
			GolVec3* p_positionResult,
			ColorRGBA* p_colorResult
		);
		void SetSegmentOffsets(const GolVec3* p_offsets);

	private:
		GolExport* m_golExport;                    // 0x000
		GolModelBase* m_model;                     // 0x004
		GdbVertexArray0xc* m_vertices;             // 0x008
		GdbModelIndexArray0xc::Indices* m_indices; // 0x00c
		GolSceneNode* m_sceneNode;                 // 0x010
		DuskwindBananaRelic0x24* m_material;       // 0x014
		BeamEntity m_entity;                       // 0x018
		LegoS32 m_windowBaseVertex;                // 0x0b0
		LegoS32 m_ringVertexIndex;                 // 0x0b4
		LegoS32 m_previousRingVertexIndex;         // 0x0b8
		LegoU32 m_vertexCursor;                    // 0x0bc
		LegoU32 m_runStartVertex;                  // 0x0c0
		LegoU32 m_runStartIndex;                   // 0x0c4
		LegoU32 m_indexCursor;                     // 0x0c8
		LegoU32 m_groupCursor;                     // 0x0cc
		LegoU32 m_sectionIndex;                    // 0x0d0
		LegoU32 m_textureColumn;                   // 0x0d4
		LegoFloat m_segmentStep;                   // 0x0d8
		LegoU32 m_sectionCount;                    // 0x0dc
		LegoU32 m_segmentCount;                    // 0x0e0
		LegoU32 m_ringQuadCount;                   // 0x0e4
		LegoU32 m_ringVertexCount;                 // 0x0e8
		GolVec3 m_ringVertices[5];                 // 0x0ec
		LegoFloat m_ringTextureXs[5];              // 0x128
		LegoU32 m_textureColumnCount;              // 0x13c
		LegoU32 m_flags;                           // 0x140
		const GolVec3* m_segmentOffsets;           // 0x144
		GolVec3 m_startPosition;                   // 0x148
		GolVec3 m_lastPosition;                    // 0x154
		ColorRGBA m_baseColor;                     // 0x160
		ColorRGBA m_secondaryColor;                // 0x164
		ColorRGBA m_tertiaryColor;                 // 0x168
		undefined4 m_vertexCapacity;               // 0x16c
	};

	class HomingMissileAction;

	// VTABLE: LEGORACERS 0x004b0248
	// SIZE 0xf8
	class HomingProjectile : public PowerupProjectile {
	public:
		HomingProjectile();
		PowerupProjectile* Destroy(undefined4 p_flags) override;
		LegoS32 Update(LegoU32 p_elapsedMs) override;
		void GetVelocity(GolVec3* p_velocity) override;
		void Destruct();
		void UpdateTargeting(
			LegoU32 p_elapsedMs,
			RaceState* p_raceState,
			LegoFloat p_minDistanceSquared,
			LegoFloat p_maxDistanceSquared,
			LegoFloat p_coneCosine
		);
		void StartHoming();
		void ApplySpiral(LegoFloat p_elapsedSeconds, GolVec3* p_direction, GolVec3* p_position);

	protected:
		friend class HomingMissileAction;

		enum {
			c_racerFlags0xd04InvalidTargetMask = 0x11,
			c_racerFlags0xaa8Bit7 = 1 << 7,
			c_targetRefreshMs = 1000,
		};

		GolVec3 m_position;                         // 0x0a8
		LegoFloat m_spiralAmplitude;                // 0x0b4
		LegoFloat m_maxSpiralAmplitude;             // 0x0b8
		LegoFloat m_spiralAngle;                    // 0x0bc
		LegoFloat m_spiralRate;                     // 0x0c0
		GolVec3 m_velocity;                         // 0x0c4
		GolVec3 m_direction;                        // 0x0d0
		GolVec3 m_waypointPosition;                 // 0x0dc
		LegoU32 m_hasWaypoint;                      // 0x0e8
		RaceSessionField0x27f4::Entry* m_pathEntry; // 0x0ec
		LegoU32 m_retargetTimerMs;                  // 0x0f0
		undefined4 m_unk0x0f4;                      // 0x0f4
	};

	// VTABLE: LEGORACERS 0x004b0ca8
	// SIZE 0x238
	class TetherProjectile : public PowerupProjectile {
	public:
		// SIZE 0x20
		struct SetupParams {
			GolExport* m_golExport;              // 0x00
			LegoFloat m_attachHeight;            // 0x04
			LegoFloat m_ropeThickness;           // 0x08
			LegoFloat m_waveAmplitude;           // 0x0c
			ColorRGBA m_baseColor;               // 0x10
			ColorRGBA m_secondaryColor;          // 0x14
			ColorRGBA m_tertiaryColor;           // 0x18
			DuskwindBananaRelic0x24* m_material; // 0x1c
		};

		TetherProjectile();
		~TetherProjectile();
		PowerupProjectile* Destroy(undefined4) override;
		void Deactivate() override;
		LegoS32 Update(LegoU32 p_elapsedMs) override;
		virtual void Initialize(const SetupParams* p_params); // vtable+0x20
		virtual void Draw(GolD3DRenderDevice* p_renderer);    // vtable+0x24

		void Release(GolVec3* p_position);
		void ResetRope()
		{
			m_tension = 0.0f;
			m_flags = 0;
		}

	private:
		enum {
			c_flagSnapped = 1 << 0,
			c_flagReleased = 1 << 1,
		};

		void RebuildBeam(const GolVec3* p_position, LegoFloat p_elapsedMs, LegoFloat p_amount);
		LegoS32 UpdateReleased(LegoU32 p_elapsedMs);
		LegoS32 UpdateAttached(LegoU32 p_elapsedMs);

		BeamMesh m_beam;                  // 0x0a8
		LegoFloat m_attachHeight;         // 0x218
		LegoFloat m_waveAmplitude;        // 0x21c
		LegoFloat m_currentWaveAmplitude; // 0x220
		LegoFloat m_tension;              // 0x224
		GolVec3 m_endPosition;            // 0x228
		LegoU32 m_flags;                  // 0x234
	};

	// SIZE 0x18
	class PowerupAction : public LegoEventQueue::Callback {
	public:
		void VTable0x00(LegoEventQueue::CallbackData* p_param) override = 0; // vtable+0x00
		virtual PowerupAction* Destroy(undefined4 p_flags) = 0;              // vtable+0x04
		virtual void Update(LegoU32 p_elapsedMs) = 0;                        // vtable+0x08
		virtual void Draw(GolD3DRenderDevice*) = 0;                          // vtable+0x0c
		virtual void DrawTransparent(GolD3DRenderDevice*) = 0;               // vtable+0x10
		virtual void AdvanceState() = 0;                                     // vtable+0x14
		virtual LegoS32 GetBrickColor() = 0;                                 // vtable+0x18
		virtual void Deactivate() = 0;                                       // vtable+0x1c

		PowerupAction* GetNext() { return m_next; }
		LegoS32 GetState() const { return m_state; }
		LegoU32 GetStateTimer() const { return m_stateTimerMs; }
		LegoU32 GetLevel() const { return m_level; }
		void SetState(LegoS32 p_state) { m_state = p_state; }
		void SetSoundSource(RaceState::Racer::Field0x004* p_soundSource) { m_soundSource = p_soundSource; }
		void SetNext(PowerupAction* p_next) { m_next = p_next; }
		void SetLevel(LegoU32 p_level) { m_level = p_level; }

	protected:
		friend class RacePowerupManager;

		LegoS32 m_state;                             // 0x004
		LegoU32 m_stateTimerMs;                      // 0x008
		PowerupAction* m_next;                       // 0x00c
		RaceState::Racer::Field0x004* m_soundSource; // 0x010
		LegoU32 m_level;                             // 0x014
	};

	// VTABLE: LEGORACERS 0x004b132c
	// SIZE 0x18
	class PowerupActionBase : public PowerupAction {
	public:
		PowerupActionBase();
		~PowerupActionBase();
		void VTable0x00(LegoEventQueue::CallbackData* p_param) override; // vtable+0x00
		PowerupAction* Destroy(undefined4 p_flags) override;             // vtable+0x04
		void Update(LegoU32) override;                                   // vtable+0x08
		void Draw(GolD3DRenderDevice*) override;                         // vtable+0x0c
		void DrawTransparent(GolD3DRenderDevice*) override;              // vtable+0x10
		void AdvanceState() override = 0;                                // vtable+0x14
		LegoS32 GetBrickColor() override = 0;                            // vtable+0x18
		void Deactivate() override;                                      // vtable+0x1c
	};

	// SIZE 0x2c
	class HazardActionBase : public PowerupActionBase {
	public:
		enum {
			c_racerFlags0xd04Bit0 = 1 << 0,
		};

		HazardActionBase();

		// SYNTHETIC: LEGORACERS 0x00451960
		// RacePowerupManager::HazardActionBase::~HazardActionBase

		// SYNTHETIC: LEGORACERS 0x00456300
		// RacePowerupManager::HazardActionBase::`scalar deleting destructor'

		void VTable0x00(LegoEventQueue::CallbackData* p_param) override; // vtable+0x00
		void AdvanceState() override;                                    // vtable+0x14
		LegoS32 GetBrickColor() override;                                // vtable+0x18
		virtual void OnHitRacer(RaceState::Racer* p_racer);              // vtable+0x20

	protected:
		void ComputeDropPosition(
			RaceState::Racer* p_racer,
			GolVec3* p_position,
			GolBoundingVolume::Field0x0c* p_record
		);

		RaceState* m_raceState0x018;              // 0x018
		LegoEventQueue::Event* m_collisionEvent;  // 0x01c
		RaceSessionField0x32b4* m_collisionWorld; // 0x020
		undefined4 m_unk0x024;                    // 0x024
		RaceState::Racer* m_ownerRacer;           // 0x028
	};

	// SIZE 0x30
	class WeaponActionBase : public PowerupActionBase {
	public:
		WeaponActionBase();
		void AdvanceState() override;                            // vtable+0x14
		LegoS32 GetBrickColor() override;                        // vtable+0x18
		virtual void OnHitRacer(RaceState::Racer* p_racer);      // vtable+0x20
		virtual void GetProjectilePosition(GolVec3* p_position); // vtable+0x24
		virtual void GetProjectileVelocity(GolVec3* p_velocity); // vtable+0x28

		GolWorldEntity* GetProjectileWorldEntity();

	protected:
		PowerupProjectile* m_activeProjectile; // 0x018
		union {
			GolExport** m_golExportPtr;       // 0x01c
			RacePowerupManager* m_owner0x01c; // 0x01c
		};
		RaceSessionField0x32b4* m_collisionWorld; // 0x020
		RaceState::Racer* m_ownerRacer;           // 0x024
		RaceState::Racer* m_targetRacer;          // 0x028
		TargetPointList::Entry* m_targetPoint;    // 0x02c
	};

	// VTABLE: LEGORACERS 0x004b14b0
	// SIZE 0x54
	class PickupBrick : public LegoEventQueue::Callback {
	public:
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual void OnTouched(RaceState::Racer* p_racer) = 0;          // vtable+0x04
		virtual ~PickupBrick();                                         // vtable+0x08
		virtual void Respawn();                                         // vtable+0x0c
		virtual void Draw(GolD3DRenderDevice* p_renderer);              // vtable+0x10
		virtual void DrawTransparent(GolD3DRenderDevice* p_renderer);   // vtable+0x14

		// SYNTHETIC: LEGORACERS 0x00453940
		// RacePowerupManager::PickupBrick::`scalar deleting destructor'

		PickupBrick();
		void Initialize(
			RacePowerupManager* p_owner,
			RaceState::Racer::Field0x004* p_soundResource,
			GolVec3* p_position,
			GolModelEntity* p_model0,
			GolModelEntity* p_model1
		);
		void Destroy();
		LegoS32 Reset();

		void SetAudible() { m_flags0x50 |= c_flagAudible; }
		void ClearAudible() { m_flags0x50 &= ~c_flagAudible; }
		void ClearVelocityX() { m_worldEntity.ClearVelocityX(); }
		GolWorldEntity* GetWorldEntity() { return &m_worldEntity; }

	protected:
		enum {
			c_stateIdle = 0,
			c_stateWait = 1,
			c_stateActive = 2,
			c_stateTransition = 3,
			c_stateInactive = 4,

			c_flagAudible = 1 << 0,
			c_flagTouched = 1 << 1,
			c_flagWasTouched = 1 << 2,
			c_flagDropped = 1 << 0,
			c_flagReturnHome = 1 << 1,
			c_racerFlags0xd04Bit4 = 1 << 4,
		};

		void Update(LegoU32 p_elapsedMs);
		void SetTouchable(LegoBool32 p_touchable);

		RacePowerupManager* m_manager;               // 0x04
		GolWorldEntity m_worldEntity;                // 0x08
		LegoFloat m_scale;                           // 0x30
		GolModelEntity* m_model;                     // 0x34
		GolModelEntity* m_blendModel;                // 0x38
		LegoU32 m_state;                             // 0x3c
		LegoU32 m_nextState;                         // 0x40
		RaceState::Racer::Field0x004* m_soundSource; // 0x44
		LegoU32 m_respawnMs;                         // 0x48
		LegoU32 m_stateTimerMs;                      // 0x4c
		LegoU8 m_flags0x50;                          // 0x50
		undefined m_unk0x51[0x54 - 0x51];            // 0x51
	};

	// SIZE 0x68
	class ColorBrick : public PickupBrick {
	public:
		enum {
			c_soundRespawn = 0x0e,
			c_soundCollect = 0x31,
			c_soundSwap = 0x48,
		};

		ColorBrick();
		~ColorBrick() override;
		void OnTouched(RaceState::Racer* p_racer) override;
		void Respawn() override;
		void Draw(GolD3DRenderDevice* p_renderer) override;
		void DrawTransparent(GolD3DRenderDevice* p_renderer) override;

		// SYNTHETIC: LEGORACERS 0x00458e20
		// RacePowerupManager::ColorBrick::`vector deleting destructor'

		void SetColor(LegoU32 p_brickColor);
		void Destroy();
		void Update(LegoU32 p_elapsedMs);
		void SetMaterials(DuskwindBananaRelic0x24* p_brickMaterial, DuskwindBananaRelic0x24* p_trailMaterial);
		void SetRespawnMs(LegoU32 p_respawnMs) { m_respawnMs = p_respawnMs; }

	private:
		DuskwindBananaRelic0x24* m_brickMaterial; // 0x54
		DuskwindBananaRelic0x24* m_trailMaterial; // 0x58
		LegoU32 m_assignedColor;                  // 0x5c
		LegoU32 m_currentColor;                   // 0x60
		LegoU32 m_nextColor;                      // 0x64
	};

	class WhiteBrick;

	// VTABLE: LEGORACERS 0x004b15fc
	// SIZE 0x84
	class MagnetAction : public HazardActionBase {
	public:
		enum {
			c_fadeDurationMs = 0x03e8,
			c_holdDurationMs = 0x0fa0,
			c_armedDurationMs = 0x4e20,
			c_soundDeploy = 0x21,
			c_soundLoop = 0x22,
			c_soundGrab = 0x23,
			c_soundRelease = 0x4a,
			c_flagVictimStopped = 1 << 0,
			c_flagVictimLifted = 1 << 1,
			c_racerFlags0xd04Bit3 = 1 << 3,
			c_racerField0xc70Flags0x014Bit0 = 1 << 0,
		};

		MagnetAction();
		~MagnetAction();
		PowerupAction* Destroy(undefined4 p_flags) override;           // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;            // vtable+0x0c
		void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
		void AdvanceState() override;                                  // vtable+0x14
		void Deactivate() override;                                    // vtable+0x1c
		void OnHitRacer(RaceState::Racer* p_racer) override;           // vtable+0x20

		void Initialize(
			RacePowerupManager* p_manager,
			RaceState* p_raceState,
			RaceSessionField0x32b4* p_collisionWorld,
			CutsceneAnimation*,
			GolExport*,
			GolD3DRenderDevice*,
			undefined4
		);
		void Destroy();
		void Reset();
		void Activate(
			RaceState::Racer* p_racer,
			GolAnimatedEntity* p_magnetModel,
			GolAnimatedEntity* p_ringModel,
			GolAnimatedEntity* p_insideModel
		);
		void Deploy();

	private:
		friend class RacePowerupManager;

		GolVec3 m_direction;               // 0x2c
		RacePowerupManager* m_manager;     // 0x38
		GolAnimatedEntity* m_magnetEntity; // 0x3c
		GolAnimatedEntity* m_ringEntity;   // 0x40
		GolAnimatedEntity* m_insideEntity; // 0x44
		GolWorldEntity m_worldEntity;      // 0x48
		union {
			SpatialSoundInstance* m_sound;                  // 0x70
			RaceResourceManager::Resource* m_soundResource; // 0x70
		};
		undefined m_unk0x74[0x78 - 0x74]; // 0x74
		RaceState::Racer* m_heldRacer;    // 0x78
		RaceState::Racer* m_pulledRacer;  // 0x7c
		LegoU8 m_flags0x80;               // 0x80
		undefined m_unk0x81[0x84 - 0x81]; // 0x81
	};

	// VTABLE: LEGORACERS 0x004b16e0
	// SIZE 0x190
	class OilSlickAction : public HazardActionBase {
	public:
		enum {
			c_stateArmed = 2,
			c_stateActive = 3,
			c_stateExpiring = 5,
			c_stateDone = 6,
			c_racerFlags0xd04Bit3 = 1 << 3,
			c_racerField0x018Flags0x384Bit1 = 1 << 1,
			c_activeDurationMs = 0x2710,
			c_soundDrop = 0x2e,
			c_soundSlip = 0x2f,
			c_soundLoop = 0x30,
			c_randomTableMask = 0x3ff,
			c_randomPhaseRange = 0x274,
			c_randomBubbleOffsetRange = 7,
		};

		OilSlickAction();
		~OilSlickAction();
		PowerupAction* Destroy(undefined4 p_flags) override; // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;           // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;  // vtable+0x0c
		void AdvanceState() override;                        // vtable+0x14
		void Deactivate() override;                          // vtable+0x1c
		void OnHitRacer(RaceState::Racer* p_racer) override; // vtable+0x20
		void Initialize(
			RacePowerupManager* p_manager,
			RaceState* p_raceState,
			GolCollidableEntity* p_collidable,
			RaceSessionField0x32b4* p_collisionWorld,
			CutsceneAnimation* p_particleAnimation,
			GolRenderDevice* p_renderer,
			GolExport* p_export
		);
		void Destroy();
		void Activate(RaceState::Racer* p_racer);

	private:
		RacePowerupManager* m_manager; // 0x02c
		GolWorldEntity m_worldEntity;  // 0x030
		union {
			SpatialSoundInstance* m_sound;                  // 0x058
			RaceResourceManager::Resource* m_soundResource; // 0x058
		};
		CutsceneAnimation* m_particleAnimation;                // 0x05c
		CutsceneParticleRef* m_bubbleParticle;                 // 0x060
		RaceSessionField0x27d4::Item::Field0x004 m_slickDecal; // 0x064
		GolBillboard::Field0x2c m_materialTable;               // 0x180
		GolCollidableEntity* m_collidable;                     // 0x18c
	};

	// VTABLE: LEGORACERS 0x004b1448
	// SIZE 0x17c
	class DynamiteAction : public HazardActionBase {
	public:
		enum {
			c_stateArmed = 2,
			c_stateThrown = 3,
			c_stateSecondBlast = 4,
			c_stateThirdBlast = 5,
			c_stateDone = 6,
			c_blastIntervalMs = 0x01f4,
			c_flightLifetimeMs = 0x0bb8,
			c_fuseDurationMs = 0x1388,
			c_soundExplode = 0x05,
			c_soundFuse = 0x11,
			c_randomTableMask = 0x3ff,
			c_randomOffsetRange = 13,
			c_randomOffsetCenter = 6,
		};

		DynamiteAction();
		~DynamiteAction();
		PowerupAction* Destroy(undefined4 p_flags) override; // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;           // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;  // vtable+0x0c
		void AdvanceState() override;                        // vtable+0x14
		void Deactivate() override;                          // vtable+0x1c
		void Initialize(
			RaceState* p_raceState,
			RaceSessionField0x32b4* p_collisionWorld,
			RacePowerupManager* p_manager,
			CutsceneAnimation* p_cutsceneAnimation,
			GolModelEntity* p_model
		);
		void Destroy();
		LegoU32 Activate(RaceState::Racer* p_racer, RaceState::Racer* p_targetRacer);

	private:
		GolModelEntity m_modelEntity;           // 0x02c
		PowerupProjectile m_projectile;         // 0x0bc
		RacePowerupManager* m_manager;          // 0x164
		CutsceneAnimation* m_cutsceneAnimation; // 0x168
		CutsceneParticleRef* m_sparkParticle;   // 0x16c
		union {
			SpatialSoundInstance* m_sound;                  // 0x170
			RaceResourceManager::Resource* m_soundResource; // 0x170
		};
		RaceState::Racer* m_targetRacer; // 0x174
		LegoFloat m_tumbleAngle;         // 0x178
	};

	// VTABLE: LEGORACERS 0x004b13fc
	// SIZE 0x68
	class CurseAction : public HazardActionBase {
	public:
		enum {
			c_stateArmed = 2,
			c_stateActive = 3,
			c_stateFade = 4,
			c_stateExpiring = 5,
			c_stateDone = 6,
			c_fadeDurationMs = 0x03e8,
			c_curseDurationMs = 0x2710,
			c_activeDurationMs = 0x3a98,
			c_soundLoop = 0x09,
			c_racerFlags0xd04Bit11 = 1 << 11,
		};

		CurseAction();
		~CurseAction();
		PowerupAction* Destroy(undefined4 p_flags) override;           // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;            // vtable+0x0c
		void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
		void AdvanceState() override;                                  // vtable+0x14
		void Deactivate() override;                                    // vtable+0x1c
		void OnHitRacer(RaceState::Racer* p_racer) override;           // vtable+0x20
		void Initialize(RaceState* p_raceState, RaceSessionField0x32b4* p_curseModel, RacePowerupManager* p_manager);
		void Reset();
		void Destroy();
		void Activate(
			RaceState::Racer* p_racer,
			GolAnimatedEntity* p_curseModel,
			GolAnimatedEntity* p_auraModel,
			GolAnimatedEntity* p_innerAuraModel,
			ActionTarget* p_target
		);

	private:
		RacePowerupManager* m_manager;        // 0x2c
		GolAnimatedEntity* m_curseEntity;     // 0x30
		GolAnimatedEntity* m_auraEntity;      // 0x34
		GolAnimatedEntity* m_innerAuraEntity; // 0x38
		GolWorldEntity m_worldEntity;         // 0x3c
		union {
			SpatialSoundInstance* m_sound;                  // 0x64
			RaceResourceManager::Resource* m_soundResource; // 0x64
		};
	};

	// VTABLE: LEGORACERS 0x004b13b8
	// SIZE 0xe8
	class CannonballAction : public WeaponActionBase {
	public:
		enum {
			c_racerFlags0xd04Bit0 = 1 << 0,
			c_soundHit = 5,
			c_soundFire = 6,
			c_racerField0x018Flags0x384Bit1 = 1 << 1,
		};

		CannonballAction();
		~CannonballAction();
		PowerupAction* Destroy(undefined4 p_flags) override; // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;           // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;  // vtable+0x0c
		void AdvanceState() override;                        // vtable+0x14
		void Deactivate() override;                          // vtable+0x1c
		void OnHitRacer(RaceState::Racer* p_racer) override; // vtable+0x20
		void Initialize(GolExport** p_golExportPtr, RaceSessionField0x32b4* p_collisionWorld);
		void Destroy();
		LegoU32 Activate(ActionSetup* p_setup);

	private:
		// SIZE 0x24
		class CannonEmplacement {
		public:
			undefined m_unk0x000[0x008 - 0x000]; // 0x000
			GolVec3 m_targetPosition;            // 0x008
			GolVec3 m_position;                  // 0x014
			LegoU32 m_lifetimeMs;                // 0x020
		};

		PowerupProjectile m_projectile;       // 0x030
		GolBillboard* m_billboard;            // 0x0d8
		CutsceneParticleRef* m_smokeParticle; // 0x0dc
		union {
			CannonEmplacement* m_emplacement; // 0x0e0
			const LegoChar* m_materialName;   // 0x0e0
		};
		union {
			CutsceneParticleRef* m_trailParticle; // 0x0e4
			RaceTrailManager::Trail* m_trail;     // 0x0e4
		};
	};

	// VTABLE: LEGORACERS 0x004b1518
	// SIZE 0x290
	class GrapplingHookAction : public WeaponActionBase {
	public:
		enum {
			c_stateArmed = 2,
			c_stateFlying = 3,
			c_statePulling = 4,
			c_stateRetracting = 5,
			c_stateDone = 6,
		};

		enum {
			c_soundHitRacer = 0x12,
			c_soundRelease = 0x14,
			c_soundFire = 0x15,
			c_soundMiss = 0x16,
			c_soundRetract = 0x49,
		};

		enum {
			c_racerFlags0xd04Bit0 = 1 << 0,
		};

		GrapplingHookAction();
		~GrapplingHookAction();
		PowerupAction* Destroy(undefined4 p_flags) override; // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;           // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;  // vtable+0x0c
		void AdvanceState() override;                        // vtable+0x14
		void Deactivate() override;                          // vtable+0x1c
		void OnHitRacer(RaceState::Racer* p_racer) override; // vtable+0x20
		void Initialize(
			RacePowerupManager* p_manager,
			RaceSessionField0x32b4* p_collisionWorld,
			undefined4 p_billboardMaterialIndex
		);
		void Shutdown();
		LegoU32 Activate(
			GolModelEntity* p_hookEntity,
			RaceState::Racer* p_racer,
			RaceState::Racer* p_targetRacer,
			TargetPointList::Entry* p_targetPoint,
			MabMaterialAnimationItem0x18* p_billboardAnimation,
			LegoU32 p_delayMs
		);
		void ReleaseHook(SoundVector* p_position);

	private:
		TetherProjectile m_projectile;                     // 0x030
		GolWorldEntity* m_hookEntity;                      // 0x268
		CutsceneParticleRef* m_smokeParticleRef;           // 0x26c
		GolBillboard* m_billboard;                         // 0x270
		MabMaterialAnimationItem0x18 m_billboardAnimation; // 0x274
		undefined4 m_billboardMaterialIndex;               // 0x28c
	};

	// VTABLE: LEGORACERS 0x004b15a8
	// SIZE 0x24c
	class LightningAction : public WeaponActionBase {
	public:
		enum {
			c_stateRampIn = 2,
			c_stateSustain = 3,
			c_stateFade = 4,
			c_stateDone = 6,
			c_racerFlags0xd04Bit0 = 1 << 0,
			c_racerFlags0xaa8Bit7 = 1 << 7,
			c_racerField0x018Flags0x384Bit1 = 1 << 1,
			c_jitterIntervalMs = 0x0032,
			c_flashDurationMs = 0x0064,
			c_fadeDurationMs = 0x01f4,
			c_crackleMinIntervalMs = 0x00c8,
			c_crackleIntervalRangeMs = 0x012c,
			c_shockDurationMs = 0x03e8,
			c_sustainDurationMs = 0x1b58,
			c_soundLoop = 0x44,
			c_soundThunder = 0x42,
			c_soundZap = 0x43,
			c_soundCrackle = 0x45,
			c_colorOffset0xe1 = 0xe1,
			c_colorOffset0xff = 0xff,
			c_randomTableMask = 0x3ff,
			c_randomOffsetRange = 0x32,
		};

		LightningAction();
		~LightningAction();
		PowerupAction* Destroy(undefined4 p_flags) override;           // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
		void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
		void AdvanceState() override;                                  // vtable+0x14
		void Deactivate() override;                                    // vtable+0x1c
		void OnHitRacer(RaceState::Racer* p_racer) override;           // vtable+0x20
		void GetProjectilePosition(GolVec3* p_position) override;      // vtable+0x24
		void GetProjectileVelocity(GolVec3* p_velocity) override;      // vtable+0x28

		void Initialize(GolExport* p_export, RacePowerupManager* p_manager);
		void AcquireSound();
		void Destroy();
		void AdvanceJitter();
		void FillJitterTable();
		void RebuildBolt();
		void Activate(RaceState::Racer* p_racer, ActionTarget* p_target);
		void UpdateSound(LegoU32 p_elapsedMs);
		void UpdateBoltPath();
		void FindVictim();
		void UpdateHitParticle();

	private:
		BeamMesh m_beam;             // 0x030
		GolVec3 m_boltPoints[4];     // 0x1a0
		LegoFloat m_jitterTable[20]; // 0x1d0
		LegoU32 m_jitterCursor;      // 0x220
		LegoU32 m_jitterTimerMs;     // 0x224
		undefined4 m_unk0x228;       // 0x228
		LegoU32 m_crackleTimerMs;    // 0x22c
		LegoFloat m_boltLength;      // 0x230
		undefined4 m_unk0x234;       // 0x234
		union {
			SpatialSoundInstance* m_sound;                  // 0x238
			RaceResourceManager::Resource* m_soundResource; // 0x238
		};
		RaceActionSource0x24* m_source;     // 0x23c
		LegoU32 m_shockTimerMs;             // 0x240
		CutsceneParticleRef* m_hitParticle; // 0x244
		GolBillboard* m_flashBillboard;     // 0x248
	};

	// VTABLE: LEGORACERS 0x004b1690
	// SIZE 0x224
	class HomingMissileAction : public WeaponActionBase {
	public:
		enum {
			c_stateArmed = 2,
			c_stateFlying = 3,
			c_state0x04 = 4,
			c_stateDone = 6,
			c_racerFlags0xd04Bit0 = 1 << 0,
			c_racerField0x018Flags0x384Bit1 = 1 << 1,
			c_transformNodeIndex1 = 1,
			c_flightTimeMs = 0x157c,
			c_soundExplode = 0x32,
			c_soundFire = 0x33,
		};

		HomingMissileAction();
		~HomingMissileAction();
		PowerupAction* Destroy(undefined4 p_flags) override; // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;           // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;  // vtable+0x0c
		void AdvanceState() override;                        // vtable+0x14
		void Deactivate() override;                          // vtable+0x1c
		void OnHitRacer(RaceState::Racer* p_racer) override; // vtable+0x20
		void Initialize(GolExport** p_golExportPtr, RaceSessionField0x32b4* p_collisionWorld);
		void Shutdown();
		void Activate(
			GolAnimatedEntity* p_missileTemplate,
			GolAnimatedEntity* p_unk0x08,
			RaceState::Racer* p_racer,
			LegoU32 p_missileIndex
		);
		void LaunchProjectile();

	private:
		HomingProjectile m_projectile;     // 0x030
		GolAnimatedEntity m_missileEntity; // 0x128
		RaceTrailManager::Trail* m_trail;  // 0x21c
		LegoU32 m_missileIndex;            // 0x220
	};

	// VTABLE: LEGORACERS 0x004b1938
	// SIZE 0x2c
	class ShieldAction : public PowerupActionBase {
	public:
		enum {
			c_stateActive = 3,
			c_stateFade = 4,
			c_stateDone = 6,
			c_fadeDurationMs = 0x03e8,
			c_durationLevel0Ms = 0x0fa0,
			c_durationLevel1Ms = 0x1770,
			c_durationLevel2Ms = 0x1f40,
			c_durationLevel3Ms = 0x2710,
			c_soundLevel1 = 0x35,
			c_soundExpire = 0x3b,
			c_soundLevel0 = 0x4c,
			c_soundLevel2 = 0x4d,
			c_soundLevel3 = 0x4e,
			c_racerFlags0xd04Bit0 = 1 << 0,
			c_racerFlags0xd04Bit11 = 1 << 11,
		};

		ShieldAction();
		~ShieldAction();
		PowerupAction* Destroy(undefined4 p_flags) override;           // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
		void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
		void AdvanceState() override;                                  // vtable+0x14
		LegoS32 GetBrickColor() override;                              // vtable+0x18
		void Deactivate() override;                                    // vtable+0x1c
		void Initialize(RacePowerupManager* p_manager);
		void Destroy();
		void Activate(
			RaceState::Racer* p_racer,
			LegoU32 p_level,
			GolAnimatedEntity* p_shieldTemplate,
			GolAnimatedEntity* p_innerShieldTemplate
		);

	private:
		friend class RacePowerupManager;

		GolAnimatedEntity* m_shieldEntity;      // 0x18
		GolAnimatedEntity* m_innerShieldEntity; // 0x1c
		RaceState::Racer* m_racer;              // 0x20
		RacePowerupManager* m_manager;          // 0x24
		union {
			SpatialSoundInstance* m_sound;                  // 0x28
			RaceResourceManager::Resource* m_soundResource; // 0x28
		};
	};

	// VTABLE: LEGORACERS 0x004b1a30
	// SIZE 0x34
	class TurboAction : public PowerupActionBase {
	public:
		enum {
			c_stateReady = 1,
			c_stateIgnite = 2,
			c_stateBoosting = 3,
			c_stateFade = 4,
			c_stateDone = 6,
			c_speedModDurationL0Ms = 0x007d,
			c_speedModDurationMs = 0x00fa,
			c_igniteFlashMs = 0x0032,
			c_fadeBaseMs = 0x015e,
			c_smokeWindowMs = 0x0320,
			c_boostDurationL0Ms = 0x03e8,
			c_boostDurationL1Ms = 0x05dc,
			c_earlyEndWindowMs = 0x1194,
			c_boostDurationL2Ms = 0x1388,
			c_soundBoostBase = 0x24,
			c_soundEnd = 0x28,
			c_soundWhoosh = 0x41,
			c_soundEndL2 = 0x4b,
			c_ownerFlags0x058Bit1 = 1 << 1,
			c_racerFlags0xd04Bit3 = 1 << 3,
		};

		TurboAction();
		~TurboAction();
		PowerupAction* Destroy(undefined4 p_flags) override;           // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;            // vtable+0x0c
		void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
		void AdvanceState() override;                                  // vtable+0x14
		LegoS32 GetBrickColor() override;                              // vtable+0x18
		void Deactivate() override;                                    // vtable+0x1c
		void Initialize(RacePowerupManager* p_manager, CutsceneAnimation* p_particleAnimation);
		void Destroy();
		void Reset();
		void Activate(RaceState::Racer* p_racer, LegoU32 p_level);
		void StartBoost();
		void AnchorToRacer();

	private:
		friend class RacePowerupManager;

		RaceState::Racer* m_racer;              // 0x18
		RacePowerupManager* m_manager;          // 0x1c
		GolAnimatedEntity* m_turboEntity;       // 0x20
		GolAnimatedEntity* m_flameEntity;       // 0x24
		GolAnimatedEntity* m_flame2Entity;      // 0x28
		CutsceneAnimation* m_particleAnimation; // 0x2c
		CutsceneParticleRef* m_smokeParticle;   // 0x30
	};

	// VTABLE: LEGORACERS 0x004b1a88
	// SIZE 0xe4
	class WarpAction : public PowerupActionBase {
	public:
		// SIZE 0x08
		struct SetupParams {
			RacePowerupManager* m_manager; // 0x00
			LegoFloat m_cameraFov;         // 0x04
		};

		WarpAction();
		~WarpAction();
		PowerupAction* Destroy(undefined4 p_flags) override;           // vtable+0x04
		void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
		void Draw(GolD3DRenderDevice* p_renderer) override;            // vtable+0x0c
		void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
		void AdvanceState() override;                                  // vtable+0x14
		LegoS32 GetBrickColor() override;                              // vtable+0x18
		void Deactivate() override;                                    // vtable+0x1c
		void Reset();
		void Initialize(const SetupParams* p_params);
		void Destroy();
		LegoU32 Activate(RaceState::Racer* p_racer, GolModelEntity* p_portalModel, ActionTarget* p_target);
		void TeleportEntity(GolWorldEntity* p_entity);

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

		GolModelEntity m_modelEntity;  // 0x018
		RaceState::Racer* m_racer;     // 0x0a8
		RacePowerupManager* m_manager; // 0x0ac
		LegoFloat m_cameraFov;         // 0x0b0
		SoundVector m_startPosition;   // 0x0b4
		GolVec3 m_targetPosition;      // 0x0c0
		GolVec3 m_targetDirection;     // 0x0cc
		LegoBool32 m_hasTarget;        // 0x0d8
		LegoBool32 m_followingPath;    // 0x0dc
		LegoBool32 m_isDemoRacer;      // 0x0e0
	};

	// VTABLE: LEGORACERS 0x004b0164
	// SIZE 0x270
	class Explosion : public LegoEventQueue::Callback {
	public:
		enum {
			c_stateUninitialized = 0,
			c_stateIdle = 1,
			c_stateExploding = 2,
			c_stateScarFading = 3,

			c_blastNone = 0,
			c_blastShake = 1,
			c_blastLaunch = 2,
		};

		// SIZE 0x48
		struct Params {
			GolExport* m_golExport;                             // 0x00
			GolCollidableEntity* m_collidable;                  // 0x04
			GolModelEntity* m_model;                            // 0x08
			DuskwindBananaRelic0x24* m_billboardMaterial;       // 0x0c
			DuskwindBananaRelic0x24* m_flashMaterial;           // 0x10
			DuskwindBananaRelic0x24* m_scarMaterial;            // 0x14
			LegoEventQueue* m_eventQueue;                       // 0x18
			RacePowerupManager* m_manager;                      // 0x1c
			MabMaterialAnimationItem0x18* m_billboardAnimation; // 0x20
			LegoU32 m_billboardMaterialIndex;                   // 0x24
			CutsceneAnimation* m_particleAnimation;             // 0x28
			LegoU32 m_flashDurationMs;                          // 0x2c
			LegoU32 m_scarDurationMs;                           // 0x30
			LegoFloat m_modelScale;                             // 0x34
			LegoFloat m_flashWidth;                             // 0x38
			LegoFloat m_flashHeight;                            // 0x3c
			LegoFloat m_blastRadius;                            // 0x40
			LegoU32 m_blastMode;                                // 0x44
		};

		Explosion();
		void VTable0x00(LegoEventQueue::CallbackData* p_data) override; // vtable+0x00
		virtual Explosion* Destroy(undefined4 p_flags);                 // vtable+0x04

		~Explosion();
		Explosion* GetNext() { return m_next; }
		LegoS32 GetState() const { return m_state; }
		LegoU32 GetRemainingMs() const { return m_remainingMs; }
		void SetNext(Explosion* p_next) { m_next = p_next; }
		void Initialize(const Params* p_params);
		void Destroy();
		void Spawn(const GolVec3* p_position, undefined4 p_leavesScar, RaceState::Racer* p_racer);
		void Deactivate();
		void Update(LegoU32 p_elapsedMs);
		void UpdateFlash(LegoU32 p_elapsedMs);
		void DrawTransparent(GolD3DRenderDevice* p_renderer);
		void Draw(GolD3DRenderDevice* p_renderer);

	private:
		enum {
			c_racerFlags0xd04Bit0 = 1 << 0,
		};

		LegoS32 m_state;                                      // 0x004
		GolWorldEntity m_worldEntity;                         // 0x008
		GolExport* m_golExport;                               // 0x030
		GolModelEntity m_modelEntity;                         // 0x034
		GolBillboard* m_billboard;                            // 0x0c4
		MabMaterialAnimationItem0x18 m_billboardAnimation;    // 0x0c8
		LegoU32 m_billboardMaterialIndex;                     // 0x0e0
		RaceSessionField0x27d4::Item::Field0x004 m_scarDecal; // 0x0e4
		GolCollidableEntity* m_collidable;                    // 0x200
		MaterialTable0x0c m_materialTable;                    // 0x204
		DuskwindBananaRelic0x24* m_flashMaterial;             // 0x210
		DuskwindBananaRelic0x24* m_scarMaterial;              // 0x214
		LegoEventQueue* m_eventQueue;                         // 0x218
		RaceState::Racer* m_ownerRacer;                       // 0x21c
		LegoEventQueue::Event* m_collisionEvent;              // 0x220
		RacePowerupManager* m_manager;                        // 0x224
		CutsceneAnimation* m_particleAnimation;               // 0x228
		LegoU32 m_blastMode;                                  // 0x22c
		LegoU32 m_flashDurationMs;                            // 0x230
		LegoU32 m_scarDurationMs;                             // 0x234
		LegoU32 m_remainingMs;                                // 0x238
		LegoFloat m_alpha;                                    // 0x23c
		LegoFloat m_modelAlpha;                               // 0x240
		LegoFloat m_alphaRate;                                // 0x244
		LegoFloat m_growth;                                   // 0x248
		LegoFloat m_growthRate;                               // 0x24c
		LegoFloat m_initialGrowthRate;                        // 0x250
		LegoFloat m_growthAcceleration;                       // 0x254
		LegoFloat m_modelScale;                               // 0x258
		LegoFloat m_flashWidth;                               // 0x25c
		LegoFloat m_flashHeight;                              // 0x260
		LegoFloat m_blastRadius;                              // 0x264
		LegoS32 m_leavesScar;                                 // 0x268
		Explosion* m_next;                                    // 0x26c
	};

	// SIZE 0x80
	class BrickDebris {
	public:
		// SIZE 0x14
		class Entry {
		public:
			Entry();
			~Entry();
			void Reset();
			void Update(LegoU32 p_elapsedMs);
			void Draw(GolD3DRenderDevice* p_renderer);
			void Release();
			void Initialize(GolD3DRenderDevice* p_renderer);
			void Spawn(
				GolAnimatedEntity* p_sourceEntity,
				GolAnimatedEntity* p_entity,
				const GolVec3* p_position,
				const GolVec3* p_direction,
				LegoU32 p_partIndex,
				void* p_billboardPosition
			);
			GolAnimatedEntity* GetEntity() { return m_entity; }
			LegoS32 GetState() const { return m_state; }

		private:
			friend class BrickDebris;

			GolBillboard::Field0x2c m_materialTable; // 0x00
			GolAnimatedEntity* m_entity;             // 0x0c
			LegoS32 m_state;                         // 0x10
		};

		BrickDebris();
		~BrickDebris();
		LegoS32 Destroy();
		LegoS32 Reset();
		void Update(LegoU32 p_elapsedMs);
		void Draw(GolD3DRenderDevice* p_renderer);
		void ReleaseAll();

	private:
		friend class RacePowerupManager;

		void Initialize(RacePowerupManager* p_manager, GolD3DRenderDevice* p_renderer);
		void Spawn(const GolVec3* p_position, const GolVec3* p_direction, RaceState::Racer* p_racer);

		Entry m_entries[5];                  // 0x00
		GolAnimatedEntity* m_brickModels[4]; // 0x64
		RacePowerupManager* m_manager;       // 0x74
		undefined4 m_nextModelIndex;         // 0x78
		undefined4 m_nextPartIndex;          // 0x7c
	};

	// SIZE 0x30
	class SpatialSoundResource : public RaceResourceManager::Resource {
	public:
		void SetPosition(const GolVec3& p_position) { m_position = p_position; }
		void SetVelocity(const GolVec3& p_velocity) { m_velocity = p_velocity; }

	private:
		friend class RacePowerupManager;

		undefined m_unk0x04[0x18 - 0x04]; // 0x04
		GolVec3 m_position;               // 0x18
		GolVec3 m_velocity;               // 0x24
	};

	RacePowerupManager();
	~RacePowerupManager();
	void Update(LegoU32 p_elapsedMs);
	void Draw(LegoBool32 p_warpOnly);
	void DrawTransparent();
	void UseRedPowerup(RaceState::Racer* p_racer, LegoU32 p_level);
	void UseYellowPowerup(RaceState::Racer* p_racer, LegoU32 p_level);
	void UseBluePowerup(RaceState::Racer* p_racer, LegoU32 p_level);
	void UseGreenPowerup(RaceState::Racer* p_racer, LegoU32 p_level);
	LegoU32 ActivateWarp(RaceState::Racer* p_racer, LegoU32 p_level);
	void SpawnExplosion(const GolVec3* p_position, undefined4 p_leavesScar, RaceState::Racer* p_racer);
	void FUN_0045b4d0(const GolVec3* p_position, undefined4 p_leavesScar, RaceState::Racer* p_racer);
	void SpawnSpikeExplosion(const GolVec3* p_position, undefined4 p_leavesScar, RaceState::Racer* p_racer);
	void SpawnBrickDebris(const GolVec3* p_position, const GolVec3* p_direction, RaceState::Racer* p_racer);
	void CancelWarp(RaceState::Racer* p_racer);
	void SetBricksAudible();
	LegoBool32 IsProjectileEntity(GolWorldEntity* p_entity);
	void ResetEffects();
	LegoU32 GetUsedEffectEntityCount() const { return m_usedEffectEntityCount; }
	undefined4 GetUnk0x19a0() const { return m_unk0x19a0; }
	GolBillboard::Field0x2c* GetBillboardMaterialTable() { return &m_billboardMaterialTable; }
	MabMaterialAnimationItem0x8* GetMaterialAnimationItems() const { return m_materialAnimation.GetUnk0x04(); }
	LegoU32 GetMaterialAnimationItemCount() const { return m_materialAnimation.GetUnk0x08(); }
	MabMaterialAnimationItem0x18* GetMaterialAnimationItems0x18() const { return m_materialAnimation.GetUnk0x0c(); }
	RaceState* GetRaceState() { return m_raceState; }
	void SetAimTarget(ActionTarget* p_aimTarget) { m_aimTarget = p_aimTarget; }

private:
	// SIZE 0x3c
	struct Params {
		GolExport* m_golExport;                      // 0x00
		GolD3DRenderDevice* m_renderer;              // 0x04
		RaceState* m_raceState;                      // 0x08
		GolCollidableEntity* m_collidable;           // 0x0c
		GolBoundedEntity* m_boundedEntity;           // 0x10
		RaceSessionField0x32b4* m_collisionWorld;    // 0x14
		RaceState::Racer::Field0x004* m_soundSource; // 0x18
		CutsceneAnimation* m_cutsceneAnimation;      // 0x1c
		RaceTrailManager* m_trailManager;            // 0x20
		void* m_unk0x24;                             // 0x24
		MenuAnimationList* m_animationList;          // 0x28
		GolWorldDatabase* m_trackDatabase;           // 0x2c
		TargetPointList* m_targetPoints;             // 0x30
		LegoFloat m_cameraFov;                       // 0x34
		undefined4 m_modeFlags;                      // 0x38
	};

	friend class RaceSession;
	friend class MagnetAction;
	friend class CurseAction;
	friend class CannonballAction;
	friend class GrapplingHookAction;
	friend class LightningAction;
	friend class HomingMissileAction;
	friend class ShieldAction;
	friend class TurboAction;
	friend class WarpAction;
	friend class BrickDebris;
	friend class ColorBrick;
	friend class RaceState::Racer::DroppableBrick;

	void Initialize(const Params* p_params);
	void LoadDatabases(const LegoChar* p_databaseName, const LegoChar* p_animationName, LegoBool32 p_binary);
	void PreparePools(LegoBool32 p_mirror);
	void SetActionPoolCounts(LegoBool32 p_mirror);
	void LoadPowerupFile(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
	void ParseColorBricks(GolFileParser* p_parser, LegoBool32 p_mirror);
	void ParseWhiteBricks(GolFileParser* p_parser, LegoBool32 p_mirror);
	void CreatePools();
	void CreateActionPools();
	void FUN_004164c0();
	void CreateExplosionPools();
	void Reset();
	void Destroy();
	void UpdateBricks(LegoU32 p_elapsedMs);
	void CreateBrickEvents();
	LegoU32 FireCannonball(RaceState::Racer* p_racer, LegoU32 p_level);
	LegoU32 FireGrapplingHook(RaceState::Racer* p_racer, LegoU32 p_level);
	void FireLightning(RaceState::Racer* p_racer, LegoU32 p_level);
	void DropOilSlick(RaceState::Racer* p_racer, LegoU32 p_level);
	LegoU32 ThrowDynamite(RaceState::Racer* p_racer, LegoU32 p_level);
	void ActivateMagnet(RaceState::Racer* p_racer, LegoU32 p_level);
	void CastCurse(RaceState::Racer* p_racer, LegoU32 p_level);
	void FireHomingMissiles(RaceState::Racer* p_racer, LegoU32 p_level);
	PowerupAction* ReclaimAction(
		LegoU32 p_brickColor,
		LegoU32 p_level1,
		LegoS32 p_level2,
		LegoS32 p_level3,
		LegoS32 p_level4
	);
	void CancelShield(RaceState::Racer* p_racer);
	void CancelTurbo(RaceState::Racer* p_racer);
	void CancelMagnetHold(RaceState::Racer* p_racer);
	void UpdateProjectileSound(SpatialSoundResource* p_resource, LegoU32 p_level, LegoS32 p_state);
	void ClearBricksAudible();
	GolAnimatedEntity* AllocateEffectEntity();
	LegoU32 ReleaseEffectEntity(GolAnimatedEntity* p_entity);
	DuskwindBananaRelic0x24* GetBrickMaterial(LegoU32* p_brickColor);
	DuskwindBananaRelic0x24* GetTrailMaterial(LegoU32* p_brickColor);
	static Explosion* __stdcall ReclaimExplosion(Explosion** p_head);

	enum {
		c_brickMaterialRed = 0,
		c_trailMaterialRed = 1,
		c_brickMaterialYellow = 2,
		c_trailMaterialYellow = 3,
		c_brickMaterialBlue = 4,
		c_trailMaterialBlue = 5,
		c_brickMaterialGreen = 6,
		c_trailMaterialGreen = 7,
		c_brickMaterialCount = 8,
		c_randomTableMask = 0x3ff,
		c_randomOffsetRange = 100,
		c_randomBurstMax = 3,
	};

	GolExport* m_golExport;                           // 0x000
	GolD3DRenderDevice* m_renderer;                   // 0x004
	GolBillboard::Field0x2c m_billboardMaterialTable; // 0x008
	MabMaterialAnimation0x14 m_materialAnimation;     // 0x014
	ColorBrick* m_colorBricks;                        // 0x028
	WhiteBrick* m_whiteBricks;                        // 0x02c
	LegoEventQueue::Event** m_brickEvents;            // 0x030
	LegoU32 m_colorBrickCount;                        // 0x034
	LegoU32 m_whiteBrickCount;                        // 0x038
	RaceState::Racer::Field0x004* m_soundSource;      // 0x03c
	CutsceneAnimation* m_cutsceneAnimation;           // 0x040
	RaceTrailManager* m_trailManager;                 // 0x044
	void* m_unk0x048;                                 // 0x048
	MenuAnimationList* m_animationList;               // 0x04c
	TargetPointList* m_targetPoints;                  // 0x050
	LegoFloat m_cameraFov;                            // 0x054
	undefined4 m_modeFlags;                           // 0x058
	GolWorldDatabase* m_worldDatabase;                // 0x05c
	GolWorldDatabase* m_trackDatabase;                // 0x060
	GolWorldDatabase* m_turbo3Database;               // 0x064
	RaceSessionField0x32b4* m_collisionWorld;         // 0x068
	GolCollidableEntity* m_collidable;                // 0x06c
	GolBoundedEntity* m_boundedEntity;                // 0x070
	RaceState* m_raceState;                           // 0x074
	PowerupAction* m_freeMagnetActions;               // 0x078
	PowerupAction* m_freeOilSlickActions;             // 0x07c
	PowerupAction* m_freeDynamiteActions;             // 0x080
	PowerupAction* m_freeCurseActions;                // 0x084
	PowerupAction* m_freeCannonballActions;           // 0x088
	PowerupAction* m_freeGrapplingHookActions;        // 0x08c
	PowerupAction* m_freeLightningActions;            // 0x090
	PowerupAction* m_freeHomingMissileActions;        // 0x094
	PowerupAction* m_freeShieldActions;               // 0x098
	PowerupAction* m_freeTurboActions;                // 0x09c
	PowerupAction* m_freeWarpActions;                 // 0x0a0
	GolAnimatedEntity m_effectEntities[25];           // 0x0a4
	LegoU32 m_effectEntityUsedMask;                   // 0x1878
	LegoU32 m_usedEffectEntityCount;                  // 0x187c
	PowerupAction* m_activeActions;                   // 0x1880
	LegoU8 m_actionPoolCounts[11];                    // 0x1884
	undefined m_unk0x188f;                            // 0x188f
	MagnetAction* m_magnetActions;                    // 0x1890
	OilSlickAction* m_oilSlickActions;                // 0x1894
	DynamiteAction* m_dynamiteActions;                // 0x1898
	CurseAction* m_curseActions;                      // 0x189c
	CannonballAction* m_cannonballActions;            // 0x18a0
	GrapplingHookAction* m_grapplingHookActions;      // 0x18a4
	LightningAction* m_lightningActions;              // 0x18a8
	HomingMissileAction* m_homingMissileActions;      // 0x18ac
	ShieldAction* m_shieldActions;                    // 0x18b0
	TurboAction* m_turboActions;                      // 0x18b4
	WarpAction* m_warpActions;                        // 0x18b8
	BrickDebris m_brickDebris;                        // 0x18bc
	Explosion* m_activeExplosions;                    // 0x193c
	Explosion* m_activeSpikeExplosions;               // 0x1940
	Explosion* m_freeExplosions;                      // 0x1944
	Explosion* m_freeSpikeExplosions;                 // 0x1948
	LegoU8 m_explosionPoolCount;                      // 0x194c
	LegoU8 m_spikeExplosionPoolCount;                 // 0x194d
	undefined m_unk0x194e[0x1950 - 0x194e];           // 0x194e
	Explosion* m_explosionPool;                       // 0x1950
	Explosion* m_spikeExplosionPool;                  // 0x1954
	union {
		SpatialSoundResource* m_cannonballFlightSound;                  // 0x1958
		SpatialSoundInstance* m_cannonballFlightSoundInstance;          // 0x1958
		RaceResourceManager::Resource* m_cannonballFlightSoundResource; // 0x1958
	};
	union {
		SpatialSoundResource* m_missileFlightSound;                  // 0x195c
		SpatialSoundInstance* m_missileFlightSoundInstance;          // 0x195c
		RaceResourceManager::Resource* m_missileFlightSoundResource; // 0x195c
	};
	union {
		SpatialSoundResource* m_grappleFlightSound;                  // 0x1960
		SpatialSoundInstance* m_grappleFlightSoundInstance;          // 0x1960
		RaceResourceManager::Resource* m_grappleFlightSoundResource; // 0x1960
	};
	union {
		SpatialSoundResource* m_grappleAttachedSound;                  // 0x1964
		SpatialSoundInstance* m_grappleAttachedSoundInstance;          // 0x1964
		RaceResourceManager::Resource* m_grappleAttachedSoundResource; // 0x1964
	};
	GolAnimatedEntity* m_brickModel;              // 0x1968
	GolAnimatedEntity* m_brickBlendModel;         // 0x196c
	GolAnimatedEntity* m_whiteBrickModel;         // 0x1970
	GolAnimatedEntity* m_whiteBrickBlendModel;    // 0x1974
	DuskwindBananaRelic0x24* m_brickMaterials[8]; // 0x1978
	ActionTarget* m_aimTarget;                    // 0x1998
	LegoFloat m_brickSpinAngle;                   // 0x199c
	undefined4 m_unk0x19a0;                       // 0x19a0
};

// SIZE 0x68
class RaceState::Racer::DroppableBrick : public RacePowerupManager::PickupBrick {
public:
	LegoU8 DropAt(GolVec3 p_unk0x04);
	void ReturnHome();
	LegoS32 SnapToGround(GolVec3* p_unk0x04);

protected:
	GolVec3 m_homePosition;           // 0x54
	LegoU32 m_droppedTimeMs;          // 0x60
	LegoU8 m_flags0x64;               // 0x64
	undefined m_unk0x65[0x68 - 0x65]; // 0x65
};

// SIZE 0x68
class RacePowerupManager::WhiteBrick : public RaceState::Racer::DroppableBrick {
public:
	WhiteBrick();
	~WhiteBrick() override;
	void OnTouched(RaceState::Racer* p_racer) override;
	void Respawn() override;

	// SYNTHETIC: LEGORACERS 0x00459090
	// RacePowerupManager::WhiteBrick::`vector deleting destructor'

	void Reset();
	void CaptureHomePosition();
	void Update(LegoU32 p_elapsedMs);
};

#endif // RACEPOWERUPMANAGER_H
