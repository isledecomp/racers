#ifndef PARTICLE0X18C_H
#define PARTICLE0X18C_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"
#include "util/sordidwatch0x140.h"

class GolD3DRenderDevice;
class GolExport;

// SIZE 0x18c
class Particle0x18c {
public:
	Particle0x18c();
	~Particle0x18c();

	LegoU8 GetSordidUnk0xb8() const { return (LegoU8) m_unk0x008.GetUnk0xb8(); }

	void Reset();
	void FUN_00489520(GolExport* p_golExport, GolD3DRenderDevice* p_renderer);
	void FUN_00489540(GolVec3* p_param1, GolVec3* p_param2);
	void FUN_00489660(GolVec3* p_vec);
	void FUN_004897a0();
	void FUN_004897e0(LegoU32 p_elapsedMs);
	void FUN_00489960(GolD3DRenderDevice* p_renderer);
	void FUN_004513d0(GolD3DRenderDevice* p_renderer);

private:
	undefined4 m_unk0x000;       // 0x000
	undefined4 m_unk0x004;       // 0x004
	SordidWatch0x140 m_unk0x008; // 0x008
	undefined4 m_unk0x148;       // 0x184
	undefined4 m_unk0x14c;       // 0x184
	undefined4 m_unk0x150;       // 0x184
	GolVec3 m_unk0x154;          // 0x154
	GolMatrix3 m_unk0x160;       // 0x160
	undefined4 m_unk0x184;       // 0x184
	undefined4 m_unk0x188;       // 0x188
};

#endif // PARTICLE0X18C_H
