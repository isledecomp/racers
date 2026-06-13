#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "decomp.h"
#include "golmodelentity.h"
#include "types.h"

class DuskwindBananaRelic0x24;
class GolExport;
class GolD3DRenderDevice;
class MabMaterialAnimationItem0x18;
class MabMaterialAnimationItem0x8;
class Particle;

class ParticleSystem {
public:
	ParticleSystem();
	~ParticleSystem();

	void Destroy();

	LegoBool32 IsActive() const { return m_flags & c_flagActive; }

	void Reset();

	void FUN_00412430(GolExport* p_golExport, GolD3DRenderDevice* p_renderer, LegoU32 p_param3, LegoU32 p_param4);
	void ConfigureMaterialAnimation(
		MabMaterialAnimationItem0x18* p_animation,
		MabMaterialAnimationItem0x8* p_items,
		LegoU32 p_itemCount,
		LegoFloat p_unk0x1c,
		LegoFloat p_unk0x20,
		LegoFloat p_unk0x24,
		LegoFloat p_unk0x28,
		LegoFloat p_radius,
		const GolVec3* p_position
	);
	void ConfigureMaterial(
		DuskwindBananaRelic0x24* p_material,
		LegoFloat p_unk0x1c,
		LegoFloat p_unk0x20,
		LegoFloat p_unk0x24,
		LegoFloat p_unk0x28,
		LegoFloat p_radius,
		const GolVec3* p_position
	);

	Particle* SpawnParticle(GolVec3* p_position, GolVec3* p_velocity, LegoU32 p_lifetimeMs);
	void RequestDeactivate();
	void Deactivate();
	void Update(LegoS32 p_elapsedMs);
	void ResetParticlePool();
	Particle* AllocateParticle();
	void FUN_00412a50(GolD3DRenderDevice* p_renderer);

private:
	enum {
		c_flagInitialized = 0x1 << 0,
		c_flagActive = 0x1 << 1,
		c_flagBit2 = 0x1 << 2,
		c_flagBit3 = 0x1 << 3,
		c_flagPendingReset = 0x1 << 4,
	};

	void ConfigureCommon(
		LegoFloat p_unk0x1c,
		LegoFloat p_unk0x20,
		LegoFloat p_unk0x24,
		LegoFloat p_unk0x28,
		LegoFloat p_radius,
		const GolVec3* p_position
	);

	GolExport* m_golExport;                            // 0x000
	GolModelBase* m_model;                             // 0x004
	undefined4 m_unk0x008;                             // 0x008
	undefined4 m_unk0x00c;                             // 0x00c
	GolModelEntity m_modelEntity;                      // 0x010
	LegoU32 m_unk0x0a0;                                // 0x0a0
	LegoU32 m_unk0x0a4;                                // 0x0a4
	LegoU32 m_particleCapacity;                        // 0x0a8
	Particle* m_particles;                             // 0x0ac
	Particle* m_freeList;                              // 0x0b0
	Particle* m_activeList;                            // 0x0b4
	LegoU32 m_flags;                                   // 0x0b8
	GolVec3 m_acceleration;                            // 0x0bc
	LegoU32 m_materialItemCount;                       // 0x0c8
	MabMaterialAnimationItem0x8* m_materialItems;      // 0x0cc
	MabMaterialAnimationItem0x18* m_materialAnimation; // 0x0d0
	DuskwindBananaRelic0x24* m_material;               // 0x0d4
	LegoFloat m_unk0x0d8;                              // 0x0d8
	LegoFloat m_unk0x0dc;                              // 0x0dc
	LegoFloat m_unk0x0e0;                              // 0x0e0
	LegoFloat m_unk0x0e4;                              // 0x0e4
	undefined4 m_spawnedCount;                         // 0x0e8
	undefined m_unk0x0ec[0x120 - 0xec];                // 0x0ec
	undefined4 m_unk0x120;                             // 0x120
	undefined4 m_unk0x124;                             // 0x124
	undefined4 m_unk0x128;                             // 0x128
	undefined4 m_unk0x12c;                             // 0x12c
	undefined4 m_unk0x130;                             // 0x130
	undefined4 m_unk0x134;                             // 0x134
	undefined4 m_unk0x138;                             // 0x138
	undefined4 m_unk0x13c;                             // 0x13c
};

#endif // PARTICLESYSTEM_H
