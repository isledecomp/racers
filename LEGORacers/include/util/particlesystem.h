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

	undefined4 GetUnk0xb8() const { return m_unk0x0b8; }

	void Reset();

	void FUN_00412430(GolExport* p_golExport, GolD3DRenderDevice* p_renderer, LegoU32 p_param3, LegoU32 p_param4);

	Particle* FUN_00412760(GolVec3* p_param1, GolVec3* p_param2, LegoU32 p_param3);
	void FUN_00412820();
	void FUN_00412840();
	void FUN_00412890(LegoS32 p_param);
	void FUN_00412970();
	Particle* FUN_00412a00();
	void FUN_00412a50(GolD3DRenderDevice* p_renderer);

private:
	enum {
		c_flagInitialized = 0x1 << 0,
		c_flagActive = 0x1 << 1,
		c_flagBit2 = 0x1 << 2,
		c_flagBit3 = 0x1 << 3,
		c_flagPendingReset = 0x1 << 4,
	};

	GolExport* m_unk0x000;                    // 0x000
	GolModelBase* m_unk0x004;                 // 0x004
	undefined4 m_unk0x008;                    // 0x008
	undefined4 m_unk0x00c;                    // 0x00c
	GolModelEntity m_unk0x010;                // 0x010
	LegoU32 m_unk0x0a0;                       // 0x0a0
	LegoU32 m_unk0x0a4;                       // 0x0a4
	LegoU32 m_unk0x0a8;                       // 0x0a8
	Particle* m_unk0x0ac;                     // 0x0ac
	Particle* m_unk0x0b0;                     // 0x0b0
	Particle* m_unk0x0b4;                     // 0x0b4
	LegoU32 m_unk0x0b8;                       // 0x0b8
	GolVec3 m_unk0x0bc;                       // 0x0bc
	LegoU32 m_unk0x0c8;                       // 0x0c8
	MabMaterialAnimationItem0x8* m_unk0x0cc;  // 0x0cc
	MabMaterialAnimationItem0x18* m_unk0x0d0; // 0x0d0
	DuskwindBananaRelic0x24* m_unk0x0d4;      // 0x0d4
	undefined4 m_unk0x0d8;                    // 0x0d8
	undefined4 m_unk0x0dc;                    // 0x0dc
	undefined4 m_unk0x0e0;                    // 0x0e0
	undefined4 m_unk0x0e4;                    // 0x0e4
	undefined4 m_unk0x0e8;                    // 0x0e8
	undefined m_unk0x0ec[0x120 - 0xec];       // 0x0ec
	undefined4 m_unk0x120;                    // 0x120
	undefined4 m_unk0x124;                    // 0x124
	undefined4 m_unk0x128;                    // 0x128
	undefined4 m_unk0x12c;                    // 0x12c
	undefined4 m_unk0x130;                    // 0x130
	undefined4 m_unk0x134;                    // 0x134
	undefined4 m_unk0x138;                    // 0x138
	undefined4 m_unk0x13c;                    // 0x13c
};

#endif // PARTICLESYSTEM_H
