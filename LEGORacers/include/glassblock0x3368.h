#ifndef GLASSBLOCK0X3368_H
#define GLASSBLOCK0X3368_H

#include "cactusinterface0x4.h"
#include "compat.h"
#include "decomp.h"
#include "legoracers.h"
#include "types.h"

class GlassShard0x3b8;

// VTABLE: LEGORACERS 0x004b07f4
// SIZE 0x3368
class GlassBlock0x3368 : public CactusInterface0x4 {
public:
	GlassBlock0x3368();
	~GlassBlock0x3368();
	void VTable0x00() override; // vtable+0x00
	LegoS32 Initialize(
		LegoRacers::Context* p_context,
		const LegoChar* p_raceName,
		undefined4 p_unk0x0c,
		GlassShard0x3b8* p_glassShard
	);
	void Shutdown();
	void Run();
	virtual void VTable0x30(); // vtable+0x30

private:
	undefined4* m_unk0x04;                  // 0x04
	undefined m_unk0x08[0x3334 - 0x08];     // 0x08
	undefined4 m_unk0x3334;                 // 0x3334
	undefined m_unk0x3338[0x3368 - 0x3338]; // 0x3338
};

#endif // GLASSBLOCK0X3368_H
