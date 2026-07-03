#ifndef CARVISUALS_H
#define CARVISUALS_H

#include "golanimatedentity.h"
#include "golmath.h"
#include "golname.h"
#include "golworldentitygroup.h"
#include "race/racedecalmanager.h"
#include "scene/golbillboard.h"
#include "types.h"

class ColorTransform;
class CutsceneAnimation;
class GolCamera;
class GolCollidableEntity;
class GolD3DRenderDevice;
class GolExport;
class GolModelEntity;
class GolRenderDevice;
class Racer;
class RacerContext;
class RacerPhysics;

struct CutsceneParticleRef;

// SIZE 0x3d0
class CarVisuals {
public:
	// SIZE 0x68
	class InitParams {
	public:
		GolModelEntity* m_bodyModel;         // 0x00
		GolAnimatedEntity* m_secondaryModel; // 0x04
		GolAnimatedEntity* m_carEntity;      // 0x08
		GolAnimatedEntity* m_driverEntity;   // 0x0c
		GolVec3 m_driverMountOffset;         // 0x10
		Racer* m_racer;                      // 0x1c
		LegoFloat m_shadowWidth;             // 0x20
		LegoFloat m_shadowLength;            // 0x24
		LegoFloat m_frontSkidWidth;          // 0x28
		LegoFloat m_rearSkidWidth;           // 0x2c
		GolName m_materialName;              // 0x30
		GolVec3 m_wheelOffsets[4];           // 0x38
	};

	enum {
		c_flagVisible = 1 << 1,
		c_flagShadowEnabled = 1 << 2,
		c_flagSkidding = 1 << 3,
		c_flagShadowVisible = 1 << 4,
		c_flagSliding = 1 << 8,
		c_flagAirborne = 1 << 9,
		c_flagVisible0 = 1 << 10,
		c_flagVisible1 = 1 << 11,
		c_flagVisible2 = 1 << 12,
		c_alphaOverrideFlag = 1,
		c_fadeAlphaMax = 0xbf,
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
		c_reactionHit = 1 << 1,
		c_wheelSkidActive = 1 << 0,
		c_wheelSkidGrounded = 1 << 1,
		c_wheelSkidFading = 1 << 2,
		c_wheelSkidAllButActive = 0xfe,
	};

	CarVisuals();
	void Reset();
	void Initialize(InitParams* p_params, RacerContext* p_context);
	void InitializeVisuals(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
	void RefreshCarMaterial();
	void UseTurboSkidMaterial();
	void UseNormalSkidMaterial();
	void Destroy();
	void ShowModels();
	void HideModels();
	void StartSkidEffects();
	void StopSkidEffects();
	void SetWheelParticle(LegoU32 p_wheelIndex, const LegoChar* p_name);
	void ClearWheelParticle(LegoU32 p_wheelIndex);
	void StartDust();
	void StartCarSmoke();
	void Update(LegoU32 p_elapsedMs);
	void SnapVisuals();
	void UpdateBodyLean(LegoS32 p_elapsedMs);
	void UpdateDriver(LegoU32 p_elapsedMs);
	void UpdateSkidMarks(LegoU32 p_elapsedMs);
	void UpdateCurseEntity(LegoU32 p_elapsedMs);
	void UpdateShadow(GolCamera* p_camera);
	void Draw(GolD3DRenderDevice* p_renderer);
	void DrawTransparent(GolD3DRenderDevice* p_renderer);
	void StartTurboEffects();
	void StopTurboEffects();
	void StartSlideSkid();
	void StopSlideSkid();
	LegoBool32 IntersectSegment(const GolVec3* p_start, const GolVec3* p_end, GolVec3* p_hit);
	void RenderShadowSilhouette(GolD3DRenderDevice* p_renderer);
	void RebuildEntityGroup();
	void SetColorTransform(ColorTransform* p_transform);
	void ClearColorTransform();
	void FlashColor(ColorTransform* p_transform, undefined4 p_durationMs);
	void EndFlash();
	void SetScale(LegoFloat p_scale);
	void ResetDriverAnimation();
	void PlayForwardAnimation();
	void PlayReverseAnimation();
	~CarVisuals();

	GolAnimatedEntity* GetCarEntity() const { return m_carEntity; }
	void SetReactionFlags(LegoU32 p_flags) { m_reactionFlags |= p_flags; }

	LegoU32 m_flags;                                          // 0x000
	GolWorldEntityGroup m_entityGroup;                        // 0x004
	GolModelEntity* m_bodyModelEntity;                        // 0x03c
	GolAnimatedEntity* m_secondaryEntity;                     // 0x040
	GolAnimatedEntity* m_carEntity;                           // 0x044
	GolAnimatedEntity* m_driverEntity;                        // 0x048
	GolVec3 m_driverMountOffset;                              // 0x04c
	GolVec3 m_shadowDirection;                                // 0x058
	GolCollidableEntity* m_trackCollidable;                   // 0x064
	LegoFloat m_modelDistances[3];                            // 0x068
	GolName m_shadowTextureName;                              // 0x074
	RaceDecalManager::Trail::Decal m_shadowDecal;             // 0x07c
	LegoFloat m_shadowWidth;                                  // 0x198
	LegoFloat m_shadowLength;                                 // 0x19c
	LegoFloat m_frontSkidWidth;                               // 0x1a0
	LegoFloat m_rearSkidWidth;                                // 0x1a4
	GolVec3 m_wheelOffsets[4];                                // 0x1a8
	Racer* m_racer;                                           // 0x1d8
	RacerPhysics* m_racerPhysics;                             // 0x1dc
	RaceDecalManager* m_skidMarkManager;                      // 0x1e0
	RaceDecalManager::Trail* m_skidMarks[4];                  // 0x1e4
	LegoU8 m_wheelSkidFlags[4];                               // 0x1f4
	LegoU32 m_wheelAirTimers[4];                              // 0x1f8
	undefined4 m_skidFadeTimers[4];                           // 0x208
	GolBillboard::ManagedMaterialTable m_shadowMaterialTable; // 0x218
	GolBillboard::ManagedMaterialTable m_skidMaterialTable;   // 0x224
	CutsceneParticleRef* m_wheelParticles[4];                 // 0x230
	GolName m_wheelParticleNames[4];                          // 0x240
	LegoU32 m_wheelParticleFromRace[4];                       // 0x260
	CutsceneParticleRef* m_dustParticle;                      // 0x270
	CutsceneParticleRef* m_tireSmokeParticle;                 // 0x274
	CutsceneParticleRef* m_carSmokeParticle;                  // 0x278
	CutsceneAnimation* m_particleAnimation;                   // 0x27c
	CutsceneAnimation* m_sharedParticleAnimation;             // 0x280
	GolAnimatedEntity m_curseEntity;                          // 0x284
	LegoU32 m_cursePhaseMs;                                   // 0x378
	LegoU32 m_curseBlendMs;                                   // 0x37c
	Racer* m_nearbyRacer;                                     // 0x380
	LegoU32 m_reactionFlags;                                  // 0x384
	LegoU32 m_lookCooldownMs;                                 // 0x388
	LegoFloat m_lastSpeed;                                    // 0x38c
	undefined4 m_unk0x390;                                    // 0x390
	undefined4 m_unk0x394;                                    // 0x394
	LegoFloat m_pitchLean;                                    // 0x398
	LegoFloat m_rollLean;                                     // 0x39c
	ColorTransform m_baseColorTransform;                      // 0x3a0
	LegoU32 m_hasColorTransform;                              // 0x3c0
	LegoU32 m_isFlashing;                                     // 0x3c4
	LegoU32 m_flashTimerMs;                                   // 0x3c8
	LegoU32 m_lastGroundedWheelCount;                         // 0x3cc
};

#endif // CARVISUALS_H
