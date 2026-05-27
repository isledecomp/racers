#ifndef PARTICLE0X18C_H
#define PARTICLE0X18C_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

class GolD3DRenderDevice;
class GolExport;

// SIZE 0x18c
class Particle0x18c {
public:
	Particle0x18c();
	~Particle0x18c();

	LegoU8 GetFlags() const { return m_flags; }
	void FUN_00489520(GolExport* p_golExport, GolD3DRenderDevice* p_renderer);
	void FUN_00489540(GolVec3* p_param1, GolVec3* p_param2);
	void FUN_00489660(GolVec3* p_vec);
	void FUN_004897e0(LegoU32 p_elapsedMs);
	void FUN_00489960(GolD3DRenderDevice* p_renderer);
	void FUN_004513d0(GolD3DRenderDevice* p_renderer);

private:
	undefined m_unk0x000[0xc0];          // 0x000
	LegoU8 m_flags;                      // 0x0c0
	undefined m_unk0x0c1[0x154 - 0x0c1]; // 0x0c1
	GolVec3 m_unk0x154;                  // 0x154
	GolMatrix3 m_unk0x160;               // 0x160
	undefined m_unk0x184[0x18c - 0x184]; // 0x184
};

#endif // PARTICLE0X18C_H
