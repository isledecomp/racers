#ifndef CUTSCENEPARTICLE_H
#define CUTSCENEPARTICLE_H

#include "decomp.h"
#include "golmath.h"
#include "menu/runtime/cutsceneplayer.h"
#include "types.h"
#include "util/particlesystem.h"

class GolD3DRenderDevice;
class GolExport;

// SIZE 0x18c
class CutsceneParticle {
public:
	CutsceneParticle();
	~CutsceneParticle();

	LegoBool32 IsActive() const { return m_particleSystem.IsActive(); }
	CutsceneAnimation::Emitter* GetEmitter() const { return m_emitter; }
	CutsceneParticleRef* GetRef() const { return m_ref; }
	GolMatrix3* GetBasis() { return &m_basis; }
	LegoU32 GetSpawnedCount() const { return m_particleSystem.GetSpawnedCount(); }
	void SetRef(CutsceneParticleRef* p_ref) { m_ref = p_ref; }

	void Destroy();
	void Reset();
	void Initialize(GolExport* p_golExport, GolD3DRenderDevice* p_renderer);
	void SetOrientation(GolVec3* p_param1, GolVec3* p_param2);
	void SetPosition(GolVec3* p_vec);
	void SetVelocity(GolVec3* p_vec);
	void ActivateEmitter(CutsceneAnimation::Emitter* p_runtime);
	void Deactivate();
	void Finish();
	void Update(LegoU32 p_elapsedMs);
	void DrawTransparent(GolD3DRenderDevice* p_renderer);
	void Draw(GolD3DRenderDevice* p_renderer);

private:
	CutsceneAnimation::Emitter* m_emitter; // 0x000
	CutsceneParticleRef* m_ref;            // 0x004
	ParticleSystem m_particleSystem;       // 0x008
	GolVec3 m_velocity;                    // 0x148
	GolVec3 m_position;                    // 0x154
	GolMatrix3 m_basis;                    // 0x160
	LegoU32 m_emitTimerMs;                 // 0x184
	LegoU32 m_ageMs;                       // 0x188
};

#endif // CUTSCENEPARTICLE_H
