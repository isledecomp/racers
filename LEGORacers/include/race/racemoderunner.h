#ifndef RACEMODERUNNER_H
#define RACEMODERUNNER_H

#include "app/legoracers.h"
#include "decomp.h"
#include "race/glassblock0x3368.h"
#include "race/glassshard0x3b8.h"
#include "race/glassstream0x94.h"
#include "types.h"

// SIZE 0x37b8
class RaceModeRunner {
public:
	RaceModeRunner();
	~RaceModeRunner();

	static void Run(LegoRacers::Context* p_context);

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

#endif // RACEMODERUNNER_H
