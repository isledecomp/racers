#ifndef GLASSSTREAM0X94_H
#define GLASSSTREAM0X94_H

#include "cactusinterface0x4.h"
#include "celestialforge0x48.h"
#include "compat.h"
#include "decomp.h"
#include "legoracers.h"
#include "types.h"

class GlassBlock0x3368;

// VTABLE: LEGORACERS 0x004aff70
// SIZE 0x94
class GlassStream0x94 : public CactusInterface0x4 {
public:
	GlassStream0x94();
	virtual ~GlassStream0x94(); // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0041ec70
	// GlassStream0x94::`scalar deleting destructor'

	void Reset();
	LegoS32 Initialize(LegoRacers::Context* p_context, GlassBlock0x3368* p_block);
	void Shutdown();

private:
	CelestialForge0x48 m_unk0x04;   // 0x04
	LegoRacers::Context* m_context; // 0x4c
	GlassBlock0x3368* m_unk0x50;    // 0x50
	undefined4 m_unk0x54[2][4][2];  // 0x54
};

#endif // GLASSSTREAM0X94_H
