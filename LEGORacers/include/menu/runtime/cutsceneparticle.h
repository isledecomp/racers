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

	LegoBool32 IsActive() const { return m_unk0x008.IsActive(); }
	CutsceneAnimation::Runtime* GetRuntime() const { return m_unk0x000; }
	CutsceneParticleRef* GetRef() const { return m_ref; }
	GolMatrix3* GetUnk0x160() { return &m_unk0x160; }
	void SetRef(CutsceneParticleRef* p_ref) { m_ref = p_ref; }

	void Destroy();
	void Reset();
	void FUN_00489520(GolExport* p_golExport, GolD3DRenderDevice* p_renderer);
	void FUN_00489540(GolVec3* p_param1, GolVec3* p_param2);
	void FUN_00489660(GolVec3* p_vec);
	void ActivateRuntime(CutsceneAnimation::Runtime* p_runtime);
	void FUN_004897a0();
	void FUN_004897c0();
	void FUN_004897e0(LegoU32 p_elapsedMs);
	void FUN_00489960(GolD3DRenderDevice* p_renderer);
	void FUN_004513d0(GolD3DRenderDevice* p_renderer);

private:
	CutsceneAnimation::Runtime* m_unk0x000; // 0x000
	CutsceneParticleRef* m_ref;             // 0x004
	ParticleSystem m_unk0x008;              // 0x008
	GolVec3 m_unk0x148;                     // 0x148
	GolVec3 m_unk0x154;                     // 0x154
	GolMatrix3 m_unk0x160;                  // 0x160
	undefined4 m_unk0x184;                  // 0x184
	undefined4 m_unk0x188;                  // 0x188
};

#endif // CUTSCENEPARTICLE_H
