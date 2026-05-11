#ifndef AQUACORAL0X37B8_H
#define AQUACORAL0X37B8_H

#include "decomp.h"
#include "glassblock0x3368.h"
#include "glassshard0x3b8.h"
#include "glassstream0x94.h"
#include "legoracers.h"
#include "types.h"

// SIZE 0x37b8
class AquaCoral0x37b8 {
public:
	AquaCoral0x37b8();
	~AquaCoral0x37b8();

	static void FUN_0042b130(LegoRacers::Context* p_context);

	LegoS32 Initialize(LegoRacers::Context* p_context);
	void Run();
	void Shutdown();

private:
	void ReleaseContextAssets();
	LegoS32 InitializeRaceScene();

	LegoRacers::Context* m_context; // 0x00
	GlassStream0x94 m_unk0x04;      // 0x04
	GlassBlock0x3368 m_unk0x98;     // 0x98
	GlassShard0x3b8 m_unk0x3400;    // 0x3400
};

#endif // AQUACORAL0X37B8_H
