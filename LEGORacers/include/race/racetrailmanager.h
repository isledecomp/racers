#ifndef RACETRAILMANAGER_H
#define RACETRAILMANAGER_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "surface/color.h"
#include "types.h"

class GolMaterial;
class GolD3DRenderDevice;
class GolExport;
class GolModelBase;

// VTABLE: LEGORACERS 0x004b47a0
// SIZE 0x0c
class RaceTrailManager {
public:
	RaceTrailManager();
	virtual ~RaceTrailManager(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x004937d0
	// RaceTrailManager::`scalar deleting destructor'

	void Destroy();

	// VTABLE: LEGORACERS 0x004b4794
	// SIZE 0x2a4
	class Trail {
	public:
		// SIZE 0x1c
		class Params {
		public:
			LegoU32 m_durationMs;  // 0x00
			LegoU32 m_sampleCount; // 0x04
			LegoU32 m_pointCount;  // 0x08
			LegoU32 m_unk0x0c;     // 0x0c
			LegoU32 m_unk0x10;     // 0x10
			LegoFloat m_endScale;  // 0x14
			LegoFloat m_endAlpha;  // 0x18
		};

		// SIZE 0x4c
		class Sample {
		public:
			LegoU32 m_durationMs; // 0x00
			GolVec3 m_points[5];  // 0x04
			GolVec3 m_center;     // 0x40
		};

		enum {
			c_active = 1 << 0,
			c_released = 1 << 1,
			c_flags0x09cBit2 = 1 << 2,
			c_firstSample = 1 << 3,
			c_saturated = 1 << 4,
			c_drawable = 1 << 5,
		};

		Trail();
		virtual ~Trail(); // vtable+0x00

		// SYNTHETIC: LEGORACERS 0x00493950
		// RaceTrailManager::Trail::`vector deleting destructor'

		void Initialize(GolD3DRenderDevice* p_renderer, GolExport* p_golExport);
		void SetMaterial(GolD3DRenderDevice* p_renderer, GolMaterial* p_material);
		void SetColor(const ColorRGBA* p_color);
		void Start(Params* p_params);
		void Release();
		void Update(LegoU32 p_elapsedMs);
		void AdvanceTail(LegoU32 p_elapsedMs);
		void AddSampleWithCenter(LegoU32 p_elapsedMs, GolVec3* p_positions, GolVec3 p_center);
		void AddSample(LegoU32 p_elapsedMs, GolVec3* p_positions);
		void RebuildGeometry();
		void FUN_004513d0(GolD3DRenderDevice* p_renderer);
		void Destroy();
		void DrawTransparent(GolD3DRenderDevice* p_renderer);
		LegoU8 GetFlags() const { return m_flags; }
		LegoBool32 IsActive() const { return m_flags & c_active; }

	private:
		friend class RaceTrailManager;

		void Reset();

		GolExport* m_golExport;              // 0x004
		GolModelBase* m_model;               // 0x008
		GolModelEntity m_entity;             // 0x00c
		LegoU8 m_flags;                      // 0x09c
		undefined m_unk0x09d[0x0a0 - 0x09d]; // 0x09d
		LegoU32 m_durationMs;                // 0x0a0
		LegoU32 m_sampleMs;                  // 0x0a4
		LegoU32 m_headIndex;                 // 0x0a8
		LegoU32 m_tailIndex;                 // 0x0ac
		LegoU32 m_unk0x0b0;                  // 0x0b0
		LegoU32 m_sampleCount;               // 0x0b4
		LegoU32 m_ringSize;                  // 0x0b8
		LegoU32 m_pointCount;                // 0x0bc
		LegoU32 m_unk0x0c0;                  // 0x0c0
		LegoFloat m_centerX;                 // 0x0c4
		LegoFloat m_centerY;                 // 0x0c8
		LegoFloat m_centerZ;                 // 0x0cc
		LegoFloat m_endScale;                // 0x0d0
		LegoFloat m_endAlpha;                // 0x0d4
		ColorRGBA m_color;                   // 0x0d8
		Sample m_samples[6];                 // 0x0dc
	};

	LegoU32 DrawOpaque(GolD3DRenderDevice* p_renderer);
	LegoU32 DrawTransparent(GolD3DRenderDevice* p_renderer);
	Trail* AcquireTrail(Trail::Params* p_params);
	void ReleaseTrail(Trail* p_trail);
	LegoU32 Update(LegoU32 p_elapsedMs);
	void Initialize(GolD3DRenderDevice* p_renderer, GolExport* p_golExport, LegoU32 p_trailCount);

private:
	Trail* m_trails;      // 0x04
	LegoU32 m_trailCount; // 0x08
};

#endif // RACETRAILMANAGER_H
