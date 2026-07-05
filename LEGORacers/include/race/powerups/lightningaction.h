#ifndef LIGHTNINGACTION_H
#define LIGHTNINGACTION_H

#include "race/powerups/beammesh.h"
#include "race/powerups/weaponactionbase.h"

class CutsceneAnimation;
class GolBillboard;
class MabMaterialTrack;
class SpatialSoundInstance;

struct CutsceneParticleRef;
struct SoundVector;

// VTABLE: LEGORACERS 0x004b15a8
// SIZE 0x24c
class LightningAction : public WeaponActionBase {
public:
	enum {
		c_stateUnloaded = 0,
		c_stateReady = 1,
		c_stateRampIn = 2,
		c_stateSustain = 3,
		c_stateFade = 4,
		c_stateDone = 6,
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
		c_flashRedGrnOffset = 0xe1,
		c_flashBluOffset = 0xff,
		c_randomTableMask = 0x3ff,
		c_randomOffsetRange = 0x32,
	};

	LightningAction();
	~LightningAction() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x004585d0
	// LightningAction::`vector deleting destructor'

	void Update(LegoU32 p_elapsedMs) override;                     // vtable+0x08
	void DrawTransparent(GolD3DRenderDevice* p_renderer) override; // vtable+0x10
	void AdvanceState() override;                                  // vtable+0x14
	void Deactivate() override;                                    // vtable+0x1c
	void OnHitRacer(Racer* p_racer) override;                      // vtable+0x20
	void GetProjectilePosition(GolVec3* p_position) override;      // vtable+0x24
	void GetProjectileVelocity(GolVec3* p_velocity) override;      // vtable+0x28

	void Initialize(GolExport* p_export, RacePowerupManager* p_manager);
	void AcquireSound();
	void Destroy();
	void AdvanceJitter();
	void FillJitterTable();
	void RebuildBolt();
	void Activate(Racer* p_racer, ActionTarget* p_target);
	void UpdateSound(LegoU32 p_elapsedMs);
	void UpdateBoltPath();
	void FindVictim();
	void UpdateHitParticle();

private:
	BeamMesh m_beam;                    // 0x030
	GolVec3 m_boltPoints[4];            // 0x1a0
	LegoFloat m_jitterTable[20];        // 0x1d0
	LegoU32 m_jitterCursor;             // 0x220
	LegoU32 m_jitterTimerMs;            // 0x224
	undefined4 m_unk0x228;              // 0x228
	LegoU32 m_crackleTimerMs;           // 0x22c
	LegoFloat m_boltLength;             // 0x230
	undefined4 m_unk0x234;              // 0x234
	SpatialSoundInstance* m_sound;      // 0x238
	RaceActionSource* m_source;         // 0x23c
	LegoU32 m_shockTimerMs;             // 0x240
	CutsceneParticleRef* m_hitParticle; // 0x244
	GolBillboard* m_flashBillboard;     // 0x248
};

#endif // LIGHTNINGACTION_H
