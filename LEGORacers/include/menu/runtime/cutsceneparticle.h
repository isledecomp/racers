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

	LegoU8 GetSordidUnk0xb8() const { return (LegoU8) m_unk0x008.GetUnk0xb8(); }

	void Destroy();
	void Reset();
	void FUN_00489520(GolExport* p_golExport, GolD3DRenderDevice* p_renderer);
	void FUN_00489540(GolVec3* p_param1, GolVec3* p_param2);
	void FUN_00489660(GolVec3* p_vec);
	void FUN_004897a0();
	void FUN_004897c0();
	void FUN_004897e0(LegoU32 p_elapsedMs);
	void FUN_00489960(GolD3DRenderDevice* p_renderer);
	void FUN_004513d0(GolD3DRenderDevice* p_renderer);

private:
	CutsceneAnimation::Runtime* m_unk0x000; // 0x000
	undefined4 m_unk0x004;                  // 0x004
	ParticleSystem m_unk0x008;              // 0x008
	GolVec3 m_unk0x148;                     // 0x148
	GolVec3 m_unk0x154;                     // 0x154
	GolMatrix3 m_unk0x160;                  // 0x160
	undefined4 m_unk0x184;                  // 0x184
	undefined4 m_unk0x188;                  // 0x188
};

#endif // CUTSCENEPARTICLE_H
