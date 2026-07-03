#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "decomp.h"
#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golmodelentity.h"
#include "surface/color.h"
#include "types.h"

class GolMaterial;
class GolExport;
class GolD3DRenderDevice;
class MabMaterialTrack;
class MabMaterialFrame;
class Particle;

class ParticleSystem {
public:
	ParticleSystem();
	~ParticleSystem();

	void Destroy();

	LegoBool32 IsActive() const { return m_flags & c_flagActive; }
	LegoU32 GetSpawnedCount() const { return m_spawnedCount; }

	void Reset();

	void Initialize(
		GolExport* p_golExport,
		GolD3DRenderDevice* p_renderer,
		LegoU32 p_materialCapacity,
		LegoU32 p_particleCapacity
	);
	void ConfigureMaterialAnimation(
		MabMaterialTrack* p_animation,
		MabMaterialFrame* p_items,
		LegoU32 p_itemCount,
		LegoFloat p_startSizeUp,
		LegoFloat p_startSizeForward,
		LegoFloat p_sizeGrowthUp,
		LegoFloat p_sizeGrowthForward,
		LegoFloat p_radius,
		const GolVec3* p_position
	);
	void ConfigureMaterial(
		GolMaterial* p_material,
		LegoFloat p_startSizeUp,
		LegoFloat p_startSizeForward,
		LegoFloat p_sizeGrowthUp,
		LegoFloat p_sizeGrowthForward,
		LegoFloat p_radius,
		const GolVec3* p_position
	);

	Particle* SpawnParticle(GolVec3* p_position, GolVec3* p_velocity, LegoU32 p_lifetimeMs);
	void RequestDeactivate();
	void Deactivate();
	void Update(LegoS32 p_elapsedMs);
	void ResetParticlePool();
	Particle* AllocateParticle();
	void Draw(GolD3DRenderDevice* p_renderer);

private:
	enum {
		c_flagInitialized = 0x1 << 0,
		c_flagActive = 0x1 << 1,
		c_flagSizeAnimated = 0x1 << 2,
		c_flagBit3 = 0x1 << 3,
		c_flagPendingReset = 0x1 << 4,
	};

	void ConfigureCommon(
		LegoFloat p_startSizeUp,
		LegoFloat p_startSizeForward,
		LegoFloat p_sizeGrowthUp,
		LegoFloat p_sizeGrowthForward,
		LegoFloat p_radius,
		const GolVec3* p_position
	);
	void BeginMaterialGroup(GolMaterial* p_material);
	void EmitQuad(Particle* p_particle);
	LegoU32 FlushBatch();

	GolExport* m_golExport;                 // 0x000
	GolModelBase* m_model;                  // 0x004
	GdbVertexArray* m_vertices;             // 0x008
	GdbModelIndexArray::Indices* m_indices; // 0x00c
	GolModelEntity m_modelEntity;           // 0x010
	LegoU32 m_triangleCapacity;             // 0x0a0
	LegoU32 m_materialCapacity;             // 0x0a4
	LegoU32 m_particleCapacity;             // 0x0a8
	Particle* m_particles;                  // 0x0ac
	Particle* m_freeList;                   // 0x0b0
	Particle* m_activeList;                 // 0x0b4
	LegoU32 m_flags;                        // 0x0b8
	GolVec3 m_acceleration;                 // 0x0bc
	LegoU32 m_materialItemCount;            // 0x0c8
	MabMaterialFrame* m_materialItems;      // 0x0cc
	MabMaterialTrack* m_materialAnimation;  // 0x0d0
	GolMaterial* m_material;                // 0x0d4
	LegoFloat m_startSizeUp;                // 0x0d8
	LegoFloat m_startSizeForward;           // 0x0dc
	LegoFloat m_sizeGrowthUp;               // 0x0e0
	LegoFloat m_sizeGrowthForward;          // 0x0e4
	LegoU32 m_spawnedCount;                 // 0x0e8
	GolVec3 m_cameraForward;                // 0x0ec
	GolVec3 m_cameraUp;                     // 0x0f8
	GolVec3 m_scaledCameraUp;               // 0x104
	GolVec3 m_scaledCameraForward;          // 0x110
	ColorRGBA m_particleColor;              // 0x11c
	LegoU32 m_materialCount;                // 0x120
	LegoU32 m_firstBatchVertex;             // 0x124
	LegoU32 m_firstBatchTriangle;           // 0x128
	LegoU32 m_vertexCount;                  // 0x12c
	LegoU32 m_triangleCount;                // 0x130
	LegoU32 m_groupCount;                   // 0x134
	LegoU32 m_batchVertexCount;             // 0x138
	LegoU32 m_batchTriangleCount;           // 0x13c
};

#endif // PARTICLESYSTEM_H
