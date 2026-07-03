#ifndef RACEPOWERUPMANAGER_H
#define RACEPOWERUPMANAGER_H

#include "audio/soundnode.h"
#include "core/gol.h"
#include "decomp.h"
#include "gdbmodelindexarray.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "goltxtparser.h"
#include "golworldentity.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"
#include "material/materialtable.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/checkpointgraph.h"
#include "race/powerups/actionsetup.h"
#include "race/powerups/actiontarget.h"
#include "race/powerups/beammesh.h"
#include "race/powerups/cannonballaction.h"
#include "race/powerups/colorbrick.h"
#include "race/powerups/curseaction.h"
#include "race/powerups/droppablebrick.h"
#include "race/powerups/dynamiteaction.h"
#include "race/powerups/grapplinghookaction.h"
#include "race/powerups/hazardactionbase.h"
#include "race/powerups/homingmissileaction.h"
#include "race/powerups/homingprojectile.h"
#include "race/powerups/lightningaction.h"
#include "race/powerups/magnetaction.h"
#include "race/powerups/oilslickaction.h"
#include "race/powerups/pickupbrick.h"
#include "race/powerups/powerupaction.h"
#include "race/powerups/powerupexplosion.h"
#include "race/powerups/powerupprojectile.h"
#include "race/powerups/shieldaction.h"
#include "race/powerups/tetherprojectile.h"
#include "race/powerups/turboaction.h"
#include "race/powerups/warpaction.h"
#include "race/powerups/weaponactionbase.h"
#include "race/powerups/whitebrick.h"
#include "race/raceactionsource.h"
#include "race/racedecalmanager.h"
#include "race/raceresourcemanager.h"
#include "race/racestate.h"
#include "race/racetrailmanager.h"
#include "race/targetpointlist.h"
#include "race/triggerworld.h"
#include "scene/golbillboard.h"
#include "surface/color.h"
#include "types.h"
#include "util/legoeventqueue.h"

class CutsceneAnimation;
class GolMaterial;
class TargetPointList;
class GolCollidableEntity;
class GolD3DRenderDevice;
class GolExport;
class GolFileParser;
class GolMaterialLibrary;
class GolModelBase;
class GolRenderDevice;
class GolSceneNode;
class GolWorldDatabase;
class TriggerWorld;
class SpatialSoundInstance;
struct CutsceneParticleRef;

// SIZE 0x19a4
class RacePowerupManager {
public:
	// Sound bank ids for shared projectile sounds
	enum {
		c_soundGrappleAttached = 0x13,
		c_soundGrappleFlight = 0x17,
		c_soundMissileFlight = 0x34,
	};

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
			e_unknown0x30 = 0x30,
			e_unknown0x31 = 0x31,
		};
	};

	// Brick color codes (PWB color tokens map to these; GetBrickColor returns them)
	enum {
		c_brickColorRed = 1,
		c_brickColorBlue = 2,
		c_brickColorGreen = 3,
		c_brickColorYellow = 4,
	};

	// SIZE 0x80
	class BrickDebris {
	public:
		// SIZE 0x14
		class Entry {
		public:
			enum {
				c_stateFree = 1,
				c_statePlaying = 2,
				c_stateFinished = 3,
			};

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

			GolBillboard::ManagedMaterialTable m_materialTable; // 0x00
			GolAnimatedEntity* m_entity;                        // 0x0c
			LegoS32 m_state;                                    // 0x10
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
		void Spawn(const GolVec3* p_position, const GolVec3* p_direction, Racer* p_racer);

		Entry m_entries[5];                  // 0x00
		GolAnimatedEntity* m_brickModels[4]; // 0x64
		RacePowerupManager* m_manager;       // 0x74
		LegoU32 m_nextModelIndex;            // 0x78
		LegoU32 m_nextPartIndex;             // 0x7c
	};

	RacePowerupManager();
	~RacePowerupManager();
	void Update(LegoU32 p_elapsedMs);
	void Draw(LegoBool32 p_warpOnly);
	void DrawTransparent();
	void UseRedPowerup(Racer* p_racer, LegoU32 p_level);
	void UseYellowPowerup(Racer* p_racer, LegoU32 p_level);
	void UseBluePowerup(Racer* p_racer, LegoU32 p_level);
	void UseGreenPowerup(Racer* p_racer, LegoU32 p_level);
	LegoU32 ActivateWarp(Racer* p_racer, LegoU32 p_level);
	void SpawnExplosion(const GolVec3* p_position, undefined4 p_leavesScar, Racer* p_racer);
	void FUN_0045b4d0(const GolVec3* p_position, undefined4 p_leavesScar, Racer* p_racer);
	void SpawnSpikeExplosion(const GolVec3* p_position, undefined4 p_leavesScar, Racer* p_racer);
	void SpawnBrickDebris(const GolVec3* p_position, const GolVec3* p_direction, Racer* p_racer);
	void CancelWarp(Racer* p_racer);
	void SetBricksAudible();
	LegoBool32 IsProjectileEntity(GolWorldEntity* p_entity);
	void ResetEffects();
	LegoU32 GetUsedEffectEntityCount() const { return m_usedEffectEntityCount; }
	undefined4 GetExclusiveDraw() const { return m_exclusiveDraw; }
	GolBillboard::ManagedMaterialTable* GetBillboardMaterialTable() { return &m_billboardMaterialTable; }
	MabMaterialFrame* GetMaterialAnimationItems() const { return m_materialAnimation.GetFrames(); }
	LegoU32 GetMaterialAnimationItemCount() const { return m_materialAnimation.GetFrameCount(); }
	MabMaterialTrack* GetMaterialAnimationTracks() const { return m_materialAnimation.GetTracks(); }
	RaceState* GetRaceState() { return m_raceState; }
	void SetAimTarget(ActionTarget* p_aimTarget) { m_aimTarget = p_aimTarget; }

private:
	// SIZE 0x3c
	struct Params {
		GolExport* m_golExport;                 // 0x00
		GolD3DRenderDevice* m_renderer;         // 0x04
		RaceState* m_raceState;                 // 0x08
		GolCollidableEntity* m_collidable;      // 0x0c
		GolBoundedEntity* m_boundedEntity;      // 0x10
		TriggerWorld* m_collisionWorld;         // 0x14
		RacerSoundSource* m_soundSource;        // 0x18
		CutsceneAnimation* m_cutsceneAnimation; // 0x1c
		RaceTrailManager* m_trailManager;       // 0x20
		void* m_racerTriggers;                  // 0x24
		MenuAnimationList* m_animationList;     // 0x28
		GolWorldDatabase* m_trackDatabase;      // 0x2c
		TargetPointList* m_targetPoints;        // 0x30
		LegoFloat m_cameraFov;                  // 0x34
		undefined4 m_cheatFlags;                // 0x38
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
	friend class DroppableBrick;

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
	LegoU32 FireCannonball(Racer* p_racer, LegoU32 p_level);
	LegoU32 FireGrapplingHook(Racer* p_racer, LegoU32 p_level);
	void FireLightning(Racer* p_racer, LegoU32 p_level);
	void DropOilSlick(Racer* p_racer, LegoU32 p_level);
	LegoU32 ThrowDynamite(Racer* p_racer, LegoU32 p_level);
	void ActivateMagnet(Racer* p_racer, LegoU32 p_level);
	void CastCurse(Racer* p_racer, LegoU32 p_level);
	void FireHomingMissiles(Racer* p_racer, LegoU32 p_level);
	PowerupAction* ReclaimAction(
		LegoU32 p_brickColor,
		LegoU32 p_level1,
		LegoS32 p_level2,
		LegoS32 p_level3,
		LegoS32 p_level4
	);
	void CancelShield(Racer* p_racer);
	void CancelTurbo(Racer* p_racer);
	void CancelMagnetHold(Racer* p_racer);
	void UpdateProjectileSound(SpatialSoundInstance* p_sound, LegoU32 p_level, LegoS32 p_state);
	void ClearBricksAudible();
	GolAnimatedEntity* AllocateEffectEntity();
	LegoU32 ReleaseEffectEntity(GolAnimatedEntity* p_entity);
	GolMaterial* GetBrickMaterial(LegoU32* p_brickColor);
	GolMaterial* GetTrailMaterial(LegoU32* p_brickColor);
	static PowerupExplosion* __stdcall ReclaimExplosion(PowerupExplosion** p_head);

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

	GolExport* m_golExport;                                      // 0x000
	GolD3DRenderDevice* m_renderer;                              // 0x004
	GolBillboard::ManagedMaterialTable m_billboardMaterialTable; // 0x008
	MabMaterialAnimation m_materialAnimation;                    // 0x014
	ColorBrick* m_colorBricks;                                   // 0x028
	WhiteBrick* m_whiteBricks;                                   // 0x02c
	LegoEventQueue::Event** m_brickEvents;                       // 0x030
	LegoU32 m_colorBrickCount;                                   // 0x034
	LegoU32 m_whiteBrickCount;                                   // 0x038
	RacerSoundSource* m_soundSource;                             // 0x03c
	CutsceneAnimation* m_cutsceneAnimation;                      // 0x040
	RaceTrailManager* m_trailManager;                            // 0x044
	void* m_racerTriggers;                                       // 0x048
	MenuAnimationList* m_animationList;                          // 0x04c
	TargetPointList* m_targetPoints;                             // 0x050
	LegoFloat m_cameraFov;                                       // 0x054
	undefined4 m_cheatFlags;                                     // 0x058
	GolWorldDatabase* m_worldDatabase;                           // 0x05c
	GolWorldDatabase* m_trackDatabase;                           // 0x060
	GolWorldDatabase* m_turbo3Database;                          // 0x064
	TriggerWorld* m_collisionWorld;                              // 0x068
	GolCollidableEntity* m_collidable;                           // 0x06c
	GolBoundedEntity* m_boundedEntity;                           // 0x070
	RaceState* m_raceState;                                      // 0x074
	PowerupAction* m_freeMagnetActions;                          // 0x078
	PowerupAction* m_freeOilSlickActions;                        // 0x07c
	PowerupAction* m_freeDynamiteActions;                        // 0x080
	PowerupAction* m_freeCurseActions;                           // 0x084
	PowerupAction* m_freeCannonballActions;                      // 0x088
	PowerupAction* m_freeGrapplingHookActions;                   // 0x08c
	PowerupAction* m_freeLightningActions;                       // 0x090
	PowerupAction* m_freeHomingMissileActions;                   // 0x094
	PowerupAction* m_freeShieldActions;                          // 0x098
	PowerupAction* m_freeTurboActions;                           // 0x09c
	PowerupAction* m_freeWarpActions;                            // 0x0a0
	GolAnimatedEntity m_effectEntities[25];                      // 0x0a4
	LegoU32 m_effectEntityUsedMask;                              // 0x1878
	LegoU32 m_usedEffectEntityCount;                             // 0x187c
	PowerupAction* m_activeActions;                              // 0x1880
	LegoU8 m_actionPoolCounts[11];                               // 0x1884
	MagnetAction* m_magnetActions;                               // 0x1890
	OilSlickAction* m_oilSlickActions;                           // 0x1894
	DynamiteAction* m_dynamiteActions;                           // 0x1898
	CurseAction* m_curseActions;                                 // 0x189c
	CannonballAction* m_cannonballActions;                       // 0x18a0
	GrapplingHookAction* m_grapplingHookActions;                 // 0x18a4
	LightningAction* m_lightningActions;                         // 0x18a8
	HomingMissileAction* m_homingMissileActions;                 // 0x18ac
	ShieldAction* m_shieldActions;                               // 0x18b0
	TurboAction* m_turboActions;                                 // 0x18b4
	WarpAction* m_warpActions;                                   // 0x18b8
	BrickDebris m_brickDebris;                                   // 0x18bc
	PowerupExplosion* m_activeExplosions;                        // 0x193c
	PowerupExplosion* m_activeSpikeExplosions;                   // 0x1940
	PowerupExplosion* m_freeExplosions;                          // 0x1944
	PowerupExplosion* m_freeSpikeExplosions;                     // 0x1948
	LegoU8 m_explosionPoolCount;                                 // 0x194c
	LegoU8 m_spikeExplosionPoolCount;                            // 0x194d
	undefined m_unk0x194e[0x1950 - 0x194e];                      // 0x194e
	PowerupExplosion* m_explosionPool;                           // 0x1950
	PowerupExplosion* m_spikeExplosionPool;                      // 0x1954
	SpatialSoundInstance* m_cannonballFlightSound;               // 0x1958
	SpatialSoundInstance* m_missileFlightSound;                  // 0x195c
	SpatialSoundInstance* m_grappleFlightSound;                  // 0x1960
	SpatialSoundInstance* m_grappleAttachedSound;                // 0x1964
	GolAnimatedEntity* m_brickModel;                             // 0x1968
	GolAnimatedEntity* m_brickBlendModel;                        // 0x196c
	GolAnimatedEntity* m_whiteBrickModel;                        // 0x1970
	GolAnimatedEntity* m_whiteBrickBlendModel;                   // 0x1974
	GolMaterial* m_brickMaterials[8];                            // 0x1978
	ActionTarget* m_aimTarget;                                   // 0x1998
	LegoFloat m_brickSpinAngle;                                  // 0x199c
	undefined4 m_exclusiveDraw;                                  // 0x19a0
};

#endif // RACEPOWERUPMANAGER_H
